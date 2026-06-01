# TASK-001: EnvironmentManager 重构 + Direction 集成 + SDK API

> **合并实现记录** — Owner 在 `3df5112f727..705e5d27151` 中将原计划的 Tasks 1-4 合并为一次实现。
> 本文档按实际实现状态重写，作为当前 issue 规格的 TASK-001 任务卡片。

## 任务元数据

| 字段 | 内容 |
|------|------|
| Task ID | TASK-001 |
| 标题 | EnvironmentManager 重构 + Direction 集成 + SDK API（Tasks 1-4 合并） |
| 关联 Feature | FEAT-04-03-01-01 |
| 关联 CodeSpec | issue-76660-withenv-direction |
| 关联 Issue | https://gitcode.com/openharmony/arkui_ace_engine/issues/76660 |
| 目标仓库 | arkui_ace_engine |
| 分支 | withenv_0525newspec_2 |
| 优先级 | P0 |
| 复杂度 | 高 |
| 执行方式 | 已完成（15 commits, 24 files, +389/-27） |
| 提交范围 | 3df5112f727..705e5d27151 |

## 任务描述

### 已实现

1. ✅ WithEnvNode 新增 `RemoveEnvProperty()` + 3 个 `GetEnvProperty()` 重载
2. ✅ EnvironmentManager 新增 `RemoveValue()` 方法 + ENV 类型 `DispatchValueChangedToAffectedNode`
3. ✅ EnvironmentManager `ReadScopeValue(ENV)` 实现 bool/double/string 读取（ENV 查值路径已通）
4. ✅ CustomNode 新增 `FireOnSystemEnvUpdate()` 回调
5. ✅ WithEnvModelNG 新增 `RemoveEnvProperty()` + `useEnvManager` 标志
6. ✅ Layout direction 三级优先级：`GetLayoutDirection()` + `layout_direction_env.cpp`（新建）+ `PipelineContext::ResolveDirectionFromEnv()`
7. ✅ TS SDK：`system_env.ts`（新建）创建 SystemEnvKey 体系 + WritableEnvKey（DIRECTION, FONT_SCALE）
8. ✅ TS/JS Bridge：`WithEnv.ts`（含 CustomEnvKey\<T\> 声明）+ `js_with_env.cpp`（object 参数提取）
9. ✅ 构建：BUILD.gn 更新 + tsconfig + files_to_watch
10. ✅ 测试：RemoveEnvProperty 基础测试 + FontScale env 测试

### 已知偏差（延迟到后续迭代）

- ❌ **缓存优化（ADR-1/2/3）**：ResolvedEntry + valueCache_ + dirty flag + 精准通知 — 未实现，保持原始 O(n) 爬树 + DFS 通知
- ❌ **@Env 装饰器变更**：v2_decorators.ts 中 @Env 支持 SystemEnvKey 不在本次 diff 中
- ❌ **SpecTest**：无 Inspector 断言测试
- ❌ **Dump 支持**：Task 5 未实现

### 不做什么（与计划一致）

- 不修改 CustomEnv 功能行为（AC-10 兼容性）
- 不涉及 fontScale 功能实现（仅类型体系预留）

## 规格映射与边界

### AC 映射

| AC | 来源 | 验证方式 | 实现状态 |
|----|------|----------|----------|
| AC-1 | spec.md | GetLayoutDirection() 实现 | ✅ |
| AC-5 | spec.md | layoutDirection_.has_value() 检查 | ✅ |
| AC-6 | spec.md | 爬树找最近祖先 | ✅ |
| AC-10 | spec.md | 无破坏性变更 | ✅ |
| AC-2/3/4 | spec.md | 框架就绪，缺测试 | ⚠️ |
| AC-7/8/9 | spec.md | 缓存未实现 | ❌ Deferred |

### 前置依赖

| 类型 | 编号 | 原因 |
|------|------|------|
| Stage 2 Gate | evidence/gates/gate-specify.md | 已通过 |

### 完成判据

- ✅ .env() API 从 TS 到 C++ 的完整调用链已打通
- ✅ direction 三级优先级（explicit > env > AUTO）已实现
- ✅ ENV 类型查值路径已通（ReadScopeValue ENV 已实现）
- ✅ CustomEnv 泛型签名已更新（CustomEnvKey\<T\>）
- ⚠️ 缓存优化延迟到后续迭代
- ⚠️ 端到端测试不足

## 受影响文件（实际）

| 操作 | 文件路径 | 说明 |
|------|----------|------|
| 修改 | `frameworks/core/pipeline_ng/environment_manager.h` | 新增 RemoveValue() |
| 修改 | `frameworks/core/pipeline_ng/environment_manager.cpp` | RemoveValue() + ENV dispatch + ReadScopeValue(ENV) |
| 修改 | `frameworks/core/components_ng/syntax/with_env_node.h` | RemoveEnvProperty + GetEnvProperty 重载 |
| 修改 | `frameworks/core/components_ng/syntax/with_env_node.cpp` | 实现新方法 |
| 修改 | `frameworks/core/components_ng/syntax/with_env_model.h` | RemoveEnvProperty 声明 |
| 修改 | `frameworks/core/components_ng/syntax/with_env_model_ng.h` | RemoveEnvProperty 声明 |
| 修改 | `frameworks/core/components_ng/syntax/with_env_model_ng.cpp` | 实现 + useEnvManager |
| 修改 | `frameworks/core/components_ng/pattern/custom/custom_node.h` | FireOnSystemEnvUpdate |
| 新增 | `frameworks/core/components_ng/layout/layout_direction_env.cpp` | Direction env 回调引导 |
| 修改 | `frameworks/core/components_ng/layout/layout_property.h` | GetLayoutDirection 声明 |
| 修改 | `frameworks/core/components_ng/layout/layout_property.cpp` | 三级优先级实现 |
| 修改 | `frameworks/core/pipeline_ng/pipeline_context.h` | ResolveDirectionFromEnv + 常量 |
| 修改 | `frameworks/core/pipeline_ng/pipeline_context.cpp` | Direction/FontScale env 解析 |
| 新增 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/env_base/system_env.ts` | SystemEnvKey 体系 |
| 修改 | `frameworks/bridge/declarative_frontend/ark_with_env/src/WithEnv.ts` | env\<T\>() + CustomEnvKey\<T\> |
| 修改 | `frameworks/bridge/declarative_frontend/engine/jsWithEnv.js` | 类型定义 |
| 修改 | `frameworks/bridge/declarative_frontend/jsview/js_with_env.cpp` | object 参数提取 + undefined 处理 |
| 修改 | 多个 BUILD.gn / tsconfig / files_to_watch | 构建配置 |
| 修改 | `test/mock/frameworks/core/pipeline/mock_pipeline_context.cpp` | 测试 stub |
| 修改 | `test/unittest/core/syntax/with_env_syntax_test_ng.cpp` | RemoveEnvProperty 测试 |
| 新增 | `test/unittest/core/pipeline/pipeline_context_font_scale_env_test_ng.cpp` | FontScale env 测试 |

## 验证检查清单

- [x] .env() API 调用链完整（TS → JS → C++）
- [x] direction 三级优先级正确
- [x] CustomEnv 行为不变（签名已更新为泛型版）
- [x] ENV 查值路径已通（ReadScopeValue ENV 已实现）
- [x] 编译通过（mock + BUILD.gn 已更新）
- [ ] 缓存优化（延迟）
- [ ] @Env 装饰器支持（延迟）
- [ ] 端到端测试补齐（延迟）
