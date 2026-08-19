# FrameNode Context

> 文档版本：v2.0
> 更新时间：2026-07-29
> 来源：`docs/context_registry.json` 主题 `FrameNode`

## 定位

本主题的主角是 **ArkTS 的 `FrameNode` 类**——通过 `new FrameNode(uiContext)` 创建、对外经 `@ohos.arkui.node` 模块暴露的公开 API 类型。它承载自定义节点的构造分发、状态守卫、引用持有、树/布局/坐标/渲染/事件/动画/生命周期等开发者可感知行为，是 8 个 Feat 规格的规格对象。

ArkTS `FrameNode` 是一层薄包装：它持有对底层 `NG::FrameNode`（C++，`frameworks/core/components_ng/base/`）的强引用，把 ArkTS 侧的 API 调用经 JSI bridge 下沉到 native 修饰器与 NG 核心。**C++ 的 `NG::FrameNode` 只是 ArkTS FrameNode 调用的底层能力提供者，不是本主题的主角**——如需底层度量/布局/渲染实现细节，再深入 C++ 层。

行为事实以 SDK 类型声明（`FrameNode.d.ts` / `FrameNode.static.d.ets`）、ArkTS 实现（`frame_node.ts`）、测试与长期规格为准；本页仅作路由导航，不重复行为矩阵。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| **ArkTS 运行时类（主角）** | `frameworks/bridge/declarative_frontend/ark_node/src/frame_node.ts` | `FrameNode` 类：构造分发（CustomFrameNode/BuilderRootFrameNode/ProxyFrameNode/TypedFrameNode）、`checkType`→100021、`getValidNodePtr`→100026、`isDisposed`、引用持有（`_nativeRef`/`nodePtr_`/`ElementIdToOwningFrameNode_`）、`isTransferred`/`isMinimized` 桩、树操作守卫与 `errorMap_` 错误码映射 |
| 静态前端 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/FrameNode.ets` | Koala 静态前端 `FrameNode`（`@stagemodelonly`，含 `isMinimized` 桩） |
| ArkTS 事件/属性句柄 | `frameworks/bridge/declarative_frontend/ark_node/src/`（`UICommonEvent`/`UIGestureEvent`/`ArkComponent`） | `commonEvent`/`gestureEvent`/`commonAttribute` getter 懒创建的句柄类型；`commonAttribute` 返回 `ArkComponent` 修饰器门面（`@noninterop`） |
| **JSI Bridge（ArkTS→native 边界）** | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_frame_node_bridge.cpp` | FrameNodeBridge ArkTS→native 边界：CreateFrameNode/AppendChild/GetInspectorInfo/CreateAnimation 等；native 返回码映射为 ArkTS BusinessError |
| NDK Modifier（ArkTS 调用的 native 修饰器） | `frameworks/core/interfaces/native/node/frame_node_modifier.cpp` | `ArkUIFrameNodeModifier` 自由函数：`IsModifiable`/`IsOnMainTree`/`GetChild`/`ConvertPoint`/`SetCrossLanguageOptionsFull` 等；ArkTS 调用经此下沉 |
| Extended API（measure/layout 路径） | `frameworks/core/interfaces/native/node/node_api.cpp`、`view_model.cpp` | `ViewModel::MeasureNode`/`LayoutNode`；`SetMeasureWidth`/`SetX` 直写 geometry |
| RenderNode Modifier（adopt 路径） | `frameworks/core/interfaces/native/node/node_render_node_modifier.cpp` | AdoptChild/RemoveAdoptedChild |
| **C++ NG 底层能力（仅作来源）** | `frameworks/core/components_ng/base/frame_node.cpp`、`ui_node.cpp` | `NG::FrameNode : UINode + LayoutWrapper` 提供度量/布局/渲染/树原语/生命周期等底层能力；ArkTS 层调用下沉至此。深入 C++ 实现时再查 |
| 节点注册表 | `frameworks/core/pipeline/base/element_register.h`、`element_register.cpp` | `ElementRegister::MakeUniqueId`（elementId 分配）——ArkTS 构造时经 bridge 调用 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| **SDK 动态（主角）** | `<OH_ROOT>/interface/sdk-js/api/arkui/FrameNode.d.ts` | ArkTS `FrameNode` 类 + `TypedFrameNode` 接口 + `typeNode` 命名空间 + `NodeAdapter` + `LayoutConstraint`/`ExpandMode`/`UIState`/`CrossLanguageOptions`/`InteractionEventBindingInfo` 等 |
| **SDK 静态（主角）** | `<OH_ROOT>/interface/sdk-js/api/arkui/FrameNode.static.d.ets` | 静态 `FrameNode`（`@stagemodelonly`，`@since 23 static`）；`FrameNodeOptions`（staticonly）+ `isMinimized`（staticonly） |
| 模块入口(动态) | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.node.d.ts` | re-export `FrameNode`/`LayoutConstraint`/`ExpandMode`/`UIState`/`ChildrenCountMode`/`typeNode`/`NodeAdapter` |
| 模块入口(静态) | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.node.static.d.ets` | re-export `FrameNode`/`LayoutConstraint`/`ExpandMode`/`CrossLanguageOptions`/`UIState` |

