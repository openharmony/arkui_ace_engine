# OpenHarmony ArkUI 焦点系统知识库

本文档为 Claude Code (claude.ai/code) 提供指导，用于处理 OpenHarmony ArkUI 的焦点系统代码。

## 概述

**ArkUI 焦点系统**是 OpenHarmony UI 框架中负责管理用户界面焦点交互的核心子系统，处理键盘、遥控器、触摸等多种输入方式的焦点导航和事件分发。

**核心职责**：
- 焦点链管理和维护
- 焦点导航（方向键、Tab键、数字键盘等）
- 焦点事件处理和分发
- 焦点样式渲染
- 辅助功能支持

**关键特性**：
- 支持树形焦点链结构
- 支持焦点组和焦点作用域
- 可定制的焦点样式
- 焦点优先级控制
- 无障碍访问支持

## 代码位置

### 核心代码

```
arkui_ace_engine/frameworks/core/components_ng/
├── event/                        # 焦点事件层
│   ├── focus_hub.h/cpp           # 焦点枢纽（核心）
│   ├── focus_event_handler.h/cpp # 焦点事件处理器
│   ├── focus_box.h/cpp           # 焦点框样式
│   ├── focus_state.h             # 焦点状态定义
│   └── focus_type.h              # 焦点类型定义
├── manager/focus/                # 焦点管理层
│   ├── focus_manager.h/cpp       # 焦点管理器
│   └── focus_view.h/cpp          # 焦点视图
└── render/adapter/               # 焦点渲染层
    ├── focus_modifier.h/cpp      # 焦点渲染修饰器
    ├── focus_state_modifier.h/cpp
    └── focus_animation_modifier.h/cpp
```

### 辅助功能支持

```
arkui_ace_engine/adapter/ohos/osal/accessibility/focus_move/
├── accessibility_focus_strategy.cpp/h       # 焦点移动策略
├── accessibility_focus_move_osal.cpp/h       # 焦点移动 OSAL
├── accessibility_focus_frame_node_utils.cpp/h # FrameNode 工具
└── accessibility_third_node_utils.cpp/h      # 第三方节点工具
```

### 桥接层

```
arkui_ace_engine/frameworks/bridge/declarative_frontend/engine/functions/
└── js_focus_function.cpp/h  # JS 焦点函数接口
```

## 架构设计

### 三层架构

```
应用层 (ArkTS/JS)
    - focusOnTouch, defaultFocus, tabIndex
    - onFocus, onBlur, onKey
    ↓
桥接层 (Bridge)
    - JSFocusFunction
    - ArkTS Native Interface
    ↓
焦点管理层 (Manager)
    - FocusManager: 全局焦点管理
    - FocusView: 视图容器管理
    ↓
焦点事件层 (Event/Hub)
    - FocusHub: 核心枢纽
    - FocusEventHandler: 事件处理
    ↓
焦点渲染层 (Render)
    - FocusModifier: 绘制焦点框
    - FocusAnimationModifier: 焦点动画
```

### 核心类关系

```
                    FocusManager
                   (全局管理器)
                         │
                         │ 管理
                   FocusView
                  (视图容器)
                         │
                         │ 包含
                    FocusHub
                  (焦点枢纽)
              ┌───────────────┼───────────────┐
              │               │               │
        FocusBox     FocusPattern  FocusEventHandler
       (焦点框样式)   (焦点模式)    (事件处理)
```

## 核心类详解

### 1. FocusManager (焦点管理器)

**文件**: `frameworks/core/components_ng/manager/focus/focus_manager.h`

**职责**:
- 全局焦点状态管理
- FocusView 栈管理
- 焦点切换协调

**关键方法**:

```cpp
class FocusManager {
    // FocusView 栈管理
    void FocusViewShow(const RefPtr<FocusView>& focusView, bool isTriggerByStep = false);
    void FocusViewHide(const RefPtr<FocusView>& focusView);
    void FocusViewClose(const RefPtr<FocusView>& focusView, bool isDetachFromTree = false);

    // 焦点请求
    bool RequestFocus(const RefPtr<FocusHub>& focusHub, FocusReason reason);

    // 焦点变更回调
    void AddFocusChangeCallback(const FocusChangeCallback& callback);

private:
    FocusViewMap focusViewMap_;              // FocusView 映射表
    WeakPtr<FocusView> lastFocusView_;       // 上一个聚焦的视图
};
```

