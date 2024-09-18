/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVDESTINATION_NODE_BASE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVDESTINATION_NODE_BASE_H

#include <cstdint>

#include "core/animation/page_transition_common.h"
#include "core/components_ng/base/group_node.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
class NavDestinationNodeBase : public GroupNode {
    DECLARE_ACE_TYPE(NavDestinationNodeBase, GroupNode)
public:
    NavDestinationNodeBase(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern)
        : GroupNode(tag, nodeId, pattern) {}
    ~NavDestinationNodeBase() override = default;

    void SetContentNode(const RefPtr<UINode>& contentNode)
    {
        contentNode_ = contentNode;
    }

    const RefPtr<UINode>& GetContentNode() const
    {
        return contentNode_;
    }

    void SetTitleBarNode(const RefPtr<UINode>& title)
    {
        titleBarNode_ = title;
    }

    const RefPtr<UINode>& GetTitleBarNode() const
    {
        return titleBarNode_;
    }

    // custom node checking
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(PrevTitleIsCustom, bool);
    void OnPrevTitleIsCustomUpdate(bool value) {}

    void SetTransitionType(PageTransitionType type)
    {
        transitionType_ = type;
    }

    PageTransitionType GetTransitionType() const
    {
        return transitionType_;
    }

    float GetLanguageDirection()
    {
        return AceApplicationInfo::GetInstance().IsRightToLeft() ? -1.0f : 1.0f;
    }

protected:
    RefPtr<UINode> contentNode_;
    RefPtr<UINode> titleBarNode_;
    PageTransitionType transitionType_ = PageTransitionType::NONE;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVDESTINATION_NODE_BASE_H