# 需求文档

> 一份文档，从原始需求到基线结论。按阶段追加内容，不拆成多份独立文件。

## 一、原始需求

### 基本信息

| 字段 | 内容 |
|------|------|
| 需求ID | REQ-20260521-01 |
| 需求名称 | 静态语言命令式节点 JsLeakWatcher 内存上报能力 |
| 来源 | 内部需求 |
| 提出人 | sunbees |
| 目标发行版本 | TBD |
| 候选 Profile | arkui |
| 优先级 | P1 |
| 状态 | Baselined |

### 原始描述

**原始问题：** 提供静态语言下命令式节点（BuilderNode、FrameNode、RenderNode、ComponentContent）的 JS 内存上报能力，主要能力是当这些命令式节点在调用了 dispose 和后端节点解绑之后，应该被销毁，此时应该调用 JsLeakWatcher 注册的回调方法上报节点类型和对应节点的弱引用。

**痛点：**

| 用户类型 | 当前痛点 | 影响 |
|----------|----------|------|
| 系统开发者（JsLeakWatcher） | 静态语言路径下无法感知命令式节点的 dispose 生命周期事件 | 无法对静态语言路径的节点进行 JS 内存泄漏检测 |
| 应用开发者 | 节点 dispose 后可能因引用未释放导致 JS 内存泄漏 | 内存占用持续增长，影响应用性能 |

**期望结果：** 静态语言路径的命令式节点 dispose 时，能通过已有机制通知 JsLeakWatcher，使其能检测到节点的销毁事件并上报相关信息。

### 背景证据

| 证据类型 | 链接/路径 | 说明 |
|----------|-----------|------|
| 源码对比 | 动态语言：`frameworks/bridge/declarative_frontend/ark_node/src/frame_node.ts:1233` | 动态语言已在 dispose 中调用 fireArkUIObjectLifecycleCallback |
| 源码缺失 | 静态语言：`frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/FrameNode.ets:534` | 静态语言的 dispose 中无任何 lifecycle callback 调用 |

### 初始范围

**可能包含：**
- 在静态语言的 4 个命令式节点 dispose() 中添加 fireArkUIObjectLifecycleCallback 调用
- 新增 ANI Bridge 函数，桥接 ETS 层到 C++ PipelineContext
- 保持与动态语言路径完全一致的调用链和数据格式

**明确不包含：**
- PipelineContext 本身的修改（已有完整机制）
- 动态语言路径的修改（已实现）
- UIContext 接口的修改（JsLeakWatcher 自行通过该接口注册）
- JsLeakWatcher 组件本身的实现（外部组件）

### 初始假设

| 假设 | 类型 | 验证方式 | 状态 |
|------|------|----------|------|
| PipelineContext::FireArkUIObjectLifecycleCallback 可被静态语言路径复用 | 技术 | 源码验证 PipelineContext 是共享的 | 已验证 |
| ANI Bridge 可参照现有模式新增函数 | 技术 | 查看 ArkUIAniModule 现有注册模式 | 已验证（ArkUIAniModule.ts:408, module.cpp:1187 注册模式一致） |

### 初始分级判断

| 判断项 | 结果 | 依据 |
|--------|------|------|
| 复杂度 | 标准 | 单仓，涉及 ETS + C++ 两层修改，模式明确（参照动态语言） |
| 涉及仓数量 | 1 | ace_engine |
| 是否涉及 Public/System API | 否 | 不新增/修改公开 API，仅内部桥接 |
| 是否涉及安全/性能关键路径 | 否 | dispose 路径非热路径，仅增加一次回调 |
| 是否跨 SIG | 否 | 仅 arkui 仓 |

### 进入澄清条件

- [x] 原始问题和期望结果已记录
- [x] 需求来源和责任人已明确
- [x] 初始范围和不包含项已记录
- [x] 关键假设和待澄清问题已列出
- [x] 复杂度有判断或明确为待定

---

## 二、澄清记录

> 澄清是逐轮对话，不是一次性填表。先从"待澄清问题"出发，一次只讨论一个问题，结论确认后再写入本记录。

### 待澄清问题

