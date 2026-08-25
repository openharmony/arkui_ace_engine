# BuilderNode Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `BuilderNode`

## 定位

本主题的主角是 **ArkTS 的 `BuilderNode` 类**——通过 `new BuilderNode(uiContext, options?)` 创建、对外经 `@ohos.arkui.node` 模块暴露的自定义叶子节点。它承载组件树构建（build/update）、FrameNode 访问、渲染类型/纹理、复用回收、输入事件分发、冻结策略、响应式变体（ReactiveBuilderNode），是功能域 `04-06-04` 的规格对象。

BuilderNode 持有不可改根节点 `BuilderRootFrameNode`（appendChild 等抛 100021）与底层强引用，build 经 `JSBuilderNode`/`BaseNode` 下沉到 native。**C++ 仅为底层能力提供者**。BuilderNode 仅可用作叶子节点；@Link 不可跨边界；@Reusable 抛 100030。

行为事实以 SDK（`BuilderNode.d.ts`/`.static.d.ets`）、ArkTS 实现（`builder_node.ts`）、测试与长期规格为准；本页仅作路由导航。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| **ArkTS 运行时类（主角）** | `frameworks/bridge/declarative_frontend/ark_node/src/builder_node.ts` | `BuilderNode`/`BuilderNodeCommonBase`/`JSBuilderNode`/`ReactiveBuilderNode`：build/update/dispose/reuse/recycle/事件分发；instanceId 同步；nesting Proxy（写抛 140109） |
| 不可改根节点 | `frameworks/bridge/declarative_frontend/ark_node/src/frame_node.ts` | `BuilderRootFrameNode extends ImmutableFrameNode`：appendChild 等抛 100021 |
| 共享基类 | `frameworks/bridge/declarative_frontend/ark_node/src/base_node.ts` | `BaseNode`：create/createReactive、强引用生命周期 |
| GC 终结注册 | `frameworks/bridge/declarative_frontend/ark_node/src/node_finalization_register_proxy.ts` | `BuilderNodeFinalizationRegisterProxy`：GC 触发后端节点回收 |
| **JSI Bridge（ArkTS→native 边界）** | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_frame_node_bridge.cpp` | 折叠实现：AddBuilderNode/RemoveBuilderNode/ClearBuilderNode/TriggerOnReuse/TriggerOnRecycle/UpdateConfiguration/事件分发 |
| NDK accessor | `frameworks/core/interfaces/native/implementation/builder_node_ops_accessor.cpp` | 静态/Arkoala 侧 accessor：construct/create/dispose/setOptions/postEvent |
| **C++ NG 底层（仅作来源）** | `frameworks/core/common/builder_util.h` | 根 builder 节点工具（IsBuilderRootNode/IsBuilderContainer）。深入时再查 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| **SDK 动态（主角）** | `<OH_ROOT>/interface/sdk-js/api/arkui/BuilderNode.d.ts` | `BuilderNode<Args>` 类 + `ReactiveBuilderNode` + `RenderOptions`/`BuildOptions`/`NodeRenderType`/`InputEventType` |
| **SDK 静态（主角）** | `<OH_ROOT>/interface/sdk-js/api/arkui/BuilderNode.static.d.ets` | 静态 `BuilderNode<T>`（`@stagemodelonly`，`@since 23 static`）；BuildOptions/RenderOptions 字段与动态不同 |
| 模块入口(动态) | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.node.d.ts` | re-export `BuilderNode`/`ReactiveBuilderNode`/`NodeRenderType`/`RenderOptions`/`BuildOptions`/`InputEventType` |
| 模块入口(静态) | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.node.static.d.ets` | re-export 静态 BuilderNode |

### API 解析实现路径

ArkTS `BuilderNode` API 解析自上而下：ArkTS 类 → JSI bridge/accessor → NG。**主轴在 ArkTS 层**。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| **ArkTS 运行时** | `frameworks/bridge/declarative_frontend/ark_node/src/builder_node.ts` | API 行为主轴：build 按值传递+nesting Proxy（写抛 140109）、update 冻结暂存、dispose 幂等、reuse/recycle（@Reusable 抛 100030）、事件分发坐标转换 |
| 不可改根 | `frameworks/bridge/declarative_frontend/ark_node/src/frame_node.ts` | `BuilderRootFrameNode` 树操作抛 100021 |
| ArkTS → native 边界 | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_frame_node_bridge.cpp` | 折叠实现 builder 生命周期 + 事件分发 |
| native accessor | `frameworks/core/interfaces/native/implementation/builder_node_ops_accessor.cpp` | 静态/Arkoala 侧 |
| C++ NG 终端 | `frameworks/core/common/builder_util.h` | 下沉到底层；**非规格对象，深入时再查** |

