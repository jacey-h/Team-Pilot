# Yocto basic


- ## Contents

- ## Reference site
    
    [YP Release wiki page](https://wiki.yoctoproject.org/wiki/Releases)
    
    [OpenEmbedded Layer Index](http://layers.openembedded.org/layerindex/branch/master/layers/)
    
    [Build Rpi4 Qt5 using Yocto project](http://www.yocto.co.kr/2017/03/yocto-morty-22-qtv57.html)
    
    [Hacking Raspberry Pi 4 with Yocto](https://lancesimms.com/RaspberryPi/HackingRaspberryPi4WithYocto_Part5.html)
    
---
## Step 1. Downloading Yocto

### 1. ****Build Host Packages****

```jsx
sudo apt install bmap-tools zstd liblz4-tool gawk wget git-core diffstat unzip texinfo gcc-multilib build-essential chrpath socat libsdl1.2-dev xterm python
```

### 2. Make a directory

```jsx
cd ~
mkdir yocto
cd ~/yocto
```

### 3. ****Use Git to Clone Poky****

<img src="https://user-images.githubusercontent.com/81483791/210563162-7a6747d3-ba9a-4455-b687-f98070da2da1.png"  width="500" height="110"/> 

We choose a release codename (such as `kirkstone`)

```jsx
git clone -b kirkstone git://git.yoctoproject.org/poky.git
```

### 4. Clone raspberry pi and extension

```jsx
cd poky
git clone -b kirkstone git://git.yoctoproject.org/meta-raspberrypi
git clone -b kirkstone git://git.openembedded.org/meta-openembedded
```

### 5. **Initialize the Build Environment**

From within the poky directory, run the [oe-init-build-env](https://docs.yoctoproject.org/ref-manual/structure.html#oe-init-build-env) environment setup script to define Yocto Project’s build environment on your build host. 

```jsx
cd poky
source oe-init-build-env
```

### 6. Add new layer

```jsx
cd ~/yocto/poky/build/conf
vim bblayers.conf
```

Add following line:

```jsx

/home/**username**/yocto/poky/meta-raspberrypi \  
/home/**username**/yocto/poky/meta-openembedded/meta-oe \
/home/**username**/yocto/poky/meta-openembedded/meta-multimedia \
/home/**username**/yocto/poky/meta-openembedded/meta-networking \
/home/**username**/yocto/poky/meta-openembedded/meta-perl \
/home/**username**/yocto/poky/meta-openembedded/meta-python \
```

- My case
    
    ```jsx
    # POKY_BBLAYERS_CONF_VERSION is increased each time build/conf/bblayers.conf
    # changes incompatibly
    POKY_BBLAYERS_CONF_VERSION = "2"
    
    BBPATH = "${TOPDIR}"
    BBFILES ?= ""
    
    BBLAYERS ?= " \
      /home/seame-two/yocto/poky/meta \
      /home/seame-two/yocto/poky/meta-poky \
      /home/seame-two/yocto/poky/meta-yocto-bsp \
      /home/seame-two/yocto/poky/meta-raspberrypi \  
      /home/seame-two/yocto/poky/meta-openembedded/meta-oe \
      /home/seame-two/yocto/poky/meta-openembedded/meta-multimedia \
      /home/seame-two/yocto/poky/meta-openembedded/meta-networking \
      /home/seame-two/yocto/poky/meta-openembedded/meta-perl \
      /home/seame-two/yocto/poky/meta-openembedded/meta-python \
      "
    ```
    

### 7. Update MACHINE and change directory

```jsx
cd ~/yocto/poky/build/conf
vim local.conf
```

If we want to build for the Raspberry Pi 4, we're using `raspberrypi4`

or we can also use 64bit rpi4  `MACHINE = "raspberrypi4-64"`

change the following line:

`MACHINE ??= "qemux86-64"` -> `MACHINE = "raspberrypi4-64"`

```jsx
MACHINE = "raspberrypi4-64"
```

<img src="https://user-images.githubusercontent.com/81483791/210563539-5ddb408b-98ce-4dda-b223-5b35a5f4b17d.png"  width="500" height="110"/> 

Add the end of file following lines:

```jsx
# Uncomment and set to allow bitbake to execute multiple tasks at once. 
# For a quadcore, BB_NUMBER_THREADS = "4", PARALLEL_MAKE = "-j 4" would 
# be appropriate. 
BB_NUMBER_THREADS = "8" 
# Also, make can be passed flags so it run parallel threads e.g.: 
PARALLEL_MAKE = "-j 8"
```

```jsx
# For SD card image 
IMAGE_FSTYPES = "tar.xz ext3 rpi-sdimg"
```

### 8. Edit machine.conf

```jsx
cd ~/yocto/poky/meta-raspberrypi/conf/machine
vim raspberrypi4-64.conf
```

Change this line:

Please Edit `vc4-kms-v3d` to `vc4-fkms-v3d-pi4`

```jsx
//VC4DTBO ?= "vc4-kms-v3d"
VC4DTBO ?= "vc4-fkms-v3d-pi4"
```

### 9. Build

```jsx
cd yocto/poky
source oe-init-build-env
bitbake core-image-base
```

In the [Yocto documentation](https://docs.yoctoproject.org/ref-manual/images.html), you find a short description of the available image descriptions.

- `core-image-minimal`: A small image just capable of allowing a device to boot.
- `core-image-base`: A console-only image that fully supports the target device hardware.
- `core-image-full-cmdline`: A console-only image with more full-featured Linux system functionality installed.

## Step 2. Write Os in SD card

### 1. Find where SD card is

```jsx
sudo fdisk -l
```

OUTPUT:


<img src="https://user-images.githubusercontent.com/81483791/210563632-c94aee57-9f76-45d8-8cd0-fbdc6fefc834.png"  width="500" height="110"/> 

### 2. umount

```jsx
umount /dev/sda
// umount: /dev/sda: not mounted
```

### 3. Write image to SD card

When you done bitbake, You can find `rpi-sdimg` file.

```jsx
cd ~/yocto/poky/build/tmp/deploy/images/raspberrypi4-64
sudo dd if=api-image-raspberrypi4-64-20221227103058.rootfs.rpi-sdimg of=/dev/sda
```

- **Other solution**
    
    ### 3-1. Decompressed the file
    
    ```jsx
    cd ~/yocto/poky/build/tmp/deploy/images/raspberrypi4
    sudo bzip2 -dk core-image-minimal-raspberrypi4-20221116105144.rootfs.wic.bz2
    ```
    
    - **Trouble Shooting**
        
        
        <img src="https://user-images.githubusercontent.com/81483791/210563625-a1825484-999e-44e7-8091-1babad6b94a5.png"  width="500" height="110"/> 

        ```jsx
        cd ~/yocto/poky/build/tmp/deploy/images/raspberrypi4
        cp core-image-minimal-raspberrypi4-20221116105144.rootfs.wic.bz2 ../
        cd ..
        sudo bzip2 -dk core-image-minimal-raspberrypi4-20221116105144.rootfs.wic.bz2
        ```
        
    
        <img src="https://user-images.githubusercontent.com/81483791/210563626-2bd5545f-dd9b-4d08-9226-2b6ead904e68.png"  width="500" height="110"/> 

    
    ### 3-2. Write image to SD card
    
    ```jsx
    sudo dd if=core-image-minimal-raspberrypi4-20221116105144.rootfs.wic of=/dev/sda
    sync
    ```
    

### 4. Eject and reinsert SD card

Now, you can find boot and root 

<img src="https://user-images.githubusercontent.com/81483791/210563628-fef513f7-1c67-46ce-9765-3ba57634a864.png"  width="500" height="110"/> 

<img src="https://user-images.githubusercontent.com/81483791/210563620-b8bac3fc-a080-40f0-ac79-9f77ede15c48.png"  width="500" height="110"/> 

## Step 3. Add python

### 1. Edit image.bb  file

```jsx
cd ~/yocto/poky/meta/recipes-core/images
vim core-image-base.bb
```

Add following line:

```jsx
IMAGE_INSTALL += "python3 python3-numpy"
```

- My case
    
    ```jsx
    SUMMARY = "A small image just capable of allowing a device to boot."
    
    IMAGE_INSTALL = "packagegroup-core-boot ${CORE_IMAGE_EXTRA_INSTALL}"
    
    IMAGE_LINGUAS = " "
    
    LICENSE = "MIT"
    
    inherit core-image
    
    IMAGE_ROOTFS_SIZE ?= "8192"
    IMAGE_ROOTFS_EXTRA_SPACE:append = "${@bb.utils.contains("DISTRO_FEATURES", "systemd", " + 4096", "", d)}"
    
    IMAGE_INSTALL += "python3 python3-numpy"
    ```
    

### 2. Build

```jsx
cd ~/yocto/poky
source oe-init-build-env
bitbake -c cleanall core-image-base
bitbake core-image-base
```

Then, follow [Step 2.](https://www.notion.so/Yocto-basic-4ef530584f1442a781732f34833c3346)

### 3. Booting and Executing python file

When you do first login, 

`login : root`

If you want to execute python file,

Now we can only use `vi`

```jsx
vi start.py
```

```jsx
print("Hello World!")
```

For this simple test code, you can check python3 

```jsx
python3 start.py
```


<img src="https://user-images.githubusercontent.com/81483791/210563614-153c5e79-cc41-4e89-817f-b98959e8796f.jpg"  width="500" height="110"/> 

## Step 4. Add g++

When we want to add recipe, we can change .bb file or local.conf file

### 1. Edit image.bb  file

```jsx
cd ~/yocto/poky/build/conf
vim local.conf
```

Add following line:

```jsx
CORE_IMAGE_EXTRA_INSTALL += " packagegroup-core-buildessential"
```

### 2. Build

```jsx
cd ~/yocto/poky
source oe-init-build-env
bitbake -c cleanall core-image-base
bitbake core-image-base
```

Then, follow [Step 2.](https://www.notion.so/Yocto-basic-4ef530584f1442a781732f34833c3346)


<img src="https://user-images.githubusercontent.com/81483791/210563622-d3e36683-8a0c-47c0-8111-af2e6161d146.png"  width="500" height="110"/> 

## Step 5. Build Qt on our own rpi4

### 1. Download meta-qt5

```jsx
cd ~/yocto/poky
git clone -b kirkstone https://github.com/meta-qt5/meta-qt5
```

### 2. Add new layer

```jsx
cd ~/yocto/poky/build/conf
vim bblayers.conf
```

Add following line:

```jsx
/home/**username**/yocto/poky/meta-qt5 \  
```

### 3. Add qtbase example package

```jsx
cd ~/yocto/poky/build/conf
vim local.conf
```

Add this line:

```jsx
CORE_IMAGE_EXTRA_INSTALL:append = " qtbase-examples"
```

### 4. Make a directory and .bbappend file

```jsx
cd ~/yocto/poky/meta-poky
mkdir -p recipes-qt/qt5
cd recipes-qt/qt5
vim qtbase_%.bbappend
```

Add this line:

```jsx
PACKAGECONFIG:append = " examples gles2 eglfs"
PACKAGECONFIG:remove = "tslib"
```

### 5. Build

```jsx
cd ~/yocto/poky
bitbake -c cleanall core-image-minimal
bitbake core-image-minimal
```

Then, follow [Step 2.3 ~2.6](https://www.notion.so/Yocto-basic-4ef530584f1442a781732f34833c3346)

### 6. Execute qt example file on Rpi4


<img src="https://user-images.githubusercontent.com/81483791/210563618-7e8a2812-be98-4b73-ab84-09d5bfbe3b21.jpg"  width="500" height="110"/> 

Boot and Login your raspberry pi.

Execute this simple example file.

```jsx
cd /usr/share/qt5/examples/opengl/hellowindow
```

```jsx
./hellowindow -platform eglfs
```

---