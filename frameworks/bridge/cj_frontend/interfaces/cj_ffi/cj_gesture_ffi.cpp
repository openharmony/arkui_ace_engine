/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_gesture_ffi.h"

#include "cj_gesture_native.h"
#include "cj_lambda.h"

#include "bridge/cj_frontend/cppview/gesture.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/gestures/base_gesture_event.h"
#include "core/components_ng/pattern/gesture/gesture_model_ng.h"
#include "frameworks/core/components_ng/base/view_stack_processor.h"
#include "frameworks/core/components_ng/gestures/long_press_gesture.h"
#include "frameworks/core/components_ng/gestures/pinch_gesture.h"
#include "frameworks/core/components_ng/gestures/rotation_gesture.h"
#include "frameworks/core/components_ng/gestures/swipe_gesture.h"
#if defined(WINDOWS_PLATFORM)
#include <windows.h>
#else
#include <dlfcn.h>
#endif

using namespace OHOS::FFI;
using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace {
#if defined(WINDOWS_PLATFORM)
void* FindModule()
{
    HMODULE result = nullptr;
    const char libname[] = "libace_compatible.dll";
    GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_PIN, libname, &result);
    if (result) {
        return result;
    }
    LOGE("Cannot find module!");
    return nullptr;
}
void* FindFunction(void* library, const char* name)
{
    return (void*)GetProcAddress(reinterpret_cast<HMODULE>(library), name);
}
#else
void* FindModule()
{
    const char libname[] = "libace_compatible.z.so";
    void* result = dlopen(libname, RTLD_LAZY | RTLD_LOCAL);
    if (result) {
        return result;
    }
    LOGE("Cannot load libace: %{public}s", dlerror());
    return nullptr;
}

void* FindFunction(void* library, const char* name)
{
    return dlsym(library, name);
}
#endif

ArkUIFullNodeAPI* impl = nullptr;

ArkUIFullNodeAPI* GetNodeAPIImpl()
{
    if (!impl) {
        typedef ArkUIAnyAPI* (*GetAPI_t)(int);
        GetAPI_t getAPI = nullptr;
        void* module = FindModule();
        if (module == nullptr) {
            LOGE("GetNodeAPIImpl: FindModule fail");
            return nullptr;
        }
        getAPI = reinterpret_cast<GetAPI_t>(FindFunction(module, "GetArkUIAnyFullNodeAPI"));
        if (!getAPI) {
            LOGE("GetNodeAPIImpl: getAPI failed");
            return nullptr;
        }

        impl = reinterpret_cast<ArkUIFullNodeAPI*>((*getAPI)(ARKUI_NODE_API_VERSION));
        if (!getAPI) {
            LOGE("GetNodeAPIImpl: impl is null");
            return nullptr;
        }
    }
    return impl;
}

constexpr int32_t DEFAULT_TAP_FINGER = 1;
constexpr int32_t MAX_TAP_FINGER = 10;
constexpr int32_t DEFAULT_TAP_COUNT = 1;
constexpr int32_t DEFAULT_LONG_PRESS_FINGER = 1;
constexpr int32_t MAX_LONG_PRESS_FINGER = 10;
constexpr int32_t DEFAULT_PINCH_FINGER = 2;
constexpr int32_t MAX_PINCH_FINGER = 5;
constexpr double DEFAULT_PINCH_DISTANCE = 3.0;
constexpr int32_t DEFAULT_ROTATION_FINGER = 2;
constexpr int32_t MAX_ROTATION_FINGER = 5;
constexpr double DEFAULT_ROTATION_ANGLE = 1.0;
constexpr int32_t MAX_PAN_FINGER = 10;
constexpr int32_t MAX_SLIDE_FINGER = 10;
constexpr double DEFAULT_TAP_DISTANCE = std::numeric_limits<double>::infinity();

const std::vector<GesturePriority> GESTURE_PRIORITY = { GesturePriority::Low, GesturePriority::High,
    GesturePriority::Parallel };

const std::vector<GestureMask> GESTURE_MASK = { GestureMask::Normal, GestureMask::IgnoreInternal };

const std::vector<GestureMode> GROUP_GESTURE_MODE = { GestureMode::Sequence, GestureMode::Parallel,
    GestureMode::Exclusive };

enum class GestureEventType { ACTION, START, UPDATE, END, CANCEL };

bool CheckKeysPressed(const std::vector<KeyCode>& pressedKeyCodes, std::vector<std::string>& checkKeyCodes)
{
    auto hasKeyCode = [pressedKeyCodes](const KeyCode& keyCode) -> bool {
        auto it = std::find(pressedKeyCodes.begin(), pressedKeyCodes.end(), keyCode);
        return it != pressedKeyCodes.end();
    };
    for (auto& checkKeyCode : checkKeyCodes) {
        if (checkKeyCode == "ctrl") {
            if (!hasKeyCode(KeyCode::KEY_CTRL_LEFT) && !hasKeyCode(KeyCode::KEY_CTRL_RIGHT)) {
                return false;
            }
        } else if (checkKeyCode == "shift") {
            if (!hasKeyCode(KeyCode::KEY_SHIFT_LEFT) && !hasKeyCode(KeyCode::KEY_SHIFT_RIGHT)) {
                return false;
            }
        } else if (checkKeyCode == "alt") {
            if (!hasKeyCode(KeyCode::KEY_ALT_LEFT) && !hasKeyCode(KeyCode::KEY_ALT_RIGHT)) {
                return false;
            }
        } else if (checkKeyCode == "fn") {
            if (!hasKeyCode(KeyCode::KEY_FN)) {
                return false;
            }
        } else {
            LOGE("CheckKeysPressed: indicate the keys are illegal");
            return false;
        }
    }
    return true;
}

