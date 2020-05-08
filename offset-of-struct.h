#ifndef OFFSET_OF_STRUCT
#define OFFSET_OF_STRUCT

#define OFFSETOF(a, b) ( (size_t) &((a)NULL)->b )

#endif 