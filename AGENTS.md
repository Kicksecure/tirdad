# Agent Instructions for tirdad

## Project Overview

tirdad is a Linux kernel module that randomizes TCP Initial Sequence Numbers
(ISN) for IPv4 and IPv6 to prevent CPU information leak side-channels. It uses
the kernel livepatch framework.

- **Upstream repo**: Kicksecure/tirdad
- **Language**: C (Linux kernel module)
- **Build**: `make` (requires kernel headers)
- **Packaging**: Debian/DKMS

## Rejected Upstream Changes

### PR #3: `__printf` format attribute on `_s_out()`

https://github.com/Kicksecure/tirdad/pull/3

Proposed adding `__printf(2, 3)` attribute and `const char *` qualifier to the
`_s_out()` function for compile-time format string checking.

**Rejected.** The original author (0xsirus) stated: "The existing print
function is fine and the suggested change is not necessary." The module is too
small (5 call sites, all string literals with no format arguments) for this to
provide meaningful value. Do not re-propose this change.

### PR #4: Compiler warning flags in module Makefile

https://github.com/Kicksecure/tirdad/pull/4

Proposed adding `ccflags-y` flags (`-Wall`, `-Wextra`, `-Werror`, `-Wformat`,
`-Wformat-security`, `-Wformat-nonliteral`, `-Wno-unused-parameter`) to
`module/Makefile`, plus the same `__printf`/`const` changes from PR #3.

**Rejected.** Reviewer (ArrayBolt3) noted:
- The `__printf`/`const` portion was an exact duplicate of PR #3.
- The Linux kernel's Kbuild system already sets appropriate compiler warning
  flags for modules. Out-of-tree modules should not hardcode their own flags.
- For development-time warnings, use `make KCFLAGS=-W` instead.

Do not add `ccflags-y` warning flags to the module Makefile.
