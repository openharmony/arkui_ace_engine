# ComponentContent JS 内存上报（dispose 生命周期回调）

## 概述

| 属性 | 值 |
|------|-----|
| 特性名称 | ComponentContent JS 内存上报 |
| 特性编号 | Feat-01 |
| 功能域 | 04-06-05 ComponentContent |
| 优先级 | P1 |
| 状态 | Baselined |
| 来源 | FEAT-20260521-jsleak-watcher-static-nodes |

## 行为规格

ComponentContent 在静态语言路径下调用 dispose() 时，通过 ANI Bridge 调用 PipelineContext::FireArkUIObjectLifecycleCallback，通知 JsLeakWatcher。

### 验收标准

- **AC-4.1:** WHEN 静态语言 ComponentContent 调用 dispose() 且 nodePtr 有效 THEN 通过 ANI Bridge 调用 PipelineContext::FireArkUIObjectLifecycleCallback，传递的数据包含节点类型 'ComponentContent'

### 实现路径

```
ComponentContent.ets dispose()
  → ArkUIAniModule._FireArkUIObjectLifecycleCallback(
      new WeakRef<ComponentContent<T>>(this), 'ComponentContent', 'ComponentContent',
      this.builderNode_?.getFrameNodeWithoutCheck()?.nodePtr_)
  → ANI Bridge common_module.cpp
  → Modifier Bridge common_ani_modifier.cpp
  → PipelineContext::FireArkUIObjectLifecycleCallback(data)
```

### 关键约束

- ComponentContent 通过内部 builderNode 的 getFrameNodeWithoutCheck() 获取 FrameNode 的 nodePtr
- 回调在 isDisposed_ = true 和 detachFromParent() 之前触发

### Gherkin 场景

```gherkin
Scenario: ComponentContent 首次 dispose 触发回调
  Given 一个未 dispose 的静态语言 ComponentContent 实例
  And peer.ptr 和 nodePtr 均有效
  When 调用 dispose()
  Then 通过 ANI Bridge 调用 PipelineContext::FireArkUIObjectLifecycleCallback
  And 传递的数据包含节点类型 "ComponentContent"
```
