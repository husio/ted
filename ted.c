#include "ted.h"

#include <stdarg.h>



void
ted_parse_args(ted_Obj *args, const char *format, ...)
{
    va_list ap;
    char *c;
    ted_Obj *lst_p;
    ted_Obj **param_o;
    char **param_s;
    int *param_i;

    ted_assert_is_type(&ted_type_List, args);
    lst_p = ((ted_List *)args)->l_root[0];

    va_start(ap, format);
    c = (char *)format;
    while (*c) {
        switch (*c) {
        case 'O':
            param_o = va_arg(ap, ted_Obj **);
            *param_o = lst_p;
            break;
        case 's':
            ted_panic("'s' parameter not implemented");
            break;
        case 'i':
            ted_panic("'i' parameter not implemented");
            break;
        default:
            ted_panic("Unknown \"ted_parse_args\" parameter ('%c' inside of \"%s\")",
                    *c, format);
        }
        ++lst_p;
        ++c;
    }
    va_end(ap);
}

void
ted_panic(const char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    fprintf(stderr, "PANIC: ");
    vfprintf(stderr, format, ap);
    fprintf(stderr, "\n");
    va_end(ap);
    exit(666);
}

void
ted_assert_is_type(ted_Type *tp, ted_Obj *o)
{
    /* TODO */
}
