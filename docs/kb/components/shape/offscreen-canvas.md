# OffscreenCanvas Context

> 文档版本：v1.0
> 更新时间：2026-07-24
> 来源：`docs/context_registry.json` 主题 `OffscreenCanvas`

## 定位

OffscreenCanvas 是不挂载到 ArkUI 可视组件树的离屏绘制对象。开发者通过 `OffscreenCanvas` 和 `OffscreenCanvasRenderingContext2D` 管理离屏画布、执行二维绘制并与 ImageBitmap/PixelMap 互操作；它不等同于可见的 `Canvas` FrameNode。

OffscreenCanvas 没有独立的组件化 Bridge、node modifier、Dynamic Module 或 SO。Dynamic 与 Static 路径均复用已经组件化的 Canvas 模块及其 Runtime Bridge，实际实现位于 `pattern/canvas/`，随 `libarkui_canvas.z.so` 交付。本文只提供稳定路由；接口约束、可用场景和版本兼容性应继续核对当前 SDK、源码、测试和 Spec。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 离屏绘制状态与操作 | `frameworks/core/components_ng/pattern/canvas/offscreen_canvas_pattern.cpp`、`frameworks/core/components_ng/pattern/canvas/offscreen_canvas_pattern.h` | `OffscreenCanvasPattern` 核心入口；该 Pattern 由对象路径持有，不代表已创建可视 FrameNode |
| 离屏画布实现 | `frameworks/core/components_ng/pattern/canvas/offscreen_canvas_paint_method.cpp`、`frameworks/core/components_ng/pattern/canvas/offscreen_canvas_paint_method.h` | 离屏 RSCanvas、像素和 ImageBitmap 转换入口 |
| 离屏 2D 上下文模型 | `frameworks/core/components_ng/pattern/canvas/offscreen_canvas_rendering_context_2d_model_ng.cpp`、`frameworks/core/components_ng/pattern/canvas/offscreen_canvas_rendering_context_2d_model_ng.h` | `OffscreenCanvasRenderingContext2D` 到 Pattern 的模型入口 |
| 共用二维绘制实现 | `frameworks/core/components_ng/pattern/canvas/custom_paint_paint_method.cpp`、`frameworks/core/components_ng/pattern/canvas/custom_paint_util.cpp` | 可视与离屏上下文共用的路径、文本、图像和绘制状态入口 |
| Canvas Runtime Bridge | `frameworks/core/components_ng/pattern/canvas/bridge/canvas_runtime_bridge.cpp`、`frameworks/core/interfaces/native/implementation/canvas_runtime_bridge.h` | 创建离屏 Pattern/上下文模型、调整尺寸及导出图像的共享桥接入口 |
| Dynamic OffscreenCanvas 对象 | `frameworks/bridge/declarative_frontend/jsview/canvas/js_offscreen_canvas.cpp`、`frameworks/bridge/declarative_frontend/jsview/canvas/js_offscreen_canvas.h` | NAPI 对象构造、尺寸、上下文和转移入口 |
| Dynamic 离屏 2D 上下文 | `frameworks/bridge/declarative_frontend/jsview/canvas/js_offscreen_rendering_context.cpp`、`frameworks/bridge/declarative_frontend/jsview/canvas/js_offscreen_rendering_context.h` | Dynamic 上下文属性和方法绑定入口 |
| Static OffscreenCanvas peer | `frameworks/core/interfaces/native/implementation/offscreen_canvas_accessor.cpp`、`frameworks/core/interfaces/native/implementation/offscreen_canvas_peer.cpp`、`frameworks/core/interfaces/native/implementation/offscreen_canvas_peer.h` | Static 对象构造、尺寸、上下文和 ImageBitmap 互操作入口 |
| Static 离屏上下文 peer | `frameworks/core/interfaces/native/implementation/offscreen_canvas_rendering_context2d_accessor.cpp`、`frameworks/core/interfaces/native/implementation/offscreen_canvas_rendering_context2d_peer_impl.cpp` | Static 离屏上下文构造和专属方法互操作入口 |
| 共用模块构建 | `frameworks/core/components_ng/pattern/canvas/BUILD.gn`、`adapter/ohos/build/BUILD.gn`、`adapter/ohos/osal/dynamic_module_helper.cpp` | Offscreen 源码随 Canvas 组件源集编译，并由 Canvas 动态模块提供 Runtime Bridge |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/canvas.d.ts` | `OffscreenCanvas`、`OffscreenCanvasRenderingContext2D` 及共用绘制类型 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/canvas.static.d.ets` | Static 离屏对象、上下文、ImageBitmap 和绘制类型声明 |
| Modifier SDK | 不适用 | OffscreenCanvas 不是可视节点，没有 AttributeModifier 或独立 Modifier SDK |
| Native C API / NDK | 未提供 OffscreenCanvas 专属公开接口 | `interfaces/native/native_node.h` 中没有 OffscreenCanvas 节点类型或属性；生成式 accessor/peer 不是公开 C API |

