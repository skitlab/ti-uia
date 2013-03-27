. $1

make -C packages/ti/uia/linux \
 IPC_INSTALL_DIR=$THIRD_PARTY_DIR/ipc \
 SYSLINK_INSTALL_DIR=$THIRD_PARTY_DIR/syslink \
all

make -C packages/ti/uia/examples/evmti816x \
 IPC_INSTALL_DIR=$THIRD_PARTY_DIR/ipc/packages \
 SYSLINK_INSTALL_DIR=$THIRD_PARTY_DIR/syslink/packages \
all

make -f uia.mak \
 DESTDIR=$THIRD_PARTY_DIR/devkit \
 XDC_INSTALL_DIR=$THIRD_PARTY_DIR/xdctools \
 BIOS_INSTALL_DIR=$THIRD_PARTY_DIR/bios \
 IPC_INSTALL_DIR=$THIRD_PARTY_DIR/ipc \
all install

make -f sdk.mk \
 DESTDIR=$THIRD_PARTY_DIR/devkit \
 XDC_INSTALL_DIR=$THIRD_PARTY_DIR/xdctools \
install
