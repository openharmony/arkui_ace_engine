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

#include "bridge/declarative_frontend/jsview/js_menu.h"

#include "bridge/declarative_frontend/ark_theme/theme_apply/js_menu_theme.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/menu_model_impl.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/menu/menu_model.h"
#include "core/components_ng/pattern/menu/menu_model_ng.h"
#include "core/components_ng/property/measure_property.h"
#include "core/common/resource/resource_parse_utils.h"

namespace OHOS::Ace {
std::unique_ptr<MenuModel> MenuModel::instance_ = nullptr;
std::mutex MenuModel::mutex_;

MenuModel* MenuModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::MenuModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::MenuModelNG());
            } else {
                instance_.reset(new Framework::MenuModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
void JSMenu::Create(const JSCallbackInfo& /* info */)
{
    MenuModel::GetInstance()->Create();
    JSMenuTheme::ApplyTheme();
}

void JSMenu::FontSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension fontSize;
    RefPtr<ResourceObject> fontSizeResObj;
    if (ParseJsDimensionFp(info[0], fontSize, fontSizeResObj)) {
        MenuModel::GetInstance()->SetFontSize(fontSize);
    }
    if (SystemProperties::ConfigChangePerform()) {
        MenuModel::GetInstance()->CreateWithDimensionResourceObj(fontSizeResObj, MenuDimensionType::FONT_SIZE);
    }
}

void JSMenu::Font(const JSCallbackInfo& info)
{
    CalcDimension fontSize;
    std::string weight;
    RefPtr<ResourceObject> fontSizeResObj;
    if (!info[0]->IsObject()) {
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            MenuModel::GetInstance()->SetFontSize(CalcDimension());
            MenuModel::GetInstance()->SetFontWeight(FontWeight::NORMAL);
            MenuModel::GetInstance()->SetFontStyle(FontStyle::NORMAL);
            MenuModel::GetInstance()->ResetFontFamily();
        }
        return;
    } else {
        HandleFontObject(info, fontSize, weight, fontSizeResObj);
    }
    MenuModel::GetInstance()->SetFontSize(fontSize);
    if (SystemProperties::ConfigChangePerform()) {
        MenuModel::GetInstance()->CreateWithDimensionResourceObj(fontSizeResObj, MenuDimensionType::FONT_SIZE);
    }
    MenuModel::GetInstance()->SetFontWeight(ConvertStrToFontWeight(weight));
}

void JSMenu::HandleFontObject(
    const JSCallbackInfo& info, CalcDimension& fontSize, std::string& weight, RefPtr<ResourceObject>& fontSizeResObj)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> size = obj->GetProperty("size");
    if (!size->IsNull()) {
        ParseJsDimensionFp(size, fontSize, fontSizeResObj);
        if (fontSize.Unit() == DimensionUnit::PERCENT) {
            // set zero for abnormal value
            fontSize = CalcDimension();
        }
    }
    auto jsWeight = obj->GetProperty("weight");
    if (!jsWeight->IsNull()) {
        if (jsWeight->IsNumber()) {
            weight = std::to_string(jsWeight->ToNumber<int32_t>());
        } else {
            ParseJsString(jsWeight, weight);
        }
    }
    auto jsStyle = obj->GetProperty("style");
    if (!jsStyle->IsNull()) {
        if (jsStyle->IsNumber()) {
            MenuModel::GetInstance()->SetFontStyle(static_cast<FontStyle>(jsStyle->ToNumber<int32_t>()));
        } else {
            std::string style;
            ParseJsString(jsStyle, style);
            MenuModel::GetInstance()->SetFontStyle(ConvertStrToFontStyle(style));
        }
    }
    auto jsFamily = obj->GetProperty("family");
    if (!jsFamily->IsNull() && jsFamily->IsString()) {
        RefPtr<ResourceObject> familyResObj;
        std::vector<std::string> fontFamilies;
        if (ParseJsFontFamilies(jsFamily, fontFamilies, familyResObj)) {
            MenuModel::GetInstance()->SetFontFamily(fontFamilies);
        }
        if (SystemProperties::ConfigChangePerform()) {
            MenuModel::GetInstance()->CreateWithFontFamilyResourceObj(familyResObj, MenuFamilyType::FONT_FAMILY);
        }
    }
}

void JSMenu::FontColor(const JSCallbackInfo& info)
{
    std::optional<Color> color = std::nullopt;
    if (info.Length() < 1) {
        return;
    } else {
        Color textColor;
        RefPtr<ResourceObject> resObj;
        if (ParseJsColor(info[0], textColor, resObj)) {
            color = textColor;
        }
        MenuModel::GetInstance()->SetFontColor(color);
        if (SystemProperties::ConfigChangePerform()) {
            MenuModel::GetInstance()->CreateWithColorResourceObj(resObj, MenuColorType::FONT_COLOR);
        }
    }
}

