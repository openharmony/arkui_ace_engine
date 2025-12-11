/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/list/list_item_group_accessibility_property.h"

#include "core/components_ng/pattern/list/list_item_group_pattern.h"

namespace OHOS::Ace::NG {
int32_t ListItemGroupAccessibilityProperty::GetBeginIndex() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto listItemGroupPattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_RETURN(listItemGroupPattern, -1);
    auto itemPosition = listItemGroupPattern->GetItemPosition();
    return itemPosition.empty() ? -1 : itemPosition.begin()->first;
}

int32_t ListItemGroupAccessibilityProperty::GetEndIndex() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto listItemGroupPattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_RETURN(listItemGroupPattern, -1);
    auto itemPosition = listItemGroupPattern->GetItemPosition();
    return itemPosition.empty() ? -1 : itemPosition.rbegin()->first;
}

bool ListItemGroupAccessibilityProperty::GetAccessibilityInnerVisibleRect(RectF& rect)
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, false);
    auto listItemGroupPattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_RETURN(listItemGroupPattern, false);
    auto context = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(context, false);
    auto listItemGroupRect = context->GetPaintRectWithoutTransform();
    rect = RectF(0, 0, listItemGroupRect.Width(), listItemGroupRect.Height());
    bool result = false;
    float viewTop = 0.0f;
    float viewBottom = listItemGroupRect.Height();

    auto headerFrameNode = AceType::DynamicCast<NG::FrameNode>(listItemGroupPattern->GetHeaderNode());
    if (headerFrameNode) {
        auto headerContext = headerFrameNode->GetRenderContext();
        if (headerContext) {
            auto headerRect = headerContext->GetPaintRectWithTransform();
            viewTop = headerRect.Bottom();
            result = true;
        }
    }

    auto footerFrameNode = AceType::DynamicCast<NG::FrameNode>(listItemGroupPattern->GetFooterNode());
    if (footerFrameNode) {
        auto footerContext = footerFrameNode->GetRenderContext();
        if (footerContext) {
            auto footerRect = footerContext->GetPaintRectWithTransform();
            viewBottom = footerRect.Top();
            result = true;
        }
    }

    if  (result) {
        rect.SetTop(viewTop);
        rect.SetHeight(viewBottom - viewTop);
    }

    return result;
}

ScrollableStatus ListItemGroupAccessibilityProperty::GetScrollableStatus() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, ScrollableStatus::NOT_SUPPORT);
    auto listItemGroupPattern = frameNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_RETURN(listItemGroupPattern, ScrollableStatus::NOT_SUPPORT);
    bool isDisplayStart = listItemGroupPattern->IsDisplayStart();
    bool isDisplayEnd = listItemGroupPattern->IsDisplayEnd();
    if (isDisplayStart && isDisplayEnd) {
        return ScrollableStatus::AT_BOTH_TOP_BOTTOM;
    } else if (isDisplayStart) {
        return ScrollableStatus::AT_TOP;
    } else if (isDisplayEnd) {
        return ScrollableStatus::AT_BOTTOM;
    } else {
        return ScrollableStatus::AT_NEITHER_TOP_BOTTOM;
    }
}

} // namespace OHOS::Ace::NG