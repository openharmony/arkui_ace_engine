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

#include "base/log/ace_scoring_log.h"
#include "base/log/ace_trace.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/tab_content_model_impl.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "core/components/tab_bar/tab_theme.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/tabs/tab_content_model_ng.h"
#include "core/components_ng/pattern/tabs/tabs_layout_property.h"
#include "core/components_ng/pattern/tabs/tabs_node.h"
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
    if (info.Length() <= 0 || !info[0]->IsFunction()) {
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
    auto tabBarInfo = info[0];

    std::string infoStr;
    if (ParseJsString(tabBarInfo, infoStr)) {
        TabContentModel::GetInstance()->SetTabBarStyle(TabBarStyle::NOSTYLE);
        TabContentModel::GetInstance()->SetTabBar(infoStr, std::nullopt, std::nullopt, nullptr, true);
        TabContentModel::GetInstance()->SetTabBarWithContent(nullptr);
        return;
    }

    if (!tabBarInfo->IsObject()) {
        TabContentModel::GetInstance()->SetTabBarStyle(TabBarStyle::NOSTYLE);
        TabContentModel::GetInstance()->SetTabBar(std::nullopt, std::nullopt, std::nullopt, nullptr, false);
        TabContentModel::GetInstance()->SetTabBarWithContent(nullptr);
        return;
    }

    auto paramObject = JSRef<JSObject>::Cast(tabBarInfo);
    JSRef<JSVal> contentParam = paramObject->GetProperty("builderNode_");
    if (contentParam->IsObject()) {
        auto builderNodeObject = JSRef<JSObject>::Cast(contentParam);
        JSRef<JSVal> nodeptr = builderNodeObject->GetProperty("nodePtr_");
        if (!nodeptr.IsEmpty()) {
            const auto* vm = nodeptr->GetEcmaVM();
            auto* node = nodeptr->GetLocalHandle()->ToNativePointer(vm)->Value();
            auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
            CHECK_NULL_VOID(frameNode);
            RefPtr<NG::FrameNode> refPtrFrameNode = AceType::Claim(frameNode);
            CHECK_NULL_VOID(refPtrFrameNode);
            TabContentModel::GetInstance()->SetTabBarStyle(TabBarStyle::NOSTYLE);
            TabContentModel::GetInstance()->SetTabBar(std::nullopt, std::nullopt, std::nullopt, nullptr, false);
            TabContentModel::GetInstance()->SetTabBarWithContent(refPtrFrameNode);
            return;
        }
    }
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
        TabContentModel::GetInstance()->SetTabBar(
            std::nullopt, std::nullopt, std::nullopt, std::move(tabBarBuilderFunc), false);
        TabContentModel::GetInstance()->SetTabBarWithContent(nullptr);
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
            SetBottomTabBarStyle(info);
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
    TabContentModel::GetInstance()->SetTabBar(textOpt, iconOpt, std::nullopt, nullptr, false);
    TabContentModel::GetInstance()->SetTabBarWithContent(nullptr);
}

void JSTabContent::Pop()
{
    if (ViewStackModel::GetInstance()->IsPrebuilding()) {
        return ViewStackModel::GetInstance()->PushPrebuildCompCmd("[JSTabContent][pop]", &JSTabContent::Pop);
    }
    TabContentModel::GetInstance()->Pop();
}

void JSTabContent::SetIndicator(const JSRef<JSVal>& info)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    if (info->IsObject()) {
        obj = JSRef<JSObject>::Cast(info);
    }
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
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    if (info->IsObject()) {
        obj = JSRef<JSObject>::Cast(info);
    }
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

void JSTabContent::GetFontContent(const JSRef<JSVal> font, LabelStyle& labelStyle, bool isSubTabStyle)
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
        auto parseResult = ParseFontWeight(weight->ToString());
        if (parseResult.first || !isSubTabStyle) {
            labelStyle.fontWeight = parseResult.second;
        }
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
            GetFontContent(font, labelStyle, isSubTabStyle);
        }

        GetLabelUnselectedContent(obj->GetProperty("unselectedColor"), labelStyle);

        GetLabelSelectedContent(obj->GetProperty("selectedColor"), labelStyle);
    }
    CompleteParameters(labelStyle, isSubTabStyle);
    TabContentModel::GetInstance()->SetLabelStyle(labelStyle);
}

void JSTabContent::SetIconStyle(const JSRef<JSVal>& info)
{
    IconStyle iconStyle;
    if (info->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info);
        Color unselectedColor;
        JSRef<JSVal> unselectedColorValue = obj->GetProperty("unselectedColor");
        if (ConvertFromJSValue(unselectedColorValue, unselectedColor)) {
            iconStyle.unselectedColor = unselectedColor;
        }

        Color selectedColor;
        JSRef<JSVal> selectedColorValue = obj->GetProperty("selectedColor");
        if (ConvertFromJSValue(selectedColorValue, selectedColor)) {
            iconStyle.selectedColor = selectedColor;
        }
    }
    TabContentModel::GetInstance()->SetIconStyle(iconStyle);
}