void JSMenu::SetWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    const JSRef<JSVal>& jsValue = info[0];
    if (jsValue->IsObject()) {
        JSRef<JSObject> object = JSRef<JSObject>::Cast(jsValue);
        JSRef<JSVal> layoutPolicy = object->GetProperty("id_");
        if (layoutPolicy->IsString()) {
            ViewAbstractModel::GetInstance()->ClearWidthOrHeight(true);
            auto policy = ParseLayoutPolicy(layoutPolicy->ToString());
            ViewAbstractModel::GetInstance()->UpdateLayoutPolicyProperty(policy, true);
            return;
        }
    }

    CalcDimension width;
    RefPtr<ResourceObject> resObj;
    ParseJsDimensionVp(jsValue, width, resObj);
    MenuModel::GetInstance()->SetWidth(width);
    if (SystemProperties::ConfigChangePerform()) {
        MenuModel::GetInstance()->CreateWithDimensionResourceObj(resObj, MenuDimensionType::WIDTH);
    }
}

void JSMenu::HandleDifferentRadius(const JSRef<JSVal>& args)
{
    std::optional<CalcDimension> radiusTopLeft;
    std::optional<CalcDimension> radiusTopRight;
    std::optional<CalcDimension> radiusBottomLeft;
    std::optional<CalcDimension> radiusBottomRight;
    NG::BorderRadiusProperty borderRadius;
    if (args->IsObject()) {
        JSRef<JSObject> object = JSRef<JSObject>::Cast(args);
        CalcDimension topLeft;
        RefPtr<ResourceObject> topLeftResObj;
        if (ParseJsDimensionVp(object->GetProperty("topLeft"), topLeft, topLeftResObj)) {
            radiusTopLeft = topLeft;
        }
        CalcDimension topRight;
        RefPtr<ResourceObject> topRightResObj;
        if (ParseJsDimensionVp(object->GetProperty("topRight"), topRight, topRightResObj)) {
            radiusTopRight = topRight;
        }
        CalcDimension bottomLeft;
        RefPtr<ResourceObject> bottomLeftResObj;
        if (ParseJsDimensionVp(object->GetProperty("bottomLeft"), bottomLeft, bottomLeftResObj)) {
            radiusBottomLeft = bottomLeft;
        }
        CalcDimension bottomRight;
        RefPtr<ResourceObject> bottomRightResObj;
        if (ParseJsDimensionVp(object->GetProperty("bottomRight"), bottomRight, bottomRightResObj)) {
            radiusBottomRight = bottomRight;
        }
        if (!radiusTopLeft.has_value() && !radiusTopRight.has_value() && !radiusBottomLeft.has_value() &&
            !radiusBottomRight.has_value()) {
            return;
        }
        if (SystemProperties::ConfigChangePerform()) {
            ParseBorderRadiusResourceObj(
                topLeftResObj, topRightResObj, bottomLeftResObj, bottomRightResObj, borderRadius);
            borderRadius.radiusTopLeft = radiusTopLeft;
            borderRadius.radiusTopRight = radiusTopRight;
            borderRadius.radiusBottomLeft = radiusBottomLeft;
            borderRadius.radiusBottomRight = radiusBottomRight;
            borderRadius.multiValued = true;
            MenuModel::GetInstance()->SetBorderRadius(borderRadius);
        } else {
            MenuModel::GetInstance()->SetBorderRadius(
                radiusTopLeft, radiusTopRight, radiusBottomLeft, radiusBottomRight);
        }
    }
}

void JSMenu::ParseBorderRadiusResourceObj(const RefPtr<ResourceObject>& topLeftResObj,
    const RefPtr<ResourceObject>& topRightResObj, const RefPtr<ResourceObject>& bottomLeftResObj,
    const RefPtr<ResourceObject>& bottomRightResObj, NG::BorderRadiusProperty& borderRadius)
{
    if (topLeftResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderRadiusProperty& borderRadiusProperty) {
            CalcDimension topLeft;
            if (!ResourceParseUtils::ParseResDimensionVp(resObj, topLeft)) {
                borderRadiusProperty.radiusTopLeft.reset();
                return;
            }
            borderRadiusProperty.radiusTopLeft = topLeft;
        };
        borderRadius.AddResource("borderRadius.topLeft", topLeftResObj, std::move(updateFunc));
    }
    if (topRightResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderRadiusProperty& borderRadiusProperty) {
            CalcDimension topRight;
            if (!ResourceParseUtils::ParseResDimensionVp(resObj, topRight)) {
                borderRadiusProperty.radiusTopRight.reset();
                return;
            }
            borderRadiusProperty.radiusTopRight = topRight;
        };
        borderRadius.AddResource("borderRadius.topRight", topRightResObj, std::move(updateFunc));
    }
    if (bottomLeftResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderRadiusProperty& borderRadiusProperty) {
            CalcDimension bottomLeft;
            if (!ResourceParseUtils::ParseResDimensionVp(resObj, bottomLeft)) {
                borderRadiusProperty.radiusBottomLeft.reset();
                return;
            }
            borderRadiusProperty.radiusBottomLeft = bottomLeft;
        };
        borderRadius.AddResource("borderRadius.bottomLeft", bottomLeftResObj, std::move(updateFunc));
    }
    if (bottomRightResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderRadiusProperty& borderRadiusProperty) {
            CalcDimension bottomRight;
            if (!ResourceParseUtils::ParseResDimensionVp(resObj, bottomRight)) {
                borderRadiusProperty.radiusBottomRight.reset();
                return;
            }
            borderRadiusProperty.radiusBottomRight = bottomRight;
        };
        borderRadius.AddResource("borderRadius.bottomRight", bottomRightResObj, std::move(updateFunc));
    }
}

