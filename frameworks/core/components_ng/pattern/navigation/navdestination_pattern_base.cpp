/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/navigation/navdestination_pattern_base.h"

#include "core/components_ng/pattern/navigation/navdestination_node_base.h"
namespace OHOS::Ace::NG {
namespace {
}

void NavDestinationPatternBase::SetTitleBarStyle(const std::optional<BarStyle>& barStyle)
{
    if (titleBarStyle_ != barStyle) {
        if (barStyle.value_or(BarStyle::STANDARD) == BarStyle::SAFE_AREA_PADDING ||
            titleBarStyle_.value_or(BarStyle::STANDARD) == BarStyle::SAFE_AREA_PADDING) {
            safeAreaPaddingChanged_ = true;
        }
        titleBarStyle_ = barStyle;
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    }
}

void NavDestinationPatternBase::SetToolBarStyle(const std::optional<BarStyle>& barStyle)
{
    if (toolBarStyle_ != barStyle) {
        if (barStyle.value_or(BarStyle::STANDARD) == BarStyle::SAFE_AREA_PADDING ||
            toolBarStyle_.value_or(BarStyle::STANDARD) == BarStyle::SAFE_AREA_PADDING) {
            safeAreaPaddingChanged_ = true;
        }
        toolBarStyle_ = barStyle;
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    }
}

bool NavDestinationPatternBase::UpdateBarSafeAreaPadding()
{
    if (!safeAreaPaddingChanged_ || (isHideToolbar_ && isHideTitlebar_)) {
        return false;
    }
    safeAreaPaddingChanged_ = false;
    auto navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(GetHost());
    CHECK_NULL_RETURN(navBarNode, false);
    auto contentNode = AceType::DynamicCast<FrameNode>(navBarNode->GetContentNode());
    CHECK_NULL_RETURN(contentNode, false);
    auto contentLayoutProperty = contentNode->GetLayoutProperty();
    CHECK_NULL_RETURN(contentLayoutProperty, false);

    Dimension paddingTop = 0.0_vp;
    if (titleBarStyle_.value_or(BarStyle::STANDARD) == BarStyle::SAFE_AREA_PADDING) {
        paddingTop = GetTitleBarHeightBeforeMeasure();
    }
    Dimension paddingBottom = 0.0_vp;
    if (toolBarStyle_.value_or(BarStyle::STANDARD) == BarStyle::SAFE_AREA_PADDING && !isHideToolbar_) {
        paddingBottom = NavigationGetTheme()->GetHeight();
    }
    PaddingProperty paddingProperty;
    paddingProperty.left = CalcLength(0.0_vp);
    paddingProperty.right = CalcLength(0.0_vp);
    paddingProperty.top = CalcLength(paddingTop);
    paddingProperty.bottom = CalcLength(paddingBottom);

    contentLayoutProperty->UpdateSafeAreaPadding(paddingProperty);
    return true;
}
} // namespace OHOS::Ace::NG