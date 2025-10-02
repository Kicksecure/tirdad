# TCP ISN CPU Information Leak Protection #

TCP Initial Sequence Numbers Randomization to prevent TCP ISN based CPU
Information Leaks.

The Linux kernel has a side-channel information leak bug.
It is leaked in any outgoing traffic.
This can allow side-channel attacks because sensitive information about
a system's CPU activity is leaked.

It may prove very dangerous for long-running cryptographic operations. [A]

Research has demonstrated that it can be used for de-anonymization of
location-hidden services. [1]

Clock skew,

- is leaked through TCP ISNs (Initial Sequence Number) by the Linux kernel.
- can be remotely detected through observing ISNs.
- can be induced by an attacker through producing load on the victim machine.

Quote Security researcher Steven J. Murdoch
(University of Cambridge, Cambridge, UK) [B]

"What the Linux ISN leaks is the difference between two timestamps, not the
timestamp itself. A difference lets you work out drift and skew, which can
help someone fingerprint the computer hardware, its environment and load. Of
course that only works if you can probe a computer, and maintain the same
source/destination port and IP address."

Quote Mike Perry, developer at The Tor Project [A]:

"... it is worth complaining to the kernel developers for the simple
reason that adding the 64ns timer post-hash probably *does* leak side channels
about CPU activity, and that may prove very dangerous for long-running
cryptographic operations (along the lines of the hot-or-not issue).
Unfortunately, someone probably needs to produce more research papers before
they will listen."

tirdad is a kernel module to hot-patch the Linux kernel
to generate random TCP Initial Sequence Numbers for IPv4 and IPv6 TCP
connections.

You can refer to this blog post to get familiar with the original issue:

- An analysis of TCP secure SN generation in Linux and its privacy issues
- https://bitguard.wordpress.com/?p=982

This metapackage depends on tirdad-dkms.

References:

  - [1] https://www.cl.cam.ac.uk/~sjm217/papers/ccs06hotornot.pdf
  - [2] http://caia.swin.edu.au/talks/CAIA-TALK-080728A.pdf
  - [3] http://www.cl.cam.ac.uk/~sjm217/papers/ih05coverttcp.pdf
  - [4] https://stackoverflow.com/a/12232126
  - [5] http://lxr.free-electrons.com/source/net/core/secure_seq.c?v=3.16
  - [6] https://trac.torproject.org/projects/tor/ticket/16659
  - [7] https://phabricator.whonix.org/T543
  - [A] https://trac.torproject.org/projects/tor/ticket/16659#comment:10
  - [B] https://trac.torproject.org/projects/tor/ticket/16659#comment:18
## How to install `tirdad` using apt-get ##

1\. Download [Whonix's Signing Key]().

```
wget https://www.whonix.org/patrick.asc
```

Users can [check Whonix Signing Key](https://www.whonix.org/wiki/Whonix_Signing_Key) for better security.

2\. Add Whonix's signing key.

```
sudo apt-key --keyring /etc/apt/trusted.gpg.d/whonix.gpg add ~/patrick.asc
```

3\. Add Whonix's APT repository.

```
echo "deb https://deb.whonix.org bullseye main contrib non-free" | sudo tee /etc/apt/sources.list.d/whonix.list
```

4\. Update your package lists.

```
sudo apt-get update
```

5\. Install `tirdad`.

```
sudo apt-get install tirdad
```

## How to Build deb Package ##

Any standard Debian build tools can be used. For example. Quick and easy.

```
dpkg-buildpackage -b
```

## Contact ##

* [Free Forum Support](https://forums.whonix.org)
* [Professional Support](https://www.whonix.org/wiki/Professional_Support)

## Donate ##

`tirdad` requires [donations](https://www.whonix.org/wiki/Donate) to stay alive!
