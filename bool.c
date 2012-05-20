#include "ted.h"


int
ted_Bool_to_int(ted_Obj *o)
{
    ted_assert_is_type(&ted_type_Bool, o);
    return ((ted_Bool *)o)->b_val;
}


static ted_Obj *
meth__str__(ted_Obj *self, ted_Obj *args)
{
    if (ted_Bool_to_int(self)) {
        return ted_Str_new("True");
    }
    return ted_Str_new("False");
}

static ted_Obj *
meth__bool__(ted_Obj *self, ted_Obj *args)
{
    return self;
}


static ted_method_def methods[] = {
    {"__str__", &meth__str__},
    {"__bool__", &meth__bool__},
    {NULL, NULL},
};

ted_Type ted_type_Bool = {
    TED_OBJECT_HEAD_INIT(&ted_type_Type),
    0,
    "bool",
    methods,
};


ted_Bool _ted_True = {
    TED_OBJECT_HEAD_INIT(&ted_type_Bool),
    1,
};
ted_Bool _ted_False = {
    TED_OBJECT_HEAD_INIT(&ted_type_Bool),
    0,
};
