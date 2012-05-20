#include "ted.h"



ted_Obj *
ted_Int_new(int val)
{
    ted_Int *o;
    o = (ted_Int *) ted_Obj_new(&ted_type_Int);
    o->i_val = val;
    return (ted_Obj *)o;
}

static ted_Obj *
meth__str__(ted_Obj *self, ted_Obj *args)
{
    char buf[1024];

    ted_assert_is_type(&ted_type_Int, self);

    sprintf(buf, "%d", ((ted_Int *)self)->i_val);
    return ted_Str_new(buf);
}

static ted_Obj *
meth__cmp__(ted_Obj *self, ted_Obj *args)
{
    ted_Obj *a, *b;

    ted_assert_is_type(&ted_type_Int, self);
    ted_assert_is_type(&ted_type_List, args);

    a = self;
    if (ted_List_len(args) != 1) {
        ted_panic("__cmp__ method requires two arguments, got %d instead",
                ted_List_len(args) + 1);
    }
    b = ted_List_at_index(args, 0);
    if (!ted_Bool_to_int(tedh_istype(b, &ted_type_Int))) {
        return ted_False;
    }

    if (ted_Int_to_int(a) == ted_Int_to_int(b)) {
        return ted_True;
    }
    return ted_False;
}

static ted_method_def methods[] = {
    {"__str__", &meth__str__},
    {"__cmp__", &meth__cmp__},
    {NULL, NULL},
};


ted_Type ted_type_Int = {
    TED_OBJECT_HEAD_INIT(&ted_type_Type),
    sizeof(ted_Int),
    "int",
    methods,
};

