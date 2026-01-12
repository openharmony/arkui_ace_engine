/*
 * Copyright (c) 2021-2026 Huawei Device Co., Ltd.
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

#include "compatible/components/swiper/dom_swiper.h"

namespace OHOS::Ace::Framework {
// swiper attribute and style constants
const char DOM_INDEX[] = "index";
const char DOM_SWIPER_ANIMATION_OPACITY[] = "animationopacity";
const char DOM_AUTOPLAY[] = "autoplay";
const char DOM_CACHED_SIZE[] = "cachedSize";
const char DOM_DISPLAY_MODE[] = "displaymode";
const char DOM_DISPLAY_MODE_AUTO_LINEAR[] = "autoLinear";
const char DOM_INTERVAL[] = "interval";
const char DOM_INDICATOR[] = "indicator";
const char DOM_LOOP[] = "loop";
const char DOM_VERTICAL[] = "vertical";
const char DOM_ANIMATION_CURVE[] = "animationCurve";
const char DOM_INDICATOR_MASK[] = "indicatormask";
const char DOM_INDICATOR_DISABLED[] = "indicatordisabled";
const char DOM_INDICATOR_SELECTEDCOLOR[] = "indicatorSelectedColor";
const char DOM_INDICATOR_SIZE[] = "indicatorSize";
const char DOM_INDICATOR_TOP[] = "indicatorTop";
const char DOM_INDICATOR_LEFT[] = "indicatorLeft";
const char DOM_INDICATOR_RIGHT[] = "indicatorRight";
const char DOM_INDICATOR_BOTTOM[] = "indicatorBottom";
const char DOM_METHOD_SWIPE_TO[] = "swipeTo";
const char DOM_METHOD_APPEND[] = "append";
const char DOM_METHOD_SHOW_PREVIOUS[] = "showPrevious";
const char DOM_METHOD_SHOW_NEXT[] = "showNext";
const char DOM_DIGITAL_INDICATOR[] = "digital";
const char DOM_PREVIOUS_MARGIN[] = "previousMargin";
const char DOM_NEXT_MARGIN[] = "nextMargin";
namespace {

constexpr double MAX_OPACITY = 255.0;
const std::string DISPLAY_COMPOSED_NAME = "SwiperDisplayChild";

std::string GetDisplayComposedId(const RefPtr<DOMNode>& child)
{
    return "display" + std::to_string(child->GetNodeId());
}

} // namespace

DOMSwiper::DOMSwiper(NodeId nodeId, const std::string& nodeName) : DOMNode(nodeId, nodeName)
{
    swiperChild_ = AceType::MakeRefPtr<SwiperComponent>(std::list<RefPtr<Component>>());
}

void DOMSwiper::InitializeStyle()
{
    if (declaration_) {
        declaration_->InitializeStyle();
    }
}

void DOMSwiper::OnChildNodeAdded(const RefPtr<DOMNode>& child, int32_t slot)
{
    ACE_DCHECK(child);
    auto display = AceType::MakeRefPtr<DisplayComponent>(child->GetRootComponent());
    display->SetOpacity(MAX_OPACITY);
    swiperChild_->InsertChild(
        slot, AceType::MakeRefPtr<ComposedComponent>(GetDisplayComposedId(child), DISPLAY_COMPOSED_NAME, display));
}

void DOMSwiper::OnChildNodeRemoved(const RefPtr<DOMNode>& child)
{
    ACE_DCHECK(child);
    swiperChild_->RemoveChildByComposedId(GetDisplayComposedId(child));
}

void DOMSwiper::PrepareSpecializedComponent()
{
    swiperChild_->SetShow(GetDisplay() == DisplayType::NO_SETTING || GetDisplay() == DisplayType::FLEX);
    swiperChild_->SetDeclaration(AceType::DynamicCast<SwiperDeclaration>(declaration_));
    swiperChild_->SetTextDirection(IsRightToLeft() ? TextDirection::RTL : TextDirection::LTR);
    for (const auto& item : swiperChild_->GetChildren()) {
        auto composedDisplay = AceType::DynamicCast<ComposedComponent>(item);
        if (composedDisplay) {
            composedDisplay->MarkNeedUpdate();
        }
    }
}

void DOMSwiper::AdjustSpecialParamInLiteMode()
{
    auto declaration = AceType::DynamicCast<SwiperDeclaration>(declaration_);
    if (declaration) {
        declaration->SetShowIndicator(false);
    }
}

} // namespace OHOS::Ace::Framework
