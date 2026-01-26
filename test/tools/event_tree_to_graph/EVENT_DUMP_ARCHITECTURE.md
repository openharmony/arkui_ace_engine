# Event Tree Dump Architecture Design

## 1. Overview

Event Tree Dump 是 ACE Engine 中用于调试和分析事件处理流程的工具系统。它记录从事件输入到手势识别的完整生命周期，包括触摸事件、轴事件、hit test 结果和手势处理过程。

## 2. Architecture Diagram

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                           入口触发 (Entry Point)                            │
│  pipeline_context.cpp:3950                                                │
│  eventManager_->DumpEventWithCount(params, EventTreeType::TOUCH, hasJson)  │
└────────────────────────────┬────────────────────────────────────────────┘
                             │
                             ▼
┌─────────────────────────────────────────────────────────────────────────────┐
│                      EventManager (事件管理器)                               │
│  frameworks/core/common/event_manager.cpp                                   │
│                                                                              │
│  ┌──────────────────────────────────────────────────────────────────────┐  │
│  │ DumpEventWithCount()                                                 │  │
│  │ - 解析参数 (-n <count>)                                              │  │
│  │ - 调用 DumpEvent()                                                  │  │
│  └──────────────────────────────────────────────────────────────────────┘  │
│                             │                                            │
│  ┌──────────────────────────────────────────────────────────────────────┐  │
│  │ DumpEvent(EventTreeType type, bool hasJson)                         │  │
│  │ - 获取 EventTreeRecord                                               │  │
│  │ - 调用 EventTreeRecord::Dump()                                       │  │
│  └──────────────────────────────────────────────────────────────────────┘  │
└────────────────────────────┬────────────────────────────────────────────┘
                             │
                             ▼
┌─────────────────────────────────────────────────────────────────────────────┐
│                   EventTreeRecord (事件树记录)                              │
│  frameworks/core/common/event_dump.h + event_dump.cpp                     │
│                                                                              │
│  ┌──────────────────────────────────────────────────────────────────────┐  │
│  │ std::list<EventTree> eventTreeList  (最多5个EventTree)              │  │
│  │ ┌────────────────────────────────────────────────────────────────┐   │  │
│  │ │ EventTree [0]              EventTree [1] ... EventTree [4]      │   │  │
│  │ │ ┌──────────────────┐   ┌──────────────────┐                     │   │  │
│  │ │ │ Touch Points     │   │ Touch Points     │                     │   │  │
│  │ │ │ Axis Events      │   │ Axis Events      │                     │   │  │
│  │ │ │ Hit Test Tree    │   │ Hit Test Tree    │                     │   │  │
│  │ │ │ Gesture Tree     │   │ Gesture Tree     │                     │   │  │
│  │ │ └──────────────────┘   └──────────────────┘                     │   │  │
│  │ └────────────────────────────────────────────────────────────────┘   │  │
│  └──────────────────────────────────────────────────────────────────────┘  │
│                                                                              │
│  核心方法:                                                                  │
│  - AddTouchPoint()     - 添加触摸点                                       │
│  - AddAxis()           - 添加轴事件                                       │
│  - AddFrameNodeSnapshot() - 添加hit test节点快照                          │
│  - UpdateFrameNodeSnapshot() - 更新节点快照                               │
│  - AddGestureSnapshot() - 添加手势识别器快照                             │
│  - AddGestureProcedure()  - 添加手势处理过程                              │
│  - Dump()              - 输出dump数据                                     │
└────────────────────────────┬────────────────────────────────────────────┘
                             │
                    ┌────────┴─────────┐
                    │                  │
                    ▼                  ▼
         ┌──────────────────┐   ┌──────────────────┐
         │  数据收集阶段      │   │  数据输出阶段     │
         │ (Runtime)        │   │ (Dump触发时)     │
         └──────────────────┘   └──────────────────┘
```

## 3. Data Collection Flow (数据收集流程)

```
┌───────────────────────────────────────────────────────────────────────┐
│                        运行时数据收集                                  │
└───────────────────────────────────────────────────────────────────────┘
                                    │
        ┌───────────────────────────┼───────────────────────────┐
        │                           │                           │
        ▼                           ▼                           ▼
┌───────────────────┐   ┌───────────────────┐   ┌───────────────────┐
│  Touch Events     │   │  Axis Events      │   │  Hit Test         │
│  (触摸事件)        │   │  (轴事件)         │   │  (命中测试)        │
└─────────┬─────────┘   └─────────┬─────────┘   └─────────┬─────────┘
          │                         │                         │
          │                         │                         │
    ┌─────▼─────┐             ┌────▼──────┐            │
    │ pipeline_  │             │ pipeline_ │            │
    │ context.  │             │ context.  │            │
    │ OnTouch    │             │ OnAxis    │            │
    │ Event()    │             │ Event()   │            │
    └─────┬─────┘             └────┬──────┘            │
          │                         │                     │
          ▼                         ▼                     ▼
