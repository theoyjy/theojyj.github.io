---
finished: false
---

[homepage](../index.md)

# STL源码剖析
SGI source code: https://github.com/SilverMaple/STLSourceCodeNote/blob/master/

## Allocator空间配置器

STL allocator将构造/析构与内存分配/释放区分开来。 
- <stl_alloc.h> : alloc::allocate() 分配内存 | alloc::deallocate() 释放内存
- <stl_construct.h> : ::construct() | ::destory()

### <stl_construct.h>
```
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
    typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor;
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

#### trivial
无关痛痒，意为**该类只有默认构造、析构函数，没有用户自定义构造、析构**



**To Read pdf p86**
