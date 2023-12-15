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
#include <memory>
#include <vector>
#include "base/json/json_util.h"
#include "core/components/indexer/indexer_theme.h"
#include "core/components_v2/inspector/utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float DEFAULT_SIZE = 12.0f;
const std::string DEFAULT_FAMILY = "HarmonyOS Sans";
}
void IndexerLayoutProperty::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    LayoutProperty::ToJsonValue(json);
    json->Put("selected", std::to_string(propSelected_.value_or(0)).c_str());
    json->Put("color", propColor_.value_or(Color::WHITE).ColorToString().c_str());
    json->Put("selectedColor", propSelectedColor_.value_or(Color::WHITE).ColorToString().c_str());
    json->Put("popupColor", propPopupColor_.value_or(Color::WHITE).ColorToString().c_str());
    json->Put("usingPopup", propUsingPopup_.value_or(false) ? "true" : "false");
    json->Put("itemSize", propItemSize_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str());
    json->Put("alignStyle",
        propAlignStyle_.value_or(AlignStyle::LEFT) == AlignStyle::LEFT ? "IndexerAlign.Left" : "IndexerAlign.Right");
    auto PopupPositionJsonObject = JsonUtil::Create(true);
    PopupPositionJsonObject->Put("popupPositionX", propPopupPositionX_.value_or(Dimension()).ToString().c_str());
    PopupPositionJsonObject->Put("popupPositionY", propPopupPositionY_.value_or(Dimension()).ToString().c_str());
    json->Put("popupPosition", PopupPositionJsonObject);
    auto jsonArrayValue = JsonUtil::CreateArray(true);
    auto arrayValue = propArrayValue_.value_or(std::vector<std::string>());
    for (uint32_t i = 0; i < arrayValue.size(); i++) {
        auto index = std::to_string(i);
        jsonArrayValue->Put(index.c_str(), arrayValue[i].c_str());
    }
    json->Put("arrayValue", jsonArrayValue);
    auto defaultFont = TextStyle();
    defaultFont.SetFontStyle(FontStyle::NORMAL);
    defaultFont.SetFontSize(Dimension(DEFAULT_SIZE, DimensionUnit::FP));
    defaultFont.SetFontWeight(FontWeight::REGULAR);
    auto fontFamily = std::vector<std::string>();
    fontFamily.emplace_back(DEFAULT_FAMILY);
    defaultFont.SetFontFamilies(fontFamily);
    auto fontJsonObject = ToJsonObjectValue(propFont_.value_or(defaultFont));
    json->Put("font", fontJsonObject);
    auto selectFontJsonObject = ToJsonObjectValue(propSelectedFont_.value_or(defaultFont));
    json->Put("selectFont", selectFontJsonObject);
    auto popupFontJsonObject = ToJsonObjectValue(propPopupFont_.value_or(defaultFont));
    json->Put("popupFont", popupFontJsonObject);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    auto defaultFontSize = indexerTheme->GetPopupTextStyle().GetFontSize();
    auto defaultFontWeight = indexerTheme->GetPopupTextStyle().GetFontWeight();
    json->Put("popupItemFontSize", propFontSize_.value_or(defaultFontSize).ToString().c_str());
    json->Put("popupItemFontWeight",
        V2::ConvertWrapFontWeightToStirng(propFontWeight_.value_or(defaultFontWeight)).c_str());
    json->Put("autoCollapse", propAutoCollapse_.value_or(false) ? "true" : "false");
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

} // namespace OHOS::Ace::NG
