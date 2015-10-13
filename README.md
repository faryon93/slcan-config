# slcan-config
This project should allow users of serial-line CAN adapters to reconfigure them while they are attached.
At the moment, the device has to be detached and re-attached to change configuration parameters, this operations have way to much overhead so a simpler way is needed.

A set of patches is applied to the slcan kernel module, to expose some adapter settings via ioctl() calls.


## Implemented Features

- reconfigure bitrate
