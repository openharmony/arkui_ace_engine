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

#include "bridge/declarative_frontend/jsview/js_menu_item.h"

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/jsview/models/menu_item_model_impl.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_model.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"

namespace OHOS::Ace {
std::unique_ptr<MenuItemModel> MenuItemModel::instance_ = nullptr;
std::mutex MenuItemModel::mutex_;

MenuItemModel* MenuItemModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::MenuItemModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::MenuItemModelNG());
            } else {
                instance_.reset(new Framework::MenuItemModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
void JSMenuItem::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || (!info[0]->IsObject() && !info[0]->IsFunction())) {
        LOGW("JSMenuItem The arg is wrong");
        return;
    }
    // custom menu item
    if (info[0]->IsFunction()) {
        auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(info[0]));
        CHECK_NULL_VOID(builderFunc);
        RefPtr<NG::UINode> customNode;
        {
            ViewStackModel::GetInstance()->NewScope();
            builderFunc->Execute();
            customNode = AceType::DynamicCast<NG::UINode>(ViewStackModel::GetInstance()->Finish());
        }
        CHECK_NULL_VOID(customNode);
        MenuItemModel::GetInstance()->Create(customNode);
    } else {
        auto menuItemObj = JSRef<JSObject>::Cast(info[0]);

        std::string startIconPath;
        std::string contentStr;
        std::string endIconPath;
        std::string labelStr;
        MenuItemProperties menuItemProps;

        auto startIcon = menuItemObj->GetProperty("startIcon");
        auto content = menuItemObj->GetProperty("content");
        auto endIcon = menuItemObj->GetProperty("endIcon");
        auto label = menuItemObj->GetProperty("labelInfo");

        if (ParseJsMedia(startIcon, startIconPath)) {
            menuItemProps.startIcon = startIconPath;
        } else {
            LOGI("startIcon is null");
        }

        if (!ParseJsString(content, contentStr)) {
            LOGI("content is null");
        }
        menuItemProps.content = contentStr;

        if (ParseJsMedia(endIcon, endIconPath)) {
            menuItemProps.endIcon = endIconPath;
        } else {
            LOGI("endIcon is null");
        }

        if (ParseJsString(label, labelStr)) {
            menuItemProps.labelInfo = labelStr;
        } else {
            LOGI("labelInfo is null");
        }

        auto builder = menuItemObj->GetProperty("builder");
        if (!builder.IsEmpty() && builder->IsFunction()) {
            auto subBuilderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builder));
            CHECK_NULL_VOID(subBuilderFunc);
            auto subBuildFunc = [execCtx = info.GetExecutionContext(), func = std::move(subBuilderFunc)]() {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                ACE_SCORING_EVENT("MenuItem SubBuilder");
                func->ExecuteJS();
            };
            menuItemProps.buildFunc = std::move(subBuildFunc);
        }
        MenuItemModel::GetInstance()->Create(menuItemProps);
    }
}

void JSMenuItem::JSBind(BindingTarget globalObj)
{
    JSClass<JSMenuItem>::Declare("MenuItem");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSMenuItem>::StaticMethod("create", &JSMenuItem::Create, opt);

    JSClass<JSMenuItem>::StaticMethod("selected", &JSMenuItem::IsSelected, opt);
    JSClass<JSMenuItem>::StaticMethod("selectIcon", &JSMenuItem::SelectIcon, opt);
    JSClass<JSMenuItem>::StaticMethod("onChange", &JSMenuItem::OnChange, opt);
    JSClass<JSMenuItem>::StaticMethod("contentFont", &JSMenuItem::ContentFont, opt);
    JSClass<JSMenuItem>::StaticMethod("contentFontColor", &JSMenuItem::ContentFontColor, opt);
    JSClass<JSMenuItem>::StaticMethod("labelFont", &JSMenuItem::LabelFont, opt);
    JSClass<JSMenuItem>::StaticMethod("labelFontColor", &JSMenuItem::LabelFontColor, opt);
    JSClass<JSMenuItem>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSMenuItem>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSMenuItem>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSMenuItem>::InheritAndBind<JSViewAbstract>(globalObj);
}

