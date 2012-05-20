#include "ted.h"

ted_Obj *
tedh_equal(ted_Obj *a, ted_Obj *b) {
    ted_Obj *lst;
    ted_function cmp;

    lst = ted_List_new();
    ted_List_append(lst, b);

    cmp = ted_find_method(a, "__cmp__");
    return cmp(a, lst);
}

ted_Obj *
tedh_istype(ted_Obj *o, ted_Type *tp)
{
    ted_Type *o_tp;

    o_tp = o->ob_type;
    do {
        if (o_tp == tp) {
            return ted_True;
        }
        o_tp = ((ted_Obj *)o_tp)->ob_type;
    } while (o_tp != &ted_type_Type);
    return ted_False;
}