┌───────────────────────────────────────────────────────────────────────┐
│                    EventTreeRecord::AddTouchPoint()                    │
│                    EventTreeRecord::AddAxis()                        │
│                    EventTreeRecord::AddFrameNodeSnapshot()           │
└───────────────────────────────────────────────────────────────────────┘
                                    │
                                    ▼
┌───────────────────────────────────────────────────────────────────────┐
│                      Gesture Processing (手势处理)                    │
└───────────────────────────────────────────────────────────────────────┘
                                    │
          ┌───────────────────────────┼───────────────────────────┐
          │                           │                           │
          ▼                           ▼                           ▼
┌───────────────────┐   ┌───────────────────┐   ┌───────────────────┐
│ Touch Gesture     │   │ Axis Gesture      │   │ Gesture Snapshot  │
│ Recognizers       │   │ Recognizers       │   │ Collection         │
└─────────┬─────────┘   └─────────┬─────────┘   └─────────┬─────────┘
          │                         │                         │
          │                         │                         │
          ▼                         ▼                         ▼
┌───────────────────────────────────────────────────────────────────────┐
│              EventTreeRecord::AddGestureProcedure()                   │
│              - 记录手势状态机转换                                      │
│              - 记录处理决策 (disposal)                                 │
└───────────────────────────────────────────────────────────────────────┘
```

## 4. Data Structure Hierarchy (数据结构层次)

```
EventTreeRecord
  │
  ├─ EventTree [0-N] (最多5个)
  │   │
  │   ├─ std::list<TouchPointSnapshot> touchPoints
  │   │   └─ TouchPointSnapshot
  │   │       ├─ int32_t id
  │   │       ├─ OffsetF point / screenPoint
  │   │       ├─ TouchType type (DOWN/UP/MOVE/CANCEL)
  │   │       ├─ int64_t timestamp
  │   │       └─ bool isInjected
  │   │
  │   ├─ std::list<AxisSnapshot> axis
  │   │   └─ AxisSnapshot
  │   │       ├─ int32_t id
  │   │       ├─ OffsetF point / screenPoint
  │   │       ├─ AxisAction action (BEGIN/UPDATE/END/CANCEL)
  │   │       ├─ int64_t timestamp
  │   │       └─ bool isInjected
  │   │
  │   ├─ std::list<FrameNodeSnapshot> hitTestTree
  │   │   └─ FrameNodeSnapshot
  │   │       ├─ int32_t nodeId / parentNodeId
  │   │       ├─ std::string tag / comId
  │   │       ├─ bool monopolizeEvents / isHit / active
  │   │       ├─ int32_t hitTestMode
  │   │       ├─ std::vector<RectF> responseRegionList
  │   │       └─ TouchTestStrategy strategy
  │   │
  │   └─ std::map<int32_t, std::list<RefPtr<GestureSnapshot>>> gestureTree
  │       └─ GestureSnapshot (按fingerId组织)
  │           ├─ uint64_t id (recognizer指针)
  │           ├─ int32_t nodeId
  │           ├─ std::string type ( recognizer类型)
  │           ├─ int32_t depth (手势层级)
  │           └─ std::list<ProcedureStep> procedures (处理步骤)
  │               ├─ std::string procedure (处理函数名)
  │               ├─ std::string state (状态: READY/DETECTING/SUCCEED/FAIL)
  │               ├─ std::string disposal (决策: CONTINUE/ACCEPT/REJECT/PENDING)
  │               └─ int64_t timestamp
  │
  └─ uint64_t gestureMap (全局gesture ID映射)
```

## 5. Output Format Generation (输出格式生成)

### 5.1 Text Output Format

```
xxx)-(10000:10000:scope)] EventTreeDumpInfo: WindowName: EntryView
xxx)-(10000:10000:scope)] EventTreeDumpInfo: DisplayId: 0
xxx)-(10000:10000:scope)] EventTreeDumpInfo: WinId: 8
...
xxx)-(10000:10000:scope)] EventTreeDumpInfo: 0: event tree =>
xxx)-(10000:10000:scope)] EventTreeDumpInfo:   touch points:
xxx)-(10000:10000:scope)] EventTreeDumpInfo:     id: 0, point: Offset (392.00, 312.00),
                                              screenPoint: Offset (392.00, 312.00),
                                              type: TouchDown,
                                              timestamp: 2017-08-25 15:00:20.165,
                                              isInjected: 0
xxx)-(10000:10000:scope)] EventTreeDumpInfo:   hittest:
xxx)-(10000:10000:scope)] EventTreeDumpInfo:     nodeId: 0, parentId: -1,
                                              tag: root,
                                              monopolizeEvents: 0,
                                              isHit: 1,
                                              hitTestMode: 0,
                                              responseRegion: RectT (0.00, 0.00) - [720.00 x 1280.00]
xxx)-(10000:10000:scope)] EventTreeDumpInfo:   event procedures:
xxx)-(10000:10000:scope)] EventTreeDumpInfo:     finger:0
xxx)-(10000:10000:scope)] EventTreeDumpInfo:       frameNodeId: 242,
                                              type: TouchEventActuator,
                                              depth: 0,
                                              id: 0xef6c5fa0,
                                              parentId: 0x0
