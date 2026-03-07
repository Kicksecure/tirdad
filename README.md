# TCP ISN CPU Information Leak Protection #

TCP Initial Sequence Numbers Randomization to prevent TCP ISN based CPU
Information Leaks.

The Linux kernel has a side-channel information leak bug.
It is leaked in any outgoing traffic.
This can allow side-channel attacks because sensitive information about
a system's CPU activity is leaked.

tirdad is a kernel module to hot-patch the Linux kernel
to generate random TCP Initial Sequence Numbers for IPv4 and IPv6 TCP
connections.

This metapackage depends on tirdad-dkms.

References: https://www.kicksecure.com/wiki/Tirdad

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
