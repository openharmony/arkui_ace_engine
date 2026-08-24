# Drag Framework Context

> 文档版本：v1.0
> 更新时间：2026-08-01
> 来源：`docs/context_registry.json` 主题 `DragFramework`

## 定位

拖拽框架是 ArkUI 对系统拖拽会话的内部编排层：负责手势起拖、预拖拽状态、目标命中与生命周期派发、预览/Overlay、数据协作、延迟结束及多窗口适配。系统级拖拽会话通过 `InteractionInterface` 交给平台交互实现；本页用于定位 ArkUI 内部实现，不替代 SDK 与系统服务的行为合同。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|---|---|---|
| 事件入口与系统派发 | `frameworks/core/pipeline_ng/pipeline_context.cpp` | 查找 `OnDragEvent`，定位系统拖拽事件进入 NG 管线的位置。 |
| 管理器与目标路由 | `frameworks/core/components_ng/manager/drag_drop/drag_drop_manager.h`、`frameworks/core/components_ng/manager/drag_drop/drag_drop_manager.cpp` | 命中目标、生命周期派发、数据/结果协作、窗口和预览管理的主入口。 |
| 起拖手势与真实结束回调 | `frameworks/core/components_ng/event/gesture_event_hub_drag.cpp` | 手势侧构建 DragData、调用 `InteractionInterface`，并通过 `GetDragCallback` 回收系统结束结果。 |
| 起拖事件执行器 | `frameworks/core/components_ng/event/drag_event.h`、`frameworks/core/components_ng/event/drag_event.cpp`、`frameworks/core/components_ng/event/drag_drop_event.cpp` | 起拖准备、预览与拖拽事件执行器。 |
| 预拖拽状态机 | `frameworks/core/components_ng/manager/drag_drop/drag_drop_initiating/` | 长按、准备、抬升、移动和取消的内部状态机。 |
| SpringLoading 状态机 | `frameworks/core/components_ng/manager/drag_drop/drag_drop_spring_loading/` | 拖拽停留检测、计时和 BEGIN/UPDATE/END/CANCEL 状态处理；这是延迟/周期回调状态机，不是物理弹簧动画。 |
| 预览动画与内部 Action | `frameworks/core/components_ng/manager/drag_drop/utils/` | 预览动画和内部 DragAction 数据模型。 |
| 全局/系统动作桥接 | `frameworks/core/components_ng/manager/drag_drop/drag_drop_global_controller.*`、`drag_drop_func_wrapper.*`、`drag_drop_controller_func_wrapper.*` | 延迟结束、全局会话状态和程序化起拖的内部桥接。 |

### API 入口

