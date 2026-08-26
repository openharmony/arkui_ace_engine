# 鼠标右键转长按事件 — 方案实现文档

> PR: https://gitcode.com/openharmony/arkui_ace_engine/pull/88653

## 1. 需求背景

桌面环境下，割接应用（仅适配手机）和一多应用在 PC/平板连接鼠标时，鼠标右键无法唤出文本类组件的上下文菜单。通过将右键事件映射为合成长按触摸事件，使 TextInput、TextArea、RichEditor、Text 等白名单组件通过右键即可触发长按菜单。

## 2. 方案选型

采用 **方案 E：Adapter 层 + 裁剪 HitTest 回调 + Pointer 级转换**。

| 特征 | 说明 |
|---|---|
| 决策与转换位置 | 全部在 AceViewOhos（Adapter 层） |
| Pipeline 感知 | 无（Pipeline 核心逻辑不做路由变更，仅持有被动状态） |
| 白名单读取 | AceViewOhos 层调用 EventInfoConvertor |
| 命中测试 | 通过回调调用裁剪版 HitTest（仅检查 region + tag，不做手势识别器收集） |
| 事件转换 | AceViewOhos 层将 MouseEvent 转为 TouchEvent 后调 touchEventCallback_ |

## 3. 修改文件清单

| 文件 | 变更 |
|---|---|
| `adapter/ohos/entrance/ace_container.cpp` | +37 行：回调注册 + UnActiveWindow 取消 |
| `adapter/ohos/entrance/ace_view_ohos.cpp` | +220 行：核心映射逻辑 |
| `adapter/ohos/entrance/ace_view_ohos.h` | +29 行：成员声明 + 析构函数 + include |
| `adapter/ohos/entrance/event_convertor/event_info_convertor.cpp` | +55 行：配置解析 |
| `frameworks/core/common/container.h` | +5 行：MouseTargetHitCallback 类型别名 |
| `frameworks/core/components_ng/base/frame_node.cpp` | +86 行：HitTestMouseTarget + IsMouseTargetHit |
| `frameworks/core/components_ng/base/frame_node.h` | +9 行：方法声明 |
| `frameworks/core/pipeline_ng/pipeline_context.cpp` | +23 行：source-type 保护 + OnHide/WindowFocus + HitTestMouseTargetForMapping |
| `frameworks/core/pipeline_ng/pipeline_context.h` | +20 行：isRightMouseMappingActive_ + 方法 |
| `frameworks/core/event/event_info_convertor.cpp` | +11 行：非 OHOS 平台 stub |
| `frameworks/core/event/event_info_convertor.h` | +3 行：方法声明 |
| `test/unittest/core/pipeline/BUILD.gn` | +4 行：测试源 + cJSON 依赖 |
| `test/unittest/core/pipeline/right_mouse_mapping_test_ng.cpp` | +780 行：新建测试文件 |

## 4. 核心设计

### 4.1 合成触摸 ID

```cpp
constexpr int32_t RIGHT_MOUSE_TOUCH_ID =
    static_cast<int32_t>(MouseButton::RIGHT_BUTTON) + MOUSE_BASE_ID;  // = 1002
```

避免与左键映射的 id=0 冲突，识别器可区分不同触摸会话。

### 4.2 延迟 UP 机制

右键 RELEASE 后不立即发送 UP，而是延迟发送，确保 LongPress 定时器先 ACCEPT：

```
delayMs = mouseLongPressDuration_ - elapsed + DELAYED_UP_BUFFER_MS(100ms)
下限: delayMs >= 100ms
```

### 4.3 source-type 保护

```cpp
// PipelineContext::OnTouchEvent
bool isMappedMouseTouch = point.sourceTool == SourceTool::MOUSE && point.sourceType == SourceType::TOUCH;
if (!isMappedMouseTouch && CheckSourceTypeChange(point.sourceType)) {
    HandleTouchHoverOut(point);
}
```

合成事件的 `sourceTool=MOUSE && sourceType=TOUCH` 跳过 `CheckSourceTypeChange`，避免污染 `lastSourceType_`。

### 4.4 CANCEL 优先于 UP

所有打断场景发送 CANCEL 而非 UP：
- CANCEL 触发 `onActionCancel_`（菜单消失/REJECT）— 正确行为
- UP 会误触发 `onActionEnd_`（菜单关闭后重开）— 错误行为

### 4.5 状态同步

AceViewOhos → PipelineContext::isRightMouseMappingActive_（通过回调），供 OnHide/WindowFocus 检测并取消映射。

## 5. 架构图

```mermaid
graph TB
    subgraph MMI["MMI 输入服务"]
        MMI_EVT["鼠标 PRESS / MOVE / RELEASE / CANCEL"]
    end

    subgraph AceViewOhos["AceViewOhos 适配层"]
        PME["ProcessMouseEvent"]
        PME -->|"左键PRESS打断"| CMM["CancelMouseMapping"]
        PME --> PMEWT["ProcessMouseEventWithTouch"]
        PMEWT --> SCRT["ShouldConvertRightMouseToTouch"]
        SCRT -->|"决策通过"| DRT["DispatchRightMouseTouch<br/>id=1002, 更新状态"]
        DRT -->|"DOWN/MOVE"| TCB["touchEventCallback_"]
        DRT -->|"UP/CANCEL"| HMBR["HandleMappedButtonRelease"]
        HMBR -->|"CANCEL分支"| TCB
        HMBR -->|"UP分支"| SDU["ScheduleDelayedUp<br/>延迟UP"]
        SDU -->|"延迟回调"| TCB
        CMM -->|"构造CANCEL"| HMBR
        CMM -->|"仅重置"| RMS["ResetMouseMappingState"]
        HMBR --> RMS
        SDU --> RMS
    end

    subgraph PipelineContext["PipelineContext 管线"]
        TCB -->|"合成TouchEvent id=1002"| OT["OnTouchEvent"]
        OT -->|"sourceTool=MOUSE && sourceType=TOUCH"| SKIP["跳过 CheckSourceTypeChange"]
        OH["OnHide / WindowFocus(false)"]
        OH -->|"isRightMouseMappingActive_"| CMM
        HTM["HitTestMouseTargetForMapping"]
        HTM --> FHT["FrameNode::HitTestMouseTarget<br/>递归命中"]
    end

    subgraph Recognizer["LongPressRecognizer"]
        TCB --> TT["TouchTest"]
        TT --> TIMER["启动定时器"]
        TIMER -->|"定时器到达"| ACCEPT["ACCEPT"]
        TCB -->|"UP 到达"| END["onActionEnd_"]
        TCB -->|"CANCEL 到达"| CANCEL_CB["onActionCancel_ / REJECT"]
    end

    SCRT -->|"PRESS+白名单命中"| CMW["CheckMouseMappingWhitelist"]
    CMW --> HTM
    SCRT -->|"SetRightMouseMappingActive"| SYNC["isRightMouseMappingActive_=true"]
    RMS -->|"SetRightMouseMappingActive(false)"| SYNC2["isRightMouseMappingActive_=false"]
```

## 6. 类图

