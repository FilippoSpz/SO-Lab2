# Directory Content Viewer

This project is a C program that recursively lists the contents of a directory and its subdirectories, displaying
detailed information about each file and directory.

## Features

- Recursively traverses directories starting from a specified root directory.
- Displays the following information for each file:
    - **Name**: Full path relative to the root directory.
    - **Inode Number**: The inode number of the file.
    - **Type**: File type (e.g., `file`, `directory`, `symbolic link`, `FIFO`, or `other`).
    - **Size**: File size in bytes.
    - **Owner**: User ID and username of the file owner.
    - **Group**: Group ID and group name of the file owner.

---

# Directory Content Viewer

This project is a C program that recursively lists the contents of a directory and its subdirectories, displaying
detailed information about each file and directory.

---

## Usage

1. Compile the program using a C compiler, for example:
   ```bash
   gcc -o directory_viewer main.c

2. The output will look like:

    ```c
    Node: ./root
    Inode: 15482892
    Type: directory
    Size: 4096
    Owner: 1000 username
    Group: 1000 groupname
    
    Node: ./root/dir
    Inode: 15482893
    Type: directory
    Size: 4096
    Owner: 1000 username
    Group: 1000 groupname
    
    Node: ./root/dir/test
    Inode: 15472878
    Type: file
    Size: 512
    Owner: 1000 username
    Group: 1000 groupname'  

---

## License

This project is intended for educational purposes only and is not meant for commercial use.

---

## Author

- **Name**: [Filippo Spazzali]
- **School**: [Università degli Studi di Trieste]
- **Course**: [Computer Science]
