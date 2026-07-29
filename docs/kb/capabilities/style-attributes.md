# 样式属性 Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `style-attributes`

## 定位

样式属性是所有 ArkUI 组件共享的交互状态效果与动态属性修改能力，归属 Func-04-03-07。覆盖多状态样式（stateStyles — 6 种 UIState: Normal/Pressed/Focused/Disabled/Selected/Hovered）、悬停反馈（hoverEffect — Auto/Scale/Highlight/None，OPACITY 在 NG 管线不生效；部分组件有覆盖行为：Button/ToggleButton 拒绝 BOARD→AUTO，Progress Capsule→SCALE，Progress Linear/Moon→NONE）、点击反馈（clickEffect — ClickEffectLevel LIGHT/MIDDLE/HEAVY，Spring 缩放动画）、动态属性修改器（attributeModifier — 6 个 apply 方法 + INIT/UPDATE 生命周期，与 stateStyles ArkTS 层互斥）。

stateStyles 通过 ViewStackProcessor 双阶段 VisualState 机制实现：先设置状态上下文，属性 setter 通过 IsCurrentVisualStateProcess() 判断生效范围。attributeModifier 使用 AttributeModifier<T> 接口，按状态回调修改属性；C-API 通过 excludeInner 参数可抑制系统默认状态样式。

行为事实来自 SDK 声明、源码实现和测试；本页仅提供路由入口，不重复 Spec 规格内容。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|-------|---------|------|
| 状态效果管线 | `frameworks/core/components_ng/event/state_style_manager.h/cpp` | StateStyleManager 管理 UIState 位掩码、三级优先级链（inner→frontend→user） |
| 悬停效果 | `frameworks/core/components_ng/event/input_event_hub.h/cpp` | hoverEffectType_ / hoverEffectAuto_ 存储，AnimateHoverEffectScale / AnimateHoverEffectBoard 动画 |
| 点击反馈 | `frameworks/core/components_ng/render/render_context.h/cpp` | ClickEffectInfo 存储 propClickEffectLevel_，ClickEffectPlayAnimation spring 缩放动画 |
| VisualState 上下文 | `frameworks/core/components_ng/base/view_stack_processor.h/cpp` | SetVisualState / IsCurrentVisualStateProcess 状态上下文管理 |
| 焦点状态桥接 | `frameworks/core/components_ng/event/focus_hub.h/cpp` | CheckFocusStateStyle → EventHub::UpdateCurrentUIState(UI_STATE_FOCUSED) |
| attributeModifier ArkTS 桥接 | `frameworks/bridge/declarative_frontend/ark_component/src/ArkComponent.ts` | attributeModifierFunc INIT→initializeModifier / UPDATE→onComponentChanged 生命周期 |
| AttributeUpdater | `frameworks/bridge/declarative_frontend/ark_modifier/src/modifier_utilities.ts` | AttributeUpdater state=INIT/UPDATE + applyAndMergeModifier；user 回调存在时 skipFrontendForcibly=true |
| Button/Toggle(Switch) hoverEffect 覆盖 | `button_pattern.cpp`、`toggle_model_ng.cpp` | Button 拒绝 BOARD→转为 AUTO；Toggle(Switch) 拒绝 BOARD→直接跳过（不设置） |
| Progress hoverEffect 覆盖 | `progress_pattern.cpp` | Capsule 强制 SCALE、Linear/Moon 强制 NONE |
| C-API 状态注册 | `frameworks/core/interfaces/native/node/node_api.cpp` | SetSupportedUIState / AddSupportedUIState |
| C-API 状态桥接 | `frameworks/core/interfaces/native/node/frame_node_modifier.cpp` | OH_ArkUI_AddSupportedUIStates + excludeInner |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|---------|------|
| ArkTS 声明式 | `frameworks/bridge/declarative_frontend/jsview/js_view_abstract.cpp` | JsHoverEffect / JsClickEffect / JsVisualState |
| ArkTS attributeModifier | `frameworks/bridge/declarative_frontend/ark_modifier/types/core.d.ts` | AttributeModifier<T> 接口定义 |
| C API 悬停枚举 | `interfaces/native/native_node.h` NODE_HOVER_EFFECT | ArkUI_HoverEffect: AUTO=0/SCALE=1/HIGHLIGHT=2/NONE=3 |
| C API 状态枚举 | `interfaces/native/native_type.h` ArkUI_UIState | NORMAL=0/PRESSED=1/FOCUSED=2/DISABLED=4/SELECTED=8/HOVERED=16 |
| C API 状态注册 | `interfaces/native/native_node.h` | OH_ArkUI_AddSupportedUIStates (@since 20) |
| C API 桥接 | `interfaces/native/node/style_modifier.cpp` | ConvertToHoverEffectType 映射 + SetHoverEffect |

