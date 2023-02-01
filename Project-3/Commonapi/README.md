# Commonapi-dbus


- Contents

- Reference
    
    [meta-ivi](https://github.com/GENIVI/meta-ivi) 
    
    [meta-ivi/common-api](https://ggangjo.tistory.com/211)
    
    [dbus_1.10.10](http://cgit.openembedded.org/openembedded-core/tree/meta/recipes-core/dbus/dbus_1.10.10.bb?h=morty)
    
    [systemd](https://velog.io/@markyang92/yocto-meta-raspberrypi)
    

### Step 1. Download `meta-ivi` file

```jsx
cd ~/yocto/poky
wget
unzip 
```

- *If you want to git clone from official site.*
    
    ### Step 1. git clone
    
    ```jsx
    cd ~/yocto/poky
    git clone https://github.com/GENIVI/meta-ivi.git
    ```
    
    ### Step 2. Change version
    
    ```jsx
    cd ~/yocto/poky/meta-ivi/meta-ivi/conf
    vim layer.conf
    ```
    
    Edit following line.
    
    ```jsx
    LAYERSERIES_COMPAT_ivi = "kirkstone"
    ```
    
    This version has old override syntax.
    
    We should change this override syntax. ex) `IMAGE_INSTALL_append` → `IMAGE_INSTALL:append`
    
    From kirkstone version, use `:` instead of `_`  .
    

### Step 2.  Add build system

```jsx
cd ~/yocto/poky/build/conf
vim bblayers.conf
```

Add following line:

```jsx
/home/**username**/yocto/poky/meta-ivi/meta-ivi \  
```

### Step 3. Edit local.conf file

```jsx
cd ~/yocto/poky/build/conf
vim local.conf
```

Add following line

```jsx
DISTRO_FEATURES:append = " systemd"
DISTRO_FEATURES_BACKFILL_CONSIDERED += "sysvinit"
VIRTUAL-RUNTIME_init_manager = "systemd"
VIRTUAL-RUNTIME_initscripts = ""
```

It makes that we use `systemd` instead of `sysvinit` .

### Step 4. Change dbus version.

For using commonapi dbus, We should use matching version.

```jsx
~/yocto_re/poky/meta-ivi/meta-ivi/recipes-extended/common-api
open .
```

In this directory,  you can find this .bb file.

![Untitled](Commonapi-dbus%207cbc82efde7348e5a81d2b62189f657b/Untitled.png)

Also, you can check commonapi version.

`common-api-c++_3.1.12.6.bb`

`common-api-c++-dbus_3.1.12.11.bb`

I already matched this version in Project 2.

capicxx-core-runtime 3.1.12.6

capicxx-dbus-runtime 3.1.12.11

dbus-1.10.10

So, We need to use dbus 1.10.10 version.

But in kirkstone poky directory, there has dbus 1.14.0 version.

![Untitled](Commonapi-dbus%207cbc82efde7348e5a81d2b62189f657b/Untitled%201.png)

If you want to know more details, you can check [here](http://cgit.openembedded.org/openembedded-core/tree/meta/recipes-core/dbus/dbus_1.10.10.bb?h=morty).

**Then, How to downgrade dbus version?**

I already change dbus directory for changing version. So we just download this file.

```jsx
cd ~/yocto/poky/meta/recipes-core
rm -rf dbus
wget 
unzip
```

- *If you want to know how to change version.*
    
    dbus1.10.10 used [yocto morty](http://cgit.openembedded.org/openembedded-core/tree/meta/recipes-core/dbus?h=morty).
    
    ### 1. make new dbus dirctory
    
    ```jsx
    cd ~/yocto/poky/meta/recipes-core/dbus
    rm -rf *
    ```
    
    ![Untitled](Commonapi-dbus%207cbc82efde7348e5a81d2b62189f657b/Untitled%202.png)
    
    Make correctly same file.
    
    ### 2. Edit override syntax
    
    This version is too old. We should change `_` → `:`
    
    ex) `FILES_${PN}` → `FILES:${PN}`
    
    ### 3.  Add dbus patch
    
    ```jsx
    cd ~/yocto/poky/meta/recipes-core/dbus/dbus
    ```
    
    Please unzip this file and add `yocto/poky/meta/recipes-core/dbus/dbus` here.
    
    [dbus.zip](Commonapi-dbus%207cbc82efde7348e5a81d2b62189f657b/dbus.zip)
    
    This file is form `meta-ivi/meta-ivi/recipes-core-ivi/dbus` .
    
    If you want to check this file, you should `git clone https://github.com/GENIVI/meta-ivi.git`
    
    ```jsx
    cd ~/yocto/poky/meta/recipes-core/dbus
    vim dbus_1.10.10.bb
    ```
    
    Add following line in SRC_URI
    
    ```jsx
    file://capi-dbus-add-send-with-reply-set-notify.patch \
    file://capi-dbus-add-support-for-custom-marshalling.patch \
    file://0001-dbus-fix-possible-uninitialized-variable.patch \
    ```
    
    - My case
        
        ```jsx
        SRC_URI = "http://dbus.freedesktop.org/releases/dbus/dbus-${PV}.tar.gz \
                   file://tmpdir.patch \
                   file://dbus-1.init \
                   file://os-test.patch \
                   file://clear-guid_from_server-if-send_negotiate_unix_f.patch \
                   file://0001-configure.ac-explicitely-check-stdint.h.patch \
                   file://capi-dbus-add-send-with-reply-set-notify.patch \
            	   file://capi-dbus-add-support-for-custom-marshalling.patch \
        "
        ```
        
    
    ### 4. Edit patch file
    
    ```jsx
    cd ~/yocto/poky/meta/recipes-core/dbus/dbus
    vim capi-dbus-add-send-with-reply-set-notify.patch
    
    ```
    
    ```jsx
    vim capi-dbus-add-support-for-custom-marshalling.patch
    
    ```
    
    ```jsx
    vim 0001-dbus-fix-possible-uninitialized-variable.patch 
    ```
    
    Please Add this line. 
    
    ```jsx
    Upstream-Status: Backport [from dbus-1.10]
    ```
    

### Step 5. Make bb file

```jsx
cd ~/yocto/poky/build/meta-mylayer/recipes-core/images
vim api-test.bb
```

- `api-test.bb`
    
    ```jsx
    SUMMARY = "A basic Raspberry pi image"
    
    require recipes-core/images/core-image-minimal.bb 
    
    IMAGE_INSTALL += " common-api-c++ common-api-c++-dbus"
    export IMAGE_BASENAME = "api-test"
    ```
    

![Untitled](Commonapi-dbus%207cbc82efde7348e5a81d2b62189f657b/Untitled%203.png)

We can check `/root/usr/lib`