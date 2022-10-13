/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/select/select_view.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/select/select_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void SelectView::Create(const std::vector<SelectParam>& params)
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = (stack == nullptr ? 0 : stack->ClaimNodeId());
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SELECT_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<SelectPattern>(); });
    ViewStackProcessor::GetInstance()->Push(frameNode);

    auto pattern = frameNode->GetPattern<SelectPattern>();
    pattern->
}
// void SelectView::SetSelected(int32_t idx)
// {
//     ACE_UPDATE_PAINT_PROPERTY(SelectPaintProperty, SelectSelected, idx);
// }
// void SelectView::SetValue(const std::string& value){}

// void SelectView::SetFontSize(const Dimension& value)
// {
//     ACE_UPDATE_LAYOUT_PROPERTY(SelectLayoutProperty, SelectFontSize, value);
// }
// void SelectView::SetFontColor(const Color& color)
// {
//     ACE_UPDATE_LAYOUT_PROPERTY(SelectLayoutProperty, SelectTextColor, color);
// }
// void SelectView::SetItalicFontStyle(const Ace::FontStyle& value)
// {
//     ACE_UPDATE_LAYOUT_PROPERTY(SelectLayoutProperty, SelectItalicFontStyle, value);
// }
// void SelectView::SetFontWeight(const FontWeight& value)
// {
//     ACE_UPDATE_LAYOUT_PROPERTY(SelectLayoutProperty, SelectFontWeight, value);
// }
// void SelectView::SetFontFamily(const std::vector<std::string>& value)
// {
//     ACE_UPDATE_LAYOUT_PROPERTY(SelectLayoutProperty, SelectFontFamily, value);
// }

// void SelectView::SetSelectedOptionBgColor(const Color& color)
// {
//     ACE_UPDATE_PAINT_PROPERTY(SelectPaintProperty, SelectSelectedOptionBgColor, color);
// }
// void SelectView::SetSelectedOptionFontSize(const Dimension& value)
// {
//     ACE_UPDATE_PAINT_PROPERTY(SelectLayoutProperty, SelectedOptionFontSize, value);
// }
// void SelectView::SetSelectedOptionFontColor(const Color& color)
// {
//     ACE_UPDATE_PAINT_PROPERTY(SelectLayoutProperty, SelectedOptionTextColor, color);
// }
// void SelectView::SetSelectedOptionItalicFontStyle(const Ace::FontStyle& value)
// {
//     ACE_UPDATE_PAINT_PROPERTY(SelectLayoutProperty, SelectedOptionItalicFontStyle, value);
// }
// void SelectView::SetSelectedOptionFontWeight(const FontWeight& value)
// {
//     ACE_UPDATE_PAINT_PROPERTY(SelectLayoutProperty, SelectedOptionFontWeight, value);
// }
// void SelectView::SetSelectedOptionFontFamily(const std::vector<std::string>& value)
// {
//     ACE_UPDATE_PAINT_PROPERTY(SelectLayoutProperty, SelectedOptionFontFamily, value);
// }

// void SelectView::SetOptionBgColor(const Color& color)
// {
//     ACE_UPDATE_PAINT_PROPERTY(SelectPaintProperty, SelectOptionBgColor, color);
// }
// void SelectView::SetOptionFontSize(const Dimension& value)
// {
//     ACE_UPDATE_PAINT_PROPERTY(SelectLayoutProperty, OptionFontSize, value);
// }
// void SelectView::SetOptionFontColor(const Color& color)
// {
//     ACE_UPDATE_PAINT_PROPERTY(SelectLayoutProperty, OptionTextColor, color);
// }
// void SelectView::SetOptionItalicFontStyle(const Ace::FontStyle& value)
// {
//     ACE_UPDATE_PAINT_PROPERTY(SelectLayoutProperty, OptionItalicFontStyle, value);
// }
// void SelectView::SetOptionFontWeight(const FontWeight& value)
// {
//     ACE_UPDATE_PAINT_PROPERTY(SelectLayoutProperty, OptionFontWeight, value);
// }
// void SelectView::SetOptionFontFamily(const std::vector<std::string>& value)
// {
//     ACE_UPDATE_PAINT_PROPERTY(SelectLayoutProperty, OptionFontFamily, value);
// }

// void SelectView::SetOnSelect(SelectEvent&& onSelect){}

} // namespace OHOS::Ace::NG