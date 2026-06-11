# Proposal

> 一份文档，从原始需求到基线结论。按阶段追加内容，不拆成多份独立文件。

## 一、原始需求

### 基本信息

| 字段 | 内容 |
|------|------|
| 需求ID | REQ-UISESSION-ARKUI-TEXT-TRANSLATE |
| 需求名称 | Uisession ArkUI 文本展示控件连续翻译 |
| 来源 | 用户需求 |
| 提出人 | 用户 |
| 目标发行版本 | TBD |
| 候选 Profile | arkui |
| 优先级 | P0 |
| 状态 | Baselined |

### 原始描述

**原始问题：** Uisession 中目前已有为系统 SA 提供的 innerAPI，提供了为 Web 场景提取并通过 IPC 传输文本给 SA，以及翻译文本回填的能力以实现连续智能翻译。参考现有能力，需要新增接口及实现，扩展到所有文本展示类控件。

**痛点：**

| 用户类型 | 当前痛点 | 影响 |
|----------|----------|------|
| 系统 SA | 只能通过现有 Web 翻译链路处理 Web 文本，不能统一处理 ArkUI 原生文本展示控件 | 连续翻译覆盖范围不足 |
| 终端用户 | ArkUI 原生页面中的展示文本不能被系统连续翻译能力覆盖 | 翻译体验不连续 |

**期望结果：** 系统 SA 可以通过 Uisession innerAPI 对页面文本执行单次页面文本获取、StartTranslate、EndTranslate、Reset 恢复原文展示，并在连续翻译会话期间接收文本节点变化增量。新增接口能力需要覆盖现有 Web 翻译能力；Web 内容翻译继续基于脚本注入实现。SA 可通过入参明确处理范围：页面所有内容（Web + ArkUI 原生文本展示控件）或仅 ArkUI 原生文本展示控件。

### 背景证据

| 证据类型 | 链接/路径 | 说明 |
|----------|-----------|------|
| SA 侧调用入口 | OpenHarmony/foundation/arkui/ace_engine/interfaces/inner_api/ui_session/ui_content_proxy.h:60 | `UIContentServiceProxy` 对 SA 暴露 `GetWebViewTranslateText`、`StartWebViewTranslate`、`EndWebViewTranslate`、`ResetTranslateText*`、`SendTranslateResult` 等接口 |
| SA 侧接口定义 | OpenHarmony/foundation/arkui/ace_engine/interfaces/inner_api/ui_session/ui_content_service_interface.h:266 | `IUiContentService` 定义 Web 文本获取、连续翻译、回填、Reset 接口 |
| SA 回调保存对象 | OpenHarmony/foundation/arkui/ace_engine/interfaces/inner_api/ui_session/ui_content_proxy.h:104 | `UIContentServiceProxy` 持有 `sptr<UiReportStub> report_`，用于保存 SA 侧回调 |
| 回调注册实现 | OpenHarmony/foundation/arkui/ace_engine/adapter/ohos/entrance/ui_session/ui_content_proxy.cpp:690 | `GetWebViewTranslateText` 在发送 IPC 前调用 `report_->RegisterGetTranslateTextCallback(eventCallback)` |
| 连续翻译回调注册 | OpenHarmony/foundation/arkui/ace_engine/adapter/ohos/entrance/ui_session/ui_content_proxy.cpp:808 | `StartWebViewTranslate` 注册同一个文本回调并发送 `CONTINUE_GET_WEB_TEXT` 请求 |
| 回调存储与分发 | OpenHarmony/foundation/arkui/ace_engine/interfaces/inner_api/ui_session/ui_report_stub.h:247 | `UiReportStub` 提供 `RegisterGetTranslateTextCallback`，并通过 `SendWebText` 触发 `getTranslateTextCallback_` |
| UI 上报代理 | OpenHarmony/foundation/arkui/ace_engine/interfaces/inner_api/ui_session/ui_report_proxy.h:97 | `UiReportProxy::SendWebText` 是 UI 侧向 SA 回传文本的 ReportService 接口 |
| UI 上报实现 | OpenHarmony/foundation/arkui/ace_engine/adapter/ohos/entrance/ui_session/ui_report_proxy.cpp:387 | `SendWebText` 将文本和 nodeId 写入 parcel，并通过 `SEND_TEXT` 上报 |
| 现有 manager 分发 | OpenHarmony/foundation/arkui/ace_engine/interfaces/inner_api/ui_session/ui_session_manager.h:200 | `UiSessionManager` 提供 `GetWebTranslateText`、`SendWebTextToAI`、`SendTranslateResult`、`ResetTranslate` 等内部转发点 |
| 现有 Translate Manager 抽象 | OpenHarmony/foundation/arkui/ace_engine/interfaces/inner_api/ui_session/ui_translate_manager.h:29 | 已有 `GetTranslateText`、`SendTranslateResult`、`ResetTranslate` 等虚接口 |
| 现有 Web 实现 | OpenHarmony/foundation/arkui/ace_engine/adapter/ohos/entrance/ace_translate_manager.cpp:84 | 当前实现遍历 Web listener，提取 Web 文本并通过 `UiSessionManager::SendWebTextToAI` 上报 |
| Pattern 翻译扩展点约束 | OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/pattern.h | Web 旧翻译 hook 不应继续挂在 `Pattern` 基类；本需求约束统一迁移到 `PageTranslateNode` 抽象接口，避免扩大所有 Pattern 默认虚表 |
| 模拟 SA dump 入口 | OpenHarmony/foundation/arkui/ace_engine/interfaces/inner_api/ui_session/ui_session_sample/ui_sa_service.cpp:110 | `UiSaService::DUMP_MAP` 将 dump 命令映射到模拟 SA 调用能力，现有示例包含 `StartWebViewTranslate` |
| 模拟 SA dump 调度 | OpenHarmony/foundation/arkui/ace_engine/interfaces/inner_api/ui_session/ui_session_sample/ui_sa_service.cpp:180 | `UiSaService::Dump` 获取焦点窗口对应 `IUiContentService`，按 dump 参数触发对应 handler |

