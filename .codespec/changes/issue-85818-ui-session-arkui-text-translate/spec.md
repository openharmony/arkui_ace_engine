# 特性规格

## 概述

| 属性 | 值 |
|------|-----|
| 特性名称 | Uisession 统一页面文本翻译 |
| 特性编号 | FEAT-UISESSION-UNIFIED-TEXT-TRANSLATE |
| 所属 Epic | 无 |
| 优先级 | P0 |
| 目标版本 | 跟随需求基线，产品版本未指定 |
| SIG 归属 | ArkUI/ACE |
| 状态 | Approved |
| 复杂度 | 标准 + 安全/性能专项 |

## 本次变更范围（Delta）

| 类型 | 内容 | 说明 |
|------|------|------|
| REFINED | 统一页面文本单次获取接口 | 当前源码已有 transaction/接口声明；本 Spec 固化 scope bitmask，例如 `ARKWEB_ONLY`、`ARKUI_ONLY`、`ARKUI_ARKWEB`、`XCOMPONENT`、`CANVAS_NODE`、`PAGE_ALL`；当前仅支持 ArkUI 与 ArkWeb，XComponent/CanvasNode 作为后续扩展保留字段 |
| REFINED | 统一页面文本连续翻译 Start/End 能力 | 当前源码已有基础入口；本 Spec 补齐 Start 初始上报、后续增量上报、End 恢复原文、状态隔离和 DFX |
| ADDED | ArkUI Text/Span/styled string/RichEditor 只读展示内容和 TextInput placeholder 翻译 | 运行时译文布局展示，不改原属性；TextInput 仅覆盖空内容时实际展示的 placeholder，不翻译用户可编辑文本 |
| ADDED | SA 死亡/IPC 断开恢复 | 已翻译状态恢复原文并清理会话 |
| ADDED | `ui_session_sample` dump 验证命令 | 真机触发新增接口、范围入参、回填、Reset/End |
| ADDED | Host Preview 验证应用与脚本 | `examples/UISessionTranslate` 通过 PreviewerCLI `remoteRequest` 模拟 getText/start/sendResult/reset/end，并用 `simpleTree` 对照 nodeId |
| ADDED | 翻译请求 DFX 超时处理 | 复用 `Connect` 传入的 `EventHandler` 投递超时任务，超时记录故障并清理现场 |
| ADDED | 译文 unicode 转义兼容 | `SendPageTranslateResult` 接收的 `translatedText/text` 若为 `\\uXXXX` 字面量，应在回填前规范化为 UTF-8 中文等真实字符；已是 UTF-8 的译文保持不变 |
| ADDED | 批量译文回填 | `SendPageTranslateResult` 支持 `{"results":[...]}` 和顶层数组形式，一次请求回填多个节点；仍兼容原单对象格式 |
| REFINED | 当前 Ability 实例语言地区信息获取接口 | 当前源码已有 transaction/接口声明；本 Spec 固化系统 SA 通过同步 innerAPI 获取当前 Ability 实例实际生效的 language 和 region |
| MODIFIED | `UIContentImpl` 启动期 Uisession callback 注册 | 新增统一翻译相关 callback 保存到 `UiSessionManager`，执行时通过 `TaskExecutor` 切回 UI 线程访问 `PipelineContext`/`ContentChangeManager` |
| MODIFIED | 现有 Web 翻译能力的入口覆盖 | 新统一接口在 `ARKUI_ARKWEB` 模式覆盖现有 Web 能力，但 Web 脚本注入实现保持兼容 |
| REMOVED | 无 | 不废弃现有 Web-only 接口 |

## 输入文档

| 文档 | 路径 | 状态 |
|------|------|------|
| Proposal | `proposal.md` | Approved |
| Design | `design.md` | Approved |

## 用户故事

### US-1: 按范围单次获取页面文本

**作为** 系统 SA，
**我想要** 按入参单次获取当前页面全部可翻译内容或仅 ArkUI 原生可翻译文本节点，
**以便** 发起一次性翻译或建立连续翻译基线。

**验收标准：**

- **AC-1:** WHEN 系统 SA 调用单次页面文本获取接口且入参为仅 ArkUI 原生控件 THEN ArkUI 返回有实际文本绘制内容的 Text、Span/styled string、RichEditor 只读展示文本节点，以及空内容 TextInput 当前实际展示的 placeholder 提示文本节点列表，并包含 stable nodeId 和当前可翻译文本。
- **AC-2:** WHEN 系统 SA 调用单次页面文本获取接口且入参为页面所有内容 THEN ArkUI 返回 Web 可翻译内容和 ArkUI 原生可翻译文本节点；Web 内容沿用现有脚本注入方式提取。
- **AC-3:** WHEN 页面包含 TextInput/TextArea 的用户可编辑文本、Canvas、自绘文本或图片文字 THEN 获取结果不包含这些非范围内文本；WHEN TextInput 内容为空且 placeholder 提示文本实际展示 THEN placeholder 可作为可翻译展示文本返回。

