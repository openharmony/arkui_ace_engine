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

#include "frameworks/bridge/common/dom/dom_piece.h"

#include "core/components/piece/piece_theme.h"

namespace OHOS::Ace::Framework {

DOMPiece::DOMPiece(NodeId nodeId, const std::string& nodeName) : DOMNode(nodeId, nodeName)
{
    pieceChild_ = AceType::MakeRefPtr<PieceComponent>();
    if (IsRightToLeft()) {
        pieceChild_->SetTextDirection(TextDirection::RTL);
    }
}

void DOMPiece::ResetInitializedStyle()
{
    InitializeStyle();
}

void DOMPiece::InitializeStyle()
{
    auto theme = GetTheme<PieceTheme>();
    if (!theme) {
        return;
    }
    hasBoxStyle_ = true;
    hasDecorationStyle_ = true;
    SetHeight(theme->GetHeight());
    paddingLeft_ = theme->GetPaddingHorizontal();
    paddingRight_ = theme->GetPaddingHorizontal();
    paddingTop_ = theme->GetPaddingVertical();
    paddingBottom_ = theme->GetPaddingVertical();
    backDecoration_->SetBackgroundColor(theme->GetBackgroundColor());
    border_.SetBorderRadius(Radius(theme->GetHeight() / 2.0));
    pieceChild_->SetTextStyle(theme->GetTextStyle());
    pieceChild_->SetInterval(theme->GetInterval());
    pieceChild_->SetIconResource(theme->GetIconResource());
    pieceChild_->SetIconSize(theme->GetIconSize());
    pieceChild_->SetHoverColor(theme->GetHoverColor());
}

bool DOMPiece::SetSpecializedAttr(const std::pair<std::string, std::string>& attr)
{
    if (attr.first == DOM_PIECE_CONTENT) {
        hasContent_ = !attr.second.empty();
        pieceChild_->SetContent(attr.second);
        return true;
    } else if (attr.first == DOM_PIECE_ICON) {
        pieceChild_->SetIcon(attr.second);
        return true;
    } else if (attr.first == DOM_PIECE_CLOSABLE) {
        pieceChild_->SetShowDelete(StringToBool(attr.second));
        return true;
    }
    return false;
}

bool DOMPiece::SetSpecializedStyle(const std::pair<std::string, std::string>& style)
{
    if (style.first == DOM_BACKGROUND || style.first == DOM_BACKGROUND_IMAGE) {
        hasBackGround_ = true;
    }
    return false;
}

void DOMPiece::PrepareSpecializedComponent()
{
    if (!hasBackGroundColor_ && hasBackGround_) {
        backDecoration_->SetBackgroundColor(Color::TRANSPARENT);
    }
    pieceChild_->SetMargin(GetBoxComponent()->GetMargin());
    if (boxComponent_->GetBackDecoration()) {
        pieceChild_->SetBorder(boxComponent_->GetBackDecoration()->GetBorder());
    }
    if (!hasContent_) {
        boxComponent_->SetWidth(0.0);
        boxComponent_->SetHeight(0.0);
        boxComponent_->SetPadding(Edge());
        boxComponent_->SetMargin(Edge());
    }
}

bool DOMPiece::AddSpecializedEvent(int32_t pageId, const std::string& event)
{
    if (event == DOM_PIECE_EVENT_CLOSE) {
        pieceChild_->SetOnDelete(EventMarker(GetNodeIdForEvent(), event, pageId));
        return true;
    }
    return false;
}

RefPtr<Component> DOMPiece::GetSpecializedComponent()
{
    return pieceChild_;
}

}; // namespace OHOS::Ace::Framework
