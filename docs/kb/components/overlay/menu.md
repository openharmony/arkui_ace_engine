# Menu Context

> 文档版本：v1.1
> 更新时间：2026-07-23
> 来源：`docs/context_registry.json` 主题 `Menu`

## 定位

Menu 是 ArkUI 弹窗类组件，提供下拉菜单、上下文菜单（bindContextMenu）、子菜单等多种菜单形式，支持普通菜单、选择菜单、导航菜单、桌面菜单等场景。Menu 组件族包含 Menu、MenuItem、MenuItemGroup、MenuDivider、MenuWrapper、MenuPreview 等多个子组件，均位于 `pattern/menu/` 目录下。Menu 已完成组件化改造，输出独立 SO `libarkui_menu.z.so`。

本文档用于快速定位 Menu 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Menu 主菜单 Pattern | `frameworks/core/components_ng/pattern/menu/menu_pattern.cpp` | `MenuPattern` / `InnerMenuPattern`，菜单显示/隐藏、动画、子菜单管理 |
| Menu 布局算法 | `frameworks/core/components_ng/pattern/menu/menu_layout_algorithm.cpp` | `MenuLayoutAlgorithm`，菜单位置、尺寸、避让算法、箭头布局 |
| Menu 布局属性 | `frameworks/core/components_ng/pattern/menu/menu_layout_property.h` | `MenuLayoutProperty`，菜单布局属性定义 |
| Menu 绘制方法 | `frameworks/core/components_ng/pattern/menu/menu_paint_method.cpp` | `MenuPaintMethod`，菜单绘制逻辑 |
| Menu 绘制属性 | `frameworks/core/components_ng/pattern/menu/menu_paint_property.h` | `MenuPaintProperty` |
| Menu Dynamic Model | `frameworks/core/components_ng/pattern/menu/menu_model_ng.cpp` | `MenuModelNG`，动态属性写入、节点创建 |
| Menu Static Model | `frameworks/core/components_ng/pattern/menu/menu_model_static.cpp` | `MenuModelStatic`，静态前端属性写入入口 |
| Menu 视图工厂 | `frameworks/core/components_ng/pattern/menu/menu_view.cpp` | `MenuView`，菜单节点创建工厂 |
| Menu 静态视图 | `frameworks/core/components_ng/pattern/menu/menu_view_static.cpp` | 静态前端视图方法 |
| Menu 主题 | `frameworks/core/components_ng/pattern/menu/menu_theme_wrapper.h` | Menu Token 适配 |
| Menu 管理器 | `frameworks/core/components_ng/pattern/menu/menu_manager.cpp` | `MenuManager`，菜单生命周期管理 |
| Menu 无障碍 | `frameworks/core/components_ng/pattern/menu/menu_accessibility_property.cpp` | `MenuAccessibilityProperty` |
| Menu 避让算法 | `frameworks/core/components_ng/pattern/menu/menu_avoid_algorithm.cpp` | 菜单边界避让计算 |
| 子菜单布局 | `frameworks/core/components_ng/pattern/menu/sub_menu_layout_algorithm.cpp` | `SubMenuLayoutAlgorithm` |
| 多菜单布局 | `frameworks/core/components_ng/pattern/menu/multi_menu_layout_algorithm.cpp` | `MultiMenuLayoutAlgorithm` |
| MenuItem Pattern | `frameworks/core/components_ng/pattern/menu/menu_item/menu_item_pattern.cpp` | `MenuItemPattern` / `CustomMenuItemPattern`，菜单项交互、子菜单展开 |
| MenuItem Model | `frameworks/core/components_ng/pattern/menu/menu_item/menu_item_model_ng.cpp` | `MenuItemModelNG` |
| MenuItem 静态 Model | `frameworks/core/components_ng/pattern/menu/menu_item/menu_item_model_static.cpp` | `MenuItemModelStatic` |
| MenuItem 事件 | `frameworks/core/components_ng/pattern/menu/menu_item/menu_item_event_hub.h` | `MenuItemEventHub` |
| MenuItem 布局算法 | `frameworks/core/components_ng/pattern/menu/menu_item/menu_item_layout_algorithm.cpp` | `MenuItemLayoutAlgorithm` |
| MenuItem 无障碍 | `frameworks/core/components_ng/pattern/menu/menu_item/menu_item_accessibility_property.cpp` | MenuItem 无障碍属性 |
| MenuItemGroup Pattern | `frameworks/core/components_ng/pattern/menu/menu_item_group/menu_item_group_pattern.cpp` | `MenuItemGroupPattern`，分组 header/footer 管理 |
| MenuItemGroup View | `frameworks/core/components_ng/pattern/menu/menu_item_group/menu_item_group_view.cpp` | `MenuItemGroupView` |
| MenuWrapper Pattern | `frameworks/core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.cpp` | `MenuWrapperPattern`，继承 `PopupBasePattern`，全屏容器、菜单状态管理 |
| MenuWrapper 多线程 | `frameworks/core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern_multi_thread.cpp` | 多线程支持 |
| MenuPreview Pattern | `frameworks/core/components_ng/pattern/menu/preview/menu_preview_pattern.cpp` | `MenuPreviewPattern`，预览图、Hover 动画 |
| MenuDivider Pattern | `frameworks/core/components_ng/pattern/menu/menu_divider/menu_divider_pattern.cpp` | `MenuDividerPattern`，分隔线 |
| 组件化 Bridge 目录 | `frameworks/core/components_ng/pattern/menu/bridge/` | 组件化后的统一 Bridge / DynamicModule 入口 |
| node_modifier 委托层 | `frameworks/core/interfaces/native/node/menu_modifier.cpp` | Menu C++ 属性 Set/Reset/Get 委托层 |
| MenuItem node_modifier | `frameworks/core/interfaces/native/node/menu_item_modifier.cpp` | MenuItem C++ 属性委托层 |
| MenuItemGroup node_modifier | `frameworks/core/interfaces/native/node/menu_item_group_modifier.cpp` | MenuItemGroup C++ 属性委托层 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API (Menu) | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/menu.d.ts` | 动态 ArkTS `MenuInterface`、`MenuAttribute` 声明 |
| Dynamic API (MenuItem) | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/menu_item.d.ts` | `MenuItemInterface`、`MenuItemAttribute` 声明 |
| Dynamic API (bindMenu) | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | `bindMenu(content, options?)` 和 `bindMenu(isShow, content, options?)` 属性声明 |
| Dynamic API (bindContextMenu) | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | `bindContextMenu(content, responseType, options?)`、`bindContextMenu(isShown, content, options?)`、`bindContextMenuByResponseType`、`bindContextMenuByIsShow`、`bindContextMenuWithResponse` 属性声明 |
| Modifier API (Menu) | `<OH_ROOT>/interface/sdk-js/api/arkui/MenuModifier.d.ts` | 动态 Menu Modifier 声明 |
| Modifier API (MenuItem) | `<OH_ROOT>/interface/sdk-js/api/arkui/MenuItemModifier.d.ts` | 动态 MenuItem Modifier 声明 |
| CAPI / NDK | 无独立 NODE 枚举 | Menu 使用 modifier-based C API，不走 FrameNode 节点类型枚举；C API 通过 `menu_modifier.cpp` 等委托层实现 |

