/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_STAGE_PAGE_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_STAGE_PAGE_NODE_H

#include "core/components_ng/base/frame_node.h"
#include "core/common/page_viewport_config.h"

namespace OHOS::Ace::NG {

class PageNode : public FrameNode {
    DECLARE_ACE_TYPE(PageNode, FrameNode);

public:
    static RefPtr<PageNode> CreatePageNode(int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot = false);

    PageNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern,
        bool isRoot = false, bool isLayoutNode = false) : FrameNode(tag, nodeId, pattern, isRoot, isLayoutNode) {}
    virtual ~PageNode() = default;

    void SetPageViewportConfig(const RefPtr<PageViewportConfig>& config)
    {
        viewportConfig_ = config;
    }
    const RefPtr<PageViewportConfig>& GetPageViewportConfig() const
    {
        return viewportConfig_;
    }

    void Measure(const std::optional<LayoutConstraintF>& parentConstraint) override;
    void Layout() override;

private:
    RefPtr<PageViewportConfig> viewportConfig_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_STAGE_PAGE_NODE_H
