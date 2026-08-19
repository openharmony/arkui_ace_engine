# PluginComponent Context

> 文档版本：v1.0
> 更新时间：2026-07-20
> 来源：`docs/context_registry.json` 主题 `PluginComponent`

## 定位

PluginComponent 是 ArkUI 的插件嵌入容器，允许宿主应用通过 Want 信息拉起外部 Plugin Ability 并将其 UI 内容嵌入到宿主页面中。与 UIExtensionComponent 系列不同，PluginComponent 走独立的 Plugin 管理通道，有自己的 PluginManager、PluginSubContainer 和 PluginFrontendDelegate。

本文档用于快速定位 PluginComponent 的源码、SDK、API 解析、测试和 Spec。具体属性语义、版本约束、默认值和边界条件应回到当前 SDK 声明、源码、测试与 Spec 核实。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern | `frameworks/core/components_ng/pattern/plugin/plugin_pattern.h`、`plugin_pattern.cpp` | Plugin 节点生命周期、PluginSubContainer 创建与销毁 |
| Model（Dynamic） | `frameworks/core/components_ng/pattern/plugin/plugin_model_ng.h`、`plugin_model_ng.cpp` | Dynamic 属性写入入口 |
| Model（Static） | `frameworks/core/components_ng/pattern/plugin/plugin_model_static.h`、`plugin_model_static.cpp` | Static 构造参数和属性写入入口 |
| Model 抽象 | `frameworks/core/components_ng/pattern/plugin/plugin_model.h` | Plugin 前端与 NG Model 的抽象接口 |
| Node | `frameworks/core/components_ng/pattern/plugin/plugin_node.h`、`plugin_node.cpp` | Plugin 节点创建及结构管理 |
| Layout Property | `frameworks/core/components_ng/pattern/plugin/plugin_layout_property.h` | Plugin 布局属性定义 |
| Event Hub | `frameworks/core/components_ng/pattern/plugin/plugin_event_hub.h` | Plugin 事件（onComplete、onError、onDestroy）集线器 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/plugin_component.d.ts` | `PluginComponentInterface`、`PluginComponentAttribute` |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/plugin_component.static.d.ets` | Static PluginComponent 声明（若已发布） |
| Modifier API（Dynamic） | `<OH_ROOT>/interface/sdk-js/api/arkui/PluginComponentModifier.d.ts` | Dynamic `PluginComponentModifier` 声明 |
| Modifier API（Static） | `<OH_ROOT>/interface/sdk-js/api/arkui/PluginComponentModifier.static.d.ets` | Static `PluginComponentModifier` 声明 |
| Native Node C API | `interfaces/native/native_node.h` | 搜索 `ARKUI_NODE_PLUGIN` 相关枚举（如有）；当前仅 EmbeddedComponent 有 `ARKUI_NODE_EMBEDDED_COMPONENT` |

### API 解析实现路径

