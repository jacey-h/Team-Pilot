# Adding other functions (WIFI, CAN, I2C, Auto-start etc)

### **Table of Contents**
- ### [WIFI with systemd](#wifi-with-systemd)   
- ### [CAN](#can) 
- ### [I2C](#i2c) 
- ### [Auto login](#auto-login) 
- ### [Splash](#splash) 

## WIFI with systemd

If you want to use init manager as systemd, follow this step.

1. Enable systemd

```jsx
cd ~/yocto/poky/build/conf
vim local.conf
```

Add this line:

```jsx
# To use init manager as systemd
DISTRO_FEATURES:append = " systemd"
DISTRO_FEATURES_BACKFILL_CONSIDERED += "sysvinit"
VIRTUAL-RUNTIME_init_manager = "systemd"
VIRTUAL-RUNTIME_initscripts = ""
```
2. Enable wifi

```jsx
cd ~/yocto/poky/build/conf
vim local.conf
```

Add this line:

```jsx
# Wifi
IMAGE_INSTALL:append = " wpa-supplicant"
```

3.  Modify systemd recipe in custom layer

```jsx
cd ~/yocto/poky/meta-jacey/recipes-example/wifi
vim systemd_%.bbappend
```

#### [systemd_%.bbappend](WIFI/systemd_%25.bbappend)
    

```jsx
cd ~/yocto/poky/meta-jacey/recipes-example/wifi
mkdir files
cd files
vim wlan.network
```

#### [wlan.network](WIFI/wlan.network)
    

4.  Modify wpa-supplicant recipe in custom layer

```jsx
cd ~/yocto/poky/meta-jacey/recipes-example/wifi
vim wpa-supplicant_%.bbappend
```

#### [wpa-supplicant_%.bbappend](WIFI/wpa-supplicant_%25.bbappend)
    

    

```jsx
cd ~/yocto/poky/meta-jacey/recipes-example/wifi
mkdir files
cd files
vim wpa_supplicant-nl80211-wlan0.conf
```

#### [wpa_supplicant-nl80211-wlan0.conf](WIFI/wpa_supplicant-nl80211-wlan0.conf)   


## CAN

1. Enable CAN

```jsx
~/yocto/poky/meta-mylayer/recipes-bsp/bootfiles
vim rpi-config_git.bbappend
```

Add this line

```jsx
#In order to use CAN with an MCP2515-based module, set the following variables:
ENABLE_CAN = "1"
#In case of dual CAN module (e.g. PiCAN2 Duo), set following variables instead:
#ENABLE_DUAL_CAN = "1"

CAN_OSCILLATOR="16000000"
do_deploy:append() {
    echo "dtoverlay=spi-bcm2835-overlay" >> ${DEPLOYDIR}/bootfiles/config.txt
    echo "max_framebuffers=2" >> ${DEPLOYDIR}/bootfiles/config.txt
}
```

2. IMAGE_INSTALL

Add this line in your bitbake image

```jsx
IMAGE_INSTALL:append = " can-utils libsocketcan"
```

3. Build and Run

```jsx
ip link set can0 up type can bitrate 500000
candump can0
```

## I2C

For taking battery level, We should use ina219 on yocto.

1. Enable I2C

```jsx
~/yocto/poky/meta-mylayer/recipes-bsp/bootfiles
vim rpi-config_git.bbappend
```

Add this lines:

```jsx
ENABLE_I2C = "1"
KERNEL_MODULE_AUTOLOAD:rpi += "i2c-dev i2c-bcm2708"
```

additionally, you can enable `UART`, `SPI`

```jsx
ENABLE_UART = "1"
ENABLE_SPI_BUS = "1"
```

2. Make test bb.file

```jsx
cd ~/yocto/poky/meta-jacey/recipes-example
mkdir pi-ina219
cd pi-ina219
```

```jsx
git clone https://github.com/kevinboone/pi-ina219.git
```

You can get source files in this git directory.

```jsx
cd ~/yocto/poky/meta-jacey/recipes-example/pi-ina219/pi-ina219
vim CMakeLists.txt
```

#### [CMakeLists.txt](I2C/CMakeLists.txt)   
    

    

```jsx
cd ~/yocto/poky/meta-jacey/recipes-example/pi-ina219
vim ina-battery.bb
```
#### [ina-battery.bb](I2C/ina-battery.bb)   
  

## Auto login

- Modify your custom image

Just add following lines in your bb file.

```jsx
KIRKSTONE_LOCAL_GETTY ?= " \
    ${IMAGE_ROOTFS}${systemd_system_unitdir}/serial-getty@.service \
    ${IMAGE_ROOTFS}${systemd_system_unitdir}/getty@.service \
"

local_autologin () {
     sed -i -e 's/^\(ExecStart *=.*getty \)/\1--autologin root /' ${KIRKSTONE_LOCAL_GETTY}
}

ROOTFS_POSTPROCESS_COMMAND += "local_autologin; "
```

## Splash

If you use `core-image-base`

When you boot up raspberry pi, You can see splash image.

Here is how to change this image.

1. Git clone

```jsx
cd ~/yocto/poky
git clone https://github.com/hamzamac/meta-splash
```

2. Add new layer

```jsx
cd ~/yocto/poky/build/conf
vim bblayers.conf
```

Add following line:

```jsx
/home/username/yocto/poky/meta-splash \  
```

3. Add your image

```jsx
cd ~/yocto/poky/meta-splash/recipes-core/psplash/files
```