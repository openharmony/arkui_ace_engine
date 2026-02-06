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
#include "cj_lambda.h"

#include "base/log/log_wrapper.h"
#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/jsview/models/menu_item_model_impl.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;
namespace OHOS::Ace {
// Should use CJUIModifier API later
NG::MenuItemModelNG* GetMenuItemModel()
{
    static NG::MenuItemModelNG* model = nullptr;
    if (model == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("MenuItem");
        if (module == nullptr) {
            LOGF("Can't find MenuItem dynamic module");
            abort();
        }
        model = reinterpret_cast<NG::MenuItemModelNG*>(module->GetModel());
    }
    return model;
}
} // namespace OHOS::Ace

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
    GetMenuItemModel()->Create(customNode);
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
    GetMenuItemModel()->Create(menuItemProps);
}

void FfiOHOSAceFrameworkMenuItemIsSelected(bool value)
{
    GetMenuItemModel()->SetSelected(value);
}

void FfiOHOSAceFrameworkMenuItemSelectIconByBool(bool value)
{
    GetMenuItemModel()->SetSelectIcon(value);
}

void FfiOHOSAceFrameworkMenuItemSelectIconByResource(const char* value)
{
    std::string icon = value;
    GetMenuItemModel()->SetSelectIcon(true);
    GetMenuItemModel()->SetSelectIconSrc(icon);
}

void FfiOHOSAceFrameworkMenuItemContentFont(
    double size, int32_t unit, const char* weight, const char* family, int32_t style)
{
    GetMenuItemModel()->SetFontStyle(static_cast<FontStyle>(style));

    std::string familyVal = family;
    auto fontFamilies = ConvertStrToFontFamilies(familyVal);
    GetMenuItemModel()->SetFontFamily(fontFamilies);

    CalcDimension fontSize = CalcDimension(size, DimensionUnit(unit));
    GetMenuItemModel()->SetFontSize(fontSize);

    std::string weightVal = weight;
    GetMenuItemModel()->SetFontWeight(ConvertStrToFontWeight(weightVal));
}

void FfiOHOSAceFrameworkMenuItemContentFontColor(uint32_t value)
{
    std::optional<Color> color = Color(value);
    GetMenuItemModel()->SetFontColor(color);
}

void FfiOHOSAceFrameworkMenuItemLabelFont(
    double size, int32_t unit, const char* weight, const char* family, int32_t style)
{
    GetMenuItemModel()->SetLabelFontStyle(static_cast<FontStyle>(style));

    std::string familyVal = family;
    auto fontFamilies = ConvertStrToFontFamilies(familyVal);
    GetMenuItemModel()->SetLabelFontFamily(fontFamilies);

    CalcDimension fontSize = CalcDimension(size, DimensionUnit(unit));
    GetMenuItemModel()->SetLabelFontSize(fontSize);

    std::string weightVal = weight;
    GetMenuItemModel()->SetLabelFontWeight(ConvertStrToFontWeight(weightVal));
}

void FfiOHOSAceFrameworkMenuItemLabelFontColor(uint32_t value)
{
    std::optional<Color> color = Color(value);
    GetMenuItemModel()->SetLabelFontColor(color);
}

void FfiOHOSAceFrameworkMenuItemOnChange(void (*callback)(bool isChecked))
{
    GetMenuItemModel()->SetOnChange(CJLambda::Create(callback));
}
}