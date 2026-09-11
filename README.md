# Experimental Cloud
Development of a personal and cross-platform cloud.

Storage runs on a <b>Raspberry Pi 5</b> and an app allows users to access this server (both iPhone and macOS compatibility).

## Summary

### Current tasks
Currently, the goal is to setup the Raspberry Pi and the code that manages connections and package delivery.
In parallel, the first front-end software developed is a macOS app, to make tests easier with the Raspberry Pi.

### Front-end description
The goal is to be able to access the cloud by two means:

- With a phone, a dedicated application allows user to visualize and modify the storage tree (adding files, removing files, creating folders, etc.) Ideally, pictures are displayed smoothly without requiring users to download the full-resolution files.

- With a computer, the stockage will firstly be accessible through an app. But the final goal is much more complex : ideally, all changes will be displayed in a virtual file system in the Finder and will appear just like a regular folder. But this last option requires an Apple signed ID and rights hard to obtain on a mac (at first sight).

### Back-end description
The back-end folder contains the code that is permanently running on the Raspberry Pi.
It should check for requests, ask for the password and deliver the packages.

## Details

### Raspberry Pi 5
The RPi is running on the Raspberry Pi OS Lite, a port of <b>Debian</b> Trixie. A NVMe SSD is used for storage and booting. This SSD is split in three: the third part is dedicated to file storage (mounted on <i>/mnt/storage/</i>) while the code and the OS are stored in the two first parts.

For debugging purposes, the RPi is accessed by SSH from a computer.

Code is uploaded using :
```
scp cloudberry-be username@pi.local:/home/username/
scp -r cloudberry-be.dSYM username@pi.local:/home/username/

scp stop.sh username@pi.local:/home/username/
```

C++ files are compiled using <i>messense/homebrew-macos-cross-toolchains</i> to fit the RPi's architecture.

### Code
Front-end is coded in <b>C#</b>, using Avalonia.MVVM template, while back-end mainly is <b>C++</b>.
