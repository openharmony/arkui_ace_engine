# BuilderNode JS 内存上报（dispose 生命周期回调）

## 概述

| 属性 | 值 |
|------|-----|
| 特性名称 | BuilderNode JS 内存上报 |
| 特性编号 | Feat-01 |
| 功能域 | 04-06-04 BuilderNode |
| 优先级 | P1 |
| 状态 | Baselined |
| 来源 | FEAT-20260521-jsleak-watcher-static-nodes |

## 行为规格

BuilderNode 在静态语言路径下调用 disposeNode() 时，通过 ANI Bridge 调用 PipelineContext::FireArkUIObjectLifecycleCallback，通知 JsLeakWatcher。

### 验收标准

- **AC-3.1:** WHEN 静态语言 BuilderNode 调用 disposeNode() 且 nodePtr 有效 THEN 通过 ANI Bridge 调用 PipelineContext::FireArkUIObjectLifecycleCallback，传递的数据包含节点类型 'BuilderNode'

### 实现路径

```
BuilderNode.ets disposeNode()
  → ArkUIAniModule._FireArkUIObjectLifecycleCallback(
      new WeakRef<JSBuilderNode<T>>(this), 'BuilderNode', 'BuilderNode', this.__frameNode?.nodePtr_)
  → ANI Bridge common_module.cpp
  → Modifier Bridge common_ani_modifier.cpp
    → FrameNodePeer::GetFrameNodeByPeer → null 时降级到 GetMockFrameNodeByPeer
    → mockNode->GetContext() → PipelineContext
  → PipelineContext::FireArkUIObjectLifecycleCallback(data)
```

### 关键约束

- BuilderNode 通过内部 `__frameNode?.nodePtr_` 获取 FrameNode 指针
- Modifier 桥接层特殊处理：若 GetFrameNodeByPeer 返回空（BuilderNode 场景），降级到 GetMockFrameNodeByPeer 获取 mock 节点的 context

### Gherkin 场景

```gherkin
Scenario: BuilderNode 首次 dispose 触发回调
  Given 一个未 dispose 的静态语言 BuilderNode 实例
  And peer.ptr 和 nodePtr 均有效
  When 调用 disposeNode()
  Then 通过 ANI Bridge 调用 PipelineContext::FireArkUIObjectLifecycleCallback
  And 传递的数据包含节点类型 "BuilderNode"
```