API 检索建议：

- 属性声明：在 SDK 文件中搜索 `MenuAttribute` 和具体属性名。
- 构造参数：在 SDK 文件中搜索 `MenuInterface`、`MenuOptions`。
- 绑定接口：在 `common.d.ts` 中搜索 `bindMenu`、`bindContextMenu`、`bindContextMenuWithResponse`、`MenuElement`、`MenuOptions`、`ContextMenuOptions`、`ResponseType`。
- Modifier：在 `MenuModifier*.d.ts` / `MenuItemModifier*.d.ts` 中确认声明。
- C API：在 `frameworks/core/interfaces/native/node/menu_modifier.cpp` 中搜索属性名。

### bindMenu / bindContextMenu 调用链

bindMenu 和 bindContextMenu 是注册在 `JSViewAbstract` 上的通用属性方法，实现在 `js_popups.cpp` 中，通过 `ViewAbstractModel` 分发到 NG 或 Legacy 路径。

#### bindMenu

| SDK 声明 | JSView 入口 | 说明 |
|----------|------------|------|
| `bindMenu(content: Array<MenuElement> \| CustomBuilder, options?: MenuOptions)` | `JSViewAbstract::JsBindMenu` | 基础形式，点击触发；参数数组或 CustomBuilder |
| `bindMenu(isShow: boolean, content: Array<MenuElement> \| CustomBuilder, options?: MenuOptions)` | `JSViewAbstract::JsBindMenu` | API 11+，支持条件显示控制；第一参数为 boolean 或 `{ value: boolean }` 对象（onStateChange 回调） |

