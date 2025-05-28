/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef OHOS_ACE_FRAMEWORK_CJ_GESTURE_RECOGNIZER_H
#define OHOS_ACE_FRAMEWORK_CJ_GESTURE_RECOGNIZER_H

#include <cstdint>

#include "ffi_remote_data.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_gesture_ffi.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/gestures/gesture_info.h"
#include "bridge/cj_frontend/cppview/gesture.h"

namespace OHOS::Ace::Framework {
enum class CJGestureRecognizerState {
    UNKNOWN = -1,
    READY = 0,
    DETECTING = 1,
    PENDING = 2,
    BLOCKED = 3,
    SUCCESSFUL = 4,
    FAILED = 5,
};

// used to determing the type of eventTargetInfo on the cangjie side
enum class CJEventTargetInfoType {
    NORMAL = 0,
    SCROLLABLE = 1,
};

class CJEventTargetInfo : public OHOS::FFI::FFIData {
DECL_TYPE(CJEventTargetInfo, OHOS::FFI::FFIData)
public:
    CJEventTargetInfo() : FFIData() {}

    void setId(const std::string& inspectorId)
    {
        inspectorId_ = inspectorId;
    }

    std::string getId()
    {
        return inspectorId_;
    }

    void setType(const CJEventTargetInfoType type)
    {
        type_ = type;
    }

    CJEventTargetInfoType getType()
    {
        return type_;
    }

private:
    std::string inspectorId_;
    CJEventTargetInfoType type_ = CJEventTargetInfoType::NORMAL;
};

class CJScrollableTargetInfo : public CJEventTargetInfo {
public:
    CJScrollableTargetInfo() : CJEventTargetInfo() {}

    void setPattern(const WeakPtr<NG::Pattern>& pattern)
    {
        pattern_ = pattern;
    }

    bool isBegin();

    bool isEnd();

private:
    WeakPtr<NG::Pattern> pattern_;
};

class CJGestureRecognizer : public OHOS::FFI::FFIData {
DECL_TYPE(CJGestureRecognizer, OHOS::FFI::FFIData)
public:
    CJGestureRecognizer() : FFIData() {}

    void update(const RefPtr<NG::NGGestureRecognizer>& recognizer)
    {
        recognizer_ = recognizer;
    }

    WeakPtr<NG::NGGestureRecognizer> GetRecognizer()
    {
        return recognizer_;
    }

    std::string getTag();

    int32_t getType();

    int32_t getFingers();

    bool isFingerCountLimit();

    bool isBuiltIn();

    bool isEnabled();

    void setEnabled(bool enabled);

    bool isValid();

    CJGestureRecognizerState getRefereeState();

    sptr<CJEventTargetInfo> getEventTargetInfo();

    static CJGestureRecognizerState convertRefereeState(NG::RefereeState state)
    {
        switch (state) {
            case NG::RefereeState::READY:
                return CJGestureRecognizerState::READY;
            case NG::RefereeState::DETECTING:
                return CJGestureRecognizerState::DETECTING;
            case NG::RefereeState::PENDING:
                return CJGestureRecognizerState::PENDING;
            case NG::RefereeState::PENDING_BLOCKED:
            case NG::RefereeState::SUCCEED_BLOCKED:
                return CJGestureRecognizerState::BLOCKED;
            case NG::RefereeState::SUCCEED:
                return CJGestureRecognizerState::SUCCESSFUL;
            case NG::RefereeState::FAIL:
                return CJGestureRecognizerState::FAILED;
            default:
                return CJGestureRecognizerState::UNKNOWN;
        }
    }

private:
    WeakPtr<NG::NGGestureRecognizer> recognizer_;

protected:
    bool isLimitFingerCount_ = false;
    int32_t fingers_ = 1;
};

class CJMultiFingerRecognizer : public CJGestureRecognizer {
public:
    CJMultiFingerRecognizer() : CJGestureRecognizer() {}

    void update(const RefPtr<NG::MultiFingersRecognizer>& recognizer)
    {
        CJGestureRecognizer::update(recognizer);
        isLimitFingerCount_ = recognizer->GetLimitFingerCount();
        fingers_ = recognizer->GetFingers();
    }
};

class CJPanRecognizer : public CJMultiFingerRecognizer {
public:
    CJPanRecognizer() : CJMultiFingerRecognizer() {}

    void update(const RefPtr<NG::PanRecognizer>& recognizer)
    {
        CJMultiFingerRecognizer::update(recognizer);
        setPanGestureOptions(
            recognizer->GetFingers(), recognizer->GetDistance(), recognizer->GetDirection());
    }

    sptr<NativePanGestureOption> getPanGestureOptions()
    {
        PanDirection direction;
        auto panGestureOption = FFIData::Create<NativePanGestureOption>(0, direction, 0.0);
        panGestureOption->SetPanGestureOption(panGestureOption_);
        return panGestureOption;
    }

private:
    void setPanGestureOptions(int32_t fingers, double distance, PanDirection direction)
    {
        panGestureOption_ = AceType::MakeRefPtr<PanGestureOption>();
        panGestureOption_->SetFingers(fingers);
        panGestureOption_->SetDistance(distance);
        panGestureOption_->SetDirection(direction);
    }
    RefPtr<PanGestureOption> panGestureOption_;
};

} //namespace OHOS::Ace::Framework

extern "C" {
CJ_EXPORT ExternalString FfiOHOSAceFrameworkGestureRecognizerGetTag(int64_t id);
CJ_EXPORT int32_t FfiOHOSAceFrameworkGestureRecognizerGetType(int64_t id);
CJ_EXPORT bool FfiOHOSAceFrameworkGestureRecognizerIsBuiltIn(int64_t id);
CJ_EXPORT bool FfiOHOSAceFrameworkGestureRecognizerIsEnabled(int64_t id);
CJ_EXPORT void FfiOHOSAceFrameworkGestureRecognizerSetEnabled(int64_t id, bool enabled);
CJ_EXPORT bool FfiOHOSAceFrameworkGestureRecognizerIsValid(int64_t id);
CJ_EXPORT int32_t FfiOHOSAceFrameworkGestureRecognizerGetState(int64_t id);
CJ_EXPORT int64_t FfiOHOSAceFrameworkGestureRecognizerGetEventTargetInfo(int64_t id);
CJ_EXPORT ExternalString FfiOHOSAceFrameworkEventTargetInfoGetId(int64_t id);
CJ_EXPORT int64_t FfiOHOSAceFrameworkPanRecognizerGetPanGestureOptions(int64_t id);
CJ_EXPORT bool FfiOHOSAceFrameworkScrollableTargetInfoIsEnd(int64_t id);
CJ_EXPORT bool FfiOHOSAceFrameworkScrollableTargetInfoIsBegin(int64_t id);
CJ_EXPORT int32_t FfiOHOSAceFrameworkEventTargetInfoGetType(int64_t id);
CJ_EXPORT int64_t FfiOHOSAceFrameworkGestureRecognizerCtor();
}
#endif // OHOS_ACE_FRAMEWORK_CJ_GESTURE_RECOGNIZER_H
