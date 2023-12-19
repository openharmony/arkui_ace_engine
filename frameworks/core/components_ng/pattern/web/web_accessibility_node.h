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
    WebAccessibilityNode(WeakPtr<FrameNode> webNode)
        : FrameNode(V2::WEB_CORE_TAG, 0, MakeRefPtr<Pattern>()), webNode_(webNode)
    {
        CHECK_NULL_VOID(webNode_.Upgrade());
        accessibilityNodeInfo_.pageId = webNode_.Upgrade()->GetPageId();
    }
    ~WebAccessibilityNode() override = default;
    NWeb::NWebAccessibilityNodeInfo& GetAccessibilityNodeInfo()
    {
        return accessibilityNodeInfo_;
    }
    RefPtr<FrameNode> GetWebNode()
    {
        return webNode_.Upgrade();
    }

private:
    NWeb::NWebAccessibilityNodeInfo accessibilityNodeInfo_;
    WeakPtr<FrameNode> webNode_ = nullptr;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_ACCESSIBILITY_NODE_H