**关键枚举**:

```cpp
enum class FocusActiveReason : int32_t {
    POINTER_EVENT = 0,   // 指针事件
    DEFAULT = 1,         // 默认焦点
    USE_API = 2,         // API 调用
    KEY_TAB = 3,         // Tab 键
    ACTIVE_MARK = 4,     // 激活标记
    JOYSTICK_DPAD = 5,   // 摇杆/方向键
};

enum class FocusViewStackState : int32_t {
    IDLE = 0,    // 空闲
    SHOW = 1,    // 显示
    CLOSE = 2,   // 关闭
};
```

### 2. FocusView (焦点视图)

**文件**: `frameworks/core/components_ng/manager/focus/focus_view.h`

**职责**:
- 表示可聚焦的视图容器（Window、Dialog、Overlay）
- 管理视图内的焦点子树
- 处理视图级别的焦点显示/隐藏

**关键方法**:

```cpp
class FocusView {
    // 视图生命周期
    void FocusViewShow(bool isTriggerByStep = false);
    void FocusViewHide();
    void FocusViewClose(bool isDetachFromTree = false);

    // 默认焦点处理
    bool RequestDefaultFocus();
    bool TriggerFocusMove();

    // 焦点状态查询
    RefPtr<FocusHub> GetFocusHub();
    RefPtr<FocusHub> GetViewRootScope();
    bool IsRootScopeCurrentFocus();

private:
    bool isViewRootScopeFocused_ = true;  // 视图根作用域是否聚焦
    bool isViewHasFocused_ = false;       // 视图是否曾经聚焦
    bool isViewHasShow_ = false;          // 视图是否已显示
    WeakPtr<FocusHub> rootScopeSpecified_; // 指定的根作用域
};
```

### 3. FocusHub (焦点枢纽)

**文件**: `frameworks/core/components_ng/event/focus_hub.h`

**职责**:
- 焦点系统的核心枢纽
- 管理单个节点的焦点状态
- 协调子节点的焦点管理
- 处理焦点事件和回调

**核心数据结构**:

```cpp
class FocusHub : public FocusState, public FocusEventHandler {
public:
    // 焦点属性设置
    void SetFocusable(bool focusable);
    void SetFocusType(FocusType focusType);
    void SetFocusPattern(const FocusPattern& pattern);

    // 焦点状态查询
    bool IsFocusable() const;
    bool IsFocused() const;
    bool IsCurrentFocus() const;

    // 焦点请求
    bool RequestFocusImmediately(FocusReason reason);
    bool RequestFocus(FocusReason reason);

    // 子节点管理
    void AddChild(const RefPtr<FocusHub>& child);
    void RemoveChild(const RefPtr<FocusHub>& child);

    // 焦点样式
    void SetFocusBox(const FocusBox& focusBox);
    std::optional<FocusBox> GetFocusBox() const;

private:
    // 焦点链
    std::list<WeakPtr<FocusHub>> children_;
    WeakPtr<FocusHub> parent_;

    // 焦点属性
    FocusPattern focusPattern_;
    std::optional<FocusBox> focusBox_;

    // 焦点状态
    bool isFocused_ = false;
    bool isCurrentFocus_ = false;
};
```

**关键枚举**:

```cpp
enum class RequestFocusResult : int32_t {
    DEFAULT = 0,
    NON_FOCUSABLE = 1,        // 不可聚焦
    NON_FOCUSABLE_ANCESTOR = 2, // 祖先节点不可聚焦
    NON_EXIST = 3,            // 节点不存在
    NON_FOCUSABLE_BY_TAB = 4, // Tab 键不可聚焦
};

enum class SwitchingStartReason : int32_t {
    DEFAULT = 0,
    WINDOW_FOCUS = 1,
    REQUEST_FOCUS = 2,
    LOST_FOCUS_TO_VIEW_ROOT = 3,
    REMOVE_SELF = 4,
    REMOVE_CHILD = 5,
    LOST_FOCUS_TO_TABSTOP = 6,
};

enum class FocusDependence : int32_t {
    CHILD = 0,   // 子节点聚焦
    SELF = 1,    // 自身聚焦
    AUTO = 2,    // 自动选择
};

enum class FocusPriority : int32_t {
    AUTO = 0,
    PRIOR = 2000,
    PREVIOUS = 3000,
};
```

