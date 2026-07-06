# UISession 页面场景规则化感知能力 — 测试设计规格

> ArkUI 测试设计规格 | 模板参考: sdd-spec-optimization/spec-for-test-suggested.md
>
> 本文档为测试用例设计的自包含输入件。需求目标、AC、规则、API 等内容来自 `spec.md`，标注 `[源: spec.md]`；测试维度、测试数据和验证方式在本文档中展开。

## 元信息

| 字段 | 内容 |
|------|------|
| 需求编号 | REQ-UISESSION-PAGE-SCENE-AWARENESS |
| 需求名称 | UISession 页面场景规则化感知能力 |
| 特性编号 | FEAT-UISESSION-PAGE-SCENE-AWARENESS |
| 需求来源 | 内部/系统 SA 场景感知需求 |
| 提出人 | 用户 |
| 优先级 | P0 |
| 目标版本 | TBD |
| SIG归属 | SIG_ArkUI |
| 状态 | Draft |
| 复杂度 | 标准 + 安全/DFX专项 |
| 创建日期 | 2026-06-18 |
| 最后更新 | 2026-07-06 |

## 一、需求目标与规格 `[源: spec.md]`

UISession 新增独立的页面场景规则化感知能力。系统 SA 通过 UISession 下发 `ruleJson`，宿主 ArkUI 按规则匹配场景并统一上报给 SA；Web / UIExtension 当前只做宿主到控件的规则透传通路，不做子来源内部匹配、回传和验证。本能力不复用、不绑定 `ContentChange` / `ComponentChange` 事件语义，但 PageScene 检测时机复用 `ContentChangeManager` 的页面级稳定点。

首批场景：

- `sceneType`: `TEXT_EDITOR`
- 命中规则：当前页面或子内容源内存在 2 个及以上文本输入类控件。
- ArkUI 文本输入类控件：`TextInput`、`TextArea`、`Search`、`RichEditor`
- Web / UIExtension：首版只要求规则注册、反注册、查询请求透传，不要求内部匹配和上报

### 1.1 US-1：SA 注册页面场景规则

| AC编号 | 验收标准 | 类型 |
|--------|----------|------|
| AC-1.1 | GIVEN SA 已通过 UISession 连接宿主应用，WHEN SA 调用 `RegisterPageSceneRules(ruleJson, eventCallback)` 且 `ruleJson` 合法、`eventCallback` 非空、当前 SA 无未注销页面场景规则，THEN 宿主保存规则并返回成功，后续命中结果通过回调返回 | 正常 |
| AC-1.2 | GIVEN SA 已连接宿主应用，WHEN `ruleJson` 非法或 `eventCallback` 为空，THEN 接口返回参数错误，不保存规则，不触发匹配 | 异常 |
| AC-1.3 | GIVEN 同一 SA 已成功注册页面场景规则且未调用 `UnregisterPageSceneRules`，WHEN 再次调用 `RegisterPageSceneRules` 注册新规则，THEN 接口返回重复注册错误，不覆盖已有规则，不触发子来源下发 | 异常 |
| AC-1.4 | GIVEN 合法规则允许 Web 来源参与且 `ruleJson.webRules` 存在，WHEN 注册成功，THEN 宿主向页面内 Web 控件透传 `webRules`；宿主不解析 `webRules` 内部规格 | 正常 |
| AC-1.5 | GIVEN 合法规则允许 UIExtension 来源参与，WHEN 注册成功，THEN 宿主向页面内 UIExtension 控件下发原始 `ruleJson` | 正常 |

### 1.2 US-2：首次注册后检测 TEXT_EDITOR 场景

