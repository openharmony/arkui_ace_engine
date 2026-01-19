/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "base/geometry/rrect.h"
#include "base/utils/macros.h"
#include "compatible/components/piece/dom_piece.h"
#include "compatible/components/piece/piece_component.h"
#include "compatible/components/piece/piece_modifier_compatible.h"
#include "core/pipeline/base/component.h"

namespace OHOS::Ace::PieceModifier {
namespace {

RefPtr<PieceComponent> CreatePieceComponent()
{
    auto pieceComponent = AceType::MakeRefPtr<PieceComponent>();
    return pieceComponent;
}
void SetContent(const RefPtr<Component>& component, const std::string& content)
{
    CHECK_NULL_VOID(component);
    auto pieceComponent = AceType::DynamicCast<PieceComponent>(component);
    pieceComponent->SetContent(content);
}

void SetIcon(const RefPtr<Component>& component, const std::string& icon)
{
    CHECK_NULL_VOID(component);
    auto pieceComponent = AceType::DynamicCast<PieceComponent>(component);
    pieceComponent->SetIcon(icon);
}

void InitializeStyle(const RefPtr<Component>& component, RefPtr<PieceTheme>& theme)
{
    CHECK_NULL_VOID(component);
    auto pieceComponent = AceType::DynamicCast<PieceComponent>(component);
    pieceComponent->InitializeStyle(theme);
}

void SetBorder(const RefPtr<Component>& component, const Border& border)
{
    CHECK_NULL_VOID(component);
    auto pieceComponent = AceType::DynamicCast<PieceComponent>(component);
    pieceComponent->SetBorder(border);
}

void SetShowDelete(const RefPtr<Component>& component, bool showDelete)
{
    CHECK_NULL_VOID(component);
    auto pieceComponent = AceType::DynamicCast<PieceComponent>(component);
    pieceComponent->SetShowDelete(showDelete);
}

TextStyle GetTextStyle(const RefPtr<Component>& component)
{
    CHECK_NULL_RETURN(component, TextStyle());
    auto pieceComponent = AceType::DynamicCast<PieceComponent>(component);
    return pieceComponent->GetTextStyle();
}

void SetTextStyle(const RefPtr<Component>& component, const TextStyle& textStyle)
{
    CHECK_NULL_VOID(component);
    auto pieceComponent = AceType::DynamicCast<PieceComponent>(component);
    pieceComponent->SetTextStyle(textStyle);
}

void SetOnDelete(const RefPtr<Component>& component, const EventMarker& onDelete)
{
    CHECK_NULL_VOID(component);
    auto pieceComponent = AceType::DynamicCast<PieceComponent>(component);
    pieceComponent->SetOnDelete(onDelete);
}

} // namespace
const ArkUIPieceModifierCompatible* GetPieceModifier()
{
    static const ArkUIPieceModifierCompatible instance = {
        .createPieceComponent = CreatePieceComponent,
        .setContent = SetContent,
        .setIcon = SetIcon,
        .initializeStyle = InitializeStyle,
        .setBorder = SetBorder,
        .setShowDelete = SetShowDelete,
        .getTextStyle = GetTextStyle,
        .setTextStyle = SetTextStyle,
        .setOnDelete = SetOnDelete,
    };
    return &instance;
}
} // namespace OHOS::Ace::PieceModifier