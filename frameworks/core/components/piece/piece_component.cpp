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

#include "core/components/piece/piece_component.h"

#include "core/components/flex/flex_component.h"
#include "core/components/flex/flex_item_component.h"
#include "core/components/gesture_listener/gesture_listener_component.h"
#include "core/components/image/image_component.h"
#include "core/components/padding/padding_component.h"
#include "core/components/piece/piece_element.h"
#include "core/components/piece/render_piece.h"

namespace OHOS::Ace {

RefPtr<Element> PieceComponent::CreateElement()
{
    return AceType::MakeRefPtr<PieceElement>();
}

RefPtr<RenderNode> PieceComponent::CreateRenderNode()
{
    return RenderPiece::Create();
}

RefPtr<Component> PieceComponent::BuildChild()
{
    if (content_.empty()) {
        return nullptr;
    }
    std::list<RefPtr<Component>> rowChildren;
    auto row = AceType::MakeRefPtr<RowComponent>(FlexAlign::FLEX_START, FlexAlign::CENTER, rowChildren);
    row->SetMainAxisSize(MainAxisSize::MIN);
    auto text = MakeRefPtr<TextComponent>(content_);
    text->SetTextStyle(textStyle_);
    text->SetFocusColor(textStyle_.GetTextColor());
    auto textFlex = MakeRefPtr<FlexItemComponent>(0, 1, 0.0, text);
    row->AppendChild(textFlex);
    if (showDelete_) {
        RefPtr<ImageComponent> image =
            icon_.empty() ? MakeRefPtr<ImageComponent>(iconResource_) : MakeRefPtr<ImageComponent>(icon_);
        image->SetWidth(iconSize_);
        image->SetHeight(iconSize_);
        auto gestureListener = MakeRefPtr<GestureListenerComponent>();
        gestureListener->SetOnClickId(onDelete_);
        gestureListener->SetChild(image);
        auto padding = MakeRefPtr<PaddingComponent>();
        if (GetTextDirection() == TextDirection::RTL) {
            padding->SetPadding(Edge(0.0_vp, 0.0_vp, interval_, 0.0_vp));
        } else {
            padding->SetPadding(Edge(interval_, 0.0_vp, 0.0_vp, 0.0_vp));
        }
        padding->SetChild(gestureListener);
        auto iconFlex = MakeRefPtr<FlexItemComponent>(0, 0, 0.0, padding);
        row->AppendChild(iconFlex);
    }
    row->SetTextDirection(GetTextDirection());
    return row;
}

} // namespace OHOS::Ace