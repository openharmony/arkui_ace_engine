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

#include "frameworks/bridge/declarative_frontend/jsview/js_navigation_utils.h"

#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {

namespace {
// navigation title bar options
constexpr char BACKGROUND_COLOR_PROPERTY[] = "backgroundColor";
constexpr char BACKGROUND_BLUR_STYLE_PROPERTY[] = "backgroundBlurStyle";
constexpr char BAR_STYLE_PROPERTY[] = "barStyle";
constexpr char PADDING_START_PROPERTY[] = "paddingStart";
constexpr char PADDING_END_PROPERTY[] = "paddingEnd";
constexpr char MAIN_TITLE_MODIFIER[] = "mainTitleModifier";
constexpr char SUB_TITLE_MODIFIER[] = "subTitleModifier";

void ParseSymbolAndIcon(const JSCallbackInfo& info, NG::BarItem& toolBarItem,
    const JSRef<JSObject>& itemObject)
{
    std::string icon;
    std::string activeIcon;
    auto itemSymbolIconObject = itemObject->GetProperty("symbolIcon");
    if (itemSymbolIconObject->IsObject()) {
        std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol = nullptr;
        JSViewAbstract::SetSymbolOptionApply(info, iconSymbol, itemSymbolIconObject);
        toolBarItem.iconSymbol = iconSymbol;
    }
    auto itemIconObject = itemObject->GetProperty("icon");
    if (JSViewAbstract::ParseJsMedia(itemIconObject, icon)) {
        toolBarItem.icon = icon;
    }

    auto itemActiveSymbolIconObject = itemObject->GetProperty("activeSymbolIcon");
    if (itemActiveSymbolIconObject->IsObject()) {
        std::function<void(WeakPtr<NG::FrameNode>)> activeSymbol = nullptr;
        JSViewAbstract::SetSymbolOptionApply(info, activeSymbol, itemActiveSymbolIconObject);
        toolBarItem.activeIconSymbol = activeSymbol;
    }
    auto itemActiveIconObject = itemObject->GetProperty("activeIcon");
    if (JSViewAbstract::ParseJsMedia(itemActiveIconObject, activeIcon)) {
        toolBarItem.activeIcon = activeIcon;
    }
}

void ParseBackgroundOptions(const JSRef<JSVal>& obj, NG::NavigationBackgroundOptions& options)
{
    options.color.reset();
    options.blurStyle.reset();
    if (!obj->IsObject()) {
        return;
    }
    auto optObj = JSRef<JSObject>::Cast(obj);
    auto colorProperty = optObj->GetProperty(BACKGROUND_COLOR_PROPERTY);
    Color color;
    if (JSViewAbstract::ParseJsColor(colorProperty, color)) {
        options.color = color;
    }
    auto blurProperty = optObj->GetProperty(BACKGROUND_BLUR_STYLE_PROPERTY);
    if (blurProperty->IsNumber()) {
        auto blurStyle = blurProperty->ToNumber<int32_t>();
        if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
            blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
            options.blurStyle = static_cast<BlurStyle>(blurStyle);
        }
    }
}

void ParseBarOptions(const JSRef<JSVal>& obj, NG::NavigationBarOptions& options)
{
    options.paddingStart.reset();
    options.paddingEnd.reset();
    options.barStyle.reset();
    if (!obj->IsObject()) {
        return;
    }
    auto optObj = JSRef<JSObject>::Cast(obj);
    auto barStyleProperty = optObj->GetProperty(BAR_STYLE_PROPERTY);
    if (barStyleProperty->IsNumber()) {
        auto barStyle = barStyleProperty->ToNumber<int32_t>();
        if (barStyle >= static_cast<int32_t>(NG::BarStyle::STANDARD) &&
            barStyle <= static_cast<int32_t>(NG::BarStyle::STACK)) {
            options.barStyle = static_cast<NG::BarStyle>(barStyle);
        } else {
            options.barStyle = NG::BarStyle::STANDARD;
        }
    }
    CalcDimension paddingStart;
    if (JSViewAbstract::ParseLengthMetricsToDimension(optObj->GetProperty(PADDING_START_PROPERTY), paddingStart)) {
        options.paddingStart = paddingStart;
    }
    CalcDimension paddingEnd;
    if (JSViewAbstract::ParseLengthMetricsToDimension(optObj->GetProperty(PADDING_END_PROPERTY), paddingEnd)) {
        options.paddingEnd = paddingEnd;
    }
}

void ParseTextOptions(const JSCallbackInfo& info, const JSRef<JSVal>& obj, NG::NavigationTextOptions& options)
{
    options.Reset();
    if (!obj->IsObject()) {
        return;
    }
    auto optObj = JSRef<JSObject>::Cast(obj);
    auto mainTitleModifierProperty = optObj->GetProperty(MAIN_TITLE_MODIFIER);
    auto subTitleModifierProperty = optObj->GetProperty(SUB_TITLE_MODIFIER);
    JSViewAbstract::SetTextStyleApply(info, options.mainTitleApplyFunc, mainTitleModifierProperty);
    JSViewAbstract::SetTextStyleApply(info, options.subTitleApplyFunc, subTitleModifierProperty);
}