| 编号 | 问题 | 为什么需要澄清 | 状态 |
|------|------|----------------|------|
| Q-1 | JsLeakWatcher 与现有 fireArkUIObjectLifecycleCallback 机制的关系 | 确定是新建、替换还是复用 | 已澄清 |
| Q-2 | 回调数据上报方式（逐个/批量/查询） | 影响设计和实现复杂度 | 已澄清 |
| Q-3 | 静态语言路径的具体差距（为何现有机制不可用） | 确定修改范围 | 已澄清 |
| Q-4 | 回调注册方式（全局/实例级） | 影响注册 API 设计 | 已澄清 |
| Q-5 | 回调函数签名 | 影响接口一致性 | 已澄清 |
| Q-6 | 调用路径（直接 TS 还是经 C++ 桥接） | 影响涉及层级和复杂度 | 已澄清 |
| Q-7 | 回调参数数量（2个还是4个） | 影响数据完整性 | 已澄清 |

### 讨论记录

| 日期 | 参与人 | 讨论主题 | 结论 | 后续动作 |
|------|--------|----------|------|----------|
| 2026-05-21 | sunbees | JsLeakWatcher 定位 | JsLeakWatcher 是外部组件，向 ArkUI 注册回调，节点 dispose 时 ArkUI 执行回调上报信息 | 确认接口边界 |
| 2026-05-21 | sunbees | 上报方式 | 逐个实时上报，每个节点 dispose 时立即传递 WeakRef + 节点类型 | 无 |
| 2026-05-21 | sunbees | 静态语言路径差距 | 动态语言有 fireArkUIObjectLifecycleCallback 调用（ark_node/src/），静态语言（arkoala-arkts/）没有 | 需在静态语言路径补齐 |
| 2026-05-21 | sunbees | 注册方式 | 全局单例注册，与动态语言一致 | 复用 registerArkUIObjectLifeCycleCallback |
| 2026-05-21 | sunbees | 回调签名 | 与动态语言一致：(weakRef: WeakRef\<object\>, msg: string) => void | 确认一致性 |
| 2026-05-21 | sunbees | 调用路径 | 必须经过 C++ PipelineContext，与动态语言一致：ETS → ANI Bridge → C++ PipelineContext → 回调 | 需新增 ANI 桥接函数 |
| 2026-05-21 | sunbees | 回调参数 | 4 个参数（WeakRef + className + nodeType + nodePtr），与动态语言一致 | 确认参数列表 |

### 功能范围确认

| 问题 | 回答 | 确认人 | 状态 |
|------|------|--------|------|
| 核心功能包含哪些？ | 在静态语言 4 个节点 dispose() 中添加 fireArkUIObjectLifecycleCallback 调用，经 ANI Bridge 到达 PipelineContext | sunbees | 已确认 |
| 明确不包含哪些？ | PipelineContext 修改、动态语言修改、UIContext 接口修改、JsLeakWatcher 组件实现 | sunbees | 已确认 |
| 是否有分期策略？ | 无，一次性交付 | sunbees | 已确认 |

### 方案探索

> 标准复杂度，至少列出 2 个方案。

| 编号 | 方案概述 | 优势 | 风险/代价 | 选择结论 |
|------|----------|------|-----------|----------|
| A-1 | 完整复制动态语言路径：ETS → ANI Bridge → PipelineContext → 回调 | 与动态语言完全一致，复用已有 C++ 机制，JsLeakWatcher 无需区分语言路径 | 需要新增 ANI Bridge 函数（C++ 修改） | **推荐** |
| A-2 | 纯 ETS 直调：dispose() 中直接调用 ArkUIObjectFinalizationRegisterProxy.call() | 实现简单，无需 C++ 修改 | 跳过 PipelineContext，与动态语言路径不一致，JsLeakWatcher 可能收到不同格式的数据 | 放弃 |

**取舍理由：** A-1 通过 PipelineContext 触发 JsLeakWatcher 注册的 C++ 回调（通过 UIContext），与动态语言路径一致。A-2 跳过 PipelineContext，JsLeakWatcher 的 C++ 回调无法收到通知。静态语言路径不经过 JSI Runtime，TS 回调（registerArkUIObjectLifeCycleCallback）在两种方案下都不会被触发。

### 子系统影响

| 问题 | 回答 | 确认人 | 状态 |
|------|------|--------|------|
| 涉及哪些子系统？ | arkts_frontend（ETS 层 + ANI Bridge C++ 层） | sunbees | 已确认 |
| 是否需要新增子系统或部件？ | 否 | sunbees | 已确认 |

