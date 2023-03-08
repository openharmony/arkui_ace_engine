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

#include "frameworks/bridge/declarative_frontend/jsview/js_tab_content.h"

#include <optional>

#include "base/log/ace_trace.h"
#include "bridge/declarative_frontend/jsview/models/tab_content_model_impl.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "core/components_ng/pattern/tabs/tab_content_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<TabContentModel> TabContentModel::instance_ = nullptr;

const std::vector<TextOverflow> TEXT_OVERFLOWS = { TextOverflow::NONE, TextOverflow::CLIP, TextOverflow::ELLIPSIS,
    TextOverflow::MARQUEE };
const std::vector<FontStyle> FONT_STYLES = { FontStyle::NORMAL, FontStyle::ITALIC };
const std::vector<TextHeightAdaptivePolicy> HEIGHT_ADAPTIVE_POLICIES = { TextHeightAdaptivePolicy::MAX_LINES_FIRST,
    TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST, TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST };

TabContentModel* TabContentModel::GetInstance()
{
    if (!instance_) {
#ifdef NG_BUILD
        instance_.reset(new NG::TabContentModelNG());
#else
        if (Container::IsCurrentUseNewPipeline()) {
            instance_.reset(new NG::TabContentModelNG());
        } else {
            instance_.reset(new Framework::TabContentModelImpl());
        }
#endif
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSTabContent::Create(const JSCallbackInfo& info)
{
    if (Container::IsCurrentUsePartialUpdate()) {
        CreateForPartialUpdate(info);
        return;
    }
    TabContentModel::GetInstance()->Create();
}

void JSTabContent::CreateForPartialUpdate(const JSCallbackInfo& info)
{
    if (info.Length() <= 0 && !info[0]->IsFunction()) {
        TabContentModel::GetInstance()->Create();
        return;
    }

    JSRef<JSVal> builderFunctionJS = info[0];
    auto builderFunc = [context = info.GetExecutionContext(), builder = std::move(builderFunctionJS)]() {
        JAVASCRIPT_EXECUTION_SCOPE(context)
        JSRef<JSFunc>::Cast(builder)->Call(JSRef<JSObject>());
    };
    TabContentModel::GetInstance()->Create(std::move(builderFunc));
}

void JSTabContent::SetTabBar(const JSCallbackInfo& info)
{
    if (info.Length() <= 0) {
        return;
    }

    std::string infoStr;
    if (ParseJsString(info[0], infoStr)) {
        TabContentModel::GetInstance()->SetTabBar(infoStr, std::nullopt, nullptr, true);
        return;
    }

    if (!info[0]->IsObject()) {
        return;
    }

    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> builderFuncParam = paramObject->GetProperty("builder");
    if (builderFuncParam->IsFunction()) {
        auto tabBarBuilder = AceType::MakeRefPtr<JsFunction>(info.This(), JSRef<JSFunc>::Cast(builderFuncParam));
        auto tabBarBuilderFunc = [execCtx = info.GetExecutionContext(),
                                     tabBarBuilderFunc = std::move(tabBarBuilder)]() {
            if (tabBarBuilderFunc) {
                ACE_SCOPED_TRACE("JSTabContent::Execute TabBar builder");
                JAVASCRIPT_EXECUTION_SCOPE(execCtx);
                tabBarBuilderFunc->ExecuteJS();
            }
        };
        TabContentModel::GetInstance()->SetTabBarStyle(TabBarStyle::NOSTYLE);
        TabContentModel::GetInstance()->SetTabBar(std::nullopt, std::nullopt, std::move(tabBarBuilderFunc), false);
        return;
    }
    JSRef<JSVal> typeParam = paramObject->GetProperty("type");
    if (typeParam->IsString()) {
        auto type = typeParam->ToString();
        if (type == "SubTabBarStyle") {
            SetSubTabBarStyle(paramObject);
            return;
        }
        if (type == "BottomTabBarStyle") {
            JSRef<JSVal> textParam = paramObject->GetProperty("text");
            auto isTextEmpty = textParam->IsEmpty() || textParam->IsUndefined() || textParam->IsNull();
            std::optional<std::string> textOpt = std::nullopt;
            if (isTextEmpty) {
                LOGE("The text param is empty");
                return;
            }
            std::string text;
            if (ParseJsString(textParam, text)) {
                textOpt = text;
            }

            JSRef<JSVal> iconParam = paramObject->GetProperty("icon");
            auto isIconEmpty = iconParam->IsEmpty() || iconParam->IsUndefined() || iconParam->IsNull();
            std::optional<std::string> iconOpt = std::nullopt;
            if (isIconEmpty) {
                LOGE("The icon param is empty");
                return;
            }
            std::string icon;
            if (ParseJsMedia(iconParam, icon)) {
                iconOpt = icon;
            }
            TabContentModel::GetInstance()->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
            TabContentModel::GetInstance()->SetTabBar(textOpt, iconOpt, nullptr, false);
            return;
        }
    }

    JSRef<JSVal> textParam = paramObject->GetProperty("text");
    auto isTextEmpty = textParam->IsEmpty() || textParam->IsUndefined() || textParam->IsNull();
    std::optional<std::string> textOpt = std::nullopt;
    if (!isTextEmpty) {
        std::string text;
        if (ParseJsString(textParam, text)) {
            textOpt = text;
        }
    }

    JSRef<JSVal> iconParam = paramObject->GetProperty("icon");
    auto isIconEmpty = iconParam->IsEmpty() || iconParam->IsUndefined() || iconParam->IsNull();
    std::optional<std::string> iconOpt = std::nullopt;
    if (!isIconEmpty) {
        std::string icon;
        if (ParseJsMedia(iconParam, icon)) {
            iconOpt = icon;
        }
    }
    TabContentModel::GetInstance()->SetTabBarStyle(TabBarStyle::NOSTYLE);
    TabContentModel::GetInstance()->SetTabBar(textOpt, iconOpt, nullptr, false);
}

void JSTabContent::Pop()
{
    TabContentModel::GetInstance()->Pop();
}

void JSTabContent::SetIndicator(JSRef<JSVal>& info)
{
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info);
    IndicatorStyle indicator;
    if (!info->IsObject() || !ConvertFromJSValue(obj->GetProperty("color"), indicator.color)) {
        RefPtr<TabTheme> tabTheme = GetTheme<TabTheme>();
        if (tabTheme) {
            indicator.color = tabTheme->GetActiveIndicatorColor();
        }
    }
    if (!info->IsObject() || !ConvertFromJSValue(obj->GetProperty("height"), indicator.height)
        || indicator.height.Value() < 0.0f) {
        RefPtr<TabTheme> tabTheme = GetTheme<TabTheme>();
        if (tabTheme) {
            indicator.height = tabTheme->GetActiveIndicatorWidth();
        }
    }
    if (!info->IsObject() || !ConvertFromJSValue(obj->GetProperty("width"), indicator.width)
        || indicator.width.Value() < 0.0f) {
        indicator.width = 0.0_vp;
    }
    if (!info->IsObject() || !ConvertFromJSValue(obj->GetProperty("borderRadius"), indicator.borderRadius)
        || indicator.borderRadius.Value() < 0.0f) {
        indicator.borderRadius = 0.0_vp;
    }
    if (!info->IsObject() || !ConvertFromJSValue(obj->GetProperty("marginTop"), indicator.marginTop)
        || indicator.marginTop.Value() < 0.0f) {
        RefPtr<TabTheme> tabTheme = GetTheme<TabTheme>();
        if (tabTheme) {
            indicator.marginTop = tabTheme->GetSubTabIndicatorGap();
        }
    }
    TabContentModel::GetInstance()->SetIndicator(indicator);
}

void JSTabContent::SetBoard(JSRef<JSVal>& info)
{
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info);
    BoardStyle board;
    if (!info->IsObject() || !ConvertFromJSValue(obj->GetProperty("borderRadius"), board.borderRadius)
        || board.borderRadius.Value() < 0.0f) {
        RefPtr<TabTheme> tabTheme = GetTheme<TabTheme>();
        if (tabTheme) {
            board.borderRadius = tabTheme->GetFocusIndicatorRadius();
        }
    }
    TabContentModel::GetInstance()->SetBoard(board);
}

