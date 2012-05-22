#include "ted.h"

#include <string.h>



static ted_Obj *
meth__del__(ted_Obj *self, ted_Obj *args)
{
    return NULL;
}

static ted_Obj *
meth__str__(ted_Obj *self, ted_Obj *args)
{
    ted_Obj *o;
    ted_Type *tp;
    char s[1024];

    ted_assert_is_type(&ted_type_Type, self);

    sprintf(s, "<type \"%s\">", o->ob_type->tp_name);
    o = ted_Str_new(s);
    return o;
}
static ted_Obj *
meth__cmp__(ted_Obj *self, ted_Obj *args)
{
    ted_Obj *o;

    ted_assert_is_type(&ted_type_List, args);
    if (ted_List_len(args) != 1) {
        ted_panic("__cmp__ method requires two arguments, got %d instead",
                ted_List_len(args) + 1);
    }
    o = ted_List_at_index(args, 0);

    if (self->ob_type == o->ob_type) {
        return ted_True;
    }
    return ted_False;
}

#define meth_not_supported(type, name) \
    static ted_Obj * \
    meth_not_supported##type(ted_Obj *self, ted_Obj *args) \
    { \
        ted_panic("Method \"%s\" currently not supported", name); \
    }
meth_not_supported(__mul__, "__mul__");
meth_not_supported(__add__, "__add__");
meth_not_supported(__call__, "__call__");

static ted_method_def methods[] = {
    {"__mul__", &meth_not_supported__mul__},
    {"__add__", &meth_not_supported__add__},
    {"__del__", &meth__del__},
    {"__str__", &meth__str__},
    {"__cmp__", &meth__cmp__},
    {"__call__", &meth__cmp__},
    {NULL, NULL},
};


ted_Type ted_type_Type = {
    TED_OBJECT_HEAD_INIT(&ted_type_Type),
    0,
    "type",
    methods,
};

ted_Obj *
ted_Obj_new(ted_Type *t)
{
    ted_Obj *o;

    o = malloc(t->ob_size);
    o->ob_refcnt = 1;
    o->ob_type = t;
    return o;
}


ted_function
ted_find_method(ted_Obj *o, const char *name)
{
    ted_Type *tp;

    tp = o->ob_type;
    ted_method_def *mdef;
    for (;;) {
        mdef = tp->methods;
        if (mdef != NULL) {
            for (;mdef->name != NULL; ++mdef) {
                if (!strcmp(mdef->name, name)) {
                    return mdef->function;
                }
            }
        }

        if (tp == &ted_type_Type) {
            break;
        }
        tp = ((ted_Obj *)tp)->ob_type;
    }
    return NULL;
}