| 范围 | 稳定路径 | 说明 |
|---|---|---|
| ArkTS/C 公共合同 | `docs/kb/capabilities/drag-capability.md` | 拖拽框架不单独定义应用侧签名；从对应通用能力 KB 路由到动态/静态 SDK 和 C header。 |
| 系统交互抽象 | `frameworks/core/common/interaction/interaction_interface.h` | ArkUI 与平台交互实现之间的稳定抽象边界。 |
| 内部代理 | `frameworks/core/components_ng/manager/drag_drop/drag_drop_proxy.h` | 仅用于框架内部模拟/代理路径，不作为系统会话结束的公共合同。 |

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|---|---|---|---|---|
| 系统拖拽服务 | `frameworks/core/common/interaction/interaction_interface.h`、`adapter/ohos/capability/interaction/interaction_impl.cpp`、`interfaces/napi/kits/drag_controller/BUILD.gn` | `base/msdp/device_status` | `interfaces/innerkits/interaction/include/interaction_manager.h`、`i_start_drag_listener.h`、`i_stop_drag_listener.h`、`drag_data.h`；GN 目标 `device_status:devicestatus_client` | ArkUI 通过适配层启动/停止拖拽、控制拖拽窗口并接收结束回调。 |
| 统一数据 | `frameworks/core/common/udmf/`、`frameworks/core/components_ng/manager/drag_drop/`、`adapter/ohos/capability/udmf/udmf_impl.h`、`interfaces/napi/kits/drag_controller/BUILD.gn` | `foundation/distributeddatamgr/udmf` | `interfaces/innerkits/client/udmf_client.h`、`interfaces/innerkits/data/unified_data.h`、`interfaces/innerkits/common/unified_types.h`；GN 目标 `udmf:udmf_client`、`udmf:udmf_data_napi` | 数据摘要、加载和权限协作入口；具体数据会话不在本页定义。 |
| 平台窗口 | `adapter/ohos/capability/BUILD.gn`、`frameworks/core/components_ng/manager/drag_drop/drag_drop_func_wrapper.cpp` | `foundation/window/window_manager` | `interfaces/innerkits/wm/window.h`、`interfaces/innerkits/wm/window_scene.h`、`window_scene/session_manager/include/scene_session_manager.h`；GN 目标 `window_manager:libwindow_extension_client`、`window_manager:scene_session` | 用于拖拽预览子窗口、窗口场景和跨窗口路由。 |
| 图形渲染 | `frameworks/core/components_ng/manager/drag_drop/drag_drop_manager.cpp`、`interfaces/napi/kits/drag_controller/BUILD.gn` | `foundation/graphic/graphic_2d` | `rosen/modules/render_service_client/core/transaction/rs_sync_transaction_controller.h`、`rosen/modules/render_service_client/core/ui/rs_ui_context.h`、`rosen/modules/render_service_client/core/ui/rs_ui_director.h`；GN 目标 `graphic_2d:librender_service_base`、`graphic_2d:librender_service_client` | 用于拖拽预览、Overlay 与 RenderService 同步协作。 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|---|---|---|
| 管理器与状态机 Host 单测 | `test/unittest/core/manager/drag_drop/` | 路由、起拖状态机、SpringLoading、报告与 wrapper 覆盖。 |
| 管理器综合单测 | `test/unittest/core/manager/drag_drop_manager_test_ng.cpp` 及同名前缀文件 | 管理器的通用行为和回归场景。 |
| 事件与手势 Host 单测 | `test/unittest/core/event/drag_event/`、`test/unittest/core/event/drag_event_test_ng.cpp` | 事件执行器、预拖拽及手势路径。 |

### 相关 Spec

| 功能域 | Spec 路径 | 说明 |
|---|---|---|
| 拖拽框架 | `specs/03-engine-framework/04-event-framework/02-drag-framework/` | 内部起拖、路由、数据协作、预览、专用模式与多设备集成的规格集合。 |
| 通用拖拽能力 | `specs/04-common-capability/04-common-events/07-drag-capability/` | 与本框架对应的 ArkTS/C API 公开合同。 |

## 常见问题定位

| 问题 | 优先查看 |
|---|---|
| 系统拖拽事件未到目标回调 | `PipelineContext::OnDragEvent`、`DragDropManager` 及目标 EventHub 路径。 |
| `onDragEnd` 与手势结束时机不一致 | `GestureEventHub::GetDragCallback` 以及 Interaction 适配层；不要把手势 action-end 当作系统拖拽结束。 |
| 起拖前状态或取消行为异常 | `drag_drop_initiating/` 与 `drag_event` 路径。 |
| 预览、Overlay 或落放动画异常 | `drag_event`、`DragDropManager` 和 `utils/drag_animation_helper`。 |
| 悬停响应没有触发或被取消 | `drag_drop_spring_loading/` 与 `DragDropManager` 的 ENTER/MOVE/LEAVE 调用点。 |

## 调试入口

- 使用 `rg -n "OnDragEvent|GetDragCallback|StartDrag" frameworks adapter` 快速定位系统事件、起拖和结束回调边界。
- 使用 `rg -n "DragDropSpringLoading|NotifyDragSpringLoading" frameworks/core/components_ng` 检查悬停检测状态机与 Manager 驱动关系。
- 从 `test/unittest/core/manager/drag_drop/` 选择对应状态机或 Manager 用例，再回溯生产路径。

## 相关主题

- [通用拖拽能力](../capabilities/drag-capability.md)
- [window-mechanism](window-mechanism.md)
- [ui-context](../capabilities/ui-context.md)
- [text](../components/basic/text.md)（仅在排查文本专用拖拽时）