### US-2: 按范围连续翻译

**作为** 系统 SA，
**我想要** 按入参启动和结束页面文本连续翻译会话，
**以便** 在会话期间持续同步对应范围内新增和变化文本。

**验收标准：**

- **AC-4:** WHEN StartTranslate scope 为 ArkUI-only THEN ArkUI 进入连续翻译状态，并上报当前 ArkUI 原生可翻译文本节点列表。
- **AC-5:** WHEN StartTranslate scope 为页面所有内容 THEN ArkUI 上报当前 Web 可翻译内容和 ArkUI 原生文本节点，Web 内容沿用脚本注入。
- **AC-6:** WHEN Start 后新的 ArkUI 文本展示节点或空内容 TextInput placeholder 节点上树并产生实际文本绘制且 scope 包含 ArkUI THEN ArkUI 主动向 SA 上报该节点的 nodeId、text、version。
- **AC-7:** WHEN Start 后已有 ArkUI 文本展示节点内容变化、或空内容 TextInput 当前实际展示的 placeholder 变化并产生实际文本绘制且 scope 包含 ArkUI THEN ArkUI 主动向 SA 上报该变化节点的 nodeId、text、version；用户可编辑文本变化不触发翻译上报。
- **AC-8:** WHEN Start 后 Web 内容变化且 scope 为页面所有内容 THEN Web 继续按现有脚本注入链路处理和上报。
- **AC-9:** WHEN EndTranslate 被调用 THEN ArkUI 停止变化上报并恢复原文；Web 结束沿用现有 End Web 翻译链路。
- **AC-14:** WHEN 未 Start 或 End 后文本变化 THEN ArkUI 不主动上报变化文本。

### US-3: 临时译文展示和恢复

**作为** 终端用户，
**我想要** 看到译文临时替换原文布局展示，
**以便** 理解页面内容且不影响应用原始状态。

**验收标准：**

- **AC-10:** WHEN Reset 指定 nodeId THEN ArkUI 仅恢复该节点原文展示，其他节点不受影响。
- **AC-11:** WHEN Reset 全量 THEN ArkUI 全部恢复原文展示，Web 内容按现有 Reset 行为恢复。
- **AC-12:** WHEN SA 下发 ArkUI 原生节点译文 THEN ArkUI 按 nodeId 运行时展示译文，但不修改应用原始文本属性。
- **AC-12a:** WHEN SA 下发的 ArkUI 原生节点译文中包含 `\\uXXXX` unicode 转义字面量 THEN ArkUI 在回填前解码为真实 UTF-8 文本后展示；普通 UTF-8 译文和非 unicode 反斜杠文本不得被破坏。

### US-4: 动态页面回填容错

**作为** 系统 SA，
**我想要** 批量回填译文且局部失败不影响其他节点，
**以便** 在动态页面中稳定工作。

**验收标准：**

- **AC-13:** WHEN 回填目标 ArkUI 节点离树、版本不匹配或 nodeId 不存在 THEN ArkUI 忽略该条结果、记录非正文日志，并继续处理同批次其他结果。
- **AC-15:** WHEN 现有 Web 接口或新统一接口页面所有内容模式被调用 THEN Web 文本提取、脚本注入回填和 Reset 行为保持兼容。

### US-5: SA 异常死亡恢复

**作为** 终端用户，
**我希望** 系统翻译服务异常退出后页面恢复原文展示，
**以免** 临时译文状态残留。

**验收标准：**

- **AC-16:** WHEN SA 进程意外死亡或 IPC 断开且当前存在已翻译展示 THEN ArkUI 在死亡监听中恢复所有临时译文为原文，并清理会话状态。
- **AC-17:** WHEN SA 进程意外死亡或 IPC 断开且当前处于连续翻译状态 THEN ArkUI 停止变化上报并清理连续翻译状态。

### US-6: 模拟 SA dump 验证

**作为** 系统开发者，
**我想要** 通过模拟 SA dump 命令在终端设备触发新增翻译接口和参数，
**以便** 进行真机验证和问题定位。

**验收标准：**

- **AC-18:** WHEN dump 触发单次获取并指定 scope THEN handler 调用新增接口并打印 nodeId、文本长度或安全摘要、scope 和结果状态。
- **AC-19:** WHEN dump 触发 Start/End 并指定 scope THEN handler 调用新增连续翻译接口，并能接收和打印初始节点及后续变化上报摘要。
- **AC-20:** WHEN dump 触发 Reset 或 SendTranslateResult THEN handler 调用对应接口并支持 nodeId、译文或批量结果参数。
- **AC-21:** WHEN 系统 SA 调用当前 Ability 语言地区信息获取接口 THEN ArkUI 返回当前 Ability 实例实际生效的 `language` 和 `region`，值来自该实例资源配置/配置更新后的生效 locale，而不是直接读取系统全局语言。
- **AC-22:** WHEN 当前 Ability 语言地区信息为空、配置尚未初始化或当前实例不可用 THEN 接口返回失败或空字段并记录非正文日志，不影响翻译会话状态。