调用链（`js_popups.cpp` → `ViewAbstractModel`）：

1. `JsBindMenu` 解析 `isShow` / `onStateChange` → `MenuParam` 构建
2. 参数数组分支：`JSViewPopups::ParseBindOptionParam()` 解析 `Array<MenuElement>` → `ViewAbstractModel::BindMenu(optionsParam, nullptr, menuParam)`
3. CustomBuilder 分支：解析 builder 函数 → `ViewAbstractModel::BindMenu({}, buildFunc, menuParam)`
4. NG 路径：`ViewAbstractModelNG::BindMenu()` → `ViewAbstract::BindMenuWithItems()` 或 `ViewAbstract::BindMenuWithCustomNode()` → `OverlayManager::ShowMenu()`
5. Legacy 路径：`ViewAbstractModelImpl::BindMenu()` → 注册 `TapGesture` → `MenuComponent` → 点击时触发 builder

#### bindContextMenu

| SDK 声明 | JSView 入口 | 说明 |
|----------|------------|------|
| `bindContextMenu(content: CustomBuilder, responseType: ResponseType, options?: ContextMenuOptions)` | `JSViewAbstract::JsBindContextMenu` | API 8+，按 responseType（LONG_PRESS / RIGHT_CLICK）触发 |
| `bindContextMenu(isShown: boolean, content: CustomBuilder, options?: ContextMenuOptions)` | `JSViewAbstract::JsBindContextMenuByIsShow` | API 12+，条件显示控制 |
| `bindContextMenuByResponseType(content, responseType, options?)` | `JSViewAbstract::JsBindContextMenuByResponseType` | 数组或 CustomBuilder + responseType |
| `bindContextMenuWithResponse(content: CustomBuilderT<ResponseType>, options?)` | `JSViewAbstract::JsBindContextMenuWithResponse` | API 23+，builder 内部判断响应类型 |

调用链（`js_popups.cpp` → `ViewAbstractModel`）：

1. `JsBindContextMenu` / `JsBindContextMenuByIsShow` / `JsBindContextMenuByResponseType` 解析 `isShow` / `responseType` → `MenuParam`（`type = CONTEXT_MENU`、`previewMode = NONE`）
2. 参数数组分支：`ParseBindOptionParam()` 解析 → `ViewAbstractModel::BindContextMenu(responseType, optionsParam, menuParam, previewBuildFunc)`
3. CustomBuilder 分支：解析 builder 函数 → `ViewAbstractModel::BindContextMenu(responseType, buildFunc, menuParam, previewBuildFunc)`
4. preview content 分支：`ParseBindContentOptionParam()` 解析预览内容参数 → `previewBuildFunc`
5. NG 路径：`ViewAbstractModelNG::BindContextMenu()` → 根据 `ResponseType` 注册右键鼠标事件或长按手势 → `ViewAbstract::BindMenuWithCustomNode()` → `OverlayManager::ShowMenu()`
6. Legacy 路径：`ViewAbstractModelImpl::BindContextMenu()` → `RIGHT_CLICK`：注册 `SetOnMouseId`（检测右键释放）；`LONG_PRESS`：注册 `LongPressGesture` → `ExecMenuBuilder()` → `MenuComponent::GetTargetCallback()` 显示菜单
7. 拖拽菜单：`ViewAbstractModel::BindDragWithContextMenuParams(menuParam)` 绑定拖拽参数

