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

#include "component_test/core/combination_isscrollable.h"
#include "ui/base/utils/utils.h"

#include "core/components_ng/pattern/stepper/stepper_node.h"
#include "core/components_ng/pattern/stepper/stepper_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"
#include "core/components_ng/pattern/tabs/tab_bar_layout_property.h"
#include "core/components_ng/pattern/tabs/tab_bar_pattern.h"
#include "core/interfaces/native/node/node_swiper_modifier.h"

namespace OHOS::Ace {
CombinationIsScrollable::CombinationIsScrollable(const RefPtr<NG::FrameNode> frameNode)
{
    frameNode_ = frameNode;
    pattern_ = frameNode_->GetPattern();
}

bool CombinationIsScrollable::IsComponentExist()
{
    CHECK_NULL_RETURN(pattern_, false);
    if (AceType::InstanceOf<OHOS::Ace::NG::SwiperPattern>(pattern_)) {
        isSwiper_ = true;
        return true;
    }
    if (AceType::InstanceOf<OHOS::Ace::NG::StepperPattern>(pattern_)) {
        isSteper_ = true;
        return true;
    }
    if (AceType::InstanceOf<OHOS::Ace::NG::TabBarPattern>(pattern_)) {
        isTabBar_ = false;
        return true;
    }
    return false;
}

bool CombinationIsScrollable::IsComponentScrollable() const
{
    auto modifier = NG::NodeModifier::GetSwiperCustomModifier();
    CHECK_NULL_RETURN(modifier, false);
    if (isSwiper_) {
        auto swiperLayoutProperty = frameNode_->GetLayoutProperty<OHOS::Ace::NG::SwiperLayoutProperty>();
        CHECK_NULL_RETURN(swiperLayoutProperty, false);
        bool isLoop = swiperLayoutProperty->GetLoop().value_or(true);
        if (!isLoop && modifier->getTotalCount(
            reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode_))) <= 1) {
            return false;
        }
        return true;
    }
    if (isSteper_) {
        auto swiperFrameNode = AceType::DynamicCast<OHOS::Ace::NG::StepperNode>(frameNode_);
        CHECK_NULL_RETURN(swiperFrameNode, false);
        auto swiperNode = AceType::DynamicCast<NG::FrameNode>(
            swiperFrameNode->GetChildAtIndex(swiperFrameNode->GetChildIndexById(swiperFrameNode->GetSwiperId())));
        CHECK_NULL_RETURN(swiperNode, false);
        auto swiperLayoutProperty = swiperNode->GetLayoutProperty<OHOS::Ace::NG::SwiperLayoutProperty>();
        CHECK_NULL_RETURN(swiperLayoutProperty, false);
        bool isLoop = swiperLayoutProperty->GetLoop().value_or(true);
        return (!isLoop && modifier->getTotalCount(
            reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(swiperNode))) <= 1) ? false : true;
    }
    auto tabBarPattern = frameNode_->GetPattern<OHOS::Ace::NG::TabBarPattern>();
    CHECK_NULL_RETURN(tabBarPattern, false);
    auto tabBarLayoutProperty = tabBarPattern->GetLayoutProperty<OHOS::Ace::NG::TabBarLayoutProperty>();
    CHECK_NULL_RETURN(tabBarLayoutProperty, false);
    if (tabBarLayoutProperty->GetTabBarMode().value_or(TabBarMode::FIXED) == TabBarMode::SCROLLABLE &&
        modifier->getTotalCount(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode_))) > 1) {
        return true;
    }
    return false;
}
} // namespace OHOS::Ace
