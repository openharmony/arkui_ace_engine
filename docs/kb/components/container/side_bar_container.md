# SideBarContainer Context

> 文档版本：v1.0
> 更新时间：2026-07-08
> 来源：`docs/context_registry.json` 主题 `SideBarContainer`

## 定位

SideBarContainer 是 ArkUI 的侧边栏容器组件，面向应用侧提供侧边栏显示/隐藏、侧边栏类型（叠加/嵌入）、控制按钮、动画过渡、自动折叠等能力。SideBarContainer 已完成组件化改造，输出独立动态模块 `libarkui_side_bar_container.z.so`。

本文档用于快速定位 SideBarContainer 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern 生命周期、侧边栏切换、动画 | `frameworks/core/components_ng/pattern/side_bar/side_bar_container_pattern.cpp` | SideBarContainer 核心行为实现入口 |
| Pattern 类型和扩展接口 | `frameworks/core/components_ng/pattern/side_bar/side_bar_container_pattern.h` | `SideBarContainerPattern` 类型声明 |
| ArkTS Dynamic Model | `frameworks/core/components_ng/pattern/side_bar/side_bar_container_model_ng.cpp` | 动态前端 SideBarContainer 创建和属性写入 |
| ArkTS Static Model | `frameworks/core/components_ng/pattern/side_bar/side_bar_container_model_static.cpp` | 静态前端 SideBarContainer 属性写入 |
| 布局属性 | `frameworks/core/components_ng/pattern/side_bar/side_bar_container_layout_property.h` | SideBarContainer 布局属性声明 |
| 布局算法 | `frameworks/core/components_ng/pattern/side_bar/side_bar_container_layout_algorithm.cpp` | SideBarContainer 布局计算逻辑 |
| 绘制 | `frameworks/core/components_ng/pattern/side_bar/side_bar_container_paint_method.cpp` | SideBarContainer 绘制逻辑 |
| 事件存储 | `frameworks/core/components_ng/pattern/side_bar/side_bar_container_event_hub.h` | SideBarContainer 事件回调 |
| 主题 | `frameworks/core/components_ng/pattern/side_bar/side_bar_theme.h` | SideBarContainer 主题 |
| 多线程 Pattern 扩展 | `frameworks/core/components_ng/pattern/side_bar/side_bar_container_pattern_multi_thread.cpp` | 多线程场景 Pattern 实现 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/side_bar_container.d.ts` | 动态 ArkTS SideBarContainer 接口声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/side_bar_container.static.d.ets` | 静态 ArkTS SideBarContainer 声明 |
| Modifier API (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/SideBarContainerModifier.d.ts` | 动态 Modifier 声明 |
| Modifier API (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/SideBarContainerModifier.static.d.ets` | 静态 Modifier 声明 |
| CAPI / NDK | 无 | SideBarContainer 当前无独立 C API 节点类型 |

API 检索建议：

- 属性声明：在 SDK 文件中搜索 `SideBarContainerAttribute` 和具体属性名。
- 构造参数：在 SDK 文件中搜索 `SideBarContainerInterface` 或 `SideBarContainer(`。
- Modifier：在 `SideBarContainerModifier*.d.ts` 中确认继承或实现关系。

### API 解析实现路径

SideBarContainer 已完成组件化改造，有 `bridge/` 子目录和独立动态模块。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 统一 Bridge（声明式 + 动态属性） | `frameworks/core/components_ng/pattern/side_bar/bridge/arkts_native_side_bar_container_bridge.cpp` | 通过 `IsJsView()` 区分模式，统一参数解析 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/side_bar/bridge/side_bar_container_dynamic_modifier.cpp` | 动态属性路径 |
| Static Modifier | `frameworks/core/components_ng/pattern/side_bar/bridge/side_bar_container_static_modifier.cpp` | 静态编译路径 |
| Dynamic Module | `frameworks/core/components_ng/pattern/side_bar/bridge/side_bar_container_dynamic_module.cpp` | `DynamicModule` 派生类，`libarkui_side_bar_container.z.so` 入口 |

独立 so 名称：`libarkui_side_bar_container.z.so`。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| SideBarContainer 单元测试 | `test/unittest/core/pattern/side_bar/` | Pattern、Model、Layout、View 测试 |

### 相关 Spec

| ID | 主题 | Spec 路径 | 状态 |
|----|------|-----------|------|
| 05-02-06 | SideBarContainer | `specs/05-ui-components/02-navigation-components/06-sidebar-container/` | active |

Design 文档：`specs/05-ui-components/02-navigation-components/06-sidebar-container/design.md`

| Feat-ID | 标题 | 覆盖范围 | 状态 |
|---------|------|----------|------|
| Feat-01 | 全量规格 | SideBarContainer 创建, SideBarContainerType, showSideBar, controlButton, sideBarWidth, divider, autoHide, onChange, SideBarContainerModifier | Baselined |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 侧边栏显示/隐藏异常 | `side_bar_container_pattern.cpp` 中状态切换逻辑 |
| 侧边栏类型（叠加/嵌入）异常 | `side_bar_container_layout_algorithm.cpp` 中类型布局区分 |
| 动画过渡异常 | `side_bar_container_pattern.cpp` 中动画创建逻辑 |
| 控制按钮样式异常 | `side_bar_container_paint_method.cpp` 中按钮绘制 |
| 自动折叠异常 | `side_bar_container_pattern.cpp` 中折叠策略逻辑 |
| 多线程场景渲染 | `side_bar_container_pattern_multi_thread.cpp` |

## 调试入口

- SideBarContainer 属性搜索：在源码中 grep `SideBarContainerPattern`、`SideBarContainerModel`、`SideBarContainerLayoutProperty`
- 事件关键字：grep `SideBarContainerEventHub`
- 动态模块关键字：grep `SideBarContainerDynamicModule`、`libarkui_side_bar_container`

## 相关主题

- Navigation：SideBarContainer 归属导航组件族，详见 Navigation KB
- 主题：`frameworks/core/components_ng/pattern/side_bar/side_bar_theme.h`
