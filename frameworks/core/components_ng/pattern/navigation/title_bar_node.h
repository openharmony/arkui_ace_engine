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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_TITLE_BAR_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_TITLE_BAR_NODE_H

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT TitleBarNode : public FrameNode {
    DECLARE_ACE_TYPE(TitleBarNode, FrameNode);
public:
    TitleBarNode(const std::string& tag, int32_t nodeId);
    TitleBarNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern)
        : FrameNode(tag, nodeId, pattern) {}
    ~TitleBarNode() override;
    static RefPtr<TitleBarNode> GetOrCreateTitleBarNode(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator);

    bool IsAtomicNode() const override
    {
        return false;
    }

    void SetBackButton(const RefPtr<UINode>& button)
    {
        backButton_ = button;
    }

    const RefPtr<UINode>& GetBackButton() const
    {
        return backButton_;
    }

    void SetCustomBackButton(const RefPtr<UINode>& button)
    {
        customBackButton_ = button;
    }

    const RefPtr<UINode>& GetCustomBackButton() const
    {
        return customBackButton_;
    }

    void SetTitle(const RefPtr<UINode>& title)
    {
        title_ = title;
    }

    const RefPtr<UINode>& GetTitle() const
    {
        return title_;
    }

    void SetSubtitle(const RefPtr<UINode>& subtitle)
    {
        subtitle_ = subtitle;
    }

    const RefPtr<UINode>& GetSubtitle() const
    {
        return subtitle_;
    }

    void SetMenu(const RefPtr<UINode>& menu)
    {
        menu_ = menu;
    }

    const RefPtr<UINode>& GetMenu() const
    {
        return menu_;
    }

    void SetInnerParentId(const std::string& id)
    {
        innerChildId_ = id;
    }

    std::string GetInnerParentId() const
    {
        return innerChildId_;
    }

    // The function is only used for fast preview.
    void FastPreviewUpdateChild(int32_t slot, const RefPtr<UINode>& newChild) override;

    void MarkIsInitialTitle(bool isInitialTitle);

    void SetUseContainerModalTitleHeight(bool use)
    {
        useContainerModalTitleHeight_ = use;
    }
    bool UseContainerModalTitleHeight() const
    {
        return useContainerModalTitleHeight_;
    }
    void SetNeedAvoidContainerModal(bool need)
    {
        needAvoidContainerModal_ = need;
    }
    bool NeedAvoidContainerModal() const
    {
        return needAvoidContainerModal_;
    }
    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    void OnAttachToMainTree(bool recursive) override;
    void OnDetachFromMainTree(bool recursive, PipelineContext* context) override;

private:
    RefPtr<UINode> backButton_;
    RefPtr<UINode> customBackButton_;
    RefPtr<UINode> title_;
    RefPtr<UINode> subtitle_;
    RefPtr<UINode> menu_;
    std::string innerChildId_;
    bool needAvoidContainerModal_ = false;
    bool useContainerModalTitleHeight_ = false;
    int32_t menuBarChangeListenerId_ = -1;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_TITLE_BAR_NODE_H
