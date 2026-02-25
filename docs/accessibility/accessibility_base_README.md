# ArkUI Accessibility 无障碍支持知识库

> **文档版本**：v3.0
> **更新时间**：2026-02-04
> **源码版本**：OpenHarmony ace_engine
> **作者**：基于实际代码分析生成

---

## 概述

Accessibility（无障碍）模块是 ACE Engine 中的**桥接层**，负责将 ArkUI 应用的组件树信息暴露给系统无障碍服务（如屏幕阅读器），并接收来自无障碍服务的操作请求。

### 核心职责

| 职责 | 说明 |
|------|------|
| **信息暴露** | 将组件树属性、状态、位置信息封装为 `ArkUI_AccessibilityElementInfo` 提供给外部 |
| **操作桥接** | 接收无障碍服务操作请求，通过 `AccessibilityProvider` 接口分发给组件 |
| **事件通知** | 监听组件树变化，向无障碍服务发送 `ArkUI_AccessibilityEventInfo` 事件 |
| **属性提取** | 通过 JS Inspector 为 51 个组件提取定制化无障碍属性 |
| **焦点管理** | 实现无障碍焦点移动和搜索 |
| **悬停处理** | 处理辅助技术的悬停探测事件 |

### 架构层次

```
┌─────────────────────────────────────────────────────────┐
│  系统无障碍服务（屏幕阅读器、TalkBack 等）                │
└─────────────────────────────────────────────────────────┘
                    ↕ NDK 接口
┌─────────────────────────────────────────────────────────┐
│  OSAL 层（Platform Adapter）                             │
│  - JsAccessibilityManager                               │
│  - JsInteractionOperation                               │
│  - AccessibilityHoverManagerForThirdNG                  │
│  - AccessibilityFocusStrategy                           │
└─────────────────────────────────────────────────────────┘
                    ↕ 内部调用
┌─────────────────────────────────────────────────────────┐
│  Core 层（核心框架）                                      │
│  - AccessibilityProvider (接口)                         │
│  - AccessibilityNode (旧架构)                           │
│  - AccessibilityProperty (NG 架构)                      │
│  - AccessibilityManagerNG (悬停管理)                    │
│  - JS Inspector (属性提取)                              │
└─────────────────────────────────────────────────────────┘
                    ↕ 内部调用
┌─────────────────────────────────────────────────────────┐
│  Component 层（组件层）                                   │
│  - FrameNode/DOMNode (组件树)                           │
│  - Pattern 层无障碍属性                                  │
└─────────────────────────────────────────────────────────┘
```

---

## 目录结构

```
ace_engine/
├── frameworks/core/accessibility/            # 核心 accessibility 模块
│   ├── accessibility_provider.h             # 无障碍提供者抽象接口
│   ├── accessibility_session_adapter.h/cpp   # 会话适配器
│   ├── accessibility_node.h/cpp            # 无障碍节点（旧架构）
│   ├── accessibility_manager.h             # 旧架构管理器
│   ├── accessibility_manager_ng.h          # NG 架构管理器（悬停）
│   ├── accessibility_constants.h           # 常量定义
│   ├── accessibility_utils.h               # 工具函数和类型
│   ├── native_interface_accessibility_impl.h/cpp  # NDK 接口实现
│   ├── native_interface_accessibility_provider.h     # NDK 提供者接口
│   ├── third_accessibility_manager.h       # 第三方无障碍管理器
│   ├── utils/                              # 工具类
│   │   ├── accessibility_property_utils.h  # 属性工具
│   │   ├── accessibility_action_function_utils.h
│   │   ├── accessibility_rect_info_utils.h
│   │   └── accessibility_manager_utils.h
│   ├── node_utils/                         # 节点工具
│   │   └── accessibility_frame_node_utils.h
│   ├── static/                             # 静态工具
│   │   └── accessibility_static_utils.h
│   └── hidumper/                           # 调试工具
│       └── accessibility_hidumper.h
│
├── frameworks/core/components_ng/property/  # NG 属性层
│   ├── accessibility_property.h            # 无障碍属性基类
│   ├── accessibility_property.cpp          # 多线程实现
│   ├── accessibility_property_mutilthread.cpp
│   └── accessibility_property_function.h   # 属性函数
│
├── adapter/ohos/osal/                      # OSAL 适配层
│   ├── js_accessibility_manager.h          # JS 无障碍管理器（核心）
│   ├── js_accessibility_manager.cpp
│   ├── js_third_accessibility_hover_ng.h   # 第三方悬停管理
│   ├── js_third_accessibility_hover_ng.cpp
│   ├── js_third_provider_interaction_operation.cpp  # 第三方交互
│   └── accessibility/                      # 无障碍适配器
│       ├── accessibility_hidumper_osal.h/cpp       # HiDumper
│       ├── element_info/                   # 元素信息处理
│       │   ├── accessibility_node_osal.cpp
│       │   └── accessibility_element_info_osal.cpp
│       └── focus_move/                     # 焦点移动（8 个文件）
│           ├── accessibility_focus_strategy.h/cpp
│           ├── accessibility_focus_move_osal.h/cpp
│           ├── accessibility_focus_move_osal_ng.h/cpp
│           ├── accessibility_focus_move_osal_node.h/cpp
│           ├── accessibility_focus_move_osal_third.h/cpp
│           ├── accessibility_focus_accessibility_node_utils.h/cpp
│           ├── accessibility_focus_frame_node_utils.h/cpp
│           └── accessibility_focus_third_node_utils.h/cpp
│
└── frameworks/bridge/common/accessibility/ # Bridge 层
    └── accessibility_node_manager.h        # 节点管理器接口
```

