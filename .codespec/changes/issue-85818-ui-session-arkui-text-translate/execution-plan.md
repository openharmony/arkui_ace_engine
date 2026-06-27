# 执行计划

> 将 Approved Spec 拆成可独立执行、可验证、可审查的 Task。Plan 已审批，允许按 Task 顺序进入生产代码实现。

## Plan 元数据

| 字段 | 内容 |
|------|------|
| Plan ID | PLAN-UISESSION-UNIFIED-TEXT-TRANSLATE |
| 关联 Feature/Bug | FEAT-UISESSION-UNIFIED-TEXT-TRANSLATE |
| 关联文档 | proposal.md / design.md / spec.md |
| 复杂度 | 标准 + 安全/性能专项 |
| 状态 | Approved |
| Owner | ACE/Uisession/Text 模块 Owner |

## 输入状态

| 输入 | 路径 | 要求状态 |
|------|------|----------|
| Proposal | `proposal.md` | Approved |
| Design | `design.md` | Approved |
| Spec | `spec.md` | Approved |

## AC 到 Task 追溯

| AC | 来源 | Task | 验证方式 | 覆盖 |
|----|------|------|----------|------|
| AC-1, AC-2, AC-3 | spec.md | TASK-001, TASK-002, TASK-003 | Uisession/manager/content_change 单测 | 是 |
| AC-4, AC-5, AC-6, AC-7, AC-8, AC-14, AC-14a | spec.md | TASK-002, TASK-003, TASK-004, TASK-005 | manager/Text/RichEditor/TextInput placeholder/Web 回归 | 是 |
| AC-9, AC-10, AC-11, AC-12, AC-13 | spec.md | TASK-002, TASK-004, TASK-005 | Pattern/manager 单测 | 是 |
| AC-15 | spec.md | TASK-002, TASK-006 | Web 回归 | 是 |
| AC-16, AC-17 | spec.md | TASK-001, TASK-002, TASK-003, TASK-004, TASK-005 | DeathRecipient/DFX 单测 | 是 |
| AC-18, AC-19, AC-20 | spec.md | TASK-006 | 真机 dump + hilog | 是 |
| AC-21, AC-22 | spec.md | TASK-001, TASK-002, TASK-006 | Uisession 单测 + 真机 dump | 是 |
| AC-23, AC-24, AC-25 | spec.md | TASK-007 | Host Preview remoteRequest + simpleTree | 是 |

## 首批实现边界

**首批必须实现：** 统一 innerAPI 和 report payload、当前 Ability 实例语言地区查询、`UIContentImpl` 启动期 callback 注册、`UiSessionManagerOhos` 会话/DFX/死亡恢复、`ContentChangeManager` ArkUI 文本节点快照和增量、Text/Span/styled string 运行时译文展示、RichEditor 只读展示翻译、空内容 TextInput placeholder 翻译、Web 兼容、sample SA dump、Host Preview 验证应用和脚本。

**可后置：** XComponent、CanvasNode、OCR、自绘文本、输入类控件用户可编辑文本、对外 ArkTS/Public API、多 SA 同时 owner 扩展、无障碍树同步临时译文。

**不建议延后：** 5s 译文等待 watchdog、`LargeStringAshmem` 大文本路径、SA death 恢复、实际文本绘制过滤、回填参数校验、单次 snapshot 版本/hash 校验和 Reset/End 恢复。

## 阶段计划

| 阶段 | 目标 | 关键 Task | 结束门槛 | 最小验证 |
|------|------|-----------|----------|----------|
| Phase-1 | IPC 与 manager 骨架 | TASK-001, TASK-002 | 新接口可编译，翻译 callback 注册/分发链路和 Ability language/region 同步 IPC 可单测 | 编译实际修改模块所属 so/组件目标和 Uisession 单测；必要时补 `ace_engine` 链接验证 |
| Phase-2 | ArkUI 原生文本能力 | TASK-003, TASK-004, TASK-005 | Text/RichEditor/TextInput placeholder snapshot、增量、回填、Reset 可单测 | 相关 unittest target |
| Phase-3 | 端到端验证 | TASK-006, TASK-007 | Web 兼容、sample dump 和 Host Preview remoteRequest 可触发统一接口 | unittest + 真机 dump 手工记录 + Host Preview 脚本 |

