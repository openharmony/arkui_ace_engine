# 执行计划

## Plan 元数据

| 字段 | 内容 |
|------|------|
| Plan ID | PLAN-20260522-01 |
| 关联 Feature | FEAT-20260521-jsleak-watcher-static-nodes |
| 关联文档 | proposal.md / design.md / spec.md |
| 复杂度 | 标准 |
| 状态 | Approved |
| Owner | sunbees |

## 输入状态

| 输入 | 路径 | 要求状态 |
|------|------|----------|
| Requirement | proposal.md | Approved (Baselined) |
| Design | design.md | Approved |
| Spec | spec.md | Approved |

## AC 到 Task 追溯

| AC | 来源 | Task | 验证方式 | 覆盖 |
|----|------|------|----------|------|
| AC-1.1 FrameNode dispose | spec.md | TASK-2 | UT | 是 |
| AC-1b.1 TypedFrameNode dispose | spec.md | TASK-2 | UT | 是 |
| AC-2.1 RenderNode dispose | spec.md | TASK-2 | UT | 是 |
| AC-3.1 BuilderNode dispose | spec.md | TASK-2 | UT | 是 |
| AC-4.1 ComponentContent dispose | spec.md | TASK-2 | UT | 是 |
| AC-5.1 数据格式一致性 | spec.md | TASK-1 | 对比测试 | 是 |
| AC-6.1 幂等性 | spec.md | TASK-2 | UT | 是 |
| AC-6.2 指针无效跳过 | spec.md | TASK-2 | UT | 是 |
| AC-6.3 无回调安全跳过 | spec.md | TASK-1 | UT | 是 |

## 首批实现边界

**首批必须实现：** ANI Bridge 函数 + 4 个节点 dispose 修改（TASK-1 + TASK-2）
**可后置：** UT 完善（TASK-3）
**不建议延后：** 无

## 阶段计划

| 阶段 | 目标 | 关键 Task | 结束门槛 | 最小验证 |
|------|------|-----------|----------|----------|
| Phase-1 | ANI Bridge 基础设施 | TASK-1 | 函数声明+注册+实现完成 | 编译通过 |
| Phase-2 | ETS 层接入 | TASK-2 | 4 个节点 dispose 添加回调 | 编译通过 |
| Phase-3 | 验证 | TASK-3 | UT 通过 | UT PASS |

## Task 列表

| Task ID | 目标 | 文件范围 | AC 映射 | 前置依赖 | 完成判据 | 验证命令 |
|---------|------|----------|---------|----------|----------|----------|
| TASK-1 | 新增 ANI Bridge 函数 `_FireArkUIObjectLifecycleCallback` | ArkUIAniModule.ts, module.cpp, common_module.cpp, common_module.h | AC-5.1, AC-6.3 | 无 | 函数声明、注册、实现完成，编译通过 | 编译 |
| TASK-2 | 4 个 ETS 节点 dispose() 添加 ANI 函数调用 | FrameNode.ets, RenderNode.ets, BuilderNode.ets, ComponentContent.ets | AC-1.1, AC-1b.1, AC-2.1, AC-3.1, AC-4.1, AC-6.1, AC-6.2 | TASK-1 | 4 个节点 dispose 中添加回调调用，编译通过 | 编译 |
| TASK-3 | 编译验证 + UT | 测试文件 | 全部 AC | TASK-2 | UT 通过 | UT |

## Task 详情

### TASK-1: 新增 ANI Bridge 函数

| 字段 | 内容 |
|------|------|
| 任务目标 | 在 ANI Bridge 层新增 `_FireArkUIObjectLifecycleCallback` 函数，接收 ETS 层传入的 WeakRef、className、nodeType、nodePtr，构造 ArkUIObjectLifecycleData 并调用 PipelineContext::FireArkUIObjectLifecycleCallback |
| AC 映射 | AC-5.1, AC-6.3 |
| 前置依赖 | 无 |
| 非目标 | 不修改 ETS 节点文件，不修改 PipelineContext |
| 完成判据 | 4 个文件修改完成，编译通过 |
| 停止条件 | ANI 函数签名无法匹配现有注册模式 |

**Files**

| 操作 | 文件 | 说明 |
|------|------|------|
| Modify | `arkoala-arkts/arkui-ohos/src/ani/arkts/ArkUIAniModule.ts` | 添加 native static 声明 |
| Modify | `arkoala-arkts/arkui-ohos/src/ani/native/module.cpp` | 注册到 staticMethods 数组 |
| Modify | `arkoala-arkts/arkui-ohos/src/ani/native/common/common_module.h` | 添加 C++ 函数声明 |
| Modify | `arkoala-arkts/arkui-ohos/src/ani/native/common/common_module.cpp` | 添加 C++ 函数实现，通过 modifier 桥接调用 PipelineContext |
| Modify | `frameworks/core/interfaces/ani/ani_api.h` | ArkUIAniCommonModifier 添加 fireArkUIObjectLifecycleCallback 函数指针 |
| Modify | `frameworks/core/interfaces/native/ani/common_ani_modifier.cpp` | 实现 FireArkUIObjectLifecycleCallbackImpl，从 FrameNode 获取 PipelineContext |

**Design Context**

```
ANI Bridge 签名：4 个显式参数（weakRef:WeakRef<object>, className:string, nodeType:string, nodePtr:long），加 ANI 隐式 (env, obj)
函数为静态模块方法，参照 _CheckThreadValid 注册模式
C++ 实现通过 modifier 桥接模式（arkoala_native_ani 不直接链接 ace_engine core）：
  common_module.cpp → GetNodeAniModifier()->getCommonAniModifier()->fireArkUIObjectLifecycleCallback(nodePtr, &data)
  → common_ani_modifier.cpp::FireArkUIObjectLifecycleCallbackImpl
  → frameNode->GetContext() → context->FireArkUIObjectLifecycleCallback(&data)
```

