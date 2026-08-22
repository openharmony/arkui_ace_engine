# EmbeddedComponent Context

> 文档版本：v1.0
> 更新时间：2026-07-20
> 来源：`docs/context_registry.json` 主题 `EmbeddedComponent`

## 定位

EmbeddedComponent 是 ArkUI 的嵌入式 UIExtension 容器，允许宿主应用通过 Want 信息拉起外部 Embedded UIExtension Ability 并将其 UI 内容嵌入到宿主页面。EmbeddedComponent 与 UIExtensionComponent 共享 `UIExtensionPattern` 和 `UIExtensionNode`，通过 `SessionType::EMBEDDED_UI_EXTENSION` 区分；无独立 Pattern 类，由 `UIExtensionAdapter::CreateEmbeddedComponent` 等静态工厂方法提供创建和属性设置入口。

本文档用于快速定位 EmbeddedComponent 的源码、SDK、API 解析、测试和 Spec。具体属性语义、版本约束、默认值和边界条件应回到当前 SDK 声明、源码、测试与 Spec 核实。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern（共享） | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_pattern.h`、`ui_extension_pattern.cpp` | UIExtension 与 Embedded 共用的 Pattern；Embedded 通过 `SessionType::EMBEDDED_UI_EXTENSION` 区分 |
| Node（共享） | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_node.h`、`ui_extension_node.cpp` | UIExtensionNode 创建；Embedded 使用 `V2::EMBEDDED_COMPONENT_ETS_TAG` |
| Adapter | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_adapter.h`、`ui_extension_adapter.cpp` | `UIExtensionAdapter::CreateEmbeddedComponent`、`SetEmbeddedComponentWant`、`SetEmbeddedComponentOnError`、`SetEmbeddedComponentOnTerminated` |
| Model（Dynamic） | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_model_ng.h`、`ui_extension_model_ng.cpp` | `UIExtensionModelNG::Create(EmbeddedUIExtensionConfig)` 重载 |
| Model（Static） | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_model_static.h`、`ui_extension_model_static.cpp` | Static 前端：`CreateFrameNode(id, SessionType::EMBEDDED_UI_EXTENSION)` |
| Model 抽象 | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_model.h` | 定义 `EmbeddedUIExtensionConfig` 结构体 |
| Config | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_config.h` | PlaceholderType、UIExtCallbackEventId 等共享配置类型 |

共享基础设施（Manager、SessionWrapper、Hub、LayoutAlgorithm 等）参见 UIExtensionComponent KB。

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/embedded_component.d.ts` | `EmbeddedComponentInterface`、`EmbeddedComponentAttribute` |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/embedded_component.static.d.ets` | Static EmbeddedComponent 声明（若已发布） |
| Modifier API（Dynamic） | `<OH_ROOT>/interface/sdk-js/api/arkui/EmbeddedComponentModifier.d.ts` | Dynamic `EmbeddedComponentModifier` 声明 |
| Modifier API（Static） | `<OH_ROOT>/interface/sdk-js/api/arkui/EmbeddedComponentModifier.static.d.ets` | Static `EmbeddedComponentModifier` 声明 |
| Native Node C API | `interfaces/native/native_node.h` | `ARKUI_NODE_EMBEDDED_COMPONENT`、`NODE_EMBEDDED_COMPONENT_WANT`、`NODE_EMBEDDED_COMPONENT_OPTION` |
| C API Option | `interfaces/native/node/embeddedComponent_option.h`、`embeddedComponent_option.cpp` | `ArkUI_EmbeddedComponentOption` 结构定义 |

### API 解析实现路径

EmbeddedComponent **尚未完成组件化改造**：无独立 Pattern，与 UIExtensionComponent 共享模式族代码；`pattern/ui_extension/ui_extension_component/` 下没有 `bridge/` 子目录；当前没有独立 `libarkui_embedded.z.so`。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| JSView（声明式组件） | `frameworks/bridge/declarative_frontend/jsview/js_embedded_component.cpp` | 解析 Want、onError、onTerminated 等属性，经 `UIExtensionModel::GetInstance()->Create(EmbeddedUIExtensionConfig)` 写入 |
| ArkTS Bridge（动态属性） | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_embedded_component_bridge.cpp` | 解析 EmbeddedComponent 属性并调用 embeddedComponent_modifier |
| 前端 Modifier（ArkTS 侧） | `frameworks/bridge/declarative_frontend/ark_modifier/src/embedded_component_modifier.ts` | Dynamic `EmbeddedComponentModifier` 引擎实现入口 |
| node_modifier 层 | `frameworks/core/interfaces/native/node/embeddedComponent_modifier.cpp`、`embeddedComponent_modifier.h` | Want、Option（onError+onTerminated）等属性的 Set/Reset/Get |
| Static generated modifier | `frameworks/core/interfaces/native/implementation/embedded_component_modifier.cpp` | Static 构造参数委托到 `UIExtensionStatic::CreateFrameNode(id, EMBEDDED_UI_EXTENSION)`；当前部分属性标注 "not supported" stub |
| C API Option | `interfaces/native/node/embeddedComponent_option.cpp`、`embeddedComponent_option.h` | C API 层的 Want 和 Option 定义 |


