# Flex Context

> 文档版本：v1.0
> 更新时间：2026-07-18
> 来源：`docs/context_registry.json` 主题 `Flex`

## 定位

Flex 是 ArkUI 的弹性布局容器，应用侧通过构造参数配置主轴方向、单行或多行布局、主轴和交叉轴对齐以及轴向间距。Wrap 不是独立公共组件，而是由 `FlexOptions.wrap` 选择的 Flex 多行布局模式；源码中的 `WrapLayoutAlgorithm` 也由 `FlexLayoutPattern` 选择。

本文档用于快速定位 Flex/Wrap 的源码、SDK、API 解析、测试和 Spec。具体属性语义、版本约束、默认值和边界条件应回到当前 SDK 声明、源码、测试与 Spec 核实。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern 与算法选择 | `frameworks/core/components_ng/pattern/flex/flex_layout_pattern.h` | `FlexLayoutPattern` 根据当前模式创建单行 Flex 或 Wrap 布局算法 |
| Dynamic Model | `frameworks/core/components_ng/pattern/flex/flex_model_ng.cpp`、`frameworks/core/components_ng/pattern/flex/flex_model_ng.h` | 节点创建及 Dynamic 路径属性写入入口 |
| Static Model | `frameworks/core/components_ng/pattern/flex/flex_model_ng_static.cpp`、`frameworks/core/components_ng/pattern/flex/flex_model_ng_static.h` | Static 路径的可选属性写入入口 |
| 布局属性 | `frameworks/core/components_ng/pattern/flex/flex_layout_property.h` | Flex 与 Wrap 属性组的存储和布局更新标记 |
| Flex 布局算法 | `frameworks/core/components_ng/pattern/flex/flex_layout_algorithm.cpp`、`frameworks/core/components_ng/pattern/flex/flex_layout_algorithm.h` | 单行弹性布局的 Measure/Layout 入口，也被线性布局算法复用 |
| Wrap 布局算法 | `frameworks/core/components_ng/pattern/flex/wrap_layout_algorithm.cpp`、`frameworks/core/components_ng/pattern/flex/wrap_layout_algorithm.h` | Flex 多行换行模式的 Measure/Layout 入口 |
| 布局枚举与内部样式 | `frameworks/core/components_ng/pattern/flex/flex_layout_styles.h` | Flex/Wrap 布局内部样式类型入口 |
| Flex 子项公共属性 | `frameworks/core/components_ng/property/flex_property.h`、`frameworks/core/components_ng/layout/layout_property.h` | `layoutWeight`、grow/shrink/basis、`alignSelf` 等子项布局属性的引擎入口 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/flex.d.ts` | `FlexInterface`、`FlexOptions`、`FlexSpaceOptions` 与 `FlexAttribute` |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/flex.static.d.ets` | Static Flex 构造、属性和 builder 声明 |
| Modifier API（Static） | `<OH_ROOT>/interface/sdk-js/api/arkui/FlexModifier.static.d.ets` | Static `FlexModifier` 声明 |
| Native Node C API | `interfaces/native/native_node.h` | `ARKUI_NODE_FLEX`、`NODE_FLEX_OPTION` 和 `NODE_FLEX_SPACE` 公共声明 |

当前 SDK 中没有 `api/arkui/FlexModifier.d.ts`，也没有独立的 `wrap.d.ts`、`wrap.static.d.ets` 或 Wrap Modifier。Dynamic 前端存在引擎内部 `flex_modifier.ts`，不能据此推断存在同名公共 Dynamic Modifier SDK 声明。

API 检索建议：

- 构造与换行参数：在 Flex SDK 声明中搜索 `FlexOptions`、`FlexWrap`、`space`。
- Flex 子项属性：在 Common SDK 声明和 Layout Attributes KB 中搜索 `layoutWeight`、`flexGrow`、`flexShrink`、`flexBasis`、`alignSelf`。
- Native Node：在 `interfaces/native/native_node.h` 中搜索 `ARKUI_NODE_FLEX` 和 `NODE_FLEX_`。

### API 解析实现路径

Flex **尚未完成组件化改造**：`pattern/flex/` 下没有 `bridge/` 子目录，`DynamicModuleHelper` 没有 Flex 动态模块映射，JSView 和旧 ArkTS Bridge 路径仍在使用；当前没有独立的 `libarkui_flex.z.so`。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| JSView（声明式组件） | `frameworks/bridge/declarative_frontend/jsview/js_flex_impl.cpp`、`frameworks/bridge/declarative_frontend/jsview/js_flex.cpp` | 解析构造参数和 Wrap 模式，经 `FlexModel::GetInstance()` 写入 Model |
| Dynamic 前端组件 | `frameworks/bridge/declarative_frontend/ark_component/src/ArkFlex.ts` | Dynamic AttributeModifier 的前端组件类和构造参数下发入口 |
| ArkTS Bridge（动态属性） | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_flex_bridge.cpp` | 解析 Flex 初始化参数并调用 Flex node modifier |
| 前端 Modifier（引擎内部） | `frameworks/bridge/declarative_frontend/ark_modifier/src/flex_modifier.ts` | 引擎内部 Dynamic AttributeModifier 类；不等同于缺失的公共 `FlexModifier.d.ts` |
| node_modifier 层 | `frameworks/core/interfaces/native/node/flex_modifier.cpp` | Flex/Wrap 选项和轴向间距的 Set/Reset/Get，连接 Bridge、ModelNG 与 Native Node 框架 |
| Static 前端节点 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/typedNode/ArkFlexNode.ets` | Static Flex 构造参数进入 peer 的入口 |
| Static generated modifier | `frameworks/core/interfaces/native/implementation/flex_modifier.cpp` | Static 类型转换、节点构造和属性委托，落到 `FlexModelNG` / `FlexModelNGStatic` |
| C API（通用 Native Node） | `interfaces/native/node/style_modifier.cpp`、`interfaces/native/native_node.h` | Flex 没有专属 `flex_native_impl.cpp`；公共属性由通用 style modifier 分发到 Flex node modifier |

