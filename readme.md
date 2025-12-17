# Get Next Line (C)

Implementation of **get_next_line()**: a function that reads from a file descriptor and returns the next line each time it’s called (including the trailing `\n` when present), until EOF.

This repository contains:
- Mandatory version (single static remainder): `get_next_line.c`, `get_next_line_utils.c`, `get_next_line.h`
- Bonus version (handles multiple file descriptors): `get_next_line_bonus.c`, `get_next_line_utils_bonus.c`, `get_next_line_bonus.h`

---

## Prototype

```c
char *get_next_line(int fd);
```

---

## Behavior

- Returns **one line per call** from `fd`.
- The returned line **includes** the newline character (`\n`) **if** it was read before EOF.
- Returns **NULL** when:
  - EOF is reached and no data remains
  - an error occurs (e.g., `read()` fails)
  - allocation fails
  - invalid arguments (`fd < 0`, `BUFFER_SIZE <= 0`, and for bonus: `fd >= OPEN_MAX`)

> Note: The returned string is dynamically allocated. **You must `free()` it.**

---

## Files

### Mandatory
- `get_next_line.c`  
  Core logic: reading into a growing buffer (“remainder”), extracting the current line, and updating the remainder.
- `get_next_line_utils.c`  
  Utility functions: `ft_strlen`, `ft_strchr`, `ft_strjoin`, `ft_strcpy`.
- `get_next_line.h`  
  Prototypes and `BUFFER_SIZE` definition (default is `10` if not provided at compile time).

### Bonus
- `get_next_line_bonus.c`  
  Same logic, but uses `static char *remainder[OPEN_MAX];` to support multiple FDs.
- `get_next_line_utils_bonus.c`
- `get_next_line_bonus.h`  
  Default `BUFFER_SIZE` is `42` here, and includes `<limits.h>` for `OPEN_MAX`.

---

## Compile / Use

### Mandatory example

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

### Bonus example

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl_bonus
```

---

## Minimal `main.c` test

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
    int fd = open("test.txt", O_RDONLY);
    char *line;

    if (fd < 0)
        return (1);

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

---

## Notes

- The function keeps leftover data between calls in a **static** variable (or per-fd static array in the bonus), so the state persists across calls.
- Changing `BUFFER_SIZE` can affect performance but not correctness.

---

## License

Add a license if you plan to distribute this beyond personal/educational use.