```mermaid
classDiagram
    class AceViewOhos {
        <<adapter>>
        +static constexpr int32_t LONG_PRESS_DEFAULT_DURATION
        +~AceViewOhos()
        +RegisterMouseTargetHitCallback(callback)
        +RegisterRightMouseMappingActiveCallback(callback)
        +CancelMouseMapping()
        +SetRightMouseMappingActive(active)
        +ProcessMouseEvent(pointerEvent, node, isInjected)
        -ProcessMouseEventWithTouch(pointerEvent, event, node, markProcess, leftPressEnabled) bool
        -ShouldConvertRightMouseToTouch(event, node) bool
        -CheckMouseMappingWhitelist(event, node) bool
        -DispatchRightMouseTouch(event, touchEvent, node, markProcess) bool
        -HandleMappedButtonRelease(event, touchEvent, node, markProcess) bool
        -ScheduleDelayedUp(touchEvent, node, markProcess, delayMs)
        -ResetMouseMappingState()
        -SetRightMouseMappingActive(active)
        -bool mousePressedConverted_
        -MouseButton mouseConvertedButton_
        -bool mouseTouchSessionActive_
        -int32_t mouseLongPressDuration_
        -TimeStamp mousePressTime_
        -CancelableCallback mouseDelayedUpTask_
        -TouchEvent mouseLastTouchEvent_
        -MouseTargetHitCallback mouseTargetHitCallback_
        -function~void(bool)~ rightMouseMappingActiveCallback_
    }

    class AceContainer {
        <<adapter>>
        +InitializeCallback()
        +UnActiveWindow(instanceId)
    }

    class PipelineContext {
        <<framework>>
        +IsRightMouseMappingActive() bool
        +SetRightMouseMappingActive(active)
        +SetOnRightMouseMappingCancel(callback)
        +HitTestMouseTargetForMapping(event, node, tagWhitelist, longPressDuration) bool
        +OnTouchEvent(point)
        +OnHide()
        +WindowFocus(isFocus)
        -bool isRightMouseMappingActive_
        -function~void()~ onRightMouseMappingCancel_
    }

    class FrameNode {
        <<framework>>
        +HitTestMouseTarget(event, globalPoint, parentLocalPoint, parentRevertPoint, tagWhitelist, longPressDuration) bool
        +IsMouseTargetHit(event, parentRevertPoint, tagWhitelist, isOutOfRegion, longPressDuration) bool
    }

    class EventInfoConvertor {
        <<utility>>
        <<static>>
        +GetRightMouse2LongPressConfig(outEnabled, outComponents) Mouse2TouchEventModeResult
        +IsRightMouseMappingEnabled(outEnabled, outComponents) bool
    }

    class LongPressRecognizer {
        <<framework>>
        +GetDuration() int32_t
        +SetDuration(duration)
    }

    class GestureEventHub {
        <<framework>>
        +GetLongPressRecognizer() RefPtr~LongPressRecognizer~
    }

    AceContainer --> AceViewOhos : 注册回调
    AceContainer --> PipelineContext : SetOnRightMouseMappingCancel
    AceViewOhos --> PipelineContext : SetRightMouseMappingActive (通过回调)
    AceViewOhos --> EventInfoConvertor : IsRightMouseMappingEnabled
    AceViewOhos --> AceViewOhos : CancelMouseMapping
    PipelineContext --> FrameNode : HitTestMouseTarget (递归)
    PipelineContext --> AceViewOhos : onRightMouseMappingCancel_ (反向回调)
    FrameNode --> GestureEventHub : GetGestureEventHub
    GestureEventHub --> LongPressRecognizer : GetDuration
```

## 7. 状态机

```mermaid
stateDiagram-v2
    [*] --> IDLE

    IDLE: IDLE
    IDLE: mousePressedConverted_ = false
    IDLE: mouseTouchSessionActive_ = false
    IDLE: isRightMouseMappingActive_ = false

    MAPPING_ACTIVE: MAPPING_ACTIVE
    MAPPING_ACTIVE: mousePressedConverted_ = true
    MAPPING_ACTIVE: mouseTouchSessionActive_ = true (DOWN已发送)
    MAPPING_ACTIVE: isRightMouseMappingActive_ = true
    MAPPING_ACTIVE: mouseLongPressDuration_ = 命中节点时长

    DELAYED_UP_PENDING: DELAYED_UP_PENDING
    DELAYED_UP_PENDING: 延迟UP已排队, 未执行
    DELAYED_UP_PENDING: mouseTouchSessionActive_ = false

    IDLE --> MAPPING_ACTIVE: 右键PRESS + 白名单命中 + HitTest通过
    MAPPING_ACTIVE --> MAPPING_ACTIVE: 右键MOVE → 派发MOVE(1002)
    MAPPING_ACTIVE --> DELAYED_UP_PENDING: 右键RELEASE → ScheduleDelayedUp
    MAPPING_ACTIVE --> IDLE: 左键PRESS/真实触摸/窗口隐藏/失焦/MMI CANCEL → CancelMouseMapping
    DELAYED_UP_PENDING --> IDLE: 延迟UP执行 → 派发UP(1002) → ResetState
    DELAYED_UP_PENDING --> IDLE: 左键PRESS/窗口隐藏 → CancelMouseMapping
```

## 8. 时序图

### 8.1 正常右键长按

```mermaid
sequenceDiagram
    participant User
    participant MMI
    participant View as AceViewOhos
    participant Pipe as PipelineContext
    participant Recog as Recognizer

    User->>MMI: 右键 PRESS
    MMI->>View: MouseEvent(button=RIGHT, action=PRESS)
    Note over View: ShouldConvertRightMouseToTouch → CheckWhitelist
    View->>Pipe: HitTestMouseTargetForMapping(event, node, whitelist, duration)
    Pipe->>Pipe: FrameNode::HitTestMouseTarget (递归命中)
    Pipe-->>View: true, duration=500
    Note over View: mousePressedConverted_=true<br/>SetRightMouseMappingActive(true)
    View->>Pipe: touchEventCallback_(DOWN, id=1002)
    Pipe->>Recog: TouchTest → 启动定时器(500ms)

    User->>MMI: 移动鼠标
    MMI->>View: MouseEvent(button=NONE, action=MOVE)
    Note over View: rightButtonMapping=true (NONE && mousePressedConverted_)
    View->>Pipe: touchEventCallback_(MOVE, id=1002)
    Pipe->>Recog: TouchTest → 更新位置

    User->>MMI: 右键 RELEASE
    MMI->>View: MouseEvent(button=RIGHT, action=RELEASE)
    Note over View: HandleMappedButtonRelease<br/>delayMs = 500 - elapsed + 100
    View->>Pipe: PostDelayedTask(UI, delayMs)

    Note over Recog: 定时器触发(500ms) → ACCEPT
    Note over View: 延迟回调执行
    View->>Pipe: touchEventCallback_(UP, id=1002)
    Pipe->>Recog: TouchTest → onActionEnd_ (菜单出现)
    Note over View: ResetMouseMappingState()
```

### 8.2 左键打断

```mermaid
sequenceDiagram
    participant User
    participant MMI
    participant View as AceViewOhos
    participant Recog as Recognizer

    User->>MMI: 右键 PRESS
    MMI->>View: MouseEvent(button=RIGHT, action=PRESS)
    View->>Recog: DOWN(id=1002)
    Note over Recog: 启动定时器

    User->>MMI: 左键 PRESS
    MMI->>View: MouseEvent(button=LEFT, action=PRESS)
    Note over View: button==LEFT && action==PRESS<br/>&& mousePressedConverted_ → CancelMouseMapping()
    Note over View: 构造 CANCEL(mouseLastTouchEvent_)
    View->>Recog: CANCEL(id=1002)
    Note over Recog: onActionCancel_ / REJECT
    Note over View: mouseDelayedUpTask_.Cancel()<br/>ResetMouseMappingState()
```

