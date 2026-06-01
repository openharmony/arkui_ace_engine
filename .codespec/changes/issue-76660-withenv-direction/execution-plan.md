# 执行计划 — WithEnv Direction & Framework Refactoring

## 计划元数据

| 字段 | 内容 |
|------|------|
| 关联需求 | REQ-04-03-01-01 |
| 关联设计 | design.md (DESIGN-04-03-01-01) |
| 关联 Spec | spec.md (FEAT-04-03-01-01) |
| CodeSpec ID | issue-76660-withenv-direction |
| 关联 Issue | https://gitcode.com/openharmony/arkui_ace_engine/issues/76660 |
| 复杂度 | 标准 |
| 状态 | Conditional Pass (Tasks 1-4 merged, cache deferred; tests follow-up) |
| 备注 | Owner 在 3df5112f727..705e5d27151 中合并实现了 Tasks 1-4。缓存优化（ADR-1/2/3）延迟到后续迭代 |

## 执行策略

按依赖关系从底向上：先完成框架核心重构，再叠加 direction 能力，最后做 API 层和测试补齐。

## 任务拆解

### Task 1: EnvironmentManager 核心重构 — 缓存与精准通知

**实现状态：部分完成** — 通知框架 + RemoveValue + ReadScopeValue(ENV) + ENV 类型读取已实现；缓存（ADR-1）和精准通知（ADR-2）未实现，保持原始 O(n) 方案。

**目标：** 将 EnvironmentManager 从朴素爬树+DFS 通知重构为缓存+依赖驱动精准通知。

**关联 AC：** AC-7, AC-8, AC-9, AC-10

**文件范围：**

| 文件 | 变更类型 | 说明 |
|------|----------|------|
| `frameworks/core/pipeline_ng/environment_manager.h` | 修改 | 新增解析缓存结构、ResolvedEntry（含 dirty 标记）、精准通知接口 |
| `frameworks/core/pipeline_ng/environment_manager.cpp` | 修改 | 重写 QueryEnvValue（缓存逻辑）、OnEnvValueChanged（精准通知）、缓存失效逻辑 |
| `frameworks/core/components_ng/syntax/with_env_node.h` | 修改 | 移除 version_ 字段（如有），适配新 EnvironmentManager 接口 |
| `frameworks/core/components_ng/syntax/with_env_node.cpp` | 修改 | 适配新接口 |
| `test/unittest/core/syntax/with_env_syntax_test_ng.cpp` | 扩展 | 新增缓存命中、精准通知、缓存失效、节点上下树的测试用例 |

**不做范围：**
- 不修改 WithEnvNode 的存储结构（systemEnvProperties_ 保持不变）
- 不修改 TS/JS bridge 层
- 不涉及 direction

**验证方式：**
- 组件 unittest：缓存命中/未命中、精准通知仅通知注册依赖者、脏标记懒检查、节点卸载后缓存失效
- 回归测试：现有 with_env_syntax_test_ng.cpp 测试全部通过（CustomEnv 行为不变）

**子 Profile：** arkui/component

---

### Task 2: direction env 集成 — LayoutProperty 三级优先级解析

**实现状态：完成** — layout_direction_env.cpp 新建，GetLayoutDirection() 实现三级优先级，PipelineContext 新增 ResolveDirectionFromEnv()。

**目标：** 在布局属性解析中增加 env direction 层，实现三级优先级（显式 > env > AUTO）。

**依赖：** Task 1

**关联 AC：** AC-1, AC-3, AC-5, AC-6

**文件范围：**

| 文件 | 变更类型 | 说明 |
|------|----------|------|
| `frameworks/core/components_ng/layout/layout_property.h` | 修改 | 新增 GetEffectiveLayoutDirection() 方法，接受 env 查询回调 |
| `frameworks/core/components_ng/layout/layout_property.cpp` | 修改 | 实现 GetEffectiveLayoutDirection()，三级优先级逻辑 |
| `frameworks/core/components_ng/pattern/pattern.cpp` | 修改 | CheckLocalized() 调用新方法 |
| 布局算法文件（flex_layout_algorithm.h 等） | 修改 | 消费 direction 处改用新方法（按需） |
| `test/unittest/core/syntax/with_env_syntax_test_ng.cpp` | 扩展 | 新增 direction env → 布局效果的测试 |

**不做范围：**
- 不修改 TextDirection 枚举
- 不修改 direction 的布局算法逻辑本身
- 不修改 TS/SDK 层

**验证方式：**
- 组件 unittest：显式 direction 覆盖 env、env direction 覆盖 AUTO、嵌套 WithEnv 场景
- SpecTest（如适用）：通过 Inspector 断言 direction 布局效果

**子 Profile：** arkui/component

---

### Task 3: SDK API 声明与 TS/JS Bridge 更新

**实现状态：部分完成** — system_env.ts 创建 SystemEnvKey 体系，WithEnv.ts 含 CustomEnvKey\<T\> 声明，js_with_env.cpp customEnv bridge 已改为 object 参数提取；@Env 装饰器变更（v2_decorators.ts）不在本次 diff 中。

**目标：** 按 `32825.diff` 更新 API 声明和 TS/JS bridge 层，支持 `.env()` 和 `@Env(SystemEnvKey<T>)`。

**依赖：** Task 1（@Env 需要 EnvironmentManager 查值接口）

**关联 AC：** AC-1, AC-2, AC-3, AC-4

**文件范围：**

