# Gate Check — Stage 2 Specify

## 信息检索手段记录

| 手段 | 检索内容 | 结果 |
|------|----------|------|
| 参考规格复用 | 基于用户提供的已验证规格产物 | 内容完全有效，用户确认 |
| 源码核对 | 动态语言路径 frame_node.ts:1233 | 确认 fireArkUIObjectLifecycleCallback 调用链路 |
| 源码核对 | 静态语言路径 FrameNode.ets:534 | 确认缺失 lifecycle callback |

## ARKUI-G3a：Stage 2 入口检查（存量特性归档）

| 检查项 | 结果 | 证据/理由 |
|--------|------|-----------|
| FuncID 下已注册 FeatID 列表已读取 | 通过 | 04-06-02/03/04/05 为新建域，各域 Feat-01 为首个特性，无存量 Feat |
| FeatID 连续性预检 | N/A | 各域 Feat-01 为首个特性，无前置编号需要检查 |
| 存量特性归档检查 | N/A | 新建功能域，无存量规格需要归档 |
| 存量规格读取（作为设计参考） | N/A | 新建域，无存量 design.md/spec.md |

**ARKUI-G3a 结论: 通过**

## 并行产出锚点

| 检查项 | 结果 | 证据/理由 |
|--------|------|-----------|
| proposal.md API 变更项清单已填写或标记 N/A | 通过 | proposal.md API 变更评估表已填写，无 Public API 变更 |
| design.md 和 spec.md 引用的仓/模块列表与 proposal.md 影响范围一致 | 通过 | 三份文档均引用 ace_engine / arkts_frontend |

## 二、规格化阶段检查（通用）

### 设计检查

| 检查项 | 结果 | 证据/理由 |
|--------|------|-----------|
| 分层调用合规 | 通过 | ETS → ANI Bridge → C++ PipelineContext，严格单向 |
| 无跨层违规调用 | 通过 | 无反向依赖 |
| 子系统边界清晰 | 通过 | 仅 arkts_frontend 子系统 |
| API 命名符合 OH 规范 | N/A | 无 Public API 变更 |
| 错误码不冲突 | N/A | 无新错误码 |
| 数据模型定义完整 | 通过 | ArkUIObjectLifecycleData 结构体已定义（design.md ADR-2） |
| 构建系统影响已评估 | 通过 | 无 BUILD.gn/bundle.json 变更 |
| IPC/异步超时行为 | N/A | 无 IPC 调用 |
| 接口参数规约 | N/A | 无 Public/System API |

### 一致性检查（design.md 与 spec.md 交叉校验）

| 检查项 | 结果 | 证据/理由 |
|--------|------|-----------|
| 涉及仓和模块名称一致 | 通过 | 均为 ace_engine / arkts_frontend |
| API 名称和变更类型一致 | 通过 | 均为 `_FireArkUIObjectLifecycleCallback` InnerApi |
| 架构约束不矛盾 | 通过 | spec 声明 ETS→C++ 单向，design 给出 ANI Bridge 满足方案 |
| 不涉及项结论一致 | 通过 | 均为无障碍/国际化/多形态 N/A |

### Spec 检查

| 检查项 | 结果 | 证据/理由 |
|--------|------|-----------|
| 用户故事和 AC 完整 | 通过 | 7 个 US（含 US-1b TypedFrameNode）、9 个 AC（WHEN/THEN） |
| AC 覆盖正常/异常/边界 | 通过 | 正常(AC-1.1~4.1, AC-1b.1)、数据一致(AC-5.1)、边界(AC-6.1~6.3) |
| Spec 中无 InnerKit 接口定义/内部实现细节 | 通过 | Spec 仅描述 PipelineContext 行为，不涉及内部实现 |
| API 变更分析完整 | 通过 | 新增 InnerApi ANI 函数已记录 |
| 兼容性声明完整 | 通过 | 无行为变更，纯新增内部调用 |
| 非功能需求有指标或 N/A | 通过 | 性能/安全/兼容性 N/A |
| 全局特性影响已筛选 | 通过 | 无障碍/大字体/深色模式/多窗口/多用户 均为"否" |

## ARKUI-G3b：Stage 2 出口检查

| 检查项 | 结果 | 证据/理由 |
|--------|------|-----------|
| spec.md 写清行为规则和验收标准 | 通过 | 功能规则(FR-1/FR-2)、业务规则(BR-1/BR-2)、异常规则(EX-1) |
| design.md 写清分层、对象关系、状态流转 | 通过 | 数据流图 + 3 个 ADR |
| design.md 与 spec.md 一致 | 通过 | API 名称、模块边界、不涉及项均一致 |
| 涉及热路径时 Performance Budget 填写 | N/A | dispose 非热路径 |
| 涉及内存分配时分配/释放点和所有权说明 | 通过 | ArkUIObjectLifecycleData 栈分配 |
| P0/P1 AC 映射到验证命令 | 通过 | UT + 设备验证覆盖 AC-1.1~4.1 |
| SpecTest 映射 | N/A | 回调注册仅 InnerApi，设备验证替代 |

## 总结论

**Stage 2 Gate 结论: 通过**

所有入口/出口检查项均有明确结论和证据。Owner 已确认参考规格内容完全有效。