### API 解析实现路径

ArkTS `FrameNode` API 的解析自上而下：ArkTS 类 → JSI bridge → NDK modifier →（下沉）NG 核心。**主轴在 ArkTS 层**，C++ 仅作终端能力。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| **ArkTS 运行时** | `frameworks/bridge/declarative_frontend/ark_node/src/frame_node.ts` | API 行为主轴：构造分发（按 `type` 选 createFrameNode/createTypedFrameNode/createTransFrameNode）、状态守卫（`checkType`→100021、`getValidNodePtr`→100026、`isDisposed`）、引用持有、`errorMap_`（106206/207/208/209/210→100025、106206→100027）、`isTransferred`/`isMinimized` 桩（恒 false） |
| ArkTS → native 边界 | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_frame_node_bridge.cpp` | `FrameNodeBridge::*` 把 ArkTS 调用转 native；返回码映射为 ArkTS BusinessError |
| native 修饰器 | `frameworks/core/interfaces/native/node/frame_node_modifier.cpp` | ArkTS 调用的 native 实现：身份查询/树遍历/坐标转换/跨语言校验 |
| Extended API | `frameworks/core/interfaces/native/node/node_api.cpp`、`view_model.cpp` | measure/layout 走 extended API 直写 geometry |
| C++ NG 终端 | `frameworks/core/components_ng/base/frame_node.cpp` | ArkTS 调用最终下沉到此执行度量/布局/渲染/树/生命周期；**非 ArkTS API 行为规格对象，深入底层时再查** |

**错误码归属**（详见各 Feat 规格风险表）：`100021`(不可改)/`100025`(参数/adopt)/`100026`(disposed，**仅 ArkTS 守卫**，C++ 对 disposed 节点返安全默认)/`100027`(moveTo 已 adopt)/`100028`(不在主树)/`100022`(跨语言)/`100024`(无共同祖先)/`401`(参数)。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 核心单测 | `test/unittest/core/base/frame_node_test_ng.cpp`、`frame_node_test_ng_new.cpp`、`frame_node_test_ng_v3.cpp` | 构造/身份/树/度量/布局/状态 |
| Dump 单测 | `test/unittest/core/base/frame_node_test_ng_dump.cpp` | `getInspectorInfo` JSON |
| 覆盖单测 | `test/unittest/core/base/frame_node_test_ng_coverage*.cpp` | 边界覆盖 |
| 拖拽单测 | `test/unittest/core/base/frame_node_drop_test_ng.cpp` | 拖拽相关 |
| 几何单测 | `test/unittest/core/base/geometry_node_test_ng.cpp` | `GeometryNode` |
| C-API 单测 | `test/unittest/capi/accessors/frame_node_extended_accessor_test.cpp` | `frame_node_modifier` accessor |

### 相关 Spec

| Spec | 路径 | 状态 |
|------|------|------|
| 设计基线 | `specs/04-common-capability/06-custom-node/02-frame-node/design.md` | Baselined（`DESIGN-Func-04-06-02`） |
| Feat-01 节点创建、身份与内省 | `specs/04-common-capability/06-custom-node/02-frame-node/Feat-01-node-creation-identity-introspection-spec.md` | Baselined |
| Feat-02 树结构与挂载管理 | `specs/04-common-capability/06-custom-node/02-frame-node/Feat-02-tree-structure-mounting-spec.md` | Baselined |
| Feat-03 布局与度量 | `specs/04-common-capability/06-custom-node/02-frame-node/Feat-03-layout-measurement-spec.md` | Baselined |
| Feat-04 坐标转换与位置查询 | `specs/04-common-capability/06-custom-node/02-frame-node/Feat-04-position-coordinate-conversion-spec.md` | Baselined |
| Feat-05 渲染上下文与视觉状态 | `specs/04-common-capability/06-custom-node/02-frame-node/Feat-05-render-context-visual-state-spec.md` | Baselined |
| Feat-06 事件交互与 UIState | `specs/04-common-capability/06-custom-node/02-frame-node/Feat-06-event-interaction-ui-state-spec.md` | Baselined |
| Feat-07 节点动画 | `specs/04-common-capability/06-custom-node/02-frame-node/Feat-07-node-animation-spec.md` | Baselined |
| Feat-08 生命周期、回收与跨语言 | `specs/04-common-capability/06-custom-node/02-frame-node/Feat-08-lifecycle-recycle-cross-language-spec.md` | Baselined |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| `getId()` 返回空串/不返回节点类型 | 见 Feat-01 R-5/R-7 |
| `isModifiable()` 为 false 导致 appendChild 等抛 100021 | 见 Feat-01 R-8/R-9、Feat-02 R-9 |
| `dispose()` 后节点未从父移除 | 见 Feat-01 R-21/R-22 |
| `isTransferred()`/`isMinimized()` 恒 false | 见 Feat-01 R-19/R-20（风险项） |
| `getMeasuredSize` 返 px 但 `getPositionToWindow` 返 vp | 见 Feat-03 R-9/R-11、Feat-04 |
| `isAttached()` 行为等同 `isVisible()` | 见 Feat-05 R-7/R-9 |
| `insertChildAfter(child, null)` 抛 100021 但已插首位 | 见 Feat-02 R-11 |
| `moveTo` 源类型不支持时静默 | 见 Feat-02 R-16 |
| `convertPosition` this disposed 误抛 100024 | 见 Feat-04 R-12 |
| `createAnimation` ROTATION 方向相反 | 见 Feat-07 R-2/R-10 |
| `recycle()`/`reuse()` 不入回收池 | 见 Feat-08 R-1/R-3 |
| `setCrossLanguageOptions({attributeSetting:true})` 在 CustomFrameNode 抛 100022 | 见 Feat-08 R-5/R-8 |

## 调试入口

- **Inspector**：`getInspectorInfo()` 返回与 DevEco Studio Inspector 对齐的 JSON（调试用途，高频调用有性能开销）。
- **ArkTS 状态**：`frame_node.ts` 的 `_isDisposed`/`_nativeRef`/`nodePtr_`/`ElementIdToOwningFrameNode_` 为前端层状态来源。
- **错误码常量**：`frameworks/base/error/error_code.h`（`ERROR_CODE_JS_FRAME_NODE_NODE_IS_DISPOSED=100026` 等）。
- **底层几何/脏标记**（深入 C++ 时）：`NG::FrameNode` 的 `isLayoutDirtyMarked_`/`isRenderDirtyMarked_`、`PROPERTY_UPDATE_*` 标志。

## 相关主题

- [Layout Framework](../architecture/layout-framework.md) — ArkTS FrameNode 调用的底层度量布局管线
- [UI Context](./ui-context.md) — `new FrameNode(uiContext)` 所需 `UIContext` 入口
- [Safe Area](./safe-area.md) — 底层 `ProcessSafeAreaPadding`/`OffsetNodeToSafeArea`
- [Layout Attributes](./layout-attributes.md) — `getUserConfig*` 读取的 `LayoutProperty`
- [RenderNode](./render-node.md)、[BuilderNode](./builder-node.md)、[ComponentContent](./component-content.md)、[TypedFrameNode](./typed-frame-node.md) — 同属自定义节点能力簇（已建）
- [渲染树同步](../architecture/render-tree-sync.md) — FrameNode 中渲染树同步机制（RebuildRenderContextTree/ProcessRenderTreeDiff/isPendingState_）
- [同帧下树重新上树 isPendingState_ 状态错乱](../issues/lifecycle/ispending-state-render-tree-diff.md) — isPendingState_ 同帧下树重新上树问题型 KB