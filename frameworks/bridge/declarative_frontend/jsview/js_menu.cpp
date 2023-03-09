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
#include "core/components_ng/pattern/menu/menu_view.h"

namespace OHOS::Ace::Framework {
void JSMenu::Create(const JSCallbackInfo& /* info */)
{
    if (Container::IsCurrentUseNewPipeline()) {
        NG::MenuView::Create();
        return;
    }
}

void JSMenu::FontSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Dimension fontSize;
    if (!ParseJsDimensionFp(info[0], fontSize)) {
        return;
    }
    if (Container::IsCurrentUseNewPipeline()) {
        NG::MenuView::SetFontSize(fontSize);
        return;
    }
}

void JSMenu::Font(const JSCallbackInfo& info)
{
    if (!Container::IsCurrentUseNewPipeline()) {
        return;
    }

    Dimension fontSize;
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
    }
    NG::MenuView::SetFontSize(fontSize);
    NG::MenuView::SetFontWeight(ConvertStrToFontWeight(weight));
}

void JSMenu::FontColor(const JSCallbackInfo& info)
{
    if (!Container::IsCurrentUseNewPipeline()) {
        return;
    }
    std::optional<Color> color = std::nullopt;
    if (info.Length() < 1) {
        LOGW("The argv is wrong, it is supposed to have at least 1 argument");
    } else {
        Color textColor;
        if (ParseJsColor(info[0], textColor)) {
            color = textColor;
        }
    }
    NG::MenuView::SetFontColor(color);
}

void JSMenu::JSBind(BindingTarget globalObj)
{
    JSClass<JSMenu>::Declare("Menu");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSMenu>::StaticMethod("create", &JSMenu::Create, opt);

    JSClass<JSMenu>::StaticMethod("fontSize", &JSMenu::FontSize, opt);
    JSClass<JSMenu>::StaticMethod("font", &JSMenu::Font, opt);
    JSClass<JSMenu>::StaticMethod("fontColor", &JSMenu::FontColor, opt);
    JSClass<JSMenu>::Inherit<JSViewAbstract>();
    JSClass<JSMenu>::Bind(globalObj);
}
} // namespace OHOS::Ace::Framework