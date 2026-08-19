# SecurityUIExtensionComponent Context

> 文档版本：v1.0
> 更新时间：2026-07-20
> 来源：`docs/context_registry.json` 主题 `SecurityUIExtensionComponent`

## 定位

SecurityUIExtensionComponent 是 ArkUI 的安全 UIExtension 容器，用于嵌入安全场景的 UIExtension Ability（如认证、密码输入等），通过独立 SessionWrapper 实现与宿主页面的安全隔离渲染。SecurityUIExtensionComponent 有独立 `SecurityUIExtensionPattern`，与 UIExtension 家族共享 Manager 和 Platform 基础设施。

本文档用于快速定位 SecurityUIExtensionComponent 的源码、SDK、API 解析、测试和 Spec。具体属性语义、版本约束、默认值和边界条件应回到当前 SDK 声明、源码、测试与 Spec 核实。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern | `frameworks/core/components_ng/pattern/ui_extension/security_ui_extension_component/security_ui_extension_pattern.h`、`security_ui_extension_pattern.cpp` | Security UIExtension Pattern 独立类 |
| Proxy | `frameworks/core/components_ng/pattern/ui_extension/security_ui_extension_component/security_ui_extension_proxy.h`、`security_ui_extension_proxy.cpp` | Security Proxy 实现，转发安全场景回调 |
| Model（Static） | `frameworks/core/components_ng/pattern/ui_extension/security_ui_extension_component/security_ui_extension_model_static.h`、`security_ui_extension_model_static.cpp` | Static CreateFrameNode 入口 |
| Session Wrapper | `frameworks/core/components_ng/pattern/ui_extension/security_ui_extension_component/security_session_wrapper_impl.h`、`security_session_wrapper_impl.cpp` | Security 专属 SessionWrapper 实现 |
| Manager | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_manager.h`、`ui_extension_manager.cpp` | UIExtension 家族共享的会话管理器 |
| Platform Pattern | `frameworks/core/components_ng/pattern/ui_extension/platform_pattern.h`、`platform_pattern.cpp` | UIExtension 家族共享的 Platform 适配层 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/security_ui_extension_component.d.ts` | `SecurityUIExtensionComponentInterface`、`SecurityUIExtensionComponentAttribute` |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/security_ui_extension_component.static.d.ets` | Static SecurityUIExtensionComponent 声明（若已发布） |
| Modifier API（Dynamic） | `<OH_ROOT>/interface/sdk-js/api/arkui/SecurityUIExtensionComponentModifier.d.ts` | Dynamic Modifier 声明 |
| Modifier API（Static） | `<OH_ROOT>/interface/sdk-js/api/arkui/SecurityUIExtensionComponentModifier.static.d.ets` | Static Modifier 声明 |
| Native Node C API | `interfaces/native/native_node.h` | 当前 SecurityUIExtensionComponent 无专属 ARKUI_NODE 枚举 |

### API 解析实现路径

SecurityUIExtensionComponent **尚未完成组件化改造**：`pattern/ui_extension/security_ui_extension_component/` 下没有 `bridge/` 子目录，`DynamicModuleHelper` 无映射，JSView 路径仍在使用；当前没有独立 `libarkui_security_ui_extension.z.so`。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| JSView（声明式组件） | `frameworks/bridge/declarative_frontend/jsview/js_security_ui_extension.cpp` | 解析 Want、回调等属性，经 Model 写入 |
| Static Model | `security_ui_extension_component/security_ui_extension_model_static.cpp` | Static 前端路径 |

SecurityUIExtensionComponent 暂无独立的 ArkTS Bridge 文件和 node_modifier 文件；属性解析主要通过 JSView 和 Model 路径完成。


### 外部依赖入口

与 UIExtensionComponent 共享 Session / Window、Ability Manager 和 Accessibility 依赖。额外安全场景依赖：

| 依赖方向 | 本仓入口 | 外部仓路径 | 说明 |
|----------|----------|-----------|------|
| 安全 Session | `security_session_wrapper_impl.cpp` | `window_manager` / `ability_manager` | Security SessionWrapper 可能有额外的安全隔离策略 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Security Pattern 单元测试 | `test/unittest/core/pattern/ui_extension/security_ui_extension_component_test.cpp` | SecurityUIExtensionPattern 回归 |
| Security Session Wrapper 测试 | `test/unittest/core/pattern/ui_extension/security_session_wrapper_impl_test_ng.cpp` | Security SessionWrapper 回归 |
| UIExtension 家族共享测试 | `test/unittest/core/pattern/ui_extension/` | Platform、Surface、Session 等共享基础设施回归 |
| Context registry | `docs/context_registry.json` | SecurityUIExtensionComponent 的 KB、Spec、源码、API 和测试统一路由 |

### 相关 Spec

SecurityUIExtensionComponent 功能域：`specs/05-ui-components/12-embedded-display-components/06-security-ui-extension-component/`（功能 ID `05-12-06`）。

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | Security UIExtension 创建与代理 | `Feat-01-security-creation-proxy-spec.md` |
| Feat-02 | Security UIExtension 事件 | `Feat-02-security-events-spec.md` |

架构决策和模块边界见同目录 `design.md`。行为结论以对应 Feat、当前 SDK、源码和测试的交叉证据为准。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| Security UIExtension 无法拉起 | `security_ui_extension_pattern.cpp` 生命周期、Security SessionWrapper 状态、Want 参数、Feat-01 |
| 安全隔离渲染异常 | `security_session_wrapper_impl.cpp`、Surface 连接状态 |
| 事件回调未触发 | `security_ui_extension_proxy.cpp`、JSView 事件注册、Feat-02 |
| Static 构造异常 | `security_ui_extension_model_static.cpp` |
| Dynamic 与 Static 表现不一致 | 分别核对 JSView/ModelNG 与 ModelStatic |

## 调试入口

- 节点创建：从 ModelNG 确认节点以 `SecurityUIExtensionPattern` 创建。
- 生命周期：从 `SecurityUIExtensionPattern::OnModifyDone` 追踪 Security SessionWrapper 创建。
- 回调转发：从 `security_ui_extension_proxy.cpp` 追踪安全场景回调转发。
- 回归验证：运行 `test/unittest/core/pattern/ui_extension/security_ui_extension_component_test.cpp`，再补充 SessionWrapper 测试。

## 相关主题

- [UIExtensionComponent：`docs/kb/components/container/ui-extension-component.md`](ui-extension-component.md)
- [EmbeddedComponent：`docs/kb/components/container/embedded-component.md`](embedded-component.md)
- [IsolatedComponent：`docs/kb/components/container/isolated-component.md`](isolated-component.md)
- [PluginComponent：`docs/kb/components/container/plugin-component.md`](plugin-component.md)
- [DynamicComponent：`docs/kb/components/container/dynamic-component.md`](dynamic-component.md)