### 初始范围

**包含：**
- 新增或扩展 Uisession 系统 SA innerAPI，用于 ArkUI 原生文本展示控件翻译。
- 新增接口能力覆盖现有 Web 翻译能力，作为统一入口承载 Web 与 ArkUI 原生文本展示控件。
- Web 内容翻译保留现有脚本注入实现路径。
- SA 通过入参选择处理范围：页面所有内容，或仅 ArkUI 原生文本展示控件。
- 提供单次获取当前页面可翻译文本节点的能力。
- 提供 `StartTranslate` 和 `EndTranslate` 连续翻译会话能力。
- 提供 `Reset` 能力，将运行时译文展示恢复为原文展示。
- `StartTranslate` 后获取当前可翻译文本节点，后续有变化时主动增量上报。
- 提供异常恢复能力：当 SA 意外死亡或 IPC 连接断开时，如果当前存在已翻译展示或连续翻译会话，必须在死亡监听中恢复原文展示并清理会话状态。
- 提供终端设备模拟验证能力：`interfaces/inner_api/ui_session/ui_session_sample` 下的模拟 SA dump 能触发新增接口及其参数，包括单次获取、StartTranslate、EndTranslate、Reset、范围入参和回填能力。
- 支持 `Text`、子 `Span` / styled string 文本、`RichEditor` 的只读展示内容，以及空内容 `TextInput` 当前实际展示的 placeholder 提示文本。
- SA 按节点 ID 批量回填译文，ArkUI 只做运行时临时译文布局展示。

**明确不包含：**
- 不覆盖输入类控件的用户可编辑文本，例如 `TextInput`、`TextArea` 中用户已输入或应用设置的可编辑内容；空内容 `TextInput` 当前实际展示的 placeholder 提示文本属于展示提示文本，可进入翻译范围。
- 不覆盖 Canvas、自绘文本、图片文字 OCR。
- 不重写 Web 翻译底层实现；Web 仍通过现有脚本注入链路提取和回填。
- 不新增 ArkTS/Public API，不向三方应用开放。
- 不修改应用设置的原始文本属性。
- 不要求节点失效时整批失败或强制重试。

### 初始假设

| 假设 | 类型 | 验证方式 | 状态 |
|------|------|----------|------|
| 现有 Uisession 翻译链路可作为扩展基础，且新接口需覆盖现有 Web 能力 | 技术 | 源码：ui_content_proxy.h、ui_report_stub.h、ui_report_proxy.h、ui_session_manager.h、ui_translate_manager.h、ace_translate_manager.cpp；用户确认 Web 翻译通过脚本注入实现 | 已验证 |
| ArkUI 原生文本展示控件需要运行时译文布局展示而非属性替换 | 兼容性 | 用户确认 | 已验证 |
| 权限边界沿用系统 SA 使用的 Uisession innerAPI | 安全 | 用户确认 | 已验证 |
| 文本变化主动上报仅在 StartTranslate 到 EndTranslate 期间生效 | 业务 | 用户确认 | 已验证 |

### 初始分级判断

| 判断项 | 结果 | 依据 |
|--------|------|------|
| 复杂度 | 标准 + 安全/性能专项 | 单仓特性，但涉及 System innerAPI、隐私文本跨进程传输、文本变化热路径和运行时布局刷新；按关键风险增加安全/性能/DFX专项审查，不升级为“关键”的理由是未新增 Public API、未跨仓/跨子系统落地、无持久化数据迁移，且调用边界仍限系统 SA innerAPI |
| 涉及仓数量 | 1 | OpenHarmony/foundation/arkui/ace_engine |
| 是否涉及 Public/System API | 是 | 涉及系统 SA 使用的 Uisession innerAPI；不涉及 Public API |
| 是否涉及安全/性能关键路径 | 是 | 文本内容跨进程传输涉及隐私边界；文本变化上报和布局刷新涉及性能预算 |
| 是否跨 SIG | 待确认 | 当前仅识别 ArkUI/ACE；是否需要 SA 侧同步由下游设计确认 |

### 进入澄清条件

- [x] 原始问题和期望结果已记录
- [x] 需求来源和责任人已明确
- [x] 初始范围和不包含项已记录
- [x] 关键假设和待澄清问题已列出
- [x] 复杂度有判断或明确为待定