### API 变更评估

| 问题 | 回答 | 确认人 | 状态 |
|------|------|--------|------|
| 是否需要新增/修改 Public API？ | 否 | sunbees | 已确认 |
| 是否需要新增 System API？ | 否 | sunbees | 已确认 |
| 是否会废弃已有 API？ | 否 | sunbees | 已确认 |
| 是否需要新增权限声明？ | 否 | sunbees | 已确认 |

### 兼容性与非功能需求

| 类别 | 核心问题 | 结论 | 确认人 | 状态 |
|------|----------|------|--------|------|
| 兼容性 | 破坏性变更？ | 无。仅新增回调调用，不修改已有行为 | sunbees | 已确认 |
| 性能 | 影响？ | 极小。dispose 非热路径，仅增加一次回调调用 | sunbees | 已确认 |
| 安全 | 风险？ | 无。使用 WeakRef，不会延长对象生命周期 | sunbees | 已确认 |
| 可靠性 | 风险？ | 无影响。回调失败不影响 dispose 流程（CHECK_NULL_VOID 保护） | sunbees | 已确认 |

### 依赖与风险

| 依赖项 | 类型 | 说明 | 状态 |
|--------|------|------|------|
| PipelineContext::FireArkUIObjectLifecycleCallback | 运行 | 已有机制，无需修改 | 已确认 |
| ANI Bridge 注册机制 | 编译 | 需要确认新增函数的注册方式 | 已验证（module.cpp:1187 staticMethods 注册，编译通过） |

| 风险 | 类型 | 影响 | 缓解措施 | 状态 |
|------|------|------|----------|------|
| ANI Bridge 函数注册模式不明确 | 技术 | 低 | 参照 ArkUIAniModule 现有函数注册方式 | 已确认 |

### AC 完整性

- [x] 每个用户故事有验收标准
- [x] AC 全部使用 WHEN/THEN 格式
- [x] 覆盖正常流程、异常流程、边界条件
- [x] AC 可测试、可度量

### 澄清结论

- [x] 功能范围已完全明确
- [x] 子系统影响已识别
- [x] API 变更已评估
- [x] 兼容性和非功能需求已确认
- [x] 依赖和风险已识别且有缓解方案
- [x] 已完成方案探索（2 个方案 + 取舍理由）

**结论:** 通过

### ARKUI Owner 输入记录（ARKUI-G1/G2）

| Gate | 问题 | Owner 回答 | 确认原文/链接 | 状态 |
|------|------|------------|----------------|------|
| ARKUI-G1 | FuncID 是什么？ | 04-06-02 (primary), also 04-06-03/04/05 | 对话确认 | 已确认 |
| ARKUI-G1 | FeatID 是什么？ | 各域均为 Feat-01 | 对话确认 | 已确认 |
| ARKUI-G1 | `specs/index.md` 注册是否完成？ | 已完成，04-06-01~05 已注册 | 对话确认 | 已确认 |
| ARKUI-G1 | Profile/Lineage 如何选择？ | profile=arkui, 无子 profile, lineage=new-on-legacy | 对话确认 | 已确认 |
| ARKUI-G1 | long_term_spec_path / long_term_design_path | `specs/04-common-capability/06-custom-node-capability/` | 对话确认 | 已确认 |
| ARKUI-G1 | spectest_feature_path 是否适用？ | N/A — 回调注册仅 InnerApi，外部无法注册带 UI 逻辑的回调 | Owner 确认 | 已确认 |
| ARKUI-G2 | 交互开始/结束判定 | N/A — 内部桥接层变更，无用户交互 | 对话确认 | 已确认 |
| ARKUI-G2 | 合法延迟状态 | N/A — dispose 为同步调用 | 对话确认 | 已确认 |
| ARKUI-G2 | 异常状态边界 | N/A — PipelineContext::CHECK_NULL_VOID 保护 | 对话确认 | 已确认 |
| ARKUI-G2 | 异常豁免规则 | N/A — 无用户可见异常 | 对话确认 | 已确认 |
| ARKUI-G2 | 维测合同 | UT（断言 PipelineContext::FireArkUIObjectLifecycleCallback 被调用） | Owner 确认 | 已确认 |
| ARKUI-G2 | 热路径预算 | N/A — dispose 非热路径 | 对话确认 | 已确认 |
| ARKUI-G2 | 前端/API/依赖/跨平台影响 | N/A — 纯内部桥接 | 对话确认 | 已确认 |
| ARKUI-G2 | 无障碍/国际化/多形态 | N/A — 无 UI 行为、无用户可见字符串 | 对话确认 | 已确认 |
| ARKUI-G2 | Host 可测项 | N/A — 回调注册仅 InnerApi，Host 无法注入 UI 逻辑 | Owner 确认 | 已确认 |
| ARKUI-G2 | SpecTest 可测项 | N/A — 无公开方式注册回调触发 UI 变化 | Owner 确认 | 已确认 |
| ARKUI-G2 | 设备补验项 | N/A — UT 可覆盖 | Owner 确认 | 已确认 |

