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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_TRANSITIONAL_NODE_INFO_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_TRANSITIONAL_NODE_INFO_H

#include <string>

namespace OHOS::NWeb {
    class NWebAccessibilityNodeInfo;
}

namespace OHOS::Ace::NG {
class TransitionalNodeInfo {
public:
    TransitionalNodeInfo(std::shared_ptr<NWeb::NWebAccessibilityNodeInfo> node) : node_(node) {}

    ~TransitionalNodeInfo() = default;

    std::string GetHint();
    std::string GetError();
    int32_t GetRectX();
    int32_t GetRectY();
    int32_t GetPageId();
    std::vector<uint32_t> GetActions();
    std::string GetContent();
    std::vector<int64_t> GetChildIds();
    int64_t GetParentId();
    bool GetIsHeading();
    bool GetIsChecked();
    bool GetIsEnabled();
    bool GetIsFocused();
    int32_t GetRectWidth();
    int32_t GetRectHeight();
    bool GetIsVisible();
    bool GetIsHinting();
    bool GetIsEditable();
    bool GetIsSelected();
    size_t GetItemCounts();
    int32_t GetLiveRegion();
    bool GetIsPassword();
    bool GetIsCheckable();
    bool GetIsClickable();
    bool GetIsFocusable();
    bool GetIsScrollable();
    bool GetIsDeletable();
    int64_t GetAccessibilityId();
    bool GetIsPopupSupported();
    bool GetIsContentInvalid();
    int32_t GetSelectionEnd();
    int32_t GetSelectionStart();
    float GetRangeInfoMin();
    float GetRangeInfoMax();
    float GetRangeInfoCurrent();
    int32_t GetInputType();
    std::string GetComponentType();
    std::string GetDescriptionInfo();
    int32_t GetGridRows();
    int32_t GetGridItemRow();
    int32_t GetGridColumns();
    int32_t GetGridItemColumn();
    int32_t GetGridItemRowSpan();
    int32_t GetGridSelectedMode();
    int32_t GetGridItemColumnSpan();
    bool GetIsAccessibilityFocus();
    bool GetIsPluralLineSupported();
    bool GetIsAccessibilityGroup();
    std::string GetHtmlElementId();
    std::string GetComponentTypeDescription();
    int32_t GetCheckboxGroupSelectedStatus();
    std::string GetExpandedState();

private:
    std::shared_ptr<NWeb::NWebAccessibilityNodeInfo> node_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_TRANSITIONAL_NODE_INFO_H