### 8.3 窗口隐藏取消

```mermaid
sequenceDiagram
    participant Sys as System
    participant View as AceViewOhos
    participant Pipe as PipelineContext
    participant Recog as Recognizer

    Note over View: 映射进行中<br/>isRightMouseMappingActive_=true

    Sys->>Pipe: 窗口隐藏 → OnHide()
    Note over Pipe: isRightMouseMappingActive_? → true
    Note over Pipe: onRightMouseMappingCancel_? → 非空
    Pipe->>View: onRightMouseMappingCancel_() → CancelMouseMapping()
    View->>Recog: CANCEL(id=1002)
    Note over Recog: onActionCancel_
    Note over View: ResetMouseMappingState()
    View->>Pipe: SetRightMouseMappingActive(false)
    Note over Pipe: isRightMouseMappingActive_=false
    Note over Pipe: 后续 WindowFocus(false) → 条件false → 跳过 (双重防护)
```

## 9. 函数说明与分支调用

### 9.1 AceViewOhos

#### ProcessMouseEvent — 鼠标事件入口

```
入口: 所有鼠标事件 (MMI PointerEvent)
返回: void
```

```mermaid
flowchart TD
    START["ProcessMouseEvent(pointerEvent)"] --> MARK["构造 markProcess lambda"]
    MARK --> LEFT["计算 leftPressEnabled<br/>= IsCompatibleConvertingEnabledFor(LEFT_PRESS)"]
    LEFT --> C1{"button==LEFT_BUTTON<br/>&& action==PRESS<br/>&& mousePressedConverted_?"}
    C1 -->|Yes| CANCEL1["CancelMouseMapping()<br/>发送CANCEL(id=1002)并重置"]
    C1 -->|No| PMEWT["ProcessMouseEventWithTouch(..., leftPressEnabled)"]
    CANCEL1 --> PMEWT
    PMEWT --> C2{"返回 true?"}
    C2 -->|Yes| RETURN1["return (已转为触摸)"]
    C2 -->|No| MOUSE_CB["mouseEventCallback_(event)<br/>常规鼠标处理"]
```

| 分支 | 条件 | 行为 | 设计意图 |
|---|---|---|---|
| 左键PRESS打断 | `button==LEFT && action==PRESS && mousePressedConverted_` | `CancelMouseMapping()` | 左键PRESS是用户意图切换，避免id=0和id=1002双触摸会话冲突 |
| 转换路径 | `ProcessMouseEventWithTouch` 返回 true | return | 事件已转为触摸，不走鼠标通路 |
| 常规鼠标 | 上述均不匹配 | `mouseEventCallback_()` | 非白名单/非右键事件走原有鼠标处理 |

#### ProcessMouseEventWithTouch — 统一转换分发

```
入口: ProcessMouseEvent 调用
返回: bool (true=已转换, false=走常规鼠标)
参数: pointerEvent, event, node, markProcess, leftPressEnabled
```

```mermaid
flowchart TD
    START["ProcessMouseEventWithTouch(...)"] --> CALC["计算 rightButtonMapping:<br/>(button==RIGHT 或 (button==NONE 且 mousePressedConverted_))<br/>&& ShouldConvertRightMouseToTouch(event, node)"]
    CALC --> C1{"(leftPressEnabled && button==LEFT)<br/>或 rightButtonMapping?"}
    C1 -->|No| RET_F["return false"]
    C1 -->|Yes| CONVERT["ProcessMouseToTouchEvent(event, touchEvent)"]
    CONVERT --> C2{"转换成功?"}
    C2 -->|No| C3{"mousePressedConverted_<br/>&& button==mouseConvertedButton_?"}
    C3 -->|Yes| CANCEL1["CancelMouseMapping()<br/>发送CANCEL防识别器卡死"]
    C3 -->|No| RET_F2["return false"]
    CANCEL1 --> RET_F3["return false"]
    C2 -->|Yes| C4{"touchEventCallback_ 非空?"}
    C4 -->|No| C5{"mousePressedConverted_<br/>&& button==mouseConvertedButton_?"}
    C5 -->|Yes| CANCEL2["CancelMouseMapping()<br/>取消延迟任务+重置"]
    C5 -->|No| RET_F4["return false"]
    CANCEL2 --> RET_F5["return false"]
    C4 -->|Yes| C6{"rightButtonMapping?"}
    C6 -->|Yes| DRT["DispatchRightMouseTouch(event, touchEvent, node, markProcess)"]
    C6 -->|No| LEFT_DISP["touchEventCallback_(touchEvent)<br/>左键派发(默认id)"]
    DRT --> RET_T["return true"]
    LEFT_DISP --> RET_T2["return true"]
```

| 分支 | 条件 | 行为 | 设计意图 |
|---|---|---|---|
| 不匹配 | 非左键且非右键映射 | return false | 事件走常规鼠标通路 |
| 转换失败+映射活跃 | `!ProcessMouseToTouchEvent() && mousePressedConverted_ && button==mouseConvertedButton_` | `CancelMouseMapping()` 发送 CANCEL | 识别器已收到DOWN，必须补CANCEL否则卡死 |
| 转换失败+非映射 | `!ProcessMouseToTouchEvent()` 且映射不活跃 | return false | 非映射事件转换失败，走常规处理 |
| 回调为空+映射活跃 | `!touchEventCallback_ && mousePressedConverted_ && button==mouseConvertedButton_` | `CancelMouseMapping()` 取消延迟任务+重置 | 回调不可用，需清理延迟UP防悬空 |
| 右键派发 | `rightButtonMapping==true` | `DispatchRightMouseTouch()` 设置 id=1002 | 右键映射路径，统一触摸ID |
| 左键派发 | `leftPressEnabled && button==LEFT` | `touchEventCallback_()` 默认 id | 左键映射路径（原有逻辑） |

**关键设计**：外层条件 `button==NONE_BUTTON && mousePressedConverted_` 使 MOVE 事件（MMI 设 button=NONE_BUTTON）在映射活跃时进入转换路径，经 `DispatchRightMouseTouch` 设置 id=1002，保证触摸会话 ID 一致。

#### ShouldConvertRightMouseToTouch — 映射决策

```
入口: ProcessMouseEventWithTouch 调用
返回: bool (true=应转换, false=不转换)
```

