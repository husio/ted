#ifndef TED_TED_H
#define TED_TED_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define TED_OBJECT_HEAD \
    struct _ted_Obj ob_base;
#define TED_OBJECT_HEAD_INIT(type) \
    { 1, type }


typedef struct _ted_Obj {
    int ob_refcnt;
    struct _ted_Type *ob_type;
} ted_Obj;

typedef ted_Obj * (* ted_function)(ted_Obj *, ted_Obj *);

typedef struct _ted_method_def {
    const char *name;
    ted_function function;
} ted_method_def;

typedef struct _ted_Type {
    TED_OBJECT_HEAD
    size_t ob_size;
    const char *tp_name;
    ted_method_def *methods;
} ted_Type;

extern ted_Type ted_type_Type;
extern ted_Type ted_type_Bool;
extern ted_Type ted_type_Int;
extern ted_Type ted_type_Str;
extern ted_Type ted_type_List;
extern ted_Type ted_type_Dict;

typedef struct _ted_List {
    TED_OBJECT_HEAD
    int l_size_max;
    int l_len;
    ted_Obj **l_root;
} ted_List;

typedef struct _ted_Str {
    TED_OBJECT_HEAD
    const char *s_val;
    int s_len;
} ted_Str;

typedef struct _ted_Int {
    TED_OBJECT_HEAD
    int i_val;
} ted_Int;

typedef struct _ted_Dict_Item {
    ted_Obj *key;
    ted_Obj *value;
} ted_Dict_Item;

typedef struct _ted_Dict {
    TED_OBJECT_HEAD
    ted_Dict_Item **d_items;
    int d_len;
    int d_size;
} ted_Dict;

typedef struct _ted_Bool {
    TED_OBJECT_HEAD
    int b_val;
} ted_Bool;


void ted_assert_is_type(ted_Type *, ted_Obj *);
void ted_panic(const char *, ...);

#include "type.h"
#include "bool.h"
#include "dict.h"
#include "str.h"
#include "int.h"
#include "list.h"
#include "builtins.h"

#include "helpers.h"

extern ted_Obj _ted_None;
#define ted_None (&_ted_None)

extern ted_Bool _ted_True;
#define ted_True ((ted_Obj *)(&_ted_True))
extern ted_Bool _ted_False;
#define ted_False ((ted_Obj *)(&_ted_False))

#endif
