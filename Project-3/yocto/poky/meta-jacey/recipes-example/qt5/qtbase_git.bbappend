SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"
 
PACKAGECONFIG:append = " eglfs fontconfig gles2 "
DEPENDS += "userland"