API 检索建议：

- 离屏对象：搜索 `OffscreenCanvas`、`getContext`、`transferToImageBitmap`、`width` 和 `height`。
- 离屏上下文：搜索 `OffscreenCanvasRenderingContext2D`、`toDataURL` 和共用基类 `CanvasRenderer`。
- 图像互操作：搜索 `ImageBitmap`、`ImageData`、`PixelMap` 和 `drawImage`。
- 边界判断：需要屏幕内节点、组件属性和节点生命周期时应转查 Canvas，而不是 OffscreenCanvas。

### API 解析实现路径

OffscreenCanvas **不是独立可视组件，组件化状态不单独成立**。它没有自己的组件 Bridge 或动态库；当前 Dynamic/Static 对象实现通过 Canvas Runtime Bridge 进入 Canvas 组件化模块。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| Dynamic 对象绑定 | `frameworks/bridge/declarative_frontend/jsview/canvas/js_offscreen_canvas.cpp` | OffscreenCanvas 的 NAPI 构造、对象生命周期、尺寸、上下文与 ImageBitmap 入口 |
| Dynamic 上下文绑定 | `frameworks/bridge/declarative_frontend/jsview/canvas/js_offscreen_rendering_context.cpp` | OffscreenCanvasRenderingContext2D 的绘制属性和方法入口 |
| Dynamic 共享桥接 | `frameworks/core/interfaces/native/implementation/canvas_runtime_bridge.h`、`frameworks/core/components_ng/pattern/canvas/bridge/canvas_runtime_bridge.cpp` | 通过 Canvas Dynamic Module 获取 Runtime Bridge，再创建离屏 Pattern 和模型 |
| Static OffscreenCanvas accessor | `frameworks/core/interfaces/native/implementation/offscreen_canvas_accessor.cpp`、`offscreen_canvas_peer.cpp` | Static 对象和 peer 的构造、尺寸、上下文与 ImageBitmap 入口 |
| Static 离屏上下文 accessor | `frameworks/core/interfaces/native/implementation/offscreen_canvas_rendering_context2d_accessor.cpp`、`offscreen_canvas_rendering_context2d_peer_impl.cpp` | Static 上下文对象和专属方法入口 |
| NG 模型与绘制 | `frameworks/core/components_ng/pattern/canvas/offscreen_canvas_rendering_context_2d_model_ng.cpp`、`offscreen_canvas_pattern.cpp`、`offscreen_canvas_paint_method.cpp` | Dynamic/Static 共用的离屏绘制实现 |
| 共享 Dynamic Module | `frameworks/core/components_ng/pattern/canvas/bridge/canvas_dynamic_module.cpp` | 只导出 Canvas 模块及 `canvasBridge`；不存在 OffscreenCanvas 独立模块 |

共享 SO：`libarkui_canvas.z.so`。不存在 `libarkui_offscreencanvas.z.so`。

### 外部依赖入口