xxx)-(10000:10000:scope)] EventTreeDumpInfo:         stateHistory:
xxx)-(10000:10000:scope)] EventTreeDumpInfo:           procedure: HandleTouchDown,
                                              timestamp: 2017-08-25 15:00:20.170
xxx)-(10000:10000:scope)] EventTreeDumpInfo:           procedure: HandleTouchUp,
                                              timestamp: 2017-08-25 15:00:20.235
```

## 5. Key Collection Points (关键收集点)

### 5.1 Touch Points Collection
**Location:** `pipeline_context.cpp`
```cpp
eventManager_->GetEventTreeRecord(EventTreeType::TOUCH).AddTouchPoint(scalePoint);
```
- Triggered when touch events (DOWN, UP, CANCEL) are processed
- MOVE events are NOT recorded (to avoid data overflow)

### 5.2 Axis Events Collection
**Location:** `pipeline_context.cpp`
```cpp
eventManager_->GetEventTreeRecord(EventTreeType::TOUCH).AddAxis(scaleEvent);
```
- Triggered when axis events (BEGIN, UPDATE, END, CANCEL) are processed
- Continuous UPDATE events may be limited

### 5.3 Frame Node Snapshots Collection
**Location:** `frame_node.cpp` in `OnTouchEvent()`
```cpp
AddFrameNodeSnapshot(!isOutOfRegion, parentId, responseRegionList, touchTestType);
UpdateFrameNodeSnapshot(touchRes, touchTestType);
```
- Captured during hit test processing
- Records node hierarchy and hit test results

### 5.4 Gesture Procedure Collection
**Location:** `event_manager.cpp` in gesture dispatch
```cpp
eventTree_.AddGestureProcedure(
    recognizerId,
    touchEvent/axisEvent,
    extraInfo,
    state,       // READY/DETECTING/SUCCEED/FAIL
    disposal,    // CONTINUE/ACCEPT/REJECT/PENDING
    timestamp
);
```
- Records every state transition in gesture recognizers
- Tracks decision making process

## 6. Data Storage Limits (数据存储限制)

为了防止内存泄漏和数据溢出，系统设置了严格的限制：

| 限制类型 | 最大值 | 说明 |
|---------|--------|------|
| EventTree 数量 | 5 | 总共记录5个event tree |
| 每个 EventTree 的 touch down | 10 | 最多10个touch down事件 |
| 每个 EventTree 的 touch points | 20 | 最多20个touch points |
| 每个 EventTree 的 axis events | 20 | 最多20个axis events |
| 每个 EventTree 的 frame nodes | 256 | 最多256个frame node快照 |
| 每个 EventTree 的 gestures | 100 | 最多100个gesture procedures |

**自动清理机制：**
- 达到限制时，自动删除最旧的 EventTree
- 重复的 DOWN/BEGIN 事件会触发清理
- 使用队列模式 (FIFO) 管理存储

## 7. Timestamp Usage (时间戳使用)

所有时间戳使用以下格式：
```
GetCurrentTimestamp() → int64_t (微秒)
ConvertTimestampToStr() → "YYYY-MM-DD HH:MM:SS.mmm"
```

关键时间戳：
- Touch/Axis 事件时间戳
- Gesture procedure 时间戳
- Touch info 时间戳 (createTime, processTime, dispatchTime)

## 8. Component Mapping (组件映射关系)

```
Input Data (input.txt)
  │
  ├─ EventTreeDumpInfo (窗口信息)
  │   └─ 解析后 → DumpResult.windowInfo
  │
  ├─ event tree => (事件树开始)
  │   └─ 解析后 → DumpResult.eventTrees[]
  │
  ├─ touch points: (触摸点)
  │   └─ 解析后 → EventTree.touchPoints[]
  │
  ├─ hittest: (命中测试)
  │   └─ 解析后 → EventTree.hitTestTree[]
  │
  └─ event procedures: (事件处理过程)
      └─ 解析后 → EventTree.eventProcedures[]
```

## 10. Call Stack Summary (调用栈总结)

```
用户命令: hidumper -s WindowManagerService -a '-w <WinId> -event'
    ↓
pipeline_context.cpp:3950
  eventManager_->DumpEventWithCount()
    ↓
event_manager.cpp:2648
  DumpEventWithCount() → DumpEvent()
    ↓
event_manager.cpp:2088
  DumpEvent()
    ↓
event_dump.cpp:334
  EventTreeRecord::Dump()
    ├─ TouchPointSnapshot::Dump()
    ├─ AxisSnapshot::Dump()
    ├─ FrameNodeSnapshot::Dump()
    └─ GestureSnapshot::Dump()
    ↓
DumpLog::GetInstance().Print()
    ↓
设备文件系统: /data/arkui.dump
    ↓
hdc shell cat /data/arkui.dump → 本地文件
```
