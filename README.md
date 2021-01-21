# c-nsbatux-hex-octal-file-viewer

'nsbatux' utility tool shows file content in hexadecimal or octal formats. It has some basic abilities from hexdump and od POSIX utility tools.


POSIX 'hexdump' program's output

```console
$ hexdump -C -n 100 nsbatux.c
00000000  23 69 6e 63 6c 75 64 65  20 3c 73 74 64 69 6f 2e  |#include <stdio.|
00000010  68 3e 0a 23 69 6e 63 6c  75 64 65 20 3c 73 74 64  |h>.#include <std|
00000020  6c 69 62 2e 68 3e 0a 23  69 6e 63 6c 75 64 65 20  |lib.h>.#include |
00000030  3c 63 74 79 70 65 2e 68  3e 0a 23 69 6e 63 6c 75  |<ctype.h>.#inclu|
00000040  64 65 20 3c 67 65 74 6f  70 74 2e 68 3e 0a 0a 23  |de <getopt.h>..#|
00000050  64 65 66 69 6e 65 20 56  45 52 53 49 4f 4e 5f 44  |define VERSION_D|
00000060  45 53 43 20                                       |ESC |
00000064
```

POSIX 'od' program's output

```console
$ od -A x -t x1 -N 100 nsbatux.c
0000000    23  69  6e  63  6c  75  64  65  20  3c  73  74  64  69  6f  2e
0000010    68  3e  0a  23  69  6e  63  6c  75  64  65  20  3c  73  74  64
0000020    6c  69  62  2e  68  3e  0a  23  69  6e  63  6c  75  64  65  20
0000030    3c  63  74  79  70  65  2e  68  3e  0a  23  69  6e  63  6c  75
0000040    64  65  20  3c  67  65  74  6f  70  74  2e  68  3e  0a  0a  23
0000050    64  65  66  69  6e  65  20  56  45  52  53  49  4f  4e  5f  44
0000060    45  53  43  20                                                
0000064
```

Our 'nsbatux' file content viewer which shows hexadecimal format output

```console
$ ./nsbatux -A x -t x -n 100 -p nsbatux.c
====> nsbatux.c <====
0000000    23 69 6E 63 6C 75 64 65 20 3C 73 74 64 69 6F 2E   |#include <stdio.|
0000010    68 3E 0A 23 69 6E 63 6C 75 64 65 20 3C 73 74 64   |h>.#include <std|
0000020    6C 69 62 2E 68 3E 0A 23 69 6E 63 6C 75 64 65 20   |lib.h>.#include |
0000030    3C 63 74 79 70 65 2E 68 3E 0A 23 69 6E 63 6C 75   |<ctype.h>.#inclu|
0000040    64 65 20 3C 67 65 74 6F 70 74 2E 68 3E 0A 0A 23   |de <getopt.h>..#|
0000050    64 65 66 69 6E 65 20 56 45 52 53 49 4F 4E 5F 44   |define VERSION_D|
0000060    45 53 43 20 
```


Our 'nsbatux' file content viewer without -p option which shows hexadecimal format output

```console
$ ./nsbatux -A x -t x -n 100 nsbatux.c
====> nsbatux.c <====
0000000    23 69 6E 63 6C 75 64 65 20 3C 73 74 64 69 6F 2E
0000010    68 3E 0A 23 69 6E 63 6C 75 64 65 20 3C 73 74 64
0000020    6C 69 62 2E 68 3E 0A 23 69 6E 63 6C 75 64 65 20
0000030    3C 63 74 79 70 65 2E 68 3E 0A 23 69 6E 63 6C 75
0000040    64 65 20 3C 67 65 74 6F 70 74 2E 68 3E 0A 0A 23
0000050    64 65 66 69 6E 65 20 56 45 52 53 49 4F 4E 5F 44
0000060    45 53 43 20 
```


Our 'nsbatux' file content viewer which shows octal format output

```console
$ ./nsbatux -A o -t o -n 100 -p nsbatux.c
====> nsbatux.c <====
0000000    043 151 156 143 154 165 144 145 040 074 163 164 144 151 157 056   |#include <stdio.|
0000020    150 076 012 043 151 156 143 154 165 144 145 040 074 163 164 144   |h>.#include <std|
0000040    154 151 142 056 150 076 012 043 151 156 143 154 165 144 145 040   |lib.h>.#include |
0000060    074 143 164 171 160 145 056 150 076 012 043 151 156 143 154 165   |<ctype.h>.#inclu|
0000100    144 145 040 074 147 145 164 157 160 164 056 150 076 012 012 043   |de <getopt.h>..#|
0000120    144 145 146 151 156 145 040 126 105 122 123 111 117 116 137 104   |define VERSION_D|
0000140    105 123 103 040 
```

Our 'nsbatux' file content viewer without -p option which shows octal format output

```console
$ ./nsbatux -A o -t o -n 100 nsbatux.c
====> nsbatux.c <====
0000000    043 151 156 143 154 165 144 145 040 074 163 164 144 151 157 056
0000020    150 076 012 043 151 156 143 154 165 144 145 040 074 163 164 144
0000040    154 151 142 056 150 076 012 043 151 156 143 154 165 144 145 040
0000060    074 143 164 171 160 145 056 150 076 012 043 151 156 143 154 165
0000100    144 145 040 074 147 145 164 157 160 164 056 150 076 012 012 043
0000120    144 145 146 151 156 145 040 126 105 122 123 111 117 116 137 104
0000140    105 123 103 040 
```


Show all file content (use utility tool without -n option)

```console
$ ./nsbatux -A x -t x nsbatux.c
====> nsbatux.c <====
0000000    23 69 6E 63 6C 75 64 65 20 3C 73 74 64 69 6F 2E
0000010    68 3E 0A 23 69 6E 63 6C 75 64 65 20 3C 73 74 64
0000020    6C 69 62 2E 68 3E 0A 23 69 6E 63 6C 75 64 65 20
0000030    3C 63 74 79 70 65 2E 68 3E 0A 23 69 6E 63 6C 75
0000040    64 65 20 3C 67 65 74 6F 70 74 2E 68 3E 0A 0A 23
0000050    64 65 66 69 6E 65 20 56 45 52 53 49 4F 4E 5F 44
0000060    45 53 43 20 20 20 20 20 20 20 20 20 20 20 20 22
0000070    40 43 6F 70 79 72 69 67 68 74 20 32 30 32 31 20
0000080    2D 20 56 65 72 73 69 6F 6E 20 31 2E 30 20 2D 20
0000090    4D 49 54 20 4C 69 63 65 6E 73 65 20 43 75 73 74
00000A0    6F 6D 20 6E 73 62 61 74 75 78 20 73 6F 66 74 77
00000B0    61 72 65 20 6D 6F 64 75 6C 65 2E 20 44 65 76 65
00000C0    6C 6F 70 65 64 20 62 79 20 42 61 74 75 68 61 6E
...
...
...
0002370    72 2C 20 22 69 6E 76 61 6C 69 64 20 6C 6F 6E 67
0002380    20 6F 70 74 69 6F 6E 21 5C 6E 22 29 3B 0A 20 20
0002390    20 20 20 20 20 20 20 20 20 20 20 20 20 20 7D 0A
00023A0    20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20
00023B0    2A 65 72 72 6F 72 5F 66 6C 61 67 20 3D 20 31 3B
00023C0    0A 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20
00023D0    20 62 72 65 61 6B 3B 0A 20 20 20 20 20 20 20 20
00023E0    7D 0A 20 20 20 20 7D 0A 7D 
```