| AC编号 | 验收标准 | 类型 |
|--------|----------|------|
| AC-2.1 | GIVEN 规则中 `policy.reportOnRegister=true`，WHEN `RegisterPageSceneRules` 注册成功，THEN 宿主立即扫描当前页面顶部控件树并执行 `TEXT_EDITOR` 匹配 | 正常 |
| AC-2.2 | GIVEN 当前页面顶部控件树中命中文本输入类控件数量大于等于 `condition.threshold`，WHEN 执行 `TEXT_EDITOR` 匹配，THEN 宿主通过 `ReportPageSceneEvent` 上报 `TEXT_EDITOR` 场景结果 | 正常 |
| AC-2.3 | GIVEN `scope.onlyVisible=true`，WHEN 执行 `TEXT_EDITOR` 匹配，THEN 不可见或屏幕范围外控件不参与计数 | 边界 |
| AC-2.4 | GIVEN `globalConfig.includeUnfocusableTextInput=false`，WHEN 执行 `TEXT_EDITOR` 匹配，THEN 不可获焦文本输入类控件不参与计数 | 边界 |

### 1.3 US-3：文本输入类控件上下树后稳定检测

| AC编号 | 验收标准 | 类型 |
|--------|----------|------|
| AC-3.1 | GIVEN 已注册 `TEXT_EDITOR` 规则且 `policy.reportOnTextInputAttached=true`，WHEN 文本输入类控件上树且满足可见性/可获焦规则，THEN 宿主将该控件加入页面输入控件计数并挂起待检测规则；不得仅因数量达到阈值立即上报 | 正常 |
| AC-3.2 | GIVEN `policy.deduplicate=true` 且同一页面、同一规则、同一命中节点集合已上报，WHEN 再次触发匹配且命中集合未变化，THEN 不重复上报 | 边界 |
| AC-3.3 | GIVEN 已注册 `TEXT_EDITOR` 规则，WHEN 命中节点集合变化或当前页面名变化且页面已稳定，THEN 可以重新上报新的命中结果 | 正常 |
| AC-3.4 | GIVEN 已注册 `TEXT_EDITOR` 规则且页面内已计数某个文本输入类控件，WHEN 该控件下树，THEN 宿主从页面输入控件计数中移除该控件；若数量低于阈值，首版不补发未命中事件 | 边界 |

### 1.4 US-4：SA 主动查询当前页面场景

| AC编号 | 验收标准 | 类型 |
|--------|----------|------|
| AC-4.1 | GIVEN SA 已连接宿主应用，WHEN SA 调用 `GetPageScene(ruleJsonOrRuleSetId, eventCallback)` 且参数合法、`eventCallback` 非空、当前 SA 无未完成 `GetPageScene` 请求，THEN 宿主执行一次匹配并通过回调返回本次结果 | 正常 |
| AC-4.2 | GIVEN 主动查询规则允许 Web 或 UIExtension 来源参与，WHEN SA 调用 `GetPageScene`，THEN 宿主可通过 `GetPageSceneForSubSource` 向对应控件透传查询请求；当前不等待、不验证子来源匹配结果 | 正常 |
| AC-4.3 | GIVEN `GetPageScene` 参数非法或 `eventCallback` 为空，WHEN SA 发起主动查询，THEN 接口返回参数错误，不触发匹配 | 异常 |
| AC-4.4 | GIVEN 同一 SA 已有 `GetPageScene` 请求尚未返回结果，WHEN 再次调用 `GetPageScene`，THEN 接口返回请求忙错误，不启动新的扫描或子来源查询 | 异常 |

### 1.5 US-5：Web / UIExtension 规则透传边界

| AC编号 | 验收标准 | 类型 |
|--------|----------|------|
| AC-5.1 | GIVEN 合法规则允许 Web 来源参与且 `ruleJson.webRules` 存在，WHEN 注册规则成功，THEN 宿主向页面内 Web 控件透传 `webRules` | 正常 |
| AC-5.2 | GIVEN 合法规则允许 UIExtension 来源参与，WHEN 注册规则成功，THEN 宿主向页面内 UIExtension 控件透传原始 `ruleJson` | 正常 |
| AC-5.3 | GIVEN 已向 Web 或 UIExtension 透传过规则，WHEN SA 调用 `UnregisterPageSceneRules(ruleSetId)` 或 SA 死亡，THEN 宿主向对应控件透传反注册请求 | 恢复 |
| AC-5.4 | GIVEN SA 调用 `GetPageScene` 且规则允许 Web 或 UIExtension 来源参与，WHEN 宿主发起当前页面查询，THEN 宿主向对应控件透传查询请求；当前不要求子来源返回结果 | 边界 |
| AC-5.5 | GIVEN Web 或 UIExtension 接收到规则透传，WHEN 子来源内部存在可匹配控件，THEN 本特性不要求 Web/UIExtension 完成内部匹配、上报回传或端到端验证 | 边界 |

