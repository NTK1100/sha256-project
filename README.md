# sha256-project

Thư viện SHA-256 viết bằng C, đã build sẵn **thư viện động** cho C và Python (ctypes).

---

## 1. Build thư viện

### Trên Linux/macOS

```bash
cd sha256-project
mkdir -p lib
gcc -shared -fPIC src/sha256.c -Iinclude -o lib/sha256.so
```

### Trên Windows

```bash
cd /c/Users/Admin/Downloads/sha256-project
mkdir -p lib
gcc -shared src/sha256.c -Iinclude -o lib/sha256.dll
```

Sau khi build xong, bạn sẽ có file `lib/sha256.so` (Linux/macOS) hoặc `lib/sha256.dll` (Windows).

---

### 2. Dùng trong C

#### Ví dụ: tạo file `test/test.c`:

```c
#include <stdio.h>
#include <string.h>
#include "sha256.h"  // sẽ tìm ở ../include

int main() {
    const char *msgs[] = {"", "abc", "hello world"};
    for (int i = 0; i < 3; i++) {
        BYTE out[SHA256_DIGEST_SIZE];
        sha256((BYTE*)msgs[i], strlen(msgs[i]), out);
        printf("SHA256('%s') = ", msgs[i]);
        for (int j = 0; j < SHA256_DIGEST_SIZE; j++)
            printf("%02x", out[j]);
        printf("\n");
    }
    return 0;
}
```
> **Lưu ý**: Phải để thư viện động (`sha256.so` hoặc `sha256.dll`) trong thư mục `test/` hoặc thêm đường dẫn vào biến môi trường (`LD_LIBRARY_PATH`/`PATH`).

#### Biên dịch & chạy:

* **Linux/macOS**:

  ```bash
  cd test
  cp ../lib/sha256.so .
  gcc test.c -I../include -L. -l:sha256.so -o test_c
  LD_LIBRARY_PATH=. ./test_c
  ```

* **Windows**:

  ```bash
  cd test
  copy ..\lib\sha256.dll .
  gcc test.c -I..\include -L. -l:sha256.dll -o test_c.exe
  test_c.exe
  ```

---

### 3. Dùng trong Python (ctypes)

#### Ví dụ: tạo file `test/test.py`:

```python
import ctypes
from ctypes import c_size_t, c_uint8, POINTER

# Load thư viện
# Linux/macOS: lib = ctypes.CDLL("../lib/sha256.so")
# Windows:    lib = ctypes.CDLL(r"..\lib\sha256.dll")
lib = ctypes.CDLL("../lib/sha256.so")

# Khai báo hàm
lib.sha256.argtypes = [POINTER(c_uint8), c_size_t, POINTER(c_uint8)]
lib.sha256.restype  = None

def sha256_c(data: bytes) -> bytes:
    out = (c_uint8 * 32)()
    buf = (c_uint8 * len(data))(*data)
    lib.sha256(buf, len(data), out)
    return bytes(out)

# Test
if __name__ == '__main__':
    msg = b"hello python"
    print("Python hashlib:", __import__('hashlib').sha256(msg).hexdigest())
    print("C ctypes  :", sha256_c(msg).hex())
```

#### Chạy test:

```bash
cd test
python3 test.py
```

---

