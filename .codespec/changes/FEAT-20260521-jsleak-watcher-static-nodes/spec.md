# 特性规格

## 概述

| 属性 | 值 |
|------|-----|
| 特性名称 | 静态语言命令式节点 JsLeakWatcher 内存上报 |
| 特性编号 | FEAT-20260521-jsleak-watcher-static-nodes |
| 所属 Epic | 无 |
| 优先级 | P1 |
| 目标版本 | TBD |
| SIG 归属 | SIG_ArkUI |
| 状态 | Approved |
| 复杂度 | 标准 |

## 本次变更范围（Delta）

| 类型 | 内容 | 说明 |
|------|------|------|
| ADDED | 静态语言路径 FrameNode/RenderNode/BuilderNode/ComponentContent dispose 时的 lifecycle callback 通知 | 补齐与动态语言一致的行为 |
| ADDED | ANI Bridge 函数 `_FireArkUIObjectLifecycleCallback` | 桥接 ETS 到 C++ PipelineContext |

## 输入文档

| 文档 | 路径 | 状态 |
|------|------|------|
| Requirement | proposal.md | Baselined |
| Design | design.md | Approved |

## 调用链说明

动态语言路径中，命令式节点的 dispose() 通过 `getUINativeModule().frameNode.fireArkUIObjectLifecycleCallback()` 调用 C++ bridge，最终到达 `PipelineContext::FireArkUIObjectLifecycleCallback(data)`。**不直接调用** `ArkUIObjectFinalizationRegisterProxy.call()`（该调用仅由自定义节点 pu_view/v2_view 使用）。

静态语言路径应保持一致：ETS dispose() → ANI Bridge → C++ PipelineContext::FireArkUIObjectLifecycleCallback。

## 用户故事

### US-1: 静态语言 FrameNode dispose 通知

**作为** JsLeakWatcher 开发者,
**我想要** 静态语言路径的 FrameNode 调用 dispose() 时触发已注册的回调,
**以便** 检测 FrameNode 的 JS 内存泄漏.

**验收标准：**

- **AC-1.1:** WHEN 静态语言 FrameNode 调用 dispose() 且 peer.ptr 和 nodePtr 均有效 THEN 通过 ANI Bridge 调用 PipelineContext::FireArkUIObjectLifecycleCallback，传递的数据包含节点类型 'FrameNode'

### US-1b: 静态语言 TypedFrameNode dispose 通知

**作为** JsLeakWatcher 开发者,
**我想要** 静态语言路径的 TypedFrameNode（FrameNode 子类，如 TextFrameNode、ImageFrameNode）调用 dispose() 时触发已注册的回调,
**以便** 检测具体组件节点的 JS 内存泄漏.

**验收标准：**

- **AC-1b.1:** WHEN 静态语言 TypedFrameNode（如 TextFrameNode）调用 dispose() 且 peer.ptr 和 nodePtr 均有效 THEN 通过 ANI Bridge 调用 PipelineContext::FireArkUIObjectLifecycleCallback，className 为 'FrameNode'，nodeType 为具体组件类型（如 'Text'）

### US-2: 静态语言 RenderNode dispose 通知

**作为** JsLeakWatcher 开发者,
**我想要** 静态语言路径的 RenderNode 调用 dispose() 时触发已注册的回调,
**以便** 检测 RenderNode 的 JS 内存泄漏.

**验收标准：**

- **AC-2.1:** WHEN 静态语言 RenderNode 调用 dispose() 且 nodePtr 有效 THEN 通过 ANI Bridge 调用 PipelineContext::FireArkUIObjectLifecycleCallback，传递的数据包含节点类型 'RenderNode'

### US-3: 静态语言 BuilderNode dispose 通知

**作为** JsLeakWatcher 开发者,
**我想要** 静态语言路径的 BuilderNode 调用 dispose() 时触发已注册的回调,
**以便** 检测 BuilderNode 的 JS 内存泄漏.

**验收标准：**