### 1.6 US-6：上报结果脱敏

| AC编号 | 验收标准 | 类型 |
|--------|----------|------|
| AC-6.1 | GIVEN 规则中 `report.includeText=false`，WHEN 上报 `TEXT_EDITOR` 场景结果，THEN 上报结果不得包含输入文本正文 | 安全 |
| AC-6.2 | GIVEN 规则中 `report.includeText=true`，WHEN 上报 `TEXT_EDITOR` 场景结果，THEN 每个命中文本输入类控件在 `nodes[]` 中携带 `text` 字段，字段值优先为用户已输入文本，输入为空时为框内占位提示文本 | 正常 |
| AC-6.3 | GIVEN 规则中 `report.includeRect=true`，WHEN 上报命中节点，THEN 每个命中节点包含 `rect.x`、`rect.y`、`rect.width`、`rect.height` | 正常 |
| AC-6.4 | GIVEN 规则中 `report.includeFocusable=true`，WHEN 上报命中节点，THEN 每个命中节点包含 `focusable` 字段 | 正常 |
| AC-6.5 | GIVEN 本阶段规则配置和上报规格，WHEN 解析 `ruleJson` 或构造上报结果，THEN 不设计、不输出完整控件树字段 | 安全 |

### 1.7 US-7：页面稳定点触发 PageScene 检测

| AC编号 | 验收标准 | 类型 |
|--------|----------|------|
| AC-7.1 | GIVEN 仅注册了 PageScene、未注册 ContentChange，WHEN 页面切换结束、滚动结束、Swiper/Tabs 切换结束或弹窗显示隐藏结束，THEN 宿主仍应触发 PageScene 待检测规则检查；不得上报 ContentChange 事件 | 正常 |
| AC-7.2 | GIVEN 文本输入类控件上下树后存在待检测规则，WHEN 当前仍处于普通滚动、Swiper 滚动或页面转场中，THEN 不触发 PageScene 上报，等待后续稳定点或 VSync 末尾再检查 | 边界 |
| AC-7.3 | GIVEN 仅注册了 PageScene、未注册 ContentChange，WHEN 只发生 Text/Image 具体控件 ContentChange 事件，THEN 不以这些具体控件事件作为 PageScene-only 检测入口 | 边界 |
| AC-7.4 | GIVEN Pipeline 执行 VSync 尾部逻辑，WHEN 需要处理 PageScene 待检测规则，THEN Pipeline 只调用 `ContentChangeManager::OnVsyncEnd`；PageScene 规则判断和 `FlushPageSceneNodeChanged` 封装在 ContentChangeManager / UiSessionManager 内部 | 架构 |

### 1.8 US-8：DFX 防并发与生命周期约束

| AC编号 | 验收标准 | 类型 |
|--------|----------|------|
| AC-8.1 | GIVEN 同一 SA 已注册规则未注销，WHEN 继续注册任何新规则，THEN 返回重复注册错误，已有规则保持有效 | 异常 |
| AC-8.2 | GIVEN 同一 SA 有 `GetPageScene` 请求未完成，WHEN 再次发起 `GetPageScene`，THEN 返回请求忙错误，不触发新扫描 | 异常 |
| AC-8.3 | GIVEN `UnregisterPageSceneRules(ruleSetId)` 正在执行，WHEN 同一 SA 并发注册或查询同一 `ruleSetId`，THEN 后进入的请求返回请求忙错误或等待前序操作完成后按最新状态处理；实现必须保证状态不交叉污染 | 恢复 |
| AC-8.4 | GIVEN SA 进程死亡或 UISession 连接断开，WHEN 宿主检测到死亡，THEN 清理该 SA 的规则、待返回 Get 状态、去重缓存和子来源下发状态 | 恢复 |

