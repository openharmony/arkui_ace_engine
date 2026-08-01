# IsolateComponent 机制 Context

> 文档版本：v1.0
> 更新时间：2026-07-31
> 来源：`docs/context_registry.json` 主题 `IsolatedComponent` (04-17-02)

## 定位

IsolateComponent 机制是 ArkUI `IsolatedComponent`（隔离式组件）的底层运行框架，基于 UIExtension 机制提供独立子树渲染与生命周期管理。本功能域关注 `IsolatedPattern` 的实现细节、会话适配、容器回调与隔离特性，不重复 UIExtension 机制层（`04-17-01`）与 `IsolatedComponent` 组件定义（`05-12-05`）。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| IsolatedPattern | `frameworks/core/components_ng/pattern/ui_extension/isolated_component/isolated_pattern.h`、`isolated_pattern.cpp` | 隔离式组件 Pattern 实现；继承 `PlatformPattern`、`PlatformContainerHandler`、`PlatformAccessibilityBase` |
| AccessibilitySessionAdapter (Isolated) | `frameworks/core/components_ng/pattern/ui_extension/accessibility_session_adapter_isolated_component.h`、`accessibility_session_adapter_isolated_component.cpp` | 隔离式组件无障碍会话适配器 |
| PlatformAccessibilityChildTreeCallback | `frameworks/core/components_ng/pattern/ui_extension/platform_accessibility_child_tree_callback.h` | 隔离子树无障碍回调接口 |
| PlatformPattern / PlatformUtils | `frameworks/core/components_ng/pattern/ui_extension/platform_pattern.h`、`platform_utils.h` | 平台侧 Pattern 与工具（机制层共用） |
| DynamicComponentRenderer | `frameworks/core/common/dynamic_component_renderer.h` | 动态组件渲染接口（`IsolatedPattern` 引用） |
| JSView（声明式） | `frameworks/bridge/declarative_frontend/jsview/js_isolated_component.cpp`、`js_isolated_component.h` | 隔离式组件 JSView 入口 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic IsolatedComponent API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/isolated_component.d.ts` | 隔离式组件声明（属 05-12-05） |
| Static IsolatedComponent API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/isolated_component.static.d.ets` | 静态编译路径 |

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件/目标路径 | 说明 |
|----------|----------|------------|----------------------------|------|
| Session / Window | `session_wrapper_factory.cpp`、`SurfaceProxyNode` | `<OH_ROOT>/foundation/window/window_manager` | `interfaces/innerkits/include/` | 跨进程会话通道（机制层共用，详见 `04-17-01`） |
| Ability Manager | `IsolatedPattern::InitializeIsolatedComponent` Want 拉起 Ability | `<OH_ROOT>/foundation/arkui/appexecfwk_standard` | `interfaces/innerkits/include/` | 隔离式 Ability 连接与生命周期 |
| 无障碍服务桥接 | `accessibility_session_adapter_isolated_component.*` | `<OH_ROOT>/foundation/barrierfree/accessibility` | `interfaces/innerkits/include/` | 隔离组件无障碍子树回调与会话传递 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| IsolatedPattern 单测 | `test/unittest/core/pattern/ui_extension/isolated_pattern_test_ng.cpp` | `InitializeIsolatedComponent`、布局、生命周期回归 |
| Accessibility 适配单测 | `test/unittest/core/pattern/ui_extension/accessibility_session_adapter_isolated_component_test_ng.cpp` | 无障碍会话适配回归 |
| IsolatedComponent 组件单测 | `test/unittest/core/pattern/ui_extension/isolated_component/` | IsolatedComponent 组件级回归 |

### 相关 Spec

IsolateComponent 机制功能域：`specs/04-common-capability/17-embedded-display/02-isolate-component/`（功能 ID `04-17-02`，`design.md` + Feat-01 规格已创建，spec_status `active`）。

`design.md` 与 Feat 规格已存在，行为结论以 Spec、源码、SDK 声明和测试为事实源。

组件侧关联功能域：

- IsolatedComponent（`05-12-05`）：`docs/kb/components/container/isolated_component.md`

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 隔离子树不加载 | `IsolatedPattern::InitializeIsolatedComponent`、`WantWrap` 参数、`UIExtensionManager` 连接 |
| 布局未生效 | `IsolatedPattern::OnDirtyLayoutWrapperSwap`、`SurfaceProxyNode` |
| 子组件无障碍未桥接 | `PlatformAccessibilityChildTreeCallback::OnChildAdded`、`AccessibilitySessionAdapterIsolatedComponent` |
| 上下文挂载/脱离问题 | `IsolatedPattern::OnAttachContext`、`OnDetachContext`、`OnDetachFromFrameNode` |
| 错误回调不触发 | `IsolatedPattern::FireOnErrorCallbackOnUI` |

## 调试入口

- 初始化断点：`IsolatedPattern::InitializeIsolatedComponent`
- 布局断点：`IsolatedPattern::OnDirtyLayoutWrapperSwap`
- 无障碍桥接断点：`AccessibilitySessionAdapterIsolatedComponent::Init`、`PlatformAccessibilityChildTreeCallback`
- Dump 断点：`IsolatedPattern::DumpInfo`

## 相关主题

- UIExtension 机制（`04-17-01`）：`docs/kb/capabilities/ui-extension.md`
- IsolatedComponent 组件（`05-12-05`）：`docs/kb/components/container/isolated_component.md`
- 通用无障碍属性（`04-03-09`）：`docs/kb/capabilities/accessibility-attributes.md`