### 代码规模统计

| 分类 | 数量 | 说明 |
|------|------|------|
| 核心头文件 | 12 | frameworks/core/accessibility/*.h |
| OSAL 适配器 | 20 | adapter/ohos/osal/accessibility/ |
| 焦点移动模块 | 16 | focus_move 相关文件 |
| 工具类 | 8 | 辅助工具函数 |
| 总文件数 | 100+ | 完整的无障碍模块 |

---

## 核心类

### 1. AccessibilityProvider

位置：`frameworks/core/accessibility/accessibility_provider.h:33-59`

无障碍提供者抽象接口，定义所有无障碍操作的标准 API。

```cpp
class AccessibilityProvider : public AceType {
public:
    // 节点查找
    virtual int32_t FindAccessibilityNodeInfosById(
        const int64_t elementId, const int32_t mode, const int32_t requestId,
        std::vector<ArkUI_AccessibilityElementInfo>& infos) = 0;
    virtual int32_t FindAccessibilityNodeInfosByText(...) = 0;
    virtual int32_t FindFocusedAccessibilityNode(...) = 0;
    virtual int32_t FindNextFocusAccessibilityNode(...) = 0;

    // 动作执行
    virtual int32_t ExecuteAccessibilityAction(...) = 0;

    // 焦点管理
    virtual int32_t ClearFocusedAccessibilityNode() = 0;
    virtual int32_t GetAccessibilityNodeCursorPosition(...) = 0;

    // 事件发送
    virtual int32_t SendAccessibilityAsyncEvent(...) = 0;

    // 第三方集成
    virtual void SendThirdAccessibilityProvider(...) {};
};
```

### 2. AccessibilitySessionAdapter

位置：`frameworks/core/accessibility/accessibility_session_adapter.h:30-49`

会话适配器，处理不同组件的无障碍会话。

```cpp
class AccessibilitySessionAdapter : public AceType {
public:
    // 悬停事件传输
    virtual void TransferHoverEvent(const PointF& point, SourceType source,
        AccessibilityHoverEventType eventType, TimeStamp time) { }

    // 配置方法
    virtual bool IgnoreHostNode() const { return false; };
    virtual bool IgnoreTransformMouseEvent() const { return false; };

    // 获取节点的会话适配器
    static RefPtr<AccessibilitySessionAdapter> GetSessionAdapter(const RefPtr<FrameNode>& node);
};
```

**实现类**：
- `AccessibilitySessionAdapterForm` - Form 组件适配器
- `AccessibilitySessionAdapterUIExtension` - UIExtension 适配器
- `AccessibilitySessionAdapterIsolatedComponent` - 隔离组件适配器
- `XComponentAccessibilitySessionAdapter` - XComponent 适配器

### 3. AccessibilityNode（旧架构）

位置：`frameworks/core/accessibility/accessibility_node.h:58-661`

传统的无障碍节点实现，基于 DOM 树结构。

**位域优化存储**：
```cpp
union {
    struct {
        bool isValidRect_ : 1;
        bool isChecked_ : 1;
        bool isEditable_ : 1;
        bool isEnabled_ : 1;
        bool accessible_ : 1;
        bool isFocused_ : 1;
        bool isSelected_ : 1;
        bool isCheckable_ : 1;
        bool isClickable_ : 1;
        bool isFocusable_ : 1;
        bool isScrollable_ : 1;
        bool isLongClickable_ : 1;
        bool isMultiLine_ : 1;
        bool isPassword_ : 1;
        bool visible_ : 1;
        bool shown_ : 1;
        bool isClicked_ : 1;
        bool isAccessibilityFocused_ : 1;
    };
    uint64_t bits_ = 0;
};
```

**动作类型定义**：
```cpp
using ActionClickImpl = std::function<void()>;
using ActionLongClickImpl = std::function<void()>;
using ActionSetTextImpl = std::function<void(const std::string&)>;
using ActionScrollForwardImpl = std::function<bool()>;
using ActionScrollBackwardImpl = std::function<bool()>;
using ActionFocusImpl = std::function<void()>;
using ActionUpdateIdsImpl = std::function<void()>;
using ActionAccessibilityFocusImpl = std::function<void(bool)>;
```

### 4. AccessibilityProperty（NG 架构）

位置：`frameworks/core/components_ng/property/accessibility_property.h:105-...`

NG 架构下的无障碍属性基类。

```cpp
class AccessibilityProperty : public virtual AceType {
public:
    virtual std::string GetText() const;
    virtual std::string GetGroupText(bool forceGetChildren = false) const;
    virtual bool IsCheckable() const;
    virtual bool IsChecked() const;
    virtual bool IsSelected() const;
    virtual bool IsPassword() const;
    virtual bool IsEditable() const;
    // ... 更多属性方法
};
```

### 5. JsAccessibilityManager

位置：`adapter/ohos/osal/js_accessibility_manager.h:122-939`

**核心管理器**，继承自 `AccessibilityNodeManager` 和 `AccessibilityHoverManagerForThirdNG`。

**主要职责**：
- 节点搜索与信息获取
- 动作执行
- 焦点移动管理
- 事件发送
- 第三方集成
- Web 无障碍支持

**关键方法**：
```cpp
class JsAccessibilityManager : public AccessibilityNodeManager,
    public AccessibilityHoverManagerForThirdNG {
public:
    // 初始化与回调
    void InitializeCallback() override;
    void SendAccessibilityAsyncEvent(...) override;

    // 节点搜索
    void SearchElementInfoByAccessibilityId(...) override;
    void SearchElementInfosByText(...) override;
    void SearchElementInfoByCustomIdNG(...) override;

    // 焦点管理
    void FindFocusedElementInfo(...) override;
    void FocusMoveSearch(...) override;
    void FocusMoveSearchNG(...) override;

    // 动作执行
    void ExecuteAction(...) override;
    bool ExecuteActionNG(...) override;

    // 事件处理
    bool SendAccessibilitySyncEvent(...);
    void SendCacheAccessibilityEvent(...);

    // 第三方支持
    void TransferThirdProviderHoverEvent(...) override;
    void RegisterJsThirdProviderInteractionOperation(...);

    // Web 支持
#ifdef WEB_SUPPORTED
    void SendWebAccessibilityAsyncEvent(...) override;
    void SearchWebElementInfoByAccessibilityId(...) override;
#endif
};
```

**内部交互操作类**：
- `JsInteractionOperation` - JS 交互操作实现
- `WebInteractionOperation` - Web 交互操作实现

### 6. AccessibilityManagerNG

位置：`frameworks/core/accessibility/accessibility_manager_ng.h:72-138`

**NG 架构悬停管理器**，专门处理悬停事件。

```cpp
class AccessibilityManagerNG final: public AceType {
public:
    // 悬停事件处理（多个重载）
    void HandleAccessibilityHoverEvent(const RefPtr<FrameNode>& root, const MouseEvent& event);
    void HandleAccessibilityHoverEvent(const RefPtr<FrameNode>& root, const TouchEvent& event);
    void HandleAccessibilityHoverEvent(const RefPtr<FrameNode>& root, float pointX, float pointY,
        int32_t sourceType, int32_t eventType, int64_t timeMs);

    // 按 Surface ID 处理
    HandleHoverRet HandleAccessibilityHoverEventBySurfaceId(
        const std::string& surfaceId, HandleHoverEventParam& param);

    // 坐标转换
    static bool ConvertPointFromAncestorToNode(...);

    // 调试
    void HoverTestDebug(const RefPtr<FrameNode>& root, const PointF& point,
        std::string& summary, std::string& detail) const;

private:
    AccessibilityHoverStateManager hoverStateManager_;
};
```

### 7. AccessibilityHoverManagerForThirdNG

位置：`adapter/ohos/osal/js_third_accessibility_hover_ng.h:63-126`

**第三方悬停管理器**，处理第三方辅助技术的悬停事件。

```cpp
class AccessibilityHoverManagerForThirdNG : public AceType {
public:
    void HandleAccessibilityHoverForThird(const AccessibilityHoverForThirdConfig& config);
    bool GetElementInfoForThird(...);
    bool ActThirdAccessibilityFocus(...);
    void RegisterJsThirdProviderInteractionOperation(...);
    bool ClearThirdAccessibilityFocus(...);
    bool OnDumpChildInfoForThirdRecursive(...);

private:
    AccessibilityHoverForThirdState hoverForThirdState_;
    std::unordered_map<int64_t, std::weak_ptr<JsThirdProviderInteractionOperation>>
        jsThirdProviderOperator_;
};
```

### 8. AccessibilityFocusStrategy

位置：`adapter/ohos/osal/accessibility/focus_move/accessibility_focus_strategy.h:121-...`

**焦点移动策略**，实现无障碍焦点搜索和移动算法。

```cpp
class AccessibilityFocusStrategy {
public:
    virtual bool CanAccessibilityFocus(...);
    virtual bool IsRootType(...);

    // 查找下一个可读节点
    AceFocusMoveResult FindNextReadableNode(...);

    // 查找上一个可读节点
    AceFocusMoveResult FindPrevReadableNode(...);

    // 查找最后节点
    AceFocusMoveResult FindLastNodeWithoutCheck(...);

    // 查找滚动祖先
    AceFocusMoveResult FindForwardScrollAncestor(...);
    AceFocusMoveResult FindBackwardScrollAncestor(...);

    // 边界检查
    std::shared_ptr<FocusRulesCheckNode> GetParentNodeStopByRootType(...);
};

// 焦点规则检查节点
class FocusRulesCheckNode : public Accessibility::ReadableRulesNode {
    virtual std::vector<std::shared_ptr<FocusRulesCheckNode>> GetAceChildren();
    virtual std::shared_ptr<FocusRulesCheckNode> GetAceParent();
    virtual bool IsAccessibiltyVisible();
    virtual bool IsChildTreeContainer();
    virtual bool IsEmbededTarget();
    // ... 更多检查方法
};
```

---

## 数据结构

### ArkUI_AccessibilityElementInfo

位置：`frameworks/core/accessibility/native_interface_accessibility_impl.h:30-...`

无障碍元素的核心数据结构，向 NDK 暴露元素信息。

#### 主要属性

| 属性 | 类型 | 说明 |
|------|------|------|
| `elementId` | int64_t | 元素唯一标识 |
| `parentId` | int64_t | 父元素 ID |
| `pageId` | int32_t | 页面 ID |
| `checkable` | bool | 可勾选 |
| `checked` | bool | 已勾选 |
| `focusable` | bool | 可聚焦 |
| `focused` | bool | 已聚焦 |
| `visible` | bool | 可见 |
| `accessibilityFocused` | bool | 无障碍焦点 |
| `selected` | bool | 已选择 |
| `clickable` | bool | 可点击 |
| `scrollable` | bool | 可滚动 |
| `editable` | bool | 可编辑 |

### ArkUI_AccessibilityEventInfo

位置：`frameworks/core/accessibility/native_interface_accessibility_impl.h:503-563`

| 属性 | 类型 | 说明 |
|------|------|------|
| `eventType` | ArkUI_AccessibilityEventType | 事件类型 |
| `pageId` | int32_t | 页面 ID |
| `requestFocusId` | int32_t | 请求聚焦的元素 ID |
| `elementInfo` | ArkUI_AccessibilityElementInfo* | 关联的元素信息 |
| `textAnnouncedForAccessibility` | std::string | 朗读的文本 |

### AccessibilityEvent

位置：`frameworks/core/accessibility/accessibility_manager.h:62-79`

```cpp
struct AccessibilityEvent {
    int64_t nodeId = 0;
    int64_t stackNodeId = -1;
    uint32_t windowId = 0;
    WindowsContentChangeTypes windowContentChangeTypes;
    WindowUpdateType windowChangeTypes;
    std::string eventType;
    std::string componentType;
    std::string beforeText;
    std::string latestContent;
    std::string textAnnouncedForAccessibility;
    double currentItemIndex = 0.0;
    double itemCount = 0.0;
    AccessibilityEventType type = AccessibilityEventType::UNKNOWN;
    int32_t startIndex = 0;
    int32_t endIndex = 0;
    std::map<std::string, std::string> extraEventInfo;
};
```

### 辅助结构

**AccessibilityHoverState** - 悬停状态（NG）
```cpp
struct AccessibilityHoverState {
    SourceType source = SourceType::NONE;
    std::vector<WeakPtr<FrameNode>> nodesHovering;
    TimeStamp time;
    bool idle = true;
    AccessibilityHoverEventType eventType = AccessibilityHoverEventType::MOVE;
    std::vector<WeakPtr<FrameNode>> nodeTransparent;
};
```

**AccessibilityHoverForThirdState** - 第三方悬停状态
```cpp
struct AccessibilityHoverForThirdState {
    SourceType source = SourceType::NONE;
    std::vector<int64_t> nodesHovering;
    TimeStamp time;
    bool idle = true;
    bool thirdOperationIdle = true;
};
```

**RotateTransform** - 旋转变换
```cpp
struct RotateTransform {
    int32_t rotateDegree = 0;
    int32_t centerX = 0;
    int32_t centerY = 0;
    int32_t innerCenterX = 0;
    int32_t innerCenterY = 0;
};
```

**AccessibilityParentRectInfo** - 父窗口矩形信息
```cpp
struct AccessibilityParentRectInfo {
    int32_t left = 0;
    int32_t top = 0;
    float scaleX = 1.0f;
    float scaleY = 1.0f;
    RotateTransform rotateTransform;
    bool isChanged = false;
};
```

---

## 常量和枚举

### 组件标签常量

位置：`frameworks/core/accessibility/accessibility_utils.h:29-66`

```cpp
extern const char ACCESSIBILITY_TAG_DIV[];
extern const char ACCESSIBILITY_TAG_TEXT[];
extern const char ACCESSIBILITY_TAG_BUTTON[];
extern const char ACCESSIBILITY_TAG_LIST[];
extern const char ACCESSIBILITY_TAG_INPUT[];
extern const char ACCESSIBILITY_TAG_IMAGE[];
extern const char ACCESSIBILITY_TAG_SLIDER[];
extern const char ACCESSIBILITY_TAG_SWITCH[];
extern const char ACCESSIBILITY_TAG_TABS[];
extern const char ACCESSIBILITY_TAG_VIDEO[];
extern const char ACCESSIBILITY_TAG_MARQUEE[];
// ... 共 30+ 个标签
```

### AccessibilityEventType

位置：`frameworks/core/accessibility/accessibility_utils.h:74-121`

```cpp
enum class AccessibilityEventType : size_t {
    // 基础交互事件
    CLICK = 0x00000001,
    LONG_PRESS = 0x00000002,
    SELECTED = 0x00000004,
    FOCUS = 0x00000008,

    // 内容变化事件
    TEXT_CHANGE = 0x00000010,
    CHANGE = 0x00000800,
    COMPONENT_CHANGE = 0x00000801,

    // 悬停事件
    HOVER_ENTER_EVENT = 0x0000080,
    HOVER_EXIT_EVENT = 0x0000100,

    // 触摸事件
    TOUCH_START = 0x00000200,
    TOUCH_MOVE = 0x00000201,
    TOUCH_END = 0x00000400,

    // 滚动事件
    SCROLL_START = 0x01000000,
    SCROLL_END = 0x00001000,

    // 焦点相关
    ACCESSIBILITY_FOCUSED = 0x00008000,
    ACCESSIBILITY_FOCUS_CLEARED = 0x00010000,

    // 语音播报
    ANNOUNCE_FOR_ACCESSIBILITY = 0x10000000,

    // 页面事件
    PAGE_CHANGE = 200,
    PAGE_OPEN = 0x20000000,
    PAGE_CLOSE = 0x08000000,

    // 键盘事件
    KEYBOARD_BACK = 150,
    KEYBOARD_UP = 151,
    KEYBOARD_DOWN = 152,
    // ... 更多
};
```

### AceAction

位置：`frameworks/core/accessibility/accessibility_utils.h:153-178`

```cpp
enum class AceAction : uint32_t {
    ACTION_NONE = 0,
    GLOBAL_ACTION_BACK = 1,
    CUSTOM_ACTION = 2,

    // 导航动作
    ACTION_FOCUS = 10,
    ACTION_CLEAR_FOCUS,
    ACTION_ACCESSIBILITY_FOCUS,
    ACTION_CLEAR_ACCESSIBILITY_FOCUS,

    // 交互动作
    ACTION_CLICK,
    ACTION_LONG_CLICK,

    // 滚动动作
    ACTION_SCROLL_FORWARD,
    ACTION_SCROLL_BACKWARD,

    // 文本操作
    ACTION_SET_TEXT,
    ACTION_COPY,
    ACTION_PASTE,
    ACTION_CUT,
    ACTION_SELECT,
    ACTION_SET_SELECTION,
    ACTION_SET_CURSOR_POSITION,

    // 其他
    ACTION_EXEC_SUB_COMPONENT,
    ACTION_NEXT_HTML_ITEM,
    ACTION_PREVIOUS_HTML_ITEM,
};
```

### AccessibilityHoverEventType

位置：`frameworks/core/accessibility/accessibility_constants.h:21-27`

```cpp
enum class AccessibilityHoverEventType {
    ENTER,   // 进入悬停状态
    MOVE,    // 悬停移动
    EXIT,    // 退出悬停状态
    CANCEL,  // 取消悬停
    Count
};
```

### HandleHoverRet

位置：`frameworks/core/accessibility/accessibility_manager_ng.h:54-61`

```cpp
enum class HandleHoverRet : int32_t {
    HOVER_HIT = 0,          // 命中
    HOVER_FAIL,             // 失败
    NO_MATCH_NODE,          // 无匹配节点
    ILLEGAL_PARAM,          // 非法参数
    TIMEOUT,                // 超时
    IN_TIME_LIMIT           // 在时间限制内
};
```

### AceFocusMoveResult

位置：`adapter/ohos/osal/accessibility/focus_move/accessibility_focus_strategy.h:38-47`

```cpp
enum class AceFocusMoveResult : int32_t {
    FIND_SUCCESS = 0,         // 查找成功
    FIND_FAIL,                // 查找失败
    FIND_CHILDTREE,           // 查找子树
    FIND_EMBED_TARGET,        // 查找嵌入目标
    FIND_FAIL_IN_CHILDTREE,   // 子树中查找失败
    FIND_FAIL_IN_SCROLL,      // 滚动中查找失败
    FIND_FAIL_LOST_NODE,      // 节点丢失
    FIND_FAIL_IN_ROOT_TYPE,   // 根类型中查找失败
};
```

---

## 组件无障碍属性

各组件通过继承 `AccessibilityProperty` 实现特定的无障碍属性。

### 示例组件

| 组件 | 文件位置 |
|------|----------|
| Badge | `frameworks/core/components_ng/pattern/badge/badge_accessibility_property.h` |
| Button | `frameworks/core/components_ng/pattern/button/toggle_button_accessibility_property.h` |
| Checkbox | `frameworks/core/components_ng/pattern/checkbox/*_accessibility_property.h` |
| ContainerModal | `frameworks/core/components_ng/pattern/container_modal/*_accessibility_property.h` |
| Gauge | `frameworks/core/components_ng/pattern/gauge/*_accessibility_property.h` |
| Grid | `frameworks/core/components_ng/pattern/grid/*_accessibility_property.h` |
| Indexer | `frameworks/core/components_ng/pattern/indexer/*_accessibility_property.h` |
| LinearIndicator | `frameworks/core/components_ng/pattern/linear_indicator/*_accessibility_property.h` |
| List | `frameworks/core/components_ng/pattern/list/*_accessibility_property.h` |
| Marquee | `frameworks/core/components_ng/pattern/marquee/*_accessibility_property.h` |
| Menu | `frameworks/core/components_ng/pattern/menu/*_accessibility_property.h` |
| Navigation | `frameworks/core/components_ng/pattern/navigation/*_accessibility_property.h` |
| Picker | `frameworks/core/components_ng/pattern/picker/datepicker_column_accessibility_property.h` |
| Progress | `frameworks/core/components_ng/pattern/progress/*_accessibility_property.h` |
| Rating | `frameworks/core/components_ng/pattern/rating/*_accessibility_property.h` |
| Refresh | `frameworks/core/components_ng/pattern/refresh/*_accessibility_property.h` |
| Scroll | `frameworks/core/components_ng/pattern/scroll/scroll_accessibility_property.h` |
| ScrollBar | `frameworks/core/components_ng/pattern/scroll_bar/*_accessibility_property.h` |
| Select | `frameworks/core/components_ng/pattern/select/*_accessibility_property.h` |
| Stepper | `frameworks/core/components_ng/pattern/stepper/*_accessibility_property.h` |
| Swiper | `frameworks/core/components_ng/pattern/swiper/*_accessibility_property.h` |
| Tabs | `frameworks/core/components_ng/pattern/tabs/*_accessibility_property.h` |
| TextClock | `frameworks/core/components_ng/pattern/text_clock/*_accessibility_property.h` |
| TextPicker | `frameworks/core/components_ng/pattern/text_picker/*_accessibility_property.h` |
| TextTimer | `frameworks/core/components_ng/pattern/texttimer/*_accessibility_property.h` |
| TimePicker | `frameworks/core/components_ng/pattern/time_picker/*_accessibility_property.h` |
| Toast | `frameworks/core/components_ng/pattern/toast/*_accessibility_property.h` |
| Toggle | `frameworks/core/components_ng/pattern/toggle/*_accessibility_property.h` |
| UIExtension | `frameworks/core/components_ng/pattern/ui_extension/*_accessibility_session_adapter*.h` |
| Video | `frameworks/core/components_ng/pattern/video/video_accessibility_property.h` |
| WaterFlow | `frameworks/core/components_ng/pattern/waterflow/*_accessibility_property.h` |
| Web | `frameworks/core/components_ng/pattern/web/web_accessibility_property.h` |
| XComponent | `frameworks/core/components_ng/pattern/xcomponent/*_accessibility*.h` |

---

## 回调接口

### AccessibilityChildTreeCallback

位置：`frameworks/core/accessibility/accessibility_manager.h:173-199`

子树回调接口，用于处理子树注册和管理。

```cpp
class AccessibilityChildTreeCallback {
public:
    virtual bool OnRegister(uint32_t windowId, int32_t treeId) = 0;
    virtual bool OnDeregister() = 0;
    virtual bool OnSetChildTree(int32_t childWindowId, int32_t childTreeId) = 0;
    virtual bool OnDumpChildInfo(const std::vector<std::string>& params,
        std::vector<std::string>& info) = 0;
    virtual void OnClearRegisterFlag() = 0;
};
```

### AccessibilitySAObserverCallback

位置：`frameworks/core/accessibility/accessibility_manager.h:158-171`

系统无障碍状态观察者回调。

```cpp
class AccessibilitySAObserverCallback {
public:
    virtual bool OnState(bool state) = 0;
};
```

### AccessibilityScreenReaderObserverCallback

位置：`frameworks/core/accessibility/accessibility_manager.h:143-156`

屏幕阅读器观察者回调。

```cpp
class AccessibilityScreenReaderObserverCallback {
public:
    virtual bool OnState(bool state) = 0;
};
```

---

## 工具类

### AccessibilityUtils

位置：`frameworks/core/accessibility/accessibility_utils.h`

```cpp
class AccessibilityUtils {
public:
    static std::string GetRoleByType(AccessibilityRoleType roleType);
    static std::string GetAceComponentTypeByRoleType(AccessibilityRoleType roleType);
};
```

### AccessibilityPropertyUtils

位置：`frameworks/core/accessibility/utils/accessibility_property_utils.h`

```cpp
class AccessibilityPropertyUtils {
public:
    static std::string GetContent(const RefPtr<AccessibilityProperty>& property);
    static std::string GetAccessibilityText(const RefPtr<AccessibilityProperty>& property);
    static std::string GetComponentType(const RefPtr<FrameNode>& node,
        const RefPtr<AccessibilityProperty>& property);
    static StateControllerType CheckAndGetStateController(...);
    static ActionControllerType CheckAndGetActionController(...);
};
```

---

## 参考

### 相关文档

- [ACE Engine 项目文档](../CLAUDE.md)
- [Native API - Native_Interface_Accessibility](../../../interfaces/native/native_interface_accessibility.h)
- [无障碍属性 - ArkTS 通用属性](https://developer.huawei.com/consumer/cn/doc/harmonyos-guides-V5/arkts-universal-attributes-accessibility-V5)

### 源码索引

| 模块 | 路径 |
|--------|------|
| 核心接口 | `frameworks/core/accessibility/*.h` |
| 节点实现 | `frameworks/core/accessibility/accessibility_node.cpp` |
| NG 属性 | `frameworks/core/components_ng/property/accessibility_property.h` |
| JS 管理器 | `adapter/ohos/osal/js_accessibility_manager.h` |
| 焦点移动 | `adapter/ohos/osal/accessibility/focus_move/` |
| 工具类 | `frameworks/core/accessibility/utils/` |
| 组件属性 | `frameworks/core/components_ng/pattern/*/*_accessibility_property.h` |

### 架构关系图

```
┌───────────────────────────────────────────────────────┐
│           系统无障碍服务（Accessibility SA）          │
└───────────────────────────────────────────────────────┘
                      ↕
