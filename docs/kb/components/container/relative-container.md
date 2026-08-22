# RelativeContainer Context

> 文档版本：v1.0
> 更新时间：2026-07-24
> 来源：`docs/context_registry.json` 主题 `RelativeContainer`

## 定位

RelativeContainer 是 ArkUI 的相对布局容器。容器本身提供 guideline 和 barrier 虚拟锚点，子组件通过 Common 布局属性中的 ID、对齐规则、偏置、链模式和链权重描述相互依赖。

本文档用于快速定位 RelativeContainer 的容器属性、子项公共属性、布局算法、Dynamic/Static 解析路径、Native 接口、测试和 Spec。具体行为、版本边界和异常处理以当前 SDK、源码、测试及 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern | `frameworks/core/components_ng/pattern/relative_container/relative_container_pattern.h` | Pattern、布局算法/属性创建、拓扑结果缓存及调试入口 |
| Model | `frameworks/core/components_ng/pattern/relative_container/relative_container_model_ng.cpp`、`frameworks/core/components_ng/pattern/relative_container/relative_container_model_ng.h` | 节点创建及 guideline、barrier 写入入口 |
| 布局属性 | `frameworks/core/components_ng/pattern/relative_container/relative_container_layout_property.h` | 容器虚拟锚点属性存储入口 |
| 布局算法 | `frameworks/core/components_ng/pattern/relative_container/relative_container_layout_algorithm.cpp`、`frameworks/core/components_ng/pattern/relative_container/relative_container_layout_algorithm.h` | 依赖图、测量顺序、锚定、辅助线、屏障和链式布局入口 |
| 子项公共属性 | `frameworks/core/components_ng/property/flex_property.h`、`frameworks/core/components_ng/layout/layout_property.cpp` | 子项 alignRules、bias、chain style 和 chain weight 存储入口 |
| 公共属性写入 | `frameworks/core/components_ng/base/view_abstract.cpp`、`frameworks/core/interfaces/native/node/node_common_modifier.cpp` | RelativeContainer 子项的 Common 布局属性写入入口 |
| 组件化 Bridge | `frameworks/core/components_ng/pattern/relative_container/bridge/` | 统一 Bridge、Dynamic/Static modifier 和 Dynamic Module |
| node modifier 委托 | `frameworks/core/interfaces/native/node/node_relative_container_modifier.cpp` | 通过 DynamicModuleHelper 获取组件 modifier |
| Native option 实现 | `interfaces/native/node/node_node_relative_container.cpp` | guideline、barrier 和 alignment rule option 的公开 Native 工具函数实现 |
| 组件构建 | `frameworks/core/components_ng/pattern/relative_container/BUILD.gn`、`adapter/ohos/build/BUILD.gn` | RelativeContainer 组件化源码和共享库构建入口 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic 组件 API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/relative_container.d.ts` | RelativeContainer、guideline、barrier 及相关类型声明 |
| Static 组件 API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/relativeContainer.static.d.ets` | Static RelativeContainer 构造、属性及相关类型声明 |
| Dynamic Common API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | 子项 ID、alignRules、chainMode、chainWeight 等公共属性声明 |
| Static Common API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/common.static.d.ets` | Static 子项相对布局公共属性声明 |
| Modifier API（Dynamic） | 未提供 | 当前 SDK 中没有 `RelativeContainerModifier.d.ts`，不得由引擎内部 modifier 推断公共声明 |
| Modifier API（Static） | `<OH_ROOT>/interface/sdk-js/api/arkui/RelativeContainerModifier.static.d.ets` | Static RelativeContainer Modifier 声明 |
| Native Node API | `interfaces/native/native_node.h` | `ARKUI_NODE_RELATIVE_CONTAINER`、容器专属属性及相关 Common 属性枚举 |
| Native option API | `interfaces/native/node_attributes/layout.h` | guideline、barrier 和 alignment rule option 的公开 C API 声明 |

### API 解析实现路径

RelativeContainer **已完成组件化改造**。组件专属解析统一位于 `pattern/relative_container/bridge/`，通过 `relativecontainer` 动态模块加载，并输出 `libarkui_relativecontainer.z.so`。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| Dynamic 前端组件 | `frameworks/bridge/declarative_frontend/ark_direct_component/src/arkrelativecontainer.ts` | 声明式创建、AttributeModifier 与容器属性下发入口 |
| Dynamic 前端 Modifier | `frameworks/bridge/declarative_frontend/ark_modifier/src/relative_container_modifier.ts` | RelativeContainer Modifier 类和组件动态模块加载入口 |
| 统一 Bridge | `frameworks/core/components_ng/pattern/relative_container/bridge/arkts_native_relative_container_bridge.cpp` | 声明式和动态属性的创建、guideline、barrier 参数解析入口 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/relative_container/bridge/relative_container_dynamic_modifier.cpp` | Dynamic 属性到 ModelNG 的写入入口 |
| Static 前端节点 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/typedNode/ArkRelativeContainerNode.ets` | Static 构造和容器属性进入 native peer 的入口 |
| Static Modifier | `frameworks/core/components_ng/pattern/relative_container/bridge/relative_container_static_modifier.cpp` | Static 参数转换和 ModelNG 写入入口 |
| Dynamic Module | `frameworks/core/components_ng/pattern/relative_container/bridge/relative_container_dynamic_module.cpp` | Dynamic、Static 和 CJ modifier 导出入口 |
| node modifier 委托层 | `frameworks/core/interfaces/native/node/node_relative_container_modifier.cpp` | 通过 DynamicModuleHelper 转发到组件化模块 |
| 子项 Dynamic Common 路径 | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.cpp`、`frameworks/core/interfaces/native/node/node_common_modifier.cpp` | alignRules、chainMode、chainWeight 等子项属性解析与写入 |
| 子项 Static Common 路径 | `frameworks/core/interfaces/native/implementation/common_method_modifier.cpp`、`frameworks/core/components_ng/base/view_abstract_model_static.cpp` | Static 子项相对布局属性转换与写入 |
| Public Native Node | `interfaces/native/node/style_modifier.cpp`、`interfaces/native/node/node_node_relative_container.cpp` | RelativeContainer 节点属性分发及 option 生命周期实现 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Pattern 与布局测试 | `test/unittest/core/pattern/relative_container/` | 锚定、依赖图、测量、辅助线、屏障、链、偏置和布局回归 |
| Static modifier 测试 | `test/unittest/capi/modifiers/relative_container_modifier_test.cpp` | Static generated modifier 的属性转换入口回归 |
| Native option / accessor 测试 | `test/unittest/interfaces/native_node_test.cpp`、`test/unittest/capi/accessors/frame_node_extended_accessor_test.cpp`、`test/unittest/interfaces/native_node_napi_test.cpp` | guideline、barrier、alignment rule option、Native 节点类型和扩展访问入口回归 |
| Context registry | `docs/context_registry.json` | RelativeContainer 的 KB、Spec、源码、API 和测试统一路由 |

