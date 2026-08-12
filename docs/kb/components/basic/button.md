# Button Context

> 文档版本：v1.1
> 更新时间：2026-07-23
> 来源：`docs/context_registry.json` 主题 `Button`

## 定位

Button 是 ArkUI 基础组件，提供按钮交互能力，支持多种按钮类型（Capsule、Circle、Normal）、点击事件、状态样式（pressed/normal/disabled）等。Button 已完成组件化改造，输出独立 SO `libarkui_button.z.so`，无遗留 JSView 文件。Button 同时作为 ToggleButton 的基类。C API 暴露为 `ARKUI_NODE_BUTTON` 节点类型。

本文档用于快速定位 Button 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Button Pattern | `frameworks/core/components_ng/pattern/button/button_pattern.cpp` | `ButtonPattern`，按钮交互、状态管理、点击事件 |
| Button 布局算法 | `frameworks/core/components_ng/pattern/button/button_layout_algorithm.cpp` | `ButtonLayoutAlgorithm` |
| Button 布局属性 | `frameworks/core/components_ng/pattern/button/button_layout_property.h` | `ButtonLayoutProperty` |
| Button 事件 | `frameworks/core/components_ng/pattern/button/button_event_hub.h` | `ButtonEventHub`，onClick 等事件 |
| Button 请求数据 | `frameworks/core/components_ng/pattern/button/button_request_data.h` | `ButtonRequestData` |
| Button Dynamic Model | `frameworks/core/components_ng/pattern/button/button_model_ng.cpp` | `ButtonModelNG`，动态属性写入、节点创建 |
| Button Static Model | `frameworks/core/components_ng/pattern/button/button_model_static.cpp` | `ButtonModelStatic`，静态前端属性写入 |
| Button Model 实现 | `frameworks/core/components_ng/pattern/button/button_model_impl.cpp` | `ButtonModelImpl` |
| Button 主题 | `frameworks/core/components_ng/pattern/button/button_theme_wrapper.h` | Button Token 适配 |
| ToggleButton Pattern | `frameworks/core/components_ng/pattern/button/toggle_button_pattern.cpp` | `ToggleButtonPattern`，继承 ButtonPattern |
| ToggleButton Model | `frameworks/core/components_ng/pattern/button/toggle_button_model_ng.cpp` | `ToggleButtonModelNG` |
| ToggleButton 静态 Model | `frameworks/core/components_ng/pattern/button/toggle_button_model_static.cpp` | ToggleButton 静态 Model |
| ToggleButton 绘制属性 | `frameworks/core/components_ng/pattern/button/toggle_button_paint_property.h` | `ToggleButtonPaintProperty` |
| ToggleButton 事件 | `frameworks/core/components_ng/pattern/button/toggle_button_event_hub.h` | `ToggleButtonEventHub` |
| ToggleButton 无障碍 | `frameworks/core/components_ng/pattern/button/toggle_button_accessibility_property.cpp` | `ToggleButtonAccessibilityProperty` |
| 组件化 Bridge 目录 | `frameworks/core/components_ng/pattern/button/bridge/` | 组件化后的统一 Bridge / DynamicModule 入口 |
| node_modifier 委托层 | `frameworks/core/interfaces/native/node/node_button_modifier.cpp` | Button C++ 属性委托层 |
| C API 枚举 | `interfaces/native/native_node.h` | `ARKUI_NODE_BUTTON`、`NODE_BUTTON_LABEL`、`NODE_BUTTON_TYPE` 等 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/button.d.ts` | 动态 ArkTS `ButtonInterface`、`ButtonAttribute` 声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/button.static.d.ets` | 静态 ArkTS Button 组件和属性声明 |
| Modifier API (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/ButtonModifier.d.ts` | 动态 Button Modifier 声明 |
| Modifier API (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/ButtonModifier.static.d.ets` | 静态 Modifier 声明 |
| CAPI / NDK | `interfaces/native/native_node.h` | Button C API 节点类型 `ARKUI_NODE_BUTTON` 和属性 `NODE_BUTTON_*` |

API 检索建议：

- 属性声明：在 SDK 文件中搜索 `ButtonAttribute` 和具体属性名。
- 构造参数：在 SDK 文件中搜索 `ButtonInterface`、`ButtonType`、`ButtonOptions`。
- C API：在 `interfaces/native/native_node.h` 中搜索 `NODE_BUTTON_`、`ARKUI_NODE_BUTTON`。

### API 解析实现路径

Button 已完成组件化改造，JSView 文件不存在，Bridge 和动态属性路径统一到 `pattern/button/bridge/`。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 前端 JS/TS 定义 | `frameworks/bridge/declarative_frontend/ark_direct_component/src/arkbutton.ts` | 前端组件类；ArkTS Modifier 类见 `frameworks/bridge/declarative_frontend/ark_modifier/src/button_modifier.ts` |
| 统一 Bridge（声明式 + 动态属性） | `frameworks/core/components_ng/pattern/button/bridge/arkts_native_button_bridge.cpp` | 通过 `IsJsView()` 区分模式，统一参数解析 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/button/bridge/button_dynamic_modifier.cpp` | 动态属性路径；ContentModifier 辅助见 `button_content_modifier_helper.h` |
| Static Modifier | `frameworks/core/components_ng/pattern/button/bridge/button_static_modifier.cpp` | 静态编译路径 |
| Dynamic Module | `frameworks/core/components_ng/pattern/button/bridge/button_dynamic_module.cpp` | `ButtonDynamicModule` 派生类，`libarkui_button.z.so` 入口 |
| node_modifier 委托层 | `frameworks/core/interfaces/native/node/node_button_modifier.cpp` | 通过 `DynamicModuleHelper` 转发到动态模块 |

独立 SO：`libarkui_button.z.so`。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/button/` | Button Pattern、Model、事件、ContentModifier、属性等回归测试 |
| Context registry | `docs/context_registry.json` | Button 的 KB、源码、API、测试统一路由 |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| Button 功能域 | `specs/05-ui-components/04-input-form-components/01-button/` | Button 规格目录 |
| Feat-01 | `specs/05-ui-components/04-input-form-components/01-button/Feat-01-button-full-spec.md` | Button 全量规格 |
| 架构设计 | `specs/05-ui-components/04-input-form-components/01-button/design.md` | Button 架构设计文档 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 按钮不响应点击 | `ButtonPattern` 的 `HandleEnabled()` 和事件注册；`ButtonEventHub` |
| 按钮样式不对 | `ButtonLayoutProperty` 的属性；`ButtonThemeWrapper` Token 映射 |
| 按钮类型错误 | `ButtonType` 枚举（Capsule / Circle / Normal）；`ButtonModelNG::SetType()` |
| ToggleButton 状态不更新 | `ToggleButtonPattern` 的 `OnModifyDone()`；`ToggleButtonPaintProperty` 的 IsOn |
| 无障碍操作无效 | `ToggleButtonAccessibilityProperty` |
| 静态前端属性不生效 | `ButtonModelStatic` 的属性写入；`button_static_modifier.cpp` |

## 调试入口

- 创建链路：从 `ButtonModelNG::Create()` 确认 Button 节点创建和 Pattern 设置。
- 属性链路：从 SDK 属性名定位 Bridge → node_modifier → Model 写入，再看 `ButtonLayoutProperty` 的属性分组。
- 交互链路：从 `ButtonPattern` 的点击事件处理跟踪状态变化。
- 组件化链路：从 `ButtonDynamicModule` 跟踪动态模块加载和属性注册。
- 回归验证：优先运行 `test/unittest/core/pattern/button/` 下的定向用例。

## 相关主题

- Toggle 组件（ToggleButtonPattern 继承 ButtonPattern）
- ArcButton 高级组件（ArkUI 高级按钮组件）
- 组件化改造通用方案
