# Hyperlink Context

> 文档版本：v2.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `Hyperlink`

## 定位

Hyperlink 是超链接组件，拥有独立 `HyperlinkPattern`（继承 `TextPattern`），属性存储于 `HyperlinkLayoutProperty`（继承 `TextLayoutProperty`，新增 `Color`/`Address`）。点击经 `LinkToAddress`→`pipeline->HyperlinkStartAbility(address)` 拉起能力；支持拖拽（Udmf link record）、状态视觉（hover/press/visited/disabled）、键盘激活。公共声明面极小（构造 + `color`），`draggable`/`responseRegion` 为 CommonMethod 通用属性复用。行为事实以 SDK 声明、源码、测试与 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern（导航/状态视觉/拖拽/键盘） | `frameworks/core/components_ng/pattern/hyperlink/hyperlink_pattern.h/.cpp` | 继承 TextPattern，EnableDrag/LinkToAddress/OnHoverEvent/OnTouchEvent/OnKeyEvent/OnInjectionEvent |
| Model NG | `frameworks/core/components_ng/pattern/hyperlink/hyperlink_model_ng.h/.cpp` | `Create`(HYPERLINK_ETS_TAG)/SetTextStyle/SetColor/SetDraggable/SetResponseRegion |
| Model 抽象 | `frameworks/core/components_ng/pattern/hyperlink/hyperlink_model.h` | `HyperlinkModel` 虚接口 |
| 静态范式 Model | `frameworks/core/components_ng/pattern/hyperlink/hyperlink_model_static.h/.cpp` | 静态 ArkTS |
| 属性存储 | `frameworks/core/components_ng/pattern/hyperlink/hyperlink_layout_property.h` | 继承 TextLayoutProperty，`Color`(MEASURE)/`Address`(NORMAL)，ToJsonValue/ToTreeJson（含 API 18 色分支） |
| 主题 | `frameworks/core/components/hyperlink/hyperlink_theme.h` | 默认色 textLinkedColor/textTouchedColor/textFocusedColor/装饰/opacity/draggable |
| legacy 组件 | `frameworks/core/components/hyperlink/hyperlink_component.h/.cpp` | 兼容 pipeline |
| Inspector（V2） | `frameworks/core/components_v2/inspector/hyperlink_composed_element.h/.cpp` | 序列化 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/hyperlink.d.ts` | 公共契约 `HyperlinkAttribute`（仅 `color`），`HyperlinkInterface(address, content?)` |
| Static | `<OH_ROOT>/interface/sdk-js/api/arkui/component/hyperlink.static.d.ets` | 静态 ArkTS |
| Modifier Dynamic | `<OH_ROOT>/interface/sdk-js/api/arkui/HyperlinkModifier.d.ts` | 动态 Modifier |
| C API | `frameworks/core/interfaces/arkoala/arkoala_api.h`（`GENERATED_ArkUIHyperlinkModifier`：construct/setHyperlinkOptions/setColor） | NDK Modifier 面，无独立 `NODE_HYPERLINK` 节点类型 |
| C API accessor | `frameworks/core/interfaces/native/node/hyperlink_modifier.h` | `GetHyperlinkModifier()`/`GetCJUIHyperlinkModifier()`，经 `DynamicModule("Hyperlink")` 懒加载 |
| 前端 TS | `frameworks/bridge/declarative_frontend/ark_component/src/ArkHyperlink.ts` + `ark_modifier/src/hyperlink_modifier.ts` | 动态属性下发（color/draggable/responseRegion） |

### API 解析实现路径

Hyperlink 已完成组件化改造（在 `adapter/ohos/osal/dynamic_module_helper.cpp` 动态模块列表中，键 `"Hyperlink"`→模块 `"hyperlink"`，独立 so `libarkui_hyperlink.z.so`）。无 `js_hyperlink.cpp`。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 前端 JS/TS 定义 | `frameworks/bridge/declarative_frontend/ark_component/src/ArkHyperlink.ts` + `ark_modifier/src/hyperlink_modifier.ts` | `color`/`draggable`/`responseRegion` 经 `getUINativeModule().hyperlink.*` |
| 统一 Bridge | `frameworks/core/components_ng/pattern/hyperlink/bridge/arkts_native_hyperlink_bridge.cpp` | 静态属性解析 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/hyperlink/bridge/hyperlink_dynamic_modifier.cpp` | `ArkUIHyperlinkModifier` 表（color/draggable/responseRegion + reset/createFrameNode/pop）+ CJ `CJUIHyperlinkModifier` |
| Static Modifier | `frameworks/core/components_ng/pattern/hyperlink/bridge/hyperlink_static_modifier.cpp` | 静态编译路径 |
| Dynamic Module | `frameworks/core/components_ng/pattern/hyperlink/bridge/hyperlink_dynamic_module.cpp` | `HyperlinkDynamicModule`，`libarkui_hyperlink.z.so` 入口 |
| legacy pipeline impl | `frameworks/core/components_ng/pattern/hyperlink/bridge/hyperlink_model_impl.h/.cpp` | `HyperlinkModelImpl : HyperlinkModel`（用 `HyperlinkComponent`） |
| node_modifier 委托层 | `frameworks/core/interfaces/native/node/hyperlink_modifier.h/.cpp` + `implementation/hyperlink_modifier.cpp` | 懒加载 DynamicModule，静态 `GetStaticModifier()` |


### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|-----------|-------------------------------|------|
| 能力拉起 | `hyperlink_pattern.cpp` LinkToAddress | aafwk ability | — | `pipeline->HyperlinkStartAbility(address)` |
| 拖拽传递 | `hyperlink_pattern.cpp` EnableDrag | UDMF | — | link record `{url,title}` |
| 排版引擎 | 共享 `text_pattern.cpp` | `graphic_2d` | `rosen/modules/2d_engine/rosen_text/` | Typography 段落排版 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单测 | `test/unittest/core/pattern/hyperlink/hyperlink_test_ng.cpp`、`hyperlink_test_core.cpp` | HyperlinkPattern/Model |
| C-API 单测 | `test/unittest/capi/modifiers/hyperlink_modifier_test.cpp` | NDK Modifier 面 |

### 相关 Spec

| Spec 域 | 路径 | 状态 |
|---------|------|------|
| Hyperlink 长期规格 | `specs/05-ui-components/09-text-components/09-hyperlink/` | active（3 个 Feat：链接配置颜色/拖拽响应状态视觉导航/键盘无障碍 C-API 桥） |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 默认色不一致 | `hyperlink_layout_property.h` API 18 主题派生分支（API<18 硬编码 Color::BLUE） |
| 导航不跳转 | `hyperlink_pattern.cpp` LinkToAddress + `IsPreventDefault()`/PREVIEW 跳过 |
| 拖拽不生效 | `EnableDrag` + 主题默认 `draggable_=false` |
| 无 `Type`/`usageAddress` 字段 | 实际属性为 `Address`（单 URL string），见 Spec Feat-01 |
| 无独立 C-API 节点类型 | 仅 modifier 模式（`GENERATED_ArkUIHyperlinkModifier`），见 Spec 风险表 |

## 调试入口

Dump：`HyperlinkPattern` dump；`OnInjectionEvent({"cmd":"click"})` 测试注入。

## 相关主题

- [Text](./text.md)（继承 TextPattern/TextLayoutProperty）
- [SymbolGlyph](./symbol-glyph.md)（共享 Text 排版）