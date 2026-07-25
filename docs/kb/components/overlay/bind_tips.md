# bindTips Context

> 文档版本：v1.0
> 更新时间：2026-07-14
> 来源：`docs/context_registry.json` 主题 `bindTips`

## 定位

bindTips 是 ArkUI 弹窗类属性，通过 `bindTips(message, options)` 通用属性方法为任意组件绑定提示气泡。bindTips 复用 `BubblePattern`（气泡模式），通过 `IsTips` 标志区分提示气泡和普通气泡，提供长按/悬停触发、跟随目标/光标定位、双边框、文本截断等 tips 专属能力。bindTips 没有独立的 Pattern 目录，不暴露为 C API 节点类型或 modifier。显示/隐藏生命周期由 `OverlayManager::ShowTips()` / `HideTips()` 统一管理。

本文档用于快速定位 bindTips 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Bubble Pattern（Tips 核心） | `frameworks/core/components_ng/pattern/bubble/bubble_pattern.cpp` | `BubblePattern`，`IsTips` / `isTips_` 标志、`SetIsTipsAppearing` / `IsTipsAppearing`、`PopBubble(tips)` |
| Bubble 布局算法（Tips 布局） | `frameworks/core/components_ng/pattern/bubble/bubble_layout_algorithm.cpp` | `MeasureTipsRegion`、`MeasureTipsFollowTarget`、`CalculateTipsDirections`、`ResetTipsMaxLines`，`TIPS_MARGIN_SPACE` / `MAX_TIP_WIDTH` / `TIPS_MOUSE_SPACE` 常量 |
| Bubble 布局属性（Tips 属性） | `frameworks/core/components_ng/pattern/bubble/bubble_layout_property.h` | `IsTips`、`ShowAtAnchor`（`TipsAnchorType`） |
| Bubble 渲染属性（Tips 渲染） | `frameworks/core/components_ng/pattern/bubble/bubble_render_property.h` | `IsTips`、`ShowAtAnchor` |
| Bubble 绘制方法（Tips 绘制） | `frameworks/core/components_ng/pattern/bubble/bubble_paint_method.cpp` | `isTips_`、`GetTipsPadding`、`GetTipsDoubleBorderEnable`、`GetTipsOuterBorderWidth` / `GetTipsInnerBorderColor` |
| Bubble 视图（Tips 设置） | `frameworks/core/components_ng/pattern/bubble/bubble_view.cpp` | `UpdateIsTips`、`SetTipsTag` |
| Tips 锚点类型 | `frameworks/core/components/common/properties/tips_anchor_type.h` | `TipsAnchorType` 枚举（TARGET、CURSOR） |
| Overlay 管理器（Tips 生命周期） | `frameworks/core/components_ng/pattern/overlay/overlay_manager.cpp` | `ShowTips()` / `ShowTipsInSubwindow()` / `HideTips()`，`tipsInfoList_` / `tipsStatusList_` / `tipsEnterAndLeaveInfoMap_` 管理 |
| Overlay 管理器头文件 | `frameworks/core/components_ng/pattern/overlay/overlay_manager.h` | `PopupInfo::isTips`、Tips 相关方法声明 |
| ViewAbstract 核心（dispatch） | `frameworks/core/components_ng/base/view_abstract.cpp` | `ViewAbstract::BindTips()`，`targetNode->SetBindTips(true)` |
| ViewAbstract Model 接口 | `frameworks/core/components_ng/base/view_abstract_model.h` | `BindTips()` 纯虚接口 |
| ViewAbstract Model NG | `frameworks/core/components_ng/base/view_abstract_model_ng.cpp` | NG 路径 `BindTips()` |
| ViewAbstract Model Static | `frameworks/core/components_ng/base/view_abstract_model_static.h` | 静态路径 `BindTips()` |
| ViewAbstract 多线程 | `frameworks/core/components_ng/base/view_abstract_multithread.cpp` | `BindTipsMultiThread()` |
| FrameNode 标志 | `frameworks/core/components_ng/base/frame_node.cpp` | `hasBindTips_`、`SetBindTips()` |
| 手势事件注册 | `frameworks/core/components_ng/event/gesture_event_hub.cpp` | bindTips 注册 hover/press 手势回调 |
| JSView 桥接 | `frameworks/bridge/declarative_frontend/jsview/js_popups.cpp` | `JSViewAbstract::JsBindTips()`，解析 `TipsMessageType` / `TipsOptions` → `PopupParam` + `SpanString` |
| JSView 注册 | `frameworks/bridge/declarative_frontend/jsview/js_view_abstract.cpp` | `bindTips` 静态方法注册 |
| Model 实现 | `frameworks/bridge/declarative_frontend/jsview/models/view_abstract_model_impl.cpp` | `ViewAbstractModelImpl::BindTips()`，构建 `tipsComponent` |
| 组件化 Bridge 目录 | `frameworks/core/components_ng/pattern/bubble/bridge/` | Bubble 组件化 Bridge（Tips 共用） |
| Inner Modifier | `frameworks/core/components_ng/pattern/bubble/bridge/inner_modifier/bubble_inner_modifier.cpp` | `setIsTipsAppearing` 回调注册 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API (属性) | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | `bindTips(message, options)` 属性声明；`TipsMessageType`、`TipsOptions` 类型 |
| Static API (arkoala) | `frameworks/bridge/arkts_frontend/koala_projects/inner_api/arkui/component/common.d.ets` | 静态前端 `bindTipsAttribute` 声明 |
| CAPI / NDK | 无 | bindTips 未暴露 C API |

