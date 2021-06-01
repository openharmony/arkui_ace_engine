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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BADGE_BADGE_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BADGE_BADGE_COMPONENT_H

#include "base/geometry/dimension.h"
#include "core/components/common/properties/edge.h"
#include "core/pipeline/base/sole_child_component.h"

namespace OHOS::Ace {

class ACE_EXPORT BadgeComponent : public SoleChildComponent {
    DECLARE_ACE_TYPE(BadgeComponent, SoleChildComponent);

public:
    BadgeComponent();
    ~BadgeComponent() override = default;

    RefPtr<RenderNode> CreateRenderNode() override;
    RefPtr<Element> CreateElement() override;

    const Color& GetBadgeColor() const
    {
        return badgeColor_;
    }

    const Color& GetBadgeTextColor() const
    {
        return badgeTextColor_;
    }

    const Dimension& GetBadgeFontSize() const
    {
        return badgeFontSize_;
    }

    const EventMarker& GetClickEvent() const
    {
        return clickEvent_;
    }

    BadgePosition GetBadgePosition() const
    {
        return badgePosition_;
    }

    const Edge& GetPadding() const
    {
        return padding_;
    }

    const Dimension& GetBadgeCicleSize() const
    {
        return badgeCircleSize_;
    }

    const std::string& GetBadgeLabel() const
    {
        return badgeLabel_;
    }

    void SetPadding(const Edge& padding)
    {
        padding_ = padding;
    }

    int32_t GetMessageCount() const
    {
        return messageCount_;
    }

    bool IsShowMessage() const
    {
        return showMessage_;
    }

    int32_t GetMaxCount() const
    {
        return maxCount_;
    }

    bool IsBadgeCircleSizeDefined() const
    {
        return badgeCircleSizeDefined_;
    }

    void SetBadgeCircleSizeDefined(bool badgeCircleSizeDefined)
    {
        badgeCircleSizeDefined_ = badgeCircleSizeDefined;
    }

    void SetMaxCount(int32_t maxCount)
    {
        maxCount_ = maxCount;
    }

    void SetShowMessage(bool showMessage)
    {
        showMessage_ = showMessage;
    }

    void SetMessageCount(int32_t messageCount)
    {
        messageCount_ = messageCount;
    }

    void SetBadgePosition(BadgePosition badgePostion)
    {
        badgePosition_ = badgePostion;
    }

    void SetBadgeTextColor(const Color& badgeTextColor)
    {
        badgeTextColor_ = badgeTextColor;
    }

    void SetBadgeFontSize(const Dimension& badgeFontSize)
    {
        badgeFontSize_ = badgeFontSize;
    }

    void SetBadgeColor(const Color& color)
    {
        badgeColor_ = color;
    }

    void SetClickEvent(const EventMarker& event)
    {
        clickEvent_ = event;
    }

    void SetBadgeCircleSize(const Dimension& badgeCircleSize)
    {
        badgeCircleSize_ = badgeCircleSize;
        badgeCircleSizeDefined_ = true;
    }

    void SetBadgeLabel(const std::string& badgeLabel)
    {
        badgeLabel_ = badgeLabel;
    }

private:
    Color badgeColor_;
    Color badgeTextColor_;
    Edge padding_;
    EventMarker clickEvent_;
    Dimension badgeFontSize_;
    Dimension badgeCircleSize_;
    BadgePosition badgePosition_ { BadgePosition::RIGHT_TOP };
    int32_t messageCount_ = 0;
    bool showMessage_ = false;
    int32_t maxCount_ = 99;
    bool badgeCircleSizeDefined_ = false;
    std::string badgeLabel_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BADGE_BADGE_COMPONENT_H
