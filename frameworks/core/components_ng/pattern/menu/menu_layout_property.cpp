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

#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"

namespace OHOS::Ace::NG {
void MenuLayoutProperty::BindToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
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
    for (auto&&option : options) {
        auto pattern = DynamicCast<FrameNode>(option)->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(pattern);
        auto jsonValue = JsonUtil::Create(true);

        jsonValue->Put("value", pattern->GetText().c_str());
        jsonValue->Put("icon", pattern->GetIcon().c_str());
        jsonDashArray->Put(std::to_string(index++).c_str(), jsonValue);
    }
    json->PutExtAttr("bindMenu", jsonDashArray, filter);
}

void MenuLayoutProperty::DividerToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    if (propItemDivider_.has_value()) {
        auto divider = JsonUtil::Create(true);
        divider->Put("strokeWidth", propItemDivider_.value().strokeWidth.ToString().c_str());
        divider->Put("startMargin", propItemDivider_.value().startMargin.ToString().c_str());
        divider->Put("endMargin", propItemDivider_.value().endMargin.ToString().c_str());
        divider->Put("color", propItemDivider_.value().color.ColorToString().c_str());
        json->Put("itemDivider", divider);
    }
    if (propItemGroupDivider_.has_value()) {
        auto groupDivider = JsonUtil::Create(true);
        groupDivider->Put("strokeWidth", propItemGroupDivider_.value().strokeWidth.ToString().c_str());
        groupDivider->Put("startMargin", propItemGroupDivider_.value().startMargin.ToString().c_str());
        groupDivider->Put("endMargin", propItemGroupDivider_.value().endMargin.ToString().c_str());
        groupDivider->Put("color", propItemGroupDivider_.value().color.ColorToString().c_str());
        json->Put("itemGroupDivider", groupDivider);
    }
}

void MenuLayoutProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    LayoutProperty::ToJsonValue(json, filter);
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    json->PutExtAttr("title", GetTitle().value_or("").c_str(), filter);
    json->PutExtAttr("offset", GetPositionOffset().value_or(OffsetF()).ToString().c_str(), filter);
    auto context = PipelineBase::GetCurrentContext();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto theme = context ? context->GetTheme<SelectTheme>(host->GetThemeScopeId()) : nullptr;
    auto defaultFontSize = theme ? theme->GetMenuFontSize() : Dimension(0, DimensionUnit::FP);
    json->PutExtAttr("fontSize", GetFontSize().value_or(defaultFontSize).ToString().c_str(), filter);
    auto defaultFontColor = theme ? theme->GetMenuFontColor() : Color::BLACK;
    if (host->GetThemeScopeId()) {
        defaultFontColor = theme ? theme->GetFontColor() : defaultFontColor;
    }
    json->PutExtAttr("fontColor", GetFontColor().value_or(defaultFontColor).ColorToString().c_str(), filter);
    auto fontJsonObject = JsonUtil::Create(true);
    fontJsonObject->Put("size", GetFontSize().value_or(defaultFontSize).ToString().c_str());
    fontJsonObject->Put("weight",
        V2::ConvertWrapFontWeightToStirng(GetFontWeight().value_or(FontWeight::REGULAR)).c_str());
    fontJsonObject->Put("style",
        V2::ConvertWrapFontStyleToStirng(GetItalicFontStyle().value_or(Ace::FontStyle::NORMAL)).c_str());
    fontJsonObject->Put("family", V2::ConvertFontFamily(GetFontFamilyValue({})).c_str());
    json->PutExtAttr("font", fontJsonObject, filter);
    BindToJsonValue(json, filter);
    json->PutExtAttr("showInSubWindow", propShowInSubWindow_.value_or(false) ? "true" : "false", filter);
    auto expandingMode = "SubMenuExpandingMode.SIDE";
    if (propExpandingMode_ == SubMenuExpandingMode::EMBEDDED) {
        expandingMode = "SubMenuExpandingMode.EMBEDDED";
    } else if (propExpandingMode_ == SubMenuExpandingMode::STACK) {
        expandingMode = "SubMenuExpandingMode.STACK";
    }
    json->Put("subMenuExpandingMode", expandingMode);
    DividerToJsonValue(json);
}
} // namespace OHOS::Ace::NG