void JSTabContent::GetLabelUnselectedContent(const JSRef<JSVal> unselectedColorValue, LabelStyle& labelStyle)
{
    Color unselectedColor;
    if (ConvertFromJSValue(unselectedColorValue, unselectedColor)) {
        labelStyle.unselectedColor = unselectedColor;
    }
}

void JSTabContent::GetLabelSelectedContent(const JSRef<JSVal> selectedColorValue, LabelStyle& labelStyle)
{
    Color selectedColor;
    if (ConvertFromJSValue(selectedColorValue, selectedColor)) {
        labelStyle.selectedColor = selectedColor;
    }
}

bool ParseJsLengthMetrics(const JSRef<JSObject>& obj, CalcDimension& result)
{
    if (!obj->HasProperty("value")) {
        return false;
    }
    auto value = obj->GetProperty("value");
    if (!value->IsNumber()) {
        return false;
    }
    auto unit = DimensionUnit::VP;
    auto jsUnit = obj->GetProperty("unit");
    if (jsUnit->IsNumber()) {
        unit = static_cast<DimensionUnit>(jsUnit->ToNumber<int32_t>());
    }
    CalcDimension dimension(value->ToNumber<double>(), unit);
    result = dimension;
    return true;
}

void JSTabContent::SetPadding(const JSRef<JSVal>& info, bool isSubTabStyle)
{
    CalcDimension length;
    NG::PaddingProperty padding;
    bool useLocalizedPadding = false;
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
    if (info->IsObject()) {
        JSRef<JSObject> paddingObj = JSRef<JSObject>::Cast(info);
        CalcDimension start;
        CalcDimension end;
        CalcDimension top;
        CalcDimension bottom;
        if (paddingObj->GetProperty("start")->IsObject()) {
            JSRef<JSObject> startObj = JSRef<JSObject>::Cast(paddingObj->GetProperty("start"));
            if (ParseJsLengthMetrics(startObj, start)) {
                padding.left = NG::CalcLength(start);
                useLocalizedPadding = true;
            }
        }
        if (paddingObj->GetProperty("end")->IsObject()) {
            JSRef<JSObject> endObj = JSRef<JSObject>::Cast(paddingObj->GetProperty("end"));
            if (ParseJsLengthMetrics(endObj, end)) {
                padding.right = NG::CalcLength(end);
                useLocalizedPadding = true;
            }
        }
        if (paddingObj->GetProperty("top")->IsObject()) {
            JSRef<JSObject> topObj = JSRef<JSObject>::Cast(paddingObj->GetProperty("top"));
            if (ParseJsLengthMetrics(topObj, top)) {
                padding.top = NG::CalcLength(top);
                useLocalizedPadding = true;
            }
        }
        if (paddingObj->GetProperty("bottom")->IsObject()) {
            JSRef<JSObject> bottomObj = JSRef<JSObject>::Cast(paddingObj->GetProperty("bottom"));
            if (ParseJsLengthMetrics(bottomObj, bottom)) {
                padding.bottom = NG::CalcLength(bottom);
                useLocalizedPadding = true;
            }
        }
    }
    TabContentModel::GetInstance()->SetPadding(padding);
    TabContentModel::GetInstance()->SetUseLocalizedPadding(useLocalizedPadding);
}

void JSTabContent::SetId(const JSRef<JSVal>& info)
{
    std::string id;
    if (!ParseJsString(info, id)) {
        return;
    }
    TabContentModel::GetInstance()->SetId(id);
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
        } else if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            labelStyle.fontSize = tabTheme->GetBottomTabTextSize();
        }
    }
    if (!labelStyle.fontWeight.has_value() && !isSubTabStyle) {
        labelStyle.fontWeight = FontWeight::MEDIUM;
    }
    if (!labelStyle.fontStyle.has_value()) {
        labelStyle.fontStyle = FontStyle::NORMAL;
    }
    if (!labelStyle.heightAdaptivePolicy.has_value()) {
        labelStyle.heightAdaptivePolicy = TextHeightAdaptivePolicy::MAX_LINES_FIRST;
    }
    if (!labelStyle.textOverflow.has_value()) {
        labelStyle.textOverflow = TextOverflow::ELLIPSIS;
    }
}

