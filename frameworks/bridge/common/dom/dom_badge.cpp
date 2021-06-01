/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/common/dom/dom_badge.h"

#include "base/log/event_report.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::Framework {

DOMBadge::DOMBadge(NodeId nodeId, const std::string& nodeName) : DOMNode(nodeId, nodeName)
{
    badgeChild_ = AceType::MakeRefPtr<BadgeComponent>();
    if (IsRightToLeft()) {
        badgeChild_->SetTextDirection(TextDirection::RTL);
    }
}

void DOMBadge::ResetInitializedStyle()
{
    InitializeStyle();
}

bool DOMBadge::SetSpecializedAttr(const std::pair<std::string, std::string>& attr)
{
    static const LinearMapNode<void (*)(DOMBadge&, const std::string&)> badgeAttrOperators[] = {
        { DOM_BADGE_COUNT,
            [](DOMBadge& badge, const std::string& value) { badge.badgeChild_->SetMessageCount(StringToInt(value)); } },
        { DOM_BADGE_LABEL,
            [](DOMBadge& badge, const std::string& value) { badge.badgeChild_->SetBadgeLabel(value); } },
        { DOM_BADGE_MAX_COUNT,
            [](DOMBadge& badge, const std::string& value) { badge.badgeChild_->SetMaxCount(StringToInt(value)); } },
        { DOM_BADGE_PLACEMENT,
            [](DOMBadge& badge, const std::string& value) {
                badge.badgeChild_->SetBadgePosition(ConvertStrToBadgePosition(value));
            } },
        { DOM_BADGE_VISIBLE,
            [](DOMBadge& badge, const std::string& value) { badge.badgeChild_->SetShowMessage(StringToBool(value)); } }
    };
    auto operatorIter = BinarySearchFindIndex(badgeAttrOperators, ArraySize(badgeAttrOperators), attr.first.c_str());
    if (operatorIter != -1) {
        badgeAttrOperators[operatorIter].value(*this, attr.second);
        return true;
    }
    return false;
}

bool DOMBadge::SetSpecializedStyle(const std::pair<std::string, std::string>& style)
{
    const static LinearMapNode<void (*)(DOMBadge&, const std::string&)> badgeOperators[] = {
        { DOM_BADGE_COLOR,
            [](DOMBadge& badge, const std::string& value) {
                badge.badgeChild_->SetBadgeColor(badge.ParseColor(value));
            } },
        { DOM_BADGE_CIRCLE_SIZE,
            [](DOMBadge& badge, const std::string& value) {
                badge.badgeChild_->SetBadgeCircleSize(badge.ParseDimension(value));
            } },
        { DOM_BADGE_TEXT_FONT_SIZE,
            [](DOMBadge& badge, const std::string& value) {
                badge.badgeChild_->SetBadgeFontSize(badge.ParseDimension(value));
            } },
        { DOM_BADGE_TEXT_COLOR,
            [](DOMBadge& badge, const std::string& value) {
                badge.badgeChild_->SetBadgeTextColor(badge.ParseColor(value));
            } },
    };
    auto operatorIter = BinarySearchFindIndex(badgeOperators, ArraySize(badgeOperators), style.first.c_str());
    if (operatorIter != -1) {
        badgeOperators[operatorIter].value(*this, style.second);
        return true;
    }
    return false;
}

bool DOMBadge::AddSpecializedEvent(int32_t pageId, const std::string& event)
{
    if (event == DOM_CLICK) {
        badgeClickEvent_ = EventMarker(GetNodeIdForEvent(), event, pageId);
        badgeChild_->SetClickEvent(badgeClickEvent_);
        return true;
    }
    return false;
}

void DOMBadge::PrepareSpecializedComponent()
{
    if (!boxComponent_) {
        return;
    }
    boxComponent_->SetAlignment(Alignment::TOP_LEFT);
    auto edge = boxComponent_->GetPadding();
    if (edge == Edge::NONE) {
        return;
    }
    badgeChild_->SetPadding(edge);
    boxComponent_->SetPadding(Edge());
}

void DOMBadge::OnChildNodeAdded(const RefPtr<DOMNode>& child, int32_t slot)
{
    ACE_DCHECK(child);
    if (badgeChild_->GetChild()) {
        return;
    }
    badgeChild_->SetChild(child->GetRootComponent());
}

void DOMBadge::OnChildNodeRemoved(const RefPtr<DOMNode>& child)
{
    badgeChild_->SetChild(nullptr);
}

void DOMBadge::InitializeStyle()
{
    badgeTheme_ = GetTheme<BadgeTheme>();
    if (!badgeTheme_) {
        LOGE("badgeTheme is null");
        EventReport::SendComponentException(ComponentExcepType::GET_THEME_ERR);
        return;
    }
    badgeChild_->SetBadgeColor(badgeTheme_->GetBadgeColor());
    badgeChild_->SetMessageCount(badgeTheme_->GetMessageCount());
    badgeChild_->SetBadgePosition(badgeTheme_->GetBadgePosition());
    badgeChild_->SetShowMessage(badgeTheme_->GetShowMessage());
    badgeChild_->SetBadgeTextColor(badgeTheme_->GetBadgeTextColor());
    badgeChild_->SetBadgeFontSize(badgeTheme_->GetBadgeFontSize());
}

void DOMBadge::SetBadgeConfig(const BadgeConfig& badgeConfig)
{
    if (badgeConfig.badgeColor.second) {
        badgeChild_->SetBadgeColor(badgeConfig.badgeColor.first);
    }
    if (badgeConfig.badgeSize.second) {
        badgeChild_->SetBadgeCircleSize(badgeConfig.badgeSize.first);
    }
    if (badgeConfig.textColor.second) {
        badgeChild_->SetBadgeTextColor(badgeConfig.textColor.first);
    }
    if (badgeConfig.textSize.second) {
        badgeChild_->SetBadgeFontSize(badgeConfig.textSize.first);
    }
}

} // namespace OHOS::Ace::Framework
