# 拖拽系统完整知识库

> **文档版本**: v1.0  
> **更新时间**: 2026-02-11  
> **源码版本**: OpenHarmony ace_engine (master 分支)  
> **前置知识**: [手势系统](./Gesture_Knowledge_Base_CN.md) (拖拽基于手势识别实现)

---

## 📚 目录

1. [概述](#概述)
2. [系统架构](#系统架构)
3. [目录结构](#目录结构)
4. [拖拽管理器](#拖拽管理器)
5. [拖拽状态机](#拖拽状态机)
6. [拖拽预览系统](#拖拽预览系统)
7. [完整API清单](#完整api清单)
8. [核心实现细节](#核心实现细节)
9. [使用示例](#使用示例)
10. [调试指南](#调试指南)
11. [常见问题](#常见问题)

---

## 概述

### 系统定位

**拖拽系统**是 OpenHarmony ArkUI 框架中的**高级交互模块**,基于手势系统的 Pan(滑动)识别实现,提供完整的拖拽交互能力,包括拖拽启动、拖拽移动、拖拽释放、跨窗口拖拽等功能。

### 与手势系统的关系

```
┌─────────────────────────────────────────────────────────────────┐
│  手势系统 (Gesture System)                               │
│  - PanRecognizer 识别滑动手势                             │
│  - 当滑动距离超过阈值时触发拖拽                            │
│  - 源码: frameworks/core/components_ng/gestures/       │
└─────────────────────────────────────────────────────────────────┘
                               ↓ (扩展)
┌─────────────────────────────────────────────────────────────────┐
│  拖拽系统 (Drag & Drop System)                           │
│  - DragDropManager 管理拖拽全生命周期                      │
│  - 拖拽预览、拖拽动画、拖拽状态机                         │
│  - UDMF 数据传递、跨应用拖拽                            │
│  - 源码: frameworks/core/components_ng/manager/drag_drop/ │
└─────────────────────────────────────────────────────────────────┘
```

**核心依赖**:
- **手势识别**: 基于 PanRecognizer 的滑动识别
- **拖拽启动**: 当 Pan 手势识别到滑动距离超过阈值时启动拖拽
- **拖拽移动**: 延续 Pan 手势的 Move 事件处理
- **拖拽释放**: 对应 Pan 手势的 Up 事件

详细的手势系统实现参见: [手势系统知识库](./Gesture_Knowledge_Base_CN.md)

### 技术架构

```
┌─────────────────────────────────────────────────────────────────┐
│  应用层 (ArkTS)                                        │
│  .draggable() / .onDragStart() / .onDragMove() / .onDrop()  │
└─────────────────────────────────────────────────────────────────┘
                               ↓
┌─────────────────────────────────────────────────────────────────┐
│  拖拽管理层 (DragDropManager Layer)                      │
│  ├── DragDropManager (拖拽管理器)                         │
│  ├── DragDropProxy (拖拽代理)                             │
│  ├── DragDropInitiatingStateMachine (拖拽状态机)            │
│  └── DragDropSpringLoading (拖拽弹性加载)                  │
│  源码: frameworks/core/components_ng/manager/drag_drop/     │
└─────────────────────────────────────────────────────────────────┘
                               ↓
┌─────────────────────────────────────────────────────────────────┐
│  手势识别层 (GestureRecognizer Layer)                     │
│  └── PanRecognizer (拖拽启动基于Pan手势)                  │
│  源码: frameworks/core/components_ng/gestures/            │
└─────────────────────────────────────────────────────────────────┘
                               ↓
┌─────────────────────────────────────────────────────────────────┐
│  平台适配层 (Adapter Layer)                               │
│  ├── OverlayWindow (拖拽预览窗口)                         │
│  ├── UDMF Client (统一数据管理框架)                      │
│  └── Window Manager (窗口管理)                           │
└─────────────────────────────────────────────────────────────────┘
```

### 代码规模

| 项目 | 数量 |
|-----|------|
| 核心文件 | 约 20 个文件 |
| 核心代码 | 约 10,000+ 行 C++ 代码 |
| 拖拽状态 | 6 个主要状态 (Idle/Press/Ready/Lifting/Moving/...) |
| 拖拽代理 | DragDropProxy + OverlayWindow |
| 拖拽预览 | PixelMap 截图 + UINode 自定义预览 |

### 功能特性

| 功能类别 | 具体功能 |
|---------|---------|
| **拖拽启动** | 基于 Pan 手势阈值检测拖拽启动 |
| **拖拽移动** | 实时更新拖拽预览位置、触发 onDragMove |
| **拖拽释放** | 触发 onDrop、执行 Drop 动画、清理拖拽窗口 |
| **拖拽预览** | 组件截图、自定义预览、缩放动画、阴影效果 |
| **拖拽数据** | UDMF 统一数据管理、跨应用拖拽、文本/图片/文件支持 |
| **拖拽状态机** | Idle→Press→Ready→Lifting→Moving 完整状态转换 |
| **弹性加载** | Spring Loading 检测区域、自动滚动 |
| **拖拽配置** | DragPreviewOption 预览配置、自定义回调 |

### 拖拽生命周期

```
1. 拖拽启动识别
   ↓
2. 创建拖拽代理 (DragDropProxy)
   ↓
3. 显示拖拽预览窗口 (OverlayWindow)
   ↓
4. 拖拽移动处理 (更新预览位置 + 触发回调)
   ↓
5. 检测 Drop 目标
   ↓
6. 拖拽释放处理 (onDrop + 动画 + 清理)
   ↓
7. 恢复拖拽源节点状态
```

---

## 系统架构

### 完整调用链

#### 拖拽启动流程

```
┌─────────────────────────────────────────────────────────────────┐
① Pan手势识别到滑动                                           │
┌─────────────────────────────────────────────────────────────────┐
│ PanGestureRecognizer 识别到滑动超过阈值                         │
│ frameworks/components_ng/gestures/recognizers/               │
│           pan_recognizer.cpp:456-489                        │
│                                                          │
│ 触发条件:                                                 │
│ 1. TouchDown 手指按下                                     │
│ 2. TouchMove 移动距离超过 distance_ 阈值                   │
│ 3. 速度/方向满足 Pan 配置                                  │
│ 4. 组件设置了 .draggable(true)                            │
└─────────────────────────────────────────────────────────────────┘
                               ↓
┌─────────────────────────────────────────────────────────────────┐
② 触发拖拽启动回调                                           │
┌─────────────────────────────────────────────────────────────────┐
│ 组件的 onDragStart 回调被触发                               │
│                                                          │
│ 用户可以在回调中:                                         │
│ 1. 设置拖拽数据 (event.getData().addText(...))           │
│ 2. 配置拖拽预览 (preview 选项)                             │
│ 3. 阻止拖拽 (event.preventDefault())                      │
└─────────────────────────────────────────────────────────────────┘
                               ↓
┌─────────────────────────────────────────────────────────────────┐
③ 创建拖拽代理和预览窗口                                     │
┌─────────────────────────────────────────────────────────────────┐
│ DragDropManager::CreateAndShowItemDragOverlay()            │
│ frameworks/components_ng/manager/drag_drop/                 │
│           drag_drop_manager.h:71-74                          │
│                                                          │
│ 执行流程:                                                 │
│ 1. 获取组件截图 (PixelMap 或 UINode)                      │
│ 2. 应用拖拽预览配置 (DragPreviewOption)                   │
│ 3. 创建 DragDropProxy                                      │
│ 4. 创建拖拽预览窗口 (OverlayWindow)                        │
│ 5. 设置拖拽初始位置                                        │
└─────────────────────────────────────────────────────────────────┘
```

#### 拖拽移动流程

```
┌─────────────────────────────────────────────────────────────────┐
④ 拖拽移动处理                                             │
┌─────────────────────────────────────────────────────────────────┐
│ DragDropManager::OnDragMove(pointerEvent)                 │
│ frameworks/components_ng/manager/drag_drop/                 │
│           drag_drop_manager.h:128-129                        │
│                                                          │
│ 执行流程:                                                 │
│ 1. 更新拖拽预览窗口位置                                    │
│ 2. 查找目标 Drop 节点 (HitTest)                          │
│ 3. 触发目标节点的 onDragEnter/onDragMove 回调              │
│ 4. 检测 Spring Loading (弹性加载)区域                     │
│ 5. 更新拖拽状态机 (Moving 状态)                           │
└─────────────────────────────────────────────────────────────────┘
```

#### 拖拽释放流程

```
┌─────────────────────────────────────────────────────────────────┐
⑤ 拖拽释放处理                                             │
┌─────────────────────────────────────────────────────────────────┐
│ DragDropManager::OnDragDrop(event, dragFrameNode, ...)      │
│ frameworks/components_ng/manager/drag_drop/                 │
│           drag_drop_manager.cpp:897-956                      │
│                                                          │
│ 执行流程:                                                 │
│ 1. 触发目标节点的 onDrop 回调                              │
│ 2. 处理 UDMF 数据传递 (跨应用数据)                         │
│ 3. 执行 Drop 动画                                         │
│ 4. 清理拖拽窗口和代理                                      │
│ 5. 恢复拖拽源节点状态                                     │
│ 6. 转换拖拽状态机到 Idle 状态                             │
└─────────────────────────────────────────────────────────────────┘
```

### 状态机设计

#### 拖拽启动状态机 (DragDropInitiatingStateMachine)

```
DragDropInitiatingStateMachine
│
├── Idle (空闲状态)
│   └── drag_drop_initiating_state_idle.h/cpp
│
├── Press (按下状态)
│   └── drag_drop_initiating_state_press.h/cpp
│       - 检测拖拽启动 (判断是否按下)
│
├── Ready (准备状态)
│   └── drag_drop_initiating_state_ready.h/cpp
│       - 达到拖拽阈值 (distance > threshold)
│       - 准备显示拖拽预览
│
├── Lifting (提升状态)
│   └── drag_drop_initiating_state_lifting.h/cpp
│       - 开始显示拖拽预览窗口
│       - 执行提升动画
│
├── Moving (移动状态)
│   └── drag_drop_initiating_state_moving.h/cpp
│       - 拖拽进行中
│       - 更新预览位置
│       - 检测 Drop 目标
│
└── ... (更多子状态)

源码: frameworks/components_ng/manager/drag_drop/
      drag_drop_initiating/drag_drop_initiating_state_machine.h
```

#### 状态转换图

```
[Idle] 
   ↓ (TouchDown)
[Press]
   ↓ (移动超过阈值)
[Ready]
   ↓ (准备拖拽预览)
[Lifting]
   ↓ (开始移动)
[Moving]
   ↓ (TouchUp)
[Idle]
```

---

## 目录结构

```
components_ng/manager/drag_drop/
├── drag_drop_manager.h/cpp               # 拖拽管理器 (核心)
├── drag_drop_proxy.h/cpp                # 拖拽代理
├── drag_drop_global_controller.h/cpp      # 全局拖拽控制器
├── drag_drop_related_configuration.h/cpp # 拖拽相关配置
├── drag_drop_initiating/                # 拖拽启动状态机
│   ├── drag_drop_initiating_state_machine.h/cpp
│   ├── drag_drop_initiating_handler.h/cpp
│   ├── drag_drop_initiating_state_base.h/cpp
│   ├── drag_drop_initiating_state_idle.h/cpp
│   ├── drag_drop_initiating_state_press.h/cpp
│   ├── drag_drop_initiating_state_ready.h/cpp
│   ├── drag_drop_initiating_state_lifting.h/cpp
│   └── drag_drop_initiating_state_moving.h/cpp
├── drag_drop_spring_loading/            # 弹性加载检测
│   ├── drag_drop_spring_loading_manager.h/cpp
│   └── drag_drop_spring_loading_node.h/cpp
├── drag_drop_behavior_reporter/         # 拖拽行为上报
│   └── drag_drop_behavior_reporter.h/cpp
├── utils/                             # 工具类
│   └── drag_drop_utils.h/cpp
└── overlays/                          # 拖拽预览
    ├── drag_window.h/cpp
    └── pixel_map_utils.h/cpp

components_ng/pattern/xxx_drag/
├── text_drag_pattern.h/cpp              # 文本拖拽
├── rich_editor_drag_pattern.h/cpp       # 富文本拖拽
├── image_drag_pattern.h/cpp            # 图片拖拽
└── ... (其他组件拖拽实现)

core/event/
└── drag_event.h                       # 拖拽事件定义

core/common/udmf/
├── udmf_client.h/cpp                  # UDMF 客户端
└── unified_data.h                     # 统一数据结构
```

---

## 拖拽管理器

### DragDropManager (拖拽管理器)

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/manager/drag_drop/drag_drop_manager.h`

**核心职责**: 管理拖拽全生命周期

```cpp
class ACE_EXPORT DragDropManager : public virtual AceType {
public:
    // 1. 创建拖拽预览
    RefPtr<DragDropProxy> CreateAndShowItemDragOverlay(
        const RefPtr<PixelMap>& pixelMap,
        const GestureEvent& info,
        const RefPtr<EventHub>& eventHub
    );

    RefPtr<DragDropProxy> CreateAndShowItemDragOverlay(
        const RefPtr<UINode>& customNode,
        const GestureEvent& info,
        const RefPtr<EventHub>& eventHub
    );

    // 2. 拖拽事件处理
    void OnDragStart(const Point& point);
    void OnDragMove(const DragPointerEvent& pointerEvent, ...);
    void OnDragEnd(const DragPointerEvent& pointerEvent, ...);
    void OnDragDrop(RefPtr<DragEvent>& event, ...);

    // 3. 拖拽状态管理
    bool IsDragged() const;
    void SetIsDragged(bool isDragged);
    bool IsDragWindowShow() const;
    Rect GetPreviewRect() const;

    // 4. UDMF数据管理
    void RequestDragSummaryInfoAndPrivilege();
    RefPtr<UnifiedData> RequestUDMFDataWithUDKey(const std::string& udKey);
    
    // 5. 获取全局实例
    static RefPtr<DragDropManager> GetInstance();

private:
    // 拖拽代理
    RefPtr<DragDropProxy> dragDropProxy_;
    
    // 拖拽状态机
    RefPtr<DragDropInitiatingStateMachine> initiatingStateMachine_;
    
    // 是否正在拖拽
    bool isDragged_ = false;
    
    // 拖拽预览矩形
    Rect previewRect_;
};
```

### 拖拽启动处理

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/manager/drag_drop/drag_drop_manager.cpp:123-156`

```cpp
RefPtr<DragDropProxy> DragDropManager::CreateAndShowItemDragOverlay(
    const RefPtr<PixelMap>& pixelMap,
    const GestureEvent& info,
    const RefPtr<EventHub>& eventHub)
{
    // 1. 获取组件节点
    auto dragFrameNode = eventHub->GetHost();
    CHECK_NULL_RETURN(dragFrameNode, nullptr);

    RefPtr<PixelMap> dragPixelMap;
    if (pixelMap) {
        // 使用传入的 PixelMap
        dragPixelMap = pixelMap;
    } else {
        // 从组件生成 PixelMap (截图)
        dragPixelMap = RenderSnapshot::GetWindowPixelMap(
            dragFrameNode->GetRenderContext()
        );
    }

    // 2. 应用拖拽预览配置
    ApplyDragPreviewOptions(dragPixelMap, info);

    // 3. 创建拖拽代理
    auto proxy = CreateFrameworkDragDropProxy();
    proxy->SetDragFrameNode(dragFrameNode);
    proxy->SetPixelMap(dragPixelMap);

    // 4. 显示拖拽窗口
    proxy->ShowDragWindow(info.GetScreenLocation());

    // 5. 应用拖拽动画
    ApplyDragAnimation(proxy);

    // 6. 设置拖拽状态
    SetIsDragged(true);

    return proxy;
}
```

### 拖拽移动处理

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/manager/drag_drop/drag_drop_manager.cpp:456-512`

```cpp
void DragDropManager::OnDragMove(
    const DragPointerEvent& pointerEvent,
    const RefPtr<FrameNode>& dragFrameNode,
    const RefPtr<DragEvent>& event)
{
    CHECK_NULL_VOID(dragDropProxy_);
    CHECK_NULL_VOID(event);

    // 1. 更新拖拽预览位置
    auto position = pointerEvent.GetOffset();
    dragDropProxy_->UpdateDragPosition(position);

    // 2. 查找 Drop 目标节点
    auto dropTargetNode = FindDropTarget(position);
    
    if (dropTargetNode) {
        // 3. 触发目标节点的 onDragMove 回调
        auto eventHub = dropTargetNode->GetEventHub();
        if (eventHub) {
            eventHub->GetOnDragMoveEvent()(event);
        }
    }

    // 4. 检测 Spring Loading (弹性加载) 区域
    if (CheckSpringLoadingRegion(position)) {
        StartSpringLoading(dropTargetNode);
    }

    // 5. 更新拖拽状态机
    if (initiatingStateMachine_) {
        initiatingStateMachine_->OnDragMove(pointerEvent);
    }
}
```

### 拖拽释放处理

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/manager/drag_drop/drag_drop_manager.cpp:897-956`

```cpp
void DragDropManager::OnDragDrop(
    RefPtr<DragEvent>& event,
    const RefPtr<FrameNode>& dragFrameNode,
    const RefPtr<FrameNode>& dropTargetNode)
{
    CHECK_NULL_VOID(event);

    // 1. 触发目标节点的 onDrop 回调
    if (dropTargetNode) {
        auto eventHub = dropTargetNode->GetEventHub();
        if (eventHub) {
            auto dragDropResult = eventHub->GetOnDropEvent()(event);
            
            // 处理拖拽结果
            HandleDragDropResult(dragDropResult);
        }
    }

    // 2. 处理 UDMF 数据传递 (跨应用拖拽)
    auto udKey = event->getExtraInfo();
    if (!udKey.empty()) {
        auto unifiedData = RequestUDMFDataWithUDKey(udKey);
        // 解析 UDMF 数据
        ProcessUDMFData(unifiedData);
    }

    // 3. 执行 Drop 动画
    ExecuteDropAnimation(dropTargetNode);

    // 4. 清理拖拽窗口和代理
    if (dragDropProxy_) {
        dragDropProxy_->DestroyDragWindow();
        dragDropProxy_.Reset();
    }

    // 5. 恢复拖拽源节点状态
    if (dragFrameNode) {
        dragFrameNode->GetRenderContext()->SetOpacity(1.0f);
        dragFrameNode->GetRenderContext()->SetScale(1.0f, 1.0f);
    }

    // 6. 转换拖拽状态机到 Idle
    if (initiatingStateMachine_) {
        initiatingStateMachine_->ChangeState(StateType::IDLE);
    }

    // 7. 重置拖拽状态
    SetIsDragged(false);
}
```

### DragDropProxy (拖拽代理)

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/manager/drag_drop/drag_drop_proxy.h`

```cpp
class DragDropProxy : public virtual AceType {
public:
    // 设置拖拽预览节点
    void SetDragFrameNode(const RefPtr<FrameNode>& node);
    
    // 设置拖拽 PixelMap (截图)
    void SetPixelMap(const RefPtr<PixelMap>& pixelMap);
    
    // 显示拖拽窗口
    void ShowDragWindow(const Point& position);
    
    // 更新拖拽位置
    void UpdateDragPosition(const Point& position);
    
    // 销毁拖拽窗口
    void DestroyDragWindow();
    
    // 获取拖拽窗口
    RefPtr<Window> GetDragWindow() const;
    
    // 获取拖拽预览矩形
    Rect GetPreviewRect() const;

private:
    // 拖拽预览窗口
    RefPtr<Window> dragWindow_;
    
    // 拖拽节点
    WeakPtr<FrameNode> dragFrameNode_;
    
    // 拖拽 PixelMap
    RefPtr<PixelMap> pixelMap_;
    
    // 拖拽窗口大小
    Size windowSize_;
    
    // 拖拽位置
    Point position_;
};
```

---

## 拖拽状态机

### DragDropInitiatingStateMachine (拖拽启动状态机)

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_state_machine.h`

```cpp
class DragDropInitiatingStateMachine : public AceType {
public:
    // 状态类型
    enum class StateType {
        IDLE,     // 空闲
        PRESS,    // 按下
        READY,    // 准备 (达到阈值)
        LIFTING,  // 提升 (开始显示预览)
        MOVING,   // 移动中
        // ... 更多状态
    };

    // 事件处理
    void OnDragStart(const DragPointerEvent& event);
    void OnDragMove(const DragPointerEvent& event);
    void OnDragEnd(const DragPointerEvent& event);
    
    // 状态转换
    void ChangeState(StateType newState);
    
    // 获取当前状态
    StateType GetCurrentState() const;

private:
    // 当前状态
    RefPtr<DragDropInitiatingStateBase> currentState_;
    
    // 状态处理器
    RefPtr<DragDropInitiatingHandler> handler_;
};
```

### 状态转换实现

#### Idle → Press (按下事件)

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_state_idle.cpp`

```cpp
void IdleState::OnDragStart(const DragPointerEvent& event)
{
    // 1. 记录初始按下位置
    startPoint_ = event.GetOffset();
    
    // 2. 记录按下时间
    touchDownTime_ = event.time;
    
    // 3. 转换到 Press 状态
    ChangeState(StateType::PRESS);
}
```

#### Press → Ready (移动超过阈值)

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_state_press.cpp`

```cpp
void PressState::OnDragMove(const DragPointerEvent& event)
{
    // 1. 计算移动距离
    double distance = (event.GetOffset() - startPoint_).GetLength();
    
    // 2. 检查是否超过拖拽阈值
    if (distance > dragDistanceThreshold_) {
        // 3. 转换到 Ready 状态
        ChangeState(StateType::READY);
        
        // 4. 准备拖拽预览
        PrepareDragPreview();
    }
}
```

#### Ready → Lifting (准备启动拖拽)

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_state_ready.cpp`

```cpp
void ReadyState::OnDragMove(const DragPointerEvent& event)
{
    // 1. 创建拖拽预览
    CreateDragPreview();
    
    // 2. 执行提升动画
    ExecuteLiftingAnimation();
    
    // 3. 转换到 Lifting 状态
    ChangeState(StateType::LIFTING);
}

void ReadyState::CreateDragPreview()
{
    // 调用 DragDropManager 创建拖拽代理和预览窗口
    auto proxy = DragDropManager::GetInstance()->CreateAndShowItemDragOverlay(
        pixelMap_, gestureInfo_, eventHub_
    );
}
```

#### Lifting → Moving (拖拽开始)

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_state_lifting.cpp`

```cpp
void LiftingState::OnDragMove(const DragPointerEvent& event)
{
    // 1. 更新拖拽预览位置
    auto proxy = DragDropManager::GetInstance()->GetDragDropProxy();
    if (proxy) {
        proxy->UpdateDragPosition(event.GetOffset());
    }
    
    // 2. 转换到 Moving 状态
    ChangeState(StateType::MOVING);
}
```

#### Moving → Idle (释放或取消)

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_state_moving.cpp`

```cpp
void MovingState::OnDragEnd(const DragPointerEvent& event)
{
    // 1. 执行拖拽释放逻辑
    HandleDragDrop(event);
    
    // 2. 转换到 Idle 状态
    ChangeState(StateType::IDLE);
}

void MovingState::HandleDragDrop(const DragPointerEvent& event)
{
    // 调用 DragDropManager 处理拖拽释放
    DragDropManager::GetInstance()->OnDragDrop(
        dragEvent_, dragFrameNode_, dropTargetNode_
    );
}
```

---

## 拖拽预览系统

### DragPreviewOption (拖拽预览配置)

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/gestures/gesture_info.h:89-126`

```cpp
struct DragPreviewOption {
    // 是否启用缩放动画
    bool isScaleEnabled = true;
    
    // 启用提升前的默认动画
    bool defaultAnimationBeforeLifting = false;
    
    // 是否启用多选模式
    bool isMultiSelectionEnabled = false;
    
    // 是否显示角标数字
    bool isNumber = false;
    
    // 是否启用默认阴影
    bool isDefaultShadowEnabled = false;
    
    // 是否启用默认圆角
    bool isDefaultRadiusEnabled = false;
    
    // 是否启用拖拽项目灰度效果
    bool isDefaultDragItemGrayEffectEnabled = false;
    
    // 是否启用边缘自动滚动
    bool enableEdgeAutoScroll = true;
    
    // 是否启用触觉反馈
    bool enableHapticFeedback = false;
    
    // 是否启用多瓦片效果
    bool isMultiTiled = false;
    
    // 是否禁用提升动画
    bool isLiftingDisabled = false;
    
    // 拖拽尺寸变化效果
    NG::DraggingSizeChangeEffect sizeChangeEffect =
        DraggingSizeChangeEffect::DEFAULT;
    
    // 自定义应用回调
    std::function<void(WeakPtr<NG::FrameNode>)> onApply;
    
    // 应用后的配置
    OptionsAfterApplied options;
};
```

### 拖拽预览生成

**PixelMap 截图预览**:

```cpp
RefPtr<PixelMap> DragDropManager::GenerateComponentPixelMap(
    const RefPtr<FrameNode>& node)
{
    // 1. 获取组件渲染上下文
    auto renderContext = node->GetRenderContext();
    
    // 2. 生成截图
    auto pixelMap = RenderSnapshot::GetWindowPixelMap(renderContext);
    
    // 3. 应用拖拽预览配置
    ApplyDragPreviewOptions(pixelMap, previewOption_);
    
    return pixelMap;
}
```

**自定义 UINode 预览**:

```cpp
RefPtr<UINode> DragDropManager::CreateCustomPreviewNode(
    const DragPreviewOption& option,
    const RefPtr<FrameNode>& sourceNode)
{
    // 1. 创建自定义预览节点
    auto previewNode = FrameNode::CreateFrameNode(
        "DragPreview",
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<Pattern>()
    );
    
    // 2. 应用自定义回调
    if (option.onApply) {
        option.onApply(previewNode);
    }
    
    // 3. 配置预览样式
    ConfigurePreviewNode(previewNode, option);
    
    return previewNode;
}
```

### 拖拽动画

**提升动画**:

```cpp
void DragDropManager::ExecuteLiftingAnimation()
{
    // 1. 创建动画属性
    AnimationOption animationOption;
    animationOption.SetDuration(200); // 200ms
    animationOption.SetCurve(Curve::EASE_OUT);
    
    // 2. 执行缩放动画
    if (previewOption_.isScaleEnabled) {
        auto scaleProperty = previewNode_->GetRenderProperty();
        scaleProperty->UpdateScale({ 1.05f, 1.05f }); // 放大到 105%
    }
    
    // 3. 执行透明度动画
    previewNode_->GetRenderContext()->SetOpacity(0.8f);
    
    // 4. 应用动画
    previewNode_->GetRenderContext()->AnimateTo(
        animationOption,
        []() {
            // 目标状态
        },
        []() {
            // 动画完成回调
        }
    );
}
```

**Drop 动画**:

```cpp
void DragDropManager::ExecuteDropAnimation(const RefPtr<FrameNode>& dropTarget)
{
    if (!dropTarget) {
        return;
    }
    
    // 1. 创建动画属性
    AnimationOption animationOption;
    animationOption.SetDuration(300); // 300ms
    animationOption.SetCurve(Curve::FAST_OUT_SLOW_IN);
    
    // 2. 获取 Drop 目标位置
    auto targetRect = dropTarget->GetGeometryNode()->GetFrameRect();
    
    // 3. 执行预览节点移动到目标位置的动画
    dragDropProxy_->AnimateToTarget(targetRect, animationOption);
    
    // 4. 动画完成后触发回调
    animationOption.SetOnFinishEvent([weak = WeakClaim(this)]() {
        auto manager = weak.Upgrade();
        if (manager) {
            // 清理拖拽窗口
            manager->OnDropAnimationFinished();
        }
    });
}
```

---

## 完整API清单

### 基础拖拽API

#### .draggable() 启用拖拽

**ArkTS API**:
```typescript
.draggable(value: boolean, options?: DragOptions)
```

**配置参数**:
```typescript
enum DragPreviewMode {
  AUTO = 1,
  DISABLE_SCALE = 2,
  ENABLE_DEFAULT_SHADOW = 3,
  ENABLE_DEFAULT_RADIUS = 4,
  ENABLE_DRAG_ITEM_GRAY_EFFECT = 5,
  ENABLE_MULTI_TILE_EFFECT = 6,
}

interface DragOptions {
  previewMode?: DragPreviewMode;  // 预览模式
  preview?: CustomNode | PixelMap;  // 自定义预览
  autoCancel?: boolean;  // 是否自动取消
  avatar?: PixelMap;    // 拖拽头像
  extraInfo?: string;    // 额外信息
}
```

#### 拖拽事件

**ArkTS API**:
```typescript
.onDragStart((event: DragEvent) => void)
.onDragEnter((event: DragEvent) => void)
.onDragMove((event: DragEvent) => void)
.onDragLeave((event: DragEvent) => void)
.onDrop((event: DragEvent) => void)
```

**DragEvent 定义**:
```typescript
interface DragEvent {
  offsetX?: number;    // X偏移
  offsetY?: number;    // Y偏移
  x?: number;        // 当前X
  y?: number;        // 当前Y
  screenX?: number;  // 屏幕X
  screenY?: number;  // 屏幕Y
  getData(): UnifiedData; // 获取拖拽数据
  setData(data: UnifiedData): void; // 设置拖拽数据
  setResult(result: DragDropRet): void; // 设置拖拽结果
  preventDefault(): void; // 阻止拖拽
}

enum DragDropRet {
  DROP_SUCCESS = 0,   // 拖拽成功
  DROP_FAIL = 1,      // 拖拽失败
  DROP_CANCELED = 2,  // 拖拽取消
}
```

### UDMF 数据API

#### UnifiedData (统一数据)

```typescript
// 创建统一数据
let unifiedData = new UnifiedData();

// 添加文本数据
unifiedData.addText('Hello World');

// 添加图片数据
unifiedData.addImage(pixelMap);

// 添加文件数据
unifiedData.addFile('/path/to/file');

// 添加自定义数据
unifiedData.addRecord(customRecord);

// 获取数据
let text = unifiedData.getText();
let image = unifiedData.getImage();
let file = unifiedData.getFile();
```

### 高级拖拽API

#### 自定义拖拽预览

```typescript
.draggable(true, {
  preview: () => {
    // 自定义预览节点
    Row() {
      Text('拖拽中')
        .fontSize(14)
        .fontColor(Color.White)
    }
    .width(100)
    .height(50)
    .backgroundColor(Color.Blue)
    .borderRadius(8)
  }
})
```

#### 拖拽预览配置

```typescript
interface DragPreviewOption {
  isScaleEnabled?: boolean;      // 是否启用缩放
  isDefaultShadowEnabled?: boolean; // 是否启用阴影
  enableHapticFeedback?: boolean;   // 是否启用触觉反馈
  enableEdgeAutoScroll?: boolean;   // 是否启用边缘滚动
  sizeChangeEffect?: DraggingSizeChangeEffect; // 尺寸变化效果
}

enum DraggingSizeChangeEffect {
  DEFAULT = 0,
  EXPAND = 1,    // 扩大
  SHRINK = 2,    // 缩小
}
```

---

## 核心实现细节

### 拖拽启动检测

**基于 Pan 手势的阈值检测**:

```cpp
// 在 DragDropInitiatingStateMachine 中
void PressState::OnDragMove(const DragPointerEvent& event)
{
    // 1. 计算移动距离
    double distance = (event.GetOffset() - startPoint_).GetLength();
    
    // 2. 获取拖拽阈值 (默认 8.0)
    auto threshold = GetDragDistanceThreshold();
    
    // 3. 检查是否超过阈值
    if (distance > threshold) {
        // 4. 触发拖拽启动
        HandleDragStart(event);
    }
}

double GetDragDistanceThreshold()
{
    // 从配置读取阈值
    double threshold = 8.0; // 默认 8.0 像素
    
    // 可以通过系统属性调整
    auto systemThreshold = SystemProperties::GetDragDistanceThreshold();
    if (systemThreshold > 0) {
        threshold = systemThreshold;
    }
    
    return threshold;
}
```

### UDMF 数据传递

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/common/udmf/udmf_client.h`

```cpp
class UDMFClient {
public:
    // 请求UDMF数据
    static RefPtr<UnifiedData> RequestUDMFDataWithUDKey(
        const std::string& udKey
    );
    
    // 设置拖拽数据
    static void SetUnifiedData(
        const RefPtr<UnifiedData>& data,
        const std::string& udKey
    );
    
    // 生成 UDKey
    static std::string GenerateUDKey();
};

// 使用示例: 设置拖拽数据
void OnDragStart(const DragEvent& event) {
    // 1. 创建统一数据
    auto unifiedData = MakeRefPtr<UnifiedData>();
    
    // 2. 添加文本数据
    auto textRecord = MakeRefPtr<TextRecord>(dragText);
    unifiedData->AddRecord(textRecord);
    
    // 3. 添加图片数据 (如果需要)
    if (dragImage) {
        auto imageRecord = MakeRefPtr<ImageRecord>(dragImage);
        unifiedData->AddRecord(imageRecord);
    }
    
    // 4. 生成 UDKey
    std::string udKey = UDMFClient::GenerateUDKey();
    
    // 5. 设置到 UDMF
    UDMFClient::SetUnifiedData(unifiedData, udKey);
    
    // 6. 存储 UDKey 供 Drop 时使用
    event.setExtraInfo(udKey);
}

// 使用示例: 获取拖拽数据
void OnDrop(const DragEvent& event) {
    // 1. 从 UDMF 获取数据
    std::string udKey = event.getExtraInfo();
    auto unifiedData = UDMFClient::RequestUDMFDataWithUDKey(udKey);
    
    // 2. 解析数据
    if (unifiedData) {
        // 获取文本数据
        auto textRecord = unifiedData->GetRecord<TextRecord>();
        if (textRecord) {
            std::string text = textRecord->GetContent();
            // 处理文本数据
        }
        
        // 获取图片数据
        auto imageRecord = unifiedData->GetRecord<ImageRecord>();
        if (imageRecord) {
            auto pixelMap = imageRecord->GetPixelMap();
            // 处理图片数据
        }
    }
}
```

### Spring Loading (弹性加载)

**源码位置**: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/manager/drag_drop/drag_drop_spring_loading/`

```cpp
class DragDropSpringLoadingManager {
public:
    // 检测是否进入 Spring Loading 区域
    bool CheckSpringLoadingRegion(const Point& position);
    
    // 启动 Spring Loading
    void StartSpringLoading(const RefPtr<FrameNode>& targetNode);
    
    // 停止 Spring Loading
    void StopSpringLoading();
    
    // 执行滚动
    void ExecuteScroll();

private:
    // Spring Loading 区域检测
    bool IsInSpringLoadingRegion(const Point& position, const Rect& nodeRect);
    
    // 滚动方向和速度
    ScrollDirection scrollDirection_;
    double scrollSpeed_;
    
    // 是否正在滚动
    bool isScrolling_ = false;
};

bool DragDropSpringLoadingManager::IsInSpringLoadingRegion(
    const Point& position, 
    const Rect& nodeRect)
{
    // 检查是否在节点边缘区域
    const double edgeThreshold = 50.0; // 边缘阈值 50px
    
    bool atTop = (position.y - nodeRect.top) < edgeThreshold;
    bool atBottom = (nodeRect.bottom - position.y) < edgeThreshold;
    bool atLeft = (position.x - nodeRect.left) < edgeThreshold;
    bool atRight = (nodeRect.right - position.x) < edgeThreshold;
    
    return atTop || atBottom || atLeft || atRight;
}
```

---

## 使用示例

### 基础拖拽示例

#### 简单文本拖拽

```typescript
@Entry
@Component
struct SimpleDragExample {
  @State text: string = '拖拽我';

  build() {
    Column() {
      Text(this.text)
        .width(200)
        .height(100)
        .backgroundColor(Color.Blue)
        .draggable(true)
        .onDragStart((event: DragEvent) => {
          // 设置拖拽数据
          event.setData().addText(this.text);
          console.info('Drag started');
        })
        .onDragEnd((event: DragEvent) => {
          console.info('Drag ended');
        })
    }
    .width('100%')
    .height('100%')
  }
}
```

#### 拖拽到目标区域

```typescript
@Entry
@Component
struct DragDropExample {
  @State items: string[] = ['Item 1', 'Item 2', 'Item 3'];
  @State droppedText: string = '';

  build() {
    Row() {
      // 拖拽源区域
      Column() {
        ForEach(this.items, (item: string) => {
          Text(item)
            .width(150)
            .height(50)
            .backgroundColor(Color.Blue)
            .margin(10)
            .draggable(true)
            .onDragStart((e: DragEvent) => {
              e.setData().addText(item);
            })
        })
      }
      .width('50%')
      .height('100%')
      .backgroundColor('#F0F0F0')

      // Drop 目标区域
      Column() {
        Text('拖放到这里')
          .width('100%')
          .height(50)
          .backgroundColor(Color.Gray)
        Text(this.droppedText)
          .width('100%')
          .height(100)
          .backgroundColor(Color.Yellow)
      }
      .width('50%')
      .height('100%')
      .onDrop((e: DragEvent) => {
        this.droppedText = e.getData().getText();
        console.info('Dropped: ' + this.droppedText);
      })
    }
    .width('100%')
    .height('100%')
  }
}
```

### 自定义拖拽预览

#### 自定义预览节点

```typescript
@Entry
@Component
struct CustomPreviewExample {
  @State text: string = '自定义预览';

  build() {
    Column() {
      Text(this.text)
        .width(200)
        .height(100)
        .backgroundColor(Color.Purple)
        .draggable(true, {
          preview: () => {
            // 自定义拖拽预览
            Row() {
              Image($r('app.media.icon'))
                .width(30)
                .height(30)
                .margin({ right: 10 })
              Text('正在拖拽')
                .fontSize(14)
                .fontColor(Color.White)
            }
            .width(150)
            .height(50)
            .backgroundColor(Color.Green)
            .borderRadius(8)
            .padding(10)
          }
        })
        .onDragStart((e: DragEvent) => {
          e.setData().addText(this.text);
        })
    }
  }
}
```

#### 使用 PixelMap 作为预览

```typescript
@Entry
@Component
struct PixelMapPreviewExample {
  private pixelMap: PixelMap | undefined;

  aboutToAppear() {
    // 创建或获取 PixelMap
    this.pixelMap = this.createPixelMap();
  }

  build() {
    Column() {
      Text('PixelMap 预览')
        .width(200)
        .height(100)
        .backgroundColor(Color.Orange)
        .draggable(true, {
          preview: this.pixelMap, // 使用 PixelMap 作为预览
          previewMode: DragPreviewMode.DISABLE_SCALE
        })
        .onDragStart((e: DragEvent) => {
          e.setData().addText('PixelMap Drag');
        })
    }
  }
}
```

### 复杂拖拽场景

#### 列表拖拽排序

```typescript
@Entry
@Component
struct ListDragSortExample {
  @State items: Array<{id: number, text: string}> = [
    { id: 1, text: 'Item 1' },
    { id: 2, text: 'Item 2' },
    { id: 3, text: 'Item 3' },
    { id: 4, text: 'Item 4' }
  ];
  @State draggedItemIndex: number = -1;

  build() {
    Column() {
      List({ space: 10 }) {
        ForEach(this.items, (item: {id: number, text: string}, index: number) => {
          ListItem() {
            Row() {
              Text(item.text)
                .fontSize(16)
                .margin({ right: 20 })
              Text(`Index: ${index}`)
                .fontSize(12)
                .fontColor(Color.Gray)
            }
            .width('100%')
            .height(60)
            .backgroundColor(
              this.draggedItemIndex === index ? Color.Yellow : Color.Blue
            )
            .padding(20)
          }
          .draggable(true)
          .onDragStart((e: DragEvent) => {
            this.draggedItemIndex = index;
            e.setData().addText(JSON.stringify({ index: index }));
          })
          .onDragEnd(() => {
            this.draggedItemIndex = -1;
          })
          .onDrop((e: DragEvent) => {
            const data = JSON.parse(e.getData().getText());
            const fromIndex = data.index;
            const toIndex = index;
            
            // 交换元素位置
            const temp = this.items[fromIndex];
            this.items.splice(fromIndex, 1);
            this.items.splice(toIndex, 0, temp);
          })
        })
      }
      .width('100%')
      .height('100%')
      .padding(20)
    }
    .width('100%')
    .height('100%')
  }
}
```

#### 跨应用拖拽 (UDMF)

```typescript
@Entry
@Component
struct CrossAppDragExample {
  @State text: string = '跨应用拖拽';

  build() {
    Column() {
      Text(this.text)
        .width(200)
        .height(100)
        .backgroundColor(Color.Pink)
        .draggable(true)
        .onDragStart((e: DragEvent) => {
          // 创建统一数据
          let unifiedData = new UnifiedData();
          
          // 添加文本数据
          unifiedData.addText(this.text);
          
          // 添加图片数据 (如果有)
          if (this.pixelMap) {
            unifiedData.addImage(this.pixelMap);
          }
          
          // 设置数据到拖拽事件
          e.setData(unifiedData);
        })
        .onDrop((e: DragEvent) => {
          // 获取拖拽数据
          let unifiedData = e.getData();
          
          // 提取文本
          let text = unifiedData.getText();
          console.info('Received text: ' + text);
          
          // 提取图片
          let image = unifiedData.getImage();
          if (image) {
            this.displayImage = image;
          }
        })
    }
  }
}
```

---

## 调试指南

### 拖拽调试

#### 启用拖拽调试日志

```cpp
// 在 drag_drop_manager.cpp 中
#define ENABLE_DRAG_DEBUG 1

#ifdef ENABLE_DRAG_DEBUG
    #define DRAG_LOG(content) LOGI("[DragDrop] " content)
#else
    #define DRAG_LOG(content)
#endif

// 使用示例
void DragDropManager::OnDragStart(...) {
    DRAG_LOG("OnDragStart called");
    // ...
}
```

#### 常用调试方法

1. **追踪拖拽状态**:
   ```cpp
   void DragDropInitiatingStateMachine::ChangeState(StateType newState) {
       DRAG_LOG("State change: " + std::to_string((int)currentState_) + 
                " -> " + std::to_string((int)newState));
       // ...
   }
   ```

2. **追踪拖拽事件**:
   ```cpp
   void DragDropManager::OnDragMove(...) {
       DRAG_LOG("OnDragMove position: (" + 
                std::to_string(position.x) + ", " + 
                std::to_string(position.y) + ")");
       // ...
   }
   ```

3. **追踪 UDMF 数据**:
   ```cpp
   void DragDropManager::ProcessUDMFData(...) {
       DRAG_LOG("UDMF data size: " + std::to_string(unifiedData->GetRecordCount()));
       // ...
   }
   ```

### 常见问题排查

#### 问题1: 拖拽不启动

**可能原因**:
1. 组件未设置 `.draggable(true)`
2. 滑动距离未达到阈值
3. 手势被其他手势拦截

**排查方法**:
```typescript
// 1. 检查 draggable 是否设置
Text('test')
  .draggable(true)  // 必须设置为 true
  .onDragStart((e) => {
    console.info('Drag start triggered');  // 检查是否触发
  })

// 2. 检查是否有手势冲突
// 确保没有其他手势拦截 Pan 手势
```

#### 问题2: 拖拽预览不显示

**可能原因**:
1. 组件截图失败
2. 拖拽窗口创建失败
3. 预览配置错误

**排查方法**:
```cpp
// 在 drag_drop_manager.cpp 中添加检查
RefPtr<PixelMap> DragDropManager::CreateAndShowItemDragOverlay(...) {
    auto dragPixelMap = RenderSnapshot::GetWindowPixelMap(...);
    
    // 检查截图是否成功
    if (!dragPixelMap) {
        DRAG_LOG("Failed to create pixel map");
        return nullptr;
    }
    
    // 检查拖拽代理是否创建成功
    auto proxy = CreateFrameworkDragDropProxy();
    if (!proxy) {
        DRAG_LOG("Failed to create drag proxy");
        return nullptr;
    }
    
    // ...
}
```

#### 问题3: Drop 事件不触发

**可能原因**:
1. 目标节点未注册 onDrop
2. Drop 目标未命中
3. UDMF 数据传递失败

**排查方法**:
```typescript
// 1. 确保 Drop 目标注册了 onDrop
Column()
  .onDrop((e: DragEvent) => {
    console.info('Drop triggered');  // 检查是否触发
    console.info('Data: ' + e.getData().getText());
  })

// 2. 检查 Drop 目标是否正确命中
// 在代码中添加 HitTest 日志
```

### 性能优化

#### 优化拖拽预览生成

```cpp
// 缓存 PixelMap 避免重复生成
RefPtr<PixelMap> DragDropProxy::GetPixelMap()
{
    if (!pixelMap_ && dragFrameNode_) {
        // 延迟生成
        pixelMap_ = RenderSnapshot::GetWindowPixelMap(
            dragFrameNode_->GetRenderContext()
        );
    }
    return pixelMap_;
}
```

#### 优化拖拽移动处理

```cpp
// 使用节流减少更新频率
void DragDropManager::OnDragMove(...)
{
    // 节流: 每 16ms 更新一次 (60fps)
    static auto lastUpdateTime = std::chrono::steady_clock::now();
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(
        currentTime - lastUpdateTime
    ).count();
    
    if (elapsedTime < 16) {
        return; // 跳过本次更新
    }
    
    lastUpdateTime = currentTime;
    
    // 更新拖拽位置
    dragDropProxy_->UpdateDragPosition(position);
}
```

---

## 常见问题

### Q1: 拖拽和手势系统是什么关系?

**A**: 拖拽系统基于手势系统的 Pan(滑动)识别实现:
1. **拖拽启动**: 当 Pan 手势识别到滑动距离超过阈值时触发
2. **拖拽移动**: 延续 Pan 手势的 Move 事件处理
3. **拖拽释放**: 对应 Pan 手势的 Up 事件

详细内容参见: [手势系统知识库](./Gesture_Knowledge_Base_CN.md)

### Q2: 如何调整拖拽启动阈值?

**A**: 可以通过以下方式调整:
```typescript
// 1. 在 DragPreviewOption 中配置 (如果支持)
DragPreviewOption {
  // 某些配置可能影响阈值
}

// 2. 修改系统属性 (高级)
// 需要修改框架代码中的默认阈值
```

### Q3: 拖拽预览可以自定义吗?

**A**: 可以,通过 `.draggable()` 的 `preview` 参数:
```typescript
.draggable(true, {
  preview: () => {
    // 自定义预览节点
    Row() {
      Text('自定义预览')
    }
  }
})
```

### Q4: 如何实现跨应用拖拽?

**A**: 使用 UDMF (统一数据管理框架):
```typescript
.onDragStart((e: DragEvent) => {
  let unifiedData = new UnifiedData();
  unifiedData.addText('文本数据');
  unifiedData.addImage(pixelMap);
  e.setData(unifiedData);
})

.onDrop((e: DragEvent) => {
  let unifiedData = e.getData();
  let text = unifiedData.getText();
  let image = unifiedData.getImage();
})
```

### Q5: 拖拽过程中如何获取当前状态?

**A**: 通过 DragDropManager 获取状态:
```cpp
auto manager = DragDropManager::GetInstance();
if (manager->IsDragged()) {
    // 正在拖拽
    auto previewRect = manager->GetPreviewRect();
    auto proxy = manager->GetDragDropProxy();
}
```

### Q6: 如何阻止拖拽启动?

**A**: 在 onDragStart 回调中调用 preventDefault:
```typescript
.onDragStart((e: DragEvent) => {
  if (shouldPreventDrag) {
    e.preventDefault(); // 阻止拖拽
  }
})
```

### Q7: Spring Loading 是什么?

**A**: Spring Loading (弹性加载) 是一种自动滚动机制:
- 当拖拽到滚动容器边缘时自动触发滚动
- 方便用户拖拽到列表末尾或顶部
- 可通过 `enableEdgeAutoScroll` 配置控制

### Q8: 拖拽数据如何持久化?

**A**: UDMF 框架负责数据持久化:
```cpp
// UDMF 会自动处理数据存储
UDMFClient::SetUnifiedData(unifiedData, udKey);

// 跨应用访问
auto data = UDMFClient::RequestUDMFDataWithUDKey(udKey);
```

---

## 参考文档

- [手势系统知识库](./Gesture_Knowledge_Base_CN.md) - 拖拽系统的基础
- OpenHarmony ArkUI 官方文档: https://docs.openharmony.cn/
- UDMF 官方文档: 统一数据管理框架
- 拖拽系统源码: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/manager/drag_drop/`

---

**文档维护**: 本文档随代码版本更新,如有疑问或建议,请查阅源码或提交 Issue。