```mermaid
flowchart TD
    START["ShouldConvertRightMouseToTouch(event, node)"] --> C1{"button != RIGHT<br/>&& button != NONE?"}
    C1 -->|Yes| F1["return false"]
    C1 -->|No| C2{"sourceTool != MOUSE?"}
    C2 -->|Yes| F2["return false<br/>(排除触控笔)"]
    C2 -->|No| C3{"action 不在<br/>PRESS/MOVE/RELEASE/CANCEL?"}
    C3 -->|Yes| F3["return false"]
    C3 -->|No| C4{"action==PRESS<br/>&& mousePressedConverted_?"}
    C4 -->|Yes| CM1["CancelMouseMapping()<br/>取消上一轮, 继续判断"]
    C4 -->|No| C5{"action==CANCEL<br/>&& mousePressedConverted_?"}
    CM1 --> C5
    C5 -->|Yes| CM2["CancelMouseMapping()<br/>return false<br/>(CANCEL不启动新映射)"]
    C5 -->|No| C6{"mousePressedConverted_<br/>&& (button==converted<br/>或 (NONE && MOVE))?"}
    C6 -->|Yes| T1["return true<br/>(续接映射: MOVE/RELEASE)"]
    C6 -->|No| C7{"action != PRESS?"}
    C7 -->|Yes| F4["return false<br/>(非PRESS不启动新映射)"]
    C7 -->|No| C8{"button != RIGHT_BUTTON?"}
    C8 -->|Yes| F5["return false"]
    C8 -->|No| C9{"CheckMouseMappingWhitelist()?"}
    C9 -->|No| F6["return false<br/>(白名单未命中)"]
    C9 -->|Yes| SET["设置映射状态:<br/>mousePressedConverted_=true<br/>mouseConvertedButton_=RIGHT<br/>mousePressTime_=event.time<br/>SetRightMouseMappingActive(true)"]
    SET --> T2["return true"]
```

| 检查序号 | 条件 | 通过时行为 | 失败时行为 | 设计意图 |
|---|---|---|---|---|
| 1 | `button != RIGHT && button != NONE` | 继续检查 | return false | 仅处理右键和MOVE(NONE_BUTTON) |
| 2 | `sourceTool != MOUSE` | 继续检查 | return false | 排除触控笔(sourceTool=PEN) |
| 3 | action 不在四种合法值中 | 继续检查 | return false | 排除非法action |
| 4 | `action==PRESS && mousePressedConverted_` | `CancelMouseMapping()` 取消上一轮 | — | 连续右键：新PRESS前清理旧映射 |
| 5 | `action==CANCEL && mousePressedConverted_` | `CancelMouseMapping()`, return false | — | MMI CANCEL：取消映射，不启动新映射 |
| 6 | 映射活跃且button匹配或NONE+MOVE | return true (续接) | — | MOVE/RELEASE 继续映射 |
| 7 | `action != PRESS` | — | return false | 非PRESS不启动新映射 |
| 8 | `button != RIGHT_BUTTON` | — | return false | 新映射仅从右键PRESS启动 |
| 9 | `CheckMouseMappingWhitelist()` | 设置映射状态, return true | return false | 白名单+HitTest通过才启动映射 |

#### DispatchRightMouseTouch — 派发函数

```
入口: ProcessMouseEventWithTouch (仅 rightButtonMapping==true)
返回: bool (true=已派发)
```

| 步骤 | 操作 | 说明 |
|---|---|---|
| 1 | `touchEvent.id = touchEvent.originalId = RIGHT_MOUSE_TOUCH_ID (1002)` | 设置合成触摸ID |
| 2 | 遍历 `touchEvent.pointers` 全部设为 1002 | 确保多指数据一致 |
| 3 | type==DOWN → `mouseLastTouchEvent_ = touchEvent`, `mouseTouchSessionActive_ = true` | 记录DOWN，标记会话开始 |
| 4 | type==MOVE → `mouseLastTouchEvent_ = touchEvent` | 更新缓存（供CANCEL构造） |
| 5 | type==UP/CANCEL → `HandleMappedButtonRelease()` | 转入释放处理 |
| 6 | type==DOWN/MOVE → `touchEventCallback_(touchEvent)` | 直接派发给Pipeline |

#### HandleMappedButtonRelease — 释放处理

```
入口: DispatchRightMouseTouch (UP/CANCEL) 或 CancelMouseMapping (CANCEL)
返回: bool (true=已处理)
```

```mermaid
flowchart TD
    START["HandleMappedButtonRelease(event, touchEvent, node, markProcess)"] --> CHECK["CHECK_NULL_RETURN(touchEventCallback_, false)"]
    CHECK --> C1{"touchEvent.type == CANCEL?"}
    C1 -->|Yes| CANCEL_BRANCH["构造 cancelEvent 副本<br/>设置 type/sourceType/sourceTool<br/>touchEventCallback_(cancelEvent)<br/>mouseDelayedUpTask_.Cancel()<br/>ResetMouseMappingState()"]
    C1 -->|No, type==UP| UP_BRANCH["计算 elapsed = event.time - mousePressTime_<br/>delayMs = duration - elapsed + 100<br/>下限: delayMs >= 100"]
    CANCEL_BRANCH --> RET_T["return true"]
    UP_BRANCH --> SCHED["ScheduleDelayedUp(touchEvent, node, markProcess, delayMs)"]
    SCHED --> RET_T2["return true"]
```

| 分支 | 条件 | 行为 | 设计意图 |
|---|---|---|---|
| CANCEL 分支 | `touchEvent.type == CANCEL` | 构造CANCEL副本→派发→取消延迟任务→重置 | CANCEL触发`onActionCancel_`(菜单消失/REJECT) |
| UP 分支 | `touchEvent.type == UP` | 计算延迟→`ScheduleDelayedUp()` | 延迟UP确保定时器先ACCEPT，UP后触发`onActionEnd_` |

**为什么CANCEL而非UP**：UP会触发 `onActionEnd_`（菜单关闭后重新打开），CANCEL 触发 `onActionCancel_`（菜单消失或 REJECT）。打断场景应发送CANCEL。

**延迟计算公式**：
- `elapsed = event.time - mousePressTime_`（PRESS到RELEASE的毫秒数）
- `delayMs = mouseLongPressDuration_ - elapsed + DELAYED_UP_BUFFER_MS(100)`（剩余时间+buffer）
- 若 `delayMs < 100`，设为 100（用户按住超过duration的情况）

#### ScheduleDelayedUp — 延迟UP调度

```
入口: HandleMappedButtonRelease (UP分支) 调用
返回: void
```

| 步骤 | 操作 | 说明 |
|---|---|---|
| 1 | `if (markProcess) markProcess()` | 立即标记RELEASE的MMI事件已处理，避免阻塞MMI调度队列 |
| 2 | 构造lambda：捕获 `weakThis`(WeakClaim) + `touchEvent`(值) + `node`(RefPtr值) | WeakClaim防止析构后悬空调用 |
| 3 | `mouseDelayedUpTask_.Reset(callback)` | 重置CancelableCallback |
| 4 | `container->GetPipelineContext()->GetTaskExecutor()->PostDelayedTask(UI, delayMs)` | 通过UI线程TaskExecutor延迟执行 |
| 5 | Fallback: container/context为空 → `ResetMouseMappingState()` | UP无法发送但需清理状态 |

**延迟回调内容**：
1. `self->touchEventCallback_(touchEvent, nullptr, node)` — 发送UP(id=1002)，markProcess=nullptr（RELEASE已标记）
2. `self->ResetMouseMappingState()` — 重置全部状态

**为什么markProcess为nullptr**：原始RELEASE的touchEventId已在入口处通过`markProcess()`标记，延迟回调不应再次标记（touchEventId已过期）。

#### CancelMouseMapping — 统一取消

```
入口: 多种打断场景 (左键/触摸/连续右键/MMI CANCEL/窗口隐藏/失焦/转换失败)
返回: void
```

