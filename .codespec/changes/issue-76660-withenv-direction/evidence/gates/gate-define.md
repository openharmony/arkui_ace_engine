# Define Gate — WithEnv Direction & Framework Refactoring

## 信息检索手段记录

| 手段 | 检索内容 | 结果 |
|------|----------|------|
| 32825.diff 读取 | API 接口定义 | 已读取，获取完整 API 变更定义 |
| Owner 对话 | 功能域、范围、优先级、性能标准 | 6 轮问答，所有关键点已澄清 |
| 源码核对 | 待 Stage 2 补充（Stage 1 先定义范围） | — |

---

## 入口表（arkui-define-entry）

### 功能树与定位

| 检查项 | 结果 | 证据/缺口 | 确认来源 | 后续动作 |
|--------|------|-----------|----------|----------|
| FuncID 已确认 | 通过 | FuncID 04-03-01 | Owner 对话确认 2025-05-25 | 无 |
| FeatID 已确认 | 通过 | FeatID Feat-01 | Owner 对话确认 2025-05-25 | 无 |
| specs/index.md 已注册 | 通过 | specs/index.md 已创建，FuncID 04-03-01 和 Feat-01 已注册 | Agent 创建 + Owner 确认功能域名称 | 无 |
| profile 已选择 | 通过 | arkui (arkui/component, arkui/sdk-api)，理由：WithEnv 是容器组件 + 新增 Public API | Owner 确认 | 无 |
| lineage 已选择 | 通过 | new-on-legacy，依据：已有 WithEnv 骨架，新增特性 + 重构 | Owner 对话确认 | 无 |
| .specs 流程实例路径已创建 | 通过 | .specs/features/withenv-direction/ | Agent 创建 | 无 |
| long_term_spec_path 已确定 | 通过 | specs/04-03-01-env-container/Feat-01-direction-spec.md | Agent 基于 FuncID/FeatID 推导 | 无 |
| long_term_design_path 已确定 | 通过 | specs/04-03-01-env-container/design.md | Agent 基于 FuncID 推导 | 无 |
| spectest_feature_path 适用性 | 待确认 | direction 影响布局方向，理论上可通过 Inspector 观测；待 Stage 2 详细评估 | 待评估 | Stage 2 补充 |

### 影响面与 ArkUI 补充项

| 检查项 | 结果 | 证据/缺口 | 确认来源 | 后续动作 |
|--------|------|-----------|----------|----------|
| 交互开始/结束判定 | N/A | direction 不是交互触发型能力，由声明式 API 设置 | — | 无 |
| 合法延迟状态 | N/A | env 值在 WithEnv 创建时同步设置，无异步延迟 | — | 无 |
| 异常状态边界 | 通过 | 无 WithEnv 祖先时 @Env 使用默认值（AC-4） | Owner 对话确认 | 无 |
| 异常豁免规则 | 通过 | 显式设置覆盖 env 默认值（AC-5） | Owner 对话确认 | 无 |
| 维测合同 | 通过 | 可以添加 dump 信息，较为次要；HiLog 日志按框架常规处理 | Owner 对话确认 2025-05-25 | 无 |
| 热路径预算 | 通过 | env 查值命中 layout 路径（direction 影响布局方向），设计目标为 O(1) 查值 | Owner 对话确认（性能为设计目标） | design.md 详细分析 |
| 前端/API/依赖/跨平台影响 | 通过 | 新增 Public API，ace_engine 单仓，无跨仓/跨平台影响 | Owner 确认 | 无 |
| 无障碍 | 是 | direction 影响语义树（RTL/LTR），需设计分析 | — | spec.md |
| 国际化 | 是 | direction 直接关联国际化，核心交付价值 | Owner 对话确认 | spec.md |
| 多形态适配 | N/A | direction 行为不因设备形态变化 | — | 无 |
| Host 可测项 | 待确认 | 布局方向理论上可通过 Inspector 观测 | 待 Stage 2 评估 | 无 |
| SpecTest 可测项 | 待确认 | 待评估 SpecTest 对 direction 布局断言的支持 | 待 Stage 2 评估 | 无 |
| 设备补验项 | 待确认 | 待评估是否需要真实设备验证 RTL 布局 | 待 Stage 2 评估 | 无 |

### 入口表总结论

**Blocked** — 以下项待补齐：
1. 基线审批待 Owner 审阅 proposal.md 后确认
2. spectest_feature_path 适用性待 Stage 2 评估（非阻塞）

---

## 出口表（arkui-define-exit）

### 基线审批检查

| 检查项 | 结果 | 证据/缺口 | 确认来源 | 后续动作 |
|--------|------|-----------|----------|----------|
| Owner 已审阅 proposal.md 并批准基线 | Blocked | manifest.baseline_approval.approved=false | — | 待 Owner 审阅 |

### 信息来源记录检查

| 检查项 | 结果 | 证据/缺口 | 确认来源 | 后续动作 |
|--------|------|-----------|----------|----------|
| 信息检索手段已记录 | 通过 | 本文件顶部"信息检索手段记录"区段 | — | 无 |
| 证据/缺口列包含完整来源链路 | 通过 | 入口表每行含证据和确认来源 | — | 无 |
| 确认来源列标注获取途径 | 通过 | 标注了 Owner 对话确认 / 32825.diff 读取 / Agent 创建 | — | 无 |
| 源码核验已记录路径和行号 | 待确认 | Stage 1 侧重范围定义，源码核验待 Stage 2 补充 | — | Stage 2 补充 |
| 未核验项未标记为"通过" | 通过 | 源码核验相关项标注为"待确认" | — | 无 |

### 出口表总结论

**Blocked** — 等待：
1. Owner 审阅 proposal.md 并批准基线
2. 维测合同确认
3. Stage 2 补充源码核验

---

## Define Gate 总结论

**Approved** — proposal.md 已完成，Owner 于 2025-05-25 批准基线。spectest_feature_path 待 Stage 2 评估为非阻塞项。

### Approval 记录

| 字段 | 内容 |
|------|------|
| 阶段 | 定义 (Stage 1) |
| 决策 | Approved |
| 审批人 | 需求 Owner |
| 证据 | Owner 在对话中明确"批准 stage1"，2025-05-25 |
| 下一阶段 | 规格化 (Stage 2) |