void JSTabContent::SetSelectedMode(JSRef<JSVal>& info)
{
    std::string selectedMode;
    if (!ConvertFromJSValue(info, selectedMode)) {
        TabContentModel::GetInstance()->SetSelectedMode(SelectedMode::INDICATOR);
    } else {
        TabContentModel::GetInstance()->SetSelectedMode(ConvertStrToSelectedMode(selectedMode));
    }
}

void JSTabContent::GetFontContent(const JSRef<JSVal> font, LabelStyle& labelStyle)
{
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(font);
    JSRef<JSVal> size = obj->GetProperty("size");
    Dimension fontSize;
    if (ParseJsDimensionFp(size, fontSize)) {
        labelStyle.fontSize = fontSize;
    }
    
    JSRef<JSVal> weight = obj->GetProperty("weight");
    if (weight->IsString()) {
        labelStyle.fontWeight = ConvertStrToFontWeight(weight->ToString());
    }

    JSRef<JSVal> family = obj->GetProperty("family");
    std::vector<std::string> fontFamilies;
    if (ParseJsFontFamilies(family, fontFamilies)) {
        labelStyle.fontFamily = fontFamilies;
    }

    JSRef<JSVal> style = obj->GetProperty("style");
    if (style->IsNumber()) {
        int32_t value = style->ToNumber<int32_t>();
        if (value >= 0 && value < static_cast<int32_t>(FONT_STYLES.size())) {
            labelStyle.fontStyle = FONT_STYLES[value];
        }
    }
}

