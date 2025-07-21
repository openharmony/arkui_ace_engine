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

#include "core/components_ng/pattern/search/search_model_ng.h"

#include "base/utils/utf_helper.h"
#include "base/utils/utils.h"
#include "core/common/udmf/udmf_client.h"
#include "core/components/common/properties/color.h"
#include "core/components/search/search_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/search/search_pattern.h"
#include "core/components_ng/pattern/search/search_text_field.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_event_hub.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/divider/divider_layout_property.h"
#include "core/components_ng/pattern/divider/divider_render_property.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEXTFIELD_INDEX = 0;
const std::string DROP_TYPE_STYLED_STRING = "ApplicationDefinedType";
const std::string INSPECTOR_PREFIX = "__SearchField__";
const std::vector<std::string> SPECICALIZED_INSPECTOR_INDEXS = { "", "Image__", "CancelImage__", "CancelButton__",
    "Button__", "Divider__" };
} // namespace

void SearchModelNG::CreateTextFieldMultiThread(const RefPtr<SearchNode>& parentNode,
    const std::optional<std::u16string>& placeholder, const std::optional<std::u16string>& value, bool hasTextFieldNode,
    const RefPtr<SearchTheme>& searchTheme)
{
    CHECK_NULL_VOID(searchTheme);
    auto nodeId = parentNode->GetTextFieldId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SEARCH_Field_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<SearchTextFieldPattern>(); });
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    auto textFieldPaintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    std::set<std::string> allowDropSet({ DROP_TYPE_PLAIN_TEXT, DROP_TYPE_HYPERLINK, DROP_TYPE_STYLED_STRING });
    frameNode->SetAllowDrop(allowDropSet);
    auto parentInspector = parentNode->GetInspectorIdValue("");
    frameNode->UpdateInspectorId(INSPECTOR_PREFIX + SPECICALIZED_INSPECTOR_INDEXS[TEXTFIELD_INDEX] + parentInspector);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    auto textValue = pattern->GetTextUtf16Value();
    if (textFieldLayoutProperty) {
        if (value.has_value() && value.value() != textValue) {
            auto changed = pattern->InitValueText(value.value());
            pattern->SetTextChangedAtCreation(changed);
        }
        textFieldLayoutProperty->UpdatePlaceholder(placeholder.value_or(u""));
        textFieldLayoutProperty->UpdateMaxLines(1);
        textFieldLayoutProperty->UpdatePlaceholderMaxLines(1);
        if (!hasTextFieldNode) {
            textFieldLayoutProperty->UpdateTextColor(searchTheme->GetTextColor());
            textFieldLayoutProperty->UpdatePlaceholderTextColor(searchTheme->GetPlaceholderColor());
        }
    }
    pattern->SetTextFieldController(AceType::MakeRefPtr<TextFieldController>());
    pattern->GetTextFieldController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(pattern)));
    pattern->InitSurfaceChangedCallback();
    pattern->RegisterWindowSizeCallback();
    pattern->SetTextFadeoutCapacity(true);
    pattern->InitSurfacePositionChangedCallback();
    TextFieldUpdateContextMultiThread(frameNode);
    if (!hasTextFieldNode) {
        auto pattern = parentNode->GetPattern<SearchPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetTextFieldNode(frameNode);
        frameNode->MountToParent(parentNode);
    }
    
    auto searchPattern = parentNode->GetPattern<SearchPattern>();
    CHECK_NULL_VOID(searchPattern);
    searchPattern->ProcessTextFieldDefaultStyleAndBehaviors();
}

void SearchModelNG::TextFieldUpdateContextMultiThread(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto textFieldPaintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(textFieldPaintProperty);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);

    PaddingProperty padding({ CalcLength(0.0), CalcLength(0.0), CalcLength(0.0), CalcLength(0.0),
        std::nullopt, std::nullopt });
    textFieldLayoutProperty->UpdatePadding(padding);
    BorderRadiusProperty borderRadius;
    textFieldPaintProperty->UpdateBorderRadiusFlagByUser(borderRadius);
    pattern->SetEnableTouchAndHoverEffect(true);
    textFieldPaintProperty->UpdateBackgroundColor(Color::TRANSPARENT);
}

} // namespace OHOS::Ace::NG