### US-7: Host Preview 快速验证

**作为** 系统开发者，
**我想要** 在 Host Preview 环境通过脚本模拟 Uisession 翻译调用，
**以便** 不依赖真机 SA 快速验证页面文本提取和译文回填链路。

**验收标准：**

- **AC-23:** WHEN PreviewerCLI `remoteRequest pageTranslate/getText` 指定 ArkUI scope THEN 返回真实 ArkUI 文本节点的 nodeId、text、version；若存在真实文本，不得混入 `nodeId=-1,text=empty,version=0`。
- **AC-24:** WHEN PreviewerCLI `remoteRequest pageTranslate/start` 开启连续翻译 THEN 初始可翻译文本返回正版本号；Start 后进入新页面或 List 滚动导致新的可见文本节点上树渲染时，`collect` 能获取增量节点并可通过 `sendResult` 回填译文。
- **AC-25:** WHEN PreviewerCLI 执行 `reset` 或 `end` THEN Preview 环境按统一恢复路径清理临时译文；指定 nodeId 的 `reset` 只恢复该节点，全量 `reset` 和 `end` 后 `inspector --business simpleTree` 不再包含临时译文字段。

## 验收追溯

| AC | 关联规则 | 关联 Task | 验证方式 | 证据 |
|----|----------|-----------|----------|------|
| AC-1, AC-2, AC-3 | BR-1, FR-1 | Stage 3 Task: API + manager | Uisession 单测 | test/unittest |
| AC-4 至 AC-9, AC-14, AC-14a | BR-2, BR-7, FR-2, FR-3 | Stage 3 Task: session + report | Manager/Pattern 单测 | test/unittest |
| AC-10 至 AC-13 | FR-4, EX-1, RC-1 | Stage 3 Task: Pattern runtime display | Text/RichEditor/TextInput placeholder 单测 | test/unittest |
| AC-15 | BR-3 | Stage 3 Task: Web compatibility | Web 回归 | test/unittest |
| AC-16, AC-17 | EX-2, RC-2 | Stage 3 Task: death recovery | DeathRecipient/manager 单测 | test/unittest |
| AC-18 至 AC-20 | FR-5 | Stage 3 Task: sample SA dump | 真机 dump + hilog | 手工验证记录 |
| AC-21, AC-22 | FR-7, EX-8 | Stage 3 Task: API + startup sync getter + sample dump | Uisession 单测 + 真机 dump | test/unittest + 手工验证记录 |
| AC-23 至 AC-25 | FR-8, BR-11 | Stage 3 Task: Host Preview verification | PreviewerCLI remoteRequest + simpleTree + screenshot | `examples/UISessionTranslate/.report` |

## 业务规则

