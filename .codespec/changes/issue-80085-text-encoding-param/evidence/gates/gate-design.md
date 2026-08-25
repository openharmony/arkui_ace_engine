# Gate: Design (Specify)

| 字段 | 值 |
|------|-----|
| 变更 ID | issue-80085-text-encoding-param |
| 阶段 | Specify |
| 状态 | passed |

## 证据

- [spec.md](../spec.md) — 特性规格已编写
- [design.md](../design.md) — 架构设计已编写
- [execution-plan.md](../execution-plan.md) — 执行计划已拆分
- [tasks/](../tasks/) — 4 个 Task 文件
- 调用链层级分析完整（JS bridge → LayoutInfoInterface → Pattern → Model → ParagraphManager → Paragraph → TxtParagraph → Rosen）
- 6 个 ADR 决策记录
- 3 个风险项
- 转换方案：Utf16OffsetToUtf8 / Utf8OffsetToUtf16 子串转换法
