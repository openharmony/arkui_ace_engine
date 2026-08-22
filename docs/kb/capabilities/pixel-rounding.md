# Pixel Rounding Context

> 文档版本：v1.0
> 更新时间：2026-07-27
> 来源：`docs/context_registry.json` 主题 `PixelRounding`

## 定位

Pixel Rounding 是 ArkUI 的通用布局与渲染能力。组件级 `pixelRound` 将边界取整策略写入 LayoutProperty；页面级模式由 UIContext 配置，并由布局和 RenderContext 的几何同步路径使用。

本文档只提供组件公共属性、页面模式、Dynamic/Static 实现、Native Node 接口、测试和 Spec 的稳定路由。取整策略、版本条件和实际渲染结果以当前 SDK、源码、测试及 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 公共属性与节点写入 | `frameworks/core/components_ng/base/view_abstract.cpp`、`frameworks/core/components_ng/base/view_abstract_model_static.cpp` | 组件级 pixelRound 的 NG/Static 属性写入入口 |
| 布局属性 | `frameworks/core/components_ng/layout/layout_property.cpp`、`frameworks/core/components_ng/layout/layout_property.h` | PixelRoundPolicy 的存储、读取和 dump 路由 |
| Dynamic 属性 | `frameworks/bridge/declarative_frontend/ark_component/src/ArkComponent.ts`、`frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.cpp` | Dynamic AttributeModifier 与 Common Bridge 解析入口 |
| Static 属性 | `frameworks/core/interfaces/native/implementation/common_method_modifier.cpp` | Static Common Method 的参数转换和属性写入入口 |
| node modifier | `frameworks/core/interfaces/native/node/node_common_modifier.cpp` | Common modifier 的 PixelRoundPolicy 转换和节点读写入口 |
| 页面级模式 | `frameworks/bridge/declarative_frontend/engine/jsUIContext.js`、`frameworks/bridge/declarative_frontend/jsview/js_view_abstract.cpp`、`frameworks/core/pipeline/pipeline_base.h` | Dynamic UIContext、兼容 JS 接口与 Pipeline 页面模式入口 |
| 布局与几何同步 | `frameworks/core/components_ng/layout/layout_wrapper.cpp`、`frameworks/core/components_ng/base/frame_node.cpp` | 布局完成和节点几何同步时的取整路由入口 |
| RenderContext | `frameworks/core/components_ng/render/adapter/rosen_render_context.cpp` | RS 几何、绘制矩形与单像素取整实现入口 |
| Native Node 分发 | `interfaces/native/node/style_modifier.cpp`、`interfaces/native/node/native_node_extented.cpp` | `NODE_PIXEL_ROUND` 属性分发和 PixelRoundPolicy 工具函数实现入口 |
| 系统开关 | `frameworks/base/utils/system_properties.h`、`adapter/ohos/osal/system_properties.cpp` | 平台像素取整开关的读取入口 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic Common API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | `pixelRound` 与 `PixelRoundPolicy` 声明 |
| Static Common API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/common.static.d.ets` | Static `pixelRound` 与策略类型声明 |
| Dynamic Common Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/CommonModifier.d.ts` | Dynamic Common Modifier 声明 |
| Static Common Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/CommonModifier.static.d.ets` | Static Common Modifier 声明 |
| Dynamic UIContext API | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.UIContext.d.ts` | 页面级 PixelRoundMode 接口声明 |
| Static UIContext API | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.UIContext.static.d.ets` | Static 页面级 PixelRoundMode 接口声明 |
| Native Node API | `interfaces/native/native_node.h`、`interfaces/native/node_attributes/layout.h` | `NODE_PIXEL_ROUND`、策略枚举和 Policy 对象公开 C API |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 布局与渲染单元测试 | `test/unittest/core/layout/pixel_round_test_ng.cpp` | 组件边界策略、布局结果和 RenderContext 路由回归 |
| Static Common modifier 测试 | `test/unittest/capi/modifiers/common_method_modifier_test2.cpp` | Static PixelRoundPolicy 参数转换与节点属性回归 |
| 组件样例 | `test/component_test/test_cases/components/common/entry/src/main/ets/pages/common/PixelRoundSample.ets` | 应用侧公共属性场景入口 |
| 样例实现 | `test/component_test/test_cases/components/common/entry/src/main/ets/pages/MyTest/PixelRoundTest.ets` | 组件测试用例实现入口 |
| Context registry | `docs/context_registry.json` | Pixel Rounding 的 KB、Spec、源码、API 和测试统一路由 |

### 相关 Spec

Pixel Rounding 功能 ID 为 `04-24-01`，规划功能域为 `specs/04-common-capability/24-layout-common-capability/01-pixel-rounding/`。

当前 functions registry 已登记该主题，但目标 Spec 目录尚未建立，因此 registry 使用 `spec_status: pending`；在实际 Feat 或设计文档落盘前，不在本页推断其内容。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 组件 `pixelRound` 未生效 | Common SDK、ArkComponent / Common Bridge、node_common_modifier、ViewAbstract 和 LayoutProperty |
| Static 与 Dynamic 的策略结果不同 | Static Common Method、Dynamic Common Bridge、Common modifier 和对应 SDK 声明 |
| 页面级模式设置未反映到布局 | UIContext API、`jsUIContext.js`、`JSViewAbstract` 与 `PipelineBase` |
| 几何或绘制矩形仍出现小数误差 | LayoutWrapper、FrameNode、RosenRenderContext 和 pixel_round 单元测试 |
| Native Node Policy 创建或读取异常 | `native_node.h`、`node_attributes/layout.h`、`style_modifier.cpp` 和 `native_node_extented.cpp` |
| 平台上像素取整整体未启用 | SystemProperties 的像素取整开关与 OHOS 适配层 |

## 调试入口

- 先区分组件级 `pixelRound` 与 UIContext 页面级模式，并分别从对应 SDK 声明进入。
- 属性问题依次检查 Common Bridge 或 Static Common Method、Common modifier、ViewAbstract 和 LayoutProperty。
- 布局或渲染问题同时检查 LayoutWrapper、FrameNode 的几何同步和 RosenRenderContext 的绘制矩形处理。
- Native 场景从 `NODE_PIXEL_ROUND`、策略对象接口和 style modifier 分发定位。
- 回归优先运行 `test/unittest/core/layout/pixel_round_test_ng.cpp`，再补充 Common modifier 与组件样例。

## 相关主题

- [Layout Framework：[docs/kb/architecture/layout-framework.md](../architecture/layout-framework.md)](../architecture/layout-framework.md)
- [Layout Attributes：[docs/kb/capabilities/layout-attributes.md](layout-attributes.md)](layout-attributes.md)
- [UIContext：[docs/kb/capabilities/ui-context.md](ui-context.md)](ui-context.md)
- Safe Area：[docs/kb/capabilities/safe-area.md](safe-area.md)