### 4. FocusPattern (焦点模式)

**文件**: `frameworks/core/components_ng/event/focus_hub.h`

**职责**:
- 定义节点的焦点行为模式
- 控制焦点样式类型
- 配置焦点绘制参数

```cpp
class FocusPattern {
public:
    FocusPattern(FocusType focusType, bool focusable);
    FocusPattern(FocusType focusType, bool focusable, FocusStyleType styleType);

    FocusType GetFocusType() const;
    bool GetFocusable() const;
    FocusStyleType GetStyleType() const;
    FocusPaintParam* GetFocusPaintParams() const;

private:
    FocusType focusType_;          // 焦点类型
    bool focusable_;               // 是否可聚焦
    FocusStyleType styleType_;     // 样式类型
    std::unique_ptr<FocusPaintParam> paintParams_; // 绘制参数
};
```

### 5. FocusBox (焦点框)

**文件**: `frameworks/core/components_ng/event/focus_box.h`

**职责**:
- 定义焦点框的视觉样式
- 支持资源动态更新

```cpp
struct FocusBoxStyle {
    std::optional<Color> strokeColor;   // 边框颜色
    std::optional<CalcDimension> strokeWidth; // 边框宽度
    std::optional<CalcDimension> margin;      // 外边距
};

class FocusBox {
public:
    void SetStyle(const FocusBoxStyle& style);
    std::optional<FocusBoxStyle> GetStyle() const;
    bool HasCustomStyle() const;
};
```

### 6. FocusEventHandler (焦点事件处理器)

**文件**: `frameworks/core/components_ng/event/focus_event_handler.h`

**职责**:
- 处理键盘和方向键事件
- 处理焦点导航逻辑
- 分发焦点相关回调

```cpp
class FocusEventHandler : public FocusState {
public:
    // 焦点事件回调设置
    void SetOnFocusCallback(OnFocusFunc callback);
    void SetOnBlurCallback(OnBlurFunc callback);
    void SetOnKeyCallback(OnKeyConsumeFunc callback);

protected:
    virtual bool HandleFocusTravel(const FocusEvent& event) = 0;
    bool OnFocusEvent(const FocusEvent& event);
};

struct FocusCallbackEvents {
    OnFocusFunc onFocusCallback_;
    OnBlurFunc onBlurCallback_;
    OnKeyConsumeFunc onKeyEventCallback_;
    OnKeyConsumeFunc onKeyPreImeCallback_;
    int32_t tabIndex_ = 0;
    bool isDefaultFocus_ = false;
    bool isDefaultGroupFocus_ = false;
    std::optional<bool> isFocusOnTouch_;
};
```

## 焦点类型系统

### FocusType (焦点类型)

**文件**: `frameworks/core/components_ng/event/focus_type.h`

```cpp
enum class FocusType : int32_t {
    DISABLE = 0,  // 禁用焦点
    NODE = 1,     // 聚焦节点（叶子节点）
    SCOPE = 2,    // 聚焦作用域（容器节点）
};
```

**类型说明**:
- **DISABLE**: 节点不参与焦点系统
- **NODE**: 可聚焦的终端节点（Button、TextInput 等）
- **SCOPE**: 焦点容器节点（Row、Column、Grid 等）

### FocusStyleType (焦点样式类型)

```cpp
enum class FocusStyleType : int32_t {
    NONE = -1,           // 无样式
    INNER_BORDER = 0,    // 内边框
    OUTER_BORDER = 1,    // 外边框
    CUSTOM_BORDER = 2,   // 自定义边框
    CUSTOM_REGION = 3,   // 自定义区域
    FORCE_BORDER = 4,    // 强制边框
    FORCE_NONE = 5,      // 强制无边框
};
```

