# NodeContainer Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `NodeContainer`

## 定位

`NodeContainer`（FuncID `05-16-01`）是自定义占位组件之一，作为命令式节点的渲染宿主。它将声明式树与命令式（imperative）节点桥接：纯 TS `NodeController.makeNode(uiContext)` 返回 `FrameNode`，经 `nodePtr_` 跨界指针挂入 `NodeContainerNode`（FrameNode 子类）。`NodeController` 为纯 TS 抽象类，C++ 对其不透明。

关键边界：仅命令式节点（`IsArkTsFrameNode` 或 `GetIsRootBuilderNode`）可挂入；`NodeContainerNode` 的 `OnRecycle`/`OnReuse` 覆写**不调基类**（base node 生命周期由命令式侧管理）。`NodeContainer` 不支持跨实例复用。具体行为、默认值以对应 SDK 声明、源码实现、测试和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| NG Pattern（渲染宿主） | `frameworks/core/components_ng/pattern/node_container/node_container_pattern.cpp`、`.h` | `RemakeNode` / `AddBaseNode` / `CleanChild` / `FireMakeFunction` / `CheckBeforeAddNode` 守卫 / `OnResize` / 纹理导出 |
| NG Model 工厂 | `frameworks/core/components_ng/pattern/node_container/node_container_model_ng.cpp`、`node_container_model.h` | `Create`（默认 TOP_LEFT）/ `SetMakeFunction` / `FireMakeNode` / `CreateFrameNode` |
| EventHub | `frameworks/core/components_ng/pattern/node_container/node_container_event_hub.cpp`、`.h` | aboutTo* / onAttach / Detach / bind 系列回调存储与 Fire |
| Layout | `frameworks/core/components_ng/pattern/node_container/node_container_layout_algorithm.cpp`、`.h` | extends StackLayoutAlgorithm；`MeasureContent` 返 nullopt |
| Node（FrameNode 子类） | `frameworks/core/components_ng/pattern/node_container/node_container_node.cpp`、`.h` | tag `NODE_CONTAINER_ETS_TAG`；复用 OnRecycle/OnReuse（不调基类） |
| TS NodeController | `frameworks/bridge/declarative_frontend/ark_node/src/node_controller.ts` | 纯 TS 抽象类：`__makeNode__` / `rebuild()` |
| JS 桥接 | `frameworks/bridge/declarative_frontend/jsview/js_node_container.cpp` | `JSNodeContainer`：Create / SetNodeController / nodePtr_ `reinterpret_cast` 跨界 |
| Native bridge | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_node_container_bridge.cpp` | `nodeContainer` native 对象：Rebuild / Clean |
| C-API Modifier | `frameworks/core/interfaces/native/node/node_container_modifier.cpp` | rebuild / clean vtable（ArkUINodeContainerModifier + CJUINodeContainerModifier） |
| C-API 生成 accessor | `frameworks/core/interfaces/native/implementation/node_container_ops_accessor.cpp` | Arkoala / 生成 C-API |
| UINode 守卫 | `frameworks/core/components_ng/base/ui_node.h` | `IsArkTsFrameNode` / `GetIsRootBuilderNode`（边界准入） |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic SDK | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/node_container.d.ts`、`<OH_ROOT>/interface/sdk-js/api/arkui/NodeController.d.ts` | `NodeContainer(controller)` `@since11`；`makeNode` `@since11`、回调 `@since18` |
| Static SDK | `<OH_ROOT>/interface/sdk-js/api/arkui/component/nodeContainer.static.d.ets`、`NodeController.static.d.ets` | `@since23` 整套，`@since26 staticonly` style-builder |
| CAPI / NDK | `frameworks/core/interfaces/native/node/node_container_modifier.cpp` | rebuild / clean 入口 |
| re-export | `@ohos.arkui.node(.static)` / `@kit.ArkUI` | Kit：ArkUI；SysCap：`SystemCapability.ArkUI.ArkUI.Full`；无权限 |

API 检索建议：在 SDK 中搜索 `NodeContainer`、`NodeController`、`makeNode`、`rebuild`、`aboutToResize`、`onWillBind`。

### API 解析实现路径

