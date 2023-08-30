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
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/tab_content_model_impl.h"
#include "core/components/tab_bar/tab_theme.h"
#include "core/components_ng/pattern/tabs/tab_content_model_ng.h"
#include "core/components_ng/property/measure_property.h"

namespace OHOS::Ace {

std::unique_ptr<TabContentModel> TabContentModel::instance_ = nullptr;
std::mutex TabContentModel::mutex_;

const std::vector<TextOverflow> TEXT_OVERFLOWS = { TextOverflow::NONE, TextOverflow::CLIP, TextOverflow::ELLIPSIS,
    TextOverflow::MARQUEE };
const std::vector<FontStyle> FONT_STYLES = { FontStyle::NORMAL, FontStyle::ITALIC };
const std::vector<TextHeightAdaptivePolicy> HEIGHT_ADAPTIVE_POLICIES = { TextHeightAdaptivePolicy::MAX_LINES_FIRST,
    TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST, TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST };

TabContentModel* TabContentModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
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
        TabContentModel::GetInstance()->SetTabBarStyle(TabBarStyle::NOSTYLE);
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
            SetBottomTabBarStyle(paramObject);
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

void JSTabContent::SetIndicator(const JSRef<JSVal>& info)
{
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info);
    IndicatorStyle indicator;
    CalcDimension indicatorHeight;
    CalcDimension indicatorWidth;
    CalcDimension indicatorBorderRadius;
    CalcDimension indicatorMarginTop;
    if (!info->IsObject() || !ConvertFromJSValue(obj->GetProperty("color"), indicator.color)) {
        RefPtr<TabTheme> tabTheme = GetTheme<TabTheme>();
        if (tabTheme) {
            indicator.color = tabTheme->GetActiveIndicatorColor();
        }
    }
    if (!info->IsObject() || !ParseJsDimensionVp(obj->GetProperty("height"), indicatorHeight) ||
        indicatorHeight.Value() < 0.0f || indicatorHeight.Unit() == DimensionUnit::PERCENT) {
        RefPtr<TabTheme> tabTheme = GetTheme<TabTheme>();
        if (tabTheme) {
            indicator.height = tabTheme->GetActiveIndicatorWidth();
        }
    } else {
        indicator.height = indicatorHeight;
    }
    if (!info->IsObject() || !ParseJsDimensionVp(obj->GetProperty("width"), indicatorWidth) ||
        indicatorWidth.Value() < 0.0f || indicatorWidth.Unit() == DimensionUnit::PERCENT) {
        indicator.width = 0.0_vp;
    } else {
        indicator.width = indicatorWidth;
    }
    if (!info->IsObject() || !ParseJsDimensionVp(obj->GetProperty("borderRadius"), indicatorBorderRadius) ||
        indicatorBorderRadius.Value() < 0.0f || indicatorBorderRadius.Unit() == DimensionUnit::PERCENT) {
        indicator.borderRadius = 0.0_vp;
    } else {
        indicator.borderRadius = indicatorBorderRadius;
    }
    if (!info->IsObject() || !ParseJsDimensionVp(obj->GetProperty("marginTop"), indicatorMarginTop) ||
        indicatorMarginTop.Value() < 0.0f || indicatorMarginTop.Unit() == DimensionUnit::PERCENT) {
        RefPtr<TabTheme> tabTheme = GetTheme<TabTheme>();
        if (tabTheme) {
            indicator.marginTop = tabTheme->GetSubTabIndicatorGap();
        }
    } else {
        indicator.marginTop = indicatorMarginTop;
    }
    TabContentModel::GetInstance()->SetIndicator(indicator);
}

void JSTabContent::SetBoard(const JSRef<JSVal>& info)
{
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info);
    BoardStyle board;
    CalcDimension borderRadius;
    if (!info->IsObject() || !ParseJsDimensionVp(obj->GetProperty("borderRadius"), borderRadius) ||
        borderRadius.Value() < 0.0f || borderRadius.Unit() == DimensionUnit::PERCENT) {
        RefPtr<TabTheme> tabTheme = GetTheme<TabTheme>();
        if (tabTheme) {
            board.borderRadius = tabTheme->GetFocusIndicatorRadius();
        }
    } else {
        board.borderRadius = borderRadius;
    }
    TabContentModel::GetInstance()->SetBoard(board);
}