### FocusStep (焦点移动方向)

```cpp
enum class FocusStep : int32_t {
    NONE = 0x0,
    LEFT = 0x1,       // 向左
    UP = 0x2,         // 向上
    RIGHT = 0x11,     // 向右
    DOWN = 0x12,      // 向下
    LEFT_END = 0x3,   // 向左到边界
    UP_END = 0x4,     // 向上到边界
    RIGHT_END = 0x13,  // 向右到边界
    DOWN_END = 0x14,  // 向下到边界
    SHIFT_TAB = 0x5,  // Shift+Tab（前一个）
    TAB = 0x15,        // Tab（下一个）
};
```

### FocusIntension (焦点意图)

```cpp
enum class FocusIntension : int32_t {
    NONE = 0,
    LEFT, UP, RIGHT, DOWN,  // 方向键
    TAB, SHIFT_TAB,          // Tab 键
    HOME, END,               // Home/End 键
    SELECT, SPACE, ESC,      // 其他按键
};
```

## 焦点导航流程

### 方向键导航

```
用户按下方向键
    ↓
KeyEvent 分发到 FocusHub
    ↓
FocusEventHandler.OnKeyEvent()
    ↓
解析 FocusIntension (LEFT/UP/RIGHT/DOWN)
    ↓
HandleFocusTravel()
    ↓
根据 FocusStep 查找下一个可聚焦节点
    ↓
FocusManager.RequestFocus(newFocusHub)
    ↓
焦点切换成功
```

**算法关键点**:

1. **当前节点判断**: 检查当前焦点节点类型（NODE/SCOPE）
2. **子节点遍历**: SCOPE 类型遍历子节点查找候选
3. **父节点委托**: 无法处理时向上委托给父级 SCOPE
4. **候选评估**: 基于几何位置、Tab 顺序评估候选

### Tab 键导航

```
用户按下 Tab/Shift+Tab
    ↓
KeyEvent 分发到 FocusHub
    ↓
解析为 FocusStep::TAB 或 SHIFT_TAB
    ↓
按 tabIndex 顺序查找下一个节点
    ↓
请求焦点到目标节点
    ↓
更新焦点状态
```

**Tab 顺序规则**:
1. 优先按 `tabIndex` 升序排列
2. 相同 `tabIndex` 按文档顺序
3. `tabIndex < 0` 不参与 Tab 导航

### 默认焦点

```
FocusView 显示
    ↓
RequestDefaultFocus()
    ↓
查找 defaultFocus=true 的节点
    ↓
查找 tabIndex 最小的节点
    ↓
请求焦点到默认节点
    ↓
焦点成功设置
```

**默认焦点优先级**:
1. `defaultFocus=true` 且 `isGroupDefault=true` 的节点
2. `defaultFocus=true` 的节点
3. `tabIndex` 最小的可聚焦节点

## 焦点样式渲染

### FocusModifier (焦点修饰器)

**文件**: `frameworks/core/components_ng/render/adapter/focus_modifier.h`

```cpp
class FocusModifier {
public:
    void SetRoundRect(const RoundRect& rect, float borderWidth);
    void SetPaintColor(const Color& paintColor);
    void SetFrameNode(const RefPtr<FrameNode>& frameNode);

private:
    RSRoundRect roundRect_;     // Rosen 圆角矩形
    Color paintColor_;           // 绘制颜色
    float paintWidthPx_;         // 边框宽度
    std::shared_ptr<RectF> overlayRect_; // 覆盖区域
};
```

### 焦点样式配置

**应用层 (ArkTS)**:
```typescript
Button('Click me')
  .focusOnTouch(true)
  .defaultFocus(false)
  .tabIndex(1)
  .onFocus(() => {
    console.log('focused')
  })
```

**C++ 层**:
```cpp
// 设置焦点模式
FocusPattern pattern(FocusType::NODE, true, FocusStyleType::INNER_BORDER);
focusHub->SetFocusPattern(pattern);

// 设置焦点框样式
FocusBoxStyle boxStyle;
boxStyle.strokeColor = Color::BLUE;
boxStyle.strokeWidth = 2.0_vp;
FocusBox focusBox;
focusBox.SetStyle(boxStyle);
focusHub->SetFocusBox(focusBox);
```