### 外部依赖入口

与 UIExtensionComponent 共享 Session / Window 和 Ability Manager 依赖，参见 UIExtensionComponent KB 外部依赖入口。

### 测试入口

EmbeddedComponent 当前没有专属测试目录。可借助 UIExtension 家族共享测试覆盖部分场景。

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| UIExtension 家族共享测试 | `test/unittest/core/pattern/ui_extension/` | Platform、Surface、Accessibility、Session 等共享基础设施回归 |
| Context registry | `docs/context_registry.json` | EmbeddedComponent 的 KB、Spec、源码、API 和测试统一路由 |

### 相关 Spec

EmbeddedComponent 功能域：`specs/05-ui-components/12-embedded-display-components/04-embedded-component/`（功能 ID `05-12-04`）。

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | Embedded 创建与 DPI | `Feat-01-embedded-creation-dpi-spec.md` |
| Feat-02 | Embedded 事件 | `Feat-02-embedded-events-spec.md` |

架构决策和模块边界见同目录 `design.md`。行为结论以对应 Feat、当前 SDK、源码和测试的交叉证据为准。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| Embedded 无法拉起或显示 | `ui_extension_adapter.cpp` CreateEmbeddedComponent、SessionWrapper 状态、Want 参数、Feat-01 |
| 事件回调未触发 | `ui_extension_adapter.cpp` SetEmbeddedComponentOnError/OnTerminated、JSView/Bridge 事件注册、Feat-02 |
| C API 属性未生效 | `embeddedComponent_modifier.cpp`、`native_node.h` NODE_EMBEDDED_COMPONENT_* 属性枚举 |
| Static 构造异常 | `ui_extension_model_static.cpp` 中 CreateEmbeddedComponent 路径、generated modifier stub 状态 |
| DPI 模式异常 | `EmbeddedUIExtensionConfig.densityDpi`、ModelNG Create 参数、Feat-01 |

## 调试入口

- 节点创建：从 `UIExtensionAdapter::CreateEmbeddedComponent` 或 `UIExtensionModelNG::Create(EmbeddedUIExtensionConfig)` 确认节点以 `UIExtensionPattern(SessionType::EMBEDDED_UI_EXTENSION)` 创建。
- 属性链路：Dynamic 从 JSView 或 ArkTS Bridge 向 embeddedComponent_modifier 追踪；Static 从 generated modifier 向 UIExtensionStatic 追踪。
- C API 链路：按 `NODE_EMBEDDED_COMPONENT_WANT`/`NODE_EMBEDDED_COMPONENT_OPTION` 从 `embeddedComponent_modifier.cpp` 追踪到 Adapter 和 Pattern。
- 回归验证：运行 `test/unittest/core/pattern/ui_extension/ui_extension_component/` 中与 Embedded 相关的测试。

## 相关主题

- [UIExtensionComponent：[docs/kb/components/container/ui-extension-component.md](ui-extension-component.md)](ui-extension-component.md)
- [IsolatedComponent：[docs/kb/components/container/isolated-component.md](isolated-component.md)](isolated-component.md)
- [SecurityUIExtensionComponent：[docs/kb/components/container/security-ui-extension-component.md](security-ui-extension-component.md)](security-ui-extension-component.md)
- [PluginComponent：[docs/kb/components/container/plugin-component.md](plugin-component.md)](plugin-component.md)
- [DynamicComponent：[docs/kb/components/container/dynamic-component.md](dynamic-component.md)](dynamic-component.md)