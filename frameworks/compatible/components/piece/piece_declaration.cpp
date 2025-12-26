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

#include "compatible/components/piece/piece_declaration.h"

#include "core/components/declaration/common/declaration_constants.h"
#include "bridge/common/utils/utils.h"

namespace OHOS::Ace {

using namespace Framework;

const char DOM_PIECE_CONTENT[] = "content";
const char DOM_PIECE_ICON[] = "icon";
const char DOM_PIECE_CLOSABLE[] = "closable";
const char DOM_PIECE_EVENT_CLOSE[] = "close";

// default value
const std::shared_ptr<PieceAttribute> DEFAULT_PIECE_ATTR = std::make_shared<PieceAttribute>();
const std::shared_ptr<PieceStyle> DEFAULT_PIECE_STYLE = std::make_shared<PieceStyle>();
const std::shared_ptr<PieceEvent> DEFAULT_PIECE_EVENT = std::make_shared<PieceEvent>();

void PieceDeclaration::InitSpecialized()
{
    AddCommonStyle(StyleTag::COMMON_IMAGE_STYLE);
    AddSpecializedAttribute(DEFAULT_PIECE_ATTR);
    AddSpecializedStyle(DEFAULT_PIECE_STYLE);
    AddSpecializedEvent(DEFAULT_PIECE_EVENT);
}

void PieceDeclaration::InitializeStyle()
{
    auto theme = GetTheme<PieceTheme>();
    if (!theme) {
        return;
    }

    SetHasBoxStyle(true);
    SetHasDecorationStyle(true);
    auto& sizeStyle = MaybeResetStyle<CommonSizeStyle>(StyleTag::COMMON_SIZE_STYLE);
    if (sizeStyle.IsValid()) {
        sizeStyle.height = theme->GetHeight();
    }

    auto& paddingStyle = MaybeResetStyle<CommonPaddingStyle>(StyleTag::COMMON_PADDING_STYLE);
    if (paddingStyle.IsValid()) {
        paddingStyle.padding.SetLeft(theme->GetPaddingHorizontal());
        paddingStyle.padding.SetRight(theme->GetPaddingHorizontal());
        paddingStyle.padding.SetTop(theme->GetPaddingVertical());
        paddingStyle.padding.SetBottom(theme->GetPaddingVertical());
    }

    auto& borderStyle = MaybeResetStyle<CommonBorderStyle>(StyleTag::COMMON_BORDER_STYLE);
    if (borderStyle.IsValid()) {
        borderStyle.border.SetBorderRadius(Radius(theme->GetHeight() / 2.0));
    }
    GetBackDecoration()->SetBackgroundColor(theme->GetBackgroundColor());
    SetTextStyle(theme->GetTextStyle());
    SetInterval(theme->GetInterval());
    SetIconResource(theme->GetIconResource());
    SetIconSize(theme->GetIconSize());
    SetHoverColor(theme->GetHoverColor());
}

void PieceDeclaration::InitializeStyle(RefPtr<PieceTheme>& theme)
{
    if (!theme) {
        return;
    }
    SetHasBoxStyle(true);
    SetHasDecorationStyle(true);
    auto& sizeStyle = MaybeResetStyle<CommonSizeStyle>(StyleTag::COMMON_SIZE_STYLE);
    if (sizeStyle.IsValid()) {
        sizeStyle.height = theme->GetHeight();
    }

    auto& paddingStyle = MaybeResetStyle<CommonPaddingStyle>(StyleTag::COMMON_PADDING_STYLE);
    if (paddingStyle.IsValid()) {
        paddingStyle.padding.SetLeft(theme->GetPaddingHorizontal());
        paddingStyle.padding.SetRight(theme->GetPaddingHorizontal());
        paddingStyle.padding.SetTop(theme->GetPaddingVertical());
        paddingStyle.padding.SetBottom(theme->GetPaddingVertical());
    }

    auto& borderStyle = MaybeResetStyle<CommonBorderStyle>(StyleTag::COMMON_BORDER_STYLE);
    if (borderStyle.IsValid()) {
        borderStyle.border.SetBorderRadius(Radius(theme->GetHeight() / 2.0));
    }

    SetTextStyle(theme->GetTextStyle());
    SetInterval(theme->GetInterval());
    SetIconResource(theme->GetIconResource());
    SetIconSize(theme->GetIconSize());
    SetHoverColor(theme->GetHoverColor());
    SetBackGroundColor(theme->GetBackgroundColor());
}

bool PieceDeclaration::SetSpecializedAttr(const std::pair<std::string, std::string>& attr)
{
    if (attr.first == DOM_PIECE_CONTENT) {
        hasContent_ = !attr.second.empty();
        SetContent(attr.second);
        return true;
    } else if (attr.first == DOM_PIECE_ICON) {
        SetIcon(attr.second);
        return true;
    } else if (attr.first == DOM_PIECE_CLOSABLE) {
        SetShowDelete(StringToBool(attr.second));
        return true;
    }
    return false;
}

bool PieceDeclaration::SetSpecializedStyle(const std::pair<std::string, std::string>& style)
{
    if (style.first == "background" || style.first == "backgroundImage") {
        hasBackground_ = true;
    }
    return false;
}

bool PieceDeclaration::SetSpecializedEvent(int32_t pageId, const std::string& eventId, const std::string& event)
{
    if (event == DOM_PIECE_EVENT_CLOSE) {
        SetOnDelete(EventMarker(eventId, event, pageId));
        return true;
    }
    return false;
}

} // namespace OHOS::Ace
