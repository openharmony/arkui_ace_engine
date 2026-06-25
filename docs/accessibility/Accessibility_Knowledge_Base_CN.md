# Accessibility 无障碍知识库

> 文档版本：v3.1
> 更新时间：2026-05-25
> 源码版本：OpenHarmony ace_engine (master 分支)

## 概述

- 模块定位：ACE Engine 中的**无障碍桥接层**，负责将 ArkUI 组件树信息暴露给系统无障碍服务（屏幕阅读器、TalkBack 等），并接收无障碍服务的操作请求分发到组件。
- 典型使用场景：屏幕阅读、键盘焦点导航、辅助技术悬停探测、第三方无障碍服务集成、Web/UIExtension 等跨进程组件无障碍接入。
- 与相近能力差异：与普通输入事件分发系统并行，自带焦点搜索算法（`AccessibilityFocusStrategy`）和悬停状态机（`AccessibilityManagerNG`），并通过 NDK 接口（`ArkUI_AccessibilityElementInfo` / `ArkUI_AccessibilityEventInfo`）跨语言暴露能力。

核心职责：

| 职责 | 说明 |
|------|------|
| 信息暴露 | 将组件树属性、状态、位置封装为 `ArkUI_AccessibilityElementInfo` |
| 操作桥接 | 通过 `AccessibilityProvider` 接口分发动作到组件 |
| 事件通知 | 监听组件树变化，向无障碍服务发送 `ArkUI_AccessibilityEventInfo` |
| 属性提取 | 通过 JS Inspector 为 51 个旧架构组件提取定制无障碍属性 |
| 焦点管理 | 实现无障碍焦点移动、搜索和边界检查 |
| 悬停处理 | 处理辅助技术的悬停探测事件（含第三方 Provider） |

## 目录结构

```text
OpenHarmony/foundation/arkui/ace_engine/
├── frameworks/core/accessibility/              # 核心 accessibility 模块（10 个 .h）
│   ├── accessibility_provider.h               # 无障碍提供者抽象接口
│   ├── accessibility_session_adapter.h/.cpp   # 会话适配器
│   ├── accessibility_node.h/.cpp              # 无障碍节点（旧架构）
│   ├── accessibility_manager.h                # 旧架构管理器
│   ├── accessibility_manager_ng.h/.cpp        # NG 架构管理器（悬停）
│   ├── accessibility_constants.h              # 常量定义
│   ├── accessibility_utils.h/.cpp             # 工具函数与类型
│   ├── native_interface_accessibility_impl.h/.cpp     # NDK 接口实现
│   ├── native_interface_accessibility_provider.h/.cpp # NDK 提供者接口
│   ├── third_accessibility_manager.h          # 第三方无障碍管理器
│   ├── js_inspector/                          # 51 个旧组件 inspect 子类
│   ├── utils/                                 # 工具类（property/action/rect/manager）
│   ├── node_utils/                            # 节点工具
│   ├── static/                                # 静态工具
│   └── hidumper/                              # 调试工具
│
├── frameworks/core/components_ng/property/     # NG 属性层
│   ├── accessibility_property.h/.cpp          # 无障碍属性基类
│   ├── accessibility_property_mutilthread.cpp # 多线程实现
│   ├── accessibility_property_function.h      # 属性函数
│   └── accessibility_property_helper.h        # 辅助工具
│
├── adapter/ohos/osal/                          # OSAL 适配层
│   ├── js_accessibility_manager.h/.cpp        # JS 无障碍管理器（核心）
│   ├── js_third_accessibility_hover_ng.h/.cpp # 第三方悬停管理
│   ├── js_third_provider_interaction_operation.h/.cpp # 第三方交互
│   └── accessibility/
│       ├── accessibility_hidumper_osal.h/.cpp # HiDumper
│       ├── element_info/                      # 元素信息处理
│       │   ├── accessibility_element_info_osal.cpp
│       │   └── accessibility_node_osal.cpp
│       └── focus_move/                        # 焦点移动（16 个文件）
│           ├── accessibility_focus_strategy.h/.cpp
│           ├── accessibility_focus_move_osal{,_ng,_node,_third}.h/.cpp
│           ├── accessibility_focus_accessibility_node_utils.h/.cpp
│           ├── accessibility_focus_frame_node_utils.h/.cpp
│           └── accessibility_focus_third_node_utils.h/.cpp
│
└── frameworks/bridge/common/accessibility/     # Bridge 层
    └── accessibility_node_manager.h/.cpp      # 节点管理器接口
```

