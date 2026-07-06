# Define Gate

| 检查项 | 结果 | 证据/理由 |
|--------|------|-----------|
| 原始问题和期望结果已记录 | 通过 | `proposal.md` 记录用户需求：SA 下发 `ruleJson`，ArkUI 宿主规则匹配并上报；Web/UIExtension 当前只做规则透传 |
| 需求来源和责任人已明确 | 通过 | 来源记录为用户需求；提出人与确认人为用户；Owner 暂为 ACE/UISession owner |
| 功能范围（包含/不包含）已确认 | 通过 | 明确包含 UISession 场景规则注册、反注册、查询和上报；明确不绑定 `ContentChange` / `ComponentChange`，不新增 Public API，不默认上报文本和完整树 |
| 首批场景已确认 | 通过 | 首批场景为 `TEXT_EDITOR`，规则为 ArkUI 宿主页面内存在 2 个及以上可见文本输入类控件 |
| ruleJson 规格已确认 | 通过 | `spec.md` 固化 `ruleSetId`、`globalConfig`、`sourceConfig`、`webRules` 预留字段、`rules`、`scope`、`selector`、`condition`、`report`、`policy` |
| 上报规格已确认 | 通过 | `spec.md` 固化 `currentPageName`、`source`、`matchedCount`、`nodes.nodeId`、`nodes.nodeType`、`nodes.focusable`、`nodes.rect` |
| Web / UIExtension 接入边界已确认 | 通过 | Web 当前接收 `webRules` 原样透传；UIExtension 接收规则生命周期请求；不做内部匹配、命中回传和端到端验证 |
| API 变更已评估 | 通过 | 明确涉及 UISession 系统 SA innerAPI 和 ReportService callback；不涉及 ArkTS/Public API；详细 transaction 进入 Stage 2 |
| 兼容性和非功能需求已确认 | 通过 | 默认不上报文本和完整树；支持来源区分、可见性过滤、不可获焦控件计数开关、去重和节流策略 |
| 所有 P0/P1 用户故事有 AC（WHEN/THEN 格式） | 通过 | `proposal.md` 中 US-1 到 US-5 均有 AC |
| 每条 AC 可测试、可度量 | 通过 | AC 覆盖规则注册、首次扫描、文本输入类控件上下树、子内容源规则透传和脱敏输出 |
| `manifest.target_release` 已确认或明确 TBD | 通过 | 目标发行版本明确为 TBD |
| `manifest.profile` 已确认或明确 none | 通过 | Profile 明确为 arkui/component |

## 结论

Define 阶段通过。

允许进入 Stage 2：规格化与设计。
