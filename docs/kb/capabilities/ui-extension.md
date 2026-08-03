# UIExtension 机制 Context

> 文档版本：v1.0
> 更新时间：2026-07-31
> 来源：`docs/context_registry.json` 主题 `UIExtension`

## 定位

UIExtension 机制是 ArkUI 跨进程组件的共享基础设施层，为 `UIExtensionComponent`、`IsolatedComponent`、`SecurityUIExtensionComponent`、`DynamicComponent` 等嵌入显示组件提供共用的 Pattern、Manager、Session Wrapper、Surface Proxy 与无障碍适配链路。本功能域关注：机制层的统一调度、会话管理、Platform 适配与跨进程无障碍子树回调，不涉及各组件自身的属性语义（属 `05-12-03/04/05/06/07`）。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| UIExtensionManager | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_manager.h`、`ui_extension_manager.cpp` | 嵌入显示统一管理器；负责 Ability 连接、生命周期、子树注册 |
| UIExtensionModel / ModelNG | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_model.h`、`ui_extension_model_ng.h`、`ui_extension_model_ng.cpp` | 嵌入显示模型基类与 NG 实现 |
| UIExtensionSurfacePattern | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_surface_pattern.h` | 嵌入显示 Surface Pattern（纹理/Surface 绑定） |
| UIExtensionLayoutAlgorithm | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_layout_algorithm.h` | 嵌入显示布局算法 |
| UIExtensionHub | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_hub.h` | 嵌入显示 Hub（子树/会话路由入口） |
| UIExtensionConfig | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_config.h` | 嵌入显示配置 |
| UIExtensionContainerHandler | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_container_handler.h`、`ui_extension_container_handler.cpp` | 容器 Handler（容器级事件/布局协调） |
| Session Wrapper | `frameworks/core/components_ng/pattern/ui_extension/session_wrapper.h`、`session_wrapper_factory.h`、`session_wrapper_factory.cpp` | 跨进程会话抽象与工厂 |
| PlatformPattern / PlatformUtils | `frameworks/core/components_ng/pattern/ui_extension/platform_pattern.h`、`platform_pattern.cpp`、`platform_utils.h`、`platform_utils.cpp` | 平台侧 Pattern 与工具 |
| PlatformEventProxy | `frameworks/core/components_ng/pattern/ui_extension/platform_event_proxy.h`、`platform_event_proxy.cpp` | 平台事件代理 |
| PlatformContainerHandler | `frameworks/core/components_ng/pattern/ui_extension/platform_container_handler.h`、`platform_container_handler.cpp` | 平台容器 Handler |
| SurfaceProxyNode | `frameworks/core/components_ng/pattern/ui_extension/surface_proxy_node.h`、`surface_proxy_node.cpp` | Surface 代理节点（嵌入显示表面映射） |
| 无障碍适配基类与子树回调 | `frameworks/core/components_ng/pattern/ui_extension/platform_accessibility_base.h`、`platform_accessibility_child_tree_callback.h` | Platform 层无障碍基类与子树回调接口 |
| AccessibilitySessionAdapter (UIExtension) | `frameworks/core/components_ng/pattern/ui_extension/accessibility_session_adapter_ui_extension.h`、`accessibility_session_adapter_ui_extension.cpp` | UIExtensionComponent 的无障碍会话适配 |
| AccessibilitySessionAdapter (Isolated) | `frameworks/core/components_ng/pattern/ui_extension/accessibility_session_adapter_isolated_component.h`、`accessibility_session_adapter_isolated_component.cpp` | IsolatedComponent 的无障碍会话适配 |
| JSView（声明式） | `frameworks/bridge/declarative_frontend/jsview/js_ui_extension.cpp`、`js_ui_extension.h` | UIExtension 组件 JSView 入口 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic UIExtensionComponent API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/ui_extension_component.d.ts` | UIExtensionComponent 组件声明（属 05-12-03） |
| Static UIExtensionComponent API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/ui_extension_component.static.d.ets` | 静态编译路径 |
| Dynamic IsolatedComponent API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/isolated_component.d.ts` | IsolatedComponent 组件声明（属 05-12-05） |
| Dynamic SecurityUIExtensionComponent API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/security_ui_extension_component.d.ts` | SecurityUIExtensionComponent 组件声明（属 05-12-06） |
| Dynamic DynamicComponent API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/dynamic_component.d.ts` | DynamicComponent 组件声明（属 05-12-07） |

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件/目标路径 | 说明 |
|----------|----------|------------|----------------------------|------|
| Session / Window | `session_wrapper_factory.cpp`、`surface_proxy_node.*` | `<OH_ROOT>/foundation/window/window_manager` | `interfaces/innerkits/include/` | 跨进程会话通道与窗口 Surface 绑定 |
| Ability Manager | `ui_extension_manager.*`（Want 拉起 UIExtension Ability） | `<OH_ROOT>/foundation/arkui/appexecfwk_standard` | `interfaces/innerkits/include/` | UIExtension Ability 连接与生命周期 |
| 无障碍服务桥接 | `accessibility_session_adapter_ui_extension.*`、`accessibility_session_adapter_isolated_component.*` | `<OH_ROOT>/foundation/barrierfree/accessibility` | `interfaces/innerkits/include/` | 跨进程组件无障碍子树回调与会话传递 |
| SDK 声明入口 | 应用侧声明式 API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/*.d.ts` | — | 各嵌入显示组件的公开属性声明 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| UIExtension 机制单测 | `test/unittest/core/pattern/ui_extension/ui_extension_component/` | UIExtension Pattern、Node、Proxy 与 Manager 回归 |
| Accessibility 适配单测 | `test/unittest/core/pattern/ui_extension/accessibility_session_adapter_ui_extension_test_ng.cpp`、`accessibility_session_adapter_isolated_component_test_ng.cpp` | 无障碍会话适配回归 |
| Platform 机制单测 | `test/unittest/core/pattern/ui_extension/platform_pattern_test_ng.cpp`、`platform_event_proxy_test.cpp` | Platform Pattern 与事件代理回归 |
| Surface Proxy 单测 | `test/unittest/core/pattern/ui_extension/surface_proxy_node_test_ng.cpp` | SurfaceProxyNode 回归 |
| SessionWrapper 单测 | `test/unittest/core/pattern/ui_extension/session_wrapper_impl_test_ng.cpp`、`session_wrapper_impl_test_new_ng.cpp` | SessionWrapper 实现回归 |
| Modal UIExtension Proxy 单测 | `test/unittest/core/pattern/ui_extension/modal_ui_extension_proxy_impl_test_ng.cpp` | Modal UIExtensionProxy 实现回归 |
| Preview SessionWrapper 单测 | `test/unittest/core/pattern/ui_extension/preview_session_wrapper_impl_test_ng.cpp` | Preview 形态 SessionWrapper 回归 |
| Isolated Pattern 单测 | `test/unittest/core/pattern/ui_extension/isolated_pattern_test_ng.cpp` | IsolatedComponent Pattern 回归 |
| Mock | `test/unittest/core/pattern/ui_extension/mock/` | 多个 mock 文件支撑单元测试 |

### 相关 Spec

UIExtension 机制功能域：`specs/04-common-capability/17-embedded-display/01-ui-extension/`（功能 ID `04-17-01`，`design.md` + Feat-01~03 规格已创建，spec_status `active`）。

`design.md` 与多个 Feat 规格已存在，行为结论以 Spec、源码、SDK 声明和测试为事实源。

组件侧关联功能域：

- UIExtensionComponent（`05-12-03`）：`docs/kb/components/container/ui_extension_component.md`
- PluginComponent（`05-12-01`）：`docs/kb/components/container/plugin_component.md`
- DynamicComponent（`05-12-07`）：`docs/kb/components/container/dynamic_component.md`

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| UIExtension 子树未显示/连接失败 | `UIExtensionManager` Ability 连接链路、`SessionWrapperFactory` 创建、`SurfaceProxyNode` 映射 |
| 跨进程触摸/手势不传递 | `PlatformEventProxy`、`PlatformContainerHandler`、UIExtension Surface 链路 |
| 嵌入子组件无障碍未桥接 | `PlatformAccessibilityChildTreeCallback`、`AccessibilitySessionAdapter*` 对应组件适配器 |
| Session 通道建立失败 | `SessionWrapper::Create/Open/Close`、`SessionWrapperFactory`、对应 `Adapter` |
| 平台事件代理未触发 | `PlatformEventProxy::OnEvent`、订阅链路 |

## 调试入口

- Ability 连接断点：`UIExtensionManager::ConnectAbility`
- 会话通道断点：`SessionWrapperFactory::CreateSessionWrapper`
- Surface 代理断点：`SurfaceProxyNode::BindSurface`、`SurfaceProxyNode::OnSurfaceAvailable`
- 无障碍桥接断点：`AccessibilitySessionAdapterUIExtension::Init`、`PlatformAccessibilityChildTreeCallback::OnChildAdded`

## 相关主题

- 嵌入显示子组件：
  - `docs/kb/components/container/ui_extension_component.md`（`05-12-03` UIExtensionComponent）
  - `docs/kb/components/container/isolated_component.md`（`05-12-05` IsolatedComponent）
  - `docs/kb/components/container/security_ui_extension_component.md`（`05-12-06` SecurityUIExtensionComponent）
  - `docs/kb/components/container/dynamic_component.md`（`05-12-07` DynamicComponent）
- IsolateComponent 机制（`04-17-02`）：`docs/kb/capabilities/isolate-component.md`
- 通用无障碍属性（`04-03-09`）：`docs/kb/capabilities/accessibility-attributes.md`
