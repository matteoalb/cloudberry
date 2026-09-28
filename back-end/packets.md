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

## Sent to clients