- **AC-3.1:** WHEN 静态语言 BuilderNode 调用 dispose() 且 nodePtr 有效 THEN 通过 ANI Bridge 调用 PipelineContext::FireArkUIObjectLifecycleCallback，传递的数据包含节点类型 'BuilderNode'

### US-4: 静态语言 ComponentContent dispose 通知

**作为** JsLeakWatcher 开发者,
**我想要** 静态语言路径的 ComponentContent 调用 dispose() 时触发已注册的回调,
**以便** 检测 ComponentContent 的 JS 内存泄漏.

**验收标准：**

- **AC-4.1:** WHEN 静态语言 ComponentContent 调用 dispose() 且 nodePtr 有效 THEN 通过 ANI Bridge 调用 PipelineContext::FireArkUIObjectLifecycleCallback，传递的数据包含节点类型 'ComponentContent'

### US-5: 回调数据格式一致性

**作为** JsLeakWatcher 开发者,
**我想要** 静态语言路径的回调数据与动态语言路径一致,
**以便** 统一处理两种语言路径的内存上报.

**验收标准：**

- **AC-5.1:** WHEN ANI Bridge 函数被调用 THEN 传递给 PipelineContext 的数据包含 4 个字段（WeakRef + className + nodeType + nodePtr），与动态语言传递的 4 个参数对应

### US-6: 边界和异常处理

**验收标准：**

- **AC-6.1:** WHEN 节点已 dispose（isDisposed() === true）THEN 不触发回调（幂等性）
- **AC-6.2:** WHEN 节点 peer.ptr / nodePtr 为 null 或 undefined THEN 不触发回调
- **AC-6.3:** WHEN PipelineContext::objectLifecycleCallback_ 未注册 THEN PipelineContext::FireArkUIObjectLifecycleCallback 安全跳过（CHECK_NULL_VOID 保护）

## AC 溯源映射（proposal.md → spec.md）

| proposal.md AC | spec.md AC | 说明 |
|----------------|------------|------|
| AC-1 FrameNode dispose 回调 | AC-1.1 | FrameNode 基础回调 |
| — | AC-1b.1 | Spec 细化：TypedFrameNode 子类回调（proposal 未单独列出，spec 细化展开） |
| AC-2 RenderNode dispose 回调 | AC-2.1 | 直接对应 |
| AC-3 BuilderNode dispose 回调 | AC-3.1 | 直接对应 |
| AC-4 ComponentContent dispose 回调 | AC-4.1 | 直接对应 |
| AC-7 回调注册数据一致性 | AC-5.1 | proposal AC-7 对应 spec AC-5.1 数据格式一致性 |
| AC-5 幂等性 | AC-6.1 | proposal AC-5 对应 spec AC-6.1 |
| AC-6 指针无效跳过 | AC-6.2 | proposal AC-6 对应 spec AC-6.2 |
| — | AC-6.3 | Spec 细化：PipelineContext 无回调时安全跳过（proposal 未单独列出） |

## 验收追溯

| AC | 关联规则 | 关联 Task | 验证方式 | 证据 |
|----|----------|-----------|----------|------|
| AC-1.1 | FR-1 | TASK-2 | UT + 设备验证 | UT: pipeline_context_test_ng_six.cpp; 设备: lifecycle_test.ets |
| AC-1b.1 | FR-1 | TASK-2 | UT + 设备验证 | UT: pipeline_context_test_ng_six.cpp; 设备: lifecycle_test.ets |
| AC-2.1 | FR-1 | TASK-2 | UT + 设备验证 | UT: pipeline_context_test_ng_six.cpp; 设备: lifecycle_test.ets |
| AC-3.1 | FR-1 | TASK-2 | UT + 设备验证 | UT: pipeline_context_test_ng_six.cpp; 设备: lifecycle_test.ets |
| AC-4.1 | FR-1 | TASK-2 | UT + 设备验证 | UT: pipeline_context_test_ng_six.cpp; 设备: lifecycle_test.ets |
| AC-5.1 | FR-2 | TASK-1 | 对比测试 | 4 参数 (WeakRef+className+nodeType+nodePtr) 与动态语言一致 |
| AC-6.1 | BR-1 | TASK-2 | UT | 各 dispose() 均有 isDisposed guard，review.md 确认 |
| AC-6.2 | BR-2 | TASK-2 | UT | 各实现均检查 nodePtr/frameNodePtr 非 0，review.md 确认 |
| AC-6.3 | EX-1 | TASK-1 | UT | PipelineContext::FireArkUIObjectLifecycleCallback 内 CHECK_NULL_VOID(objectLifecycleCallback_) |

