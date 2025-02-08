/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_badge.h"

#include "base/geometry/dimension.h"
#include "base/log/ace_trace.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_theme.h"
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_theme_utils.h"
#include "core/components/common/layout/grid_container_info.h"
#include "core/components_ng/pattern/badge/badge_model_ng.h"
#include "frameworks/bridge/declarative_frontend/jsview/models/badge_model_impl.h"

namespace OHOS::Ace {
std::unique_ptr<BadgeModel> BadgeModel::instance_ = nullptr;
std::mutex BadgeModel::mutex_;

BadgeModel* BadgeModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::BadgeModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::BadgeModelNG());
            } else {
                instance_.reset(new Framework::BadgeModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
void JSBadge::Create(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }

    BadgeParameters badgeParameters = CreateBadgeParameters(info);
    BadgeModel::GetInstance()->Create(badgeParameters);
}

BadgeParameters JSBadge::CreateBadgeParameters(const JSCallbackInfo& info)
{
    BadgeParameters badgeParameters;
    if (!info[0]->IsObject()) {
        return badgeParameters;
    }

    auto themeColors = JSThemeUtils::GetThemeColors();

    auto badgeTheme = GetTheme<BadgeTheme>();
    CHECK_NULL_RETURN(badgeTheme, BadgeParameters());
    auto obj = JSRef<JSObject>::Cast(info[0]);
    auto value = obj->GetProperty("value");
    if (!value->IsNull() && value->IsString()) {
        auto label = value->ToString();
        badgeParameters.badgeValue = label;
    } else if (!value->IsNull() && value->IsObject()) {
        std::string valueResult;
        ParseJsString(value, valueResult);
        badgeParameters.badgeValue = valueResult;
    }

    auto position = obj->GetProperty("position");
    if (!position->IsNull() && position->IsNumber()) {
        badgeParameters.isPositionXy = false;
        badgeParameters.badgePosition = position->ToNumber<int32_t>();
    } else if (!position->IsNull() && position->IsObject()) {
        badgeParameters.isPositionXy = true;
        auto postionValue = JSRef<JSObject>::Cast(position);
        JSRef<JSVal> xVal = postionValue->GetProperty("x");
        JSRef<JSVal> yVal = postionValue->GetProperty("y");
        CalcDimension dimenX;
        CalcDimension dimenY;
        bool xResult = ParseJsDimensionVp(xVal, dimenX);
        bool yResult = ParseJsDimensionVp(yVal, dimenY);
        if (!(xResult || yResult)) {
            badgeParameters.badgePositionX = badgeTheme->GetBadgePositionX();
            badgeParameters.badgePositionY = badgeTheme->GetBadgePositionY();
        } else {
            badgeParameters.badgePositionX = dimenX;
            badgeParameters.badgePositionY = dimenY;
        }
    }

    auto style = obj->GetProperty("style");
    if (!style->IsNull() && style->IsObject()) {
        auto value = JSRef<JSObject>::Cast(style);
        JSRef<JSVal> colorValue = value->GetProperty("color");
        JSRef<JSVal> fontSizeValue = value->GetProperty("fontSize");
        JSRef<JSVal> badgeSizeValue = value->GetProperty("badgeSize");
        JSRef<JSVal> badgeColorValue = value->GetProperty("badgeColor");
        JSRef<JSVal> borderColorValue = value->GetProperty("borderColor");
        JSRef<JSVal> borderWidthValue = value->GetProperty("borderWidth");
        JSRef<JSVal> fontWeightValue = value->GetProperty("fontWeight");

        bool isDefaultFontSize = true;
        bool isDefaultBadgeSize = true;

        Color colorVal;
        if (ParseJsColor(colorValue, colorVal)) {
            badgeParameters.badgeTextColor = colorVal;
        } else {
            if (themeColors) {
                badgeParameters.badgeTextColor = themeColors->FontOnPrimary();
            }
        }

        CalcDimension fontSize;
        if (ParseJsDimensionNG(fontSizeValue, fontSize, DimensionUnit::FP)) {
            if (fontSize.IsNonNegative() && fontSize.Unit() != DimensionUnit::PERCENT) {
                badgeParameters.badgeFontSize = fontSize;
                isDefaultFontSize = false;
            } else {
                badgeParameters.badgeFontSize = badgeTheme->GetBadgeFontSize();
            }
        } else if (!fontSizeValue->IsUndefined()) {
            badgeParameters.badgeFontSize = badgeTheme->GetBadgeFontSize();
        } else {
            badgeParameters.badgeFontSize = UNDEFINED_DIMENSION;
        }

        CalcDimension badgeSize;
        if (ParseJsDimensionNG(badgeSizeValue, badgeSize, DimensionUnit::FP)) {
            if (badgeSize.IsNonNegative() && badgeSize.Unit() != DimensionUnit::PERCENT) {
                badgeParameters.badgeCircleSize = badgeSize;
                isDefaultBadgeSize = false;
            } else {
                badgeParameters.badgeCircleSize = badgeTheme->GetBadgeCircleSize();
            }
        } else {
            badgeParameters.badgeCircleSize = badgeTheme->GetBadgeCircleSize();
        }

        BadgeModel::GetInstance()->SetIsDefault(isDefaultFontSize, isDefaultBadgeSize);
        Color color;
        if (ParseJsColor(badgeColorValue, color)) {
            badgeParameters.badgeColor = color;
        } else {
            if (themeColors) {
                badgeParameters.badgeColor = themeColors->Warning();
            }
        }

        CalcDimension borderWidth;
        if (ParseJsDimensionVp(borderWidthValue, borderWidth)) {
            if (borderWidth.IsNonNegative() && borderWidth.Unit() != DimensionUnit::PERCENT) {
                badgeParameters.badgeBorderWidth = borderWidth;
            } else {
                badgeParameters.badgeBorderWidth = badgeTheme->GetBadgeBorderWidth();
            }
        } else {
            badgeParameters.badgeBorderWidth = badgeTheme->GetBadgeBorderWidth();
        }

        Color borderColor;
        if (ParseJsColor(borderColorValue, borderColor)) {
            badgeParameters.badgeBorderColor = borderColor;
        } else {
            badgeParameters.badgeBorderColor = themeColors ? themeColors->Warning() : badgeTheme->GetBadgeBorderColor();
        }

        std::string fontWeight;
        if (fontWeightValue->IsNumber()) {
            fontWeight = std::to_string(fontWeightValue->ToNumber<int32_t>());
        } else {
            if (!ParseJsString(fontWeightValue, fontWeight)) {
                badgeParameters.badgeFontWeight = FontWeight::NORMAL;
            }
        }
        badgeParameters.badgeFontWeight = ConvertStrToFontWeight(fontWeight);
    }

    auto count = obj->GetProperty("count");
    if (!count->IsNull() && count->IsNumber()) {
        badgeParameters.badgeCount = count->ToNumber<int32_t>();
    }
    auto maxCount = obj->GetProperty("maxCount");
    if (!maxCount->IsNull() && maxCount->IsNumber()) {
        badgeParameters.badgeMaxCount = maxCount->ToNumber<int32_t>();
    } else {
        badgeParameters.badgeMaxCount = badgeTheme->GetMaxCount();
    }

    return badgeParameters;
}

void JSBadge::JSBind(BindingTarget globalObj)
{
    JSClass<JSBadge>::Declare("Badge");

    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSBadge>::StaticMethod("create", &JSBadge::Create, opt);
    JSClass<JSBadge>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSBadge>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSBadge>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSBadge>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSBadge>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);

    JSClass<JSBadge>::InheritAndBind<JSContainerBase>(globalObj);
}
} // namespace OHOS::Ace::Framework
