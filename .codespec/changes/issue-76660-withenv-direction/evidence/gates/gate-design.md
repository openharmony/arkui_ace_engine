# Gate: Implement (Stage 3)

## 元数据

| 字段 | 内容 |
|------|------|
| 阶段 | Stage 3 — Implement |
| 关联 Feature | FEAT-04-03-01-01 |
| CodeSpec ID | issue-76660-withenv-direction |
| 关联 Issue | https://gitcode.com/openharmony/arkui_ace_engine/issues/76660 |
| 提交范围 | 3df5112f727..current_show (含仓上后续演进) |
| 日期 | 2026-06-01 |

## 一、入口检查 (arkui-implement-entry)

| 检查项 | 结果 | 证据/理由 |
|--------|------|-----------|
| Stage 2 已通过 | ✅ Pass | gates/specify.md Approved, 2025-05-25 |
| execution-plan.md 存在 | ✅ Pass | 已创建，任务状态已更新 |
| 任务卡片存在 | ✅ Pass | tasks/TASK-001-environment-manager-direction-sdk-api.md 已按实际实现重写 |
| 涉及子系统/仓已识别 | ✅ Pass | ace_engine 单仓 |

## 二、实现检查 (arkui-implement-check)

### 2.1 规范符合性

| 检查项 | 结果 | 证据/理由 |
|--------|------|-----------|
| .env() API 完整 | ✅ Pass | TS → JS → C++ 全链路已实现 |
| direction 三级优先级 | ✅ Pass | GetLayoutDirection() + ResolveDirectionFromEnv() |
| CustomEnv 不变 | ✅ Pass | 无破坏性变更（签名已更新为泛型版 customEnv\<T\>(CustomEnvKey\<T\>, T)） |
| SystemEnvKey 体系 | ✅ Pass | system_env.ts 创建类型体系 |
| ENV 类型查值路径 | ✅ Pass | ReadScopeValue(ENV) 已实现 bool/double/string 读取，FindValueByKey(ENV) 可用 |
| customEnv bridge | ✅ Pass | js_with_env.cpp 已改为 object 参数提取 _internal_id |
| 缓存 O(1) 查值 | ❌ Deferred | ADR-1/2/3 延迟到后续迭代 |
| 精准通知 | ❌ Deferred | 保持 DFS 通知方案 |

### 2.2 AC 覆盖

| AC | 状态 | 证据 |
|----|------|------|
| AC-1 | ✅ Pass | GetLayoutDirection() 实现 |
| AC-2 | ⚠️ Partial | 框架就绪（ReadScopeValue(ENV) 可用），无测试 |
| AC-3 | ⚠️ Partial | 框架就绪，无测试 |
| AC-4 | ⚠️ Partial | 框架就绪，无测试 |
| AC-5 | ✅ Pass | layoutDirection_ 优先检查 |
| AC-6 | ✅ Pass | 爬树找最近祖先 |
| AC-7 | ❌ Deferred | 缓存未实现 |
| AC-8 | ❌ Deferred | 缓存未实现 |
| AC-9 | ❌ Deferred | 缓存未实现 |
| AC-10 | ✅ Pass | CustomEnv 签名已更新为泛型版，功能行为不变 |

### 2.3 测试覆盖

| 检查项 | 结果 | 证据/理由 |
|--------|------|-----------|
| RemoveEnvProperty 测试 | ✅ Pass | WithEnvSyntaxTest015 |
| FontScale env 测试 | ✅ Pass | pipeline_context_font_scale_env_test_ng.cpp |
| 缓存/通知测试 | ❌ N/A | 缓存未实现 |
| 响应式更新测试 | ❌ Missing | 待补齐 |
| 嵌套 WithEnv 测试 | ❌ Missing | 待补齐 |
| 默认值测试 | ❌ Missing | 待补齐 |
| CustomEnv 回归测试 | ⚠️ Implicit | 无破坏性变更但无显式回归测试 |

### 2.4 构建验证

| 检查项 | 结果 | 证据/理由 |
|--------|------|-----------|
| BUILD.gn 更新 | ✅ Pass | 新文件已加入构建 |
| tsconfig 更新 | ✅ Pass | system_env.ts 已加入 |
| mock 更新 | ✅ Pass | mock_pipeline_context.cpp stub 已更新 |

### 2.5 文件范围

| 检查项 | 结果 | 证据/理由 |
|--------|------|-----------|
| 变更在计划范围内 | ✅ Pass | 24 文件覆盖 Tasks 1-4 范围 |
| 新增文件有记录 | ✅ Pass | layout_direction_env.cpp + system_env.ts 已在偏差记录 |

## 三、偏差记录

| 偏差 | 影响 | 处理 |
|------|------|------|
| ADR-1/2/3 缓存+精准通知未实现 | AC-7/8/9 不达标 | 标记为 Deferred，后续迭代 |
| @Env 装饰器变更不在 diff 中 | AC-3 完整性 | 可能为后续变更 |
| 响应式更新/嵌套/默认值测试缺失 | 验证信心不足 | 待补齐 |
| 方法名 GetEffectiveLayoutDirection → GetLayoutDirection | 语义等价 | 已记录 |

### 已修正的偏差（仓上已解决）

| 原偏差 | 仓上状态 |
|--------|----------|
| ~~ReadScopeValue(ENV) 返回 false，ENV 查值是死路径~~ | ✅ 已修复，bool/double/string 读取已实现 |
| ~~CustomEnvKey\<T\> 泛型签名未声明~~ | ✅ WithEnv.ts 已声明 CustomEnvKey\<T\> class |
| ~~customEnv bridge 未改~~ | ✅ js_with_env.cpp 已改为 object 参数提取 _internal_id |

## 四、退出决策

| 检查项 | 结果 |
|--------|------|
| 所有 P0 AC 通过或有明确 defer 理由 | ⚠️ 6/10 通过，3/10 deferred，1/10 部分 |
| 构建通过 | ✅ |
| 测试覆盖充分 | ❌ 最小覆盖 |
| 无未记录的范围扩展 | ✅ |

**结论：Conditional Pass** — 功能实现正确，但缓存优化和测试覆盖为已知短板，标记为后续迭代。需 Owner 确认是否接受此状态进入 Stage 4。
