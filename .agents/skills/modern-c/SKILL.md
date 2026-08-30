---
name: modern-c
description: Answer questions about the C programming language from Jens Gustedt's "Modern C" (C23 edition), which is bundled here as searchable per-section reference files. Use when the user asks how something works in C, what the standard says, whether something is undefined behaviour, or how to write idiomatic modern C — covering pointers, arrays, structs, the memory model, storage and lifetime, types and conversions, the C library, strings and IO, error handling, performance, macros, type-generic programming, control flow, threads, and atomics.
---

# Modern C (Gustedt, C23 edition)

The full text of the book lives in `references/`, split one file per section.
Answer from these files rather than from memory, and say which section an answer came from.

## How to look something up

1. **Grep first.** The whole book is plain text, so search it before opening anything:

   ```
   grep -ril "restrict" references/
   grep -rn "effective type" references/ | head
   ```

   Searching costs nothing; loading the wrong chapter costs a lot.

2. **Or go through the index.** `references/INDEX.md` lists every section with its
   file and printed page range. Use it when the question names a topic that maps
   cleanly onto a chapter (see the map below).

3. **Read only what you need.** One section file is a handful of pages. Read the
   whole chapter folder only when the question genuinely spans it.

4. **Quote the page.** Every file carries `[page N]` markers matching the printed
   page numbers of the book, so cite them — "Modern C §11.2, p. 171". The PDF's own
   page number is the printed number **+ 12**.

## Where things live

Files are grouped by chapter under `references/`:

| Ask about | Look in |
|---|---|
| first program, compiling, program structure, declarations, statements | `01-getting-started/`, `02-the-principal-structure-of-a-program/` |
| `if`/loops/`switch`, operators, evaluation order | `03-everything-is-about-control/`, `04-expressing-computations/` |
| types, integers, floats, literals, conversions, initializers, `constexpr`, binary representation | `05-basic-values-and-data/` |
| arrays, structs, `typedef`, opaque types | `06-derived-data-types/` |
| functions, `main`, recursion | `07-functions/` |
| the standard library, `printf`/`scanf`, strings, time, `exit`, assertions | `08-c-library-functions/` |
| style, naming, documentation, interfaces | `09-style/`, `10-organization-and-documentation/` |
| **pointers** — arithmetic, `NULL`, pointers to structs and arrays, function pointers | `11-pointers/` |
| unions, aliasing, effective types, alignment, `void*`, casts | `12-the-c-memory-model/` |
| `malloc`/`free`, storage duration, lifetime, visibility, `static`, initialization | `13-storage/` |
| text processing, formatted input, wide chars, UTF-8, binary streams | `14-more-involved-processing-and-io/` |
| undefined behaviour, `errno`, error checking, cleanup, program failure | `15-program-failure/` |
| `inline`, `restrict`, benchmarking, optimization | `16-performance/` |
| macros, `#define`, variadic macros, default arguments | `17-function-like-macros/` |
| `_Generic`, type inference, `auto`, anonymous functions | `18-type-generic-programming/` |
| `goto`, `setjmp`/`longjmp`, signal handlers, sequencing | `19-variations-in-control-flow/` |
| threads, mutexes, condition variables, thread-local storage | `20-threads/` |
| atomics, memory ordering, happens-before, sequential consistency | `21-atomic-access-and-memory-consistency/` |
| C23 features missing from a compiler, fallbacks, transitional code | `references/annex/`, `references/appendix-technical-annex.md` |

## Figures

All 21 figures were cropped out of the PDF as PNGs in `references/figures/`. Wherever a
figure appears, the section text carries a marker right above the caption:

```
[figure image: ../figures/figure-19.1-p334.png]
Figure 19.1. Control flow of function calls: return jumps to the ...
```

When you hit one of those markers and the answer depends on the picture, **read the PNG** —
don't guess at the diagram or tell the user to open the book. `references/FIGURES.md` lists
all of them with pages. Tables are not images: they came through as text and are already in
the section files.

## Three files worth knowing about

- `references/appendix-takeaways.md` — the book's ~250 numbered rules, in one file.
  Excellent for a fast, quotable answer ("Takeaway #1: C and C++ are different").
- `references/INDEX.md` — the complete section-to-file map.
- `references/FIGURES.md` — every figure, its page, and its image file.

Level introductions (`level-0-encounter.md` … `level-3-experience.md`) explain what
the author expects a reader to know at each stage; useful when the user asks what to
study next.

## Caveats

- *Modern C* is an expert secondary source, not the normative C standard. When the user
  asks what the standard says, distinguish the book's explanation from the standard's
  exact requirements; do not present the book's wording as normative text.
- If the book is silent on a question, say so plainly. Do not fill the gap from memory
  while implying that the answer came from the book.
- The text was extracted from the PDF. Code listings keep their indentation, tables kept
  their columns, and figures are available as PNGs (see above). A figure crop sometimes
  catches a line or two of surrounding text — harmless, ignore it.
- The index (printed pages 407+) was deliberately not included; grep replaces it.
- The book targets C23. When it describes a feature as new, note which revision
  introduced it — the user's compiler may not have it yet.
