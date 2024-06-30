# Items 1 Template Type Deduction
>[!INFO] Definition
>Template type deduction is a fundamental concept in C++ that determines the types of
>template parameters based on arguments passed to a template function. 
>```cpp
> template <typename T\>
>void f(ParamType param);
>
>f(expr);
>```
>The type deducted for **T is dependent not just on the type of *expr*, but also on the form of *ParamType***, there are 3 cases:
>1. Pointer or reference type(not universal ref)
>2. Universal references.
>3. Neither a pointer nor a reference

## Case 1: *ParamType* is reference or pointer 

>[!Success] Rules
> 1. If expr’s type is a reference, ignore the reference part.
> 2. Then pattern-match expr’s type against ParamType to determine T.
* Examples:
```cpp
// T&
template <typename T>
void f(T& x);

int a;
int& b;
int&& c;
const int d;
const int& e;

int* p1;
const int* p2;
int* const p3;
const int* const p4;

char s1[] = "downdemo";
const char s2[] = "downdemo";

f(a);  // ParamType 是 int&，T 是 int
f(b);  // ParamType 是 int&，T 是 int
f(c);  // ParamType 是int&，T是int
f(d);  // ParamType 是 const int&，T 是 const int
f(e);  // ParamType 是 const int&，T 是 const int
// 因为 top-level const 和 low-level const 都保留
// 对于指针只要记住 const 的情况和实参类型一样
f(p1);  // ParamType 是 int* &，T 是 int*
f(p2);  // ParamType 是 const int* &，T 是const int*
f(p3);  // ParamType 是 int* const&，T 是 int* const
f(p4);  // ParamType 是 const int* const &，T 是 const int* const
// 数组类型对于 T& 的情况比较特殊，不会退化到指针
f(s1);  // ParamType 是 char(&)[9]，T 是 char[9]
f(s2);  // ParamType 是 const char(&)[9]，T 是 const char[9]

// const T&:
// 如果把 ParamType 从 T& 改为 const T&，区别只是 ParamType 一定为 top-level const，ParamType 去掉 top-level const 和引用符就是 T 的类型，即 T 一定不为 top-level const 引用类型

template <typename T>
void f(const T& x);

int a;
int& b;
int&& c;
const int d;
const int& e;

int* p1;
const int* p2;
int* const p3;
const int* const p4;

char s1[] = "downdemo";
const char s2[] = "downdemo";

// 以下情况 ParamType 都是 const int&，T 都是 int
f(a);
f(b);
f(c);
f(d);
f(e);
// 数组类型类似
f(s1);  // ParamType 是 const char(&)[9]，T 是 char[9]
f(s2);  // ParamType 是 const char(&)[9]，T 是 char[9]
// 对于指针只要记住，T的指针符后一定无const
f(p1);  // ParamType 是 int* const &，T 是 int*
f(p2);  // ParamType 是 const int* const &，T 是 const int*
f(p3);  // ParamType 是 int* const&，T 是 int*
f(p4);  // ParamType 是 const int* const &，T 是 const int*

// T*
template<typename T>
void f(T* param);

const int * px = &x;
// [pointer in T is removed since ParamType]
f(&x); // T is int, Param is int*
f(px); // T is const int, Param is const int*

```

## Case 2: Universal Reference
>[!Success] Rules:
>1. If *expr* is an lvalue, both `T` and `ParanType` are deducted to lvalue reference. 
>	1. It's the only situation where `T` is deducted to be a reference
>	2. although `ParamType` is declared using syntax for an rvalue reference, its deducted type is an lvalue reference.
>2. If *expr* is an rvalue, the "normal"(Case 1) rules apply.

```cpp
// T&&
template<typename T>
void f(T&& param);

int x = 27; // x is lvalue, 27 is rvalue
const int cx = x;
const int& rx = x;

f(x);  // x is lvalue, so T is int&, param is int&
f(cx); // cx is lvalue, so T is const int &, param is const int &
f(rx); // rx is lvalue, so T is consy int &, param is const int &
f(27); // 27 is rvalue, so T is int, param is int&&
```

## Case 3: Pass-by-value
>[!Success] Rules
>The param is a copy of whatever passed in -- a completely new object
>1. ignore reference
>2. ignore const, volatile. If it's const T * const ptr, only ignore the right const decorating ptr itself.
```cpp
template <typename T>
void f(T x);

int a;
const int b;
const int& c;

int* p1;
const int* p2;
int* const p3;
const int* const p4;

char s1[] = "downdemo";
const char s2[] = "downdemo";

// 以下情况 T 和 ParamType 都是 int
f(a);
f(b);
f(c);
// 指针类型丢弃的是 top-level const（即指针本身的 const）
// low-level const（即所指对象的 const）会保留
f(p1);  // T 和 ParamType 都是 int*
f(p2);  // T 和 ParamType 都是 const int*
f(p3);  // T 和 ParamType 都是 int*
f(p4);  // T 和 ParamType 都是 const int*
// char 数组会退化为指针
f(s1);  // T 和 ParamType 都是 char*
f(s2);  // T 和 ParamType 都是 const char*
```

## Niche Case
>[!IMPORTANT]
>1. Array Arguments:
   Assuming `const char s[] = "hello world"`;
>	1. If `void f(T x)` **Array decays to Pointer**, T=ParamType = const char \*
>	2. If `void f(T& x)` **T is const char\[11\], ParamType is const char(&)\[11\]** 
>1. Function Arguments:
   Assuming `void g(int)`
>	1. if `f(T x)`:  T=ParamType=void(\*)(int)
>	2. if `f(T& x)`:  P=void(&)(int), T=void()(int)
>	3. if `f(T&& x)`:  T=P=void(&)(int)

## 01 Template Type Deduction Summary
>[!caution] Summary
> `T` depends on both `expr` and `paramType`
>1.  `T` Pass-by-value `ParamType - & Const = T`
>	1. ignore top-level const(the const for pointer itself, right side of \*)
>	2. ignore reference
>	3. copy pass-in obj
>	4. Array arguments decay to pointer
>	5. Function Argument **decay to function pointers**: T=ParamType=void(\*)(int)
>2. `T&` ParamType is reference `ParamType - & = T`
>	1. if `const T&` : `ParamType - const & = T`;
>	2. Array arguments do not decay: **ParamType = const char(&)\[11\], T = const char\[11\]**
>	3. Function arguments do not decay; they remain as function references: T = ParamType = void(&)(int)
>3. `T*` ParamType is pointer `ParamType - * = T`
>	1. Rules are the same for `T*` and `T&`, and `const T*` and `const T&`
>	2. **Low-level const gets to keep, top-level const is removed**:
>		1. `T* const`: `ParamType - *const = T`
>		2. `const T* const` : `ParamType -*const = T` 
>	3. Array decays to Pointers
>4. `T&&` Universal Reference
>	1. lvalue: `T = ParamType = &`
>	2. rvalue: `ParamType - && = T`


# 02 auto type deduction



