### 高优先级（核心考点）

1. 理解模板类型推导、auto类型推导和decltype（Effective Modern C++ 1-4）[link](#01%20Template%20Type%20Deduction) 
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

