#include "ted.h"



int main(int argc, const char *argv[])
{
    ted_Obj *o, *lst, *args;
    ted_Obj *key, *value, *dt;
    ted_function lst_append;
    ted_function lst_mul;

    lst = ted_List_new();
    ted_List_append(lst, ted_Int_new(23));
    ted_print(lst);


    /* test append method */
    lst_append = ted_find_method(lst, "append");
    if (!lst_append) {
        ted_panic("List type does not provide \"append\" method");
    }
    args = ted_List_new();
    ted_List_append(args, ted_Str_new("fist string"));
    ted_List_append(args, ted_Str_new("second"));
    lst_append(lst, args);
    ted_print(lst);
    ted_print(ted_None);
    ted_print(ted_True);
    ted_print(ted_False);


    dt = ted_Dict_new();

    ted_print(dt);
    ted_print(ted_type(dt));

    key = ted_Str_new("a");
    value = ted_Str_new("b");
    ted_Dict_setitem(dt, key, value);

    key = ted_Str_new("one");
    value = ted_Int_new(33);
    ted_Dict_setitem(dt, key, value);

    value = ted_Int_new(1);
    ted_Dict_setitem(dt, key, value);

    key = value;
    ted_Dict_setitem(dt, key, value);
    value = ted_Int_new(99);
    ted_Dict_setitem(dt, key, value);
    key = ted_Int_new(0);
    ted_Dict_setitem(dt, key, value);

    ted_print(dt);



    return 0;
}
