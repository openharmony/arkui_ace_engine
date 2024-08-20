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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCREEN_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCREEN_NODE_H

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ScreenNode : public FrameNode {
    DECLARE_ACE_TYPE(ScreenNode, FrameNode);

public:
    ScreenNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot = false)
        : FrameNode(tag, nodeId, pattern, isRoot)
    {}
    ~ScreenNode() override = default;

    HitTestResult TouchTest(const PointF& globalPoint, const PointF& parentLocalPoint, const PointF& parentRevertPoint,
        TouchRestrict& touchRestrict, TouchTestResult& result, int32_t touchId, ResponseLinkResult& responseLinkResult,
        bool isDispatch = false) override;

    static RefPtr<ScreenNode> GetOrCreateScreenNode(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCREEN_NODE_H