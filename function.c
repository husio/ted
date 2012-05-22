#include "ted.h"


ted_Obj *
ted_Func_new(ted_function func)
{
    ted_Func *o;

    o = (ted_Func *)ted_Obj_new(&ted_type_Func);
    o->function = func;
    return (ted_Obj *)o;
}

ted_Obj *
ted_Func_is_bound(ted_Obj *o)
{
    ted_assert_is_type(&ted_type_Func, o);
    if (((ted_Func *)o)->bound_obj == NULL) {
        return ted_False;
    }
    return ted_True;
}

static ted_Obj *
meth__call__(ted_Obj *self, ted_Obj *args)
{
    ted_Func *func;

    ted_assert_is_type(&ted_type_Func, self);
    func = (ted_Func *)self;
    return func->function(func->bound_obj, args);
}

static ted_Obj *
meth__str__(ted_Obj *self, ted_Obj *args)
{
    /* buffer overflow :( */
    char s[1024];
    ted_Func *func;

    ted_assert_is_type(&ted_type_Func, self);
    func = (ted_Func *)self;
    if (ted_Bool_to_int(ted_Func_is_bound(self))) {
        sprintf(s, "<bound method #%#x>", func->function);
    } else {
        sprintf(s, "<function #%#x>", func->function);
    }

    return ted_Str_new(s);
}

static ted_method_def methods[] = {
    {"__call__", &meth__call__},
    {"__str__", &meth__str__},
    {NULL, NULL},
};

ted_Type ted_type_Func = {
    TED_OBJECT_HEAD_INIT(&ted_type_Type),
    sizeof(ted_Func),
    "function",
    methods,
};