void JSMenu::SetRadius(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension radius;
    if (info[0]->IsObject()) {
        HandleDifferentRadius(info[0]);
    } else {
        if (!ParseJsDimensionVpNG(info[0], radius)) {
            MenuModel::GetInstance()->ResetBorderRadius();
            return;
        }
        if (LessNotEqual(radius.Value(), 0.0)) {
            MenuModel::GetInstance()->ResetBorderRadius();
            return;
        }
        MenuModel::GetInstance()->SetBorderRadius(radius);
        if (SystemProperties::ConfigChangePerform()) {
            RefPtr<ResourceObject> resObj;
            ParseJsDimensionVp(info[0], radius, resObj);
            MenuModel::GetInstance()->CreateWithDimensionResourceObj(resObj, MenuDimensionType::BORDER_RADIUS);
        }
    }
}

void JSMenu::SetExpandingMode(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || info[0]->IsNull() || !info[0]->IsNumber()) {
        return;
    }

    auto mode = static_cast<SubMenuExpandingMode>(info[0]->ToNumber<int32_t>());
    auto expandingMode = mode == SubMenuExpandingMode::EMBEDDED ? NG::SubMenuExpandingMode::EMBEDDED
                         : mode == SubMenuExpandingMode::STACK  ? NG::SubMenuExpandingMode::STACK
                                                                : NG::SubMenuExpandingMode::SIDE;

    MenuModel::GetInstance()->SetExpandingMode(expandingMode);
}

void JSMenu::SetExpandSymbol(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        return;
    }
    std::function<void(WeakPtr<NG::FrameNode>)> expandSymbol;
    JSViewAbstract::SetSymbolOptionApply(info, expandSymbol, info[0]);
    MenuModel::GetInstance()->SetExpandSymbol(expandSymbol);
}

