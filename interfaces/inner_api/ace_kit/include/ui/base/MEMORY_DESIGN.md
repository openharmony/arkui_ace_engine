# ACE Engine 内存管理设计总结

本文档总结 ACE Engine 的内存管理系统，包括 AceType 和智能指针的设计与使用。

## 一、整体架构图

```
                    ┌─────────────────────┐
                    │    TypeInfoBase     │  ← 类型信息基类（RTTI 支持）
                    │  - TypeId()         │
                    │  - TypeName()       │
                    │  - SafeCastById()   │
                    └──────────┬──────────┘
                               │ 继承
                    ┌──────────▼───────────┐
                    │    Referenced        │  ← 引用计数基类
                    │  - RefCounter*       │
                    │  - Inc/DecRefCount() │
                    └──────────┬───────────┘
                               │ 继承
                    ┌──────────▼───────────┐
                    │     AceType         │  ← 统一基类
                    │  (TypeInfoBase +    │     组合类型系统 + 引用计数
                    │   Referenced)       │
                    └─────────────────────┘
                               ▲
                               │ 继承
                    ┌──────────┴───────────┐
                    │   用户自定义类       │
                    │   DECLARE_ACE_TYPE   │
                    └─────────────────────┘
```

## 二、核心组件

### 1. AceType - 统一基类

**位置**: `ui/base/ace_type.h`

```cpp
class AceType : public virtual TypeInfoBase, public virtual Referenced
```

**功能**：
- 组合了 `TypeInfoBase`（类型信息）和 `Referenced`（引用计数）
- 提供 `DynamicCast`、`InstanceOf`、`TypeId`、`TypeName` 等类型查询功能
- 通过 `DECLARE_ACE_TYPE` 宏自动生成类型关系

**使用示例**：
```cpp
class MyClass : public virtual AceType {
    DECLARE_ACE_TYPE(MyClass, AceType);
};

RefPtr<MyClass> ptr = AceType::MakeRefPtr<MyClass>();
auto typeId = AceType::TypeId(ptr);
const char* name = AceType::TypeName(ptr);
```

---

### 2. Referenced - 引用计数基类

**位置**: `ui/base/referenced.h`

**核心成员**：
- `RefCounter* refCounter_` - 引用计数器（支持线程安全/不安全两种模式）

**关键方法**：
```cpp
// 创建智能指针
template<class T>
static RefPtr<T> Claim(T* rawPtr);

// 工厂方法
template<class T, class... Args>
static RefPtr<T> MakeRefPtr(Args&&... args);

// 引用计数操作
void IncRefCount();
void DecRefCount();     // 计数为0时自动 delete this
int32_t RefCount();
```

**生命周期检查**：继承自 `LifeCycleCheckable`，可以检测对象在使用中被销毁的问题

---

### 3. RefPtr - 强引用智能指针

**位置**: `ui/base/referenced.h`

**特点**：
- 类似 `std::shared_ptr`，但专为 ACE 引擎设计
- 构造时自动增加强引用计数
- 析构时自动减少强引用计数，计数归零时删除对象
- 支持隐式类型转换（移除了 `explicit`）
- 支持模板多态转换

**关键操作**：
```cpp
RefPtr<MyClass> ptr1 = Referenced::MakeRefPtr<MyClass>();
RefPtr<MyClass> ptr2 = ptr1;           // 拷贝：引用计数+1
RefPtr<Base> basePtr = ptr1;           // 向上转型
RefPtr<MyClass> ptr3 = AceType::DynamicCast<Base>(basePtr);

ptr1->Method();        // operator-> 返回 PtrHolder（带生命周期检查）
ptr1.Reset();          // 释放引用
```

**比较运算符**：通过比较 `RefCounter*` 来判断是否指向同一对象

---

### 4. WeakPtr - 弱引用智能指针

**位置**: `ui/base/referenced.h`

**特点**：
- 类似 `std::weak_ptr`，用于解决循环引用
- 不影响强引用计数
- 需要通过 `Upgrade()` 升级为 `RefPtr` 才能使用

**关键操作**：
```cpp
WeakPtr<MyClass> weak = strongPtr;
if (auto ptr = weak.Upgrade()) {
    // 对象仍然存活，可以安全使用
    ptr->Method();
} else {
    // 对象已被销毁
}

if (weak.Invalid()) {
    // 对象已失效
}
```

