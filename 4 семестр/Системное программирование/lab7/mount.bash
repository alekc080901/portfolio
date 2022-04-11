dd if=/dev/zero of=vfs-image count=20480
mke2fs -q ./vfs-image
mkdir vfs
mknod /dev/loop0 b 7 0
mount -o loop=/dev/loop0 ./vfs-image ./vfs
df -h ./vfs
