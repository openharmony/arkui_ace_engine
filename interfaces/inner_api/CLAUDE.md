# Inner API 子目录规范

本文档包含 Inner API 目录的专用规范，**必须继承并遵守**仓库根目录的 `CLAUDE.md`。本文档仅描述本目录特有的约束和知识。

> **文档版本**: v1.0
> **更新时间**: 2026-02-02
> **源码版本**: OpenHarmony ace_engine (master branch)

---

## 📋 目录

1. [概述](#概述)
2. [模块架构](#模块架构)
3. [核心职责](#核心职责)
4. [接口稳定性约束](#接口稳定性约束)
5. [模块依赖规则](#模块依赖规则)
6. [跨语言绑定](#跨语言绑定)
7. [内存管理契约](#内存管理契约)
8. [错误处理约定](#错误处理约定)
9. [常见陷阱](#常见陷阱)
10. [调试方法](#调试方法)
11. [性能指南](#性能指南)
12. [测试指南](#测试指南)
13. [API 迁移指南](#api-迁移指南)

---

## 概述

### Inner API 定位

**Inner API** (`interfaces/inner_api/`) 是 ACE Engine 的**接口层**，位于框架层（frameworks）和平台适配层（adapter）之间，为整个 ace_engine 提供核心接口和基础设施支持。

**核心价值**：
- 🏗️ **架构桥梁** - 连接 frameworks/core、frameworks/bridge 和 adapter 层
- 🎯 **接口抽象** - 定义稳定的内部接口，隔离底层平台变化
- 🔧 **基础设施** - 提供内存管理、几何计算、动画等基础能力
- 🛡️ **平台适配** - 支持 OpenHarmony 和 Previewer 双平台

### 在 ACE Engine 中的位置

```
应用层（ArkTS 应用）
    ↓
frameworks/bridge（前端桥接层）
    ↓
frameworks/core（核心框架层）
    ↓
interfaces/inner_api（接口层）← 本文档范围
    ↓
adapter（平台适配层）
    ↓
OpenHarmony 子系统（Ability、Window、Graphic2D、MMI、IPC）
```

### 代码规模

- **总文件数**: 273 个文件
  - 头文件: 203 个
  - 源文件: 70 个
- **主要模块**: 8 个
- **构建产物**: 7 个主要库

---

## 模块架构

### 8 大核心模块概览

| 模块 | 路径 | 构建产物 | 核心职责 | 主要使用者 |
|------|------|---------|---------|-----------|
| **Ace** | `ace/` | `libace_uicontent.z.so` | UI 内容管理核心接口 | `adapter/entrance`, `frameworks/bridge` |
| **AceKit** | `ace_kit/` | `ace_kit.a` | 基础设施（内存、几何、动画） | 所有 NG 组件 |
| **DrawableDescriptor** | `drawable_descriptor/` | （静态库） | 可绘制资源描述符 | 图片加载系统 |
| **FormRender** | `form_render/` | `libace_form_render.z.so` | 卡片渲染器 | 卡片服务 |
| **UIServiceManager** | `ui_service_manager/` | `libui_service_mgr.z.so` | UI 服务管理客户端 | 应用层 |
| **UISession** | `ui_session/` | `libui_session.z.so` | UI 会话管理（跨进程） | DevEco Studio |
| **XComponentController** | `xcomponent_controller/` | `libace_xcomponent_controller.z.so` | XComponent 控制 | `XComponentPattern` |
| **Drawable** | `drawable/` | `libdrawable_inner_ani.so` | Drawable ANI 接口 | ANI 模块 |

### 模块依赖关系图

```
                    ┌─────────────────────────────────────────┐
                    │         frameworks/bridge               │
                    │         frameworks/core                 │
                    └─────────────┬───────────────────────────┘
                                  │
                                  ↓
                    ┌─────────────────────────────────────────┐
                    │          Inner API Layer                │
                    │  ┌───────────────────────────────────┐  │
                    │  │  Ace ←→ AceKit ←→ Drawable       │  │
                    │  │  ↓        ↓         ↓             │  │
                    │  │  FormRender (depends on Ace)      │  │
                    │  │  ↓                            │  │
                    │  │  UISession (depends on Ace)      │  │
                    │  │  UIServiceMgr (independent)      │  │
                    │  │  ↓                            │  │
                    │  │  XComponentController (on Ace)   │  │
                    │  └───────────────────────────────────┘  │
                    └─────────────┬───────────────────────────┘
                                  │
                                  ↓
                    ┌─────────────────────────────────────────┐
                    │         adapter/ohos                    │
                    └─────────────────────────────────────────┘
```

### 模块选择规则

```
使用场景 → 模块映射：

UI 生命周期管理 → Ace (UIContent)
内存管理 → AceKit (AceType, RefPtr, WeakPtr)
几何计算 → AceKit (Dimension, Size, Offset, Point)
动画曲线 → AceKit (Curve, CubicCurve)
图片抽象 → DrawableDescriptor
卡片渲染 → FormRender
跨进程通信（调试） → UISession
UI 服务管理 → UIServiceManager
自定义组件控制 → XComponentController
ANI 接口 → Drawable
```

---

## 核心职责

### Inner API 负责

1. **接口定义** - 定义稳定的公共 API
2. **基础设施** - 提供内存管理、几何、动画工具
3. **跨模块协调** - 协调 frameworks 和 adapter 之间的交互
4. **多语言桥接** - C++ ↔ ArkTS ↔ NAPI 绑定

### Inner API 不负责

- ❌ **组件实现** → **frameworks/core/components_ng**
- ❌ **布局算法** → **frameworks/core/layout**
- ❌ **平台适配** → **adapter/ohos**
- ❌ **前端解析** → **frameworks/bridge**

### 模块特定职责

#### Ace 模块

**负责**：
- UIContent 生命周期（Create、Initialize、Destroy、Foreground、Background）
- 导航控制
- UI 事件处理
- 热重载支持

**不负责**：
- ❌ 组件树构建 → frameworks/core
- ❌ 布局测量 → frameworks/core/layout
- ❌ 渲染 → adapter/ohos/rosen

#### AceKit 模块

**负责**：
- 内存管理（AceType、RefPtr、WeakPtr）
- 几何工具（Dimension、Size、Offset、Point）
- 动画曲线
- Pattern 基类
- 属性系统

**不负责**：
- ❌ 具体组件逻辑 → components_ng/pattern/*
- ❌ 布局算法 → frameworks/core/layout

---

## 接口稳定性约束

### 公共 API 语义（不可改变）

#### Ace 模块

```cpp
// UIContent - 核心方法
class UIContent {
    // 必须保持向后兼容
    virtual UIContentErrorCode Initialize(
        Window* window,
        const std::string& url,
        napi_value storage) = 0;

    virtual void Foreground() = 0;
    virtual void Background() = 0;
    virtual void Destroy() = 0;
    virtual void ProcessPointerEvent(const std::shared_ptr<PointerEvent>& event) = 0;
};
```

**禁止**：
- ❌ 改变参数顺序
- ❌ 改变返回值类型
- ❌ 改变方法语义（例如 Destroy() 应该清理所有资源）
- ❌ 删除公共方法

#### AceKit 模块

```cpp
// AceType - 内存管理
class AceType {
    template<typename T>
    static RefPtr<T> MakeRefPtr(Args&&... args);

    template<typename T>
    static RefPtr<T> DynamicCast(const RefPtr<AceType>& ptr);
};
```

**禁止**：
- ❌ 改变 RefPtr/WeakPtr 语义
- ❌ 修改引用计数行为
- ❌ 改变类型转换行为

### API 版本规则

| API 级别 | 稳定性 | 允许破坏性变更 |
|---------|-------|--------------|
| 内部接口 | 主版本内稳定 | 否 |
| 公共接口（导出） | 跨次版本稳定 | 否 |
| 实验性接口 | 不稳定 | 是（需标记废弃） |

### 废弃流程

```cpp
// 示例：废弃旧 API

// 1. 标记为废弃（至少使用 2 个次版本）
class ACE_DEPRECATED("使用 NewMethod() 代替") UIContent {
    virtual void OldMethod() = 0;  // API 10 废弃
    virtual void NewMethod() = 0;  // API 10 新增
};

// 2. 在下一个主版本移除
class UIContent {
    // OldMethod() 在 API 11 移除（主版本升级）
    virtual void NewMethod() = 0;
};
```

---

## 模块依赖规则

### 允许的依赖

```
Inner API 模块依赖关系：

AceKit ← 独立（基础设施）
    ↑
    │
Ace ← 依赖 AceKit
    ↑
    │
UISession ← 依赖 Ace
    ↑
    │
XComponentController ← 依赖 Ace

DrawableDescriptor ← 独立
    ↑
    │
Ace ← 使用 DrawableDescriptor 处理图片

FormRender ← 依赖 Ace、AceKit
```

### 禁止的依赖

**禁止**：
- ❌ **Inner API → frameworks/core**: Inner API 不能依赖组件实现
- ❌ **Inner API → frameworks/bridge**: Inner API 不能依赖前端
- ❌ **AceKit → Ace**: AceKit 必须保持独立的基础层
- ❌ **循环依赖**: 模块 A → 模块 B → 模块 A

### 依赖倒置原则

```cpp
// ✅ 正确：Inner API 定义接口，adapter 实现
// Inner API (interfaces/inner_api/ace/ui_content.h)
class UIContent {
    virtual void Initialize(...) = 0;
};

// Adapter (adapter/ohos/entrance/ui_content_impl.cpp)
class UIContentImpl : public UIContent {
    void Initialize(...) override {
        // 平台特定实现
    }
};

// ❌ 错误：Inner API 直接依赖 adapter
// interfaces/inner_api/ace/ui_content.h
#include "adapter/ohos/entrance/platform_specific.h"  // 禁止
```

---

## 跨语言绑定

### C++ ↔ ArkTS 绑定

#### 示例：UIContent 绑定

**C++ 接口** (inner_api/ace/ui_content.h):
```cpp
class UIContent {
    virtual void SetBackgroundColor(const Color& color) = 0;
};
```

**ArkTS 声明** (bridge/declarative_frontend/jsview/js_ui_content.ts):
```typescript
export class UIContent {
    SetBackgroundColor(color: string | Color | ResourceColor): void;
}
```

**绑定层** (adapter/ohos/entrance/ui_content_impl.cpp):
```cpp
void UIContentImpl::SetBackgroundColor(const Color& color) {
    // 转换 ArkTS color 到 C++ Color
    // 调用 framework 层
}
```

### NAPI 桥接

```cpp
// napi_bind.cpp
static napi_value SetBackgroundColor(napi_env env, napi_callback_info info) {
    // 1. 从 JavaScript 提取参数
    napi_value jsColor;
    napi_get_cb_info(env, info, &argc, &jsColor, nullptr, nullptr);

    // 2. 转换 JavaScript color 到 C++ Color
    Color color = ConvertNapiToColor(env, jsColor);

    // 3. 调用 C++ 接口
    uiContent->SetBackgroundColor(color);

    return nullptr;
}
```

### 绑定规则

**应该做**：
- ✅ 保持接口简单，使用 POD（Plain Old Data）类型
- ✅ 使用显式类型转换
- ✅ 在语言边界处理异常
- ✅ 记录类型映射

**禁止做**：
- ❌ 直接暴露 C++ 特定类型（RefPtr、std::function）
- ❌ 跨语言边界使用 C++ 异常
- ❌ 假设内存管理语义直接对应

---

## 内存管理契约

### AceType 内存管理（AceKit）

#### 接口使用者规则

```cpp
// 规则 1: 为接口对象使用 RefPtr
RefPtr<UIContent> uiContent = UIContent::Create(context, runtime);

// 规则 2: 传递 RefPtr 转移所有权
void RegisterUIContent(const RefPtr<UIContent>& content);

// 规则 3: 使用 WeakPtr 打破循环
class MyClass {
    WeakPtr<UIContent> uiContent_;  // 防止循环
};

// 规则 4: 始终检查 WeakPtr::Upgrade() 结果
RefPtr<UIContent> locked = uiContent_.Upgrade();
if (locked) {
    locked->Foreground();
}
```

#### 禁止的模式

```cpp
// ❌ 错误：裸指针
UIContent* content = new UIContentImpl();  // 内存泄漏！

// ❌ 错误：混用 RefPtr 和裸指针
RefPtr<UIContent> ref = ...;
UIContent* raw = ref.Get();  // 危险，如果 ref 超出作用域

// ❌ 错误：删除 RefPtr 管理的对象
RefPtr<UIContent> ref = ...;
delete ref.Get();  // 双重删除！
```

### 内存所有权转移

```cpp
// 工厂函数：返回 RefPtr（调用者拥有）
RefPtr<UIContent> UIContent::Create(...) {
    return AceType::MakeRefPtr<UIContentImpl>();
}

// Setter：接受 RefPtr（转移共享所有权）
void SetUIContent(const RefPtr<UIContent>& content) {
    uiContent_ = content;  // 两者共享所有权
}

// Getter：返回 RefPtr（调用者获得共享所有权）
RefPtr<UIContent> GetUIContent() const {
    return uiContent_;
}
```

---

## 错误处理约定

### 错误码策略（Ace 模块）

```cpp
// UIContentErrorCode - 使用错误码，而非异常
enum class UIContentErrorCode {
    NO_ERROR = 0,
    INVALID_WINDOW,
    INVALID_URL,
    INIT_FAILED,
    // ...
};

// 返回错误码
virtual UIContentErrorCode Initialize(...) = 0;

// 使用者检查错误码
UIContentErrorCode err = uiContent->Initialize(...);
if (err != UIContentErrorCode::NO_ERROR) {
    LOGE("Initialize failed: %{public}d", err);
    return;
}
```

### 错误处理模式

#### 模式 1：错误码 + 日志
```cpp
UIContentErrorCode UIContentImpl::Initialize(...) {
    if (!window) {
        LOGE("Initialize failed: window is null");
        return UIContentErrorCode::INVALID_WINDOW;
    }
    return UIContentErrorCode::NO_ERROR;
}
```

#### 模式 2：可选返回 + 日志
```cpp
std::optional<RefPtr<UIContent>> CreateUIContent(...) {
    if (!context) {
        LOGW("Cannot create UIContent: context is null");
        return std::nullopt;
    }
    return AceType::MakeRefPtr<UIContentImpl>();
}
```

#### 模式 3：回调错误
```cpp
using ResultCallback = std::function<void(bool success, int32_t errorCode)>;

void AsyncOperation(ResultCallback callback) {
    bool success = DoOperation();
    if (!success) {
        callback(false, ERROR_CODE);
    }
}
```

---

## 常见陷阱

### 1. 接口破坏性变更

**⚠️ 常见错误**：
```cpp
// ❌ 错误：在现有接口中改变方法签名
class UIContent {
    // 旧版本
    virtual void Initialize(Window* window) = 0;

    // 新版本 - 破坏所有使用者！
    virtual void Initialize(Window* window, const std::string& url) = 0;
};
```

**✅ 正确做法**：
```cpp
// 使用不同名称添加新方法
class UIContent {
    // 保留旧方法以保持兼容性
    virtual void Initialize(Window* window) = 0;

    // 添加新方法
    virtual void InitializeWithURL(Window* window, const std::string& url) = 0;
};

// 或使用默认参数（如果 ABI 兼容）
class UIContent {
    virtual void Initialize(Window* window, const std::string& url = "") = 0;
};
```

### 2. 模块间循环依赖

**⚠️ 常见错误**：
```cpp
// ❌ 错误：Ace 依赖 FormRender
// ace/ui_content.h
#include "form_render/form_renderer.h"  // 禁止

class UIContent {
    RefPtr<FormRenderer> renderer_;  // 创建循环依赖
};
```

**✅ 正确做法**：
```cpp
// 使用前向声明和接口
// ace/ui_content.h
class FormRendererInterface;  // 前向声明

class UIContent {
    FormRendererInterface* renderer_;  // 使用接口指针
};

// form_render/form_renderer.h
#include "ace/ui_content.h"  // OK: FormRender 依赖 Ace
```

### 3. 回调中的内存泄漏

**⚠️ 常见错误**：
```cpp
// ❌ 错误：在 lambda 中捕获 RefPtr 创建循环
class MyClass {
    RefPtr<UIContent> uiContent_;

    void RegisterCallback() {
        uiContent_->SetCallback([this, uiContent = uiContent_]() {
            // uiContent_ 和 this 相互保持存活，永远泄漏
        });
    }
};
```

**✅ 正确做法**：
```cpp
// 使用 WeakPtr 打破循环
class MyClass {
    RefPtr<UIContent> uiContent_;

    void RegisterCallback() {
        WeakPtr<UIContent> weakUi = uiContent_;
        uiContent_->SetCallback([weakUi]() {
            auto ui = weakUi.Upgrade();
            if (ui) {
                // 安全使用
            }
        });
    }
};
```

### 4. 线程安全违规

**⚠️ 常见错误**：
```cpp
// ❌ 错误：从错误线程访问 UIContent
// 在 UI 线程创建
auto uiContent = UIContent::Create(context, runtime);

// 在工作线程访问
std::thread([&]() {
    uiContent->Foreground();  // 崩溃！仅 UI 线程
}).detach();
```

**✅ 正确做法**：
```cpp
// 使用 task runner 发布到正确线程
uiContent->GetTaskRunner()->PostTask([&]() {
    uiContent->Foreground();  // 在 UI 线程运行
});
```

### 5. 违反依赖方向

**⚠️ 常见错误**：
```cpp
// ❌ 错误：AceKit 依赖 Ace
// ace_kit/include/ui/base/ace_type.h
#include "ace/ui_content.h"  // 禁止！

class AceType {
    // 这样会创建循环依赖
};
```

**✅ 正确做法**：
```cpp
// AceKit 保持独立
// ace_kit/include/ui/base/ace_type.h
// 不包含任何 Ace 模块的头文件

class AceType {
    // 纯粹的基础设施
};

// Ace 可以使用 AceKit
// ace/ui_content.h
#include "ace_kit/include/ui/base/ace_type.h"

class UIContent : public AceType {
    // OK: Ace 依赖 AceKit
};
```

---

## 调试方法

### 1. 启用日志

```cpp
#include "base/log/log_wrapper.h"

// 使用适当的日志标签
#define TAG "InnerApi"

// 日志级别
LOGD("%{public}s", "Debug message");
LOGI("%{public}s", "Info message");
LOGW("%{public}s", "Warning message");
LOGE("%{public}s", "Error message");
```

### 2. 转储接口状态

```cpp
// 实现转储方法用于调试
class UIContentImpl : public UIContent {
    void DumpInfo(std::ostream& os) const override {
        os << "UIContent state:\n";
        os << "  initialized: " << initialized_ << "\n";
        os << "  foreground: " << isForeground_ << "\n";
        os << "  url: " << url_ << "\n";
    }
};

// 在调试中使用
uiContent->DumpInfo(std::cerr);
```

### 3. 内存泄漏检测

```cpp
// 使用内存监控（AceKit 功能）
#include "base/memory/memory_monitor.h"

// 启用内存监控
MemoryMonitor::GetInstance().StartTracking();

// 创建对象
RefPtr<UIContent> content = UIContent::Create(...);

// 检查泄漏
MemoryMonitor::GetInstance().DumpMemoryStats();
```

### 4. 常见问题定位

| 问题 | 可能原因 | 检查清单 |
|------|---------|---------|
| **接口未找到** | 库未加载 | 检查 `out/` 中的 `.so` 文件 |
| **符号未找到** | ABI 不匹配 | 重新构建所有依赖 |
| **调用崩溃** | 错误线程 | 检查日志中的线程 ID |
| **内存泄漏** | RefPtr 循环 | 使用 WeakPtr，检查转储 |
| **回调未调用** | Task runner 未运行 | 检查 task runner 状态 |

### 5. 关键数据结构检查

**在调试器中检查**：

```cpp
// Ace 模块
currentOffset_           // 当前偏移
scrollableDistance_      // 可滚动距离

// AceKit 模块
refCount_                // 引用计数
weakRefCount_            // 弱引用计数

// UISession 模块
sessionId_               // 会话 ID
proxy_                   // 代理对象
```

---

## 性能指南

### 1. 最小化虚函数调用开销

```cpp
// ✅ 好的做法：缓存接口指针
class MyClass {
    RefPtr<UIContent> uiContent_;

    void Init() {
        uiContent_ = UIContent::Create(...);  // 创建一次
    }

    void Update() {
        uiContent_->ProcessVsyncEvent(time);  // 重用
    }
};

// ❌ 坏的做法：每次调用都创建接口
void Update() {
    auto content = UIContent::Create(...);  // 昂贵！
    content->ProcessVsyncEvent(time);
}
```

### 2. 对大对象使用移动语义

```cpp
// ✅ 好的做法：对字符串/向量使用 std::move
virtual void SetURL(std::string url) = 0;

// 调用
uiContent->SetURL(std::string("https://..."));  // 拷贝
uiContent->SetURL(std::move(urlString));         // 移动（更快）

// ❌ 坏的做法：按值传递大对象
virtual void SetData(std::vector<uint8_t> data) = 0;  // 可能拷贝
```

### 3. 批量接口调用

```cpp
// ✅ 好的做法：批量属性更新
uiContent->BeginPropertyUpdates();
uiContent->SetWidth(100.0);
uiContent->SetHeight(200.0);
uiContent->SetBackgroundColor(Color::RED);
uiContent->EndPropertyUpdates();  // 一次性应用

// ❌ 坏的做法：单独更新（每次触发通知）
uiContent->SetWidth(100.0);        // 通知
uiContent->SetHeight(200.0);       // 通知
uiContent->SetBackgroundColor(...); // 通知
```

### 4. 避免频繁的 Measure/Layout

```cpp
// ❌ 坏的做法：在滚动回调中触发布局
void ScrollPattern::OnScrollCallback(float offset, int32_t source) override
{
    UpdateCurrentOffset(offset, source);
    FireOnDidScroll(offset);  // 如果回调修改属性，触发新布局
}

// ✅ 好的做法：合并布局请求
// 使用 requestFrame 合并多个布局请求
// 仅在滚动结束时（OnScrollEndCallback）触发布局
```

---

## 测试指南

### 1. 单元测试结构

```
test/unittest/interfaces/inner_api/
├── ace/
│   ├── ui_content_test.cpp
│   ├── navigation_controller_test.cpp
│   └── ui_event_test.cpp
├── ace_kit/
│   ├── ace_type_test.cpp
│   ├── geometry_test.cpp
│   └── animation_test.cpp
├── drawable_descriptor/
│   └── drawable_descriptor_test.cpp
└── ...
```

### 2. 接口 Mock 示例

```cpp
// Mock UIContent 用于测试
class MockUIContent : public UIContent {
public:
    MOCK_METHOD(UIContentErrorCode, Initialize,
              (Window* window, const std::string& url, napi_value storage),
              (override));
    MOCK_METHOD(void, Foreground, (), (override));
    MOCK_METHOD(void, Background, (), (override));
};

// 在测试中使用 mock
TEST(MyClassTest, UsesUIContent) {
    auto mockContent = std::make_shared<MockUIContent>();
    EXPECT_CALL(*mockContent, Initialize(_, _, _))
        .WillOnce(Return(UIContentErrorCode::NO_ERROR));

    MyClass myClass(mockContent);
    ASSERT_TRUE(myClass.Initialize());
}
```

### 3. 内存泄漏测试

```cpp
TEST(AceTypeTest, NoMemoryLeak) {
    // 记录初始内存
    size_t initialMemory = MemoryMonitor::GetInstance().GetCurrentMemory();

    {
        // 创建对象
        RefPtr<MyClass> obj1 = AceType::MakeRefPtr<MyClass>();
        RefPtr<MyClass> obj2 = AceType::MakeRefPtr<MyClass>();
        obj1->SetChild(obj2);
    }

    // 对象应该被销毁
    size_t finalMemory = MemoryMonitor::GetInstance().GetCurrentMemory();
    ASSERT_NEAR(initialMemory, finalMemory, 1024);  // 允许小误差
}
```

### 4. 运行测试

```bash
# 编译单元测试
./build.sh --product-name rk3568 --build-target unittest

# 运行 inner_api 测试
cd out/rk3568/tests/ace_engine/unittest
./interfaces_test --gtest_filter="InnerApi*"
```

---

## API 迁移指南

### 从旧 API 迁移到新 API

#### 示例：UIContent API 变更

**旧 API（已废弃）**：
```cpp
// 旧方式（API 9）
UIContent* content = new UIContentImpl();
content->Init(window);
content->SetPageUrl(url);
content->CreateRootView();
```

**新 API（推荐）**：
```cpp
// 新方式（API 10+）
RefPtr<UIContent> content = UIContent::Create(context, runtime);
UIContentErrorCode err = content->Initialize(window, url, storage);
if (err != UIContentErrorCode::NO_ERROR) {
    // 处理错误
}
```

#### 迁移清单

- [ ] 替换工厂方法（new → Create）
- [ ] 使用错误码替代异常
- [ ] 使用 RefPtr 替代裸指针
- [ ] 更新方法签名
- [ ] 更新回调签名
- [ ] 测试所有迁移的代码

---

## 总结

### 核心原则

1. **接口稳定性优先** - 永不破坏现有 API
2. **清晰的模块边界** - 尊重依赖规则
3. **内存安全** - 正确使用 AceType
4. **错误处理** - 使用错误码，而非异常
5. **线程安全** - 尊重线程边界

### 记住

Inner API 是 ACE Engine 的基础。任何变更会影响：
- 所有组件实现（frameworks/core/components_ng）
- 所有前端桥接（frameworks/bridge）
- 所有平台适配器（adapter/*）

在修改 Inner API 之前：
- 了解对所有使用者的影响
- 检查 ABI 兼容性
- 运行完整测试套件
- 更新文档
- 考虑破坏性变更的废弃流程

---

## 相关资源

### 内部文档
- 📖 **[Inner API 完整知识库](../../docs/interfaces/inner_api/inner_api_Knowledge_Base.md)** - 深度技术参考
- 📄 **[README.md](README.md)** - 快速索引

### 参考文档
- [ace_kit/include/ui/base/MEMORY_DESIGN.md](ace_kit/include/ui/base/MEMORY_DESIGN.md) - 内存管理设计
- [CLAUDE.md](../../CLAUDE.md) - 项目指导文档

### 测试资源
- `test/unittest/interfaces/inner_api/` - 单元测试
- `test/mock/ohos_mock/` - Mock 对象
