#include "ted.h"

#include <stdio.h>
#include <string.h>



ted_Obj *
ted_Str_new(const char *s)
{
    ted_Str *o;
    o = (ted_Str *) ted_Obj_new(&ted_type_Str);
    o->s_val = strdup(s);
    o->s_len = strlen(s);
    return (ted_Obj *)o;
}

static ted_Obj *
meth__str__(ted_Obj *self, ted_Obj *args)
{
    char *buf;
    ted_Obj *o;

    ted_assert_is_type(&ted_type_Str, self);

    buf = malloc(((ted_Str *)o)->s_len + 3);
    sprintf(buf, "\"%s\"", ((ted_Str *)self)->s_val);
    o = ted_Str_new(buf);
    free(buf);
    return o;
}

static ted_Obj *
meth__cmp__(ted_Obj *self, ted_Obj *args)
{
    ted_Obj *a, *b;

    ted_assert_is_type(&ted_type_Str, self);
    ted_assert_is_type(&ted_type_List, args);

    a = self;
    if (ted_List_len(args) != 1) {
        ted_panic("__cmp__ method requires two arguments, got %d instead",
                ted_List_len(args) + 1);
    }
    b = ted_List_at_index(args, 0);
    if (!ted_Bool_to_int(tedh_istype(b, &ted_type_Str))) {
        return ted_False;
    }

    if (strcmp(ted_Str_to_charptr(a), ted_Str_to_charptr(b)) == 0) {
        return ted_True;
    }
    return ted_False;
}

static ted_Obj *
meth__del__(ted_Obj *self, ted_Obj *args)
{
    free((char *)((ted_Str *)self)->s_val);
    return ted_None;
}

static ted_method_def methods[] = {
    {"__str__", &meth__str__},
    {"__cmp__", &meth__cmp__},
    {"__del__", &meth__del__},
    {NULL, NULL},
};

ted_Type ted_type_Str = {
    TED_OBJECT_HEAD_INIT(&ted_type_Type),
    sizeof(ted_Str),
    "str",
    methods,
};
