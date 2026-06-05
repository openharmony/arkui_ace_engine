# 架构设计

## 设计元数据

| 字段 | 内容 |
|------|------|
| Design ID | DESIGN-20260521-01 |
| 关联需求 | proposal.md |
| 目标 Feature | FEAT-20260521-jsleak-watcher-static-nodes |
| 复杂度 | 标准 |
| 目标版本 | TBD |
| Owner | sunbees |
| 状态 | Approved |

## 需求基线

| 项 | 补充说明 |
|----|------------------|
| 调用路径 | 必须经过 C++ PipelineContext，与动态语言一致 |
| 回调参数 | 4 个参数：WeakRef + className + nodeType + nodePtr |
| 不涉及 Public API | 内部桥接，不暴露公开接口 |

## 上下文和现状

### 涉及仓和模块

| 仓库 | 补充架构说明 |
|------|-------------|
| ace_engine / arkts_frontend (ETS层) | 静态语言节点实现（FrameNode.ets 等），使用 ArkUIAniModule 调用 C++ 原生函数。peer.ptr 是 C++ 节点的原生指针。 |
| ace_engine / arkts_frontend (ANI Bridge C++层) | ANI 原生函数注册在 `arkoala-arkts/arkui-ohos/src/ani/native/module.cpp` 的 `staticMethods` 数组中，使用 `ani_native_function` 结构注册。新函数为静态模块方法，签名：4 个显式参数（weakRef:WeakRef\<object\>, className:string, nodeType:string, nodePtr:long），加 ANI 隐式 (env, cls)。ETS 层传入 `new WeakRef<FrameNode>(this)` 作为首个参数。 |
| ace_engine / core (PipelineContext) | `PipelineContext::FireArkUIObjectLifecycleCallback(void* data)` 已有完整机制，接收 void* 并调用已注册的 `objectLifecycleCallback_` 回调。 |

### 现有动态语言路径（参照实现）

```
TS dispose()
  → getUINativeModule().frameNode.fireArkUIObjectLifecycleCallback(
      new WeakRef(this), 'FrameNode', nodeType, nodePtr)
  → C++ JSI Bridge: FrameNodeBridge::FireArkUIObjectLifecycleCallback()
    → 从 runtimeCallInfo 提取 arg[3] (nodePtr)
    → reinterpret_cast<FrameNode*>(nodePtr)
    → frameNode->GetContext() → PipelineContext
    → context->FireArkUIObjectLifecycleCallback(runtimeCallInfo)
  → PipelineContext 调用 objectLifecycleCallback_(data)
  → JsLeakWatcher 注册的回调接收通知
```

### 现有静态语言路径（当前缺失）

```
ETS dispose()
  → ArkUIAniModule._CheckThreadValid(false, peer.ptr)
  → peer.close()
  → 无 lifecycle callback 调用 ❌
```

### 适用架构规则

| Rule ID | 适用原因 | 设计结论 | 验证方式 |
|---------|----------|----------|----------|
| OH-ARCH-LAYERING | ETS → ANI Bridge → C++ PipelineContext | 严格单向调用，ETS 不直接引用 PipelineContext | 代码评审 |
| OH-ARCH-API-LEVEL | 无 Public API 变更 | N/A，仅内部桥接 | 无 |
| OH-ARCH-COMPONENT-BUILD | 无新增部件 | 不涉及 BUILD.gn/bundle.json 变更 | 构建验证 |

## 不涉及项承接

proposal.md 中所有维度均标记为 N/A，无需要展开设计的维度。

## 关键设计决策

### ADR-1: ANI Bridge 函数设计 — 统一函数 vs 按类型分函数

| 决策 ID | 问题 | 推荐方案 | 探索过的替代方案 | 取舍理由 | 影响 |
|---------|------|----------|-----------------|------|------|
| ADR-1 | 静态语言路径用统一还是分类型的 ANI 函数 | **统一函数**：单个 `_FireArkUIObjectLifecycleCallback` 处理所有节点类型 | 备选1：按类型分函数（_FrameNodeFireCallback 等），与动态语言 JSI bridge 一致。**放弃原因**：C++ 实现逻辑完全相同，拆分徒增维护成本。 | 统一函数减少重复代码，className 由 ETS 层传入，C++ 层无需区分节点类型 | 新增 1 个 ANI 函数（而非 4 个） |

