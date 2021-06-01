/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/common/dom/dom_swiper.h"

#include "base/utils/linear_map.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/color.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::Framework {
namespace {

constexpr uint32_t METHOD_SWIPE_TO_ARGS_SIZE = 1;
constexpr double MAX_OPACITY = 255.0;
constexpr double INDICATOR_POINT_SCALE = 1.33;

} // namespace

DOMSwiper::DOMSwiper(NodeId nodeId, const std::string& nodeName) : DOMNode(nodeId, nodeName)
{
    swiperChild_ = AceType::MakeRefPtr<SwiperComponent>(std::list<RefPtr<Component>>());
    indicator_ = AceType::MakeRefPtr<SwiperIndicator>();
    if (IsRightToLeft()) {
        swiperChild_->SetTextDirection(TextDirection::RTL);
    }
}

void DOMSwiper::InitializeStyle()
{
    ResetInitializedStyle();
}

bool DOMSwiper::SetSpecializedAttr(const std::pair<std::string, std::string>& attr)
{
    static const LinearMapNode<void (*)(const std::string&, DOMSwiper&)> swiperAttrsOperators[] = {
        { DOM_SWIPER_ANIMATION_OPACITY,
            [](const std::string& val, DOMSwiper& swiper) {
                swiper.swiperChild_->SetAnimationOpacity(StringToBool(val)); } },
        { DOM_AUTOPLAY,
            [](const std::string& val, DOMSwiper& swiper) { swiper.swiperChild_->SetAutoPlay(StringToBool(val)); } },
        { DOM_DIGITAL_INDICATOR,
            [](const std::string& val, DOMSwiper& swiper) {
                swiper.swiperChild_->SetDigitalIndicator(StringToBool(val));
            } },
        { DOM_DURATION,
            [](const std::string& val, DOMSwiper& swiper) { swiper.swiperChild_->SetDuration(StringToDouble(val)); } },
        { DOM_INDEX,
            [](const std::string& val, DOMSwiper& swiper) {
                swiper.swiperChild_->SetIndex(StringUtils::StringToInt(val));
            } },
        { DOM_INDICATOR,
            [](const std::string& val, DOMSwiper& swiper) {
                swiper.showIndicator_ = StringToBool(val);
                swiper.swiperChild_->SetIndicator(swiper.showIndicator_ ? swiper.indicator_ : nullptr);
            } },
        { DOM_INDICATOR_DISABLED,
            [](const std::string& val, DOMSwiper& swiper) {
              swiper.indicator_->SetIndicatorDisabled(StringToBool(val));
            } },
        { DOM_INDICATOR_MASK,
            [](const std::string& val, DOMSwiper& swiper) { swiper.indicator_->SetIndicatorMask(StringToBool(val)); } },
        { DOM_INTERVAL, [](const std::string& val,
                        DOMSwiper& swiper) { swiper.swiperChild_->SetAutoPlayInterval(StringToDouble(val)); } },
        { DOM_LOOP,
            [](const std::string& val, DOMSwiper& swiper) { swiper.swiperChild_->SetLoop(StringToBool(val)); } },
        { DOM_VERTICAL,
            [](const std::string& val, DOMSwiper& swiper) {
                swiper.swiperChild_->SetAxis(StringToBool(val) ? Axis::VERTICAL : Axis::HORIZONTAL);
            } },
        };
    auto operatorIter = BinarySearchFindIndex(
        swiperAttrsOperators, ArraySize(swiperAttrsOperators), attr.first.c_str());
    if (operatorIter != -1) {
        swiperAttrsOperators[operatorIter].value(attr.second, *this);
        return true;
    } else {
        return false;
    }
}

