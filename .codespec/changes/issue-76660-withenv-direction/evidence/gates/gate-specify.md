# Specify Gate — WithEnv Direction & Framework Refactoring

## 信息检索手段记录

| 手段 | 检索内容 | 结果 |
|------|----------|------|
| 源码探索 | WithEnv 组件实现（with_env_node.h/cpp, with_env_model_ng.h/cpp, js_with_env.h/cpp, WithEnv.ts） | 已读取，理解当前朴素架构 |
| 源码探索 | @Env/@CustomEnv 装饰器（v2_decorators.ts） | 已读取，理解装饰器注册和查值机制 |
| 源码探索 | EnvironmentManager（environment_manager.h/cpp） | 已读取，理解 FindWithEnvNodeInternal 爬树、DependentEntry、NotifyValueChanged DFS |
| 源码探索 | Direction 属性（layout_property.h/cpp, pattern.cpp, enums.ets） | 已读取，理解 TextDirection 枚举、LayoutProperty 存储、AUTO 解析逻辑、无父子继承 |
| 32825.diff 读取 | API 接口定义 | 已读取，获取完整 API 变更 |
| Owner 对话 | 范围、优先级、性能标准、框架规格化程度 | Stage 1 已完成 6+ 轮问答 |

---

## 入口表（arkui-specify-entry）

### FeatID 连续性预检

| 检查项 | 结果 | 证据/缺口 | 确认来源 |
|--------|------|-----------|----------|
| 当前 FeatID 为 Feat-01 | 通过 | Feat-01 为该功能域下第一个特性，连续性自动通过 | manifest.md |

### 存量规格读取

| 检查项 | 结果 | 证据/缺口 | 确认来源 |
|--------|------|-----------|----------|
| 存量 spec 读取 | N/A | Feat-01 为首个特性，无存量 spec | — |
| 存量 design 读取 | N/A | 无存量 design.md | — |
| 源码上下文收集 | 通过 | 已读取 WithEnv 全链路源码（WithEnvNode、EnvironmentManager、@Env/@CustomEnv 装饰器、Direction 属性体系） | 源码核对 |
| 测试覆盖评估 | 通过 | 已定位 with_env_syntax_test_ng.cpp，现有测试仅覆盖节点创建和属性存取 | 源码核对 test/unittest/core/syntax/with_env_syntax_test_ng.cpp |

### 存量规格读取记录

无长期存量规格文件。源码上下文已通过以下核验：

| 文件 | 路径 | 关键参考点 |
|------|------|-----------|
| WithEnvNode | frameworks/core/components_ng/syntax/with_env_node.h | 环境变量存储（string/double/bool/custom maps） |
| EnvironmentManager | frameworks/core/pipeline_ng/environment_manager.h/cpp | FindWithEnvNodeInternal 爬树、DependentEntry、NotifyValueChanged DFS |
| @Env/@CustomEnv | frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_decorators.ts:375-488 | 装饰器注册、EnvV2.registerEnv()、findCustomValueByKey() |
| WithEnv TS | frameworks/bridge/declarative_frontend/ark_with_env/src/WithEnv.ts | WritableSystemProperties 枚举、SDK 层 env()/customEnv() |
| LayoutProperty | frameworks/core/components_ng/layout/layout_property.h/cpp | layoutDirection_ 存储、GetNonAutoLayoutDirection() AUTO 解析 |
| Pattern::CheckLocalized | frameworks/core/components_ng/pattern/pattern.cpp:162-191 | direction 在布局中的消费点 |
| TextDirection 枚举 | interfaces/inner_api/ace_kit/include/ui/common/layout/constants.h:37-42 | LTR/RTL/INHERIT/AUTO |
| Direction TS 枚举 | frameworks/bridge/.../generated/component/enums.ets:155-159 | Ltr=0, Rtl=1, Auto=2 |
| 现有测试 | test/unittest/core/syntax/with_env_syntax_test_ng.cpp | 节点创建和属性存取测试 |

**入口表总结论：通过** — Feat-01 首个特性，连续性自动通过；源码上下文已充分收集。

---

## 出口表（arkui-specify-exit）

### 短期/长期归档分离

| 检查项 | 结果 | 证据/缺口 | 确认来源 |
|--------|------|-----------|----------|
| .specs spec.md 已创建且内容完整 | 通过 | .specs/features/withenv-direction/spec.md 包含 10 条 AC、API 变更、验证映射 | — |
| .specs design.md 已创建且含增量设计 | 通过 | .specs/features/withenv-direction/design.md 包含 5 个 ADR、对象关系、流程设计 | — |
| 长期 specs 下 Feat 文件状态正确 | 待 Stage 4 | specs/04-03-01-env-container/ 目录已创建，Stage 4 迁移 | — |
| Stage 4 迁移路径已在 manifest 中记录 | 通过 | manifest.md long_term_spec_path 和 long_term_design_path 已记录 | manifest.md |

### 交叉校验（design.md ↔ spec.md）

| 检查项 | 结果 | 证据 | 确认来源 |
|--------|------|------|----------|
| 涉及仓和模块名称一致 | 通过 | 两者均为 ace_engine 单仓 | — |
| API 名称和变更类型一致 | 通过 | SystemEnvKey/WritableSystemEnvKey/Env/CustomEnv/customEnv 签名一致 | 32825.diff 核验 |
| 架构约束不矛盾 | 通过 | spec 定义三级优先级（显式>env>AUTO），design 给出 GetEffectiveLayoutDirection 实现 | — |
| 不涉及项结论一致 | 通过 | 两者均标记 fontScale/ReadonlySystemEnvKey/跨仓/安全/IPC/构建为 N/A | — |
| AC 覆盖 | 通过 | 10 条 AC 映射到 design 的设值/查值/通知/缓存/集成路径 | — |
| SpecTest 适用性 | 通过 | AC-1/AC-5 标注 SpecTest 验证，其他为 unittest/代码审查 | — |

### 信息来源记录检查

| 检查项 | 结果 | 证据/缺口 | 确认来源 |
|--------|------|-----------|----------|
| 信息检索手段已记录 | 通过 | 本文件顶部"信息检索手段记录"区段 + 入口表"存量规格读取记录" | — |
| 源码核验已记录路径和行号 | 通过 | 入口表记录了 9 个源文件的路径和行号 | 源码核对 |
| Stage 1 与存量设计差异已核验 | N/A | Feat-01 为首个特性，无存量设计差异 | — |
| 确认来源列标注获取途径 | 通过 | 每条检查项标注了"源码核对"/"32825.diff 核验"/"Owner 对话确认" | — |
| 未核验项未标记为"通过" | 通过 | 待 Stage 4 迁移项标记为"待 Stage 4" | — |

### 出口表总结论

**通过** — design.md 和 spec.md 已创建并交叉一致。Stage 4 迁移待实现完成后执行。

---

## Specify Gate 总结论

**Approved** — 入口和出口检查均通过，Owner 于 2025-05-25 批准。执行计划和任务拆解完成后告一段落，不进入代码实现。

### Approval 记录

| 字段 | 内容 |
|------|------|
| 阶段 | 规格化 (Stage 2) |
| 决策 | Approved |
| 审批人 | 需求 Owner |
| 证据 | Owner 在对话中明确"批准进入 Stage 3，但只做到设计结束，然后告一段落，不要上手写代码"，2025-05-25 |
| 下一阶段 | 实现 (Stage 3) — 仅执行计划，不写代码 |