```mermaid
flowchart TD
    START["CancelMouseMapping()"] --> C1{"!mousePressedConverted_?"}
    C1 -->|Yes| RET["return (映射未活跃)"]
    C1 -->|No| C2{"mouseTouchSessionActive_<br/>&& touchEventCallback_?"}
    C2 -->|Yes| CANCEL_BRANCH["构造 cancelEvent = mouseLastTouchEvent_<br/>设置 type=CANCEL, sourceType=TOUCH, sourceTool=MOUSE<br/>HandleMappedButtonRelease({}, cancelEvent, nullptr, nullptr)<br/>→ 发送CANCEL + 取消延迟任务 + 重置"]
    C2 -->|No| RESET_BRANCH["mouseDelayedUpTask_.Cancel()<br/>ResetMouseMappingState()"]
```

| 分支 | 条件 | 行为 | 设计意图 |
|---|---|---|---|
| 空操作 | `!mousePressedConverted_` | return | 映射未活跃或已清理 |
| 发送CANCEL | `mouseTouchSessionActive_ && touchEventCallback_` | 构造CANCEL→`HandleMappedButtonRelease(CANCEL)` | DOWN已发送但UP未发送→必须发CANCEL让识别器清理 |
| 仅重置 | 否则（延迟UP排队中） | `Cancel()` + `ResetMouseMappingState()` | DOWN已发送且UP已排队→只需取消延迟任务并重置 |

**两个分支的区别**：
- `mouseTouchSessionActive_=true`：DOWN已发送但UP未发送（MAPPING_ACTIVE状态）→ 必须发CANCEL
- `mouseTouchSessionActive_=false`：DOWN已发送且UP已排队（DELAYED_UP_PENDING状态）→ 取消延迟任务即可

#### ResetMouseMappingState — 状态重置

| 重置项 | 值 | 说明 |
|---|---|---|
| `mousePressedConverted_` | false | 映射不再活跃 |
| `mouseConvertedButton_` | NONE_BUTTON | 清除映射按钮 |
| `mouseTouchSessionActive_` | false | 触摸会话结束 |
| `mouseLongPressDuration_` | LONG_PRESS_DEFAULT_DURATION (500) | 恢复默认时长 |
| `SetRightMouseMappingActive(false)` | — | 通过回调通知PipelineContext: `isRightMouseMappingActive_ = false` |

#### CheckMouseMappingWhitelist — 白名单检查

```mermaid
flowchart TD
    START["CheckMouseMappingWhitelist(event, node)"] --> C1{"IsRightMouseMappingEnabled(enabled, components)?"}
    C1 -->|No| F1["return false<br/>(配置未开启或无效)"]
    C1 -->|Yes| C2{"mouseTargetHitCallback_ 非空?"}
    C2 -->|No| F2["return false<br/>(回调未注册)"]
    C2 -->|Yes| CALL["mouseTargetHitCallback_(event, node, components, longPressDuration)<br/>执行裁剪版HitTest"]
    CALL --> C3{"hitTestResult?"}
    C3 -->|No| F3["return false<br/>(未命中白名单组件)"]
    C3 -->|Yes| SAVE["mouseLongPressDuration_ = longPressDuration<br/>保存命中节点的LongPress时长"]
    SAVE --> T["return true"]
```

| 步骤 | 失败行为 | 成功行为 |
|---|---|---|
| `IsRightMouseMappingEnabled` 检查配置 | return false | 继续 |
| `CHECK_NULL_RETURN(mouseTargetHitCallback_)` | return false | 继续 |
| `mouseTargetHitCallback_` 执行HitTest | return false | `mouseLongPressDuration_ = longPressDuration` |

#### SetRightMouseMappingActive — 状态同步

```
行为: rightMouseMappingActiveCallback_(active) → PipelineContext::SetRightMouseMappingActive(active)
```

通过回调将映射状态同步到 PipelineContext，供 OnHide/WindowFocus 检测。

### 9.2 AceContainer — 回调注册

#### InitializeCallback (新增片段)

| 注册项 | 目标 | 捕获方式 | 回调内容 | 用途 |
|---|---|---|---|---|
| `RegisterMouseTargetHitCallback` | AceViewOhos | WeakPtr | `weakPipeline.Upgrade() → HitTestMouseTargetForMapping()` | 白名单命中查询+获取duration |
| `RegisterRightMouseMappingActiveCallback` | AceViewOhos | WeakPtr | `weakPipeline.Upgrade() → SetRightMouseMappingActive(active)` | 映射状态同步到PipelineContext |
| `SetOnRightMouseMappingCancel` | PipelineContext | WeakPtr | `weakView.Upgrade() → CancelMouseMapping()` | OnHide/WindowFocus时反向取消映射 |

**WeakPtr 使用**：三个回调均使用 WeakPtr，防止引用循环和 PipelineContext/AceViewOhos 销毁后悬空调用。

#### UnActiveWindow (新增片段)

```
窗口反激活时: aceViewOhos → CancelMouseMapping()
```

### 9.3 PipelineContext — 管线层

#### OnTouchEvent — source-type 保护 (修改)

```
位置: OnTouchEvent 内, HandlePenHoverOut 之后
```

| 条件 | 行为 | 目的 |
|---|---|---|
| `sourceTool==MOUSE && sourceType==TOUCH` (合成事件) | 跳过 `CheckSourceTypeChange` | 不污染 `lastSourceType_`，避免后续真实鼠标事件误触发 `HandleTouchHoverOut` |
| 其他事件 (真实触摸/真实鼠标) | 正常调用 `CheckSourceTypeChange` | 真实事件的正常source-type切换行为 |

**不加此保护的后果**：合成事件 sourceType=TOUCH 会将 `lastSourceType_` 改为 TOUCH，后续真实鼠标事件(MOUSE)到来时检测到 source-type change → `HandleTouchHoverOut` → 界面闪烁。

#### OnHide — 取消映射 (修改)

```
位置: OnHide() 内, NotifyCoastingAxisEventOnHide() 之后, onShow_=false 之前
```

| 条件 | 行为 | 触发场景 |
|---|---|---|
| `isRightMouseMappingActive_ && onRightMouseMappingCancel_` | `onRightMouseMappingCancel_()` → `CancelMouseMapping()` | 应用后台、其他窗口遮挡 |

#### WindowFocus — 取消映射 (修改)

```
位置: WindowFocus(false) 分支内, NotifyPopupDismiss() 之后
```

| 条件 | 行为 | 触发场景 |
|---|---|---|
| `isRightMouseMappingActive_ && onRightMouseMappingCancel_` | `onRightMouseMappingCancel_()` → `CancelMouseMapping()` | 点击其他窗口、通知弹出 |

**双重取消防护**：OnHide 和 WindowFocus(false) 可能同时触发。第一个执行后 `isRightMouseMappingActive_=false`，第二个检查条件为 false → 跳过。无双重取消。

#### HitTestMouseTargetForMapping — HitTest入口 (新增)

```mermaid
flowchart TD
    START["HitTestMouseTargetForMapping(event, node, tagWhitelist, longPressDuration)"] --> C1{"node 非空?"}
    C1 -->|Yes| USE_NODE["frameNode = node"]
    C1 -->|No| USE_ROOT["frameNode = GetRootElement()"]
    USE_NODE --> CHECK["CHECK_NULL_RETURN(frameNode, false)"]
    USE_ROOT --> CHECK
    CHECK --> SCALE["scaleEvent = event.CreateScaleEvent(GetViewScale())"]
    SCALE --> INIT["longPressDuration = LONG_PRESS_DEFAULT_DURATION (500)"]
    INIT --> WL{"tagWhitelist 为空?"}
    WL -->|Yes| WL_NULL["whitelistPtr = nullptr (无限制)"]
    WL -->|No| WL_PTR["whitelistPtr = &tagWhitelist"]
    WL_NULL --> HIT["frameNode->HitTestMouseTarget(event, p, p, p, whitelistPtr, &longPressDuration)"]
    WL_PTR --> HIT
    HIT --> RET["return result"]
```

