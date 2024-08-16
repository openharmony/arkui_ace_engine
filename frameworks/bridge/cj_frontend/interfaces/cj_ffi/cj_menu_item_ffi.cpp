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

#include "cj_menu_item_ffi.h"
#include "core/components_ng/base/view_stack_model.h"
#include "cj_lambda.h"
#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/jsview/models/menu_item_model_impl.h"
using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

extern "C" {
void FfiOHOSAceFrameworkMenuItemCreateByBuilder(void(*builder)())
{
    auto builderFunc = CJLambda::Create(builder);
    RefPtr<NG::UINode> customNode;
    {
        ViewStackModel::GetInstance()->NewScope();
        builderFunc();
        customNode = AceType::DynamicCast<NG::UINode>(ViewStackModel::GetInstance()->Finish());
    }
    MenuItemModel::GetInstance()->Create(customNode);
}

void FfiOHOSAceFrameworkMenuItemCreateByOption(const char* startIcon,
    const char* content, const char* endIcon, const char* labelInfo, void(*builder)())
{
    std::string startIconPath = startIcon;
    std::string contentStr = content;
    std::string endIconPath = endIcon;
    std::string labelStr = labelInfo;
    MenuItemProperties menuItemProps;
    {
        ImageSourceInfo imageSourceInfo(startIconPath, "", "");
        menuItemProps.startIcon = imageSourceInfo;
    }
    {
        ImageSourceInfo imageSourceInfo(endIconPath, "", "");
        menuItemProps.endIcon = imageSourceInfo;
    }
    menuItemProps.content = contentStr;
    menuItemProps.labelInfo = labelStr;
    if (builder) {
        menuItemProps.buildFunc = CJLambda::Create(builder);
    }
    MenuItemModel::GetInstance()->Create(menuItemProps);
}

void FfiOHOSAceFrameworkMenuItemIsSelected(bool value)
{
    MenuItemModel::GetInstance()->SetSelected(value);
}

void FfiOHOSAceFrameworkMenuItemSelectIconByBool(bool value)
{
    MenuItemModel::GetInstance()->SetSelectIcon(value);
}

void FfiOHOSAceFrameworkMenuItemSelectIconByResource(const char* value)
{
    std::string icon = value;
    MenuItemModel::GetInstance()->SetSelectIcon(true);
    MenuItemModel::GetInstance()->SetSelectIconSrc(icon);
}

void FfiOHOSAceFrameworkMenuItemContentFont(
    double size, int32_t unit, const char* weight, const char* family, int32_t style)
{
    MenuItemModel::GetInstance()->SetFontStyle(static_cast<FontStyle>(style));

    std::string familyVal = family;
    auto fontFamilies = ConvertStrToFontFamilies(familyVal);
    MenuItemModel::GetInstance()->SetFontFamily(fontFamilies);

    CalcDimension fontSize = CalcDimension(size, DimensionUnit(unit));
    MenuItemModel::GetInstance()->SetFontSize(fontSize);

    std::string weightVal = weight;
    MenuItemModel::GetInstance()->SetFontWeight(ConvertStrToFontWeight(weightVal));
}

void FfiOHOSAceFrameworkMenuItemContentFontColor(uint32_t value)
{
    std::optional<Color> color = Color(value);
    MenuItemModel::GetInstance()->SetFontColor(color);
}

void FfiOHOSAceFrameworkMenuItemLabelFont(
    double size, int32_t unit, const char* weight, const char* family, int32_t style)
{
    MenuItemModel::GetInstance()->SetLabelFontStyle(static_cast<FontStyle>(style));

    std::string familyVal = family;
    auto fontFamilies = ConvertStrToFontFamilies(familyVal);
    MenuItemModel::GetInstance()->SetLabelFontFamily(fontFamilies);

    CalcDimension fontSize = CalcDimension(size, DimensionUnit(unit));
    MenuItemModel::GetInstance()->SetLabelFontSize(fontSize);

    std::string weightVal = weight;
    MenuItemModel::GetInstance()->SetLabelFontWeight(ConvertStrToFontWeight(weightVal));
}

void FfiOHOSAceFrameworkMenuItemLabelFontColor(uint32_t value)
{
    std::optional<Color> color = Color(value);
    MenuItemModel::GetInstance()->SetLabelFontColor(color);
}

void FfiOHOSAceFrameworkMenuItemOnChange(void (*callback)(bool isChecked))
{
    MenuItemModel::GetInstance()->SetOnChange(CJLambda::Create(callback));
}
}