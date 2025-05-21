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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_gesture_recognizer_ffi.h"

#include "bridge/common/utils/utils.h"
#include "core/components_ng/gestures/recognizers/pan_recognizer.h"

using namespace OHOS;
using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

std::string CJGestureRecognizer::getTag()
{
    std::string tag;
    auto recognizer = recognizer_.Upgrade();
    if (recognizer) {
        auto gestureInfo = recognizer->GetGestureInfo();
        if (gestureInfo->GetTag().has_value()) {
            tag = gestureInfo->GetTag().value();
        }
    }
    return tag;
}

int32_t CJGestureRecognizer::getType()
{
    GestureTypeName type = GestureTypeName::UNKNOWN;
    auto recognizer = recognizer_.Upgrade();
    if (recognizer) {
        auto gestureInfo = recognizer->GetGestureInfo();
        type = gestureInfo->GetRecognizerType();
    }
    return static_cast<int32_t>(type);
}

int32_t CJGestureRecognizer::getFingers()
{
    return fingers_;
}

bool CJGestureRecognizer::isFingerCountLimit()
{
    return isLimitFingerCount_;
}

bool CJGestureRecognizer::isBuiltIn()
{
    bool isBuiltIn = false;
    auto recognizer = recognizer_.Upgrade();
    if (recognizer) {
        auto gestureInfo = recognizer->GetGestureInfo();
        isBuiltIn = gestureInfo->IsSystemGesture();
    }
    return isBuiltIn;
}

bool CJGestureRecognizer::isEnabled()
{
    bool isEnabled = false;
    auto recognizer = recognizer_.Upgrade();
    if (recognizer) {
        isEnabled = recognizer->IsEnabled();
    }
    return isEnabled;
}

bool CJGestureRecognizer::isValid()
{
    bool isValid = false;
    auto recognizer = recognizer_.Upgrade();
    if (recognizer && recognizer->IsInResponseLinkRecognizers()) {
        isValid = true;
    }
    return isValid;
}

void CJGestureRecognizer::setEnabled(bool enabled)
{
    auto recognizer = recognizer_.Upgrade();
    CHECK_NULL_VOID(recognizer);
    recognizer->SetEnabled(enabled);
}

CJGestureRecognizerState CJGestureRecognizer::getRefereeState()
{
    CJGestureRecognizerState state = CJGestureRecognizerState::FAILED;
    auto recognizer = recognizer_.Upgrade();
    if (recognizer) {
        state = convertRefereeState(recognizer->GetRefereeState());
    }
    return state;
}

sptr<CJEventTargetInfo> CJGestureRecognizer::getEventTargetInfo()
{
    auto recognizer = recognizer_.Upgrade();
    if (!recognizer) {
        return nullptr;
    }
    auto attachNode = recognizer->GetAttachedNode().Upgrade();
    if (!attachNode) {
        return nullptr;
    }
    RefPtr<NG::Pattern> pattern;
    auto scrollablePattern = attachNode->GetPattern<NG::ScrollablePattern>();
    if (scrollablePattern) {
        pattern = scrollablePattern;
    }
    if (pattern) {
        auto scrollableTarget = FFIData::Create<CJScrollableTargetInfo>();
        scrollableTarget->setPattern(pattern);
        scrollableTarget->setId(attachNode->GetInspectorIdValue(""));
        scrollableTarget->setType(CJEventTargetInfoType::SCROLLABLE);
        return scrollableTarget;
    }
    auto eventTargetInfo = FFIData::Create<CJEventTargetInfo>();
    eventTargetInfo->setId(attachNode->GetInspectorIdValue(""));
    return eventTargetInfo;
}

bool CJScrollableTargetInfo::isBegin()
{
    auto pattern = pattern_.Upgrade();
    if (!pattern) {
        return false;
    }
    auto scrollablePattern = AceType::DynamicCast<NG::ScrollablePattern>(pattern);
    if (scrollablePattern) {
        return scrollablePattern->IsAtTop();
    }
    return false;
}

bool CJScrollableTargetInfo::isEnd()
{
    auto pattern = pattern_.Upgrade();
    if (!pattern) {
        return false;
    }
    auto scrollablePattern = AceType::DynamicCast<NG::ScrollablePattern>(pattern);
    if (scrollablePattern) {
        return scrollablePattern->IsAtBottom();
    }
    return false;
}

