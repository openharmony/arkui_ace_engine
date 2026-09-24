# Select Context

> 文档版本：v1.1
> 更新时间：2026-07-23
> 来源：`docs/context_registry.json` 主题 `Select`

## 定位

Select 是 ArkUI 选择类组件，提供下拉选择器功能，点击后弹出选项列表供用户选择。Select 已完成组件化改造，输出独立 SO `libarkui_select.z.so`，无遗留 JSView 文件。Select 不暴露为 `ArkUI_NodeType` 节点类型，C API 通过 modifier 委托层提供属性设置。

本文档用于快速定位 Select 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Select Pattern | `frameworks/core/components_ng/pattern/select/select_pattern.cpp` | `SelectPattern`，选择器交互、下拉弹出、选中管理 |
| Select 多线程 | `frameworks/core/components_ng/pattern/select/select_pattern_multi_thread.cpp` | 多线程支持 |
| Select 布局算法 | `frameworks/core/components_ng/pattern/select/select_layout_algorithm.cpp` | `SelectLayoutAlgorithm` |
| Select 布局属性 | `frameworks/core/components_ng/pattern/select/select_layout_property.h` | `SelectLayoutProperty` |
| Select 绘制属性 | `frameworks/core/components_ng/pattern/select/select_paint_property.cpp` | `SelectPaintProperty` |
| Select 属性定义 | `frameworks/core/components_ng/pattern/select/select_properties.h` | `SelectProperties` 数据结构 |
| Select Dynamic Model | `frameworks/core/components_ng/pattern/select/select_model_ng.cpp` | `SelectModelNG`，动态属性写入、节点创建 |
| Select 多线程 Model | `frameworks/core/components_ng/pattern/select/select_model_ng_multi_thread.cpp` | 多线程 Model |
| Select Static Model | `frameworks/core/components_ng/pattern/select/select_model_static.cpp` | `SelectModelStatic`，静态前端属性写入 |
| Select 事件 | `frameworks/core/components_ng/pattern/select/select_event_hub.h` | `SelectEventHub`，onSelect 等事件 |
| Select 无障碍 | `frameworks/core/components_ng/pattern/select/select_accessibility_property.cpp` | `SelectAccessibilityProperty` |
| Select 主题 | `frameworks/core/components_ng/pattern/select/select_theme_wrapper.h` | Select Token 适配 |
| Select Content Overlay | `frameworks/core/components_ng/pattern/select_content_overlay/select_content_overlay_pattern.cpp` | `SelectContentOverlayPattern`，下拉内容覆盖层 |
| Selection Container | `frameworks/core/components_ng/pattern/selection_container/selection_container_pattern.cpp` | `SelectionContainerPattern`，选择容器 |
| Selection Container Controller | `frameworks/core/components_ng/pattern/selection_container/selection_container_controller_holder.h` | 控制器持有 |
| 组件化 Bridge 目录 | `frameworks/core/components_ng/pattern/select/bridge/` | 组件化后的统一 Bridge / DynamicModule 入口 |
| node_modifier 委托层 | `frameworks/core/interfaces/native/node/select_modifier.cpp` | Select C++ 属性委托层 |
| Selection Container node_modifier | `frameworks/core/interfaces/native/node/selection_container_modifier.cpp` | SelectionContainer C++ 属性委托层 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/select.d.ts` | 动态 ArkTS `SelectInterface`、`SelectAttribute` 声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/select.static.d.ets` | 静态 ArkTS Select 组件和属性声明 |
| Modifier API (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/SelectModifier.d.ts` | 动态 Select Modifier 声明 |
| Modifier API (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/SelectModifier.static.d.ets` | 静态 Modifier 声明 |
| SelectionContainer Modifier (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/SelectionContainerModifier.d.ts` | SelectionContainer 动态 Modifier |
| SelectionContainer Modifier (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/SelectionContainerModifier.static.d.ets` | SelectionContainer 静态 Modifier |
| CAPI / NDK | 无独立 NODE 枚举 | Select 使用 modifier-based C API，不走 FrameNode 节点类型枚举 |

API 检索建议：

- 属性声明：在 SDK 文件中搜索 `SelectAttribute` 和具体属性名。
- 构造参数：在 SDK 文件中搜索 `SelectInterface`、`SelectOption`、`SelectOptions`。
- Modifier：在 `SelectModifier*.d.ts` / `SelectModifier*.d.ets` 中确认声明。
- C API：在 `frameworks/core/interfaces/native/node/select_modifier.cpp` 中搜索属性名。

### API 解析实现路径

Select 已完成组件化改造，JSView 文件不存在，Bridge 和动态属性路径统一到 `pattern/select/bridge/`。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 前端 JS/TS 定义 | `frameworks/bridge/declarative_frontend/ark_direct_component/src/arkselect.ts` | 前端组件类；ArkTS Modifier 类见 `frameworks/bridge/declarative_frontend/ark_modifier/src/select_modifier.ts` |
| 统一 Bridge（声明式 + 动态属性） | `frameworks/core/components_ng/pattern/select/bridge/arkts_native_select_bridge.cpp` | 通过 `IsJsView()` 区分模式，统一参数解析 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/select/bridge/select_dynamic_modifier.cpp` | 动态属性路径 |
| Static Modifier | `frameworks/core/components_ng/pattern/select/bridge/select_static_modifier.cpp` | 静态编译路径 |
| Dynamic Module | `frameworks/core/components_ng/pattern/select/bridge/select_dynamic_module.cpp` | `SelectDynamicModule` 派生类，`libarkui_select.z.so` 入口 |
| Model Impl | `frameworks/core/components_ng/pattern/select/bridge/select_model_impl.cpp` | Model 实现桥接 |
| Custom Modifier | `frameworks/core/components_ng/pattern/select/bridge/select_custom_modifier.h` | 自定义 Modifier 声明 |
| Selection Container Bridge | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_selection_container_bridge.cpp` | SelectionContainer 原生模块桥接 |
| node_modifier 委托层 | `frameworks/core/interfaces/native/node/select_modifier.cpp` | 通过 `DynamicModuleHelper` 转发到动态模块 |

独立 SO：`libarkui_select.z.so`。

### 外部依赖入口

外部仓路径以 OpenHarmony 根目录为基准；相对路径列仅记录外部仓内的头文件、目录或 GN 目标。

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 无障碍框架 | `frameworks/core/components_ng/pattern/select/select_accessibility_property.*` | `base/accessibility` | `accessibility:accessibility_common` | Select 无障碍属性上报和操作响应 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/select/` | Select Pattern、Model、布局、事件、控制尺寸等回归测试 |
| Context registry | `docs/context_registry.json` | Select 的 KB、源码、API、测试统一路由 |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| Select 功能域 | `specs/05-ui-components/05-picker-components/05-select/` | Select 规格目录 |
| Feat-01 | `specs/05-ui-components/05-picker-components/05-select/Feat-01-select-full-spec.md` | Select 全量规格 |
| 架构设计 | `specs/05-ui-components/05-picker-components/05-select/design.md` | Select 架构设计文档 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 下拉列表不弹出 | `SelectPattern` 的点击处理；`SelectContentOverlayPattern` 的覆盖层管理 |
| 选中状态不更新 | `SelectModelNG::SetSelected()`；`SelectEventHub` 的 onSelect 回调 |
| 选项内容不显示 | `SelectLayoutAlgorithm` 的布局计算；`SelectPaintProperty` 的绘制属性 |
| 无障碍操作无效 | `SelectAccessibilityProperty` |
| 静态前端属性不生效 | `SelectModelStatic` 的属性写入；`select_static_modifier.cpp` |

## 调试入口

- 创建链路：从 `SelectModelNG::Create()` 确认 Select 节点创建和 Pattern 设置。
- 属性链路：从 SDK 属性名定位 Bridge → node_modifier → Model 写入，再看 `SelectLayoutProperty` / `SelectPaintProperty` 的属性分组。
- 交互链路：从 `SelectPattern` 的点击事件跟踪下拉弹出逻辑。
- 组件化链路：从 `SelectDynamicModule` 跟踪动态模块加载和属性注册。
- 回归验证：优先运行 `test/unittest/core/pattern/select/` 下的定向用例。

## 相关主题

- [Menu 组件（菜单组件，Select 下拉弹出类似菜单交互）](menu.md)
- [Checkbox/CheckboxGroup 组件（选择类组件）](../selector/checkbox.md)