## 二、规则定义 `[源: spec.md]`

| 规则ID | 类型 | 触发条件 | 预期行为 | 边界/约束 | 关联AC | 验证方式 | 测试数据 | 优先级 |
|--------|------|----------|----------|-----------|--------|----------|----------|--------|
| R-1 | 行为 | 首次合法注册 | 保存规则并建立回调路由 | 单 SA 单注册态 | AC-1.1 | 单测/sample | 合法 `TEXT_EDITOR` ruleJson | P0 |
| R-2 | 异常 | `ruleJson` 非法、回调为空或未连接 `ReportService` | 返回错误，不保存规则 | 不触发扫描和下发 | AC-1.2 | 单测 | 空串、非 JSON、缺少 `ruleSetId`、空 callback、未 Connect | P0 |
| R-3 | 异常 | 已注册未注销时再次注册 | 返回重复注册错误，不覆盖旧规则 | 防重复注册 | AC-1.3, AC-8.1 | 单测/并发测试 | ruleA 注册成功后注册 ruleB | P0 |
| R-4 | 行为 | `reportOnRegister=true` 且注册成功 | 扫描当前页面顶部控件树，初始化页面可见输入控件计数 | 只采集规则所需字段 | AC-2.1 | 集成测试 | 注册后立即检查 tracker 计数和回调 | P0 |
| R-5 | 行为 | 页面内符合规则的可见输入节点数量 >= 2 | 上报 `TEXT_EDITOR` | `COUNT_GTE` 阈值为 2 | AC-2.2 | 单测/集成 | 0/1/2/3 个文本输入控件 | P0 |
| R-6 | 边界 | `onlyVisible=true` | 不可见/屏外控件不计数 | 空 rect 或无交集过滤 | AC-2.3 | 单测 | visible/hidden/offscreen 三类节点 | P0 |
| R-7 | 边界 | `includeUnfocusableTextInput=false` | 不可获焦控件不计数 | 默认 false | AC-2.4 | 单测 | focusable=true/false | P0 |
| R-8 | 行为 | 文本输入类控件上树 | 按规则加入页面输入控件计数，并挂起对应规则待检测任务 | 不因达到阈值立即上报 | AC-3.1 | 单测/集成测试 | 动态添加 TextInput/TextArea/Search/RichEditor，确认未稳定前不回调 | P0 |
| R-9 | 边界 | 重复命中集合 | 不重复上报 | 页面名、规则、来源、节点集合构成签名 | AC-3.2 | 单测 | 连续相同节点集合触发 3 次 | P0 |
| R-10 | 行为 | 命中集合或页面名变化 | 页面稳定后允许重新上报 | 满足最小间隔 | AC-3.3 | 集成测试 | 增加一个输入框、切换页面名，再触发稳定点 | P1 |
| R-10A | 边界 | 已计数文本输入类控件下树 | 从页面输入控件计数中移除；数量低于阈值时不上报未命中 | 防止销毁节点继续贡献计数 | AC-3.4 | 单测/集成 | 2 个输入框命中后移除 1 个 | P0 |
| R-11 | 行为 | 合法 Get 且无 pending 请求 | 返回本次匹配结果 | 一次性规则不长期保存 | AC-4.1 | 单测/sample | `ruleSetId` 查询、临时 ruleJson 查询 | P0 |
| R-12 | 异常 | Get 未返回时再次 Get | 返回 busy，不启动新扫描 | 防并发查询 | AC-4.4, AC-8.2 | 并发测试 | 两次连续 Get，首个回调延迟 | P0 |
| R-13 | 行为 | 规则允许 Web 来源且 `webRules` 存在 | 宿主向 Web 控件透传 `webRules` 及反注册/查询请求 | `webRules` 内部规格不在本特性设计；不要求 Web 内部匹配和回传 | AC-1.4, AC-4.2, AC-5.1, AC-5.3, AC-5.4, AC-5.5 | mock/单测 | Web enabled/disabled、webRules 原样透传、register/unregister/get | P1 |
| R-14 | 行为 | 规则允许 UIExtension 来源 | 宿主向 UIExtension 控件透传注册、反注册或查询请求 | 不要求 UIExtension 内部匹配和回传 | AC-1.5, AC-4.2, AC-5.2, AC-5.3, AC-5.4, AC-5.5 | mock/单测 | UIExtension enabled/disabled、register/unregister/get | P2 |
| R-15 | 边界 | Web / UIExtension 控件不存在或透传失败 | 记录来源级摘要错误，不影响 ArkUI 宿主匹配 | 不做子来源端到端验证 | AC-5.5 | mock | no web/uie、透传失败 | P2 |
| R-16 | 边界 | `includeText=false` | ArkUI 宿主来源不上报文本正文 | 日志也不得打印正文 | AC-6.1 | 单测/日志检查 | 输入框含敏感文本 `password123` | P0 |
| R-16A | 行为 | `includeText=true` | ArkUI 宿主来源在命中节点 `nodes[]` 中上报 `text` 字段，优先为用户已输入文本，输入为空时为框内占位提示文本 | 日志仍只打印摘要；sample 通过 `-tofile` 保存完整结果用于验证 | AC-6.2 | 单测/sample | 输入框固定文本 `account/password` 和占位提示 `input account` | P0 |
| R-16B | 边界 | 本阶段规则和上报规格 | 不设计、不上报完整控件树，也不提供完整树上报开关 | 防止完整树透出 | AC-6.5 | JSON 检查 | ruleJson/report JSON | P0 |
| R-17 | 行为 | `includeRect=true` / `includeFocusable=true` | ArkUI 宿主来源节点包含 rect/focusable | rect 四字段完整 | AC-6.3, AC-6.4 | 单测 | include 开关 true/false | P0 |
| R-18 | 恢复 | 反注册、SA 死亡或断连 | 清理所有该 SA 状态 | 不影响其他 SA | AC-8.3, AC-8.4 | 单测/死亡监听测试 | unregister、remote death、disconnect | P0 |
| R-19 | 行为 | PageScene 已注册且页面级稳定点到达 | `ContentChangeManager` 检查并 flush PageScene 待检测规则 | PageScene-only 时不得发送 ContentChange 事件 | AC-7.1 | 单测 | Page/Scroll/Dialog 稳定点，PageScene-only 注册 | P0 |
| R-20 | 边界 | 存在待检测规则但页面仍滚动、Swiper 滚动或转场 | 暂不 flush，稳定后再检测 | 防中间态上报 | AC-7.2 | 单测 | OnVsyncEnd 时 scrolling/swiperScrolling/transitioning 为 true | P0 |
| R-21 | 架构 | Pipeline VSync 尾部 | 只调用 `ContentChangeManager::OnVsyncEnd(rootRect)` | Pipeline 不直接调用 UiSessionManager PageScene flush | AC-7.4 | 代码检查 | `pipeline_context.cpp` 无 `FlushPageSceneNodeChanged` 调用 | P0 |
| R-22 | 边界 | 仅发生 Text/Image 具体控件 ContentChange 事件 | 不触发 PageScene-only 检测 | Text/Image 仍由 ContentChange 注册控制 | AC-7.3 | 单测/代码检查 | PageScene-only 时 Text/Image 路径不调用 PageScene flush | P1 |

