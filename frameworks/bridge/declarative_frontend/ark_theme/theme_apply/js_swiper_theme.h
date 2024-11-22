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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_THEME_JS_SWIPER_THEME_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_THEME_JS_SWIPER_THEME_H

#include "bridge/declarative_frontend/ark_theme/theme_apply/js_theme_utils.h"
#include "bridge/declarative_frontend/jsview/js_swiper.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/swiper/swiper_model.h"
    
namespace OHOS::Ace::Framework {
class JSSwiper;
class JSSwiperTheme : public JSSwiper {
public:
    static void ApplyThemeInConstructor()
    {
        auto themeColors = JSThemeUtils::GetThemeColors();
        if (!themeColors) {
            // no need to apply custom theme colors
            return;
        }
        JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
        JSRef<JSObject> obj = objectTemplate->NewInstance();
        SwiperParameters swiperParameters = JSSwiper::GetDotIndicatorInfo(obj);
        ApplyThemeToDotIndicatorForce(swiperParameters);
        SwiperModel::GetInstance()->SetDotIndicatorStyle(swiperParameters);
        SwiperModel::GetInstance()->SetIndicatorType(SwiperIndicatorType::DOT);
        SwiperModel::GetInstance()->SetShowIndicator(true);
    }

    static void ApplyThemeToDotIndicator(SwiperParameters &swiperParameters, const JSRef<JSObject>& obj)
    {
        auto themeColors = JSThemeUtils::GetThemeColors();
        if (!themeColors.has_value()) {
            return;
        }
        Color color;
        if (!obj->HasProperty("colorValue") || !ParseJsColor(obj->GetProperty("colorValue"), color)) {
            swiperParameters.colorVal = themeColors->CompBackgroundSecondary();
        }
        if (!obj->HasProperty("selectedColorValue") || !ParseJsColor(obj->GetProperty("selectedColorValue"), color)) {
            swiperParameters.selectedColorVal = themeColors->CompBackgroundEmphasize();
        }
    }

    static void ApplyThemeToDotIndicatorForce(SwiperParameters &swiperParameters)
    {
        if (auto themeColors = JSThemeUtils::GetThemeColors(); themeColors.has_value()) {
            swiperParameters.colorVal = themeColors->CompBackgroundSecondary();
            swiperParameters.selectedColorVal = themeColors->CompBackgroundEmphasize();
            return;
        }
    }

    static void ApplyThemeToIndicatorStyle(SwiperParameters &swiperParameters, const JSRef<JSObject>& obj)
    {
        auto themeColors = JSThemeUtils::GetThemeColors();
        if (!themeColors.has_value()) {
            return;
        }
        Color color;
        if (!obj->HasProperty("color") || !ParseJsColor(obj->GetProperty("color"), color)) {
            swiperParameters.colorVal = themeColors->CompBackgroundSecondary();
        }
        if (!obj->HasProperty("selectedColor") || !ParseJsColor(obj->GetProperty("selectedColor"), color)) {
            swiperParameters.selectedColorVal = themeColors->CompBackgroundEmphasize();
        }
    }

    static void ApplyThemeToDigitIndicator(SwiperDigitalParameters &swiperParameters, const JSRef<JSObject>& obj)
    {
        auto themeColors = JSThemeUtils::GetThemeColors();
        if (!themeColors.has_value()) {
            return;
        }
        Color color;
        if (!obj->HasProperty("fontColorValue") || !ParseJsColor(obj->GetProperty("fontColorValue"), color)) {
            swiperParameters.fontColor = themeColors->FontPrimary();
        }
        if (!obj->HasProperty("selectedColorValue") || !ParseJsColor(obj->GetProperty("selectedColorValue"), color)) {
            swiperParameters.selectedFontColor = themeColors->FontPrimary();
        }
    }

    static void ApplyThemeToDisplayArrow(SwiperArrowParameters &swiperParameters, const JSRef<JSObject>& obj)
    {
        auto themeColors = JSThemeUtils::GetThemeColors();
        if (!themeColors.has_value()) {
            return;
        }
        Color color;
        if (!obj->HasProperty("arrowColor") || !ParseJsColor(obj->GetProperty("arrowColor"), color)) {
            swiperParameters.arrowColor = themeColors->IconPrimary();
        }
        if (!obj->HasProperty("backgroundColor") ||
                !ParseJsColor(obj->GetProperty("backgroundColor"), color)) {
            swiperParameters.backgroundColor = themeColors->CompBackgroundSecondary();
        }
    }

    static void ApplyThemeToDisplayArrowForce(SwiperArrowParameters &swiperParameters)
    {
        auto themeColors = JSThemeUtils::GetThemeColors();
        if (themeColors.has_value()) {
            swiperParameters.arrowColor = themeColors->IconPrimary();
            swiperParameters.backgroundColor = themeColors->CompBackgroundSecondary();
        }
    }
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_THEME_JS_SWIPER_THEME_H
