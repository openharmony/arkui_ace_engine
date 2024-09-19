/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/indexer/indexer_layout_property.h"

#include "core/components/indexer/indexer_theme.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float DEFAULT_SIZE = 12.0f;
}
void IndexerLayoutProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    LayoutProperty::ToJsonValue(json, filter);
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    json->PutExtAttr("selected", std::to_string(propSelected_.value_or(0)).c_str(), filter);
    json->PutExtAttr("color", propColor_.value_or(Color::WHITE).ColorToString().c_str(), filter);
    json->PutExtAttr("selectedColor", propSelectedColor_.value_or(Color::WHITE).ColorToString().c_str(), filter);
    json->PutExtAttr("popupColor", propPopupColor_.value_or(Color::WHITE).ColorToString().c_str(), filter);
    json->PutExtAttr("usingPopup", propUsingPopup_.value_or(false) ? "true" : "false", filter);
    json->PutExtAttr("itemSize",
        propItemSize_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
    std::string alignStyle = AlignStyleToString(propAlignStyle_.value_or(AlignStyle::END));
    json->PutExtAttr("alignStyle", alignStyle.c_str(), filter);
    auto PopupPositionJsonObject = JsonUtil::Create(true);
    PopupPositionJsonObject->Put("popupPositionX", propPopupPositionX_.value_or(Dimension()).ToString().c_str());
    PopupPositionJsonObject->Put("popupPositionY", propPopupPositionY_.value_or(Dimension()).ToString().c_str());
    json->PutExtAttr("popupPosition", PopupPositionJsonObject, filter);
    auto jsonArrayValue = JsonUtil::CreateArray(true);
    auto arrayValue = propArrayValue_.value_or(std::vector<std::string>());
    for (uint32_t i = 0; i < arrayValue.size(); i++) {
        auto index = std::to_string(i);
        jsonArrayValue->Put(index.c_str(), arrayValue[i].c_str());
    }
    json->PutExtAttr("arrayValue", jsonArrayValue, filter);
    auto defaultFont = TextStyle();
    defaultFont.SetFontStyle(FontStyle::NORMAL);
    defaultFont.SetFontSize(Dimension(DEFAULT_SIZE, DimensionUnit::FP));
    defaultFont.SetFontWeight(FontWeight::REGULAR);
    auto fontFamily = std::vector<std::string>();
    defaultFont.SetFontFamilies(fontFamily);
    json->PutExtAttr("font", ToJsonObjectValue(propFont_.value_or(defaultFont)), filter);
    json->PutExtAttr("selectedFont", ToJsonObjectValue(propSelectedFont_.value_or(defaultFont)), filter);
    json->PutExtAttr("popupFont", ToJsonObjectValue(propPopupFont_.value_or(defaultFont)), filter);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    auto defaultFontSize = indexerTheme->GetPopupTextStyle().GetFontSize();
    auto defaultFontWeight = indexerTheme->GetPopupTextStyle().GetFontWeight();
    json->PutExtAttr("popupItemFontSize", propFontSize_.value_or(defaultFontSize).ToString().c_str(), filter);
    json->PutExtAttr("popupItemFontWeight",
        V2::ConvertWrapFontWeightToStirng(propFontWeight_.value_or(defaultFontWeight)).c_str(), filter);
    json->PutExtAttr("autoCollapse", propAutoCollapse_.value_or(false) ? "true" : "false", filter);
    json->PutExtAttr("popupHorizontalSpace", propPopupHorizontalSpace_.value_or(
        Dimension(NG::INDEXER_BUBBLE_INVALID_SPACE, DimensionUnit::VP)).ToString().c_str(), filter);
    json->PutExtAttr("adaptiveWidth", propAdaptiveWidth_.value_or(false) ? "true" : "false", filter);
    json->PutExtAttr("enableHapticFeedback", propEnableHapticFeedback_.value_or(true) ? "true" : "false", filter);
}

std::unique_ptr<JsonValue> IndexerLayoutProperty::ToJsonObjectValue(const TextStyle& textStyle)
{
    auto fontJsonObject = JsonUtil::Create(true);
    fontJsonObject->Put("fontSize", textStyle.GetFontSize().ToString().c_str());
    fontJsonObject->Put(
        "fontStyle", textStyle.GetFontStyle() == FontStyle::NORMAL ? "FontStyle::NORMAL" : "FontStyle::ITALIC");
    fontJsonObject->Put("fontWeight", V2::ConvertWrapFontWeightToStirng(textStyle.GetFontWeight()).c_str());
    auto fontFamilyVector = textStyle.GetFontFamilies();
    std::string fontFamily;
    for (uint32_t i = 0; i < fontFamilyVector.size(); i++) {
        if (i == (fontFamilyVector.size() - 1)) {
            fontFamily += fontFamilyVector.at(i);
            break;
        }
        fontFamily += fontFamilyVector.at(i) + ",";
    }
    fontJsonObject->Put("fontFamily", fontFamily.c_str());
    return fontJsonObject;
}

std::string IndexerLayoutProperty::AlignStyleToString(const AlignStyle& alignStyle)
{
    std::string alignStyleStr;
    switch (alignStyle) {
        case AlignStyle::LEFT:
            alignStyleStr = "IndexerAlign.Left";
            break;
        case AlignStyle::RIGHT:
            alignStyleStr = "IndexerAlign.Right";
            break;
        case AlignStyle::START:
            alignStyleStr = "IndexerAlign.Start";
            break;
        case AlignStyle::END:
            alignStyleStr = "IndexerAlign.End";
            break;
        default:
            break;
    }
    return alignStyleStr;
}


} // namespace OHOS::Ace::NG
