# RenderNode JS 内存上报（dispose 生命周期回调）

## 概述

| 属性 | 值 |
|------|-----|
| 特性名称 | RenderNode JS 内存上报 |
| 特性编号 | Feat-01 |
| 功能域 | 04-06-03 RenderNode |
| 优先级 | P1 |
| 状态 | Baselined |
| 来源 | FEAT-20260521-jsleak-watcher-static-nodes |

## 行为规格

RenderNode 在静态语言路径下调用 dispose() 时，通过 ANI Bridge 调用 PipelineContext::FireArkUIObjectLifecycleCallback，通知 JsLeakWatcher。

### 验收标准

- **AC-2.1:** WHEN 静态语言 RenderNode 调用 dispose() 且 nodePtr 有效 THEN 通过 ANI Bridge 调用 PipelineContext::FireArkUIObjectLifecycleCallback，传递的数据包含节点类型 'RenderNode'

### 实现路径

```
RenderNode.ets dispose()
  → ArkUIAniModule._FireArkUIObjectLifecycleCallback(
      new WeakRef<RenderNode>(this), 'RenderNode', 'RenderNode', frameNodePtr)
  → ANI Bridge common_module.cpp
  → Modifier Bridge common_ani_modifier.cpp (className=="RenderNode" → RenderNodePeer::GetFrameNode)
  → PipelineContext::FireArkUIObjectLifecycleCallback(data)
```

### 关键约束

- RenderNode 的 nodePtr 实际指向关联的 FrameNode 的 nodePtr（通过 `this.frameNode_?.deref()?.nodePtr_` 获取）
- Modifier 桥接层通过 className 判断使用 RenderNodePeer 路径获取 FrameNode

### Gherkin 场景

```gherkin
Scenario: RenderNode 首次 dispose 触发回调
  Given 一个未 dispose 的静态语言 RenderNode 实例
  And peer.ptr 和 nodePtr 均有效
  When 调用 dispose()
  Then 通过 ANI Bridge 调用 PipelineContext::FireArkUIObjectLifecycleCallback
  And 传递的数据包含节点类型 "RenderNode"
```
