# check-spec

> spec.md 自检记录。

## 核验项

| 项 | 结论 | 依据 |
|----|------|------|
| AC 用 WHEN/THEN 可测 | 是 | AC-1.1~4.1 |
| 验收追溯 ≥1 AC | 是 | 每条 AC→规则→Task→验证 |
| 无实现细节（归 design） | 是 | 仅行为/默认值/参数槽/兼容性 |
| 规则表 5 项质量 | 是 | R-1~R-13 可复现/可观测/边界/关联AC/无冲突 |
| 兼容性声明 + API 清单 | 是 | 仅追加，`@since 26.1.0` |
| 默认值与 PR #5447 一致 | 是 | 逐属性对齐（COLOR=0xFFFFFFFF 等） |

## capi 子 profile 追加要求

| 项 | 结论 |
|----|------|
| 每条 C API AC 映射 CAPI unittest | 是（验收追溯表） |
| modifier/accessor 影响 UI 时 SpecTest 或 N/A 理由 | 是（Host Preview 无法直达 C API → 转组件 unittest/ArkTS 回归，记录 N/A 理由） |

## 结论

spec 结构与内容达标；Draft（上游 Blocked）。