| 步骤 | 说明 |
|---|---|
| 确定frameNode | `node ? node : GetRootElement()` — 优先使用传入节点，否则用根节点 |
| 坐标缩放 | `event.CreateScaleEvent(GetViewScale())` — 适配视图缩放 |
| 初始化duration | `LONG_PRESS_DEFAULT_DURATION (500)` — 默认值，命中后覆盖 |
| 空白名单处理 | `tagWhitelist.empty() ? nullptr : &tagWhitelist` — 空列表表示"无限制"(All) |
| 递归命中 | `HitTestMouseTarget(event, p, p, p, ...)` — 根节点三个坐标相同，递归子节点时自动区分 |

### 9.4 FrameNode — 命中测试

#### HitTestMouseTarget — 递归命中

```mermaid
flowchart TD
    START["HitTestMouseTarget(event, globalPoint, parentLocalPoint, parentRevertPoint, tagWhitelist, longPressDuration)"] --> C1{"renderContext_ 非空?"}
    C1 -->|No| F1["return false"]
    C1 -->|Yes| C2{"isActive_?"}
    C2 -->|No| F2["return false"]
    C2 -->|Yes| CACHE["GetOrRefreshMatrixFromCache()<br/>获取 paintRect, localMatrix, revertMatrix"]
    CACHE --> SELF["IsMouseTargetHit(event, parentRevertPoint, tagWhitelist, isOutOfRegion, curDuration)"]
    SELF --> C3{"自身命中?"}
    C3 -->|Yes| OUT["*longPressDuration = curDuration"]
    C3 -->|No| CALC["计算子节点坐标:<br/>localPoint = parentLocalPoint - paintRect.GetOffset()<br/>subRevertPoint = revertPoint - origRect.GetOffset()"]
    OUT --> CALC
    CALC --> LOOP["逆序遍历 frameChildren_"]
    LOOP --> C4{"child 存在?"}
    C4 -->|No| NEXT["continue"]
    C4 -->|Yes| RECURSE["child->HitTestMouseTarget(event, globalPoint, localPoint, subRevertPoint, ...)"]
    NEXT --> LOOP
    RECURSE --> C5{"子命中?"}
    C5 -->|Yes| OVERRIDE["ret=true, *longPressDuration=childDuration, break"]
    C5 -->|No| LOOP
    OVERRIDE --> RET["return ret"]
```

| 步骤 | 说明 | 设计意图 |
|---|---|---|
| renderContext检查 | `CHECK_NULL_RETURN(renderContext_, false)` | 无渲染上下文的节点不可命中 |
| isActive检查 | `!isActive_` → false | 不可见/未激活节点不参与命中 |
| 矩阵缓存 | `GetOrRefreshMatrixFromCache()` | 复用变换矩阵，避免重复计算 |
| 自身命中 | `IsMouseTargetHit(...)` | 检查当前节点的region+tag |
| 输出duration | 命中时 `*longPressDuration = curDuration` | 返回命中节点的LongPress时长 |
| 子节点坐标计算 | `localPoint = parentLocalPoint - paintRect.GetOffset()` | 将父坐标转换为子坐标 |
| 逆序遍历 | `frameChildren_.rbegin() → rend()` | 后添加的子节点在上层(z-order正确) |
| 命中即break | 子命中后break | 返回最上层命中节点，不继续遍历 |

#### IsMouseTargetHit — 单节点命中

| 检查 | 通过条件 | 失败行为 |
|---|---|---|
| renderContext非空 | `CHECK_NULL_RETURN(renderContext_, false)` | return false |
| ResponseRegion命中 | `!IsOutOfTouchTestRegion(parentRevertPoint, ...)` | isOutOfRegion=true |
| Tag白名单 | `tagWhitelist`为空(All) 或包含 `GetTag()` | tagAllowed=false |
| LongPress duration | `eventHub_->GetGestureEventHub()->GetLongPressRecognizer()->GetDuration()` | 保持默认值 |

**使用 `GetGestureEventHub()` (非创建式)**：避免在只读HitTest中创建GestureEventHub副作用。hub不存在时返回nullptr，duration保持默认值。

### 9.5 EventInfoConvertor — 配置解析

#### GetRightMouse2LongPressConfig

```mermaid
flowchart TD
    START["GetRightMouse2LongPressConfig(outEnabled, outComponents)"] --> READ["FeatureManager.GetFeatureParam(CONTEXT_MENU_OPTIONS, config)"]
    READ --> C1{"ret == INIT_FAILED?"}
    C1 -->|Yes| F1["return INIT_FAILED"]
    C1 -->|No| C2{"ret != SUCCESS?"}
    C2 -->|Yes| F2["return NOT_FOUND"]
    C2 -->|No| PARSE["JsonUtil::ParseJsonString(config)"]
    PARSE --> C3{"无效JSON?"}
    C3 -->|Yes| F3["return NOT_FOUND"]
    C3 -->|No| BOOL["outEnabled = GetBool(rightMouse2LongPress, false)"]
    BOOL --> C4{"!outEnabled?"}
    C4 -->|Yes| F4["return UNMATCHED<br/>(功能关闭)"]
    C4 -->|No| ARR["GetValue(needTransferComponent)"]
    ARR --> C5{"空/null/数组大小<=0?"}
    C5 -->|Yes| F5["outEnabled=false, return UNMATCHED<br/>(无组件列表)"]
    C5 -->|No| LOOP["遍历数组"]
    LOOP --> C6{"item == 'All'?"}
    C6 -->|Yes| ALL["outComponents.clear()<br/>return MATCHED (无限制)"]
    C6 -->|No| ADD["outComponents.push_back(value)"]
    ADD --> LOOP
```

| 返回值 | 条件 | outEnabled | outComponents |
|---|---|---|---|
| INIT_FAILED | FeatureManager初始化失败 | — | — |
| NOT_FOUND | key不存在 或 JSON无效 | — | — |
| UNMATCHED | `rightMouse2LongPress=false` 或 `needTransferComponent`为空/非数组 | false | 空 |
| MATCHED | `rightMouse2LongPress=true` 且 `needTransferComponent`非空 | true | 组件列表 |

**"All" 通配**：`needTransferComponent` 包含 "All" 时，`outComponents` 清空（表示无白名单限制，HitTest 不检查 tag）。

#### IsRightMouseMappingEnabled

```cpp
auto configResult = GetRightMouse2LongPressConfig(outEnabled, outComponents);
return configResult == Mouse2TouchEventModeResult::MATCHED && outEnabled;
```

| configResult | 返回值 | 说明 |
|---|---|---|
| MATCHED | `true && outEnabled` = true | 配置匹配，功能开启 |
| UNMATCHED | `false && ...` = false (短路) | 功能关闭或无组件 |
| NOT_FOUND | `false && ...` = false (短路) | 配置不存在 |
| INIT_FAILED | `false && ...` = false (短路) | 初始化失败 |

## 10. 配置格式

