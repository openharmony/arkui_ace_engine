# Sheet（半模态）组件完整知识库

> **文档版本**: v1.0
> **更新时间**: 2026-02-05
> **源码版本**: OpenHarmony ace_engine (master 分支)

---

## 📚 目录

1. [概述](#概述)
2. [目录结构](#目录结构)
3. [核心类继承关系](#核心类继承关系)
4. [Pattern层详解](#pattern层详解)
5. [Model层详解](#model层详解)
6. [完整API清单](#完整api清单)
7. [关键实现细节](#关键实现细节)
8. [使用示例](#使用示例)
9. [调试指南](#调试指南)
10. [常见问题](#常见问题)

---

## 概述

### 组件定位

**Sheet（半模态组件）** 是 OpenHarmony ArkUI 中用于展示临时内容、表单、菜单等的重要容器组件。它支持从屏幕底部、侧边、居中等多种位置弹出，并提供了丰富的交互能力（拖拽、滚动、键盘避让等）。

### 技术特点

- **自适应布局**：根据设备屏幕尺寸和方向自动选择最佳展示方式
- **流畅动画**：基于弹簧曲线的自然拖拽和回弹效果
- **多种展示类型**：支持 9 种不同的半模态类型（底部、居中、侧边、气泡等）
- **完整生命周期**：提供从创建到销毁的全流程回调
- **嵌套滚动支持**：与内部滚动组件完美协作
- **键盘避让**：多种策略应对软键盘弹出场景

### 架构演进

Sheet 组件在 ACE Engine 中存在两套实现：

| 架构 | 位置 | 状态 | 说明 |
|-----|------|------|------|
| **Legacy 架构** | `frameworks/core/components/semi_modal/` | ⚠️ 已废弃 | 旧版实现，不建议使用 |
| **NG 架构** | `frameworks/core/components_ng/pattern/overlay/` | ✅ 推荐 | 新版实现，功能完善 |

**本知识库重点关注 NG 架构**。

### 代码规模

- **核心文件**：15+ 个源文件
- **代码行数**：约 10,000+ 行
- **测试文件**：7+ 个单元测试文件
- **支持类型**：9 种半模态类型

---

## 目录结构

### NG 架构目录树

```
frameworks/core/components_ng/pattern/
├── overlay/
│   ├── sheet_presentation_pattern.h        # 主 Pattern 类（核心）
│   ├── sheet_presentation_pattern.cpp      # 主 Pattern 实现
│   ├── sheet_presentation_property.h       # 属性定义
│   ├── sheet_presentation_property.cpp     # 属性实现
│   ├── sheet_presentation_layout_algorithm.h    # 布局算法
│   ├── sheet_presentation_layout_algorithm.cpp  # 布局实现
│   ├── sheet_style.h                       # 样式数据结构（枚举、SheetStyle）
│   ├── sheet_manager.h                     # 管理器（单例）
│   ├── sheet_manager.cpp                   # 管理器实现
│   ├── sheet_view.cpp                      # 视图创建
│   ├── sheet_wrapper_pattern.h             # 包装器 Pattern
│   ├── sheet_wrapper_pattern.cpp           # 包装器实现
│   └── sheet_drag_bar_pattern.h/cpp        # 拖拽条 Pattern
│
└── sheet/
    ├── sheet_object.h                      # 抽象基类
    ├── sheet_object.cpp                    # 基类实现
    ├── side/
    │   ├── sheet_side_object.h             # 侧边半模态专用
    │   ├── sheet_side_object.cpp
    │   └── sheet_presentation_side_layout_algorithm.h
    ├── content_cover/
    │   ├── sheet_content_cover_object.h    # 内容覆盖型半模态
    │   ├── sheet_content_cover_object.cpp
    │   └── sheet_content_cover_layout_algorithm.h
    └── minimize/
        ├── sheet_minimize_object.h         # 最小化模式
        ├── sheet_minimize_object.cpp
        └── sheet_presentation_minimize_layout_algorithm.h
```

### 测试目录

```
test/unittest/core/pattern/overlay/
├── sheet_presentation_test_one_ng.cpp      # 基础功能测试
├── sheet_presentation_test_two_ng.cpp      # 边界情况测试
├── sheet_presentation_test_five_ng.cpp     # 特定场景测试
├── sheet_others_test_ng.cpp                # 其他功能测试
├── sheet_popup_test_ng.cpp                 # 气泡类型测试
├── sheet_showInSubwindow_test_ng.cpp       # 子窗口测试
└── sheet_presentation_test_ng.cpp          # 综合测试
```

---

## 核心类继承关系

### 类继承层次图

```
                     ┌──────────────────────────────────────────────────────────────┐
                     │                SheetPresentationPattern                       │
                     │           (overlay/sheet_presentation_pattern.h:52)          │
                     └──────────────────────────────────────────────────────────────┘
                                          │
          ┌───────────────┬───────────────┼───────────────┬───────────────┐
          │               │               │               │               │
          ↓               ↓               ↓               ↓               ↓
    ┌──────────┐   ┌──────────┐   ┌──────────┐   ┌──────────┐   ┌──────────────┐
    │LinearLayout│  │PopupBase │  │FocusView │  │Nestable  │  │AutoFill      │
    │  Pattern   │  │ Pattern  │  │          │  │Scroll    │  │TriggerState  │
    └──────────┘   └──────────┘   └──────────┘   └──────────┘   │  Holder      │
                                                        └──────────────┘
                                                               │
                                                        ┌──────┴──────┐
                                                        ↓             ↓
                                                  ┌──────────┐  ┌──────────┐
                                                  │AvoidInfo │  │IAvoidInfo│
                                                  │Listener  │  │Listener  │
                                                  └──────────┘  └──────────┘

                     ┌──────────────────────────────────────────────────────────────┐
                     │                      SheetObject                             │
                     │              (sheet/sheet_object.h:32)                      │
                     └──────────────────────────────────────────────────────────────┘
                                          │
          ┌───────────────────────────────┼───────────────────────┐
          │                               │                       │
          ↓                               ↓                       ↓
    ┌──────────┐                   ┌──────────┐           ┌──────────┐
    │SheetObject│                   │SheetSide │           │SheetContent│
    │  (Base)   │                   │  Object  │           │  Cover    │
    └──────────┘                   └──────────┘           └──────────┘
```

### 核心类说明

| 类名 | 文件位置 | 核心职责 | 继承基类数量 |
|-----|---------|---------|-------------|
| **SheetPresentationPattern** | [overlay/sheet_presentation_pattern.h:52](d:\Code\arkui_ace_engine_2_4\frameworks\core\components_ng\pattern\overlay\sheet_presentation_pattern.h:52) | 主 Pattern 类，管理半模态生命周期、布局、交互 | 6 个基类 |
| **SheetManager** | [overlay/sheet_manager.h:156](d:\Code\arkui_ace_engine_2_4\frameworks\core\components_ng\pattern\overlay\sheet_manager.h:156) | 单例管理器，负责创建/更新/关闭半模态 | Singleton<SheetManager> |
| **SheetObject** | [sheet/sheet_object.h:32](d:\Code\arkui_ace_engine_2_4\frameworks\core\components_ng\pattern\sheet\sheet_object.h:32) | 抽象基类，定义不同类型半模态的通用行为 | AceType |
| **SheetSideObject** | `sheet/side/sheet_side_object.h` | 侧边半模态专用实现 | SheetObject |
| **SheetContentCoverObject** | `sheet/content_cover/sheet_content_cover_object.h` | 内容覆盖型半模态实现 | SheetObject |
| **SheetPresentationProperty** | `overlay/sheet_presentation_property.h` | 属性管理，存储 SheetStyle | LayoutProperty |

---

## Pattern层详解

### SheetPresentationPattern 核心职责

**位置**: [overlay/sheet_presentation_pattern.h:52](d:\Code\arkui_ace_engine_2_4\frameworks\core\components_ng\pattern\overlay\sheet_presentation_pattern.h:52)

#### 多继承实现

```cpp
class SheetPresentationPattern :
    public LinearLayoutPattern,        // 线性布局能力
    public PopupBasePattern,           // 弹出层基础能力
    public FocusView,                  // 焦点管理
    public NestableScrollContainer,    // 嵌套滚动容器
    public AutoFillTriggerStateHolder, // 自动填充状态
    public IAvoidInfoListener          // 避让信息监听
```

**职责说明**：

1. **LinearLayoutPattern**：提供线性布局能力，管理子组件垂直/水平排列
2. **PopupBasePattern**：提供弹出层基础能力，管理遮罩、层级等
3. **FocusView**：管理焦点移动，支持键盘导航
4. **NestableScrollContainer**：实现嵌套滚动，协调内外滚动事件
5. **AutoFillTriggerStateHolder**：管理自动填充状态（如密码自动填充）
6. **IAvoidInfoListener**：监听系统避让信息（如系统栏、AI 栏）

### 生命周期方法

#### 1. OnModifyDone（属性修改完成）

**位置**: [overlay/sheet_presentation_pattern.cpp:92](d:\Code\arkui_ace_engine_2_4\frameworks\core\components_ng\pattern\overlay\sheet_presentation_pattern.cpp:92)

```cpp
void SheetPresentationPattern::OnModifyDone()
{
    Pattern::CheckLocalized();
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    // 1. 初始化手势事件
    InitPanEvent();

    // 2. 初始化页面高度
    InitPageHeight();

    // 3. 初始化半模态模式
    InitSheetMode();

    // 4. 初始化滚动属性
    sheetObject_->InitScrollProps();

    // 5. 初始化折叠屏区域
    InitFoldCreaseRegion();
}
```

**调用时机**：组件属性修改完成后，首次创建或属性更新时都会调用

**核心操作**：
- 初始化拖拽手势监听
- 计算页面高度和安全区域
- 确定半模态展示类型（底部、居中、侧边等）
- 初始化滚动参数
- 处理折叠屏场景

#### 2. OnAttachToFrameNode（挂载到节点）

**作用**：将 Pattern 挂载到 FrameNode 时执行

**核心操作**：
- 注册事件监听器（手势、焦点、键盘）
- 初始化动画属性
- 建立与 OverlayManager 的连接

#### 3. OnDirtyLayoutWrapperSwap（布局包装器交换）

**作用**：当布局需要更新时执行

**核心操作**：
- 执行布局计算（Measure → Layout）
- 计算半模态高度、宽度、位置
- 处理键盘避让
- 更新滚动高度
- 触发动画（如需要）

**代码位置**: [overlay/sheet_presentation_pattern.h:1134](d:\Code\arkui_ace_engine_2_4\frameworks\core\components_ng\pattern\overlay\sheet_presentation_pattern.h:1134)

```cpp
bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty,
                              const DirtySwapConfig& config) override;
```

#### 4. OnDetachFromFrameNode（从节点分离）

**位置**: [overlay/sheet_presentation_pattern.h:1127](d:\Code\arkui_ace_engine_2_4\frameworks\core\components_ng\pattern\overlay\sheet_presentation_pattern.h:1127)

```cpp
void OnDetachFromFrameNode(FrameNode* sheetNode) override;
```

**作用**：组件销毁时执行

**核心操作**：
- 移除手势监听
- 清理动画资源
- 移除回调
- 断开与 OverlayManager 的连接

### 交互事件处理

#### 拖拽事件

**位置**: [overlay/sheet_presentation_pattern.h:320-324](d:\Code\arkui_ace_engine_2_4\frameworks\core\components_ng\pattern\overlay\sheet_presentation_pattern.h:320-324)

```cpp
void HandleDragStart();                        // 拖拽开始
void HandleDragUpdate(const GestureEvent& info); // 拖拽中
void HandleDragEnd(float dragVelocity);        // 拖拽结束
```

**实现流程**：

```
HandleDragStart()
    ↓
记录初始位置、设置拖拽标志 (isDrag_ = true)
    ↓
HandleDragUpdate(info)
    ↓
计算拖拽偏移量 → UpdateTransformTranslate() → 实时更新 UI
    ↓
HandleDragEnd(dragVelocity)
    ↓
判断拖拽速度和距离
    ├─ 速度/距离超过阈值 → SheetInteractiveDismiss() 关闭
    └─ 未超过阈值 → SheetSpringBack() 回弹
```

**关键常量**（sheet_style.h）:
```cpp
constexpr float SHEET_VELOCITY_THRESHOLD = 1000.0f;  // 速度阈值
```

#### 滚动事件

**位置**: [overlay/sheet_presentation_pattern.h:924-936](d:\Code\arkui_ace_engine_2_4\frameworks\core\components_ng\pattern\overlay\sheet_presentation_pattern.h:924-936)

```cpp
// 实现 NestableScrollContainer 接口
Axis GetAxis() const override { return Axis::VERTICAL; }

ScrollResult HandleScroll(float scrollOffset, int32_t source,
    NestedState state = NestedState::GESTURE, float velocity = 0.f) override;

void OnScrollStartRecursive(WeakPtr<NestableScrollContainer> child,
    float position, float dragVelocity = 0.0f) override;

void OnScrollEndRecursive(const std::optional<float>& velocity) override;

void OnScrollDragEndRecursive() override;

bool HandleScrollVelocity(float velocity,
    const RefPtr<NestableScrollContainer>& child = nullptr) override;
```

**嵌套滚动处理**：
- 半模态可与内部 Scroll 组件协调滚动
- 支持手势速度传递实现惯性滚动
- 实现 `HandleScrollWithSheet()` 处理边界滚动

#### 键盘事件

**位置**: [overlay/sheet_presentation_pattern.h:316](d:\Code\arkui_ace_engine_2_4\frameworks\core\components_ng\pattern\overlay\sheet_presentation_pattern.h:316)

```cpp
void InitOnkeyEvent(const RefPtr<FocusHub>& focusHub);
```

**支持操作**：
- ESC 键关闭半模态
- Tab 键焦点导航
- 方向键移动焦点

### 动画系统

#### 动画曲线生成

**位置**: [sheet/sheet_object.h:40](d:\Code\arkui_ace_engine_2_4\frameworks\core\components_ng\pattern\sheet\sheet_object.h:40)

```cpp
virtual RefPtr<InterpolatingSpring> GetSheetTransitionCurve(float dragVelocity) const;
```

**弹簧参数**（sheet_style.h:39-42）:
```cpp
constexpr float CURVE_MASS = 1.0f;        // 质量
constexpr float CURVE_STIFFNESS = 328.0f;  // 刚度
constexpr float CURVE_DAMPING = 36.0f;     // 阻尼
```

#### 动画类型

| 动画类型 | 时长 | 说明 |
|---------|------|------|
| **进入动画** | 250ms | 从底部/侧边滑入 + 淡入 |
| **退出动画** | 100ms | 滑出 + 淡出 |
| **拖拽跟随** | 动态 | 根据拖拽速度实时更新 |
| **回弹动画** | 动态 | 使用弹簧曲线回弹 |

**动画触发**:
```cpp
void SheetTransition(bool isTransitionIn, float dragVelocity = 0.0f);
```

---

## Model层详解

### SheetStyle 数据结构

**位置**: [overlay/sheet_style.h:179-315](d:\Code\arkui_ace_engine_2_4\frameworks\core\components_ng\pattern\overlay\sheet_style.h:179-315)

#### 核心属性

```cpp
struct SheetStyle {
    // ========== 基础属性 ==========
    SheetHeight sheetHeight;                      // 高度设置
    std::optional<SheetType> sheetType;           // 半模态类型
    std::optional<Dimension> width;               // 宽度

    // ========== 显示属性 ==========
    std::optional<bool> showDragBar;              // 是否显示拖拽条
    std::optional<bool> enableFloatingDragBar;    // 是否启用浮动拖拽条
    std::optional<bool> showCloseIcon;            // 是否显示关闭按钮
    std::optional<bool> isTitleBuilder;           // 是否使用自定义标题构建器

    // ========== 样式属性 ==========
    std::optional<Color> backgroundColor;         // 背景颜色
    std::optional<Color> maskColor;               // 遮罩颜色
    std::optional<BlurStyleOption> backgroundBlurStyle; // 背景模糊
    std::optional<NG::BorderRadiusProperty> radius; // 圆角
    std::optional<Shadow> shadow;                 // 阴影
    std::optional<NG::BorderWidthProperty> borderWidth; // 边框宽度
    std::optional<NG::BorderColorProperty> borderColor; // 边框颜色

    // ========== 标题属性 ==========
    std::optional<std::string> sheetTitle;        // 主标题
    std::optional<std::string> sheetSubtitle;     // 副标题

    // ========== 交互属性 ==========
    std::optional<bool> interactive;              // 是否允许交互
    std::optional<bool> showInPage;               // 是否在页面内显示（非覆盖）
    std::vector<SheetHeight> detents;             // 停留点（多档位高度）

    // ========== 高级属性 ==========
    std::optional<ScrollSizeMode> scrollSizeMode; // 滚动模式
    std::optional<SheetKeyboardAvoidMode> sheetKeyboardAvoidMode; // 键盘避让
    std::optional<OffsetF> bottomOffset;          // 底部偏移（SHEET_BOTTOM_OFFSET）
    std::optional<SheetHeight> detentSelection;   // 选中的停留点
    std::optional<SheetEffectEdge> sheetEffectEdge; // 拖拽边缘
    std::optional<HoverModeAreaType> hoverModeArea; // 悬停模式区域

    // ========== 布局属性 ==========
    std::optional<Placement> placement;           // 气泡位置
    std::optional<bool> placementOnTarget;        // 是否定位在目标上
    std::optional<bool> showInSubWindow;          // 是否在子窗口显示

    // ========== 其他 ==========
    std::optional<int32_t> instanceId;            // UIContext 实例 ID
    std::optional<ModalTransition> modalTransition; // 转场动画
    std::optional<RenderStrategy> radiusRenderStrategy; // 圆角渲染策略
    RefPtr<UiMaterial> systemMaterial;            // 系统材质（模糊等）
};
```

### SheetType 枚举

**位置**: [overlay/sheet_style.h:53-63](d:\Code\arkui_ace_engine_2_4\frameworks\core\components_ng\pattern\overlay\sheet_style.h:53-63)

```cpp
enum SheetType {
    SHEET_BOTTOM,              // 底部半模态（默认，手机竖屏）
    SHEET_CENTER,              // 居中半模态（平板、大屏）
    SHEET_POPUP,               // 气泡半模态（大屏，带箭头）
    SHEET_SIDE = 3,            // 侧边半模态（横屏、大屏）
    SHEET_CONTENT_COVER = 4,   // 内容覆盖型（覆盖目标区域）
    SHEET_BOTTOMLANDSPACE,     // 横屏底部（手机横屏）
    SHEET_BOTTOM_FREE_WINDOW,  // 自由窗口模式
    SHEET_BOTTOM_OFFSET,       // 带偏移的底部（自定义位置）
    SHEET_MINIMIZE,            // 最小化模式
};
```

### SheetMode 枚举

**位置**: [overlay/sheet_style.h:47-51](d:\Code\arkui_ace_engine_2_4\frameworks\core\components_ng\pattern\overlay\sheet_style.h:47-51)

```cpp
enum SheetMode {
    MEDIUM,  // 中等高度（50% 屏幕高度）
    LARGE,   // 大高度（90% 屏幕高度）
    AUTO,    // 自动（根据内容）
};
```

### SheetHeight 结构

**位置**: [overlay/sheet_style.h:156-169](d:\Code\arkui_ace_engine_2_4\frameworks\core\components_ng\pattern\overlay\sheet_style.h:156-169)

```cpp
struct SheetHeight {
    std::optional<Dimension> height;      // 具体高度值
    std::optional<SheetMode> sheetMode;   // 预设模式

    bool operator==(const SheetHeight& sheetHeight) const;
    bool operator!=(const SheetHeight& sheetHeight) const;
};
```

### SheetKeyboardAvoidMode 枚举

**位置**: [overlay/sheet_style.h:171-177](d:\Code\arkui_ace_engine_2_4\frameworks\core\components_ng\pattern\overlay\sheet_style.h:171-177)

```cpp
enum class SheetKeyboardAvoidMode {
    NONE,                   // 不避让
    TRANSLATE_AND_RESIZE,   // 平移 + 缩放
    RESIZE_ONLY,            // 仅缩放
    TRANSLATE_AND_SCROLL,   // 平移 + 滚动（推荐）
    POPUP_SHEET,            // 气泡半模态模式
};
```

### ScrollSizeMode 枚举

**位置**: [overlay/sheet_style.h:151-154](d:\Code\arkui_ace_engine_2_4\frameworks\core\components_ng\pattern\overlay\sheet_style.h:151-154)

```cpp
enum ScrollSizeMode {
    FOLLOW_DETENT,  // 跟随停留点（档位切换）
    CONTINUOUS,     // 连续滚动（无档位）
};
```

---

## 完整API清单

### ArkTS API

#### 静态 API（.ets 文件）

**位置**: `OpenHarmony/interface/sdk-js/api/arkui/@ohos.arkui.advanced.SheetPanel.d.ts`

```typescript
// 创建半模态
SheetPanel.create(): SheetPanel;

// 设置高度
height(value: SheetHeight | SheetMode): SheetPanel;

// 设置类型
type(value: SheetType): SheetPanel;

// 设置背景颜色
backgroundColor(value: ResourceColor): SheetPanel;

// 设置遮罩颜色
maskColor(value: ResourceColor): SheetPanel;

// 显示/隐藏拖拽条
dragBar(value: boolean): SheetPanel;

// 显示/隐藏关闭按钮
showClose(value: boolean): SheetPanel;

// 设置边框圆角
borderRadius(value: BorderRadius): SheetPanel;

// 设置阴影
shadow(value: ShadowOptions): SheetPanel;

// 设置停留点（多档位）
detents(value: Array<SheetHeight>): SheetPanel;

// 设置键盘避让模式
avoidMode(value: SheetKeyboardAvoidMode): SheetPanel;

// 设置标题
title(value: string): SheetPanel;

// 设置副标题
subtitle(value: string): SheetPanel;

// 绑定到目标组件
bindTo(value: CoreObject): SheetPanel;

// 显示半模态
show(): void;

// 关闭半模态
dismiss(): void;
```

#### 回调 API

```typescript
// 出现回调
onAppear(callback: () => void): SheetPanel;

// 即将出现回调
onWillAppear(callback: () => void): SheetPanel;

// 即将消失回调
onWillDisappear(callback: () => void): SheetPanel;

// 消失回调
onDisappear(callback: () => void): SheetPanel;

// 即将关闭回调（带原因）
onWillDismiss(callback: (reason: number) => void): SheetPanel;

// 是否允许关闭回调
shouldDismiss(callback: () => boolean): SheetPanel;

// 高度变化回调
onHeightDidChange(callback: (height: number) => void): SheetPanel;

// 停留点变化回调
onDetentsDidChange(callback: (height: number) => void): SheetPanel;

// 宽度变化回调
onWidthDidChange(callback: (width: number) => void): SheetPanel;

// 类型变化回调
onTypeDidChange(callback: (type: number) => void): SheetPanel;

// 回弹回调
onSpringBack(callback: () => void): SheetPanel;
```

### C++ API

#### SheetManager API

**位置**: [overlay/sheet_manager.h:156-233](d:\Code\arkui_ace_engine_2_4\frameworks\core\components_ng\pattern\overlay\sheet_manager.h:156-233)

```cpp
class SheetManager : public Singleton<SheetManager> {
public:
    // 创建半模态
    int32_t OpenBindSheetByUIContext(
        const RefPtr<NG::FrameNode>& sheetContentNode,
        std::function<void()>&& titleBuildFunc,
        NG::SheetStyle& sheetStyle,
        std::function<void()>&& onAppear,
        std::function<void()>&& onDisappear,
        std::function<void()>&& shouldDismiss,
        std::function<void(const int32_t info)>&& onWillDismiss,
        std::function<void()>&& onWillAppear,
        std::function<void()>&& onWillDisappear,
        std::function<void(const float)>&& onHeightDidChange,
        std::function<void(const float)>&& onDetentsDidChange,
        std::function<void(const float)>&& onWidthDidChange,
        std::function<void(const float)>&& onTypeDidChange,
        std::function<void()>&& sheetSpringBack,
        int32_t currentInstanceId,
        int32_t targetId
    );

    // 更新半模态
    int32_t UpdateBindSheetByUIContext(
        const RefPtr<NG::FrameNode>& sheetContentNode,
        const NG::SheetStyle& sheetStyle,
        bool isPartialUpdate,
        int32_t currentInstanceId
    );

    // 关闭半模态
    int32_t CloseBindSheetByUIContext(
        const RefPtr<NG::FrameNode>& sheetContentNode,
        int32_t currentInstanceId
    );

    // 清理映射
    void CleanBindSheetMap(int32_t instanceId, int32_t sheetContentNodeId);

    // 查找 OverlayManager
    static RefPtr<OverlayManager> FindPageNodeOverlay(
        const RefPtr<FrameNode>& targetNode,
        bool isShow,
        bool isStartByUIContext = false
    );

    // 设置关闭 ID
    void SetDismissSheet(int32_t dismissId);
    int32_t GetDismissSheet();

    // 焦点管理
    void SetFocusSheetId(const std::optional<int32_t>& id);
    std::optional<int32_t> GetFocusSheetId() const;

    // 移除半模态（ESC 键）
    bool RemoveSheetByESC();

    // 删除窗口场景的 Overlay
    void DeleteOverlayForWindowScene(
        int32_t rootNodeId,
        RootNodeType rootNodeType,
        int32_t targetId
    );

    // 设置遮罩可交互
    static void SetMaskInteractive(
        const RefPtr<FrameNode>& maskNode,
        bool isInteractive
    );

    // 注册销毁回调
    void RegisterDestroyCallback(
        const RefPtr<FrameNode>& targetNode,
        NG::SheetStyle& sheetStyle,
        const int32_t containerId
    );

    // 创建断点状态（状态模式）
    std::unique_ptr<State> CreateBreakPointState(
        WidthBreakpoint width,
        HeightBreakpoint height
    );
};
```

#### SheetPresentationPattern API

**位置**: [overlay/sheet_presentation_pattern.h:62-1082](d:\Code\arkui_ace_engine_2_4\frameworks\core\components_ng\pattern\overlay\sheet_presentation_pattern.h:62-1082)

##### 生命周期管理

```cpp
// 初始化布局属性
void InitialLayoutProps();

// 更新拖拽条状态
void UpdateDragBarStatus();

// 检查是否单档位
bool IsSingleDetents(const NG::SheetStyle& sheetStyle);

// 检查是否可滚动
bool IsScrollable() const;

// 避让 AI 栏
void AvoidAiBar();

// 避让安全区域
void AvoidSafeArea(bool forceAvoid = false);

// 避让键盘
void AvoidKeyboard(bool forceAvoid);

// 检查构建器变化
void CheckBuilderChange();

// 获取半模态高度变化
float GetSheetHeightChange();

// 滚动到指定高度
void ScrollTo(float height);

// 设置列最小尺寸
void SetColumnMinSize(bool reset = false);

// 初始化单档位高度
float InitialSingleGearHeight(NG::SheetStyle& sheetStyle);

// 获取半模态顶部安全区域
float GetSheetTopSafeArea();

// 更新半模态转场偏移
float UpdateSheetTransitionOffset();
```

##### 动画相关

```cpp
// 半模态转场
void SheetTransition(bool isTransitionIn, float dragVelocity = 0.0f);

// 侧边半模态转场
void SideSheetTransition(bool isTransitionIn);

// 修改触发半模态转场
void ModifyFireSheetTransition(float dragVelocity = 0.0f);

// 半模态交互式关闭
void SheetInteractiveDismiss(BindSheetDismissReason dismissReason, float dragVelocity = 0.0f);

// 遮罩半模态回弹
void OverlaySheetSpringBack();

// 遮罩关闭半模态
void OverlayDismissSheet();

// 关闭半模态
void DismissSheet();

// 半模态回弹
void SheetSpringBack();
```

##### 尺寸计算

```cpp
// 获取页面高度（去除偏移）
float GetPageHeight();

// 设置页面高度
void SetPageHeight(float height);

// 设置居中高度
void SetCenterHeight(float height);

// 获取居中高度
float GetCenterHeight() const;

// 获取半模态偏移 X
float GetSheetOffsetX() const;

// 获取半模态偏移 Y
float GetSheetOffsetY() const;

// 设置半模态偏移 X
void SetSheetOffsetX(float offsetX);

// 设置半模态偏移 Y
void SetSheetOffsetY(float offsetY);

// 获取高度
float GetHeight() const;

// 设置半模态向上高度
void SetSheetHeightUp(float value);

// 获取半模态向上高度
float GetSheetHeightUp() const;

// 获取最大半模态高度
float GetSheetMaxHeight();

// 设置最大半模态高度
void SetSheetMaxHeight(float height);

// 设置最大半模态宽度
void SetSheetMaxWidth(float width);
```

##### 类型判断

```cpp
// 获取半模态类型
SheetType GetSheetType() const;

// 判断是否手机横屏
bool IsPhoneInLandScape();

// 判断是否显示关闭图标
bool IsShowCloseIcon();

// 初始化半模态模式
void InitSheetMode();

// 使用 Auto 获取半模态类型
void GetSheetTypeWithAuto(SheetType& sheetType) const;

// 使用 Popup 获取半模态类型
void GetSheetTypeWithPopup(SheetType& sheetType) const;

// 使用 Center 获取半模态类型
void GetSheetTypeWithCenter(SheetType& sheetType) const;

// 判断是否底部样式
bool IsSheetBottomStyle();

// 判断是否底部类型
bool IsSheetBottom() const;

// 判断是否折叠展开
bool IsFoldExpand() const;

// 判断是否显示在子窗口二合一
bool IsShowInSubWindowTwoInOne();

// 判断是否显示在子窗口
bool IsShowInSubWindow() const;

// 计算子窗口中的半模态类型
SheetType ComputeSheetTypeInSubWindow() const;

// 判断是否 PC 或平板自由多窗口模式
bool IsPcOrPadFreeMultiWindowMode() const;
```

##### 状态管理

```cpp
// 设置 UI 首次切换
void SetUIFirstSwitch(bool isFirstTransition, bool isNone);

// 气泡半模态转场
void BubbleStyleSheetTransition(bool isTransitionIn);

// 开始偏移进入动画
void StartOffsetEnteringAnimation();

// 开始 Alpha 进入动画
void StartAlphaEnteringAnimation(std::function<void()> finish);

// 开始偏移退出动画
void StartOffsetExitingAnimation();

// 开始 Alpha 退出动画
void StartAlphaExitingAnimation(std::function<void()> finish);

// 重置为不可见
void ResetToInvisible();

// 获取动画中断
bool GetAnimationBreak() const;

// 设置动画中断
void SetAnimationBreak(bool value);

// 设置动画进行中
void SetAnimationProcess(bool isProcess);

// 获取动画进行中
bool GetAnimationProcess();

// 设置关闭进行中
void SetDismissProcess(bool isProcess);

// 获取关闭进行中
bool GetDismissProcess();

// 设置显示状态
void SetShowState(bool show);

// 获取显示状态
bool GetShowState() const;

// 设置拖拽中
void SetIsDragging(bool isDrag);

// 判断是否拖拽中
bool IsDragging() const;

// 判断是否回弹
bool WillSpringBack() const;

// 设置回弹
void SetSpringBack(bool value);
```

---

## 关键实现细节

### 1. 自动类型选择（状态模式）

**位置**: [overlay/sheet_manager.h:24-154](d:\Code\arkui_ace_engine_2_4\frameworks\core\components_ng\pattern\overlay\sheet_manager.h:24-154)

#### 状态模式实现

```cpp
// 抽象状态
class State {
public:
    virtual SheetType HandleType(const SheetStyle& sheetStyle) = 0;
    virtual ~State() = default;
};

// 具体状态
class WidthXSState : public State {
public:
    SheetType HandleType(const SheetStyle& sheetStyle) override {
        // 超小屏幕：默认底部样式，可设置为内容覆盖
        if (sheetStyle.sheetType.has_value() &&
            sheetStyle.sheetType.value() == SheetType::SHEET_CONTENT_COVER) {
            return sheetStyle.sheetType.value();
        }
        SheetType sheetType = SheetType::SHEET_BOTTOM;
        auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_RETURN(pipeline, sheetType);
        auto sheetTheme = pipeline->GetTheme<SheetTheme>();
        CHECK_NULL_RETURN(sheetTheme, sheetType);
        auto sheetThemeType = sheetTheme->GetSheetType();
        if (sheetThemeType == "popup") {
            sheetType = SheetType::SHEET_BOTTOM_FREE_WINDOW;
        }
        return sheetType;
    }
};

class WidthSMState : public State { /* 类似实现 */ };
class WidthMDHeightSMState : public State { /* 横屏底部 */ };
class WidthMDHeightMDOrLGState : public State { /* 居中 */ };
class WidthLGState : public State { /* 气泡 */ };
```

#### 断点选择规则

| 屏幕尺寸 | 默认类型 | 开发者可设置 |
|---------|---------|------------|
| WidthXS (≤320vp) | SHEET_BOTTOM | SHEET_CONTENT_COVER |
| WidthSM (≤600vp) | SHEET_BOTTOM | SHEET_CONTENT_COVER |
| WidthMD + HeightSM | SHEET_BOTTOMLANDSPACE | SHEET_CONTENT_COVER, SHEET_BOTTOM, SHEET_SIDE |
| WidthMD + HeightMD/LG | SHEET_CENTER | 所有类型 |
| WidthLG (≥840vp) | SHEET_POPUP (可配置) | 所有类型 |

### 2. 桥接模式（动态类型切换）

**位置**: [overlay/sheet_presentation_pattern.h:1034-1041](d:\Code\arkui_ace_engine_2_4\frameworks\core\components_ng\pattern\overlay\sheet_presentation_pattern.h:1034-1041)

#### 实现方式

```cpp
class SheetPresentationPattern {
private:
    RefPtr<SheetObject> sheetObject_;  // 桥接到具体类型

public:
    void InitSheetObject();

    void UpdateSheetObject(SheetType newType) {
        auto oldObject = sheetObject_;

        // 根据类型创建新的 SheetObject
        switch (newType) {
            case SheetType::SHEET_SIDE:
                sheetObject_ = MakeRefPtr<SheetSideObject>();
                break;
            case SheetType::SHEET_CONTENT_COVER:
                sheetObject_ = MakeRefPtr<SheetContentCoverObject>();
                break;
            case SheetType::SHEET_MINIMIZE:
                sheetObject_ = MakeRefPtr<SheetMinimizeObject>();
                break;
            default:
                sheetObject_ = MakeRefPtr<SheetObject>(newType);
                break;
        }

        // 复制数据
        sheetObject_->CopyData(oldObject);

        // 重新绑定 Pattern
        sheetObject_->BindPattern(WeakPtr(this));
    }
};
```

#### 优势

- 运行时动态切换半模态类型
- 不同类型共享核心逻辑
- 易于扩展新类型

### 3. 键盘避让机制

**位置**: [overlay/sheet_presentation_pattern.h:303](d:\Code\arkui_ace_engine_2_4\frameworks\core\components_ng\pattern\overlay\sheet_presentation_pattern.h:303)

#### 实现流程

```cpp
void SheetPresentationPattern::AvoidKeyboard(bool forceAvoid)
{
    // 1. 判断是否需要避让
    if (!IsNeedChangeScrollHeight(height)) {
        return;
    }

    // 2. 获取键盘高度
    uint32_t keyboardHeight = GetKeyboardHeight();
    if (keyboardHeight == 0) {
        return;
    }

    // 3. 根据模式执行避让策略
    auto avoidMode = GetKeyboardAvoidMode();

    switch (avoidMode) {
        case SheetKeyboardAvoidMode::TRANSLATE_AND_SCROLL:
            // 平移半模态 + 减小滚动区域
            AvoidKeyboardBySheetMode(forceAvoid);
            break;

        case SheetKeyboardAvoidMode::RESIZE_ONLY:
            // 仅减小半模态高度
            SetSheetHeight(height - keyboardHeight);
            break;

        case SheetKeyboardAvoidMode::POPUP_SHEET:
            // 气泡半模态：调整位置
            AdjustPopupPosition(keyboardHeight);
            break;

        default:
            break;
    }

    // 4. 标记需要重新布局
    host->MarkDirtyNode(PROPERTY_PATTERN_LAYOUT_ALGORITHM);
}

void SheetPresentationPattern::AvoidKeyboardBySheetMode(bool forceAvoid)
{
    auto keyboardHeight = GetKeyboardHeight();

    // 方式 1：双次避让（先平移，再滚动）
    if (IsDoubleAvoid(forceAvoid)) {
        // 第一次：平移半模态
        float translateHeight = keyboardHeight / 2;
        TranslateTo(translateHeight);

        // 第二次：减小滚动高度
        float scrollHeightDecrease = keyboardHeight - translateHeight;
        DecreaseScrollHeightInSheet(scrollHeightDecrease);
    } else {
        // 单次避让：只减小滚动高度
        DecreaseScrollHeightInSheet(keyboardHeight);
    }
}
```

#### 避让效果

```
┌─────────────────────────────────┐
│         页面内容                  │
├─────────────────────────────────┤ ← 键盘弹出
│    ┌───────────────────────┐    │
│    │   Sheet 半模态         │    │
│    │  ┌─────────────────┐  │    │
│    │  │  可滚动区域      │  │    │ ← 滚动区域减小
│    │  │                 │  │    │
│    │  └─────────────────┘  │    │
│    └───────────────────────┘    │
├─────────────────────────────────┤
│         软键盘                   │
└─────────────────────────────────┘
```

### 4. 嵌套滚动实现

**位置**: [overlay/sheet_presentation_pattern.h:924-936](d:\Code\arkui_ace_engine_2_4\frameworks\core\components_ng\pattern\overlay\sheet_presentation_pattern.h:924-936)

#### 滚动协调机制

```cpp
ScrollResult SheetPresentationPattern::HandleScroll(
    float scrollOffset,
    int32_t source,
    NestedState state,
    float velocity)
{
    // 1. 判断是否需要处理滚动
    if (!IsScrollable()) {
        return { .consume = false, .reachBottom = false, .reachEdge = false };
    }

    // 2. 委托给 SheetObject 处理
    auto result = sheetObject_->HandleScroll(scrollOffset, source, state, velocity);

    // 3. 如果 SheetObject 未消耗，尝试内部滚动
    if (!result.consume) {
        result = HandleScrollWithSheet(scrollOffset);
    }

    return result;
}

void SheetPresentationPattern::OnScrollStartRecursive(
    WeakPtr<NestableScrollContainer> child,
    float position,
    float dragVelocity)
{
    // 通知子滚动容器开始滚动
    auto childPtr = child.Upgrade();
    if (childPtr) {
        childPtr->OnScrollStartRecursive(position, dragVelocity);
    }

    // 记录滚动起始位置
    scrollStartPosition_ = position;
}

void SheetPresentationPattern::OnScrollEndRecursive(
    const std::optional<float>& velocity)
{
    // 处理惯性滚动
    if (velocity.has_value() && HandleScrollVelocity(velocity.value())) {
        return;
    }

    // 判断是否需要切换停留点
    CheckDetentChange();
}
```

#### 滚动优先级

```
1. Sheet 半模态拖拽滚动（改变高度）
2. Sheet 内部滚动组件滚动
3. 父容器滚动
```

### 5. 多档位高度（Detents）

**位置**: [overlay/sheet_style.h:192](d:\Code\arkui_ace_engine_2_4\frameworks\core\components_ng\pattern\overlay\sheet_style.h:192)

#### 实现方式

```cpp
// SheetStyle 中定义
std::vector<SheetHeight> detents;

// ArkTS API 使用
SheetPanel()
    .height(100)      // 档位 1: 100vp
    .detents([
        { height: 200 },  // 档位 2: 200vp
        { height: 300 },  // 档位 3: 300vp
        { mode: SheetMode.LARGE }  // 档位 4: 大模式
    ])
```

#### 档位切换逻辑

```cpp
void SheetPresentationPattern::UpdateDetentsIndex(float currentHeight)
{
    auto detents = GetSheetDetentHeight();

    // 找到最近的档位
    uint32_t nearestIndex = 0;
    float minDistance = std::abs(currentHeight - detents[0]);

    for (uint32_t i = 1; i < detents.size(); i++) {
        float distance = std::abs(currentHeight - detents[i]);
        if (distance < minDistance) {
            minDistance = distance;
            nearestIndex = i;
        }
    }

    // 如果档位发生变化
    if (nearestIndex != GetDetentsIndex()) {
        SetDetentsIndex(nearestIndex);

        // 触发回调
        FireOnDetentsDidChange(detents[nearestIndex]);

        // 滚动到档位高度
        ScrollTo(detents[nearestIndex]);
    }
}
```

### 6. 拖拽物理效果

**位置**: [sheet/sheet_object.h:40](d:\Code\arkui_ace_engine_2_4\frameworks\core\components_ng\pattern\sheet\sheet_object.h:40)

#### 弹簧曲线生成

```cpp
RefPtr<InterpolatingSpring> SheetObject::GetSheetTransitionCurve(float dragVelocity) const
{
    // 根据拖拽速度调整弹簧参数
    float stiffness = CURVE_STIFFNESS;  // 默认 328
    float damping = CURVE_DAMPING;      // 默认 36
    float mass = CURVE_MASS;            // 默认 1.0

    // 速度越快，刚度越大（回弹更有力）
    if (std::abs(dragVelocity) > 1000.0f) {
        stiffness = 400.0f;
    }

    // 创建弹簧曲线
    return InterpolatingSpring::Create(stiffness, damping, mass);
}
```

#### 拖拽结束判断

```cpp
void SheetPresentationPattern::HandleDragEnd(float dragVelocity)
{
    float currentOffset = GetCurrentOffset();
    float threshold = GetSheetHeight() * 0.3f;  // 30% 阈值

    // 判断是否关闭
    if (std::abs(dragVelocity) > SHEET_VELOCITY_THRESHOLD ||  // 速度超过阈值
        currentOffset > threshold) {                             // 拖拽距离超过阈值
        SheetInteractiveDismiss(BindSheetDismissReason::SLIDE_DOWN, dragVelocity);
    } else {
        // 回弹到最近档位
        SheetSpringBack();
    }
}
```

---

## 使用示例

### 示例 1：基础底部半模态

```typescript
@Entry
@Component
struct BasicSheetExample {
  @State showSheet: boolean = false;

  build() {
    Column() {
      Button('显示半模态')
        .onClick(() => {
          this.showSheet = true;
        })
    }
    .width('100%')
    .height('100%')
    .bindSheet(this.showSheet, this.SheetContent())
    .height(SheetMode.MEDIUM)
  }

  @Builder
  SheetContent() {
    Column() {
      Text('这是半模态内容')
        .fontSize(20)
        .margin(20)
    }
    .width('100%')
    .height('100%')
  }
}
```

### 示例 2：多档位高度

```typescript
@Entry
@Component
struct DetentsSheetExample {
  @State showSheet: boolean = false;

  build() {
    Column() {
      Button('显示多档位半模态')
        .onClick(() => {
          this.showSheet = true;
        })
    }
    .bindSheet(this.showSheet, this.SheetContent(), {
      height: 100,  // 初始高度
      detents: [
        200,        // 档位 1: 200vp
        400,        // 档位 2: 400vp
        SheetMode.LARGE  // 档位 3: 大模式（90%）
      ],
      showDragBar: true,
      onHeightDidChange: (height) => {
        console.info(`高度变化: ${height}`);
      }
    })
  }

  @Builder
  SheetContent() {
    Column() {
      Text('可滚动内容')
      // ... 更多内容
    }
  }
}
```

### 示例 3：侧边半模态

```typescript
@Entry
@Component
struct SideSheetExample {
  @State showSheet: boolean = false;

  build() {
    Column() {
      Button('显示侧边半模态')
        .onClick(() => {
          this.showSheet = true;
        })
    }
    .bindSheet(this.showSheet, this.SheetContent(), {
      type: SheetType.SIDE,
      width: 300,
      showClose: true
    })
  }

  @Builder
  SheetContent() {
    Column() {
      Text('侧边菜单')
      List() {
        ListItem() { Text('选项 1') }
        ListItem() { Text('选项 2') }
        ListItem() { Text('选项 3') }
      }
    }
  }
}
```

### 示例 4：居中对话框式半模态

```typescript
@Entry
@Component
struct CenterSheetExample {
  @State showSheet: boolean = false;

  build() {
    Column() {
      Button('显示对话框')
        .onClick(() => {
          this.showSheet = true;
        })
    }
    .bindSheet(this.showSheet, this.SheetContent(), {
      type: SheetType.CENTER,
      height: SheetMode.MEDIUM,
      width: '80%',
      borderRadius: 16,
      showClose: true,
      onWillDismiss: (reason) => {
        console.info(`关闭原因: ${reason}`);
      }
    })
  }

  @Builder
  SheetContent() {
    Column() {
      Text('确认操作')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Text('是否确认执行此操作？')
        .fontSize(16)
        .margin({ bottom: 30 })

      Row() {
        Button('取消')
          .onClick(() => {
            this.showSheet = false;
          })

        Button('确认')
          .onClick(() => {
            // 执行操作
            this.showSheet = false;
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .padding(30)
  }
}
```

### 示例 5：带回调的半模态

```typescript
@Entry
@Component
struct CallbackSheetExample {
  @State showSheet: boolean = false;
  @State currentHeight: number = 0;

  build() {
    Column() {
      Button('显示半模态')
        .onClick(() => {
          this.showSheet = true;
        })

      Text(`当前高度: ${this.currentHeight}`)
    }
    .bindSheet(this.showSheet, this.SheetContent(), {
      height: 300,
      detents: [200, 400, 600],
      showDragBar: true,

      // 生命周期回调
      onAppear: () => {
        console.info('半模态已出现');
      },
      onWillAppear: () => {
        console.info('半模态即将出现');
      },
      onWillDisappear: () => {
        console.info('半模态即将消失');
      },
      onDisappear: () => {
        console.info('半模态已消失');
      },

      // 变化回调
      onHeightDidChange: (height) => {
        this.currentHeight = height;
        console.info(`高度变化: ${height}`);
      },
      onDetentsDidChange: (height) => {
        console.info(`档位变化: ${height}`);
      },
      onSpringBack: () => {
        console.info('回弹');
      },

      // 关闭回调
      shouldDismiss: () => {
        // 返回 true 允许关闭，false 阻止关闭
        return true;
      },
      onWillDismiss: (reason) => {
        // reason: 0=返回键, 1=点击外部, 2=关闭按钮, 3=下拉, 4=拖拽
        console.info(`关闭原因: ${reason}`);
      }
    })
  }

  @Builder
  SheetContent() {
    Column() {
      Text('拖拽我体验回调')
        .fontSize(20)
    }
  }
}
```

### 示例 6：键盘避让

```typescript
@Entry
@Component
struct KeyboardAvoidExample {
  @State showSheet: boolean = false;
  @State inputValue: string = '';

  build() {
    Column() {
      Button('显示表单')
        .onClick(() => {
          this.showSheet = true;
        })
    }
    .bindSheet(this.showSheet, this.SheetContent(), {
      height: 400,
      avoidMode: SheetKeyboardAvoidMode.TRANSLATE_AND_SCROLL,
      showDragBar: true
    })
  }

  @Builder
  SheetContent() {
    Column() {
      Text('表单')
        .fontSize(24)
        .margin({ bottom: 20 })

      TextInput({ placeholder: '请输入内容' })
        .width('100%')
        .onChange((value) => {
          this.inputValue = value;
        })

      TextArea({ placeholder: '多行文本' })
        .width('100%')
        .height(100)
        .margin({ top: 10 })
    }
    .padding(20)
    .width('100%')
  }
}
```

---

## 调试指南

### 1. 日志调试

#### 启用 Sheet 组件日志

**代码位置**: 使用 `AceLogTag::ACE_SHEET` 标签

```cpp
// 在代码中添加日志
TAG_LOGI(AceLogTag::ACE_SHEET, "Sheet 高度: %{public}f", height);
TAG_LOGD(AceLogTag::ACE_SHEET, "Sheet 类型: %{public}d", static_cast<int>(sheetType_));
```

**HDC 日志过滤**：

```bash
# 查看 Sheet 相关日志
hdc shell hilog | grep "ACE_SHEET"

# 只看 Info 级别
hdc shell hilog -t ACE_SHEET -v time

# 保存到文件
hdc shell hilog -t ACE_SHEET > sheet_log.txt
```

### 2. Dump 信息

#### 获取半模态组件信息

**位置**: [overlay/sheet_presentation_pattern.h:886-887](d:\Code\arkui_ace_engine_2_4\frameworks\core\components_ng\pattern\overlay\sheet_presentation_pattern.h:886-887)

```cpp
void DumpAdvanceInfo() override;
void DumpAdvanceInfo(std::unique_ptr<JsonValue>& json) override;
```

**使用方式**：

```bash
# 获取组件树 dump
hdc shell "dumpsys Ace container"

# 获取特定节点信息
hdc shell "dumpsys Ace hierarchy | grep -A 50 'SheetPresentation'"
```

**输出示例**：

```
SheetPresentation:
  sheetType: SHEET_BOTTOM
  height: 500.0
  width: 1080.0
  currentOffset: 0.0
  detentsIndex: 1
  isDragging: false
  animationProcess: false
```

### 3. 常见问题调试

#### 问题 1：半模态不显示

**排查步骤**：

1. 检查 `showInPage` 设置
   ```typescript
   // 确保不是 false
   .bindSheet(this.showSheet, content, {
     showInPage: false  // true 时不显示遮罩
   })
   ```

2. 检查父容器高度
   ```typescript
   // 父容器必须有明确高度
   Column() { /* ... */ }
     .width('100%')
     .height('100%')  // 必须设置
   ```

3. 检查 OverlayManager 是否创建
   ```cpp
   // 在 C++ 中添加日志
   auto overlayManager = SheetManager::GetInstance().FindPageNodeOverlay(...);
   TAG_LOGI(AceLogTag::ACE_SHEET, "OverlayManager: %{public}p", overlayManager.Get());
   ```

#### 问题 2：拖拽不响应

**排查步骤**：

1. 检查 `interactive` 设置
   ```typescript
   .bindSheet(this.showSheet, content, {
     interactive: true  // 必须为 true
   })
   ```

2. 检查是否嵌套在可滚动组件中
   ```typescript
   // 如果内部有 Scroll，需要处理嵌套滚动
   Column() {
     Scroll() {
       // ...
     }
     .onScroll((event) => {
       // 确保滚动事件正确传递
     })
   }
   ```

3. 检查 `enableDragControl`
   ```cpp
   // 在 C++ 中检查
   bool enable = pattern->GetEnableDragControl();
   TAG_LOGI(AceLogTag::ACE_SHEET, "Enable Drag: %{public}d", enable);
   ```

#### 问题 3：键盘避让不生效

**排查步骤**：

1. 检查 `avoidMode` 设置
   ```typescript
   .bindSheet(this.showSheet, content, {
     avoidMode: SheetKeyboardAvoidMode.TRANSLATE_AND_SCROLL
   })
   ```

2. 检查键盘事件监听
   ```cpp
   // 检查窗口尺寸变化事件
   void SheetPresentationPattern::OnWindowSizeChanged(
       int32_t width, int32_t height, WindowSizeChangeReason type) {
       TAG_LOGI(AceLogTag::ACE_SHEET, "Window size: %{public}d x %{public}d", width, height);
   }
   ```

3. 检查是否需要双次避让
   ```cpp
   bool needDouble = pattern->GetNeedDoubleAvoidAfterLayout();
   TAG_LOGI(AceLogTag::ACE_SHEET, "Need double avoid: %{public}d", needDouble);
   ```

#### 问题 4：动画卡顿

**排查步骤**：

1. 检查动画进程标志
   ```cpp
   bool isAnimating = pattern->GetAnimationProcess();
   TAG_LOGI(AceLogTag::ACE_SHEET, "Is animating: %{public}d", isAnimating);
   ```

2. 检查弹簧参数
   ```cpp
   auto curve = sheetObject_->GetSheetTransitionCurve(dragVelocity);
   TAG_LOGI(AceLogTag::ACE_SHEET, "Curve stiffness: %{public}f", curve->GetStiffness());
   ```

3. 检查是否在折叠屏上
   ```cpp
   pattern->InitFoldState();
   bool isFoldChanged = pattern->IsFoldStatusChanged();
   TAG_LOGI(AceLogTag::ACE_SHEET, "Fold status changed: %{public}d", isFoldChanged);
   ```

### 4. 性能分析

#### 测量布局时间

```cpp
auto start = std::chrono::high_resolution_clock::now();

// 执行布局
OnDirtyLayoutWrapperSwap(dirty, config);

auto end = std::chrono::high_resolution_clock::now();
auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
TAG_LOGI(AceLogTag::ACE_SHEET, "Layout time: %{public}lld μs", duration.count());
```

#### 测量动画帧率

```bash
# 启用性能监控
hdc shell "hdc shell param set persist.ace.perf.enable 1"

# 查看 FPS
hdc shell "dumpsys SurfaceFlinger | grep fps"
```

### 5. 单元测试

#### 测试文件位置

```
test/unittest/core/pattern/overlay/
├── sheet_presentation_test_one_ng.cpp
├── sheet_presentation_test_two_ng.cpp
├── sheet_presentation_test_five_ng.cpp
├── sheet_others_test_ng.cpp
└── sheet_popup_test_ng.cpp
```

#### 运行测试

```bash
# 编译测试
./build.sh --product-name rk3568 --build-target unittest

# 运行 Sheet 测试
./out/rk3568/tests/ace_engine/unittest/core/pattern/overlay/sheet_presentation_test_one_ng

# 使用 gtest_filter 运行特定测试
./out/rk3568/tests/ace_engine/unittest/core/pattern/overlay/sheet_presentation_test_one_ng \
  --gtest_filter="SheetPresentationTest.OnModifyDone"
```

---

## 常见问题

### Q1: 半模态和 Dialog、Popup 有什么区别？

| 特性 | Sheet | Dialog | Popup |
|-----|-------|--------|-------|
| **展示位置** | 底部/侧边/居中 | 居中 | 任意位置 |
| **交互方式** | 拖拽、滚动 | 点击 | 点击 |
| **遮罩** | 可配置 | 固有 | 可配置 |
| **键盘避让** | 完善 | 一般 | 无 |
| **档位高度** | 支持 | 不支持 | 不支持 |
| **适用场景** | 表单、菜单、内容预览 | 确认对话框 | 气泡提示 |

**推荐使用 Sheet 的场景**：
- 需要用户输入大量内容的表单
- 需要多档位高度切换的内容
- 需要拖拽交互的场景
- 需要键盘避让的输入场景

### Q2: 如何自定义半模态样式？

**标题区域**：

```typescript
@Builder
CustomTitle() {
  Row() {
    Image($r('app.media.icon'))
      .width(24)
      .height(24)

    Text('自定义标题')
      .fontSize(18)
      .margin({ left: 10 })
  }
  .padding(16)
  .width('100%')
}

.bindSheet(this.showSheet, content, {
  titleBuilder: this.CustomTitle()
})
```

**拖拽条样式**：

```typescript
.bindSheet(this.showSheet, content, {
  showDragBar: true,
  enableFloatingDragBar: true  // 浮动拖拽条
})
```

**圆角和阴影**：

```typescript
.bindSheet(this.showSheet, content, {
  borderRadius: 16,
  shadow: {
    radius: 10,
    color: '#33000000',
    offsetX: 0,
    offsetY: 2
  }
})
```

### Q3: 如何实现半模态与页面内容的联动？

**方式 1：使用双向绑定**

```typescript
@Entry
@Component
struct LinkedSheetExample {
  @State showSheet: boolean = false;
  @State selectedItem: string = '';

  build() {
    Column() {
      List() {
        ForEach(['Item 1', 'Item 2', 'Item 3'], (item: string) => {
          ListItem() {
            Text(item)
              .onClick(() => {
                this.selectedItem = item;
                this.showSheet = true;
              })
          }
        })
      }

      // 半模态中显示选中项
      .bindSheet(this.showSheet, this.SheetContent())
    }
  }

  @Builder
  SheetContent() {
    Text(`选中: ${this.selectedItem}`)
  }
}
```

**方式 2：使用回调**

```typescript
.bindSheet(this.showSheet, content, {
  onHeightDidChange: (height) => {
    // 根据高度调整页面内容
    this.pageContentHeight = 1000 - height;
  }
})
```

### Q4: 如何在横屏时使用侧边半模态？

**自动切换**：

```typescript
.bindSheet(this.showSheet, content, {
  type: SheetType.AUTO  // 自动选择（根据屏幕方向）
})
```

**手动指定**：

```typescript
.bindSheet(this.showSheet, content, {
  type: SheetType.SIDE,
  width: 400
})
```

**判断屏幕方向**：

```typescript
@Entry
@Component
struct OrientationSheetExample {
  @State orientation: string = 'portrait';

  build() {
    Column() {
      Button('显示半模态')
        .onClick(() => {
          this.showSheet = true;
        })
    }
    .bindSheet(this.showSheet, content, {
      type: this.orientation === 'landscape' ? SheetType.SIDE : SheetType.BOTTOM
    )
    .onAreaChange((oldValue, newValue) => {
      if (oldValue.width !== newValue.width) {
        this.orientation = newValue.width > newValue.height ? 'landscape' : 'portrait';
      }
    })
  }
}
```

### Q5: 如何阻止半模态关闭？

**使用 shouldDismiss 回调**：

```typescript
.bindSheet(this.showSheet, content, {
  shouldDismiss: () => {
    // 检查是否有未保存的内容
    if (this.hasUnsavedChanges) {
      // 显示确认对话框
      this.showConfirmDialog = true;
      return false;  // 阻止关闭
    }
    return true;  // 允许关闭
  }
})
```

**使用 onWillDismiss 回调**：

```typescript
.bindSheet(this.showSheet, content, {
  onWillDismiss: (reason) => {
    // reason: 0=返回键, 1=点击外部, 2=关闭按钮, 3=下拉, 4=拖拽
    if (reason === 1) {  // 点击外部
      // 阻止关闭
      this.showSheet = true;
    }
  }
})
```

### Q6: 如何实现半模态之间的切换？

**方式 1：关闭一个再打开另一个**

```typescript
@State showSheet1: boolean = false;
@State showSheet2: boolean = false;

Button('切换到半模态 2')
  .onClick(() => {
    this.showSheet1 = false;
    setTimeout(() => {
      this.showSheet2 = true;
    }, 100);
  })
```

**方式 2：使用类型切换**

```typescript
@State sheetType: SheetType = SheetType.BOTTOM;

.bindSheet(this.showSheet, content, {
  type: this.sheetType,
  onTypeDidChange: (type) => {
    this.sheetType = type;
  }
})
```

### Q7: 如何处理多次点击导致的动画问题？

**使用动画进程标志**：

```typescript
.bindSheet(this.showSheet, content, {
  onWillAppear: () => {
    // 防止重复点击
    if (!this.isAnimating) {
      this.isAnimating = true;
    }
  },
  onAppear: () => {
    this.isAnimating = false;
  }
})
```

**在 C++ 中检查**：

```cpp
bool SheetPresentationPattern::GetAnimationProcess() {
    return isAnimationProcess_;
}

void SheetPresentationPattern::SetAnimationProcess(bool isProcess) {
    isAnimationProcess_ = isProcess;
}

// 在动画开始前检查
if (!pattern->GetAnimationProcess()) {
    pattern->SetAnimationProcess(true);
    // 执行动画
}
```

### Q8: 如何在折叠屏上优化半模态？

**检测折叠状态**：

```cpp
pattern->InitFoldState();
bool isFoldChanged = pattern->IsFoldStatusChanged();

if (isFoldChanged) {
    // 重新计算布局
    pattern->AvoidSafeArea();
    pattern->UpdateSheetType();
}
```

**监听折叠状态变化**：

```typescript
.bindSheet(this.showSheet, content, {
  onAppear: () => {
    // 注册折叠状态监听
  }
})
```

**特殊处理折叠屏缝隙**：

```cpp
void SheetPresentationPattern::InitFoldCreaseRegion() {
    auto container = Container::Current();
    CHECK_NULL_VOID(container);

    if (container->IsFoldable()) {
        // 获取折叠屏缝隙区域
        auto foldCreaseRegions = container->GetFoldCreaseRegions();
        currentFoldCreaseRegion_ = foldCreaseRegions;

        // 避让折叠屏缝隙
        AvoidFoldCrease();
    }
}
```

---

## 附录

### A. 关键常量

**位置**: [overlay/sheet_presentation_pattern.cpp:66-89](d:\Code\arkui_ace_engine_2_4\frameworks\core\components_ng\pattern\overlay\sheet_presentation_pattern.cpp:66-89)

```cpp
// 档位常量
constexpr int32_t SHEET_DETENTS_ZERO = 0;
constexpr int32_t SHEET_DETENTS_ONE = 1;
constexpr int32_t SHEET_DETENTS_TWO = 2;
constexpr int32_t SHEET_DETENTS_THREE = 3;

// Alpha 值
constexpr float SHEET_VISIABLE_ALPHA = 1.0f;
constexpr float SHEET_INVISIABLE_ALPHA = 0.0f;

// 动画时长
constexpr int32_t SHEET_ENTRY_ANIMATION_DURATION = 250;  // 进入动画 250ms
constexpr int32_t SHEET_EXIT_ANIMATION_DURATION = 100;   // 退出动画 100ms

// 不可见偏移
constexpr float SHEET_INVISIABLE_OFFSET = 8.0f;

// 底部样式比例
constexpr float BOTTOM_STYLE_RATIO = 1.25f;

// 半高度比例
constexpr int32_t SHEET_HALF_HEIGHT = 2;
```

### B. 弹簧曲线参数

**位置**: [overlay/sheet_style.h:39-45](d:\Code\arkui_ace_engine_2_4\frameworks\core\components_ng\pattern\overlay\sheet_style.h:39-45)

```cpp
// 物理参数
constexpr float CURVE_MASS = 1.0f;        // 质量
constexpr float CURVE_STIFFNESS = 328.0f;  // 刚度
constexpr float CURVE_DAMPING = 36.0f;     // 阻尼

// 高度比例
constexpr float MEDIUM_SIZE = 0.6f;        // 中等高度 60%
constexpr float MEDIUM_SIZE_PRE = 0.5f;    // 中等高度 50%（旧版）

// 动画时长
constexpr int32_t SHEET_ANIMATION_DURATION = 580;  // 拖拽动画 580ms
```

### C. 关闭原因枚举

**位置**: [overlay/sheet_presentation_pattern.h:45-51](d:\Code\arkui_ace_engine_2_4\frameworks\core\components_ng\pattern\overlay\sheet_presentation_pattern.h:45-51)

```cpp
enum class BindSheetDismissReason {
    BACK_PRESSED = 0,      // 返回键
    TOUCH_OUTSIDE,         // 点击外部
    CLOSE_BUTTON,          // 关闭按钮
    SLIDE_DOWN,            // 下拉
    SLIDE,                 // 拖拽
};
```

### D. 性能优化建议

1. **减少不必要的布局计算**
   ```cpp
   // 只在必要时标记脏节点
   if (IsNeedChangeScrollHeight(height)) {
       host->MarkDirtyNode(PROPERTY_PATTERN_LAYOUT_ALGORITHM);
   }
   ```

2. **使用脏标记避免重复动画**
   ```cpp
   if (!pattern->GetAnimationProcess()) {
       pattern->SheetTransition(true);
   }
   ```

3. **延迟加载复杂内容**
   ```typescript
   @Builder
   LazyContent() {
     if (this.showSheet) {
       // 只在显示时加载
       ComplexComponent()
     }
   }
   ```

4. **优化滚动性能**
   ```cpp
   // 使用缓存避免重复计算
   float cachedHeight = pattern->GetScrollHeightNoProcess();
   if (!NearEqual(cachedHeight, newHeight)) {
       pattern->SetScrollHeight(newHeight);
   }
   ```

### E. 参考资料

- **OpenHarmony 文档**: [Sheet Panel 官方文档](https://developer.huawei.com/consumer/cn/doc/harmonyos-references-V5/ts-container-sheet-V5)
- **ACE Engine 架构**: [CLAUDE.md](../../CLAUDE.md)
- **NG 组件开发指南**: [如何新增一个组件.md](../../如何新增一个组件.md)

---

**文档维护**：本文档应随代码更新及时维护，如有问题或建议，请联系 ACE Engine 团队。

**最后更新**: 2026-02-05
**文档版本**: v1.0
