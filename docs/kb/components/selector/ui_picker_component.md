# UIPickerComponent Context

> 文档版本：v1.0
> 更新时间：2026-07-11
> 来源：`docs/context_registry.json` 主题 `UIPickerComponent`

## 定位

UIPickerComponent 是 ArkUI 的 UI 选择容器组件，SDK 名称为 `UIPickerComponent`，ace_engine 内部实现主要使用 `ContainerPicker` 命名。本文档只作为 UIPickerComponent / ContainerPicker 相关源码、SDK 声明、C API、测试和 Spec 的快速路由；具体行为、默认值、边界处理和兼容性以 SDK 声明、源码实现、测试用例和 Spec 为准。

当前实现未发现 `ContainerPicker` / `UIPickerComponent` 的独立动态模块表项，也没有 `frameworks/core/components_ng/pattern/container_picker/bridge/` 目录。声明式 JSView 入口仍在 `js_container_picker.cpp`，动态属性走 `arkts_native_container_picker_bridge.cpp` → `node_container_picker_modifier.cpp` → `ContainerPickerModel`。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern 主目录 | `frameworks/core/components_ng/pattern/container_picker/` | ContainerPicker Pattern、Model、布局、绘制、无障碍和主题实现集中目录 |
| Pattern | `frameworks/core/components_ng/pattern/container_picker/container_picker_pattern.cpp` | 滚动、选中、触觉反馈、无障碍和事件协调入口 |
| Model | `frameworks/core/components_ng/pattern/container_picker/container_picker_model.cpp` | 动态前端和 node_modifier 写入 Model 的入口 |
| Static Model | `frameworks/core/components_ng/pattern/container_picker/container_picker_model_static.cpp` | 静态前端属性写入入口 |
| 布局算法 | `frameworks/core/components_ng/pattern/container_picker/container_picker_layout_algorithm.cpp` | 容器选择器布局测量入口 |
| LayoutProperty | `frameworks/core/components_ng/pattern/container_picker/container_picker_layout_property.h` | selectedIndex、canLoop、indicator、displayedItemCount、itemHeight 等布局属性 |
| 工具类 | `frameworks/core/components_ng/pattern/container_picker/container_picker_utils.h` | 展示项数量、itemHeight 等参数归一化辅助 |
| 事件定义 | `frameworks/core/components_ng/pattern/container_picker/container_picker_event_hub.h` | onChange/onScrollStop 事件挂接 |
| JSView 声明式入口 | `frameworks/bridge/declarative_frontend/jsview/js_container_picker.cpp` | 对外声明 `UIPickerComponent`，解析声明式 API |
| ArkTS nativeModule Bridge | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_container_picker_bridge.cpp` | 动态属性参数解析入口 |
| nativeModule 注册 | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_impl_bridge.cpp` | 注册 ContainerPicker native module 属性函数 |
| node_modifier | `frameworks/core/interfaces/native/node/node_container_picker_modifier.cpp` | C++ 属性 Set/Reset/Get 委托层 |
| C API style modifier | `interfaces/native/node/style_modifier.cpp` | `ARKUI_NODE_PICKER` 属性 Set/Get/Reset 分发 |
| C API option 辅助 | `interfaces/native/node/container_picker_option.cpp` | Picker indicator style 相关原生结构处理 |
| C API 枚举 | `interfaces/native/native_node.h` | `ARKUI_NODE_PICKER`、`NODE_PICKER_*`、`NODE_PICKER_EVENT_*` |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/ui_picker_component.d.ts` | `UIPickerComponentInterface`、`UIPickerComponentAttribute`、`UIPickerComponentOptions` 声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/uiPickerComponent.static.d.ets` | 静态 ArkTS UIPickerComponent 组件、Options 和 Attribute 声明 |
| Modifier API (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/UIPickerComponentModifier.d.ts` | 动态 Modifier 声明 |
| Modifier API (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/UIPickerComponentModifier.static.d.ets` | 静态 Modifier 声明 |
| CAPI / NDK | `interfaces/native/native_node.h` | C API 使用 `ARKUI_NODE_PICKER` 与 `NODE_PICKER_*` |
| Picker 通用结构 | `interfaces/native/node_attributes/picker.h` | `ArkUI_PickerIndicatorStyle` 等通用结构 |

API 检索建议：

- 构造参数：搜索 `UIPickerComponentInterface`、`UIPickerComponentOptions`、`UIPickerComponent(`。
- 属性声明：搜索 `UIPickerComponentAttribute` 和具体属性名。
- 运行时实现：搜索 `JSContainerPicker`、`ContainerPickerBridge`、`ContainerPickerModel`。
- C API：搜索 `ARKUI_NODE_PICKER`、`NODE_PICKER_`、`ArkUI_PickerIndicatorStyle`。

### API 解析实现路径

UIPickerComponent 当前未完成独立组件化改造：未在 `adapter/ohos/osal/dynamic_module_helper.cpp` 中发现 `UIPickerComponent` / `ContainerPicker` 动态模块表项，`pattern/container_picker/bridge/` 目录也不存在。实际解析路径仍分为 JSView、nativeModule Bridge 和 C API style_modifier。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| JSView（声明式组件） | `frameworks/bridge/declarative_frontend/jsview/js_container_picker.cpp` | `JSContainerPicker::JSBind()` 声明 `UIPickerComponent`，组件属性调用 `ContainerPickerModel` |
| ArkTS Bridge（动态属性） | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_container_picker_bridge.cpp` | 动态属性参数解析，调用 `getContainerPickerModifier()` |
| nativeModule 注册 | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_impl_bridge.cpp` | 注册 `containerPicker` 对象上的 set/reset 函数 |
| node_modifier 层 | `frameworks/core/interfaces/native/node/node_container_picker_modifier.cpp` | C++ Set/Reset/Get，Bridge 和 C API 共用 |
| C API（NDK） | `interfaces/native/node/style_modifier.cpp` | `ARKUI_NODE_PICKER` 属性分发到 ContainerPicker modifier |
| 节点创建 | `frameworks/core/interfaces/native/node/view_model.cpp` | C API `ARKUI_NODE_PICKER` 创建 ContainerPicker FrameNode |
| option 辅助 | `interfaces/native/node/container_picker_option.cpp` | Indicator style 结构校验和字段转换 |

组件化改造参考：`./组件化重构通用方案.md`。改造后预期会收敛到 `pattern/container_picker/bridge/` 和独立动态模块路径；当前 KB 只记录已验证的现状。

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 触觉反馈 | `frameworks/core/components_ng/pattern/container_picker/container_picker_pattern.cpp` | `foundation/multimedia/player_framework` | `audio_haptic` | 通过 `PickerAudioHapticFactory` 获取音频触觉控制器 |
| 触觉适配 | `adapter/ohos/entrance/picker/`、`adapter/ohos/entrance/vibrator/` | `base/sensors/miscdevice` | `vibrator_interface_native` | 平台侧触觉和 vibrator 适配 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Pattern 单元测试 | `test/unittest/core/pattern/container_picker/` | ContainerPicker 模型、布局、绘制、事件、资源、主题和无障碍回归 |
| Native node C API 测试 | `test/unittest/interfaces/native_node_two_part_test.cpp` | `ARKUI_NODE_PICKER` 属性 Set/Get/Reset 回归 |
| Native node 事件测试 | `test/unittest/interfaces/native_node_test.cpp` | `NODE_PICKER_EVENT_*` 事件转换回归 |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| Picker 设计文档 | `specs/05-ui-components/05-picker-components/06-picker/design.md` | Spec 仓库存在时的设计入口 |
| UIPickerComponent 特性规格 | `specs/05-ui-components/05-picker-components/06-picker/Feat-01-uipicker-component-full-spec.md` | UIPickerComponent 功能规格定义 |
| 本仓规格目录 | `specs/05-ui-components/05-picker-components/06-picker/` | 当前工作区规格目录 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| SDK 名称和源码目录对不上 | SDK 搜 `UIPickerComponent`，ace_engine 实现搜 `ContainerPicker` / `JSContainerPicker` |
| 组件创建失败或属性不生效 | `js_container_picker.cpp`、`arkts_native_container_picker_bridge.cpp`、`node_container_picker_modifier.cpp` |
| C API 属性不生效 | `interfaces/native/native_node.h`、`interfaces/native/node/style_modifier.cpp`、`view_model.cpp` |
| indicator 样式异常 | `container_picker_option.cpp`、`container_picker_utils.h`、`container_picker_layout_property.h` |
| 滚动、吸附或选中异常 | `container_picker_pattern.cpp`、`container_picker_layout_algorithm.cpp` |
| 触觉反馈异常 | `container_picker_pattern.cpp`、`adapter/ohos/entrance/picker/` |

## 调试入口

- 命名链路：SDK 和前端入口使用 `UIPickerComponent`；C++ Pattern、Model、Modifier 使用 `ContainerPicker`。
- 创建链路：声明式看 `JSContainerPicker::Create()`；C API 看 `view_model.cpp` 中 `ARKUI_NODE_PICKER` 创建路径。
- 属性链路：声明式 JSView 属性从 `js_container_picker.cpp` 到 `ContainerPickerModel`；动态属性从 `arkts_native_container_picker_bridge.cpp` 到 `node_container_picker_modifier.cpp`。
- C API 链路：从 `NODE_PICKER_*` 枚举定位 `style_modifier.cpp`，再跟到 `getContainerPickerModifier()`。
- 回归验证：优先运行 `test/unittest/core/pattern/container_picker/`，C API 属性问题看 `test/unittest/interfaces/native_node_two_part_test.cpp`。

## 相关主题

- TextPicker Context
- DatePicker Context
- TimePicker Context
- CalendarPicker Context
- 组件化改造通用方案
