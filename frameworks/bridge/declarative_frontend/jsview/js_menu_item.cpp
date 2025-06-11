/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_model.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_menu_item_theme.h"
#include "core/components_ng/pattern/symbol/symbol_source_info.h"

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
void JSMenuItem::ParseMenuItemOptionsResource(
    const JSCallbackInfo& info, const JSRef<JSObject>& menuItemObj, MenuItemProperties& menuItemProps)
{
    std::string startIconPath;
    std::string contentStr;
    std::string endIconPath;
    std::string labelStr;
    std::function<void(WeakPtr<NG::FrameNode>)> symbolApply;

    auto startIcon = menuItemObj->GetProperty("startIcon");
    auto content = menuItemObj->GetProperty("content");
    auto endIcon = menuItemObj->GetProperty("endIcon");
    auto label = menuItemObj->GetProperty("labelInfo");
    auto symbolStart = menuItemObj->GetProperty("symbolStartIcon");
    auto symbolEnd = menuItemObj->GetProperty("symbolEndIcon");

    if (symbolStart->IsObject()) {
        JSViewAbstract::SetSymbolOptionApply(info, symbolApply, symbolStart);
        menuItemProps.startApply = symbolApply;
    } else if (ParseJsMedia(startIcon, startIconPath)) {
        std::string bundleName;
        std::string moduleName;
        GetJsMediaBundleInfo(startIcon, bundleName, moduleName);
        ImageSourceInfo imageSourceInfo(startIconPath, bundleName, moduleName);
        menuItemProps.startIcon = imageSourceInfo;
    }

    ParseJsString(content, contentStr);
    menuItemProps.content = contentStr;

    if (symbolEnd->IsObject()) {
        JSViewAbstract::SetSymbolOptionApply(info, symbolApply, symbolEnd);
        menuItemProps.endApply = symbolApply;
    } else if (ParseJsMedia(endIcon, endIconPath)) {
        std::string bundleName;
        std::string moduleName;
        GetJsMediaBundleInfo(endIcon, bundleName, moduleName);
        ImageSourceInfo imageSourceInfo(endIconPath, bundleName, moduleName);
        menuItemProps.endIcon = imageSourceInfo;
    }

    if (ParseJsString(label, labelStr)) {
        menuItemProps.labelInfo = labelStr;
    }
}

void JSMenuItem::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || (!info[0]->IsObject() && !info[0]->IsFunction())) {
        MenuItemModel::GetInstance()->Create(nullptr);
        return;
    }
    auto vm = info.GetVm();
    // custom menu item
    if (info[0]->IsFunction()) {
        auto jsFunc = JSRef<JSFunc>::Cast(info[0]);
        auto func = jsFunc->GetLocalHandle();
        auto builderFunc = panda::CopyableGlobal(vm, func);
        RefPtr<NG::UINode> customNode;
        {
            ViewStackModel::GetInstance()->NewScope();
            builderFunc->Call(vm, builderFunc.ToLocal(), nullptr, 0);
            customNode = AceType::DynamicCast<NG::UINode>(ViewStackModel::GetInstance()->Finish());
        }
        CHECK_NULL_VOID(customNode);
        MenuItemModel::GetInstance()->Create(customNode);
    } else {
        auto menuItemObj = JSRef<JSObject>::Cast(info[0]);
        MenuItemProperties menuItemProps;
        ParseMenuItemOptionsResource(info, menuItemObj, menuItemProps);
        auto builder = menuItemObj->GetProperty("builder");
        if (!builder.IsEmpty() && builder->IsFunction()) {
            auto jsFunc = JSRef<JSFunc>::Cast(builder);
            auto func = jsFunc->GetLocalHandle();
            auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
            auto subBuildFunc = [vm, func = panda::CopyableGlobal(vm, func), node = targetNode]() {
                panda::LocalScope pandaScope(vm);
                panda::TryCatch trycatch(vm);
                ACE_SCORING_EVENT("MenuItem SubBuilder");
                PipelineContext::SetCallBackNode(node);
                func->Call(vm, func.ToLocal(), nullptr, 0);
            };
            menuItemProps.buildFunc = std::move(subBuildFunc);
        }
        MenuItemModel::GetInstance()->Create(menuItemProps);
    }
    JSMenuItemTheme::ApplyTheme();
}

