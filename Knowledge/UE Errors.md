### 每个类会生成模板对象，调用该类的构造函数，如果给模板对象生成 `component`并尝试注册：
```cpp
AAnchorActor::AAnchorActor()
{
	billboardCmp = CreateDefaultSubobject<UBillboardComponent
	(TEXT("BillboardIconCmp"));
	// ...
	billboardCmp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform) //此时RootComponent = nullptr 
}
```

=> 在析构时，如果恰巧重载 **BeginDestroy** 释放资源，会 **crash** 在 **UnregisterComponent** ，因为BeginDetroy 模板对象也会调用
==⭐应该重载EndPlay, 模板对象析构时不会调用，
同时也应该在构造函数里加上IsTemplate()的判断，或者重载BeginPlay 去构造获取资源==