| 文件 | 变更类型 | 说明 |
|------|----------|------|
| API 声明文件（按 32825.diff） | 新增/修改 | SystemEnvKey、WritableSystemEnvKey、WritableEnvKey、Env 签名变更 |
| `frameworks/bridge/declarative_frontend/ark_with_env/src/WithEnv.ts` | 修改 | 新增 .env() 方法、更新 customEnv() 签名 |
| `frameworks/bridge/declarative_frontend/jsview/js_with_env.h/.cpp` | 修改 | 新增 SetEnvProperty bridge、适配新签名 |
| `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_decorators.ts` | 修改 | @Env 扩展支持 SystemEnvKey<T>、@CustomEnv 改用 CustomEnvKey<T> |
| `frameworks/core/components_ng/syntax/with_env_model_ng.h/.cpp` | 修改 | 新增 SetEnvProperty model 方法 |

**不做范围：**
- 不修改 C++ 侧 EnvironmentManager 核心逻辑（Task 1 已完成）
- 不涉及 fontScale 功能实现
- 不修改 ReadonlySystemEnvKey 的具体实现

**验证方式：**
- SDK 编译：`./build.sh --product-name ohos-sdk --build-target ace_engine`
- API 签名与 design.md / spec.md 一致
- @Env(SystemEnvKey) 装饰器在真实 ArkTS 工程中可用

**子 Profile：** arkui/sdk-api

---

### Task 4: @Env direction 响应式更新与端到端测试

**实现状态：最小完成** — 仅 1 个 RemoveEnvProperty 基础测试；无响应式更新、嵌套场景、默认值、节点移动测试。

**目标：** 验证 @Env(WritableEnvKey.DIRECTION) 的响应式更新能力，补齐端到端测试。

**依赖：** Task 2, Task 3

**关联 AC：** AC-2, AC-4, AC-9, AC-10

**文件范围：**

| 文件 | 变更类型 | 说明 |
|------|----------|------|
| `test/unittest/core/syntax/with_env_*_test_ng.cpp` | 扩展 | env 值变化后 @Env 变量响应式更新、无 WithEnv 祖先默认值、节点移动缓存一致性 |
| SpecTest 用例（如适用） | 新增 | direction env → 布局效果 Inspector 断言 |

**不做范围：**
- 不修改生产代码（Task 1-3 已覆盖）
- 不涉及性能 benchmark（代码审查替代）

**验证方式：**
- 组件 unittest：AC-2（env 变化 → @Env 更新）、AC-4（无祖先 → 默认值）、AC-9（节点移动缓存）
- 回归测试：现有 CustomEnv 测试全部通过（AC-10）
- SpecTest（如适用）：AC-1、AC-5 Inspector 断言

**子 Profile：** arkui/component

---

### Task 5: Dump 支持与收尾

**实现状态：未实现**

**目标：** 在 WithEnvNode 的 dump 中输出 env 属性信息，次要优先级。

**依赖：** Task 1

**关联 AC：** 无直接 AC（次要需求）

**文件范围：**

| 文件 | 变更类型 | 说明 |
|------|----------|------|
| `frameworks/core/components_ng/syntax/with_env_node.cpp` | 修改 | Dump 方法中输出 env 键值信息 |

**不做范围：**
- 不修改其他 dump 逻辑
- 不涉及 dump 格式标准化

**验证方式：**
- dump 输出包含 env 信息
- 代码审查

**子 Profile：** arkui/component

## 任务依赖关系

```
Task 1 (EnvironmentManager 核心重构)
  ├── Task 2 (direction 集成)
  │     └── Task 4 (@Env 响应式 + 端到端测试)
  ├── Task 3 (SDK API + TS/JS Bridge)
  │     └── Task 4
  └── Task 5 (Dump 支持)
```

## 交接信息

| 项 | 说明 |
|------|------|
| 分支策略 | 在 withenv_0525newspec_2 分支上开发 |
| 编译验证 | `./build.sh --product-name rk3568 -j8 --build-target ace_engine --ccache --fast-rebuild` |
| 测试验证 | `./build.sh --product-name rk3568 --build-target //foundation/arkui/ace_engine/test/unittest:unittest --ccache` |
| SDK 编译 | `./build.sh --product-name ohos-sdk --build-target ace_engine` |
| SpecTest | `cd examples/SpecTest && ./tools/host_preview/run_feature.sh --suite-id <suite-id>` |
| 注意事项 | Task 1 是所有后续任务的前置依赖；Task 2 和 Task 3 可并行；Task 4 依赖 Task 2 和 Task 3 |

## 实现偏差记录

**提交范围：** `3df5112f727..705e5d27151`（15 commits, 24 files changed, +389/-27）

**偏差 1：缓存优化未实现（ADR-1/2/3 Deferred）**

Owner 选择首期保持原始 O(n) 爬树 + DFS 通知方案，理由：
- 功能正确性优先于性能优化
- 缓存失效逻辑复杂度高，风险大
- 典型场景树深度有限，O(n) 可接受

**影响：** AC-7（零开销）和 AC-8（O(1) 查值）本期不达标，标记为 Deferred。

**偏差 2：方法名变更**

`GetEffectiveLayoutDirection()` → `GetLayoutDirection()`（语义等价）

**偏差 3：新增文件未在计划中**

- `frameworks/core/components_ng/layout/layout_direction_env.cpp` — direction env 回调引导注册
- `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/env_base/system_env.ts` — SystemEnvKey 类型体系

**偏差 4：@Env 装饰器变更不在本次 diff**

`v2_decorators.ts` 中 @Env 支持 SystemEnvKey 的变更未包含，可能为后续变更。
