# Review — 静态自定义组件支持跨 Ability 实例迁移

> **状态**: Draft
> **关联 Execution Plan**: execution-plan.md
> **创建日期**: 2026-06-11

---

## 1. 规范符合性检查

| # | 检查项 | 结果 | 证据 |
|---|--------|------|------|
| 1 | 不新增/修改 Public API | 通过 | design.md API 签名与权限章节确认无新增/变更 |
| 2 | 不修改 `**/generated/` 下的生成文件 | 通过 | 不涉及生成文件 |
| 3 | 不在 BUILD.gn 中添加外部依赖 | 通过 | design.md 构建系统影响章节确认无变更 |
| 4 | 优先使用 components_ng | 通过 | 复用已有 Env 回调通路，前端闭合 |
| 5 | 单仓变更 | 通过 | 仅 ace_engine |
| 6 | 代码优先、证据优先 | 待验证 | 实现后需通过 SPEC 测试提供证据 |
| 7 | C++ 零新增 | 通过 | design.md ADR-1：不新增 C++ 函数、不新增 ANI 注册、不修改 UINode 基类 |

## 2. 代码质量检查

| # | 检查项 | 结果 | 证据 |
|---|--------|------|------|
| 1 | Env+Switch 闭包合并正确性 | 待实现 | TASK-01 |
| 2 | 两层幂等保护覆盖 | 待实现 | AC-3.1, AC-3.2 |
| 3 | 子组件递归传播 + 弱引用 GC 安全 | 待实现 | TASK-01, ER-1 |
| 4 | FreeRootNode 条目转移正确性 | 待实现 | TASK-01 + TASK-02 |
| 5 | transformFromCustomBuilder UIContext 延迟获取 | 待实现 | TASK-02 |
| 6 | 无 hilog 敏感信息泄露 | 待实现 | 代码审查 |

## 3. 测试覆盖检查

| # | SPEC | 覆盖 AC | 测试状态 |
|---|------|---------|---------|
| 1 | SPEC-001 (UIContext 更新) | AC-1.1 | 待执行 |
| 2 | SPEC-002 (@State/@Watch) | AC-1.2, AC-1.3 | 待执行 |
| 3 | SPEC-003 (冻结功能) | AC-6.1, AC-6.2 | 待执行 |
| 4 | SPEC-004 (子组件传播) | AC-2.1, AC-3.3 | 待执行 |
| 5 | SPEC-005 (幂等保护) | AC-3.1, AC-3.2 | 待执行 |
| 6 | SPEC-006 (异常安全) | ER-1, ER-2 | 待执行 |
| 7 | SPEC-007 (@ComponentV2 V2) | AC-4.1~4.5 | 待执行 |
| 8 | SPEC-008 (组件复用) | AC-5.1~5.3 | 待执行 |

**AC 覆盖率**: 17/17 AC 已规划测试（待执行）

## 4. 关键决策记录

| 决策 | 理由 | 依据 |
|------|------|------|
| 复用已有 Env 回调通路（非新增 C++ Switch 函数） | 新增 C++ 通道会产生与 Env 通道完全相同的冗余代码；复用 Env 通道可零改动 C++ 层 | design.md ADR-1 |
| 前端闭合，C++ 零新增 | 所有 Switch 逻辑在 ArkTS 层完成，C++ 侧完全无感知 | design.md 详细设计 |
| 两层幂等保护（Env 层 + Switch 层） | 首次 AttachContext 时两层均命中幂等，确保无副作用 | design.md ADR-3 |
| 子组件通过 WeakRef 递归传播 | 弱引用天然 GC 安全，不阻止组件回收 | design.md ADR-4 |
| UIContext 延迟到闭包内部获取 | 跨 Ability 迁移后外层 context 已过时 | design.md ADR-6 |

## 5. 开放问题

| # | 问题 | 状态 | Owner |
|---|------|------|-------|
| （无开放问题） | — | — | — |
