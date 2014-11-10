#ifndef TED_LIST_H
#define TED_LIST_H

ted_Obj *ted_List_new();
ted_Obj *ted_List_at_index(ted_Obj *, int);
ted_Obj *ted_List_pop(ted_Obj *);
void ted_List_append(ted_Obj *, ted_Obj *item);


#define ted_List_len(o) \
    (((ted_List *)o)->l_len)

#endif