void ParseToolBarItemAction(const WeakPtr<NG::FrameNode>& targetNode,
    const JSCallbackInfo& info, const JSRef<JSObject>& itemObject, NG::BarItem& toolBarItem)
{
    auto itemActionValue = itemObject->GetProperty("action");
    if (!itemActionValue->IsFunction()) {
        return;
    }

    RefPtr<JsFunction> onClickFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(itemActionValue));
    auto onItemClick = [execCtx = info.GetExecutionContext(), func = std::move(onClickFunc),
                            node = targetNode]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        if (func) {
            PipelineContext::SetCallBackNode(node);
            func->ExecuteJS();
        }
    };
    toolBarItem.action = onItemClick;
}
}

void JSNavigationUtils::ParseToolbarItemsConfiguration(const WeakPtr<NG::FrameNode>& targetNode,
    const JSCallbackInfo& info, const JSRef<JSArray>& jsArray, std::vector<NG::BarItem>& items)
{
    auto length = jsArray->Length();
    for (size_t i = 0; i < length; i++) {
        auto item = jsArray->GetValueAt(i);
        if (!item->IsObject()) {
            continue;
        }

        NG::BarItem toolBarItem;
        std::string text;
        auto itemObject = JSRef<JSObject>::Cast(item);
        auto itemValueObject = itemObject->GetProperty("value");
        if (JSViewAbstract::ParseJsString(itemValueObject, text)) {
            toolBarItem.text = text;
        }

        ParseToolBarItemAction(targetNode, info, itemObject, toolBarItem);

        auto itemStatusValue = itemObject->GetProperty("status");
        if (itemStatusValue->IsNumber()) {
            toolBarItem.status = static_cast<NG::NavToolbarItemStatus>(itemStatusValue->ToNumber<int32_t>());
        }
        ParseSymbolAndIcon(info, toolBarItem, itemObject);
        items.push_back(toolBarItem);
    }
}

void JSNavigationUtils::ParseTitleBarOptions(
    const JSCallbackInfo& info, bool needSetDefaultValue, NG::NavigationTitlebarOptions& options)
{
    if (needSetDefaultValue) {
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            auto pipelineContext = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(pipelineContext);
            auto theme = pipelineContext->GetTheme<NavigationBarTheme>();
            CHECK_NULL_VOID(theme);
            auto blurStyle = static_cast<BlurStyle>(theme->GetTitlebarBackgroundBlurStyle());
            if (blurStyle != BlurStyle::NO_MATERIAL) {
                options.bgOptions.blurStyle = blurStyle;
                options.bgOptions.color = Color::TRANSPARENT;
            }
        }
    }

    if (info.Length() > 1) {
        ParseBackgroundOptions(info[1], options.bgOptions);
        ParseBarOptions(info[1], options.brOptions);
        ParseTextOptions(info, info[1], options.textOptions);
    }
}

void JSNavigationUtils::ParseToolbarBgOptions(const JSCallbackInfo& info, NG::NavigationToolbarOptions& options)
{
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto theme = pipelineContext->GetTheme<NavigationBarTheme>();
        CHECK_NULL_VOID(theme);
        auto blurStyle = static_cast<BlurStyle>(theme->GetToolbarBackgroundBlurStyle());
        if (blurStyle != BlurStyle::NO_MATERIAL) {
            options.bgOptions.blurStyle = blurStyle;
            options.bgOptions.color = Color::TRANSPARENT;
        }
    }
    if (info.Length() > 1) {
        ParseBackgroundOptions(info[1], options.bgOptions);
    }
}

void JSNavigationUtils::ParseBarItems(const WeakPtr<NG::FrameNode>& targetNode,
    const JSCallbackInfo& info, const JSRef<JSArray>& jsArray, std::vector<NG::BarItem>& items)
{
    auto length = jsArray->Length();
    for (size_t i = 0; i < length; i++) {
        auto item = jsArray->GetValueAt(i);
        if (!item->IsObject()) {
            continue;
        }
        auto itemObject = JSRef<JSObject>::Cast(item);
        NG::BarItem toolBarItem;
        std::string value;
        auto itemValueObject = itemObject->GetProperty("value");
        if (JSViewAbstract::ParseJsString(itemValueObject, value)) {
            toolBarItem.text = value;
        }

        auto itemSymbolIconObject = itemObject->GetProperty("symbolIcon");
        if (itemSymbolIconObject->IsObject()) {
            std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol = nullptr;
            JSViewAbstract::SetSymbolOptionApply(info, iconSymbol, itemSymbolIconObject);
            toolBarItem.iconSymbol = iconSymbol;
        }
        std::string icon;
        auto itemIconObject = itemObject->GetProperty("icon");
        if (JSViewAbstract::ParseJsMedia(itemIconObject, icon)) {
            toolBarItem.icon = icon;
        }

        auto itemEnabledObject = itemObject->GetProperty("isEnabled");
        if (itemEnabledObject->IsBoolean()) {
            toolBarItem.isEnabled = itemEnabledObject->ToBoolean();
        }

        ParseToolBarItemAction(targetNode, info, itemObject, toolBarItem);
        items.push_back(toolBarItem);
    }
}

} // namespace OHOS::Ace::Framework