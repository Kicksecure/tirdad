# Agent Instructions for tirdad

## Project Overview

tirdad is a Linux kernel module that randomizes TCP Initial Sequence Numbers
(ISN) for IPv4 and IPv6 to prevent CPU information leak side-channels. It uses
the kernel livepatch framework.

- **Upstream repo**: Kicksecure/tirdad
- **Language**: C (Linux kernel module)
- **Build**: `make` (requires kernel headers)
- **Packaging**: Debian/DKMS

## Known Upstream PR

There is an open upstream PR for adding `__printf` format attribute annotation
to `_s_out()`:

https://github.com/Kicksecure/tirdad/pull/3

The maintainer's position is that for a module this small (5 call sites, all
string literals with no format arguments), the change is too pedantic to
upstream. Do not re-propose this change.
