# UIExtensionComponent Context

> 文档版本：v1.0
> 更新时间：2026-07-20
> 来源：`docs/context_registry.json` 主题 `UIExtensionComponent`

## 定位

UIExtensionComponent 是 ArkUI 的 UIExtension 能力嵌入容器，允许宿主应用通过 Want 信息拉起外部 UIExtension Ability 并将其 UI 内容以 Session 通道嵌入到宿主页面。UIExtensionComponent 与 EmbeddedComponent 共享 `UIExtensionPattern` 和 `UIExtensionNode`，通过 `SessionType::UI_EXTENSION_ABILITY` 区分；两者同属 `ui_extension/` 模式族。

本文档用于快速定位 UIExtensionComponent 的源码、SDK、API 解析、测试和 Spec。具体属性语义、版本约束、默认值和边界条件应回到当前 SDK 声明、源码、测试与 Spec 核实。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern（共享） | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_pattern.h`、`ui_extension_pattern.cpp` | UIExtension 与 Embedded 共用的 Pattern；构造参数含 SessionType |
| Node（共享） | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_node.h`、`ui_extension_node.cpp` | UIExtensionNode 创建，通过 ETS TAG 和 SessionType 区分组件类型 |
| Model（Dynamic） | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_model_ng.h`、`ui_extension_model_ng.cpp` | Dynamic Create 入口，含 UIExtensionConfig 与 EmbeddedUIExtensionConfig 两个重载 |
| Model（Static） | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_model_static.h`、`ui_extension_model_static.cpp` | Static CreateFrameNode 入口，通过 SessionType 参数区分 UIExtension 与 Embedded |
| Model 抽象 | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_model.h` | Model 抽象接口，定义 `UIExtensionConfig`、`EmbeddedUIExtensionConfig` 等 |
| Hub | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_hub.h` | UIExtension 事件集线器 |
| Adapter | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_adapter.h`、`ui_extension_adapter.cpp` | 静态工厂方法 `CreateUIExtensionComponent`、`CreateEmbeddedComponent`；属性 Set 方法 |
| Proxy | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_proxy.h`、`ui_extension_proxy.cpp` | UIExtension Proxy 实现，转发远程回调 |
| Manager | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_manager.h`、`ui_extension_manager.cpp` | UIExtension 会话管理器，管理多 Session 生命周期 |
| Session Wrapper | `frameworks/core/components_ng/pattern/ui_extension/session_wrapper.h`、`session_wrapper_factory.cpp` | SessionType 定义、SessionWrapper 工厂，各子组件通过不同 SessionWrapper 实现区分 |
| Container Handler | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_container_handler.h`、`ui_extension_container_handler.cpp` | UIExtension 容器事件和状态处理器 |
| Layout Algorithm | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_layout_algorithm.h` | UIExtension 布局算法 |
| Surface Pattern | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_surface_pattern.h` | Surface 层 Pattern，管理渲染节点与 SurfaceProxyNode |
| Surface Proxy Node | `frameworks/core/components_ng/pattern/ui_extension/surface_proxy_node.h`、`surface_proxy_node.cpp` | 渲染 Surface 代理节点 |

共享基础设施（platform_pattern、platform_container_handler、platform_event_proxy、platform_utils、accessibility_session_adapter）也位于 `ui_extension/` 根目录。

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/ui_extension_component.d.ts` | `UIExtensionComponentInterface`、`UIExtensionComponentAttribute` |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/ui_extension_component.static.d.ets` | Static UIExtensionComponent 声明（若已发布） |
| Modifier API（Dynamic） | `<OH_ROOT>/interface/sdk-js/api/arkui/UIExtensionComponentModifier.d.ts` | Dynamic `UIExtensionComponentModifier` 声明 |
| Modifier API（Static） | `<OH_ROOT>/interface/sdk-js/api/arkui/UIExtensionComponentModifier.static.d.ets` | Static `UIExtensionComponentModifier` 声明 |
| Native Node C API | `interfaces/native/native_node.h` | 当前 UIExtensionComponent 无专属 ARKUI_NODE 枚举 |

### API 解析实现路径

UIExtensionComponent **尚未完成组件化改造**：`pattern/ui_extension/ui_extension_component/` 下没有 `bridge/` 子目录，`DynamicModuleHelper` 无映射，JSView 路径仍在使用；当前没有独立 `libarkui_ui_extension.z.so`。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| JSView（声明式组件） | `frameworks/bridge/declarative_frontend/jsview/js_ui_extension.cpp` | 解析 Want、回调等属性，经 `UIExtensionModel::GetInstance()` 写入 Model |
| Static Model | `ui_extension_component/ui_extension_model_static.cpp` | Static 前端路径：`CreateFrameNode(nodeId, SessionType::UI_EXTENSION_ABILITY)` |

UIExtensionComponent 暂无独立的 ArkTS Bridge 文件和 node_modifier 文件；属性解析主要通过 JSView 和 UIExtensionModelNG/Static 路径完成。

