#ifndef TED_VM_H
#define TED_VM_H

ted_VM *ted_VM_new();

ted_Obj *ted_VM_setvar(ted_VM *, ted_Obj *, ted_Obj *);
ted_Obj *ted_VM_push_closure(ted_VM *vm);
ted_Obj *ted_VM_pop_closure(ted_VM *vm);
ted_Obj *ted_VM_getvar(ted_VM *, ted_Obj *);


#endif
