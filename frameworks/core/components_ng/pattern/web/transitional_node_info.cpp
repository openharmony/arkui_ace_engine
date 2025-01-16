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

#include "core/components_ng/pattern/web/transitional_node_info.h"

#include "nweb_handler.h"

namespace OHOS::Ace::NG {
    std::string TransitionalNodeInfo::GetHint()
    {
        return node_->GetHint();
    }

    std::string TransitionalNodeInfo::GetError()
    {
        return node_->GetError();
    }

    int32_t TransitionalNodeInfo::GetRectX()
    {
        return node_->GetRectX();
    }

    int32_t TransitionalNodeInfo::GetRectY()
    {
        return node_->GetRectY();
    }

    int32_t TransitionalNodeInfo::GetPageId()
    {
        return node_->GetPageId();
    }

    std::vector<uint32_t> TransitionalNodeInfo::GetActions()
    {
        return node_->GetActions();
    }

    std::string TransitionalNodeInfo::GetContent()
    {
        return node_->GetContent();
    }

    std::vector<int64_t> TransitionalNodeInfo::GetChildIds()
    {
        return node_->GetChildIds();
    }

    int64_t TransitionalNodeInfo::GetParentId()
    {
        return node_->GetParentId();
    }

    bool TransitionalNodeInfo::GetIsHeading()
    {
        return node_->GetIsHeading();
    }

    bool TransitionalNodeInfo::GetIsChecked()
    {
        return node_->GetIsChecked();
    }

    bool TransitionalNodeInfo::GetIsEnabled()
    {
        return node_->GetIsEnabled();
    }

    bool TransitionalNodeInfo::GetIsFocused()
    {
        return node_->GetIsFocused();
    }

    int32_t TransitionalNodeInfo::GetRectWidth()
    {
        return node_->GetRectWidth();
    }

    int32_t TransitionalNodeInfo::GetRectHeight()
    {
        return node_->GetRectHeight();
    }

    bool TransitionalNodeInfo::GetIsVisible()
    {
        return node_->GetIsVisible();
    }

    bool TransitionalNodeInfo::GetIsHinting()
    {
        return node_->GetIsHinting();
    }

    bool TransitionalNodeInfo::GetIsEditable()
    {
        return node_->GetIsEditable();
    }

    bool TransitionalNodeInfo::GetIsSelected()
    {
        return node_->GetIsSelected();
    }

    size_t TransitionalNodeInfo::GetItemCounts()
    {
        return node_->GetItemCounts();
    }

    int32_t TransitionalNodeInfo::GetLiveRegion()
    {
        return node_->GetLiveRegion();
    }

    bool TransitionalNodeInfo::GetIsPassword()
    {
        return node_->GetIsPassword();
    }

    bool TransitionalNodeInfo::GetIsCheckable()
    {
        return node_->GetIsCheckable();
    }

    bool TransitionalNodeInfo::GetIsClickable()
    {
        return node_->GetIsClickable();
    }

    bool TransitionalNodeInfo::GetIsFocusable()
    {
        return node_->GetIsFocusable();
    }

    bool TransitionalNodeInfo::GetIsScrollable()
    {
        return node_->GetIsScrollable();
    }

    bool TransitionalNodeInfo::GetIsDeletable()
    {
        return node_->GetIsDeletable();
    }

    int64_t TransitionalNodeInfo::GetAccessibilityId()
    {
        return node_->GetAccessibilityId();
    }

    bool TransitionalNodeInfo::GetIsPopupSupported()
    {
        return node_->GetIsPopupSupported();
    }

    bool TransitionalNodeInfo::GetIsContentInvalid()
    {
        return node_->GetIsContentInvalid();
    }

    int32_t TransitionalNodeInfo::GetSelectionEnd()
    {
        return node_->GetSelectionEnd();
    }

    int32_t TransitionalNodeInfo::GetSelectionStart()
    {
        return node_->GetSelectionStart();
    }

    float TransitionalNodeInfo::GetRangeInfoMin()
    {
        return node_->GetRangeInfoMin();
    }

    float TransitionalNodeInfo::GetRangeInfoMax()
    {
        return node_->GetRangeInfoMax();
    }

    float TransitionalNodeInfo::GetRangeInfoCurrent()
    {
        return node_->GetRangeInfoCurrent();
    }

    int32_t TransitionalNodeInfo::GetInputType()
    {
        return node_->GetInputType();
    }

    std::string TransitionalNodeInfo::GetComponentType()
    {
        return node_->GetComponentType();
    }

    std::string TransitionalNodeInfo::GetDescriptionInfo()
    {
        return node_->GetDescriptionInfo();
    }

    int32_t TransitionalNodeInfo::GetGridRows()
    {
        return node_->GetGridRows();
    }

    int32_t TransitionalNodeInfo::GetGridItemRow()
    {
        return node_->GetGridItemRow();
    }

    int32_t TransitionalNodeInfo::GetGridColumns()
    {
        return node_->GetGridColumns();
    }

    int32_t TransitionalNodeInfo::GetGridItemColumn()
    {
        return node_->GetGridItemColumn();
    }

    int32_t TransitionalNodeInfo::GetGridItemRowSpan()
    {
        return node_->GetGridItemRowSpan();
    }

    int32_t TransitionalNodeInfo::GetGridSelectedMode()
    {
        return node_->GetGridSelectedMode();
    }

    int32_t TransitionalNodeInfo::GetGridItemColumnSpan()
    {
        return node_->GetGridItemColumnSpan();
    }

    bool TransitionalNodeInfo::GetIsAccessibilityFocus()
    {
        return node_->GetIsAccessibilityFocus();
    }

    bool TransitionalNodeInfo::GetIsPluralLineSupported()
    {
        return node_->GetIsPluralLineSupported();
    }

    bool TransitionalNodeInfo::GetIsAccessibilityGroup()
    {
        return node_->GetIsAccessibilityGroup();
    }
} // namespace OHOS::Ace::NG