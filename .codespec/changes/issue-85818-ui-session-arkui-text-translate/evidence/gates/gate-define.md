# Define Gate

| 检查项 | 结果 | 证据/理由 |
|--------|------|-----------|
| 原始问题和期望结果已记录 | 通过 | `proposal.md` 已保留用户原始需求，并记录单次获取、StartTranslate、EndTranslate、Reset、变化上报等期望结果 |
| 需求来源和责任人已明确 | 通过 | 来源记录为用户需求；提出人与确认人为用户；Owner 暂为 TBD |
| 功能范围（包含/不包含）已确认 | 通过 | 用户确认新增统一接口能力覆盖现有 Web 能力和 ArkUI Text、Span/styled string、RichEditor 只读展示内容，并补充覆盖空内容 TextInput placeholder；SA 通过入参选择页面所有内容或仅 ArkUI 原生控件；不覆盖输入类控件用户可编辑文本、自绘、Public API |
| API 变更已评估 | 通过 | 明确涉及 Uisession 系统 SA innerAPI，不新增 Public API 或应用权限；SA 调用入口在 `UIContentServiceProxy` / `IUiContentService`，UI 上报链路经 `UiReportProxy` / `ReportService`，SA 回调保存在 `UiReportStub`；Stage 2 需设计范围入参 |
| 兼容性和非功能需求已确认 | 通过 | 明确不修改原始文本属性、Reset/End 恢复原文；SA 意外死亡或 IPC 断开时须通过死亡监听恢复原文并清理会话；新增接口需覆盖现有 Web 能力，Web 内容翻译继续通过脚本注入实现；性能、安全、可靠性进入 Stage 2 |
| 依赖和风险已识别并有缓解方案 | 通过 | 已列出 IPC、Report Stub/Proxy、UiTranslateManager、Text/RichEditor/TextField Pattern、ui_session_sample 依赖和文本变化、节点失效、日志隐私、SA 死亡、真机验证入口等风险 |
| 所有 P0/P1 用户故事有 AC（WHEN/THEN 格式） | 通过 | US-1 到 US-6 均有 AC；AC-1 到 AC-22 使用 WHEN/THEN，AC-21/AC-22 已通过变更控制补入需求基线 |
| 每条 AC 可测试、可度量 | 通过 | AC 覆盖接口结果、节点范围、主动上报、恢复、局部失败和 Web 回归，可通过单元测试验证 |
| `manifest.target_release` 已确认或明确 TBD | 通过 | 目标发行版本明确为 TBD |
| `manifest.profile` 已确认或明确 none | 通过 | Profile 明确为 arkui |
| 不涉及项已显式标记 N/A | 通过 | 数据迁移标记 N/A；其他涉及项进入下游文档 |

## 结论

Define 阶段通过。

允许进入 Stage 2：规格化。

## 证据修正记录

2026-05-13：根据用户反馈补充现有翻译 IPC/report 链路证据。Stage 2 设计必须以 `ui_content_proxy.h` 作为 SA 获取文本和开始连续翻译的接口入口，以 `ui_report_stub.h` 作为 SA 回调保存点，以 `ui_report_proxy.h` 作为 UI 文本上报接口入口。

2026-05-13：根据用户反馈补充 Web 兼容和范围入参要求。Stage 2 设计必须让新增接口能力覆盖现有 Web 翻译能力，保留 Web 脚本注入实现，并定义 SA 入参用于选择“页面所有内容”或“仅 ArkUI 原生控件”。

2026-05-13：根据用户反馈补充 SA 异常死亡恢复要求。Stage 2 设计必须覆盖 DeathRecipient 或 IPC 连接断开监听，在当前存在已翻译展示或连续翻译会话时恢复原文展示、停止变化上报并清理会话状态。

2026-05-13：根据用户反馈补充终端模拟验证要求。Stage 2 设计必须覆盖 `interfaces/inner_api/ui_session/ui_session_sample` 的 dump 命令和 handler，让新增接口及范围入参、Start/End、Reset、SendTranslateResult 能通过模拟 SA 在终端触发。
