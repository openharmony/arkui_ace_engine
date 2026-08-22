# 样式属性 Context

> 文档版本：v3.1
> 更新时间：2026-07-31
> 来源：`docs/context_registry.json` 主题 `style-attributes`

## 定位

样式属性是所有 ArkUI 组件共享的多态样式与动态属性设置能力，归属 Func-04-03-07。它连接 Common API、前端参数解析、ViewAbstract 属性写入和 StateStyleManager 状态消费。按 Spec 拆分为多态样式（Feat-01）和动态属性设置（Feat-02）两个 Feat 域；hoverEffect 与 clickEffect 由 `04-03-04` 交互属性承接。

本页仅提供路由入口，属性语义、API 版本、边界条件和兼容性应以当前 SDK、源码、测试及 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| NG 公共属性写入 | `frameworks/core/components_ng/base/view_abstract.cpp`、`frameworks/core/components_ng/base/view_abstract_model_ng.cpp` | stateStyles/VisualState 等动态版写入入口 |
| StateStyleManager | `frameworks/core/components_ng/event/state_style_manager.h`、`frameworks/core/components_ng/event/state_style_manager.cpp` | UIState 位掩码、三级优先级链（inner→frontend→user）、状态注册与刷新 |
| VisualState 上下文 | `frameworks/core/components_ng/base/view_stack_processor.h`、`frameworks/core/components_ng/base/view_stack_processor.cpp` | SetVisualState / IsCurrentVisualStateProcess 状态上下文管理 |
| 焦点状态桥接 | `frameworks/core/components_ng/event/focus_hub.h`、`frameworks/core/components_ng/event/focus_hub.cpp` | CheckFocusStateStyle → EventHub::UpdateCurrentUIState(UI_STATE_FOCUSED) |
| ArkTS attributeModifier 桥接 | `frameworks/bridge/declarative_frontend/ark_component/src/ArkComponent.ts` | attributeModifierFunc INIT→initializeModifier / UPDATE→onComponentChanged 生命周期 |
| AttributeUpdater | `frameworks/bridge/declarative_frontend/ark_modifier/src/modifier_utilities.ts` | AttributeUpdater state=INIT/UPDATE + applyAndMergeModifier |
| Dynamic JSView 解析 | `frameworks/bridge/declarative_frontend/jsview/js_view_abstract.cpp` | Common 属性的声明式 JS/ArkTS 动态参数解析入口 |
| ArkTS Common Bridge | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.cpp` | AttributeModifier 和 FrameNode 动态属性解析入口 |
| Common node modifier | `frameworks/core/interfaces/native/node/node_common_modifier.cpp` | Common Bridge 到 ViewAbstract/ModelNG 的 native 属性入口 |
| Static Common modifier | `frameworks/core/interfaces/native/implementation/common_method_modifier.cpp` | Static ArkTS Common 属性的类型转换及 ViewAbstract/Static Model 写入入口 |
| Native 状态注册 | `frameworks/core/interfaces/native/node/node_api.cpp` | SetSupportedUIState / AddSupportedUIState |
| Native 状态桥接 | `frameworks/core/interfaces/native/node/frame_node_modifier.cpp` | OH_ArkUI_AddSupportedUIStates + excludeInner |
| Native 属性分发 | `interfaces/native/node/style_modifier.cpp`、`interfaces/native/native_node.h` | Node C API 通用属性枚举与分发入口 |

按属性族检索：

| 属性族 | 建议检索词 |
|--------|------------|
| 状态样式 | `StateStyleManager`、`VisualState`、`SetVisualState`、`IsCurrentVisualStateProcess`、`UIState`、`supportedStates_` |
| 动态属性修改器 | `attributeModifier`、`AttributeModifier`、`AttributeUpdater`、`applyNormalAttribute`、`applyPressedAttribute`、`excludeInner` |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic Common API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | CommonAttribute 中的 stateStyles 声明 |
| Static Common API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/common.static.d.ets` | 静态 ArkTS Common 属性声明 |
| Dynamic Common Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/CommonModifier.d.ts` | Dynamic Modifier 类型入口 |
| Static Common Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/CommonModifier.static.d.ets` | Static Modifier 类型入口 |
| Node C API | `interfaces/native/native_node.h`、`interfaces/native/native_type.h` | ArkUI_UIState 枚举、OH_ArkUI_AddSupportedUIStates |

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|-----------|-------------------------------|------|
| 窗口焦点上下文 | `frameworks/core/components_ng/event/focus_hub.cpp` | `window_manager` | Subwindow 焦点路由 | 焦点管理与 UIExtension 焦点路由 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|---------|------|
| StateStyleManager 测试 | `test/unittest/core/event/` | 状态注册、刷新、优先级链测试 |
| ViewAbstract 测试 | `test/unittest/core/base/` | 按 `ViewAbstract` 和具体属性名检索公共属性写入测试 |
| Common C modifier 测试 | `test/unittest/capi/modifiers/` | 按 `common_method_modifier` 和具体属性名检索 native modifier 回归 |
| Context registry | `docs/context_registry.json` | `style-attributes` 的 KB、Spec、源码、API 和测试统一路由 |

### 相关 Spec

样式属性功能域：`specs/04-common-capability/03-common-attributes/07-style-attributes/`（功能 ID `04-03-07`）。

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | 多态样式 | `Feat-01-state-effect-spec.md` |
| Feat-02 | 动态属性设置 | `Feat-02-attribute-modifier-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| Pressed 状态在滚动容器中延迟 | `state_style_manager.h` — HandleScrollingParent |
| Pressed 快速抬起后闪烁 | `state_style_manager.h` — HandleTouchUp |
| 触摸移出 Pressed 区域后取消 | `state_style_manager.h` — IsOutOfPressedRegion |
| 快速滚动完全阻止 Pressed 状态 | `state_style_manager.h` — ShouldPreventChildPressedState |
| stateStyles 在 attributeModifier 上下文报错 | `ArkComponent.ts` — stateStyles 与 attributeModifier 互斥；C++ 层两条 subscriber 路径可并存 |
| excludeInner 抑制系统默认 Pressed 效果 | `state_style_manager.h` — IsExcludeInner |
| stateStyles clicked 别名 | `clicked` 映射到 VisualState::PRESSED |
| attributeModifier 6 个 apply 方法 | `ArkComponent.ts` — applyNormalAttribute / applyPressedAttribute / applyFocusedAttribute / applyDisabledAttribute / applySelectedAttribute / applyHoveredAttribute |
| Dynamic 与 Static 行为不一致 | 分别核对 Dynamic JSView/Common Bridge、Static Common modifier/Static Model 和对应 SDK 声明，不从另一范式推断 |
| C API 找不到对应属性 | 在 `native_node.h` 按具体枚举检索；ArkTS Common 属性不保证均有公开 Node C API |

## 调试入口

- 从具体 SDK 属性名定位 Dynamic/Static 声明，再进入对应前端解析入口。
- StateStyleManager 状态可通过 supportedStates_/currentState_ 位掩码 dump 查看。
- attributeModifier 生命周期可通过 modifierState (INIT/UPDATE) 确认。
- 回归优先运行 `test/unittest/core/event/` 和 `test/unittest/capi/modifiers/` 中对应属性用例。

## 相关主题

- [基础属性：[docs/kb/capabilities/basic-attributes.md](basic-attributes.md)](basic-attributes.md)
- [布局属性：[docs/kb/capabilities/layout-attributes.md](layout-attributes.md)](layout-attributes.md)
- [视效属性：[docs/kb/capabilities/visual-effect-attributes.md](visual-effect-attributes.md)](visual-effect-attributes.md)