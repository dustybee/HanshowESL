
#pragma once

// static assertion. evaluate at compile time. It is very useful like,  STATIC_ASSERT(sizeof(a) == 5);

// #define STATIC_ASSERT(expr)   			{ char static_assertion[(expr) ? 1 : -1]; ((void) static_assertion); }	// (void) array;  to remove compiler unused variable warning

// more complicated version canbe used anywhere in the source
#define STATIC_ASSERT_M(COND,MSG) typedef char static_assertion_##MSG[(!!(COND))*2-1] 
// token pasting madness: 
#define STATIC_ASSERT3(X,L) 	STATIC_ASSERT_M(X,static_assertion_at_line_##L) 
#define STATIC_ASSERT2(X,L) 	STATIC_ASSERT3(X,L) 

#define STATIC_ASSERT(X)    	STATIC_ASSERT2(X,__LINE__) 

#define STATIC_ASSERT_POW2(expr)		STATIC_ASSERT(!((expr) & ((expr)-1)))					//  assert  expr  is  2**N
#define STATIC_ASSERT_EVEN(expr)		STATIC_ASSERT(!((expr) & 1))
#define STATIC_ASSERT_ODD(expr)			STATIC_ASSERT(((expr) & 1))
#define STATIC_ASSERT_INT_DIV(a, b) 	STATIC_ASSERT((a) / (b) * (b) == (a))

