# Shape Context

> 文档版本：v1.0
> 更新时间：2026-07-24
> 来源：`docs/context_registry.json` 主题 `Shape`

## 定位

Shape 绘制组件族包括 Shape、Rect、Circle、Ellipse、Line、Polyline、Polygon 和 Path。八个公开组件共享形状尺寸、位置、填充与描边等基础实现，并分别保留容器、圆角、端点、点集或路径命令等专属入口。

该组件族已完成组件化改造：八个组件均映射到 `shape` 动态模块，共享组件化产物 `libarkui_shape.z.so`；各组件在同一 `pattern/shape/bridge/` 目录中提供独立的 Bridge、Dynamic Module 和 modifier。本文档仅提供当前源码、SDK、测试和 Spec 的稳定路由，不复述接口行为或调用链，也不固化易漂移的实现细节。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 共享 Pattern、布局与绘制属性 | `frameworks/core/components_ng/pattern/shape/shape_pattern.cpp`、`frameworks/core/components_ng/pattern/shape/shape_layout_algorithm.cpp`、`frameworks/core/components_ng/pattern/shape/shape_paint_property.cpp` | 各图元共享的 Pattern、测量和绘制属性入口 |
| 共享 Model 与绘制工具 | `frameworks/core/components_ng/pattern/shape/shape_abstract_model_ng.cpp`、`frameworks/core/components_ng/pattern/shape/shape_abstract_model_static.cpp`、`frameworks/core/components_ng/pattern/shape/shape_painter.cpp`、`frameworks/core/components_ng/pattern/shape/drawing_painter.cpp` | Dynamic/Static 公共属性写入及通用 Pen、Brush、Path 绘制入口 |
| Shape 容器 | `frameworks/core/components_ng/pattern/shape/shape_model_ng.cpp`、`frameworks/core/components_ng/pattern/shape/shape_model_static.cpp`、`frameworks/core/components_ng/pattern/shape/shape_container_pattern.cpp`、`frameworks/core/components_ng/pattern/shape/shape_container_layout_algorithm.cpp` | Shape 节点创建、子图元容器、viewport 和 mesh 相关入口 |
| Rect | `frameworks/core/components_ng/pattern/shape/rect_model_ng.cpp`、`frameworks/core/components_ng/pattern/shape/rect_model_static.cpp`、`frameworks/core/components_ng/pattern/shape/rect_pattern.cpp`、`frameworks/core/components_ng/pattern/shape/rect_paint_property.h`、`frameworks/core/components_ng/pattern/shape/rect_painter.cpp` | Rect 创建、圆角属性和绘制入口 |
| Circle | `frameworks/core/components_ng/pattern/shape/circle_model_ng.cpp`、`frameworks/core/components_ng/pattern/shape/circle_pattern.h`、`frameworks/core/components_ng/pattern/shape/circle_painter.cpp` | Circle 创建、Pattern 和绘制入口 |
| Ellipse | `frameworks/core/components_ng/pattern/shape/ellipse_model_ng.cpp`、`frameworks/core/components_ng/pattern/shape/ellipse_model_static.cpp`、`frameworks/core/components_ng/pattern/shape/ellipse_pattern.h`、`frameworks/core/components_ng/pattern/shape/ellipse_painter.cpp` | Ellipse Dynamic/Static Model、Pattern 和绘制入口 |
| Line | `frameworks/core/components_ng/pattern/shape/line_model_ng.cpp`、`frameworks/core/components_ng/pattern/shape/line_model_static.cpp`、`frameworks/core/components_ng/pattern/shape/line_layout_algorithm.cpp`、`frameworks/core/components_ng/pattern/shape/line_paint_property.h`、`frameworks/core/components_ng/pattern/shape/line_painter.cpp` | Line 端点属性、布局和绘制入口 |
| Polyline / Polygon | `frameworks/core/components_ng/pattern/shape/polygon_model_ng.cpp`、`frameworks/core/components_ng/pattern/shape/polygon_model_static.cpp`、`frameworks/core/components_ng/pattern/shape/polygon_pattern.h`、`frameworks/core/components_ng/pattern/shape/polygon_paint_property.h`、`frameworks/core/components_ng/pattern/shape/polygon_painter.cpp` | 两个组件共享的点集 Model、Pattern、属性与绘制入口；前端和 Bridge 仍分别路由 |
| Path | `frameworks/core/components_ng/pattern/shape/path_model_ng.cpp`、`frameworks/core/components_ng/pattern/shape/path_model_static.cpp`、`frameworks/core/components_ng/pattern/shape/path_pattern.cpp`、`frameworks/core/components_ng/pattern/shape/path_layout_algorithm.cpp`、`frameworks/core/components_ng/pattern/shape/path_painter.cpp` | Path 命令、布局和绘制入口 |
| 兼容实现 | `frameworks/core/components_ng/pattern/shape/bridge/*_model_impl.cpp`、`frameworks/core/components/shape/` | Bridge 保留的旧管线 Model 实现和 legacy Shape 组件入口 |
| 组件化 Bridge | `frameworks/core/components_ng/pattern/shape/bridge/` | 公共及各图元的 Bridge、Dynamic/Static modifier、Dynamic Module 和兼容 Model |
| node modifier 委托 | `frameworks/core/interfaces/native/node/` | 搜索 `common_shape_modifier` 及八个图元的 `*_modifier.cpp`；这些文件通过 DynamicModuleHelper 取得 shape 模块中的内部 modifier |
| 构建与动态加载 | `frameworks/core/components_ng/pattern/shape/BUILD.gn`、`adapter/ohos/build/BUILD.gn`、`adapter/ohos/osal/dynamic_module_helper.cpp` | Shape 源集、共享组件 SO 和八个组件名到 `shape` 模块的映射 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic 组件 API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/` | `shape.d.ts`、`rect.d.ts`、`circle.d.ts`、`ellipse.d.ts`、`line.d.ts`、`polyline.d.ts`、`polygon.d.ts`、`path.d.ts` |
| Static 组件 API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/` | 对应八个小写组件名的 `*.static.d.ets` 声明 |
| Modifier API（Dynamic） | `<OH_ROOT>/interface/sdk-js/api/arkui/` | 当前有 Shape、Rect、Line、Polyline、Polygon、Path 的 `*Modifier.d.ts`；没有 Circle、Ellipse 同名文件 |
| Modifier API（Static） | `<OH_ROOT>/interface/sdk-js/api/arkui/` | 当前有 Shape、Rect、Line、Polyline、Polygon、Path 的 `*Modifier.static.d.ets`；没有 Circle、Ellipse 同名文件 |
| Public Native Node API | `interfaces/native/native_node.h` | 当前没有为这八个 UI 组件提供 `ArkUI_NodeType` 或专属 `NODE_*` 属性；内部 shape modifier 函数表不等同于公开 C API |
| 内部 modifier ABI | `frameworks/core/interfaces/arkoala/arkoala_api.h` | `ArkUICommonShapeModifier` 及八个图元 modifier 函数表声明，供组件化 Bridge、Static 前端和内部测试使用 |

