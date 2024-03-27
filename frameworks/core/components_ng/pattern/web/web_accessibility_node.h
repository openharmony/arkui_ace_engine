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
#include "core/components_ng/base/node_flag.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
class WebPattern;

class ACE_EXPORT WebAccessibilityNode : public FrameNode {
    DECLARE_ACE_TYPE(WebAccessibilityNode, FrameNode)
public:
    WebAccessibilityNode(const RefPtr<WebPattern>& webPattern);

    ~WebAccessibilityNode() = default;

    void SetAccessibilityNodeInfo(const std::shared_ptr<OHOS::NWeb::NWebAccessibilityNodeInfo>& info)
    {
        if (info) {
            info->SetPageId(pageId_);
        }
        accessibilityNodeInfo_ = info;
    }

    std::string GetHint() const
    {
        if (!accessibilityNodeInfo_) {
            return "";
        }
        return accessibilityNodeInfo_->GetHint();
    }

    std::string GetError() const
    {
        if (!accessibilityNodeInfo_) {
            return "";
        }
        return accessibilityNodeInfo_->GetError();
    }

    int32_t GetRectX() const
    {
        if (!accessibilityNodeInfo_) {
            return 0;
        }
        return accessibilityNodeInfo_->GetRectX();
    }

    int32_t GetRectY() const
    {
        if (!accessibilityNodeInfo_) {
            return 0;
        }
        return accessibilityNodeInfo_->GetRectY();
    }

    int32_t GetPageId() const
    {
        if (!accessibilityNodeInfo_) {
            return pageId_;
        }
        return accessibilityNodeInfo_->GetPageId();
    }

    std::vector<uint32_t> GetActions() const
    {
        if (!accessibilityNodeInfo_) {
            std::vector<uint32_t> empty;
            return empty;
        }
        return accessibilityNodeInfo_->GetActions();
    }

    std::string GetContent() const
    {
        if (!accessibilityNodeInfo_) {
            return "";
        }
        return accessibilityNodeInfo_->GetContent();
    }

    std::vector<int64_t> GetChildIds() const
    {
        if (!accessibilityNodeInfo_) {
            std::vector<int64_t> empty;
            return empty;
        }
        return accessibilityNodeInfo_->GetChildIds();
    }

    int64_t GetParentId() const
    {
        if (!accessibilityNodeInfo_) {
            return -1;
        }
        return accessibilityNodeInfo_->GetParentId();
    }

    bool GetIsHeading() const
    {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsHeading();
    }

    bool GetIsChecked() const
    {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsChecked();
    }

    bool GetIsEnabled() const
    {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsEnabled();
    }

    bool GetIsFocused() const
    {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsFocused();
    }

    int32_t GetRectWidth() const
    {
        if (!accessibilityNodeInfo_) {
            return 0;
        }
        return accessibilityNodeInfo_->GetRectWidth();
    }

    int32_t GetRectHeight() const
    {
        if (!accessibilityNodeInfo_) {
            return 0;
        }
        return accessibilityNodeInfo_->GetRectHeight();
    }

    bool GetIsVisible() const
    {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsVisible();
    }

    bool GetIsHinting() const
    {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsHinting();
    }

    bool GetIsEditable() const
    {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsEditable();
    }

    bool GetIsSelected() const
    {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsSelected();
    }

    size_t GetItemCounts() const
    {
        if (!accessibilityNodeInfo_) {
            return 0;
        }
        return accessibilityNodeInfo_->GetItemCounts();
    }

    int32_t GetLiveRegion() const
    {
        if (!accessibilityNodeInfo_) {
            return -1;
        }
        return accessibilityNodeInfo_->GetLiveRegion();
    }

    bool GetIsPassword() const
    {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsPassword();
    }

    bool GetIsCheckable() const
    {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsCheckable();
    }

    bool GetIsClickable() const
    {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsClickable();
    }

    bool GetIsFocusable() const
    {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsFocusable();
    }

    bool GetIsScrollable() const
    {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsScrollable();
    }

