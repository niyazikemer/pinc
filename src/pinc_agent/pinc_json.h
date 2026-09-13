#ifndef PINC_AGENT_PINC_JSON_H
#define PINC_AGENT_PINC_JSON_H

# include <stdbool.h>
# include <stddef.h>

/*
 * The provider-neutral JSON value type (Python: tau_agent/types.py).
 *
 * One type covers all three Python names; the kind tag is the distinction:
 *   JSONPrimitive -> kind is NULL, BOOL, NUMBER or STRING
 *   JSONValue     -> any pinc_json
 *   JSONObject    -> kind is OBJECT
 *
 * Ownership: a pinc_json owns everything inside it (its string, its
 * children). Build with the pinc_json_* helpers, free the whole value
 * with pinc_json_free. Never free the inside by hand.
 */
typedef enum pinc_json_kind {
    PINC_JSON_NULL,
    PINC_JSON_BOOL,
    PINC_JSON_NUMBER,
    PINC_JSON_STRING,
    PINC_JSON_ARRAY,
    PINC_JSON_OBJECT,
} pinc_json_kind;

typedef struct pinc_json pinc_json;

/* One key/value pair of an object. */
typedef struct pinc_json_member {
    char *key;        /* owned, NUL-terminated */
    pinc_json *value; /* owned */
} pinc_json_member;

struct pinc_json {
    pinc_json_kind kind;
    union {
        bool boolean;
        double number; /* int and float both live here */
        char *string;  /* owned */
        struct {
            pinc_json **items; /* owned array of owned values */
            size_t len;
        } array;
        struct {
            pinc_json_member *members; /* owned array of owned pairs */
            size_t len;
        } object;
    } as;
};

pinc_json *pinc_json_null(void);
pinc_json *pinc_json_bool(bool v);
pinc_json *pinc_json_number(double v);
pinc_json *pinc_json_string(const char *s);
pinc_json *pinc_json_array(void);
pinc_json *pinc_json_object(void);

/* Takes ownership of item. */
void pinc_json_array_append(pinc_json *arr, pinc_json *item);

/* Copies key, takes ownership of value. */
void pinc_json_object_set(pinc_json *obj, const char *key, pinc_json *value);

void pinc_json_free(pinc_json *j);

#endif
