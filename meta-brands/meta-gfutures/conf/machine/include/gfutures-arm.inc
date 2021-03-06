#IMAGE_CLASSES += "hd-emmc_image_single"
IMAGE_CLASSES += "hd-emmc_image_multi"

IMAGE_FSTYPES += "hd-emmc"
IMAGE_ROOTFS_SIZE ?= "196608"

TARGET_ARCH = "arm"
DEFAULTTUNE = "armv7ahf-neon"

IMAGE_CMD_hd-emmc_append = "\
    mkdir -p ${DEPLOY_DIR_IMAGE}/${MACHINE}; \
    mv ${DEPLOY_DIR_IMAGE}/${IMAGE_NAME}.emmc.img ${DEPLOY_DIR_IMAGE}/${MACHINE}/disk.img; \
    cd ${IMAGE_ROOTFS}; \
    tar -cvf ${DEPLOY_DIR_IMAGE}/rootfs.tar -C ${IMAGE_ROOTFS} .; \
    mv ${DEPLOY_DIR_IMAGE}/rootfs.tar ${DEPLOY_DIR_IMAGE}/${MACHINE}/rootfs.tar; \
    bzip2 ${DEPLOY_DIR_IMAGE}/${MACHINE}/rootfs.tar; \
    cp ${DEPLOY_DIR_IMAGE}/zImage ${DEPLOY_DIR_IMAGE}/${MACHINE}/${KERNEL_FILE}; \
    echo ${IMAGE_VER_STRING} > ${DEPLOY_DIR_IMAGE}/${MACHINE}/imageversion; \
    cd ${DEPLOY_DIR_IMAGE}; \
    zip ${IMAGE_NAME}_usb.zip ${MACHINE}/*; \
    rm -f ${DEPLOY_DIR_IMAGE}/*.ext4; \
    rm -f ${DEPLOY_DIR_IMAGE}/*.manifest; \
    rm -f ${DEPLOY_DIR_IMAGE}/.ext4; \
    rm -f ${DEPLOY_DIR_IMAGE}/.manifest; \
    rm -Rf ${MACHINE}; \
    "

require conf/machine/include/arm/arch-armv7a.inc
require conf/machine/include/gfutures-oem.inc