#ifndef _STD_TYPE_H_ 
#define _STD_TYPE_H_

/* unsigned data */

typedef  unsigned char            u8 ; 
typedef  unsigned short int       u16 ; 
typedef  unsigned long int        u32; 
typedef  unsigned long long int   u64 ; 


/* signed data */

typedef  signed char            s8 ; 
typedef  signed short int       s16 ; 
typedef  signed long int        s32; 
typedef  signed long long int   s64 ; 

/*float data */

typedef float   f32 ; 
typedef double  f64 ; 

/*bool data type */

typedef enum{F,T}Bool ; 

/*null  */

#define NULL    ((void*)0)


#endif 