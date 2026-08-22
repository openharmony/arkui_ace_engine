# Canvas Context

> 文档版本：v1.0
> 更新时间：2026-07-24
> 来源：`docs/context_registry.json` 主题 `Canvas`

## 定位

Canvas 是挂载到 ArkUI 组件树中的可视绘制节点。它将 `CanvasRenderingContext2D` 或 `DrawingRenderingContext` 绑定到 `CanvasPattern`，并在节点的布局、绘制和渲染上下文生命周期中呈现自定义图形。离屏绘制对象 `OffscreenCanvas` 不创建可视节点，相关入口见独立主题。

Canvas 已完成组件化改造：统一 Bridge、Dynamic/Static modifier 和 Runtime Bridge 位于 `pattern/canvas/bridge/`，动态模块映射为 `Canvas` → `canvas`，独立组件库为 `libarkui_canvas.z.so`。本文只提供稳定路由；接口约束、绘制语义和版本兼容性应继续核对当前 SDK、源码、测试和 Spec。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 可视节点、生命周期和上下文绑定 | `frameworks/core/components_ng/pattern/canvas/canvas_pattern.cpp`、`frameworks/core/components_ng/pattern/canvas/canvas_pattern.h` | `CanvasPattern` 核心入口 |
| 节点创建和属性写入 | `frameworks/core/components_ng/pattern/canvas/canvas_model_ng.cpp`、`frameworks/core/components_ng/pattern/canvas/canvas_model_ng.h` | `CanvasModelNG` 与 FrameNode 创建入口 |
| 测量与节点绘制 | `frameworks/core/components_ng/pattern/canvas/canvas_layout_algorithm.cpp`、`frameworks/core/components_ng/pattern/canvas/canvas_paint_method.cpp` | Canvas 尺寸测量、绘制任务与 RenderContext 交互入口 |
| 通用二维绘制实现 | `frameworks/core/components_ng/pattern/canvas/custom_paint_paint_method.cpp`、`frameworks/core/components_ng/pattern/canvas/custom_paint_util.cpp` | 路径、文本、图像、像素数据和绘制状态共用入口 |
| Canvas 2D 上下文模型 | `frameworks/core/components_ng/pattern/canvas/canvas_rendering_context_2d_model_ng.cpp`、`frameworks/core/components_ng/pattern/canvas/rendering_context_2d_model.h` | `CanvasRenderingContext2D` 到 Pattern 的模型入口 |
| 即时与延迟渲染上下文 | `frameworks/core/components_ng/pattern/canvas/canvas_render_context_immediate.cpp`、`frameworks/core/components_ng/pattern/canvas/canvas_render_context_deferred.cpp` | 两类渲染上下文实现入口 |
| 组件化 Bridge | `frameworks/core/components_ng/pattern/canvas/bridge/` | 统一 Bridge、Dynamic/Static modifier、Runtime Bridge 和 Dynamic Module |
| Dynamic 前端组件 | `frameworks/bridge/declarative_frontend/ark_direct_component/src/arkcanvas.ts` | Canvas 创建、属性和 AttributeModifier 前端入口 |
| Dynamic 上下文对象 | `frameworks/bridge/declarative_frontend/jsview/canvas/` | `CanvasRenderingContext2D`、`CanvasRenderer`、Path2D、ImageData 等绑定入口 |
| Static 前端补充实现 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/component/canvas.ets`、`frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/hooks/CanvasOpsHandWritten.ets` | Static Canvas 相关手写类型和 Hook 入口 |
| Static 互操作实现 | `frameworks/core/interfaces/native/implementation/canvas_modifier.cpp`、`frameworks/core/interfaces/native/implementation/canvas_rendering_context2d_accessor.cpp`、`frameworks/core/interfaces/native/implementation/canvas_renderer_accessor.cpp` | 生成式 Static modifier/accessor 的本仓实现入口 |
| 动态模块映射与构建 | `adapter/ohos/osal/dynamic_module_helper.cpp`、`frameworks/core/components_ng/pattern/canvas/BUILD.gn`、`adapter/ohos/build/BUILD.gn` | `canvas` 模块映射、源集、外部依赖和独立 SO 聚合入口 |
| 图像分析适配 | `frameworks/core/common/ai/image_analyzer_manager.h`、`adapter/ohos/osal/image_analyzer_manager.cpp`、`adapter/ohos/osal/image_analyzer_loader.cpp` | Canvas 图像分析开关、上下文 API 与可选运行时插件的排查入口 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/canvas.d.ts` | `CanvasInterface`、`CanvasAttribute`、`CanvasRenderingContext2D` 及共用绘制类型 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/canvas.static.d.ets` | Static Canvas 组件、上下文、绘制对象和 Builder 声明 |
| Modifier SDK | 未提供独立文件 | 当前 SDK 中没有 `CanvasModifier.d.ts` 或 `CanvasModifier.static.d.ets`；AttributeModifier 能力由组件声明承载 |
| Native C API / NDK | 未提供 Canvas 专属公开接口 | `interfaces/native/native_node.h` 中没有 `ARKUI_NODE_CANVAS` 或 `NODE_CANVAS_*`；内部 modifier/accessor 不是公开 C API |

API 检索建议：

- 可视组件：搜索 `CanvasInterface`、`CanvasAttribute`、`CanvasParams`、`onReady` 和 `enableAnalyzer`。
- 二维上下文：搜索 `CanvasRenderingContext2D`、`CanvasRenderer`、`DrawingRenderingContext` 和 `RenderingContextSettings`。
- 绘制辅助对象：搜索 `Path2D`、`CanvasGradient`、`CanvasPattern`、`ImageData` 和 `ImageBitmap`。
- Native 边界：`OH_ArkUI_DrawContext_GetCanvas` 属于通用自定义绘制上下文，不是 Canvas 组件的公开创建或属性接口。

### API 解析实现路径

Canvas **已完成组件化改造**。动态模块中包含组件创建、属性解析、二维上下文操作和 Static 互操作桥接；不应再按旧的通用 `nativeModule` Canvas Bridge 推断实现。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| Dynamic 前端组件 | `frameworks/bridge/declarative_frontend/ark_direct_component/src/arkcanvas.ts` | Canvas 创建、事件和 AttributeModifier 下发入口 |
| 统一 Bridge（声明式 + 动态属性） | `frameworks/core/components_ng/pattern/canvas/bridge/arkts_native_canvas_bridge.cpp` | 统一处理创建、`onReady`、分析开关和 Canvas 参数，并区分 JSView 调用模式 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/canvas/bridge/canvas_dynamic_modifier.cpp` | Dynamic 创建、属性、上下文绑定和事件委托入口 |
| Dynamic 2D 上下文 Modifier | `frameworks/core/components_ng/pattern/canvas/bridge/canvas_rendering_context_2d_dynamic_modifier.cpp` | Canvas 2D 绘制命令和状态写入入口 |
| Static Modifier | `frameworks/core/components_ng/pattern/canvas/bridge/canvas_static_modifier.cpp` | Static 节点构造、上下文绑定、属性和事件转换入口 |
| Runtime Bridge | `frameworks/core/components_ng/pattern/canvas/bridge/canvas_runtime_bridge.cpp`、`frameworks/core/interfaces/native/canvas_runtime_bridge_api.h` | Dynamic JS 对象和 Static peer 共用的 Canvas/Offscreen 模型访问接口 |
| Dynamic Module | `frameworks/core/components_ng/pattern/canvas/bridge/canvas_dynamic_module.cpp`、`frameworks/core/components_ng/pattern/canvas/bridge/canvas_dynamic_module.h` | Dynamic、Static、自定义上下文 modifier 和 Runtime Bridge 导出入口 |
| node modifier 委托 | `frameworks/core/interfaces/native/node/node_canvas_modifier.cpp`、`frameworks/core/interfaces/native/node/canvas_rendering_context_2d_modifier.cpp` | 通过 DynamicModuleHelper 获取 Canvas 模块 modifier |
| Static peer/accessor | `frameworks/core/interfaces/native/implementation/canvas_rendering_context2d_accessor.cpp`、`frameworks/core/interfaces/native/implementation/canvas_renderer_accessor.cpp` | Static 对象构造、方法和属性互操作入口；不属于公开 NDK |

