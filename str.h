#ifndef TED_STR_H
#define TED_STR_H

ted_Obj * ted_Str_new(const char *);

#define ted_Str_to_charptr(o) \
    ((char *)(((ted_Str *)o)->s_val))


#endif