## API 映射

### ArkTS 层到 C++ 层映射

| ArkTS 属性 | C++ 属性 | 设置方法 |
|------------|---------|---------|
| `focusOnTouch` | FocusPattern::focusOnTouch | `SetFocusOnTouch()` |
| `defaultFocus` | FocusPattern::defaultFocus | `SetDefaultFocus()` |
| `tabIndex` | FocusPattern::tabIndex | `SetTabIndex()` |
| `groupDefaultFocus` | FocusPattern::isGroupDefault | `SetIsGroupDefault()` |
| `onFocus` | FocusCallbackEvents::onFocusCallback_ | `SetOnFocusCallback()` |
| `onBlur` | FocusCallbackEvents::onBlurCallback_ | `SetOnBlurCallback()` |
| `onKey` | FocusCallbackEvents::onKeyEventCallback_ | `SetOnKeyCallback()` |

### 桥接代码示例

**文件**: `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.cpp`

```cpp
// 设置 focusOnTouch
ArkUINativeModuleValue SetFocusOnTouch(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);  // Node
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1); // Value

    auto node = nodePtr(firstArg->ToNativePointer(vm)->Value());
    bool focusOnTouch = secondArg->ToBoolean(vm)->Value();

    auto frameNode = GetFrameNodeByNode(node);
    auto focusHub = frameNode->GetFocusHub();
    focusHub->SetFocusOnTouch(focusOnTouch);

    return panda::JSValueRef::Undefined(vm);
}
```

## 常见问题排查

### 1. 焦点无法移动

**检查清单**:
- [ ] 节点 `focusable` 属性是否为 true
- [ ] 父节点是否为 SCOPE 类型
- [ ] 几何位置是否正确
- [ ] 是否有遮罩层阻挡

### 2. 焦点框不显示

**检查清单**:
- [ ] `FocusStyleType` 配置是否正确
- [ ] `FocusBox` 样式是否设置
- [ ] `FocusModifier` 是否正确应用
- [ ] 节点是否真正获得焦点

### 3. 默认焦点不生效

**检查清单**:
- [ ] `defaultFocus` 和 `tabIndex` 配置
- [ ] FocusView 是否已显示
- [ ] 节点是否可聚焦
- [ ] 焦点优先级是否冲突

## 最佳实践

### 1. 焦点设计原则

- **可预测性**: 焦点移动应符合用户直觉（左→右，上→下）
- **可见性**: 焦点框应清晰可见
- **一致性**: 相同类型组件焦点行为一致
- **效率**: 最小化焦点移动次数

### 2. 性能优化

- 避免过深焦点树嵌套（建议不超过 5 层）
- 合理使用 SCOPE 类型减少遍历范围
- 延迟加载复杂界面的焦点树
- 复用 FocusHub 实例

### 3. 无障碍支持

- 为所有可交互元素设置合适的 `tabIndex`
- 提供有意义的 `onFocus`/`onBlur` 回调
- 支持 keyboard navigation
- 为自定义组件实现焦点移动逻辑

## 搜索模式

```bash
# 查找焦点相关文件
find ace_engine -name "*focus*"

# 查找 FocusHub 使用
grep -r "GetFocusHub()" frameworks/core/components_ng

# 查找焦点事件处理
grep -r "OnKeyEvent\|OnFocus\|OnBlur" frameworks/core/components_ng

# 查找焦点样式
grep -r "FocusBox\|FocusPattern" frameworks/core/components_ng
```

## 参考资源

### 相关文件
| 文件 | 说明 |
|------|------|
| `focus_hub.h:45` | FocusHub 类定义 |
| `focus_manager.h:171` | FocusManager 类定义 |
| `focus_view.h:30` | FocusView 类定义 |
| `focus_type.h:23` | FocusType 枚举 |
| `focus_event_handler.h:125` | HandleFocusTravel 方法 |

---

**最后更新**: 2025-02-04
**适用版本**: OpenHarmony API 12+