void ParseIsSelectedObject(const JSCallbackInfo& info, const JSRef<JSVal>& changeEventVal)
{
    CHECK_NULL_VOID(changeEventVal->IsFunction());

    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(changeEventVal));
    auto onSelected = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](bool selected) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("MenuItem.SelectedChangeEvent");
        auto newJSVal = JSRef<JSVal>::Make(ToJSValue(selected));
        func->ExecuteJS(1, &newJSVal);
    };
    MenuItemModel::GetInstance()->SetSelectedChangeEvent(std::move(onSelected));
}

void JSMenuItem::IsSelected(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || info.Length() > 2) {
        LOGE("The arg is wrong, it is supposed to have 1 or 2 arguments");
        return;
    }

    bool isSelected = false;
    if (info.Length() > 0 && info[0]->IsBoolean()) {
        isSelected = info[0]->ToBoolean();
    }
    MenuItemModel::GetInstance()->SetSelected(isSelected);
    if (info.Length() > 1 && info[1]->IsFunction()) {
        ParseIsSelectedObject(info, info[1]);
    }
}

void JSMenuItem::SelectIcon(const JSCallbackInfo& info)
{
    bool isShow = false;
    std::string icon;
    if (info.Length() < 1) {
        LOGW("The arg is wrong, it is supposed to have at least 1 arguments");
    } else {
        if (info[0]->IsBoolean()) {
            isShow = info[0]->ToBoolean();
        } else if (info[0]->IsString()) {
            icon = info[0]->ToString();
            isShow = true;
        } else if (ParseJsMedia(info[0], icon)) {
            isShow = true;
        } else {
            LOGW("can not parse select icon.");
        }
    }
    MenuItemModel::GetInstance()->SetSelectIcon(isShow);
    MenuItemModel::GetInstance()->SetSelectIconSrc(icon);
}

void JSMenuItem::OnChange(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsFunction()) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 argument.");
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto onChange = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](bool selected) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("MenuItem.onChange");
        JSRef<JSVal> params[1];
        params[0] = JSRef<JSVal>::Make(ToJSValue(selected));
        func->ExecuteJS(1, params);
    };
    MenuItemModel::GetInstance()->SetOnChange(std::move(onChange));
    info.ReturnSelf();
}

void JSMenuItem::ContentFont(const JSCallbackInfo& info)
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
                MenuItemModel::GetInstance()->SetFontStyle(static_cast<FontStyle>(jsStyle->ToNumber<int32_t>()));
            } else {
                std::string style;
                ParseJsString(jsStyle, style);
                MenuItemModel::GetInstance()->SetFontStyle(ConvertStrToFontStyle(style));
            }
        }

        auto jsFamily = obj->GetProperty("family");
        if (!jsFamily->IsNull() && jsFamily->IsString()) {
            auto familyVal = jsFamily->ToString();
            auto fontFamilies = ConvertStrToFontFamilies(familyVal);
            MenuItemModel::GetInstance()->SetFontFamily(fontFamilies);
        }
    }
    MenuItemModel::GetInstance()->SetFontSize(fontSize);
    MenuItemModel::GetInstance()->SetFontWeight(ConvertStrToFontWeight(weight));
}

void JSMenuItem::ContentFontColor(const JSCallbackInfo& info)
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
    MenuItemModel::GetInstance()->SetFontColor(color);
}

void JSMenuItem::LabelFont(const JSCallbackInfo& info)
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
                MenuItemModel::GetInstance()->SetLabelFontStyle(static_cast<FontStyle>(jsStyle->ToNumber<int32_t>()));
            } else {
                std::string style;
                ParseJsString(jsStyle, style);
                MenuItemModel::GetInstance()->SetLabelFontStyle(ConvertStrToFontStyle(style));
            }
        }

        auto jsFamily = obj->GetProperty("family");
        if (!jsFamily->IsNull() && jsFamily->IsString()) {
            auto familyVal = jsFamily->ToString();
            auto fontFamilies = ConvertStrToFontFamilies(familyVal);
            MenuItemModel::GetInstance()->SetLabelFontFamily(fontFamilies);
        }
    }
    MenuItemModel::GetInstance()->SetLabelFontSize(fontSize);
    MenuItemModel::GetInstance()->SetLabelFontWeight(ConvertStrToFontWeight(weight));
}

void JSMenuItem::LabelFontColor(const JSCallbackInfo& info)
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
    MenuItemModel::GetInstance()->SetLabelFontColor(color);
}
} // namespace OHOS::Ace::Framework
