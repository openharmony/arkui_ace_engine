# Blank Context

> 文档版本：v1.0
> 更新时间：2026-07-18
> 来源：`docs/context_registry.json` 主题 `Blank`

## 定位

Blank 是 ArkUI 的基础布局占位组件，公开接口包含最小尺寸和填充颜色配置。它与 Divider 一同完成组件化改造，由 spacing 聚合模块承载。

本文档用于快速定位 Blank 的源码、SDK 声明、属性解析、测试和 Spec。具体行为、边界条件和版本兼容性以当前 SDK、源码、测试及 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern 与节点生命周期 | `frameworks/core/components_ng/pattern/blank/blank_pattern.cpp`、`frameworks/core/components_ng/pattern/blank/blank_pattern.h` | Blank Pattern、布局属性和绘制方法装配入口 |
| Model | `frameworks/core/components_ng/pattern/blank/blank_model_ng.cpp`、`frameworks/core/components_ng/pattern/blank/blank_model_ng.h` | 节点创建、最小尺寸和颜色写入入口 |
| 布局属性 | `frameworks/core/components_ng/pattern/blank/blank_layout_property.h` | Blank 最小尺寸相关属性存储入口 |
| 绘制属性与绘制方法 | `frameworks/core/components_ng/pattern/blank/blank_paint_property.h`、`frameworks/core/components_ng/pattern/blank/blank_paint_method.cpp` | 填充颜色与内容区域绘制入口 |
| 组件化 Bridge | `frameworks/core/components_ng/pattern/blank/bridge/` | 统一 Bridge、Dynamic/Static Modifier 和 Dynamic Module |
| spacing 聚合模块 | `frameworks/core/components_ng/pattern/spacing/BUILD.gn`、`adapter/ohos/build/BUILD.gn` | Blank 与 Divider 的组件化聚合和共享 SO 构建入口 |
| node modifier 委托 | `frameworks/core/interfaces/native/node/blank_modifier.cpp`、`frameworks/core/interfaces/native/node/blank_modifier.h` | 通过 `DynamicModuleHelper` 获取 Blank 动态模块的内部委托层 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/blank.d.ts` | `BlankInterface`、`BlankAttribute` 及构造参数声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/blank.static.d.ets` | 静态 ArkTS Blank 组件和属性声明 |
| Modifier API (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/BlankModifier.d.ts` | 动态 Modifier 声明 |
| Modifier API (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/BlankModifier.static.d.ets` | 静态 Modifier 声明 |
| Public Native Node API | `interfaces/native/native_node.h` | 当前未提供 `ARKUI_NODE_BLANK` 或 `NODE_BLANK_*` 专属公共入口；同名内部 modifier 不是 Blank 专属公共 C API |

API 检索建议：

- 构造参数与属性：在 Dynamic/Static SDK 文件中搜索 `BlankInterface`、`BlankAttribute`、`Blank(` 和 `color`。
- Modifier：在 `BlankModifier*.d.ts` / `BlankModifier*.d.ets` 中核对声明。
- Native API：先在 `interfaces/native/native_node.h` 核对公共节点类型和属性枚举，不要以内部 `ArkUIBlankModifier` 推断公开 C API。

### API 解析实现路径

Blank **已完成组件化改造**，前端组件定义和属性解析统一路由到 `pattern/blank/bridge/`，并与 Divider 共享 `libarkui_spacing.z.so`。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 前端 JS/TS 定义 | `frameworks/bridge/declarative_frontend/ark_direct_component/src/arkblank.ts` | Blank 前端组件类；ArkTS Modifier 类见 `frameworks/bridge/declarative_frontend/ark_modifier/src/blank_modifier.ts` |
| 统一 Bridge | `frameworks/core/components_ng/pattern/blank/bridge/arkts_native_blank_bridge.cpp` | 声明式创建与动态属性参数解析入口，按调用模式选择当前节点 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/blank/bridge/blank_dynamic_modifier.cpp` | 动态属性到 `BlankModelNG` 的写入入口，并保留兼容管线路由 |
| Static Modifier | `frameworks/core/components_ng/pattern/blank/bridge/blank_static_modifier.cpp` | 静态编译接口到 `BlankModelNG` 的转换与写入入口 |
| Dynamic Module | `frameworks/core/components_ng/pattern/blank/bridge/blank_dynamic_module.cpp` | `BlankDynamicModule` 注册属性并提供动态、静态和 CJ modifier |
| node modifier 委托层 | `frameworks/core/interfaces/native/node/blank_modifier.cpp` | 通过 `DynamicModuleHelper` 转发到 spacing 模块中的 Blank 实现 |

组件化产物：`libarkui_spacing.z.so`。该共享库同时承载 Blank 与 Divider，不能据组件名推断为 `libarkui_blank.z.so`。

### 外部依赖入口

外部仓路径以 OpenHarmony 根目录为基准。

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 图形绘制与 RenderService | `frameworks/core/components_ng/pattern/blank/blank_paint_method.cpp`、`frameworks/core/components_ng/render/drawing.h`、`frameworks/core/components_ng/render/adapter/rosen_render_context.cpp`、`frameworks/core/components_ng/render/adapter/rosen_render_context.h` | `foundation/graphic/graphic_2d` | `rosen/modules/2d_graphics/include/draw/`、`rosen/modules/render_service_client/core/` | Blank 的内容区域绘制及 Rosen 绘制区域同步入口 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Pattern 单元测试 | `test/unittest/core/pattern/blank/` | 节点创建、属性、布局和绘制相关回归 |
| 内部 modifier 单元测试 | `test/unittest/capi/modifiers/blank_modifier_test.cpp` | `ArkUIBlankModifier` 内部函数表契约验证，不代表专属公共 C API |
| Static 生成接口测试 | `test/unittest/capi/modifiers/generated/blank_modifier_test.cpp` | 静态生成 modifier 的构造和属性入口回归 |
| 组件样例测试 | `test/component_test/test_cases/components/miscellaneous/entry/src/main/ets/pages/blank/` | Blank 公开属性的组件级样例入口 |

### 相关 Spec

Blank 功能域：`specs/05-ui-components/01-layout-components/01-blank/`（功能 ID `05-01-01`）。

| 文档 | 稳定路径 | 说明 |
|------|----------|------|
| 特性规格 | `specs/05-ui-components/01-layout-components/01-blank/Feat-01-blank-component-spec.md` | Blank 创建、布局、颜色及多范式接口规格 |
| 设计文档 | `specs/05-ui-components/01-layout-components/01-blank/design.md` | Blank 模块边界和实现设计 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| Blank 未按预期参与父容器布局 | `blank_layout_property.h`、`blank_pattern.*`、父容器布局算法及 Blank Spec |
| 构造参数未生效 | Dynamic/Static SDK 的 Blank 构造声明、统一 Bridge、Dynamic/Static Modifier |
| 填充颜色未更新 | SDK `color` 声明、`blank_paint_property.h`、`blank_paint_method.cpp` |
| 动态与静态范式结果不一致 | `blank_dynamic_modifier.cpp`、`blank_static_modifier.cpp` 和对应 modifier 测试 |
| 动态模块加载失败 | `blank_dynamic_module.cpp`、`blank_modifier.cpp`、`dynamic_module_helper.cpp` 与 spacing 构建入口 |

## 调试入口

- 创建链路：从前端 Blank 定义进入统一 Bridge，再核对 Dynamic/Static Modifier 与 `BlankModelNG`。
- 布局链路：核对 `BlankLayoutProperty`、父布局约束及对应父容器布局算法。
- 绘制链路：核对 PaintProperty、PaintMethod、GeometryNode 内容区域和 Rosen RenderContext。
- 组件化链路：确认 Blank 映射到 spacing 模块，且 `libarkui_spacing.z.so` 已随目标产物安装。
- 回归验证：优先运行 `test/unittest/core/pattern/blank/` 下的定向用例，再运行内部 modifier 测试。

## 相关主题

- Divider：`docs/kb/components/basic/divider.md`
- Layout Framework：`docs/kb/architecture/layout-framework.md`
- 基础布局属性：`docs/kb/capabilities/layout-attributes.md`
- 线性布局组件：`docs/kb/components/container/flex.md`
