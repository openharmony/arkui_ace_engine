# 自定义节点能力 — 架构设计

## 功能域概述

本目录涵盖 ArkUI 命令式节点（FrameNode、RenderNode、BuilderNode、ComponentContent）的能力设计。

## 通用设计约束

| 约束 | 说明 |
|------|------|
| ETS → C++ 单向调用 | ETS 通过 ANI Bridge 调用 C++，不反向依赖 |
| Modifier 桥接模式 | arkoala_native_ani 不直接链接 ace_engine core，通过 dlsym 加载的 modifier 函数指针表间接调用 |
| PipelineContext 线程安全 | 所有回调需在 UI 线程调用 |
| dispose 非热路径 | 回调为同步调用，栈上分配结构体，无堆分配/锁/异步 |

## Feat-01: JS 内存上报（dispose 生命周期回调）

### 设计来源

FEAT-20260521-jsleak-watcher-static-nodes

### 问题陈述

静态语言路径的命令式节点 dispose 时不经过 C++ PipelineContext 通知 JsLeakWatcher，导致无法检测静态语言路径下这些节点的 JS 内存泄漏。

### 架构分层

```
ETS Layer (dispose)
  → ArkUIAniModule._FireArkUIObjectLifecycleCallback(WeakRef, className, nodeType, nodePtr)
    → ANI Bridge (common_module.cpp)
      → Modifier Bridge (ani_api.h 函数指针 → common_ani_modifier.cpp)
        → PipelineContext::FireArkUIObjectLifecycleCallback(data)
          → JsLeakWatcher C++ 回调
```

### 关键设计决策

| ADR | 决策 | 取舍理由 |
|-----|------|----------|
| ADR-1 | 统一函数 `_FireArkUIObjectLifecycleCallback` 处理所有节点类型 | C++ 实现逻辑相同，className 由 ETS 层传入，不按类型拆函数 |
| ADR-2 | 定义 `ArkUIObjectLifecycleData` 结构体传递数据 | 静态语言路径无 JSI Runtime，无法构造 ArkUIRuntimeCallInfo |
| ADR-3 | 仅通过 C++ PipelineContext，不额外调用 JS Proxy | 与动态语言命令式节点保持一致 |
| ADR-4 | Modifier 桥接层按 className 分发节点类型获取逻辑 | RenderNode/BuilderNode 的 nodePtr 不是 FrameNode*，需不同 Peer 类型转换 |

### 受影响文件

| 文件 | 变更类型 |
|------|----------|
| `arkoala-arkts/.../ani/arkts/ArkUIAniModule.ts` | 声明 native static |
| `arkoala-arkts/.../ani/native/module.cpp` | 注册 ANI 函数 |
| `arkoala-arkts/.../ani/native/common/common_module.h` | 函数声明 |
| `arkoala-arkts/.../ani/native/common/common_module.cpp` | 函数实现 |
| `frameworks/core/interfaces/ani/ani_api.h` | modifier 函数指针 |
| `frameworks/core/interfaces/native/ani/common_ani_modifier.cpp` | 桥接实现（按 className 分发） |
| `arkoala-arkts/.../FrameNode.ets` | dispose() 添加回调 |
| `arkoala-arkts/.../RenderNode.ets` | dispose() 添加回调 |
| `arkoala-arkts/.../BuilderNode.ets` | disposeNode() 添加回调 |
| `arkoala-arkts/.../ComponentContent.ets` | dispose() 添加回调 |

### 不涉及项

PipelineContext 修改、动态语言修改、UIContext 接口修改、JsLeakWatcher 组件实现、Public API 变更。