void JSMenuItem::JSBind(BindingTarget globalObj)
{
    JSClass<JSMenuItem>::Declare("MenuItem");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSMenuItem>::StaticMethod("create", &JSMenuItem::Create, opt);

    JSClass<JSMenuItem>::StaticMethod("selected", &JSMenuItem::IsSelected, opt);
    JSClass<JSMenuItem>::StaticMethod("selectIcon", &JSMenuItem::SelectIcon, opt);
    JSClass<JSMenuItem>::StaticMethod("contentFont", &JSMenuItem::ContentFont, opt);
    JSClass<JSMenuItem>::StaticMethod("contentFontColor", &JSMenuItem::ContentFontColor, opt);
    JSClass<JSMenuItem>::StaticMethod("labelFont", &JSMenuItem::LabelFont, opt);
    JSClass<JSMenuItem>::StaticMethod("labelFontColor", &JSMenuItem::LabelFontColor, opt);
    JSClass<JSMenuItem>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSMenuItem>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSMenuItem>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSMenuItem>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSMenuItem>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSMenuItem>::InheritAndBind<JSContainerBase>(globalObj);
}

void ParseIsSelectedObject(const JSCallbackInfo& info, const JSRef<JSVal>& changeEventVal)
{
    CHECK_NULL_VOID(changeEventVal->IsFunction());
    auto vm = info.GetVm();
    auto jsFunc = JSRef<JSFunc>::Cast(changeEventVal);
    auto func = jsFunc->GetLocalHandle();
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onSelected = [vm, func = panda::CopyableGlobal(vm, func), node = targetNode](bool selected) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ACE_SCORING_EVENT("MenuItem.SelectedChangeEvent");
        PipelineContext::SetCallBackNode(node);
        panda::Local<panda::JSValueRef> params[1] = { panda::BooleanRef::New(vm, selected) };
        func->Call(vm, func.ToLocal(), params, 1);
    };
    MenuItemModel::GetInstance()->SetSelectedChangeEvent(std::move(onSelected));
}

void JSMenuItem::IsSelected(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || info.Length() > 2) {
        return;
    }

    bool isSelected = false;
    JSRef<JSVal> changeEventVal;
    auto selectedVal = info[0];
    if (selectedVal->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(selectedVal);
        selectedVal = obj->GetProperty("value");
        changeEventVal = obj->GetProperty("$value");
    } else if (info.Length() > 1) {
        changeEventVal = info[1];
    }
    if (selectedVal->IsBoolean()) {
        isSelected = selectedVal->ToBoolean();
    }

    MenuItemModel::GetInstance()->SetSelected(isSelected);
    if (changeEventVal->IsFunction()) {
        ParseIsSelectedObject(info, changeEventVal);
    }
}

void JSMenuItem::SelectIcon(const JSCallbackInfo& info)
{
    bool isShow = false;
    std::string icon;
    std::function<void(WeakPtr<NG::FrameNode>)> symbolApply;
    if (info[0]->IsBoolean()) {
        isShow = info[0]->ToBoolean();
    } else if (info[0]->IsString()) {
        icon = info[0]->ToString();
        isShow = true;
    } else if (ParseJsMedia(info[0], icon)) {
        isShow = true;
    } else if (info[0]->IsObject()) {
        isShow = true;
        JSViewAbstract::SetSymbolOptionApply(info, symbolApply, info[0]);
    }
    MenuItemModel::GetInstance()->SetSelectIcon(isShow);
    MenuItemModel::GetInstance()->SetSelectIconSrc(icon);
    MenuItemModel::GetInstance()->SetSelectIconSymbol(std::move(symbolApply));
}

void JSMenuItem::ContentFont(const JSCallbackInfo& info)
{
    CalcDimension fontSize;
    std::string weight;
    if (!info[0]->IsObject()) {
        return;
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
        return;
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
    if (!info[0]->IsObject()) {
        return;
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
        return;
    } else {
        Color textColor;
        if (ParseJsColor(info[0], textColor)) {
            color = textColor;
        }
    }
    MenuItemModel::GetInstance()->SetLabelFontColor(color);
}
} // namespace OHOS::Ace::Framework
