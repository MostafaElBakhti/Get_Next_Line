# 📖 Get Next Line - Complete Code Explanation

## 🎯 Project Overview

**get_next_line** is a function that reads a line from a file descriptor, one line at a time. Each call returns the next line including the newline character `\n` (if present).

### Key Concept

The function uses a **static variable** to remember what was read but not yet returned between function calls. This allows it to read chunks of data (BUFFER_SIZE bytes) and return one line at a time.

---

## 🏗️ Architecture

The project is split into 3 files:

| File                    | Purpose                                      |
| ----------------------- | -------------------------------------------- |
| `get_next_line.h`       | Header with function prototypes and includes |
| `get_next_line. c`      | Main logic (4 functions)                     |
| `get_next_line_utils.c` | Helper functions (string manipulation)       |

---

## 📋 Function Breakdown

### 1️⃣ `get_next_line(int fd)` - Main Entry Point

```c
char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remainder = ft_read_line(fd, remainder);
	if (!remainder)
		return (NULL);
	line = extract_line(remainder);
	if (!line)
		return (free(remainder), remainder = NULL, NULL);
	remainder = update_remainder(remainder);
	return (line);
}
```

#### 🔍 What it does:

1. **Validates input**: Checks if `fd` is valid and BUFFER_SIZE is positive
2. **Reads data**: Calls `ft_read_line()` to read until a newline or EOF
3. **Extracts line**: Gets the current line from the data read
4. **Updates remainder**: Saves leftover data for the next call
5. **Returns line**: Gives back one complete line

#### 💡 Key Points:

- `static char *remainder` persists between function calls
- Returns `NULL` when file ends or on error
- User must `free()` the returned line

---

### 2️⃣ `ft_read_line(int fd, char *remainder)` - Read Data

```c
char	*ft_read_line(int fd, char *remainder)
{
	char	*buffer;
	int		readed_bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (! buffer)
		return (free(remainder), NULL);
	readed_bytes = 1;
	while (! ft_strchr(remainder, '\n') && readed_bytes > 0)
	{
		readed_bytes = read(fd, buffer, BUFFER_SIZE);
		if (readed_bytes < 0)
			return (free(buffer), free(remainder), NULL);
		buffer[readed_bytes] = '\0';
		remainder = ft_strjoin(remainder, buffer);
		if (!remainder)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (remainder);
}
```

#### 🔍 What it does:

1.  Allocates a temporary buffer of size `BUFFER_SIZE + 1`
2.  Reads data in chunks until:
    - A newline `\n` is found **OR**
    - End of file is reached (read returns 0)
3.  Appends each chunk to `remainder` using `ft_strjoin()`
4.  Returns the accumulated data

#### 💡 Key Points:

- Reads **BUFFER_SIZE** bytes at a time (efficient!)
- Null-terminates buffer after each read
- Stops when `\n` is found (no need to read more)
- Handles read errors by freeing everything

#### 📊 Visual Example (BUFFER_SIZE = 10):

```
File content: "Hello World\nNext line"

Call 1: read() → "Hello Worl"  (no \n, continue)
Call 2: read() → "d\nNext lin" (\n found, stop!)
remainder = "Hello World\nNext lin"
```

---

### 3️⃣ `extract_line(char *remainder)` - Get Current Line

```c
char	*extract_line(char *remainder)
{
	char	*line;
	int		i;
	size_t	len;

	if (!remainder || !*remainder)
		return (NULL);
	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	len = i;
	if (remainder[i] == '\n')
		len++;
	line = malloc(len + 1);
	if (! line)
		return (NULL);
	i = 0;
	while (remainder[i] && remainder[i] != '\n')
	{
		line[i] = remainder[i];
		i++;
	}
	if (remainder[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}
```

#### 🔍 What it does:

1. Finds the first newline (or end of string)
2. Calculates line length (including `\n` if present)
3. Allocates memory for the line
4. Copies characters up to and including `\n`
5. Null-terminates and returns the line

#### 📊 Visual Example:

```
remainder = "Hello World\nNext line"
                        ↑
                     found \n

Result:
line = "Hello World\n"  ← extracted
remainder still = "Hello World\nNext line" (unchanged)
```

#### 💡 Key Points:

- **Includes** the `\n` in the returned line
- Returns `NULL` if remainder is empty
- Does **not** modify the remainder (read-only)

---

### 4️⃣ `update_remainder(char *remainder)` - Save Leftover Data

```c
char	*update_remainder(char *remainder)
{
	char	*new_remainder;
	int		i;
	int		j;

	if (!remainder)
		return (NULL);
	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (! remainder[i])
		return (free(remainder), NULL);
	i++;
	new_remainder = malloc(ft_strlen(remainder + i) + 1);
	if (!new_remainder)
		return (free(remainder), NULL);
	j = 0;
	while (remainder[i])
		new_remainder[j++] = remainder[i++];
	new_remainder[j] = '\0';
	free(remainder);
	if (new_remainder[0] == '\0')
		return (free(new_remainder), NULL);
	return (new_remainder);
}
```

#### 🔍 What it does:

1. Finds the newline character
2. Skips past it (i++)
3. Copies everything **after** the newline to a new string
4. Frees the old remainder
5. Returns the new remainder (or NULL if empty)

#### 📊 Visual Example:

```
Before:
remainder = "Hello World\nNext line"
                        ↑
                     skip this

After:
new_remainder = "Next line"
old remainder is freed
```

