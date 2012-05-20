#include "ted.h"


static ted_Obj *
meth__str__(ted_Obj *self, ted_Obj *args)
{
    return ted_Str_new("None");
}

static ted_Obj *
meth__bool__(ted_Obj *self, ted_Obj *args)
{
    return ted_False;
}

static ted_method_def methods[] = {
    {"__str__", &meth__str__},
    {"__bool__", &meth__bool__},
    {NULL, NULL},
};

ted_Type ted_type_None = {
    TED_OBJECT_HEAD_INIT(&ted_type_Type),
    0,
    "none",
    methods,
};


ted_Obj _ted_None = TED_OBJECT_HEAD_INIT(&ted_type_None);
