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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UIEXTENSION_COMPONENT_UIEXTENSION_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UIEXTENSION_COMPONENT_UIEXTENSION_NODE_H

#include <optional>

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT UIExtensionNode : public FrameNode {
    DECLARE_ACE_TYPE(UIExtensionNode, FrameNode);

public:
    UIExtensionNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot = false);
    ~UIExtensionNode() override;

    static RefPtr<UIExtensionNode> GetOrCreateUIExtensionNode(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator);
    HitTestResult TouchTest(const PointF& globalPoint, const PointF& parentLocalPoint, const PointF& parentRevertPoint,
        TouchRestrict& touchRestrict, TouchTestResult& result, int32_t touchId, ResponseLinkResult& responseLinkResult,
        bool isDispatch = false) override;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UIEXTENSION_COMPONENT_UIEXTENSION_NODE_H