API 检索建议：

- 属性声明：在 `common.d.ts` 中搜索 `bindTips`、`TipsMessageType`、`TipsOptions`、`TipsAnchorType`。
- 调用链路：`js_popups.cpp::JsBindTips` → `ViewAbstractModel::BindTips()` → `ViewAbstract::BindTips()` → `OverlayManager::ShowTips()`。

### API 解析实现路径

bindTips 复用 Bubble Pattern，无独立 Pattern 目录和 Bridge。通过 `IsTips` 标志在 Bubble 的布局、绘制、事件中切换 tips 专属逻辑。bindTips 属性通过通用属性桥接（`js_popups.cpp` → `ViewAbstractModel`）触发。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| JSView（声明式属性） | `frameworks/bridge/declarative_frontend/jsview/js_popups.cpp` | `JsBindTips()` 解析参数 → `ViewAbstractModel::BindTips()` |
| Model 实现 | `frameworks/bridge/declarative_frontend/jsview/models/view_abstract_model_impl.cpp` | `ViewAbstractModelImpl::BindTips()` 构建 tips 组件 |
| NG Model | `frameworks/core/components_ng/base/view_abstract_model_ng.cpp` | NG 路径，调用 `ViewAbstract::BindTips()` |
| 静态 Model | `frameworks/core/components_ng/base/view_abstract_model_static.h` | 静态路径 |
| 核心 dispatch | `frameworks/core/components_ng/base/view_abstract.cpp` | `ViewAbstract::BindTips()`，设置 `SetBindTips(true)` 并注册手势回调 |
| 多线程 dispatch | `frameworks/core/components_ng/base/view_abstract_multithread.cpp` | `BindTipsMultiThread()` |
| Overlay 生命周期 | `frameworks/core/components_ng/pattern/overlay/overlay_manager.cpp` | `ShowTips()` / `HideTips()` 创建和管理 tips 节点 |
| Bubble 节点 | `frameworks/core/components_ng/pattern/bubble/bubble_view.cpp` | `UpdateIsTips()` 设置 Bubble 为 tips 模式 |
| 统一 Bridge（动态模块） | `frameworks/core/components_ng/pattern/bubble/bridge/bubble_dynamic_module.cpp` | `BubbleDynamicModule` 派生类，`libarkui_bubble.z.so` 入口（Tips 共用） |
| Inner Modifier | `frameworks/core/components_ng/pattern/bubble/bridge/inner_modifier/bubble_inner_modifier.cpp` | `setIsTipsAppearing` 回调 |
| 静态 ArkTS 前端 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/generated/component/common.ets` | 静态生成 `bindTips` 属性 |
| 静态 Modifier | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/generated/CommonMethodModifier.ets` | 静态 Modifier `setBindTipsAttribute` |