## 三、API 变更分析 `[源: spec.md]`

### 3.1 新增 API

| API 名称 | 开放范围 | 入参概要 | 返回值 | 错误码范围 | 功能描述 | 关联 AC |
|----------|----------|----------|--------|------------|----------|---------|
| `RegisterPageSceneRules` | System innerAPI | `ruleJson`、`PageSceneEventCallback` | `int32_t` | 成功、参数错误、重复注册、请求忙、IPC 错误 | 注册页面场景规则 | AC-1.1, AC-1.2, AC-1.3 |
| `UnregisterPageSceneRules` | System innerAPI | `ruleSetId` | `int32_t` | 成功、参数错误、未注册、请求忙、IPC 错误 | 反注册页面场景规则 | AC-8.3, AC-8.4 |
| `GetPageScene` | System innerAPI | `ruleJsonOrRuleSetId`、`PageSceneEventCallback` | `int32_t` | 成功、参数错误、请求忙、IPC 错误 | 主动查询一次页面场景 | AC-4.1, AC-4.3, AC-4.4 |
| `ReportPageSceneEvent` | ReportService callback | `sceneJson` | void | N/A | UI 侧向 SA 回传 ArkUI 宿主来源场景命中结果 | AC-2.2 |

### 3.2 测试补充信息

