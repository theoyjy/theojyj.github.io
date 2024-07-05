### 高优先级（核心考点）

1. [ ] 理解模板类型推导、auto类型推导和decltype（Effective Modern C++ 1-4）[Knowledge](#01%20Template%20Type%20Deduction) [Questions](#1%20Template%20Type%20Deduction%20|%20`auto`%20|%20`decltype`%20Questions)
2. [ ] 理解std::move和std::forward，理解右值引用，移动语义，完美转发（Effective Modern C++ 23-30）[Link](#2%20`move`%20and%20`forward`)
3. [ ] 对于占有性资源使用std::unique_ptr（Effective Modern C++ 18）
4. [ ] 对于共享性资源使用std::shared_ptr（Effective Modern C++ 19）
5. 优先考虑使用std::make_unique和std::make_shared而非new（Effective Modern C++ 21）
6. 对于右值引用使用std::move，对于通用引用使用std::forward（Effective Modern C++ 25）
7. 确保const成员函数线程安全（Effective Modern C++ 16）
8. 使用override声明重载函数（Effective Modern C++ 12）
9. 理解异常处理（More Effective C++ 9-15）

### 中等优先级（重要但不一定常考）

11. 避免使用默认捕获模式（Effective Modern C++ 31）
12. 使用初始化捕获来移动对象到闭包中（Effective Modern C++ 32）
13. 对于std::forward的auto&&形参使用decltype（Effective Modern C++ 33）
14. 有限考虑lambda表达式而非std::bind（Effective Modern C++ 34）
15. 优先考虑基于任务的编程而非基于线程的编程（Effective Modern C++ 35）
16. 对于并发使用std::atomic（Effective Modern C++ 40）
17. 避免返回handles指向对象内部成分（Effective C++ 28）
18. 成对使用new和delete时要采取相同形式（Effective C++ 16）
19. 以对象管理资源（Effective C++ 13）
20. 考虑写出一个不抛异常的swap函数（Effective C++ 25）


# 01 Template Type Deduction

>[!INFO] Definition 
>Template type deduction is a fundamental concept in C++ that ==**allows compiler to determine the types of template parameters based on arguments passed to a template function.**== 
>
>```cpp
> template <typename T\>
>void f(ParamType param);
>
>f(expr);
>```
>The type deducted for **T is dependent not just on the type of *expr*, but also on the form of *ParamType***, there are 3 cases:
>1. Pass-by-value: strips cvr.
>2. Pointer or reference type(not universal ref): Preserves cvr,
>3. Universal references: Preserves cvr, lvalue -> T = P = expr +&, rvalue -> T = ParamType - &&

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
*Start: 2024-07-01 14:25 End: 2024-07-01 16:09* 
## Almost Same as Template Type Deduction
- 调用模板时，编译器根据 expr 推断 T 和 ParamType 的类型。当变量用 auto 声明时，auto 就扮演了模板中的T的角色，变量的类型修饰符则扮演 ParamType 的角色
- 为了推断变量类型，编译器表现得好比每个声明对应一个模板，模板的调用就相当于对应的初始化表达式

```c
auto x = 1;
const auto cx = x;
const auto& rx = x;

template <typename T>  // 用来推断 x 类型的概念上假想的模板
void func_for_x(T x);

func_for_x(1);  // 假想的调用: param 的推断类型就是 x 的类型

template <typename T>  // 用来推断 cx 类型的概念上假想的模板
void func_for_cx(const T x);

func_for_cx(x);  // 假想的调用: param 的推断类型就是 cx 的类型

template <typename T>  // 用来推断 rx 类型的概念上假想的模板
void func_for_rx(const T& x);

func_for_rx(x);  // 假想的调用: param 的推断类型就是 rx 的类型
```

- auto 的推断适用模板推断机制的三种情形：T&、T&& 和 T

```c
auto x = 1;          // int x
const auto cx = x;   // const int cx
const auto& rx = x;  // const int& rx
auto&& uref1 = x;    // int& uref1
auto&& uref2 = cx;   // const int& uref2
auto&& uref3 = 1;    // int&& uref3
```

- auto 对数组和指针的推断也和模板一致

```cpp
const char name[] = "downdemo";  // 数组类型是 const char[9]
auto arr1 = name;                // const char* arr1
auto& arr2 = name;               // const char (&arr2)[9]

void g(int, double);  // 函数类型是 void(int, double)
auto f1 = g;          // void (*f1)(int, double)
auto& f2 = g;         // void (&f2)(int, double)
```

## Special Case: Braced initializer {}

* auto initialization is different from origin type:

```cpp
auto x1 = 1;    // int x1
auto x2(1);     // int x2
auto x3 = {1};  // std::initializer_list<int> x3
auto x4{1};     // ⭐只有一个值时：C++11 为 std::initializer_list<int> x4，C++14 为 int x4

// 错误：初始化列表中元素类型不同, 不能为 std::initializer_list<T> 推断 T
auto x = {1, 2, 3.0}; 
```

* `auto` assume {} represents a `std::initializer_list{}`, while `template type` deduction doesn't accept {}

```cpp

template <typename T>  // 等价于 x 声明的模板
void f(T x);
f({1, 2, 3});  // 错误： 模板不支持模板参数为 T 而 expr 为初始化列表的推断，不会将其假设为 std::initializer_list，这就是 auto 推断和模板推断唯一的不同之处

template <typename T>
void f(std::initializer_list<T> initList);
f({1, 2, 3});  // T 被推断为 int，initList 类型是 std::initializer_list<int>
```

## `auto` New Features in C++14  

1. `auto` can be return type of a function

```cpp
auto f() { return 1; }

// when no return, it would deduct `void`, but if can't match -> error
auto f1() {}           // OK：返回类型是 void
auto f2() { return; }  // OK：返回类型是 void
auto* f3() {}          // 错误：auto*不能推断为 void
```

2. can declare `lambda`, this type of lambda is called ‘Generic Lambda’. Remember: The type deduction it use is 'template type deduction',  so it doesn't support braced initializer as parameter or return value.

```cpp
auto g = [](auto x) { return x; };

auto f() {return {1}; }// error
g({1, 2, 3}); // error
```

## `auto` New Features in C++17

1. C++17 中，auto 可以作为非类型模板参数, enhance the flexibility and add type deduction:

- **Non-Type Template Parameters**: that represent **constant values** rather than types(must be compile-time constant): integers, enumerations, pointers, references, user-defined types that satisfy certain conditions:

```cpp
template<int N>
void print()
{
	std::cout << N << std::endl;
}

int main()
{
	print<10>(); // works
	print<3.14>(); // error, it's not an int
	return 0;
}
```

* With `auto`, the type of non-type template parameter can be any type that is a compile-constant:
```cpp
template<auto N>
void print()
{
	std::cout << N << std::endl;
}

int main()
{
	print<10>();   // works
	print<3.14>(); // works
	print<"Hi">(); // works
}
```

* More complex example:
```cpp
namespace jc {

template <auto N, typename T = decltype(N)>
constexpr T add(T n) {
  return n + N;
}

template <typename T, T N = T{}>
constexpr T add(T n) {
  return n + N;
}

}

static_assert(jc::add<2>(3) == 5);
static_assert(jc::add<int>(3) == 3);
```

2. Template Argument Deduction for Class Templates
Allows the compiler to deduce the template parameters **when you create an instance** of a class template
```cpp
// before C++17
std::pair<int, double> myPair<42, 3.14>;

// with C++17
auto myPair = std::pair(42, 3.14);
```

3. C++17 引入了[结构化绑定（structured binding）](https://en.cppreference.com/w/cpp/language/structured_binding)
Allow you to **unpack** tuples, pairs, arrays, and other similar structures **into individual variables**
```cpp
#include <cassert>
#include <string>
#include <tuple>

namespace jc {

struct A {
  int n = 42;
  std::string s = "hello";
};

A f() { return {}; }

}  // namespace jc

int main() {
  const auto&& [n, s] = jc::f();
  assert(n == 42);
  assert(s == "hello");

  int a[] = {1, 2, 3};
  auto& [x, y, z] = a;
  assert(&x == a);
  assert(&y == a + 1);
  assert(&z == a + 2);

  auto t = std::make_tuple(true, 'c');
  auto& [b, c] = t;  // auto& b = std::get<0>(t); auto& c = std::get<1>(t);
  assert(&b == &std::get<0>(t));
  assert(&c == &std::get<1>(t));
}
```

4. 特化 [std::tuple_size](https://en.cppreference.com/w/cpp/utility/tuple/tuple_size)、[std::tuple_element](https://en.cppreference.com/w/cpp/utility/tuple/tuple_element)、[std::get(std::tuple)](https://en.cppreference.com/w/cpp/utility/tuple/get) 即可生成一个 tuple-like 类

```cpp
#include <cassert>
#include <string>
#include <tuple>

namespace jc {

struct A {};

}  // namespace jc

namespace std {

template <>
struct std::tuple_size<jc::A> {
  static constexpr int value = 2;
};

template <>
struct std::tuple_element<0, jc::A> {
  using type = int;
};

template <>
struct std::tuple_element<1, jc::A> {
  using type = std::string;
};

template <int>
auto get(jc::A);

template <>
auto get<0>(jc::A) {
  return 42;
}

template <>
auto get<1>(jc::A) {
  return "hello";
}

}  // namespace std

int main() {
  auto&& [x, y] = jc::A{};
  static_assert(std::is_same_v<decltype(x), int>);
  static_assert(std::is_same_v<decltype(y), std::string>);
  assert(x == 42);
  assert(y == "hello");
}
```

5. `auto` in `if` and `switch` Statements
C++17 allows the use of `auto` in `if` and `switch` statement initializers, enabling more concise and expressive code.
```cpp
std::vector<int> v = {1, 2, 3, 4, 5}; 
if (auto it = v.find(3); it != v.end()) {
	// do something 
}
```



# 03 decltype
*start 2024-07-01 16:10 End: 2024-07-01 18:02*

>[!Abstract]
>* deducting type for expression
>* `decltype` typically parrots back the exact type of the name or expression you give it
>* Mainly used for **declare the return type that is related to parameter type**:
>	* `decltype(auto)` for correctness of return type since `auto` ignore ref and const
>	* `&&` + `std::forward` to accept rvalue and correctly handle
>* Special deductions: decltype(\*p) -> & | decltype((variable)) -> & | decltype(lhs = rhs) -> lhs&

```cpp
const int i = 0;  // decltype(i) 为 const int

struct Point {
  int x, y;  // decltype(Point::x) 和 decltype(Point::y) 为 int
};

A a;                 // decltype(a) 为 A
bool f(const A& x);  // decltype(x) 为 const A&，decltype(f) 为 bool(const A&)
if (f(a)) {          // decltype(f(a)) 为 bool
}

int a[]{1, 2, 3};  // decltype(a) 为 int[3]
```

>[!Caution] override `T` and `T&` cann't exist at the same time
>```cpp
>// error C2668: 对重载函数的调用不明确		
>void process(int x) {...}
>void process(int& x) {...}
>```

1. Mainly used for **declare the return type that is related to parameter type**. For instance,  parameter is contain and index, the return type depends on element type:

```cpp
template<typename Container, typename Index>
auto f(Container& c, Index i) -> decltype(c[i])
{
	return c[i]; // auto only indicates for the type deduction of decltype
}
```

*  C++14 allow to omit **trailing return type**, only leaves `auto`

```cpp
template<typename Container, typename Index>
auto f(Container& c, Index i) {
	return c[i];
}

// error: even though operator[] returns reference, but auto deducts `int`, so the return value is a rvalue
std::vector<int> v{1, 2, 3};
f(v, 1) = 42; // can'y assign to a rvalue
```

* To obtain correct return type, use `decltype(auto)`

```cpp
template<typename Container, typename Index>
decltype(auto) f(Container& c, Index i) {
	return c[i];
}

std::vector<int> v{1, 2, 3};
f(v, 1) = 42; // correct
```

* `decltype(auto)` can also be used for declaration of variables

```cpp
int i = 1;
const int & j = i;
auto x = j; // int

decltype(auto) y = j; // const int&
decltype(j) y = j; // const int&
```

* There are still issues, Contain is non-const reference of lvalue, it can not accept rvalue, so we are using `&&`+ `std::forward<T>()`

```cpp
// only using && in ParamType
void process(int& x)
{
    cout << "lvalue reference " << x << endl;
}

void process(int&& x)
{
    cout << "rvalue reference " << x << endl;
}

template<typename T>
void forwarder(T&& x)
{
    process(T);
}

int x = 10;
forward(x); // correct: lvalue reference
forward(20);// wrong: lvalue reference

//error even though we use universal reference &&, which will make rvalue -> rvalue&&. The param c has name 'c', so it is a lvalue inside of f. 
// So it would call process(int& x) rather than process(int&& x)

// combine && with forward
template<typename T>
void forwarder(T&& x)
{
    process(forward<T>());
}

template <typename Container, typename Index>
decltype(auto) f(Container&& c, Index i) {
  return std::forward<Container>(c)[i];  // 传入的实参是右值时，将 c 转为右值
}

```

2. **Special deduction**
```cpp
// 1. 解引用 -> 引用类型
int* p; // decltype(*p) 解引用 is int*

// 2. 赋值表达式 -> 左值的引用
int a = 0;
int b = 1;
decltypr(a = 1) c = b;// int&

// 3. 如果表达式加上一层或多层括号，编译器会将其看作表达式，变量是一种可以作为赋值语句左值的特殊表达式，因此也得到引用类型。
// decltype((variable)) 结果永远是引用，declytpe(variable) 只有当变量本身是引用时才是引用
int i; // decltype((i)) is int&
```

>[!Caution] `decltype(auto)` may result reference to local variable
>```cpp
>decltype(auto) f()
>{
>	int x = 0;
>	return x; // decltype(x) is int
>	return (x); // error: decltype((x)) is int*
>}
>```

# 04 Know how to view deduced types
*start 2024-07-01 19:50 end 2024-07-01 21:00*
* Hover on variables in IDE
* Using warnings:
```cpp
// 比如写一个声明但不定义的类模板，用这个模板创建实例时将出错，编译将提示错误原因
template <typename T>
class A;

A<decltype(x)> xType;  // 未定义类模板，错误信息将提示 x 类型
// 比如对 int x 报错如下
// error C2079 : “xType”使用未定义的 class“A<int>”
```

* `typeid(T).name()` and `std::type_info::name` , but it will ignore cv `const` and `&`
```cpp
template<typename T>
void f(T& x)
{
	using namespace std;
	cout << "T = " << typeid(T).name() << endl;
	cout << "x = " << typeid(decltype(x)).name() << endl;
}
```

* `boost::typeindex::type_id_with_cvr<T>().pretty_name()` fetch precise type
```cpp
#include <boost/type_index.hpp>
template<typename T>
void f(const T& x)
{
	using boost::typeindex::type_id_with_cvr;
	cout << "T = " << type_id_with_cvr<T>().pretty_name() << endl;
	cout << "x = " << type_id_with_cvr<decltype(x)>().pretty_name() << endl;
}
```

>[!Caution] ## `const T&` is the king
>### 1. **Accepting Any Type of Argument**:
>
>Using `const T&` allows the function to accept:
>
>- **Lvalues**: Regular variables (e.g., `int x`).
>- **Const Lvalues**: Constants (e.g., `const int y`).
>- **Rvalues**: Temporaries and literals (e.g., `42`).
>
> Meanwhile:
> 1. `T&` does not accept `const` and Rvalues
> 2. `T&&` requires `forward` to correctly handle, which increases complexity and potential for misuse, even though enhance flexibility and preserves exact types.
>
>### 2. **Avoiding Copies**:
>
>Passing by `const T&` avoids making unnecessary copies of the argument, which can be important for performance, especially for large objects.
>
>### 3. **Preserving `const`-ness**:
>
>It ensures that the function does not modify the passed argument, maintaining the `const`->correctness.
>
>### 4. **Supporting Rvalues**:
>
>By using `const T&`, the function can also accept rvalues, which would not be possible with `T&` >alone, since non-const lvalue references cannot bind to rvalues.

# 1 Template Type Deduction | `auto` | `decltype` Questions

## Template Type Deduction

- **How does template type deduction work in C++?**
    
    - Template type deduction allows the ==**compiler** to determine the **types**== of template parameters ==**based on the provided arguments**==. For example, in `template <typename T> void func(T t);`, calling `func(42);` deduces `T` as `int`.

- **What is the difference between template type deduction for pass-by-value, pass-by-reference, and pass-by-universal-reference (forwarding reference)?**
    
    - **Pass-by-value:** ==Strips== `const` and `volatile` qualifiers. E.g., `template <typename T> void func(T t);` with `const int` deduces `T` as `int`.
    - **Pass-by-reference:** ==Preserves== `const` and `volatile` qualifiers. E.g., `template <typename T> void func(T& t);` with `const int&` deduces `T` as `const int`.
    - **Universal reference:** Deduces `T&` if passed an lvalue, otherwise deduces `T`. E.g., `template <typename T> void func(T&& t);` with `int` deduces `T` as `int` and with `int&` deduces `T` as `int&`.

- **What are the special rules for template type deduction with arrays and function pointers?**
    
    - Arrays and function pointers **decay to pointers** unless the template parameter is a reference. E.g., `template <typename T> void func(T t);` with `int arr[10]` deduces `T` as `int*`. Use `T&` to preserve the array type.

- **How can you prevent type deduction and explicitly specify template arguments?**
    
    - Use angle brackets syntax to explicitly specify template arguments. E.g., `func<int>(42);` specifies `T` as `int`.

## `auto` Type Deduction

- **How does `auto` type deduction work in C++?**
    
    - ==**`auto` deduces the type from the initializer==.** E.g., `auto x = 42;` deduces `x` as `int`.

- **What are the differences in type deduction between `auto` and template type deduction?**
    
    - `auto` deduces type based on initializer expression; templates deduce from function arguments. E.g., `auto x = 42;` deduces `x` as `int`, similar to `template <typename T> void func(T t); func(42);`.

- **How does `auto` handle references and `const` qualifiers?**
    
    - `auto` ==**strips `const` and reference**== qualifiers from the initializer. E.g., `const int x = 42; auto y = x;` deduces `y` as `int`.

- **What are the implications of using `auto` with initializer lists?**
    
    - `auto` deduces `std::initializer_list<T>` with brace-enclosed initializers. E.g., `auto x = {1, 2, 3};` deduces `x` as `std::initializer_list<int>`.

## `decltype`

- **What is `decltype` and how is it used?**
    
    - **==`decltype` deduces the type of an expression without evaluating it==**. E.g., `int x = 42; decltype(x) y = x;` deduces `y` as `int`.

- **How does `decltype` differ from `auto` in terms of type deduction?**
    
    - **==`decltype` preserves `const` and reference qualifiers, `auto` may strip them==**. E.g., `const int x = 42; decltype(x) y = x;` deduces `y` as `const int`.
- **What is the difference between `decltype(expr)` and `decltype((expr))`?**
    
    - `decltype(expr)` without parentheses deduces type without reference qualifiers, `decltype((expr))` with parentheses gives enforcing lvalue reference. E.g., `int x = 42; decltype(x) a = x;` deduces `a` as `int`, but `decltype((x)) b = x;` deduces `b` as `int&`.
- **How can `decltype` be useful in template metaprogramming and generic programming?**
    
    - `decltype` is useful for defining return types in template functions. E.g., `template <typename T, typename U> auto add(T t, U u) -> decltype(t + u) { return t + u; }`.

# 2 `move` and `forward`

## Interview questions

### Questions on `std::move`

1. **What is `std::move` and how does it work?**
    
    - `std::move` is a standard library **utility** that **==casts an object to an rvalue reference==**, **==enabling move semantics==**. It does not actually move the object but **==allows the compiler to treat it as a temporary (rvalue)==** so that its **==resources can be transferred instead of copied==**.
    	```cpp
    	#include<utility>
    	std::string str = "hello";
    	std::string newStr = std::move(str);
    	```
	Here, `std::move(str)` casts `str` to an rvalue reference, **==allowing the move constructor==** of `std::string` **==to transfer its contents to `newStr`==** 

2. **When should you use `std::move`?**
    
    - Use `std::move` when you **==need to transfer ownership of resources==** from one object to another, particularly when dealing with **==expensive-to-copy resources like dynamic memory, file handle==**s, etc. It is commonly used in move constructors and move assignment operators.
	```cpp
	class MyClass{
	public:
		MyClass(std::vector<int> && vec) : data(std::move(vec)) {}
	private:
		std::vector<int> data;
	}
	```
    
3. **What are the potential pitfalls of using `std::move`?**
    
    - **==After `std::move`, the original object is in a valid but unspecified state. It should not be used except for assignment or destruction.==** Misuse of `std::move` can lead to **undefined behavior if the moved-from object is accessed without being reassigned**.
    ```cpp
	std::string str = "hello";
	std::string newStr = std::move(str);
	// using str is risky, it's in a valid but unspecified state
	```
    

### Questions on `std::forward`

1. **What is `std::forward` and how does it work?**
    
    - **==`std::forward` is a utility that preserves the value category (lvalue or rvalue) of its argument==**. It is primarily used in template code to implement **==perfect forwarding, allowing function templates to forward arguments while retaining their original value category==**.
    ```cpp
    #include <utility>
    template <typename T>
    void wrapper(T&& x)
    {
	    fuc(std::forward<T>(arg));
    }
	```
    
2. **When should you use `std::forward`?**
    
    - Use `std::forward` when you are **==implementing forwarding functions==** that **take a forwarding reference (universal reference)** and **==need to pass the argument to another function, preserving its value category==**.
    
3. **What is the difference between `std::move` and `std::forward`?**
    
    - ==`std::move` **unconditionally** casts its argument to an rvalue reference==, while ==`std::forward` **conditionally casts its argument to an rvalue reference** based on the template parameter type==. **==`std::move` is used for enabling move semantics, and `std::forward` is used for perfect forwarding==**.
    ```cpp
    template<typename T>
    void process(T&& t)
    {
	    anotherFunction1(std::move(t)); // forces t to be an rvalue
	    anotherFunction2(std::forward<T>(t)); // preserves t's value category
    }
	```
    

### Practical Example Questions

1. **Write a simple function template that uses `std::move` to implement a move constructor.**
    
    ```cpp
    class myClass
    {
    public:
		myClass(std::vector<int>&& vec) : data(std::move(vec)) {}
	private:
		std::vector<int> data;
    }
	```

2. **Write a function template that demonstrates the use of `std::forward` to implement perfect forwarding.**
    
	```cpp
	template<typename T>
	void wrapper(T&& t)
	{
		anotherFunc(std::forward<T>(t));
	}
	```
    
3. **Explain the behavior of the following code snippet:**
    
    ```cpp
	template <typename T>
	void f(T&& t) {
	    g(std::forward<T>(t));
	}
	
	int main() {
	    int x = 10;
	    f(x); // lvalue is forwarded as lvalue
	    f(20); // rvalue is forwarded as rvalue
	}

	```
    
    - `f(x);` forwards `x` as an lvalue to `g`, so `g` receives `int&`.
    - `f(20);` forwards `20` as an rvalue to `g`, so `g` receives `int&&`.

## 23 `std::move` and `std::forward`
* They **==both preserves cv==**
* `move` unconditionally casts values to rvalue ref, it is for movement semantics. `forward` conditionally casts(only cast rvalue to rvalue&&, not deal with lvalue)that keep the value category, and it is for perfect forwarding
* `&&` is the basis for both move semantics and perfect forwarding.
* They both do nothing, `move` just tell compiler the ownership can be moved, while `forward` just preserve the value categories.
* Any value passed into a function, inside that function, it will have a name, no matter it was a lvalue or rvalue, **the param is naturally a lvalue**. To enable move semantics, we need to use `move`.
### `move`
* `std::move` 实现
	```cpp
	// remove_reference_t 去掉左值引用
	template<typename T>
	constexpr std::remove_reference_t<T>&& move(T&& x) noexcepty {
	    return static_cast<std::remove_reference_t<T>&&>(x);
	}
	constexpr int f(const std::string&) { return 1; }
	constexpr int f(std::string&&) { return 2; }
	
	}  // namespace jc
	
	int main() {
	  std::string s;
	  static_assert(jc::f(s) == 1);
	  assert(jc::f(std::string{}) == 2);
	  static_assert(jc::f(static_cast<std::string&&>(s)) == 2);
	  static_assert(jc::f(jc::move(s)) == 2);
	  static_assert(jc::f(std::move(s)) == 2);
	}
	```
* 4 Mainly Purpose:
>[!Success] `move` usages:
>1. **Move Constructors and Move Assignment Operator**: enable moving resources from one to another rather than copying
>```cpp
>MyClass a;
>MyClass b = std::move(a); // move constructor
>a = std::move(b); // move assignment operator
>```
>
>2. **Passing to functions**: avoid copying
>```cpp
>void process(MyType c);
>
>MyClass a;
>process(std::move(a));
>```
>
>3. **Returning Objects from Functions**: to return a local object from a function, enable move semantics
>```cpp
>MyType createMyClass()
>{
>	MyClass a;
>	return std::move(a); // 
>
>}
>```
>
>4. **Perfect Forwarding in Generic Programming**
>```cpp
>template\<typename T\>
>void wrapper(T&& arg)
>{
>	anotherFunc(std::move(arg));
>}
>```

* **`move` preserve `cv` may cause copy operations**:
	move operations (move constructor and move assignment operator) typically **==require non-const objects because they modify the source object by transferring its resources to the destination object.==** If the source object is **const, it cannot be modified**, which means its resources cannot be transferred. As a result, **the compiler will fall back to using the copy** constructor or copy assignment operator, which do not modify the source object and can work with const objects.
```cpp
class MyClass {  
public:  
    // Move constructor  
    MyClass(MyClass&& other) noexcept {  
        std::cout << "Move constructor called\n";  
    }  
  
    // Copy constructor  
    MyClass(const MyClass& other) {  
        std::cout << "Copy constructor called\n";  
    }  
};  
  
int main() {  
    const MyClass obj; // obj is const  
    MyClass obj2 = std::move(obj); // Attempts to move, but will copy instead  
    return 0;  
}
```

### `forward`

- C++11 之前的转发很简单

```cpp
#include <iostream>

void f(int&) { std::cout << 1; }
void f(const int&) { std::cout << 2; }

// 用多个重载转发给对应版本比较繁琐
void g(int& x) { f(x); }

void g(const int& x) { f(x); }

// 同样的功能可以用一个模板替代
template <typename T>
void h(T& x) {
  f(x);
}

int main() {
  int a = 1;
  const int b = 1;

  g(a);
  h(a);  // 11
  g(b);
  h(b);  // 22
  g(1);  // 2
  // h(1);  // 错误 C++11无法转发右值
}
```

- C++11 引入了右值引用，但原有的模板无法转发右值。如果使用 [std::move](https://en.cppreference.com/w/cpp/utility/move) 则无法转发左值，因此为了方便引入了 [std::forward](https://en.cppreference.com/w/cpp/utility/forward)

```c
#include <iostream>
#include <utility>

void f(int&) { std::cout << 1; }
void f(const int&) { std::cout << 2; }
void f(int&&) { std::cout << 3; }

// 用多个重载转发给对应版本比较繁琐
void g(int& x) { f(x); }
void g(const int& x) { f(x); }
void g(int&& x) { f(std::move(x)); }

// 用一个模板来替代上述功能
template <typename T>
void h(T&& x) {
  f(std::forward<T>(x));
}

int main() {
  int a = 1;
  const int b = 1;

  g(a);
  h(a);  // 11
  g(b);
  h(b);  // 22
  g(std::move(a));
  h(std::move(a));  // 33
  g(1);
  h(1);  // 33
}
```

## 24 Distinguish universal references from rvalue references.

1. Universal Reference **==must be the format `T&&`==**, `std::vector<T>&&` is rvalue red
2. Universal Reference must **==doesn't have `const`==**, it makes the param unmodifiable, can't be move. 
3. Universal Reference must involves **==type deduction==**
4. **==`template <class... Args> void emplace_back(Args&&... args);` is universal reference==**
5. **==any `auto&&` is a universal ref==**, but remember pass it rvalue
6. **==`lambda` can have perfect forwarding==**: Lambdas in C++ can actually be templated, starting from C++14. This feature allows you to use generic lambdas with template type deduction. The `auto` keyword in the lambda parameter list makes the lambda a generic lambda
```cpp
// 1. exact format
template<typename T>
void f(std::vector<T>&&){} // not T&&, so rvalue reference(or univeral reference)

std::vector<int> v;
f(v); // error, f only accept rvalue

// 2. no const
template<typename T>
void g(const T&&) {} // const is not movable, so no forwarding, only rvalue ref

int i = 1;
g(i); // error

// 3. Must have type deduction

// 3.1 no type deduction when calling with specific type
template<typename T>
void f(T&&){}

f<int>(5); // type is specified, so no univeral red

// 3.2 when calling push_back, there must have been an instance, the T is already decided, so no type deduction during push_back
template<class T, class Allocator = allocator<T>>
class vector
{
public:
	void push_back(T&&); // T is already deduced when instantiation, so rvalue ref

	// 4. class.. Args
	template <class... Args> // Args is independent of vector’s type parameter T, 
					// so Args must be deduced each time emplace_back is called.
	void emplace_back(Args&&... args);  // universal ref, because it doesn't 
}

std::vector<A> v;  // 实例化指定了 T

// 对应的实例化为
class vector<A, allocator<A>> {
 public:
  void push_back(A&& x);  // 不涉及类型推断，右值引用

  template <class... Args>
  void emplace_back(Args&&... args);  // 转发引用
};


// 5. auto&&
int a = 1;
auto&& x = a; // int&
auto&& y = std::move(a); // int&&
auto&& z = 7; // int&&


// 6. lambda can have perfect forward
auto f = [](auto&& x) 
{ 
	// T is replaced by auto, so use decltype(x) get deduced type
	return g(std::forward<decltype(x)>(x));
};

auto f = [](auto&&..args)
{
	return g(std::forward<decltype(args)>(args));
}

```

## 25 Use `std::move` on rvalue ref, `std::forward` on universal ref

- 右值引用只会绑定到可移动对象上，因此应该使用 [std::move](https://en.cppreference.com/w/cpp/utility/move)。转发引用用右值初始化时才是右值引用，因此应当使用 [std::forward](https://en.cppreference.com/w/cpp/utility/forward)
-  To Maintain **Strong Exception Safety** which means If the operation **must either complete successfully or have no observable effect**, could use [std::move_if_noexcept](https://en.cppreference.com/w/cpp/utility/move_if_noexcept) instead of [std::move](https://en.cppreference.com/w/cpp/utility/move)```

```cpp
#include <type_traits>
struct A{
	A() = defualt;
	A(const A&) { std::cout << 1; }
	A(A&&) { std::cout << 2; }
}

struct B
{
	B()
	B(const B&) noexcept { std::cout << 3; }
	B(B&&) {std::cout << 4;}
}

int main()
{
	A a;
	A a2= std::move_if_noexcept(a); // 1

	B b;
	B b2 = std::move_if_noexcept(b); // 4
}
```

- **==Returning passed-in rvalue ref or universal reference object==**: use `std::move` or `std::forward` to **==cast it accordingly==**. No need to declare the return type as a reference; **==return by value is sufficient==**.

```cpp
A f(A&& a) {
  do_something(a);
  return std::move(a);
}

template <typename T>
A g(T&& x) {
  do_something(x);
  return std::forward<T>(x);
}
```

- **==Return Local Variables==**: **no need to use `move` for optimization**. C++ standard provides **==Return Value Optimization(RVO) which avoids unnecessary copies==**

```cpp
#include <string>
std::string createString() 
{ 
	std::string local = "Hello, World!"; 
	return local; // RVO kicks in, no need for std::move 
}
```
*RVO (Return Value Optimization) ensures that local objects are created directly in the memory allocated for the return value, avoiding copy operations. Using `std::move` here would prevent RVO from being applied.*

```cpp
A make_a() { return A{}; }

auto x = make_a(); // only call default constructor once
```

## 26 Avoid overloading on universal references

>[!warning] If function param accepts lvalue ref, passing a rvalue still performs a copy
>
>```cpp
>void f(const std::string& s) { // do something }
>
>// pass in rvalue -> still triggers copy constructor
>f("hi");
>f(std::string("hi));
>```
>
>>[!Success] Universal Ref accepts all types and avoid unnecessary copies
>>```cpp
>>template\<typename T\>
>>void f(T&& a) { // ... }
>>
>>f("hi"); // move
>>f(std::string("hi")); // move
>>```
>>

>[!warning] Overloading on universal references leads to ambiguities, 3 scenarios:
>1. Overloading a universal reference and an lvalue reference.
>2. Overloading a universal reference and a rvalue reference.
>3. Ambiguities between template and non-template functions.
>```cpp
>std::vector\<std::string\> vec;
>
>// 3. Ambiguities between template and non-template functions:
>template \<typename T\>
>void f(T&& s){
>	v.emplace_back(s);
>}
>std::string make_string(int n) { return std::string("hi"); }
>void f(int n) {
>	v.emplace_back(make_string(n));
>}
>// 之前的调用仍然正常 , T&&
>f(std::string("hi"));
>f("hi");
>
>// overloading works as well
>f(1);
>
>// Universal Ref is more precise than int
>int i = 1;
>f(i); // error, call T&&, s is int&& and it calls v.emplace_back(s); v is vector\<string\>
>     // construct string from s -> error
> 
> 
> ```

>[!Warning] Template Constructor Issues
>1. Template constructor match more broadly than copy constructor, leading to incorrect behavior
>2. Template constructor automatically generating default constructor
>3. More complex when inheritance exist, base class with template constructor 
>```cpp
> // 1. Match broadly, incorrect behavior
> class A{
> public:
> 	A() = default;
> 	template\<typename T\>
> 	explicit A(T&& x) : s_(std\:\:forward\<T\>(x)) {}
> 	explicit A(int x) : s_(make_string(x)) {}
> private:
> 	std::string s_;
> }
> int i = 1;
> A a{i}; //error: match with T&&, construct s_ with int&
> A b{"hi"}; // OK
> A c{b}; // error: match with T&&, construct s_ with A&
> 
>class A{
>public:
>	template \<typename T\>
>	void A(T&& x) : s\_(std::forward\<T\>(x)) {}
>	
>// 2. prevent compiler automatically generating copy and move constructors
>// we have to do it by our own 
>	A(const A& rhs) = default;
>	A(A&& rhs) = default;
>private:
>	std::string s_;
>}
>
> // 1. Match broadly, incorrect behavior
> int main()
> {
> 	A a{"hi"}; // match T&&
> 	A b{a}; // error, T&& is more general so match T&& rather than copy constructor, but T&& 
> 			// can construct s_ with A
> 	const A c{"hi"};
> 	A d(c); // OK, match copy constructor
> }
> 
>  // 3. inheritance
>class A {
> public:
>  template \<typename T\>
>  explicit A(T&& n) : s(std::forward\<T\>(n)) {}
>
> private:
>  std::string s;
>};
>
>class B : public A {
> public:
>  /*
>   * 错误：调用基类模板而非拷贝构造函数
>   * const B 不能转为 std::string
>   */
>  B(const B& rhs) : A(rhs) {}
>
>  /*
>   * 错误：调用基类模板而非移动构造函数
>   * B 不能转为 std::string
>   */
>  B(B&& rhs) noexcept : A(std::move(rhs)) {}
>};
>```

## 27 Alternatives to overloading on universal references

1. The most direct method is not using overloading at all. The second direct method is not using universal references, like C++98. The third is pass-by-value

```cpp
#include <string>

// no overloading or no unversal references
class A {
 public:
  template <typename T>
  explicit A(const T& x) : s_(x) {}

 private:
  std::string s_;
};

int main() {
  A a{"hi"};
  A b{a};  // OK
}

// pass-by-value
std::string make_string(int n) { return std::string{"hi"}; }

class A {
 public:
  explicit A(std::string s) : s_(std::move(s)) {}
  explicit A(int n) : s_(make_string(n)) {}

 private:
  std::string s_;
};

int main() {
  int i = 1;
  A a{i};  // OK，调用 int 版本的构造函数
}

```

###  ==Tag Dispatching==

Tag dispatch involves creating tag types and using them to differentiate between function overloads, improving clarity and avoiding ambiguities.

**==The existence of a single (unoverloaded) function as the client API. This single function dispatches the work to be done to the implementation functions.==**

1. universal reference is **not overloaded, but get a tag value** to dispatch params to implementations
2. the **implementation functions are overloaded**, o**ne takes a universal reference parameter, and a tag parameter** so no more than one overload will be **a viable match**.
3. As a result, it’s the **tag that determines which overload gets called**

```cpp

vector<string> vec;

string make_string(int n)
{
	return string("hi");
}

// universal template, emplace element to vec
template <typename T> 
void processImpl(T&& x, std::false_type)
{
	v.emplace_back(std::forward<T>(s));
}

// to have an overload taking an int that's used to look up objects by index, then insert it to vec

string element_from_idx(int idx)
{
	if(idx < vec.size())
		return vec[idex];
	return "";
}

void processImpl(int n, std::true_type)
{
	process(element_from_idx(n));
}

template <typename T>
void process(T && arg)
{
	// int&& is not intergral, so we have to remove reference
	processImpl(forward<T> s, std::is_intergral<remove_reference_t<T>>());
}

```
*Notice that we don’t even name those parameters. They serve no purpose at runtime, and in fact we hope that compilers will recognize that the tag parameters are unused and will optimize them out of the program’s execution image. (Some compilers do, at least some of the time.)*


### Constraining templates that take universal references `std::enable_if`

>[!Warning] Tag Dispatch issues on Constructor
>Compilers may generate copy and move constructors themselves, so even if you write only one constructor and use tag dispatch within it, some **constructor calls may be handled by compiler-generated functions that bypass the tag dispatch system**.
>
>Providing a constructor taking a universal reference causes the **universal reference constructor** (rather than the copy constructor) **to be called when copying non-const lvalues**. That Item also explains that **when a base class declares a perfect-forwarding constructor, that constructor will typically be called when derived classes implement their copy and move constructors in the conventional fashion, even though the correct behavior is for the base class’s copy and move constructors to be invoked.**

>[!Abstract] `std::enable_if`
> Gives you a way to ==**force compilers**== to behave as if a particular template didn’t exist. Such **==templates are said to be disabled.==**
>
>In our case, we’d like to **enable** the Person perfect-forwarding constructor **==only if the type being passed isn’t Person.==** If the type being passed is Person, we want to disable the perfect-forwarding constructor, because that will cause the class’s copy or move constructor to handle the call, which is what we want when a Person object is initialized with another Person. 
>
>when we’re looking at T, **we want to ignore**:
>1. **Whether it’s a reference**. For the purpose of determining whether the universal reference constructor should be enabled, the types Person, Person&, and Per son&& are all the same as Person. 
>2. **Whether it’s const or volatile**. As far as we’re concerned, a const Person and a volatile Person and a const volatile Person are all the same as a Person.
>
>=> `std::decay<T>::type`:
>This means we need a way to **==strip any references, consts, and volatiles from T before checking to see if that type is the same as Person==**.
>=> The condition: `!std::is_same<Person, typename std::decay<T>::type>::value`
```cpp
class Person{
public:
	template<typename T,
		typename  = typename std::enable_if<
					!std::is_same<Person, 
								typename std::decay<T>::type>
								>::value			
					>::type
	>
	explicit Person(T&& n);
}

// issue：
class SpecialPerson : Person
{
	SpecialPerson(const Person& rhs) : Person(rhs) {}
	
	//the universal reference constructor in the base class is enabled, and it happily instantiates to perform an exact match for a SpecialPerson argument
	SpecialPerson(Person&& rhs) :: Person(std::move(rhs)) {} 
}

// final version C++11
class Person { 
public: 
	template< typename T, 
			  typename = typename std::enable_if< 
						  !std::is_base_of<Person, 
										  typename std::decay<T>::type 
						                   >::value
                         >::type 
           > 
	explicit Person(T&& n);

// C++14
class Person
{
public:
	template<
		typename T,
		typename = std::enable_if_t<
					!std::is_base_of<Person,
									 std::decay_t<T>
									>::value
					>		
	>
	explicit Person(&& n);

}
```

#### Final Version
(1) add a Person constructor overload to handle integral arguments and 
(2) further constrain the templatized constructor so that it’s disabled for such arguments.
```cpp
class Person
{
public:
	template<
		typename T,
		typename = std::enable_if_t<
					!std::is_base_of<Person, std::decay_t<T>>::value
					&&
					!std::is_intergral<std::remove_reference_t<T>::value>
		>
	>
	explicit Person(&& n);

	explicit Person(int idx) : name(nameFromIdx)
	{
	}
}
```

## Item 28: Understand reference collapsing.

>[!INFO] Reference Collapsing rules
>& + & → &
>& + && → &
>&& + & → &
>&& + && → &&
>
>**Reference Collapsing** is the basis for `forward`
>**==Works in 4 scenarios==**: 
>1. [Template Instantiation](###Template%20Instantiation%20After%20Template%20Type%20Deduction)
>2. `auto` type deduction
>3. `decltype` type deduction
>4. `typedef` or `using` declaring alternative names

```cpp
int& & b = a;  // 错误
```

* **==`std::forward` 实现==**
	*`static_cast` 是强制让对象编程目标类型，而不是在原有类型上加东西*
	* **==`static_cast<A&&>(A&)` -> would not cause ref collapsing, but force A be A&&==**
```cpp
template<typename T>
T&& forward(std::remove_reference_t<T>& x)
{
	return static_cast<T&&>(x);
}

// pass lvalue ref A&
T is A&
std::remove_reference_T<A&> is A, x is A&
type of return is A& && -> collapse to A&
static_cast<A& &&>(A&) -> static_cast<A&>(A&) -> A&
would return A&

// Template Instantiation to:
A& forward(A& x)
{
	return static_cast<A&>(x);
}

// pass rvalue ref A&&
T is A&&
std::remove_reference_t<A&&> is A, so x is A&
return type is A&& && -> collapse to A&&
static_cast<A&& &&>(A&) -> static_cast<A&&> (A&) -> A&&
would return A&&

// template instantiation to:
A&& forward(A& x)
{
	return static_cast<A&&>(x);
}
```

- auto&& 与使用转发引用的模板原理一样

```c
int a = 1;
auto&& b = a;  // a 是左值，auto 被推断为 int&，int& && 折叠为 int&
```

- decltype 同理，如果推断中出现了引用的引用，就会发生引用折叠
- 如果在 typedef 的创建或求值中出现了引用的引用，就会发生引用折叠

```c
template <typename T>
struct A {
  using RvalueRef = T&&;  // typedef T&& RvalueRef
};

int a = 1;
A<int&>::RvalueRef b = a;  // int& && 折叠为 int&，int& b = a
```

* Can't apply `const` `volatie` to reference, will be ignored
```c
using A = const int&;
using B = int&&;
static_assert(std::is_same_v<volatile A&&, const int&>);
static_assert(std::is_same_v<const B&&, int&&>);
```

### Template Instantiation After Template Type Deduction

* **Template Type Deduction**: is compiler deduce type of parameters based on arguments provided to a template function or class. **==This occurs==** when you call a template function or create an instance of a template class **==without explicitly specifying the template arguments==**

```cpp
template <typename T> void 
func(T x) 
{
	// Implementation 
} 

int main() {
	int a = 42; 
	func(a); // T is deduced to be int return 0; 
}
```

* **Template Instantiation**: the process of generating a concrete function or class from a template by substituting the deduced or explicitly specified types for the template parameters. This **==happens after the template type deduction (or when explicit types are provided), and the compiler generates the actual code for the specific types==**.

```cpp
template <typename T> 
class MyClass { 
public: 
	T value; 
	MyClass(T v) : value(v) {} 
}; 

int main() { 
	MyClass<int> obj(42); // no deduction, since the type has been specified,
						// directly Instantiation of MyClass<int> return 0; 
}
```

* **Combination**:

```cpp
#include <iostream>
#include <utility>

// Template function with type deduction
template <typename T>
void printTypeAndValue(T&& t) {
    std::cout << "Value: " << t << std::endl;
}

int main() {
    int a = 42;
    
    // T deduced as int&, instantiation of printTypeAndValue<int&>
    printTypeAndValue(a);
	
	// T deduced as int, instantiation of printTypeAndValue<int>
    printTypeAndValue(42);
    
    // T deduced as int&&, instantiation of printTypeAndValue<int&&>
    printTypeAndValue(std::move(a)); 
    return 0;
}

```


## Item 29: Assume that move operations are not present, not cheap, and not used.

>[!Abstract] Several Scenarios in which C++11' s move semantics do you no good:
>1. **No Move Operations**: The obj requires to be moved from fails to offer move operations. The move request therefore becomes a copy request.
>2. **Move not fast**: for example, `std::array` [Explanation](###No%20truly%20cheap%20way%20to%20move%20their%20contents)
>3. **Move not usable**: The context in which the moving would take place **requires** a move operation that **emits no exceptions, but that operation isn't declared `noexcept`**
>4. **Source object is lvalue**: 


### No truly cheap way to move their contents

#### `std::array`

* ==The **other standard containers**, each of which stores its **contents on the heap**==. Objects of such container types hold (as data members), conceptually, **only a pointer** to the heap memory storing the contents of the container
  The existence of this pointer makes it possible to **==move the contents of an entire container in constant time==**: **just copy the pointer** to the container’s contents from the source container to the target, and s**et the source’s pointer to null**:
	![[C++ Crucial Knowledge-20240704204435316.webp]]

* `std::array` objects lack such a pointer, because the **data** for a std::array’s contents **are stored directly in the std::array object**:
  ==Even if move `Widget` is faster than copying, both moving and copying a `std::array` have linear-time computational complexity==, because each element in the container must be copied or moved.. This is far from the “moving a container is now as cheap as assigning a couple of pointers” claim that one sometimes hears
	![[C++ Crucial Knowledge-20240704204635291.webp]]

#### Short String Optimization

>[!INFO] Special example
>The motivation for the ***SSO(short string optimization)*** is extensive evidence that short strings(usually less than 15 bytes) are the norm for many applications. Using **an internal buffer to store the contents** of such strings **eliminates the need to dynamically allocate memory** for them, and that’s typically an efficiency win. An implication of the win, however, is that moves are no faster than copies.

## Item 30:Familiarize yourself with perfect forwarding failure cases.

>[!Abstract] Perfect Forwarding Fails:
>**==If calling overload f with a particular argument does one thing, but calling template forwarding function`fwd` with the same function does something else==**
>```cpp
>template < typename... Ts >
>void fwd(Ts&&... params) // variadic template
>{
>	f(std::forward< Ts >(params)...);
>}
>
>f(expr); // if this does one thing,
>fwd(expr); // but this does another thing, fwd fails to perfectly forward expr to f
>```
>**==Scenarios that Perfect forwarding Fails occurs:==**
>1. **Compiler are unable to deduce a type**: such as template type deduction does accept braced initializer.
>2. **Compiler deduce the "wrong" type**

### Braced Initializer:

```cpp
void f(const std::vector< int > & v ) ;
f({1, 2, 3}); // works. "{1, 2, 3}" implicitly converted to std::vector< int>

fwd({1, 2, 3}); // error, doesn't compile
```

### 0 or NULL as null pointer

```cpp
void f(int*) {}

template <typename T>
void fwd(T&& x) {
  f(std::forward<T>(x));
}

fwd(NULL);  // T 推断为 int，转发失败
```

### Declaration-only integral static const data members 

  类内的 static 成员的声明不是定义，**==如果 static 成员声明为 const，则编译器会为这些成员值执行 const propagation，从而不需要为它们保留内存==**。==对整型 static const 成员取址可以通过编译，但会导致链接期的错误。**转发引用也是引用**==，在编译器生成的机器代码中，引用一般会被当成指针处理。程序的二进制代码中，从硬件角度看，指针和引用的本质相同
  
```cpp
class A {
 public:
  static const int n = 1;  // 仅声明
};

void f(int) {}

template <typename T>
void fwd(T&& x) {
  f(std::forward<T>(x));
}

f(A::n);    // OK：等价于 f(1)
fwd(A::n);  // 错误：fwd 形参是转发引用，需要取址，无法链接
```

- 但并非所有编译器的实现都有此要求，上述代码可能可以链接。考虑到移植性，最好还是提供定义

```cpp
// A.h
class A {
 public:
  static const int n = 1;
};

// A.cpp
const int A::n;
```

### Overloaded function names and template names

- 如果转发的是函数指针，可以直接将函数名作为参数，函数名会转换为函数指针

```c
void g(int) {}

void f(void (*pf)(int)) {}

template <typename T>
void fwd(T&& x) {
  f(std::forward<T>(x));
}

f(g);    // OK
fwd(g);  // OK
```

- 但如果要转发的函数名对应多个重载函数，则无法转发，因为模板无法从单独的函数名推断出函数类型

```c
void g(int) {}
void g(int, int) {}

void f(void (*)(int)) {}

template <typename T>
void fwd(T&& x) {
  f(std::forward<T>(x));
}

f(g);    // OK
fwd(g);  // 错误：不知道转发的是哪一个函数指针
```

- 转发函数模板名称也会出现同样的问题，因为函数模板可以看成一批重载函数

```c
template <typename T>
void g(T x) {
  std::cout << x;
}

void f(void (*pf)(int)) { pf(1); }

template <typename T>
void fwd(T&& x) {
  f(std::forward<T>(x));
}

f(g);         // OK
fwd(g<int>);  // 错误
```

- 要**让转发函数接受重载函数名称或模板名称，只能手动指定需要转发的重载版本或模板实例**。不过完美转发本来就是为了接受任何实参类型，而要传入的函数指针类型一般是未知的

```c
template <typename T>
void g(T x) {
  std::cout << x;
}

void f(void (*pf)(int)) { pf(1); }

template <typename T>
void fwd(T&& x) {
  f(std::forward<T>(x));
}

using PF = void (*)(int);
PF p = g;
fwd(p);                   // OK
fwd(static_cast<PF>(g));  // OK
```

### Bitfields

>[!Abstract] Definition of Bitfield
>```cpp
>struct Flags {
>    unsigned int a : 1;  // will occupy exactly 1 bit.
>    unsigned int b : 3;  // will occupy 3 bits.
>    unsigned int c : 4;  // will occupy 4 bits.
};
>```
>**Purpose of Bitfields**:
>
>Bitfields are used to **pack data into a smaller amount of memory**. Instead of each member occupying the default size of its type (e.g., 4 bytes for an `unsigned int` on most systems), the members only take up the specified number of bits.
>
>Bitfields are **useful when memory efficiency is crucial**, such as in embedded systems or when dealing with hardware registers.
>
>**Why Can't You Access the Address of a Bitfield?**
>
>There are several reasons why you cannot take the address of a bitfield:
>
>1. **Non-Addressable Storage**:
>    
>    - A bitfield does **not necessarily occupy a whole addressable storage unit (like a byte). It may span across bytes or other bits, making it non-addressable in the typical sense.**
>2. **Implementation-Dependent Layout**:
>    
>    - **The layout and alignment of bitfields are implementation-dependent**. Different compilers may place bitfields differently within the containing storage unit, complicating address computation.
>3. **Access Mechanics**:
>    
>    - **Access** to bitfields usually involves bit manipulation operations, **which do not map cleanly to memory addresses. Taking the address of a bitfield would require exposing these operations, which is not supported by the language**.

- **==转发引用也是引用，实际上需要取址，但位域不允许直接取址==**

```c


void f(int) {}

template <typename T>
void fwd(T&& x) {
  f(std::forward<T>(x));
}

Flags x{1, 5, 12};
f(x.a);    // OK
fwd(x.a);  // 错误
```

- **==实际上接受位域实参的函数也只能收到位域值的拷贝，因此不需要使用完美转发==**，换用传值或传 const 引用即可。完美转发中也可以通过强制转换解决此问题，虽然转换的结果是一个临时对象的拷贝而非原有对象，但位域本来就无法做到真正的完美转发

```c
fwd(static_cast<int>(x.a));  // OK
```


# 3 Smart Pointers

## Pitfalls Drawbacks of raw pointers:

>[!Danger]
>1. Can't tell if a pointer points to a single object or an array
>2. Not defined whether should release the resource when you're done using it, i.e. if the pointer owns the thing it points to
>3. Can't be sure should we use `delete` or other destruction functions
>4. Even we figure it out that need to apply `delete`, should be extra careful to decide `delete` or `delect[]`, misuse would lead to undefined behaviors
>5. Difficult to ensure you perform the destruction exactly once along every path in the code. Missing a path leads to resources leaks, while doing the destruction more than once leads to undefined behaviors 
>6. Can't tell if a pointer dangles, i.e. it points to memory that no longer holds the object the pointer is supposed to point to

## 18 `std::unique_ptr`

* there was `std::auto_ptr` in C++98 which was replaced totally by `std::unique_ptr` in C++11

>[!Abstract]
>1. `std::unique_ptr` is **==small==** as raw pointer, fast, **==move-only==** pointer for managing resources with **==exclusive-ownership semantics==**
>2. By default, resource destruction takes places via `delete`, but **custom deleters can be specified**. **Stateful deleters and function pointers as deleters increases the size of `std::unique_ptr` objects.**
>3. Converting a `std::unique_ptr` to a `std::shared_ptr` is easy

```cpp
class Investment {}
class Stock : public Investment {}
class Bond : public Investment {}
class RealEstate : public Investment{}

// 1. custom deleter function
void delInvmt(Investment* pInvestment)
{
	// do something
	delete pInvestment;
}

// 1. custom deleter lambda, if it captures some variables, unique_str would 
// increase size, if not, no size rised
auto delInvmt = [](Investment* pInvestment)
{
	// do something
	delete pInvestment;
};
	
// unique_ptr 常用作工厂函数的返回类型，这样工厂函数生成的对象在需要销毁时会被自动析构，而不需要手动析构
template<typename..Ts>
std::unique_ptr<Investment, decltype<delInvmt>> makeInvestment(Ts&&..params)
{

	
	// 2. create a null unique_ptr
	std::unique_ptr<Investment, decltype<delInvmt>> pInv(nullptr, delInvmt);

	// 3. then make it points to an appropriate obj
	if(/*a stock should be created*/)
	{
		pInv.reset(new Stock(std::forward<Ts>(params)..));
	}
	else if(/*a Bond should be created*/)
	{
		pInv.reset(new Bond(std::forward<Ts>(params)..));
	}
	else if(/*a RealEstate should be created*/)
	{
		pInv.reset(new RealEstate(std::forward<Ts>(params)..));
	}
	
	return pInv; // return local variable, RVO will optimize it to move
}

// return type could be simpler and more encapsulated fashion
template<typename..Ts>
auto makeInvestment(Ts&&..params)
{
	// can define lambda deleter inside factory function, better encapsulation
	auto delInvmt = [](Investment* pInvestment)
	{
		// do something
		delete pInvestment;
	};
	// same as before
}
```

* size of `unique_ptr`

```cpp
struct A {};

auto f = [](A* p) { delete p; };

void g(A* p) { delete p; }

struct X {
  void operator()(A* p) const { delete p; }
};

std::unique_ptr<A> p1{new A};
std::unique_ptr<A, decltype(f)> p2{new A, f};
std::unique_ptr<A, decltype(g)*> p3{new A, g};
std::unique_ptr<A, decltype(X())> p4{new A, X{}};

static_assert(sizeof(p1) == sizeof(nullptr));  // 默认尺寸，即一个原始指针的尺寸
static_assert(sizeof(p2) == sizeof(nullptr));  // 无捕获 lambda 不会浪费尺寸
static_assert(sizeof(p3) == sizeof(nullptr) * 2);  // 函数指针占一个原始指针尺寸
static_assert(sizeof(p4) == sizeof(nullptr));  // 无状态的函数对象，但如果函数对象有状态（如数据成员、虚函数）就会增加尺寸
```

* return `unique_ptr` is convenient to convert to `shared_ptr`

```cpp
std::shared_ptr<int> p = std::make_unique<int>(42)
```

- [std::unique_ptr](https://en.cppreference.com/w/cpp/memory/unique_ptr) 针对数组提供了一个特化版本，此版本提供 [operator[]](https://en.cppreference.com/w/cpp/memory/unique_ptr/operator_at)，但不提供[单元素版本的 `operator*` 和 `operator->`](https://en.cppreference.com/w/cpp/memory/unique_ptr/operator*)，这样对其指向的对象就不存在二义性

```c
#include <cassert>
#include <memory>

int main() {
  std::unique_ptr<int[]> p{new int[3]{0, 1, 2}};
  
  for (int i = 0; i < 3; ++i) {
    assert(p[i] == i);
  }
}
```

## 19 `std::shared_ptr` for shared-ownership resource management.

* **`shared_ptr` are twice the size of raw pointer**: they internally contain a raw pointer to the resource as well as a raw pointer to the resource's reference count
	* **Memory for the reference count must be dynamically allocated**: pointed-to objects know nothing about this. They thus have no place to store a reference count. **The cost of the dynamic allocation is avoided when the `std::shared_ptr` is created by `std::make_shared`**, but there are situations where **`std::make_shared` can’t be used**. Either way, the reference count is stored as dynamically allocated data.

```cpp
int* p = new int{42};
auto q = std::make_shared<int>(42);
static_assert(sizeof(p) == sizeof(nullptr));
static_assert(sizeof(q) == sizeof(nullptr) * 2);
```

* **Increments and decrements of the reference count must be atomic**: because there can be simultaneous readers and writers in different threads. Atomic operations are typically slower than non-atomic, even though the counts are usually only one word in size, you should assume that reading and writing them is comparatively costly.

* By default, resource destruction takes places via `delete`, can also have **custom deleters**, but **==no need to declare type in template type, this is for flexible usage==**

```cpp
class A {};
auto f = [](A* p) { delete p; };

std::unique_ptr<A, decltype(f)> p{new A, f};
std::shared_ptr<A> q{new A, f};

// more flexible
std::shared_ptr<A> a(new A, f);
std::shared_ptr<A> b(new A, g);
std::shared_ptr<A> c(new A);

// shared_ptrs with different deleters, can be put in the same vector
std::vector<std::shared_ptr<A>> vec{a, b, c};
```

### Control Block
deleters is on the heap or allocated in mem by self-defined allocator's. **==`shared_ptr` contains a control block, which contains the pointer to reference count and custom deleters, and some other data==**(like weak ref count) , so that **==Custom deleters do not affect the size of `shared_ptr`==**
![[C++ Crucial Knowledge-20240705205039265.webp]]
* **==The Scenarios that create a new control blocks==**:
	1. call **==`std::make_shared`==**: it will generate a raw pointer inside, which can be inside of any other control blocks
	2. construct `shared_ptr` by **==converting `unique_ptr`==**: because `unique_ptr` doesn't have a control block
	3. create `shared_ptr` ==**by a raw pointer**==, which means the same raw pointer can create multiple `shared_ptr`, which leads to multiple control block -> multiple pointers of reference counts -> will lead to multiple destructions then undefined behaviors 
	```cpp
	#include <memory>
	int main()
	{
		{
			int *i = new int(42);
			std::shared_ptr<int> p1{i};
			std::shared_ptr<int> p2{i};
		} // error, double destruction on i
	}
	```

	* use `make_shared` would not lead to such error
	```cpp
	auto p = std::make_shared<int>(42);
	```
	* However, `make_shared` does not support pass custom deleters, which can be done by:
	```cpp
	auto f = [](int * ptr){ delete ptr; };
	std::shared_ptr<int> p(new int(42), f);
	```
	