---

## 二、澄清记录

### 待澄清问题

| 编号 | 问题 | 为什么需要澄清 | 状态 |
|------|------|----------------|------|
| Q-1 | 文本展示控件范围如何定义 | 影响节点遍历、数据模型和测试覆盖 | 已澄清 |
| Q-2 | 提取和回填调用模型 | 影响 innerAPI 形态与 IPC 数据结构 | 已澄清 |
| Q-3 | 回填是否修改原属性 | 影响兼容性、Reset/End 语义和布局实现 | 已澄清 |
| Q-4 | 是否覆盖 RichEditor | 影响 Pattern 覆盖范围 | 已澄清 |
| Q-5 | 权限/API 边界 | 影响是否新增 Public/System API 或权限 | 已澄清 |
| Q-6 | 连续翻译期间文本变化策略 | 影响是否需要主动上报和会话状态 | 已澄清 |
| Q-7 | 主动上报粒度 | 影响 IPC 数据量和同步语义 | 已澄清 |
| Q-8 | 节点失效或内容不匹配时如何处理 | 影响回填容错策略 | 已澄清 |
| Q-9 | SA 意外死亡时如何恢复 | 影响异常恢复、DeathRecipient 和会话状态清理 | 已澄清 |
| Q-10 | 终端设备如何模拟测试新增接口 | 影响真机验证入口、dump 命令和参数覆盖 | 已澄清 |

### 讨论记录

| 日期 | 参与人 | 讨论主题 | 结论 | 后续动作 |
|------|--------|----------|------|----------|
| 2026-05-13 | 用户、AI | 控件范围 | 覆盖 ArkUI 原生文本展示控件，不覆盖输入类控件的用户可编辑文本和自绘；首期包含 Text/Span/styled string/RichEditor 只读展示内容 | 写入基线 |
| 2026-05-13 | 用户、AI | 调用模型 | 使用通用文本节点模型：稳定 nodeId、文本节点列表、批量回填 | Stage 2 设计数据模型 |
| 2026-05-13 | 用户、AI | 回填语义 | 不修改原有属性，仅运行时临时译文布局展示，Reset/End 恢复原文 | Stage 2 设计恢复机制 |
| 2026-05-13 | 用户、AI | 权限/API | 沿用 Uisession 系统 SA innerAPI，不新增 ArkTS/Public API 或应用权限 | Stage 2 设计 IPC 接口 |
| 2026-05-13 | 用户、AI | 连续翻译 | 提供单次获取页面文本、StartTranslate、EndTranslate；Start 后获取当前节点，后续新节点渲染和内容变化主动上报，End 后恢复原文 | Stage 2 设计状态机 |
| 2026-05-13 | 用户、AI | 容错 | 节点离树、内容变化或 ID 不匹配时忽略该条结果，不影响其他节点，记录日志 | Stage 2 设计错误语义 |
| 2026-05-13 | 用户、AI | 现有 IPC 链路证据补充 | SA 暴露接口在 `ui_content_proxy.h`；SA 回调保存在 `UiReportStub`；UI 上报接口是 `ui_report_proxy.h` | 修正背景证据和 Stage 2 设计输入 |
| 2026-05-13 | 用户、AI | Web 兼容与范围入参 | 新增接口能力要覆盖现有 Web 能力；Web 翻译继续通过脚本注入实现；SA 可通过入参选择页面所有内容或仅 ArkUI 原生控件 | 更新范围、AC 和 Stage 2 设计输入 |
| 2026-05-13 | 用户、AI | SA 意外死亡恢复 | 如果当前处于已翻译状态或连续翻译会话，SA 意外死亡时必须在死亡监听中恢复原文展示并清理状态 | 更新异常 AC 和 Stage 2 设计输入 |
| 2026-05-13 | 用户、AI | 模拟 SA dump 验证 | 为了在终端设备模拟测试，需要在 `ui_session_sample` 增加 dump 能力，新增接口和参数可通过模拟 SA dump 触发 | 更新可测试性 AC 和 Stage 2 设计输入 |

### 功能范围确认

| 问题 | 回答 | 确认人 | 状态 |
|------|------|--------|------|
| 核心功能包含哪些？ | 统一接口下的单次页面文本获取、StartTranslate、EndTranslate、Reset、变化增量上报、批量译文回填、SA 死亡异常恢复、模拟 SA dump 触发验证；通过入参选择页面所有内容或仅 ArkUI 原生文本展示控件 | 用户 | 已确认 |
| 明确不包含哪些？ | 输入类控件的用户可编辑文本、自绘文本、三方 Public API、原属性替换、Canvas/OCR、Web 脚本注入底层重写 | 用户 | 已确认 |
| 是否有分期策略？ | 首期覆盖 Text/Span/styled string/RichEditor 只读展示内容；补充覆盖空内容 TextInput 当前实际展示的 placeholder 提示文本 | 用户 | 已确认 |

### 子系统影响

