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

- https://bitguard.wordpress.com/2019/09/03/an-analysis-of-tcp-secure-sn-generation-in-linux-and-its-privacy-issues/

This metapackage depends on tirdad-dkms.

References:

- [1] https://murdoch.is/papers/ccs06hotornot.pdf (Archived: https://web.archive.org/web/20130205021944/https://www.cl.cam.ac.uk/~sjm217/papers/ccs06hotornot.pdf)
- [2] https://web.archive.org/web/20130429084306/http://caia.swin.edu.au/talks/CAIA-TALK-080728A.pdf
- [3] https://murdoch.is/papers/ih05coverttcp.pdf (Archived: https://web.archive.org/web/20130326121117/http://www.cl.cam.ac.uk/~sjm217/papers/ih05coverttcp.pdf)
- [4] https://stackoverflow.com/questions/12231623/initial-sequence-number-generation-in-linux-tcp-stack/12232126
- [5] https://gitlab.torproject.org/legacy/trac/-/issues/16659
- [6] https://elixir.bootlin.com/linux/v3.16-rc1/source/net/core/secure_seq.c#L26
- [7] https://forums.whonix.org/t/tcp-isns-and-temperature-induced-clock-skews/18862
[8] https://forums.whonix.org/t/tcp-isn-cpu-information-leak-protection-tirdad/8552
[9] https://mailarchive.ietf.org/arch/msg/tcpm/FzXQv-QmlQyMi-hbvGpg9uCB5Zs/
- [A] https://gitlab.torproject.org/legacy/trac/-/issues/16659#note_2196153
- [B] https://gitlab.torproject.org/legacy/trac/-/issues/16659#note_2196161

## How to install `tirdad` using apt-get ##

1\. Download the APT Signing Key.

```
wget https://www.kicksecure.com/keys/derivative.asc
```

Users can [check the Signing Key](https://www.kicksecure.com/wiki/Signing_Key) for better security.

2\. Add the APT Signing Key.

```
sudo cp ~/derivative.asc /usr/share/keyrings/derivative.asc
```

3\. Add the derivative repository.

```
echo "deb [signed-by=/usr/share/keyrings/derivative.asc] https://deb.kicksecure.com trixie main contrib non-free" | sudo tee /etc/apt/sources.list.d/derivative.list
```

4\. Update your package lists.

```
sudo apt-get update
```

5\. Install `tirdad`.

```
sudo apt-get install tirdad
```

## How to Build deb Package from Source Code ##

Can be build using standard Debian package build tools such as:

```
dpkg-buildpackage -b
```

See instructions.

NOTE: Replace `generic-package` with the actual name of this package `tirdad`.

* **A)** [easy](https://www.kicksecure.com/wiki/Dev/Build_Documentation/generic-package/easy), _OR_
* **B)** [including verifying software signatures](https://www.kicksecure.com/wiki/Dev/Build_Documentation/generic-package)

## Contact ##

* [Free Forum Support](https://forums.kicksecure.com)
* [Premium Support](https://www.kicksecure.com/wiki/Premium_Support)

## Donate ##

`tirdad` requires [donations](https://www.kicksecure.com/wiki/Donate) to stay alive!