---

## 三、需求基线

> 澄清完成后固化。manifest.md 是事实源，此处为审批结论。

### 基线信息

| 字段 | 内容 |
|------|------|
| 基线版本 | v1.0 |
| 基线日期 | 2026-05-21 |
| Owner | sunbees |
| 确认人 | sunbees |
| 复杂度 | 标准 |
| Profile | arkui |
| 目标发行版本 | TBD |
| 版本状态 | proposed |

### 问题陈述

静态语言路径（arkoala-arkts）的命令式节点（BuilderNode、FrameNode、RenderNode、ComponentContent）在调用 dispose() 时，不经过 C++ PipelineContext 通知 JsLeakWatcher，导致 JsLeakWatcher 无法检测静态语言路径下这些节点的 JS 内存泄漏。需要补齐与动态语言路径一致的 fireArkUIObjectLifecycleCallback 调用链路。

### 目标和成功指标

| 目标 | 成功指标 | 验证方式 |
|------|----------|----------|
| 静态语言节点 dispose 时通知 JsLeakWatcher | 节点 dispose 后 PipelineContext::FireArkUIObjectLifecycleCallback 被调用 | UT 验证 |
| 回调数据与动态语言一致 | 4 个参数（WeakRef + className + nodeType + nodePtr）格式一致 | 对比动态语言参数 |
| 4 种节点类型均支持 | FrameNode、RenderNode、BuilderNode、ComponentContent 各有回调 | 逐一验证 |

### 用户故事与 AC

| Story ID | 用户故事 | 优先级 |
|----------|----------|--------|
| US-1 | 作为 JsLeakWatcher 开发者，我希望静态语言路径的 FrameNode dispose 时能触发已注册的回调，以便检测 FrameNode 的 JS 内存泄漏 | P0 |
| US-2 | 作为 JsLeakWatcher 开发者，我希望静态语言路径的 RenderNode dispose 时能触发已注册的回调，以便检测 RenderNode 的 JS 内存泄漏 | P0 |
| US-3 | 作为 JsLeakWatcher 开发者，我希望静态语言路径的 BuilderNode dispose 时能触发已注册的回调，以便检测 BuilderNode 的 JS 内存泄漏 | P0 |
| US-4 | 作为 JsLeakWatcher 开发者，我希望静态语言路径的 ComponentContent dispose 时能触发已注册的回调，以便检测 ComponentContent 的 JS 内存泄漏 | P0 |
| US-5 | 作为 JsLeakWatcher 开发者，我希望回调数据与动态语言路径一致，以便统一处理两种语言路径的内存上报 | P1 |