#### 💡 Key Points:

- Creates a **new** string (can't modify in place)
- Frees the old remainder (no leaks!)
- Returns `NULL` if no data left after newline
- Handles edge case: remainder with no newline

---

## 🛠️ Helper Functions (get_next_line_utils. c)

### `ft_strchr(const char *s, int c)`

Finds first occurrence of character `c` in string `s`.

```c
char *ft_strchr(const char *s, int c)
```

- Returns pointer to character if found
- Returns `NULL` if not found
- Used to check if `\n` exists in remainder

---

### `ft_strlen(const char *s)`

Returns length of string.

```c
size_t ft_strlen(const char *s)
```

- Counts characters until `\0`
- Returns 0 if `s` is NULL

---

### `ft_strcpy(char *dst, const char *src)`

Copies string from `src` to `dst`.

```c
char *ft_strcpy(char *dst, const char *src)
```

- Includes null terminator
- Returns `dst`

---

### `ft_strjoin(char *s1, char *s2)`

Concatenates two strings, freeing `s1`.

```c
char *ft_strjoin(char *s1, char *s2)
```

#### 🔍 Special behavior:

- **Frees s1** after joining (important!)
- If `s1` is NULL, starts with empty string
- Returns NULL on malloc failure (and frees s1)

#### 📊 Example:

```c
s1 = "Hello";
s2 = " World";
result = ft_strjoin(s1, s2);
// result = "Hello World"
// s1 is FREED automatically!
```

---

## 🧠 Memory Management

### Static Variable Lifecycle

```
Call 1:
  remainder = NULL → read "Hello\n" → extract "Hello\n" → remainder = NULL

Call 2:
  remainder = NULL → read "World" (EOF) → extract "World" → remainder = NULL

Call 3:
  remainder = NULL → read returns 0 → return NULL
```

### Memory Rules

✅ **Always freed:**

- Temporary buffer in `ft_read_line()`
- Old remainder in `ft_strjoin()` and `update_remainder()`
- Remainder when empty or on error

❌ **User must free:**

- The returned line from `get_next_line()`

---

## 🎮 Usage Example

```c
#include "get_next_line.h"
#include <fcntl. h>
#include <stdio. h>

int main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);  // 🚨 MUST FREE!
	}

	close(fd);
	return (0);
}
```

---

## 🧪 Edge Cases Handled

| Case                 | Behavior                     |
| -------------------- | ---------------------------- |
| Empty file           | Returns `NULL` immediately   |
| File with no newline | Returns content without `\n` |
| File with only `\n`  | Returns `"\n"`               |
| Multiple `\n\n`      | Each call returns one `"\n"` |
| Invalid fd           | Returns `NULL`               |
| Read error           | Frees memory, returns `NULL` |
| Malloc failure       | Frees memory, returns `NULL` |
| BUFFER_SIZE = 1      | Works (but slow!)            |
| Very large line      | Works (dynamic allocation)   |

---

## ⚙️ Compilation

```bash
# Basic compilation
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c

# With your main
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl

# Test with different BUFFER_SIZE
gcc -D BUFFER_SIZE=1 ...     # Slow but works
gcc -D BUFFER_SIZE=1000000 ... # Fast but uses more memory
```

---

## 🐛 Common Mistakes to Avoid

❌ **Forgetting to free the returned line**

```c
line = get_next_line(fd);
// Memory leak!  Must free(line);
```

❌ **Not checking for NULL**

```c
line = get_next_line(fd);
printf("%s", line);  // CRASH if line is NULL!
```

❌ **Closing fd before getting all lines**

```c
close(fd);
line = get_next_line(fd);  // Returns NULL (invalid fd)
```

❌ **Using spaces instead of tabs (Norminette)**

- Always use **TABS** for indentation in 42 projects!

---

## 📊 Performance Analysis

### Time Complexity

- **Per call**: O(n) where n = line length
- **Reading**: O(BUFFER_SIZE) per read() call

### Space Complexity

- **Remainder**: O(BUFFER_SIZE + longest_line)
- **Returned line**: O(line_length)

### Optimal BUFFER_SIZE

- **Small files**: 42-128 bytes
- **Large files**: 4096-8192 bytes (typical page size)
- **Trade-off**: Larger = fewer syscalls, more memory

---

## 🎯 Key Takeaways

1. **Static variable** preserves data between calls
2. **Read in chunks** (BUFFER_SIZE) for efficiency
3. **Dynamic memory** handles any line length
4. **Clean up** on errors to avoid leaks
5. **User frees** returned lines
6. **Handles edge cases** gracefully

---

## ✅ Testing Checklist

- [ ] Empty file
- [ ] Single character file
- [ ] File without newline at end
- [ ] File with only newlines
- [ ] Very long lines (> 10,000 chars)
- [ ] Multiple files (multiple fds)
- [ ] Invalid fd (-1, 1000, closed fd)
- [ ] Read error simulation
- [ ] Different BUFFER_SIZE values
- [ ] Memory leaks (valgrind/fsanitize)

---

## 📚 Resources

- [42 Subject PDF](https://cdn.intra.42.fr/pdf/pdf/960/get_next_line. en.pdf)
- [Francinette Tester](https://github.com/xicodomingues/francinette)
- `man 2 read` - Read system call documentation
- `man 3 malloc` - Memory allocation

---

**Made with ❤️ by mel-bakh for 42 School**

_Last Updated: 2025-11-25_