void JSTabContent::SetSelectedMode(const JSRef<JSVal>& info)
{
    int32_t selectedMode;
    if (!ConvertFromJSValue(info, selectedMode)) {
        TabContentModel::GetInstance()->SetSelectedMode(SelectedMode::INDICATOR);
    } else {
        TabContentModel::GetInstance()->SetSelectedMode(static_cast<SelectedMode>(selectedMode));
    }
}

void JSTabContent::GetFontContent(const JSRef<JSVal> font, LabelStyle& labelStyle)
{
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(font);
    JSRef<JSVal> size = obj->GetProperty("size");
    CalcDimension fontSize;
    if (ParseJsDimensionFp(size, fontSize) && NonNegative(fontSize.Value()) &&
        fontSize.Unit() != DimensionUnit::PERCENT) {
        labelStyle.fontSize = fontSize;
    }

    JSRef<JSVal> weight = obj->GetProperty("weight");
    if (weight->IsString() || weight->IsNumber()) {
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

void JSTabContent::SetLabelStyle(const JSRef<JSVal>& info, bool isSubTabStyle)
{
    LabelStyle labelStyle;
    if (!info->IsObject()) {
        LOGW("info not is Object");
    } else {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info);
        JSRef<JSVal> overflowValue = obj->GetProperty("overflow");
        if (!overflowValue->IsNull() && overflowValue->IsNumber()) {
            auto overflow = overflowValue->ToNumber<int32_t>();
            if (overflow >= 0 && overflow < static_cast<int32_t>(TEXT_OVERFLOWS.size())) {
                labelStyle.textOverflow = TEXT_OVERFLOWS[overflow];
            }
        }

        JSRef<JSVal> maxLines = obj->GetProperty("maxLines");
        if (!maxLines->IsNull() && maxLines->IsNumber() && maxLines->ToNumber<int32_t>() > 0) {
            labelStyle.maxLines = maxLines->ToNumber<int32_t>();
        }

        JSRef<JSVal> minFontSizeValue = obj->GetProperty("minFontSize");
        CalcDimension minFontSize;
        if (ParseJsDimensionFp(minFontSizeValue, minFontSize) && NonNegative(minFontSize.Value()) &&
            minFontSize.Unit() != DimensionUnit::PERCENT) {
            labelStyle.minFontSize = minFontSize;
        }

        JSRef<JSVal> maxFontSizeValue = obj->GetProperty("maxFontSize");
        CalcDimension maxFontSize;
        if (ParseJsDimensionFp(maxFontSizeValue, maxFontSize) && NonNegative(maxFontSize.Value()) &&
            maxFontSize.Unit() != DimensionUnit::PERCENT) {
            labelStyle.maxFontSize = maxFontSize;
        }

        JSRef<JSVal> heightAdaptivePolicyValue = obj->GetProperty("heightAdaptivePolicy");
        if (!heightAdaptivePolicyValue->IsNull() && heightAdaptivePolicyValue->IsNumber()) {
            auto heightAdaptivePolicy = heightAdaptivePolicyValue->ToNumber<int32_t>();
            if (heightAdaptivePolicy >= 0 &&
                heightAdaptivePolicy < static_cast<int32_t>(HEIGHT_ADAPTIVE_POLICIES.size())) {
                labelStyle.heightAdaptivePolicy = HEIGHT_ADAPTIVE_POLICIES[heightAdaptivePolicy];
            }
        }

        JSRef<JSVal> font = obj->GetProperty("font");
        if (!font->IsNull() && font->IsObject()) {
            GetFontContent(font, labelStyle);
        }
    }
    CompleteParameters(labelStyle, isSubTabStyle);
    TabContentModel::GetInstance()->SetLabelStyle(labelStyle);
}

void JSTabContent::SetPadding(const JSRef<JSVal>& info, bool isSubTabStyle)
{
    CalcDimension length;
    NG::PaddingProperty padding;
    if (ParseJsDimensionVp(info, length) && NonNegative(length.Value()) && length.Unit() != DimensionUnit::PERCENT) {
        padding.left = NG::CalcLength(length);
        padding.right = NG::CalcLength(length);
        padding.top = NG::CalcLength(length);
        padding.bottom = NG::CalcLength(length);
        TabContentModel::GetInstance()->SetPadding(padding);
        return;
    }

    RefPtr<TabTheme> tabTheme = GetTheme<TabTheme>();
    if (tabTheme) {
        if (isSubTabStyle) {
            padding.top = NG::CalcLength(tabTheme->GetSubTabTopPadding());
            padding.bottom = NG::CalcLength(tabTheme->GetSubTabBottomPadding());
            padding.left = NG::CalcLength(tabTheme->GetSubTabHorizontalPadding());
            padding.right = NG::CalcLength(tabTheme->GetSubTabHorizontalPadding());
        } else {
            padding.top = NG::CalcLength(0.0_vp);
            padding.bottom = NG::CalcLength(0.0_vp);
            padding.left = NG::CalcLength(tabTheme->GetBottomTabHorizontalPadding());
            padding.right = NG::CalcLength(tabTheme->GetBottomTabHorizontalPadding());
        }
    }
    if (info->IsObject()) {
        JSRef<JSObject> paddingObj = JSRef<JSObject>::Cast(info);
        CalcDimension left;
        if (ParseJsDimensionVp(paddingObj->GetProperty("left"), left) && NonNegative(left.Value()) &&
            left.Unit() != DimensionUnit::PERCENT) {
            padding.left = NG::CalcLength(left);
        }
        CalcDimension right;
        if (ParseJsDimensionVp(paddingObj->GetProperty("right"), right) && NonNegative(right.Value()) &&
            right.Unit() != DimensionUnit::PERCENT) {
            padding.right = NG::CalcLength(right);
        }
        CalcDimension top;
        if (ParseJsDimensionVp(paddingObj->GetProperty("top"), top) && NonNegative(top.Value()) &&
            top.Unit() != DimensionUnit::PERCENT) {
            padding.top = NG::CalcLength(top);
        }
        CalcDimension bottom;
        if (ParseJsDimensionVp(paddingObj->GetProperty("bottom"), bottom) && NonNegative(bottom.Value()) &&
            bottom.Unit() != DimensionUnit::PERCENT) {
            padding.bottom = NG::CalcLength(bottom);
        }
    }
    TabContentModel::GetInstance()->SetPadding(padding);
}

void JSTabContent::CompleteParameters(LabelStyle& labelStyle, bool isSubTabStyle)
{
    auto tabTheme = GetTheme<TabTheme>();
    if (!tabTheme) {
        return;
    }
    if (!labelStyle.maxLines.has_value()) {
        labelStyle.maxLines = 1;
    }
    if (!labelStyle.minFontSize.has_value()) {
        labelStyle.minFontSize = 0.0_vp;
    }
    if (!labelStyle.maxFontSize.has_value()) {
        labelStyle.maxFontSize = 0.0_vp;
    }
    if (!labelStyle.fontSize.has_value()) {
        if (isSubTabStyle) {
            labelStyle.fontSize = tabTheme->GetSubTabTextDefaultFontSize();
        } else {
            labelStyle.fontSize = tabTheme->GetBottomTabTextSize();
        }
    }
    if (!labelStyle.fontWeight.has_value()) {
        if (isSubTabStyle) {
            labelStyle.fontWeight = FontWeight::NORMAL;
        } else {
            labelStyle.fontWeight = FontWeight::MEDIUM;
        }
    }
    if (!labelStyle.fontStyle.has_value()) {
        labelStyle.fontStyle = FontStyle::NORMAL;
    }
    if (!labelStyle.fontFamily.has_value()) {
        labelStyle.fontFamily = { "HarmonyOS Sans" };
    }
    if (!labelStyle.heightAdaptivePolicy.has_value()) {
        labelStyle.heightAdaptivePolicy = TextHeightAdaptivePolicy::MAX_LINES_FIRST;
    }
    if (!labelStyle.textOverflow.has_value()) {
        labelStyle.textOverflow = TextOverflow::ELLIPSIS;
    }
}

void JSTabContent::SetSubTabBarStyle(const JSRef<JSObject>& paramObject)
{
    JSRef<JSVal> contentParam = paramObject->GetProperty("content");
    auto isContentEmpty = contentParam->IsEmpty() || contentParam->IsUndefined() || contentParam->IsNull();
    if (isContentEmpty) {
        LOGW("The content param is empty");
    }
    std::optional<std::string> contentOpt;
    std::string content;
    if (ParseJsString(contentParam, content)) {
        contentOpt = content;
    }

    JSRef<JSVal> indicatorParam = paramObject->GetProperty("indicator");
    SetIndicator(indicatorParam);

    JSRef<JSVal> selectedModeParam = paramObject->GetProperty("selectedMode");
    SetSelectedMode(selectedModeParam);

    JSRef<JSVal> boardParam = paramObject->GetProperty("board");
    SetBoard(boardParam);

    JSRef<JSVal> labelStyleParam = paramObject->GetProperty("labelStyle");
    SetLabelStyle(labelStyleParam, true);

    JSRef<JSVal> paddingParam = paramObject->GetProperty("padding");
    SetPadding(paddingParam, true);

    TabContentModel::GetInstance()->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    TabContentModel::GetInstance()->SetTabBar(contentOpt, std::nullopt, nullptr, false);
}

void JSTabContent::SetLayoutMode(const JSRef<JSVal>& info)
{
    int32_t layoutMode;
    if (!ConvertFromJSValue(info, layoutMode)) {
        TabContentModel::GetInstance()->SetLayoutMode(LayoutMode::VERTICAL);
    } else {
        TabContentModel::GetInstance()->SetLayoutMode(static_cast<LayoutMode>(layoutMode));
    }
}

void JSTabContent::SetVerticalAlign(const JSRef<JSVal>& info)
{
    auto align = FlexAlign::CENTER;
    if (info->IsNumber()) {
        auto value = info->ToNumber<int32_t>();
        if (value >= static_cast<int32_t>(FlexAlign::FLEX_START) &&
            value <= static_cast<int32_t>(FlexAlign::FLEX_END)) {
            align = static_cast<FlexAlign>(value);
        }
    }
    TabContentModel::GetInstance()->SetVerticalAlign(align);
}

void JSTabContent::SetSymmetricExtensible(const JSRef<JSVal>& info)
{
    bool isExtensible = false;
    ParseJsBool(info, isExtensible);
    TabContentModel::GetInstance()->SetSymmetricExtensible(isExtensible);
}

void JSTabContent::SetBottomTabBarStyle(const JSRef<JSObject>& paramObject)
{
    JSRef<JSVal> textParam = paramObject->GetProperty("text");
    std::optional<std::string> textOpt = std::nullopt;
    std::string text;
    if (ParseJsString(textParam, text)) {
        textOpt = text;
    }

    JSRef<JSVal> iconParam = paramObject->GetProperty("icon");
    std::optional<std::string> iconOpt = std::nullopt;
    std::string icon;
    if (ParseJsMedia(iconParam, icon)) {
        iconOpt = icon;
    }

    JSRef<JSVal> paddingParam = paramObject->GetProperty("padding");
    SetPadding(paddingParam, false);

    JSRef<JSVal> layoutParam = paramObject->GetProperty("layoutMode");
    SetLayoutMode(layoutParam);

    JSRef<JSVal> verticalAlignParam = paramObject->GetProperty("verticalAlign");
    SetVerticalAlign(verticalAlignParam);

    JSRef<JSVal> extensibleParam = paramObject->GetProperty("symmetricExtensible");
    SetSymmetricExtensible(extensibleParam);

    JSRef<JSVal> labelStyleParam = paramObject->GetProperty("labelStyle");
    SetLabelStyle(labelStyleParam, false);

    TabContentModel::GetInstance()->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    TabContentModel::GetInstance()->SetTabBar(textOpt, iconOpt, nullptr, false);
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
    JSClass<JSTabContent>::InheritAndBind<JSContainerBase>(globalObj);
}

} // namespace OHOS::Ace::Framework
