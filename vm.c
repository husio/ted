#include "ted.h"


extern ted_method_def ted_builtin_functions[];


ted_VM *
ted_VM_new()
{
    ted_method_def *meth_def;
    ted_VM *vm;

    vm = malloc(sizeof(ted_VM));
    vm->closures = ted_List_new();
    vm->builtins = ted_Dict_new();

    ted_List_append(vm->closures, ted_Dict_new());

    meth_def = ted_builtin_functions;
    while (meth_def->name != NULL) {
        ted_Dict_setitem(vm->builtins,
                ted_Str_new(meth_def->name),
                ted_Func_new(meth_def->function));
        ++meth_def;
    }

    return vm;
}

ted_Obj *
ted_VM_push_closure(ted_VM *vm)
{
    ted_Obj *closure;

    closure = ted_Dict_new();
    ted_List_append(vm->closures, closure);
    return closure;
}

ted_Obj *
ted_VM_pop_closure(ted_VM *vm)
{
    if (ted_List_len(vm->closures) == 0) {
        ted_panic("Cannot pop from empty closures list");
    }
    return ted_List_pop(vm->closures);
}

ted_Obj *
ted_VM_setvar(ted_VM *vm, ted_Obj *name, ted_Obj *value)
{
    ted_Obj *closure;

    closure = ted_List_at_index(vm->closures, ted_List_len(vm->closures) - 1);
    ted_Dict_setitem(closure, name, value);

    return ted_None;
}

ted_Obj *
ted_VM_getvar(ted_VM *vm, ted_Obj *name)
{
    int i;
    ted_Obj *closure, *o;

    ted_assert_is_type(&ted_type_Str, name);

    for (i=ted_List_len(vm->closures) - 1; i>=0; --i) {
        closure = ted_List_at_index(vm->closures, i);
        o = ted_Dict_getitem(closure, name);
        if (o != NULL) {
            return o;
        }
    }

    return NULL;
}
