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
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/gestures/recognizers/pan_recognizer.h"
#include "core/components_ng/pattern/swiper/bridge/swiper_custom_modifier.h"

using namespace OHOS;
using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace {
const ArkUISwiperCustomModifier* GetSwiperCustomModifier()
{
    static const ArkUISwiperCustomModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Swiper");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier =
            reinterpret_cast<const ArkUISwiperCustomModifier*>(module->GetCustomModifier("customModifier"));
    }
    return cachedModifier;
}
} // namespace

std::string CJGestureRecognizer::GetTag() const
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

int32_t CJGestureRecognizer::GetType() const
{
    GestureTypeName type = GestureTypeName::UNKNOWN;
    auto recognizer = recognizer_.Upgrade();
    if (recognizer) {
        auto gestureInfo = recognizer->GetGestureInfo();
        type = gestureInfo->GetRecognizerType();
    }
    return static_cast<int32_t>(type);
}

int32_t CJGestureRecognizer::GetFingers() const
{
    return fingers_;
}

bool CJGestureRecognizer::IsFingerCountLimit() const
{
    return isLimitFingerCount_;
}

bool CJGestureRecognizer::IsBuiltIn() const
{
    bool isBuiltIn = false;
    auto recognizer = recognizer_.Upgrade();
    if (recognizer) {
        auto gestureInfo = recognizer->GetGestureInfo();
        isBuiltIn = gestureInfo->IsSystemGesture();
    }
    return isBuiltIn;
}

bool CJGestureRecognizer::IsEnabled() const
{
    bool isEnabled = false;
    auto recognizer = recognizer_.Upgrade();
    if (recognizer) {
        isEnabled = recognizer->IsEnabled();
    }
    return isEnabled;
}

bool CJGestureRecognizer::IsValid() const
{
    bool isValid = false;
    auto recognizer = recognizer_.Upgrade();
    if (recognizer && recognizer->IsInResponseLinkRecognizers()) {
        isValid = true;
    }
    return isValid;
}

void CJGestureRecognizer::SetEnabled(bool enabled)
{
    auto recognizer = recognizer_.Upgrade();
    CHECK_NULL_VOID(recognizer);
    recognizer->SetEnabled(enabled);
}

CJGestureRecognizerState CJGestureRecognizer::GetRefereeState() const
{
    CJGestureRecognizerState state = CJGestureRecognizerState::FAILED;
    auto recognizer = recognizer_.Upgrade();
    if (recognizer) {
        state = ConvertRefereeState(recognizer->GetRefereeState());
    }
    return state;
}

sptr<CJEventTargetInfo> CJGestureRecognizer::GetEventTargetInfo() const
{
    auto recognizer = recognizer_.Upgrade();
    if (!recognizer) {
        return nullptr;
    }
    auto attachNode = recognizer->GetAttachedNode().Upgrade();
    if (!attachNode) {
        return nullptr;
    }
    if (attachNode->GetPattern<NG::ScrollablePattern>() || attachNode->GetTag() == V2::SWIPER_ETS_TAG) {
        auto scrollableTarget = FFIData::Create<CJScrollableTargetInfo>();
        scrollableTarget->SetNode(attachNode);
        scrollableTarget->SetId(attachNode->GetInspectorIdValue(""));
        scrollableTarget->SetType(CJEventTargetInfoType::SCROLLABLE);
        return scrollableTarget;
    }
    auto eventTargetInfo = FFIData::Create<CJEventTargetInfo>();
    eventTargetInfo->SetId(attachNode->GetInspectorIdValue(""));
    return eventTargetInfo;
}

bool CJScrollableTargetInfo::IsBegin() const
{
    auto node = node_.Upgrade();
    if (!node) {
        return false;
    }
    if (auto scrollablePattern = node->GetPattern<NG::ScrollablePattern>()) {
        return scrollablePattern->IsAtTop();
    }
    if (node->GetTag() == V2::SWIPER_ETS_TAG) {
        auto swiperModifier = GetSwiperCustomModifier();
        return swiperModifier && swiperModifier->isAtStart(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(node)));
    }
    return false;
}

bool CJScrollableTargetInfo::IsEnd() const
{
    auto node = node_.Upgrade();
    if (!node) {
        return false;
    }
    if (auto scrollablePattern = node->GetPattern<NG::ScrollablePattern>()) {
        return scrollablePattern->IsAtBottom();
    }
    if (node->GetTag() == V2::SWIPER_ETS_TAG) {
        auto swiperModifier = GetSwiperCustomModifier();
        return swiperModifier && swiperModifier->isAtEnd(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(node)));
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
    auto tag = gestureRecognizer->GetTag();
    return ::Utils::MallocCString(tag);
}

int32_t FfiOHOSAceFrameworkGestureRecognizerGetType(int64_t id)
{
    auto gestureRecognizer = FFIData::GetData<CJGestureRecognizer>(id);
    if (gestureRecognizer == nullptr) {
        LOGE("FfiOHOSAceFrameworkGestureRecognizerGetType: invalid id");
        return FFI_ERROR_CODE;
    }
    return gestureRecognizer->GetType();
}

