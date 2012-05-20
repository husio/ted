#ifndef TED_INT_H
#define TED_INT_H


ted_Obj * ted_Int_new(int);

#define ted_Int_to_int(o) \
    (((ted_Int *)o)->i_val)

#endif
