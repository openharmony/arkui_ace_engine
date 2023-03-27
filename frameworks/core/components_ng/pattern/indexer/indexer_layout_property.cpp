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

#include "core/components_ng/pattern/indexer/indexer_layout_property.h"
#include <memory>
#include <vector>
#include "base/json/json_util.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float DEFAULT_SIZE = 12.0f;
const std::string DEFAULT_FAMILY = "HarmonyOS Sans";
}
void IndexerLayoutProperty::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    LayoutProperty::ToJsonValue(json);
    json->Put("Selected", std::to_string(propSelected_.value_or(0)).c_str());
    json->Put("Color", propColor_.value_or(Color::WHITE).ColorToString().c_str());
    json->Put("SelectedColor", propSelectedColor_.value_or(Color::WHITE).ColorToString().c_str());
    json->Put("PopupColor", propPopupColor_.value_or(Color::WHITE).ColorToString().c_str());
    json->Put("UsingPopup", propUsingPopup_.value_or(false) ? "true" : "false");
    json->Put("ItemSize", propItemSize_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str());
    json->Put("AlignStyle",
        propAlignStyle_.value_or(AlignStyle::LEFT) == AlignStyle::LEFT ? "AlignStyle::LEFT" : "AlignStyle::RIGHT");
    auto PopupPositionJsonObject = JsonUtil::Create(true);
    PopupPositionJsonObject->Put("PopupPositionX", propPopupPositionX_.value_or(Dimension()).ToString().c_str());
    PopupPositionJsonObject->Put("PopupPositionY", propPopupPositionY_.value_or(Dimension()).ToString().c_str());
    json->Put("PopupPosition", PopupPositionJsonObject);
    auto jsonArrayValue = JsonUtil::CreateArray(true);
    auto arrayValue = propArrayValue_.value_or(std::vector<std::string>());
    for (uint32_t i = 0; i < arrayValue.size(); i++) {
        auto index = std::to_string(i);
        jsonArrayValue->Put(index.c_str(), arrayValue[i].c_str());
    }
    json->Put("ArrayValue", jsonArrayValue);
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
    json->Put("SelectFont", selectFontJsonObject);
    auto popupFontJsonObject = ToJsonObjectValue(propPopupFont_.value_or(defaultFont));
    json->Put("PopupFont", popupFontJsonObject);
}

std::unique_ptr<JsonValue> IndexerLayoutProperty::ToJsonObjectValue(const TextStyle& textStyle)
{
    auto fontJsonObject = JsonUtil::Create(true);
    fontJsonObject->Put("FontSize", textStyle.GetFontSize().ToString().c_str());
    fontJsonObject->Put(
        "FontStyle", textStyle.GetFontStyle() == FontStyle::NORMAL ? "FontStyle::NORMAL" : "FontStyle::ITALIC");
    fontJsonObject->Put("FontWeight", V2::ConvertWrapFontWeightToStirng(textStyle.GetFontWeight()).c_str());
    auto fontFamilyVector = textStyle.GetFontFamilies();
    std::string fontFamily;
    for (uint32_t i = 0; i < fontFamilyVector.size(); i++) {
        if (i == (fontFamilyVector.size() - 1)) {
            fontFamily += fontFamilyVector.at(i);
            break;
        }
        fontFamily += fontFamilyVector.at(i) + ",";
    }
    fontJsonObject->Put("FontFamily", fontFamily.c_str());
    return fontJsonObject;
}

} // namespace OHOS::Ace::NG