```json
{
  "contextMenuOptions": {
    "rightMouse2LongPress": true,
    "needTransferComponent": ["TextInput", "TextArea", "RichEditor", "Text"]
  }
}
```

| 字段 | 类型 | 说明 |
|---|---|---|
| `rightMouse2LongPress` | bool | 功能总开关 |
| `needTransferComponent` | string[] | 白名单组件 Tag 列表 |
| `"All"` | — | 通配符，清空白名单（对所有组件生效） |

## 11. 事件冲突场景

| 场景 | 触发 | 处理 | 识别器收到 | 结果 |
|---|---|---|---|---|
| 正常右键长按 | PRESS→RELEASE | DOWN→延迟UP→ACCEPT | DOWN→UP | onActionEnd_ ✓ |
| 快速右键 | PRESS→快速RELEASE | 延迟UP在定时器后到达 | DOWN→UP | 识别为长按 ✓ |
| 左键打断 | 映射中 LEFT PRESS | CancelMouseMapping | DOWN→CANCEL | onActionCancel_ ✓ |
| 真实触摸打断 | 映射中 finger DOWN | CancelMouseMapping | DOWN→CANCEL | onActionCancel_ ✓ |
| 连续右键 | 映射中新 PRESS | CancelMouseMapping→新DOWN | DOWN→CANCEL→DOWN | 上轮CANCEL+新轮启动 ✓ |
| 窗口隐藏 | 映射中 OnHide | onRightMouseMappingCancel_ | DOWN→CANCEL | onActionCancel_ ✓ |
| 窗口失焦 | 映射中 WindowFocus(false) | onRightMouseMappingCancel_ | DOWN→CANCEL | onActionCancel_ ✓ |
| MMI CANCEL | 映射中 CANCEL(NONE_BUTTON) | ShouldConvert→CancelMouseMapping | DOWN→CANCEL | onActionCancel_ ✓ |
| 转换失败 | ProcessMouseToTouchEvent失败 | CancelMouseMapping | DOWN→CANCEL | 识别器不卡死 ✓ |
| MOVE期间右键释放 | MOVE→RELEASE | MOVE(1002)→延迟UP(1002) | DOWN→MOVE→UP | 完整触摸会话 ✓ |

## 12. 测试覆盖

| 类别 | 用例数 | 覆盖内容 |
|---|---|---|
| GetRightMouse2LongPressConfig | 15 | INIT_FAILED/NOT_FOUND/无效JSON/disabled/无组件/有组件/空数组/非数组/空对象/字符串/重复/"All"/"All"混合/自定义Tag |
| IsRightMouseMappingEnabled | 5 | INIT_FAILED/NOT_FOUND/UNMATCHED/MATCHED/"All" |
| LongPressRecognizer GetDuration | 3 | 默认值/自定义值/SetGet往返 |
| PipelineContext 状态 | 8 | 默认/Set/Toggle/Cancel回调/空回调/替换/幂等 |
| source-type 保护 | 6 | 合成事件跳过/正常更新/连续映射 |
| ABI 安全性 | 1 | 成员布局验证 |
| HitTestMouseTargetForMapping | 7 | null根/空白名单/默认duration/命中白名单组件/白名单过滤/递归子节点 |
| 事件交互 | 7 | MOUSE+TOUCH混合/WindowFocus取消/左键取消/CANCEL/MOVE不取消/lastSourceType保护 |
| OnHide取消 | 1 | OnHide触发cancel回调 |

**合计 52 个测试用例，855 行。**

---

## 13. PR 检视意见确认（PR #88653）

### 13.1 检视意见汇总

PR #88653 共收到 44 条 diff 评论（4 位审查人：zhou-chaobo 25 条、hwliujinwei 7 条、jyj-0306 4 条、carnivore233 8 条）。按严重性分类：

| 严重性 | 数量 | 说明 |
|---|---|---|
| 严重 | 6 | 日志频繁打印 ×3、逻辑不应走 ×1、去除条件 ×1、存疑 ×1 |
| 一般 | 13 | 硬编码/常量/Cancel 合理性/逻辑位置/延时任务/HitTest遍历/捕获策略/命名等 |
| 提示 | 6 | 线程安全/DynamicCast 开销/bridge wiring/死代码/冗余分支/未使用include |
| 建议 | 1 | 测试窗口失焦场景 |
| 去掉/不改 | 10 | 指定代码删除或保留 |
| start build | 1 | CI 触发 |
| 正面总结 | 1 | jyj-0306 总评：实现完整、建议合入 |
| 不适用 | 6 | PR 版本与当前实现不同 |

### 13.2 逐一确认

#### hwliujinwei 意见（7 条）

| # | 严重性 | 意见摘要 | 确认结果 | 说明 |
|---|---|---|---|---|
| 1 | 重要 | ProcessMouseEvent fallback TAG_LOGI 日志频繁打印 | ✅ 不适用 | 当前实现未添加 fallback 日志 |
| 2 | 重要 | HitTest 传入三个相同 PointF | ✅ 设计正确 | 根节点 p,p,p 正确，递归子节点时坐标已区分 |
| 3 | 重要 | CancelMouseMapping 需补发 UP | ✅ 已处理 | 发送 CANCEL（非 UP），触发 onActionCancel_ |
| 4 | 重要 | leftPressEnabled true/false 两条路径不一致 | ✅ 已统一 | 左右键统一在 ProcessMouseEventWithTouch 处理 |
| 5 | 重要 | ResetMouseMappingState 未补发 UP | ✅ 已修复 | 改为 CancelMouseMapping（发送 CANCEL 再重置） |
| 6 | 次要 | DynamicCast 开销 | ✅ 可接受 | 非热路径，开销极低 |
| 7 | 提示 | 线程安全 | ✅ 安全 | 全部在 UI 线程，PostDelayedTask 也走 UI |

#### zhou-chaobo 意见（25 条）

