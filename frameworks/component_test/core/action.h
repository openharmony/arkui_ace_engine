/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef OHOS_ACE_COMPONENT_TEST_CORE_ACTION_H
#define OHOS_ACE_COMPONENT_TEST_CORE_ACTION_H

#include <map>
#include <string_view>

#include "component_test/component_test_proxy.h"

#include "adapter/preview/entrance/event_dispatcher.h"
#include "adapter/preview/external/multimodalinput/key_event.h"
#include "adapter/preview/external/multimodalinput/pointer_event.h"
#include "base/geometry/ng/point_t.h"
#include "core/common/ace_engine.h"

namespace OHOS::Ace::ComponentTest {
constexpr int64_t SEC_TO_NANOSEC = 1000000000;
constexpr uint32_t MIN_STEP_CONUT = 2;
constexpr uint32_t MAX_STEP_CONUT = 50;
constexpr uint32_t TAP_HOLD_MS = 100;
constexpr uint32_t DOUBLE_TAP_INTERVAL_MS = 200;
constexpr uint32_t SWITCH_HOLD_MS = 500;
constexpr uint32_t PRESS_HOLD_MS = 1500;
constexpr uint32_t DEFAULT_SPEED = 600;
constexpr uint32_t MIN_SPEED = 200;
constexpr uint32_t MAX_SPEED = 40000;
constexpr uint32_t DEFAULT_STEP_CONUT = 10;
constexpr int32_t ACE_INSTANCE_ID = 0;
constexpr float PINCH_OUT_POINT_OFFSET = 80.0f;
constexpr float PINCH_IN_POINT_OFFSET = 2.0f;
constexpr float HALF = 0.5f;
constexpr float QUARTER = 0.25f;
constexpr size_t KEY_VALUE_START = 32;

enum TouchType : uint8_t { TAP, DOUBLE_TAP, PRESS, DRAG, FLING };

struct KeyInput {
    bool isShiftPressed;
    OHOS::MMI::KeyCode key;
};

constexpr KeyInput keyValue[] = { { false, OHOS::MMI::KeyCode::KEY_SPACE }, { true, OHOS::MMI::KeyCode::KEY_1 },
    { true, OHOS::MMI::KeyCode::KEY_APOSTROPHE }, { true, OHOS::MMI::KeyCode::KEY_3 },
    { true, OHOS::MMI::KeyCode::KEY_4 }, { true, OHOS::MMI::KeyCode::KEY_5 }, { true, OHOS::MMI::KeyCode::KEY_7 },
    { false, OHOS::MMI::KeyCode::KEY_APOSTROPHE }, { true, OHOS::MMI::KeyCode::KEY_9 },
    { true, OHOS::MMI::KeyCode::KEY_0 }, { true, OHOS::MMI::KeyCode::KEY_8 }, { true, OHOS::MMI::KeyCode::KEY_EQUALS },
    { false, OHOS::MMI::KeyCode::KEY_COMMA }, { false, OHOS::MMI::KeyCode::KEY_MINUS },
    { false, OHOS::MMI::KeyCode::KEY_PERIOD }, { false, OHOS::MMI::KeyCode::KEY_SLASH },
    { false, OHOS::MMI::KeyCode::KEY_0 }, { false, OHOS::MMI::KeyCode::KEY_1 }, { false, OHOS::MMI::KeyCode::KEY_2 },
    { false, OHOS::MMI::KeyCode::KEY_3 }, { false, OHOS::MMI::KeyCode::KEY_4 }, { false, OHOS::MMI::KeyCode::KEY_5 },
    { false, OHOS::MMI::KeyCode::KEY_6 }, { false, OHOS::MMI::KeyCode::KEY_7 }, { false, OHOS::MMI::KeyCode::KEY_8 },
    { false, OHOS::MMI::KeyCode::KEY_9 }, { false, OHOS::MMI::KeyCode::KEY_SEMICOLON },
    { true, OHOS::MMI::KeyCode::KEY_SEMICOLON }, { true, OHOS::MMI::KeyCode::KEY_COMMA },
    { false, OHOS::MMI::KeyCode::KEY_EQUALS }, { true, OHOS::MMI::KeyCode::KEY_PERIOD },
    { true, OHOS::MMI::KeyCode::KEY_SLASH }, { true, OHOS::MMI::KeyCode::KEY_2 }, { true, OHOS::MMI::KeyCode::KEY_A },
    { true, OHOS::MMI::KeyCode::KEY_B }, { true, OHOS::MMI::KeyCode::KEY_C }, { true, OHOS::MMI::KeyCode::KEY_D },
    { true, OHOS::MMI::KeyCode::KEY_E }, { true, OHOS::MMI::KeyCode::KEY_F }, { true, OHOS::MMI::KeyCode::KEY_G },
    { true, OHOS::MMI::KeyCode::KEY_H }, { true, OHOS::MMI::KeyCode::KEY_I }, { true, OHOS::MMI::KeyCode::KEY_J },
    { true, OHOS::MMI::KeyCode::KEY_K }, { true, OHOS::MMI::KeyCode::KEY_L }, { true, OHOS::MMI::KeyCode::KEY_M },
    { true, OHOS::MMI::KeyCode::KEY_N }, { true, OHOS::MMI::KeyCode::KEY_O }, { true, OHOS::MMI::KeyCode::KEY_P },
    { true, OHOS::MMI::KeyCode::KEY_Q }, { true, OHOS::MMI::KeyCode::KEY_R }, { true, OHOS::MMI::KeyCode::KEY_S },
    { true, OHOS::MMI::KeyCode::KEY_T }, { true, OHOS::MMI::KeyCode::KEY_U }, { true, OHOS::MMI::KeyCode::KEY_V },
    { true, OHOS::MMI::KeyCode::KEY_W }, { true, OHOS::MMI::KeyCode::KEY_X }, { true, OHOS::MMI::KeyCode::KEY_Y },
    { true, OHOS::MMI::KeyCode::KEY_Z }, { false, OHOS::MMI::KeyCode::KEY_LEFT_BRACKET },
    { false, OHOS::MMI::KeyCode::KEY_BACKSLASH }, { false, OHOS::MMI::KeyCode::KEY_RIGHT_BRACKET },
    { true, OHOS::MMI::KeyCode::KEY_6 }, { true, OHOS::MMI::KeyCode::KEY_MINUS },
    { true, OHOS::MMI::KeyCode::KEY_GRAVE }, { false, OHOS::MMI::KeyCode::KEY_A }, { false, OHOS::MMI::KeyCode::KEY_B },
    { false, OHOS::MMI::KeyCode::KEY_C }, { false, OHOS::MMI::KeyCode::KEY_D }, { false, OHOS::MMI::KeyCode::KEY_E },
    { false, OHOS::MMI::KeyCode::KEY_F }, { false, OHOS::MMI::KeyCode::KEY_G }, { false, OHOS::MMI::KeyCode::KEY_H },
    { false, OHOS::MMI::KeyCode::KEY_I }, { false, OHOS::MMI::KeyCode::KEY_J }, { false, OHOS::MMI::KeyCode::KEY_K },
    { false, OHOS::MMI::KeyCode::KEY_L }, { false, OHOS::MMI::KeyCode::KEY_M }, { false, OHOS::MMI::KeyCode::KEY_N },
    { false, OHOS::MMI::KeyCode::KEY_O }, { false, OHOS::MMI::KeyCode::KEY_P }, { false, OHOS::MMI::KeyCode::KEY_Q },
    { false, OHOS::MMI::KeyCode::KEY_R }, { false, OHOS::MMI::KeyCode::KEY_S }, { false, OHOS::MMI::KeyCode::KEY_T },
    { false, OHOS::MMI::KeyCode::KEY_U }, { false, OHOS::MMI::KeyCode::KEY_V }, { false, OHOS::MMI::KeyCode::KEY_W },
    { false, OHOS::MMI::KeyCode::KEY_X }, { false, OHOS::MMI::KeyCode::KEY_Y }, { false, OHOS::MMI::KeyCode::KEY_Z },
    { true, OHOS::MMI::KeyCode::KEY_LEFT_BRACKET }, { true, OHOS::MMI::KeyCode::KEY_BACKSLASH },
    { true, OHOS::MMI::KeyCode::KEY_RIGHT_BRACKET }, { true, OHOS::MMI::KeyCode::KEY_GRAVE } };

enum PointerActionState : uint8_t {
    UNKNOWN,
    DOWN,
    MOVE,
    UP,
    AXIS_VERTICAL,
    AXIS_HORIZONTAL,
    AXIS_VERTICAL_STOP,
    AXIS_HORIZONTAL_STOP,
};

enum ErrCode : int32_t {
    RET_OK = 0,
    RET_ERR_FAILED = -1,
    RET_ERROR_PARAM_INVALID = 401,
    RET_ERR_COMPONENT_NOT_SUPPORTED = 17000001,
    RET_ERR_COMPONENT_INVISIBLE_OR_DESTROYED = 17000002,
    RET_ERR_ASSERTION_COMPONENT_EXIST = 17000003,
    RET_ERR_ASSERTION_CONTAINS = 17000004,
    RET_ERR_ASSERTION_EQUAL = 17000005,
    RET_ERR_ASSERTION_TRUE = 17000006,
    RET_ERR_ASSERTION_FALSE = 17000006,
};

struct ErrInfo {
    ErrCode errCode;
    std::string_view message;
};

const std::map<ErrCode, ErrInfo> ErrDescMap = {
    { ErrCode::RET_OK, { ErrCode::RET_OK, "" } },
    { ErrCode::RET_ERR_FAILED, { ErrCode::RET_ERR_FAILED, "System abnormality" } },
    { ErrCode::RET_ERROR_PARAM_INVALID, { ErrCode::RET_ERROR_PARAM_INVALID, "Invalid input parameter." } },
    { ErrCode::RET_ERR_COMPONENT_NOT_SUPPORTED,
        { ErrCode::RET_ERR_COMPONENT_NOT_SUPPORTED, "Component not supported." } },
    { ErrCode::RET_ERR_COMPONENT_INVISIBLE_OR_DESTROYED,
        { ErrCode::RET_ERR_COMPONENT_INVISIBLE_OR_DESTROYED, "Component is invisible or destroyed." } },
    { ErrCode::RET_ERR_ASSERTION_COMPONENT_EXIST,
        { ErrCode::RET_ERR_ASSERTION_COMPONENT_EXIST, "Expect component exist assertion failed." } },
    { ErrCode::RET_ERR_ASSERTION_CONTAINS,
        { ErrCode::RET_ERR_ASSERTION_CONTAINS, "Expect contain actual assertion failed." } },
    { ErrCode::RET_ERR_ASSERTION_EQUAL, { ErrCode::RET_ERR_ASSERTION_EQUAL, "Expect equal actual assertion failed." } },
    { ErrCode::RET_ERR_ASSERTION_TRUE, { ErrCode::RET_ERR_ASSERTION_TRUE, "Expect is true assertion failed." } },
    { ErrCode::RET_ERR_ASSERTION_FALSE, { ErrCode::RET_ERR_ASSERTION_FALSE, "Expect is false assertion failed." } },
};

inline ErrInfo QueryRetMsg(ErrCode errorCode)
{
    auto iter = ErrDescMap.find(errorCode);
    if (iter != ErrDescMap.end()) {
        return iter->second;
    } else {
        return ErrDescMap.at(ErrCode::RET_ERR_FAILED);
    }
}

class EventAction {
public:
    explicit EventAction(uint32_t holdMs = 0) : holdMs(holdMs) {};
    virtual ~EventAction() = default;
    uint32_t holdMs;
};

struct PointerEventAction {
    PointerActionState stage;
    NG::PointF point;
    uint32_t holdMs;
};

class EventMatrix {
public:
    EventMatrix() = default;
    EventMatrix(uint32_t fingersNum, uint32_t stepsNum);
    ~EventMatrix() = default;
    EventMatrix& operator=(EventMatrix&& other);
    EventMatrix(EventMatrix&& other);
    EventMatrix(const EventMatrix&) = delete;
    EventMatrix& operator=(const EventMatrix&) = delete;