| 编号 | 规则描述 | 约束条件 | 关联 AC |
|------|----------|----------|---------|
| BR-1 | scope 控制处理范围 | scope 是节点来源类型 bitmask；`ARKUI_ONLY` 不进入 ArkWeb 文本翻译；`ARKWEB_ONLY` 只处理 ArkWeb；`ARKUI_ARKWEB` 为当前推荐页面内容范围，包含 ArkWeb 与 ArkUI 原生文本；`XCOMPONENT`、`CANVAS_NODE` 是已知保留 bit，当前解析但不触发处理；scope 包含任何未定义 bit 时必须返回 `PARAM_INVALID`，不进入会话、不注册 callback、不产生上报 | AC-1, AC-2 |
| BR-2 | 连续翻译只在 Start 到 End/Reset/SA death 期间有效 | 未 Start 或 End 后不主动上报 | AC-4 至 AC-9, AC-14 |
| BR-3 | Web 兼容 | Web 仍通过脚本注入提取/回填；新接口全页面模式覆盖现有 Web 能力 | AC-2, AC-5, AC-8, AC-15 |
| BR-4 | ArkUI 原属性不变 | 译文仅作为 Pattern 运行时展示状态参与布局 | AC-10 至 AC-12 |
| BR-5 | DFX timeout | 单次获取和 Start 初始快照必须有 timeout 任务；超时清 callback 并执行现场清理。原文发出后等待译文回填默认 5s，SA 未死亡时只输出告警日志和现场摘要，不强制结束会话 | AC-16, AC-17, AC-18, AC-19 |
| BR-6 | UI 线程访问边界 | 统一翻译新增 callback 在 `UIContentImpl::InitUISessionManagerCallbacks` 启动期注册到 `UiSessionManager`；IPC stub 不直接访问 Pipeline/Pattern，实际执行通过 `TaskExecutor` 回到 UI 线程 | AC-1, AC-4, AC-9, AC-16, AC-17 |
| BR-7 | 实际文本绘制过滤 | 文本展示控件仅占位布局、未产生实际文本绘制内容时不进入单次获取和增量上报；后续真实绘制文本时再按 snapshot 或增量规则处理 | AC-1, AC-6, AC-7, AC-14a |
| BR-8 | 按需写入和低开销 | 未处于 StartTranslate 连续翻译状态时，`ContentChangeManager` 不写入 translate 专用容器、不计算 translate version/hash、不维护 pending、不投递 translate 延迟任务；单次 Get 只做临时快照，不留下连续监听状态 | AC-1, AC-4, AC-6, AC-7, AC-14, AC-14a |
| BR-9 | Ability 语言地区来源 | 当前 Ability 语言地区接口只返回当前 UIContent/Ability 实例生效 locale，优先使用实例资源配置已生效值；不得用系统全局语言替代实例语言；返回字段仅包含 `language` 和 `region`，不暴露应用正文或页面文本；该接口是简单查询业务，必须采用同步 IPC，从 reply 直接返回结果 | AC-21, AC-22 |
| BR-10 | 当前实现基线复用 | 当前源码已存在 `GET_PAGE_TRANSLATE_TEXT`、`START_PAGE_TRANSLATE`、`END_PAGE_TRANSLATE`、`RESET_PAGE_TRANSLATE`、`SEND_PAGE_TRANSLATE_RESULT`、`GET_CURRENT_ABILITY_LANGUAGE_INFO` transaction 和 `IUiContentService` 声明，以及 `ContentChangeManager::StartTextTranslateReport`、`ReportCurrentTranslateTextNodes`、`ApplyTranslateResult` 基础实现；Stage 3 是补齐语义、隔离状态、DFX 和测试，不重复新增平行接口 | 全部 AC |
| BR-11 | Host Preview 验证边界 | PreviewerCLI `remoteRequest` 是 host 验证入口，通过 `business + method` 扩展模拟 Uisession 调用，不作为正式产品接口；验证脚本允许断言固定测试文本，但日志和报告不得采集应用未知正文 | AC-23 至 AC-25 |
| BR-12 | 译文编码规范化 | `SendPageTranslateResult` 在进入 Web/ArkUI 临时译文展示前，只对 `translatedText/text` 字段中的 unicode 转义字面量做解码；不改变全局 JSON parser 行为，不解码普通路径类反斜杠文本 | AC-12, AC-12a |
| BR-13 | 批量回填语义 | `SendPageTranslateResult` 兼容单条对象、顶层数组和 `results` 数组；批量中每个节点按自身 `nodeId/version` 独立校验，单条失败不得阻断其他节点；Preview 和 sample 验证不得通过按节点循环多次发送替代批量能力 | AC-12, AC-20, AC-25 |
| BR-14 | 统一翻译节点抽象 | 可翻译节点通过 `PageTranslateNode` 接口接入：ArkUI 原生控件提供 nodeId、可翻译文本提取、译文回填和 Reset；`WebPattern` 继承同一接口并承载 Web 旧脚本注入 hook。`Pattern` 基类不增加或保留默认翻译虚函数；`ContentChangeManager` 和 `UiTranslateManagerImpl` 只缓存 `WeakPtr<PageTranslateNode>`，页面遍历或 Web 注册时从具体 Pattern 动态转换到接口；WebInfo/image 查询等 Web 专属能力才局部转回 `WebPattern` | AC-1, AC-4, AC-6, AC-7, AC-10 至 AC-15 |

## 功能规则

| 编号 | 规则描述 | 触发条件 | 作用对象 | 关联 AC |
|------|----------|----------|----------|---------|
| FR-1 | 单次页面文本获取 | SA 调用 GetPageTranslateText | Web、Text、Span/styled string、RichEditor 只读展示、空内容 TextInput placeholder；ArkUI 文本需已实际绘制 | AC-1 至 AC-3 |
| FR-2 | Start 初始上报 | SA 调用 StartTranslate | scope 覆盖的当前可翻译节点 | AC-4, AC-5 |
| FR-3 | 增量变化上报 | Start 后节点产生实际文本绘制或已绘制文本内容变化 | scope 覆盖且有实际文本绘制的节点 | AC-6 至 AC-8, AC-14a |
| FR-4 | 运行时译文展示 | SA SendTranslateResult | ArkUI 原生文本展示节点和空内容 TextInput placeholder 展示状态 | AC-10 至 AC-13 |
| FR-5 | 模拟 SA dump | 开发者执行 dump 命令 | 新增接口和参数 | AC-18 至 AC-20 |
| FR-6 | 超时任务管理 | 注册翻译回调后、发送 IPC 成功后 | `UiReportStub` pending callback 和 manager 会话 | AC-16, AC-17 |
| FR-7 | 当前 Ability 语言地区获取 | SA 调用 GetCurrentAbilityLanguageInfo | 当前 Ability/UIContent 实例生效 locale | AC-21, AC-22 |
| FR-8 | Host Preview 模拟调用 | PreviewerCLI `remoteRequest pageTranslate/*` | Preview `UiSessionManagerPreview`、Preview `UiTranslateManagerImpl`、`examples/UISessionTranslate` | AC-23 至 AC-25 |

