/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/indexer/arc_indexer_layout_property.h"
#include <memory>
#include <vector>
#include "base/json/json_util.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::NG {
void ArcIndexerLayoutProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
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
    json->PutExtAttr("usePopup", propUsingPopup_.value_or(false) ? "true" : "false", filter);
    json->PutExtAttr("itemSize",
        propItemSize_.value_or(Dimension(ARC_INDEXER_ITEM_SIZE, DimensionUnit::VP)).ToString().c_str(), filter);
    auto jsonArrayValue = JsonUtil::CreateArray(true);
    auto arrayValue = propArrayValue_.value_or(std::vector<std::string>());
    for (uint32_t i = 0; i < arrayValue.size(); i++) {
        auto index = std::to_string(i);
        jsonArrayValue->Put(index.c_str(), arrayValue[i].c_str());
    }
    json->PutExtAttr("arrayValue", jsonArrayValue, filter);
    auto fontFamily = std::vector<std::string>();
    fontFamily.emplace_back("HarmonyOS Sans");
    auto defaultFont = TextStyle();
    defaultFont.SetFontStyle(FontStyle::NORMAL);
    defaultFont.SetFontSize(Dimension(ARC_INDEXER_ITEM_TEXT_SIZE, DimensionUnit::FP));
    defaultFont.SetFontWeight(FontWeight::W500);
    defaultFont.SetFontFamilies(fontFamily);
    auto defaultPopupFont = TextStyle();
    defaultPopupFont.SetFontStyle(FontStyle::NORMAL);
    defaultPopupFont.SetFontSize(Dimension(ARC_INDEXER_POPUP_TEXT_SIZE, DimensionUnit::FP));
    defaultPopupFont.SetFontWeight(FontWeight::W500);
    defaultPopupFont.SetFontFamilies(fontFamily);
    json->PutExtAttr("font", ToJsonObjectValue(propFont_.value_or(defaultFont)), filter);
    json->PutExtAttr("selectedFont", ToJsonObjectValue(propSelectedFont_.value_or(defaultFont)), filter);
    json->PutExtAttr("popupFont", ToJsonObjectValue(propPopupFont_.value_or(defaultPopupFont)), filter);
    json->PutExtAttr("autoCollapse", propAutoCollapse_.value_or(false) ? "true" : "false", filter);
}

std::unique_ptr<JsonValue> ArcIndexerLayoutProperty::ToJsonObjectValue(const TextStyle& textStyle)
{
    auto fontJsonObject = JsonUtil::Create(true);
    fontJsonObject->Put("size", textStyle.GetFontSize().ToString().c_str());
    fontJsonObject->Put(
        "style", textStyle.GetFontStyle() == FontStyle::NORMAL ? "FontStyle.Normal" : "FontStyle.Italic");
    fontJsonObject->Put("weight", V2::ConvertWrapFontWeightToStirng(textStyle.GetFontWeight()).c_str());
    auto fontFamilyVector = textStyle.GetFontFamilies();
    std::string fontFamily;
    for (uint32_t i = 0; i < fontFamilyVector.size(); i++) {
        if (i == (fontFamilyVector.size() - 1)) {
            fontFamily += fontFamilyVector.at(i);
            break;
        }
        fontFamily += fontFamilyVector.at(i) + ",";
    }
    fontJsonObject->Put("family", fontFamily.c_str());
    return fontJsonObject;
}
} // namespace OHOS::Ace::NG
