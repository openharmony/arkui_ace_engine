# Divider Context

> 文档版本：v1.0
> 更新时间：2026-07-18
> 来源：`docs/context_registry.json` 主题 `Divider`

## 定位

Divider 是 ArkUI 的基础分隔线组件，公开接口覆盖方向、颜色、线宽和端点样式。它与 Blank 一同完成组件化改造，由 spacing 聚合模块承载。

本文档用于快速定位 Divider 的源码、SDK 声明、属性解析、测试和 Spec。具体行为、边界条件和版本兼容性以当前 SDK、源码、测试及 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern 与生命周期 | `frameworks/core/components_ng/pattern/divider/divider_pattern.cpp`、`frameworks/core/components_ng/pattern/divider/divider_pattern.h` | Divider Pattern、布局算法和绘制方法装配入口 |
| Model | `frameworks/core/components_ng/pattern/divider/divider_model_ng.cpp`、`frameworks/core/components_ng/pattern/divider/divider_model_ng_static.cpp` | Dynamic/Static 节点创建与属性写入入口 |
| 布局 | `frameworks/core/components_ng/pattern/divider/divider_layout_algorithm.cpp`、`frameworks/core/components_ng/pattern/divider/divider_layout_property.h` | 分隔线测量和布局属性入口 |
| 绘制属性 | `frameworks/core/components_ng/pattern/divider/divider_render_property.h` | 方向、颜色、线宽和端点样式的绘制属性入口 |
| 绘制方法与 modifier | `frameworks/core/components_ng/pattern/divider/divider_paint_method.cpp`、`frameworks/core/components_ng/pattern/divider/divider_modifier.cpp` | 绘制参数准备和线段绘制入口 |
| 组件化 Bridge | `frameworks/core/components_ng/pattern/divider/bridge/` | 统一 Bridge、Dynamic/Static Modifier 和 Dynamic Module |
| spacing 聚合模块 | `frameworks/core/components_ng/pattern/spacing/BUILD.gn`、`adapter/ohos/build/BUILD.gn` | Blank 与 Divider 的组件化聚合和共享 SO 构建入口 |
| node modifier 委托 | `frameworks/core/interfaces/native/node/divider_modifier.cpp`、`frameworks/core/interfaces/native/node/divider_modifier.h` | 通过 `DynamicModuleHelper` 获取 Divider 动态模块的内部委托层 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/divider.d.ts` | `DividerInterface`、`DividerAttribute` 及组件属性声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/divider.static.d.ets` | 静态 ArkTS Divider 组件和属性声明 |
| Modifier API (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/DividerModifier.d.ts` | 动态 Modifier 声明 |
| Modifier API (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/DividerModifier.static.d.ets` | 静态 Modifier 声明 |
| Public Native Node API | `interfaces/native/native_node.h` | 当前未提供 `ARKUI_NODE_DIVIDER` 或 `NODE_DIVIDER_*` 专属公共入口；同名内部 modifier 不是 Divider 专属公共 C API |

API 检索建议：

- 组件属性：在 Dynamic/Static SDK 文件中搜索 `DividerAttribute`、`vertical`、`color`、`strokeWidth` 和 `lineCap`。
- Modifier：在 `DividerModifier*.d.ts` / `DividerModifier*.d.ets` 中核对声明。
- Native API：先在 `interfaces/native/native_node.h` 核对公共节点类型和属性枚举，不要以内部 `ArkUIDividerModifier` 推断公开 C API。

### API 解析实现路径

Divider **已完成组件化改造**，前端组件定义和属性解析统一路由到 `pattern/divider/bridge/`，并与 Blank 共享 `libarkui_spacing.z.so`。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 前端 JS/TS 定义 | `frameworks/bridge/declarative_frontend/ark_direct_component/src/arkdivider.ts` | Divider 前端组件类；ArkTS Modifier 类见 `frameworks/bridge/declarative_frontend/ark_modifier/src/divider_modifier.ts` |
| 统一 Bridge | `frameworks/core/components_ng/pattern/divider/bridge/arkts_native_divider_bridge.cpp` | 声明式创建与动态属性参数解析入口，按调用模式选择当前节点 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/divider/bridge/divider_dynamic_modifier.cpp` | 动态属性到 `DividerModelNG` 的写入入口，并保留兼容管线路由 |
| Static Modifier | `frameworks/core/components_ng/pattern/divider/bridge/divider_static_modifier.cpp` | 静态编译接口到 Static Model/ModelNG 的转换与写入入口 |
| Dynamic Module | `frameworks/core/components_ng/pattern/divider/bridge/divider_dynamic_module.cpp` | `DividerDynamicModule` 注册属性并提供动态、静态和 CJ modifier |
| node modifier 委托层 | `frameworks/core/interfaces/native/node/divider_modifier.cpp` | 通过 `DynamicModuleHelper` 转发到 spacing 模块中的 Divider 实现 |

组件化产物：`libarkui_spacing.z.so`。该共享库同时承载 Divider 与 Blank，不能据组件名推断为 `libarkui_divider.z.so`。

### 外部依赖入口

外部仓路径以 OpenHarmony 根目录为基准。

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 图形绘制 | `frameworks/core/components_ng/pattern/divider/divider_modifier.cpp`、`frameworks/core/components_ng/render/divider_painter.cpp`、`frameworks/core/components_ng/render/divider_painter.h`、`frameworks/core/components_ng/render/drawing_forward.h` | `foundation/graphic/graphic_2d` | `rosen/modules/2d_graphics/include/draw/` | Divider 通过 ArkUI 绘制抽象进入 Drawing Canvas 的线段绘制入口 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Pattern 单元测试 | `test/unittest/core/pattern/divider/` | 节点创建、布局、属性和绘制相关回归 |
| 内部 modifier 单元测试 | `test/unittest/capi/modifiers/divider_modifier_test.cpp` | `ArkUIDividerModifier` 内部函数表契约验证，不代表专属公共 C API |
| 组件样例测试 | `test/component_test/test_cases/components/miscellaneous/entry/src/main/ets/pages/divider/` | Divider 公开属性的组件级样例入口 |
| Context registry | `docs/context_registry.json` | Divider 的 KB、Spec、源码、API 和测试统一路由 |

### 相关 Spec

Divider 功能域：`specs/05-ui-components/01-layout-components/02-divider/`（功能 ID `05-01-02`）。

| 文档 | 稳定路径 | 说明 |
|------|----------|------|
| 特性规格 | `specs/05-ui-components/01-layout-components/02-divider/Feat-01-divider-spec.md` | Divider 创建、方向、绘制属性和多范式接口规格 |
| 设计文档 | `specs/05-ui-components/01-layout-components/02-divider/design.md` | Divider 模块边界和实现设计 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| Divider 尺寸或方向异常 | Dynamic/Static SDK、`divider_layout_algorithm.cpp`、`divider_layout_property.h` 与 Divider Spec |
| 颜色、线宽或端点样式未生效 | SDK 属性声明、统一 Bridge、`divider_render_property.h` 和 `divider_modifier.cpp` |
| 绘制区域与布局结果不一致 | `divider_paint_method.cpp`、`divider_modifier.cpp`、GeometryNode 与 RenderContext |
| 动态与静态范式结果不一致 | `divider_dynamic_modifier.cpp`、`divider_static_modifier.cpp` 和 Pattern 测试 |
| 动态模块加载失败 | `divider_dynamic_module.cpp`、`divider_modifier.cpp`、`dynamic_module_helper.cpp` 与 spacing 构建入口 |

## 调试入口

- 创建链路：从前端 Divider 定义进入统一 Bridge，再核对 Dynamic/Static Modifier 与 Model。
- 布局链路：核对方向属性、布局约束、LayoutAlgorithm 和 GeometryNode 结果。
- 绘制链路：从 RenderProperty 进入 PaintMethod、DividerModifier 和通用 DividerPainter。
- 组件化链路：确认 Divider 映射到 spacing 模块，且 `libarkui_spacing.z.so` 已随目标产物安装。
- 回归验证：优先运行 `test/unittest/core/pattern/divider/` 下的定向用例，再运行内部 modifier 测试。

## 相关主题

- Blank：`docs/kb/components/basic/blank.md`
- Layout Framework：`docs/kb/architecture/layout-framework.md`
- 基础布局属性：`docs/kb/capabilities/layout-attributes.md`