| API 名称 | API Reference | Sample Code | 调用使用方式 | 运行触发方式 | 头文件 | 权限要求 |
|----------|---------------|-------------|-------------|-------------|--------|----------|
| `RegisterPageSceneRules` | `interfaces/inner_api/ui_session/ui_content_service_interface.h` | Stage 3 补充 `ui_session_sample` | SA 连接 UISession 后调用 proxy | hidumper/sample 或 SA 自动化测试 | `ui_content_service_interface.h`, `ui_content_proxy.h` | native SA |
| `UnregisterPageSceneRules` | 同上 | 同上 | SA 按 `ruleSetId` 反注册 | hidumper/sample 或死亡清理 | 同上 | native SA |
| `GetPageScene` | 同上 | 同上 | SA 传 `ruleSetId` 或一次性 ruleJson 查询 | hidumper/sample 或自动化测试 | 同上 | native SA |
| `ReportPageSceneEvent` | `ui_report_proxy.h`, `ui_report_stub.h` | Stage 3 补充 `ui_session_sample` 回调日志 | 宿主通过 ReportService 回调 SA | 场景命中或主动查询结果返回 | `ui_content_service_interface.h` | ReportService 内部回调 |

## 四、兼容性声明 `[源: spec.md]`

| 字段 | 内容 |
|------|------|
| 已有 API 行为变更 | 否 |
| 修改前规格 | 无页面场景规则化感知能力 |
| 修改后规格 | 系统 SA 可通过 UISession 注册/查询页面场景规则 |
| 是否进行版本隔离 | 否，System innerAPI 随 UISession 内部能力管理 |
| 配置文件格式变更 | 否 |
| 数据存储格式变更 | 否 |
| 最低支持版本 | TBD |
| changelog | `.codespec/changes/ui-session-page-scene-awareness/manifest.md` |

## 五、2D 能力特征分析

### 5.1 是否涉及新增开放 API

**是否涉及：** 是。涉及 System innerAPI，不涉及 ArkTS/Public API。测试覆盖见第三章。

### 5.2 是否涉及应用兼容性

**是否涉及：** 否。不改变应用侧组件 API 行为。

### 5.3 是否涉及跨平台

**是否涉及：** 否。首版按 OpenHarmony ArkUI UISession 能力验证。

### 5.4 是否涉及 IDE 预览

**是否涉及：** 否。

### 5.5 是否涉及编译工具链

**是否涉及：** 否。

### 5.6 是否涉及全球化语言

**是否涉及：** 否。

### 5.7 是否涉及深浅色模式

**是否涉及：** 否。本能力不改变 UI 显示。

### 5.8 是否涉及新材质

**是否涉及：** 否。

### 5.9 是否涉及无障碍

**是否涉及：** 否。首版不读取无障碍文本内容。

### 5.10 是否涉及多设备差异

**是否涉及：** 是。

| 设备类型 | 差异化描述 | 测试验证 |
|----------|-----------|----------|
| 手机 | 按当前窗口可见区域计算 `onlyVisible` 和 `rect` | 是 |
| Pad | 多窗口/分屏验证当前宿主窗口页面名、rect、可见性 | 是 |
| PC | 窗口尺寸变化和焦点场景验证 rect 与 focusable | 是 |
| 穿戴/智慧屏/座舱 | 首版无强制差异 | 否 |
| 其他 | Web / UIExtension 仅验证规则透传入口 | 是 |