void SetBuilderNode(const JSRef<JSObject>& paramObject)
{
    JSRef<JSVal> contentParam = paramObject->GetProperty("content");
    if (!contentParam->IsObject()) {
        return;
    }
    auto contentObject = JSRef<JSObject>::Cast(contentParam);
    JSRef<JSVal> builderNodeParam = contentObject->GetProperty("builderNode_");
    if (!builderNodeParam->IsObject()) {
        return;
    }
    auto builderNodeObject = JSRef<JSObject>::Cast(builderNodeParam);
    JSRef<JSVal> nodeptr = builderNodeObject->GetProperty("nodePtr_");
    if (nodeptr.IsEmpty()) {
        return;
    }
    const auto* vm = nodeptr->GetEcmaVM();
    CHECK_NULL_VOID(nodeptr->GetLocalHandle()->IsNativePointer(vm));
    auto* node = nodeptr->GetLocalHandle()->ToNativePointer(vm)->Value();
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<NG::FrameNode> refPtrFrameNode = AceType::Claim(frameNode);
    TabContentModel::GetInstance()->SetCustomStyleNode(refPtrFrameNode);
}

void JSTabContent::SetSubTabBarStyle(const JSRef<JSObject>& paramObject)
{
    JSRef<JSVal> contentParam = paramObject->GetProperty("content");
    SetBuilderNode(paramObject);

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

    JSRef<JSVal> idParam = paramObject->GetProperty("id");
    SetId(idParam);

    TabContentModel::GetInstance()->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    TabContentModel::GetInstance()->SetTabBar(contentOpt, std::nullopt, std::nullopt, nullptr, false);
    TabContentModel::GetInstance()->SetTabBarWithContent(nullptr);
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

void JSTabContent::SetBottomTabBarStyle(const JSCallbackInfo& info)
{
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> textParam = paramObject->GetProperty("text");
    std::optional<std::string> textOpt = std::nullopt;
    std::string text;
    if (ParseJsString(textParam, text)) {
        textOpt = text;
    }

    JSRef<JSVal> iconParam = paramObject->GetProperty("icon");
    std::optional<std::string> iconOpt = std::nullopt;
    std::string icon;
    std::optional<TabBarSymbol> tabBarSymbol = std::nullopt;
    if (ParseJsMedia(iconParam, icon)) {
        iconOpt = icon;
    } else if (iconParam->IsObject()) {
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(iconParam);
        JSRef<JSVal> normalModifier = jsObj->GetProperty("normal");
        JSRef<JSVal> selectedModifier = jsObj->GetProperty("selected");
        if (normalModifier->IsObject()) {
            TabBarSymbol symbolApply;
            JSViewAbstract::SetTabBarSymbolOptionApply(info, symbolApply, normalModifier, selectedModifier);
            if (selectedModifier->IsObject()) {
                symbolApply.selectedFlag = true;
            }
            tabBarSymbol = symbolApply;
        }
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

    SetIconStyle(paramObject->GetProperty("iconStyle"));

    JSRef<JSVal> idParam = paramObject->GetProperty("id");
    SetId(idParam);

    TabContentModel::GetInstance()->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    TabContentModel::GetInstance()->SetTabBar(textOpt, iconOpt, tabBarSymbol, nullptr, false);
    TabContentModel::GetInstance()->SetTabBarWithContent(nullptr);
}

void JSTabContent::SetOnWillShow(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsFunction()) {
        return;
    }
    auto willShowHandler = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onWillShow = [executionContext = info.GetExecutionContext(), func = std::move(willShowHandler)]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext);
        ACE_SCORING_EVENT("TabContent.onWillShow");
        func->Execute();
    };
    TabContentModel::GetInstance()->SetOnWillShow(std::move(onWillShow));
}

void JSTabContent::SetOnWillHide(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsFunction()) {
        return;
    }
    auto willHideHandler = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onWillHide = [executionContext = info.GetExecutionContext(), func = std::move(willHideHandler)]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext);
        ACE_SCORING_EVENT("TabContent.onWillHide");
        func->Execute();
    };
    TabContentModel::GetInstance()->SetOnWillHide(std::move(onWillHide));
}

void JSTabContent::JSBind(BindingTarget globalObj)
{
    JSClass<JSTabContent>::Declare("TabContent");
    JSClass<JSTabContent>::StaticMethod("create", &JSTabContent::Create);
    JSClass<JSTabContent>::StaticMethod("pop", &JSTabContent::Pop);
    JSClass<JSTabContent>::StaticMethod("tabBar", &JSTabContent::SetTabBar);
    JSClass<JSTabContent>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSTabContent>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSTabContent>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSTabContent>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSTabContent>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSTabContent>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSTabContent>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSTabContent>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSTabContent>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSTabContent>::StaticMethod("width", &JSTabContent::SetTabContentWidth);
    JSClass<JSTabContent>::StaticMethod("height", &JSTabContent::SetTabContentHeight);
    JSClass<JSTabContent>::StaticMethod("size", &JSTabContent::SetTabContentSize);
    JSClass<JSTabContent>::StaticMethod("onWillShow", &JSTabContent::SetOnWillShow);
    JSClass<JSTabContent>::StaticMethod("onWillHide", &JSTabContent::SetOnWillHide);
    JSClass<JSTabContent>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);
    JSClass<JSTabContent>::InheritAndBind<JSContainerBase>(globalObj);
}

} // namespace OHOS::Ace::Framework