### API 解析实现路径

Menu 已完成组件化改造，主菜单 JSView 文件不存在，Bridge 和动态属性路径统一到 `pattern/menu/bridge/`。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 前端 JS/TS 定义 | `frameworks/bridge/declarative_frontend/ark_component/src/ArkMenu.ts`、`frameworks/bridge/declarative_frontend/ark_component/components/arkmenu.js` | 前端组件类；ArkTS Modifier 类见 `frameworks/bridge/declarative_frontend/ark_modifier/src/menu_modifier.ts` |
| 统一 Bridge（声明式 + 动态属性） | `frameworks/core/components_ng/pattern/menu/bridge/menu/arkts_native_menu_bridge.cpp` | 通过 `IsJsView()` 区分模式，统一参数解析 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/menu/bridge/menu/menu_dynamic_modifier.cpp` | 动态属性路径 |
| Static Modifier | `frameworks/core/components_ng/pattern/menu/bridge/menu/menu_static_modifier.cpp` | 静态编译路径 |
| Dynamic Module | `frameworks/core/components_ng/pattern/menu/bridge/menu/menu_dynamic_module.cpp` | `MenuDynamicModule` 派生类，`libarkui_menu.z.so` 入口 |
| node_modifier 委托层 | `frameworks/core/interfaces/native/node/menu_modifier.cpp` | 通过 `DynamicModuleHelper` 转发到动态模块 |
| MenuItem Bridge | `frameworks/core/components_ng/pattern/menu/bridge/menu_item/arkts_native_menu_item_bridge.cpp` | MenuItem 统一 Bridge |
| MenuItemGroup Bridge | `frameworks/core/components_ng/pattern/menu/bridge/menu_item_group/arkts_native_menu_item_group_bridge.cpp` | MenuItemGroup 统一 Bridge |
| Inner Modifier | `frameworks/core/components_ng/pattern/menu/bridge/inner_modifier/` | 内部 modifier 委托（menu_inner_modifier、menu_item_inner_modifier 等） |

独立 SO：`libarkui_menu.z.so`。

注：`bindMenu` / `bindContextMenu` 绑定接口仍通过通用属性桥接（`js_popups.cpp` → `ViewAbstractModel`）触发，菜单内容构建走组件化路径。

### 外部依赖入口

外部仓路径以 OpenHarmony 根目录为基准；相对路径列仅记录外部仓内的头文件、目录或 GN 目标。

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 窗口子系统 | `frameworks/core/components_ng/pattern/menu/menu_pattern.cpp` | `window_manager` | `interfaces/innerkits/wm/window_manager.h` | 菜单子窗口创建与管理（子窗模式显示菜单） |
| 图形渲染 | `frameworks/core/components_ng/pattern/menu/menu_paint_method.cpp` | `foundation/graphic/graphic_2d` | `rosen/modules/render_service_base/include/` | RSNode / RSCanvas 绘制菜单背景、圆角、阴影 |
| 无障碍框架 | `frameworks/core/components_ng/pattern/menu/menu_accessibility_property.*` | `base/accessibility` | `accessibility:accessibility_common` | 菜单无障碍属性上报和操作响应 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/menu/` | Menu/MenuItem/MenuItemGroup/MenuWrapper/MenuDivider Pattern、布局、动画、无障碍等回归测试 |
| C API 测试 | `test/unittest/capi/modifiers/menu_modifier_test.cpp` | Menu Modifier C API 回归 |
| C API 测试 | `test/unittest/capi/modifiers/menu_item_modifier_test.cpp` | MenuItem Modifier C API 回归 |
| C API 测试 | `test/unittest/capi/modifiers/menu_item_group_modifier_test.cpp` | MenuItemGroup Modifier C API 回归 |
| Context registry | `docs/context_registry.json` | Menu 的 KB、源码、API、测试统一路由 |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| Menu 功能域 | `specs/05-ui-components/06-popup-components/01-menu-menu-item-menu-item-group/` | Menu/MenuItem/MenuItemGroup 规格目录 |
| Feat-01 | `specs/05-ui-components/06-popup-components/01-menu-menu-item-menu-item-group/Feat-01-bind-menu-trigger-spec.md` | bindMenu/bindContextMenu 绑定与触发机制 |
| Feat-02 | `specs/05-ui-components/06-popup-components/01-menu-menu-item-menu-item-group/Feat-02-menu-creation-properties-spec.md` | Menu/MenuItem/MenuItemGroup 创建与属性 |
| Feat-03 | `specs/05-ui-components/06-popup-components/01-menu-menu-item-menu-item-group/Feat-03-submenu-layout-animation-spec.md` | 子菜单展开、布局避让、动画与预览 |
| 架构设计 | `specs/05-ui-components/06-popup-components/01-menu-menu-item-menu-item-group/design.md` | Menu 架构设计文档 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 菜单不显示或位置错误 | `MenuLayoutAlgorithm` 的 `MenuLayoutAvoidAlgorithm()`、`FitToScreen()`；`MenuWrapperPattern` 的菜单状态 |
| 子菜单不展开/收起异常 | `MenuItemPattern` 的 `ShowSubMenu()` / `HideSubMenu()`；`SubMenuExpandingMode` 枚举 |
| bindMenu/bindContextMenu 不触发 | `js_popups.cpp` 的 `JsBindMenu` / `JsBindContextMenu`；`ViewAbstractModel` 事件注册 |
| 菜单动画异常 | `MenuPattern::ShowMenuAppearAnimation()`；`MenuWrapperPattern` 的转场效果和 `MenuStatus` 状态机 |
| Preview 预览图不显示 | `MenuPreviewPattern` 的 Hover 动画和缩放逻辑 |
| 菜单避让算法错误 | `menu_avoid_algorithm.cpp` 和 `MenuLayoutAlgorithm::CalculateMenuPath()` |
| 无障碍操作无效 | `MenuAccessibilityProperty`、`MenuItemAccessibilityProperty`、`MenuItemGroupAccessibilityProperty` |

## 调试入口

- 创建链路：从 `MenuView::Create()` 或 `MenuModelNG::Create()` 确认菜单节点创建和 Pattern 设置。
- 属性链路：从 SDK 属性名定位 Bridge → node_modifier → Model 写入，再看 `MenuLayoutProperty` / `MenuPaintProperty` 的属性分组。
- 布局链路：从 `MenuLayoutAlgorithm::Measure()` / `Layout()` 跟踪菜单位置、尺寸、避让和箭头计算。
- 绑定链路：`bindMenu` 从 `js_popups.cpp::JsBindMenu` → `ViewAbstractModel::BindMenu()`；`bindContextMenu` 从 `JsBindContextMenu` → `BindContextMenu()`。
- 组件化链路：从 `MenuDynamicModule` 的 `GetDynamicModifier()` / `GetStaticModifier()` 跟踪动态模块加载和属性注册。
- 回归验证：优先运行 `test/unittest/core/pattern/menu/` 下的定向用例。

## 相关主题

- [Dialog 组件（自定义弹窗，同属弹窗类组件）](dialog.md)
- bindSheet 组件（半模态弹窗，同属弹窗类组件）
- [bindPopup / Popup 组件（气泡弹窗，同属弹窗类组件）](bind-popup.md)