### 5.11 是否涉及适老化

**是否涉及：** 否。

### 5.12 是否涉及资料新增或变更

**是否涉及：** 是。新增 SDD 文档目录 `.codespec/changes/ui-session-page-scene-awareness/`。

## 六、非功能性需求 `[源: spec.md]`

### 6.1 性能指标

**是否涉及：** 是。

| 规格描述 | 验证指标 | 验证方式 |
|----------|----------|----------|
| WHEN 文本输入类控件频繁上下树触发计数变化 THEN 只维护计数和待检测规则，页面稳定后再 check 并按 `policy.minReportIntervalMs` / `deduplicate` 限制重复上报 | 未稳定前无上报；稳定后同一规则相同命中集合不重复上报；上报间隔不小于配置值 | 单测/集成测试 |
| WHEN 当前页面节点较多 THEN 只采集规则所需字段，不生成完整树 | 上报 JSON 不包含完整树 | 单测/JSON 检查 |

### 6.2 功耗指标

**是否涉及：** 否。

### 6.3 稳定性 & 可靠性

**是否涉及：** 是。

| 指标项 | 目标值 | 测试场景 | 验证方法 |
|--------|--------|----------|----------|
| 重复注册保护 | 已注册未注销时新注册失败且旧规则保持有效 | 注册 ruleA 后注册 ruleB | 单测/并发测试 |
| Get 并发保护 | 前一次 Get 未返回时再次 Get 返回 busy | 延迟首个回调后发起第二次 Get | 单测/并发测试 |
| 生命周期清理 | 反注册或 SA 死亡后不再上报 | 注册、命中、反注册、再次上树 | 单测/sample |
| 子来源透传隔离 | Web/UIExtension 透传失败不影响 ArkUI 匹配 | Web/UIExtension 控件不存在或透传失败 | mock/单元测试 |
| 稳定点调度 | PageScene-only 注册时页面级稳定点仍触发检测，且 Text/Image 具体事件不触发 PageScene-only 检测 | Page/Scroll/Swiper/Dialog/VSync/Text/Image 路径组合 | ContentChangeManager 单元测试 |

### 6.4 安全隐私合规

**是否涉及：** 是。

| 类型 | 规格描述 |
|------|----------|
| 隐私合规 | WHEN `report.includeText=false` THEN ArkUI 宿主来源上报 JSON 不包含输入文本正文 |
| 功能验证 | WHEN `report.includeText=true` THEN ArkUI 宿主来源上报 JSON 的命中节点包含 `text`，字段值为用户已输入文本或输入为空时的占位提示文本 |
| 隐私合规 | WHEN 构造上报 JSON THEN 不包含完整控件树；ruleJson 不设计完整树上报开关 |
| 信息安全 | WHEN 非 native SA 或 interface token 不匹配 THEN UISession 拒绝调用 |
| 代码实现 | WHEN 打印日志 THEN 只打印 ruleId、sceneType、source、matchedCount、错误码等摘要 |

### 6.5 DFX

**是否涉及：** 是。

| 维度 | 规格描述 |
|------|----------|
| 可测试性 | WHEN sample/hidumper 注册规则或主动查询 THEN 能观察 ruleId、sceneType、source、matchedCount、错误码等脱敏结果 |
| 自动化维测 | WHEN 自动化测试触发注册、重复注册、Get、Get busy、反注册、死亡清理、Web/UIExtension 规则透传 THEN 均可自动验证返回值、透传入口和 ArkUI 回调 JSON |
| 定界定位 | WHEN 场景上报失败 THEN 日志能根据 ruleSetId、ruleId、source、错误码区分宿主匹配问题与子来源透传问题 |

## 七、2C 功能体验分析

### 7.1 是否涉及 UX — 静态 UI 效果

**是否涉及：** 否。本能力不改变页面显示效果。

### 7.2 是否涉及 UX — 动态 UI 效果

**是否涉及：** 否。

### 7.3 是否涉及 UX — 手势/事件/交互/焦点