## 异常/豁免规则

| 编号 | 规则描述 | 触发条件 | 处理结果 | 关联 AC |
|------|----------|----------|----------|---------|
| EX-1 | 回填目标无效 | nodeId 不存在、节点离树、版本不匹配 | 单条忽略，记录非正文日志，继续处理其他结果 | AC-13 |
| EX-2 | SA 死亡或 IPC 断开 | DeathRecipient 或连接断开回调触发 | 全量恢复原文，停止上报，清理会话 | AC-16, AC-17 |
| EX-3 | 参数非法 | scope 为 0、scope 包含未定义 bit、payload 缺字段或字段类型非法 | 返回 `PARAM_INVALID` 或等价参数错误，不进入会话、不注册 callback、不上报；`XCOMPONENT`/`CANVAS_NODE` 作为已定义保留 bit 不属于非法 bit，但当前只解析不处理 | AC-18 至 AC-20 |
| EX-4 | 非范围控件 | TextInput/TextArea 用户可编辑文本、Canvas/OCR 等 | 不收集、不上报、不回填；TextInput 空内容且 placeholder 实际展示时按展示提示文本处理 | AC-3 |
| EX-5 | 翻译请求超时 | 单次获取或 Start 初始快照长时间无响应 | 记录非正文故障日志，清 pending callback，停止会话并恢复现场 | AC-16, AC-17 |
| EX-6 | EventHandler 为空或投递 timeout 失败 | Connect 未传入 EventHandler 或 PostTask 失败 | 返回失败或回滚 callback 注册，不进入 pending 状态 | AC-18, AC-19 |
| EX-7 | 译文回填等待超时 | 原文 nodeId/text/version 已发送给 SA 后 5s 内未收到对应 version 的 SendTranslateResult，且 SA 未死亡 | 输出非正文告警日志，记录 requestId/nodeId/version/textLength/elapsedMs，不清理会话、不恢复原文、不阻塞后续回填 | AC-6, AC-7, AC-13 |
| EX-8 | 当前 Ability 语言地区不可用 | 当前 instanceId 不存在、UIContent 未完成初始化或 locale 字段为空 | 返回失败或空字段并记录非正文日志，不触发翻译 Reset/End | AC-22 |
| EX-9 | 译文 unicode 转义非法 | `translatedText/text` 中存在非法 `\\u` 序列或不完整 surrogate pair | 保持原始字面量，不丢弃整条译文，不影响其他节点回填 | AC-12a, AC-13 |

## 恢复契约

| 编号 | 触发条件 | 恢复策略 | 恢复结果 | 约束 |
|------|----------|----------|----------|------|
| RC-1 | Reset nodeId | 清理指定 Pattern 临时译文状态，MarkDirty | 指定节点恢复原文 | 不修改其他节点 |
| RC-2 | Reset all / End | 清理所有 Pattern 临时译文和 manager 会话 | 所有节点恢复原文，停止上报 | Web 走现有 End/Reset |
| RC-3 | SA death / IPC disconnect | 死亡监听调用统一全量恢复流程 | 页面无译文残留，会话状态为空 | 日志不输出正文 |
| RC-4 | 请求 timeout | 单次获取或 Start 初始快照 timeout task 触发 | 清 callback，取消会话，恢复原文，输出 DFX 日志 | 迟到回调不得重新进入会话 |
| RC-5 | 译文回填 watchdog | 原文发送后 5s 未收到译文且 SA 未死亡 | 只输出告警日志和安全现场摘要，保留会话和原文/译文状态 | 后续译文到达仍按 nodeId/version 校验处理 |

## 验证映射

