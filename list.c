#include "ted.h"

#define TED_LIST_INIT_SIZE_MAX 1024

ted_Obj *
ted_List_new()
{
    ted_List *o;
    o = (ted_List *) ted_Obj_new(&ted_type_List);
    o->l_size_max = TED_LIST_INIT_SIZE_MAX;
    o->l_len = 0;
    o->l_root = malloc(sizeof(ted_Obj *) * TED_LIST_INIT_SIZE_MAX);
    return (ted_Obj *)o;
}

void
ted_List_append(ted_Obj *o, ted_Obj *item)
{
    ted_List *lst;

    ted_assert_is_type(&ted_type_List, o);
    lst = (ted_List *)o;
    lst->l_root[lst->l_len] = item;
    lst->l_len += 1;
    if (lst->l_len >= lst->l_size_max) {
        ted_panic("List size change not implemented");
    }
}

ted_Obj *
ted_List_at_index(ted_Obj *o, int index)
{
    ted_assert_is_type(&ted_type_List, o);
    if (ted_List_len(o) < index) {
        ted_panic("Index out of range");
    }
    return ((ted_List *)o)->l_root[index];
}

ted_Obj *
meth_append(ted_Obj *self, ted_Obj *args)
{
    int i;
    ted_Obj *o;
    ted_List *lst;

    ted_assert_is_type(&ted_type_List, args);
    lst = (ted_List *) args;
    for (i=0; i<lst->l_len; ++i) {
        ted_List_append(self, lst->l_root[i]);
    }
    return ted_None;
}

ted_Obj *
meth_pop(ted_Obj *self, ted_Obj *args)
{
    return ted_None;
}

static ted_Obj *
meth__del__(ted_Obj *self, ted_Obj *args)
{
    free(((ted_List *)self)->l_root);
    return ted_None;
}

static ted_Obj *
meth__str__(ted_Obj *self, ted_Obj *args)
{
    char *buf, *buf_p, *p;
    int i;
    ted_Obj *o;
    ted_List *lst;

    ted_assert_is_type(&ted_type_List, self);
    lst = (ted_List *)self;

    /* XXX how about a buffer overflow? */
    buf = malloc(1024 ^ 2);
    buf_p = buf;
    *buf_p = '[';
    ++buf_p;

    /* convert all objects inside of the list into strings */
    for (i=0; i<lst->l_len; ++i) {
        o = lst->l_root[i];
        p = ted_Str_to_charptr(ted_str(o));
        while (*p) {
            *buf_p = *p;
            ++buf_p;
            ++p;
        }
        *buf_p = ',';
        ++buf_p;
        *buf_p = ' ';
        ++buf_p;
    }
    --buf_p;
    --buf_p;

    *buf_p = ']';
    ++buf_p;
    *buf_p = '\0';
    o = ted_Str_new(buf);
    free(buf);
    return o;
}

static ted_method_def methods[] = {
    {"append", &meth_append},
    {"pop", &meth_pop},
    {"__str__", &meth__str__},
    {"__del__", &meth__del__},
    {NULL, NULL},
};

ted_Type ted_type_List = {
    TED_OBJECT_HEAD_INIT(&ted_type_Type),
    sizeof(ted_List),
    "list",
    methods,
};
