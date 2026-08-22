# 无障碍自定义 Action 动态刷新失效 Issue Context

> 文档版本：v1.0
> 更新时间：2026-08-07
> 来源：`docs/context_registry.json` 主题 `AccessibilityCustomActionsStale`
> 关联功能域：04-03-09（通用无障碍属性）、03-07-01（无障碍能力）

## 问题概述

动态声明式前端更新组件的 `accessibilityCustomActions` 后，自定义 Action 列表可能在多次状态切换或节点滚动复用后停止刷新。应用侧已提供新 Action，但 Modifier 可能不下发变更，或者 Native 属性已更新却未通知无障碍服务重新获取元素信息。

典型表现：
- 列表项的自定义 Action 首次设置有效，多次切换后仍显示或执行旧 Action。
- 滚动列表、复用节点或反复修改 Action 后问题更容易出现。
- 普通界面状态已经更新，但辅助技术侧获取的 Action 列表没有同步变化。

> 覆盖范围说明：当前仅覆盖动态声明式前端 `AccessibilityCustomActionsModifier` 的差异提交，以及 `AccessibilityProperty::SetAccessibilityCustomActions` 的元素信息变更通知。静态 ArkTS 前端、Reset 路径及其他无障碍属性的刷新问题不在本页范围。

## 关联模块

| kind | role | name | evidence | confidence |
|------|------|------|----------|------------|
| component | symptom_surface | 通用 ArkUI 组件的 `accessibilityCustomActions` 属性 | Issue #78769 的公开问题描述及当前属性写入入口 | verified |
| capability | trigger | 动态属性 Modifier 差异提交 | `ArkComponent.ts` 中 `AccessibilityCustomActionsModifier::applyStage` | verified |
| architecture | root_cause_owner | 动态声明式前端 Modifier 状态快照与差异判断 | PR #84494、PR #87269 及当前源码 | verified |
| capability | root_cause_owner | `AccessibilityProperty` 属性存储与事件通知 | `AccessibilityProperty::SetAccessibilityCustomActions` | verified |
| architecture | fix_location | 无障碍元素信息变更事件链 | `NotifyComponentChangeEvent`、`JsAccessibilityManager::FireAccessibilityEventCallback` | verified |

## 根因分类

| 根因类别 | 触发条件 | 典型场景 |
|----------|----------|----------|
| A. Modifier 状态快照与差异语义错误 | Action 数组或其中对象被动态修改；旧实现未保存独立快照，且 `checkObjectDiff` 的返回语义和比较字段不正确 | 列表项在多个 Action 状态间切换，节点复用后 Modifier 判断无需下发 |
| B. Native 属性更新后缺少元素信息变更通知 | 新 Action 已写入 `AccessibilityProperty`，但没有触发 `ELEMENT_INFO_CHANGE` | 辅助技术仍使用此前缓存的元素 Action 信息 |

## 排查路径

### 快速判断

1. 确认普通界面状态已经变化，但辅助技术侧的 Action 名称或回调仍为旧值。
2. 在 `AccessibilityCustomActionsModifier::applyStage` 检查本次更新是否执行 `applyPeer`。
3. 检查 `value` 与 `stageValue` 是否为独立快照，并确认差异判断比较 `name` 和 `onAction`。
4. 在 `AccessibilityProperty::SetAccessibilityCustomActions` 检查新 Action 是否成功写入。
5. 确认写入后是否产生 `ON_SEND_ELEMENT_INFO_CHANGE`，并由 `JsAccessibilityManager` 转换为 `ELEMENT_INFO_CHANGE`。

### 详细排查

#### A. Modifier 状态快照与差异语义错误

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 在 `AccessibilityCustomActionsModifier::applyStage` 检查 `stageValue` | 包含本次设置的最新 Action 列表 | 若仍是旧值，继续排查应用状态更新 |
| 2 | 比较 `value` 与 `stageValue` 的对象引用 | `value` 是上次提交值的独立逐元素副本 | 若引用相同，原对象的原地修改可能同时污染新旧状态 |
| 3 | 检查 `checkObjectDiff` 的字段 | 比较 API 实际使用的 `name` 和 `onAction` | 若比较 `actionName` 等非输入字段，差异结果不可信 |
| 4 | 检查差异返回语义 | 长度、名称或回调不同返回 `true`；完全相同返回 `false` | 若语义相反，实际变化不会调用 `applyPeer` |
| 5 | 检查 `applyPeer` | 差异存在时调用 `setAccessibilityCustomActions` | 若未调用，继续检查 `_needDiff` 和 Modifier 生命周期 |

关键代码定位：
- `frameworks/bridge/declarative_frontend/ark_component/src/ArkComponent.ts`，`ModifierWithKey::applyStage`：通用 Modifier 提交语义。
- `frameworks/bridge/declarative_frontend/ark_component/src/ArkComponent.ts`，`AccessibilityCustomActionsModifier::applyStage`：保存逐元素副本并决定是否下发。
- `frameworks/bridge/declarative_frontend/ark_component/src/ArkComponent.ts`，`AccessibilityCustomActionsModifier::checkObjectDiff`：比较 `name` 和 `onAction`。
- `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.cpp`，`CommonBridge::SetAccessibilityCustomActions`：解析 `name` 和 `onAction`。