bool FfiOHOSAceFrameworkGestureRecognizerIsBuiltIn(int64_t id)
{
    auto gestureRecognizer = FFIData::GetData<CJGestureRecognizer>(id);
    if (gestureRecognizer == nullptr) {
        LOGE("FfiOHOSAceFrameworkGestureRecognizerIsBuiltIn: invalid id");
        return false;
    }
    return gestureRecognizer->IsBuiltIn();
}

bool FfiOHOSAceFrameworkGestureRecognizerIsEnabled(int64_t id)
{
    auto gestureRecognizer = FFIData::GetData<CJGestureRecognizer>(id);
    if (gestureRecognizer == nullptr) {
        LOGE("FfiOHOSAceFrameworkGestureRecognizerIsEnabled: invalid id");
        return false;
    }
    return gestureRecognizer->IsEnabled();
}

bool FfiOHOSAceFrameworkGestureRecognizerIsValid(int64_t id)
{
    auto gestureRecognizer = FFIData::GetData<CJGestureRecognizer>(id);
    if (gestureRecognizer == nullptr) {
        LOGE("FfiOHOSAceFrameworkGestureRecognizerIsValid: invalid id");
        return false;
    }
    return gestureRecognizer->IsValid();
}

void FfiOHOSAceFrameworkGestureRecognizerSetEnabled(int64_t id, bool enabled)
{
    auto gestureRecognizer = FFIData::GetData<CJGestureRecognizer>(id);
    if (gestureRecognizer == nullptr) {
        LOGE("FfiOHOSAceFrameworkGestureRecognizerSetEnabled: invalid id");
        return;
    }
    gestureRecognizer->SetEnabled(enabled);
}

int32_t FfiOHOSAceFrameworkGestureRecognizerGetState(int64_t id)
{
    auto gestureRecognizer = FFIData::GetData<CJGestureRecognizer>(id);
    if (gestureRecognizer == nullptr) {
        LOGE("FfiOHOSAceFrameworkGestureRecognizerGestState: invalid id");
        return FFI_ERROR_CODE;
    }
    auto state = gestureRecognizer->GetRefereeState();
    return static_cast<int32_t>(state);
}

int64_t FfiOHOSAceFrameworkGestureRecognizerGetEventTargetInfo(int64_t id)
{
    auto gestureRecognizer = FFIData::GetData<CJGestureRecognizer>(id);
    if (gestureRecognizer == nullptr) {
        LOGE("FfiOHOSAceFrameworkGestureRecognizerGetEventTargetInfo: invalid id");
        return FFI_ERROR_CODE;
    }
    auto eventTargetInfo = gestureRecognizer->GetEventTargetInfo();
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
    auto targetId = eventTargetInfo->GetId();
    return ::Utils::MallocCString(targetId);
}

int32_t FfiOHOSAceFrameworkEventTargetInfoGetType(int64_t id)
{
    auto eventTargetInfo = FFIData::GetData<CJEventTargetInfo>(id);
    if (eventTargetInfo == nullptr) {
        LOGE("FfiOHOSAceFrameworkEventTargetInfoGetType: invalid id");
        return FFI_ERROR_CODE;
    }
    auto type = eventTargetInfo->GetType();
    return static_cast<int32_t>(type);
}

int64_t FfiOHOSAceFrameworkPanRecognizerGetPanGestureOptions(int64_t id)
{
    auto panRecognizer = FFIData::GetData<CJPanRecognizer>(id);
    if (panRecognizer == nullptr) {
        LOGE("FfiOHOSAceFrameworkPanRecognizerGetPanGestureOptions: invalid id");
        return FFI_ERROR_CODE;
    }
    auto panGestureOptions = panRecognizer->GetPanGestureOptions();
    if (panGestureOptions == nullptr) {
        LOGE("FfiOHOSAceFrameworkPanRecognizerGetPanGestureOptions: get panGestureOptions failed.");
        return FFI_ERROR_CODE;
    }
    return panGestureOptions->GetID();
}

bool FfiOHOSAceFrameworkScrollableTargetInfoIsBegin(int64_t id)
{
    auto scrollableTargetInfo = FFIData::GetData<CJScrollableTargetInfo>(id);
    if (scrollableTargetInfo == nullptr) {
        LOGE("FfiOHOSAceFrameworkScrollableTargetInfoIsBegin: invalid id");
        return false;
    }
    return scrollableTargetInfo->IsBegin();
}

bool FfiOHOSAceFrameworkScrollableTargetInfoIsEnd(int64_t id)
{
    auto scrollableTargetInfo = FFIData::GetData<CJScrollableTargetInfo>(id);
    if (scrollableTargetInfo == nullptr) {
        LOGE("FfiOHOSAceFrameworkScrollableTargetInfoIsEnd: invalid id");
        return false;
    }
    return scrollableTargetInfo->IsEnd();
}

int64_t FfiOHOSAceFrameworkGestureRecognizerCtor()
{
    auto gestureRecognizer = FFIData::Create<CJGestureRecognizer>();
    if (gestureRecognizer == nullptr) {
        LOGE("FfiOHOSAceFrameworkGestureRecognizerCtor: create fail");
        return FFI_ERROR_CODE;
    }
    return gestureRecognizer->GetID();
}
}