组件化改造参考：`./组件化重构通用方案.md`。改造后 JSView 和 Bridge 双路径将统一到 `pattern/flex/bridge/`，并输出独立 so。

### 外部依赖入口

Flex 的核心 Model、Pattern 和布局算法未发现组件特有的跨仓依赖，因此不建立组件专属外部依赖表。公共布局调度和渲染同步应转到 Layout Framework；`pointLight` 走 `JSViewAbstract` / `ViewAbstractModelStatic` 的公共渲染属性路径，不属于 Flex 布局算法本身。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Flex/Wrap 单元测试 | `test/unittest/core/pattern/flex/` | Flex 单行布局、Wrap、多行溢出、匹配父约束及布局边界回归 |
| Flex 算法 Mock | `test/mock/frameworks/core/components_ng/pattern/flex/` | 依赖 Flex 布局算法的测试替身 |
| Static generated modifier 测试 | `test/unittest/capi/modifiers/flex_modifier_test.cpp` | Static Flex 构造参数、属性转换及 modifier 委托回归 |
| Native Node 通用测试 | `test/unittest/interfaces/native_node_test.cpp` | `NODE_FLEX_OPTION`、`NODE_FLEX_SPACE` 等公共 Native Node 属性回归 |
| Context registry | `docs/context_registry.json` | Flex 的 KB、Spec、源码、API 和测试统一路由 |

### 相关 Spec

Flex 功能域：`specs/05-ui-components/01-layout-components/05-flex/`（功能 ID `05-01-05`）。

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | Flex 单行弹性布局与轴向对齐 | `Feat-01-flex-single-line-axis-layout-spec.md` |
| Feat-02 | Flex 多行换行与内容对齐 | `Feat-02-flex-wrap-content-alignment-spec.md` |
| Feat-03 | Flex 主轴与交叉轴间距 | `Feat-03-flex-main-cross-space-spec.md` |
| Feat-04 | Flex 多范式接口与版本兼容 | `Feat-04-flex-multi-paradigm-version-spec.md` |
| Feat-05 | Flex PointLight 系统光效 | `Feat-05-flex-point-light-spec.md` |

架构决策和模块边界见同目录 `design.md`。行为结论以对应 Feat、当前 SDK、源码和测试的交叉证据为准。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 找不到独立 Wrap 组件或 API | `FlexOptions.wrap`、`FlexLayoutPattern`、`WrapLayoutAlgorithm`、Feat-02 |
| Flex 构造参数未生效 | 对应范式 SDK、JSView 或 Static typed node、Bridge/generated modifier、`FlexModelNG` |
| 单行方向或对齐异常 | `flex_layout_property.h`、`FlexLayoutAlgorithm`、Feat-01 |
| 多行换行、行内或行间对齐异常 | `WrapLayoutAlgorithm`、Wrap 属性组、Feat-02 |
| 主轴或交叉轴间距异常 | SDK `FlexSpaceOptions`、Flex node modifier、布局属性、Feat-03 |
| 子项 grow/shrink/weight 表现异常 | Layout Attributes KB、`flex_property.h`、`FlexLayoutAlgorithm` |
| Dynamic `FlexModifier.d.ts` 无法定位 | 该公共 SDK 文件当前不存在；核对 `flex.d.ts`，并区分引擎内部 `flex_modifier.ts` |
| PointLight 表现异常 | Dynamic 公共属性入口或 Static generated modifier、ViewAbstract 公共渲染属性、Feat-05 |

## 调试入口

- 模式确认：先从节点 dump 的 Flex 类型信息和 `FlexLayoutPattern` 确认当前走单行还是 Wrap 算法。
- 属性链路：Dynamic 从 `ArkFlex.ts` / JSView 或 ArkTS Bridge 向 node modifier 追踪；Static 从 `ArkFlexNode.ets` 向 generated modifier 和 Static Model 追踪。
- 测量链路：单行问题进入 `FlexLayoutAlgorithm`，换行问题进入 `WrapLayoutAlgorithm`，同时记录父约束和 Flex 子项属性。
- Native Node：按 `NODE_FLEX_` 属性名从 `style_modifier.cpp` 追踪到 `flex_modifier.cpp`。
- 回归验证：优先运行 `test/unittest/core/pattern/flex/` 下对应 Flex 或 Wrap 用例，再补充 modifier / Native Node 定向测试。

## 相关主题

- Column 纵向线性布局：`docs/kb/components/container/column.md`
- Row 横向线性布局：`docs/kb/components/container/row.md`
- 基础布局属性：`docs/kb/capabilities/layout-attributes.md`
- 布局框架：`docs/kb/architecture/layout-framework.md`
- Blank 及其在弹性布局中的路由：`docs/kb/components/basic/blank.md`
