# C Data Structures Library

**Author:** James Dwyer  
**Language:** C (`-std=gnu11`)  
**What it is:** From-scratch implementations of common data structures in C, with `void *` storage so the same containers can hold different value types.

## Structures

| Module | Files | Behavior |
|--------|--------|----------|
| **Array list** | `List.c` / `List.h` | Dynamic array with append/prepend/insert/remove, capacity growth via `listresize` |
| **Linked list** | `Linkedlist.c` / `Linkedlist.h` | Singly linked list with head/tail, get/append/prepend/remove |
| **Dictionary** | `Dict.c` / `Dict.h` | Hash table with separate chaining (bucket = linked list), string or integer keys, resize on load |

Supporting pieces: `Node.h`, small test drivers (`test.c`, `dicttests.c`, `test2.c`), and a `Makefile`.

## Design choices

- **Generic via `void *`:** lists and dict values are untyped pointers; callers manage ownership and cast.
- **Dict hashing:** `Dicthash` supports string keys (byte sum over the first characters) and integer keys; collisions go into per-bucket linked lists.
- **Dict key set:** a parallel `List` of keys supports iteration / destroy and drives some cleanup paths.
- **Load factor:** insert path can `resize` when the table grows past a configured load threshold.

## Build / run

Linux or any environment with `gcc`/`cc` and Make:

```bash
make          # builds test binary from Dict + List + Linkedlist + test.c
./test
make clean
make debug    # same build with -g
```

## Scope

Coursework / practice library for learning C memory management and classic structures — not a production collections package. Useful as a short sample of readable C: malloc/free discipline, pointer-heavy APIs, and a working hash map on top of the list types.

## Files in this sample

Source and headers only (object files and binaries stripped). Start with `Dict.h` / `List.h` / `Linkedlist.h` for the API, then `Dict.c` for the hash-table logic.