**Handoff Summary**

| 项 | 内容 |
|----|------|
| 允许修改 | ArkUIAniModule.ts, module.cpp, common_module.h, common_module.cpp, ani_api.h, common_ani_modifier.cpp |
| 只读参考 | design.md ADR-1/ADR-2, spec.md InnerApi 表 |
| 验证命令 | 编译通过 |

### TASK-2: 4 个 ETS 节点 dispose 添加回调

| 字段 | 内容 |
|------|------|
| 任务目标 | 在 FrameNode、RenderNode、BuilderNode、ComponentContent 的 dispose() 方法中添加 `_FireArkUIObjectLifecycleCallback` 调用 |
| AC 映射 | AC-1.1, AC-1b.1, AC-2.1, AC-3.1, AC-4.1, AC-6.1, AC-6.2 |
| 前置依赖 | TASK-1（ANI 函数已声明） |
| 非目标 | 不修改 ANI Bridge 层，不修改 PipelineContext |
| 完成判据 | 4 个节点 dispose 中均有回调调用，guard 条件正确，编译通过 |
| 停止条件 | 某个节点类型无 nodePtr 或 peer.ptr 可用 |

**Files**

| 操作 | 文件 | 说明 |
|------|------|------|
| Modify | `arkoala-arkts/arkui-ohos/src/FrameNode.ets` | dispose() 添加回调 |
| Modify | `arkoala-arkts/arkui-ohos/src/RenderNode.ets` | dispose() 添加回调 |
| Modify | `arkoala-arkts/arkui-ohos/src/BuilderNode.ets` | disposeNode() 添加回调 |
| Modify | `arkoala-arkts/arkui-ohos/src/ComponentContent.ets` | dispose() 添加回调 |

**各节点当前 dispose 模式：**

FrameNode (line 534-545):
```typescript
public dispose(): void {
    if (this.isDisposed()) { return; }
    if (this.peer?.ptr) {
        ArkUIAniModule._CheckThreadValid(false, this.peer!.ptr!);
        this.peer?.close();
    }
    this.nodePtr_ = undefined;
    this.renderNode_?.dispose();
    this.isDisposed_ = true;
}
```

RenderNode (line 541-550):
```typescript
dispose() {
    if (this.isDisposed()) { return; }
    this.frameNode_?.deref()?.resetNodePtr()
    if (this.peer?.ptr) {
        this.peer?.close();
    }
    this.isDisposed_ = true;
}
```

BuilderNode (line 676-687):
```typescript
public disposeNode(): void {
    if (this.__isDisposed && this.__rootStage === undefined) { return; }
    ArkUIAniModule._Common_Sync_InstanceId(this._instanceId);
    this.disposeAll();
    this.__frameNode?.disposeNode();
    this.__frameNode = null;
    this.__isDisposed = true;
    ArkUIAniModule._Common_Restore_InstanceId();
    this.__isDisposed = true;
}
```

ComponentContent (line 104-108):
```typescript
dispose(): void {
    this.isDisposed_ = true;
    this.detachFromParent();
    this.builderNode_?.dispose();
}
```

**Design Context**

```
ETS 调用模式（参照 FrameNode）：
  ArkUIAniModule._CheckThreadValid(false, peer.ptr)
  ArkUIAniModule._FireArkUIObjectLifecycleCallback(
    new WeakRef<FrameNode>(this),
    'FrameNode', this.getNodeType(), this.nodePtr_)
  注意：各节点类型获取 nodePtr 的方式不同，需确认每个节点的 nodePtr 来源
  TypedFrameNode 继承 FrameNode.dispose()，getNodeType() 返回具体组件类型
```

**Handoff Summary**

| 项 | 内容 |
|----|------|
| 允许修改 | FrameNode.ets, RenderNode.ets, BuilderNode.ets, ComponentContent.ets |
| 只读参考 | design.md 数据流图, spec.md AC-1.1~AC-4.1, AC-6.1~AC-6.2 |
| 验证命令 | 编译通过 |

### TASK-3: 编译验证 + UT

| 字段 | 内容 |
|------|------|
| 任务目标 | 编译验证 + 编写 UT 断言 PipelineContext::FireArkUIObjectLifecycleCallback 被调用 |
| AC 映射 | 全部 AC |
| 前置依赖 | TASK-2 |
| 非目标 | 不修改业务代码 |
| 完成判据 | 编译通过，UT 通过 |
| 停止条件 | 编译失败需回退修正 TASK-1/TASK-2 |

**Handoff Summary**

| 项 | 内容 |
|----|------|
| 允许修改 | 测试文件 |
| 只读参考 | spec.md 验证映射表 (VM-1~VM-4) |
| 验证命令 | UT PASS |

## Plan 自审清单

- [x] 每个 P0/P1 AC 至少映射到一个 Task
- [x] 每个 Task 文件范围明确
- [x] 每个 Task 明确前置依赖、非目标、完成判据和停止条件
- [x] 每个 Task 有验证命令
- [x] Task 粒度形成能力闭环
- [x] 没有 TBD/TODO/占位符
- [x] 没有要求 Agent 自行寻找未列出的上下文
- [x] 交接信息自包含（Handoff Summary 完整）
- [x] 超 3000 行阈值的 Task 已说明不拆分理由（无需拆分）