独立 SO：`libarkui_canvas.z.so`。

### 外部依赖入口

外部仓路径以 OpenHarmony 根目录为基准；只列出当前源码包含关系和构建依赖已确认的入口。

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 二维图形与 Render Service | `frameworks/core/components_ng/pattern/canvas/canvas_paint_method.cpp`、`custom_paint_paint_method.cpp`、`pattern/canvas/BUILD.gn` | `<OH_ROOT>/foundation/graphic/graphic_2d` | `rosen/modules/2d_graphics/`、`rosen/modules/render_service_client/`；`graphic_2d:2d_graphics`、`graphic_2d:librender_service_client` | RSCanvas、图像、路径、画刷及节点渲染入口 |
| 文本绘制 | `frameworks/core/components_ng/pattern/canvas/canvas_paint_method.cpp`、`custom_paint_paint_method.cpp`、`pattern/canvas/BUILD.gn` | `<OH_ROOT>/foundation/graphic/graphic_2d` | `frameworks/text/`、`rosen/modules/2d_engine/rosen_text/`；`graphic_2d:rosen_text` | Canvas 文本样式转换、测量与绘制入口 |
| PixelMap 与图片数据 | `frameworks/core/components_ng/pattern/canvas/canvas_rendering_context_2d_model_ng.cpp`、`canvas_paint_method.cpp`、`frameworks/core/interfaces/native/BUILD.gn` | `<OH_ROOT>/foundation/multimedia/image_framework` | `interfaces/innerkits/include/pixel_map.h`；`image_framework:image` | PixelMap 创建、像素读写及 ImageBitmap 互操作入口 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Pattern / 绘制单元测试 | `test/unittest/core/pattern/canvas/` | 节点、布局、绘制状态、图像、文本、即时/延迟上下文和 Offscreen 共用逻辑回归 |
| Static modifier 测试 | `test/unittest/capi/modifiers/canvas_modifier_test.cpp` | 生成式 Canvas Static modifier 回归；不是公开 NDK 测试 |
| Static accessor 测试 | `test/unittest/capi/accessors/canvas_rendering_context2d_accessor_test.cpp`、`canvas_renderer_accessor_test.cpp`、`canvas_pattern_accessor_test.cpp` | Static 上下文、渲染器和辅助对象互操作回归 |
| 组件测试样例 | `test/component_test/test_cases/components/graphic_drawing/entry/src/main/ets/pages/canvas_rendering_context2D/` | 应用侧 CanvasRenderingContext2D 属性和绘制场景入口 |

