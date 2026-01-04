## 系统下载22.04
https://www.openeuler.openatom.cn/zh/download/archive/detail/?version=openEuler%2024.03%20LTS%20SP2
1.欧拉系统安装
2.配置xfce的环境

显示中文
sudo yum install google-noto-sans-cjk-sc-fonts 

3.安装VWare Tools 的工具
安装 open-vm-tools

sudo yum remove open-vm-tools open-vm-tools-desktop

bash
- 安装核心工具
sudo dnf install -y open-vm-tools
sudo dnf install open-vm-tools-desktop

- 启用开机自启
sudo systemctl enable vmtoolsd

- 2. 重启 open-vm-tools 服务，或直接重启虚拟机
sudo systemctl restart vmtoolsd
- 启动服务
sudo systemctl start vmtoolsd

- 检查状态
sudo systemctl status vmtoolsd
复制粘贴功能依赖于两个后台代理程序。在终端中手动启动它们：

bash
- 1. 启动文件传输代理（处理拖放）
/usr/bin/vmware-user-suid-wrapper &

- 2. 启动剪贴板代理（处理复制粘贴）
/usr/bin/vmware-user  &
配置自动启动代理（永久生效）
需要将这些代理程序添加到您的桌面环境自动启动项中。以常见的 GNOME 为例：

搜索并打开 “启动应用程序” 工具。

点击 “添加”。

分别创建两条启动项：

名称: VMware Clipboard Agent
命令: /usr/bin/vmware-user

名称: VMware File Transfer Agent
命令: /usr/bin/vmware-user-suid-wrapper

保存，注销并重新登录（或重启）使配置生效。
3. 配置共享文件夹（如果需要）
bash
- 创建挂载点
sudo mkdir -p /mnt/hgfs

- 手动挂载（每次启动需要,VMware 共享文件夹在虚拟机设置中启用）
sudo mount -t fuse.vmhgfs-fuse .host:/ /mnt/hgfs -o allow_other

  或添加到 /etc/fstab 自动挂载
echo ".host:/ /mnt/hgfs fuse.vmhgfs-fuse allow_other 0 0" | sudo tee -a /etc/fstab


## 网络配置
```
cd /etc/systemd/network/

vi 10-static-eth0.network

enu1u2
=ip/23

systemctl restart systemd-networkd

```

## Qt安装，80G空间

~/qt-everywhere-src-5.15.10/configure \
    -prefix /opt/Qt/5.15.10/ \
    -debug \
    -opensource \
    -confirm-license \
    -xcb \
    -skip qtdoc \
    -skip qtwebengine \
    -skip qt3d \
    -skip qtcharts \
    -skip qtdatavis3d \
    -skip qtgamepad \
    -skip qtlottie \
    -skip qtquick3d \
    -skip qtremoteobjects \
    -skip qtscript \
    -skip qtsensors \
    -skip qtserialbus \
    -skip qtspeech \
    -skip qtvirtualkeyboard \
    -skip qtnetworkauth \
    -skip qtpurchasing \
    -nomake tests
    
# 安装 gperf
sudo dnf install -y gperf

# 验证安装
which gperf
gperf --version

# 安装 XCB 相关依赖
sudo dnf install -y \
    libxcb-devel \
    xcb-util-devel \
    xcb-util-image-devel \
    xcb-util-keysyms-devel \
    xcb-util-renderutil-devel \
    xcb-util-wm-devel \
    xcb-util-cursor-devel


# 安装 X11 其他必要依赖
sudo dnf install -y \
    libX11-devel \
    libXext-devel \
    libXfixes-devel \
    libXi-devel \
    libXrender-devel \
    libXrandr-devel \
    libXcursor-devel \
    libXinerama-devel \
    libxshmfence-devel \
    libepoxy-devel


# 安装 qtwebengine

    /opt/Qt/5.15.10/bin/qmake ~/qt-everywhere-src-5.15.10/qtwebengine/qtwebengine.pro CONFIG+=debug 

    WEBENGINE_CONFIG+=use_system_re2

    /opt/Qt/5.15.10/bin/qmake ../qtwebengine.pro \
    CONFIG+=debug \
    QMAKE_CXXFLAGS+="-I/usr/local/include -I/usr/local/include/re2" \
    QMAKE_LFLAGS+="-L/usr/local/lib -L/usr/lib64" \
    LIBS+="-L/usr/local/lib -lre2" \
    PKG_CONFIG_PATH=/usr/local/lib/pkgconfig:/usr/lib64/pkgconfig \
    WEBENGINE_CONFIG+=use_system_re2 \
    WEBENGINE_CONFIG-=pdf \
    WEBENGINE_CONFIG+=use_proprietary_codecs


    升级到5.15.14，解决这个问题

"cmakeCommandArgs": "-DQt5_DIR=C:/Qt/Qt5.9.9/5.9.9/msvc2017_64/lib/cmake/Qt5",


交叉编译环境搭建
查看文档，编译内核开发环境，不要其他，内核和镜像文件太大，20G不够


# QTDIR指向Qt安装根目录
export QTDIR=/usr/local/Qt-5.13.0

# PATH需要包含bin目录，用于找到Qt工具（qmake, moc, uic等）
export PATH=$QTDIR/bin:$PATH

# LD_LIBRARY_PATH需要包含lib目录，用于运行时查找Qt库文件（.so文件）
export LD_LIBRARY_PATH=$QTDIR/lib:$LD_LIBRARY_PATH

查看系统信息，命令如下：


cat /etc/os-release
查看系统相关的资源信息。

查看CPU信息，命令如下：


# lscpu
查看内存信息，命令如下：


# free
查看磁盘信息，命令如下：


# fdisk -l
查看IP地址，命令如下：


# ip addr

最小虚拟化空间要求
openEuler所需的最小虚拟化空间要求如表3所示。

表 3 最小虚拟化空间要求

部件名称	最小虚拟化空间要求
架构	AArch64或x86_64
CPU	2个CPU
内存	不小于4GB（为了获得更好的应用体验，建议不小于8GB）
硬盘	不小于32GB（为了获得更好的应用体验，建议不小于120GB）