| 编号 | 对应规格项 | 验证方式 | 验证重点 |
|------|------------|----------|----------|
| VM-1 | FR-1/BR-7 | Uisession 单测 | scope、payload、非范围过滤、未实际绘制文本过滤 |
| VM-2 | FR-2/FR-3/BR-7 | Manager 单测 | Start 状态、初始上报、增量去重、实际绘制后首次上报 |
| VM-3 | FR-4/RC-1/RC-2/BR-12 | Text/RichEditor/TextInput placeholder/Uisession 单测 | 译文参与布局、原属性不变、Reset/End；用户填充内容不翻译；unicode 转义译文解码后展示 |
| VM-4 | BR-3 | Web 回归 | 脚本注入路径不回退 |
| VM-5 | EX-2/RC-3 | DeathRecipient 单测 | SA death 恢复和状态清理 |
| VM-6 | FR-5 | 真机 dump | 新接口和参数可触发 |
| VM-7 | BR-5/EX-5/EX-7/RC-4/RC-5 | DFX 单测 | timeout 投递/取消、超时清理、迟到回调保护、5s 译文等待告警 |
| VM-8 | IPC 非功能需求 | IPC 单测 | 大文本通过 `LargeStringAshmem` 共享内存传输 |
| VM-9 | FR-7/BR-9/EX-8 | Uisession 单测 + dump | 返回当前 Ability 实例 language/region；实例不可用或字段为空时失败/空字段且不影响翻译状态 |
| VM-10 | FR-8/BR-11/BR-12 | Host Preview 脚本 | `getText` 返回真实 ArkUI 文本且不混入 empty 哨兵；`start/collect` 覆盖动态页面和 List 滚动进入视口增量；`sendResult/reset/end` 可触发；首屏标题通过 `\\uXXXX` 字面量发送并在 `simpleTree`/截图中显示中文；`simpleTree` 和截图可对照译文展示与恢复 |

## API 变更分析

### 当前接口基线与补齐项

| 接口/模块 | 当前源码基线 | 本 Spec 要求补齐 |
|-----------|--------------|------------------|
| `IUiContentService` | 已存在页面翻译 transaction 和接口声明：`GET_PAGE_TRANSLATE_TEXT`、`START_PAGE_TRANSLATE`、`END_PAGE_TRANSLATE`、`RESET_PAGE_TRANSLATE`、`SEND_PAGE_TRANSLATE_RESULT`、`GET_CURRENT_ABILITY_LANGUAGE_INFO` | 固化 scope bitmask、参数错误语义、同步 language/region reply、DFX/requestId、sample dump 和单测 |
| `ContentChangeManager` | 已存在 `StartTextTranslateReport`、`ReportCurrentTranslateTextNodes`、`ReportTranslateTextNode`、`ApplyTranslateResult` 等基础入口 | 单次 Get 改为局部无状态快照；连续翻译容器与纯 content change 容器隔离；容器类型改为 `WeakPtr<PageTranslateNode>`；补实际绘制过滤、按需写入、版本清理和测试 |
| Pattern/Web 翻译接口 | Text/RichEditor/TextField 已有各自展示文本和布局状态；Web 已有 JS 注入提取/回填实现 | 新增/使用 `PageTranslateNode` 抽象接口，支持翻译的 Pattern 按需继承；Web 旧 hook 从 `Pattern` 基类迁移到 `PageTranslateNode`；不得在 `Pattern` 基类增加或保留默认翻译虚函数，避免扩大所有 Pattern 虚表 |
| TextInput placeholder | 当前 TextFieldPattern 已区分用户输入内容和 placeholder 展示文本 | 空内容且 placeholder 实际展示时进入翻译快照/增量/回填；用户填充值不进入翻译结果，回填时也不得覆盖用户输入 |
| Web 翻译 | 已有 Web 脚本注入提取/回填路径 | `ARKWEB_ONLY`/`ARKUI_ARKWEB` 复用现有路径，不重写 Web 底层 |
| Preview 验证 | 已有 PreviewerCLI action 命令和 preview adapter | 通过 `remoteRequest` 增加 pageTranslate 业务模拟，不新增正式产品接口；`examples/UISessionTranslate` 承载独立 Host Preview 回归 |

### 统一/补齐 API

| API 签名 | 类型 | 功能 | d.ts 位置 | 权限要求 |
|----------|------|------|-----------|----------|
| `int32_t GetPageTranslateText(const std::string& request, const std::function<void(int32_t, std::string)>& callback)` | Inner/System SA | 单次获取页面文本，request 包含 scope | N/A | 沿用 Uisession SA 边界 |
| `int32_t StartPageTranslate(const std::string& request, const std::function<void(int32_t, std::string)>& callback)` | Inner/System SA | 启动连续翻译，初始和增量上报 | N/A | 沿用 Uisession SA 边界 |
| `int32_t EndPageTranslate()` | Inner/System SA | 结束连续翻译并恢复原文 | N/A | 沿用 Uisession SA 边界 |
| `int32_t SendPageTranslateResult(const std::string& result)` | Inner/System SA | 回填统一译文结果，支持 ArkUI 和 Web | N/A | 沿用 Uisession SA 边界 |
| `int32_t GetCurrentAbilityLanguageInfo(std::string& language, std::string& region)` | Inner/System SA | 通过同步 IPC 获取当前 Ability 实例实际生效的语言和地区信息 | N/A | 沿用 Uisession SA 边界 |

### 变更/废弃 API

