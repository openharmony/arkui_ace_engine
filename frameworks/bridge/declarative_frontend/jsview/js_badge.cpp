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
    auto obj = JSRef<JSObject>::Cast(info[0]);
    auto value = obj->GetProperty("value");
    if (!value->IsNull() && value->IsString()) {
        auto label = value->ToString();
        badgeParameters.badgeValue = label;
    }

    auto position = obj->GetProperty("position");
    if (!position->IsNull() && position->IsNumber()) {
        badgeParameters.badgePosition = position->ToNumber<int32_t>();
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

        Color colorVal;
        if (ParseJsColor(colorValue, colorVal)) {
            badgeParameters.badgeTextColor = colorVal;
        }

        CalcDimension fontSize;
        if (ParseJsDimensionFp(fontSizeValue, fontSize)) {
            badgeParameters.badgeFontSize = fontSize;
        }

        CalcDimension badgeSize;
        if (ParseJsDimensionFp(badgeSizeValue, badgeSize)) {
            auto badgeTheme = GetTheme<BadgeTheme>();
            if (badgeSize.IsNonNegative() && badgeSize.Unit() != DimensionUnit::PERCENT) {
                badgeParameters.badgeCircleSize = badgeSize;
            } else if (!badgeTheme) {
                LOGW("Get badge theme error");
                return BadgeParameters();
            } else {
                badgeParameters.badgeCircleSize = badgeTheme->GetBadgeCircleSize();
            }
        }

        Color color;
        if (ParseJsColor(badgeColorValue, color)) {
            badgeParameters.badgeColor = color;
        }

        CalcDimension borderWidth;
        if (ParseJsDimensionVp(borderWidthValue, borderWidth)) {
            badgeParameters.badgeBorderWidth = borderWidth;
        } else {
            auto badgeTheme = GetTheme<BadgeTheme>();
            if (!badgeTheme) {
                LOGW("Get badge theme error");
                return BadgeParameters();
            }
            badgeParameters.badgeBorderWidth = badgeTheme->GetBadgeBorderWidth();
        }

        Color borderColor;
        if (ParseJsColor(borderColorValue, borderColor)) {
            badgeParameters.badgeBorderColor = borderColor;
        } else {
            auto badgeTheme = GetTheme<BadgeTheme>();
            if (!badgeTheme) {
                LOGW("Get badge theme error");
                return BadgeParameters();
            }
            badgeParameters.badgeBorderColor = badgeTheme->GetBadgeBorderColor();
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
    }

    return badgeParameters;
}

void JSBadge::JSBind(BindingTarget globalObj)
{
    JSClass<JSBadge>::Declare("Badge");

    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSBadge>::StaticMethod("create", &JSBadge::Create, opt);
    JSClass<JSBadge>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSBadge>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSBadge>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    
    JSClass<JSBadge>::InheritAndBind<JSContainerBase>(globalObj);
}

void JSBadge::SetDefaultTheme(OHOS::Ace::RefPtr<OHOS::Ace::BadgeComponent>& badge)
{
    auto badgeTheme = GetTheme<BadgeTheme>();
    if (!badgeTheme) {
        LOGE("Get badge theme error");
        return;
    }

    badge->SetBadgeColor(badgeTheme->GetBadgeColor());
    badge->SetMessageCount(badgeTheme->GetMessageCount());
    badge->SetBadgePosition(badgeTheme->GetBadgePosition());
    badge->SetBadgeTextColor(badgeTheme->GetBadgeTextColor());
    badge->SetBadgeFontSize(badgeTheme->GetBadgeFontSize());
    badge->SetBadgeCircleSize(badgeTheme->GetBadgeCircleSize());
}

void JSBadge::SetCustomizedTheme(const JSRef<JSObject>& obj, OHOS::Ace::RefPtr<OHOS::Ace::BadgeComponent>& badge)
{
    auto count = obj->GetProperty("count");
    if (!count->IsNull() && count->IsNumber()) {
        auto value = count->ToNumber<int32_t>();
        badge->SetMessageCount(value);
    }

    auto position = obj->GetProperty("position");
    if (!position->IsNull() && position->IsNumber()) {
        auto value = position->ToNumber<int32_t>();
        badge->SetBadgePosition(static_cast<BadgePosition>(value));
    }

    auto maxCount = obj->GetProperty("maxCount");
    if (!maxCount->IsNull() && maxCount->IsNumber()) {
        auto value = maxCount->ToNumber<int32_t>();
        badge->SetMaxCount(value);
    }

    auto style = obj->GetProperty("style");
    if (!style->IsNull() && style->IsObject()) {
        auto value = JSRef<JSObject>::Cast(style);
        JSRef<JSVal> colorValue = value->GetProperty("color");
        JSRef<JSVal> fontSizeValue = value->GetProperty("fontSize");
        JSRef<JSVal> badgeSizeValue = value->GetProperty("badgeSize");
        JSRef<JSVal> badgeColorValue = value->GetProperty("badgeColor");

        Color colorVal;
        if (ParseJsColor(colorValue, colorVal)) {
            badge->SetBadgeTextColor(colorVal);
        }

        CalcDimension fontSize;
        if (ParseJsDimensionFp(fontSizeValue, fontSize)) {
            badge->SetBadgeFontSize(fontSize);
        }

        CalcDimension badgeSize;
        if (ParseJsDimensionFp(badgeSizeValue, badgeSize)) {
            if (badgeSize.IsNonNegative()) {
                badge->SetBadgeCircleSize(badgeSize);
            }
        }

        Color badgeColor;
        if (ParseJsColor(badgeColorValue, badgeColor)) {
            badge->SetBadgeColor(badgeColor);
        }
    }

    auto value = obj->GetProperty("value");
    if (!value->IsNull() && value->IsString()) {
        auto label = value->ToString();
        badge->SetBadgeLabel(label);
    }
}
} // namespace OHOS::Ace::Framework