| 问题 | 回答 | 确认人 | 状态 |
|------|------|--------|------|
| 涉及哪些子系统？ | ArkUI ACE Engine，Uisession innerAPI，OHOS entrance adapter，NG Text/RichEditor/TextField Pattern | AI 基于源码识别 | 已确认 |
| 是否需要新增子系统或部件？ | 否，预计在现有 ace_engine 内扩展 | AI 基于源码识别 | 已确认 |

### API 变更评估

| 问题 | 回答 | 确认人 | 状态 |
|------|------|--------|------|
| 是否需要新增/修改 Public API？ | 否 | 用户 | 已确认 |
| 是否需要新增 System API？ | 是，扩展系统 SA 使用的 Uisession innerAPI/IPC 接口 | 用户 | 已确认 |
| 是否会废弃已有 API？ | 否，现有 Web 能力需兼容 | 用户 | 已确认 |
| 是否需要新增权限声明？ | 否，沿用现有 Uisession 系统 SA 调用边界 | 用户 | 已确认 |

### 兼容性与非功能需求

| 类别 | 核心问题 | 结论 | 确认人 | 状态 |
|------|----------|------|--------|------|
| 兼容性 | 是否破坏现有 Web 翻译接口、Web 脚本注入实现和 ArkUI 文本属性语义 | 不破坏；新增接口能力覆盖 Web 现有能力，Web 仍通过脚本注入实现；ArkUI 译文只做运行时展示，不改原属性 | 用户 | 已确认 |
| 性能 | 页面文本获取、变化上报、译文布局是否影响热路径 | 需要在 Stage 2 明确增量上报、去重和布局刷新预算 | AI | 已确认 |
| 安全 | 文本内容跨进程给系统 SA 是否需要新权限 | 不新增权限，沿用系统 SA innerAPI 边界；Stage 2 明确隐私日志规则 | 用户 | 已确认 |
| 可靠性 | 节点变化导致回填失败如何恢复；SA 死亡时如何恢复 | 单条回填失败忽略并记录日志，不影响其他节点；SA 意外死亡或连接断开时，死亡监听必须恢复原文展示并清理翻译会话状态 | 用户 | 已确认 |

### 依赖与风险

| 依赖项 | 类型 | 说明 | 状态 |
|--------|------|------|------|
| Uisession IPC content proxy/stub | 编译/运行 | SA 侧调用入口在 `UIContentServiceProxy` / `IUiContentService`，需要新增或扩展接口码、parcel 数据结构和兼容处理 | 已确认 |
| Uisession report proxy/stub | 编译/运行 | UI 侧文本上报通过 `UiReportProxy` / `ReportService`，SA 回调保存在 `UiReportStub` | 已确认 |
| UiTranslateManagerImpl | 运行 | 需要管理统一翻译 listener、会话状态和回填分发；listener 统一保存 `WeakPtr<PageTranslateNode>`，Web 旧脚本注入 hook 和 ArkUI 原生文本节点均通过该接口进入 | 已确认 |
| Text/RichEditor/TextField Pattern | 运行 | 需要提供可翻译文本获取、运行时译文展示、Reset/End 恢复能力；TextField 仅处理空内容 TextInput placeholder，用户输入内容排除 | 已确认 |
| ui_session_sample 模拟 SA | 运行/验证 | 需要在 `UiSaService::DUMP_MAP` 和对应 handler 中新增 dump 命令，触发新增接口及参数 | 已确认 |

| 风险 | 类型 | 影响 | 缓解措施 | 状态 |
|------|------|------|----------|------|
| 文本内容变化频繁导致 IPC 过量 | 性能 | 可能增加主线程和跨进程压力 | Stage 2 设计去重、节流或合并策略；AC 覆盖仅 Start 后上报 | 已确认 |
| 文本展示控件仅占位布局但未实际绘制文本 | 性能/正确性 | 可能提前上报不可见或尚未绘制内容，增加 IPC 并触发无效翻译 | 上报前要求 Pattern/ContentChangeManager 确认存在实际文本绘制内容；仅占位布局不上报，待实际绘制文本时再上报 | 已确认 |
| 译文长度变化导致布局抖动 | 体验/性能 | 页面布局可能频繁刷新 | 运行时译文触发布局刷新，限制只在译文实际变化时刷新 | 已确认 |
| 节点 ID 复用或节点离树导致回填错误 | 可靠性 | 可能展示错误译文 | 回填时校验节点存在和内容版本，失败单条忽略 | 已确认 |
| 日志泄露原文或译文 | 安全 | 文本隐私风险 | Stage 2 明确日志不打印正文，仅记录长度、节点 ID、错误码 | 已确认 |
| SA 意外死亡后译文残留 | 可靠性 | 页面可能持续显示临时译文，且后续变化上报状态不一致 | 在 DeathRecipient 或连接断开监听中调用全量恢复原文和会话清理逻辑；AC 覆盖死亡恢复 | 已确认 |
| 缺少真机模拟入口导致功能不可验证 | 测试 | 新增接口只能通过真实 SA 或单测验证，终端问题定位困难 | `ui_session_sample` 增加 dump 命令覆盖新增接口、范围入参、回填和 Reset/End | 已确认 |

### AC 完整性

- [x] 每个用户故事有验收标准
- [x] AC 全部使用 WHEN/THEN 格式
- [x] 覆盖正常流程、异常流程、边界条件
- [x] AC 可测试、可度量

