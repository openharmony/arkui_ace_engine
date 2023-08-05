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

#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/menu_model_impl.h"
#include "core/components_ng/pattern/menu/menu_model.h"
#include "core/components_ng/pattern/menu/menu_model_ng.h"

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
}

void JSMenu::FontSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    CalcDimension fontSize;
    if (!ParseJsDimensionFp(info[0], fontSize)) {
        return;
    }
    MenuModel::GetInstance()->SetFontSize(fontSize);
}

void JSMenu::Font(const JSCallbackInfo& info)
{
    CalcDimension fontSize;
    std::string weight;
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGW("The argv is wrong, it is supposed to have at least 1 object argument");
    } else {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> size = obj->GetProperty("size");
        if (!size->IsNull()) {
            ParseJsDimensionFp(size, fontSize);
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
            auto familyVal = jsFamily->ToString();
            auto fontFamilies = ConvertStrToFontFamilies(familyVal);
            MenuModel::GetInstance()->SetFontFamily(fontFamilies);
        }
    }
    MenuModel::GetInstance()->SetFontSize(fontSize);
    MenuModel::GetInstance()->SetFontWeight(ConvertStrToFontWeight(weight));
}

void JSMenu::FontColor(const JSCallbackInfo& info)
{
    std::optional<Color> color = std::nullopt;
    if (info.Length() < 1) {
        LOGW("The argv is wrong, it is supposed to have at least 1 argument");
    } else {
        Color textColor;
        if (ParseJsColor(info[0], textColor)) {
            color = textColor;
        }
    }
    MenuModel::GetInstance()->SetFontColor(color);
}

void JSMenu::JSBind(BindingTarget globalObj)
{
    JSClass<JSMenu>::Declare("Menu");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSMenu>::StaticMethod("create", &JSMenu::Create, opt);
    JSClass<JSMenu>::StaticMethod("fontSize", &JSMenu::FontSize, opt);
    JSClass<JSMenu>::StaticMethod("font", &JSMenu::Font, opt);
    JSClass<JSMenu>::StaticMethod("fontColor", &JSMenu::FontColor, opt);
    JSClass<JSMenu>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSMenu>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSMenu>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSMenu>::InheritAndBind<JSViewAbstract>(globalObj);
}
} // namespace OHOS::Ace::Framework
