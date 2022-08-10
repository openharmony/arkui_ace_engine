/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_TEXT_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_TEXT_COMPONENT_H

#include <string>

#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "core/components/box/drag_drop_event.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/shadow.h"
#include "core/components/common/properties/text_style.h"
#include "core/pipeline/base/component_group.h"
#include "core/components/declaration/text/text_declaration.h"

namespace OHOS::Ace {

// A component can show text.
class ACE_EXPORT TextComponent : public ComponentGroup {
    DECLARE_ACE_TYPE(TextComponent, ComponentGroup);

public:
    explicit TextComponent(const std::string& data);
    ~TextComponent() override = default;

    RefPtr<RenderNode> CreateRenderNode() override;
    RefPtr<Element> CreateElement() override;
    uint32_t Compare(const RefPtr<Component>& component) const override;

    const std::string& GetData() const;
    void SetData(const std::string& data);

    const TextStyle& GetTextStyle() const;
    void SetTextStyle(const TextStyle& textStyle);

    const std::optional<TextAlign>& GetAlignment() const;
    void SetAlignment(const TextAlign& alignment);

    const Color& GetFocusColor() const;
    void SetFocusColor(const Color& focusColor);

    const CopyOptions& GetCopyOption() const;
    void SetCopyOption(const CopyOptions& copyOption);

    bool GetMaxWidthLayout() const;
    void SetMaxWidthLayout(bool isMaxWidthLayout);

    bool GetAutoMaxLines() const;
    void SetAutoMaxLines(bool autoMaxLines);

    bool IsChanged() const;
    void SetIsChanged(bool isChanged);

    void SetOnClick(const EventMarker& onClick);

    const RefPtr<TextDeclaration>& GetDeclaration() const;
    void SetDeclaration(const RefPtr<TextDeclaration>& declaration);
    Dimension GetDeclarationHeight() const;

    void SetRemoteMessageEvent(const EventMarker& eventId);

    const OnDragFunc& GetOnDragStartId() const
    {
        return onDragStartId_;
    }

    void SetOnDragStartId(const OnDragFunc& onDragStartId)
    {
        onDragStartId_ = onDragStartId;
    }

    const OnDropFunc& GetOnDragEnterId() const
    {
        return onDragEnterId_;
    }

    void SetOnDragEnterId(const OnDropFunc& onDragEnterId)
    {
        onDragEnterId_ = onDragEnterId;
    }

    const OnDropFunc& GetOnDragMoveId() const
    {
        return onDragMoveId_;
    }

    void SetOnDragMoveId(const OnDropFunc& onDragMoveId)
    {
        onDragMoveId_ = onDragMoveId;
    }

    const OnDropFunc& GetOnDragLeaveId() const
    {
        return onDragLeaveId_;
    }

    void SetOnDragLeaveId(const OnDropFunc& onDragLeaveId)
    {
        onDragLeaveId_ = onDragLeaveId;
    }

    const OnDropFunc& GetOnDropId() const
    {
        return onDropId_;
    }

    void SetOnDropId(const OnDropFunc& onDropId)
    {
        onDropId_ = onDropId;
    }

private:
    std::optional<TextAlign> alignment_;
    RefPtr<TextDeclaration> declaration_;
    OnDragFunc onDragStartId_;
    OnDropFunc onDragEnterId_;
    OnDropFunc onDragMoveId_;
    OnDropFunc onDragLeaveId_;
    OnDropFunc onDropId_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_TEXT_COMPONENT_H
