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
    DECLARE_ACE_TYPE(TitleBarNode, FrameNode)
public:
    TitleBarNode(const std::string& tag, int32_t nodeId);
    TitleBarNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern)
        : FrameNode(tag, nodeId, pattern) {}
    ~TitleBarNode() override = default;
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

    void SetPrevMenu(const RefPtr<UINode>& prevMenu)
    {
        prevMenu_ = prevMenu;
    }

    const RefPtr<UINode>& GetPrevMenu() const
    {
        return prevMenu_;
    }

    void SetMoreMenuNode(const RefPtr<UINode>& moreMenuNode)
    {
        moreMenuNode_ = moreMenuNode;
    }

    void SetIsTitleMenuNodeShowing(const bool isTitleMenuNodeShowing)
    {
        isTitleMenuNodeShowing_ = isTitleMenuNodeShowing;
    }

    bool IsTitleMenuNodeShowing() const
    {
        return isTitleMenuNodeShowing_;
    }
    // The function is only used for fast preview.
    void FastPreviewUpdateChild(int32_t slot, const RefPtr<UINode>& newChild) override;

    void MarkIsInitialTitle(bool isInitialTitle);

    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(PrevMenuIsCustom, bool);
    void OnPrevMenuIsCustomUpdate(bool value) {}

    // node operation related
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(MenuNodeOperation, ChildNodeOperation);
    void OnMenuNodeOperationUpdate(ChildNodeOperation value) {}

private:
    RefPtr<UINode> backButton_;
    RefPtr<UINode> title_;
    RefPtr<UINode> subtitle_;
    RefPtr<UINode> menu_;
    RefPtr<UINode> prevMenu_;
    RefPtr<UINode> moreMenuNode_;
    bool isTitleMenuNodeShowing_ = false;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_TITLE_BAR_NODE_H