NodeContainer **尚未进行组件化改造**，属性解析为多路径架构（声明式 JSView + native bridge + C-API Modifier），编译产物在主 `libace_compatible.z.so` 中。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| **TS NodeController** | `frameworks/bridge/declarative_frontend/ark_node/src/node_controller.ts` | `__makeNode__` 调 `makeNode` + 暂存 FrameNode；`rebuild()` 调 native |
| **JSView（声明式组件）** | `frameworks/bridge/declarative_frontend/jsview/js_node_container.cpp` | `JSNodeContainer::Create` / `SetNodeController`；读 `nodePtr_` `reinterpret_cast<NG::UINode*>` 跨界 |
| **ArkTS Native Bridge** | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_node_container_bridge.cpp` | `nodeContainer` native 对象：Rebuild / Clean |
| **node_modifier 委托层** | `frameworks/core/interfaces/native/node/node_container_modifier.cpp` | rebuild / clean 经 `ElementRegister` → `NodeContainerPattern` |
| **C-API 生成 accessor** | `frameworks/core/interfaces/native/implementation/node_container_ops_accessor.cpp` | Arkoala / 生成 C-API 入口 |


### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|-----------|------------------------------|------|
| 纹理导出（embed node surface sharing） | `node_container_pattern.cpp`（`HandleTextureExport` / `SetExportTextureInfoIfNeeded`）、`rosen_render_context.*` | `foundation/graphic/graphic_2d` | `rosen/.../RSSurfaceNode::SetTextureExport`、`RSTextureExport` | 子节点 `IsNeedExportTexture` 时经 `surfaceId_` 键入 ElementRegister，Rosen 做 surface sharing，供 accessibility 跨 surface 遍历 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| UT | `test/unittest/core/pattern/node_container/` | Pattern RemakeNode / AddBaseNode / 守卫、Layout、rebuild/Clean、NodeAdapter |
| XTS | `test/xts` | dynamic/static 端到端 makeNode |
| Spec 功能域 | `specs/05-ui-components/16-custom-placeholder-components/01-node-container/` | 设计与验收契约 |
| Spec 总索引 | `specs/index.md` | `05-16-01` 功能域注册入口 |

### 相关 Spec

NodeContainer 功能域：

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | NodeContainer 渲染宿主与 FrameNode 桥接（基线） | `Feat-01-node-container-render-host-and-framenode-bridge-spec.md` |
| Feat-02 | NodeController 生命周期回调 | `Feat-02-nodecontroller-lifecycle-callbacks-spec.md` |
| Feat-03 | 复用与纹理导出 | `Feat-03-reuse-and-texture-export-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| makeNode 返回节点不挂入 | `node_container_pattern.cpp` `CheckBeforeAddNode`（须 `IsArkTsFrameNode` 或 `GetIsRootBuilderNode`），返回声明式节点仅警告不崩 |
| rebuild 不生效 | `node_controller.ts`（`_value<0` 未绑定时静默不派发） |
| 回调时机异常 | `node_container_event_hub.*`（`aboutToAppear` 异步、其余同步）；`aboutToResize` 存于 Pattern `resizeFunc_`（非 EventHub） |
| bind/unbind 与 appear/detach 混淆 | 两轴独立（身份绑定 vs 主树可见性），详见 Spec Feat-02 |
| 复用时子节点 OnRecycle 未触发 | `node_container_node.cpp` OnRecycle/OnReuse 不调基类（不递归子） |
| 纹理导出不生效 | `node_container_pattern.cpp` `HandleTextureExport`（after-layout 驱动、防嵌套） |

## 调试入口

- 创建链路：`JSNodeContainer::Create` → Model `FireMakeNode` → Pattern `RemakeNode` → `AddBaseNode`（守卫）。
- 跨界桥接：`nodePtr_` `reinterpret_cast<NG::UINode*>` + `AceType::Claim`，依赖 `IsArkTsFrameNode` 守卫兜底类型安全。
- rebuild 链路：`controller.rebuild()` → native modifier → Pattern `RemakeNode`（复用初始渲染路径）。
- 复用链路：`NodeContainerNode` OnRecycle/OnReuse 不调基类，复用单元为 FrameNode（非 controller）。

## 相关主题

- [ContentSlot：[docs/kb/components/custom-node/content-slot.md](content-slot.md)](content-slot.md)
- [NodeAdapter：[docs/kb/capabilities/node-adapter.md](../../capabilities/node-adapter.md)](../../capabilities/node-adapter.md)
- [组件复用框架：[docs/kb/architecture/component-reuse-framework.md](../../architecture/component-reuse-framework.md)](../../architecture/component-reuse-framework.md)
- 占位组件概念入口：[docs/kb/capabilities/placeholder-component.md](../../capabilities/placeholder-component.md)