### 相关 Spec

RelativeContainer 功能域：`specs/05-ui-components/01-layout-components/08-relative-container/`（功能 ID `05-01-08`）。

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | 锚定与自适应尺寸 | `Feat-01-relative-container-anchor-auto-size-spec.md` |
| Feat-02 | 依赖图、循环检测与偏置 | `Feat-02-relative-container-dependency-bias-spec.md` |
| Feat-03 | 辅助线、屏障与 RTL | `Feat-03-relative-container-guideline-barrier-spec.md` |
| Feat-04 | 链式布局与权重 | `Feat-04-relative-container-chain-weight-spec.md` |
| Feat-05 | 多范式与原生接口兼容 | `Feat-05-relative-container-multi-paradigm-native-spec.md` |

架构决策和模块边界见同目录 `design.md`。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 子项未按锚点定位 | Common API、Common Bridge / Static Common modifier、子项 LayoutProperty 和 Feat-01 |
| 兄弟依赖顺序或循环异常 | RelativeContainer Pattern、布局算法、依赖图测试和 Feat-02 |
| guideline 或 barrier 未生效 | 组件 SDK、统一 Bridge、ModelNG、LayoutProperty 和 Feat-03 |
| RTL 下 START/END 方向异常 | localized API 类型、布局算法和 Feat-03 |
| chainMode 或 chainWeight 不生效 | Common 属性解析、FlexItemProperty、布局算法和 Feat-04 |
| ArkTS 与 Native Node 能力不一致 | `native_node.h`、`node_attributes/layout.h`、`style_modifier.cpp` 和 Feat-05 |
| 动态模块加载失败 | DynamicModuleHelper 映射、relative_container BUILD、Dynamic Module 和 node modifier 委托 |

## 调试入口

- 创建与容器属性从对应范式前端进入统一 Bridge，再检查 Dynamic/Static modifier 和 ModelNG。
- 子项锚定属性从 Common API 跟踪到 Common Bridge 或 Static Common modifier，再确认 LayoutProperty 中的相对布局数据。
- 布局问题同时检查子项 ID、有效锚点集合、拓扑结果、循环节点、guideline/barrier 和父约束。
- Native 场景分别核对节点属性枚举、option 生命周期和 style modifier 分发。
- 回归优先运行 `test/unittest/core/pattern/relative_container/` 的 feature、layout 和 measure 用例。

## 相关主题

- [Layout Framework：[docs/kb/architecture/layout-framework.md](../../architecture/layout-framework.md)](../../architecture/layout-framework.md)
- [Layout Attributes：[docs/kb/capabilities/layout-attributes.md](../../capabilities/layout-attributes.md)](../../capabilities/layout-attributes.md)
- [Row：[docs/kb/components/container/row.md](row.md)](row.md)
- [Column：[docs/kb/components/container/column.md](column.md)](column.md)