extern "C" {
ExternalString FfiOHOSAceFrameworkGestureRecognizerGetTag(int64_t id)
{
    auto gestureRecognizer = FFIData::GetData<CJGestureRecognizer>(id);
    if (gestureRecognizer == nullptr) {
        LOGE("FfiOHOSAceFrameworkGestureRecognizerGetTag: invalid id");
        return {};
    }
    auto tag = gestureRecognizer->getTag();
    return ::Utils::MallocCString(tag);
}

int32_t FfiOHOSAceFrameworkGestureRecognizerGetType(int64_t id)
{
    auto gestureRecognizer = FFIData::GetData<CJGestureRecognizer>(id);
    if (gestureRecognizer == nullptr) {
        LOGE("FfiOHOSAceFrameworkGestureRecognizerGetType: invalid id");
        return FFI_ERROR_CODE;
    }
    return gestureRecognizer->getType();
}

bool FfiOHOSAceFrameworkGestureRecognizerIsBuiltIn(int64_t id)
{
    auto gestureRecognizer = FFIData::GetData<CJGestureRecognizer>(id);
    if (gestureRecognizer == nullptr) {
        LOGE("FfiOHOSAceFrameworkGestureRecognizerIsBuiltIn: invalid id");
        return false;
    }
    return gestureRecognizer->isBuiltIn();
}

bool FfiOHOSAceFrameworkGestureRecognizerIsEnabled(int64_t id)
{
    auto gestureRecognizer = FFIData::GetData<CJGestureRecognizer>(id);
    if (gestureRecognizer == nullptr) {
        LOGE("FfiOHOSAceFrameworkGestureRecognizerIsEnabled: invalid id");
        return false;
    }
    return gestureRecognizer->isEnabled();
}

bool FfiOHOSAceFrameworkGestureRecognizerIsValid(int64_t id)
{
    auto gestureRecognizer = FFIData::GetData<CJGestureRecognizer>(id);
    if (gestureRecognizer == nullptr) {
        LOGE("FfiOHOSAceFrameworkGestureRecognizerIsValid: invalid id");
        return false;
    }
    return gestureRecognizer->isValid();
}

void FfiOHOSAceFrameworkGestureRecognizerSetEnabled(int64_t id, bool enabled)
{
    auto gestureRecognizer = FFIData::GetData<CJGestureRecognizer>(id);
    if (gestureRecognizer == nullptr) {
        LOGE("FfiOHOSAceFrameworkGestureRecognizerSetEnabled: invalid id");
        return;
    }
    gestureRecognizer->setEnabled(enabled);
}

int32_t FfiOHOSAceFrameworkGestureRecognizerGetState(int64_t id)
{
    auto gestureRecognizer = FFIData::GetData<CJGestureRecognizer>(id);
    if (gestureRecognizer == nullptr) {
        LOGE("FfiOHOSAceFrameworkGestureRecognizerGestState: invalid id");
        return FFI_ERROR_CODE;
    }
    auto state = gestureRecognizer->getRefereeState();
    return static_cast<int32_t>(state);
}

int64_t FfiOHOSAceFrameworkGestureRecognizerGetEventTargetInfo(int64_t id)
{
    auto gestureRecognizer = FFIData::GetData<CJGestureRecognizer>(id);
    if (gestureRecognizer == nullptr) {
        LOGE("FfiOHOSAceFrameworkGestureRecognizerGetEventTargetInfo: invalid id");
        return FFI_ERROR_CODE;
    }
    auto eventTargetInfo = gestureRecognizer->getEventTargetInfo();
    if (eventTargetInfo == nullptr) {
        LOGE("FfiOHOSAceFrameworkGestureRecognizerGetEventTargetInfo: invalid eventTargetInfo");
        return FFI_ERROR_CODE;
    }
    return eventTargetInfo->GetID();
}

ExternalString FfiOHOSAceFrameworkEventTargetInfoGetId(int64_t id)
{
    auto eventTargetInfo = FFIData::GetData<CJEventTargetInfo>(id);
    if (eventTargetInfo == nullptr) {
        LOGE("FfiOHOSAceFrameworkEventTargetInfoGetId: invalid id");
        return {};
    }
    auto targetId = eventTargetInfo->getId();
    return ::Utils::MallocCString(targetId);
}

int32_t FfiOHOSAceFrameworkEventTargetInfoGetType(int64_t id)
{
    auto eventTargetInfo = FFIData::GetData<CJEventTargetInfo>(id);
    if (eventTargetInfo == nullptr) {
        LOGE("FfiOHOSAceFrameworkEventTargetInfoGetType: invalid id");
        return FFI_ERROR_CODE;
    }
    auto type = eventTargetInfo->getType();
    return static_cast<int32_t>(type);
}

int64_t FfiOHOSAceFrameworkPanRecognizerGetPanGestureOptions(int64_t id)
{
    auto panRecognizer = FFIData::GetData<CJPanRecognizer>(id);
    if (panRecognizer == nullptr) {
        LOGE("FfiOHOSAceFrameworkPanRecognizerGetPanGestureOptions: invalid id");
        return FFI_ERROR_CODE;
    }
    auto panGestureOptions = panRecognizer->getPanGestureOptions();
    return panGestureOptions->GetID();
}

bool FfiOHOSAceFrameworkScrollableTargetInfoIsBegin(int64_t id)
{
    auto scrollableTargetInfo = FFIData::GetData<CJScrollableTargetInfo>(id);
    if (scrollableTargetInfo == nullptr) {
        LOGE("FfiOHOSAceFrameworkScrollableTargetInfoIsBegin: invalid id");
        return false;
    }
    return scrollableTargetInfo->isBegin();
}

bool FfiOHOSAceFrameworkScrollableTargetInfoIsEnd(int64_t id)
{
    auto scrollableTargetInfo = FFIData::GetData<CJScrollableTargetInfo>(id);
    if (scrollableTargetInfo == nullptr) {
        LOGE("FfiOHOSAceFrameworkScrollableTargetInfoIsEnd: invalid id");
        return false;
    }
    return scrollableTargetInfo->isEnd();
}

int64_t FfiOHOSAceFrameworkGestureRecognizerCtor()
{
    auto gestureRecognizer = FFIData::Create<CJGestureRecognizer>();
    if(gestureRecognizer == nullptr) {
        LOGE("FfiOHOSAceFrameworkGestureRecognizerCtor: create fail");
        return FFI_ERROR_CODE;
    }
    return gestureRecognizer->GetID();
}
}