## 业务规则

| 编号 | 规则描述 | 约束条件 | 关联 AC |
|------|----------|----------|---------|
| BR-1 | 回调仅在首次 dispose 时触发 | isDisposed() 为 true 时跳过 | AC-6.1 |
| BR-2 | 仅在节点指针有效时触发回调 | peer.ptr / nodePtr 不为 null/undefined | AC-6.2 |

## 功能规则

| 编号 | 规则描述 | 触发条件 | 作用对象 | 关联 AC |
|------|----------|----------|----------|---------|
| FR-1 | dispose 时通过 ANI Bridge 调用 PipelineContext::FireArkUIObjectLifecycleCallback | 节点 dispose() + 指针有效 | FrameNode(含TypedFrameNode), RenderNode, BuilderNode, ComponentContent | AC-1.1~4.1 |
| FR-2 | 传递给 PipelineContext 的数据包含节点弱引用和节点类型信息 | ANI Bridge 调用时 | PipelineContext | AC-5.1 |

## 异常/豁免规则

| 编号 | 异常码/枚举 | 规则描述 | 触发条件 | 超时阈值 | 处理结果 | 关联 AC |
|------|------------|----------|----------|----------|----------|---------|
| EX-1 | N/A | PipelineContext 无注册回调时安全跳过 | objectLifecycleCallback_ 为 nullptr | N/A | 静默忽略 | AC-6.3 |

## 验证映射

| 编号 | 对应规格项 | 验证方式 | 验证重点 |
|------|------------|----------|----------|
| VM-1 | FR-1, AC-1.1~4.1 | UT | PipelineContext::FireArkUIObjectLifecycleCallback 是否被调用 |
| VM-2 | FR-2, AC-5.1 | UT | 传递的数据是否包含正确的节点类型和弱引用 |
| VM-3 | BR-1, AC-6.1 | UT | 重复 dispose 不触发回调 |
| VM-4 | BR-2, AC-6.2 | UT | 指针无效时不触发回调 |
| VM-5 | FR-1, AC-1.1~4.1 | 设备验证 | 应用侧通过 dlsym + vtable 注册回调后，4 种节点 dispose 均触发回调（端到端验证） |

### 设备验证方案

NAPI 模块通过 dlsym + vtable 调用 `UIContext::RegisterArkUIObjectLifecycleCallback` 注册计数回调，ArkTS 页面创建节点并 dispose 后检查回调计数。验证步骤：

1. dlopen `libace_compatible.z.so`，dlsym 获取 `UIContext::Current()` 符号
2. 通过 vtable 读取 `RegisterArkUIObjectLifecycleCallback` 函数指针，注册计数回调
3. ArkTS 测试页面依次对 FrameNode、RenderNode、BuilderNode、ComponentContent 执行 new → dispose
4. 每次操作后检查回调计数是否递增

具体验证用例和代码见 `evidence/gates/gate-archive.md` 设备补验方案（含 NAPI 模块核心逻辑、ArkTS 测试页面核心逻辑和验证用例表）。

覆盖 AC: AC-1.1 (FrameNode), AC-2.1 (RenderNode), AC-3.1 (BuilderNode), AC-4.1 (ComponentContent)

## API 变更分析

无 Public/System API 变更。仅新增内部 ANI Bridge 函数。

### 新增 InnerApi

| API 名称 | 开放范围 | 入参概要 | 返回值 | 错误码范围 | 功能描述 | 关联 AC |
|----------|----------|----------|--------|------------|----------|---------|
| `_FireArkUIObjectLifecycleCallback` | InnerApi (ANI) | weakRef: WeakRef\<object\>, className: string, nodeType: string, nodePtr: long（加 ANI 隐式 env, cls） | void | N/A | ETS 层通知 C++ PipelineContext 节点生命周期事件 | AC-1.1~4.1 |