**成员**：
- `T* unsafeRawPtr_` - 原始指针（仅用于 Upgrade 成功后访问）
- `RefCounter* refCounter_` - 引用计数器指针

---

### 5. RefCounter - 引用计数器

**位置**: `ui/base/ref_counter.h`

**两种实现**：

```cpp
// 线程安全版本（使用 std::atomic）
using ThreadSafeRef = RefCounterImpl<ThreadSafeCounter>;

// 线程不安全版本（普通 int32_t）
using ThreadUnsafeRef = RefCounterImpl<ThreadUnsafeCounter>;
```

**计数字段**：
- `strongRef_` - 强引用计数（从 0 开始）
- `weakRef_` - 弱引用计数（从 1 开始，因为对象自己持有一份）

**关键方法**：
- `TryIncStrongRef()` - 尝试增加强引用（仅当强引用 > 0 时成功）
- 用于 `WeakPtr::Upgrade()` 避免访问已销毁对象

---

### 6. TypeInfoBase - 类型系统

**位置**: `ui/base/type_info_base.h`

**功能**：提供类似 RTTI 的类型查询能力，但不依赖 C++ RTTI

**核心机制**：
```cpp
#define DECLARE_RELATIONSHIP_OF_CLASSES(classname, ...)
```

- 使用 `std::hash<std::string>` 生成 TypeId
- 通过递归模板实现多继承的类型遍历
- `SafeCastById()` 依次检查继承链上的每个类型

**DynamicCast 实现**：
```cpp
template<class T>
static T* DynamicCast(TypeInfoBase* rawPtr) {
    return reinterpret_cast<T*>(rawPtr->SafeCastById(T::TypeId()));
}
```

---

### 7. MemoryMonitor - 内存监控

**位置**: `ui/base/memory_monitor.h`

**功能**：
- 追踪所有 `Referenced` 对象的生命周期
- 按类型统计内存使用
- 可通过系统属性 `persist.ace.memorymonitor.enabled` 启用

**实现**：
```cpp
class MemoryMonitorImpl {
    std::map<void*, MemInfo> memoryMap_;     // 指针 -> 内存信息
    std::map<std::string, TypeInfo> typeMap_; // 类型名 -> 统计信息
    size_t total_;                           // 总内存
    size_t count_;                           // 总对象数
};
```

---

## 三、设计特点总结

| 特性 | 实现方式 |
|------|----------|
| **引用计数** | 自定义 `RefCounter`，支持线程安全/不安全模式 |
| **智能指针** | `RefPtr`（强引用）+ `WeakPtr`（弱引用） |
| **类型系统** | 自定义 RTTI，使用哈希TypeId + 递归继承检查 |
| **内存监控** | 单例 `MemoryMonitor` 追踪所有对象 |
| **生命周期检查** | `LifeCycleCheckable` 检测使用中销毁 |
| **对象创建** | `Referenced::MakeRefPtr<T>()` 工厂方法 |
| **循环引用解决** | `WeakPtr` + `Upgrade()` 机制 |
| **隐式转换** | 移除 `explicit` 支持链式调用和多态 |

---

## 四、使用建议

```cpp
// 1. 定义类时使用 DECLARE_ACE_TYPE
class MyComponent : public virtual AceType {
    DECLARE_ACE_TYPE(MyComponent, AceType);
};

// 2. 创建对象使用 MakeRefPtr
RefPtr<MyComponent> comp = Referenced::MakeRefPtr<MyComponent>();

// 3. 需要打破循环引用时使用 WeakPtr
class Parent : public virtual AceType {
    WeakPtr<Child> child_;  // 使用 WeakPtr 避免循环引用
};

// 4. 类型转换使用 DynamicCast
RefPtr<Base> base = ...;
RefPtr<Derived> derived = AceType::DynamicCast<Derived>(base);

// 5. 获取原始指针（谨慎使用）
MyComponent* raw = Referenced::RawPtr(comp);
```

---

## 五、核心文件列表

| 文件 | 功能 |
|------|------|
| `ace_type.h` | AceType 统一基类 |
| `referenced.h` | Referenced 引用计数基类、RefPtr、WeakPtr |
| `ref_counter.h` | RefCounter 引用计数器 |
| `type_info_base.h` | TypeInfoBase 类型系统 |
| `memory_monitor.h` | MemoryMonitor 内存监控 |
| `lifecycle_checkable.h` | LifeCycleCheckable 生命周期检查 |
| `macros.h` | 宏定义 |
