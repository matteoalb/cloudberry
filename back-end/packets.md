# Packet Description

## Sent to server

Packet length   [Unsigned Short]
Request         [Unsigned Short]
Arguments

### Available Requests

0:  Ask for available space in /mnt/storage/
1:  Ask for hierarchy
        Args: starting folder path, depth
2:  Ask for file
        Args: preview? [bool], path
3:  Delete file
        Args: path
4:  Move file
        Args: oldPath, newPath
5:  Upload file
        Args: path, file

## Sent to clients