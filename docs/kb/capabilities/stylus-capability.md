# Stylus Capability Context

> 文档版本：v1.0
> 更新时间：2026-07-31
> 来源：`docs/context_registry.json` 主题 `StylusCapability`

## 定位

手写笔能力覆盖 Pen 输入数据、悬停命中与派发、系统手写服务接入及文本编辑命令协同。它横跨 OHOS 输入适配、ArkUI 事件模型、Native 输入事件、Pipeline 命中派发以及 TextField、RichEditor、Web 等消费端。

本文档只提供稳定路由。字段版本、事件支持范围、服务降级、命令行为与组件差异，应以当前 SDK、源码、测试及 `04-04-08` Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| MMI 输入转换 | `adapter/ohos/entrance/mmi_event_convertor.cpp` | Pen 工具类型、压力、倾角、旋转角及坐标转换入口 |
| 核心触摸模型 | `frameworks/core/event/touch_event.h`、`frameworks/core/event/touch_event.cpp` | TouchPoint、TouchEvent 与历史事件数据 |
| NG 触摸事件封装 | `frameworks/core/components_ng/event/touch_event.cpp` | TouchEventInfo 与 TouchLocationInfo 转换入口 |
| 鼠标与悬停事件 | `frameworks/core/event/mouse_event.cpp` | Pen Hover 信息和坐标转换入口 |
| Pen Hover 调度 | `frameworks/core/pipeline_ng/pipeline_context.cpp` | Pen Hover 的 UI Pipeline 入口与调度 |
| Pen Hover 派发 | `frameworks/core/common/event_manager_pen.cpp` | 悬停目标状态、进入退出及移动事件派发 |
| 命中目标收集 | `frameworks/core/components_ng/base/frame_node.cpp`、`frameworks/core/components_ng/event/input_event_hub.cpp` | Pen Hover 命中及回调目标收集 |
| 手写服务装载 | `adapter/ohos/osal/stylus_detector_loader.cpp` | 可选手写服务动态装载和符号解析 |
| 手写服务管理 | `adapter/ohos/osal/stylus_detector_mgr.cpp` | 节点、监听器、当前目标与服务通知管理 |
| 手写命令回调 | `adapter/ohos/osal/stylus_detector_callback.cpp` | 手写编辑命令分派及 UI 任务入口 |
| 手写服务 Inner API | `interfaces/inner_api/ace/stylus/stylus_detector_interface.h` | 服务、监听器与命令接口边界 |
| Native 输入事件 | `interfaces/native/event/ui_input_event.cpp` | Pen 当前值、历史值及克隆事件读写实现 |
| 文本输入协同 | `frameworks/core/components_ng/pattern/text_input/bridge/text_input_dynamic_modifier.cpp` | TextField/Search 手写编辑命令入口 |
| 富文本协同 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_pattern.cpp` | RichEditor 手写编辑和几何操作入口 |
| Web 拦截 | `frameworks/core/components_ng/pattern/web/web_pattern.cpp` | Web 可编辑区域识别与手写触摸拦截 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic ArkTS 事件 | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | SourceTool、压力、倾角、旋转角和悬停事件声明 |
| Static ArkTS 事件 | `<OH_ROOT>/interface/sdk-js/api/arkui/component/common.static.d.ets` | Static ArkTS 输入事件字段与公共事件契约 |
| Native Input Event | `interfaces/native/ui_input_event.h` | Pen 工具类型、压力、倾角、旋转角及历史/克隆事件接口 |
| 手写服务内部接口 | `interfaces/inner_api/ace/stylus/stylus_detector_interface.h` | ArkUI 与系统手写服务的内部协同接口 |

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 外部目标 | 说明 |
|----------|----------|-----------|----------|------|
| 多模输入 | `adapter/ohos/entrance/mmi_event_convertor.cpp` | `<OH_ROOT>/foundation/multimodalinput/input/` | `input:libmmi-client` | 提供 Pen 指针、工具类型和姿态数据 |
| 系统手写服务 | `adapter/ohos/osal/stylus_detector_loader.cpp` | 产品/系统手写服务实现 | `libstylus_innerapi.z.so` | 运行时可选装载，仓内保留默认降级实现 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Pen Hover | `test/unittest/core/event/event_manager_pen_test_ng.cpp` | 悬停状态、差分派发和传播验证 |
| Native Input Event | `test/unittest/interfaces/ace_ui_input_event/` | tool、pressure、tilt、roll 及历史/克隆接口验证 |
| Pipeline 与输入事件 | `test/unittest/core/pipeline/`、`test/unittest/core/event/` | Pen 输入调度、命中和事件封装验证 |
| 文本组件协同 | `test/unittest/core/pattern/text_input/`、`test/unittest/core/pattern/rich_editor/` | 手写编辑命令在文本组件中的集成验证 |

### 相关 Spec

功能域：`specs/04-common-capability/04-common-events/08-stylus-capability/`（功能 ID `04-04-08`）。

| Feat | 稳定路径 | 覆盖范围 |
|------|----------|----------|
| Feat-01 | `Feat-01-stylus-input-event-data-spec.md` | 手写笔输入事件与数据暴露 |
| Feat-02 | `Feat-02-stylus-hover-hit-dispatch-spec.md` | 手写笔悬停命中与事件派发 |
| Feat-03 | `Feat-03-handwriting-service-touch-interception-spec.md` | 手写检测服务接入与触控拦截 |
| Feat-04 | `Feat-04-handwriting-edit-command-text-coordination-spec.md` | 手写编辑命令与文本组件协同 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| Pen 字段在 ArkTS 与 Native 中不一致 | SDK 声明、`mmi_event_convertor.cpp`、`touch_event.cpp` 和 `ui_input_event.cpp` |
| 悬停目标或进入退出事件异常 | `pipeline_context.cpp`、`event_manager_pen.cpp`、`frame_node.cpp` |
| 手写服务未生效或退化 | `stylus_detector_loader.cpp`、`stylus_detector_mgr.cpp` 和 Preview 适配实现 |
| 文本编辑命令未到达目标组件 | `stylus_detector_callback.cpp`、TextInput Modifier、RichEditorPattern |

## 调试入口

- 输入字段检索：`SourceTool`、`PEN`、`pressure`、`tiltX`、`tiltY`、`rollAngle`。
- 悬停链路检索：`OnPenHoverEvent`、`PenHoverTest`、`UpdatePenHoverNode`、`HoverEventTarget`。
- 服务链路检索：`StylusDetectorMgr`、`StylusDetectorLoader`、`Notify`。
- 编辑命令检索：`StylusDetectorCallBack`、`CommandType`、`TextInputClient`。

## 相关主题

- [交互归一化：[docs/kb/capabilities/interaction-normalization.md](interaction-normalization.md)。](interaction-normalization.md)
- [文本交互：[docs/kb/capabilities/text-interaction.md](text-interaction.md)。](text-interaction.md)
- [输入法交互：[docs/kb/capabilities/input-method-interaction.md](input-method-interaction.md)。](input-method-interaction.md)