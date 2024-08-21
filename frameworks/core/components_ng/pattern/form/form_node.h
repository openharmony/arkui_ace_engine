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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_NODE_H

#include <optional>

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT FormNode : public FrameNode {
    DECLARE_ACE_TYPE(FormNode, FrameNode);

public:
    FormNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot = false)
        : FrameNode(tag, nodeId, pattern, isRoot)
    {}
    ~FormNode() override;

    HitTestResult TouchTest(const PointF& globalPoint, const PointF& parentLocalPoint, const PointF& parentRevertPoint,
        TouchRestrict& touchRestrict, TouchTestResult& result, int32_t touchId, ResponseLinkResult& responseLinkResult,
        bool isDispatch = false) override;

    static RefPtr<FormNode> GetOrCreateFormNode(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator);

    void DispatchPointerEvent(const TouchEvent& touchEvent,
        SerializedGesture& serializedGesture);

    void OnDetachFromMainTree(bool, PipelineContext* = nullptr) override;

    OffsetF GetFormOffset() const;

    void InitializeFormAccessibility();

    void OnAccessibilityChildTreeRegister(uint32_t windowId, int32_t treeId);

    void OnAccessibilityChildTreeDeregister();

    void OnSetAccessibilityChildTree(int32_t childWindowId, int32_t childTreeId);

    void OnAccessibilityDumpChildInfo(const std::vector<std::string>& params, std::vector<std::string>& info);

    void NotifyAccessibilityChildTreeRegister();

    int32_t GetImageId()
    {
        if (!imageId_.has_value()) {
            imageId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return imageId_.value();
    }

    void ClearAccessibilityChildTreeRegisterFlag();
private:
    std::optional<int32_t> imageId_;
    std::shared_ptr<AccessibilityChildTreeCallback> accessibilityChildTreeCallback_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_NODE_H
