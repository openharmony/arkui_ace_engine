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

#include "core/components_ng/pattern/grid/grid_item_pattern.h"

#include "base/utils/utils.h"
namespace OHOS::Ace::NG {
namespace {
const Color ITEM_FILL_COLOR = Color::TRANSPARENT;
} // namespace
void GridItemPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    SetAccessibilityAction();
}

void GridItemPattern::MarkIsSelected(bool isSelected)
{
    if (isSelected_ != isSelected) {
        isSelected_ = isSelected;
        auto eventHub = GetEventHub<GridItemEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->FireOnSelect(isSelected);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        if (isSelected) {
            host->OnAccessibilityEvent(AccessibilityEventType::SELECTED);
        } else {
            host->OnAccessibilityEvent(AccessibilityEventType::CHANGE);
        }
    }
}

void GridItemPattern::SetSelectable(bool selectable)
{
    if (isSelected_ && selectable_ && !selectable) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto context = host->GetRenderContext();
        CHECK_NULL_VOID(context);
        context->OnMouseSelectUpdate(false, ITEM_FILL_COLOR, ITEM_FILL_COLOR);
        MarkIsSelected(true);
    }
    selectable_ = selectable;
}

void GridItemPattern::SetAccessibilityAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetActionSelect([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (!pattern->Selectable()) {
            return;
        }
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto context = host->GetRenderContext();
        CHECK_NULL_VOID(context);
        context->OnMouseSelectUpdate(false, ITEM_FILL_COLOR, ITEM_FILL_COLOR);
        pattern->MarkIsSelected(true);
        context->OnMouseSelectUpdate(true, ITEM_FILL_COLOR, ITEM_FILL_COLOR);
    });

    accessibilityProperty->SetActionClearSelection([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (!pattern->Selectable()) {
            return;
        }
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto context = host->GetRenderContext();
        CHECK_NULL_VOID(context);
        pattern->MarkIsSelected(false);
        context->OnMouseSelectUpdate(false, ITEM_FILL_COLOR, ITEM_FILL_COLOR);
    });
}

void GridItemPattern::BeforeCreateLayoutWrapper()
{
    if (shallowBuilder_ && !shallowBuilder_->IsExecuteDeepRenderDone()) {
        shallowBuilder_->ExecuteDeepRender();
        shallowBuilder_.Reset();
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!host->IsActive()) {
        host->GetLayoutProperty()->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
    }
}
} // namespace OHOS::Ace::NG