void JSTabContent::SetLabelStyle(JSRef<JSVal>& info)
{
    if (!info->IsObject()) {
        LOGE("info not is Object");
        return;
    }
    
    LabelStyle labelStyle;
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info);
    JSRef<JSVal> overflowValue = obj->GetProperty("overflow");
    if (!overflowValue->IsNull() && overflowValue->IsNumber()) {
        auto overflow = overflowValue->ToNumber<int32_t>();
        if (overflow >= 0 &&
            overflow < static_cast<int32_t>(TEXT_OVERFLOWS.size())) {
            labelStyle.textOverflow = TEXT_OVERFLOWS[overflow];
        }
    }

    JSRef<JSVal> maxLines = obj->GetProperty("maxLines");
    if (!maxLines->IsNull() && maxLines->IsNumber()) {
        labelStyle.maxLines = maxLines->ToNumber<int32_t>();
    }

    JSRef<JSVal> minFontSizeValue = obj->GetProperty("minFontSize");
    Dimension minFontSize;
    if (ParseJsDimensionFp(minFontSizeValue, minFontSize)) {
        labelStyle.minFontSize = minFontSize;
    }

    JSRef<JSVal> maxFontSizeValue = obj->GetProperty("maxFontSize");
    Dimension maxFontSize;
    if (ParseJsDimensionFp(maxFontSizeValue, maxFontSize)) {
        labelStyle.maxFontSize = maxFontSize;
    }

    JSRef<JSVal> heightAdaptivePolicyValue = obj->GetProperty("heightAdaptivePolicy");
    if (!heightAdaptivePolicyValue->IsNull() && heightAdaptivePolicyValue->IsNumber()) {
        auto heightAdaptivePolicy = heightAdaptivePolicyValue->ToNumber<int32_t>();
        if (heightAdaptivePolicy >= 0 && heightAdaptivePolicy < static_cast<int32_t>(HEIGHT_ADAPTIVE_POLICIES.size())) {
            labelStyle.heightAdaptivePolicy = HEIGHT_ADAPTIVE_POLICIES[heightAdaptivePolicy];
        }
    }

    JSRef<JSVal> font = obj->GetProperty("font");
    if (!font->IsNull() && font->IsObject()) {
        TextStyle textStyle;
        GetFontContent(font, labelStyle);
    }

    if (Container::IsCurrentUseNewPipeline()) {
        TabContentModel::GetInstance()->SetLabelStyle(labelStyle);
        return;
    }
}

void JSTabContent::SetSubTabBarStyle(JSRef<JSObject>& paramObject)
{
    JSRef<JSVal> contentParam = paramObject->GetProperty("content");
    auto isContentEmpty = contentParam->IsEmpty() || contentParam->IsUndefined() || contentParam->IsNull();
    if (isContentEmpty) {
        LOGE("The content param is empty");
        return;
    }
    std::optional<std::string> contentOpt = std::nullopt;
    std::string content;
    if (ParseJsString(contentParam, content)) {
        contentOpt = content;
    }
    JSRef<JSVal> indicatorParam = paramObject->GetProperty("indicator");
    if (!indicatorParam->IsUndefined()) {
        SetIndicator(indicatorParam);
    }
    JSRef<JSVal> selectedModeParam = paramObject->GetProperty("selectedMode");
    if (!selectedModeParam->IsUndefined()) {
        SetSelectedMode(selectedModeParam);
    }
    JSRef<JSVal> boardParam = paramObject->GetProperty("board");
    if (!boardParam->IsUndefined()) {
        SetBoard(boardParam);
    }
    JSRef<JSVal> labelStyleParam = paramObject->GetProperty("labelStyle");
    if (!boardParam->IsUndefined()) {
        SetLabelStyle(labelStyleParam);
    }
    TabContentModel::GetInstance()->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    TabContentModel::GetInstance()->SetTabBar(contentOpt, std::nullopt, nullptr, false);
}

void JSTabContent::JSBind(BindingTarget globalObj)
{
    JSClass<JSTabContent>::Declare("TabContent");
    JSClass<JSTabContent>::StaticMethod("create", &JSTabContent::Create);
    JSClass<JSTabContent>::StaticMethod("pop", &JSTabContent::Pop);
    JSClass<JSTabContent>::StaticMethod("tabBar", &JSTabContent::SetTabBar);
    JSClass<JSTabContent>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSTabContent>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSTabContent>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSTabContent>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSTabContent>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSTabContent>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSTabContent>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSTabContent>::StaticMethod("width", &JSTabContent::SetTabContentWidth);
    JSClass<JSTabContent>::StaticMethod("height", &JSTabContent::SetTabContentHeight);
    JSClass<JSTabContent>::StaticMethod("size", &JSTabContent::SetTabContentSize);
    JSClass<JSTabContent>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);
    JSClass<JSTabContent>::Inherit<JSContainerBase>();
    JSClass<JSTabContent>::Bind<>(globalObj);
}

} // namespace OHOS::Ace::Framework
