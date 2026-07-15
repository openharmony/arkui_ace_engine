# Slider Context

> 文档版本：v1.0
> 更新时间：2026-07-13
> 来源：`docs/context_registry.json` 主题 `Slider`

## 定位

Slider 是 ArkUI 的滑动选择输入组件，面向应用侧提供数值范围、步长、横纵方向、反向、轨道/已选区域/滑块视觉、步点、提示气泡、交互模式、触感反馈、自定义内容和无障碍内容等能力。Slider 已完成组件化改造，输出独立 SO `libarkui_slider.z.so`。

本文档用于快速定位 Slider 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Slider Pattern 主体 | `frameworks/core/components_ng/pattern/slider/slider_pattern.cpp` | 生命周期、事件注册、手势处理、提示、自定义内容、无障碍虚拟节点等核心行为入口 |
| Pattern 类型和接口 | `frameworks/core/components_ng/pattern/slider/slider_pattern.h` | `SliderPattern` 状态、手势接口、触感反馈、prefix/suffix、无障碍相关成员 |
| ArkTS Dynamic Model | `frameworks/core/components_ng/pattern/slider/slider_model_ng.cpp` | 动态前端创建、属性写入、资源对象处理和 FrameNode 静态写入入口 |
| ArkTS Static Model | `frameworks/core/components_ng/pattern/slider/slider_model_static.cpp` | 静态前端属性写入入口 |
| Model 抽象 | `frameworks/core/components_ng/pattern/slider/slider_model.h` | `SliderModel` 抽象接口、事件类型、选项结构和枚举定义 |
| 布局算法 | `frameworks/core/components_ng/pattern/slider/slider_layout_algorithm.cpp` | Slider 测量、布局和 prefix/suffix 内容布局入口 |
| 布局属性 | `frameworks/core/components_ng/pattern/slider/slider_layout_property.h` | value/min/max/step/direction/reverse/style/sliderInteractionMode 等布局相关属性 |
| 绘制属性 | `frameworks/core/components_ng/pattern/slider/slider_paint_property.h` | 轨道、已选区域、滑块、步点、提示和触感反馈等绘制属性 |
| 绘制方法 | `frameworks/core/components_ng/pattern/slider/slider_paint_method.cpp` | `SliderContentModifier` / `SliderTipModifier` 的绘制数据装配入口 |
| 内容渲染修改器 | `frameworks/core/components_ng/pattern/slider/slider_content_modifier.cpp` | 轨道、已选区域、滑块、步点和自定义内容绘制 |
| 提示渲染修改器 | `frameworks/core/components_ng/pattern/slider/slider_tip_modifier.cpp` | showTips 提示绘制 |
| 事件中心 | `frameworks/core/components_ng/pattern/slider/slider_event_hub.h` | onChange / value change 事件回调存储和分发 |
| 无障碍属性 | `frameworks/core/components_ng/pattern/slider/slider_accessibility_property.*` | Range、scroll action、extra element info 等无障碍入口 |
| 自定义内容选项 | `frameworks/core/components_ng/pattern/slider/slider_custom_content_options.h` | prefix/suffix 自定义内容无障碍配置结构 |
| Slider 主题 | `frameworks/core/components_ng/pattern/slider/slider_theme_wrapper.h`、`frameworks/core/components/slider/slider_theme.h` | Token / 主题参数入口 |
| 组件化 Bridge 目录 | `frameworks/core/components_ng/pattern/slider/bridge/` | 组件化后的统一 Bridge、DynamicModule、Dynamic/Static Modifier 和自定义内容 Modifier |
| node_modifier 委托层 | `frameworks/core/interfaces/native/node/node_slider_modifier.cpp` | 通过 `DynamicModuleHelper` 获取 Slider 动态模块并暴露动态/CJ modifier |
| Peer / Accessor | `frameworks/core/interfaces/native/implementation/slider_modifier.cpp`、`slider_extender_accessor.cpp`、`slider_ops_accessor.cpp` | 静态 ArkTS / Peer 层对 Slider modifier、prefix/suffix accessor、value callback 的入口 |
| C API 枚举 | `interfaces/native/native_node.h` | `ARKUI_NODE_SLIDER`、`NODE_SLIDER_*` 属性和事件枚举 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/slider.d.ts` | 动态 ArkTS `SliderInterface`、`SliderAttribute`、`SliderOptions`、事件和扩展选项声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/slider.static.d.ets` | 静态 ArkTS Slider 组件、属性、配置和回调声明 |
| Modifier API (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/SliderModifier.d.ts` | 动态 Modifier 声明 |
| Modifier API (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/SliderModifier.static.d.ets` | 静态 Modifier 声明 |
| CAPI / NDK | `interfaces/native/native_node.h` | `ARKUI_NODE_SLIDER`、`NODE_SLIDER_*`、`NODE_SLIDER_EVENT_ON_CHANGE` 等节点属性和事件枚举 |

API 检索建议：

- 构造参数：在 SDK 文件中搜索 `SliderInterface`、`SliderOptions` 或 `Slider(`。
- 属性声明：在 SDK 文件中搜索 `SliderAttribute` 和具体属性名，如 `trackColor`、`selectedColor`、`showSteps`、`showTips`、`trackThickness`、`blockStyle`、`sliderInteractionMode`。
- 枚举和结构：搜索 `SliderStyle`、`SliderChangeMode`、`SliderInteraction`、`SliderBlockStyle`、`SliderConfiguration`。
- 自定义内容：搜索 `contentModifier`、`prefix`、`suffix`、`SliderPrefixOptions`、`SliderSuffixOptions`。
- 触感反馈：搜索 `enableHapticFeedback`、`digitalCrownSensitivity`。
- Modifier：在 `SliderModifier*.d.ts` / `SliderModifier*.d.ets` 中确认声明。
- C API：在 `interfaces/native/native_node.h` 中搜索 `ARKUI_NODE_SLIDER`、`NODE_SLIDER_`。

### API 解析实现路径

Slider 已完成组件化改造，JSView 文件不存在，Bridge 和动态属性路径统一到 `pattern/slider/bridge/`。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 前端 JS/TS 定义 | `frameworks/bridge/declarative_frontend/ark_component/components/arkslider.js` | 前端组件类；ArkTS Modifier 类见 `frameworks/bridge/declarative_frontend/ark_modifier/src/slider_modifier.ts` |
| 统一 Bridge（声明式 + 动态属性） | `frameworks/core/components_ng/pattern/slider/bridge/arkts_native_slider_bridge.cpp` | 注册 Slider 属性并解析声明式 / 动态属性参数 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/slider/bridge/slider_dynamic_modifier.cpp` | 动态属性路径，写入 `SliderModelNG`；同时提供 CJ modifier 入口 |
| Static Modifier | `frameworks/core/components_ng/pattern/slider/bridge/slider_static_modifier.cpp` | 静态编译路径，写入 `SliderModelNG` / `SliderModelStatic` |
| Dynamic Module | `frameworks/core/components_ng/pattern/slider/bridge/slider_dynamic_module.cpp` | `SliderDynamicModule` 派生类，`libarkui_slider.z.so` 入口 |
| Model Impl | `frameworks/core/components_ng/pattern/slider/bridge/slider_model_impl.cpp` | 组件化模块内的 Model 实现入口，服务旧调用或 CJ 路径 |
| 自定义内容 Modifier | `frameworks/core/components_ng/pattern/slider/bridge/slider_custom_modifier.cpp`、`slider_content_modifier_helper.h` | contentModifier / prefix / suffix 等自定义内容和静态内容 accessor |
| node_modifier 委托层 | `frameworks/core/interfaces/native/node/node_slider_modifier.cpp` | 通过 `DynamicModuleHelper` 转发到 Slider 动态模块 |
| Peer / Accessor 委托层 | `frameworks/core/interfaces/native/implementation/slider_modifier.cpp`、`slider_extender_accessor.cpp`、`slider_ops_accessor.cpp` | 静态 ArkTS Peer / extender / ops accessor 通过动态模块获取实现 |

独立 SO：`libarkui_slider.z.so`。组件化改造参考：`./组件化重构通用方案.md`。

### 外部依赖入口

外部仓路径以 OpenHarmony 根目录为基准。以下依赖通过 `BUILD.gn`、`#include` 或源码调用在 Slider 当前实现中确认。

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 无障碍框架 | `frameworks/core/components_ng/pattern/slider/slider_accessibility_property.*`、`slider_pattern.cpp` | `base/accessibility` | `accessibility:accessibility_common` | Slider Range、scroll action、prefix/suffix 虚拟节点和无障碍回调 |
| NAPI 桥接 | `frameworks/core/components_ng/pattern/slider/bridge/arkts_native_slider_bridge.cpp` | `foundation/arkui/napi` | `napi:ace_napi` | 组件化 Bridge 使用 NAPI / ArkTS runtime 类型进行参数解析 |
| UI Session | `frameworks/core/components_ng/pattern/slider/slider_pattern.cpp` | 本仓 `interfaces/inner_api/ui_session/` | `ui_session:ui_session` | 非 SDK 构建下记录和上报 UI 会话状态 |
| 触感反馈适配 | `frameworks/core/components_ng/pattern/slider/slider_pattern.cpp` → `frameworks/core/common/vibrator/vibrator_utils.h` | `base/sensors/miscdevice` | `interfaces/native/innerkits/vibrator_agent.h` | Slider 滑动和数字表冠相关触感反馈最终由 OHOS 适配层调用振动能力 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/slider/` | Pattern、Model、布局、绘制、Modifier、自定义内容、Material 和静态 Model 等行为回归 |
| C API Modifier 测试 | `test/unittest/capi/modifiers/slider_modifier_test.cpp`、`test/unittest/capi/modifiers/generated/` | Slider C API / generated modifier 回归 |
| C API Accessor 测试 | `test/unittest/capi/accessors/slider_content_modifier_accessor_test.cpp` | Slider content modifier accessor 回归 |
| 组件示例测试 | `test/component_test/test_cases/components/button_and_selection/entry/src/main/ets/pages/slider/` | ArkTS 示例和组件集成场景 |
| Context registry | `docs/context_registry.json` | Slider 的 KB、Spec、源码、API、测试统一路由 |

### 相关 Spec

Slider 功能域：`specs/05-ui-components/04-input-form-components/05-slider/`

| Feat | 主题 | 文件 |
|------|------|------|
| Design | 架构设计 | `design.md` |
| Feat-01 | 创建、数值范围与布局样式 | `Feat-01-slider-creation-range-layout-spec.md` |
| Feat-02 | 轨道、滑块与步点视觉 | `Feat-02-slider-track-block-step-visual-spec.md` |
| Feat-03 | 交互模式、事件与反馈 | `Feat-03-slider-interaction-events-feedback-spec.md` |
| Feat-04 | 提示、自定义内容与无障碍内容 | `Feat-04-slider-tips-custom-accessibility-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| Slider 创建后 value/min/max/step 不符合预期 | SDK `SliderOptions` 声明、`slider_model_ng.cpp` 创建和属性规范化入口、Feat-01 |
| 横纵向、reverse、style 布局异常 | `slider_layout_property.h`、`slider_layout_algorithm.cpp`、`slider_pattern.cpp` 中方向和坐标换算逻辑 |
| 轨道、已选区域、滑块或步点颜色异常 | `slider_paint_property.h`、`slider_content_modifier.cpp`、Bridge 中 `trackColor` / `selectedColor` / `blockColor` / `stepColor` 解析 |
| showSteps / stepSize 不生效 | SDK `showSteps` / `stepSize` 声明、`SliderModelNG::SetShowSteps`、`slider_content_modifier.cpp` 步点绘制 |
| showTips 内容或位置异常 | SDK `showTips` 声明、`slider_pattern.cpp` 提示节点逻辑、`slider_tip_modifier.cpp` |
| onChange 模式或触发时机异常 | SDK `SliderChangeMode`、`slider_event_hub.h`、`slider_pattern.cpp` 手势处理和事件分发 |
| sliderInteractionMode 不符合预期 | SDK `SliderInteraction`、Bridge `SetInteractionMode`、`slider_pattern.cpp` 点击/拖拽处理 |
| enableHapticFeedback 或 digitalCrownSensitivity 不生效 | SDK 声明、`slider_pattern.cpp` 触感反馈调用、`adapter/ohos/entrance/vibrator/vibrator_utils.cpp` |
| prefix / suffix 自定义内容不显示或无障碍不对 | SDK `prefix` / `suffix` 选项、`slider_model_ng.cpp`、`slider_pattern.cpp` 自定义内容和虚拟节点逻辑 |
| contentModifier 绘制异常 | SDK `SliderConfiguration`、`slider_custom_modifier.*`、`slider_content_modifier_helper.h` |
| C API 设置不生效 | `interfaces/native/native_node.h` 中 `NODE_SLIDER_*`、`node_slider_modifier.cpp` 动态模块委托、CAPI 单测 |

## 调试入口

- 创建链路：从 `SliderModelNG::Create()` 或 `SliderModelNG::CreateFrameNode()` 确认 FrameNode、Pattern、EventHub 和属性初始写入。
- 属性链路：从 SDK 属性名定位 `arkts_native_slider_bridge.cpp` → `slider_dynamic_modifier.cpp` / `slider_static_modifier.cpp` → `SliderModelNG` / `SliderModelStatic`。
- 组件化链路：从 `DynamicModuleHelper` 的 `Slider` 注册项跟踪 `SliderDynamicModule::GetDynamicModifier()` / `GetStaticModifier()` / `GetCustomModifier()`。
- 交互链路：点击、触摸和拖拽问题看 `SliderPattern::InitClickEvent()`、`InitTouchEvent()`、`InitPanEvent()` 及对应处理函数。
- 绘制链路：轨道、滑块、步点问题看 `SliderPaintMethod` 装配和 `SliderContentModifier` 绘制；提示问题看 `SliderTipModifier`。
- 无障碍链路：Range 和滚动操作看 `SliderAccessibilityProperty`；prefix/suffix 虚拟节点看 `SliderPattern` 中自定义内容无障碍逻辑。
- 回归验证：优先运行 `test/unittest/core/pattern/slider/` 下的定向用例；C API 修改补充运行 `test/unittest/capi/modifiers/` 和 `test/unittest/capi/accessors/` 中 Slider 相关用例。

## 相关主题

- Toggle 组件：`docs/kb/components/selector/toggle.md`
- Text 组件：`docs/kb/components/basic/text.md`
- Image 组件：`docs/kb/components/media/image.md`
- 组件化重构通用方案：`./组件化重构通用方案.md`
