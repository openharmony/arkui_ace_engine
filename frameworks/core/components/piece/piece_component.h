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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PIECE_PIECE_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PIECE_PIECE_COMPONENT_H

#include "base/resource/internal_resource.h"
#include "core/components/common/properties/border.h"
#include "core/components/common/properties/edge.h"
#include "core/components/piece/piece_element.h"
#include "core/components/text/text_component.h"
#include "core/pipeline/base/component.h"
#include "core/pipeline/base/sole_child_component.h"

namespace OHOS::Ace {

class PieceComponent : public SoleChildComponent {
    DECLARE_ACE_TYPE(PieceComponent, SoleChildComponent);

public:
    PieceComponent() = default;
    ~PieceComponent() override = default;

    RefPtr<Element> CreateElement() override;
    RefPtr<RenderNode> CreateRenderNode() override;

    RefPtr<Component> BuildChild();

    const std::string& GetContent() const
    {
        return content_;
    }
    void SetContent(const std::string& content)
    {
        content_ = content;
    }

    const std::string& GetIcon() const
    {
        return icon_;
    }
    void SetIcon(const std::string& icon)
    {
        icon_ = icon;
    }

    void SetTextStyle(const TextStyle& textStyle)
    {
        textStyle_ = textStyle;
    }

    void SetInterval(const Dimension& interval)
    {
        interval_ = interval;
    }

    void SetIconResource(InternalResource::ResourceId iconResource)
    {
        iconResource_ = iconResource;
    }

    void SetIconSize(const Dimension& iconSize)
    {
        iconSize_ = iconSize;
    }

    const EventMarker& GetOnDelete() const
    {
        return onDelete_;
    }
    void SetOnDelete(const EventMarker& onDelete)
    {
        onDelete_ = onDelete;
    }

    bool ShowDelete() const
    {
        return showDelete_;
    }
    void SetShowDelete(bool showDelete)
    {
        showDelete_ = showDelete;
    }

    const Edge& GetMargin() const
    {
        return margin_;
    }
    void SetMargin(const Edge& margin)
    {
        margin_ = margin;
    }

    const Border& GetBorder() const
    {
        return border_;
    }
    void SetBorder(const Border& border)
    {
        border_ = border;
    }

    const Color& GetHoverColor() const
    {
        return hoverColor_;
    }
    void SetHoverColor(const Color& hoverColor)
    {
        hoverColor_ = hoverColor;
    }

private:
    bool showDelete_ = false;
    std::string content_;
    std::string icon_;
    Dimension interval_; // Interval between text and icon.
    Dimension iconSize_;
    TextStyle textStyle_;
    EventMarker onDelete_;
    Edge margin_;
    Border border_;
    Color hoverColor_;
    InternalResource::ResourceId iconResource_ = InternalResource::ResourceId::NO_ID;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PIECE_PIECE_COMPONENT_H