### 澄清结论

- [x] 功能范围已完全明确
- [x] 子系统影响已识别
- [x] API 变更已评估
- [x] 兼容性和非功能需求已确认
- [x] 依赖和风险已识别且有缓解方案
- [x] AC 完整可测试

**结论:** 通过

---

## 三、需求基线

### 基线信息

| 字段 | 内容 |
|------|------|
| 基线版本 | v1.0 |
| 基线日期 | 2026-05-13 |
| Owner | TBD |
| 确认人 | 用户 |
| 复杂度 | 标准 + 安全/性能专项 |
| Profile | arkui |
| 目标发行版本 | TBD |
| 版本状态 | proposed |

### 问题陈述

现有 Uisession 连续翻译能力主要面向 Web 场景，系统 SA 可以获取 Web 文本并回填译文，但 ArkUI 原生文本展示控件缺少统一的文本节点提取、变化上报和临时译文展示能力。该需求要求在 ace_engine 内扩展系统 SA 使用的 Uisession innerAPI 和文本 Pattern 支撑，使系统连续翻译覆盖 ArkUI 原生文本展示节点，同时保持应用原始文本属性不变。

### 目标和成功指标

| 目标 | 成功指标 | 验证方式 |
|------|----------|----------|
| 支持系统 SA 单次获取页面文本 | 能按 SA 入参返回页面所有可翻译内容，或仅 ArkUI 原生 Text/Span/styled string/RichEditor 只读展示文本节点以及空内容 TextInput placeholder 提示文本列表 | Uisession 单元测试 + Pattern 单元测试 |
| 支持连续翻译会话 | Start 后按入参获取当前节点，新增/变化节点主动上报；End 后停止上报并恢复原文展示 | Uisession/Pattern 单元测试 |
| 支持临时译文展示 | 回填译文后布局展示译文，但原 Text/Span/RichEditor/TextInput placeholder 属性保持原文，用户输入内容不被翻译或覆盖 | Pattern 单元测试 |
| 支持 Reset 恢复 | Reset 单节点或全量后恢复原文展示 | Pattern 单元测试 |
| 兼容并覆盖现有 Web 翻译能力 | 新增接口在页面所有内容模式下覆盖 Web GetTranslateText/SendTranslateResult/ResetTranslate 能力；Web 脚本注入实现不回退 | 现有 Web 相关测试或新增回归测试 |
| 支持异常恢复 | SA 意外死亡或 IPC 连接断开后，已翻译内容恢复原文展示，连续翻译会话停止 | DeathRecipient/Manager 单元测试或模拟连接断开测试 |
| 支持终端模拟验证 | 模拟 SA dump 能触发新增接口及参数，并打印文本获取、变化上报、回填、Reset/End 结果 | 真机 dump 命令验证 |
| 支持 Host Preview 验证 | PreviewerCLI 可通过 `remoteRequest` 模拟触发页面文本获取、Start、译文回填、Reset 和 End，并通过 simpleTree 辅助核对 nodeId | `examples/UISessionTranslate` Host Preview 脚本 |

### 用户故事与 AC

| Story ID | 用户故事 | 优先级 |
|----------|----------|--------|
| US-1 | 作为系统 SA，我想按入参单次获取当前页面全部可翻译内容或仅 ArkUI 原生可翻译文本节点，以便发起一次性翻译或建立连续翻译基线 | P0 |
| US-2 | 作为系统 SA，我想按入参启动和结束页面文本连续翻译会话，以便在会话期间持续同步对应范围内新增和变化文本 | P0 |
| US-3 | 作为终端用户，我想看到译文临时替换原文布局展示，以便理解页面内容且不影响应用原始状态 | P0 |
| US-4 | 作为系统 SA，我想批量回填译文且局部失败不影响其他节点，以便在动态页面中稳定工作 | P1 |
| US-5 | 作为终端用户，我希望系统翻译服务异常退出后页面恢复原文展示，以免临时译文状态残留 | P0 |
| US-6 | 作为系统开发者，我想通过模拟 SA 的 dump 命令在终端设备触发新增翻译接口和参数，以便进行真机验证和问题定位 | P0 |
| US-7 | 作为系统开发者，我想在 Host Preview 环境通过脚本模拟 Uisession 翻译调用，以便不依赖真机 SA 快速验证页面文本提取和译文回填链路 | P0 |

