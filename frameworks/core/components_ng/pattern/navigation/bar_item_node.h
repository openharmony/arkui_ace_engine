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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_BAR_ITEM_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_BAR_ITEM_NODE_H

#include <cstdint>
#include <optional>

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT BarItemNode : public FrameNode {
    DECLARE_ACE_TYPE(BarItemNode, FrameNode);
public:
    BarItemNode(const std::string& tag, int32_t nodeId);
    BarItemNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern)
        : FrameNode(tag, nodeId, pattern), isMoreItemNode_(false)
    {}
    ~BarItemNode() override = default;

    static RefPtr<BarItemNode> GetOrCreateBarItemNode(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator);
    bool IsAtomicNode() const override
    {
        return false;
    }

    void SetTextNode(const RefPtr<UINode>& text)
    {
        text_ = text;
    }

    const RefPtr<UINode>& GetTextNode() const
    {
        return text_;
    }

    void SetIconNode(const RefPtr<UINode>& icon)
    {
        icon_ = icon;
    }

    const RefPtr<UINode>& GetIconNode() const
    {
        return icon_;
    }

    void SetBarItemUsedInToolbarConfiguration(bool isInToolbar)
    {
        isInToolbar_ = isInToolbar;
    }

    bool IsBarItemUsedInToolbarConfiguration() const
    {
        return isInToolbar_;
    }

    void SetIsMoreItemNode(bool isMoreItemNode)
    {
        isMoreItemNode_ = isMoreItemNode;
    }

    bool IsMoreItemNode() const
    {
        return isMoreItemNode_;
    }
    
    bool IsHideText() const
    {
        return isHideText_;
    }

    void SetIsHideItemText(bool isHideText)
    {
        isHideText_ = isHideText;
    }

    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(IconSrc, std::string);
    void OnIconSrcUpdate(const std::string& value) {}
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(Text, std::string);
    void OnTextUpdate(const std::string& value) {}

private:
    RefPtr<UINode> text_;
    RefPtr<UINode> icon_;
    bool isInToolbar_ = false;
    bool isMoreItemNode_ = false;
    bool isHideText_ = false;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_BAR_ITEM_NODE_H