组件化改造参考：`./组件化重构通用方案.md`。改造后 JSView 和 Bridge 双路径将统一到 `pattern/ui_extension/ui_extension_component/bridge/`，并输出独立 so。

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|-----------|-------------------------------|------|
| Session / Window | `session_wrapper.h`、`session_wrapper_factory.cpp` | `<OH_ROOT>/foundation/window/window_manager` | `interfaces/innerkits/include/` | Session 通道创建和窗口渲染表面绑定 |
| Ability Manager | `ui_extension_pattern.cpp` 通过 Want 拉起 UIExtension Ability | `<OH_ROOT>/foundation/arkui/appexecfwk_standard` | `interfaces/innerkits/include/` | UIExtension Ability 连接与生命周期 |
| Accessibility | `accessibility_session_adapter_ui_extension.h` | `<OH_ROOT>/foundation/barrierfree/accessibility` | `interfaces/innerkits/include/` | UIExtension 组件的无障碍桥接 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| UIExtension 组件单元测试 | `test/unittest/core/pattern/ui_extension/ui_extension_component/` | UIExtension Pattern、Node、Proxy 和 Manager 回归 |
| Accessibility 适配测试 | `test/unittest/core/pattern/ui_extension/accessibility_session_adapter_ui_extension_test_ng.cpp` | UIExtension 无障碍适配回归 |
| Platform 适配测试 | `test/unittest/core/pattern/ui_extension/platform_pattern_test_ng.cpp`、`platform_event_proxy_test.cpp` | 平台 Pattern 和事件代理回归 |
| Surface Proxy 测试 | `test/unittest/core/pattern/ui_extension/surface_proxy_node_test_ng.cpp` | SurfaceProxyNode 回归 |
| Session Wrapper 测试 | `test/unittest/core/pattern/ui_extension/session_wrapper_impl_test_ng.cpp`、`session_wrapper_impl_test_new_ng.cpp` | SessionWrapper 实现回归 |
| Mock 基础设施 | `test/unittest/core/pattern/ui_extension/mock/` | 多个 mock 文件支撑单元测试 |
| Context registry | `docs/context_registry.json` | UIExtensionComponent 的 KB、Spec、源码、API 和测试统一路由 |

### 相关 Spec

UIExtensionComponent 功能域：`specs/05-ui-components/12-embedded-display-components/03-ui-extension-component/`（功能 ID `05-12-03`）。

通用能力域：`specs/04-common-capability/17-embedded-display/01-ui-extension/`（功能 ID `04-17-01`，spec_status `pending`）。

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | UIExtension 创建与代理 | `Feat-01-ui-extension-creation-proxy-spec.md` |
| Feat-02 | UIExtension 事件 | `Feat-02-ui-extension-events-spec.md` |
| Feat-03 | UIExtension 弃用兼容 | `Feat-03-ui-extension-deprecated-compat-spec.md` |

架构决策和模块边界见同目录 `design.md`。行为结论以对应 Feat、当前 SDK、源码和测试的交叉证据为准。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| UIExtension 无法拉起或显示 | `ui_extension_pattern.cpp` 生命周期、SessionWrapper 状态、Want 参数、Feat-01 |
| 回调事件未触发 | `ui_extension_proxy.cpp`、`ui_extension_event_hub.h`、JSView 事件注册链路、Feat-02 |
| 尺寸或布局异常 | `ui_extension_layout_algorithm.h`、`surface_proxy_node.h`、`ui_extension_container_handler.cpp` |
| 无障碍桥接异常 | `accessibility_session_adapter_ui_extension.h`、`platform_accessibility_child_tree_callback.h` |
| Dynamic 与 Static 表现不一致 | 分别核对 JSView/ModelNG 与 ModelStatic，再看 Feat |
| Session 断连或重连 | `ui_extension_manager.cpp`、`session_wrapper_factory.cpp`、相关 mock |

## 调试入口

- 节点创建：从 `UIExtensionModelNG::Create(UIExtensionConfig)` 确认节点以 `UIExtensionPattern(SessionType::UI_EXTENSION_ABILITY)` 创建。
- 属性链路：Dynamic 从 JSView 向 ModelNG 追踪；Static 从 `ui_extension_model_static.cpp` 向 Adapter 和 Pattern 追踪。
- 生命周期：从 `UIExtensionPattern::OnModifyDone` 追踪 SessionWrapper 创建和 Session 连接。
- 回调转发：从 `ui_extension_proxy.cpp` 追踪远程回调到本地 EventHandler 的转发链路。
- 回归验证：优先运行 `test/unittest/core/pattern/ui_extension/ui_extension_component/`，再补充 platform、surface、accessibility 测试。

## 相关主题

- EmbeddedComponent：`docs/kb/components/container/embedded_component.md`
- IsolatedComponent：`docs/kb/components/container/isolated_component.md`
- SecurityUIExtensionComponent：`docs/kb/components/container/security_ui_extension_component.md`
- PluginComponent：`docs/kb/components/container/plugin_component.md`
- DynamicComponent：`docs/kb/components/container/dynamic_component.md`
