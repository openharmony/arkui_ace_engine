# Drag Capability Context

> 文档版本：v1.0
> 更新时间：2026-07-29
> 来源：`docs/context_registry.json` 主题 `DragCapability`

## 定位

通用拖拽能力是组件面向应用的公开接口集合：包含源/目标配置、生命周期事件、数据与结果、预览、程序化起拖、延迟落放完成及弹簧加载。动态 ArkTS、静态 ArkTS 与 C API 的签名、可空性和版本分别以各自 canonical SDK 或 C header 为准；不要用某一前端的声明代替另一前端。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|---|---|---|
| 通用事件与节点配置存储 | `frameworks/core/components_ng/base/view_abstract.*`、`frameworks/core/components_ng/event/event_hub.*` | CommonMethod 回调、配置和节点 EventHub 保存入口。 |
| 动态 ArkTS 绑定/解析 | `frameworks/bridge/declarative_frontend/jsview/js_view_abstract.cpp` | 通用拖拽属性与事件的动态前端绑定入口。 |
| 动态 NativeModule 桥接 | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.cpp` | 动态 ArkTS 通用属性/事件到原生层的桥接入口。 |
| 程序化 Controller | `interfaces/napi/kits/drag_controller/` | 动态 `DragController` 模块与拖拽预览桥接。 |
| 静态 ArkTS Controller | `frameworks/core/interfaces/native/ani/drag_controller_ani_modifier.*`、`frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/ani/native/dragController/` | 静态 ANI 和 koala 对应入口。 |
| C API 适配 | `interfaces/native/drag_and_drop.h`、`interfaces/native/event/drag_and_drop_impl.cpp`、`frameworks/core/interfaces/native/node/drag_adapter_impl.cpp` | ArkUI C header、事件/API 实现及内部 Action 转换。 |
| 公共能力消费 | `frameworks/core/components_ng/manager/drag_drop/` | 公开配置、事件和 Controller 最终由拖拽框架消费。 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|---|---|---|
| 动态 ArkTS 通用组件 API | `<OH_ROOT>/interface_sdk-js/api/@internal/component/ets/common.d.ts` | 查找 `draggable`、`allowDrop`、drag lifecycle、preview、`onPreDrag` 与 `onDragSpringLoading`。 |
| 静态 ArkTS 通用组件 API | `<OH_ROOT>/interface_sdk-js/api/arkui/component/common.static.d.ets` | 动态接口的静态前端声明；版本与可空性需独立核对。 |
| 动态 ArkTS DragController | `<OH_ROOT>/interface_sdk-js/api/@ohos.arkui.dragController.d.ts`、`<OH_ROOT>/interface_sdk-js/api/@ohos.arkui.UIContext.d.ts` | 程序化 Action、DragController、SpringLoading context 等公开合同。 |
| 静态 ArkTS DragController | `<OH_ROOT>/interface_sdk-js/api/@ohos.arkui.dragController.static.d.ets`、`<OH_ROOT>/interface_sdk-js/api/@ohos.arkui.UIContext.static.d.ets` | 静态 DragController 与 UIContext 合同。 |
| C API | `<OH_ROOT>/interface_sdk_c/arkui/ace_engine/native/drag_and_drop.h` | 节点事件、DragEvent、预览、Action、结果和延迟完成的 NDK 合同。 |

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|---|---|---|---|---|
| 系统拖拽服务 | `frameworks/core/common/interaction/interaction_interface.h`、`adapter/ohos/capability/interaction/` | MSDP DeviceStatus | Interaction 服务接口 | ArkUI 负责 API/交互编排；真实系统拖拽会话经 Interaction 适配层协作。 |
| 统一数据 | `frameworks/core/common/udmf/`、`interfaces/native/event/drag_and_drop_impl.cpp` | UDMF | UnifiedData 相关接口 | ArkTS/C API 的数据、摘要和加载参数与 UDMF 协作。 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|---|---|---|
| C API 测试 | `test/unittest/capi/` 中的 drag-and-drop 相关用例 | 校验 C header 对应的参数、事件、Action 和错误码合同。 |
| 通用属性/事件测试 | `test/unittest/core/event/drag_event/`、`test/unittest/core/event/drag_event_test_ng.cpp` | CommonMethod 事件、预览和预拖拽的底层行为。 |
| Controller 与框架测试 | `test/unittest/core/manager/drag_drop/`、`test/unittest/core/manager/drag_drop_controller_func_wrapper_test_ng.cpp` | Controller/Action 到框架消费路径。 |

### 相关 Spec

| 功能域 | Spec 路径 | 说明 |
|---|---|---|
| 通用拖拽能力 | `specs/04-common-capability/04-common-events/07-drag-capability/` | 源/目标、生命周期、数据、预览、Controller、延迟结束和悬停检测规格。 |
| 拖拽框架 | `specs/03-engine-framework/04-event-framework/02-drag-framework/` | 公共合同所依赖的内部框架机制。 |

## 常见问题定位

| 问题 | 优先查看 |
|---|---|
| 动态/静态 API 签名或版本不一致 | 先分别打开 `common.d.ts`、`common.static.d.ets` 和相应 `dragController` SDK 声明。 |
| C API 参数或错误码问题 | 先读 external canonical `drag_and_drop.h`，再查本仓 `interfaces/native/event/drag_and_drop_impl.cpp`。 |
| `onDragEnd` 的真实触发路径 | 转到拖拽框架 KB 的 `GetDragCallback` 路由；不要以模拟派发路径代替。 |
| SpringLoading C API 查询 | C header 没有此通用能力；从 `onDragSpringLoading` 的动态/静态 ArkTS 声明和框架状态机开始。 |
| Controller/API 调用成功但无系统拖拽 | 检查 DragController 桥接、Action 配置和 `InteractionInterface` 适配边界。 |

## 调试入口

- 用 `rg -n "onDragSpringLoading|onPreDrag|onDrop" <OH_ROOT>/interface_sdk-js/api` 对照公开 ArkTS 合同。
- 用 `rg -n "OH_ArkUI_.*Drag" <OH_ROOT>/interface_sdk_c/arkui/ace_engine/native/drag_and_drop.h` 检索 C API 分组。
- 用 `rg -n "DragController|DragAction" interfaces/api/kits frameworks/core/interfaces/native` 回溯 Controller 桥接与 Action 消费。

## 相关主题

- [拖拽框架](../architecture/drag-framework.md)
- `docs/kb/capabilities/ui-context.md`
- `docs/kb/architecture/window-mechanism.md`
