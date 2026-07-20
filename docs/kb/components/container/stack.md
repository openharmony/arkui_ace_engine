# Stack Context

> 文档版本：v1.0
> 更新时间：2026-07-18
> 来源：`docs/context_registry.json` 主题 `Stack`

## 定位

Stack 是 ArkUI 的基础叠放布局容器，用于让多个子组件共享同一内容区域，并通过容器对齐或子项布局属性确定各自位置。当前接口还包含子节点加载策略和 PointLight 系统光效入口。

本文档用于快速定位 Stack 的源码、Dynamic/Static SDK、属性解析、Native C API、测试和 Spec。具体行为、默认值、边界条件及版本兼容性以当前 SDK 声明、源码、测试和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern 生命周期与续帧调度 | `frameworks/core/components_ng/pattern/stack/stack_pattern.cpp`、`frameworks/core/components_ng/pattern/stack/stack_pattern.h` | `StackPattern` 及布局完成后的调度入口 |
| 节点创建和属性写入 | `frameworks/core/components_ng/pattern/stack/stack_model_ng.cpp`、`frameworks/core/components_ng/pattern/stack/stack_model_ng.h` | `StackModelNG` 创建 FrameNode，写入对齐和加载属性 |
| 子项定位 | `frameworks/core/components_ng/pattern/stack/stack_layout_algorithm.cpp`、`frameworks/core/components_ng/pattern/stack/stack_layout_algorithm.h` | 对齐、布局方向、子项 gravity 和安全区分支入口 |
| 测量基类 | `frameworks/core/components_ng/layout/box_layout_algorithm.cpp`、`frameworks/core/components_ng/layout/box_layout_algorithm.h` | Stack 复用的 Box 测量入口 |
| 布局属性 | `frameworks/core/components_ng/pattern/stack/stack_layout_property.h` | Stack 专属布局属性及通用 PositionProperty 关联入口 |
| Dynamic 声明式入口 | `frameworks/bridge/declarative_frontend/jsview/js_stack.cpp`、`frameworks/bridge/declarative_frontend/jsview/js_stack.h` | `JSStack` 创建和属性绑定 |
| Dynamic ArkTS Bridge | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_stack_bridge.cpp`、`frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_stack_bridge.h` | Stack 专属动态属性解析入口 |
| ArkTS 前端组件与 Modifier | `frameworks/bridge/declarative_frontend/ark_component/src/ArkStack.ts`、`ark_modifier/src/stack_modifier.ts` | Dynamic AttributeModifier 和属性差量更新入口 |
| node modifier | `frameworks/core/interfaces/native/node/node_stack_modifier.cpp`、`frameworks/core/interfaces/native/node/node_stack_modifier.h` | Stack C++ Set/Reset/Get 入口 |
| Static 前端节点 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/typedNode/ArkStackNode.ets` | Static Stack 构造参数和属性进入 native peer 的入口 |
| Static native 实现 | `frameworks/core/interfaces/native/implementation/stack_modifier.cpp` | Static 构造、属性转换和 PointLight 写入入口 |
| Native 节点映射与属性分发 | `interfaces/native/node/node_model.cpp`、`interfaces/native/node/style_modifier.cpp` | `ARKUI_NODE_STACK` 创建和公开属性分发入口 |
| 组件源集归属 | `frameworks/core/components_ng/pattern/BUILD.gn` | Stack 源码由通用 Pattern 源集聚合 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/stack.d.ts` | `StackInterface`、`StackOptions`、`StackAttribute` |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/stack.static.d.ets` | Static Stack 组件、属性和 Builder 声明 |
| Modifier API (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/StackModifier.d.ts` | Dynamic `StackModifier` 声明 |
| Modifier API (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/StackModifier.static.d.ets` | Static `StackModifier` 声明 |
| Native C API / NDK | `interfaces/native/native_node.h` | `ARKUI_NODE_STACK` 节点类型和 `NODE_STACK_ALIGN_CONTENT` 属性枚举 |

API 检索建议：

- 构造与属性：在 Dynamic/Static SDK 中搜索 `StackInterface`、`StackOptions`、`StackAttribute`。
- 子项加载：搜索 `syncLoad`，再转到 `StackLayoutProperty`、`StackLayoutAlgorithm` 和 `StackPattern`。
- PointLight：搜索 `pointLight`、`PointLightStyle`，并检查 ArkTS 前端组件和 Static native 实现。
- Native C API：在 `native_node.h` 中搜索 `ARKUI_NODE_STACK` 和 `NODE_STACK_`。

### API 解析实现路径

Stack **尚未完成组件化改造**：`pattern/stack/` 下没有组件化 `bridge/`，动态模块映射中没有 Stack，旧 JSView 仍存在，源码由通用 Pattern 源集聚合。因此 Stack 没有统一组件化 Bridge、Dynamic Module 或独立组件 SO。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| JSView（声明式组件） | `frameworks/bridge/declarative_frontend/jsview/js_stack.cpp` | 创建和声明式属性入口，经 `StackModel` 写入 NG Model |
| ArkTS Bridge（动态属性） | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_stack_bridge.cpp` | Stack 专属动态属性经 node modifier 写入 `StackModelNG` |
| 通用 PointLight 路径 | `frameworks/bridge/declarative_frontend/ark_component/src/ArkStack.ts` | PointLight 经通用 native module 写入 RenderContext 相关状态 |
| node_modifier 层 | `frameworks/core/interfaces/native/node/node_stack_modifier.cpp` | 对齐和子节点加载属性的 Set/Reset/Get 实现 |
| Static 前端节点 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/typedNode/ArkStackNode.ets` | Static Stack 构造参数和属性下发入口 |
| Static native 路径 | `frameworks/core/interfaces/native/implementation/stack_modifier.cpp` | Static 构造、Stack options、属性和 PointLight 实现 |
| C API（NDK） | `interfaces/native/node/node_model.cpp`、`interfaces/native/node/style_modifier.cpp` | 创建 `ARKUI_NODE_STACK`，按 `NODE_STACK_*` 公开枚举分发属性 |
| 前端 Modifier（ArkTS 侧） | `frameworks/bridge/declarative_frontend/ark_modifier/src/stack_modifier.ts` | `StackModifier` 的 ArkTS AttributeModifier 入口 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Pattern / Layout 单元测试 | `test/unittest/core/pattern/stack/` | 节点创建、测量、对齐、布局方向、加载和 Pattern 生命周期回归 |
| Static modifier 测试 | `test/unittest/capi/modifiers/stack_modifier_test.cpp` | 生成式 Static modifier 与 PointLight 属性转换回归 |
| Native 节点接口测试 | `test/unittest/interfaces/node_style_modifier_test.cpp`、`test/unittest/interfaces/native_node_test.cpp` | `ARKUI_NODE_STACK` 创建及 Native 属性路径回归 |
| 组件测试样例 | `test/component_test/test_cases/components/common_container/entry/src/main/ets/pages/stack/` | 应用侧 Stack 对齐场景入口 |

### 相关 Spec

Stack 功能域：`specs/05-ui-components/01-layout-components/11-stack/`

| Feat | 主题 | 文件 | 状态 |
|------|------|------|------|
| Feat-01 | Stack 叠放布局、尺寸与对齐 | `Feat-01-stack-overlay-layout-alignment-spec.md` | Baselined |
| Feat-02 | Stack 子节点分帧加载与多范式接口 | `Feat-02-stack-sync-load-multi-paradigm-spec.md` | Baselined |
| Feat-03 | Stack PointLight 系统光效 | `Feat-03-stack-point-light-spec.md` | Baselined |

设计入口：`specs/05-ui-components/01-layout-components/11-stack/design.md`。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 子项叠放位置或 RTL 镜像异常 | `StackLayoutAlgorithm`、`StackLayoutProperty`、Feat-01 |
| 单个子项的对齐覆盖不符合预期 | 子项 `PositionProperty` / layout gravity、`StackLayoutAlgorithm`、Feat-01 |
| 容器尺寸或子项测量异常 | `BoxLayoutAlgorithm`、Stack 布局算法、Pattern 单元测试、Feat-01 |
| `syncLoad` 设置后布局续帧异常 | Dynamic/Static SDK、Stack Bridge、node modifier、`StackPattern`、Feat-02 |
| PointLight 不生效 | SDK `PointLightStyle`、`ArkStack.ts`、Static native modifier、Feat-03 |
| Native 创建或 `alignContent` 属性异常 | `native_node.h`、`node_model.cpp`、`style_modifier.cpp`、Native 接口测试 |
| Dynamic 与 Static 表现需要对照 | 两套 SDK 声明、Dynamic Bridge、Static native modifier、对应 Feat |

## 调试入口

- 创建链路：从 `JSStack` 或 Static modifier 确认 `StackModelNG` 创建的节点和 `StackPattern`。
- 属性链路：按 SDK 属性名定位 ArkTS 前端、Bridge / Static modifier、node modifier 和 Model 写入。
- 测量链路：先检查 `BoxLayoutAlgorithm` 产生的尺寸，再检查 `StackLayoutAlgorithm` 的子项定位。
- Native 链路：从 `ARKUI_NODE_STACK` 和 `NODE_STACK_` 枚举定位 node model 与 style modifier 分发。
- 回归验证：优先运行 `test/unittest/core/pattern/stack/` 和 Stack modifier 定向测试。

## 相关主题

- FolderStack：`docs/kb/components/container/folder_stack.md`
- Layout Framework：`docs/kb/architecture/layout-framework.md`
- Layout Attributes：`docs/kb/capabilities/layout-attributes.md`
- Safe Area：`docs/kb/capabilities/safe-area.md`
