# ContextMenu Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `ContextMenu`

## 定位

ArkUI ContextMenu 提供上下文菜单交互能力，基于 MenuPattern 实现。通过 `bindContextMenu` / `bindMenu` 属性挂载到组件。MenuManager 管理菜单的显示/隐藏/子菜单展开。支持 MenuItem/MenuItemGroup/MenuDivider 子组件。

本文档用于快速定位 ContextMenu 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| menu_pattern | `frameworks/core/components_ng/pattern/menu/menu_pattern.cpp` | |
| menu_model_ng | `frameworks/core/components_ng/pattern/menu/menu_model_ng.cpp` | |
| menu_model_static | `frameworks/core/components_ng/pattern/menu/menu_model_static.cpp` | |
| menu_layout_algorithm | `frameworks/core/components_ng/pattern/menu/menu_layout_algorithm.cpp` | |
| multi_menu_layout_algorithm | `frameworks/core/components_ng/pattern/menu/multi_menu_layout_algorithm.cpp` | |
| sub_menu_layout_algorithm | `frameworks/core/components_ng/pattern/menu/sub_menu_layout_algorithm.cpp` | |
| menu_layout_property | `frameworks/core/components_ng/pattern/menu/menu_layout_property.cpp` | |
| menu_paint_method | `frameworks/core/components_ng/pattern/menu/menu_paint_method.cpp` | |
| menu_view | `frameworks/core/components_ng/pattern/menu/menu_view.cpp` | |
| menu_manager | `frameworks/core/components_ng/pattern/menu/menu_manager.cpp` | |
| menu_item_pattern | `frameworks/core/components_ng/pattern/menu/menu_item/menu_item_pattern.cpp` | |
| menu_item_model_ng | `frameworks/core/components_ng/pattern/menu/menu_item/menu_item_model_ng.cpp` | |
| menu_wrapper_pattern | `frameworks/core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.cpp` | |
| bridge | `frameworks/core/components_ng/pattern/menu/bridge/menu/arkts_native_menu_bridge.cpp` | |
| dynamic_module | `frameworks/core/components_ng/pattern/menu/bridge/menu/menu_dynamic_module.cpp` | |
| static_modifier | `frameworks/core/components_ng/pattern/menu/bridge/menu/menu_static_modifier.cpp` | |
| dynamic_modifier | `frameworks/core/components_ng/pattern/menu/bridge/menu/menu_dynamic_modifier.cpp` | |
| context_menu_accessor | `frameworks/core/interfaces/native/implementation/context_menu_accessor.cpp` | |
| js_context_menu | `frameworks/bridge/declarative_frontend/jsview/menu/js_context_menu.cpp` | |
| js_view_abstract | `frameworks/bridge/declarative_frontend/jsview/js_view_abstract.cpp` | |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| context_menu | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/context_menu.d.ts` | |
| menu | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/menu.d.ts` | |
| menu_item | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/menu_item.d.ts` | |
| menu_item_group | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/menu_item_group.d.ts` | |

### 测试入口

| 稳定路径 | 用途 |
|----------|------|
| test/unittest/core/pattern/menu/ | |
| test/unittest/capi/modifiers/menu_modifier_test.cpp | |
| test/unittest/capi/modifiers/menu_item_modifier_test.cpp | |

### API 解析实现路径

ContextMenu 基于 MenuPattern 实现，通过 bindContextMenu/bindMenu 属性挂载。已完成组件化改造。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 声明式前端 | `frameworks/bridge/declarative_frontend/jsview/menu/js_context_menu.cpp` | JS ContextMenu 组件 |
| 统一 Bridge | `frameworks/core/components_ng/pattern/menu/bridge/menu/arkts_native_menu_bridge.cpp` | 通过 `IsJsView()` 区分模式 |
| Dynamic Module | `frameworks/core/components_ng/pattern/menu/bridge/menu/menu_dynamic_module.cpp` | 动态模块入口 |
| C API | `frameworks/core/interfaces/native/implementation/context_menu_accessor.cpp` | ContextMenu C API accessor |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| 功能域 | `specs/05-ui-components/06-popup-components/09-context-menu/` | ContextMenu 上下文菜单接口，基于 MenuPattern/MenuManager，支持 bindMenu/bindContextMenu 挂载。 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 菜单不显示 | 确认 OverlayManager 的 Menu 创建和 MenuWrapperPattern 初始化 |
| 子菜单展开异常 | 检查 SubMenuLayoutAlgorithm 的布局计算 |
| 菜单项点击无响应 | 查看 MenuItemPattern 的事件处理和 MenuWrapperPattern 的事件拦截 |

## 调试入口

- 创建链路：bindContextMenu → OverlayManager → MenuPattern → MenuWrapperPattern
- 布局链路：MultiMenuLayoutAlgorithm / SubMenuLayoutAlgorithm
- C API 链路：context_menu_accessor.cpp

## 相关主题

- Menu 菜单组件
- Select 选择器组件
- 弹窗类属性