| AC编号 | 验收标准 | 类型 | 关联Story |
|--------|----------|------|-----------|
| AC-1 | WHEN 系统 SA 调用单次页面文本获取接口且入参为仅 ArkUI 原生控件 THEN ArkUI 返回当前页面中有实际文本绘制内容的可翻译 Text、Span/styled string、RichEditor 只读展示文本节点，以及空内容 TextInput 当前实际展示的 placeholder 提示文本节点列表，并包含每个节点的稳定 nodeId 和当前可翻译文本 | 正常 | US-1 |
| AC-2 | WHEN 系统 SA 调用单次页面文本获取接口且入参为页面所有内容 THEN ArkUI 返回 Web 可翻译内容和 ArkUI 原生可翻译文本节点；其中 Web 内容沿用现有脚本注入方式提取 | 正常 | US-1 |
| AC-3 | WHEN 页面包含 TextInput/TextArea 的用户可编辑文本、Canvas、自绘文本或图片文字 THEN 单次页面文本获取结果不包含这些非范围内文本；WHEN TextInput 内容为空且 placeholder 提示文本实际展示 THEN placeholder 可作为可翻译展示文本返回 | 边界 | US-1 |
| AC-4 | WHEN 系统 SA 调用 StartTranslate 且入参为仅 ArkUI 原生控件 THEN ArkUI 进入连续翻译状态，并上报当前 ArkUI 原生可翻译文本节点列表作为会话初始数据 | 正常 | US-2 |
| AC-5 | WHEN 系统 SA 调用 StartTranslate 且入参为页面所有内容 THEN ArkUI 进入连续翻译状态，并上报当前 Web 可翻译内容和 ArkUI 原生可翻译文本节点作为会话初始数据；其中 Web 内容沿用现有脚本注入方式处理 | 正常 | US-2 |
| AC-6 | WHEN StartTranslate 后有新的 Text、Span/styled string、RichEditor 只读展示节点或空内容 TextInput placeholder 节点上树并产生实际文本绘制且会话范围包含 ArkUI 原生控件 THEN ArkUI 主动向 SA 上报该变化节点的 nodeId、当前可翻译文本和 version；变化原因仅作为 UI 内部 DFX/去重信息 | 正常 | US-2 |
| AC-7 | WHEN StartTranslate 后已有范围内 ArkUI 原生文本展示节点内容变化、或空内容 TextInput 当前实际展示的 placeholder 变化并产生实际文本绘制且会话范围包含 ArkUI 原生控件 THEN ArkUI 主动向 SA 上报该变化节点的 nodeId、当前可翻译文本和 version；用户可编辑文本变化不触发翻译上报 | 正常 | US-2 |
| AC-8 | WHEN StartTranslate 后 Web 内容变化且会话范围为页面所有内容 THEN Web 内容变化继续按现有 Web 脚本注入翻译链路处理和上报 | 正常 | US-2 |
| AC-9 | WHEN EndTranslate 被调用 THEN ArkUI 停止后续文本变化主动上报，并将所有运行时译文展示恢复为原文展示；Web 翻译结束沿用现有 End Web 翻译链路 | 正常 | US-2/US-3 |
| AC-10 | WHEN Reset 被调用且指定某个 nodeId THEN ArkUI 仅将该节点运行时译文展示恢复为原文展示，并保持其他已翻译节点状态不变 | 正常 | US-3 |
| AC-11 | WHEN Reset 被调用且目标为全量 THEN ArkUI 将所有运行时译文展示恢复为原文展示，Web 内容按现有 Reset 行为恢复 | 正常 | US-3 |
| AC-12 | WHEN 系统 SA 下发 ArkUI 原生节点译文结果 THEN ArkUI 按 nodeId 将译文用于运行时布局展示，但不修改应用原始文本属性；若译文为 `\\uXXXX` unicode 转义字面量，回填前应解码为真实 UTF-8 文本展示，非法 unicode 转义保持字面量且不影响其他节点 | 正常 | US-3 |
| AC-13 | WHEN 译文回填时目标 ArkUI 原生节点已经离树、内容版本不匹配或 nodeId 不存在 THEN ArkUI 忽略该条结果、记录非正文日志，并继续处理同批次其他结果 | 异常 | US-4 |
| AC-14 | WHEN 未调用 StartTranslate 或 EndTranslate 已完成后文本节点上树或内容变化 THEN ArkUI 不主动上报变化文本 | 边界 | US-2 |
| AC-14a | WHEN 文本展示类控件仅进行占位布局但没有实际文本内容绘制 THEN 单次获取和连续翻译增量均不上报该节点；WHEN 后续产生实际文本绘制 THEN 按 snapshot 或增量规则上报 | 边界 | US-1/US-2 |
| AC-15 | WHEN 现有 Web 翻译接口或新增统一接口的页面所有内容模式被调用 THEN 现有 Web 文本提取、脚本注入回填和 Reset 行为保持兼容 | 回归 | US-1/US-2 |
| AC-16 | WHEN SA 进程意外死亡或 IPC 连接断开且当前存在已翻译展示 THEN ArkUI 在死亡监听处理流程中恢复所有临时译文为原文展示，并清理翻译会话状态 | 异常 | US-5 |
| AC-17 | WHEN SA 进程意外死亡或 IPC 连接断开且当前处于 StartTranslate 连续翻译状态 THEN ArkUI 停止后续文本变化主动上报，并清理已注册的连续翻译状态 | 异常 | US-5 |
| AC-18 | WHEN 系统开发者在终端通过模拟 SA dump 命令触发单次页面文本获取并指定范围入参 THEN dump handler 调用新增单次获取接口，并在日志中输出回调 nodeId、文本长度或安全摘要、范围参数和结果状态 | 验证 | US-6 |
| AC-19 | WHEN 系统开发者在终端通过模拟 SA dump 命令触发 StartTranslate 或 EndTranslate 并指定范围入参 THEN dump handler 调用新增连续翻译接口，并能接收和打印初始文本节点及后续变化上报的安全摘要 | 验证 | US-6 |
| AC-20 | WHEN 系统开发者在终端通过模拟 SA dump 命令触发 Reset 或 SendTranslateResult THEN dump handler 调用对应新增接口并支持传入 nodeId、译文或批量结果参数，用于验证恢复原文和译文回填 | 验证 | US-6 |
| AC-21 | WHEN 系统 SA 调用当前 Ability 语言地区信息获取接口 THEN ArkUI 返回当前 Ability 实例实际生效的 language 和 region，值来自该实例资源配置/配置更新后的生效 locale，而不是直接读取系统全局语言 | 正常 | US-6 |
| AC-22 | WHEN 当前 Ability 语言地区信息为空、配置尚未初始化或当前实例不可用 THEN 接口返回失败或空字段并记录非正文日志，不影响翻译会话状态 | 异常 | US-6 |
| AC-23 | WHEN 系统开发者在 Host Preview 中启动 `examples/UISessionTranslate` 并通过 PreviewerCLI `remoteRequest pageTranslate/getText` 指定 ArkUI scope THEN 返回真实 ArkUI 文本节点的 nodeId、text、version，且存在真实文本时不得混入 `nodeId=-1,text=empty,version=0` 空哨兵 | 验证 | US-7 |
| AC-24 | WHEN 系统开发者在 Host Preview 中通过 `remoteRequest pageTranslate/sendResult` 向获取到的 nodeId/version 发送译文 THEN Preview 环境触发统一译文回填路径，并可继续通过 `reset` 和 `end` 恢复现场 | 验证 | US-7 |
| AC-25 | WHEN 系统开发者在 Host Preview 中通过 `inspector --business simpleTree` 获取可见控件树 THEN 可用该树核对 getText 返回的真实文本节点 id，辅助定位 Preview 侧文本提取问题 | 验证 | US-7 |

