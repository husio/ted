#ifndef TED_LIST_H
#define TED_LIST_H

ted_Obj *ted_List_new();
ted_Obj *ted_List_at_index(ted_Obj *, int);

#define ted_List_len(o) \
    (((ted_List *)o)->l_len)

#endif