API 检索建议：

- 公共属性先在各 Dynamic/Static 组件声明中搜索 `CommonShapeMethod`，再核对 Shape 自身的 `ShapeAttribute`。
- 专属入口分别搜索 `radius`、`startPoint`、`endPoint`、`points`、`commands`、`viewPort` 和 `mesh`。
- Modifier SDK 只以实际存在的六组文件为准，不要从 Bridge 或内部 modifier 推断 Circle、Ellipse 的公开 Modifier 声明。
- Native 接口先核对 `ArkUI_NodeType` 和 `ArkUI_NodeAttributeType`；不要把 RenderNode 的形状裁剪、遮罩 option 当作本组件族的公开节点 API。

### API 解析实现路径

Shape、Rect、Circle、Ellipse、Line、Polyline、Polygon 和 Path **均已完成组件化改造**。DynamicModuleHelper 将八个组件名映射到 `shape` 模块，由 `libarkui_shape.z.so` 聚合；共享属性与图元专属属性在同一 Bridge 目录中分层实现。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 前端 JS/TS 定义 | `frameworks/bridge/declarative_frontend/ark_direct_component/src/` | `arkcommonshape.ts` 以及八个图元对应的 `ark*.ts` 前端组件入口 |
| 前端 Modifier | `frameworks/bridge/declarative_frontend/ark_modifier/src/` | 搜索 `common_shape_modifier.ts` 及各图元 modifier；当前未找到 `ellipse_modifier.ts` |
| 共享 Bridge | `frameworks/core/components_ng/pattern/shape/bridge/arkts_native_common_shape_bridge.cpp` | 尺寸、位置、填充、描边等共享属性解析入口 |
| 图元专属 Bridge | `frameworks/core/components_ng/pattern/shape/bridge/` | 搜索八个图元对应的 `arkts_native_*_bridge.cpp`，定位构造和专属属性解析 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/shape/bridge/` | 搜索 common shape 与八个图元的 `*_dynamic_modifier.cpp` |
| Static Modifier | `frameworks/core/components_ng/pattern/shape/bridge/` | 搜索 common shape 与八个图元的 `*_static_modifier.cpp` |
| Dynamic Module | `frameworks/core/components_ng/pattern/shape/bridge/` | 搜索 common shape 与八个图元的 `*_dynamic_module.cpp`，定位模块创建、属性注册和 modifier 导出 |
| node modifier 委托层 | `frameworks/core/interfaces/native/node/` | 搜索 common shape 与八个图元的 `*_modifier.cpp`，定位共享 SO 加载和 modifier 获取 |
| Dynamic / Static Model | `frameworks/core/components_ng/pattern/shape/` | 搜索 `*_model_ng.cpp` 和 `*_model_static.cpp`；具体图元是否有独立 Static Model 以目录实际文件为准 |

组件化产物：`libarkui_shape.z.so`。八个组件具有各自的 Dynamic Module 导出入口，但不据此拆分为八个独立 SO。

### 外部依赖入口

外部仓路径以 OpenHarmony 根目录为基准；这里只列出由当前包含关系、绘制类型和构建依赖确认的入口。

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 图形绘制 | `frameworks/core/components_ng/pattern/shape/*_painter.cpp`、`frameworks/core/components_ng/pattern/shape/drawing_painter.cpp`、`frameworks/core/components_ng/render/drawing.h` | `<OH_ROOT>/foundation/graphic/graphic_2d` | `rosen/modules/2d_graphics/include/draw/`；`graphic_2d:2d_graphics` | 通过 Drawing 的画布、Pen、Brush、Path 和 Vertices 完成图元绘制 |
| Render Service 绘制适配 | `frameworks/core/components_ng/pattern/shape/drawing_painter.cpp`、`frameworks/core/components_ng/render/drawing.h`、`frameworks/core/components_ng/components.gni` | `<OH_ROOT>/foundation/graphic/graphic_2d` | `rosen/modules/render_service_base/include/`、`rosen/modules/render_service_client/` | 提供 RS 绘制类型、PixelMap shader 及组件源集依赖 |
| Path 命令解析 | `frameworks/core/components_ng/pattern/shape/path_layout_algorithm.cpp` | `<OH_ROOT>/third_party/skia` | `include/utils/SkParsePath.h` | Path 布局阶段的命令解析入口 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Pattern / Model 单元测试 | `test/unittest/core/pattern/shape/` | 八个图元的节点、布局、属性、Pattern 和 Dynamic/Static Model 回归 |
| Painter 单元测试 | `test/unittest/core/render/` | 搜索 Shape、Circle、Ellipse、Line、Polygon 的 `*_painter*_test_ng.cpp`，定位绘制入口回归 |
| 内部 modifier 单元测试 | `test/unittest/capi/modifiers/` | 搜索 common shape 与八个图元的 modifier 测试；内部函数表测试不代表本组件族已有专属公开 C API |
| 组件样例测试 | `test/component_test/test_cases/components/graphic_drawing/entry/src/main/ets/pages/` | `shape`、`rect`、`circle`、`ellipse`、`line`、`polyline`、`polygon`、`path` 的组件级样例入口 |
| 构建入口 | `test/unittest/core/pattern/shape/BUILD.gn` | Shape Pattern 定向测试目标和源码清单 |

### 相关 Spec

功能注册项为 `05-14-01`（Shape 相关），规划目录为 `specs/05-ui-components/14-drawing-components/01-shape/`。当前未找到该功能域的 Spec 文件，因此 `docs/context_registry.json` 应标记 `spec_status: pending`；在 Spec 文件落盘前，不在本页推断 Feat 列表或设计文档。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 填充、描边或尺寸等共享属性解析异常 | Dynamic/Static SDK、`arkts_native_common_shape_bridge.cpp`、common shape modifier、`shape_abstract_model_*` 和 `shape_paint_property.*` |
| Shape 容器的 viewport、mesh 或子图元布局异常 | Shape SDK、`shape_model_*`、`shape_container_pattern.*`、`shape_container_layout_algorithm.*` 和 Shape 单元测试 |
| Rect 圆角、Line 端点、Polyline/Polygon 点集或 Path 命令异常 | 对应 SDK、图元专属 Bridge、Model、PaintProperty / LayoutAlgorithm 与定向测试 |
| Polyline 与 Polygon 的问题互相影响 | 两者前端和 Bridge 独立，但共享 `polygon_model_*`、`polygon_pattern.h`、`polygon_paint_property.h` 和 `polygon_painter.cpp`，优先检查共享层 |
| Circle / Ellipse Modifier SDK 无法找到 | 当前 SDK 没有这两组 Modifier 声明；核对组件声明和内部 Bridge，避免虚构公开文件 |
| 误将内部 modifier 当作 Native Node C API | 先检查 `interfaces/native/native_node.h`；`frameworks/core/interfaces/native/node/*shape*_modifier.*` 属于内部委托层 |
| 组件动态模块加载失败 | `dynamic_module_helper.cpp`、shape `BUILD.gn`、各图元 Dynamic Module 和 `adapter/ohos/build/BUILD.gn` |
| 绘制结果与属性状态不一致 | 对应 PaintProperty、PaintMethod、Painter、`drawing_painter.cpp` 和 graphic_2d 入口 |

## 调试入口

- API 路由：先按具体图元核对 Dynamic/Static 声明，再进入 `ark_direct_component/src/` 中对应的 `ark*.ts`、专属 Bridge 和 modifier。
- 共享属性：从 `arkts_native_common_shape_bridge.cpp` 跟踪到 common shape modifier、ShapeAbstractModel 和 ShapePaintProperty。
- 专属属性：从具体图元 Bridge 进入对应 Dynamic/Static modifier，再检查专属 Model、LayoutAlgorithm 或 PaintProperty。
- 绘制链路：由 PaintMethod / Painter 进入 `drawing_painter.cpp` 和 `core/components_ng/render/drawing.h`，随后核对 graphic_2d 接口。
- 组件化链路：确认八个组件均映射到 `shape`，并检查 `libarkui_shape.z.so`、Dynamic Module 导出和 node modifier 委托。
- 回归验证：先运行 `test/unittest/core/pattern/shape/` 的定向测试，再按问题范围补充 Painter 或内部 modifier 测试。

## 相关主题

- [Canvas：`docs/kb/components/shape/canvas.md`](canvas.md)
- [OffscreenCanvas：`docs/kb/components/shape/offscreen-canvas.md`](offscreen-canvas.md)
- [Layout Framework：`docs/kb/architecture/layout-framework.md`](../../architecture/layout-framework.md)
- [Layout Attributes：`docs/kb/capabilities/layout-attributes.md`](../../capabilities/layout-attributes.md)
- [Image：`docs/kb/components/media/image.md`](../media/image.md)