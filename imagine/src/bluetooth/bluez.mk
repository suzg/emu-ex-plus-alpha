ifndef inc_bluetooth_bluez
inc_bluetooth_bluez := 1

include $(IMAGINE_PATH)/make/package/bluez.mk

include $(imagineSrcDir)/bluetooth/bluetooth.mk

SRC += bluetooth/BluezBluetoothAdapter.cc

endif
