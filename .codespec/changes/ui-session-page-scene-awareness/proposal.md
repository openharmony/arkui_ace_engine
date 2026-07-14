# 需求文档

## Proposal

> This document records the Stage 1 Define deliverable for UISession page scene rule awareness.

## 一、原始需求

### 基本信息

| 字段 | 内容 |
|------|------|
| 需求ID | REQ-UISESSION-PAGE-SCENE-AWARENESS |
| 需求名称 | UISession 页面场景规则化感知能力 |
| 来源 | 用户需求 |
| 提出人 | 用户 |
| 目标发行版本 | TBD |
| 候选 Profile | arkui |
| 优先级 | TBD |
| 状态 | Baselined for Stage 1 |

### 原始描述

UISession 需要新增独立的页面场景规则化感知能力。系统 SA 通过 UISession 下发 `ruleJson`，宿主 ArkUI 按规则匹配场景并通过 UISession 上报给 SA；Web / UIExtension 提供宿主到控件的规则透传通路。

本能力与现有 `ContentChange` 和 `ComponentChange` 分离；场景由 SA 与 ArkUI 共同定义的一系列规则描述，不复用现有变化事件语义。

### 首批场景

首批场景为文本编辑类场景：

- 场景类型：`TEXT_EDITOR`
- 命中语义：当前 ArkUI 宿主页面内存在 2 个及以上文本输入类控件时，上报 `TEXT_EDITOR` 场景事件。
- 文本输入类控件范围：
  - ArkUI：`TextInput`、`TextArea`、`Search`、`RichEditor`
  - Web / UIExtension：规则注册、反注册、查询请求透传

### 初始范围

包含：

- 新增 UISession 页面场景规则注册、反注册、一次性查询和异步上报能力。
- 使用 `ruleJson` 描述场景规则，首版支持 `TEXT_EDITOR`。
- `ruleJson` 预留 `webRules` 字段；Web 来源启用时宿主将 `webRules` 原样透传给 Web 控件。
- 支持 ArkUI 宿主控件树场景匹配。
- Web / UIExtension 提供内部接口接收规则生命周期请求。
- 最终只由宿主 UISession 向 SA 上报。
- 上报命中节点的 `nodeId`、`nodeType`、`focusable`、`rect`，并带 `currentPageName`。

## 二、澄清记录

| 编号 | 问题 | 结论 | 状态 |
|------|------|------|------|
| Q-1 | 场景能力是否复用 ContentChange / ComponentChange | 不复用、不绑定，场景是全新定义 | 已澄清 |
| Q-2 | 规则如何表达 | 使用 `ruleJson` 描述规则集、规则、过滤、上报和策略 | 已澄清 |
| Q-3 | 首批场景是什么 | `TEXT_EDITOR`，两个及以上文本输入类控件命中 | 已澄清 |
| Q-4 | 是否统计不可获焦文本输入控件 | 由 `globalConfig.includeUnfocusableTextInput` 控制 | 已澄清 |
| Q-5 | 是否上报文本位置大小 | 由 `report.includeRect` 控制，节点上报包含 `rect` | 已澄清 |
| Q-6 | 是否上报控件可获焦状态 | 由 `report.includeFocusable` 控制，节点上报包含 `focusable` | 已澄清 |
| Q-7 | 是否带当前页面名 | 上报结果必须带 `currentPageName` | 已澄清 |
| Q-8 | Web / UIExtension 如何接入 | 宿主向内部控件透传规则注册、反注册和查询请求；Web 注册透传使用 `webRules` | 已澄清 |
| Q-9 | 上报如何区分来源 | ArkUI 宿主上报使用 `source.type=ARKUI`；Web/UIExtension 通过宿主透传接口接入 | 已澄清 |

## 三、需求基线

### 用户故事

#### US-1: SA 注册页面场景规则

作为系统 SA，我想通过 UISession 注册页面场景规则，以便 ArkUI 按规则识别页面场景。

验收标准：

- AC-1: WHEN SA 调用 `RegisterPageSceneRules(ruleJson)` 且 `ruleJson` 合法 THEN 宿主保存规则并返回成功。
- AC-2: WHEN 规则包含 `sourceConfig.web=true` 或规则级 `scope.includeWeb=true` 且 `webRules` 存在 THEN 宿主向页面内 Web 控件透传 `webRules`。
- AC-3: WHEN 规则包含 `sourceConfig.uiExtension=true` 或规则级 `scope.includeUIExtension=true` THEN 宿主向页面内 UIExtension 控件下发规则。

#### US-2: 首次注册后检测 TEXT_EDITOR 场景

作为系统 SA，我想在规则注册后立即知道当前页面是否命中文本编辑场景。

验收标准：

- AC-4: WHEN 规则 `policy.reportOnRegister=true` THEN 宿主在注册后扫描当前页面顶部控件树。
- AC-5: WHEN 当前页面文本输入类控件数量大于等于 `condition.threshold` THEN 宿主通过 UISession 上报 `TEXT_EDITOR`。
- AC-6: WHEN `scope.onlyVisible=true` THEN 不可见或屏幕范围外控件不参与计数。
- AC-7: WHEN `globalConfig.includeUnfocusableTextInput=false` THEN 不可获焦文本输入类控件不参与计数。

#### US-3: 文本输入类控件上下树后稳定检测

作为系统 SA，我想在文本输入类控件上下树后于页面稳定点收到新的场景结果。

验收标准：

- AC-8: WHEN 文本输入类控件上树 THEN 维护输入控件计数并在页面稳定点触发 `TEXT_EDITOR` 匹配。
- AC-9: WHEN 同一页面、同一规则、同一命中节点集合已上报且 `policy.deduplicate=true` THEN 不重复上报。

#### US-6: SA 反注册页面场景规则

作为系统 SA，我想反注册已注册的页面场景规则，以便停止后续场景检测并释放宿主保存的规则状态。

验收标准：

- AC-15: WHEN SA 调用 `UnregisterPageSceneRules(ruleSetId)` 且 `ruleSetId` 对应当前已注册规则 THEN 宿主清理该规则、待检测状态和去重状态并返回成功。
- AC-16: WHEN SA 调用 `UnregisterPageSceneRules(ruleSetId)` 且 `ruleSetId` 为空、不存在或不属于当前 SA THEN 宿主返回参数错误或未注册错误，不影响其他 SA 的规则。
- AC-17: WHEN 反注册成功后页面文本输入类控件继续变化 THEN 宿主不得再因该规则上报 PageScene 事件。

#### US-4: Web / UIExtension 规则透传

作为系统 SA，我想让宿主把规则生命周期请求透传给 Web / UIExtension 控件。

验收标准：

- AC-10: WHEN 规则允许 Web 来源参与 THEN 宿主向 Web 控件透传规则注册、反注册和查询请求。
- AC-11: WHEN 规则允许 UIExtension 来源参与 THEN 宿主向 UIExtension 控件透传规则注册、反注册和查询请求。

#### US-5: 上报结果脱敏

作为终端用户，我希望场景感知不会默认泄露输入内容。

验收标准：

- AC-12: WHEN `report.includeText=false` THEN 上报结果不得包含文本内容。
- AC-13: WHEN `report.includeRect=true` THEN 命中节点包含 `rect`。
- AC-14: WHEN `report.includeFocusable=true` THEN 命中节点包含 `focusable`。

## 四、Stage 1 结论

Define 阶段通过。允许进入 Stage 2：规格化与设计。
