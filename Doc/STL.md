---
finished: false
---

[homepage](../index.md)

# STL源码剖析
SGI source code: https://github.com/SilverMaple/STLSourceCodeNote/blob/master/

## Allocator 空间配置器
STL配置器定义于 `<memory>` ，STL allocator将构造/析构与内存分配/释放区分开来，其包含：
- `<stl_alloc.h>` : `alloc::allocate()` 分配内存 | `alloc::deallocate()` 释放内存      //负责内存空间的配置与释放
- `<stl_construct.h>` : `::construct()` | `::destroy()`                                              //*负责对象的构造与析构*
- `<stl_unitialized.h>` 里面包含了一些全局函数, 与**对象初值设置**有关 
	- `un_initialized_copy() | un_initialized_fill() | un_initialized_fill_n()`
	- 这些函数对于效率都有考量
		- **最差**情况下会调用`construct()`
		- **最优**情况会使用**C标准函数`memmove()`直接进行内存数据移动**

### 2.2.3 构造和析构基本工具 <stl_construct.h>

```cpp
#include <new.h>

// 构造：只有泛化构造
template <class T1, class T2>
inline void construct(T1 *p, const T2& value) {
    new (p) T1(value); // p =  new T1(value);
}

// 析构
// 泛化析构
template <class ForwardIterator>
inline void destory(ForwardIterator first, ForwardIterator last) {
    typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor; // trivial_destructor : 用来标记析构函数是否为平凡的参数
    __destory_aux(first, last, trivial_destructor());
}

// 上个函数所调用的trivial_destructor()返回__true_type表示为trivial析构，没必要对每一个对象进行无关痛痒的析构，很损耗效率
template <class ForwardIterator>
inline void __destory_aux(ForwardIterator, ForwardIterator, __true_type) {} // 确认所有对象只有trivial析构后，不再一一析构，直接结束

// 若为non-trivial
template <class ForwardIterator>
inline void __destory_aux(ForwardIterator, ForwardIterator, __false_type) {
    for( ; first < last; ++first)
        destory(&*first); // 调用每一个对象的non-trivial析构👇
}

// 特化析构： 用于析构一个对象，活上述接受两个迭代器的destory其中的每一个对象
template <class T>
inline void destory(T* pointer){
    pointer->~T();
}

```
![[Pasted image 20240329174543.png|600]]

> [!Tip] 泛化析构的优势
> 若使用参数为first, end 迭代器的析构函数，万一范围很大，而如果每个对象的析构函数都是无关痛痒的(trivial destructor), 那么一次次调用这些 trivial destructor 对效率是一种伤害。因此先利用 `value_type()` 获得迭代器所指对象的型别，再利用 `__type_traits<T>` 判断是否`trivial`。若是 `__true_type` , 则什么也不做直接结束；若否 `__false_type` , 才循环整个范围，并调用 `destroy()`

> [!note] trivial
> 平凡，意为**该类只有默认构造、析构函数，没有用户自定义构造、析构**，==析构函数不执行任何操作（或者说是无副作用的）==。这个信息对于性能优化是很有用的，因为对于平凡析构函数，我们可以省略显式调用析构函数的步骤，从而提高代码执行效率。


### 2.2.4 空间的配置与释放 std::alloc

>[!Danger] 内存分配注意的问题
>1. 向 system heap 请求空间
>2. 考虑多线程
>3. 内存不足时的应变措施
>4. 考虑过多”小型区块“可能造成的内存碎片问题

#### SGI 双层级配置器
第一级配置器 `malloc()  free()`
第二级配置器:
1. 当配置区块 `> 128 bytes`, 视为"足够大"，调用第一级配置器
2. `< 128 byes` , 视为"过小"，为了降低额外负担，采用复杂的 memory pool。
*整个设计是否只开放第一级配置器，或同时开放第二级配置器，取决于 `__USE_MALLOC` 是否被定义*
![[STL-20240329184439033.webp]]
![[STL-20240329184717314.webp]]

 >[!INFO] C++ new handler
 >当 c++ 的 `new` 或 `new[]` 分配内存失败时:
 >1. 若用户有自定义的函数即 "new handler",系统会调用这个函数**尝试释放内存或进行其他操作**
 >2. 若没有设置新的处理程序，则抛出`std::bad_alloc` 异常
>For example:
```cpp
 #include <iostream>
 #include <new>
 
 void customeNewHandler()
 {
	 std::cerr << "Memory allocation failed! Custom New Handler called" << 
			 std::endl;
	 // free up  memory or other actions
 }

int main()
{
	std::set_new_handler(customNewHandler);
	int* ptr = new int[100000000000000000];
	// Use the allocated memory  ... 

	// Release memory 
	delete[] ptr; 
	return 0;
}
```

#### 第一级配置器 `__malloc_alloc_template`

```cpp
template <int inst>
class __malloc_alloc_template{

private:
	// 内存不足时调用
	static void * oom_malloc(size_t);
	static void * oom_realloc(void *, size_t);
	static void (* __malloc_alloc_oom_handler) ();

public:
	static void * allocate(size_t n)
	
}

```