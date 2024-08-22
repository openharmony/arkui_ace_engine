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

#include "core/components/tab_bar/tab_bar_item_component.h"

#include "core/components/flex/flex_component.h"
#include "core/components/padding/padding_component.h"
#include "core/components/tab_bar/tab_bar_item_element.h"

namespace OHOS::Ace {

constexpr Dimension DEFAULT_SINGLE_TEXT_FONT_SIZE = 16.0_fp;
constexpr Dimension DEFAULT_SMALL_TEXT_FONT_SIZE = 10.0_fp;
constexpr Dimension DEFAULT_SMALL_IMAGE_WIDTH = 24.0_vp;
constexpr Dimension DEFAULT_SMALL_IMAGE_HEIGHT = 26.0_vp;

TabBarItemComponent::TabBarItemComponent(const RefPtr<Component>& child)
{
    SetChild(child);
}

TabBarItemComponent::TabBarItemComponent(const std::string& text, const RefPtr<Component>& imageComponent)
{
    std::list<RefPtr<Component>> children;
    RefPtr<ImageComponent> icon = AceType::DynamicCast<ImageComponent>(imageComponent);
    if (icon) {
        icon_ = icon;
        children.push_back(icon_);
    }
    if (!text.empty()) {
        text_ = AceType::MakeRefPtr<TextComponent>(text);
        TextStyle textStyle;
        textStyle.SetTextAlign(TextAlign::CENTER);
        textStyle.SetMaxLines(1);
        textStyle.SetTextOverflow(TextOverflow::CLIP);
        text_->SetTextStyle(textStyle);
        children.push_back(text_);
    }
    if (!children.empty()) {
        auto flex = AceType::MakeRefPtr<ColumnComponent>(FlexAlign::CENTER, FlexAlign::CENTER, children);
        SetChild(flex);
    } else {
        LOGE("Create Tab err: text == null && icon == null");
    }
}

RefPtr<Element> TabBarItemComponent::CreateElement()
{
    return AceType::MakeRefPtr<TabBarItemElement>();
}

RefPtr<RenderNode> TabBarItemComponent::CreateRenderNode()
{
    return RenderTabBarItem::Create();
}

void FindChildren(const RefPtr<Component>& component, std::stack<RefPtr<Component>>& allChildren)
{
    auto singleChildGroup = AceType::DynamicCast<SingleChild>(component);
    if (singleChildGroup) {
        allChildren.push(singleChildGroup->GetChild());
    }

    auto multiChildGroup = AceType::DynamicCast<ComponentGroup>(component);
    if (multiChildGroup) {
        for (const auto& item : multiChildGroup->GetChildren()) {
            allChildren.push(item);
        }
    }
}

void TabBarItemComponent::UpdateStyle(const TextStyle& textStyle, const Color& color)
{
    std::stack<RefPtr<Component>> allChildren;
    allChildren.push(GetChild());

    while (!allChildren.empty()) {
        auto component = allChildren.top();
        allChildren.pop();
        auto text = AceType::DynamicCast<TextComponent>(component);
        auto image = AceType::DynamicCast<ImageComponent>(component);
        if (text) {
            text->SetTextStyle(textStyle);
        } else if (image) {
            image->SetImageFill(color);
        } else {
            FindChildren(component, allChildren);
        }
    }
}

RefPtr<Component> TabBarItemComponent::BuildWithTextIcon(const std::string& textStr, const std::string& iconUri)
{
    if (!textStr.empty() && !iconUri.empty()) {
        auto imageComponent = AceType::MakeRefPtr<ImageComponent>(iconUri);
        auto box = AceType::MakeRefPtr<BoxComponent>();
        auto padding = AceType::MakeRefPtr<PaddingComponent>();
        padding->SetPadding(Edge(0, 0, 0, 2, DimensionUnit::VP));
        padding->SetChild(imageComponent);
        box->SetChild(padding);
        box->SetWidth(DEFAULT_SMALL_IMAGE_WIDTH);
        box->SetHeight(DEFAULT_SMALL_IMAGE_HEIGHT);
        auto textComponent = AceType::MakeRefPtr<TextComponent>(textStr);
        auto textStyle = textComponent->GetTextStyle();
        textStyle.SetFontSize(DEFAULT_SMALL_TEXT_FONT_SIZE);
        textStyle.SetMaxLines(1);
        textStyle.SetTextOverflow(TextOverflow::ELLIPSIS);
        textComponent->SetTextStyle(textStyle);
        std::list<RefPtr<Component>> children;
        children.emplace_back(box);
        children.emplace_back(textComponent);
        auto columnComponent = AceType::MakeRefPtr<ColumnComponent>(FlexAlign::FLEX_START, FlexAlign::CENTER, children);
        columnComponent->SetMainAxisSize(MainAxisSize::MIN);
        return columnComponent;
    }

    if (!textStr.empty()) {
        auto text = AceType::MakeRefPtr<TextComponent>(textStr);
        auto textStyle = text->GetTextStyle();
        textStyle.SetFontSize(DEFAULT_SINGLE_TEXT_FONT_SIZE);
        textStyle.SetMaxLines(1);
        textStyle.SetTextOverflow(TextOverflow::ELLIPSIS);
        text->SetTextStyle(textStyle);
        text->SetAutoMaxLines(false);
        return text;
    }

    return nullptr;
}

} // namespace OHOS::Ace
