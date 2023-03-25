# DO NOT RUN THIS CODE
I have no idea how it works

---

see
[Ruan de Bruyn's Medium post](https://medium.com/dvt-engineering/how-to-write-your-first-linux-kernel-module-cf284408beeb)
for a nice guide.

see
[Linux Device Drivers, 3rd Edition](https://lwn.net/Kernel/LDD3/) for a guided
deep-dive into Linux module development, but bear in mind the publication date.

---

use Kconfig

# todo

```
[    3.772197] test_logger_mod: module verification failed: signature and/or required key missing - tainting kernel
```

# before

## generate ctags for vim navigation

```
ctags -R /usr/src/linux-headers-`uname -r`/include
```

```
sudo apt install build-essential kconfig
sudp apt install linux-headers-$(uname -r) linux-modules-extra-$(uname -r) linux-modules-$(uname -r)
sudo apt install pahole
# for BNF warnings. can't be a hardlink
sudo cp /sys/kernel/btf/vmlinux /lib/modules/`uname -r`/build/
```


# build

```
make clean
make all
```

# one-shot load

```
sudo insmod test-logger-mod.ko
sudo dmesg
```


# install

no idea what to expect when installing a new kernel... `uname -r` should be
fine\*

```
sudo cp test-logger-mod.ko /usr/lib/modules/`uname -r`/kernel/drivers
# add test_logger_mod entry in /etc/modules
sudo modprobe test_logger_mod
sudo depmod
```


# uninsall

```
sudo rm /usr/lib/modules/`uname -r`/kernel/drivers
# remove test_logger_mod entry from /etc/modules
```

