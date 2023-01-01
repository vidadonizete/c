# Some C code

## Interesting knowledge
### Importing directives

```
target_include_directories(
    "${module_name}"
    PRIVATE include
)
```

will be equal to:

```
gcc main.c -Isomefolder/include -o main
```

It allows you to import as **#include <mylib.h>** instead of **#include mylib.h**.
