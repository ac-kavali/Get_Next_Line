
![GNL](GNL1.png)

# Get_Next_Line

# Valgrind Memory Debugging Guide

## Check if Valgrind is Installed

```bash
user@host~> valgrind --version
```

If not found, install it using:

```bash
sudo apt install valgrind     # Debian/Ubuntu
sudo pacman -S valgrind       # Arch
sudo dnf install valgrind     # Fedora
```

If yes, proceed to the next step.

---

## A) Compile Your Program with Debugging Symbols

```bash
gcc -g -Wall -Wextra -Werror your_program.c -o program
```


## B) Run Your Program with Valgrind

### Basic usage:

```bash
valgrind ./program
```

### For memory debugging, always use:

```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./program
```

### What These Flags Mean:

- **`--leak-check=full`** → detailed leak info
- **`--show-leak-kinds=all`** → shows all leak types (definite, indirect, possible)
- **`--track-origins=yes`** → tells you where uninitialized values come from


## C) Understand Valgrind Output

### Example: Invalid Memory Access

```bash
==1234== Invalid write of size 4
==1234==    at  main (test.c:10)
==1234==  Address 0x1ffefff10 is not stack'd, malloc'd or free'd
```

This means you wrote to memory you shouldn't.

### Example: Memory Leak

```bash
==1234== 20 bytes in 1 blocks are definitely lost in loss record 1
==1234==    at  malloc (vg_replace_malloc.c:xxx)
==1234==    by main (test.c:12)
```

This means you **allocated memory and never freed it**.

## D) Check Summary at the End

The most important part:

```bash
HEAP SUMMARY:
    definitely lost: 20 bytes in 1 blocks
    indirectly lost: 0 bytes in 0 blocks
    possibly lost: 0 bytes in 0 blocks
    still reachable: 0 bytes
```

### Understanding the Summary:

- **definitely lost** → REAL memory leak (you must fix this)
- **indirectly lost** → leak caused by another leak
- **still reachable** → memory not freed before exit, but accessible
- **possibly lost** → suspicious pointer issues

---

## Other Uses of Valgrind

### For Segmentation Faults

When you suspect a segmentation fault, use:

```bash
valgrind --track-origins=yes --verbose ./a.out
```

This will give you detailed information about where and why the segfault occurred.