void FormatGestureType(CJBaseGestureEvent& cjEvent, const std::shared_ptr<BaseGestureEvent>& info, GestureTypeName type)
{
    double density = PipelineBase::GetCurrentDensity();
    if (density != 0.0) {
        switch (type) {
            case GestureTypeName::LONG_PRESS_GESTURE: {
                auto* longPressGestureEvent = TypeInfoHelper::DynamicCast<LongPressGestureEvent>(info.get());
                cjEvent.repeat = longPressGestureEvent->GetRepeat();
                break;
            }
            case GestureTypeName::PAN_GESTURE: {
                auto* panGestureEvent = TypeInfoHelper::DynamicCast<PanGestureEvent>(info.get());
                cjEvent.offsetX = panGestureEvent->GetOffsetX() / density;
                cjEvent.offsetY = panGestureEvent->GetOffsetY() / density;
                cjEvent.velocityX = panGestureEvent->GetVelocity().GetVelocityX() / density;
                cjEvent.velocityY = panGestureEvent->GetVelocity().GetVelocityY() / density;
                cjEvent.velocity = panGestureEvent->GetVelocity().GetVelocityValue() / density;
                break;
            }
            case GestureTypeName::PINCH_GESTURE: {
                auto* pinchGestureEvent = TypeInfoHelper::DynamicCast<PinchGestureEvent>(info.get());
                cjEvent.scale = pinchGestureEvent->GetScale();
                cjEvent.pinchCenterX = pinchGestureEvent->GetPinchCenter().GetX() / density;
                cjEvent.pinchCenterY = pinchGestureEvent->GetPinchCenter().GetY() / density;
                break;
            }
            case GestureTypeName::SWIPE_GESTURE: {
                auto* swipeGestureEvent = TypeInfoHelper::DynamicCast<SwipeGestureEvent>(info.get());
                cjEvent.angle = swipeGestureEvent->GetAngle();
                cjEvent.speed = swipeGestureEvent->GetSpeed();
                break;
            }
            case GestureTypeName::ROTATION_GESTURE: {
                auto* rotationGestureEvent = TypeInfoHelper::DynamicCast<RotationGestureEvent>(info.get());
                cjEvent.angle = rotationGestureEvent->GetAngle();
                break;
            }
            default:
                break;
        }
    }
}

std::function<void(const GestureEvent& event)> FormatGestureEvenFunction(void (*callback)(CJGestureEvent info))
{
    std::function<void(const GestureEvent& event)> result = [ffiOnAction = CJLambda::Create(callback)](
                                                                const GestureEvent& event) -> void {
        CJGestureEvent ffiGestureEvent {};
        CJEventTarget ffiEventTarget {};
        CJArea ffiArea {};
        CJPosition ffiPosition {};
        CJPosition ffiGlobalPosition {};

        const auto& eventTarget = event.GetTarget();
        ffiArea.width = eventTarget.area.GetWidth().ConvertToVp();
        ffiArea.height = eventTarget.area.GetHeight().ConvertToVp();
        const auto& localOffset = eventTarget.area.GetOffset();
        const auto& origin = eventTarget.origin;
        ffiPosition.x = localOffset.GetX().ConvertToVp();
        ffiPosition.y = localOffset.GetY().ConvertToVp();
        ffiGlobalPosition.x = origin.GetX().ConvertToVp() + localOffset.GetX().ConvertToVp();
        ffiGlobalPosition.y = origin.GetY().ConvertToVp() + localOffset.GetY().ConvertToVp();

        ffiArea.globalPosition = &ffiGlobalPosition;
        ffiArea.position = &ffiPosition;

        ffiEventTarget.area = &ffiArea;

        auto& fingerList = event.GetFingerList();
        ffiGestureEvent.fingerListSize = static_cast<int32_t>(fingerList.size());
        ffiGestureEvent.fingerList = new CJFingerInfo[fingerList.size()];
        TransformNativeCJFingerInfo(ffiGestureEvent.fingerList, fingerList);

        ffiGestureEvent.target = &ffiEventTarget;
        ffiGestureEvent.timestamp = event.GetTimeStamp().time_since_epoch().count();
        ffiGestureEvent.repeat = event.GetRepeat();
        ffiGestureEvent.source = static_cast<int32_t>(event.GetSourceDevice());
        ffiGestureEvent.offsetX = event.GetOffsetX();
        ffiGestureEvent.offsetY = event.GetOffsetY();
        ffiGestureEvent.scale = event.GetScale();
        ffiGestureEvent.pinchCenterX = event.GetPinchCenter().GetX();
        ffiGestureEvent.pinchCenterY = event.GetPinchCenter().GetY();
        ffiGestureEvent.angle = event.GetAngle();
        ffiGestureEvent.speed = event.GetSpeed();
        ffiGestureEvent.tiltX = event.GetTiltX().value_or(0.0f);
        ffiGestureEvent.tiltY = event.GetTiltY().value_or(0.0f);
        ffiGestureEvent.sourceTool = static_cast<int32_t>(event.GetSourceTool());
        ffiGestureEvent.velocityX = PipelineBase::Px2VpWithCurrentDensity(event.GetVelocity().GetVelocityX());
        ffiGestureEvent.velocityY = PipelineBase::Px2VpWithCurrentDensity(event.GetVelocity().GetVelocityY());
        ffiGestureEvent.velocity = PipelineBase::Px2VpWithCurrentDensity(event.GetVelocity().GetVelocityValue());
        ffiGestureEvent.pressure = event.GetForce();
        ffiGestureEvent.axisHorizontal = event.GetHorizontalAxis();
        ffiGestureEvent.axisVertical = event.GetVerticalAxis();
        ffiGestureEvent.deviceId = event.GetDeviceId();
        ffiGestureEvent.baseEventInfoPtr = dynamic_cast<const BaseEventInfo*>(&event);
        ffiOnAction(ffiGestureEvent);
    };
    return result;
}

