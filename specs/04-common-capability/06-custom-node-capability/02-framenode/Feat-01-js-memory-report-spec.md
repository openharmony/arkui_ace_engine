# FrameNode JS 内存上报（dispose 生命周期回调）

## 概述

| 属性 | 值 |
|------|-----|
| 特性名称 | FrameNode JS 内存上报 |
| 特性编号 | Feat-01 |
| 功能域 | 04-06-02 FrameNode |
| 优先级 | P1 |
| 状态 | Baselined |
| 来源 | FEAT-20260521-jsleak-watcher-static-nodes |

## 行为规格

FrameNode（含子类 TypedFrameNode）在静态语言路径下调用 dispose() 时，通过 ANI Bridge 调用 PipelineContext::FireArkUIObjectLifecycleCallback，通知 JsLeakWatcher。

### 验收标准

- **AC-1.1:** WHEN 静态语言 FrameNode 调用 dispose() 且 peer.ptr 和 nodePtr 均有效 THEN 通过 ANI Bridge 调用 PipelineContext::FireArkUIObjectLifecycleCallback，传递的数据包含节点类型 'FrameNode'
- **AC-1b.1:** WHEN 静态语言 TypedFrameNode（如 TextFrameNode）调用 dispose() 且 peer.ptr 和 nodePtr 均有效 THEN 通过 ANI Bridge 调用 PipelineContext::FireArkUIObjectLifecycleCallback，className 为 'FrameNode'，nodeType 为具体组件类型（如 'Text'）

### 实现路径

```
FrameNode.ets dispose()
  → ArkUIAniModule._FireArkUIObjectLifecycleCallback(
      new WeakRef<FrameNode>(this), 'FrameNode', this.getNodeType(), this.nodePtr_)
  → ANI Bridge common_module.cpp
  → Modifier Bridge common_ani_modifier.cpp (className 分发)
  → PipelineContext::FireArkUIObjectLifecycleCallback(data)
```

### 关键约束

- ETS → C++ 单向调用，不反向依赖
- 回调仅在首次 dispose 时触发（isDisposed() guard）
- 仅在 nodePtr 有效时触发

### Gherkin 场景

```gherkin
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
  And className 为 "FrameNode"，nodeType 为具体组件类型（如 "Text")
```
