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
#include "core/components/declaration/piece/piece_declaration.h"

namespace OHOS::Ace {

class PieceComponent : public SoleChildComponent {
    DECLARE_ACE_TYPE(PieceComponent, SoleChildComponent);

public:
    PieceComponent();
    ~PieceComponent() override = default;

    RefPtr<Element> CreateElement() override;
    RefPtr<RenderNode> CreateRenderNode() override;

    RefPtr<Component> BuildChild();

    const std::string& GetContent() const;
    void SetContent(const std::string& content);

    const std::string& GetIcon() const;
    void SetIcon(const std::string& icon);

    const TextStyle& GetTextStyle() const;
    void SetTextStyle(const TextStyle& textStyle);

    const Dimension& GetInterval() const;
    void SetInterval(const Dimension& interval);

    InternalResource::ResourceId GetIconResource() const;
    void SetIconResource(InternalResource::ResourceId iconResource);

    const Dimension& GetIconSize() const;
    void SetIconSize(const Dimension& iconSize);

    const EventMarker& GetOnDelete() const;
    void SetOnDelete(const EventMarker& onDelete);

    bool ShowDelete() const;
    void SetShowDelete(bool showDelete);

    const Edge& GetMargin() const;
    void SetMargin(const Edge& margin);

    const Border& GetBorder() const;
    void SetBorder(const Border& border);

    const Color& GetHoverColor() const;
    void SetHoverColor(const Color& hoverColor);

    void SetDeclaration(const RefPtr<PieceDeclaration>& declaration);

private:
    RefPtr<PieceDeclaration> declaration_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PIECE_PIECE_COMPONENT_H
