# Review Gate — WithEnv direction 与 tree-state 恢复

## 审查元数据

| 项 | 内容 |
|----|------|
| Review ID | REV-ISSUE-76660-20260805 |
| 审查阶段 | 实现草稿符合性 / 代码质量 / GC 前置检查 |
| 关联文档 | `proposal.md`、`spec.md`、`design.md`、`execution-plan.md` |
| 复杂度 | 标准 |
| 涉及仓 | arkui_ace_engine |
| Reviewer | Codex 辅助审查；最终审批人未指定 |
| 日期 | 2026-08-05 |
| Base SHA | `1614e2daa1a` |
| 输入 Head SHA | `46849cd852ab` |
| 当前对象 | 输入提交 + 本轮仅文档归并工作区 |

## 审查输入

| 输入 | 路径/范围 | 说明 |
|------|-----------|------|
| Requirement | `proposal.md` | 原基线及 2026-08-05 生命周期补充 |
| Spec | `spec.md` | AC-1.1～AC-4.6 |
| Design | `design.md` | 实际 reader/callback 模型、时序和风险 |
| Plan | `execution-plan.md` | TASK-001～TASK-003 与验证矩阵 |
| Diff | `46849cd852ab` | 生命周期实现、C++ 测试和原始 Markdown 输入 |

## GA / GB 基线回顾

| 检查项 | 结论 | 证据 |
|--------|------|------|
| direction、显式覆盖和最近祖先目标明确 | PASS（历史基线） | `proposal.md` baseline_approval 记录 |
| 下树默认值、懒初始化和离屏首次读取已进入需求补充 | PASS（文档一致性） | `proposal.md` 2026-08-05 讨论记录、`spec.md` US-4 |
| spec 只描述可观察行为，design 承载类/方法/时序 | PASS（本轮文档审查） | `spec.md`、`design.md` |
| fontScale 默认值未被纳入本期规格 | PASS | proposal/spec/design 明确 N/A |
| 最终 Design/Plan Owner 审批 | NOT RECORDED | Owner/目标版本仍未指定；不得由 AI 自评替代 |

## 实现草稿规范符合性

| AC | 静态实现证据 | 运行证据 | 结论 |
|----|--------------|----------|------|
| AC-1.1～AC-1.4 | direction handler、最近祖先解析和 layout fallback 已存在 | targeted component/HAP 未提供 fresh 结果 | PASS（静态）/ UNVERIFIED（运行） |
| AC-2.1～AC-2.4 | direct-query getter、system update bridge、只读 setter 已存在 | ArkTS/HAP 未执行 | PASS（静态）/ UNVERIFIED（运行） |
| AC-3.1～AC-3.4 | layout 显式值优先；嵌套 owner 解析和 focus 消费链可追溯 | layout/focus targeted 回归未执行 | PASS（静态）/ UNVERIFIED（运行） |
| AC-4.1 | detach 先注销 reader；TS detach 不查 native并恢复 direction/local custom default | native gtest 与 HAP-1 未执行 | PASS（静态）/ UNVERIFIED（运行） |
| AC-4.2 | attach 在新 parent/context 就绪后重查；同/跨 context gtest 已写 | 两个 reparent gtest 未执行；HAP-1 未执行 | PASS（静态）/ UNVERIFIED（运行） |
| AC-4.3 | callback 缺失表示无消费；handler 对每个变量继续检查 own backing | callback activation gtest 未执行；HAP-3 未执行 | PASS（静态）/ UNVERIFIED（运行） |
| AC-4.4 | native find 前 Ensure，即使 context 为空也保留后续 attach 入口 | off-tree activation gtest 未执行；HAP-2 未执行 | PASS（静态）/ UNVERIFIED（运行） |
| AC-4.5 | CustomEnv initializer 写独立 local-default backing，覆盖值写 current backing | HAP-1/HAP-4 未执行 | PASS（静态）/ UNVERIFIED（运行） |
| AC-4.6 | Ensure 幂等，真实 tree-state 事件只回调一次；每个实际变化 fireChange/Watch 一次 | 多 key Watch 运行证据缺失 | PASS（静态）/ UNVERIFIED（运行） |

静态 PASS 只表示实现形状与规格一致，不替代编译或测试 PASS。

## 多余实现与范围检查

| 实现内容 | 是否在 Spec/Plan 中 | 风险 | 处理 |
|----------|---------------------|------|------|
| direction direct-query 默认值 `Auto` | 是 | 低 | 保留 |
| CustomEnv local-default backing | 是 | 低 | 保留 |
| direct-query getter 曾增加 own-property 判定与 TS fallback | 不属于 lifecycle 修正，且会改变 fontScale 的既有重复查询特征 | 中 | 已恢复原有 truthy 初始化条件并直接使用 native 返回值；不定义 fontScale 默认值或初始化次数新规格 |
| CustomNode Set/Has/Reset callback | 是，内部设计 | 低 | 保留；分别用于安装、Ensure 幂等、reuse 清旧 callback |
| 全局 manager/root 注册表、mutex、UINode reader count | 否 | 高 | 已撤回，不应恢复 |
| 900+ 行 ETS 草稿 | 否，未执行示例不是交付证据 | 中 | 删除独立文档，仅保留 execution-plan 场景矩阵 |

## 时序与重入审查