| AC编号 | 验收标准 | 类型 | 关联Story |
|--------|----------|------|-----------|
| AC-1 | WHEN 静态语言 FrameNode 调用 dispose() 且 nodePtr 有效 THEN 通过 ANI Bridge 调用 PipelineContext::FireArkUIObjectLifecycleCallback，传递 (WeakRef, 'FrameNode', nodeType, nodePtr) | 正常 | US-1 |
| AC-2 | WHEN 静态语言 RenderNode 调用 dispose() 且 nodePtr 有效 THEN 通过 ANI Bridge 调用 PipelineContext::FireArkUIObjectLifecycleCallback，传递 (WeakRef, 'RenderNode', nodeType, nodePtr) | 正常 | US-2 |
| AC-3 | WHEN 静态语言 BuilderNode 调用 dispose() 且 nodePtr 有效 THEN 通过 ANI Bridge 调用 PipelineContext::FireArkUIObjectLifecycleCallback，传递 (WeakRef, 'BuilderNode', nodeType, nodePtr) | 正常 | US-3 |
| AC-4 | WHEN 静态语言 ComponentContent 调用 dispose() 且 nodePtr 有效 THEN 通过 ANI Bridge 调用 PipelineContext::FireArkUIObjectLifecycleCallback，传递 (WeakRef, 'ComponentContent', nodeType, nodePtr) | 正常 | US-4 |
| AC-5 | WHEN 节点已 dispose（isDisposed() === true）THEN 不重复触发回调 | 边界 | US-1~4 |
| AC-6 | WHEN 节点 nodePtr 为 null/undefined THEN 不触发回调（跳过 fire 调用） | 异常 | US-1~4 |
| AC-7 | WHEN JsLeakWatcher 通过 UIContext::RegisterArkUIObjectLifecycleCallback 注册回调 THEN 静态语言节点 dispose 时回调被触发，收到与动态语言一致的数据格式 | 正常 | US-5 |

### 范围边界

**包含：**
- ETS 层：修改 FrameNode.ets、RenderNode.ets、BuilderNode.ets、ComponentContent.ets 的 dispose() 方法
- C++ 层：新增 ANI Bridge 函数 fireArkUIObjectLifecycleCallback
- 确保回调参数格式与动态语言一致（4 参数）

**不包含：**
- PipelineContext 本身的修改
- 动态语言路径的修改
- UIContext 接口的修改
- JsLeakWatcher 组件本身的实现
- SDK 公开 API 的变更

### 影响范围

| 子系统 | 仓库 | 模块/路径 | 当前职责 | 影响类型 | Owner |
|--------|------|-----------|----------|----------|-------|
| arkts_frontend | ace_engine | `arkoala-arkts/arkui-ohos/src/FrameNode.ets` | 静态语言 FrameNode 实现 | 修改 | sunbees |
| arkts_frontend | ace_engine | `arkoala-arkts/arkui-ohos/src/RenderNode.ets` | 静态语言 RenderNode 实现 | 修改 | sunbees |
| arkts_frontend | ace_engine | `arkoala-arkts/arkui-ohos/src/BuilderNode.ets` | 静态语言 BuilderNode 实现 | 修改 | sunbees |
| arkts_frontend | ace_engine | `arkoala-arkts/arkui-ohos/src/ComponentContent.ets` | 静态语言 ComponentContent 实现 | 修改 | sunbees |
| arkts_frontend | ace_engine | ANI Bridge 层（待确认具体文件） | ANI 原生函数注册 | 新增 | sunbees |

### 不涉及项确认

| 维度 | 涉及？ | 依据 | 若涉及，进入哪个下游文档 |
|------|--------|------|--------------------------|
| 性能 | 否 | dispose 非热路径，仅增加一次轻量回调 | N/A |
| 安全与权限 | 否 | 无新权限，使用 WeakRef 不延长生命周期 | N/A |
| 兼容性 | 否 | 纯内部实现补齐，不改变公开行为 | N/A |
| API/SDK | 否 | 不新增/修改 Public/System API | N/A |
| IPC/跨进程 | 否 | 所有调用在同一进程内 | N/A |
| 构建与部件 | 否 | 不新增部件，不修改 bundle.json | N/A |
| 国际化/无障碍 | 否 | 无用户可见字符串 | N/A |
| 数据迁移 | 否 | 不涉及数据持久化 | N/A |

### 变更控制

| 变更类型 | 触发条件 | 处理规则 |
|----------|----------|----------|
| 范围新增 | 新增节点类型 | 重新评估影响范围 |
| AC 变更 | 修改回调参数格式 | 重新审批基线和 Spec |
| API 变更 | 不适用（不涉及公开 API） | N/A |

### 进入设计/Spec 条件

- [x] 所有 P0/P1 用户故事有 AC
- [x] 每条 AC 可测试、可度量
- [x] 范围内/外已确认
- [x] 涉及仓、模块已识别
- [x] 不涉及项已标记 N/A
- [x] 变更控制规则已确认

**基线结论:** 通过
