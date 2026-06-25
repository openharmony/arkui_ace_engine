# Specify Gate

## 设计检查

| 检查项 | 结果 | 证据/理由 |
|--------|------|-----------|
| 分层调用合规 | 通过 | `design.md` 固化 SA -> `IUiContentService` -> `UiSessionManager` -> `UiTranslateManager` -> Pattern；UI 上报走 `ReportService` |
| 无跨层违规调用 | 通过 | 不新增三方/Public API；不从 Pattern 直接调用 SA，仅经 manager/report proxy |
| 子系统边界清晰、依赖已声明 | 通过 | 影响范围限定 ace_engine 的 ui_session、adapter、pipeline、Text/RichEditor/Web、sample SA |
| 启动期注册链路明确 | 通过 | `design.md` 增加 `UIContentImpl::InitUISessionManagerCallbacks` 增量设计，统一翻译 callback 保存到 `UiSessionManager`，执行时通过 `TaskExecutor` 回到 UI 线程 |
| API 命名和参数符合 OH 规范 | 条件通过 | 设计给出推荐签名和 scope enum；最终命名需 Stage 3 前由模块 Owner 确认 |
| 错误码不与已有子系统冲突 | 通过 | 复用 `ui_content_errors.h` 现有 `PARAM_INVALID/FAILED/REPLY_ERROR` 语义，不新增冲突错误码 |
| 数据模型定义完整 | 通过 | `design.md` 定义 request、scope、node、result、version；`sourceType/changeType` 仅作为 UI 内部 DFX/调度字段，不对 SA 暴露 |
| 构建系统影响已评估 | 通过 | `design.md` 和 `spec.md` 均标明 adapter/ui_session 与 unittest BUILD.gn 影响 |
| DFX 设计已覆盖 | 通过 | `design.md` 增加 DFX 章节，复用 Connect 传入的 EventHandler 投递 timeout task；请求 timeout 清 callback 并清理现场，译文等待 timeout 默认 5s 且 SA 未死亡时只输出告警 |
| 图表语法一致 | 通过 | `design.md` 明确所有流程图、架构图、设计图和状态机图必须使用 Mermaid fenced code block；现有架构图、时序图、状态机图均为 `mermaid` |

## Spec 检查

| 检查项 | 结果 | 证据/理由 |
|--------|------|-----------|
| 用户故事和 AC 完整 | 通过 | `spec.md` 覆盖 US-1 至 US-7，AC-1 至 AC-25；AC-21/AC-22 与 AC-23/AC-25 已在 `proposal.md` 变更控制记录中补入范围新增 |
| AC 覆盖正常/异常/边界 | 通过 | 正常：获取/Start/回填；异常：node 失效、SA death；边界：scope、非范围控件、End 后不上报 |
| API 变更分析完整 | 通过 | `spec.md` 列出当前统一 innerAPI 基线、待补齐语义与 Web 旧接口兼容策略 |
| 兼容性声明完整 | 通过 | 保留现有 Web-only API，Web 脚本注入路径不重写，不改 ArkUI 原属性 |
| 非功能需求有指标或明确 N/A | 通过 | 性能、内存、安全、可靠性、DFX、问题定位均有验证要求 |
| 全局特性影响已筛选 | 通过 | 无障碍、大字体、多窗口、版本升级、生态兼容均有结论 |
| 上下文引用完整 | 通过 | `proposal.md`、`design.md` 和源码路径证据已覆盖关键链路 |

## 结论

Specify 阶段产物已完成，结论为通过。用户已于 2026-05-15 明确 approve，允许进入 Stage 3。Stage 3 需由模块 Owner 确认故障上报接口名和 requestId 生成策略；译文等待 watchdog 默认值已明确为 5s。

## 设计修正记录

2026-05-14：根据用户反馈，取消新增 `TextTranslateNodeManager` 的设计。ArkUI 文本翻译节点管理改为增强现有 `ContentChangeManager`，复用其文本展示类控件上树/变化管理、Text AABB 收集、延迟任务和 dump 能力，避免新增小管理类和重复注册体系。

2026-05-22：根据用户新增 TASK-007，补充 Host Preview 验证设计。PreviewerCLI 通过 `remoteRequest business+method` 模拟 Uisession 翻译调用，`examples/UISessionTranslate` 承载测试页面和脚本；该能力仅作为验证入口，不作为正式产品接口。