### ADR-2: 传递给 PipelineContext 的数据格式

| 决策 ID | 问题 | 推荐方案 | 探索过的替代方案 | 取舍理由 | 影响 |
|---------|------|----------|-----------------|------|------|
| ADR-2 | ANI 路径无法传递 ArkUIRuntimeCallInfo*，需要定义新的数据格式 | **定义结构体 `ArkUIObjectLifecycleData`**，包含 weakRef、className、nodeType、nodePtr 字段，传递给 PipelineContext | 备选1：传 nullptr。**放弃原因**：JsLeakWatcher 无法获取节点信息。备选2：复用动态语言的 runtimeCallInfo 格式。**放弃原因**：静态语言路径无 JSI 运行时，无法构造 ArkUIRuntimeCallInfo。 | 结构体是最通用的方案，JsLeakWatcher 的 C++ 回调可根据数据来源判断格式（runtimeCallInfo 还是 ArkUIObjectLifecycleData） | 新增 1 个 C++ 结构体 |

### ADR-3: 调用路径 — 仅 C++ PipelineContext（与动态语言一致）

| 决策 ID | 问题 | 推荐方案 | 探索过的替代方案 | 取舍理由 | 影响 |
|---------|------|----------|-----------------|------|------|
| ADR-3 | ETS 层的调用路径应该是什么 | **仅通过 ANI Bridge → C++ PipelineContext**，不额外调用 JS Proxy | 备选1：双路通知（C++ PipelineContext + 直接调用 ArkUIObjectFinalizationRegisterProxy.call()）。**放弃原因**：动态语言路径的命令式节点只走 C++ PipelineContext，不直接调用 JS Proxy（仅 pu_view/v2_view 的自定义节点才直接调用 Proxy）。保持一致必须走单路。 | 动态语言命令式节点（FrameNode/RenderNode/BuilderNode/ComponentContent）只通过 C++ PipelineContext 通知，不直接调用 JS Proxy。静态语言应保持一致。 | ETS 层每次 dispose 仅增加一次 ANI 函数调用 |

## 设计骨架

### 数据流/控制流

```
┌─────────────────────────────────────────────────────────────────────┐
│  ETS Layer (dispose)                                                │
│                                                                     │
│  FrameNode.ets (含子类 TypedFrameNode)                              │
│  / RenderNode.ets / BuilderNode.ets / ComponentContent.ets          │
│                                                                     │
│  dispose():                                                         │
│    1. 检查 isDisposed()                                             │
│    2. if (peer?.ptr && this.nodePtr_) {                             │
│         ArkUIAniModule._CheckThreadValid(false, peer.ptr)           │
│         ArkUIAniModule._FireArkUIObjectLifecycleCallback(           │
│           new WeakRef<FrameNode>(this),                             │
│           'FrameNode', this.getNodeType(), this.nodePtr_)           │
│       }                                                             │
│    3. 执行原有清理逻辑 (peer.close 等)                               │
└──────────────────────────┬──────────────────────────────────────────┘
                           │ ANI Bridge
                           ↓
┌─────────────────────────────────────────────────────────────────────┐
│  C++ ANI Bridge Layer                                               │
│                                                                     │
│  _FireArkUIObjectLifecycleCallback(env, cls,                        │
│       weakRef, className, nodeType, nodePtr):                       │
│    1. 按 className 分发获取 FrameNode：                             │
│       - "FrameNode" → FrameNodePeer::GetFrameNodeByPeer(nodePtr)    │
│       - "RenderNode" → RenderNodePeer(nodePtr)->GetFrameNode()      │
│       - "BuilderNode" → FrameNodePeer::GetFrameNodeByPeer(nodePtr)  │
│         (若失败则尝试 GetMockFrameNodeByPeer，从 mockNode 取 context)│
│    2. frameNode->GetContext() → PipelineContext                     │
│    3. 构造 ArkUIObjectLifecycleData                                 │
│       {weakRef, className, nodeType, nodePtr}                       │
│    4. context->FireArkUIObjectLifecycleCallback(&data)              │
└──────────────────────────┬──────────────────────────────────────────┘
                           │
                           ↓
┌─────────────────────────────────────────────────────────────────────┐
│  C++ PipelineContext Layer                                          │
│                                                                     │
│  FireArkUIObjectLifecycleCallback(data):                            │
│    → objectLifecycleCallback_(data)                                 │
│    → JsLeakWatcher 的 C++ 回调接收通知                              │
└─────────────────────────────────────────────────────────────────────┘
```

