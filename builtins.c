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