## 核心类继承关系

```text
AceType
 ├── AccessibilityProvider                                  (抽象接口)
 ├── AccessibilitySessionAdapter                            (会话适配)
 │    ├── AccessibilitySessionAdapterForm
 │    ├── AccessibilitySessionAdapterUIExtension
 │    ├── AccessibilitySessionAdapterIsolatedComponent
 │    ├── XcomponentAccessibilitySessionAdapter
 │    ├── WebAccessibilitySessionAdapter
 │    └── CustomAccessibilitySessionAdapter
 ├── AccessibilityNode                                      (旧架构 DOM 节点)
 ├── AccessibilityManagerNG                                 (NG 悬停管理)
 ├── AccessibilityHoverManagerForThirdNG                    (第三方悬停)
 └── AccessibilityProperty                                  (NG 属性基类)
      └── <Component>AccessibilityProperty                  (各组件特化)

AccessibilityManager (核心 IF)
 └── AccessibilityNodeManager   (Bridge 层节点管理器)
      └── JsAccessibilityManager (同时继承 AccessibilityHoverManagerForThirdNG)
```

- `JsAccessibilityManager` 多重继承：[adapter/ohos/osal/js_accessibility_manager.h:146](adapter/ohos/osal/js_accessibility_manager.h#L146)
- `AccessibilityProperty` 基类：[frameworks/core/components_ng/property/accessibility_property.h:785](frameworks/core/components_ng/property/accessibility_property.h#L785)
- `AccessibilityNode` 旧架构节点：[frameworks/core/accessibility/accessibility_node.h:58](frameworks/core/accessibility/accessibility_node.h#L58)
- `FocusRulesCheckNode` 焦点规则节点：[adapter/ohos/osal/accessibility/focus_move/accessibility_focus_strategy.h:66](adapter/ohos/osal/accessibility/focus_move/accessibility_focus_strategy.h#L66)

## Pattern层详解

无障碍体系的"Pattern 等价物"是 **OSAL/Core 层管理器与 NDK 接口**，负责接入系统、调度动作、转发事件。

### JsAccessibilityManager（OSAL 核心）

Source: [adapter/ohos/osal/js_accessibility_manager.h:146](adapter/ohos/osal/js_accessibility_manager.h#L146)（共 992 行）

```cpp
class JsAccessibilityManager : public AccessibilityNodeManager,
    public AccessibilityHoverManagerForThirdNG {
    DECLARE_ACE_TYPE(JsAccessibilityManager, AccessibilityNodeManager);
```

主要职责：节点搜索、动作执行、焦点移动、事件发送、第三方 Provider 注册、Web 无障碍。关键方法：
- `SearchElementInfoByAccessibilityId(...)` / `SearchElementInfosByText(...)`
- `FindFocusedElementInfo(...)` / `FocusMoveSearchNG(...)`
- `ExecuteAction(...)` / `ExecuteActionNG(...)`
- `SendAccessibilityAsyncEvent(...)` / `SendAccessibilitySyncEvent(...)`
- `RegisterJsThirdProviderInteractionOperation(...)`
- WEB_SUPPORTED 宏内：`SearchWebElementInfoByAccessibilityId`、`SendWebAccessibilityAsyncEvent`

内部交互操作类：`JsInteractionOperation`（主交互）、`WebInteractionOperation`（Web 交互）。

### AccessibilityManagerNG（NG 悬停状态机）

Source: [frameworks/core/accessibility/accessibility_manager_ng.h:72](frameworks/core/accessibility/accessibility_manager_ng.h#L72)

```cpp
class AccessibilityManagerNG final: public AceType {
public:
    void HandleAccessibilityHoverEvent(const RefPtr<FrameNode>& root, const MouseEvent& event);
    void HandleAccessibilityHoverEvent(const RefPtr<FrameNode>& root, const TouchEvent& event);
    void HandleAccessibilityHoverEvent(const RefPtr<FrameNode>& root,
        float pointX, float pointY, int32_t sourceType, int32_t eventType, int64_t timeMs);

    HandleHoverRet HandleAccessibilityHoverEventBySurfaceId(
        const std::string& surfaceId, HandleHoverEventParam& param);

    static bool ConvertPointFromAncestorToNode(...);
    void HoverTestDebug(const RefPtr<FrameNode>& root, const PointF& point,
        std::string& summary, std::string& detail) const;
private:
    AccessibilityHoverStateManager hoverStateManager_;
};
```

### AccessibilityFocusStrategy（焦点搜索算法）

Source: [adapter/ohos/osal/accessibility/focus_move/accessibility_focus_strategy.h:127](adapter/ohos/osal/accessibility/focus_move/accessibility_focus_strategy.h#L127)

提供 `FindNextReadableNode` / `FindPrevReadableNode` / `FindLastNodeWithoutCheck` / `FindForwardScrollAncestor` / `FindBackwardScrollAncestor` 等算法；配合 `FocusRulesCheckNode`（行 66）做可访问性、子树容器、嵌入目标等边界判定。

### AccessibilityHoverManagerForThirdNG（第三方悬停）

Source: [adapter/ohos/osal/js_third_accessibility_hover_ng.h:63](adapter/ohos/osal/js_third_accessibility_hover_ng.h#L63)

管理第三方 Provider 的悬停状态、焦点动作及子节点信息 dump：`HandleAccessibilityHoverForThird`、`ActThirdAccessibilityFocus`、`ClearThirdAccessibilityFocus`、`OnDumpChildInfoForThirdRecursive`。

## Model层详解

无障碍属性的"Model 等价物"是 **NG `AccessibilityProperty` 基类** 与各组件继承的属性类，承担组件树侧的属性写入和暴露。

### AccessibilityProperty 基类

Source: [frameworks/core/components_ng/property/accessibility_property.h:785](frameworks/core/components_ng/property/accessibility_property.h#L785)

```cpp
class ACE_FORCE_EXPORT AccessibilityProperty : public virtual AceType, ... {
public:
    virtual std::string GetText() const;
    virtual std::string GetGroupText(bool forceGetChildren = false) const;
    virtual bool IsCheckable() const;
    virtual bool IsChecked() const;
    virtual bool IsSelected() const;
    virtual bool IsPassword() const;
    virtual bool IsEditable() const;
    // ...
};
```

各组件通过继承 `AccessibilityProperty` 实现差异化暴露，例如：

| 组件 | 文件 |
|------|------|
| Badge | [frameworks/core/components_ng/pattern/badge/badge_accessibility_property.h](frameworks/core/components_ng/pattern/badge/badge_accessibility_property.h) |
| Checkbox | `frameworks/core/components_ng/pattern/checkbox/*_accessibility_property.h` |
| Grid / List / Scroll / Swiper / Tabs / WaterFlow | `frameworks/core/components_ng/pattern/<comp>/*_accessibility_property.h` |
| Picker / TimePicker / TextPicker / DatePicker | `frameworks/core/components_ng/pattern/<picker>/*_accessibility_property.h` |
| Progress / Gauge / Rating / Slider | `frameworks/core/components_ng/pattern/<comp>/*_accessibility_property.h` |
| UIExtension / Web / XComponent | `frameworks/core/components_ng/pattern/<comp>/*_accessibility*.h` |

### AccessibilityNode（旧架构 DOM）

Source: [frameworks/core/accessibility/accessibility_node.h:58](frameworks/core/accessibility/accessibility_node.h#L58)（共 665 行）

位域优化存储与动作回调类型集合（`ActionClickImpl`、`ActionLongClickImpl`、`ActionSetTextImpl`、`ActionScrollForwardImpl` 等）。

### JS Inspector 旧组件属性提取

[frameworks/core/accessibility/js_inspector/](frameworks/core/accessibility/js_inspector/) 包含 51 个 `inspect_<component>.h/.cpp`，为旧 DOM 组件抽取无障碍属性。

## 完整API清单

### Native API（NDK）

- 头文件：[OpenHarmony/foundation/arkui/ace_engine/interfaces/native/native_interface_accessibility.h](../../interfaces/native/native_interface_accessibility.h)
- 数据结构：
  - `ArkUI_AccessibilityElementInfo` — [frameworks/core/accessibility/native_interface_accessibility_impl.h:30](frameworks/core/accessibility/native_interface_accessibility_impl.h#L30)
  - `ArkUI_AccessibilityEventInfo` — [frameworks/core/accessibility/native_interface_accessibility_impl.h:503](frameworks/core/accessibility/native_interface_accessibility_impl.h#L503)
  - `ArkUI_AccessibilityElementInfoList` — 行 566
- 提供者接口：[frameworks/core/accessibility/native_interface_accessibility_provider.h](frameworks/core/accessibility/native_interface_accessibility_provider.h)

### Core 抽象接口

- `AccessibilityProvider`：[frameworks/core/accessibility/accessibility_provider.h:33](frameworks/core/accessibility/accessibility_provider.h#L33)
  - `FindAccessibilityNodeInfosById/ByText`、`FindFocusedAccessibilityNode`、`FindNextFocusAccessibilityNode`
  - `ExecuteAccessibilityAction`、`ClearFocusedAccessibilityNode`、`GetAccessibilityNodeCursorPosition`
  - `SendAccessibilityAsyncEvent`、`SendThirdAccessibilityProvider`
- `AccessibilitySessionAdapter`：[frameworks/core/accessibility/accessibility_session_adapter.h:30](frameworks/core/accessibility/accessibility_session_adapter.h#L30)
  - `TransferHoverEvent`、`IgnoreHostNode`、`IgnoreTransformMouseEvent`、静态 `GetSessionAdapter`

### 回调接口

- `AccessibilityChildTreeCallback`：[frameworks/core/accessibility/accessibility_manager.h:172](frameworks/core/accessibility/accessibility_manager.h#L172)
- `AccessibilitySAObserverCallback`：[frameworks/core/accessibility/accessibility_manager.h:157](frameworks/core/accessibility/accessibility_manager.h#L157)
- `AccessibilityScreenReaderObserverCallback`：[frameworks/core/accessibility/accessibility_manager.h:142](frameworks/core/accessibility/accessibility_manager.h#L142)

### 工具类

- `AccessibilityUtils`：[frameworks/core/accessibility/accessibility_utils.h](frameworks/core/accessibility/accessibility_utils.h)（`GetRoleByType`、`GetAceComponentTypeByRoleType`）
- `AccessibilityPropertyUtils`：[frameworks/core/accessibility/utils/accessibility_property_utils.h](frameworks/core/accessibility/utils/accessibility_property_utils.h)
- `AccessibilityActionFunctionUtils` / `AccessibilityRectInfoUtils` / `AccessibilityManagerUtils`：同目录

## 关键实现细节

### 关键枚举与常量

- 组件标签常量（`ACCESSIBILITY_TAG_*`，共 **37** 个）：[frameworks/core/accessibility/accessibility_utils.h:29](frameworks/core/accessibility/accessibility_utils.h#L29)
- `AccessibilityEventType`：[frameworks/core/accessibility/accessibility_utils.h:74](frameworks/core/accessibility/accessibility_utils.h#L74)（CLICK / LONG_PRESS / TEXT_CHANGE / HOVER_* / SCROLL_* / ANNOUNCE_FOR_ACCESSIBILITY 等）
- `AceAction`：[frameworks/core/accessibility/accessibility_utils.h:153](frameworks/core/accessibility/accessibility_utils.h#L153)（ACTION_FOCUS / ACTION_CLICK / ACTION_SCROLL_FORWARD / ACTION_SET_TEXT 等）
- `AccessibilityHoverEventType`：[frameworks/core/accessibility/accessibility_constants.h:21](frameworks/core/accessibility/accessibility_constants.h#L21)（ENTER/MOVE/EXIT/CANCEL）
- `HandleHoverRet`：[frameworks/core/accessibility/accessibility_manager_ng.h:54](frameworks/core/accessibility/accessibility_manager_ng.h#L54)
- `AceFocusMoveResult`：[adapter/ohos/osal/accessibility/focus_move/accessibility_focus_strategy.h:39](adapter/ohos/osal/accessibility/focus_move/accessibility_focus_strategy.h#L39)

### 关键数据结构

- `AccessibilityEvent`（事件载荷）：[frameworks/core/accessibility/accessibility_manager.h:62](frameworks/core/accessibility/accessibility_manager.h#L62)
- `AccessibilityHoverState` / `AccessibilityHoverForThirdState`：分别管理 NG 与第三方悬停状态
- `RotateTransform` / `AccessibilityParentRectInfo`：父窗口坐标变换信息

### 架构分层

```
系统无障碍服务 (Accessibility SA)
        ↕  NDK 接口
NDK 层 (native_interface_accessibility_*)
        ↕
OSAL 层 (JsAccessibilityManager / JsInteractionOperation /
         WebInteractionOperation / AccessibilityHoverManagerForThirdNG /
         AccessibilityFocusStrategy)
        ↕
Core 层 (AccessibilityProvider / AccessibilityNode / AccessibilityProperty /
         AccessibilityManagerNG)
        ↕
组件层 (FrameNode / DOMNode + Pattern 层无障碍属性)
```

## 使用示例

ArkTS 应用侧通过通用属性接入无障碍能力：

```ts
@Entry
@Component
struct AccessibilityDemo {
  @State checked: boolean = false
  build() {
    Column() {
      Button(this.checked ? '已选中' : '未选中')
        .accessibilityText('收藏开关')
        .accessibilityDescription('双击切换收藏状态')
        .accessibilityLevel('yes')
        .accessibilityChecked(this.checked)
        .onClick(() => { this.checked = !this.checked })
    }
  }
}
```

Native 侧通过 `ArkUI_AccessibilityProvider` 注册自定义节点能力（详见 NDK 头文件 `native_interface_accessibility.h`）。

## 调试指南

### HiDumper

- 入口：[adapter/ohos/osal/accessibility/accessibility_hidumper_osal.h](adapter/ohos/osal/accessibility/accessibility_hidumper_osal.h)
- Core 端：[frameworks/core/accessibility/hidumper/accessibility_hidumper.h](frameworks/core/accessibility/hidumper/accessibility_hidumper.h)
- 用法：`hidumper -s WindowManagerService -a '-w <windowId> -element <id>'` 类似命令可触发 accessibility 节点信息 dump。

### 悬停命中调试

`AccessibilityManagerNG::HoverTestDebug(root, point, summary, detail)` 用于在测试代码或日志中输出悬停命中链与详细信息。

### 关键日志点

- `JsInteractionOperation::SearchElementInfoByAccessibilityId` — 节点查询入口
- `JsAccessibilityManager::ExecuteActionNG` — 动作分发
- `AccessibilityFocusStrategy::FindNextReadableNode` — 焦点搜索

### 排查流程

1. 复现时打开 accessibility 日志域。
2. 确认 `AccessibilityProperty` 是否暴露预期 text / role / state。
3. 若动作失败，检查 `AceAction` 是否在 `AccessibilityProperty::GetSupportAction()` 返回集合中。
4. 跨进程组件（Form / UIExtension / Isolated / XComponent）需检查对应 `AccessibilitySessionAdapter` 实现。

## 常见问题

1. **问题**：自定义组件读屏无法朗读。
   **结论**：检查是否设置了 `accessibilityText` / `accessibilityDescription`，并确认 `accessibilityLevel` 不是 `'no'` / `'no-hide-descendants'`；底层对应 `AccessibilityProperty::GetText/GetAccessibilityText`。

2. **问题**：滚动容器内无障碍焦点无法跳转到下一项。
   **结论**：参考 `AccessibilityFocusStrategy::FindForwardScrollAncestor/FindBackwardScrollAncestor`，确认容器的 `FocusRulesCheckNode::IsAccessibiltyVisible` 与可滚动祖先识别是否成立。

3. **问题**：第三方/跨进程组件（UIExtension/XComponent）的无障碍节点未上报。
   **结论**：需要实现 `AccessibilityProvider` 接口并通过 `JsAccessibilityManager::RegisterJsThirdProviderInteractionOperation` 注册；悬停由 `AccessibilityHoverManagerForThirdNG::HandleAccessibilityHoverForThird` 处理。

4. **问题**：旧 DOM 组件无障碍属性缺失。
   **结论**：补充 [frameworks/core/accessibility/js_inspector/](frameworks/core/accessibility/js_inspector/) 中对应 `inspect_<component>` 实现（NG 组件不走该路径，改用 `AccessibilityProperty` 子类）。

5. **问题**：朗读文本与显示不一致。
   **结论**：`AccessibilityPropertyUtils::GetContent / GetAccessibilityText` 优先级 — 用户设置的 `accessibilityText` 优先于 `GetText()` 自动提取；检查应用是否覆盖了相关属性。
