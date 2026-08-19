# DynamicLayout Context

> 文档版本：v1.0
> 更新时间：2026-07-24
> 来源：`docs/context_registry.json` 主题 `DynamicLayout`

## 定位

DynamicLayout 是 ArkUI 的动态布局容器，通过 LayoutAlgorithm 对象在同一节点和子树上切换 Row、Column、Stack、Grid 或自定义测量/布局策略。它复用既有布局 Pattern 和属性，但由 DynamicLayoutNode 维护当前算法类型并协调 Pattern 替换。

本文档只覆盖 DynamicLayout；同一源码和动态模块中的 LazyDynamicLayout 是相邻能力，不并入本主题。具体算法参数、版本边界和回调约束以当前 SDK、源码、测试及 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 动态节点 | `frameworks/core/components_ng/pattern/dynamiclayout/dynamic_layout_node.cpp`、`frameworks/core/components_ng/pattern/dynamiclayout/dynamic_layout_node.h` | 节点复用、当前布局类型和 Pattern 替换入口 |
| Model | `frameworks/core/components_ng/pattern/dynamiclayout/dynamic_layout_model_ng.cpp`、`frameworks/core/components_ng/pattern/dynamiclayout/dynamic_layout_model_ng.h` | 节点创建、算法类型分流及共享布局属性写入入口 |
| 自定义 Pattern | `frameworks/core/components_ng/pattern/dynamiclayout/dynamic_layout_pattern.cpp`、`frameworks/core/components_ng/pattern/dynamiclayout/dynamic_layout_pattern.h` | CustomLayoutAlgorithm 对应 Pattern 与参数更新入口 |
| 自定义布局算法 | `frameworks/core/components_ng/pattern/dynamiclayout/dynamic_layout_algorithm.cpp`、`frameworks/core/components_ng/pattern/dynamiclayout/dynamic_layout_algorithm.h` | 自定义 Measure/Layout 回调及阶段回退入口 |
| 算法参数 | `frameworks/core/components_ng/pattern/dynamiclayout/algorithm_param_base.cpp`、`frameworks/core/components_ng/pattern/dynamiclayout/algorithm_param_base.h` | Row、Column、Stack、Grid、Custom 参数对象和类型入口 |
| 共享布局实现 | `frameworks/core/components_ng/pattern/linear_layout/`、`frameworks/core/components_ng/pattern/stack/`、`frameworks/core/components_ng/pattern/lazy_grid_layout/` | DynamicLayout 预置算法复用的 Pattern、Property 和算法入口 |
| 组件化 Bridge | `frameworks/core/components_ng/pattern/dynamiclayout/bridge/` | Dynamic Bridge、Dynamic Module、Dynamic modifier 与 Static ANI modifier |
| node modifier 委托 | `frameworks/core/interfaces/native/node/dynamic_layout_modifier.cpp` | DynamicModuleHelper 到 DynamicLayout 动态 modifier 的委托层 |
| Static ANI 接入 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/ani/native/dynamiclayout/` | Static 构造、算法参数读取和回调包装入口 |
| 组件构建 | `frameworks/core/components_ng/pattern/dynamiclayout/BUILD.gn`、`adapter/ohos/build/BUILD.gn` | dynamiclayout 组件化模块与共享库构建入口 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic 组件 API | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.components.ArkDynamicLayout.d.ts` | DynamicLayout 构造与 Attribute 声明 |
| Static 组件 API | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.components.ArkDynamicLayout.static.d.ets` | Static DynamicLayout 构造与 Attribute 声明 |
| Dynamic 算法 API | `<OH_ROOT>/interface/sdk-js/api/arkui/LayoutAlgorithm.d.ts` | Row、Column、Stack、Grid 和 Custom LayoutAlgorithm 声明 |
| Static 算法 API | `<OH_ROOT>/interface/sdk-js/api/arkui/LayoutAlgorithm.static.d.ets` | Static LayoutAlgorithm 类型声明 |
| Modifier SDK | 未提供独立文件 | 当前 SDK 中没有 `DynamicLayoutModifier.d.ts` 或 `DynamicLayoutModifier.static.d.ets` |
| Public Native Node API | 未提供独立节点类型 | `interfaces/native/native_node.h` 中没有 `ARKUI_NODE_DYNAMIC_LAYOUT` 或 `NODE_DYNAMIC_LAYOUT_*` |

### API 解析实现路径

DynamicLayout **已完成组件化改造**，动态模块映射为 `dynamiclayout`，组件化产物为 `libarkui_dynamiclayout.z.so`。Dynamic 范式通过统一 Bridge 和 Dynamic Module；Static 范式使用 ArkTS 前端的 handwritten hook 与 ANI 接入，不能按传统 generated Static modifier 路径推断。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| Dynamic 前端组件 | `frameworks/bridge/declarative_frontend/ark_component/components/arkdynamiclayout.js` | DynamicLayout 声明式组件、模块加载和 AttributeModifier 入口 |
| 统一 Dynamic Bridge | `frameworks/core/components_ng/pattern/dynamiclayout/bridge/arkts_native_dynamic_layout_bridge.cpp` | LayoutAlgorithm 类型识别、参数解析、创建与运行时更新入口 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/dynamiclayout/bridge/dynamic_layout_dynamic_modifier.cpp` | 解析结果到 DynamicLayoutModelNG 的创建和更新入口 |
| Dynamic Module | `frameworks/core/components_ng/pattern/dynamiclayout/bridge/dynamic_layout_dynamic_module.cpp` | DynamicLayout/LazyDynamicLayout 动态模块导出及 Dynamic modifier 接入 |
| node modifier 委托层 | `frameworks/core/interfaces/native/node/dynamic_layout_modifier.cpp` | 通过 DynamicModuleHelper 取得 DynamicLayout 动态 modifier |
| Static 前端组件 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/@ohos.arkui.components.ArkDynamicLayout.ets` | Static 组件 peer 和属性入口 |
| Static handwritten hook | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/hooks/DynamicLayoutHandWritten.ets` | Static LayoutAlgorithm 类型分流及 ANI 调用入口 |
| Static ANI module | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/ani/native/dynamiclayout/dynamiclayout_module.cpp` | Static 参数、FrameNode 和自定义回调到 native modifier 的转换入口 |
| Static ANI modifier | `frameworks/core/components_ng/pattern/dynamiclayout/bridge/dynamic_layout_static_ani_modifier.cpp` | Static 节点构造及各类算法参数写入 ModelNG 的入口 |

内部 `ArkUIDynamicLayoutModifier` 是组件模块函数表，不等同于公开 Native Node C API。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| DynamicLayout 单元测试 | `test/unittest/core/pattern/dynamiclayout/` | 节点、Model、Pattern、自定义算法和参数切换回归 |
| Grid 复用路径测试 | `test/unittest/core/pattern/lazy_layout/dynamic_layout_grid_test_ng.cpp` | GridLayoutAlgorithm 与 LazyGrid 复用入口回归 |
| 相邻 LazyDynamicLayout 测试 | `test/unittest/core/pattern/lazydynamiclayout/` | 共享模块内 LazyDynamicLayout 的边界回归；不替代本主题测试 |
| Context registry | `docs/context_registry.json` | DynamicLayout 的 KB、Spec、源码、API 和测试统一路由 |

### 相关 Spec

DynamicLayout 功能域：`specs/05-ui-components/01-layout-components/13-dynamic-layout/`（功能 ID `05-01-13`）。

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | 容器创建与运行时算法切换 | `Feat-01-dynamic-layout-runtime-switching-spec.md` |
| Feat-02 | Row/Column 线性布局算法 | `Feat-02-dynamic-layout-linear-algorithms-spec.md` |
| Feat-03 | Stack/Grid 布局算法 | `Feat-03-dynamic-layout-stack-grid-algorithms-spec.md` |
| Feat-04 | 自定义测量与布局算法 | `Feat-04-dynamic-layout-custom-algorithm-spec.md` |

架构决策和模块边界见同目录 `design.md`。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 算法切换后子树或布局类型异常 | DynamicLayoutNode、ModelNG、Pattern 替换和 Feat-01 |
| Row/Column 参数未生效 | LayoutAlgorithm SDK、Dynamic/Static 参数解析、LinearLayoutProperty 和 Feat-02 |
| Stack/Grid 参数未生效 | ModelNG 的类型分流、Stack/LazyGrid 共享实现和 Feat-03 |
| 自定义 Measure/Layout 回调异常 | Custom LayoutAlgorithm SDK、Dynamic Bridge 或 Static ANI module、DynamicLayoutAlgorithm 和 Feat-04 |
| Dynamic 与 Static 结果不一致 | Dynamic Bridge/Dynamic modifier 与 Static handwritten hook/ANI 两套入口 |
| 查找 DynamicLayout 公共 C API | 当前没有独立公开节点类型；不要把内部 modifier 函数表解释为 Native Node API |
| 动态模块加载失败 | DynamicModuleHelper 映射、dynamiclayout BUILD、Dynamic Module 和 node modifier 委托 |

## 调试入口

- 先记录传入的 LayoutAlgorithm 具体类型，再核对对应 Dynamic 或 Static 解析入口。
- 检查 DynamicLayoutNode 当前类型、实际 Pattern、对应 LayoutProperty 和 ModelNG 参数更新。
- Custom 场景分别追踪 Measure 与 Layout 阶段回调，不从预置算法路径推断回调行为。
- Grid 场景同时检查 LazyGrid Pattern/Property 的动态布局标记和参数写入。
- 回归优先运行 `test/unittest/core/pattern/dynamiclayout/`，再按算法类型补充共享布局测试。

## 相关主题

- [Layout Framework：`docs/kb/architecture/layout-framework.md`](../../architecture/layout-framework.md)
- [Layout Attributes：`docs/kb/capabilities/layout-attributes.md`](../../capabilities/layout-attributes.md)
- [自定义测量/布局：`docs/kb/capabilities/custom-measure-layout.md`](../../capabilities/custom-measure-layout.md)
- [Row：`docs/kb/components/container/row.md`](row.md)
- [Column：`docs/kb/components/container/column.md`](column.md)
- [Stack：`docs/kb/components/container/stack.md`](stack.md)