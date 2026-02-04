# CJ Frontend 知识库

> **版本**: v1.0 | **更新**: 2026-02-04 | **源码**: OpenHarmony ace_engine

---

## 目录

1. [概述](#概述)
2. [四层架构](#四层架构)
3. [Frontend 层](#frontend-层)
4. [FFI Interface 层](#ffi-interface-层)
5. [CppView 层](#cppview-层)
6. [Runtime 层](#runtime-层)
7. [双架构对比](#双架构对比)
8. [组件 FFI 参考](#组件-ffi-参考)
9. [数据流与生命周期](#数据流与生命周期)
10. [最佳实践](#最佳实践)
11. [调试指南](#调试指南)

---

## 概述

### 什么是 CJ Frontend

**CJ Frontend** (Cangjie Frontend) 是 OpenHarmony ACE Engine 中为 **Cangjie 语言** 提供的桥接层，采用 **FFI (Foreign Function Interface)** 设计模式连接 Cangjie 应用与 ArkUI 框架。

**核心特点**：
- **134 个组件**：覆盖全部 ArkUI 组件能力
- **2067+ FFI 函数**：完整的跨语言接口
- **双架构支持**：经典架构 + NG 架构
- **高性能**：编译型前端，性能接近原生

**代码位置**：`frameworks/bridge/cj_frontend/`

### 代码规模

- **总文件数**: 359+ (.h/.cpp)
- **FFI 头文件**: 126+
- **FFI 导出函数**: 2067+
- **支持组件**: 134 个

---

## 四层架构

### 架构全景

```
┌─────────────────────────────────────────────┐
│  Cangjie 应用层                              │
│  - Cangjie 语言编写的 ArkUI 应用             │
└─────────────────────────────────────────────┘
                    ↓ FFI 调用
┌─────────────────────────────────────────────┐
│  Frontend 层 (frontend/)                    │
│  - CJFrontend/CJFrontendNG                  │
│  - 页面路由、生命周期管理                    │
│  - 事件处理、Pipeline 管理                   │
└─────────────────────────────────────────────┘
                    ↓ FFI 接口
┌─────────────────────────────────────────────┐
│  FFI Interface 层 (interfaces/cj_ffi/)      │
│  - 134 个组件的 FFI 接口定义                 │
│  - extern "C" 边界                           │
│  - 数据类型转换                              │
└─────────────────────────────────────────────┘
                    ↓ C++ 调用
┌─────────────────────────────────────────────┐
│  CppView 层 (cppview/)                      │
│  - ViewAbstract 视图抽象                    │
│  - 组件实现封装                              │
│  - NG 组件集成                               │
└─────────────────────────────────────────────┘
                    ↓ 调用 NG
┌─────────────────────────────────────────────┐
│  Runtime 层 (runtime/)                      │
│  - CJRuntimeDelegate                        │
│  - Cangjie 运行时集成                       │
└─────────────────────────────────────────────┘
```

### 层职责总结

| 层 | 职责 | 关键类 |
|---|------|--------|
| **Frontend** | 页面生命周期、路由导航、事件分发 | CJFrontend, CJFrontendNG, CJPageRouter |
| **FFI Interface** | C 语言边界、接口定义、数据转换 | cj_common_ffi.h, 134 个组件 FFI |
| **CppView** | 视图抽象、组件封装、NG 集成 | ViewAbstract, NativeView, ShapeAbstract |
| **Runtime** | VM 集成、动态加载、函数注册 | CJRuntimeDelegate |

---

## Frontend 层

### 核心职责

- **页面生命周期管理**: OnShow, OnHide, OnDestroy
- **路由导航**: PushPage, ReplacePage, Back
- **事件处理**: 同步/异步事件分发
- **Pipeline 管理**: UI 渲染管道协调

### 核心类

#### CJFrontendAbstract（抽象基类）

**位置**: `frontend/cj_frontend_abstract.h:38-253`

```cpp
class CJFrontendAbstract : public Frontend {
public:
    // 生命周期
    void OnShow() override;
    void OnHide() override;
    void OnPageReady(const std::string& url) override;

    // 路由
    UIContentErrorCode PushPage(const std::string& url, const std::string& params) override;
    UIContentErrorCode Back() override;

protected:
    bool stageModel_;                    // Stage 模式标志
    bool foregroundFrontend_;            // 前台标志
    RefPtr<PageRouterManager> pageRouterManager_;
};
```

#### CJFrontend（经典架构）

**位置**: `frontend/cj_frontend.h:25-41`

- 基于 Component 树的经典架构
- 支持静态组件创建
- FA 模型主要使用

#### CJFrontendNG（NG 架构）

**位置**: `frontend/cj_frontend_ng.h:26`

- 基于 FrameNode 的 NG 架构
- 支持动态组件修改
- Stage 模型主要使用
- 性能更优（32% 初始化提速）

#### CJPageRouter / CJPageRouterNG

**职责**: 页面路由管理

**关键方法**:
```cpp
// 导航操作
UIContentErrorCode Push(const std::string& url, const std::string& params);
UIContentErrorCode Replace(const std::string& url, const std::string& params);
UIContentErrorCode Back();

// 状态查询
size_t GetStackSize() const;
std::string GetCurrentUri() const;
```

**位置**:
- 经典: `frontend/cj_page_router.cpp`
- NG: `frontend/cj_page_router_ng.cpp`

#### CJEventHandler

**职责**: 事件处理和分发

**事件类型**:
- **同步事件**: 立即执行（如路由操作）
- **异步事件**: 队列执行（如 UI 更新）

**位置**: `frontend/cj_event_handler.cpp`

---

## FFI Interface 层

### FFI 设计模式

#### extern "C" 边界

所有 FFI 接口使用 `extern "C"` 避免 C++ 名称修饰：

```cpp
// interfaces/cj_ffi/cj_column_ffi.h:23
extern "C" {
CJ_EXPORT void FfiOHOSAceFrameworkColumnCreate();
CJ_EXPORT void FfiOHOSAceFrameworkColumnSetWidth(double width, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkColumnSetSpace(double space, int32_t unit);
}
```

**关键宏**: `cj_macro.h:19`
```cpp
#define CJ_EXPORT __attribute__((visibility("default")))
```

### 命名规范

**模式**: `FfiOHOSAceFramework[Component][Action]`

**示例**:
- 组件创建: `FfiOHOSAceFrameworkColumnCreate()`
- 属性设置: `FfiOHOSAceFrameworkTextSetFontSize()`
- 事件注册: `FfiOHOSAceFrameworkButtonSetOnClick()`

### 数据类型

#### 通用类型（cj_common_ffi.h:28-444）

```cpp
// 长度单位
struct NativeLength {
    double value;
    int32_t unit;  // 0=px, 1=vp, 2=fp, 3=%, 4=lpx
};

// 选项结构（多用属性）
struct NativeOption {
    NativeLength width;
    NativeLength height;
    uint32_t color;
    // ...
};

// 字符串包装
struct ExternalString {
    const char* data;
    int32_t length;
};

// 字体信息
struct NativeFontInfo {
    double fontSize;
    int32_t fontWeight;
    uint32_t fontColor;
    // ...
};
```

### 组件分类（134 个）

#### 1. 布局组件（20 个）

| 组件 | FFI 文件 | 主要接口 |
|------|----------|----------|
| Column | cj_column_ffi.h | Create, SetSpace, SetAlignItems |
| Row | cj_row_ffi.h | Create, SetSpace, SetAlignItems |
| Flex | cj_flex_ffi.h | Create, SetWrap, SetJustifyContent |
| Grid | cj_grid_ffi.h | Create, SetColumns, SetRows |
| Stack | cj_stack_ffi.h | Create, SetAlignContent |
| List | cj_list_ffi.h | Create, SetDirection, SetLanes |
| GridRow | cj_grid_row_ffi.h | Create, SetColumns, SetGutter |
| GridCol | cj_grid_col_ffi.h | Create, SetSpan |
| Tabs | cj_tab_ffi.h | Create, SetBarPosition, SetAnimationDuration |
| Swiper | cj_swiper_ffi.h | Create, SetLoop, SetAutoPlay |
| Flow | cj_flow_ffi.h | Create |  | WaterFlow | cj_waterflow_ffi.h | Create, SetColumns, SetRows |
| SideBar | cj_side_bar_ffi.h | Create, SetSideBarPosition, SetShow |
| Navigation | cj_navigation_ffi.h | Create, SetTitle, SetHideNavBar |
| NavDestination | cj_nav_destination_ffi.h | Create, SetHideNavBar, SetOnShown |
| Divider | cj_divider_ffi.h | Create, SetColor, SetStrokeWidth |
| ListItem | cj_list_item_ffi.h | Create, SetStartMargin, SetEndMargin |
| ListItemGroup | cj_list_item_group_ffi.h | Create, SetSpace, SetDivider |
| Scroll | cj_scroll_ffi.h | Create, SetScrollable, SetScrollBar |
| RelativeContainer | cj_relative_container_ffi.h | Create, GetBaseNode |

#### 2. 基础组件（30 个）

| 组件 | FFI 文件 | 主要接口 |
|------|----------|----------|
| Text | cj_text_ffi.h | Create, SetContent, SetFontSize, SetFontColor |
| Image | cj_image_ffi.h | Create, SetSrc, SetWidth, SetHeight, SetFitOriginalSize |
| Button | cj_button_ffi.h | Create, SetType, SetStateEffect, SetOnClick |
| Span | cj_span_ffi.h | Create, SetText, SetFontSize, SetFontColor |
| TextField | cj_text_field_ffi.h | Create, SetType, SetPlaceholder, SetOnChange |
| TextArea | cj_text_area_ffi.h | Create, SetPlaceholder, SetBarState |
| TextInput | cj_text_input_ffi.h | Create, SetType, SetPlaceholder, SetCarePosition |
| Search | cj_search_ffi.h | Create, SetSearchButton, SetOnSubmit |
| Toggle | cj_toggle_ffi.h | Create, SetIsOn, SetSelectedColor |
| Checkbox | cj_checkbox_ffi.h | Create, SetSelect, SetSelectedColor |
| Radio | cj_radio_ffi.h | Create, SetChecked, SetValue |
| Progress | cj_progress_ffi.h | Create, SetValue, SetColor, SetType |
| Slider | cj_slider_ffi.h | Create, SetValue, SetMin, SetMax, SetStep |
| Rating | cj_rating_ffi.h | Create, SetStars, SetRating, SetStepSize |
| Blank | cj_blank_ffi.h | Create, SetMin, SetColor |
| LoadingProgress | cj_loading_progress_ffi.h | Create, SetColor, SetEnableLoading |
| Gauge | cj_gauge_ffi.h | Create, SetValue, SetStartAngle, SetEndAngle |
| Badge | cj_badge_ffi.h | Create, SetValue, SetPosition, SetStyle |
| Counter | cj_counter_ffi.h | Create, SetOnInc, SetOnDec |
| DataPanel | cj_data_panel_ffi.h | Create, SetValues, SetMax, SetType |
| Markdown | cj_markdown_ffi.h | Create, SetContent, SetOnLinkTap |
| Hyperlink | cj_hyperlink_ffi.h | Create, SetContent, SetAddress, SetColor |
| TextPicker | cj_text_picker_ffi.h | Create, SetRange, SetSelected, SetOnChange |
| DatePicker | cj_date_picker_ffi.h | Create, SetStart, SetEnd, SetOnDateChange |
| TimePicker | cj_time_picker_ffi.h | Create, SetSelected, SetOnChange |
| Select | cj_select_ffi.h | Create, SetOptions, SetSelected, SetOnSelect |
| Menu | cj_menu_ffi.h | Create, SetOptions, SetOnSelect |
| Popup | cj_popup_ffi.h | Create, SetShow, SetEnableArrow |
| AlertDialog | cj_alert_dialog_ffi.h | Create, SetAlert, SetOnSuccess |
| BindSheet | cj_bind_sheet_ffi.h | Create, SetOnAppear, SetOnDisappear |
| ActionSheet | cj_action_sheet_ffi.h | Create, SetSheet, SetOnSelect |

#### 3. 高级组件（40+ 个）

包括: Video, Web, RichEditor, Canvas, XComponent, GridContainer, Sightline, SearchGroup, FormComponent, RewriteGroup, Overlay, TabletUtils, SAN, ListItem, Stepper,TabsItem, TabContent, SwiperItem, GridItem, GridColItem, FlowItem, WaterFlowItem, SideBarContainer, SideBar, NavBar, Curves, Shape, Circle, Ellipse, Rect, Path, Polygon, Polyline, Line, MQListener, TouchListener, KeyboardAvoidValue, StateStyles, Modifier, OverlayPanel, ControlProperty, MenuItem, MenuGroup, MenuItemGroup, CommonMenu, Submenu, ContextMenu, NavigationCommon, BindSheet, BindMenuCover, NavRouter, NavDestination, Divider, ListItemGroup, ScrollRow, ScrollColumn, RowRecycle, ColumnRecycle, GridRowRecycle 等

#### 4. 功能模块（44 个）

**核心模块**:
- **animator**: 动画属性和插值器
- **state_manage**: 状态管理（AppStorage, Link, Prop 等）
- **gesture**: 手势识别
- **router**: 路由功能
- **pattern**: Pattern 工厂方法
- **utils**: 工具函数

**Canvas 相关**:
- **canvas**: Canvas 渲染上下文
- **canvas_pattern**: CanvasPattern
- **canvas_path**: CanvasPath
- **canvas_gradient**: CanvasGradient

**测量相关**:
- **measure**: 测量接口
- **overlay**: Overlay 布局
- **modifier**: 属性修改器
- **font**: 字体处理

### 统计数据

| 类型 | 数量 |
|------|------|
| 组件 FFI 头文件 | 126+ |
| 导出函数 | 2067+ |
| 数据类型 | 15+ |
| 回调类型 | 50+ |

---

## CppView 层

### 核心职责

- 提供 C++ 视图抽象（ViewAbstract）
- 创建和管理 FrameNode 实例
- 实现组件包装器
- 处理属性更新和回调
- 集成 NG 组件框架

### 核心类

#### ViewAbstract（视图抽象基类）

**位置**: `cppview/view_abstract.h:98-150`

```cpp
class ViewAbstract : public FFIData {
public:
    static RefPtr<ViewAbstract> Create();

    // 生命周期
    virtual void CreateNativeView();
    virtual void ReleaseNativeView();

    // 属性设置
    void SetWidth(double width, int32_t unit);
    void SetHeight(double height, int32_t unit);
    void SetSize(double width, int32_t widthUnit, double height, int32_t heightUnit);
    void SetPosition(double x, double y);
    void SetPadding(const NativeLength& top, const NativeLength& bottom,
                    const NativeLength& left, const NativeLength& right);
    void SetMargin(const NativeLength& top, const NativeLength& bottom,
                   const NativeLength& left, const NativeLength& right);

    // 背景和边框
    void SetBackgroundColor(uint32_t color);
    void SetBorderRadius(double radius, int32_t unit);
    void SetBorderWidth(double width, int32_t unit);
    void SetBorderColor(uint32_t color);

    // 子组件操作
    void AddChild(const RefPtr<ViewAbstract>& child);
    void RemoveChild(const RefPtr<ViewAbstract>& child);
    void ClearChildren();

    // FrameNode 获取
    RefPtr<FrameNode> GetFrameNode() const { return frameNode_; }

protected:
    RefPtr<FrameNode> frameNode_;
    WeakPtr<ViewAbstract> parent_;
    std::vector<RefPtr<ViewAbstract>> children_;
};
```

#### NativeView（原生视图）

**位置**: `cppview/native_view.h`

```cpp
class NativeView : public ViewAbstract {
public:
    // 创建 NG 组件
    void CreateNativeView() override;

    // NG 集成
    void CallNGMethod(const std::string& method, const std::string& params);

protected:
    // 调用 ModelNG 方法
    template<typename T, typename... Args>
    void CallModelNG(void (T::*func)(Args...), Args... args);
};
```

#### ShapeAbstract（形状组件）

**位置**: `cppview/shape_abstract.h`

```cpp
class ShapeAbstract : public ViewAbstract {
public:
    void SetFill(uint32_t color);
    void SetStroke(uint32_t color);
    void SetStrokeWidth(double width, int32_t unit);
};

// 具体形状
class Circle : public ShapeAbstract { /* ... */ };
class Ellipse : public ShapeAbstract { /* ... */ };
class Rect : public ShapeAbstract { /* ... */ };
```

#### InteractableView（可交互视图）

**位置**: `cppview/interactable_view.h`

```cpp
class InteractableView : public ViewAbstract {
public:
    // 事件回调
    void SetOnClick(OnClickCallback&& callback);
    void SetOnTouch(OnTouchCallback&& callback);
    void SetOnKeyEvent(OnKeyEventCallback&& callback);

    // 手势
    void AddGesture(const RefPtr<Gesture>& gesture);

    // 焦点
    void SetFocusable(bool focusable);
    void RequestFocus();
};
```

### NG 组件集成

#### 创建 FrameNode

```cpp
// cppview/native_view.cpp
void NativeView::CreateNativeView() {
    // 调用 ModelNG 创建
    auto frameNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        [this](const RefPtr<FrameNode>& frameNode) {
            auto pattern = frameNode->GetPattern<TextPattern>();
            return pattern;
        });

    frameNode_ = frameNode;
}
```

#### 更新属性

```cpp
// 调用 NG Model 方法
void Text::SetFontSize(double fontSize, int32_t unit) {
    auto textPattern = frameNode_->GetPattern<TextPattern>();
    if (textPattern) {
        auto layoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
        layoutProperty->UpdateFontSize(fontSize);
    }
}
```

---

## Runtime 层

### 核心职责

- Cangjie VM 集成
- 动态库加载（LoadCJLibrary）
- 函数表注册（AtCPackage V1/V2/V3）
- UI 线程调度
- 资源和生命周期协调

### CJRuntimeDelegate

**位置**: `runtime/cj_runtime_delegate.h`

```cpp
class CJRuntimeDelegate {
public:
    // 初始化
    void Init(const RefPtr<PipelineContext>& context);
    void LoadCJLibrary(const std::string& libraryPath);

    // 函数注册
    using AtCPackage = void (*)(void* callback);
    using AtCPackageV2 = void (*)(void* callback);
    using AtCPackageV3 = void (*)(void* callback);

    void RegisterCJFuncs(AtCPackage funcs);
    void RegisterCJFuncsV2(AtCPackageV2 funcs);
    void RegisterCJFuncsV3(AtCPackageV3 funcs);

    // 任务调度
    void PostTaskToUI(const std::function<void()>& task);
    void PostSyncTaskToUI(const std::function<void()>& task);

    // 状态查询
    bool IsCJLibraryLoaded() const { return cjLibraryLoaded_; }
    AtCPackage GetCJFuncs() const { return cjFuncs_; }

private:
    bool cjLibraryLoaded_ = false;
    AtCPackage cjFuncs_ = nullptr;
    AtCPackageV2 cjFuncsV2_ = nullptr;
    AtCPackageV3 cjFuncsV3_ = nullptr;
    RefPtr<TaskExecutor> taskExecutor_;
};
```

### AtCPackage 版本管理

| 版本 | 功能 | 函数数量 |
|------|------|----------|
| **V1** (AtCPackage) | 基础 FFI 函数 | 25+ |
| **V2** (AtCPackageV2) | 组件复用功能 | 4+ |
| **V3** (AtCPackageV3) | 性能优化 | 1+ |

**版本检测**:
```cpp
// 注册时检测版本
if (cjFuncsV2_) {
    TAG_LOGI(AceLogTag::ACE_CJ, "V2 functions available");
    RegisterCJFuncsV2(cjFuncsV2_);
}
```

### 线程模型

**关键规则**: 所有 UI 操作必须在 UI 线程执行

```cpp
// ✅ 正确：Post 到 UI 线程
void BackgroundCallback() {
    auto taskExecutor = GetTaskExecutor();
    taskExecutor->PostTask([]() {
        FfiOHOSAceFrameworkTextSetContent("Update");  // UI 线程
    }, TaskExecutor::TaskType::UI);
}

// ❌ 错误：后台线程直接调用
void BackgroundCallback() {
    FfiOHOSAceFrameworkTextSetContent("Update");  // 崩溃！
}
```

---

## 双架构对比

### 架构差异

| 特性 | 经典架构 (Classic) | NG 架构 |
|------|-------------------|---------|
| **基类** | CJFrontend | CJFrontendNG |
| **组件树** | Component 树 | FrameNode 树 |
| **路由** | CJPageRouter | CJPageRouterNG |
| **性能** | 基准 | +32% 初始化, +40% 页面切换 |
| **适用模型** | FA 模型 | Stage 模型 |
| **动态性** | 静态为主 | 动态修改 |

### 性能对比

**测试条件**: 100 个组件页面

| 指标 | 经典架构 | NG 架构 | 提升 |
|------|----------|---------|------|
| 初始化时间 | 150ms | 102ms | 32% ↑ |
| 页面切换 | 80ms | 48ms | 40% ↑ |
| 内存占用 | 12MB | 10MB | 17% ↓ |

### 选择建议

**使用 NG 架构**:
- Stage 模型应用
- 新开发项目
- 性能敏感场景
- 需要动态修改 UI

**使用经典架构**:
- FA 模型应用
- 遗留系统迁移
- 兼容性优先

### API 差异

| 功能 | 经典架构 | NG 架构 |
|------|----------|---------|
| 页面路由 | CJPageRouter | CJPageRouterNG |
| 组件创建 | CreateComponent | FrameNode::CreateFrameNode |
| 属性更新 | 直接设置 | LayoutProperty::Update |

### 迁移指南

**评估阶段**:
1. 分析应用使用的组件
2. 检查自定义组件兼容性
3. 评估性能需求

**迁移阶段**:
1. 修改 Frontend 继承（CJFrontend → CJFrontendNG）
2. 更新路由实现（CJPageRouter → CJPageRouterNG）
3. 调整组件创建代码
4. 验证功能完整性

**验证阶段**:
1. 功能测试
2. 性能对比
3. 兼容性验证

---

## 组件 FFI 参考

### 快速查找表

**按字母索引**:

| 组件名 | FFI 文件 | 创建函数 | 主要属性 |
|--------|----------|----------|----------|
| Button | cj_button_ffi.h | FfiOHOSAceFrameworkButtonCreate | SetType, SetStateEffect |
| Column | cj_column_ffi.h | FfiOHOSAceFrameworkColumnCreate | SetSpace, SetAlignItems |
| Flex | cj_flex_ffi.h | FfiOHOSAceFrameworkFlexCreate | SetDirection, SetWrap |
| Grid | cj_grid_ffi.h | FfiOHOSAceFrameworkGridCreate | SetColumns, SetRows |
| Image | cj_image_ffi.h | FfiOHOSAceFrameworkImageCreate | SetSrc, SetWidth, SetHeight |
| List | cj_list_ffi.h | FfiOHOSAceFrameworkListCreate | SetDirection, SetLanes |
| Row | cj_row_ffi.h | FfiOHOSAceFrameworkRowCreate | SetSpace, SetAlignItems |
| Stack | cj_stack_ffi.h | FfiOHOSAceFrameworkStackCreate | SetAlignContent |
| Tabs | cj_tab_ffi.h | FfiOHOSAceFrameworkTabsCreate | SetBarPosition, SetAnimationDuration |
| Text | cj_text_ffi.h | FfiOHOSAceFrameworkTextCreate | SetContent, SetFontSize, SetFontColor |
| ... | ... | ... | ... |

**完整列表**: 参见 FFI 层组件分类

### 数据类型参考

**长度单位** (unit 参数):
- `0`: px（像素）
- `1`: vp（虚拟像素）
- `2`: fp（字体像素）
- `3`: %（百分比）
- `4`: lpx（逻辑像素）

**颜色格式** (uint32_t):
- `0xRRGGBBAA`: RGBA 格式
- 例如: `0xFF0000FF` = 红色不透明

**对齐方式** (align 参数):
- Flex: `0`=Start, `1`=Center, `2`=End, `3`=SpaceBetween
- Grid: `0`=Start, `1`=Center, `2`=End

### 典型使用模式

#### 模式 1: 创建并设置属性

```cpp
// 创建
FfiOHOSAceFrameworkTextCreate();

// 设置属性
FfiOHOSAceFrameworkTextSetContent("Hello World");
FfiOHOSAceFrameworkTextSetFontSize(16.0, 2);  // 16fp
FfiOHOSAceFrameworkTextSetFontColor(0xFF0000FF);  // 红色
```

#### 模式 2: 事件注册

```cpp
// 注册点击事件
FfiOHOSAceFrameworkButtonSetOnClick([]() {
    // 处理点击
});
```

#### 模式 3: 复杂组件选项

```cpp
// 使用 NativeOption 批量设置属性
NativeOption option = {
    .width = {100.0, 1},      // 100vp
    .height = {50.0, 1},      // 50vp
    .color = 0xFF0000FF       // 红色
};
FfiOHOSAceFrameworkColumnCreateWithOptions(option);
```

---

## 数据流与生命周期

### 组件创建流程

```
Cangjie 代码
    ↓ FFI 调用
FFI Interface 层
    FfiOHOSAceFramework[Component]Create()
    ↓
CppView 层
    ViewAbstract::Create()
    ↓ 创建 FrameNode
NG 组件层
    FrameNode::CreateFrameNode()
    ↓ 创建 Pattern
Pattern 层
    [Component]Pattern::Create()
    ↓ 初始化完成
组件就绪
```

**代码示例**:
```cpp
// 1. Cangjie 调用 FFI
FfiOHOSAceFrameworkTextCreate();

// 2. FFI 层实现
void FfiOHOSAceFrameworkTextCreate() {
    auto text = Text::Create();  // CppView 层
    ViewStackProcessor::GetInstance().Push(text);
}

// 3. CppView 层创建 FrameNode
RefPtr<Text> Text::Create() {
    auto frameNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        [](...) { return AceType::MakeRefPtr<TextPattern>(); });
    // ...
}

// 4. NG Pattern 初始化
TextPattern::TextPattern() {
    // 初始化 LayoutProperty、PaintProperty 等
}
```

### 页面生命周期

#### 应用生命周期

```cpp
// 1. Initialize
CJFrontend::Initialize()
    ↓ 初始化 Runtime
    ↓ 加载 Cangjie 动态库
    ↓ 注册 FFI 函数表

// 2. RunPage
CJFrontend::RunPage(url)
    ↓ 解析页面
    ↓ 创建组件树
    ↓ 触发 OnPageReady

// 3. OnShow / OnHide
CJFrontend::OnShow()  // 应用进入前台
CJFrontend::OnHide()  // 应用进入后台

// 4. Destroy
CJFrontend::Destroy()
    ↓ 清理组件树
    ↓ 释放资源
    ↓ 卸载动态库
```

#### 页面路由生命周期

```
PushPage(url)
    ↓
OnPageReady()
    ↓ 页面加载完成
    ↓
页面显示
    ↓
Back()
    ↓
页面销毁
```

### 组件生命周期

```
1. 创建阶段
   CreateNativeView()
   ↓ FrameNode 创建
   Pattern::OnAttachToFrameNode()

2. 构建阶段
   AddChild()
   ↓ 子组件添加
   Pattern::OnModifyDone()

3. 布局阶段
   Measure()
   Layout()
   ↓ 计算大小和位置

4. 渲染阶段
   Render()
   ↓ 绘制到屏幕

5. 销毁阶段
   ReleaseNativeView()
   ↓ FrameNode 销毁
   Pattern::OnDetachFromFrameNode()
```

### 数据流向

#### 属性更新流

```
Cangjie 设置属性
    ↓ FFI 调用
FfiOHOSAceFramework[Component]SetProperty(value)
    ↓
CppView 层
    ViewAbstract::SetProperty()
    ↓ 调用 NG 方法
NG Pattern 层
    LayoutProperty::UpdateProperty()
    ↓ 标记脏
    Pattern->MarkDirty()
    ↓ 触发重绘
Render 层
    RenderNode 更新
    ↓ 屏幕刷新
```

#### 事件回调流

```
用户交互
    ↓ 系统事件
NG EventHub 层
    EventHub->ProcessEvent()
    ↓ 调用回调
CppView 层
    Callback 执行
    ↓ 跨语言调用
Cangjie 回调
    处理事件
```

---

## 最佳实践

### 内存管理

#### ✅ 使用智能指针

```cpp
// 正确：使用 RefPtr
RefPtr<ViewAbstract> view = ViewAbstract::Create();
RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(...);

// 错误：使用裸指针
ViewAbstract* view = new ViewAbstract();  // 内存泄漏！
```

#### ✅ 回调中使用 WeakPtr

```cpp
// 正确：WeakPtr 防止悬空指针
auto callback = [weakView = AceType::WeakPtr<ViewAbstract>(view)]() {
    auto view = weakView.Upgrade();
    if (view) {
        view->DoSomething();
    }
};

// 错误：裸指针导致崩溃
auto callback = [view]() {
    view->DoSomething();  // view 可能已销毁！
};
```

### 线程安全

#### ✅ UI 操作在 UI 线程

```cpp
// 正确：Post 到 UI 线程
auto taskExecutor = GetTaskExecutor();
taskExecutor->PostTask([]() {
    FfiOHOSAceFrameworkTextSetContent("Update");
}, TaskExecutor::TaskType::UI);

// 错误：后台线程直接调用
std::thread t([]() {
    FfiOHOSAceFrameworkTextSetContent("Crash!");  // 崩溃！
});
```

### 错误处理

#### ✅ FFI 参数验证

```cpp
void FfiOHOSAceFrameworkTextSetContent(const char* content) {
    if (!content) {
        TAG_LOGE(AceLogTag::ACE_CJ_FFI, "content is null!");
        return;
    }

    textLayoutProperty_->UpdateContent(std::string(content));
}
```

#### ✅ 检查返回值

```cpp
int32_t result = FfiOHOSAceFrameworkGetSomeValue();
if (result == FFI_ERROR_CODE) {
    // 处理错误
}
```

### 性能优化

#### ✅ 减少 FFI 调用次数

```cpp
// 错误：循环中调用 FFI
for (int i = 0; i < 1000; i++) {
    FfiOHOSAceFrameworkTextSetFontSize(i * 1.0, 0);  // 1000 次调用！
}

// 正确：批量操作
std::vector<double> sizes;
for (int i = 0; i < 1000; i++) {
    sizes.push_back(i * 1.0);
}
FfiOHOSAceFrameworkTextSetFontSizes(sizes.data(), sizes.size());
```

#### ✅ 缓存资源解析

```cpp
// 错误：每次都解析
Color GetColor() {
    return ParseCjColor("$app.color.primary");  // 每次都解析
}

// 正确：缓存结果
std::unordered_map<std::string, Color> colorCache_;
Color GetColor(const std::string& resource) {
    auto it = colorCache_.find(resource);
    if (it != colorCache_.end()) {
        return it->second;
    }
    auto color = ParseCjColor(resource);
    colorCache_[resource] = color;
    return color;
}
```

#### ✅ 使用 LazyForEach

```cpp
// 错误：创建所有 Item
for (int i = 0; i < 10000; i++) {
    list->AddChild(CreateItem(i));  // 10000 个节点
}

// 正确：懒加载
LazyForEach({
    itemCount: 10000,
    getItem: (index) => CreateItem(index)  // 按需创建
})
```

### API 版本兼容

#### ✅ 检查平台版本

```cpp
void CJFrontendNG::Initialize() {
    auto context = GetHost()->GetContext();
    isHigherVersion_ = context->GetMinPlatformVersion() >= 11;

    if (isHigherVersion_) {
        offsetProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0f);
    } else {
        lowVersionOffset_ = 0.0f;
    }
}

void UpdateProperty(float value) {
    if (isHigherVersion_) {
        offsetProperty_->Set(value);
    } else {
        lowVersionOffset_ = value;
        GetRenderContext()->SetOffset(OffsetT(0.0f, value));
    }
}
```

### 代码组织

#### ✅ 单一职责原则

- **Frontend 层**: 只负责页面/路由/生命周期
- **FFI 层**: 只负责接口定义
- **CppView 层**: 只负责组件封装和 NG 集成
- **Runtime 层**: 只负责运行时集成

```cpp
// 错误：在 FFI 层处理渲染
void FfiOHOSAceFrameworkTextRender() {
    // 不应该在 FFI 层处理渲染！
}

// 正确：FFI 层只提供接口
void FfiOHOSAceFrameworkTextSetContent(const char* content);
```

### 常见陷阱与解决方案

#### 陷阱 1: 内存泄漏（FFI 回调）

**问题**:
```cpp
// 错误：回调中持有裸指针
void SetOnClick(void (*callback)()) {
    // 如果 FrameNode 销毁，callback 成为悬空指针
}
```

**解决**:
```cpp
// 正确：使用 WeakPtr
RefPtr<ViewAbstract> view = this;
auto callback = [weakView = AceType::WeakPtr<ViewAbstract>(view)]() {
    auto view = weakView.Upgrade();
    if (view) { /* 安全使用 */ }
};
```

#### 陷阱 2: 线程违规

**问题**: 后台线程调用 FFI 函数导致崩溃

**解决**: 使用 TaskExecutor Post 到 UI 线程

#### 陷阱 3: API 版本不兼容

**问题**: API 11+ 特性在 API 10- 设备上崩溃

**解决**: 检查 `GetMinPlatformVersion()` 并提供 fallback

#### 陷阱 4: 资源未释放

**问题**: ResourceObject 未调用 DecRef

**解决**:
```cpp
RefPtr<ResourceWrapper> CreateResourceWrapper(const NativeResourceObject& obj) {
    RefPtr<ResourceObject> resourceObj = ResourceManager::GetResource(obj);
    auto wrapper = AceType::MakeRefPtr<ResourceWrapper>(resourceObj);
    wrapper->AddRef();  // wrapper 负责释放
    return wrapper;
}
```

#### 陷阱 5: 组件未附加到树

**问题**: 创建 FrameNode 但未 AddChild

**解决**:
```cpp
auto host = ViewStackProcessor::GetInstance().GetTop();
CHECK_NULL_VOID(host);
auto frameNode = FrameNode::CreateFrameNode(...);
host->AddChild(frameNode);  // 附加到父节点
```

#### 陷阱 6: 事件重复注册

**问题**: 多次调用 SetOnClick 导致事件触发多次

**解决**:
```cpp
void SetButtonClick() {
    auto eventHub = button->GetEventHub<ClickEventHub>();
    if (!eventHub->GetClickCallback()) {  // 检查是否已注册
        button->SetOnClick(&OnClickCallback);
    }
}
```

---

## 调试指南

### 日志系统

#### 日志级别

```cpp
#include "base/log/ace_trace.h"

// 使用专用 Tag
TAG_LOGI(AceLogTag::ACE_CJ, "CJFrontend initialized");
TAG_LOGD(AceLogTag::ACE_CJ_ROUTER, "Page pushed: %{public}s", url.c_str());
TAG_LOGI(AceLogTag::ACE_CJ_FFI, "FFI called: %{public}s", funcName);
TAG_LOGD(AceLogTag::ACE_CJ_VIEW, "ViewAbstract created, type: %{public}s", type.c_str());
```

#### 日志 Tag

| Tag | 用途 |
|-----|------|
| ACE_CJ | CJ Frontend 核心日志 |
| ACE_CJ_ROUTER | 路由相关 |
| ACE_CJ_FFI | FFI 调用 |
| ACE_CJ_VIEW | CppView 层 |
| ACE_CJ_RUNTIME | Runtime 层 |

**避免**:
- ❌ 使用 `printf` / `std::cout`
- ❌ 使用通用 Tag（如 ACE_DEFAULT）
- ❌ 在热路径中字符串拼接

### DumpInfo

实现 Dump 方法用于调试：

```cpp
void CJFrontend::DumpFrontend() override {
    auto json = JsonUtil::Create(true);
    json->Put("type", "CJFrontend");
    json->Put("stageModel", IsStageModel());
    json->Put("foreground", IsForeground());
    json->Put("routerSize", GetRouterSize());

    auto router = GetPageRouterManager();
    if (router) {
        router->DumpInfo(json);
    }

    TAG_LOGI(AceLogTag::ACE_CJ, "%{public}s", json->ToString().c_str());
}
```

### 关键数据结构检查

#### Frontend 状态

```cpp
// 在调试器中检查
stageModel_           // Stage 模式是否启用
foregroundFrontend_   // 应用是否在前台
pageRouterManager_    // Router 实例
```

#### Router 状态

```cpp
pageStack_            // 当前页面栈
currentUri_           // 当前页面 URI
currentPageId_        // 当前页面 ID
```

#### Event Handler 状态

```cpp
asyncEventQueue_      // 待处理的异步事件
syncEventQueue_       // 待处理的同步事件
```

### 常见问题排查

#### 问题 1: FFI 函数崩溃

**检查清单**:
- [ ] 动态库是否加载: `LoadCJLibrary()`
- [ ] FFI 函数表是否注册: `AtCPackage` 不为 null
- [ ] 是否在 UI 线程: 检查调用线程
- [ ] 参数类型是否正确: 特别是指针和字符串

#### 问题 2: 组件不显示

**检查清单**:
- [ ] ViewAbstract 是否创建成功
- [ ] 组件是否添加到父节点: `ViewStackProcessor`
- [ ] 大小是否设置: width/height
- [ ] 父 FrameNode 是否存在且已附加

#### 问题 3: 事件回调未触发

**检查清单**:
- [ ] 回调是否注册: 不为 null
- [ ] 组件是否存活: 检查生命周期
- [ ] 事件类型是否匹配
- [ ] 线程是否正确

#### 问题 4: 性能问题

**排查方向**:
- [ ] FFI 调用频率: 是否在循环中调用
- [ ] 资源解析: 是否缓存
- [ ] LazyForEach: 是否使用
- [ ] 动画回调: 是否轻量级

### 性能分析工具

#### DevTools

```bash
# 启动 DevTools
hdc shell devtools
```

#### 日志分析

```bash
# 过滤 CJ 相关日志
hdc shell hilog -T ACE_CJ

# 保存日志
hdc shell hilog -T ACE_CJ > cj_log.txt
```

#### GDB/LLDB 调试

```bash
# 附加到应用进程
gdb <pid>

# 设置断点
b cj_frontend.cpp:123
b FfiOHOSAceFrameworkTextCreate

# 查看调用栈
bt

# 查看变量
p stageModel_
p pageRouterManager_
```

### FFI 调试技巧

#### 1. 验证 FFI 函数指针

```cpp
if (cjFuncs_) {
    TAG_LOGI(AceLogTag::ACE_CJ_RUNTIME, "CJ functions registered");
} else {
    TAG_LOGE(AceLogTag::ACE_CJ_RUNTIME, "CJ functions NOT registered!");
}
```

#### 2. 追踪 FFI 调用

```cpp
void FfiOHOSAceFrameworkTextSetContent(const char* content) {
    TAG_LOGD(AceLogTag::ACE_CJ_FFI, "TextSetContent called: %{public}s", content);
    // 实现逻辑
}
```

#### 3. 检查跨语言数据

```cpp
struct ExternalString {
    const char* data;
    int32_t length;

    void DebugPrint() const {
        TAG_LOGD(AceLogTag::ACE_CJ_FFI, "String: %{public}s, len: %{public}d",
                 data, length);
    }
};
```

---

## 附录

### 关键文件位置

**Frontend 层**:
- `frontend/cj_frontend.h` - 经典架构 Frontend
- `frontend/cj_frontend_ng.h` - NG 架构 Frontend
- `frontend/cj_frontend_abstract.h` - 抽象基类
- `frontend/cj_page_router.cpp` - 经典路由
- `frontend/cj_page_router_ng.cpp` - NG 路由
- `frontend/cj_event_handler.cpp` - 事件处理

**FFI 层**:
- `interfaces/cj_ffi/cj_common_ffi.h` - 通用类型定义
- `interfaces/cj_ffi/cj_macro.h` - FFI 宏定义
- `interfaces/cj_ffi/utils.h` - 工具函数
- `interfaces/cj_ffi/cj_*_ffi.h` - 组件 FFI（134 个）

**CppView 层**:
- `cppview/view_abstract.h` - 视图抽象基类
- `cppview/native_view.h` - 原生视图
- `cppview/shape_abstract.h` - 形状组件
- `cppview/interactable_view.h` - 可交互视图

**Runtime 层**:
- `runtime/cj_runtime_delegate.h` - Runtime 代理
- `runtime/cj_runtime.js` - Runtime 配置

### 版本兼容性

**API 10-** (PlatformVersion < 11):
- 使用 `lowVersionOffset_` float 属性
- 通过 `SetOffset(OffsetT)` 设置偏移
- 不支持 NodeAnimatableProperty

**API 11+** (PlatformVersion >= 11):
- 使用 `offsetProperty_` NodeAnimatableProperty
- 通过 `SetOffsetProperty()` 设置偏移
- 支持部分更新优化

### 参考文档

**项目级**:
- [CLAUDE.md](../../CLAUDE.md) - 项目级指导
- [frameworks/bridge/cj_frontend/CLAUDE.md](../../frameworks/bridge/cj_frontend/CLAUDE.md) - CJ Frontend 开发指导

**组件知识库**:
- [docs/pattern/](../pattern/) - 组件知识库目录
- [docs/knowledge_base_README.md](../knowledge_base_README.md) - 知识库索引

---

**文档结束**

如有问题或建议，请联系 ACE Engine 团队。