    void PushEventAction(const PointerEventAction& action);
    bool Empty() const;
    PointerEventAction& GetEventAction(uint32_t fingerIndex, uint32_t stepIndex) const;
    uint32_t GetCapacity() const;
    uint32_t GetSize() const;
    uint32_t GetSteps() const;
    uint32_t GetFingers() const;

private:
    std::unique_ptr<PointerEventAction[]> data_ = nullptr;
    uint32_t capacity_ = 0;
    uint32_t stepNum_ = 0;
    uint32_t fingerNum_ = 0;
    uint32_t size_ = 0;
};

struct ActionTask {
    uint32_t holdMs;
    std::function<void()> task;
};

class Action {
public:
    Action() : taskExecutor_(AceEngine::Get().GetContainer(ACE_INSTANCE_ID)->GetTaskExecutor()) {};
    virtual ~Action() = default;
    Action(const Action&) = delete;
    Action& operator=(const Action&) = delete;
    Action(Action&&) = delete;
    Action& operator=(Action&&) = delete;

protected:
    RefPtr<TaskExecutor> taskExecutor_;
};

class PointerAction : public Action {
public:
    PointerAction() = default;
    ~PointerAction() override = default;
    virtual void Decompose(EventMatrix& recv) const = 0;
    virtual void DispatchPointerEvent(const EventMatrix& events);
};

class EventSequenceManager {
public:
    ~EventSequenceManager() = default;
    EventSequenceManager(const EventSequenceManager&) = delete;
    static EventSequenceManager& GetInstance();
    void Execute(PointerAction* pointerAction) const;

private:
    EventSequenceManager() = default;
    EventSequenceManager& operator=(const EventSequenceManager&) = delete;
};

class ClickAction : public PointerAction {
public:
    ClickAction(const NG::PointF point, const TouchType touchType, uint32_t duration = PRESS_HOLD_MS)
        : point_(point), touchType_(touchType), duration_(duration) {};
    ~ClickAction() override = default;
    void Decompose(EventMatrix& recv) const override;

private:
    const NG::PointF point_;
    const TouchType touchType_;
    const uint32_t duration_ = 0;
};

class MoveAction : public PointerAction {
public:
    MoveAction(const NG::PointF from, const NG::PointF to, const TouchType touchType, uint32_t speed = DEFAULT_SPEED,
        uint32_t steps = DEFAULT_STEP_CONUT)
        : from_(from), to_(to), touchType_(touchType),
          speed_((speed < MIN_SPEED || speed > MAX_SPEED) ? DEFAULT_SPEED : speed),
          steps_(std::clamp(steps, MIN_STEP_CONUT, MAX_STEP_CONUT)) {};
    ~MoveAction() override = default;
    void Decompose(EventMatrix& recv) const override;

private:
    const NG::PointF from_;
    const NG::PointF to_;
    const TouchType touchType_;
    const uint32_t speed_;
    const uint32_t steps_;
};

class PinchAction : public PointerAction {
public:
    PinchAction(const NG::RectF rect, const float scale) : rect_(rect), scale_(scale) {};
    ~PinchAction() override = default;
    void Decompose(EventMatrix& recv) const override;

private:
    const NG::RectF rect_;
    float scale_;
};

class ScrollAction : public PointerAction {
public:
    ScrollAction(float deltaX, float deltaY) : deltaX_(deltaX), deltaY_(deltaY) {};
    ~ScrollAction() override = default;
    void Decompose(EventMatrix& recv) const override;

private:
    float deltaX_;
    float deltaY_;
};

class ScrollToAction : public PointerAction {
public:
    ScrollToAction(float speed, float deltaY)
        : speed_((speed < MIN_SPEED || speed > MAX_SPEED) ? DEFAULT_SPEED : speed), deltaY_(deltaY) {};
    ~ScrollToAction() override = default;
    void Decompose(EventMatrix& recv) const override;

private:
    const float speed_;
    float deltaY_;
};

class CombinedKeysAction : public Action {
protected:
    enum KeyActionState : uint8_t {
        DOWN,
        UP,
    };
    struct KeyEvent {
        KeyActionState stage_;
        OHOS::MMI::KeyCode code_;
        uint32_t holdMs_;
    };
    std::vector<OHOS::MMI::KeyCode> pressedCodes_;
    std::vector<CombinedKeysAction::KeyEvent> events_;
    size_t codeLength_;

public:
    CombinedKeysAction() = default;
    explicit CombinedKeysAction(const std::vector<OHOS::MMI::KeyCode>& keyCodes) : CombinedKeysAction()
    {
        codeLength_ = keyCodes.size();
        for (auto num : keyCodes) {
            pressedCodes_.push_back(OHOS::MMI::KeyCode(num));
        }
        CreateEvents();
    };
    ~CombinedKeysAction() override = default;
    void CreateEvents();
    void Send();
};

class SingleKeyAction : public CombinedKeysAction {
public:
    explicit SingleKeyAction(OHOS::MMI::KeyCode keyCode);
    explicit SingleKeyAction(const std::vector<OHOS::MMI::KeyCode>& keyCodes);
    SingleKeyAction(std::string& text, std::string& currentText);
    ~SingleKeyAction() override = default;

private:
    void CopyCreateEvents();
    void CreateClearEvent(std::string& currentText);
    void CreateEnterEvents();
    void CreateDoubleBackslashEvents();
    bool IsSpecialKey(OHOS::MMI::KeyCode keyCode);
};

} // namespace OHOS::Ace::ComponentTest

#endif // OHOS_NAPI_ACE_COMPONENT_TEST_CORE_ACTION_H
