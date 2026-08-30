---
name: pinc-architecture
description: Routes questions about pinc's architecture to the right design document. Use this skill whenever the user asks about pinc internals — the layering and package boundaries, the agent loop, AgentHarness, the provider layer, tools (read/write/edit/bash), sessions, transcripts, messages, or the agent event stream — and also when they ask where a piece of code belongs, whether something violates the layering, or share code from pinc_agent, pinc_ai, or pinc_coding. Consult it before answering from memory; these documents are the source of truth and the summaries here are deliberately incomplete.
---

# pinc Architecture

These documents specify pinc's design. Treat them as the reference for what the
implementation is meant to reproduce.

## The one rule to hold in mind

```text
pinc_coding -> pinc_agent -> pinc_ai
```

`pinc_ai` owns provider-specific streaming. `pinc_agent` is the portable brain — messages,
tools, events, loop, harness, session primitives — and must not import CLI, Rich, Textual,
or resource-loading code. `pinc_coding` is the application: CLI, built-in coding tools,
prompt templates, on-disk sessions, UI adapters.

Most "where does this belong?" questions resolve against that line alone. Anything more
specific needs the file.

## Where to look

Paths are relative to the skill directory.

| File | Answers questions about |
| --- | --- |
| `docs/01-architecture.md` | What each package owns, the dependency direction, and the harness/session/TUI split. Read when the question is about boundaries or placement. |
| `docs/02-agent-loop.md` | The loop's numbered responsibilities and its explicit non-responsibilities. Read for what the loop is allowed to know about. |
| `docs/03-tools.md` | The tool model (`AgentTool`, `AgentToolResult`) and the full spec for `read`, `write`, `edit`, `bash` — arguments, behavior, truncation, errors. By far the longest document; read the relevant tool's section rather than the whole file. |
| `docs/04-sessions.md` | The append-only session tree and its planned entry types. Still a design direction, not a built system — check before assuming anything is implemented. |
| `docs/05-core-types-and-events.md` | The provider-neutral vocabulary: message types, tool types, and the full list of event names. Read when a question turns on what an event or message is called. |
| `docs/harness.md` | `AgentHarness` usage and its responsibility list, including what it deliberately doesn't know. |
| `docs/agent-loop.md` | The `run_agent_loop()` call shape. Short. |
| `docs/providers.md` | The provider layer: the OpenAI-compatible adapter, its environment variables, and the fake provider used for deterministic tests. |

Note the overlap: `02-agent-loop.md` is conceptual, `agent-loop.md` is the call signature.
For a question about what the loop *does*, read 02; for how it's invoked, read the short one.

## How to use this

Open the file before answering. The table above is a routing index, not a substitute — it
names the territory each document covers and nothing more, so any answer with real detail
in it comes from the document, not from here.

If a question spans two files, read both rather than reasoning across the gap.

If the documents are silent on something, say so plainly. Several sections describe planned
rather than existing behavior, and inventing the missing part is worse than the gap.