### 接口实现路径总览

| 范式 | 入口文件 | 实例路由守卫 | 说明 |
|------|----------|--------------|------|
| 动态版 | `frameworks/bridge/declarative_frontend/jsview/js_view_abstract.cpp` | `withInstanceId(instanceId_)` | JsHoverEffect/JsClickEffect/JsVisualState；stateStyles 通过 ViewStackProcessor 双阶段 VisualState 机制 |
| 静态版 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/generated/` | `Sync_InstanceId(instanceId_)` + `Restore_InstanceId()` | 静态版属性通过 Arkoala 生成代码调用 ViewAbstract |
| C-API | `interfaces/native/node/style_modifier.cpp` | `ArkUI_ContextHandle.id → ContainerScope` | ConvertToHoverEffectType 映射 + SetHoverEffect；OH_ArkUI_AddSupportedUIStates + excludeInner |
| Kit 层 | `interfaces/inner_api/ace_kit/include/ui/view/ui_context.h` | `PipelineContext::Current()` | Kit 层薄包装 PipelineContext |

**关键前端差异**：

- hoverEffect：动态版通过 JsHoverEffect，C-API HIGHLIGHT 枚举经 converter 映射为内部 BOARD 枚举；Button/ToggleButton 拒绝 BOARD（Button→AUTO，Toggle→跳过）
- stateStyles：动态版通过 ViewStackProcessor VisualState 上下文，静态版通过 Arkoala 生成代码；C-API 通过 OH_ArkUI_AddSupportedUIStates + excludeInner
- attributeModifier：动态版通过 ArkComponent.ts INIT→initializeModifier / UPDATE→onComponentChanged，静态版通过 Arkoala 生成代码

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓 | 说明 |
|----------|----------|--------|------|
| 状态效果渲染 | `frameworks/core/components_ng/render/adapter/rosen_render_context.cpp` | `graphic_2d` | HoverEffect 动画（AnimateHoverEffectScale/Board）和 ClickEffect Spring 缩放动画通过 RSNode + RSModifierNG 下发；UIEffect (BrightnessBlender / FilterRadiusGradientBlurPara / RSMask) 用于模糊与遮罩特效 |
| 窗口焦点上下文 | `frameworks/core/components_ng/event/focus_hub.cpp`（通过 SubwindowManager） | `window_manager` | Subwindow 焦点管理；Window Scene 用于 UIExtension 焦点路由 |
| 状态转换日志 | 多处 `hilog` / `hitrace` 调用 | `hiviewdfx` | 状态切换性能追踪与日志上报 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|---------|------|
| 状态样式单测 | `test/unittest/core/event/` | StateStyleManager 状态注册与刷新 |
| hover 效果单测 | `test/unittest/core/event/` | InputEventHub hover 效果类型 |
| C API 单测 | `test/unittest/ace_engine/C-API-Main/components/` | hoverEffect/clickEffect C-API 测试 |

### 相关 Spec

| Spec | 路径 | 状态 |
|------|------|------|
| Feat-01 状态效果 | `specs/04-common-capability/03-common-attributes/07-style-attributes/Feat-01-state-effect-spec.md` | Baselined |
| Feat-02 动态属性设置 | `specs/04-common-capability/03-common-attributes/07-style-attributes/Feat-02-attribute-modifier-spec.md` | Baselined |
| 样式属性设计文档 | `specs/04-common-capability/03-common-attributes/07-style-attributes/design.md` | Baselined |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| HoverEffectType.OPACITY 在 NG 管线不生效 | `frame_node.cpp` AnimateHoverEffect — 不处理 OPACITY；仅旧管线 RenderBox 实现 |
| Button 设置 BOARD / C-API HIGHLIGHT 不生效 | `button_pattern.cpp` — 拒绝内部枚举 BOARD 转为 AUTO；C-API HIGHLIGHT 经 converter 映射为 BOARD 后同样被拒 → AUTO |
| ToggleButton 同样拒绝 BOARD（直接跳过不设置） | `toggle_model_ng.cpp` — BOARD 时 return，不调用 ViewAbstract::SetHoverEffect |
| Progress Capsule 强制 SCALE、Linear/Moon 强制 NONE | `progress_pattern.cpp` — Capsule→SCALE、Linear/Moon→NONE |
| Pressed 状态在滚动容器中延迟 300ms | `state_style_manager.cpp` HandleScrollingParent → PostPressStyleTask(PRESS_STYLE_DELAY=300ms) |
| Pressed 快速抬起后闪烁 64ms | `state_style_manager.cpp` HandleTouchUp → PostPressCancelStyleTask(64ms) |
| 触摸移出 Pressed 区域后取消 Pressed | `state_style_manager.cpp` IsOutOfPressedRegion → 取消 Pressed 状态 |
| 快速滚动完全阻止 Pressed 状态 | `state_style_manager.cpp` ShouldPreventChildPressedState → 滚动中不触发 Pressed |
| stateStyles 在 attributeModifier 上下文报错 | `ArkComponent.ts` stateStyles → BusinessError(100201)；C++ 层两条 subscriber 路径可并存 |
| excludeInner 抑制系统默认 Pressed 效果 | `state_style_manager.cpp` IsExcludeInner → HandleStateChangeInternal 跳过 inner 回调 |
| clickEffect 与 stateStyles pressed 并存 | clickEffect 存 RenderContext（TransformScale），stateStyles 存 StateStyleManager（属性覆盖），独立生效 |
| attributeModifier 6 个 apply 方法 | applyNormalAttribute / applyPressedAttribute / applyFocusedAttribute / applyDisabledAttribute / applySelectedAttribute / applyHoveredAttribute |
| stateStyles clicked 别名 | `clicked` 参数映射到 VisualState::PRESSED（与 pressed 等价） |
| HoverEffectType 未设置时默认 UNKNOWN=5 | `input_event_hub.h` hoverEffectType_ 默认 UNKNOWN（5），无动画效果 |

## 调试入口

- Hover 效果可通过 EventManager::DispatchMouseHoverAnimationNG → AnimateHoverEffect 调用链追踪
- ClickEffect 动画可通过 ClickEffectPlayAnimation → spring 参数和 scale 目标值验证
- StateStyleManager 状态可通过 supportedStates_/currentState_ 位掩码 dump 查看
- attributeModifier 生命周期可通过 modifierState (INIT/UPDATE) 和 applyModifierPatch 刷新确认

## 相关主题

- [basic-attributes](basic-attributes.md) — 基础属性 (id/visibility/background/overlay/renderGroup)
- [layout-attributes](layout-attributes.md) — 布局属性 (width/height/position 等)
- 动效框架：`docs/kb/capabilities/animation_framework.md` — ClickEffect Spring 缩放动画
- 渲染管线：`docs/kb/architecture/basic-render-pipeline.md` — RS 层动画 (HoverEffect/ClickEffect)
