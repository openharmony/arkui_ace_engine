# DynamicComponent Context

> 文档版本：v1.0
> 更新时间：2026-07-20
> 来源：`docs/context_registry.json` 主题 `DynamicComponent`

## 定位

DynamicComponent 是 ArkUI 的动态组件容器，用于动态加载和渲染外部组件内容。DynamicComponent 有独立 `DynamicPattern`（含 `ArktsDynamicPattern` 派生类）和 `DynamicComponentManager`，与 UIExtension 家族共享 Manager、SessionWrapper 工厂和 Platform 基础设施。

本文档用于快速定位 DynamicComponent 的源码、SDK、API 解析、测试和 Spec。具体属性语义、版本约束、默认值和边界条件应回到当前 SDK 声明、源码、测试与 Spec 核实。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern | `frameworks/core/components_ng/pattern/ui_extension/dynamic_component/dynamic_pattern.h`、`dynamic_pattern.cpp` | DynamicPattern 主类 |
| ArkTS Pattern | `frameworks/core/components_ng/pattern/ui_extension/dynamic_component/arkts_dynamic_pattern.h`、`arkts_dynamic_pattern.cpp` | ArktsDynamicPattern 派生类，ArkTS 动态组件渲染适配 |
| Model | `frameworks/core/components_ng/pattern/ui_extension/dynamic_component/dynamic_model.h`、`dynamic_model.cpp` | DynamicComponent Model |
| Model（Static） | `frameworks/core/components_ng/pattern/ui_extension/dynamic_component/dynamic_model_static.h`、`dynamic_model_static.cpp` | Static CreateFrameNode 入口 |
| Node | `frameworks/core/components_ng/pattern/ui_extension/dynamic_component/dynamic_node.h`、`dynamic_node.cpp` | DynamicNode 创建及结构管理 |
| Component Manager | `frameworks/core/components_ng/pattern/ui_extension/dynamic_component/dynamic_component_manager.h`、`dynamic_component_manager.cpp` | 动态组件管理器，管理多动态组件实例生命周期 |
| Touch Delegate | `frameworks/core/components_ng/pattern/ui_extension/dynamic_component/dynamic_touch_delegate.h`、`dynamic_touch_delegate.cpp` | 动态组件触摸事件委托 |
| Param | `frameworks/core/components_ng/pattern/ui_extension/dynamic_component/dynamic_param.h` | 动态组件参数定义 |
| Manager（共享） | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_manager.h`、`ui_extension_manager.cpp` | UIExtension 家族共享的会话管理器 |
| Platform Pattern（共享） | `frameworks/core/components_ng/pattern/ui_extension/platform_pattern.h`、`platform_pattern.cpp` | UIExtension 家族共享的 Platform 适配层 |
| Layout Modifier | `frameworks/core/interfaces/native/node/dynamic_layout_modifier.h`、`dynamic_layout_modifier.cpp` | 动态布局属性 modifier |
| Renderer 抽象 | `frameworks/core/common/dynamic_component_renderer.h` | 动态组件 Renderer 抽象（被 `DynamicPattern` 持有） |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/dynamic_component.d.ts` | `DynamicComponentInterface`、`DynamicComponentAttribute` |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/dynamic_component.static.d.ets` | Static DynamicComponent 声明（若已发布） |
| Modifier API（Dynamic） | `<OH_ROOT>/interface/sdk-js/api/arkui/DynamicComponentModifier.d.ts` | Dynamic Modifier 声明 |
| Modifier API（Static） | `<OH_ROOT>/interface/sdk-js/api/arkui/DynamicComponentModifier.static.d.ets` | Static Modifier 声明 |
| Native Node C API | `interfaces/native/native_node.h` | 当前 DynamicComponent 无专属 ARKUI_NODE 枚举；布局属性通过 `dynamic_layout_modifier.cpp` 处理 |

### API 解析实现路径

DynamicComponent **尚未完成组件化改造**：`pattern/ui_extension/dynamic_component/` 下没有 `bridge/` 子目录，`DynamicModuleHelper` 无映射，JSView 路径仍在使用；当前没有独立 `libarkui_dynamic.z.so`。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| JSView（声明式组件） | `frameworks/bridge/declarative_frontend/jsview/js_dynamic_component.cpp` | 解析 Want、回调等属性，经 Model 写入 |
| Static Model | `dynamic_component/dynamic_model_static.cpp` | Static 前端路径 |
| Layout Modifier | `frameworks/core/interfaces/native/node/dynamic_layout_modifier.cpp` | 动态组件布局属性的 modifier 层 |

DynamicComponent 暂无独立的 ArkTS Bridge 文件；属性解析主要通过 JSView 和 Model 路径完成。


### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件/目标路径 | 说明 |
|----------|----------|------------|----------------------------|------|
| Session / Window | `DynamicComponentManager`（窗口避障区回调）、`SurfaceProxyNode` | `<OH_ROOT>/foundation/window/window_manager` | `interfaces/innerkits/include/`、`OHOS::Rosen::AvoidArea` | 窗口避障区与尺寸变化回调分发到所有已注册的动态组件（机制层 `04-17-01` 共用） |
| Ability Manager | `DynamicPattern::InitializeDynamicComponent`（Want 拉起 Dynamic Ability） | `<OH_ROOT>/foundation/arkui/appexecfwk_standard` | `interfaces/innerkits/include/` | 动态 Ability 连接与生命周期 |
| 无障碍服务桥接 | `AccessibilitySessionAdapterIsolatedComponent`（动态组件复用） | `<OH_ROOT>/foundation/barrierfree/accessibility` | `interfaces/innerkits/include/` | 动态组件无障碍子树回调与会话传递 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Dynamic Pattern 单元测试 | `test/unittest/core/pattern/ui_extension/dynamic_component/dynamic_pattern_test.cpp`、`dynamic_pattern_test_two.cpp`、`dynamic_pattern_test_three.cpp` | DynamicPattern 回归（多文件覆盖不同场景） |
| ArkTS Dynamic Pattern 测试 | `test/unittest/core/pattern/ui_extension/dynamic_component/arkts_dynamic_pattern_test.cpp` | ArktsDynamicPattern 回归 |
| ArkTS Dynamic Pattern TDD | `test/unittest/core/pattern/ui_extension/dynamic_component/arkts_dynamic_pattern_tdd_test.cpp` | ArkTS Dynamic TDD 回归 |
| Dynamic Component Manager 测试 | `test/unittest/core/pattern/ui_extension/dynamic_component/dynamic_component_manager_test_ng.cpp`、`dynamic_component_manager_tdd_test.cpp` | DynamicComponentManager 回归 |
| UIExtension 家族共享测试 | `test/unittest/core/pattern/ui_extension/` | Platform、Surface、Session 等共享基础设施回归 |
| Mock | `test/unittest/core/pattern/ui_extension/mock/mock_dynamic_component_manager.cpp`、`mock_dynamic_component_renderer_impl.cpp` | Manager 与 Renderer 测试替身 |
| Context registry | `docs/context_registry.json` | DynamicComponent 的 KB、Spec、源码、API 和测试统一路由 |

### 相关 Spec

DynamicComponent 功能域：`specs/05-ui-components/12-embedded-display-components/07-dynamic-component/`（功能 ID `05-12-07`）。

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | DynamicComponent 规格定义 | `Feat-01-dynamic-component-spec.md` |

架构决策和模块边界见同目录 `design.md`。行为结论以对应 Feat、当前 SDK、源码和测试的交叉证据为准。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| DynamicComponent 无法加载或显示 | `dynamic_pattern.cpp` 生命周期、DynamicComponentManager 状态、Want 参数、Feat-01 |
| ArkTS 动态组件渲染异常 | `arkts_dynamic_pattern.cpp`、ArkTS 渲染通道 |
| 动态组件管理器异常 | `dynamic_component_manager.cpp`、多实例生命周期管理 |
| 触摸事件异常 | `dynamic_touch_delegate.cpp`、事件委托转发 |
| 布局属性未生效 | `dynamic_layout_modifier.cpp` |
| 避障区/尺寸变化未响应 | `DynamicComponentManager::OnAvoidAreaChanged`、`OnWindowSizeChanged`、`Rosen::AvoidArea` |
| 节点查找失败 | `DynamicComponentManager::GetRegisteredDynamicNode`、节点注册时机 |
| 状态更新不生效 | `DynamicModel::SetState` / `DynamicModelStatic`（静态编译路径） |

## 调试入口

- 节点创建：从 `DynamicModelNG` 确认节点以 `DynamicPattern` 或 `ArktsDynamicPattern` 创建。
- 生命周期：从 `DynamicPattern::OnModifyDone` 追踪 DynamicComponentManager 初始化和渲染连接。
- 节点注册断点：`DynamicComponentManager::Register` / `Unregister`。
- 初始化断点：`DynamicPattern::InitializeDynamicComponent`、`DynamicPattern::OnAttachToFrameNode`。
- 窗口回调断点：`DynamicComponentManager::OnAvoidAreaChanged`、`OnWindowSizeChanged`。
- 触摸代理断点：`DynamicTouchDelegate::HandleTouchEvent`。
- ArkTS 动态渲染：从 `arkts_dynamic_pattern.cpp` 追踪 ArkTS 动态组件的渲染通道建立。
- 回归验证：运行 `test/unittest/core/pattern/ui_extension/dynamic_component/` 下的所有测试文件。

## 相关主题

- [UIExtensionComponent：[docs/kb/components/container/ui-extension-component.md](ui-extension-component.md)](ui-extension-component.md)
- [EmbeddedComponent：[docs/kb/components/container/embedded-component.md](embedded-component.md)](embedded-component.md)
- [IsolatedComponent：[docs/kb/components/container/isolated-component.md](isolated-component.md)](isolated-component.md)
- [SecurityUIExtensionComponent：[docs/kb/components/container/security-ui-extension-component.md](security-ui-extension-component.md)](security-ui-extension-component.md)
- [PluginComponent：[docs/kb/components/container/plugin-component.md](plugin-component.md)](plugin-component.md)