### 受影响文件

| 文件 | 变更类型 | 说明 |
|------|----------|------|
| `arkoala-arkts/arkui-ohos/src/ani/arkts/ArkUIAniModule.ts` | 修改 | 声明 `native static _FireArkUIObjectLifecycleCallback` |
| `arkoala-arkts/arkui-ohos/src/ani/native/module.cpp` | 修改 | 注册新 ANI 函数到 staticMethods 数组 |
| `arkoala-arkts/arkui-ohos/src/ani/native/common/common_module.cpp` | 修改 | 实现 ANI 函数 |
| `arkoala-arkts/arkui-ohos/src/ani/native/common/common_module.h` | 修改 | 声明 ANI 函数 |
| `frameworks/core/interfaces/ani/ani_api.h` | 修改 | 新增 fireArkUIObjectLifecycleCallback 函数指针 |
| `frameworks/core/interfaces/native/ani/common_ani_modifier.cpp` | 修改 | 按 className 分发的 FireArkUIObjectLifecycleCallbackImpl |
| `arkoala-arkts/arkui-ohos/src/FrameNode.ets` | 修改 | dispose() 中添加 ANI 函数调用 |
| `arkoala-arkts/arkui-ohos/src/RenderNode.ets` | 修改 | dispose() 中添加 ANI 函数调用 |
| `arkoala-arkts/arkui-ohos/src/BuilderNode.ets` | 修改 | disposeNode() 中添加 ANI 函数调用 |
| `arkoala-arkts/arkui-ohos/src/ComponentContent.ets` | 修改 | dispose() 中添加 ANI 函数调用 |

## 后续 Task 拆分

| Task ID | 目标 | 受影响文件 | 依赖 |
|---------|------|------------|------|
| TASK-1 | 新增 ANI Bridge 函数 `_FireArkUIObjectLifecycleCallback` | ArkUIAniModule.ts, common_module.cpp, common_module.h, module.cpp | design.md + spec.md Approved |
| TASK-2 | 修改 4 个 ETS 节点 dispose()，添加 ANI 函数调用 | FrameNode.ets, RenderNode.ets, BuilderNode.ets, ComponentContent.ets | TASK-1 完成 |
| TASK-3 | 编译验证 + UT | 编译配置 | TASK-2 完成 |

## 风险和开放问题

| 项 | 类型 | 影响 | 处理方式 | Owner |
|----|------|------|----------|-------|
| JsLeakWatcher C++ 回调是否需要适配新数据格式 | 架构 | 中 | JsLeakWatcher 为外部组件，需确认其 C++ 回调是否已支持 `ArkUIObjectLifecycleData` 结构体，或仅依赖 JS 层回调 | sunbees |

## 设计审批

- [x] 需求基线已确认，设计覆盖 P0/P1 AC
- [x] 不涉及项已承接，N/A 和展开项都有结论
- [x] 涉及仓和模块职责清楚
- [x] 适用架构规则已识别并形成设计结论
- [x] 分层和子系统边界合规
- [x] API 变更有签名、权限、错误码和兼容性说明（无 Public API 变更，仅新增 InnerApi `_FireArkUIObjectLifecycleCallback`，签名见 spec.md InnerApi 表）
- [x] 设计输出和后续 Task 拆分明确
- [x] 关键设计决策有理由和影响说明
- [x] 风险和开放问题有 Owner

**结论:** 已通过 (2026-05-22)
