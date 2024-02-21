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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_ACCESSIBILITY_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_ACCESSIBILITY_NODE_H
#include "base/memory/referenced.h"
#include "base/web/webview/ohos_nweb/include/nweb_accessibility_node_info.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT WebAccessibilityNode : public FrameNode {
    DECLARE_ACE_TYPE(WebAccessibilityNode, FrameNode)
public:
    WebAccessibilityNode(const RefPtr<FrameNode>& webNode)
        : FrameNode(V2::WEB_CORE_TAG, 0, MakeRefPtr<Pattern>())
    {
        webNode_ = WeakPtr(webNode);
        pageId_ = webNode->GetPageId();
    }
    ~WebAccessibilityNode()
    {
        webNode_.Reset();
    }
    void SetAccessibilityNodeInfo(std::shared_ptr<OHOS::NWeb::NWebAccessibilityNodeInfo> info) {
        if (info) {
            info->SetPageId(pageId_);
        }
        accessibilityNodeInfo_ = info;
    }
    std::string GetHint() {
        if (!accessibilityNodeInfo_) {
            return "";
        }
        return accessibilityNodeInfo_->GetHint();
    }
    std::string GetError() {
        if (!accessibilityNodeInfo_) {
            return "";
        }
        return accessibilityNodeInfo_->GetError();
    }
    int32_t GetRectX() {
        if (!accessibilityNodeInfo_) {
            return 0;
        }
        return accessibilityNodeInfo_->GetRectX();
    }
    int32_t GetRectY() {
        if (!accessibilityNodeInfo_) {
            return 0;
        }
        return accessibilityNodeInfo_->GetRectY();
    }
    int32_t GetPageId() {
        if (!accessibilityNodeInfo_) {
            return pageId_;
        }
        return accessibilityNodeInfo_->GetPageId();
    }
    std::vector<uint32_t> GetActions() {
        if (!accessibilityNodeInfo_) {
            std::vector<uint32_t> empty;
            return empty;
        }
        return accessibilityNodeInfo_->GetActions();
    }
    std::string GetContent() {
        if (!accessibilityNodeInfo_) {
            return "";
        }
        return accessibilityNodeInfo_->GetContent();
    }
    std::vector<int64_t> GetChildIds() {
        if (!accessibilityNodeInfo_) {
            std::vector<int64_t> empty;
            return empty;
        }
        return accessibilityNodeInfo_->GetChildIds();
    }
    int64_t GetParentId() {
        if (!accessibilityNodeInfo_) {
            return -1;
        }
        return accessibilityNodeInfo_->GetParentId();
    }
    bool GetIsHeading() {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsHeading();
    }
    bool GetIsChecked() {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsChecked();
    }
    bool GetIsEnabled() {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsEnabled();
    }
    bool GetIsFocused() {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsFocused();
    }
    int32_t GetRectWidth() {
        if (!accessibilityNodeInfo_) {
            return 0;
        }
        return accessibilityNodeInfo_->GetRectWidth();
    }
    int32_t GetRectHeight() {
        if (!accessibilityNodeInfo_) {
            return 0;
        }
        return accessibilityNodeInfo_->GetRectHeight();
    }
    bool GetIsVisible() {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsVisible();
    }
    bool GetIsHinting() {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsHinting();
    }
    bool GetIsEditable() {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsEditable();
    }
    bool GetIsSelected() {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsSelected();
    }
    size_t GetItemCounts() {
        if (!accessibilityNodeInfo_) {
            return 0;
        }
        return accessibilityNodeInfo_->GetItemCounts();
    }
    int32_t GetLiveRegion() {
        if (!accessibilityNodeInfo_) {
            return -1;
        }
        return accessibilityNodeInfo_->GetLiveRegion();
    }
    bool GetIsPassword() {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsPassword();
    }
    bool GetIsCheckable() {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsCheckable();
    }
    bool GetIsClickable() {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsClickable();
    }
    bool GetIsFocusable() {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsFocusable();
    }
    bool GetIsScrollable() {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsScrollable();
    }
    bool GetIsDeletable() {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsDeletable();
    }
    int64_t GetAccessibilityId() {
        if (!accessibilityNodeInfo_) {
            return -1;
        }
        return accessibilityNodeInfo_->GetAccessibilityId();
    }
    bool GetIsPopupSupported() {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsPopupSupported();
    }
    bool GetIsContentInvalid() {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsContentInvalid();
    }
    float GetRangeInfoMin() {
        if (!accessibilityNodeInfo_) {
            return 0;
        }
        return accessibilityNodeInfo_->GetRangeInfoMin();
    }
    float GetRangeInfoMax() {
        if (!accessibilityNodeInfo_) {
            return 0;
        }
        return accessibilityNodeInfo_->GetRangeInfoMax();
    }
    float GetRangeInfoCurrent() {
        if (!accessibilityNodeInfo_) {
            return 0;
        }
        return accessibilityNodeInfo_->GetRangeInfoCurrent();
    }
    int32_t GetSelectionEnd() {
        if (!accessibilityNodeInfo_) {
            return 0;
        }
        return accessibilityNodeInfo_->GetSelectionEnd();
    }
    int32_t GetSelectionStart() {
        if (!accessibilityNodeInfo_) {
            return 0;
        }
        return accessibilityNodeInfo_->GetSelectionStart();
    }
    int32_t GetInputType() {
        if (!accessibilityNodeInfo_) {
            return -1;
        }
        return accessibilityNodeInfo_->GetInputType();
    }
    std::string GetComponentType() {
        if (!accessibilityNodeInfo_) {
            return "";
        }
        return accessibilityNodeInfo_->GetComponentType();
    }
    std::string GetDescriptionInfo() {
        if (!accessibilityNodeInfo_) {
            return "";
        }
        return accessibilityNodeInfo_->GetDescriptionInfo();
    }
    int32_t GetGridRows() {
        if (!accessibilityNodeInfo_) {
            return -1;
        }
        return accessibilityNodeInfo_->GetGridRows();
    }
    int32_t GetGridItemRow() {
        if (!accessibilityNodeInfo_) {
            return -1;
        }
        return accessibilityNodeInfo_->GetGridItemRow();
    }
    int32_t GetGridColumns() {
        if (!accessibilityNodeInfo_) {
            return -1;
        }
        return accessibilityNodeInfo_->GetGridColumns();
    }
    int32_t GetGridItemColumn() {
        if (!accessibilityNodeInfo_) {
            return -1;
        }
        return accessibilityNodeInfo_->GetGridItemColumn();
    }
    int32_t GetGridItemRowSpan() {
        if (!accessibilityNodeInfo_) {
            return -1;
        }
        return accessibilityNodeInfo_->GetGridItemRowSpan();
    }
    int32_t GetGridSelectedMode() {
        if (!accessibilityNodeInfo_) {
            return -1;
        }
        return accessibilityNodeInfo_->GetGridSelectedMode();
    }
    int32_t GetGridItemColumnSpan() {
        if (!accessibilityNodeInfo_) {
            return -1;
        }
        return accessibilityNodeInfo_->GetGridItemColumnSpan();
    }
    bool GetIsAccessibilityFocus() {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsAccessibilityFocus();
    }
    bool GetIsPluralLineSupported() {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsPluralLineSupported();
    }
    RefPtr<FrameNode> GetWebNode()
    {
        return webNode_.Upgrade();
    }

private:
    int64_t pageId_;
    std::shared_ptr<OHOS::NWeb::NWebAccessibilityNodeInfo> accessibilityNodeInfo_;
    WeakPtr<FrameNode> webNode_ = nullptr;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_ACCESSIBILITY_NODE_H