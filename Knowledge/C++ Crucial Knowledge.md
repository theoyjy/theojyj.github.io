### 高优先级（核心考点）

1. 理解模板类型推导、auto类型推导和decltype（Effective Modern C++ 1-4）[Knowledge](#01%20Template%20Type%20Deduction) [Questions](#1%20Template%20Type%20Deduction%20|%20`auto`%20|%20`decltype`%20Questions)
2. 理解std::move和std::forward（Effective Modern C++ 23-25）
3. 理解右值引用，移动语义，完美转发（Effective Modern C++ 23-30）
4. 对于占有性资源使用std::unique_ptr（Effective Modern C++ 18）
5. 对于共享性资源使用std::shared_ptr（Effective Modern C++ 19）
6. 优先考虑使用std::make_unique和std::make_shared而非new（Effective Modern C++ 21）
7. 对于右值引用使用std::move，对于通用引用使用std::forward（Effective Modern C++ 25）
8. 确保const成员函数线程安全（Effective Modern C++ 16）
9. 使用override声明重载函数（Effective Modern C++ 12）
10. 理解异常处理（More Effective C++ 9-15）

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

# 2 `std::move` and `std::forward`

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
> // 1. Match broadly, incorrect behavio
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