bool DOMSwiper::SetSpecializedStyle(const std::pair<std::string, std::string>& style)
{
    // static linear map must be sorted buy key.
    static const LinearMapNode<void (*)(const std::string&, DOMSwiper&)> swiperStylesOperators[] = {
        { DOM_ANIMATION_CURVE,
            [](const std::string& val, DOMSwiper& swiper) {
                swiper.swiperChild_->SetAnimationCurve(ConvertStrToAnimationCurve(val)); } },
        { DOM_INDICATOR_BOTTOM, [](const std::string& val,
                                DOMSwiper& swiper) { swiper.indicator_->SetBottom(swiper.ParseDimension(val)); } },
        { DOM_INDICATOR_COLOR,
            [](const std::string& val, DOMSwiper& swiper) { swiper.indicator_->SetColor(swiper.ParseColor(val)); } },
        { DOM_INDICATOR_LEFT,
            [](const std::string& val, DOMSwiper& swiper) { swiper.indicator_->SetLeft(swiper.ParseDimension(val)); } },
        { DOM_INDICATOR_RIGHT, [](const std::string& val,
                               DOMSwiper& swiper) { swiper.indicator_->SetRight(swiper.ParseDimension(val)); } },
        { DOM_INDICATOR_SELECTEDCOLOR,
            [](const std::string& val, DOMSwiper& swiper) {
                swiper.indicator_->SetSelectedColor(swiper.ParseColor(val));
            } },
        { DOM_INDICATOR_SIZE,
            [](const std::string& val, DOMSwiper& swiper) {
                Dimension indicatorSize = swiper.ParseDimension(val);
                swiper.indicator_->SetSize(indicatorSize);
                swiper.indicator_->SetSelectedSize(indicatorSize);
                swiper.indicator_->SetPressSize(indicatorSize * INDICATOR_POINT_SCALE);
                swiper.indicator_->SetHoverSize(indicatorSize * INDICATOR_POINT_SCALE * INDICATOR_POINT_SCALE);
            } },
        { DOM_INDICATOR_TOP,
            [](const std::string& val, DOMSwiper& swiper) { swiper.indicator_->SetTop(swiper.ParseDimension(val)); } },
    };
    auto operatorIter =
        BinarySearchFindIndex(swiperStylesOperators, ArraySize(swiperStylesOperators), style.first.c_str());
    if (operatorIter != -1) {
        swiperStylesOperators[operatorIter].value(style.second, *this);
        return true;
    } else {
        return false;
    }
}

bool DOMSwiper::AddSpecializedEvent(int32_t pageId, const std::string& event)
{
    if (event == DOM_CHANGE) {
        changeEventId_ = EventMarker(GetNodeIdForEvent(), event, pageId);
        swiperChild_->SetChangeEventId(changeEventId_);
        return true;
    } else if (event == DOM_ROTATION) {
        rotationEventId_ = EventMarker(GetNodeIdForEvent(), event, pageId);
        swiperChild_->SetRotationEventId(rotationEventId_);
        return true;
    } else if (event == DOM_CLICK) {
        clickEventId_ = EventMarker(GetNodeIdForEvent(), event, pageId);
        swiperChild_->SetClickEventId(clickEventId_);
        return true;
    } else {
        return false;
    }
}

void DOMSwiper::CallSpecializedMethod(const std::string& method, const std::string& args)
{
    LOGD("DOMSwiper CallSpecializedMethod");
    if (method == DOM_METHOD_SWIPE_TO) {
        auto controller = swiperChild_->GetSwiperController();
        if (!controller) {
            LOGE("get controller failed");
            return;
        }

        std::unique_ptr<JsonValue> argsValue = JsonUtil::ParseJsonString(args);
        if (!argsValue || !argsValue->IsArray() || argsValue->GetArraySize() != METHOD_SWIPE_TO_ARGS_SIZE) {
            LOGE("parse args error");
            return;
        }

        std::unique_ptr<JsonValue> indexValue = argsValue->GetArrayItem(0)->GetValue("index");
        if (!indexValue || !indexValue->IsNumber()) {
            LOGE("get index failed");
            return;
        }
        int32_t index = indexValue->GetInt();
        controller->SwipeTo(index);
    } else if (method == DOM_METHOD_SHOW_PREVIOUS) {
        auto controller = swiperChild_->GetSwiperController();
        if (!controller) {
            return;
        }
        controller->ShowPrevious();
    } else if (method == DOM_METHOD_SHOW_NEXT) {
        auto controller = swiperChild_->GetSwiperController();
        if (!controller) {
            return;
        }
        controller->ShowNext();
    } else if (method == DOM_ROTATION) {
        auto controller = swiperChild_->GetRotationController();
        if (controller) {
            LOGD("DOMSwiper rotation focus request");
            controller->RequestRotation(true);
        }
    }
}

void DOMSwiper::OnChildNodeAdded(const RefPtr<DOMNode>& child, int32_t slot)
{
    ACE_DCHECK(child);
    auto display = AceType::MakeRefPtr<DisplayComponent>(child->GetRootComponent());
    display->SetOpacity(MAX_OPACITY);
    swiperChild_->InsertChild(slot, display);
}

void DOMSwiper::OnChildNodeRemoved(const RefPtr<DOMNode>& child)
{
    ACE_DCHECK(child);
    swiperChild_->RemoveChild(child->GetRootComponent());
}

void DOMSwiper::PrepareSpecializedComponent()
{
    if (showIndicator_) {
        swiperChild_->SetIndicator(indicator_);
    }
    swiperChild_->SetShow(GetDisplay() == DisplayType::NO_SETTING || GetDisplay() == DisplayType::FLEX);
}

void DOMSwiper::ResetInitializedStyle()
{
    RefPtr<SwiperIndicatorTheme> theme = GetTheme<SwiperIndicatorTheme>();
    if (theme) {
        indicator_->InitStyle(theme);
    }
}

void DOMSwiper::AdjustSpecialParamInLiteMode()
{
    showIndicator_ = false;
}

} // namespace OHOS::Ace::Framework
