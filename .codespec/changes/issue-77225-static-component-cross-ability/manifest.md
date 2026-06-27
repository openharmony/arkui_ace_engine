# Manifest — issue-77225-static-component-cross-ability

## 基本信息

| 字段 | 值 |
|------|------|
| 需求标题 | 静态自定义组件支持跨 Ability 实例迁移 |
| FuncID | 03-03-01 |
| FeatID | Feat-01 |
| API 版本 | 26.0.0 |
| 复杂度 | 标准（单仓） |
| 涉及仓库 | ace_engine |
| 创建日期 | 2026-06-11 |

## 阶段状态

| 阶段 | 状态 | 审批人 | 审批日期 | 产物 |
|------|------|--------|---------|------|
| Stage 1: Define | Baselined | 用户批准 | 2026-06-11 | proposal.md |
| Stage 2: Specify | Approved | 用户批准 | 2026-06-11 | design.md, spec.md |
| Stage 3: Implement | Approved | 用户批准 | 2026-06-11 | execution-plan.md, task.md, review.md |
| Stage 4: Release | Approved | 用户批准 | 2026-06-11 | evidence/gates/gate-release.md |

## Profile

- 已检查 `.claude/ohos-sdd/profiles/`：无命中 Profile
- 已读取 `AGENTS.md` 并记录关键约束

## AGENTS.md 关键约束记录

- 代码优先、证据优先、不捏造
- 优先使用 `components_ng` 而非 legacy `components`
- 不修改公共 API 签名/语义/错误码/结构体布局
- 不手动编辑 `**/generated/` 下的生成文件
- 不在 `BUILD.gn` 中添加外部依赖
