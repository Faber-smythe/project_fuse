<h1 align="center">Project Fuse</h1>

<p align="center" height="80px">

<img style="height: 80px; margin: 0px 20px" src="https://dvic.devinci.fr/static/img/uploads/1580643817504-AeOG5rDzar33ga5BVMJK.png" >

<img style="height: 80px; margin: 0px 20px" src="https://pngimg.com/uploads/linux/linux_PNG12.png" >

<img style="height: 80px; margin: 0px 20px" src="https://cdn.iconscout.com/icon/free/png-256/c-programming-569564.png" >

</p>

_A C programming exercise about Linux filesystem, asked for in  the **[DVIC](https://dvic.devinci.fr/)**'s IRM course._

---

Libfuse is a software interface used to mount filesystems in the userspace. 
This project's assignment can be found in the [PDF file](https://github.com/Faber-smythe/project_fuse/blob/master/README.md)




# Installation


Please keep in mind, this project was made on Ubuntu, and is meant to run on Linux only.
- **Clone this repository on your machine**
- **Make sure you have fuse version 2.9 or higher on your machine**
  ```
  fusermount --v
  ```
- Compile the `main.c` file with the following command :
  ``` 
  gcc -Wall main.c `pkg-config fuse --cflags --libs` -o main
  ```

# Usage

The compiled executable is used in commandline to mount the pseudo filesystem onto the `mnt` folder.
```
./main -f mnt
```
The only argument needed is the mount point (here the empty `mnt` folder). Flag -f allows commandline to print further output until process interruption (e.g. using `ctrl+c`).


## Features

Three features have been implemented, each exposing a file.


| File       | Action  | Description                      |
| ---------- | ------ | --------------------------------- |
| `hello` | read |  This file can be opened and its content can be read |
| `output` | write | Text written into this is output in the console |     
| `shutdown` | write | Any attempt to write on this file results in the computer shutting down

Writing onto a file is best done from another commandline (the first one being busy during the execution), for example as follows :
  ```
  echo "hello world !" >> ./mnt/output
  ```
  
  # Thanks
  ```
  Nice of you to help, Grégor, Guillaume, Paul-Peter !  \ (◠﹏◠) 
  ```
