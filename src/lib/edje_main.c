/*
 * vim:ts=8:sw=3:sts=8:noexpandtab:cino=>5n-3f0^-2{2
 */

#include "Edje.h"
#include "edje_private.h"
#include <time.h>

static int initted = 0;

/************************** API Routines **************************/

/** Initialize the EDJE library.
 *
 * @return The new init count.
 */
int
edje_init(void)
{
   initted++;
   if (initted == 1)
     {
	srand(time(NULL));
	_edje_edd_setup();
	_edje_text_init();
	embryo_init();
     }
   _edje_message_init();
   return initted;
}

/** Shutdown the EDJE library.
 *
 * @return The new init count.
 */
int
edje_shutdown(void)
{
   initted--;
   if (initted > 0) return initted;

   _edje_message_shutdown();
   _edje_edd_free();
   _edje_color_class_members_free();
   _edje_color_class_hash_free();
   _edje_text_class_members_free();
   _edje_text_class_hash_free();
   embryo_shutdown();
   
   return 0;
}

/* Private Routines */

Edje *
_edje_add(Evas_Object *obj)
{
   Edje *ed;
   
   ed = calloc(1, sizeof(Edje));
   if (!ed) return NULL;
   ed->evas = evas_object_evas_get(obj);
   ed->clipper = evas_object_rectangle_add(ed->evas);
   evas_object_smart_member_add(ed->clipper, obj);
   evas_object_color_set(ed->clipper, 255, 255, 255, 255);
   evas_object_move(ed->clipper, -10000, -10000);
   evas_object_resize(ed->clipper, 20000, 20000);
   evas_object_pass_events_set(ed->clipper, 1);
   ed->have_objects = 1;
   ed->references = 1;
   return ed;
}

void
_edje_del(Edje *ed)
{
   _edje_file_del(ed);
   if (ed->path) free(ed->path);
   ed->path = NULL;
   if (ed->part) free(ed->part);
   ed->part = NULL;
   if ((ed->actions) || (ed->pending_actions))
     {
	_edje_animators = evas_list_remove(_edje_animators, ed);
     }
   while (ed->actions)
     {
	Edje_Running_Program *runp;
	
	runp = ed->actions->data;
	ed->actions = evas_list_remove(ed->actions, runp);
	free(runp);
     }
   while (ed->pending_actions)
     {
	Edje_Pending_Program *pp;
	
	pp = ed->pending_actions->data;
	ed->pending_actions = evas_list_remove(ed->pending_actions, pp);
	free(pp);
     }
   while (ed->callbacks)
     {
	Edje_Signal_Callback *escb;
	
	escb = ed->callbacks->data;
	ed->callbacks = evas_list_remove(ed->callbacks, escb);
	free(escb->signal);
	free(escb->source);
	free(escb);
     }
   while (ed->color_classes)
     {
	Edje_Color_Class *cc;
	
	cc = ed->color_classes->data;
	ed->color_classes = evas_list_remove(ed->color_classes, cc);
	if (cc->name) free(cc->name);
	free(cc);
     }
   while (ed->text_classes)
     {
	Edje_Text_Class *tc;
	
	tc = ed->text_classes->data;
	ed->text_classes = evas_list_remove(ed->text_classes, tc);
	if (tc->name) free(tc->name);
	if (tc->font) free(tc->font);
	free(tc);
     }
   free(ed);
}

void
_edje_clean_objects(Edje *ed)
{
   evas_object_del(ed->clipper);
   ed->evas = NULL;
   ed->obj = NULL;
   ed->clipper = NULL;
}

void
_edje_ref(Edje *ed)
{
   ed->references++;
}

void
_edje_unref(Edje *ed)
{
   ed->references--;
   if (ed->references <= 0) _edje_del(ed);
}
