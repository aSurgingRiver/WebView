linux下和vulkan版本有关：
1. 1.2.131，兼容Ubuntu20
2. 1.3.204，兼容Ubuntu22

cef内核对应vulkan版本：
5060： 1.2.0
6099:  1.3.0

cef和linux的vulkan版本要保持一致如1.3.* 、1.2.*
否则会发生冲突

依赖库：
apt(Debian/Ubuntu)         yum/dnf(RHEL/CentOS)
libx11-dev                 libX11-devel
libglib2.0-dev             glib2-devel
libgtk-3-dev               gtk3-devel  epel-release


配置依赖路径:
pkg-config --cflags --libs glib-2.0
