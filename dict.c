#include "ted.h"

#define TED_DICT_INIT_SIZE 100

/* *VERY* dummy dict implementation */

ted_Obj *
ted_Dict_new()
{
    ted_Dict *o;
    o = (ted_Dict *)ted_Obj_new(&ted_type_Dict);
    o->d_size = TED_DICT_INIT_SIZE;
    o->d_len = 0;
    o->d_items = malloc(sizeof(ted_Dict_Item *) * TED_DICT_INIT_SIZE);
    return (ted_Obj *)o;
}

ted_Obj *
ted_Dict_setitem(ted_Obj *o, ted_Obj *key, ted_Obj *value)
{
    int i;
    ted_Dict_Item *item;

    ted_assert_is_type(&ted_type_Dict, o);
    ted_Dict *dt = (ted_Dict *)o;

    if (dt->d_len == dt->d_size) {
        ted_panic("Dict is too small.");
    }

    for (i=0; i<dt->d_len; ++i) {
        item = dt->d_items[i];
        if (ted_Bool_to_int(tedh_equal(item->key, key))) {
            item->value = value;
            return;
        }
    }

    item = malloc(sizeof(ted_Dict_Item * ));
    item->key = key;
    item->value = value;

    dt->d_items[dt->d_len] = item;
    dt->d_len += 1;

    return ted_None;
}

ted_Obj *
ted_Dict_getitem(ted_Obj *o, ted_Obj *key)
{
    int i;
    char *raw_key;
    ted_Dict_Item *item;
    ted_Dict *dt;

    ted_assert_is_type(&ted_type_Dict, o);
    raw_key = ted_Str_to_charptr(key);
    dt = (ted_Dict *)o;
    for (i=0; i<dt->d_len; ++i) {
        item = dt->d_items[i];
        if (strcmp(raw_key, ted_Str_to_charptr(item->key)) == 0) {
            return item->value;
        }
    }
    return NULL;
}


static ted_Obj *
meth__str__(ted_Obj *self, ted_Obj *args)
{
    int i;
    char *str, *p, *o_str;
    ted_Obj *o;
    ted_Dict_Item *item;
    ted_Dict *dt;

    ted_assert_is_type(&ted_type_Dict, self);
    dt = (ted_Dict *)self;

    /* XXX overflow :( */
    str = malloc(sizeof(char) * 1024);
    p = str;
    *p = '{';
    ++p;
    for (i=0; i<dt->d_len; ++i) {
        item = dt->d_items[i];
        o_str = ted_Str_to_charptr(ted_str(item->key));
        while (*o_str) {
            *p = *o_str;
            ++p;
            ++o_str;
        }
        *p = ':';
        ++p;
        *p = ' ';
        ++p;
        o_str = ted_Str_to_charptr(ted_str(item->value));
        while (*o_str) {
            *p = *o_str;
            ++p;
            ++o_str;
        }
        *p = ',';
        ++p;
        *p = ' ';
        ++p;
    }
    if (dt->d_len > 0) {
        --p;
        --p;
    }
    *p = '}';
    ++p;
    *p = 0;

    o = ted_Str_new(str);
    free(str);
    return o;
}

static ted_Obj *
meth__del__(ted_Obj *self, ted_Obj *args)
{
    return ted_None;
}

static ted_method_def methods[] = {
    {"__str__", &meth__str__},
    {"__del__", &meth__del__},
    {NULL, NULL},
};

ted_Type ted_type_Dict = {
    TED_OBJECT_HEAD_INIT(&ted_type_Type),
    sizeof(ted_Dict),
    "dict",
    methods,
};
