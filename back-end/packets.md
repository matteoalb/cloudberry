# Packet Description

## Sent to server

Packet length   [Unsigned Short]<br>
Request         [Unsigned Short]<br>
Arguments

### Available Requests

0:  Ask for available space in /mnt/storage/<br>
1:  Ask for hierarchy<br>
        Args: starting folder path, depth<br>
2:  Ask for file<br>
        Args: preview? [bool], path<br>
3:  Delete file<br>
        Args: path<br>
4:  Move file<br>
        Args: oldPath, newPath<br>
5:  Upload file<br>
        Args: path, file<br>

## Sent to clients
