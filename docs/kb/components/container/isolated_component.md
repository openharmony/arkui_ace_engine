# IsolatedComponent Context

> 文档版本：v1.0
> 更新时间：2026-07-20
> 来源：`docs/context_registry.json` 主题 `IsolatedComponent`

## 定位

IsolatedComponent 是 ArkUI 的隔离式 UIExtension 容器，将外部 Ability 的 UI 内容在独立进程中渲染并通过 Surface 嵌入宿主页面。IsolatedComponent 有独立 `IsolatedPattern`，与 UIExtension 家族共享 Manager、SessionWrapper 工厂和 Platform 基础设施。

本文档用于快速定位 IsolatedComponent 的源码、SDK、API 解析、测试和 Spec。具体属性语义、版本约束、默认值和边界条件应回到当前 SDK 声明、源码、测试与 Spec 核实。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern | `frameworks/core/components_ng/pattern/ui_extension/isolated_component/isolated_pattern.h`、`isolated_pattern.cpp` | IsolatedPattern 独立类，管理隔离进程渲染和 Surface 连接 |
| Model（Dynamic） | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_model_ng.h`、`ui_extension_model_ng.cpp` | Dynamic Create 入口（UIExtension 家族共享） |
| Model（Static） | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_model_static.h`、`ui_extension_model_static.cpp` | Static CreateFrameNode 入口（UIExtension 家族共享） |
| Model 抽象 | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_model.h` | Model 抽象接口（UIExtension 家族共享） |
| Accessibility Adapter | `frameworks/core/components_ng/pattern/ui_extension/accessibility_session_adapter_isolated_component.h`、`accessibility_session_adapter_isolated_component.cpp` | Isolated 无障碍适配 |
| Accessibility 子树回调 | `frameworks/core/components_ng/pattern/ui_extension/platform_accessibility_child_tree_callback.h` | 隔离子树无障碍回调接口 |
| Session Wrapper 工厂 | `frameworks/core/components_ng/pattern/ui_extension/session_wrapper_factory.h`、`session_wrapper_factory.cpp` | 根据 SessionType 创建不同 SessionWrapper 实现 |
| Platform Pattern | `frameworks/core/components_ng/pattern/ui_extension/platform_pattern.h`、`platform_pattern.cpp` | UIExtension 家族共享的 Platform 适配层 |
| Renderer 抽象 | `frameworks/core/common/dynamic_component_renderer.h` | 动态组件渲染接口（`IsolatedPattern` 引用） |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/isolated_component.d.ts` | `IsolatedComponentInterface`、`IsolatedComponentAttribute` |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/isolated_component.static.d.ets` | Static IsolatedComponent 声明（若已发布） |
| Modifier API（Dynamic） | `<OH_ROOT>/interface/sdk-js/api/arkui/IsolatedComponentModifier.d.ts` | Dynamic `IsolatedComponentModifier` 声明 |
| Modifier API（Static） | `<OH_ROOT>/interface/sdk-js/api/arkui/IsolatedComponentModifier.static.d.ets` | Static `IsolatedComponentModifier` 声明 |
| Native Node C API | `interfaces/native/native_node.h` | 当前 IsolatedComponent 无专属 ARKUI_NODE 枚举 |

### API 解析实现路径

IsolatedComponent **尚未完成组件化改造**：`pattern/ui_extension/isolated_component/` 下没有 `bridge/` 子目录，`DynamicModuleHelper` 无映射，JSView 路径仍在使用；当前没有独立 `libarkui_isolated.z.so`。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| JSView（声明式组件） | `frameworks/bridge/declarative_frontend/jsview/js_isolated_component.cpp` | 解析 Want、回调等属性，经 Model 写入 |
| Static Model | `ui_extension_component/ui_extension_model_static.cpp` | Static 前端路径（若支持 Isolated SessionType） |

IsolatedComponent 暂无独立的 ArkTS Bridge 文件和 node_modifier 文件；属性解析主要通过 JSView 和共享 Model 路径完成。

组件化改造参考：`./组件化重构通用方案.md`。改造后 JSView 和 Bridge 双路径将统一到 `pattern/ui_extension/isolated_component/bridge/`，并输出独立 so。

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件/目标路径 | 说明 |
|----------|----------|------------|----------------------------|------|
| Session / Window | `session_wrapper_factory.cpp`、`SurfaceProxyNode` | `<OH_ROOT>/foundation/window/window_manager` | `interfaces/innerkits/include/` | 跨进程会话通道（机制层 `04-17-01` 共用） |
| Ability Manager | `IsolatedPattern::InitializeIsolatedComponent` Want 拉起 Ability | `<OH_ROOT>/foundation/arkui/appexecfwk_standard` | `interfaces/innerkits/include/` | 隔离式 Ability 连接与生命周期 |
| 无障碍服务桥接 | `accessibility_session_adapter_isolated_component.*` | `<OH_ROOT>/foundation/barrierfree/accessibility` | `interfaces/innerkits/include/` | 隔离组件无障碍子树回调与会话传递 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Isolated Pattern 单元测试 | `test/unittest/core/pattern/ui_extension/isolated_pattern_test_ng.cpp` | IsolatedPattern 回归 |
| IsolatedComponent 组件单测 | `test/unittest/core/pattern/ui_extension/isolated_component/` | IsolatedComponent 组件级回归 |
| Accessibility 适配测试 | `test/unittest/core/pattern/ui_extension/accessibility_session_adapter_isolated_component_test_ng.cpp` | Isolated 无障碍适配回归 |
| UIExtension 家族共享测试 | `test/unittest/core/pattern/ui_extension/` | Platform、Surface、Session 等共享基础设施回归 |
| Context registry | `docs/context_registry.json` | IsolatedComponent 的 KB、Spec、源码、API 和测试统一路由 |

### 相关 Spec

IsolatedComponent 功能域：`specs/05-ui-components/12-embedded-display-components/05-isolated-component/`（功能 ID `05-12-05`）。

通用能力域：`specs/04-common-capability/17-embedded-display/02-isolate-component/`（功能 ID `04-17-02`，spec_status `pending`）。

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | IsolatedComponent 规格定义 | `Feat-01-isolated-component-spec.md` |

架构决策和模块边界见同目录 `design.md`。行为结论以对应 Feat、当前 SDK、源码和测试的交叉证据为准。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| Isolated 无法拉起或显示 | `isolated_pattern.cpp` 生命周期、SessionWrapper 状态、Want 参数、Feat-01 |
| 隔离进程渲染异常 | `isolated_pattern.cpp` Surface 连接、`surface_proxy_node.h` |
| 无障碍桥接异常 | `accessibility_session_adapter_isolated_component.h` |
| 事件回调未触发 | JSView 事件注册链路、`platform_event_proxy.cpp` |
| Dynamic 与 Static 表现不一致 | 分别核对 JSView/ModelNG 与 ModelStatic |
| 隔离子树不加载 | `IsolatedPattern::InitializeIsolatedComponent`、`WantWrap` 参数、`UIExtensionManager` 连接 |
| 布局未生效 | `IsolatedPattern::OnDirtyLayoutWrapperSwap`、`SurfaceProxyNode` |
| 上下文挂载/脱离问题 | `IsolatedPattern::OnAttachContext`、`OnDetachContext`、`OnDetachFromFrameNode` |
| 错误回调不触发 | `IsolatedPattern::FireOnErrorCallbackOnUI` |

## 调试入口

- 节点创建：从 ModelNG 或 ModelStatic 确认节点以 `IsolatedPattern` 创建。
- 生命周期：从 `IsolatedPattern::OnModifyDone` 追踪 SessionWrapper 和隔离进程连接。
- 初始化断点：`IsolatedPattern::InitializeIsolatedComponent`。
- 布局断点：`IsolatedPattern::OnDirtyLayoutWrapperSwap`。
- 无障碍桥接断点：`AccessibilitySessionAdapterIsolatedComponent::Init`、`PlatformAccessibilityChildTreeCallback`。
- Dump 断点：`IsolatedPattern::DumpInfo`。
- 无障碍链路：从 `accessibility_session_adapter_isolated_component.h` 追踪跨进程无障碍桥接。
- 回归验证：运行 `test/unittest/core/pattern/ui_extension/isolated_pattern_test_ng.cpp`，再补充 accessibility 测试。

## 相关主题

- UIExtensionComponent：`docs/kb/components/container/ui_extension_component.md`
- EmbeddedComponent：`docs/kb/components/container/embedded_component.md`
- SecurityUIExtensionComponent：`docs/kb/components/container/security_ui_extension_component.md`
- PluginComponent：`docs/kb/components/container/plugin_component.md`
- DynamicComponent：`docs/kb/components/container/dynamic_component.md`
