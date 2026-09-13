# include "pinc_json.h"

# include <stdlib.h>
# include <string.h>

/* malloc that gives up on failure; later, real error propagation. */
static void *xmalloc(size_t n)
{
    void *p = malloc(n);
    if (p == NULL) abort();
    return p;
}

static char *xstrdup(const char *s)
{
    size_t n = strlen(s) + 1;
    char *p = xmalloc(n);
    memcpy(p, s, n);
    return p;
}

static pinc_json *json_new(pinc_json_kind kind)
{
    pinc_json *j = xmalloc(sizeof *j);
    memset(j, 0, sizeof *j);
    j->kind = kind;
    return j;
}

pinc_json *pinc_json_null(void)
{
    return json_new(PINC_JSON_NULL);
}

pinc_json *pinc_json_bool(bool v)
{
    pinc_json *j = json_new(PINC_JSON_BOOL);
    j->as.boolean = v;
    return j;
}

pinc_json *pinc_json_number(double v)
{
    pinc_json *j = json_new(PINC_JSON_NUMBER);
    j->as.number = v;
    return j;
}

pinc_json *pinc_json_string(const char *s)
{
    pinc_json *j = json_new(PINC_JSON_STRING);
    j->as.string = xstrdup(s);
    return j;
}

pinc_json *pinc_json_array(void)
{
    return json_new(PINC_JSON_ARRAY);
}

pinc_json *pinc_json_object(void)
{
    return json_new(PINC_JSON_OBJECT);
}

void pinc_json_array_append(pinc_json *arr, pinc_json *item)
{
    size_t cap = arr->as.array.len != 0 ? arr->as.array.len : 4;
    if (arr->as.array.len == cap) {
        cap *= 2;
        pinc_json **items = realloc(arr->as.array.items, cap * sizeof *items);
        if (items == NULL) abort();
        arr->as.array.items = items;
    }
    arr->as.array.items[arr->as.array.len++] = item;
}

void pinc_json_object_set(pinc_json *obj, const char *key, pinc_json *value)
{
    size_t cap = obj->as.object.len != 0 ? obj->as.object.len : 4;
    if (obj->as.object.len == cap) {
        cap *= 2;
        pinc_json_member *members = realloc(obj->as.object.members, cap * sizeof *members);
        if (members == NULL) abort();
        obj->as.object.members = members;
    }
    obj->as.object.members[obj->as.object.len] =
        (pinc_json_member){ .key = xstrdup(key), .value = value };
    obj->as.object.len++;
}

void pinc_json_free(pinc_json *j)
{
    if (j == NULL) return;
    switch (j->kind) {
    case PINC_JSON_STRING:
        free(j->as.string);
        break;
    case PINC_JSON_ARRAY:
        for (size_t i = 0; i < j->as.array.len; i++)
            pinc_json_free(j->as.array.items[i]);
        free(j->as.array.items);
        break;
    case PINC_JSON_OBJECT:
        for (size_t i = 0; i < j->as.object.len; i++) {
            free(j->as.object.members[i].key);
            pinc_json_free(j->as.object.members[i].value);
        }
        free(j->as.object.members);
        break;
    default:
        break;
    }
    free(j);
}