## 兼容性声明

- **已有 API 行为变更:** 否，纯新增内部调用
- **配置文件格式变更:** 否
- **数据存储格式变更:** 否
- **最低支持版本:** N/A
- **API 版本号策略:** 无新公开 API

## 架构约束

| 关键约束 | 约束说明 | 影响 AC |
|----------|----------|---------|
| ETS → C++ 单向调用 | ETS 通过 ANI Bridge 调用 C++，不反向依赖 | AC-1.1~4.1 |

## 全局特性影响

| 特性 | 适用？ | 结论 | 关联场景 |
|------|--------|------|----------|
| 无障碍 | 否 | N/A | N/A |
| 大字体 | 否 | N/A | N/A |
| 深色模式 | 否 | N/A | N/A |
| 多窗口/分屏 | 否 | N/A | N/A |
| 多用户 | 否 | N/A | N/A |

## 行为场景（Gherkin）

```gherkin
Feature: 静态语言命令式节点 JsLeakWatcher 内存上报

  Scenario: FrameNode 首次 dispose 触发回调
    Given 一个未 dispose 的静态语言 FrameNode 实例
    And peer.ptr 和 nodePtr 均有效
    When 调用 dispose()
    Then 通过 ANI Bridge 调用 PipelineContext::FireArkUIObjectLifecycleCallback
    And 传递的数据包含节点类型 "FrameNode"

  Scenario: TypedFrameNode 首次 dispose 触发回调
    Given 一个未 dispose 的静态语言 TypedFrameNode 实例（如 TextFrameNode）
    And peer.ptr 和 nodePtr 均有效
    When 调用 dispose()
    Then 通过 ANI Bridge 调用 PipelineContext::FireArkUIObjectLifecycleCallback
    And className 为 "FrameNode"，nodeType 为具体组件类型（如 "Text"）

  Scenario: RenderNode 首次 dispose 触发回调
    Given 一个未 dispose 的静态语言 RenderNode 实例
    And peer.ptr 和 nodePtr 均有效
    When 调用 dispose()
    Then 通过 ANI Bridge 调用 PipelineContext::FireArkUIObjectLifecycleCallback
    And 传递的数据包含节点类型 "RenderNode"

  Scenario: BuilderNode 首次 dispose 触发回调
    Given 一个未 dispose 的静态语言 BuilderNode 实例
    And peer.ptr 和 nodePtr 均有效
    When 调用 disposeNode()
    Then 通过 ANI Bridge 调用 PipelineContext::FireArkUIObjectLifecycleCallback
    And 传递的数据包含节点类型 "BuilderNode"

  Scenario: ComponentContent 首次 dispose 触发回调
    Given 一个未 dispose 的静态语言 ComponentContent 实例
    And peer.ptr 和 nodePtr 均有效
    When 调用 dispose()
    Then 通过 ANI Bridge 调用 PipelineContext::FireArkUIObjectLifecycleCallback
    And 传递的数据包含节点类型 "ComponentContent"

  Scenario: 已 dispose 节点不重复触发回调
    Given 一个已 dispose 的静态语言 FrameNode 实例
    When 再次调用 dispose()
    Then 不触发 PipelineContext::FireArkUIObjectLifecycleCallback

  Scenario: 节点指针无效时不触发回调
    Given 一个静态语言 FrameNode 实例
    And peer.ptr 或 nodePtr 为 null
    When 调用 dispose()
    Then 不触发 PipelineContext::FireArkUIObjectLifecycleCallback
```

## Spec 自审清单

- [x] 无"待定""TODO"等占位符（目标版本 TBD 为明确标记，非占位符）
- [x] 所有 AC 使用 WHEN/THEN 格式，可独立测试
- [x] 范围边界明确（做什么/不做什么清晰）
- [x] 无语义模糊表述
- [x] AC 与业务规则/异常规则交叉一致