**错误码**：100021（不可改根树操作）、100030（@Reusable）、140109（nesting Proxy 写）、401（参数）。详见各 Feat 规格风险表。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 工具单测 | `test/unittest/core/common/builder_util/builder_util_test.cpp` | IsBuilderRootNode/IsBuilderContainer |
| NodeContainer 单测 | `test/unittest/core/pattern/node_container/node_container_test_ng.cpp` | 根 builder 节点挂载场景 |

> 注：无独立 builder_node ArkTS 单测；行为间接经 node_container/builder_util 覆盖。

### 相关 Spec

| Spec | 路径 | 状态 |
|------|------|------|
| 设计基线 | `specs/04-common-capability/06-custom-node/04-builder-node/design.md` | Baselined（`DESIGN-Func-04-06-04`） |
| Feat-01 创建、释放与渲染类型 | `specs/04-common-capability/06-custom-node/04-builder-node/Feat-01-creation-dispose-render-type-spec.md` | Baselined |
| Feat-02 构建与更新 | `specs/04-common-capability/06-custom-node/04-builder-node/Feat-02-build-update-spec.md` | Baselined |
| Feat-03 FrameNode 访问 | `specs/04-common-capability/06-custom-node/04-builder-node/Feat-03-framenode-access-spec.md` | Baselined |
| Feat-04 渲染类型与纹理 | `specs/04-common-capability/06-custom-node/04-builder-node/Feat-04-render-type-texture-spec.md` | Baselined |
| Feat-05 复用与回收 | `specs/04-common-capability/06-custom-node/04-builder-node/Feat-05-reuse-recycle-spec.md` | Baselined |
| Feat-06 输入事件分发 | `specs/04-common-capability/06-custom-node/04-builder-node/Feat-06-input-event-dispatch-spec.md` | Baselined |
| Feat-07 冻结策略 | `specs/04-common-capability/06-custom-node/04-builder-node/Feat-07-freeze-policy-spec.md` | Baselined |
| Feat-08 响应式变体 | `specs/04-common-capability/06-custom-node/04-builder-node/Feat-08-reactive-variant-spec.md` | Baselined |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| getFrameNode() 返回节点树操作抛 100021 | BuilderRootFrameNode 不可改。见 Feat-03 R-4 |
| @Reusable 抛 100030 | builder 内自定义组件不支持 @Reusable。见 Feat-05 R-5 |
| 嵌入 RenderNode 时尺寸 [0,0] | selfIdealSize 须显式设置。见 Feat-01 R-3 |
| build 后状态不更新 | @Builder 无状态，须显式 update()。见 Feat-02 R-6 |
| nesting 写参数抛 140109 | nestingBuilderSupported 时 params 包 Proxy。见 Feat-02 R-2 |
| dispose 后崩溃 | SDK NOTE 警告。见 Feat-01 R-6 |
| postTouchEvent 同 timestamp 无效 | 仅第一次有效。见 Feat-06 R-2 |
| 动态/静态 BuildOptions 字段不同 | useParallel 仅静态，enableProvideConsumeCrossing 仅动态。见 Feat-02 风险项 |
| V1 参数不更新 | V1(@Observed) 须 flushState()，V2(@ObservedV2) 自动。见 Feat-08 R-3/R-4 |

## 调试入口

- **不可改根**：`BuilderRootFrameNode` 树操作抛 100021（设计约束，非 bug）。
- **GC 回收**：`BuilderNodeFinalizationRegisterProxy` 在 GC 时触发后端节点回收。
- **isDisposed**：dispose 后查询有效性。

## 相关主题

- [FrameNode](./frame_node.md) — `getFrameNode()` 返回的不可改根；BuilderNode 挂载到其他 FrameNode
- [RenderNode](./render_node.md) — 可嵌入 BuilderNode 的绘制节点
- NodeAdapter（`04-06-06`）、ComponentContent（`04-06-05`）、TypedFrameNode（`04-06-07`）— 同属自定义节点能力簇（KB 待建）