std::function<void(const GestureEvent& event)> FormatGestureEvenFunction(void (*callback)())
{
    std::function<void(const GestureEvent& event)> result = [ffiOnAction = CJLambda::Create(callback)](
                                                                const GestureEvent& event) -> void { ffiOnAction(); };
    return result;
}

void HandlerOnGestureEvent(
    const GestureEventType& action, const std::function<void(const GestureEvent& event)>& callback)
{
    RefPtr<GestureProcessor> gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto gesture = gestureProcessor->TopGestureNG();
    if (!gesture) {
        LOGE("top gesture is illegal");
        return;
    }

    if (action == GestureEventType::CANCEL) {
        auto onActionCancelFunc = [callback = std::move(callback)](GestureEvent& info) { callback(info); };
        gesture->SetOnActionCancelId(onActionCancelFunc);
        return;
    }

    auto onActionFunc = [callback = std::move(callback)](GestureEvent& info) { callback(info); };

    switch (action) {
        case GestureEventType::ACTION:
            gesture->SetOnActionId(onActionFunc);
            break;
        case GestureEventType::START:
            gesture->SetOnActionStartId(onActionFunc);
            break;
        case GestureEventType::UPDATE:
            gesture->SetOnActionUpdateId(onActionFunc);
            break;
        case GestureEventType::END:
            gesture->SetOnActionEndId(onActionFunc);
            break;
        default:
            LOGW("Gesture: Unknown gesture action %{public}d", action);
            break;
    }
}

} // namespace