PluginComponent **尚未完成组件化改造**：`pattern/plugin/` 下没有 `bridge/` 子目录，`DynamicModuleHelper` 没有 Plugin 动态模块映射，JSView 和旧 ArkTS Bridge 路径仍在使用；当前没有独立的 `libarkui_plugin.z.so`。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| JSView（声明式组件） | `frameworks/bridge/declarative_frontend/jsview/js_plugin.cpp` | 解析 Want、宽高和回调属性，经 `PluginModel::GetInstance()` 写入 Model |
| JSView Model 实现 | `frameworks/bridge/declarative_frontend/jsview/models/plugin_model_impl.cpp` | JSView 声明式路径的 PluginModel 旧实现 |
| ArkTS Bridge（动态属性） | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_plugin_bridge.cpp` | 解析 PluginComponent 属性并调用 plugin_modifier |
| 前端 Modifier（ArkTS 侧） | `frameworks/bridge/declarative_frontend/ark_modifier/src/plugin_component_modifier.ts` | Dynamic `PluginComponentModifier` 引擎实现入口 |
| node_modifier 层 | `frameworks/core/interfaces/native/node/plugin_modifier.cpp`、`plugin_modifier.h` | Want、宽高等属性的 Set/Reset/Get，连接 Bridge 与 ModelNG |
| Static generated modifier | `frameworks/core/interfaces/native/implementation/plugin_component_modifier.cpp` | Static 类型转换、节点构造和属性委托 |


### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|-----------|-------------------------------|------|
| Plugin Ability 管理 | `plugin_pattern.cpp` 中引用 PluginManager / PluginSubContainer | `appexecfwk_standard`（ability_manager） | `interfaces/innerkits/include/` | PluginComponent 通过 AbilityManager 拉起 Plugin Ability |
| Session / Window | `platform_pattern.h`、`platform_container_handler.h` | `window_manager` | `interfaces/innerkits/include/` | UIExtension 家族共享的 Session 和 Window 适配 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Pattern 单元测试 | `test/unittest/core/pattern/plugin/plugin_pattern_test_ng.cpp` | Plugin Pattern 生命周期和属性回归 |
| Node 单元测试 | `test/unittest/core/pattern/plugin/plugin_node_test_ng.cpp` | Plugin 节点创建和结构回归 |
| Plugin Manager 测试 | `test/unittest/core/common/plugin/plugin_manager_test.cpp` | PluginManager 连接和回调回归 |
| C API modifier 测试 | `test/unittest/capi/modifiers/plugin_component_modifier_test.cpp` | Plugin node modifier C API 回归 |
| Context registry | `docs/context_registry.json` | PluginComponent 的 KB、Spec、源码、API 和测试统一路由 |

### 相关 Spec

PluginComponent 功能域：`specs/05-ui-components/12-embedded-display-components/01-plugin-component/`（功能 ID `05-12-01`）。

通用能力域：`specs/04-common-capability/17-embedded-display/04-plugin-component/`（功能 ID `04-17-04`，spec_status `pending`）。

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | PluginComponent 创建与事件 | `Feat-01-plugin-component-creation-events-spec.md` |
| Feat-02 | PluginComponent 管理器 | `Feat-02-plugin-component-manager-spec.md` |

架构决策和模块边界见同目录 `design.md`。行为结论以对应 Feat、当前 SDK、源码和测试的交叉证据为准。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| Plugin 无法拉起或显示 | `plugin_pattern.cpp` 生命周期、PluginManager 连接状态、Want 参数、Feat-01 |
| Plugin 尺寸异常 | `plugin_layout_property.h`、plugin_modifier 宽高属性、ModelNG |
| 事件回调未触发 | `plugin_event_hub.h`、JSView/Bridge 的事件注册链路、Feat-01 |
| Dynamic 与 Static 表现不一致 | 分别核对 ArkTS Bridge/node modifier 与 Static generated modifier，再看 Feat |
| C API 属性未生效 | `plugin_modifier.cpp`、native_node.h 中 Plugin 相关属性枚举 |

## 调试入口

- 节点创建：从 `PluginModelNG` 确认节点以 `PluginPattern` 创建，并检查 PluginSubContainer 是否成功建立。
- 属性链路：Dynamic 从 JSView 或 ArkTS Bridge 向 plugin_modifier 追踪；Static 从 generated modifier 向 ModelStatic 追踪。
- 生命周期：从 `PluginPattern::OnModifyDone` 追踪 PluginManager 的连接和 PluginSubContainer 的初始化。
- Native Node：按 `plugin_modifier.cpp` 属性名追踪 Set/Reset/Get 流向。
- 回归验证：优先运行 `test/unittest/core/pattern/plugin/`，再补充 C API modifier 测试。

## 相关主题

- [UIExtensionComponent：`docs/kb/components/container/ui-extension-component.md`](ui-extension-component.md)
- [EmbeddedComponent：`docs/kb/components/container/embedded-component.md`](embedded-component.md)
- [IsolatedComponent：`docs/kb/components/container/isolated-component.md`](isolated-component.md)
- [SecurityUIExtensionComponent：`docs/kb/components/container/security-ui-extension-component.md`](security-ui-extension-component.md)
- [DynamicComponent：`docs/kb/components/container/dynamic-component.md`](dynamic-component.md)