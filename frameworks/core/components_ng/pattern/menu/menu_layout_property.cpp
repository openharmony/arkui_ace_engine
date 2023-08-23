/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/menu/menu_layout_property.h"

#include "core/components/common/properties/placement.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"

namespace OHOS::Ace::NG {
void MenuLayoutProperty::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    LayoutProperty::ToJsonValue(json);
    json->Put("title", GetTitle().value_or("").c_str());
    json->Put("offset", GetPositionOffset().value_or(OffsetF()).ToString().c_str());
    auto context = PipelineBase::GetCurrentContext();
    auto theme = context ? context->GetTheme<SelectTheme>() : nullptr;
    auto defaultFontSize = theme ? theme->GetMenuFontSize() : Dimension(0, DimensionUnit::FP);
    json->Put("fontSize", GetFontSize().value_or(defaultFontSize).ToString().c_str());
    auto defaultFontColor = theme ? theme->GetMenuFontColor() : Color::BLACK;
    json->Put("fontColor", GetFontColor().value_or(defaultFontColor).ColorToString().c_str());
    auto fontJsonObject = JsonUtil::Create(true);
    fontJsonObject->Put("size", GetFontSize().value_or(defaultFontSize).ToString().c_str());
    fontJsonObject->Put("weight",
        V2::ConvertWrapFontWeightToStirng(GetFontWeight().value_or(FontWeight::REGULAR)).c_str());
    fontJsonObject->Put("style",
        V2::ConvertWrapFontStyleToStirng(GetItalicFontStyle().value_or(Ace::FontStyle::NORMAL)).c_str());
    fontJsonObject->Put("family", V2::ConvertFontFamily(GetFontFamilyValue({})).c_str());
    json->Put("font", fontJsonObject);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto menuPattern = host->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto options = menuPattern->GetOptions();
    auto jsonDashArray = JsonUtil::CreateArray(true);
    int32_t index = 0;
    // output format
    // {
    //     "bindMenu" : [
    //         <index> : <value>,
    //         ...
    //     ]
    // }
    for (auto&& option : options) {
        auto pattern = DynamicCast<FrameNode>(option)->GetPattern<OptionPattern>();
        CHECK_NULL_VOID(pattern);
        auto jsonValue = JsonUtil::Create(true);

        jsonValue->Put("value", pattern->GetText().c_str());
        jsonValue->Put("icon", pattern->GetIcon().c_str());
        jsonDashArray->Put(std::to_string(index++).c_str(), jsonValue);
    }
    json->Put("bindMenu", jsonDashArray);
}
} // namespace OHOS::Ace::NG
