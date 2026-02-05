# ArkUI Menu 组件完整知识库

> **文档版本**：v2.0 (Unified)
> **更新时间**：2026-01-26
> **源码版本**：OpenHarmony ace_engine (master 分支)
> **作者**：基于 CLAUDE.md 规范自动生成

---

## 📚 目录

1. [概述](#概述)
2. [完整调用链](#完整调用链)
3. [目录结构](#目录结构)
4. [核心类继承关系](#核心类继承关系)
5. [Pattern层详解](#pattern层详解)
6. [Model层详解](#model层详解)
7. [View层详解](#view层详解)
8. [布局算法](#布局算法)
9. [属性系统](#属性系统)
10. [事件处理](#事件处理)
11. [主题系统](#主题系统)
12. [动画系统](#动画系统)
13. [执行流程](#执行流程)
14. [完整API清单](#完整api清单)
15. [关键实现细节](#关键实现细节)
16. [子窗机制](#子窗机制)
17. [使用示例](#使用示例)
18. [调试指南](#调试指南)
19. [附录](#附录)

---

## 概述

### 组件定位

**Menu 组件**是 OpenHarmony ArkUI 框架中的**菜单组件**，提供下拉菜单、上下文菜单、子菜单等多种菜单形式，支持普通菜单、选择菜单、导航菜单等多种场景。

**技术栈**：
- **前端**：ArkTS/JavaScript
- **桥接层**：JSViewAbstract + ViewAbstractModel
- **核心层**：NG Pattern 架构
- **渲染层**：Rosen + Skia

**代码规模**：
- 总文件数：约 80 个文件
- 核心代码：约 15,000+ 行 C++ 代码
- 涉及 4 个架构层次

### 功能特性

Menu组件支持：
- **多种菜单类型**: 普通菜单、上下文菜单、子菜单、导航菜单、桌面菜单等
- **Preview模式**: Hover模式下的预览功能
- **多种展开方式**: SIDE、EMBEDDED、STACK三种子菜单展开模式
- **完整动画**: 出现、消失、箭头旋转、背景色等动画效果
- **无障碍支持**: 完整的Accessibility支持
- **避让算法**: 自动调整菜单位置避免超出屏幕边界

### 设计模式

Menu 组件采用 **NG Pattern 架构** + **Bridge 模式**：

```
前端 (ArkTS/JS)
    ↓ (Bridge Layer)
JSViewAbstract (js_view_abstract.cpp)
    ↓ (Model Layer)
ViewAbstractModelImpl (view_abstract_model_impl.cpp)
    ↓ (Legacy Component Layer - 兼容层)
MenuComponent (menu_component.cpp)
    ↓ (NG Model Layer)
MenuModelNG (menu_model_ng.cpp)
    ↓ (NG Pattern Layer)
MenuPattern (menu_pattern.cpp)
    ↓ (NG LayoutAlgorithm Layer)
MenuLayoutAlgorithm (menu_layout_algorithm.cpp)
    ↓
渲染显示
```

---

## 完整调用链

### 1. 三种入口 API 对比

| API | 用途 | 触发方式 | 源码位置 |
|-----|------|---------|---------|
| **JsBindMenu** | 绑定普通菜单 | 点击 | `js_popups.cpp:2906` |
| **JsBindContextMenu** | 绑定上下文菜单 | 长按/右键 | `js_popups.cpp:1950` |
| **JsBindContextMenuWithResponse** | 绑定上下文菜单（带响应类型参数） | 多种触发 | `js_popups.cpp:1996` |

### 2. JsBindMenu 完整调用链

#### 调用链图

```
┌─────────────────────────────────────────────────────────┐
│ 前端 JavaScript / ArkTS                                 │
│                                                          │
│ Button/Component.onClick()                             │
│     ↓                                                    │
│ .bindMenu(isShow, options)                            │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ Bridge Layer (JS → C++)                                  │
│                                                          │
│ void JSViewAbstract::JsBindMenu(const JSCallbackInfo&)  │
│   源码：frameworks/bridge/declarative_frontend/jsview/  │
│         js_popups.cpp:2906-2968                        │
│                                                          │
│ 执行流程：                                                 │
│ 1. 解析 isShow 参数                                     │
│ 2. 解析 options 数组 或 CustomBuilder                   │
│ 3. 创建 MenuParam 结构                                  │
│ 4. 调用 ViewAbstractModel::BindMenu()                   │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ Model Layer (参数管理)                                   │
│                                                          │
│ void ViewAbstractModelImpl::BindMenu(                   │
│   std::vector<OptionParam>& params,                     │
│   std::function<void()>& buildFunc,                      │
│   const MenuParam& menuParam)                           │
│   源码：frameworks/bridge/declarative_frontend/jsview/  │
│         models/view_abstract_model_impl.cpp:1593-1613    │
│                                                          │
│ 执行流程：                                                 │
│ 1. 获取 MenuComponent 实例                               │
│ 2. 创建事件处理器（GestureEventFunc）                     │
│    - CreateMenuEventWithParams（选项参数）                │
│    - CreateMenuEventWithBuilder（自定义 Builder）        │
│ 3. 注册 TapGesture 到目标组件                            │
│ 4. 保存 builderFunc 供触发时执行                         │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ Legacy Component Layer (兼容层)                          │
│                                                          │
│ class MenuComponent : public ComposedComponent           │
│   源码：frameworks/core/components/menu/                   │
│         menu_component.h:36                               │
│                                                          │
│ 职责：                                                    │
│ - 包装 SelectPopupComponent                               │
│ - 管理选项列表（OptionComponent）                        │
│ - 提供兼容性接口                                           │
│ - 触发 targetCallback_                                   │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ NG Model Layer (NG 组件模型)                             │
│                                                          │
│ class MenuModelNG : public MenuModel                      │
│   源码：frameworks/core/components_ng/pattern/menu/         │
│         menu_model_ng.h:22                                 │
│                                                          │
│ 方法：                                                    │
│ - Create() - 创建菜单节点                                │
│ - SetFontSize() - 设置字体大小                            │
│ - SetFontColor() - 设置字体颜色                            │
│ - SetBorderRadius() - 设置圆角                              │
│ - SetExpandingMode() - 设置子菜单展开模式                  │
│                                                          │
│ 执行流程：                                                 │
│ 1. 创建 MenuWrapper FrameNode                            │
│   - V2::MENU_WRAPPER_ETS_TAG                             │
│ 2. 创建 Menu FrameNode                                    │
│   - V2::MENU_ETS_TAG                                      │
│ 3. 设置 MenuPattern                                      │
│ 4. 应用 MenuParam 中的属性                                │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ NG Pattern Layer (业务逻辑)                               │
│                                                          │
│ class MenuPattern : public Pattern, public FocusView    │
│   源码：frameworks/core/components_ng/pattern/menu/         │
│         menu_pattern.h:70                                  │
│                                                          │
│ 关键方法：                                                │
│ - OnAttachToFrameNode() - 附加到节点树                     │
│ - OnModifyDone() - 修改完成回调                            │
│ - HideMenu() - 隐藏菜单                                    │
│ - ShowMenuAppearAnimation() - 显示动画                     │
│                                                          │
│ 管理对象：                                                │
│ - options_: 菜单选项列表                                 │
│ - menuItems_: MenuItem 节点列表                          │
│ - showedSubMenu_: 当前显示的子菜单                         │
│ - targetTag_/targetId_: 目标组件信息                        │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ NG LayoutAlgorithm Layer (布局计算)                        │
│                                                          │
│ class MenuLayoutAlgorithm : public BoxLayoutAlgorithm     │
│   源码：frameworks/core/components_ng/pattern/menu/         │
│         menu_layout_algorithm.h:78                          │
│                                                          │
│ 核心方法：                                                │
│ - Measure() - 测量菜单尺寸                                │
│ - Layout() - 布局菜单                                      │
│ - MenuLayoutAvoidAlgorithm() - 菜单避让算法               │
│ - CalculateMenuPath() - 计算菜单裁剪路径                   │
│ - LayoutArrow() - 绘制箭头                                  │
│                                                          │
│ 计算内容：                                                │
│ - 菜单位置（基于 Placement）                               │
│ - 菜单尺寸（考虑屏幕边界）                                 │
│ - 箭头位置和方向                                         │
│ - 与 Preview 的相对位置                                   │
└─────────────────────────────────────────────────────────┘
                          ↓
                    [菜单显示在屏幕上]
```

#### 关键代码片段

**① JS 入口解析** - `js_popups.cpp:2906-2944`
```cpp
void JSViewAbstract::JsBindMenu(const JSCallbackInfo& info)
{
    NG::MenuParam menuParam;
    MenuDefaultParam(menuParam);
    size_t builderIndex = 0;

    // 解析 isShow 参数（可以是 boolean、undefined 或 object）
    if (info.Length() > PARAMETER_LENGTH_FIRST) {
        auto jsVal = info[0];
        if (jsVal->IsBoolean()) {
            menuParam.isShow = jsVal->ToBoolean();
            menuParam.setShow = true;
            builderIndex = 1;
        } else if (jsVal->IsObject()) {
            // 解析为 onChange 回调
            JSRef<JSObject> callbackObj = JSRef<JSObject>::Cast(jsVal);
            menuParam.onStateChange =
                JSViewPopups::ParseDoubleBindCallback(info, callbackObj, "$value");
            // ...
        }
    }

    // 解析 options 数组或 CustomBuilder
    if (info[builderIndex]->IsArray()) {
        std::vector<NG::OptionParam> optionsParam =
            JSViewPopups::ParseBindOptionParam(info, builderIndex);
        ViewAbstractModel::GetInstance()->BindMenu(
            std::move(optionsParam), nullptr, menuParam);
    } else if (info[builderIndex]->IsObject()) {
        // CustomBuilder 分支
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[builderIndex]);
        auto builder = obj->GetProperty("builder");
        auto builderFunc = AceType::MakeRefPtr<JsFunction>(
            JSRef<JSFunc>::Cast(builder));

        // 创建 buildFunc lambda
        WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(
            NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        std::function<void()> buildFunc =
            [execCtx = info.GetExecutionContext(),
             func = std::move(builderFunc),
             node = frameNode]() {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                ACE_SCORING_EVENT("BuildMenu");
                func->Execute();
            };

        ViewAbstractModel::GetInstance()->BindMenu(
            {}, std::move(buildFunc), menuParam);
    }
}
```

**② Model 层事件注册** - `view_abstract_model_impl.cpp:1593-1613`
```cpp
void ViewAbstractModelImpl::BindMenu(
    std::vector<NG::OptionParam>&& params,
    std::function<void()>&& buildFunc,
    const NG::MenuParam&)
{
    // 获取 MenuComponent
    auto menuComponent = ViewStackProcessor::GetInstance()->GetMenuComponent(true);
    CHECK_NULL_VOID(menuComponent);
    auto weak = WeakPtr<OHOS::Ace::MenuComponent>(menuComponent);

    // 创建事件函数
    GestureEventFunc eventFunc;
    if (!params.empty()) {
        // 选项参数模式
        eventFunc = CreateMenuEventWithParams(weak, std::move(params));
    } else if (buildFunc) {
        // 自定义 Builder 模式
        eventFunc = CreateMenuEventWithBuilder(weak, std::move(buildFunc));
    } else {
        LOGE("No param object.");
        return;
    }

    // 注册点击事件
    auto click = ViewStackProcessor::GetInstance()->GetBoxComponent();
    RefPtr<Gesture> tapGesture = AceType::MakeRefPtr<TapGesture>();
    tapGesture->SetOnActionId(eventFunc);
    click->SetOnClick(tapGesture);
}
```

### 3. JsBindContextMenu 完整调用链

#### 调用链图

```
前端 JavaScript / ArkTS
    ↓
.bindContextMenu(responseType, { builder, options })
    ↓
┌─────────────────────────────────────────────────────────┐
│ Bridge Layer                                              │
│                                                          │
│ void JSViewAbstract::JsBindContextMenu(info)           │
│   源码：js_popups.cpp:1950-1994                          │
│                                                          │
│ 执行流程：                                                 │
│ 1. 解析 responseType (默认 LONG_PRESS)                   │
│    - LONG_PRESS: 长按触发                              │
│    - RIGHT_CLICK: 右键触发                               │
│ 2. 解析 builder (必填)                                   │
│ 3. 解析 options (可选，包含 preview content)          │
│ 4. 设置 menuParam.type = CONTEXT_MENU                   │
│ 5. 创建 buildFunc lambda                                │
│ 6. 调用 ViewAbstractModel::BindContextMenu()             │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ Model Layer                                               │
│                                                          │
│ void ViewAbstractModelImpl::BindContextMenu(             │
│   ResponseType type,                                    │
│   std::function<void()>& buildFunc,                    │
│   NG::MenuParam& menuParam,                              │
│   std::function<void()>& previewBuildFunc)               │
│   源码：view_abstract_model_impl.cpp:1615-1650             │
│                                                          │
│ 执行流程：                                                 │
│ 1. menuComponent->SetIsContextMenu(true)                │
│ 2. 根据 responseType 注册事件：                           │
│    - RIGHT_CLICK: 注册鼠标右键事件                       │
│      - 检测 MouseButton::RIGHT_BUTTON + MouseAction::RELEASE  │
│      - 调用 ExecMenuBuilder(builderFunc)                  │
│    - LONG_PRESS: 注册长按事件                            │
│      - 检测长按手势                                    │
│      - 调用 ExecMenuBuilder(builderFunc)                  │
│ 3. 绑定拖拽菜单（如果需要）                             │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ 等待用户触发                                              │
│                                                          │
│ 用户长按/右键                                             │
│    ↓                                                      │
│ 事件回调被触发                                           │
│    ↓                                                      │
│ ExecMenuBuilder(builderFunc, menuComponent)             │
│    ↓                                                      │
│ 执行用户提供的 builder 函数                                │
│    ↓                                                      │
│ 调用 MenuModelNG::Create()                             │
│    ↓                                                      │
│ 创建 MenuPattern (type = CONTEXT_MENU)                  │
│    ↓                                                      │
│ 显示上下文菜单                                            │
└─────────────────────────────────────────────────────────┘
```

#### 关键代码片段

**① JS 入口** - `js_popups.cpp:1950-1994`
```cpp
void JSViewAbstract::JsBindContextMenu(const JSCallbackInfo& info)
{
    NG::MenuParam menuParam;

    // 解析参数
    size_t builderIndex = ParseBindContextMenuShow(info, menuParam);

    // 解析 responseType（可选参数，默认 LONG_PRESS）
    ResponseType responseType = ResponseType::LONG_PRESS;
    if (!info[NUM_ZERO]->IsBoolean() &&
        info.Length() >= PARAMETER_LENGTH_SECOND &&
        info[NUM_FIRST]->IsNumber()) {
        auto response = info[NUM_FIRST]->ToNumber<int32_t>();
        responseType = static_cast<ResponseType>(response);
    }

    // 解析 builder (必填)
    JSRef<JSObject> menuObj = JSRef<JSObject>::Cast(info[builderIndex]);
    auto builder = menuObj->GetProperty("builder");
    if (!builder->IsFunction()) {
        return;
    }
    auto builderFunc = AceType::MakeRefPtr<JsFunction>(
        JSRef<JSFunc>::Cast(builder));

    // 设置菜单类型
    menuParam.previewMode = MenuPreviewMode::NONE;
    menuParam.type = NG::MenuType::CONTEXT_MENU;

    // 解析 options (可选，用于 preview content)
    std::function<void()> previewBuildFunc = nullptr;
    if (info.Length() >= PARAMETER_LENGTH_THIRD &&
        info[NUM_SECOND]->IsObject()) {
        ParseBindContentOptionParam(info, info[NUM_SECOND],
            menuParam, previewBuildFunc);
    }

    // 创建 buildFunc lambda
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(
        NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    std::function<void()> buildFunc =
        [execCtx = info.GetExecutionContext(),
         func = std::move(builderFunc),
         node = frameNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("BuildContextMenu");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };

    // 调用 Model 层
    ViewAbstractModel::GetInstance()->BindContextMenu(
        responseType, buildFunc, menuParam, previewBuildFunc);
}
```

**② Model 层事件注册** - `view_abstract_model_impl.cpp:1615-1650`
```cpp
void ViewAbstractModelImpl::BindContextMenu(
    ResponseType type,
    std::function<void()>& buildFunc,
    NG::MenuParam& menuParam,
    std::function<void()>& previewBuildFunc)
{
    auto menuComponent = ViewStackProcessor::GetInstance()->GetMenuComponent(true);
    CHECK_NULL_VOID(menuComponent);

    #if defined(MULTIPLE_WINDOW_SUPPORTED)
    menuComponent->SetIsContextMenu(true);
    #endif

    auto weak = WeakPtr<OHOS::Ace::MenuComponent>(menuComponent);

    // 根据响应类型注册不同的事件
    if (type == ResponseType::RIGHT_CLICK) {
        auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
        box->SetOnMouseId([weak, builderFunc = std::move(buildFunc)](
            MouseInfo& info) {
            auto menuComponent = weak.Upgrade();
            CHECK_NULL_VOID(menuComponent);

            // 检测右键释放事件
            if (info.GetButton() == MouseButton::RIGHT_BUTTON &&
                info.GetAction() == MouseAction::RELEASE) {
                ExecMenuBuilder(builderFunc, menuComponent);
                auto showMenu = menuComponent->GetTargetCallback();
                info.SetStopPropagation(true);
                LOGI("Context menu is triggered, type is right click.");
            }
        });
    } else if (type == ResponseType::LONG_PRESS) {
        // 注册长按事件
        // 类似 RIGHT_CLICK 的逻辑...
    }

    // 绑定拖拽菜单（如果需要）
    ViewAbstractModel::GetInstance()->BindDragWithContextMenuParams(menuParam);
}
```

### 4. JsBindContextMenuWithResponse 完整调用链

**与 JsBindContextMenu 的区别**：

| 特性 | JsBindContextMenu | JsBindContextMenuWithResponse |
|-----|-------------------|----------------------------|
| Builder 函数签名 | `buildFunc()` | `buildFuncWithType(type: MenuBindingType)` |
| 响应类型传递 | 作为参数单独传递 | 通过 builder 参数传递 |
| 灵活性 | 固定的响应类型 | Builder 可以根据类型动态响应 |

### 5. 三种 API 的使用场景

| API | 使用场景 | 前端示例 |
|-----|---------|----------|
| **JsBindMenu** | 普通下拉菜单（按钮点击触发） | `Button("Menu").bindMenu(isShow, options)` |
| **JsBindContextMenu** | 右键菜单或长按菜单 | `Text().bindContextMenu(ResponseType.RightClick, { builder })` |
| **JsBindContextMenuWithResponse** | 需要根据触发类型执行不同逻辑 | `Text().bindContextMenu({ builder })` (builder 内部判断类型) |

---

## 目录结构

```
frameworks/core/components_ng/pattern/menu/
├── menu_pattern.h/cpp                    # 主菜单Pattern（核心）
├── menu_layout_algorithm.h/cpp           # 布局算法
├── menu_layout_property.h/cpp            # 布局属性
├── menu_paint_method.h/cpp               # 绘制方法
├── menu_paint_property.h                 # 绘制属性
├── menu_model_ng.h/cpp                   # Model接口（C++→ArkTS绑定）
├── menu_model_static.h/cpp               # 静态Model方法
├── menu_view.h/cpp                       # 视图创建工厂
├── menu_view_static.h/cpp                # 静态View方法
├── menu_theme.h                          # 主题定义
├── menu_accessibility_property.h/cpp     # 无障碍属性
│
├── menu_item/                            # MenuItem子组件目录
│   ├── menu_item_pattern.h/cpp           # MenuItem Pattern
│   ├── menu_item_model_ng.h/cpp          # MenuItem Model
│   ├── menu_item_model_static.h/cpp      # MenuItem 静态Model
│   ├── menu_item_layout_algorithm.h/cpp  # MenuItem 布局算法
│   ├── menu_item_layout_property.h       # MenuItem 布局属性
│   ├── menu_item_paint_method.h/cpp      # MenuItem 绘制方法
│   ├── menu_item_paint_property.h        # MenuItem 绘制属性
│   ├── menu_item_event_hub.h             # MenuItem 事件中心
│   ├── menu_item_accessibility_property.h/cpp # MenuItem 无障碍
│   ├── custom_menu_item_layout_algorithm.h/cpp # 自定义布局
│   └── menu_item_row_pattern.h           # MenuItem Row Pattern
│
├── menu_item_group/                      # MenuItemGroup子组件目录
│   ├── menu_item_group_pattern.h/cpp     # MenuItemGroup Pattern
│   ├── menu_item_group_view.h/cpp        # MenuItemGroup View
│   ├── menu_item_group_view_static.h/cpp # MenuItemGroup 静态View
│   ├── menu_item_group_layout_algorithm.h/cpp # 布局算法
│   ├── menu_item_group_paint_method.h/cpp    # 绘制方法
│   ├── menu_item_group_paint_property.h      # 绘制属性
│   └── menu_item_group_accessibility_property.h/cpp # 无障碍
│
├── menu_divider/                         # MenuDivider子组件目录
│   ├── menu_divider_pattern.h/cpp        # MenuDivider Pattern
│   ├── menu_divider_layout_algorithm.h/cpp # 布局算法
│   ├── menu_divider_paint_method.h/cpp   # 绘制方法
│   ├── menu_divider_paint_property.h     # 绘制属性
│   └── menu_divider_modifier.h/cpp       # 修饰符
│
├── wrapper/                              # MenuWrapper子组件目录
│   ├── menu_wrapper_pattern.h/cpp        # MenuWrapper Pattern
│   ├── menu_wrapper_pattern_multi_thread.cpp   # 多线程支持
│   ├── menu_wrapper_layout_algorithm.h/cpp     # 布局算法
│   ├── menu_wrapper_paint_method.h/cpp   # 绘制方法
│   └── menu_wrapper_paint_property.h     # 绘制属性
│
├── preview/                              # MenuPreview子组件目录
│   ├── menu_preview_pattern.h/cpp        # MenuPreview Pattern
│   └── menu_preview_layout_algorithm.h/cpp     # 布局算法
│
├── sub_menu_layout_algorithm.h/cpp       # 子菜单布局算法
└── multi_menu_layout_algorithm.h/cpp     # 多菜单布局算法
```

**文件统计**: 约80个文件
**核心代码规模**: 约15,000+行C++代码

---

## 核心类继承关系

### Pattern继承层次

```
Pattern (基础Pattern类)
├─ MenuPattern (menu_pattern.h:70)
│  └─ InnerMenuPattern (menu_pattern.h:896)
│     └─ 对应前端<Menu>标签
│
├─ MenuItemPattern (menu_item_pattern.h:45)
│  └─ CustomMenuItemPattern (menu_item_pattern.h:666)
│     └─ 支持自定义内容节点
│
├─ MenuItemGroupPattern (menu_item_group_pattern.h:30)
│  └─ 管理分组header/footer
│
├─ MenuDividerPattern (menu_divider_pattern.h:25)
│  └─ 绘制分隔线
│
├─ MenuWrapperPattern (menu_wrapper_pattern.h:50)
│  └─ PopupBasePattern (弹窗基类)
│
└─ MenuPreviewPattern (menu_preview_pattern.h:33)
   └─ LinearLayoutPattern (线性布局基类)
```

### 其他继承关系

```
LayoutProperty
├─ MenuLayoutProperty (menu_layout_property.h:50)
└─ MenuItemLayoutProperty (menu_item_layout_property.h:47)

PaintProperty
├─ MenuPaintProperty (menu_paint_property.h:46)
└─ MenuItemPaintProperty (menu_item_paint_property.h)

EventHub
└─ MenuItemEventHub (menu_item_event_hub.h:27)

AccessibilityProperty
├─ MenuAccessibilityProperty (menu_accessibility_property.h:23)
├─ MenuItemAccessibilityProperty
└─ MenuItemGroupAccessibilityProperty
```

---

## Pattern层详解

### 1. MenuPattern（主菜单Pattern）

**源码**: `menu_pattern.h:70`

```cpp
class MenuPattern : public Pattern, public FocusView
```

**继承链**：
```
Pattern (基类)
  ↓
MenuPattern (实现类)
  ↓
FocusView (焦点视图接口)
```

**核心成员变量**:
```cpp
int32_t targetId_ = -1;              // 目标节点ID
const std::string targetTag_;         // 目标节点Tag
MenuType type_ = MenuType::MENU;      // 菜单类型
std::vector<SelectProperties> selectProperties_;  // Select属性
std::vector<RefPtr<FrameNode>> options_;          // Option节点列表
std::vector<RefPtr<FrameNode>> menuItems_;       // MenuItem节点列表
RefPtr<FrameNode> parentMenuItem_;   // 父MenuItem（用于子菜单）
RefPtr<FrameNode> showedSubMenu_;    // 当前显示的子菜单
```

**核心职责**：
- 管理菜单的显示/隐藏逻辑
- 处理菜单的动画效果
- 管理子菜单（SubMenu）的展开/收起
- 处理菜单的触摸事件、键盘事件
- 管理菜单项（MenuItem）列表

**核心方法**：

| 方法名 | 源码位置 | 功能描述 |
|--------|----------|----------|
| `OnModifyDone()` | menu_pattern.h:398 | 组件修改完成回调，初始化主题、事件、样式 |
| `HideMenu()` | menu_pattern.h:359 | 隐藏菜单，支持动画 |
| `ShowMenuAppearAnimation()` | menu_pattern.cpp | 显示出现动画 |
| `FireBuilder()` | menu_pattern.h:589 | 触发自定义Builder构建 |
| `OnItemPressed()` | menu_pattern.h:607 | 处理菜单项按下事件 |
| `UpdateSelectParam()` | menu_pattern.h:345 | 更新Select参数 |
| `GetMenuWrapper()` | menu_pattern.h:405 | 获取MenuWrapper节点 |
| `GetFirstInnerMenu()` | menu_pattern.h:406 | 获取第一个内部菜单 |
| `DumpInfo()` | menu_pattern.h:407 | 输出调试信息 |

**类型判断方法**：

| 方法 | 返回条件 |
|------|----------|
| `IsContextMenu()` | type_ == MenuType::CONTEXT_MENU |
| `IsMenu()` | type_ == MenuType::MENU |
| `IsSubMenu()` | type_ == MenuType::SUB_MENU |
| `IsNavigationMenu()` | type_ == MenuType::NAVIGATION_MENU |
| `IsMultiMenu()` | type_ == MenuType::MULTI_MENU |
| `IsDesktopMenu()` | type_ == MenuType::DESKTOP_MENU |

### 2. InnerMenuPattern（内部菜单Pattern）

**源码**: `menu_pattern.h:896`

```cpp
class InnerMenuPattern : public MenuPattern
```

**继承链**：
```
MenuPattern
  ↓
InnerMenuPattern (内部菜单实现)
```

**核心职责**：
- 对应前端 `<Menu>` 标签
- 应用桌面菜单主题
- 管理菜单项和组的列表
- 处理半折叠状态（halfFoldStatus_）

**特点**:
- 重写`OnModifyDone()`和`BeforeCreateLayoutWrapper()`
- 支持桌面菜单主题（`ApplyDesktopMenuTheme()`）
- 支持多菜单主题（`ApplyMultiMenuTheme()`）
- 记录第一级items和groups（`itemsAndGroups_`）

### 3. MenuItemPattern（菜单项Pattern）

**源码**: `menu_item_pattern.h:45`

```cpp
class MenuItemPattern : public Pattern
```

**继承链**：
```
Pattern (基类)
  ↓
MenuItemPattern (菜单项实现)
```

**核心成员变量**:
```cpp
bool isSelected_ = false;                    // 选中状态
bool isSubMenuShowed_ = false;               // 子菜单是否显示
bool isSubMenuHovered_ = false;              // 子菜单是否hover
int32_t index_ = 0;                          // 菜单项索引
std::function<void()> subBuilderFunc_;       // 子菜单Builder
RefPtr<FrameNode> subMenu_;                  // 子菜单节点
RefPtr<FrameNode> content_;                  // 内容节点
RefPtr<FrameNode> label_;                    // 标签节点
RefPtr<FrameNode> startIcon_;                // 起始图标
RefPtr<FrameNode> endIcon_;                  // 结束图标
RefPtr<FrameNode> checkMarkNode_;            // 选中标记节点
RefPtr<FrameNode> selectIcon_;               // 选择图标
RefPtr<FrameNode> expandIcon_;               // 展开图标
RefPtr<FrameNode> embeddedMenu_;             // 嵌入式菜单
Color bgBlendColor_;                         // 背景色混合颜色
SubMenuExpandingMode expandingMode_;         // 展开模式
```

**核心职责**：
- 处理菜单项的点击、悬停事件
- 管理子菜单的显示/隐藏
- 更新选中状态
- 处理图标、文本的显示
- 管理分割线（Divider）

**核心方法**：

| 方法名 | 源码位置 | 功能描述 |
|--------|----------|----------|
| `OnModifyDone()` | menu_item_pattern.h:256 | 初始化主题、事件、样式 |
| `SetSelected()` | menu_item_pattern.h:132 | 设置选中状态 |
| `ShowSubMenu()` | menu_item_pattern.h:513 | 显示子菜单 |
| `HideSubMenu()` | menu_item_pattern.h:518 | 隐藏子菜单 |
| `PlayBgColorAnimation()` | menu_item_pattern.h:240 | 播放背景色动画 |
| `CloseMenu()` | menu_item_pattern.h:212 | 关闭菜单 |
| `UpdateTextNodes()` | menu_item_pattern.h:253 | 更新文本节点 |
| `OnHover()` | menu_item_pattern.h:318 | Hover事件处理 |
| `GetMenu()` | menu_item_pattern.h:251 | 获取所属菜单 |

**子菜单展开模式**：
```cpp
enum class SubMenuExpandingMode {
    SIDE,      // 侧边展开（默认）
    EMBEDDED,  // 嵌入式展开
    STACK      // 堆叠式展开
};
```

### 4. MenuItemGroupPattern（菜单项分组Pattern）

**源码**: `menu_item_group_pattern.h:30`

```cpp
class MenuItemGroupPattern : public Pattern
```

**核心成员变量**:
```cpp
int32_t headerIndex_ = -1;          // header索引
int32_t footerIndex_ = -1;          // footer索引
int32_t itemStartIndex_ = 0;        // 起始item索引
bool hasSelectIcon_ = false;        // 是否有选择图标
bool hasStartIcon_ = false;         // 是否有起始图标
RefPtr<FrameNode> headerContent_;   // header内容节点
RefPtr<FrameNode> footerContent_;   // footer内容节点
WeakPtr<FrameNode> header_;         // header节点
WeakPtr<FrameNode> footer_;         // footer节点
RefPtr<FrameNode> bottomDivider_;   // 底部分隔线
```

**核心职责**：
- 管理菜单项分组
- 处理分组header和footer
- 统一分组内菜单项的图标显示
- 管理分组分隔线

**核心方法**：

| 方法名 | 源码位置 | 功能描述 |
|--------|----------|----------|
| `AddHeader()` | menu_item_group_pattern.h:62 | 添加header |
| `AddFooter()` | menu_item_group_pattern.h:63 | 添加footer |
| `UpdateMenuItemIconInfo()` | menu_item_group_pattern.h:106 | 更新菜单项图标信息 |
| `OnExtItemPressed()` | menu_item_group_pattern.h:107 | 外部项按下事件 |
| `ModifyDivider()` | menu_item_group_pattern.h:109 | 修改分隔线 |

### 5. MenuDividerPattern（分隔线Pattern）

**源码**: `menu_divider_pattern.h:25`

```cpp
class MenuDividerPattern : public Pattern
```

**核心成员变量**:
```cpp
WeakPtr<FrameNode> menuItemWk_;    // 关联的MenuItem弱引用
RefPtr<MenuDividerPaintMethod> paintMethod_;  // 绘制方法
bool isOption_;                    // 是否为Option类型
```

**核心职责**：
- 绘制菜单项之间的分隔线
- 根据父节点状态调整样式
- 支持hover、press、selected等状态

**核心方法**：

| 方法名 | 源码位置 | 功能描述 |
|--------|----------|----------|
| `BindMenuItem()` | menu_divider_pattern.h:41 | 绑定到MenuItem |
| `GetMenuItem()` | menu_divider_pattern.h:48 | 获取关联的MenuItem |
| `OnDirtyLayoutWrapperSwap()` | menu_divider_pattern.h:53 | 布局交换回调 |

### 6. MenuWrapperPattern（菜单包装器Pattern）

**源码**: `menu_wrapper_pattern.h:50`

```cpp
class MenuWrapperPattern : public PopupBasePattern
```

**核心成员变量**:
```cpp
int32_t targetId_ = -1;                      // 目标节点ID
std::string targetTag_ = "";                 // 目标节点Tag
MenuStatus menuStatus_ = MenuStatus::INIT;   // 菜单状态
bool isFirstShow_ = true;                    // 是否首次显示
bool hasTransitionEffect_ = false;           // 是否有转场效果
RefPtr<FrameNode> lastTouchItem_;            // 最后触摸的item
RefPtr<FrameNode> currentTouchItem_;         // 当前触摸的item
AnimationOption animationOption_;           // 动画选项
Placement menuPlacement_ = Placement::NONE; // 菜单位置
```

**MenuStatus枚举** (menu_wrapper_pattern.h:40):
```cpp
enum class MenuStatus {
    INIT,              // 未创建
    ON_SHOW_ANIMATION, // 显示动画中
    SHOW,              // 已显示
    ON_HIDE_ANIMATION, // 隐藏动画中
    HIDE               // 已隐藏
};
```

**核心职责**：
- 全屏尺寸，用于检测菜单外点击
- 管理菜单的显示/隐藏状态
- 处理子窗口模式
- 管理菜单生命周期回调

**核心方法**：

| 方法名 | 源码位置 | 功能描述 |
|--------|----------|----------|
| `HideMenu()` | menu_wrapper_pattern.h:89 | 隐藏菜单 |
| `GetMenu()` | menu_wrapper_pattern.h:128 | 获取内部Menu节点 |
| `GetPreview()` | menu_wrapper_pattern.h:185 | 获取Preview节点 |
| `RegisterMenuCallback()` | menu_wrapper_pattern.h:291 | 注册生命周期回调 |
| `SetMenuTransitionEffect()` | menu_wrapper_pattern.h:440 | 设置转场动画效果 |
| `IsShow()` | menu_wrapper_pattern.h:414 | 判断是否显示 |
| `SetMenuStatus()` | menu_wrapper_pattern.h:419 | 设置菜单状态 |

**生命周期回调**：

| 回调方法 | 功能描述 |
|---------|----------|
| `CallMenuAboutToAppearCallback()` | 即将显示回调 |
| `CallMenuOnWillAppearCallback()` | Will显示回调 |
| `CallMenuOnDidAppearCallback()` | Did显示回调 |
| `CallMenuOnWillDisappearCallback()` | Will隐藏回调 |
| `CallMenuOnDidDisappearCallback()` | Did隐藏回调 |
| `CallMenuAboutToDisappearCallback()` | 即将隐藏回调 |
| `CallMenuAppearCallback()` | 显示回调 |
| `CallMenuDisappearCallback()` | 隐藏回调 |

### 7. MenuPreviewPattern（预览Pattern）

**源码**: `menu_preview_pattern.h:33`

```cpp
class MenuPreviewPattern : public LinearLayoutPattern
```

**核心成员变量**:
```cpp
bool isFirstShow_ = false;                     // 是否首次显示
bool hasPreviewTransitionEffect_ = false;      // 是否有预览转场效果
bool isShowHoverImage_ = false;                // 是否显示HoverImage
float hoverImageAfterScaleWidth_ = 0.0f;       // HoverImage缩放后宽度
float hoverImageAfterScaleHeight_ = 0.0f;      // HoverImage缩放后高度
OffsetF hoverImageAfterScaleOffset_;           // HoverImage缩放后偏移
float customPreviewWidth_ = 0.0f;              // 自定义预览宽度
float customPreviewHeight_ = 0.0f;             // 自定义预览高度
float hoverImageScaleFrom_ = 1.0f;             // HoverImage缩放起始值
float hoverImageScaleTo_ = 1.0f;               // HoverImage缩放结束值
float customPreviewScaleTo_ = 1.0f;            // 自定义预览缩放结束值
VectorF hoverTargetOriginScale_;               // Hover目标原始缩放
```

**核心职责**：
- 显示菜单的预览图
- 处理预览动画
- 管理悬停图片（Hover Image）

**核心方法**：

| 方法名 | 源码位置 | 功能描述 |
|--------|----------|----------|
| `OnModifyDone()` | menu_preview_pattern.h:198 | 组件修改完成回调 |
| `GetMenuWrapper()` | menu_preview_pattern.h:174 | 获取MenuWrapper |
| `GetHoverScaleInterruption()` | menu_preview_pattern.h:175 | 获取Hover缩放中断状态 |

---

## Model层详解

### 1. MenuModelNG

**源码**: `menu_model_ng.h:22`

```cpp
class MenuModelNG : public OHOS::Ace::MenuModel
```

**继承关系**:
```
MenuModel (基类，menu_model.h:40)
    ↓
MenuModelNG (NG实现)
```

**核心职责**：
- 提供前端 API 接口
- 设置菜单属性（字体、颜色、尺寸等）
- 创建菜单节点
- 处理资源对象

**核心方法**：

| 方法名 | 源码位置 | 功能描述 |
|--------|----------|----------|
| `Create()` | menu_model_ng.h:24 | 创建Menu节点 |
| `SetFontSize()` | menu_model_ng.h:25 | 设置菜单项字体大小 |
| `SetFontWeight()` | menu_model_ng.h:26 | 设置菜单项字体粗细 |
| `SetFontStyle()` | menu_model_ng.h:27 | 设置菜单项字体样式 |
| `SetFontColor()` | menu_model_ng.h:28 | 设置菜单项字体颜色 |
| `SetFontFamily()` | menu_model_ng.h:29 | 设置菜单项字体家族 |
| `SetWidth()` | menu_model_ng.h:31 | 设置菜单宽度 |
| `SetBorderRadius()` | menu_model_ng.h:32 | 设置菜单圆角 |
| `SetExpandingMode()` | menu_model_ng.h:36 | 设置子菜单展开模式 |
| `SetExpandSymbol()` | menu_model_ng.h:38 | 设置展开Symbol图标 |
| `SetItemDivider()` | menu_model_ng.h:39 | 设置菜单项分隔线 |
| `SetItemGroupDivider()` | menu_model_ng.h:40 | 设置分组分隔线 |

**静态方法**（用于直接操作FrameNode）:

| 方法名 | 源码位置 | 功能描述 |
|--------|----------|----------|
| `CreateMenu()` | menu_model_ng.h:61 | 创建菜单节点 |
| `SetFontColor()` | menu_model_ng.h:45 | 设置字体颜色 |
| `SetFontSize()` | menu_model_ng.h:46 | 设置字体大小 |
| `SetFontWeight()` | menu_model_ng.h:47 | 设置字体粗细 |
| `SetFontStyle()` | menu_model_ng.h:48 | 设置字体样式 |
| `SetFontFamily()` | menu_model_ng.h:49 | 设置字体家族 |
| `SetBorderRadius()` | menu_model_ng.h:50 | 设置圆角 |
| `ResetBorderRadius()` | menu_model_ng.h:51 | 重置圆角 |
| `SetWidth()` | menu_model_ng.h:55 | 设置宽度 |
| `SetItemDivider()` | menu_model_ng.h:56 | 设置菜单项分隔线 |
| `SetItemGroupDivider()` | menu_model_ng.h:57 | 设置分组分隔线 |
| `SetExpandingMode()` | menu_model_ng.h:58 | 设置展开模式 |

### 2. MenuItemModelNG

**源码**: `menu_item_model_ng.h:25`

```cpp
class MenuItemModelNG : public OHOS::Ace::MenuItemModel
```

**继承关系**:
```
MenuItemModel (基类，menu_item_model.h:91)
    ↓
MenuItemModelNG (NG实现)
```

**核心方法**：

| 方法名 | 源码位置 | 功能描述 |
|--------|----------|----------|
| `Create()` | menu_item_model_ng.h:27 | 创建MenuItem（支持custom或props） |
| `SetSelected()` | menu_item_model_ng.h:29 | 设置选中状态 |
| `SetSelectIcon()` | menu_item_model_ng.h:30 | 设置选中图标显示 |
| `SetSelectIconSrc()` | menu_item_model_ng.h:31 | 设置选中图标源 |
| `SetOnChange()` | menu_item_model_ng.h:32 | 设置变化回调 |
| `SetFontSize()` | menu_item_model_ng.h:33 | 设置字体大小 |
| `SetFontWeight()` | menu_item_model_ng.h:34 | 设置字体粗细 |
| `SetFontStyle()` | menu_item_model_ng.h:35 | 设置字体样式 |
| `SetFontColor()` | menu_item_model_ng.h:36 | 设置字体颜色 |
| `SetFontFamily()` | menu_item_model_ng.h:37 | 设置字体家族 |
| `SetLabelFontSize()` | menu_item_model_ng.h:38 | 设置标签字体大小 |
| `SetLabelFontWeight()` | menu_item_model_ng.h:39 | 设置标签字体粗细 |
| `SetLabelFontStyle()` | menu_item_model_ng.h:40 | 设置标签字体样式 |
| `SetLabelFontColor()` | menu_item_model_ng.h:41 | 设置标签字体颜色 |
| `SetLabelFontFamily()` | menu_item_model_ng.h:42 | 设置标签字体家族 |
| `SetSelectedChangeEvent()` | menu_item_model_ng.h:43 | 设置选中变化事件 |
| `SetSelectIconSymbol()` | menu_item_model_ng.h:44 | 设置选中图标Symbol |

**静态方法**（用于直接操作FrameNode）:

| 方法名 | 源码位置 | 功能描述 |
|--------|----------|----------|
| `CreateMenuItem()` | menu_item_model_ng.h:67 | 创建菜单项 |
| `SetSelected()` | menu_item_model_ng.h:51 | 设置选中状态 |
| `SetFontColor()` | menu_item_model_ng.h:58 | 设置字体颜色 |
| `SetFontSize()` | menu_item_model_ng.h:59 | 设置字体大小 |
| `SetFontWeight()` | menu_item_model_ng.h:60 | 设置字体粗细 |
| `SetFontFamily()` | menu_item_model_ng.h:61 | 设置字体家族 |
| `SetLabelFontColor()` | menu_item_model_ng.h:52 | 设置标签字体颜色 |
| `SetLabelFontSize()` | menu_item_model_ng.h:53 | 设置标签字体大小 |
| `SetLabelFontWeight()` | menu_item_model_ng.h:54 | 设置标签字体粗细 |
| `SetLabelFontFamily()` | menu_item_model_ng.h:55 | 设置标签字体家族 |
| `SetLabelFontStyle()` | menu_item_model_ng.h:56 | 设置标签字体样式 |
| `SetFontStyle()` | menu_item_model_ng.cpp:62 | 设置字体样式 |
| `SetSelectIcon()` | menu_item_model_ng.h:63 | 设置选中图标 |
| `SetSelectIconSrc()` | menu_item_model_ng.h:64 | 设置选中图标源 |
| `SetSelectIconSymbol()` | menu_item_model_ng.h:65 | 设置选中图标Symbol |
| `SetOnChange()` | menu_item_model_ng.h:66 | 设置变化回调 |
| `SetSelectedChangeEvent()` | menu_item_model_ng.h:61 | 设置选中变化事件 |

---

## View层详解

### 1. MenuView

**源码**: `menu_view.h:41`

```cpp
class MenuView
```

**核心方法**：

| 方法名 | 源码位置 | 功能描述 |
|--------|----------|----------|
| `Create()` | menu_view.h:55 | 创建菜单（OptionParam数组） |
| `Create()` | menu_view.h:59 | 创建菜单（自定义节点） |
| `Create()` | menu_view.h:64 | 创建Select菜单 |
| `BindImageNodeToMenu()` | menu_view.h:51 | 绑定图片节点到菜单 |
| `ShowPixelMapAnimation()` | menu_view.h:67 | 显示PixelMap动画 |
| `UpdateMenuParam()` | menu_view.h:70 | 更新菜单参数 |
| `UpdateMenuProperties()` | menu_view.h:72 | 更新菜单属性 |
| `CalcHoverScaleInfo()` | menu_view.h:75 | 计算Hover缩放信息 |
| `CreateIcon()` | menu_view.h:76 | 创建图标节点 |
| `CreateText()` | menu_view.h:78 | 创建文本节点 |
| `CreateSelectOption()` | menu_view.h:82 | 创建Select选项 |
| `CreateSymbol()` | menu_view.h:83 | 创建Symbol节点 |
| `SetHasCustomOutline()` | menu_view.h:88 | 设置自定义轮廓 |

### 2. MenuItemGroupView

**源码**: `menu_item_group_view.h:30`

```cpp
class MenuItemGroupView
```

**核心方法**：

| 方法名 | 源码位置 | 功能描述 |
|--------|----------|----------|
| `Create()` | menu_item_group_view.h:33 | 创建MenuItemGroup |
| `SetHeader()` | menu_item_group_view.h:35 | 设置header（UINode） |
| `SetHeader()` | menu_item_group_view.h:36 | 设置header（string） |
| `SetFooter()` | menu_item_group_view.h:39 | 设置footer（UINode） |
| `SetFooter()` | menu_item_group_view.h:40 | 设置footer（string） |

---

## 布局算法

### 1. MenuLayoutAlgorithm

**源码**: `menu_layout_algorithm.h:78`

```cpp
class MenuLayoutAlgorithm : public BoxLayoutAlgorithm
```

**继承关系**:
```
BoxLayoutAlgorithm (盒布局算法)
    ↓
MenuLayoutAlgorithm (菜单布局算法)
```

**核心成员变量**:
```cpp
OffsetF position_;                    // 菜单位置
OffsetF positionOffset_;              // 位置偏移
SizeF wrapperSize_;                   // 包装器尺寸
Rect wrapperRect_;                    // 包装器矩形
PreviewMenuParam param_;              // Preview参数
std::optional<OffsetF> lastPosition_; // 上次位置
OffsetF targetOffset_;                // 目标偏移
SizeF targetSize_;                    // 目标尺寸
Placement placement_ = Placement::BOTTOM_LEFT; // 菜单位置
int32_t targetNodeId_ = -1;           // 目标节点ID
float topSpace_ = 0.0f;               // 顶部空间
float bottomSpace_ = 0.0f;            // 底部空间
float leftSpace_ = 0.0f;              // 左侧空间
float rightSpace_ = 0.0f;             // 右侧空间
```

**核心职责**：
- 计算菜单位置和尺寸
- 处理菜单的定位（Placement）
- 实现菜单避让算法
- 计算箭头（Arrow）位置
- 处理预览菜单（Preview Menu）布局

**核心方法**：

| 方法名 | 源码位置 | 功能描述 |
|--------|----------|----------|
| `Measure()` | menu_layout_algorithm.h:87 | 测量菜单尺寸 |
| `Layout()` | menu_layout_algorithm.h:89 | 布局菜单位置 |
| `GetPlacement()` | menu_layout_algorithm.h:91 | 获取菜单位置 |
| `GetClipPath()` | menu_layout_algorithm.h:96 | 获取裁剪路径 |
| `Initialize()` | menu_layout_algorithm.h:147 | 初始化参数 |
| `CreateChildConstraint()` | menu_layout_algorithm.h:161 | 创建子节点约束 |
| `MenuLayoutAvoidAlgorithm()` | menu_layout_algorithm.h:173 | 菜单避障算法 |
| `SelectLayoutAvoidAlgorithm()` | menu_layout_algorithm.h:175 | Select避障算法 |
| `LayoutArrow()` | menu_layout_algorithm.h:181 | 布局箭头 |
| `GetArrowPositionWithPlacement()` | menu_layout_algorithm.h:182 | 获取箭头位置 |
| `CalculateMenuPath()` | menu_layout_algorithm.h:301 | 计算菜单路径（用于clipPath） |
| `FitToScreen()` | menu_layout_algorithm.h:198 | 适配屏幕边界 |

**Placement支持的12种方位**：

```
TOP, TOP_LEFT, TOP_RIGHT
BOTTOM, BOTTOM_LEFT, BOTTOM_RIGHT
LEFT, LEFT_TOP, LEFT_BOTTOM
RIGHT, RIGHT_TOP, RIGHT_BOTTOM
```

### 2. SubMenuLayoutAlgorithm

**源码**: `sub_menu_layout_algorithm.h`

专门处理子菜单的布局，考虑：
- 父菜单的位置
- 子菜单展开方向
- 避免超出屏幕边界

### 3. MultiMenuLayoutAlgorithm

**源码**: `multi_menu_layout_algorithm.h`

处理多菜单场景的布局：
- 桌面菜单
- 多列菜单
- 网格菜单

### 4. MenuItemLayoutAlgorithm

**源码**: `menu_item_layout_algorithm.h`

处理单个菜单项的布局：
- 图标、文本、选中标记的排列
- 左右Row布局
- 内容对齐

### 5. MenuItemGroupLayoutAlgorithm

**源码**: `menu_item_group_layout_algorithm.h`

处理分组的布局：
- Header/Footer布局
- 分组内Item布局
- 分组分隔线布局

---

## 属性系统

### 1. MenuLayoutProperty

**源码**: `menu_layout_property.h:50`

```cpp
class MenuLayoutProperty : public LayoutProperty
```

**核心属性组**：

| 属性组 | 属性名 | 类型 | 更新策略 | 功能描述 |
|--------|--------|------|----------|----------|
| - | `IsRectInTarget` | bool | PROPERTY_UPDATE_MEASURE | 是否在目标区域内 |
| - | `MenuOffset` | NG::OffsetF | PROPERTY_UPDATE_MEASURE | 菜单偏移量 |
| - | `TargetSize` | NG::SizeF | PROPERTY_UPDATE_MEASURE | 目标节点尺寸 |
| - | `PositionOffset` | NG::OffsetF | PROPERTY_UPDATE_LAYOUT | 相对于光标的偏移 |
| - | `Title` | std::string | PROPERTY_UPDATE_LAYOUT | 菜单标题 |
| - | `MenuPlacement` | Placement | PROPERTY_UPDATE_LAYOUT | 菜单位置 |
| - | `AnchorPosition` | NG::OffsetF | PROPERTY_UPDATE_LAYOUT | 锚点位置 |
| - | `BorderRadius` | BorderRadiusProperty | PROPERTY_UPDATE_MEASURE | 圆角 |
| - | `MenuWidth` | Dimension | PROPERTY_UPDATE_MEASURE | 菜单宽度 |
| - | `ItemDivider` | V2::ItemDivider | PROPERTY_UPDATE_MEASURE | 菜单项分隔线 |
| - | `ItemGroupDivider` | V2::ItemDivider | PROPERTY_UPDATE_MEASURE | 分组分隔线 |
| `MenuItemFontStyle` | `FontSize` | Dimension | PROPERTY_UPDATE_MEASURE | 字体大小 |
| `MenuItemFontStyle` | `FontColor` | Color | PROPERTY_UPDATE_MEASURE | 字体颜色 |
| `MenuItemFontStyle` | `FontWeight` | FontWeight | PROPERTY_UPDATE_MEASURE | 字体粗细 |
| `MenuItemFontStyle` | `FontFamily` | vector<string> | PROPERTY_UPDATE_MEASURE | 字体家族 |
| `SelectMenuAlignOption` | `AlignType` | MenuAlignType | PROPERTY_UPDATE_MEASURE | 对齐类型 |
| `SelectMenuAlignOption` | `Offset` | DimensionOffset | PROPERTY_UPDATE_MEASURE | 偏移量 |
| - | `ExpandingMode` | SubMenuExpandingMode | PROPERTY_UPDATE_MEASURE | 展开模式 |

**SubMenuExpandingMode枚举** (menu_layout_property.h:34):
```cpp
enum class SubMenuExpandingMode { SIDE, EMBEDDED, STACK };
```

### 2. MenuItemLayoutProperty

**源码**: `menu_item_layout_property.h:47`

```cpp
class MenuItemLayoutProperty : public LayoutProperty
```

**核心属性组**：

| 属性组 | 属性名 | 类型 | 更新策略 | 功能描述 |
|--------|--------|------|----------|----------|
| - | `StartIcon` | ImageSourceInfo | PROPERTY_UPDATE_MEASURE | 起始图标 |
| - | `Content` | std::string | PROPERTY_UPDATE_MEASURE | 内容文本 |
| - | `EndIcon` | ImageSourceInfo | PROPERTY_UPDATE_MEASURE | 结束图标 |
| - | `Label` | std::string | PROPERTY_UPDATE_MEASURE | 标签文本 |
| - | `MenuWidth` | Dimension | PROPERTY_UPDATE_MEASURE | 菜单宽度 |
| `SelectIconStyle` | `SelectIcon` | bool | PROPERTY_UPDATE_MEASURE | 是否显示选中图标 |
| `SelectIconStyle` | `SelectIconSrc` | std::string | PROPERTY_UPDATE_MEASURE | 选中图标源 |
| `FontStyle` | `FontSize` | Dimension | PROPERTY_UPDATE_MEASURE | 字体大小 |
| `FontStyle` | `FontColor` | Color | PROPERTY_UPDATE_MEASURE | 字体颜色 |
| `FontStyle` | `FontWeight` | FontWeight | PROPERTY_UPDATE_MEASURE | 字体粗细 |
| `FontStyle` | `FontFamily` | vector<string> | PROPERTY_UPDATE_MEASURE | 字体家族 |
| `LabelFontStyle` | `LabelFontSize` | Dimension | PROPERTY_UPDATE_MEASURE | 标签字体大小 |
| `LabelFontStyle` | `LabelFontColor` | Color | PROPERTY_UPDATE_MEASURE | 标签字体颜色 |
| `LabelFontStyle` | `LabelFontWeight` | FontWeight | PROPERTY_UPDATE_MEASURE | 标签字体粗细 |
| `LabelFontStyle` | `LabelFontFamily` | vector<string> | PROPERTY_UPDATE_MEASURE | 标签字体家族 |

### 3. MenuPaintProperty

**源码**: `menu_paint_property.h:46`

```cpp
class MenuPaintProperty : public PaintProperty
```

**核心属性**：

| 属性名 | 类型 | 更新策略 | 功能描述 |
|--------|------|----------|----------|
| `EnableArrow` | bool | PROPERTY_UPDATE_RENDER | 是否启用箭头 |
| `ArrowOffset` | Dimension | PROPERTY_UPDATE_RENDER | 箭头偏移 |
| `ArrowPosition` | OffsetF | PROPERTY_UPDATE_RENDER | 箭头位置 |
| `ArrowPlacement` | Placement | PROPERTY_UPDATE_RENDER | 箭头方位 |
| `ClipPath` | std::string | PROPERTY_UPDATE_RENDER | 裁剪路径（SVG格式） |

**常量定义** (menu_paint_property.h:28):
```cpp
constexpr Dimension ARROW_WIDTH = 32.0_vp;
constexpr Dimension ARROW_HIGHT = 8.0_vp;
constexpr Dimension TARGET_SECURITY = 8.0_vp;
constexpr Dimension TARGET_SPACE = 8.0_vp;
```

### 4. MenuItemPaintProperty

包含菜单项的绘制属性，如背景色、选中态样式等。

---

## 事件处理

### 1. MenuItemEventHub

**源码**: `menu_item_event_hub.h:27`

```cpp
class MenuItemEventHub : public EventHub
```

**事件类型**：

| 事件类型 | 回调类型 | 功能描述 |
|---------|---------|----------|
| `onChange` | std::function<void(bool)> | 选中状态变化回调 |
| `selectedChangeEvent` | std::function<void(bool)> | 选中事件回调 |
| `menuOnClick` | MenuJSCallback | 点击回调 |
| `onSelect` | OnSelectEvent | Select组件的选中回调 |
| `selectOverlayMenuOnClick` | MenuJSCallback | SelectOverlay菜单点击回调 |

### 2. MenuPattern事件处理

**注册的事件**：

| 事件方法 | 源码位置 | 功能描述 |
|---------|----------|----------|
| `OnTouchEvent()` | menu_pattern.h:769 | 触摸事件处理 |
| `OnKeyEvent()` | menu_pattern.h:778 | 键盘事件（方向键导航） |
| `OnClick()` | menu_pattern.cpp | 点击事件处理 |
| `OnAttachToFrameNode()` | menu_pattern.h:763 | 附加到FrameNode时注册事件 |
| `RegisterOnTouch()` | menu_pattern.cpp | 注册触摸事件 |
| `RegisterOnKeyEvent()` | menu_pattern.cpp | 注册键盘事件 |

**键盘导航支持**:
- 方向键上下：在菜单项之间导航
- Enter键：选中当前菜单项
- Escape键：关闭菜单
- Tab键：禁用（通过`DisableTabInMenu()`）

### 3. MenuWrapperPattern事件处理

**处理的事件**：

| 事件方法 | 源码位置 | 功能描述 |
|---------|----------|----------|
| `OnTouchEvent()` | menu_wrapper_pattern.h:715 | 处理点击外部区域关闭菜单 |
| `HandleMouseEvent()` | menu_wrapper_pattern.h:82 | 处理鼠标事件（PC端） |
| `HandleInteraction()` | menu_wrapper_pattern.h:744 | 处理触摸交互 |
| `ChangeTouchItem()` | menu_wrapper_pattern.cpp | 改变当前触摸的item |
| `FindTouchedMenuItem()` | menu_wrapper_pattern.cpp:749 | 查找触摸的菜单项 |

**点击外部区域关闭**:
- 通过`OnTouchEvent()`检测触摸位置
- 判断是否在菜单区域内（`CheckPointInMenuZone()`）
- 如果不在区域内，调用`HideMenu()`

---

## 主题系统

### 1. MenuTheme

**源码**: `menu_theme.h:50`

```cpp
class MenuTheme : public virtual Theme
```

**Builder模式** (menu_theme.h:54):
```cpp
class Builder {
    RefPtr<MenuTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const;
};
```

**主题常量** (menu_theme.h:25):
```cpp
constexpr Dimension GRADIENT_HEIGHT = Dimension(50, DimensionUnit::VP);
constexpr uint8_t GRADIENT_END_GRADIENT = 255;
constexpr uint32_t DEFAULT_BACKGROUND_COLOR = 0xFFFFFFF;
constexpr uint32_t MENU_MIN_GRID_COUNTS = 2;
constexpr uint32_t MENU_MAX_GRID_COUNTS = 6;
constexpr int32_t HOVER_IMAGE_OPACITY_CHANGE_DURATION = 150;
constexpr int32_t HOVER_IMAGE_DELAY_DURATION = 200;
constexpr int32_t SUB_MENU_SHOW_DELAY_DURATION = 300;
constexpr int32_t SUB_MENU_HIDE_DELAY_DURATION = 500;
```

**核心样式配置**：

#### 动画相关

| 属性名 | 默认值 | 功能描述 |
|--------|--------|----------|
| `filterAnimationDuration_` | 250ms | 过滤动画时长 |
| `previewAnimationDuration_` | 300ms | 预览动画时长 |
| `hoverImageSwitchToPreviewOpacityDuration_` | 150ms | Hover到预览的透明度动画时长 |
| `hoverImageDelayDuration_` | 200ms | Hover延迟时长 |
| `hoverImageDelayDurationForInterrupt_` | 350ms | Hover中断延迟时长 |
| `hoverImageCustomPreviewScaleDuration_` | 650ms | 自定义预览缩放时长 |
| `hoverImagePreviewDisappearDuration_` | 450ms | 预览消失时长 |
| `previewBeforeAnimationScale_` | 0.95f | 预览前缩放 |
| `previewAfterAnimationScale_` | 1.1f | 预览后缩放 |
| `menuAnimationScale_` | 0.4f | 菜单动画缩放 |
| `menuDragAnimationScale_` | 0.95f | 拖拽动画缩放 |
| `springMotionResponse_` | 0.416f | 弹性动画响应 |
| `springMotionDampingFraction_` | 0.73f | 弹性动画阻尼 |
| `contextMenuAppearDuration_` | 250ms | 上下文菜单出现时长 |
| `disappearDuration_` | 250ms | 消失时长 |
| `previewDisappearSpringMotionResponse_` | 0.304f | 预览消失弹性响应 |
| `previewDisappearSpringMotionDampingFraction_` | 0.97f | 预览消失弹性阻尼 |
| `previewMenuScaleNumber_` | 0.95f | 预览菜单缩放数值 |

#### 模糊背景效果

| 属性名 | 默认值 | 功能描述 |
|--------|--------|----------|
| `bgBlurEffectEnable_` | 0 | 是否启用模糊 |
| `bgEffectSaturation_` | 1.0 | 模糊饱和度 |
| `bgEffectBrightness_` | 1.0 | 模糊亮度 |
| `bgEffectRadius_` | 0.0_vp | 模糊半径 |
| `bgEffectColor_` | Color::TRANSPARENT | 模糊颜色 |
| `menuBackGroundBlurStyle_` | COMPONENT_ULTRA_THICK | 模糊样式 |
| `hasBackBlur_` | 1 | 是否有背景模糊 |
| `hasFilter_` | true | 是否有过滤效果 |
| `filterRadius_` | 100.0f | 过滤半径 |

#### 双边框效果

| 属性名 | 默认值 | 功能描述 |
|--------|--------|----------|
| `doubleBorderEnable_` | 0 | 是否启用双边框 |
| `outerBorderWidth_` | 1.0 | 外边框宽度 |
| `outerBorderRadius_` | 19.75f | 外边框圆角 |
| `outerBorderColor_` | Color::TRANSPARENT | 外边框颜色 |
| `innerBorderWidth_` | 1.0 | 内边框宽度 |
| `innerBorderRadius_` | 0.0_vp | 内边框圆角 |
| `innerBorderColor_` | Color::TRANSPARENT | 内边框颜色 |

#### 字体缩放

| 属性名 | 默认值 | 功能描述 |
|--------|--------|----------|
| `bigFontSizeScale_` | 1.75f | 大字体缩放 |
| `largeFontSizeScale_` | 2.0f | 更大字体缩放 |
| `maxFontSizeScale_` | 3.2f | 最大字体缩放 |
| `textMaxLines_` | INT_MAX | 文本最大行数 |

#### 其他样式

| 属性名 | 默认值 | 功能描述 |
|--------|--------|----------|
| `menuShadowStyle_` | OuterDefaultMD | 菜单阴影样式 |
| `previewBorderRadius_` | 16.0_vp | 预览圆角 |
| `previewMenuMaskColor_` | 0x33182431 | 预览遮罩颜色 |
| `menuOutlineColor_` | 0x19FFFFFF | 菜单轮廓颜色 |
| `subMenuShowDelayDuration_` | 300ms | 子菜单显示延迟 |
| `subMenuHideDelayDuration_` | 500ms | 子菜单隐藏延迟 |
| `menuHapticFeedback_` | "haptic.long_press_medium" | 触觉反馈类型 |

**主题获取方法**:

```cpp
auto menuTheme = pipelineContext->GetTheme<MenuTheme>();
```

---

## 动画系统

### 1. 菜单出现动画

**Preview模式动画**：

| 动画方法 | 源码位置 | 功能描述 |
|---------|----------|----------|
| `ShowPreviewMenuAnimation()` | menu_pattern.cpp | 预览菜单动画 |
| `ShowPreviewMenuScaleAnimation()` | menu_pattern.cpp | 缩放动画 |
| `ShowPreviewPositionAnimation()` | menu_pattern.cpp | 位置动画 |

**普通菜单动画**：

| 动画方法 | 源码位置 | 功能描述 |
|---------|----------|----------|
| `ShowMenuAppearAnimation()` | menu_pattern.cpp | 普通出现动画 |
| `ShowStackMenuAppearAnimation()` | menu_pattern.cpp | Stack展开动画 |

### 2. 菜单消失动画

**源码**: `menu_pattern.h:537`

| 动画方法 | 功能描述 |
|---------|----------|
| `ShowMenuDisappearAnimation()` | 普通消失动画 |
| `ShowStackMenuDisappearAnimation()` | Stack消失动画 |

**消失动画类型**:
- `hasAnimation_ = false`: 从BOTTOM到TOP消失
- `hasAnimation_ = true`: 从LEFT_BOTTOM到RIGHT_TOP消失

### 3. 箭头旋转动画

| 动画方法 | 源码位置 | 功能描述 |
|---------|----------|----------|
| `ShowArrowRotateAnimation()` | menu_pattern.cpp:796 | 箭头旋转动画（展开） |
| `ShowArrowReverseRotateAnimation()` | menu_pattern.cpp:797 | 箭头反向旋转（收起） |

### 4. 背景色动画

**MenuItemPattern**：

| 动画方法 | 源码位置 | 功能描述 |
|---------|----------|----------|
| `PlayBgColorAnimation()` | menu_item_pattern.cpp:240 | 播放背景色动画（hover效果） |
| `UpdateDividerHoverStatus()` | menu_item_pattern.cpp | 更新分隔线hover状态 |
| `UpdateDividerPressStatus()` | menu_item_pattern.cpp | 更新分隔线按下状态 |
| `UpdateDividerSelectedStatus()` | menu_item_pattern.cpp | 更新分隔线选中状态 |

### 5. 动画参数

**PreviewMenuAnimationInfo** (menu_pattern.h:63):
```cpp
struct PreviewMenuAnimationInfo {
    BorderRadiusProperty borderRadius;
    float clipRate = -1.0f;
};
```

---

## 执行流程

### 1. Menu创建流程

```
1. ArkTS/JS调用bindMenu()
   ↓
2. MenuModelNG::Create()
   ↓
3. MenuView::Create() [创建FrameNode]
   ↓
4. 创建节点层次结构:
   MenuWrapperPattern
   ├─ MenuPattern
   │  └─ InnerMenuPattern
   └─ MenuPreviewPattern (可选)
   ↓
5. 添加MenuItem/MenuItemGroup子节点
   ↓
6. OnAttachToFrameNode() → 初始化事件
   ↓
7. OnModifyDone() → 初始化主题、样式
   ↓
8. OnAttachToMainTree() → 触发显示动画
   ↓
9. 菜单显示完成
```

### 2. MenuItem点击流程

```
1. 用户点击MenuItem
   ↓
2. MenuItemPattern::OnClick()
   ↓
3. 检查是否有子菜单
   ├─ 有子菜单 → ShowSubMenu()
   │              ├─ 计算子菜单位置
   │              ├─ 创建子菜单节点
   │              ├─ ShowSubMenuAnimation()
   │              └─ 更新箭头状态
   └─ 无子菜单 → 触发onClick回调
                  ├─ MenuItemEventHub::menuOnClick_
                  ├─ 隐藏菜单 (HideMenu)
                  └─ 触发消失动画
```

### 3. 布局测量流程

```
1. MenuLayoutAlgorithm::Measure()
   ↓
2. Initialize() → 初始化参数
   ├─ 获取目标节点尺寸和位置
   ├─ 计算安全区域边界
   └─ 初始化Padding和Margin
   ↓
3. CreateChildConstraint() → 创建子节点约束
   ├─ 根据目标尺寸计算约束
   ├─ 应用主题样式
   └─ 处理Preview模式
   ↓
4. 测量所有子节点
   ├─ MenuItem
   ├─ MenuItemGroup
   └─ MenuDivider
   ↓
5. GetSelectChildPosition() → 计算菜单位置
   ↓
6. MenuLayoutAvoidAlgorithm() → 避障处理
   ├─ 检查是否超出屏幕边界
   ├─ 调整菜单位置
   └─ 更新Placement
   ↓
7. LayoutArrow() → 计算箭头位置
   ↓
8. CalculateMenuPath() → 计算裁剪路径
   ↓
9. 测量完成
```

### 4. 子菜单显示流程

```
1. MenuItem触发ShowSubMenu()
   ↓
2. 检查ExpandingMode
   ├─ SIDE → 侧边显示
   │        ├─ 计算相对于父菜单的位置
   │        └─ 避障处理
   ├─ EMBEDDED → 嵌入式显示
   │              ├─ 展开在父菜单内部
   │              └─ 更新父菜单高度
   └─ STACK → Stack显示
              ├─ 在新窗口中显示
              └─ 添加转场动画
   ↓
3. 创建子菜单节点
   ↓
4. ShowSubMenuAnimation()
   ↓
5. 更新父MenuItem状态
   ├─ 旋转箭头图标
   └─ 设置isSubMenuShowed_ = true
```

---

## 完整API清单

### 1. MenuModelNG API

**源码**：`frameworks/core/components_ng/pattern/menu/menu_model_ng.h:22-76`

#### 创建和配置

```cpp
// 创建菜单
void Create() override;

// 字体属性
void SetFontSize(const Dimension& fontSize);
void SetFontWeight(FontWeight weight);
void SetFontStyle(Ace::FontStyle style);
void SetFontColor(const std::optional<Color>& color);
void SetFontFamily(const std::vector<std::string>& families);
void ResetFontFamily();

// 布局属性
void SetWidth(const Dimension& width);
void SetBorderRadius(const Dimension& radius);
void ResetBorderRadius();
void SetBorderRadius(
    const std::optional<Dimension>& radiusTopLeft,
    const std::optional<Dimension>& radiusTopRight,
    const std::optional<Dimension>& radiusBottomLeft,
    const std::optional<Dimension>& radiusBottomRight
);

// 子菜单展开模式
void SetExpandingMode(const SubMenuExpandingMode& expandingMode);

// 分割线
void SetItemDivider(const V2::ItemDivider& divider, const DividerMode& mode);
void SetItemGroupDivider(const V2::ItemDivider& divider, const DividerMode& mode);

// 资源对象
void CreateWithColorResourceObj(
    const RefPtr<ResourceObject>& resObj,
    const MenuColorType menuColorType
);
void CreateWithDimensionResourceObj(
    const RefPtr<ResourceObject>& resObj,
    const MenuDimensionType menuDimensionType
);
void CreateWithFontFamilyResourceObj(
    const RefPtr<ResourceObject>& resObj,
    MenuFamilyType type
);

// 静态方法（直接操作 FrameNode）
static RefPtr<FrameNode> CreateMenu();
static RefPtr<FrameNode> CreateMenu(int32_t nodeId);
static void SetFontSize(FrameNode* frameNode, const Dimension& fontSize);
static void SetFontWeight(FrameNode* frameNode, FontWeight weight);
static void SetFontStyle(FrameNode* frameNode, Ace::FontStyle style);
static void SetFontFamily(FrameNode* frameNode,
    const std::vector<std::string>& families);
static void SetBorderRadius(FrameNode* frameNode, const Dimension& radius);
static void ResetBorderRadius(FrameNode* frameNode);
static void SetBorderRadius(
    FrameNode* frameNode,
    const std::optional<Dimension>& radiusTopLeft,
    const std::optional<Dimension>& radiusTopRight,
    const std::optional<Dimension>& radiusBottomLeft,
    const std::optional<Dimension>& radiusBottomRight
);
static void SetWidth(FrameNode* frameNode, const Dimension& width);
static void SetItemDivider(FrameNode* frameNode,
    const V2::ItemDivider& divider, const DividerMode& mode);
static void SetItemGroupDivider(FrameNode* frameNode,
    const V2::ItemDivider& divider, const DividerMode& mode);
static void SetExpandingMode(FrameNode* frameNode,
    const SubMenuExpandingMode& expandingMode);
static void SetBorderRadius(FrameNode* frameNode,
    const NG::BorderRadiusProperty& borderRadius);
static void SetExpandSymbol(FrameNode* frameNode,
    const std::function<void(WeakPtr<NG::FrameNode>)>& expandSymbol);
static void CreateWithColorResourceObj(
    FrameNode* frameNode,
    const RefPtr<ResourceObject>& resObj,
    const MenuColorType menuColorType);
static void CreateWithDimensionResourceObj(
    FrameNode* frameNode,
    const RefPtr<ResourceObject>& resObj,
    const MenuDimensionType menuDimensionType);
static void CreateWithFontFamilyResourceObj(
    FrameNode* frameNode,
    const RefPtr<ResourceObject>& resObj,
    MenuFamilyType type);
```

### 2. MenuPattern API

**源码**：`frameworks/core/components_ng/pattern/menu/menu_pattern.h:70-893`

#### 菜单类型判断

```cpp
// 菜单类型查询
bool IsContextMenu() const;
bool IsNavigationMenu() const;
bool IsMultiMenu() const;
bool IsDesktopMenu() const;
bool IsMenu() const;
bool IsSubMenu() const;
bool IsSelectOverlayExtensionMenu() const;
bool IsSelectOverlayCustomMenu() const;
bool IsSelectOverlaySubMenu() const;
bool IsSelectOverlayRightClickMenu() const;
```

#### 菜单操作

```cpp
// 显示/隐藏
void HideMenu(const HideMenuType& reason);
void HideSubMenu();
void ShowMenuAppearAnimation();
void ShowStackMenuAppearAnimation();

// 获取节点
RefPtr<FrameNode> GetMenuWrapper() const;
RefPtr<FrameNode> GetFirstInnerMenu() const;
RefPtr<MenuPattern> GetMainMenuPattern() const;

// 目标信息
int32_t GetTargetId() const;
const std::string& GetTargetTag() const;

// 菜单项管理
void AddOptionNode(const RefPtr<FrameNode>& option);
void PopOptionNode();
const std::vector<RefPtr<FrameNode>>& GetOptions() const;
void AddMenuItemNode(const RefPtr<FrameNode>& menuItem);
const std::vector<RefPtr<FrameNode>>& GetMenuItems() const;
std::vector<RefPtr<FrameNode>>& GetEmbeddedMenuItems();
void AddEmbeddedMenuItem(const RefPtr<FrameNode>& menuItem);

// 状态管理
void SetPreviewMode(MenuPreviewMode mode);
MenuPreviewMode GetPreviewMode() const;
void SetIsSelectMenu(bool isSelectMenu);
bool IsSelectMenu() const;
void SetIsFirstShow(bool isFirstShow);
bool GetIsFirstShow() const;

// 样式更新
void UpdateSelectParam(const std::vector<SelectParam>& params);
void SetSelectProperties(const std::vector<SelectParam>& params);
```

### 3. MenuItemPattern API

**源码**：`frameworks/core/components_ng/pattern/menu/menu_item_pattern.h:45-687`

#### 选中状态

```cpp
void SetSelected(bool isSelected);
bool IsSelected() const;
void MarkIsSelected(bool isSelected);
```

#### 子菜单管理

```cpp
// 显示子菜单
void ShowSubMenu(ShowSubMenuType type = ShowSubMenuType::DEFAULT);
    // ShowSubMenuType:
    //   - DEFAULT (0)
    //   - HOVER (1)
    //   - CLICK (2)
    //   - LONG_PRESS (3)
    //   - KEY_DPAD_RIGHT (4)
    //   - ACTION (5)

// 隐藏子菜单
void HideSubMenu();

// 子菜单状态
bool IsSubMenuShowed() const;
void SetIsSubMenuShowed(bool isSubMenuShowed);
bool IsSubMenuHovered() const;
void SetIsSubMenuHovered(bool isSubMenuHovered);
```

#### 样式更新

```cpp
// 背景颜色
void SetBgColor(const Color& color);
Color GetBgColor();

// 字体颜色
void SetFontColor(const Color& color, bool isNeedRecord = true);
Color GetFontColor();

// 字体大小
void SetFontSize(const Dimension& value);
Dimension GetFontSize();

// 字体粗细
void SetFontWeight(const FontWeight& value);
FontWeight GetFontWeight();

// 斜体
void SetItalicFontStyle(const Ace::FontStyle& value);
Ace::FontStyle GetItalicFontStyle();

// 字体家族
void SetFontFamily(const std::vector<std::string>& value);
std::vector<std::string> GetFontFamily();

// 边框
void SetBorderColor(const Color& color);
Color GetBorderColor() const;
void SetBorderWidth(const Dimension& value);
Dimension GetBorderWidth() const;
```

#### 节点获取

```cpp
RefPtr<FrameNode> GetContentNode();
RefPtr<FrameNode> GetLabelNode();
RefPtr<FrameNode> GetMenu(bool needTopMenu = false);
RefPtr<MenuPattern> GetMenuPattern(bool needTopMenu = false);
RefPtr<FrameNode> GetTopDivider();
RefPtr<FrameNode> GetBottomDivider();
```

#### 事件处理

```cpp
void OnHover(bool isHover);
void CloseMenu();
void OnTouch(const TouchEventInfo& info);
bool OnKeyEvent(const KeyEvent& event);
bool OnClick();
```

### 4. MenuLayoutAlgorithm API

**源码**：`frameworks/core/components_ng/pattern/menu/menu_layout_algorithm.h:78-393`

#### 布局计算

```cpp
void Measure(LayoutWrapper* layoutWrapper) override;
void Layout(LayoutWrapper* layoutWrapper) override;
```

#### 位置计算

```cpp
// 避让算法
OffsetF MenuLayoutAvoidAlgorithm(
    const RefPtr<MenuLayoutProperty>& menuProp,
    const RefPtr<MenuPattern>& menuPattern,
    const SizeF& size,
    bool didNeedArrow = false,
    LayoutWrapper* layoutWrapper = nullptr
);

// Select 避让算法
OffsetF SelectLayoutAvoidAlgorithm(
    const RefPtr<MenuLayoutProperty>& menuProp,
    const RefPtr<MenuPattern>& menuPattern,
    const SizeF& size,
    bool didNeedArrow = false,
    LayoutWrapper* layoutWrapper = nullptr
);

// 根据 Placement 获取位置
OffsetF GetPositionWithPlacement(
    const SizeF& childSize,
    const OffsetF& topPosition,
    const OffsetF& bottomPosition
);

// 适配屏幕位置
OffsetF FitToScreen(
    const OffsetF& position,
    const SizeF& childSize,
    bool didNeedArrow = false
);
```

#### 箭头相关

```cpp
void LayoutArrow(const LayoutWrapper* layoutWrapper);
OffsetF GetArrowPositionWithPlacement(
    const SizeF& menuSize,
    const LayoutWrapper* layoutWrapper
);
bool GetIfNeedArrow(
    const LayoutWrapper* layoutWrapper,
    const SizeF& menuSize
);
```

#### Preview 菜单

```cpp
void LayoutPreviewMenu(LayoutWrapper* layoutWrapper);
void GetPreviewNodeAndMenuNodeTotalSize(
    const RefPtr<FrameNode>& frameNode,
    RefPtr<LayoutWrapper>& previewLayoutWrapper,
    RefPtr<LayoutWrapper>& menuLayoutWrapper
);
```

### 5. MenuLayoutProperty API

**源码**：`frameworks/core/components_ng/pattern/menu/menu_layout_property.h:50-162`

#### 位置和尺寸

```cpp
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsRectInTarget, bool, PROPERTY_UPDATE_MEASURE)
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(MenuOffset, NG::OffsetF, PROPERTY_UPDATE_MEASURE)
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(TargetSize, NG::SizeF, PROPERTY_UPDATE_MEASURE)
```

#### 样式属性

```cpp
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BorderRadius, NG::BorderRadiusProperty, PROPERTY_UPDATE_MEASURE)
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(MenuWidth, Dimension, PROPERTY_UPDATE_MEASURE)
```

#### 字体样式组

```cpp
ACE_DEFINE_PROPERTY_GROUP(MenuItemFontStyle, MenuItemFontStyle)
ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(MenuItemFontStyle, FontSize, Dimension, PROPERTY_UPDATE_MEASURE)
ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(MenuItemFontStyle, FontColor, Color, PROPERTY_UPDATE_MEASURE)
ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(MenuItemFontStyle, FontColorSetByUser, bool, PROPERTY_UPDATE_MEASURE)
ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(MenuItemFontStyle, FontWeight, FontWeight, PROPERTY_UPDATE_MEASURE)
ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(MenuItemFontStyle, FontFamily, std::vector<std::string>, PROPERTY_UPDATE_MEASURE)
ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(MenuItemFontStyle, ItalicFontStyle, Ace::FontStyle, PROPERTY_UPDATE_MEASURE)
```

#### 对齐选项

```cpp
ACE_DEFINE_PROPERTY_GROUP(SelectMenuAlignOption, SelectMenuAlignOption)
ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SelectMenuAlignOption, AlignType, MenuAlignType, PROPERTY_UPDATE_MEASURE)
ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SelectMenuAlignOption, Offset, DimensionOffset, PROPERTY_UPDATE_MEASURE)
```

#### 分割线

```cpp
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ItemDivider, V2::ItemDivider, PROPERTY_UPDATE_MEASURE)
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ItemDividerMode, DividerMode, PROPERTY_UPDATE_MEASURE)
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ItemGroupDivider, V2::ItemDivider, PROPERTY_UPDATE_MEASURE)
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ItemGroupDividerMode, DividerMode, PROPERTY_UPDATE_MEASURE)
```

### 6. MenuPaintProperty API

**源码**：`frameworks/core/components_ng/pattern/menu/menu_paint_property.h:46-118`

#### 箭头相关

```cpp
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EnableArrow, bool, PROPERTY_UPDATE_RENDER)
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ArrowOffset, Dimension, PROPERTY_UPDATE_RENDER)
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ArrowPosition, OffsetF, PROPERTY_UPDATE_RENDER)
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ArrowPlacement, Placement, PROPERTY_UPDATE_RENDER)
```

#### 裁剪路径

```cpp
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ClipPath, std::string, PROPERTY_UPDATE_RENDER)
```

---

## 关键实现细节

### 1. 菜单类型

**源码**：`menu_pattern.h:151-246`

```cpp
enum class MenuType {
    MENU,                              // 普通下拉菜单
    CONTEXT_MENU,                      // 上下文菜单（右键菜单）
    SUB_MENU,                          // 子菜单
    NAVIGATION_MENU,                   // 导航菜单
    MULTI_MENU,                        // 多列菜单
    DESKTOP_MENU,                      // 桌面菜单
    SELECT_OVERLAY_EXTENSION_MENU,     // 选择覆盖扩展菜单
    SELECT_OVERLAY_CUSTOM_MENU,        // 选择覆盖自定义菜单
    SELECT_OVERLAY_SUB_MENU,           // 选择覆盖子菜单
    SELECT_OVERLAY_RIGHT_CLICK_MENU    // 选择覆盖右键菜单
};
```

### 2. 子菜单展开模式

**源码**：`menu_layout_property.h:34`

```cpp
enum class SubMenuExpandingMode {
    SIDE,      // 侧边展开（默认）
    EMBEDDED,  // 嵌入式展开
    STACK      // 堆叠式展开
};
```

**使用场景**：
- **SIDE**：子菜单在父菜单项的右侧/左侧展开（桌面端常见）
- **EMBEDDED**：子菜单嵌入父菜单内部展开（移动端常见）
- **STACK**：子菜单以堆叠动画方式展开（平板等大屏设备）

### 3. 菜单定位（Placement）

**源码**：`menu_layout_algorithm.h:318`

```cpp
Placement placement_ = Placement::BOTTOM_LEFT;
```

**支持的 Placement**：

**基础 Placement**：
- `LEFT`, `RIGHT`, `TOP`, `BOTTOM`
- `TOP_LEFT`, `TOP_RIGHT`, `BOTTOM_LEFT`, `BOTTOM_RIGHT`

**组合 Placement**：
- `LEFT_TOP`, `LEFT_BOTTOM`, `RIGHT_TOP`, `RIGHT_BOTTOM`

**NONE**：自动定位

### 4. 菜单避让算法

**源码**：`menu_layout_algorithm.h:173-177`

**算法目标**：
- 确保菜单不超出屏幕边界
- 当菜单在指定 Placement 会超出屏幕时，自动调整到合适位置
- 考虑箭头显示空间

**算法流程**：
```
1. 计算理想位置（根据 Placement）
2. 检查是否超出屏幕边界
3. 如果超出：
   a. 尝试调整 Placement（如 BOTTOM_LEFT → TOP_LEFT）
   b. 如果仍超出，尝试其他 Placement
   c. 确保菜单完全在屏幕内
4. 考虑箭头显示空间（TARGET_SPACE = 8.0_vp）
5. 返回最终位置
```

### 5. 菜单状态机

**源码**：`menu_wrapper_pattern.h:40`

```cpp
enum class MenuStatus {
    INIT,              // 初始化状态
    ON_SHOW_ANIMATION, // 显示动画中
    SHOW,              // 已显示
    ON_HIDE_ANIMATION, // 隐藏动画中
    HIDE               // 已隐藏
};
```

### 6. 触摸事件处理

**源码**：`menu_pattern.cpp:OnTouchEvent()`

```cpp
void MenuPattern::OnTouchEvent(const TouchEventInfo& info)
```

**处理流程**：
1. 检测点击位置
2. 判断是否点击在菜单外部
3. 如果是，调用 `HideMenu()`
4. 否则传递给子组件处理

### 7. 焦点管理

**源码**：`menu_pattern.h:84-92`

```cpp
FocusPattern GetFocusPattern() const override {
    return { FocusType::SCOPE, true };
}
```

**焦点类型**：
- `FocusType::SCOPE` - 菜单是焦点作用域
- `FocusType::NODE` - 菜单项是独立焦点节点

### 8. 主题系统

**源码**：`menu_theme.h:50-496`

**主题参数**：
```cpp
// 动画时长
int32_t hoverImageSwitchToPreviewOpacityDuration_ = 150;
int32_t hoverImageDelayDuration_ = 200;
int32_t hoverImageCustomPreviewScaleDuration_ = 650;
float previewBeforeAnimationScale_ = 0.95f;
float previewAfterAnimationScale_ = 1.1f;
int32_t contextMenuAppearDuration_ = 250;

// 箭头
Dimension ARROW_WIDTH = 32.0_vp;
Dimension ARROW_HIGHT = 8.0_vp;
Dimension TARGET_SECURITY = 8.0_vp;

// 安全边距
Dimension PORTRAIT_TOP_SECURITY = 48.0_vp;
Dimension PORTRAIT_BOTTOM_SECURITY = 48.0_vp;
```

---

## 子窗机制

### 概述

Menu 组件支持在**子窗（SubWindow）**中显示，这是 OpenHarmony 特有的一种窗口机制。子窗是附着在主窗口上的独立窗口，可以提供更好的性能和更灵活的布局控制。

**核心概念**：
- **SubWindow**: 独立于主窗口的窗口对象，拥有独立的渲染上下文
- **SubwindowManager**: 单例管理器，负责创建、销毁和管理所有子窗
- **ContainerId**: 子窗容器ID，用于标识不同的子窗实例
- **ShowInSubWindow**: 控制菜单是否在子窗中显示的属性

### 子窗架构

```
┌─────────────────────────────────────────────────────────┐
│ 主窗口 (Main Window)                                      │
│ ┌─────────────────────────────────────────────────────┐ │
│ │ AceContainer                                         │ │
│ │  - PipelineContext                                  │ │
│ │  - OverlayManager                                   │ │
│ │  - UI Tree (Application Content)                    │ │
│ └─────────────────────────────────────────────────────┘ │
│                          ↑                              │
│                          │ 创建和管理                  │
│                          ↓                              │
│ ┌─────────────────────────────────────────────────────┐ │
│ │ SubwindowManager (Singleton)                        │ │
│ │  - CreateSubwindow()                                │ │
│ │  - HideMenuNG()                                     │ │
│ │  - ShowMenuNG()                                     │ │
│ └─────────────────────────────────────────────────────┘ │
│                          ↑                              │
│                          │ 通信                        │
│                          ↓                              │
│ ┌─────────────────────────────────────────────────────┐ │
│ │ 子窗 (SubWindow) - TYPE_MENU                         │ │
│ │ ┌─────────────────────────────────────────────────┐ │ │
│ │ │ SubwindowOhos                                    │ │ │
│ │ │  - Window (Rosen)                                │ │ │
│ │ │  - AceContainer (Child)                          │ │ │
│ │ │  - MenuWrapper FrameNode                         │ │ │
│ │ │  └─ Menu FrameNode                               │ │ │
│ │ └─────────────────────────────────────────────────┘ │ │
│ └─────────────────────────────────────────────────────┘ │
└─────────────────────────────────────────────────────────┘
```

### 核心类关系

#### 1. Subwindow 基类

**源码**: `base/subwindow/subwindow.h`

```cpp
class Subwindow : public AceType {
public:
    virtual void ShowMenuNG(
        const RefPtr<NG::FrameNode> customNode,
        const NG::MenuParam& menuParam,
        const RefPtr<NG::FrameNode>& targetNode,
        const NG::OffsetF& offset
    ) = 0;

    virtual void HideMenuNG(
        const RefPtr<NG::FrameNode>& menu,
        int32_t targetId
    ) = 0;

    virtual void ClearMenuNG(
        int32_t targetId,
        bool inWindow,
        bool showAnimation = false
    ) = 0;

    virtual void HideSubWindowNG() = 0;
    virtual NG::RectF GetRect() const = 0;
};
```

#### 2. SubwindowOhos 实现类

**源码**: `adapter/ohos/entrance/subwindow/subwindow_ohos.h:51`

```cpp
class SubwindowOhos : public Subwindow {
    DECLARE_ACE_TYPE(SubwindowOhos, Subwindow);

public:
    explicit SubwindowOhos(int32_t instanceId);
    ~SubwindowOhos() = default;

    // 子窗初始化
    void InitContainer() override;
    void ResizeWindow() override;
    void ResizeWindowForMenu() override;

    // Menu 相关方法
    void ShowMenuNG(
        const RefPtr<NG::FrameNode> customNode,
        const NG::MenuParam& menuParam,
        const RefPtr<NG::FrameNode>& targetNode,
        const NG::OffsetF& offset
    ) override;

    void ShowMenuNG(
        std::function<void()>&& buildFunc,
        std::function<void()>&& previewBuildFunc,
        const NG::MenuParam& menuParam,
        const RefPtr<NG::FrameNode>& targetNode,
        const NG::OffsetF& offset
    ) override;

    void HideMenuNG(
        const RefPtr<NG::FrameNode>& menu,
        int32_t targetId
    ) override;

    void HideMenuNG(
        bool showPreviewAnimation,
        bool startDrag
    ) override;

    void ClearMenuNG(
        int32_t targetId,
        bool inWindow,
        bool showAnimation = false
    ) override;

    // Preview 相关方法
    bool ShowPreviewNG(bool isStartDraggingFromSubWindow = false) override;
    void HidePreviewNG() override;
    void UpdatePreviewPosition() override;
    bool GetMenuPreviewCenter(NG::OffsetF& offset) override;

    // 窗口管理
    void HideSubWindowNG() override;
    NG::RectF GetRect() override;
    void SetRect(const NG::RectF& rect) override;
    void SetWindowTouchable(bool touchable) override;

    // 获取容器信息
    int32_t GetChildContainerId() const override { return childContainerId_; }
    Rect GetParentWindowRect() const override;
};
```

**核心成员变量**：
```cpp
int32_t instanceId_;              // 实例ID
int32_t childContainerId_;         // 子容器ID
sptr<OHOS::Rosen::Window> window_; // Rosen 窗口对象
RefPtr<AceContainer> container_;   // Ace 容器
bool isShowed_;                    // 是否已显示
```

#### 3. SubwindowManager 管理器

**源码**: `base/subwindow/subwindow_manager.h`

**核心方法**：
```cpp
class SubwindowManager {
public:
    static SubwindowManager* GetInstance();

    // 创建子窗
    RefPtr<Subwindow> CreateSubwindow(int32_t instanceId);

    // Menu 操作
    void ShowMenuNG(
        const RefPtr<NG::FrameNode>& menuNode,
        const NG::MenuParam& menuParam,
        const RefPtr<NG::FrameNode>& targetNode,
        const NG::OffsetF& offset
    );

    void HideMenuNG(const RefPtr<NG::FrameNode>& menuWrapper, int32_t targetId);
    void HideMenuNG(bool showPreviewAnimation = false, bool startDrag = false);
    void ClearMenuNG(int32_t containerId, int32_t targetId);

    // 子窗查询
    RefPtr<Subwindow> GetSubwindowById(int32_t instanceId);
    RefPtr<Subwindow> GetSubwindowByType(int32_t containerId, SubwindowType type);
    bool IsSubwindowExist(const RefPtr<Subwindow>& subwindow);

    // 容器管理
    int32_t GetParentContainerId(int32_t containerId);
    void SetParentContainerId(int32_t containerId, int32_t parentContainerId);

private:
    std::unordered_map<int32_t, RefPtr<Subwindow>> subwindows_;
    std::unordered_map<int32_t, int32_t> parentContainerMap_;
};
```

**SubwindowType 枚举**：
```cpp
enum class SubwindowType {
    TYPE_MENU,        // 菜单子窗
    TYPE_DIALOG,      // 对话框子窗
    TYPE_TOAST,       // Toast 子窗
    TYPE_PICKER,      // 选择器子窗
    TYPE_PANEL        // 面板子窗
};
```

### Menu 子窗显示机制

#### 1. 显示条件判断

**源码**: `menu_pattern.cpp:960-970`

```cpp
void MenuPattern::HideMenu(bool isMenuOnTouch, OffsetF position, const HideMenuType& reason) const
{
    auto layoutProperty = rootMenuPattern->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    // 获取是否在子窗中显示的属性
    bool isShowInSubWindow = layoutProperty->GetShowInSubWindowValue(true);
    auto wrapper = GetMenuWrapper();
    CHECK_NULL_VOID(wrapper);

    if (wrapper->GetTag() == V2::SELECT_OVERLAY_ETS_TAG) {
        return;
    }

    // 判断是否使用子窗显示
    // 1. ContextMenu 强制使用子窗
    // 2. expandDisplay 模式 + isShowInSubWindow = true
    if (((IsContextMenu() || (expandDisplay && isShowInSubWindow))) && !IsSelectMenu()) {
        TAG_LOGI(AceLogTag::ACE_MENU, "will hide menu, targetNode id %{public}d. reason %{public}d",
            targetId_, reason);
        SubwindowManager::GetInstance()->HideMenuNG(wrapper, targetId_);
        DoCloseSubMenus();
        return;
    }

    // Select 菜单特殊处理
    if (IsSelectMenu() && expandDisplay && layoutProperty->GetShowInSubWindowValue(false)) {
        auto subWindowManager = SubwindowManager::GetInstance();
        CHECK_NULL_VOID(subWindowManager);
        auto containerId = Container::CurrentId();
        auto subwindow = subWindowManager->GetSubwindowByType(containerId, SubwindowType::TYPE_MENU);
        if (subWindowManager->IsSubwindowExist(subwindow)) {
            subWindowManager->ClearMenuNG(containerId, targetId_);
            return;
        }
    }
}
```

**显示条件**：
1. **ContextMenu**：强制使用子窗显示
2. **expandDisplay 模式**：平板/大屏设备上的展开菜单
3. **showInSubWindow 属性**：显式设置在子窗中显示

#### 2. 布局算法中的子窗判断

**源码**: `menu_layout_algorithm.cpp:3549-3582`

```cpp
void MenuLayoutAlgorithm::InitCanExpandCurrentWindow(
    bool isContextMenu, const RefPtr<MenuLayoutProperty>& menuLayoutProperty)
{
    CHECK_NULL_VOID(menuLayoutProperty);

    // 获取 showInSubWindow 属性
    showInSubWindow_ = menuLayoutProperty->GetShowInSubWindowValue(false) || isContextMenu;
    dumpInfo_.showInSubWindow = showInSubWindow_;

    if (!showInSubWindow_) {
        canExpandCurrentWindow_ = false;
        return;
    }

    // 手机端的子窗与主窗口尺寸相同
    // 因此手机端的子窗菜单无法扩展当前窗口
    canExpandCurrentWindow_ = IsExpandDisplay();

    auto containerId = Container::CurrentId();
    auto container = AceEngine::Get().GetContainer(containerId);

    // 如果当前是子容器，获取父容器
    if (containerId >= MIN_SUBCONTAINER_ID) {
        auto parentContainerId = SubwindowManager::GetInstance()->GetParentContainerId(containerId);
        container = AceEngine::Get().GetContainer(parentContainerId);
    }

    CHECK_NULL_VOID(container);

    // 处理 UIExtension 子窗的特殊情况
    if (containerId >= MIN_SUBCONTAINER_ID) {
        isUIExtensionSubWindow_ = container->IsUIExtensionWindow();
        if (isUIExtensionSubWindow_) {
            // UIExtension 窗口可以被菜单扩展
            canExpandCurrentWindow_ = true;
            auto subwindow = SubwindowManager::GetInstance()->GetSubwindowById(containerId);
            CHECK_NULL_VOID(subwindow);
            auto rect = subwindow->GetUIExtensionHostWindowRect();
            UIExtensionHostWindowRect_ = RectF(rect.Left(), rect.Top(), rect.Width(), rect.Height());
            TAG_LOGI(AceLogTag::ACE_MENU, "GetUIExtensionHostWindowRect : %{public}s",
                UIExtensionHostWindowRect_.ToString().c_str());
        }
    }
}
```

#### 3. ExpandDisplay 判断

**源码**: `menu_layout_algorithm.cpp:553-568`

```cpp
bool MenuLayoutAlgorithm::IsExpandDisplay()
{
    auto containerId = Container::CurrentId();
    auto container = AceEngine::Get().GetContainer(containerId);

    // 如果当前是子容器，获取父容器
    if (containerId >= MIN_SUBCONTAINER_ID) {
        auto parentContainerId = SubwindowManager::GetInstance()->GetParentContainerId(containerId);
        container = AceEngine::Get().GetContainer(parentContainerId);
    }

    CHECK_NULL_RETURN(container, false);

    auto pipelineContext = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_RETURN(pipelineContext, false);

    auto theme = pipelineContext->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(theme, false);

    // 获取主窗口或宿主窗口的 FreeMultiWindow 状态
    isFreeMultiWindow_ = container->IsFreeMultiWindow();

    // 手机设备返回 false
    return theme->GetExpandDisplay();
}
```

### MenuLayoutProperty 中的子窗属性

**源码**: `menu_layout_property.h`

```cpp
class MenuLayoutProperty : public LayoutProperty {
public:
    // ShowInSubWindow 属性
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ShowInSubWindow, bool, PROPERTY_UPDATE_MEASURE)

    // 获取方法
    bool GetShowInSubWindowValue(bool defaultValue) const {
        if (showInSubWindow.has_value()) {
            return showInSubWindow.value();
        }
        return defaultValue;
    }

private:
    std::optional<bool> showInSubWindow_;
};
```

### 子窗显示流程

```
1. 用户触发菜单显示
   ↓
2. MenuModelNG::Create() 或 BindMenu()
   ↓
3. 判断是否使用子窗显示
   ├─ 检查 MenuType (ContextMenu 强制子窗)
   ├─ 检查 ShowInSubWindow 属性
   └─ 检查 ExpandDisplay 状态（平板/大屏）
   ↓
4. 如果需要子窗显示：
   ├─ SubwindowManager::CreateSubwindow()
   │   └─ 创建 SubwindowOhos 实例
   │       ├─ 创建 Rosen Window
   │       ├─ 创建 AceContainer (子容器)
   │       └─ 初始化 PipelineContext
   ├─ SubwindowManager::ShowMenuNG()
   │   ├─ 设置子窗尺寸和位置
   │   ├─ 添加 MenuWrapper FrameNode
   │   ├─ 执行布局测量
   │   └─ 显示子窗
   └─ 设置 targetId_ 用于后续隐藏
   ↓
5. 如果不需要子窗显示：
   └─ 直接在主窗口的 OverlayManager 中显示
       ├─ 创建 MenuWrapper FrameNode
       ├─ 添加到 OverlayManager
       └─ 执行布局和显示
```

### 子窗隐藏流程

```
1. 触发菜单隐藏
   ├─ HideMenuType::CLICK (点击外部)
   ├─ HideMenuType::WRAPPER_LOSE_FOCUS (失去焦点)
   ├─ HideMenuType::API (API 调用)
   └─ HideMenuType::CANCEL (取消操作)
   ↓
2. MenuPattern::HideMenu()
   ├─ 检查是否在子窗中
   ├─ 如果是子窗：
   │   ├─ SubwindowManager::HideMenuNG(wrapper, targetId_)
   │   ├─ 关闭子菜单
   │   ├─ 隐藏子窗
   │   └─ 销毁子窗资源
   └─ 如果是 Overlay：
       ├─ OverlayManager::RemoveMenu()
       └─ 从 UI 树中移除
```

### 关键实现细节

#### 1. 子窗生命周期

**创建时机**：
- ContextMenu 触发时
- ExpandDisplay 模式下，ShowInSubWindow = true 时
- Select 菜单在 ExpandDisplay 模式下

**销毁时机**：
- 用户点击菜单外部区域
- 菜单失去焦点
- 用户选择菜单项后
- API 调用隐藏菜单

#### 2. 子窗与主窗口的通信

**机制**：
- **ContainerId 映射**：通过 parentContainerMap_ 维护父子容器关系
- **事件传递**：通过 SubwindowManager 中转事件
- **状态同步**：通过 AceContainer 共享状态

**示例代码**：
```cpp
// 获取父容器ID
auto parentContainerId = SubwindowManager::GetInstance()->GetParentContainerId(childContainerId);

// 获取父容器
auto parentContainer = AceEngine::Get().GetContainer(parentContainerId);

// 获取父容器的主题
auto theme = parentContainer->GetPipelineContext()->GetTheme<SelectTheme>();
```

#### 3. UIExtension 子窗特殊处理

UIExtension 是 OpenHarmony 中的一种特殊窗口类型，菜单需要特殊处理：

```cpp
if (container->IsUIExtensionWindow()) {
    // UIExtension 窗口可以被菜单扩展
    canExpandCurrentWindow_ = true;
    auto subwindow = SubwindowManager::GetInstance()->GetSubwindowById(containerId);
    auto rect = subwindow->GetUIExtensionHostWindowRect();
    UIExtensionHostWindowRect_ = RectF(rect.Left(), rect.Top(), rect.Width(), rect.Height());
}
```

#### 4. FoldStatus 折叠状态监听

**源码**: `menu_pattern.cpp:214-227`

```cpp
auto foldStatusChangeCallback = [weak = WeakClaim(this)](FoldStatus foldStatus) {
    TAG_LOGI(AceLogTag::ACE_MENU, "foldStatus is changed: %{public}d", foldStatus);
    auto menuPattern = weak.Upgrade();
    CHECK_NULL_VOID(menuPattern);
    auto menuWrapper = menuPattern->GetMenuWrapper();
    CHECK_NULL_VOID(menuWrapper);
    auto wrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(wrapperPattern);
    wrapperPattern->SetHasFoldModeChangedTransition(true);
    SubwindowManager::GetInstance()->HideMenuNG(false);
};
```

#### 5. 多窗口支持 (MULTIPLE_WINDOW_SUPPORTED)

**编译宏**：
```cpp
#if defined(MULTIPLE_WINDOW_SUPPORTED)
    menuComponent->SetIsContextMenu(true);
#endif
```

**启用条件**：
- 平板设备
- 大屏设备
- 支持 FreeMultiWindow 的设备

### API 使用示例

#### 设置菜单在子窗中显示

```cpp
// C++ 端设置
auto menuNode = MenuModelNG::Create();
auto layoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
layoutProperty->SetShowInSubWindow(true);
```

#### 检查菜单是否在子窗中

```cpp
auto menuPattern = menuNode->GetPattern<MenuPattern>();
if (menuPattern->IsContextMenu()) {
    // ContextMenu 强制使用子窗
}

auto layoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
bool showInSubWindow = layoutProperty->GetShowInSubWindowValue(false);
if (showInSubWindow) {
    // 菜单将在子窗中显示
}
```

### 调试子窗问题

#### 常见问题

**问题1：菜单不在子窗中显示**
- 检查 `ShowInSubWindow` 属性是否设置
- 检查设备类型（手机端可能不支持）
- 检查 `ExpandDisplay` 主题设置

**问题2：子窗无法隐藏**
- 检查 `targetId_` 是否正确设置
- 检查 `SubwindowManager::HideMenuNG()` 调用
- 检查事件处理是否正确

**问题3：子窗位置不正确**
- 检查目标节点的位置和尺寸
- 检查子窗的 `GetRect()` 返回值
- 检查避让算法是否执行

#### 调试日志

```cpp
// 启用菜单日志
#define ACE_LOG_TAG AceLogTag::ACE_MENU

// 关键日志位置
TAG_LOGI(AceLogTag::ACE_MENU, "will hide menu, targetNode id %{public}d. reason %{public}d",
    targetId_, reason);

TAG_LOGI(AceLogTag::ACE_MENU, "foldStatus is changed: %{public}d", foldStatus);

TAG_LOGI(AceLogTag::ACE_MENU, "GetUIExtensionHostWindowRect : %{public}s",
    UIExtensionHostWindowRect_.ToString().c_str());
```

### 性能优化

#### 1. 子窗复用

```cpp
// 复用已存在的子窗
auto subwindow = SubwindowManager::GetInstance()->GetSubwindowByType(
    containerId, SubwindowType::TYPE_MENU);
if (SubwindowManager::GetInstance()->IsSubwindowExist(subwindow)) {
    // 复用现有子窗
    subwindow->ShowMenuNG(...);
} else {
    // 创建新子窗
    SubwindowManager::GetInstance()->CreateSubwindow(instanceId);
}
```

#### 2. 延迟销毁

```cpp
// 隐藏时保留子窗实例，避免频繁创建销毁
void SubwindowManager::HideMenuNG(
    const RefPtr<NG::FrameNode>& menuWrapper,
    int32_t targetId)
{
    // 隐藏菜单但保留子窗
    auto subwindow = GetSubwindowByType(containerId, SubwindowType::TYPE_MENU);
    if (subwindow) {
        subwindow->HideMenuNG(menuWrapper, targetId);
        // 不调用 subwindow->HideSubWindowNG()
    }
}
```

#### 3. 容器ID 映射缓存

```cpp
// 缓存父子容器映射关系
std::unordered_map<int32_t, int32_t> parentContainerMap_;

// 快速查找父容器
int32_t SubwindowManager::GetParentContainerId(int32_t containerId) {
    auto iter = parentContainerMap_.find(containerId);
    if (iter != parentContainerMap_.end()) {
        return iter->second;
    }
    return -1;
}
```

---

## 使用示例

### 示例 1：普通菜单

```typescript
@Entry
@Component
struct MenuExample {
  @State select: number = 0
  @State isMenuOpen: boolean = false

  build() {
    Column() {
      Button("显示菜单")
        .onClick(() => {
          this.isMenuOpen = !this.isMenuOpen
        })

      if (this.isMenuOpen) {
        Menu() {
          MenuItem({ value: "选项1", icon: $r('app.media.icon1') })
            .onClick(() => {
              console.log("选择了选项1")
              this.isMenuOpen = false
            })
          MenuItem({ value: "选项2", icon: $r('app.media.icon2') })
            .onClick(() => {
              console.log("选择了选项2")
              this.isMenuOpen = false
            })
        }
        .width("200vp")
        .placement(Placement.Bottom)
        .fontSize(16)
        .fontColor(Color.Black)
      }
    }
  }
}
```

### 示例 2：上下文菜单

```typescript
@Entry
@Component
struct ContextMenuExample {
  build() {
    Text("右键点击我")
      .bindContextMenu(ResponseType.RightClick, {
        builder: () => {
          Menu() {
            MenuItem({ value: "复制", icon: $r('app.media.copy') })
              .onClick(() => {
                console.log("复制操作")
              })
            MenuItem({ value: "粘贴", icon: $r('app.media.paste') })
              .onClick(() => {
                console.log("粘贴操作")
              })
          }
          .width("200vp")
        }
      })
  }
}
```

### 示例 3：带预览的菜单

```typescript
@Entry
@Component
struct PreviewMenuExample {
  @State showPreview: boolean = false

  build() {
    Column() {
      Button("显示预览菜单")
        .onClick(() => {
          this.showPreview = !this.showPreview
        })

      if (this.showPreview) {
        Menu() {
          MenuItem({ value: "选项1" })
          MenuItem({ value: "选项2" })
        }
        .preview()
        .previewMode(MenuPreviewMode.IMAGE)
        .width("200vp")
      }
    }
  }
}
```

### 示例 4：子菜单

```typescript
@Entry
@Component
struct SubMenuExample {
  build() {
    Column() {
      Button("显示子菜单")
        .onClick(() => {
          // 触发子菜单显示
        })

      Menu() {
        MenuItem({ value: "文件",
                 suffix: { icon: "$r('app.media.chevron_right')" },
                 children: [
                   MenuItem({ value: "新建",
                            action: () => console.log("新建文件") }),
                   MenuItem({ value: "打开",
                            action: () => console.log("打开文件") }),
                   MenuItem({ value: "另存为",
                            action: () => console.log("另存为") }),
                 ]
               })
        MenuItem({ value: "编辑",
                 suffix: { icon: "$r('app.media.chevron_right')" },
                 children: [
                   MenuItem({ value: "撤销",
                               action: () => console.log("撤销") }),
                   MenuItem({ value: "重做",
                               action: () => console.log("重做") }),
                 ]
               })
      }
      .width("200vp")
      .expandingMode(SubMenuExpandingMode.EMBEDDED)
    }
  }
}
```

---

## 调试指南

### 常见问题排查

#### 问题1：菜单不显示

**排查步骤**：
1. 检查 `isShow` 参数是否正确
2. 验证 MenuParam 是否正确解析
3. 确认目标节点（targetId/targetTag）是否存在
4. 检查事件处理器是否正确注册
5. 查看日志：`LOGI("Context menu is triggered")`

**关键日志位置**：
- `js_popups.cpp:1634` - 上下文菜单触发日志
- `view_abstract_model_impl.cpp:1632` - 事件执行日志

#### 问题2：子菜单不显示

**排查步骤**：
1. 检查 `ExpandingMode` 设置
2. 确认父 MenuItem 是否有 `subBuilder`
3. 验证子菜单构建器是否被调用
4. 检查子菜单位置计算（避让算法）
5. 查看日志输出

**关键代码**：
- `menu_item_pattern.cpp:ShowSubMenu()` - 子菜单显示入口
- `menu_layout_algorithm.cpp:GetSelectChildPosition()` - 子菜单位置计算

#### 问题3：菜单位置不正确

**排查步骤**：
1. 检查 `Placement` 参数
2. 确认目标节点位置和尺寸
3. 验证避让算法是否执行
4. 检查屏幕边界和安全边距
5. 使用 `DumpInfo()` 输出调试信息

**关键方法**：
- `MenuLayoutAlgorithm::MenuLayoutAvoidAlgorithm()` - 避让算法
- `MenuPattern::DumpInfo()` - 输出调试信息

#### 问题4：动画不执行

**排查步骤**：
1. 检查 `menuParam.animationDuration` 设置
2. 确认动画曲线和参数
3. 验证动画状态机（MenuStatus）
4. 检查 `isFirstShow_` 标志
5. 查看动画执行日志

**关键代码**：
- `menu_pattern.cpp:ShowMenuAppearAnimation()` - 显示动画入口
- `menu_theme.h` - 动画参数定义

### 调试工具

#### 1. DumpInfo

**源码**：`menu_pattern.cpp:407`

```cpp
void MenuPattern::DumpInfo()
```

**输出内容**：
- 菜单类型
- 目标信息
- 位置和尺寸
- 显示状态
- 动画参数

#### 2. 日志输出

**关键日志位置**：

| 日志 | 级别 | 位置 | 说明 |
|------|------|------|------|
| `Context menu is triggered` | INFO | `view_abstract_model_impl.cpp:1634` | 上下文菜单触发 |
| `BuildMenu` | SCORING | `view_abstract_model_impl.cpp:1628` | 菜单构建 |
| `MenuLayoutAvoidAlgorithm` | - | `menu_layout_algorithm.cpp` | 避让算法执行 |
| `ShowMenuAppearAnimation` | - | `menu_pattern.cpp` | 显示动画执行 |

#### 3. 断点调试

**关键断点位置**：

| 函数 | 文件:行号 | 说明 |
|------|-----------|------|
| `JsBindMenu` | `js_popups.cpp:2906` | JS 入口 |
| `BindMenu` | `view_abstract_model_impl.cpp:1593` | Model 层 |
| `Create()` | `menu_model_ng.cpp` | NG Model 创建 |
| `OnAttachToFrameNode` | `menu_pattern.cpp:177` | Pattern 附加 |
| `OnModifyDone` | `menu_pattern.cpp:398` | 修改完成回调 |
| `Measure()` | `menu_layout_algorithm.cpp:87` | 布局测量 |
| `Layout()` | `menu_layout_algorithm.cpp:89` | 布局执行 |

---

## 附录

### A. 术语表

| 术语 | 说明 |
|------|------|
| **NG 架构** | Next Generation，新一代组件架构 |
| **Pattern** | 模式类，封装组件的业务逻辑 |
| **LayoutAlgorithm** | 布局算法，计算组件位置和尺寸 |
| **PaintMethod** | 绘制方法，处理组件绘制 |
| **FrameNode** | 框架节点，表示 UI 树中的一个节点 |
| **RefPtr/WeakPtr** | 引用计数智能指针，用于内存管理 |
| **Placement** | 定位方式，如 TOP_LEFT、BOTTOM_RIGHT 等 |
| **ResponseType** | 响应类型，如 LONG_PRESS、RIGHT_CLICK |
| **ExpandingMode** | 展开模式，如 SIDE、EMBEDDED、STACK |
| **MenuPreviewMode** | 预览模式，如 NONE、IMAGE 等 |
| **MenuType** | 菜单类型，区分不同使用场景 |

### B. 架构演进

```
Legacy Components (旧组件)
├─ menu_component.cpp (旧实现)
└─ select_popup_component.cpp

NG Components (新组件)
├─ menu/ (NG Pattern 架构)
│   ├─ menu_pattern.h/cpp
│   ├─ menu_model_ng.h/cpp
│   ├─ menu_layout_algorithm.h/cpp
│   └─ menu_paint_method.h/cpp
└─ menu_item/ (MenuItem Pattern 架构)
    ├─ menu_item_pattern.h/cpp
    └─ menu_item_model_ng.h/cpp
```

### C. MenuType枚举

```cpp
enum class MenuType {
    MENU,                              // 普通菜单
    CONTEXT_MENU,                      // 右键上下文菜单
    SUB_MENU,                          // 子菜单
    NAVIGATION_MENU,                   // 导航菜单
    MULTI_MENU,                        // 多菜单（桌面）
    DESKTOP_MENU,                      // 桌面菜单
    SELECT_OVERLAY_EXTENSION_MENU,     // SelectOverlay扩展菜单
    SELECT_OVERLAY_CUSTOM_MENU,        // SelectOverlay自定义菜单
    SELECT_OVERLAY_SUB_MENU,           // SelectOverlay子菜单
    SELECT_OVERLAY_RIGHT_CLICK_MENU    // SelectOverlay右键菜单
};
```

### D. Placement枚举

支持12种方位：
- `TOP`, `TOP_LEFT`, `TOP_RIGHT`
- `BOTTOM`, `BOTTOM_LEFT`, `BOTTOM_RIGHT`
- `LEFT`, `LEFT_TOP`, `LEFT_BOTTOM`
- `RIGHT`, `RIGHT_TOP`, `RIGHT_BOTTOM`
- `NONE`

### E. SubMenuExpandingMode枚举

```cpp
enum class SubMenuExpandingMode {
    SIDE,      // 侧边展开（默认）
    EMBEDDED,  // 嵌入式展开
    STACK      // Stack展开（新窗口）
};
```

### F. MenuPreviewMode枚举

```cpp
enum class MenuPreviewMode {
    NONE,      // 无预览
    IMAGE,     // 图片预览
    CUSTOM     // 自定义预览
};
```

### G. MenuStatus枚举

```cpp
enum class MenuStatus {
    INIT,              // 未创建
    ON_SHOW_ANIMATION, // 显示动画中
    SHOW,              // 已显示
    ON_HIDE_ANIMATION, // 隐藏动画中
    HIDE               // 已隐藏
};
```

### H. MenuHoverScaleStatus枚举

```cpp
enum class MenuHoverScaleStatus {
    DISABLE = 0,    // 禁用
    NONE,           // 无状态
    READY,          // 准备
    HOVER,          // Hover中
    INTERRUPT,      // 中断
    MENU_SHOW       // 菜单显示中
};
```

### I. ShowSubMenuType枚举

```cpp
enum class ShowSubMenuType : int32_t {
    DEFAULT = 0,       // 默认
    HOVER = 1,         // Hover触发
    CLICK = 2,         // 点击触发
    LONG_PRESS = 3,    // 长按触发
    KEY_DPAD_RIGHT = 4,// 方向键右触发
    ACTION = 5         // Action触发
};
```

---

**文档维护**：
- 版本：v2.0 (Unified)
- 最后更新：2026-01-26
- 维护者：基于 CLAUDE.md 规范自动生成

**相关文档**：
- [CLAUDE.md](../../../../CLAUDE.md) - 项目代码规范
- [测试文件](../../../../../test/unittest/core/pattern/menu/) - 单元测试

**反馈**：
如有问题或建议，请在项目根目录的 `CLAUDE.md` 中更新。