**是否涉及：** 是。

| 交互类型 | 触发条件 | 预期结果 | UX 效果图 |
|----------|----------|----------|-----------|
| 焦点属性采集 | WHEN 命中文本输入类控件且 `report.includeFocusable=true` | THEN 上报节点包含 `focusable`，用于区分可自由输入和可能拉起 picker 的表单入口 | N/A |

### 7.4 是否涉及用户数据

**是否涉及：** 是。

| 测试场景 | 触发条件 | 预期结果 |
|----------|----------|----------|
| 数据使用 | WHEN 场景匹配并上报 | THEN 仅使用控件类型、可获焦状态、rect、节点 ID 等结构化数据，不上报输入文本正文 |
| 数据存储 | WHEN 宿主保存 `ruleJson` | THEN 仅保存规则配置和回调状态，反注册或 SA 死亡后清理 |
| 重启恢复 | WHEN 应用进程重启或 SA 断连 | THEN 旧规则状态不残留，不向死亡 SA 上报 |
| 版本升级 | WHEN 系统升级 | THEN 不涉及应用数据迁移 |

## 八、测试用例设计建议

| 用例组 | 重点用例 |
|--------|----------|
| 注册接口 | 首次合法注册、非法 JSON、空 callback、未 Connect、重复注册、注册期间并发注册 |
| 首次扫描 | 0/1/2/3 个文本输入控件、`reportOnRegister=false`、页面名变化 |
| 节点过滤 | visible/hidden/offscreen、focusable true/false、rect 开关、focusable 开关 |
| 上下树触发 | 动态添加 TextInput/TextArea/Search/RichEditor、控件下树移除计数、未稳定前不立即上报、稳定后触发检测、重复触发去重、最小间隔 |
| 稳定点调度 | PageScene-only 注册下 Page/Scroll/Dialog 稳定点触发、Swiper 延迟到 VSync、滚动/转场/Swiper 滚动中不 flush、Pipeline 不直接依赖 PageScene flush、Text/Image 不触发 PageScene-only |
| 主动查询 | ruleSetId 查询、一次性 ruleJson 查询、非法参数、pending Get busy |
| Web 透传 | `webRules` 注册透传、反注册透传、查询请求透传、透传失败隔离；不验证 `webRules` 内部规格、Web 内部匹配和回传 |
| UIExtension 透传 | 规则注册透传、反注册透传、查询请求透传、透传失败隔离；不验证 UIExtension 内部匹配和回传 |
| 隐私安全 | 输入敏感文本时 JSON/日志不含正文；非 SA 调用失败 |
| 生命周期 | 反注册后不上报、SA death 清理、断连清理、多 SA 隔离 |

## 九、参考资料

| 文档 | 路径 | 状态 |
|------|------|------|
| spec.md | `.codespec/changes/ui-session-page-scene-awareness/spec.md` | Baselined |
| design.md | `.codespec/changes/ui-session-page-scene-awareness/design.md` | Designed |
| execution-plan.md | `.codespec/changes/ui-session-page-scene-awareness/execution-plan.md` | Draft |
| UISession KB | `docs/architecture/UISession_Knowledge_Base_CN.md` | Reference |

## 附录：术语表

| 术语 | 定义 |
|------|------|
| UISession | ArkUI 在应用进程内提供给系统 SA、调试工具和 AI 能力的内部 UI 会话通道 |
| SA | System Ability，系统服务侧调用方 |
| ruleJson | SA 下发的页面场景规则 JSON |
| TEXT_EDITOR | 首批页面场景类型，表示当前页面或子内容源存在 2 个及以上文本输入类控件 |
| COUNT_GTE | `COUNT Greater Than or Equal`，命中节点数量大于等于阈值 |
| SubSource | Web 或 UIExtension 等由宿主控件承载的子内容源 |
| 稳定点 | 页面切换、滚动、Swiper/Tabs 切换、弹窗显示隐藏等完成后，或 VSync 尾部确认无滚动/转场/Swiper 滚动时执行场景检测的时机 |
