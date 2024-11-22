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

#include "swiper_helper.h"

#include "base/log/dump_log.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_layout_property.h"

namespace OHOS::Ace::NG {
void SwiperHelper::InitSwiperController(const RefPtr<SwiperController>& controller, const WeakPtr<SwiperPattern>& weak)
{
    CHECK_NULL_VOID(controller);
    controller->SetSwipeToImpl([weak](int32_t index, bool reverse) {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        swiper->SwipeTo(index);
    });

    controller->SetSwipeToWithoutAnimationImpl([weak](int32_t index) {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        swiper->SwipeToWithoutAnimation(index);
    });

    controller->SetShowNextImpl([weak]() {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        auto swiperNode = swiper->GetHost();
        CHECK_NULL_VOID(swiperNode);
        TAG_LOGI(AceLogTag::ACE_SWIPER, "Swiper ShowNext, id:%{public}d", swiperNode->GetId());
        swiper->ShowNext();
    });

    controller->SetShowPrevImpl([weak]() {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        auto swiperNode = swiper->GetHost();
        CHECK_NULL_VOID(swiperNode);
        TAG_LOGI(AceLogTag::ACE_SWIPER, "Swiper ShowPrevious, id:%{public}d", swiperNode->GetId());
        swiper->ShowPrevious();
    });

    controller->SetChangeIndexImpl([weak](int32_t index, bool useAnimation) {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        TAG_LOGI(AceLogTag::ACE_SWIPER, "Swiper ChangeIndex %{public}d, useAnimation:%{public}d", index, useAnimation);
        swiper->ChangeIndex(index, useAnimation);
    });

    controller->SetFinishImpl([weak]() {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        swiper->FinishAnimation();
    });

    controller->SetPreloadItemsImpl([weak](const std::set<int32_t>& indexSet) {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        swiper->PreloadItems(indexSet);
    });
}

void SwiperHelper::SaveDigitIndicatorProperty(const RefPtr<FrameNode>& indicatorNode, SwiperPattern& swiper)
{
    CHECK_NULL_VOID(indicatorNode);
    auto indicatorProps = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    CHECK_NULL_VOID(indicatorProps);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    const auto theme = pipeline->GetTheme<SwiperIndicatorTheme>();
    const auto digitalParams = swiper.GetSwiperDigitalParameters();
    CHECK_NULL_VOID(digitalParams);
    indicatorProps->ResetIndicatorLayoutStyle();
    if (digitalParams->dimLeft.has_value()) {
        indicatorProps->UpdateLeft(digitalParams->dimLeft.value());
    }
    if (digitalParams->dimTop.has_value()) {
        indicatorProps->UpdateTop(digitalParams->dimTop.value());
    }
    if (digitalParams->dimRight.has_value()) {
        indicatorProps->UpdateRight(digitalParams->dimRight.value());
    }
    if (digitalParams->dimBottom.has_value()) {
        indicatorProps->UpdateBottom(digitalParams->dimBottom.value());
    }
    indicatorProps->UpdateFontColor(
        digitalParams->fontColor.value_or(theme->GetDigitalIndicatorTextStyle().GetTextColor()));
    indicatorProps->UpdateSelectedFontColor(
        digitalParams->selectedFontColor.value_or(theme->GetDigitalIndicatorTextStyle().GetTextColor()));
    indicatorProps->UpdateFontSize(
        digitalParams->fontSize.value_or(theme->GetDigitalIndicatorTextStyle().GetFontSize()));
    indicatorProps->UpdateSelectedFontSize(
        digitalParams->selectedFontSize.value_or(theme->GetDigitalIndicatorTextStyle().GetFontSize()));
    indicatorProps->UpdateFontWeight(
        digitalParams->fontWeight.value_or(theme->GetDigitalIndicatorTextStyle().GetFontWeight()));
    indicatorProps->UpdateSelectedFontWeight(
        digitalParams->selectedFontWeight.value_or(theme->GetDigitalIndicatorTextStyle().GetFontWeight()));
    auto props = swiper.GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(props);
    props->UpdateLeft(digitalParams->dimLeft.value_or(0.0_vp));
    props->UpdateTop(digitalParams->dimTop.value_or(0.0_vp));
    props->UpdateRight(digitalParams->dimRight.value_or(0.0_vp));
    props->UpdateBottom(digitalParams->dimBottom.value_or(0.0_vp));
    swiper.SetDigitStartAndEndProperty(indicatorNode);
}

void SwiperHelper::SaveDotIndicatorProperty(const RefPtr<FrameNode>& indicatorNode, SwiperPattern& swiper)
{
    CHECK_NULL_VOID(indicatorNode);
    auto indicatorProps = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    CHECK_NULL_VOID(indicatorProps);
    const auto params = swiper.GetSwiperParameters();
    CHECK_NULL_VOID(params);
    indicatorProps->ResetIndicatorLayoutStyle();
    if (params->dimLeft.has_value()) {
        indicatorProps->UpdateLeft(params->dimLeft.value());
    }
    if (params->dimTop.has_value()) {
        indicatorProps->UpdateTop(params->dimTop.value());
    }
    if (params->dimRight.has_value()) {
        indicatorProps->UpdateRight(params->dimRight.value());
    }
    if (params->dimBottom.has_value()) {
        indicatorProps->UpdateBottom(params->dimBottom.value());
    }
    const bool isRtl = swiper.GetNonAutoLayoutDirection() == TextDirection::RTL;
    if (params->dimStart.has_value()) {
        auto dimValue = params->dimStart.value();
        isRtl ? indicatorProps->UpdateRight(dimValue) : indicatorProps->UpdateLeft(dimValue);
    } else if (params->dimEnd.has_value()) {
        auto dimValue = params->dimEnd.value();
        isRtl ? indicatorProps->UpdateLeft(dimValue) : indicatorProps->UpdateRight(dimValue);
    }

    swiper.UpdatePaintProperty(indicatorNode);
}

namespace {
void DumpPanDirection(const PanDirection& pan)
{
    switch (pan.type) {
        case PanDirection::NONE: {
            DumpLog::GetInstance().AddDesc("PanDirection:NONE");
            break;
        }
        case PanDirection::LEFT: {
            DumpLog::GetInstance().AddDesc("PanDirection:LEFT");
            break;
        }
        case PanDirection::RIGHT: {
            DumpLog::GetInstance().AddDesc("PanDirection:RIGHT");
            break;
        }
        case PanDirection::HORIZONTAL: {
            DumpLog::GetInstance().AddDesc("PanDirection:HORIZONTAL");
            break;
        }
        case PanDirection::UP: {
            DumpLog::GetInstance().AddDesc("PanDirection:UP");
            break;
        }
        case PanDirection::DOWN: {
            DumpLog::GetInstance().AddDesc("PanDirection:DOWN");
            break;
        }
        case PanDirection::VERTICAL: {
            DumpLog::GetInstance().AddDesc("PanDirection:VERTICAL");
            break;
        }
        case PanDirection::ALL: {
            DumpLog::GetInstance().AddDesc("PanDirection:ALL");
            break;
        }
        default: {
            break;
        }
    }
}

void DumpDirection(Axis direction)
{
    switch (direction) {
        case Axis::NONE: {
            DumpLog::GetInstance().AddDesc("Axis:NONE");
            break;
        }
        case Axis::HORIZONTAL: {
            DumpLog::GetInstance().AddDesc("Axis:HORIZONTAL");
            break;
        }
        case Axis::FREE: {
            DumpLog::GetInstance().AddDesc("Axis:FREE");
            break;
        }
        case Axis::VERTICAL: {
            DumpLog::GetInstance().AddDesc("Axis:VERTICAL");
            break;
        }
        default: {
            break;
        }
    }
}

void DumpIndicatorType(const std::optional<SwiperIndicatorType>& type)
{
    if (type.has_value()) {
        switch (type.value()) {
            case SwiperIndicatorType::DOT: {
                DumpLog::GetInstance().AddDesc("SwiperIndicatorType:DOT");
                break;
            }
            case SwiperIndicatorType::DIGIT: {
                DumpLog::GetInstance().AddDesc("SwiperIndicatorType:DIGIT");
                break;
            }
            default: {
                break;
            }
        }
    } else {
        DumpLog::GetInstance().AddDesc("lastSwiperIndicatorType:null");
    }
}

void DumpItemPosition(const SwiperLayoutAlgorithm::PositionMap& positions)
{
    for (const auto& item : positions) {
        DumpLog::GetInstance().AddDesc(std::string("id:")
                                           .append(std::to_string(item.first))
                                           .append(",startPos:")
                                           .append(std::to_string(item.second.startPos))
                                           .append(",endPos:" + std::to_string(item.second.endPos)));
    }
}
} // namespace

void SwiperHelper::DumpAdvanceInfo(SwiperPattern& swiper)
{
    DumpInfoAddPositionDesc(swiper);
    DumpInfoAddGestureDesc(swiper);
    DumpIndicatorType(swiper.lastSwiperIndicatorType_);
    DumpInfoAddAnimationDesc(swiper);
    if (!swiper.itemPosition_.empty()) {
        DumpLog::GetInstance().AddDesc("-----------start print itemPosition------------");
        DumpItemPosition(swiper.itemPosition_);
        DumpLog::GetInstance().AddDesc("-----------end print itemPosition------------");
    }
    if (!swiper.itemPositionInAnimation_.empty()) {
        DumpLog::GetInstance().AddDesc("-----------start print itemPositionInAnimation------------");
        DumpItemPosition(swiper.itemPositionInAnimation_);
        DumpLog::GetInstance().AddDesc("-----------end print itemPositionInAnimation------------");
    }
    DumpPanDirection(swiper.panDirection_);
    DumpDirection(swiper.direction_);
    swiper.IsDisableSwipe() ? DumpLog::GetInstance().AddDesc("disableSwipe:true")
                            : DumpLog::GetInstance().AddDesc("disableSwipe:false");
    swiper.GetNonAutoLayoutDirection() == TextDirection::RTL ? DumpLog::GetInstance().AddDesc("TextDirection::RTL")
                                                             : DumpLog::GetInstance().AddDesc("TextDirection::LTR");
}

void SwiperHelper::DumpInfoAddPositionDesc(SwiperPattern& swiper)
{
    swiper.crossMatchChild_ ? DumpLog::GetInstance().AddDesc("crossMatchChild:true")
                            : DumpLog::GetInstance().AddDesc("crossMatchChild:false");
    swiper.uiCastJumpIndex_.has_value()
        ? DumpLog::GetInstance().AddDesc("uiCastJumpIndex:" + std::to_string(swiper.uiCastJumpIndex_.value()))
        : DumpLog::GetInstance().AddDesc("uiCastJumpIndex:null");
    swiper.jumpIndex_.has_value()
        ? DumpLog::GetInstance().AddDesc("jumpIndex:" + std::to_string(swiper.jumpIndex_.value()))
        : DumpLog::GetInstance().AddDesc("jumpIndex:null");
    swiper.targetIndex_.has_value()
        ? DumpLog::GetInstance().AddDesc("targetIndex:" + std::to_string(swiper.targetIndex_.value()))
        : DumpLog::GetInstance().AddDesc("targetIndex:null");
    swiper.pauseTargetIndex_.has_value()
        ? DumpLog::GetInstance().AddDesc("pauseTargetIndex:" + std::to_string(swiper.pauseTargetIndex_.value()))
        : DumpLog::GetInstance().AddDesc("pauseTargetIndex:null");
    DumpLog::GetInstance().AddDesc("currentIndex:" + std::to_string(swiper.currentIndex_));
    DumpLog::GetInstance().AddDesc("oldIndex:" + std::to_string(swiper.oldIndex_));
    DumpLog::GetInstance().AddDesc("currentOffset:" + std::to_string(swiper.currentOffset_));
    DumpLog::GetInstance().AddDesc("fadeOffset:" + std::to_string(swiper.fadeOffset_));
    DumpLog::GetInstance().AddDesc("touchBottomRate:" + std::to_string(swiper.touchBottomRate_));
    DumpLog::GetInstance().AddDesc("currentIndexOffset:" + std::to_string(swiper.currentIndexOffset_));
    DumpLog::GetInstance().AddDesc("gestureSwipeIndex:" + std::to_string(swiper.gestureSwipeIndex_));
    DumpLog::GetInstance().AddDesc("currentFirstIndex:" + std::to_string(swiper.currentFirstIndex_));
    DumpLog::GetInstance().AddDesc("startMainPos:" + std::to_string(swiper.startMainPos_));
    DumpLog::GetInstance().AddDesc("endMainPos:" + std::to_string(swiper.endMainPos_));
    DumpLog::GetInstance().AddDesc("contentMainSize:" + std::to_string(swiper.contentMainSize_));
    DumpLog::GetInstance().AddDesc("contentCrossSize:" + std::to_string(swiper.contentCrossSize_));
}

void SwiperHelper::DumpInfoAddGestureDesc(SwiperPattern& swiper)
{
    swiper.isLastIndicatorFocused_ ? DumpLog::GetInstance().AddDesc("isLastIndicatorFocused:true")
                                   : DumpLog::GetInstance().AddDesc("isLastIndicatorFocused:false");
    swiper.moveDirection_ ? DumpLog::GetInstance().AddDesc("moveDirection:true")
                          : DumpLog::GetInstance().AddDesc("moveDirection:false");
    swiper.indicatorDoingAnimation_ ? DumpLog::GetInstance().AddDesc("indicatorDoingAnimation:true")
                                    : DumpLog::GetInstance().AddDesc("indicatorDoingAnimation:false");
    swiper.hasVisibleChangeRegistered_ ? DumpLog::GetInstance().AddDesc("hasVisibleChangeRegistered:true")
                                       : DumpLog::GetInstance().AddDesc("hasVisibleChangeRegistered:false");
    swiper.isVisible_ ? DumpLog::GetInstance().AddDesc("isVisible:true")
                      : DumpLog::GetInstance().AddDesc("isVisible:false");
    swiper.isVisibleArea_ ? DumpLog::GetInstance().AddDesc("isVisibleArea:true")
                          : DumpLog::GetInstance().AddDesc("isVisibleArea:false");
    swiper.isWindowShow_ ? DumpLog::GetInstance().AddDesc("isWindowShow:true")
                         : DumpLog::GetInstance().AddDesc("isWindowShow:false");
    swiper.isCustomSize_ ? DumpLog::GetInstance().AddDesc("IsCustomSize:true")
                         : DumpLog::GetInstance().AddDesc("IsCustomSize:false");
    swiper.indicatorIsBoolean_ ? DumpLog::GetInstance().AddDesc("indicatorIsBoolean:true")
                               : DumpLog::GetInstance().AddDesc("indicatorIsBoolean:false");
    swiper.isAtHotRegion_ ? DumpLog::GetInstance().AddDesc("isAtHotRegion:true")
                          : DumpLog::GetInstance().AddDesc("isAtHotRegion:false");
    swiper.isDragging_ ? DumpLog::GetInstance().AddDesc("isDragging:true")
                       : DumpLog::GetInstance().AddDesc("isDragging:false");
    swiper.isTouchDown_ ? DumpLog::GetInstance().AddDesc("isTouchDown:true")
                        : DumpLog::GetInstance().AddDesc("isTouchDown:false");
    swiper.isIndicatorLongPress_ ? DumpLog::GetInstance().AddDesc("isIndicatorLongPress:true")
                                 : DumpLog::GetInstance().AddDesc("isIndicatorLongPress:false");
    swiper.preLoop_.has_value() ? DumpLog::GetInstance().AddDesc("preLoop:" + std::to_string(swiper.preLoop_.value()))
                                : DumpLog::GetInstance().AddDesc("preLoop:null");
    swiper.indicatorId_.has_value()
        ? DumpLog::GetInstance().AddDesc("indicatorId:" + std::to_string(swiper.indicatorId_.value()))
        : DumpLog::GetInstance().AddDesc("indicatorId:null");
    swiper.leftButtonId_.has_value()
        ? DumpLog::GetInstance().AddDesc("leftButtonId:" + std::to_string(swiper.leftButtonId_.value()))
        : DumpLog::GetInstance().AddDesc("leftButtonId:null");
    swiper.rightButtonId_.has_value()
        ? DumpLog::GetInstance().AddDesc("rightButtonId:" + std::to_string(swiper.rightButtonId_.value()))
        : DumpLog::GetInstance().AddDesc("rightButtonId:null");
}

void SwiperHelper::DumpInfoAddAnimationDesc(SwiperPattern& swiper)
{
    swiper.isFinishAnimation_ ? DumpLog::GetInstance().AddDesc("isFinishAnimation:true")
                              : DumpLog::GetInstance().AddDesc("isFinishAnimation:false");
    swiper.mainSizeIsMeasured_ ? DumpLog::GetInstance().AddDesc("mainSizeIsMeasured:true")
                               : DumpLog::GetInstance().AddDesc("mainSizeIsMeasured:false");
    swiper.usePropertyAnimation_ ? DumpLog::GetInstance().AddDesc("usePropertyAnimation:true")
                                 : DumpLog::GetInstance().AddDesc("usePropertyAnimation:false");
    swiper.isUserFinish_ ? DumpLog::GetInstance().AddDesc("isUserFinish:true")
                         : DumpLog::GetInstance().AddDesc("isUserFinish:false");
    swiper.isVoluntarilyClear_ ? DumpLog::GetInstance().AddDesc("isVoluntarilyClear:true")
                               : DumpLog::GetInstance().AddDesc("isVoluntarilyClear:false");
    swiper.stopIndicatorAnimation_ ? DumpLog::GetInstance().AddDesc("stopIndicatorAnimation:true")
                                   : DumpLog::GetInstance().AddDesc("stopIndicatorAnimation:false");
    swiper.isTouchPad_ ? DumpLog::GetInstance().AddDesc("isTouchPad:true")
                       : DumpLog::GetInstance().AddDesc("isTouchPad:false");
    swiper.surfaceChangedCallbackId_.has_value()
        ? DumpLog::GetInstance().AddDesc("surfaceChangedCallbackId:"
        + std::to_string(swiper.surfaceChangedCallbackId_.value()))
        : DumpLog::GetInstance().AddDesc("surfaceChangedCallbackId:null");
    swiper.velocity_.has_value()
        ? DumpLog::GetInstance().AddDesc("velocity:" + std::to_string(swiper.velocity_.value()))
        : DumpLog::GetInstance().AddDesc("velocity:null");
    swiper.GetCurveIncludeMotion()
        ? DumpLog::GetInstance().AddDesc("curve:" + swiper.GetCurveIncludeMotion()->ToString())
        : DumpLog::GetInstance().AddDesc("curve:null");
    DumpLog::GetInstance().AddDesc("currentDelta:" + std::to_string(swiper.currentDelta_));
    DumpLog::GetInstance().AddDesc("propertyAnimationIndex:" + std::to_string(swiper.propertyAnimationIndex_));
    DumpLog::GetInstance().AddDesc("mainDeltaSum:" + std::to_string(swiper.mainDeltaSum_));
}

std::string SwiperHelper::GetDotIndicatorStyle(const std::shared_ptr<SwiperParameters>& params)
{
    CHECK_NULL_RETURN(params, "");
    auto jsonValue = JsonUtil::Create(true);
    CHECK_NULL_RETURN(jsonValue, "");
    jsonValue->Put("left", params->dimLeft.value_or(0.0_vp).ToString().c_str());
    jsonValue->Put("top", params->dimTop.value_or(0.0_vp).ToString().c_str());
    jsonValue->Put("right", params->dimRight.value_or(0.0_vp).ToString().c_str());
    jsonValue->Put("bottom", params->dimBottom.value_or(0.0_vp).ToString().c_str());
    jsonValue->Put("itemWidth", params->itemWidth.value_or(6.0_vp).ToString().c_str());
    jsonValue->Put("itemHeight", params->itemHeight.value_or(6.0_vp).ToString().c_str());
    jsonValue->Put("selectedItemWidth", params->selectedItemWidth.value_or(12.0_vp).ToString().c_str());
    jsonValue->Put("selectedItemHeight", params->selectedItemHeight.value_or(6.0_vp).ToString().c_str());
    jsonValue->Put(
        "selectedColor", params->selectedColorVal.value_or(Color::FromString("#ff007dff")).ColorToString().c_str());
    jsonValue->Put("color", params->colorVal.value_or(Color::FromString("#19182431")).ColorToString().c_str());
    jsonValue->Put("mask", params->maskValue.value_or(false) ? "true" : "false");
    jsonValue->Put(
        "maxDisplayCount", (params->maxDisplayCountVal.has_value()) ? params->maxDisplayCountVal.value() : 0);
    return jsonValue->ToString();
}

std::string SwiperHelper::GetDigitIndicatorStyle(const std::shared_ptr<SwiperDigitalParameters>& params)
{
    CHECK_NULL_RETURN(params, "");
    auto jsonValue = JsonUtil::Create(true);
    CHECK_NULL_RETURN(jsonValue, "");
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, "");
    auto theme = pipeline->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_RETURN(theme, "");
    jsonValue->Put("left", params->dimLeft.value_or(0.0_vp).ToString().c_str());
    jsonValue->Put("top", params->dimTop.value_or(0.0_vp).ToString().c_str());
    jsonValue->Put("right", params->dimRight.value_or(0.0_vp).ToString().c_str());
    jsonValue->Put("bottom", params->dimBottom.value_or(0.0_vp).ToString().c_str());
    jsonValue->Put(
        "fontSize", params->fontSize.value_or(theme->GetDigitalIndicatorTextStyle().GetFontSize()).ToString().c_str());
    jsonValue->Put("fontColor",
        params->fontColor.value_or(theme->GetDigitalIndicatorTextStyle().GetTextColor()).ColorToString().c_str());
    jsonValue->Put(
        "fontWeight", V2::ConvertWrapFontWeightToStirng(params->fontWeight.value_or(FontWeight::NORMAL)).c_str());
    jsonValue->Put("selectedFontSize",
        params->selectedFontSize.value_or(theme->GetDigitalIndicatorTextStyle().GetFontSize()).ToString().c_str());
    jsonValue->Put(
        "selectedFontColor", params->selectedFontColor.value_or(theme->GetDigitalIndicatorTextStyle().GetTextColor())
                                 .ColorToString()
                                 .c_str());
    jsonValue->Put("selectedFontWeight",
        V2::ConvertWrapFontWeightToStirng(params->selectedFontWeight.value_or(FontWeight::NORMAL)).c_str());
    return jsonValue->ToString();
}

float SwiperHelper::CalculateFriction(float gamma)
{
    if (LessOrEqual(gamma, 0.0f)) {
        return 1.0f;
    }
    if (GreatOrEqual(gamma, 1.0f)) {
        gamma = 1.0f;
    }
    constexpr float scrollRatio = 0.72f;
    constexpr float coefficient = M_E / (1.0f -  M_E);
    auto fx = (gamma + coefficient) * (log(M_E - (M_E - 1.0f) * gamma) - 1.0f);
    return scrollRatio * fx / gamma;
}
} // namespace OHOS::Ace::NG