#### B. Native 属性更新后缺少元素信息变更通知

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 检查 `CommonBridge::SetAccessibilityCustomActions` 的解析结果 | 有效 Action 被传给 `ViewAbstractModelNG` | 若为空，检查名称和回调是否合法 |
| 2 | 检查 `ViewAbstractModelNG::SetAccessibilityCustomActions` | 调用节点的 `AccessibilityProperty` Setter | 若未调用，检查 FrameNode 和属性对象 |
| 3 | 检查 `AccessibilityProperty` 内部列表 | 已替换为最新 Action 集合 | 若仍是旧值，排查 Setter 调用或输入转换 |
| 4 | 检查 Setter 末尾 | 调用 `NotifyComponentChangeEvent(ELEMENT_INFO_CHANGE)` | 若缺少通知，辅助技术可能继续使用缓存 |
| 5 | 检查 Pipeline 与 Manager 事件链 | `ON_SEND_ELEMENT_INFO_CHANGE` 转换并发送为 `ELEMENT_INFO_CHANGE` | 若未发送，检查无障碍启用状态及 Pipeline 上下文 |

关键代码定位：
- `frameworks/core/components_ng/base/view_abstract_model_ng.cpp`，`ViewAbstractModelNG::SetAccessibilityCustomActions`。
- `frameworks/core/components_ng/property/accessibility_property.cpp`，`AccessibilityProperty::SetAccessibilityCustomActions`。
- `frameworks/core/components_ng/property/accessibility_property.cpp`，`AccessibilityProperty::NotifyComponentChangeEvent`。
- `adapter/ohos/osal/js_accessibility_manager.cpp`，`JsAccessibilityManager::FireAccessibilityEventCallback`。

## 修复方案

| 根因类别 | 修复策略 | 关键代码改动点 | 修复/缓解变更 | 关系证据 |
|----------|----------|---------------|---------------|----------|
| A. Modifier 状态快照与差异语义错误 | 重写 `applyStage`，对 Action 数组逐元素复制以保存独立快照；修正差异返回语义，并比较实际输入字段 `name/onAction` | `ArkComponent.ts` 中 `AccessibilityCustomActionsModifier` | [PR #87269](https://gitcode.com/openharmony/arkui_ace_engine/merge_requests/87269) (`fixed`) | PR diff、当前源码及 `git blame` 均指向对应修复 |
| B. Native 属性更新后缺少通知 | Action 列表写入完成后发送 `ELEMENT_INFO_CHANGE` | `accessibility_property.cpp` 中 `SetAccessibilityCustomActions` | [PR #87269](https://gitcode.com/openharmony/arkui_ace_engine/merge_requests/87269) (`fixed`) | PR diff 增加 `NotifyComponentChangeEvent`，当前通知链可定位 |
| 发布分支同步 | 将相同修复回合至 OpenHarmony 7.0 发布分支 | 同上 | [PR #87370](https://gitcode.com/openharmony/arkui_ace_engine/merge_requests/87370) (`follow_up`) | GitCode PR 和合并历史显示其为 PR #87269 的 cherry-pick |

## 关联变更

| 变更编号 | 变更简述 | 根因类别 | 变更关系 | 证据 | 确信度 |
|----------|----------|----------|----------|------|--------|
| CHG-01 | 初始 Native 自定义 Action Setter 只写入属性，没有发送元素信息变更事件 | B | introduced | [PR #84197](https://gitcode.com/openharmony/arkui_ace_engine/merge_requests/84197)、提交 `bb73410b576` 的新增代码 | verified |
| CHG-02 | 动态 Modifier 初始实现未保存独立状态快照，且差异判断的返回语义和字段存在错误 | A | introduced | [PR #84494](https://gitcode.com/openharmony/arkui_ace_engine/merge_requests/84494)、提交 `eda99ac49341` 的初始实现 | verified |
| CHG-03 | [Issue #78769](https://gitcode.com/openharmony/arkui_ace_engine/issues/78769) 记录自定义 Action 动态刷新失效及两条根因 | A、B | related | 公开 Issue 描述与源码、修复 diff 一致 | verified |
| CHG-04 | 修复 Modifier 差异提交和 Native 通知，并补充 Setter 测试 | A、B | fixed | [PR #87269](https://gitcode.com/openharmony/arkui_ace_engine/merge_requests/87269)、提交 `3fc6e850c0d` 及当前源码 | verified |
| CHG-05 | 将修复回合到 OpenHarmony 7.0 发布分支 | A、B | follow_up | [PR #87370](https://gitcode.com/openharmony/arkui_ace_engine/merge_requests/87370)、合并提交 `ff991ed5dce` | verified |
| CHG-06 | 通知事件单测因本地失败被回退，当前树仅保留四个 Setter 行为测试 | B 的测试覆盖 | related | 提交 `3abd85b8f25` 及当前测试文件 | verified |

## 预防措施

- 对数组或对象类型 Modifier 保存独立的上次提交快照，不能直接令 `value` 与 `stageValue` 引用同一可变对象。
- `checkObjectDiff` 必须遵守“存在差异返回 `true`”的统一约定，并比较 API 实际使用的字段。
- 修改无障碍可观察属性时，评估是否需要发送 `ELEMENT_INFO_CHANGE`，避免只更新引擎内存而不刷新辅助技术缓存。
- 增加稳定的 Modifier 动态更新测试，覆盖名称变化、回调变化、数组长度变化和对象原地修改。
- 重新补充可稳定运行的通知事件回归测试；当前源码存在通知逻辑，但对应直接单测已被回退。
- 单独验证 `ResetAccessibilityCustomActions` 是否需要发送刷新通知，本页不推断其当前行为是否符合产品要求。

## 相关主题

- [docs/kb/architecture/accessibility.md](../../architecture/accessibility.md) — 通用无障碍属性，FuncID `04-03-09`
- [docs/kb/architecture/accessibility.md](../../architecture/accessibility.md) — 无障碍能力与事件桥接，FuncID `03-07-01`
- [docs/kb/capabilities/attribute-modifier.md](../../capabilities/attribute-modifier.md) — 动态属性 Modifier 通路