# Toggle Context

> 文档版本：v1.3
> 更新时间：2026-06-29
> 来源：`docs/context_registry.json` 主题 `Toggle`

## 定位

Toggle 是 ArkUI 的开关/选择组件，通过 `ToggleType` 统一入口提供三种外观形态：Switch（滑块开关）、Checkbox（复选框）、Button（按钮）。三种类型共享同一个 `TOGGLE_ETS_TAG` 节点标签，但分发到完全不同的 Pattern 实现。Toggle 已完成组件化改造，输出独立 SO `libarkui_toggle.z.so`。

本文档用于快速定位 Toggle 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Toggle 统一入口 + Switch 类型 | `frameworks/core/components_ng/pattern/toggle/` | Model 分发、ToggleBasePattern、SwitchPattern 等 |
| Model 抽象接口 | `frameworks/core/components_ng/pattern/toggle/toggle_model.h` | `ToggleModel` 抽象、`ToggleType` 枚举定义 |
| ArkTS Dynamic Model | `frameworks/core/components_ng/pattern/toggle/toggle_model_ng.cpp` | 按 ToggleType 分发创建 Switch/Checkbox/Button FrameNode |
| ArkTS Static Model | `frameworks/core/components_ng/pattern/toggle/toggle_model_static.cpp` | 静态前端 Toggle 属性写入入口 |
| ToggleBasePattern | `frameworks/core/components_ng/pattern/toggle/toggle_base_pattern.cpp` | Switch/Checkbox 共享基类，管理 type 切换时子节点迁移 |
| SwitchPattern 生命周期、交互、动画 | `frameworks/core/components_ng/pattern/toggle/switch_pattern.cpp` | Switch 类型核心行为入口，含拖拽、动画、长按效果 |
| SwitchPattern 类型和接口 | `frameworks/core/components_ng/pattern/toggle/switch_pattern.h` | `SwitchPattern` 类型、状态变量、事件注册接口 |
| Switch 绘制属性 | `frameworks/core/components_ng/pattern/toggle/switch_paint_property.h` | IsOn、SelectedColor、SwitchPointColor、PointRadius、UnselectedColor、TrackBorderRadius 等 |
| Switch 事件 | `frameworks/core/components_ng/pattern/toggle/switch_event_hub.h` | Switch onChange 事件定义 |
| Switch 布局算法 | `frameworks/core/components_ng/pattern/toggle/switch_layout_algorithm.h` | Switch 宽高比约束布局 |
| Switch 绘制方法 | `frameworks/core/components_ng/pattern/toggle/switch_paint_method.h` | Switch 绘制逻辑入口 |
| Switch 渲染修改器（动画） | `frameworks/core/components_ng/pattern/toggle/switch_modifier.h` | 弹簧动画、颜色过渡、Material 效果 |
| Switch 无障碍 | `frameworks/core/components_ng/pattern/toggle/switch_accessibility_property.h` | Switch 无障碍属性 |
| Switch 主题 | `frameworks/core/components_ng/pattern/toggle/switch_theme_wrapper.h` | Switch Token 适配 |
| ToggleButtonPattern | `frameworks/core/components_ng/pattern/button/toggle_button_pattern.cpp` | Button 类型，继承 ButtonPattern，通过 RenderContext 背景色切换 |
| ToggleButton Model | `frameworks/core/components_ng/pattern/button/toggle_button_model_ng.cpp` | Button 类型 Model |
| ToggleButton 绘制属性 | `frameworks/core/components_ng/pattern/button/toggle_button_paint_property.h` | IsOn、SelectedColor、BackgroundColor |
| ToggleButton 事件 | `frameworks/core/components_ng/pattern/button/toggle_button_event_hub.h` | Button onChange 事件定义 |
| ToggleButton 无障碍 | `frameworks/core/components_ng/pattern/button/toggle_button_accessibility_property.h` | Button 无障碍属性 |
| ToggleButton 主题 | `frameworks/core/components_ng/pattern/toggle/toggle_theme_wrapper.h` | Button Token 适配 |
| ToggleCheckBoxPattern | `frameworks/core/components_ng/pattern/checkbox/toggle_checkbox_pattern.h` | Checkbox 类型，继承 CheckBoxPattern 的薄封装 |
| ToggleCheckBox 无障碍 | `frameworks/core/components_ng/pattern/checkbox/toggle_checkbox_accessibility_property.h` | Checkbox 无障碍属性 |
| 组件化 Bridge 目录 | `frameworks/core/components_ng/pattern/toggle/bridge/` | 组件化后的统一 Bridge / DynamicModule 入口 |
| node_modifier | `frameworks/core/interfaces/native/node/node_toggle_modifier.cpp` | C++ 属性 Set/Reset/Get 委托层 |
| C API 枚举 | `interfaces/native/native_node.h` | `NODE_TOGGLE_*` 属性和事件枚举 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/toggle.d.ts` | 动态 ArkTS `ToggleInterface`、`ToggleAttribute`、`ToggleOptions` 声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/toggle.static.d.ets` | 静态 ArkTS Toggle 组件和属性声明 |
| Modifier API (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/ToggleModifier.d.ts` | 动态 Modifier 声明 |
| Modifier API (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/ToggleModifier.static.d.ets` | 静态 Modifier 声明 |
| CAPI / NDK | `interfaces/native/native_node.h` | Toggle C API 属性 `NODE_TOGGLE_*` 和事件枚举 |

API 检索建议：

- 属性声明：在 SDK 文件中搜索 `ToggleAttribute` 和具体属性名。
- 构造参数：在 SDK 文件中搜索 `ToggleInterface`、`ToggleOptions` 或 `Toggle(`。
- ToggleType 枚举：在 SDK 文件中搜索 `ToggleType`。
- SwitchStyle 子属性：在 SDK 文件中搜索 `SwitchStyle`。
- Modifier：在 `ToggleModifier*.d.ts` / `ToggleModifier*.d.ets` 中确认声明。
- C API：在 `interfaces/native/native_node.h` 中搜索 `NODE_TOGGLE_`、`ARKUI_NODE_TOGGLE`。

### API 解析实现路径

Toggle 已完成组件化改造，JSView 文件不存在，Bridge 和动态属性路径统一到 `pattern/toggle/bridge/`。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 前端 JS/TS 定义 | `frameworks/bridge/declarative_frontend/ark_direct_component/src/arktoggle.ts` | 前端组件类，ArkTS Modifier 类见 `frameworks/bridge/declarative_frontend/ark_modifier/src/toggle_modifier.ts` |
| 统一 Bridge（声明式 + 动态属性） | `frameworks/core/components_ng/pattern/toggle/bridge/arkts_native_toggle_bridge.cpp` | 通过 `IsJsView()` 区分模式，统一参数解析；声明见同目录 `.h` |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/toggle/bridge/toggle_dynamic_modifier.cpp` | 动态属性路径；ContentModifier 辅助见 `toggle_content_modifier_helper.h` |
| Static Modifier | `frameworks/core/components_ng/pattern/toggle/bridge/toggle_static_modifier.cpp` | 静态编译路径；扩展访问器见 `toggle_static_extender_accessor.cpp`（均仅非 wearable、非 ArkUI-X 构建） |
| Dynamic Module | `frameworks/core/components_ng/pattern/toggle/bridge/toggle_dynamic_module.cpp` | `ToggleDynamicModule` 派生类，`libarkui_toggle.z.so` 入口；声明见同目录 `.h` |
| node_modifier 委托层 | `frameworks/core/interfaces/native/node/node_toggle_modifier.cpp` | 通过 `DynamicModuleHelper` 转发到动态模块 |

独立 SO：`libarkui_toggle.z.so`。

### 外部依赖入口

外部仓路径以 OpenHarmony 根目录为基准；相对路径列仅记录外部仓内的头文件、目录或 GN 目标。

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 无障碍框架 | `frameworks/core/components_ng/pattern/toggle/switch_accessibility_property.*`、`frameworks/core/components_ng/pattern/button/toggle_button_accessibility_property.*` | `base/accessibility` | `accessibility:accessibility_common` | Switch / Button / Checkbox 无障碍属性上报和操作响应 |
| 图形渲染 Material 效果 | `frameworks/core/components_ng/pattern/toggle/switch_pattern.cpp` | `foundation/graphic/graphic_2d` | `rosen/modules/render_service_client/core/ui_effect/effect/include/brightness_blender.h` | Switch 长按 Material frosted glass 效果所需的亮度混合器 |
| Checkbox 模块（跨组件委托） | `frameworks/core/components_ng/pattern/toggle/toggle_model_ng.cpp` | 同仓 `frameworks/core/interfaces/native/node/node_checkbox_modifier.h` | — | Toggle(type=Checkbox) 通过 `NodeModifier::GetCheckboxCustomModifier()` 委托 Checkbox 模块创建 ToggleCheckBoxPattern |
| UI Session | `frameworks/core/components_ng/pattern/toggle/switch_pattern.cpp` | 同仓 `interfaces/inner_api/ui_session/` | `ui_session:ui_session` | NodeDataCache 记录 isOn 状态（非 SDK 构建） |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/toggle/` | Switch/Button/Checkbox/ContentModifier/Static Model/Material 等 Toggle 行为回归 |
| Context registry | `docs/context_registry.json` | Toggle 的 KB、源码、API、测试统一路由 |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| Toggle 设计文档 | `specs/05-ui-components/04-input-form-components/06-toggle/design.md` | Toggle 架构设计 |
| Toggle 特性规格 | `specs/05-ui-components/04-input-form-components/06-toggle/Feat-01-toggle-spec.md` | Toggle 功能规格定义 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| Toggle 不响应点击 | SwitchPattern 的 `HandleEnabled()` 和事件注册；ToggleButtonPattern 的 `InitEvent()` |
| Switch 动画异常 | `switch_modifier.h` 中的弹簧动画参数；`SwitchPaintProperty` 的 Duration/Curve |
| Button 颜色不对 | `ToggleButtonPaintProperty` 的 SelectedColor/BackgroundColor；`toggle_theme_wrapper.h` Token 映射 |
| ToggleType 运行时切换崩溃或子节点丢失 | `toggle_model_ng.cpp` 的 `ReCreateFrameNode()` 路径；`ToggleBasePattern::GetOrCreateHolderNode()` 子节点迁移 |
| Toggle(Checkbox) vs 独立 Checkbox 行为差异 | ToggleCheckBoxPattern 继承 CheckBoxPattern，使用 `TOGGLE_ETS_TAG` 标签；独立 Checkbox 使用 `CHECKBOX_ETS_TAG` |
| switchPointColor vs switchStyle.pointColor 优先级 | 两者写入同一个 `SwitchPaintProperty::SwitchPointColor`，功能等价 |
| onChange 不触发 | SDK 事件声明、`SwitchEventHub` / `ToggleButtonEventHub`、C API `NODE_TOGGLE_ON_CHANGE` |
| 无障碍操作无效 | `SwitchAccessibilityProperty`、`ToggleButtonAccessibilityProperty`、`ToggleCheckBoxAccessibilityProperty` |

## 调试入口

- 创建链路：从 `ToggleModelNG::CreateFrameNode()` 确认 ToggleType 分发和 Pattern 创建是否正确。
- 属性链路：从 SDK 属性名定位 Bridge → node_modifier → Model 写入，再看 `SwitchPaintProperty` 或 `ToggleButtonPaintProperty` 的属性分组。
- 交互链路：Switch 点击/拖拽问题看 `SwitchPattern::OnClick()`、`HandleDragEnd()`；Button 点击看 `ToggleButtonPattern::OnModifyDone()` 和 `InitEvent()`。
- 动画链路：Switch 弹簧动画和颜色过渡看 `switch_modifier.h`；Material 长按效果看 `SwitchPattern` 中 `dragFrameNode_`、`blurCoverNode_` 相关逻辑。
- 组件化链路：从 `ToggleDynamicModule` 的 `GetDynamicModifier()` / `GetStaticModifier()` 跟踪动态模块加载和属性注册。
- 回归验证：优先运行 `test/unittest/core/pattern/toggle/` 下的定向用例。

## 相关主题

- Checkbox 组件（独立组件，与 Toggle(type=Checkbox) 共享 CheckBoxPattern 基类）
- Button 组件（ToggleButtonPattern 继承 ButtonPattern）
- 组件化改造通用方案