1. attach：AddChild 先 `SetParent`，随后 `AttachContext` 和 `onMainTree=true`，再进入 CustomNode callback；attach 查值具备新 parent/context。
2. detach：先 `onMainTree=false`、保存 old context、清 node context，再以 old manager 注销 reader，最后 callback(false)；旧 parent 在 `OnRemoveFromParent` 后半段才 Reset。
3. 正常 TS detach handler 不执行 native find；direction backing 已写入 truthy 的 `Auto`，Watch 间接触发普通 getter时不会再次查询。
4. `DetachContext(false)` 只清空 attached context；`UINode::GetContext()` 会回退当前 PipelineContext，而旧 parent 尚未 Reset，因此 detach 窗口内若直接调用 native find，仍可能沿旧 parent 解析并重新注册。
5. 残余风险：EnvironmentManager 的 find/register 接口本身未拒绝 off-main-tree reader。返回 `undefined` 的 direct-query key、直接 native 调用或其他重入入口仍可能在 ResetParent 前沿旧 parent 重绑；当前 TS handler 只避免了标准 detach 处理自身触发该风险。

结论：现有路径的时序设计成立，但“off-main-tree consumer 不得解析/注册 WithEnv”应作为后续底层不变量；新增查询入口必须先验证此约束。

## PR #87514 意见闭环

| 意见 | 结论 |
|------|------|
| CustomNode 不应直接强持有 JS function | 已吸收：JSView 持有并在 Destroy/析构清空；CustomNode 仅捕获 WeakPtr |
| fontScale detach 默认值 | 不采纳业务默认值：本期只定义 direction=`Auto`，fontScale 保持无已定义默认值 |
| tree-state TS handler 缺单测 | 不新增 TS unittest；但必须保留 ArkTS/HAP 端到端缺口，不能用 C++ 测试冒充覆盖 |
| 跨 PipelineContext reparent 和 detach-without-reattach | 已补 C++ 用例代码；运行结果仍缺失 |
| tree-state debug 日志 | 已吸收入口/结束与 `needUpdated` 日志 |
| 默认值 helper 类型 | 保持内部 `unknown`，避免为未规格化的其他 key 扩张类型承诺 |

## 代码质量审查

| 检查项 | 结论 | 证据/说明 |
|--------|------|-----------|
| 模块边界 | PASS（静态） | 查询缺省转换在 bridge，detach 本地复位在状态管理，生命周期在 CustomNode，索引在 EnvironmentManager |
| 抽象层次 | PASS（静态） | callback 本身表达消费关系，无 first-attach 双状态 |
| 重复工作 | PASS（静态） | Ensure 幂等；system/custom 各一次 forEach；dirty flush 合并 |
| 引用链 | PASS（静态） | JSView 清 JS handler，CustomNode weak forward |
| API/ABI | PASS（静态） | lifecycle 修改仅内部 C++ 方法，无公共 C ABI |
| 性能 | WARN | 每个 find 有一次廉价 Ensure；attach 按已初始化 key 查询；无 benchmark |
| 测试质量 | WARN | native case 已补但未运行，TS/HAP 证据缺失 |
| detach parent 时差 | WARN | 当前 bridge 安全，但底层缺 off-main-tree 防线 |

## GC Final Delivery Gate

| 检查项 | 结论 | 证据 |
|--------|------|------|
| 文档结构与职责归并 | PASS | `git diff --check`；`ohos-sdd validate --level all` 35/35、0 broken、0 warning |
| native 定向测试 | BLOCKED | 当前仓 checkout 无 OpenHarmony 根目录 `build.sh`/out 产物 |
| ArkTS/HAP 主场景 | NOT RUN | HAP-1～HAP-4 无运行报告 |
| AC 逐条运行闭环 | FAIL | 静态审查不能替代运行证据 |
| 公共 API/ABI/依赖风险 | PASS（静态） | 未新增 lifecycle 公共接口或依赖 |
| Open Issues 已关闭 | FAIL | native/HAP 证据和 off-tree 底层不变量仍开放 |

## Open Issues

| 类型 | 问题 | 处理方式 | Owner |
|------|------|----------|-------|
| blocker | 4 个 lifecycle gtest 未在完整构建环境运行 | 按 execution-plan 命令编译并执行，保存日志 | 模块 Owner |
| blocker | HAP-1～HAP-4 未执行 | 在含本特性 SDK 的真实 ArkTS 工程运行并归档 | 模块 Owner |
| risk | EnvironmentManager 未统一拒绝 off-main-tree reader | 后续设计底层 guard 并补重入测试；不能依赖空 attached context，因为 `GetContext()` 会回退当前 PipelineContext | EnvironmentManager Owner |
| follow-up | O(1) cache、PRECISE implicit、dump | 单独立项，不阻塞本期功能正确性 | 后续需求 Owner |

## 审查决策

| 项 | 内容 |
|----|------|
| Decision | ChangesRequested |
| 下一阶段 | 完成 fresh 文档校验；在完整环境执行 native 与 ArkTS/HAP 验证后重审 GC |
| Recheck Scope | AC-1.*～AC-4.* 运行证据、fontScale 无新增默认行为、detach 重入风险 |
| 修改意见 | 不得把“测试代码存在”“静态路径可推导”表述为“测试通过”或“可合入” |

**审查摘要：** 文档职责和实现时序已收敛；当前没有确认的实现缺陷，但验证证据不足，GC 不能通过。