| 原有 API | 变更类型 | 新 API | 迁移说明 |
|----------|----------|--------|----------|
| `GetWebViewTranslateText` | 保留 | `GetPageTranslateText` | 现有 Web 调用继续可用；新能力推荐使用统一接口 |
| `StartWebViewTranslate` | 保留 | `StartPageTranslate` | `ARKUI_ARKWEB` 覆盖现有 Web 能力并同时获取 ArkUI 原生文本 |
| `EndWebViewTranslate` | 保留 | `EndPageTranslate` | 新接口结束 Web + ArkUI；老接口只保持 Web 兼容 |
| `SendTranslateResult` | 保留/可复用 | `SendPageTranslateResult` | Stage 3 可评估复用现有重载或新增统一 payload |

## 构建系统影响

### BUILD.gn 变更

```text
文件路径: adapter/ohos/entrance/ui_session/BUILD.gn 或相关目标
变更说明: 如新增源文件，纳入 ui_session proxy/stub/manager 编译。

文件路径: test/unittest/.../BUILD.gn
变更说明: 增加 Uisession、Text、RichEditor、Web 回归相关测试源。
```

### bundle.json 变更

不预期新增 component 或外部依赖。

## 兼容性声明

- **已有 API 行为变更:** 否。现有 Web-only API 保留，脚本注入路径不重写。
- **配置文件格式变更:** 否。
- **数据存储格式变更:** 否。
- **最低支持版本:** 跟随目标分支。
- **API 版本号策略:** innerAPI，不涉及 ArkTS Public API `@since`。

## 架构约束

| 关键约束 | 设计结论 | 影响 AC |
|----------|----------|---------|
| 仅系统 SA 通过 Uisession innerAPI 调用 | 不新增 Public API/权限 | 全部 AC |
| Web 继续脚本注入 | scope 包含 `ARKWEB_ONLY` 位时通过 `PageTranslateNode` 调用 WebPattern 现有脚本注入 hook；SA 获取页面内容默认使用 `ARKUI_ARKWEB` 同时覆盖 ArkUI 原生控件和 ArkWeb 页面；`XCOMPONENT`、`CANVAS_NODE` 当前仅保留不处理 | AC-2, AC-5, AC-8, AC-15 |
| UIContent 启动注册 | `UIContentImpl::InitUISessionManagerCallbacks` 集中注册统一翻译 callback，`UiSessionManager` 只保存 callable，callback 内部再取当前 `PipelineContext` 或遍历 container | AC-1, AC-4, AC-9, AC-16, AC-17 |
| Ability 语言地区读取 | `UIContentImpl::InitUISessionManagerCallbacks` 增加当前实例语言地区同步读取函数，执行时在当前 UIContent/Container 实例上下文读取已生效 locale；IPC 采用同步 `SendRequest` 并在 reply 写回 `language` 和 `region`，不触发页面遍历、文本提取或翻译状态变更 | AC-21, AC-22 |
| ArkUI 译文只运行时展示 | Pattern 临时状态，不改原属性 | AC-10 至 AC-12 |
| ArkUI 文本实际上屏过滤 | 只完成占位布局、没有实际文本绘制的展示控件不参与翻译上报，减少 IPC；Pattern 后续真正绘制文本时触发首次上报 | AC-1, AC-6, AC-7, AC-14a |
| ArkUI 文本节点管理边界 | 不新增 `TextTranslateNodeManager`；增强现有 `ContentChangeManager`，但新增 translate 专用注册/反注册入口和待翻译文本容器，承载 ArkUI 文本节点注册、遍历、版本、增量和恢复。不得使用 `AddOnContentChangeNode` / `RemoveOnContentChangeNode` 纯内容变化监听接口，不复用纯 content change 监听运行时集合；IPC/Web/SA callback 不放入该类 | AC-1, AC-4, AC-6, AC-7, AC-10 至 AC-13 |
| 翻译监听与内容变化监听隔离 | 纯 content change 的 start/stop/config 不得清空或触发翻译容器；translate start/end/reset 不得影响纯 content change 容器。两类监听同时开启时各自按自身配置上报 | AC-4, AC-6, AC-7, AC-14, AC-14a |
| 无连续翻译时低开销 | translate inactive 时仅允许常量级开关判断，不允许写 translate 容器、提取文本、计算 hash/version 或投递 translate 任务 | AC-14, AC-14a |
| SA death 必须恢复 | DeathRecipient 调用全量恢复 | AC-16, AC-17 |
| DFX timeout 必须清理现场 | 复用 `Connect` 传入的 `EventHandler` 投递 timeout task，超时清 callback、恢复原文、停止会话 | AC-16, AC-17, AC-18, AC-19 |
| dump 必须可触发 | sample SA 新增 handler | AC-18 至 AC-20 |
| preview 验证必须脚本化 | `examples/UISessionTranslate/tools/host_preview/run_page_translate.sh` 固化 getText/start/collect/sendResult/reset/end/simpleTree/screenshot 验证；`sendResult` 必须用单次批量 `results` 覆盖多个节点一起发送；Demo 必须包含初始页面文本、Span、TextInput placeholder、用户输入排除、动态新页面文本和 List 滚动 repeat 文本进入视口场景 | AC-23 至 AC-25 |