extern "C" {
void FfiOHOSAceFrameworkGestureCreate(int32_t priority, int32_t mask)
{
    if (!Utils::CheckParamsValid(priority, GESTURE_PRIORITY.size())) {
        LOGE("invalid value for gesturePriority");
        return;
    }
    if (!Utils::CheckParamsValid(mask, GESTURE_MASK.size())) {
        LOGE("invalid value for gestureMask");
        return;
    }

    RefPtr<GestureProcessor> gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    gestureProcessor->SetPriority(GESTURE_PRIORITY[priority]);
    gestureProcessor->SetGestureMask(GESTURE_MASK[mask]);
}

void FfiOHOSAceFrameworkGestureOnAction(void (*callback)(CJGestureEvent info))
{
    HandlerOnGestureEvent(GestureEventType::ACTION, FormatGestureEvenFunction(callback));
}

void FfiOHOSAceFrameworkGestureSetTag(const char* tag)
{
    RefPtr<GestureProcessor> gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto gesture = gestureProcessor->TopGestureNG();
    if (!gesture) {
        LOGE("FfiOHOSAceFrameworkGestureSetTag: get gesture failed");
        return;
    }
    gesture->SetTag(tag);
}

void FfiOHOSAceFrameworkGestureOnActionStart(void (*callback)(CJGestureEvent info))
{
    HandlerOnGestureEvent(GestureEventType::START, FormatGestureEvenFunction(callback));
}

void FfiOHOSAceFrameworkGestureOnActionUpdate(void (*callback)(CJGestureEvent info))
{
    HandlerOnGestureEvent(GestureEventType::UPDATE, FormatGestureEvenFunction(callback));
}

void FfiOHOSAceFrameworkGestureOnActionEnd(void (*callback)(CJGestureEvent info))
{
    HandlerOnGestureEvent(GestureEventType::END, FormatGestureEvenFunction(callback));
}

void FfiOHOSAceFrameworkGestureOnActionCancel(void (*callback)())
{
    HandlerOnGestureEvent(GestureEventType::CANCEL, FormatGestureEvenFunction(callback));
}

void FfiOHOSAceFrameworkGestureFinish()
{
    RefPtr<GestureProcessor> gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    NG::ViewStackProcessor::GetInstance()->ResetGestureProcessor();

    auto gesture = gestureProcessor->FinishGestureNG();
    if (!gesture) {
        LOGE("gesture is not exist when component finish");
        return;
    }
    gesture->SetGestureMask(gestureProcessor->GetGestureMask());
    gesture->SetPriority(gestureProcessor->GetPriority());
    auto gestureEventHub = NG::ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    if (gestureEventHub) {
        gestureEventHub->AddGesture(gesture);
    }
}

void FfiOHOSAceFrameworkGesturePop()
{
    RefPtr<GestureProcessor> gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    gestureProcessor->PopGestureNG();
}

// tapGesture
void FfiOHOSAceFrameworkTapGestureCreate(int32_t count, int32_t fingers)
{
    RefPtr<GestureProcessor> gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();

    int32_t countNum = Utils::CheckMin(DEFAULT_TAP_COUNT, DEFAULT_TAP_COUNT, count);
    int32_t fingersNum = Utils::CheckRange(DEFAULT_TAP_FINGER, MAX_TAP_FINGER, DEFAULT_TAP_FINGER, fingers);

    auto gesture = AceType::MakeRefPtr<NG::TapGesture>(countNum, fingersNum);
    gestureProcessor->PushGestureNG(gesture);
}

// LongPressGesture
void FfiOHOSAceFrameworkLongPressGestureCreate(int32_t fingers, bool repeat, int32_t duration)
{
    RefPtr<GestureProcessor> gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();

    int32_t fingersNum =
        Utils::CheckRange(DEFAULT_LONG_PRESS_FINGER, MAX_LONG_PRESS_FINGER, DEFAULT_LONG_PRESS_FINGER, fingers);
    int32_t durationNum = Utils::CheckMin(0, DEFAULT_LONG_PRESS_DURATION, duration);

    auto gesture = AceType::MakeRefPtr<NG::LongPressGesture>(fingersNum, repeat, durationNum);
    gestureProcessor->PushGestureNG(gesture);
}

// PinchPressGesture
void FfiOHOSAceFrameworkPinchGestureCreate(int32_t fingers, double distance)
{
    RefPtr<GestureProcessor> gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();

    int32_t fingersNum = Utils::CheckRange(DEFAULT_PINCH_FINGER, MAX_PINCH_FINGER, DEFAULT_PINCH_FINGER, fingers);
    double distanceNum = Utils::CheckMin(0.0, DEFAULT_PINCH_DISTANCE, distance);

    auto gesture = AceType::MakeRefPtr<NG::PinchGesture>(fingersNum, distanceNum);
    gestureProcessor->PushGestureNG(gesture);
}

// SwipeGesture
void FfiOHOSAceFrameworkSwipeGestureCreate(int32_t fingers, uint32_t direction, double speed)
{
    OHOS::Ace::SwipeDirection swipeDirection;
    swipeDirection.type = direction;

    RefPtr<GestureProcessor> gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();

    int32_t fingersNum = Utils::CheckRange(DEFAULT_SLIDE_FINGER, MAX_SLIDE_FINGER, DEFAULT_SLIDE_FINGER, fingers);
    double speedNum = Utils::CheckMin(0.0, DEFAULT_SLIDE_SPEED, speed);

    auto gesture = AceType::MakeRefPtr<NG::SwipeGesture>(fingersNum, swipeDirection, speedNum);
    gestureProcessor->PushGestureNG(gesture);
}

// RotationGesture
void FfiOHOSAceFrameworkRotationGestureCreate(int32_t fingers, double angle)
{
    RefPtr<GestureProcessor> gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();

    int32_t fingersNum =
        Utils::CheckRange(DEFAULT_ROTATION_FINGER, MAX_ROTATION_FINGER, DEFAULT_ROTATION_FINGER, fingers);
    double angleNum = Utils::CheckMin(0.0, DEFAULT_ROTATION_ANGLE, angle);

    auto gesture = AceType::MakeRefPtr<NG::RotationGesture>(fingersNum, angleNum);
    gestureProcessor->PushGestureNG(gesture);
}

// PanGesture
void FfiOHOSAceFrameworkPanGestureCreate(int32_t fingers, uint32_t direction, double distance)
{
    OHOS::Ace::PanDirection panDirection;
    panDirection.type = direction;

    RefPtr<GestureProcessor> gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();

    int32_t fingersNum = Utils::CheckRange(DEFAULT_PAN_FINGER, MAX_PAN_FINGER, DEFAULT_PAN_FINGER, fingers);
    double distanceNum = Utils::CheckMin(0.0, DEFAULT_PAN_DISTANCE.Value(), distance);

    auto gesture = AceType::MakeRefPtr<NG::PanGesture>(fingersNum, panDirection, distanceNum);
    gestureProcessor->PushGestureNG(gesture);
}

void FfiOHOSAceFrameworkPanGestureCreateWithOptions(int64_t optionId)
{
    auto panGestureOption = FFIData::GetData<NativePanGestureOption>(optionId);
    if (panGestureOption == nullptr) {
        LOGE("FfiGesture: invalid PanGestureOptions ID");
    } else {
        RefPtr<GestureProcessor> gestureProcessor =
            NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();

        auto gesture = AceType::MakeRefPtr<NG::PanGesture>(panGestureOption->GetPanGestureOption());
        gestureProcessor->PushGestureNG(gesture);
    }
}

// GestureGroup
void FfiOHOSAceFrameworkGestureGroupCreate(int32_t mode)
{
    if (!Utils::CheckParamsValid(mode, GROUP_GESTURE_MODE.size())) {
        LOGE("invalid value for gesture group mode");
        return;
    }

    RefPtr<GestureProcessor> gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto gesture = AceType::MakeRefPtr<NG::GestureGroup>(GROUP_GESTURE_MODE[mode]);
    gestureProcessor->PushGestureNG(gesture);
}

int64_t FfiOHOSAceFrameworkPanGestureOptionsCtor(int32_t fingers, uint32_t direction, double distance)
{
    OHOS::Ace::PanDirection panDirection;
    panDirection.type = direction;

    int32_t fingersNum = Utils::CheckRange(DEFAULT_PAN_FINGER, MAX_PAN_FINGER, DEFAULT_PAN_FINGER, fingers);
    double distanceNum = Utils::CheckMin(0.0, DEFAULT_PAN_DISTANCE.Value(), distance);

    auto ret_ = FFIData::Create<NativePanGestureOption>(fingersNum, panDirection, distanceNum);
    if (ret_ == nullptr) {
        return FFI_ERROR_CODE;
    }
    return ret_->GetID();
}

void FfiOHOSAceFrameworkPanGestureOptionsSetFingers(int64_t selfID, int32_t fingers)
{
    auto self = FFIData::GetData<NativePanGestureOption>(selfID);
    if (self != nullptr) {
        self->SetFingers(fingers);
    } else {
        LOGE("FfiGesture: invalid PanGestureOptions ID");
    }
}

void FfiOHOSAceFrameworkPanGestureOptionsSetDirection(int64_t selfID, uint32_t direction)
{
    OHOS::Ace::PanDirection panDirection;
    panDirection.type = direction;

    auto self = FFIData::GetData<NativePanGestureOption>(selfID);
    if (self != nullptr) {
        self->SetDirection(panDirection);
    } else {
        LOGE("FfiGesture: invalid PanGestureOptions ID");
    }
}

void FfiOHOSAceFrameworkPanGestureOptionsSetDistance(int64_t selfID, double distance)
{
    auto self = FFIData::GetData<NativePanGestureOption>(selfID);
    if (self != nullptr) {
        self->SetDistance(distance);
    } else {
        LOGE("FfiGesture: invalid PanGestureOptions ID");
    }
}

int64_t FfiOHOSAceFrameworkTapGestureHandlerCtor(int32_t count, int32_t fingers)
{
    auto nativeGesture = FFIData::Create<NativeGesture>();
    if (nativeGesture == nullptr) {
        LOGE("FfiOHOSAceFrameworkTapGestureHandlerCtor: nativeGesture create failed");
        return FFI_ERROR_CODE;
    }
    auto tapGesture = GetNodeAPIImpl()->getNodeModifiers()->getGestureModifier()->
        createTapGestureWithDistanceThreshold(count, fingers, DEFAULT_TAP_DISTANCE, false, nullptr);
    nativeGesture->setArkUIGesture(tapGesture);
    return nativeGesture->GetID();
}

int64_t FfiOHOSAceFrameworkLongPressGestureHandlerCtor(int32_t fingers, bool repeat, int32_t duration)
{
    auto nativeGesture = FFIData::Create<NativeGesture>();
    if (nativeGesture == nullptr) {
        LOGE("FfiOHOSAceFrameworkLongPressGestureHandlerCtor: nativeGesture create failed");
        return FFI_ERROR_CODE;
    }
    auto longPressGesture = GetNodeAPIImpl()->getNodeModifiers()->getGestureModifier()->
        createLongPressGesture(fingers, repeat, duration, false, nullptr);
    nativeGesture->setArkUIGesture(longPressGesture);
    return nativeGesture->GetID();
}

int64_t FfiOHOSAceFrameworkPinchGestureHandlerCtor(int32_t fingers, double distance)
{
    auto nativeGesture = FFIData::Create<NativeGesture>();
    if (nativeGesture == nullptr) {
        LOGE("FfiOHOSAceFrameworkPinchGestureHandlerCtor: nativeGesture create failed");
        return FFI_ERROR_CODE;
    }
    auto pinchGesture = GetNodeAPIImpl()->getNodeModifiers()->getGestureModifier()->
        createPinchGesture(fingers, distance, false, nullptr);
    nativeGesture->setArkUIGesture(pinchGesture);
    return nativeGesture->GetID();
}

int64_t FfiOHOSAceFrameworkSwipeGestureHandlerCtor(int32_t fingers, uint32_t direction, double speed)
{
    auto nativeGesture = FFIData::Create<NativeGesture>();
    if (nativeGesture == nullptr) {
        LOGE("FfiOHOSAceFrameworkSwipeGestureHandlerCtor: nativeGesture create failed");
        return FFI_ERROR_CODE;
    }
    auto swipeGesture = GetNodeAPIImpl()->getNodeModifiers()->getGestureModifier()->
        createSwipeGestureByModifier(fingers, direction, speed, false);
    nativeGesture->setArkUIGesture(swipeGesture);
    return nativeGesture->GetID();
}

int64_t FfiOHOSAceFrameworkRotationGestureHandlerCtor(int32_t fingers, double angle)
{
    auto nativeGesture = FFIData::Create<NativeGesture>();
    if (nativeGesture == nullptr) {
        LOGE("FfiOHOSAceFrameworkRotationGestureHandlerCtor: nativeGesture create failed");
        return FFI_ERROR_CODE;
    }
    auto rotationGesture = GetNodeAPIImpl()->getNodeModifiers()->getGestureModifier()->
        createRotationGesture(fingers, angle, false, nullptr);
    nativeGesture->setArkUIGesture(rotationGesture);
    return nativeGesture->GetID();
}

int64_t FfiOHOSAceFrameworkPanGestureHandlerCtor(int32_t fingers, uint32_t direction, double distance)
{
    auto nativeGesture = FFIData::Create<NativeGesture>();
    if (nativeGesture == nullptr) {
        LOGE("FfiOHOSAceFrameworkPanGestureHandlerCtor: nativeGesture create failed");
        return FFI_ERROR_CODE;
    }
    auto panGesture = GetNodeAPIImpl()->getNodeModifiers()->getGestureModifier()->
        createPanGesture(fingers, direction, distance, false, nullptr);
    nativeGesture->setArkUIGesture(panGesture);
    return nativeGesture->GetID();
}

int64_t FfiOHOSAceFrameworkGestureGroupHandlerCtor(int32_t mode, VectorInt64Handle vectorHandle)
{
    auto nativeGestureGroup = FFIData::Create<NativeGestureGroup>();
    if (nativeGestureGroup == nullptr) {
        LOGE("FfiOHOSAceFrameworkGestureGroupHandlerCtor: nativeGestureGroup create failed");
        return FFI_ERROR_CODE;
    }
    auto gestureGroup = GetNodeAPIImpl()->getNodeModifiers()->getGestureModifier()->createGestureGroup(mode);
    nativeGestureGroup->setArkUIGesture(gestureGroup);
    const auto& gestureList = *reinterpret_cast<std::vector<int64_t>*>(vectorHandle);
    for (auto id : gestureList) {
        auto nativeGesture = FFIData::GetData<NativeGesture>(id);
        if (nativeGesture == nullptr) {
            LOGE("FfiOHOSAceFrameworkGestureGroupHandlerCtor: invalid id");
            return FFI_ERROR_CODE;
        }
        GetNodeAPIImpl()->getNodeModifiers()->getGestureModifier()->addGestureToGestureGroupWithRefCountDecrease(
            nativeGestureGroup->getArkUIGesture(), nativeGesture->getArkUIGesture());
    }
    return nativeGestureGroup->GetID();
}

void FfiOHOSAceFrameworkGestureGroupHandlerSetOnCancel(int64_t id, void (*onCancel)())
{
    auto nativeGesture = FFIData::GetData<NativeGestureGroup>(id);
    if (nativeGesture == nullptr) {
        LOGE("FfiOHOSAceFrameworkGestureGroupHandlerSetOnCancel: invalid id");
        return;
    }
    auto event = [ffiOnCancel = CJLambda::Create(onCancel)](GestureEvent& info) -> void { ffiOnCancel(); };

    auto gesturePtr = Referenced::Claim(reinterpret_cast<OHOS::Ace::NG::Gesture*>(nativeGesture->getArkUIGesture()));
    gesturePtr->SetOnActionCancelId(event);
}

void FfiOHOSAceFrameworkGestureHandlerSetTag(int64_t id, const char* tag)
{
    auto nativeGesture = FFIData::GetData<NativeGesture>(id);
    if (nativeGesture == nullptr) {
        LOGE("FfiOHOSAceFrameworkGestureHandlerSetTag: invalid id");
        return;
    }
    auto gesturePtr = Referenced::Claim(reinterpret_cast<OHOS::Ace::NG::Gesture*>(nativeGesture->getArkUIGesture()));
    gesturePtr->SetTag(tag);
}

void FfiOHOSAceFrameworkGestureHandlerSetOnAction(int64_t id, void (*onActionCallback)(CJGestureEvent))
{
    auto nativeGesture = FFIData::GetData<NativeGesture>(id);
    if (nativeGesture == nullptr) {
        LOGE("FfiOHOSAceFrameworkLongPressGestureHandlerCtor: invalid id");
        return;
    }
    auto event = FormatGestureEvenFunction(onActionCallback);

    auto gesturePtr = Referenced::Claim(reinterpret_cast<OHOS::Ace::NG::Gesture*>(nativeGesture->getArkUIGesture()));
    gesturePtr->SetOnActionId(event);
}

void FfiOHOSAceFrameworkGestureHandlerSetOnActionStart(int64_t id, void (*onActionCallback)(CJGestureEvent))
{
    auto nativeGesture = FFIData::GetData<NativeGesture>(id);
    if (nativeGesture == nullptr) {
        LOGE("FfiOHOSAceFrameworkGestureHandlerSetOnActionStart: invalid id");
        return;
    }
    auto event = FormatGestureEvenFunction(onActionCallback);

    auto gesturePtr = Referenced::Claim(reinterpret_cast<OHOS::Ace::NG::Gesture*>(nativeGesture->getArkUIGesture()));
    gesturePtr->SetOnActionStartId(event);
}

void FfiOHOSAceFrameworkGestureHandlerSetOnActionUpdate(int64_t id, void (*onActionCallback)(CJGestureEvent))
{
    auto nativeGesture = FFIData::GetData<NativeGesture>(id);
    if (nativeGesture == nullptr) {
        LOGE("FfiOHOSAceFrameworkGestureHandlerSetOnActionUpdate: invalid id");
        return;
    }
    auto event = FormatGestureEvenFunction(onActionCallback);

    auto gesturePtr = Referenced::Claim(reinterpret_cast<OHOS::Ace::NG::Gesture*>(nativeGesture->getArkUIGesture()));
    gesturePtr->SetOnActionUpdateId(event);
}

void FfiOHOSAceFrameworkGestureHandlerSetOnActionEnd(int64_t id, void (*onActionCallback)(CJGestureEvent))
{
    auto nativeGesture = FFIData::GetData<NativeGesture>(id);
    if (nativeGesture == nullptr) {
        LOGE("FfiOHOSAceFrameworkGestureHandlerSetOnActionEnd: invalid id");
        return;
    }
    auto event = FormatGestureEvenFunction(onActionCallback);

    auto gesturePtr = Referenced::Claim(reinterpret_cast<OHOS::Ace::NG::Gesture*>(nativeGesture->getArkUIGesture()));
    gesturePtr->SetOnActionEndId(event);
}

void FfiOHOSAceFrameworkGestureHandlerSetOnActionCancel(int64_t id, void (*onCancel)())
{
    auto nativeGesture = FFIData::GetData<NativeGesture>(id);
    if (nativeGesture == nullptr) {
        LOGE("FfiOHOSAceFrameworkGestureHandlerSetOnActionCancel: invalid id");
        return;
    }
    auto event = [ffiOnCancel = CJLambda::Create(onCancel)](GestureEvent& info) -> void { ffiOnCancel(); };

    auto gesturePtr = Referenced::Claim(reinterpret_cast<OHOS::Ace::NG::Gesture*>(nativeGesture->getArkUIGesture()));
    gesturePtr->SetOnActionCancelId(event);
}

bool FfiOHOSAceFrameworkGestureGetModifierKeyState(void* baseEventInfoPtr, VectorStringHandle vectorHanle)
{
    if (!baseEventInfoPtr) {
        return false;
    }
    const auto& paramArray = *reinterpret_cast<std::vector<std::string>*>(vectorHanle);
    auto pBaseEventInfo = static_cast<BaseEventInfo*>(baseEventInfoPtr);
    auto pressedKeyCodes = pBaseEventInfo->GetPressedKeyCodes();
    std::vector<std::string> checkKeyCodes;
    std::vector<std::string> validKeyCodes = { "ctrl", "shift", "alt", "fn" };
    for (size_t i = 0; i < paramArray.size(); i++) {
        auto code = paramArray[i];
        std::transform(code.begin(), code.end(), code.begin(), [](char& c) { return std::tolower(c); });
        auto it = std::find(validKeyCodes.begin(), validKeyCodes.end(), code.c_str());
        if (it == validKeyCodes.end()) {
            LOGE("FfiOHOSAceFrameworkGestureGetModifierKeyState: indicate the keys are illegal");
            return false;
        } else {
            checkKeyCodes.emplace_back(code);
        }
    }
    if (checkKeyCodes.empty()) {
        LOGE("FfiOHOSAceFrameworkGestureGetModifierKeyState: indicate the keys are illegal");
        return false;
    }
    return CheckKeysPressed(pressedKeyCodes, checkKeyCodes);
}

void FfiOHOSAceFrameworkViewAbstractSetGestureHandler(int64_t elemId, int64_t gestureId, int32_t priority, int32_t mask)
{
    auto nativeGesture = FFIData::GetData<NativeGesture>(gestureId);
    if (nativeGesture == nullptr) {
        LOGE("FfiOHOSAceFrameworkViewAbstractSetGestureHandler: invalid id");
        return;
    }
    auto nativeNode = GetNodeAPIImpl()->getNodeModifiers()->getFrameNodeModifier()->getFrameNodeById(elemId);
    GetNodeAPIImpl()->getNodeModifiers()->getGestureModifier()->addGestureToNodeWithRefCountDecrease(
        nativeNode, nativeGesture->getArkUIGesture(), priority, mask);
}

void FfiOHOSAceFrameworkViewAbstractSetGestureGroupHandler(
    int64_t elemId, int64_t gestureId, int32_t priority, int32_t mask)
{
    auto nativeGesture = FFIData::GetData<NativeGestureGroup>(gestureId);
    if (nativeGesture == nullptr) {
        LOGE("FfiOHOSAceFrameworkViewAbstractSetGestureGroupHandler: invalid id");
        return;
    }
    auto nativeNode = GetNodeAPIImpl()->getNodeModifiers()->getFrameNodeModifier()->getFrameNodeById(elemId);
    GetNodeAPIImpl()->getNodeModifiers()->getGestureModifier()->addGestureToNodeWithRefCountDecrease(
        nativeNode, nativeGesture->getArkUIGesture(), priority, mask);
}

void FfiOHOSAceFrameworkViewAbstractClearGestureHandlers(int64_t elemId)
{
    auto nativeNode = GetNodeAPIImpl()->getNodeModifiers()->getFrameNodeModifier()->getFrameNodeById(elemId);
    if (!nativeNode) {
        LOGE("FfiOHOSAceFrameworkViewAbstractClearGestureHandlers: invalid id");
        return;
    }
    GetNodeAPIImpl()->getNodeModifiers()->getGestureModifier()->clearGestures(nativeNode);
}

void FfiOHOSAceFrameworkViewAbstractRemoveGestureHandlerByTag(int64_t elemId, const char* tag)
{
    auto nativeNode = GetNodeAPIImpl()->getNodeModifiers()->getFrameNodeModifier()->getFrameNodeById(elemId);
    if (!nativeNode) {
        LOGE("FfiOHOSAceFrameworkViewAbstractRemoveGestureHandlerByTag: invalid id");
        return;
    }
    GetNodeAPIImpl()->getNodeModifiers()->getGestureModifier()->removeGestureFromNodeByTag(nativeNode, tag);
}

void FfiOHOSAceFrameworkViewAbstractSetOnGestureJudgeBegin(int32_t (*callback)(CJGestureInfo, CJBaseGestureEvent))
{
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onGestureJudgeFunc = [ffiCallback = CJLambda::Create(callback), node = frameNode](
                                  const RefPtr<NG::GestureInfo>& gestureInfo,
                                  const std::shared_ptr<BaseGestureEvent>& info) -> GestureJudgeResult {
        CJGestureInfo cjGestureInfo;
        CJBaseGestureEvent baseGestureEvent;
        if (gestureInfo->GetTag()) {
            cjGestureInfo.tag = gestureInfo->GetTag().value().c_str();
        }
        cjGestureInfo.type = static_cast<int32_t>(gestureInfo->GetType());
        cjGestureInfo.isSystemGesture = gestureInfo->IsSystemGesture();

        CJBaseEvent ffiBaseEvent {};
        CJEventTarget ffiEventTarget {};
        CJArea ffiArea {};
        CJPosition ffiPosition {};
        CJPosition ffiGlobalPosition {};

        const auto& eventTarget = info->GetTarget();
        ffiArea.width = eventTarget.area.GetWidth().ConvertToVp();
        ffiArea.height = eventTarget.area.GetHeight().ConvertToVp();
        const auto& localOffset = eventTarget.area.GetOffset();
        const auto& origin = eventTarget.origin;
        ffiPosition.x = localOffset.GetX().ConvertToVp();
        ffiPosition.y = localOffset.GetY().ConvertToVp();
        ffiGlobalPosition.x = origin.GetX().ConvertToVp() + localOffset.GetX().ConvertToVp();
        ffiGlobalPosition.y = origin.GetY().ConvertToVp() + localOffset.GetY().ConvertToVp();
        ffiArea.globalPosition = &ffiGlobalPosition;
        ffiArea.position = &ffiPosition;
        ffiEventTarget.area = &ffiArea;

        ffiBaseEvent.timestamp = info->GetTimeStamp().time_since_epoch().count();
        ffiBaseEvent.source = static_cast<int32_t>(info->GetSourceDevice());
        ffiBaseEvent.pressure = info->GetForce();
        ffiBaseEvent.tiltX = info->GetTiltX().value();
        ffiBaseEvent.tiltY = info->GetTiltY().value();
        ffiBaseEvent.sourceTool = static_cast<int32_t>(info->GetSourceTool());
        ffiBaseEvent.target = &ffiEventTarget;
        ffiBaseEvent.deviceId = info->GetDeviceId();
        ffiBaseEvent.axisHorizontal = nullptr;
        ffiBaseEvent.axisVertical = nullptr;
        baseGestureEvent.baseEvent = &ffiBaseEvent;

        auto& fingerList = info->GetFingerList();
        baseGestureEvent.fingerListSize = static_cast<int32_t>(fingerList.size());
        baseGestureEvent.fingerList = new CJFingerInfo[fingerList.size()];
        TransformNativeCJFingerInfo(baseGestureEvent.fingerList, fingerList);
        FormatGestureType(baseGestureEvent, info, gestureInfo->GetType());
        auto result = ffiCallback(cjGestureInfo, baseGestureEvent);
        return static_cast<GestureJudgeResult>(result);
    };
    ViewAbstractModel::GetInstance()->SetOnGestureJudgeBegin(std::move(onGestureJudgeFunc));
}
}