### 相关 Spec

Canvas 已在功能 registry 中登记为 `05-14-02`，目标功能域为 `specs/05-ui-components/14-drawing-components/02-canvas`。当前 Spec 目录尚未建立，因此 registry 应标记 `spec_status: pending`；不要为尚不存在的 Feat 或设计文档建立链接。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| Canvas 节点没有进入预期绘制生命周期 | `CanvasModelNG`、`CanvasPattern`、布局算法和组件化统一 Bridge |
| `onReady` 或上下文绑定异常 | Dynamic/Static SDK、统一 Bridge、Static modifier、`CanvasPattern` |
| 二维绘制状态或路径结果异常 | `CanvasRenderer` API、Dynamic 上下文 modifier、`CustomPaintPaintMethod` 和 Pattern 单元测试 |
| 图像、PixelMap、ImageBitmap 或 SVG 绘制异常 | 上下文模型、`CanvasPaintMethod`、ImageProvider 入口和图片框架依赖 |
| 文本测量或绘制异常 | `CustomPaintPaintMethod`、`CanvasPaintMethod`、Rosen Text 依赖和相关单元测试 |
| `enableAnalyzer` 或上下文图像分析异常 | SDK 的平台/版本约束、`CanvasPattern`、ImageAnalyzerManager 和 OHOS 适配层 |
| Canvas 动态模块加载失败 | DynamicModuleHelper 映射、Canvas Dynamic Module、node modifier、Canvas BUILD 和独立 SO |
| 试图通过 Native C API 创建 Canvas | 当前没有公开 Canvas 节点类型；不要把内部 node modifier、生成式 accessor 或通用 DrawContext API 当成 Canvas NDK |

## 调试入口

- 节点链路：从 Dynamic `arkcanvas.ts` 或 Static Canvas 声明进入统一 Bridge/Static modifier，再检查 `CanvasModelNG` 和 `CanvasPattern`。
- 绘制链路：从 `CanvasRenderingContext2D` 方法定位上下文 modifier 或 accessor，再进入上下文模型和 PaintMethod。
- 渲染链路：区分即时与延迟 RenderContext，随后检查 RSCanvas、Render Service 和 PixelMap 入口。
- 组件化链路：从 node modifier 或 Runtime Bridge 跟踪 DynamicModuleHelper、Canvas Dynamic Module 和 `libarkui_canvas.z.so`。
- 回归验证：优先运行 Canvas Pattern 测试、Static modifier/accessor 定向测试和 graphic_drawing 组件样例。

## 相关主题

- [OffscreenCanvas：[docs/kb/components/shape/offscreen-canvas.md](offscreen-canvas.md)](offscreen-canvas.md)
- Shape 组件族：[docs/kb/components/shape/shape.md](shape.md)
- [Image：[docs/kb/components/media/image.md](../media/image.md)](../media/image.md)
- [Layout Framework：[docs/kb/architecture/layout-framework.md](../../architecture/layout-framework.md)](../../architecture/layout-framework.md)