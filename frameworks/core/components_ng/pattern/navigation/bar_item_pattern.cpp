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

#include "core/components_ng/pattern/navigation/bar_item_pattern.h"
#include "core/components_ng/pattern/image/image_layout_property.h"

namespace OHOS::Ace::NG {

void BarItemPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    CHECK_NULL_VOID_NOLOG(!clickListener_);
    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& /* info */) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto eventHub = pattern->GetEventHub<BarItemEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->FireItemAction();
        pattern->UpdateBarItemActiveStatusResource();
    };
    if (clickListener_) {
        gesture->RemoveClickEvent(clickListener_);
    }
    clickListener_ = MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gesture->AddClickEvent(clickListener_);
}

void BarItemPattern::UpdateBarItemActiveStatusResource()
{
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);

    auto barItemNode = AceType::DynamicCast<BarItemNode>(GetHost());
    auto status = GetToolbarItemStatus();
    auto iconStatus = GetCurrentIconStatus();

    auto iconNode = DynamicCast<FrameNode>(barItemNode->GetIconNode());
    CHECK_NULL_VOID(iconNode);
    auto imageLayoutProperty = iconNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    auto textNode = DynamicCast<FrameNode>(barItemNode->GetTextNode());
    CHECK_NULL_VOID(textNode);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    if (status == NavToolbarItemStatus::ACTIVE && iconStatus == ToolbarIconStatus::INITIAL) {
        imageLayoutProperty->UpdateImageSourceInfo(GetActiveIconImageSourceInfo());
        iconNode->MarkModifyDone();
        iconNode->MarkDirtyNode();
        textLayoutProperty->UpdateTextColor(theme->GetToolBarItemActiveFontColor());
        textNode->MarkModifyDone();
        textNode->MarkDirtyNode();
        SetCurrentIconStatus(ToolbarIconStatus::ACTIVE);
    } else if (status == NavToolbarItemStatus::ACTIVE && iconStatus == ToolbarIconStatus::ACTIVE) {
        imageLayoutProperty->UpdateImageSourceInfo(GetInitialIconImageSourceInfo());
        iconNode->MarkModifyDone();
        iconNode->MarkDirtyNode();
        textLayoutProperty->UpdateTextColor(theme->GetToolBarItemFontColor());
        textNode->MarkModifyDone();
        textNode->MarkDirtyNode();
        SetCurrentIconStatus(ToolbarIconStatus::INITIAL);
    }
}
} // namespace OHOS::Ace::NG