    bool GetIsDeletable() const
    {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsDeletable();
    }

    int64_t GetAccessibilityId() const
    {
        if (!accessibilityNodeInfo_) {
            return -1;
        }
        return accessibilityNodeInfo_->GetAccessibilityId();
    }

    bool GetIsPopupSupported() const
    {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsPopupSupported();
    }

    bool GetIsContentInvalid() const
    {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsContentInvalid();
    }

    float GetRangeInfoMin() const
    {
        if (!accessibilityNodeInfo_) {
            return 0;
        }
        return accessibilityNodeInfo_->GetRangeInfoMin();
    }

    float GetRangeInfoMax() const
    {
        if (!accessibilityNodeInfo_) {
            return 0;
        }
        return accessibilityNodeInfo_->GetRangeInfoMax();
    }

    float GetRangeInfoCurrent() const
    {
        if (!accessibilityNodeInfo_) {
            return 0;
        }
        return accessibilityNodeInfo_->GetRangeInfoCurrent();
    }

    int32_t GetSelectionEnd() const
    {
        if (!accessibilityNodeInfo_) {
            return 0;
        }
        return accessibilityNodeInfo_->GetSelectionEnd();
    }

    int32_t GetSelectionStart() const
    {
        if (!accessibilityNodeInfo_) {
            return 0;
        }
        return accessibilityNodeInfo_->GetSelectionStart();
    }

    int32_t GetInputType() const
    {
        if (!accessibilityNodeInfo_) {
            return -1;
        }
        return accessibilityNodeInfo_->GetInputType();
    }

    std::string GetComponentType() const
    {
        if (!accessibilityNodeInfo_) {
            return "";
        }
        return accessibilityNodeInfo_->GetComponentType();
    }

    std::string GetDescriptionInfo() const
    {
        if (!accessibilityNodeInfo_) {
            return "";
        }
        return accessibilityNodeInfo_->GetDescriptionInfo();
    }

    int32_t GetGridRows() const
    {
        if (!accessibilityNodeInfo_) {
            return -1;
        }
        return accessibilityNodeInfo_->GetGridRows();
    }

    int32_t GetGridItemRow() const
    {
        if (!accessibilityNodeInfo_) {
            return -1;
        }
        return accessibilityNodeInfo_->GetGridItemRow();
    }

    int32_t GetGridColumns() const
    {
        if (!accessibilityNodeInfo_) {
            return -1;
        }
        return accessibilityNodeInfo_->GetGridColumns();
    }

    int32_t GetGridItemColumn() const
    {
        if (!accessibilityNodeInfo_) {
            return -1;
        }
        return accessibilityNodeInfo_->GetGridItemColumn();
    }

    int32_t GetGridItemRowSpan() const
    {
        if (!accessibilityNodeInfo_) {
            return -1;
        }
        return accessibilityNodeInfo_->GetGridItemRowSpan();
    }

    int32_t GetGridSelectedMode() const
    {
        if (!accessibilityNodeInfo_) {
            return -1;
        }
        return accessibilityNodeInfo_->GetGridSelectedMode();
    }

    int32_t GetGridItemColumnSpan() const
    {
        if (!accessibilityNodeInfo_) {
            return -1;
        }
        return accessibilityNodeInfo_->GetGridItemColumnSpan();
    }

    bool GetIsAccessibilityFocus() const
    {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsAccessibilityFocus();
    }

    bool GetIsPluralLineSupported() const
    {
        if (!accessibilityNodeInfo_) {
            return false;
        }
        return accessibilityNodeInfo_->GetIsPluralLineSupported();
    }

    RefPtr<FrameNode> GetWebNode() const;

private:
    int64_t pageId_ = -1;
    std::shared_ptr<OHOS::NWeb::NWebAccessibilityNodeInfo> accessibilityNodeInfo_ = nullptr;
    WeakPtr<WebPattern> webPattern_ = nullptr;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_ACCESSIBILITY_NODE_H