### 变更控制记录

| 变更项 | 日期 | 原因 | 影响 | 状态 |
|--------|------|------|------|------|
| AC-21/AC-22 当前 Ability 语言地区查询 | 2026-05-16 | 用户新增 innerAPI 要求：SA 需获取当前 Ability 实例生效 language/region，且该查询是简单同步 IPC 业务 | 范围新增，纳入同一 Feature 的原因是其入口、连接对象、sample SA dump 和当前 instance 分发均复用 Uisession innerAPI 链路；实现与翻译状态解耦，不进入文本遍历、回填或连续翻译会话 | Approved |
| AC-23/AC-24/AC-25 Host Preview 验证 | 2026-05-22 | 用户已在另一会话搭建 Preview 验证方式并新增 TASK-007，要求将 Preview 验证纳入相关设计文档，并提供独立测试应用与脚本 | 范围新增为验证方式，不新增产品接口；用于在 host 上通过 PreviewerCLI `remoteRequest` 模拟 Uisession 获取文本和发送译文，补充真机 dump 之外的快速回归路径 | Approved |
| AC-12 unicode 转义译文兼容 | 2026-05-25 | 真机/脚本验证发现回填译文可能显示为 `\\uXXXX` 字符码而非中文 | 明确 `SendPageTranslateResult` 对译文字段做局部 unicode 转义字面量解码，并纳入 Uisession 单测、Host Preview 和真机 dump 验证 | Approved |
| TextInput placeholder 翻译边界 | 2026-05-23 | 用户新增功能点：`TextInput` 内预置提示文本应能被提取并翻译，但不翻译用户填充内容 | 范围精炼：输入类控件的用户可编辑文本仍排除；空内容 `TextInput` 当前实际展示的 placeholder 作为展示提示文本纳入 ArkUI 文本节点提取、连续翻译、临时译文展示和 Preview 验证 | Approved |

### 范围边界

**包含：** Uisession innerAPI/IPC 扩展、SA 入参控制处理范围、Web 现有脚本注入翻译能力覆盖与兼容、UiTranslateManager 会话状态、ArkUI 文本展示节点收集与监听、Text/Span/styled string/RichEditor 只读展示文本和空内容 TextInput placeholder 提示文本的临时译文布局展示、Reset/End 恢复、SA 死亡异常恢复、变化增量上报、当前 Ability 实例语言地区同步查询、模拟 SA dump 验证入口、Host Preview `remoteRequest` 验证应用与脚本。

**不包含：** ArkTS/Public API、新权限、输入类控件用户可编辑文本、自绘文本、OCR、Web 脚本注入底层重写、SA 侧翻译算法。

**分期策略（如适用）：**

| 阶段 | 范围 | 不做 | 进入条件 |
|------|------|------|----------|
| 首期 | 统一接口覆盖 Web 现有翻译能力和 ArkUI Text、Span/styled string、RichEditor 只读展示内容、空内容 TextInput placeholder 提示文本；SA 入参选择页面所有内容或仅 ArkUI 原生控件；单次获取、Start/End、Reset、变化增量上报、批量回填；当前 Ability 实例 language/region 查询；模拟 SA dump 触发新增接口及参数；Host Preview 脚本模拟 getText/start/sendResult/reset/end | 输入类控件用户可编辑文本、自绘文本、三方 API、Web 脚本注入底层重写；Previewer remoteRequest 不作为正式产品接口 | Stage 2 设计通过 |