## Task 列表

| Task ID | 目标 | 文件范围 | AC 映射 | 前置依赖 | 完成判据 | 验证命令 |
|---------|------|----------|---------|----------|----------|----------|
| TASK-001 | 建立统一 IPC/API/report payload、Ability 语言地区接口与共享内存/DFX 基础 | `interfaces/inner_api/ui_session`, `adapter/ohos/entrance/ui_session` | AC-1, AC-2, AC-16 至 AC-22 | 无 | 新接口、parcel、翻译 callback、LargeStringAshmem、单次 Get callback timeout、真实节点译文等待 watchdog、result 参数校验、Ability language/region 同步 IPC 基础可编译并有单测 | 相关 ui_session/adapter so 目标 + Uisession 单测 |
| TASK-002 | 建立 manager 会话、启动期 callback 注册、Ability 语言地区读取、Web 兼容和死亡恢复 | `adapter/ohos/entrance/ui_content_impl.*`, `ace_container.cpp`, `ui_session_manager_ohos.*`, `ace_translate_manager.*`, `ui_translate_manager.h` | AC-4, AC-5, AC-8, AC-9, AC-15 至 AC-17, AC-21, AC-22 | TASK-001 | Start/End/Reset/Get 分发到当前 instance，连续翻译记录 owner pid 且初始无文本不自动 End，SA death 按 owner pid 恢复；Web 旧能力通过 `PageTranslateNode` hook 继续脚本注入且不回退；当前 Ability language/region 能按 instance 返回 | 相关 adapter/entrance so 目标 + manager/death 单测 |
| TASK-003 | 增强 `ContentChangeManager`，新增待翻译文本容器并实现快照/增量/版本/过滤 | `frameworks/core/components_ng/manager/content_change_manager`, `page_translate_node.h`, `pipeline_context.*`, 相关 test/mock | AC-1, AC-4, AC-6, AC-7, AC-10, AC-11, AC-13, AC-14, AC-14a | TASK-002 | translate 专用容器与纯 content change 容器隔离，容器仅保存 `WeakPtr<PageTranslateNode>`；无连续翻译任务时不写连续容器、不维护 pending；单次 Get 仅使用隔离 snapshot cache 并用 version/source hash 校验迟到译文；snapshot 和 Start 增量只上报实际绘制文本；空内容 TextInput placeholder 纳入，用户可编辑内容排除 | content_change_manager 单测 |
| TASK-004 | 实现 Text/Span/styled string 和 TextInput placeholder 运行时译文布局展示与恢复 | `frameworks/core/components_ng/pattern/page_translate/page_translate_node.h`, `frameworks/core/components_ng/pattern/text`, `frameworks/core/components_ng/pattern/text_field`, text/text_field tests | AC-1, AC-3, AC-6, AC-7, AC-10 至 AC-14a | TASK-003 | Text 不改原属性，译文参与布局，Reset/End/SA death 恢复，未实际绘制不上报；Text/TextField 按需实现 `PageTranslateNode`，不在 `Pattern` 基类扩默认翻译虚函数；TextInput 空内容 placeholder 可翻译，用户填充值不提取不覆盖 | text pattern + text_field/text_input 单测 |
| TASK-005 | 实现 RichEditor 只读展示内容翻译 | `frameworks/core/components_ng/pattern/rich_editor`, rich_editor tests | AC-1, AC-3, AC-6, AC-7, AC-10 至 AC-14a | TASK-003 | 仅只读展示内容进入翻译，编辑态排除，译文临时展示和恢复可验证 | rich_editor 单测 |
| TASK-006 | sample SA dump、Web 回归和端到端验证 | `interfaces/inner_api/ui_session/ui_session_sample`, Web/uisession tests | AC-15, AC-18, AC-19, AC-20, AC-21, AC-22 | TASK-001 至 TASK-005 | dump 可触发 Get/Start/End/Reset/回填/scope 和 Ability language/region 查询，Web 脚本注入路径兼容 | unittest + 真机 dump |
| TASK-007 | Host Preview 验证应用和脚本 | `adapter/preview/entrance`, `ide/tools/previewer`, `examples/UISessionTranslate` | AC-23, AC-24, AC-25 | TASK-001 至 TASK-005 | PreviewerCLI `remoteRequest pageTranslate/getText/start/collect/sendResult/reset/end` 可模拟触发统一翻译能力，`simpleTree` 可对照 nodeId 和临时译文字段；Demo 覆盖初始页面、动态新页面、Text/Span/TextInput placeholder、用户输入排除、List 滚动 repeat 文本进入视口、单节点 reset、全量 reset/end；脚本报告和截图固化 | `ohos-sdk` 编译 + `examples/UISessionTranslate/tools/host_preview/run_page_translate.sh` |

