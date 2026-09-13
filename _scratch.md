# Scratch

## To learn (phase 01)
Why we need this at all: C has no JSON type. In Python the data is plain dicts/lists — the three type lines in types.py only *name* the shape, and Pydantic *checks* data against it. In C there is no plain version of the data anywhere: the struct we write **is the container for the data itself**. So pinc_json is not a description checked at the boundary — it is the thing, and the tag field is the only answer to "which kind is this value?". That's why struct/enum/union are the things to learn first.


- struct — box with named compartments, one value each → Modern C §6.3 Structures, pp. 85-92
- enum — set of named constants → Modern C §5.6 Named constants, p. 58
- union — one compartment shared by several types; last write wins → Modern C §12.2 Unions, pp. 185-186
- typedef for structs (the `typedef struct pinc_json pinc_json;` pattern) → Modern C §6.4, p. 92 (takeaways 6.4 #1-#2)
- "tag" is not a keyword — it's just an enum field in a struct; tagged union = struct + enum + union (see `src/pinc_agent/pinc_json.h`)
- the ownership rules behind `pinc_json_free` → Modern C §13.1, takeaways: every allocation gets a free (p. 204), malloc fails with NULL (p. 200)

After learning this, try a standard JSON library (cJSON, jansson, yyjson) — they all have this same value type plus a parser/serializer, so pinc_json should read like a familiar shape.
