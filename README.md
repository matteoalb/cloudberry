# Experimental Cloud
Development of a personal and cross-platform cloud.

Storage runs on a Raspberry Pi 5 and an app allows users to access this server (both iPhone and macOS compatibility).

### Current tasks
Currently, the goal is to setup the Raspberry Pi and the code that manages connections and package delivery.
In parallel, the first front-end software developed is a macOS app, to make tests easier with the Raspberry Pi.

### Front-end description
The goal is to be able to access the cloud by two means:

- With a phone, a dedicated application allows user to visualize and modify the storage tree (adding files, removing files, creating folders, etc.) Ideally, pictures are displayed smoothly without requiring users to download the full-resolution files.

- With a computer, the stockage will firstly be accessible through an app (Avalonia.MVVM template). But the final goal is much more complex : ideally, all changes will be displayed in a virtual file system in the Finder and will appear just like a regular folder. But this last option requires an Apple signed ID and rights hard to obtain on a mac (at first sight).

### Back-end description
The back-end folder contains the code that is permanently running on the Raspberry Pi.
It should check for requests, ask for the password and deliver the packages.
The Raspberry Pi uses __ OS.
