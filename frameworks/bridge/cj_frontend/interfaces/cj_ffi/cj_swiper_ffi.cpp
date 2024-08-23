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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_swiper_ffi.h"


#include "bridge/cj_frontend/cppview/swiper_controller.h"
#include "bridge/cj_frontend/cppview/view_abstract.h"
#include "cj_lambda.h"
#include "bridge/common/utils/utils.h"
#include "core/components_ng/pattern/swiper/swiper_model.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace {
const std::vector<SwiperDisplayMode> SWIPER_DISPLAY_MODES = { SwiperDisplayMode::STRETCH,
    SwiperDisplayMode::AUTO_LINEAR };
const std::vector<EdgeEffect> EDGE_EFFECTS = { EdgeEffect::SPRING, EdgeEffect::FADE, EdgeEffect::NONE };
} // namespace

extern "C" {
void FfiOHOSAceFrameworkSwiperCreate(int64_t controllerId)
{
    auto nativeSwiperController = FFIData::GetData<NativeSwiperController>(controllerId);
    if (nativeSwiperController == nullptr) {
        LOGE("Swiper create error, Cannot get NativeSwiperController by id: %{public}" PRId64, controllerId);
        return;
    }
    auto controller = SwiperModel::GetInstance()->Create();
    nativeSwiperController->SetController(controller);
}

void FfiOHOSAceFrameworkSwiperSetAutoplay(bool autoPlay)
{
    SwiperModel::GetInstance()->SetAutoPlay(autoPlay);
}

void FfiOHOSAceFrameworkSwiperSetDigital(bool digitalIndicator)
{
    // deleted in the future
}

void FfiOHOSAceFrameworkSwiperSetDuration(uint32_t duration)
{
    SwiperModel::GetInstance()->SetDuration(duration);
}

void FfiOHOSAceFrameworkSwiperSetIndex(uint32_t index)
{
    SwiperModel::GetInstance()->SetIndex(index);
}

void FfiOHOSAceFrameworkSwiperSetInterval(uint32_t interval)
{
    SwiperModel::GetInstance()->SetAutoPlayInterval(interval);
}

void FfiOHOSAceFrameworkSwiperSetLoop(bool loop)
{
    SwiperModel::GetInstance()->SetLoop(loop);
}

void FfiOHOSAceFrameworkSwiperSetVertical(bool isVertical)
{
    SwiperModel::GetInstance()->SetDirection(isVertical ? Axis::VERTICAL : Axis::HORIZONTAL);
}

void FfiOHOSAceFrameworkSwiperSetIndicator(bool showIndicator)
{
    SwiperModel::GetInstance()->SetShowIndicator(showIndicator);
}

void FfiOHOSAceFrameworkSwiperSetWidth(double width, int32_t unit)
{
    Dimension value(width, static_cast<DimensionUnit>(unit));
    ViewAbstractModel::GetInstance()->SetWidth(value);
    SwiperModel::GetInstance()->SetMainSwiperSizeWidth();
}

void FfiOHOSAceFrameworkSwiperSetHeight(double height, int32_t unit)
{
    Dimension value(height, static_cast<DimensionUnit>(unit));
    ViewAbstractModel::GetInstance()->SetHeight(value);
    SwiperModel::GetInstance()->SetMainSwiperSizeHeight();
}

void FfiOHOSAceFrameworkSwiperSetSize(double width, int32_t widthUnit, double height, int32_t heightUnit)
{
    Dimension widthValue(width, static_cast<DimensionUnit>(widthUnit));
    Dimension heightValue(height, static_cast<DimensionUnit>(heightUnit));
    ViewAbstractModel::GetInstance()->SetWidth(widthValue);
    ViewAbstractModel::GetInstance()->SetHeight(heightValue);
}

void FfiOHOSAceFrameworkSwiperSetIndicatorStyle(CJIndicatorStyle value)
{
    Dimension leftValue(value.left, static_cast<DimensionUnit>(value.leftUnit));
    Dimension topValue(value.top, static_cast<DimensionUnit>(value.topUnit));
    Dimension rightValue(value.right, static_cast<DimensionUnit>(value.rightUnit));
    Dimension bottomValue(value.bottom, static_cast<DimensionUnit>(value.bottomUnit));
    Dimension sizeValue(value.size, static_cast<DimensionUnit>(value.sizeUnit));
    SwiperParameters swiperParameters {
        .dimLeft = leftValue,
        .dimTop = topValue,
        .dimRight = rightValue,
        .dimBottom = bottomValue,
        .maskValue = value.mask,
        .colorVal = Color(value.color),
        .selectedColorVal = Color(value.selectedColor) };
    SwiperModel::GetInstance()->SetIndicatorStyle(swiperParameters);
}

void FfiOHOSAceFrameworkSwiperSetItemSpace(double itemSpace, int32_t unit)
{
    Dimension value(itemSpace, static_cast<DimensionUnit>(unit));
    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    SwiperModel::GetInstance()->SetItemSpace(value);
}

void FfiOHOSAceFrameworkSwiperSetDisplayMode(int32_t modeValue)
{
    if (!Utils::CheckParamsValid(modeValue, SWIPER_DISPLAY_MODES.size())) {
        LOGE("invalid value for swiper display mode");
        return;
    }
    SwiperModel::GetInstance()->SetDisplayMode(SWIPER_DISPLAY_MODES[modeValue]);
}

void FfiOHOSAceFrameworkSwiperSetEffectMode(int32_t modeValue)
{
    if (!Utils::CheckParamsValid(modeValue, EDGE_EFFECTS.size())) {
        LOGE("invalid value for effect mode");
        return;
    }
    SwiperModel::GetInstance()->SetEdgeEffect(EDGE_EFFECTS[modeValue]);
}

void FfiOHOSAceFrameworkSwiperSetDisplayCount(int32_t count)
{
    SwiperModel::GetInstance()->SetDisplayCount(count);
}

void FfiOHOSAceFrameworkSwiperSetCachedCount(int32_t cachedCount)
{
    SwiperModel::GetInstance()->SetCachedCount(cachedCount);
}

void FfiOHOSAceFrameworkSwiperSetEnabled(bool value)
{
    ViewAbstract::CjEnabled(value);
    SwiperModel::GetInstance()->SetEnabled(value);
}

void FfiOHOSAceFrameworkSwiperSetDisableSwipe(bool disable)
{
    SwiperModel::GetInstance()->SetDisableSwipe(disable);
}

void FfiOHOSAceFrameworkSwiperSetCurve(const char* curveStr)
{
    RefPtr<Curve> curve = CreateCurve(curveStr);
    SwiperModel::GetInstance()->SetCurve(curve);
}

void FfiOHOSAceFrameworkSwiperSetOnChange(void (*callback)(int32_t index))
{
    auto lambda = CJLambda::Create(callback);
    auto onChange = [lambda](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        if (!swiperInfo) {
            return;
        }
        lambda(swiperInfo->GetIndex());
    };
    SwiperModel::GetInstance()->SetOnChange(std::move(onChange));
}

int64_t FfiOHOSAceFrameworkSwiperControllerCtor()
{
    auto ret_ = FFIData::Create<NativeSwiperController>();
    if (ret_ == nullptr) {
        return FFI_ERROR_CODE;
    }
    return ret_->GetID();
}

void FfiOHOSAceFrameworkSwiperControllerShowNext(int64_t selfId)
{
    auto self_ = FFIData::GetData<NativeSwiperController>(selfId);
    if (self_ != nullptr) {
        self_->ShowNext();
    }
}

void FfiOHOSAceFrameworkSwiperControllerShowPrevious(int64_t selfId)
{
    auto self_ = FFIData::GetData<NativeSwiperController>(selfId);
    if (self_ != nullptr) {
        self_->ShowPrevious();
    }
}

void FfiOHOSAceFrameworkSwiperControllerFinishAnimation(int64_t selfId)
{
    auto self_ = FFIData::GetData<NativeSwiperController>(selfId);
    if (self_ != nullptr) {
        self_->FinishAnimation();
    }
}

void FfiOHOSAceFrameworkSwiperControllerFinishAnimationWithCallback(int64_t selfId, void (*callback)())
{
    auto self_ = FFIData::GetData<NativeSwiperController>(selfId);
    if (self_ != nullptr) {
        self_->FinishAnimationWithCallback(CJLambda::Create(callback));
    }
}
}