外部仓路径以 OpenHarmony 根目录为基准；只列出当前源码包含关系和构建依赖已确认的入口。

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 离屏二维图形 | `frameworks/core/components_ng/pattern/canvas/offscreen_canvas_paint_method.cpp`、`custom_paint_paint_method.cpp`、`pattern/canvas/BUILD.gn` | `<OH_ROOT>/foundation/graphic/graphic_2d` | `rosen/modules/2d_graphics/`；`graphic_2d:2d_graphics` | RSCanvas、位图、路径、画刷及图像编码入口 |
| 文本绘制 | `frameworks/core/components_ng/pattern/canvas/offscreen_canvas_paint_method.cpp`、`custom_paint_paint_method.cpp`、`pattern/canvas/BUILD.gn` | `<OH_ROOT>/foundation/graphic/graphic_2d` | `frameworks/text/`、`rosen/modules/2d_engine/rosen_text/`；`graphic_2d:rosen_text` | 离屏文本样式转换、测量与绘制入口 |
| PixelMap 与 ImageBitmap | `frameworks/core/components_ng/pattern/canvas/offscreen_canvas_rendering_context_2d_model_ng.cpp`、`offscreen_canvas_paint_method.cpp`、`frameworks/core/interfaces/native/BUILD.gn` | `<OH_ROOT>/foundation/multimedia/image_framework` | `interfaces/innerkits/include/pixel_map.h`；`image_framework:image` | 离屏像素缓冲创建、读写和 ImageBitmap 转换入口 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Pattern / 绘制单元测试 | `test/unittest/core/pattern/canvas/` | OffscreenCanvasPattern、OffscreenCanvasPaintMethod、像素、图像、路径和文本共用逻辑回归 |
| Mock 模型 | `test/mock/frameworks/core/components_ng/pattern/canvas/` | 离屏上下文模型替身和依赖隔离入口 |
| Static 绘制对象测试 | `test/unittest/capi/accessors/drawing_canvas_accessor_test.cpp` | 基于 OffscreenCanvasPattern 的生成式绘制 accessor 回归；不是公开 NDK 测试 |
| OffscreenCanvas 组件样例 | `test/component_test/test_cases/components/graphic_drawing/entry/src/main/ets/pages/offscreen_canvas/` | 离屏对象尺寸和创建场景入口 |
| 离屏上下文组件样例 | `test/component_test/test_cases/components/graphic_drawing/entry/src/main/ets/pages/offscreen_canvas_rendering_context2D/` | OffscreenCanvasRenderingContext2D 属性和绘制场景入口 |

### 相关 Spec

OffscreenCanvas 已在功能 registry 中登记为 `05-14-03`，目标功能域为 `specs/05-ui-components/14-drawing-components/03-offscreen-canvas`。当前 Spec 目录尚未建立，因此 registry 应标记 `spec_status: pending`；不要为尚不存在的 Feat 或设计文档建立链接。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 把 OffscreenCanvas 当成可见组件或 FrameNode 使用 | 先确认 SDK 对象类型，再对照 Offscreen peer、Canvas Runtime Bridge 和可视 Canvas 主题 |
| 离屏上下文创建或对象生命周期异常 | Dynamic `js_offscreen_canvas.cpp` 或 Static accessor/peer、Runtime Bridge、`OffscreenCanvasPattern` |
| 离屏尺寸或像素缓冲异常 | Dynamic/Static 对象入口、Runtime Bridge 的尺寸更新、Offscreen PaintMethod 和 PixelMap 依赖 |
| `transferToImageBitmap` 或图像读写异常 | Offscreen accessor/peer、Runtime Bridge、Offscreen Pattern/PaintMethod 和 ImageBitmap/PixelMap 路径 |
| 路径、文本或绘制状态异常 | `JSOffscreenRenderingContext` 或 Static 上下文 accessor、上下文模型、`CustomPaintPaintMethod` |
| 查找 OffscreenCanvas node modifier 或独立 SO | 两者均不存在；应检查 Canvas Runtime Bridge、Canvas Dynamic Module 和 `libarkui_canvas.z.so` |
| 试图通过 Native C API 创建 OffscreenCanvas | 当前没有专属公开 Native C API；不要把生成式 Static accessor 或 `OH_Drawing_Canvas` 当成 OffscreenCanvas NDK |

## 调试入口

- 对象链路：先区分 Dynamic NAPI 对象与 Static peer，再检查它们是否取得 Canvas Runtime Bridge。
- 上下文链路：从 OffscreenCanvasRenderingContext2D 绑定/accessor 进入离屏上下文模型、Pattern 和 PaintMethod。
- 图像链路：从 ImageBitmap、ImageData 或 PixelMap 操作定位 Runtime Bridge、Offscreen PaintMethod 和图片框架入口。
- 模块链路：只检查 Canvas 动态模块及 `libarkui_canvas.z.so`，不要寻找不存在的 OffscreenCanvas 独立模块。
- 回归验证：优先运行 Canvas Pattern 单元测试及 offscreen_canvas、offscreen_canvas_rendering_context2D 组件样例。

## 相关主题

- [Canvas：[docs/kb/components/shape/canvas.md](canvas.md)](canvas.md)
- Shape 组件族：[docs/kb/components/shape/shape.md](shape.md)
- [Image：[docs/kb/components/media/image.md](../media/image.md)](../media/image.md)