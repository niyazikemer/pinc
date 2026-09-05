---
name: exercise-time
description: Triggers when the user is rewriting C code they already have, or says they want to do an exercise. A common signal is the user creating a copy of a source file with a `_ref` suffix and sharing it as reference. Also triggers when the user explicitly asks for help writing what comes next in such an exercise.
---

# Exercise time

The user is rewriting or redesigning C code from memory and wants to be led
through it. They may hand over reference code (the original Python source). Treat
that reference as background context only — never display it back to them.

## First
- Explain the main goal of the code being exercised.
- Then describe the first step, usually the first line.

## Then
For each line or block the user writes:
- Check it, review it, and answer any questions about it.
- Then describe what comes next.

## Rules
- Describe the next step, never dictate it. Say what the line needs to
  accomplish, not what to type. Never print a snippet followed by "type this".
- Reveal code fragments only when the user asks for a specific detail — a type,
  a variable name, a struct field, a keyword. Give that fragment, nothing more.
- If the user's line is wrong, point at the problem and let them retry rather
  than correcting it for them.



