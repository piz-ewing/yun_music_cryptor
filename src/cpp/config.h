#pragma once
#define _TEST_MODULE 1


#ifdef _DEBUG
#define DEBUG_EXPR(x) do{x}while(0)
#else
#define DEBUG_EXPR(x)
#endif