### 影响范围

| 子系统 | 仓库 | 模块/路径 | 影响类型 | Owner |
|--------|------|-----------|----------|-------|
| ArkUI ACE Engine | OpenHarmony/foundation/arkui/ace_engine | interfaces/inner_api/ui_session/ui_content_proxy.h, ui_content_service_interface.h | SA 侧 innerAPI/IPC 入口新增或扩展 | TBD |
| ArkUI ACE Engine | OpenHarmony/foundation/arkui/ace_engine | interfaces/inner_api/ui_session/ui_report_proxy.h, ui_report_stub.h | UI 到 SA 文本上报和回调保存新增或扩展 | TBD |
| ArkUI ACE Engine | OpenHarmony/foundation/arkui/ace_engine | adapter/ohos/entrance/ui_session | Content Stub/Proxy、Report Stub/Proxy、Manager 实现 | TBD |
| ArkUI ACE Engine | OpenHarmony/foundation/arkui/ace_engine | adapter/ohos/entrance/ace_translate_manager.cpp | Translate manager 会话与分发 | TBD |
| ArkUI ACE Engine | OpenHarmony/foundation/arkui/ace_engine | interfaces/inner_api/ui_session/ui_session_sample | 模拟 SA dump 命令和 handler 新增 | TBD |
| ArkUI ACE Engine | OpenHarmony/foundation/arkui/ace_engine | examples/UISessionTranslate, adapter/preview/entrance, ide/tools/previewer | Host Preview 验证应用、脚本和 PreviewerCLI 模拟调用链路 | TBD |
| ArkUI ACE Engine | OpenHarmony/foundation/arkui/ace_engine | adapter/ohos/entrance/ui_content_impl.cpp, ui_session_manager_ohos.* | 当前 Ability 实例语言地区同步查询回调和当前 instance 分发 | TBD |
| ArkUI ACE Engine | OpenHarmony/foundation/arkui/ace_engine | frameworks/core/components_ng/pattern/text | Text/Span/styled string 支撑 | TBD |
| ArkUI ACE Engine | OpenHarmony/foundation/arkui/ace_engine | frameworks/core/components_ng/pattern/rich_editor | RichEditor 只读展示支撑 | TBD |
| ArkUI ACE Engine | OpenHarmony/foundation/arkui/ace_engine | frameworks/core/components_ng/pattern/text_field | TextInput 空内容 placeholder 提示文本支撑；用户可编辑文本排除 | TBD |
| ArkUI ACE Engine | OpenHarmony/foundation/arkui/ace_engine | test/unittest | 单元测试和回归测试 | TBD |

### 不涉及项确认

| 维度 | 涉及？ | 依据 | 若涉及，进入哪个下游文档 |
|------|--------|------|--------------------------|
| 性能 | 是 | Start 后主动上报和译文布局刷新可能影响热路径 | design.md / spec.md |
| 安全与权限 | 是 | 文本内容跨进程传输给系统 SA，需限制日志和调用边界 | design.md / spec.md |
| 兼容性 | 是 | 需保持现有 Web 翻译能力和 ArkUI 原属性语义 | spec.md |
| API/SDK | 是 | 涉及 Uisession innerAPI，不涉及 Public API | design.md / spec.md |
| IPC/跨进程 | 是 | SA 通过 Uisession IPC 调用和接收文本 | design.md |
| 构建与部件 | 是 | 可能涉及 BUILD.gn 测试目标更新 | design.md |
| 国际化/无障碍 | 是 | 翻译文本展示涉及多语言布局；首期不修改 accessibility text 和原始语义属性，无障碍树继续读取应用原文属性 | spec.md |
| 数据迁移 | N/A | 不持久化数据，不改应用模型 | N/A |

### 基线结论

需求基线通过，可以进入 Stage 2 规格化。Stage 2 必须产出 `design.md` 和 `spec.md`，重点明确：

- Uisession innerAPI 命名、参数、返回值和 IPC parcel 数据结构，明确 SA 调用入口在 `UIContentServiceProxy` / `IUiContentService`。
- UI 到 SA 的文本上报链路，明确回调保存在 `UiReportStub`，上报接口经 `UiReportProxy` / `ReportService`。
- SA 入参数据模型，明确页面所有内容和仅 ArkUI 原生控件两种处理范围。
- 新增统一接口如何覆盖现有 Web 翻译接口能力，并保持 Web 脚本注入实现兼容。
- DeathRecipient 或 IPC 连接断开监听中的异常恢复流程，确保 SA 死亡时恢复原文展示并停止连续翻译上报。
- `ui_session_sample` 模拟 SA dump 命令设计，确保新增接口和参数能在终端设备上触发。
- 文本节点对 SA 暴露的数据模型、UI 内部变化类型、内容版本或校验策略。
- Start/End/Reset 状态机。
- Text/Span/styled string/RichEditor 的运行时译文展示与恢复机制。
- 性能预算、隐私日志规则和 Web 兼容策略。
