# DynamicComponent 机制 Context

> 文档版本：v1.0
> 更新时间：2026-08-02
> 来源：`docs/context_registry.json` 主题 `DynamicComponentMechanism`

## 定位

DynamicComponent 机制是 ArkUI `DynamicComponent`（动态组件）的底层运行框架，基于 UIExtension 机制（`04-17-01`）提供动态加载子组件的渲染、管理与事件链路。本功能域关注 `DynamicPattern`/`ArkTSDynamicPattern`、`DynamicComponentManager`、`DynamicModel` 的实现细节，不重复 UIExtension 机制层与 `DynamicComponent` 组件定义（`05-12-07`）。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| DynamicPattern | `frameworks/core/components_ng/pattern/ui_extension/dynamic_component/dynamic_pattern.h`、`dynamic_pattern.cpp` | Native 动态组件 Pattern（继承 `PlatformPattern`，管理 Surface / Session） |
| ArkTSDynamicPattern | `frameworks/core/components_ng/pattern/ui_extension/dynamic_component/arkts_dynamic_pattern.h`、`arkts_dynamic_pattern.cpp` | ArkTS 侧的动态组件 Pattern（与 ArkDirect Frontend 的绑定） |
| DynamicComponentManager | `frameworks/core/components_ng/pattern/ui_extension/dynamic_component/dynamic_component_manager.h`、`dynamic_component_manager.cpp` | 动态组件管理器；节点注册/查找、窗口避障区与尺寸变化回调分发 |
| DynamicModel / DynamicModelStatic | `frameworks/core/components_ng/pattern/ui_extension/dynamic_component/dynamic_model.h`、`dynamic_model.cpp`、`dynamic_model_static.h`、`dynamic_model_static.cpp` | 动态组件 Model（属性写入与状态管理，动态 / 静态编译双路径） |
| DynamicNode | `frameworks/core/components_ng/pattern/ui_extension/dynamic_component/dynamic_node.h`、`dynamic_node.cpp` | 动态组件节点（与 FrameNode / PlatformPattern 的协作） |
| DynamicTouchDelegate | `frameworks/core/components_ng/pattern/ui_extension/dynamic_component/dynamic_touch_delegate.h`、`dynamic_touch_delegate.cpp` | 触摸事件代理（手势/触摸链路与 Surface 事件转发） |
| DynamicParam | `frameworks/core/components_ng/pattern/ui_extension/dynamic_component/dynamic_param.h` | 动态组件参数结构体 |
| JSView（声明式） | `frameworks/bridge/declarative_frontend/jsview/js_dynamic_component.cpp`、`js_dynamic_component.h` | DynamicComponent JSView 解析入口 |
| Renderer 抽象 | `frameworks/core/common/dynamic_component_renderer.h` | 动态组件 Renderer 抽象（被 `DynamicPattern` 持有） |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic DynamicComponent API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/dynamic_component.d.ts` | 动态组件组件声明（属 05-12-07） |
| Static DynamicComponent API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/dynamic_component.static.d.ets` | 静态编译路径 |

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件/目标路径 | 说明 |
|----------|----------|------------|----------------------------|------|
| Session / Window | `DynamicComponentManager`（窗口避障区回调）、`SurfaceProxyNode` | `<OH_ROOT>/foundation/window/window_manager` | `interfaces/innerkits/include/`、`OHOS::Rosen::AvoidArea` | 窗口避障区与尺寸变化回调分发到所有已注册的动态组件 |
| Ability Manager | `DynamicPattern::InitializeDynamicComponent`（Want 拉起 Dynamic Ability） | `<OH_ROOT>/foundation/arkui/appexecfwk_standard` | `interfaces/innerkits/include/` | 动态 Ability 连接与生命周期 |
| 无障碍服务桥接 | `AccessibilitySessionAdapterIsolatedComponent`（动态组件复用） | `<OH_ROOT>/foundation/barrierfree/accessibility` | `interfaces/innerkits/include/` | 动态组件无障碍子树回调与会话传递 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| DynamicComponentManager 单测 | `test/unittest/core/pattern/ui_extension/dynamic_component/dynamic_component_manager_test_ng.cpp` | 节点注册/查找、避障区回调回归 |
| DynamicComponentManager TDD 测试 | `test/unittest/core/pattern/ui_extension/dynamic_component/dynamic_component_manager_tdd_test.cpp` | TDD 驱动的 Manager 行为回归 |
| Mock | `test/unittest/core/pattern/ui_extension/mock/mock_dynamic_component_manager.cpp`、`mock_dynamic_component_renderer_impl.cpp` | Manager 与 Renderer 测试替身 |

### 相关 Spec

DynamicComponent 机制功能域：`specs/04-common-capability/17-embedded-display/05-dynamic-component/`（功能 ID `04-17-05`，当前 spec_status `pending`：已在 registry 注册，但目录与 Feat 规格尚未创建）。

组件侧关联功能域：

- DynamicComponent（`05-12-07`）：`docs/kb/components/container/dynamic_component.md`

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 动态子组件不加载 | `DynamicPattern::InitializeDynamicComponent`、`DynamicComponentManager::Register` |
| 避障区/尺寸变化未响应 | `DynamicComponentManager::OnAvoidAreaChanged`、`OnWindowSizeChanged`、`Rosen::AvoidArea` |
| 触摸/手势未传递到子层 | `DynamicTouchDelegate`、`PlatformEventProxy`（机制层 `04-17-01` 共用） |
| 节点查找失败 | `DynamicComponentManager::GetRegisteredDynamicNode`、节点注册时机 |
| 状态更新不生效 | `DynamicModel::SetState` / `DynamicModelStatic`（静态编译路径） |

## 调试入口

- 节点注册断点：`DynamicComponentManager::Register` / `Unregister`
- 初始化断点：`DynamicPattern::InitializeDynamicComponent`、`DynamicPattern::OnAttachToFrameNode`
- 窗口回调断点：`DynamicComponentManager::OnAvoidAreaChanged`、`OnWindowSizeChanged`
- 触摸代理断点：`DynamicTouchDelegate::HandleTouchEvent`

## 相关主题

- UIExtension 机制（`04-17-01`）：`docs/kb/capabilities/ui-extension.md`
- IsolateComponent 机制（`04-17-02`）：`docs/kb/capabilities/isolate-component.md`
- DynamicComponent 组件（`05-12-07`）：`docs/kb/components/container/dynamic_component.md`
- 通用无障碍属性（`04-03-09`）：`docs/kb/capabilities/accessibility-attributes.md`