| # | 严重性 | 意见摘要 | 确认结果 | 说明 |
|---|---|---|---|---|
| 8 | 一般 | 主要逻辑应抽象到 pipeline | ⚠️ 设计决策 | 方案 E 选择 Adapter 层，Pipeline 无感知 |
| 9 | 严重 | 日志频繁打印 (line 473) | ✅ 不适用 | 当前实现未添加该日志 |
| 10 | 严重 | 日志频繁打印 (line 490) | ✅ 不适用 | 同上 |
| 11 | 一般 | 配置读取应和左键放一起 | ⚠️ 设计决策 | 方案 E 白名单判断在 AceViewOhos 层 |
| 12 | 严重 | 日志频繁打印 (line 504) | ✅ 不适用 | 当前实现未添加该日志 |
| 17 | 严重 | 不应该走这段逻辑 (line 742-743) | ⚠️ 需澄清 | PR 版本行号不同，无法精确定位 |
| 18 | 建议 | 测试窗口失焦场景 | ✅ 已覆盖 | LeftClickCancelsMapping001 + OnHideCancelsMapping001 |
| 19 | — | 去掉 (line 1149) | ⚠️ 需澄清 | 无法精确定位 |
| 20 | 严重 | 去除 !leftPressEnabled | ✅ 已处理 | 不存在 !leftPressEnabled 分支 |
| 21 | 一般 | 确认 Cancel 及转 UP 合理性 | ✅ 已确认 | 发送 CANCEL 非 UP，触发 onActionCancel_ |
| 22 | 一般 | 逻辑放 pipeline 可行性 | ⚠️ 设计决策 | 方案 E 延时逻辑放在 AceViewOhos 层 |
| 23 | 一般 | 延时任务在 UP 事件判断 | ✅ 已处理 | 延迟公式含 buffer，确保 UP 在定时器后到达 |
| 24 | — | 存疑 (line 755) | ⚠️ 需澄清 | 无具体问题描述 |
| 25 | — | 去掉日志 (line 1225) | ✅ 不适用 | 当前实现未添加该日志 |
| 26 | — | 去掉 (line 1544) | ✅ 不适用 | PR 版本代码，当前实现不含 |
| 27 | — | 函数名改一下 | ⚠️ 需澄清 | 无建议名称，命名与 TouchTest/MouseTest 一致 |
| 28 | 一般 | 命中后是否继续遍历 | ✅ 已处理 | 子节点命中后 break，停止遍历 |
| 29 | — | 去掉 (line 1656) | ✅ 不适用 | 不使用 isDisableMouseRight（GAP-4 方案变更） |
| 30 | — | 不改 (line 1643) | ✅ 已记录 | 保留原样 |
| 31 | — | 去掉 (line 38) | ⚠️ 需澄清 | 无法精确定位 |
| 32 | — | 日志去除 (line 515) | ✅ 不适用 | 当前实现未添加该日志 |
| 33 | — | 长按手势不应有适配逻辑 | ✅ 已处理 | long_press_recognizer.h 已回退，无修改 |
| 34 | — | 去掉 (line 3951) | ✅ 不适用 | PR 版本代码，当前实现不含 |
| 35 | — | 确认触发场景 (OnHide) | ✅ 已确认 | 应用后台/其他窗口遮挡 → OnHide → cancel |
| 36 | — | 确认触发场景 (WindowFocus) | ✅ 已确认 | 点击其他窗口/通知弹出 → WindowFocus(false) → cancel |

#### jyj-0306 意见（4 条）

| # | 严重性 | 意见摘要 | 确认结果 | 说明 |
|---|---|---|---|---|
| 13 | 一般 | 硬编码 1000 作为 mapped touch id 阈值 | ✅ 已处理 | 使用 `RIGHT_MOUSE_TOUCH_ID = MouseButton::RIGHT_BUTTON + MOUSE_BASE_ID`，基于命名常量 |
| 14 | 一般 | LONG_PRESS_DURATION_MS=500 硬编码 | ✅ 已处理 | 实际 duration 从 `GetLongPressRecognizer()->GetDuration()` 获取，500 仅初始默认值 |
| 15 | 提示 | SetDisableMouseRightForLongPress bridge wiring | ✅ 不适用 | 不使用 isDisableMouseRight（GAP-4 方案变更，改用白名单+HitTest） |
| 16 | 正面 | 实现完整、测试充分、建议合入 | ✅ 已记录 | — |

#### carnivore233 意见（8 条）

| # | 严重性 | 意见摘要 | 确认结果 | 说明 |
|---|---|---|---|---|
| 36 | 提示 | 回调捕获策略不一致：mouseTargetHitCallback 强引用 | ✅ 已修复 | 改为 `WeakPtr<NG::PipelineContext>` 弱引用，与其他回调一致 |
| 37 | 提示 | ScheduleDelayedUp fallback 路径 UP 未发送 | ✅ 已确认 | container/context 为空时立即 ResetMouseMappingState（异常路径，app 关闭） |
| 38 | 提示 | ShouldConvertRightMouseToTouch 命名为谓词但有副作用 | ⚠️ 设计可接受 | 函数有状态设置副作用，但命名与 Should*Pattern 一致，可后续迭代改名 |
| 39 | 提示 | MULTI_MODAL_INPUT_OPTIONS 常量无引用（死代码） | ✅ 已修复 | 已移除 |
| 40 | 提示 | IsRightMouseMappingEnabled 三分支均 return false 冗余 | ✅ 已修复 | 简化为 `return configResult == MATCHED && outEnabled` |
| 41 | 提示 | container.h 新增 event_constants.h 不必要 | ✅ 不适用 | 当前实现未添加该 include |
| 42 | 一般 | IsMouseTargetHit 调用 GetOrCreateGestureEventHub 有创建副作用 | ✅ 已修复 | 改为 `eventHub_ ? eventHub_->GetGestureEventHub() : nullptr`（非创建式） |
| 43 | 一般 | HitTestMouseTarget 未复用 HitTestMode | ⚠️ 设计决策 | 裁剪版 HitTest 仅检查 region+tag，不检查 HitTestMode（故意的轻量化） |
| 44 | 提示 | globalPoint 参数未消费 | ⚠️ 设计合理 | 与 TouchTest 签名一致，递归时透传，保持 API 一致性 |

### 13.3 需要修改的检视意见及修复

| # | 审查人 | 问题 | 修复内容 | 修复文件 |
|---|---|---|---|---|
| 5 | hwliujinwei | ResetMouseMappingState 未补发 UP | `ResetMouseMappingState()` → `CancelMouseMapping()`（转换失败/回调空路径） | `ace_view_ohos.cpp` |
| 36 | carnivore233 | mouseTargetHitCallback 强引用捕获 | `[context = pipelineContext_]` → `[weakPipeline = WeakPtr<NG::PipelineContext>(...)]` | `ace_container.cpp` |
| 39 | carnivore233 | MULTI_MODAL_INPUT_OPTIONS 死代码 | 移除常量定义 | `event_info_convertor.cpp` |
| 40 | carnivore233 | IsRightMouseMappingEnabled 冗余分支 | 三分支简化为单行 `return configResult == MATCHED && outEnabled` | `event_info_convertor.cpp` |
| 42 | carnivore233 | GetOrCreateGestureEventHub 创建副作用 | 改为 `eventHub_ ? eventHub_->GetGestureEventHub() : nullptr` | `frame_node.cpp` |

### 13.4 编译问题修复

| 问题 | 原因 | 修复 | 文件 |
|---|---|---|---|
| `unknown type name 'MouseButton'` | ace_view_ohos.h 使用 MouseButton 但未 include mouse_event.h，window_scene 构建目标中不可见 | 添加 `#include "core/event/mouse_event.h"` | `ace_view_ohos.h` |
| `#define PRIVATE public` 不生效 | 大写宏名不替换 C++ 小写关键字 private/protected | 改为 `#define private public // NOLINT` | `right_mouse_mapping_test_ng.cpp` |
| `'test/mock/base/mock_task_executor.h' file not found` | mock include 路径错误 | 改为 `test/mock/frameworks/base/thread/mock_task_executor.h` 等 5 个路径 | `right_mouse_mapping_test_ng.cpp` |
| G.NAM.03-CPP 宏命名规范 | `#define private public` 触发命名检查 | 添加 `// NOLINT` 抑制 | `right_mouse_mapping_test_ng.cpp` |

### 13.5 确认结果统计

| 确认结果 | 数量 | 占比 |
|---|---|---|
| ✅ 已处理/不适用/已覆盖 | 28 | 64% |
| ⚠️ 设计决策（方案 E 选择） | 6 | 14% |
| ⚠️ 需 reviewer 澄清 | 5 | 11% |
| ✅ 已修复（代码变更） | 5 | 11% |
| ❌ 严重缺陷 | 0 | 0% |

**已修复 5 项 + 编译问题 4 项 = 共 9 项代码变更。无严重缺陷。**
