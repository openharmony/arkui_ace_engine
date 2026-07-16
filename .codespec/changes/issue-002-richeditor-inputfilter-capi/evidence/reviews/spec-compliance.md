# Spec Compliance Review — FEAT-002

> 检查实现是否严格符合 Spec：不多、不少、不误解。

## 需求覆盖

| AC/规则 | 是否在 Spec/Plan 中 | 证据 | 结论 |
|---------|---------------------|------|------|
| AC-1 / R-1: setAttribute 正则生效 | 是 | spec.md AC-1 + R-1 | PASS |
| AC-2 / R-1: getAttribute 返回一致 | 是 | spec.md AC-2 + R-1 | PASS |
| AC-3 / R-2: resetAttribute 清除 | 是 | spec.md AC-3 + R-2 | PASS |
| AC-4 / R-4: registerNodeEvent 回调注册 | 是 | spec.md AC-4 + R-4 | PASS |
| AC-5 / R-3: 过滤失败 pStr 回传 | 是 | spec.md AC-5 + R-3 | PASS |
| AC-6 / R-5: unregisterNodeEvent 回调注销 | 是 | spec.md AC-6 + R-5 | PASS |
| AC-7 / R-6: spanString+singleLine 生效 | 是 | spec.md AC-7 + R-6 | PASS |
| AC-8 / R-7: 非 spanString/singleLine 不生效 | 是 | spec.md AC-8 + R-7 | PASS |
| AC-9 / R-8: inputFilter→maxLength 优先级 | 是 | spec.md AC-9 + R-8 | PASS |
| AC-10 / R-2: 空字符串等效于不设置 | 是 | spec.md AC-10 + R-2 | PASS |
| AC-11 / R-9: "\n" 被过滤 | 是 | spec.md AC-11 + R-9 | PASS |

## 多余实现

| 实现内容 | 是否在 Spec/Design 中 | 风险 | 处理 |
|----------|---------------------|------|------|
| 无 | — | — | — |

## 理解偏差

| 检查项 | 结论 | 证据 |
|--------|------|------|
| AC 理解是否正确 | PASS | spec.md AC 定义明确，WHEN/THEN 格式 |
| 边界和不做范围是否遵守 | PASS | 仅 CAPI、仅 spanString+singleLine、不涉及 1.2/1.1 |
| 适用规则是否遵守 | PASS | AGENTS.md 约束已在 design.md C-3 标注 |
| 枚举编号是否正确 | PASS | 22031/22009/67009 紧跟现有最大值 |
| 过滤插入点位置是否正确 | PASS | ProcessTextTruncationOperation 之前 |
| 回调与 inputFilter 关系是否约束 | PASS | design.md C-7(过滤在回调前) + C-8(无两阶段差异), spec.md R-10 |
| onSubmit 特殊处理是否覆盖 | PASS | spec.md AC-11 明确"不触发 onSubmit(NEW_LINE)" |

**结论:** 通过 — Spec 合规性审查无偏差