## 全局实现规则

| Rule ID | Must / Must Not |
|---------|-----------------|
| OH-ARCH-LAYERING | SA 只经 innerAPI/IPC 调用；Pattern 不直接调用 SA；UI 上报只经 `UiReportProxy` / `ReportService` |
| UI-THREAD | IPC stub 只解析参数和调用 `UiSessionManager`；实际 Pipeline/Pattern/ContentChangeManager 操作必须通过启动期 callback 切到 UI 线程 |
| DATA-MIN | 对翻译 SA 暴露 payload 仅 `nodeId/text/version`；`sourceType/changeType/scope` 只作 UI 内部 DFX/调度 |
| RUNTIME-ONLY | 译文只作为运行时展示状态参与布局，不替换原 Text/Span/RichEditor/TextInput placeholder 属性，不覆盖用户输入内容 |
| DRAWN-TEXT-ONLY | 仅实际文本绘制内容进入 snapshot/增量；占位布局但未绘制文本不上报 |
| BIG-TEXT-IPC | 大文本统一复用现有 `LargeStringAshmem` 共享内存方式，不新增分片协议 |
| DFX | 单次 Get 请求 timeout 清 callback、清一次性现场并移除调用方 pid；连续 Start 初始无文本不自动 End；译文等待 watchdog 默认 5s，仅对 `nodeId >= 0` 真实节点启动，SA 未死亡时只输出非正文告警 |
| WEB-COMPAT | `ARKUI_ARKWEB` 覆盖 ArkUI 原生文本和 Web 能力，Web 文本提取/回填继续走现有脚本注入路径；`XCOMPONENT`/`CANVAS_NODE` 仅预留 |
| ABILITY-LANGUAGE | 当前 Ability language/region 查询采用同步 IPC，只返回当前 instance 生效 locale，不读取系统全局语言替代实例配置，不影响翻译会话 |
| PREVIEW-VERIFY | Host Preview 验证只能作为开发测试入口；`remoteRequest business+method` 不作为正式产品接口；脚本只断言固定测试文本和安全摘要 |
| BUILD-MIN | 编译验证按实际修改代码选择最近的 GN so/组件目标；不默认编全量 `ace_engine` |
| ON-DEMAND-WRITE | 未 StartTranslate 时不得写连续 translate 容器、提取文本、维护 pending 或投递连续 translate 任务；单次 Get 只允许写隔离 snapshot cache，并在请求边界清理 |
| TRANSLATE-NODE-IFACE | ArkUI 翻译业务和 Web 旧脚本注入 hook 统一通过 `PageTranslateNode` 接口接入，manager 缓存接口弱引用；`Pattern` 不提供默认翻译虚函数 |
| SMALL-FUNCTION-REUSE | 共享逻辑抽成职责单一的小函数复用，避免复制分支；不得为复用新增无必要 manager 类 |

## Plan 自审清单

- [x] 每个 P0/P1 AC 至少映射到一个 Task
- [x] 每个 Task 文件范围明确
- [x] 每个 Task 明确前置依赖、非目标、完成判据和停止条件
- [x] 每个 Task 有验证命令
- [x] Task 粒度形成能力闭环
- [x] 没有 TBD/TODO/占位符
- [x] 没有要求 Agent 自行寻找未列出的上下文
- [x] 交接信息自包含，详见 `tasks/`，包含 TASK-001 至 TASK-007
- [x] 每个 Task 验证在完成时立即执行并记录证据，不得积压到阶段末尾批量补验