## 非功能性需求

| 类型 | 指标/阈值 | 验证方式 | 证据 |
|------|-----------|----------|------|
| 性能 | Start 前不启用 ArkUI 文本变化主动上报，且不写 translate 容器/不算 version/hash/不投递任务；Start 后相同内容不重复上报 | Manager/ContentChangeManager 单测 | test/unittest |
| 内存 | End/Reset/SA death 后 manager 会话状态和 Pattern 临时译文清空 | 单测 | test/unittest |
| 安全 | 对翻译 SA 暴露字段收敛为 nodeId、text、version；日志不打印原文/译文，只打印 nodeId、长度、错误码，UI 内部可附带 scope/changeType/sourceType | 代码审查/单测 | review.md |
| 可靠性 | nodeId 无效、版本不匹配、SA death 均不导致崩溃或译文残留 | 单测 | test/unittest |
| IPC | 大文本统一复用现有 `LargeStringAshmem` 共享内存方式传输，不新增分片策略 | IPC 单测/代码审查 | test/unittest |
| DFX | 单次获取和 Start 初始快照 timeout 后必须清 callback、恢复现场并记录非正文故障日志；原文发送后 5s 未收到译文且 SA 未死亡时必须输出非正文告警日志 | DFX 单测 | test/unittest |
| 问题定位 | sample SA dump 能输出安全摘要和状态；timeout/cleanup 日志可定位 requestId、scope、错误码；Host Preview 脚本能输出 Previewer 日志和 remoteRequest 响应文件 | 真机验证 + Host Preview | release 记录 + `.report` |

## 全局特性影响

| 特性 | 适用？ | 结论 | 关联场景 |
|------|--------|------|----------|
| 无障碍 | 是 | 首期明确不修改 accessibility text 和原始语义属性；无障碍树继续读取应用原文属性，临时译文仅影响视觉布局展示。若后续要求读屏读取译文，需单独立项评估隐私、语言切换和可访问性一致性 | ArkUI 临时展示 |
| 大字体 | 是 | 译文进入布局，遵循现有 Text/RichEditor/TextInput placeholder 大字体布局 | AC-12 |
| 深色模式 | N/A | 不改颜色和主题属性 | N/A |
| 多窗口/分屏 | 是 | 通过当前 focused window/service 触发；manager 按 instance/window 隔离 | dump 验证 |
| 多用户 | N/A | 不新增持久化或跨用户数据 | N/A |
| 版本升级 | 是 | 保留老 Web API | AC-15 |
| 生态兼容 | 是 | 不新增三方 API，不改应用原属性 | AC-12 |

## 行为场景

```gherkin
Feature: Uisession unified page text translation

  Scenario: Start ArkUI-only translation
    Given a page contains Text, Span, readonly RichEditor and Web
    When SA calls StartPageTranslate with scope ARKUI_ONLY
    Then ArkUI reports Text, Span and readonly RichEditor text nodes
    And Web text is not reported by this session

  Scenario: Start full page translation
    Given a page contains Web and ArkUI native text nodes
    When SA calls StartPageTranslate with scope ARKUI_ARKWEB
    Then ArkUI reports native text nodes
    And Web text is processed by the existing script injection path

  Scenario: SA death recovery
    Given translation results have been applied to ArkUI text nodes
    When the SA report remote dies
    Then ArkUI restores all temporary translated display to original text
    And active translation session state is cleared

  Scenario: Translate request timeout cleanup
    Given SA has connected with an EventHandler
    When SA starts page translation and no initial text callback arrives before timeout
    Then the pending callback is cleared
    And active translation session state is cleared
    And all temporary translated display is restored to original text
    And logs contain request id, scope and cleanup result without original text

  Scenario: Host Preview getText and sendResult
    Given the UISessionTranslate preview app contains visible ArkUI Text and Span nodes
    When the host script calls remoteRequest pageTranslate/getText with ArkUI scope
    Then the response contains real nodeId, text and version records
    And the response does not mix the empty sentinel with real text
    When the script calls remoteRequest pageTranslate/sendResult for one returned node
    Then the Preview environment accepts the result and reset/end can restore the session
```

## Spec 自审清单

- [x] 无未解释占位符；目标版本沿需求基线未指定
- [x] 所有 AC 使用 WHEN/THEN 格式，可独立测试
- [x] 范围边界明确
- [x] 无语义模糊表述
- [x] AC 与业务规则/异常规则/恢复契约交叉一致

## context-references

```yaml
context-queries:
  - repo: "OpenHarmony/foundation/arkui/ace_engine"
    query: "Uisession UIContentServiceProxy UiReportStub UiReportProxy Web translate TextPattern RichEditorPattern"
```

**关键文档：** `proposal.md`, `design.md`