┌───────────────────────────────────────────────────────┐
│            NDK 接口层（Native API）                   │
└───────────────────────────────────────────────────────┘
                      ↕
┌───────────────────────────────────────────────────────┐
│          OSAL 层（Platform Adapter）                  │
│  ┌─────────────────────────────────────────────┐     │
│  │  JsAccessibilityManager                      │     │
│  │  - JsInteractionOperation (主交互)          │     │
│  │  - WebInteractionOperation (Web 交互)        │     │
│  │  - AccessibilityHoverManagerForThirdNG      │     │
│  └─────────────────────────────────────────────┘     │
│  ┌─────────────────────────────────────────────┐     │
│  │  AccessibilityFocusStrategy                  │     │
│  │  - 焦点搜索算法                              │     │
│  │  - FocusRulesCheckNode                      │     │
│  └─────────────────────────────────────────────┘     │
└───────────────────────────────────────────────────────┘
                      ↕
┌───────────────────────────────────────────────────────┐
│              Core 层（Framework）                      │
│  ┌─────────────────────────────────────────────┐     │
│  │  AccessibilityProvider (接口)                │     │
│  │  AccessibilityNode (旧架构)                 │     │
│  │  AccessibilityProperty (NG 架构)            │     │
│  │  AccessibilityManagerNG (悬停)              │     │
│  └─────────────────────────────────────────────┘     │
└───────────────────────────────────────────────────────┘
                      ↕
┌───────────────────────────────────────────────────────┐
│         Component 层（组件层）                        │
│  - FrameNode (NG 组件)                                │
│  - DOMNode (旧组件)                                   │
│  - Pattern 层无障碍属性                                │
└───────────────────────────────────────────────────────┘
```

---

> 本文档基于 ace_engine 仓库的实际代码分析生成，涵盖 100+ 个文件，包含核心层、OSAL 适配层、属性层和组件层的完整无障碍实现。遵循 [CLAUDE.md](../CLAUDE.md) 规范。
