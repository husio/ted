#include "ted.h"

#include <stdlib.h>
#include <stdio.h>


ted_Obj *
ted_print(ted_Obj *o)
{
    const char *str = ted_Str_to_charptr(ted_str(o));
    fprintf(stdout, "%s\n", str);
    return NULL;
}

ted_Obj *
ted_str(ted_Obj *o)
{
    ted_function to_str;

    to_str = ted_find_method(o, "__str__");
    if (!to_str) {
        ted_panic("Method \"__str__\" of type \"%s\" not found.\n",
                o->ob_type->tp_name);
    }
    return to_str(o, NULL);
}

ted_Obj *
ted_type(ted_Obj *o)
{
    return (ted_Obj *)(o->ob_type);
}

static ted_Obj *
fun_print(ted_Obj *self, ted_Obj *args)
{
    int i;

    ted_assert_is_type(&ted_type_List, args);
    if (ted_List_len(args) == 1) {
        return ted_print(ted_List_at_index(args, 0));
    }
    return ted_print(args);
}

static ted_Obj *
fun_str(ted_Obj *self, ted_Obj *args)
{
    ted_assert_is_type(&ted_type_List, args);
    ted_panic("Not implemented");
    return ted_None;
}

static ted_Obj *
fun_type(ted_Obj *self, ted_Obj *args)
{
    ted_Obj *o;

    ted_assert_is_type(&ted_type_List, args);
    if (ted_List_len(args) != 1) {
        ted_panic("Invalid list len: %d", ted_List_len(args));
    }
    o = ted_List_at_index(args, 0);
    return ted_type(o);
}

ted_method_def ted_builtin_functions[] = {
    {"print", &fun_print},
    {"str", &fun_str},
    {"type", &fun_type},
    {NULL, NULL},
};