void JSMenu::SetItemGroupDivider(const JSCallbackInfo& args)
{
    auto mode = DividerMode::FLOATING_ABOVE_MENU;
    auto divider = V2::ItemDivider {
        .strokeWidth = Dimension(0.0f, DimensionUnit::INVALID),
        .color = Color::FOREGROUND,
    };
    if (args.Length() >= 1 && args[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
        CalcDimension value;
        if (!ParseLengthMetricsToPositiveDimension(obj->GetProperty("strokeWidth"), value)) {
            value.Reset();
            value.SetUnit(DimensionUnit::INVALID);
        }
        if (value.IsNegative() || value.Unit() < DimensionUnit::PX || value.Unit() > DimensionUnit::LPX) {
            value.Reset();
            value.SetUnit(DimensionUnit::INVALID);
        }
        divider.strokeWidth = value;
        if (!ParseLengthMetricsToPositiveDimension(obj->GetProperty("startMargin"), value)) {
            value.Reset();
            value.SetUnit(DimensionUnit::INVALID);
        }
        if (value.IsNegative() || value.Unit() < DimensionUnit::PX || value.Unit() > DimensionUnit::LPX) {
            value.Reset();
            value.SetUnit(DimensionUnit::INVALID);
        }
        divider.startMargin = value;
        if (!ParseLengthMetricsToPositiveDimension(obj->GetProperty("endMargin"), value)) {
            value.Reset();
            value.SetUnit(DimensionUnit::INVALID);
        }
        if (value.IsNegative() || value.Unit() < DimensionUnit::PX || value.Unit() > DimensionUnit::LPX) {
            value.Reset();
            value.SetUnit(DimensionUnit::INVALID);
        }
        divider.endMargin = value;
        if (!ConvertFromJSValue(obj->GetProperty("color"), divider.color)) {
            divider.color = Color::FOREGROUND;
        }
        auto modeVal = obj->GetProperty("mode");
        if (modeVal->IsNumber() && modeVal->ToNumber<int32_t>() == 1) {
            mode = DividerMode::EMBEDDED_IN_MENU;
        }
        if (SystemProperties::ConfigChangePerform()) {
            RefPtr<ResourceObject> resObj;
            ParseJsColor(obj->GetProperty("color"), divider.color, resObj);
            MenuModel::GetInstance()->CreateWithColorResourceObj(resObj, MenuColorType::GROUP_DIVIDER_COLOR);
        }
    }
    MenuModel::GetInstance()->SetItemGroupDivider(divider, mode);
    args.ReturnSelf();
}

void JSMenu::SetItemDivider(const JSCallbackInfo& args)
{
    auto mode = DividerMode::FLOATING_ABOVE_MENU;
    V2::ItemDivider divider;
    if (args.Length() >= 1 && args[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
        auto modeVal = obj->GetProperty("mode");
        if (modeVal->IsNumber() && modeVal->ToNumber<int32_t>() == 1) {
            mode = DividerMode::EMBEDDED_IN_MENU;
        }
        CalcDimension value;
        if (!ParseLengthMetricsToPositiveDimension(obj->GetProperty("strokeWidth"), value)) {
            value.Reset();
            value.SetUnit(mode == DividerMode::EMBEDDED_IN_MENU ? DimensionUnit::INVALID : DimensionUnit::PX);
        }
        if (value.IsNegative()) {
            value.Reset();
            value.SetUnit(mode == DividerMode::EMBEDDED_IN_MENU ? DimensionUnit::INVALID : DimensionUnit::PX);
        }
        divider.strokeWidth = value;
        if (!ParseLengthMetricsToPositiveDimension(obj->GetProperty("startMargin"), value)) {
            value.Reset();
            value.SetUnit(mode == DividerMode::EMBEDDED_IN_MENU ? DimensionUnit::INVALID : DimensionUnit::PX);
        }
        if (value.IsNegative()) {
            value.Reset();
            value.SetUnit(mode == DividerMode::EMBEDDED_IN_MENU ? DimensionUnit::INVALID : DimensionUnit::PX);
        }
        divider.startMargin = value;
        if (!ParseLengthMetricsToPositiveDimension(obj->GetProperty("endMargin"), value)) {
            value.Reset();
            value.SetUnit(mode == DividerMode::EMBEDDED_IN_MENU ? DimensionUnit::INVALID : DimensionUnit::PX);
        }
        if (value.IsNegative()) {
            value.Reset();
            value.SetUnit(mode == DividerMode::EMBEDDED_IN_MENU ? DimensionUnit::INVALID : DimensionUnit::PX);
        }
        divider.endMargin = value;

        if (!ConvertFromJSValue(obj->GetProperty("color"), divider.color)) {
            divider.color = Color::TRANSPARENT;
        }
        if (SystemProperties::ConfigChangePerform()) {
            RefPtr<ResourceObject> resObj;
            ParseJsColor(obj->GetProperty("color"), divider.color, resObj);
            MenuModel::GetInstance()->CreateWithColorResourceObj(resObj, MenuColorType::DIVIDER_COLOR);
        }
    }
    MenuModel::GetInstance()->SetItemDivider(divider, mode);
    args.ReturnSelf();
}

void JSMenu::JSBind(BindingTarget globalObj)
{
    JSClass<JSMenu>::Declare("Menu");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSMenu>::StaticMethod("create", &JSMenu::Create, opt);
    JSClass<JSMenu>::StaticMethod("fontSize", &JSMenu::FontSize, opt);
    JSClass<JSMenu>::StaticMethod("font", &JSMenu::Font, opt);
    JSClass<JSMenu>::StaticMethod("fontColor", &JSMenu::FontColor, opt);
    JSClass<JSMenu>::StaticMethod("width", &JSMenu::SetWidth, opt);
    JSClass<JSMenu>::StaticMethod("radius", &JSMenu::SetRadius, opt);
    JSClass<JSMenu>::StaticMethod("subMenuExpandingMode", &JSMenu::SetExpandingMode);
    JSClass<JSMenu>::StaticMethod("subMenuExpandSymbol", &JSMenu::SetExpandSymbol);
    JSClass<JSMenu>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSMenu>::StaticMethod("menuItemDivider", &JSMenu::SetItemDivider);
    JSClass<JSMenu>::StaticMethod("menuItemGroupDivider", &JSMenu::SetItemGroupDivider);
    JSClass<JSMenu>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSMenu>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSMenu>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSMenu>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSMenu>::InheritAndBind<JSViewAbstract>(globalObj);
}
} // namespace OHOS::Ace::Framework