独立 SO：`libarkui_bubble.z.so`（与 bindPopup 共用）。

### 外部依赖入口

外部仓路径以 OpenHarmony 根目录为基准；相对路径列仅记录外部仓内的头文件、目录或 GN 目标。

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 窗口子系统 | `frameworks/core/components_ng/pattern/bubble/bubble_pattern.cpp` | `window_manager` | `interfaces/innerkits/wm/window_manager.h` | tips 子窗口创建与管理（`SubwindowType::TYPE_TIPS`） |
| 图形渲染 | `frameworks/core/components_ng/pattern/bubble/bubble_paint_method.cpp` | `foundation/graphic/graphic_2d` | `rosen/modules/render_service_base/include/` | RSNode / RSCanvas 绘制 tips 背景、双边框、圆角、阴影 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/bubble/bubble_tips_test_ng.cpp` | Tips 专属回归（`MeasureTipsRegion`、`ResetTipsMaxLines`、`CalculateTipsDirections`、Cursor/Arrow 模式） |
| 单元测试 | `test/unittest/core/pattern/bubble/bubble_test_two_ng.cpp` | Bubble 通用测试（含 `isTips_` 场景） |
| Context registry | `docs/context_registry.json` | bindTips 的 KB、源码、API、测试统一路由 |

### 相关 Spec

bindTips 未在 `specs/registry/functions.yaml` 中独立注册，归属于弹窗类属性功能域。

| Spec | 路径 | 说明 |
|------|------|------|
| 弹窗类属性功能域 | `specs/04-common-capability/03-common-attributes/05-popup-attributes/` | 通用弹窗属性规格目录（待创建） |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| Tips 不显示 | `ViewAbstract::BindTips()` 的 `SetBindTips(true)` 和手势回调注册；`OverlayManager::ShowTips()` |
| Tips 位置/方向错误 | `BubbleLayoutAlgorithm::MeasureTipsRegion()` / `MeasureTipsFollowTarget()` / `CalculateTipsDirections()` |
| Tips 边框/间距不对 | `BubblePaintMethod::GetTipsPadding()` / `GetTipsDoubleBorderEnable()` / `GetTipsOuterBorderWidth()` |
| Tips 文本截断异常 | `BubbleLayoutAlgorithm::ResetTipsMaxLines()` / `MAX_TIP_WIDTH` |
| Cursor 模式不跟随 | `TipsAnchorType::CURSOR` 相关逻辑；`TIPS_MOUSE_SPACE` 常量 |
| Tips 不消失 | `OverlayManager::HideTips()` / `EraseTipsInfo()`；`BubblePattern::PopBubble(tips)` |
| 子窗口 Tips 不生效 | `OverlayManager::ShowTipsInSubwindow()` / `SubwindowManager::HideTipsNG` / `SubwindowType::TYPE_TIPS` |
| 手势触发异常 | `gesture_event_hub.cpp` 中 bindTips 的 hover/press 回调注册 |

## 调试入口

- 调用链路：从 `js_popups.cpp::JsBindTips()` → `ViewAbstractModelImpl::BindTips()` → `ViewAbstract::BindTips()` → `OverlayManager::ShowTips()`。
- 布局链路：从 `BubbleLayoutAlgorithm::MeasureTipsRegion()` / `MeasureTipsFollowTarget()` 跟踪 tips 位置、方向和文本截断。
- 绘制链路：从 `BubblePaintMethod` 的 `isTips_` 分支跟踪 tips 间距和双边框。
- 生命周期链路：从 `OverlayManager::ShowTips()` / `HideTips()` 跟踪 tips 状态机和 `tipsInfoList_` 管理。
- 子窗口链路：从 `ShowTipsInSubwindow()` 跟踪子窗口 tips 模式。
- 回归验证：优先运行 `test/unittest/core/pattern/bubble/bubble_tips_test_ng.cpp`。

## 相关主题

- bindPopup 组件（底层气泡弹窗属性，Tips 复用 BubblePattern）
- Toast 组件（提示组件，同属弹窗类组件）
- Overlay 管理器（Tips / Popup / Toast / Dialog / Sheet 共享的 overlay 基础设施）
