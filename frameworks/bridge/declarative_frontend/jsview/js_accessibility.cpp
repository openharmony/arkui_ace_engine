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

#include "bridge/declarative_frontend/jsview/models/view_abstract_model_impl.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "frameworks/base/log/ace_scoring_log.h"

namespace OHOS::Ace::Framework {
namespace {
const std::unordered_map<AccessibilityRoleType, std::string> accessibilityRoleMap {
    { AccessibilityRoleType::ACTION_SHEET, "actionsheet" }, { AccessibilityRoleType::ALERT_DIALOG, "alertdialog" },
    { AccessibilityRoleType::INDEXER_COMPONENT, "alphabetindexer" },
    { AccessibilityRoleType::BADGE_COMPONENT, "badge" }, { AccessibilityRoleType::BLANK, "blank" },
    { AccessibilityRoleType::BUTTON, "button" }, { AccessibilityRoleType::BACK_BUTTON, "backbutton" },
    { AccessibilityRoleType::SHEET_DRAG_BAR, "sheetdragbar" },
    { AccessibilityRoleType::CALENDAR_PICKER, "calendarpicker" }, { AccessibilityRoleType::CALENDAR, "calendar" },
    { AccessibilityRoleType::CANVAS, "canvas" }, { AccessibilityRoleType::CANVAS_GRADIENT, "canvasgradient" },
    { AccessibilityRoleType::CANVAS_PATTERN, "canvaspattern" }, { AccessibilityRoleType::CHECKBOX, "checkbox" },
    { AccessibilityRoleType::CHECKBOX_GROUP, "checkboxgroup" }, { AccessibilityRoleType::CIRCLE, "circle" },
    { AccessibilityRoleType::COLUMN_SPLIT, "columnsplit" }, { AccessibilityRoleType::COLUMN, "column" },
    { AccessibilityRoleType::CANVAS_RENDERING_CONTEXT_2D, "canvasrenderingcontext2d" },
    { AccessibilityRoleType::CHART, "chart" }, { AccessibilityRoleType::COUNTER, "counter" },
    { AccessibilityRoleType::CONTAINER_MODAL, "containermodal" }, { AccessibilityRoleType::DATA_PANEL, "datapanel" },
    { AccessibilityRoleType::DATE_PICKER, "datepicker" }, { AccessibilityRoleType::DIALOG, "dialog" },
    { AccessibilityRoleType::DIVIDER, "divider" }, { AccessibilityRoleType::DRAG_BAR, "dragbar" },
    { AccessibilityRoleType::EFFECT_COMPONENT, "effectcomponent" }, { AccessibilityRoleType::ELLIPSE, "ellipse" },
    { AccessibilityRoleType::FLEX, "flex" }, { AccessibilityRoleType::FLOW_ITEM, "flowitem" },
    { AccessibilityRoleType::FORM_COMPONENT, "formcomponent" }, { AccessibilityRoleType::FORM_LINK, "formlink" },
    { AccessibilityRoleType::GAUGE, "gauge" }, { AccessibilityRoleType::GRID, "grid" },
    { AccessibilityRoleType::GRID_COL, "gridcol" }, { AccessibilityRoleType::GRID_CONTAINER, "gridcontainer" },
    { AccessibilityRoleType::GRID_ITEM, "griditem" }, { AccessibilityRoleType::GRID_ROW, "grid-row" },
    { AccessibilityRoleType::HYPERLINK, "hyperlink" }, { AccessibilityRoleType::IMAGE, "image" },
    { AccessibilityRoleType::IMAGE_ANIMATOR, "imageanimator" },
    { AccessibilityRoleType::ROLE_IMAGE_BITMAP, "imagebitmap" }, { AccessibilityRoleType::IMAGE_DATA, "imagedata" },
    { AccessibilityRoleType::IMAGE_SPAN, "imagespan" }, { AccessibilityRoleType::LABEL, "label" },
    { AccessibilityRoleType::LINE, "line" }, { AccessibilityRoleType::LIST, "list" },
    { AccessibilityRoleType::LIST_ITEM, "listitem" }, { AccessibilityRoleType::LIST_ITEM_GROUP, "listitemgroup" },
    { AccessibilityRoleType::LOADING_PROGRESS, "loadingprogress" }, { AccessibilityRoleType::MARQUEE, "marquee" },
    { AccessibilityRoleType::MATRIX2D, "matrix2d" }, { AccessibilityRoleType::MENU, "menu" },
    { AccessibilityRoleType::MENU_ITEM, "menuitem" }, { AccessibilityRoleType::MENU_ITEM_GROUP, "menuitemgroup" },
    { AccessibilityRoleType::NAV_DESTINATION, "navdestination" }, { AccessibilityRoleType::NAV_ROUTER, "navrouter" },
    { AccessibilityRoleType::NAVIGATION, "navigation" }, { AccessibilityRoleType::NAVIGATION_BAR, "navigation-bar" },
    { AccessibilityRoleType::NAVIGATION_MENU, "navigation-menu" }, { AccessibilityRoleType::NAVIGATOR, "navigator" },
    { AccessibilityRoleType::OFFSCREEN_CANVAS, "offscreencanvas" },
    { AccessibilityRoleType::OFFSCREEN_CANVAS_RENDERING_CONTEXT2D, "offscreencanvasrenderingcontext2d" },
    { AccessibilityRoleType::OPTION, "option" }, { AccessibilityRoleType::PANEL, "panel" },
    { AccessibilityRoleType::PAPER_PAGE, "paperpage" }, { AccessibilityRoleType::PATH, "path" },
    { AccessibilityRoleType::PATH2D, "path2d" }, { AccessibilityRoleType::PATTERN_LOCK, "patternlock" },
    { AccessibilityRoleType::PICKER, "picker" }, { AccessibilityRoleType::PICKER_VIEW, "picker-view" },
    { AccessibilityRoleType::PLUGIN_COMPONENT, "plugincomponent" }, { AccessibilityRoleType::POLYGON, "polygon" },
    { AccessibilityRoleType::POLYLINE, "polyline" }, { AccessibilityRoleType::POPUP, "popup" },
    { AccessibilityRoleType::PROGRESS, "progress" }, { AccessibilityRoleType::QRCODE, "qrcode" },
    { AccessibilityRoleType::RADIO, "radio" }, { AccessibilityRoleType::RATING, "rating" },
    { AccessibilityRoleType::RECT, "rect" }, { AccessibilityRoleType::REFRESH, "refresh" },
    { AccessibilityRoleType::RELATIVE_CONTAINER, "relativecontainer" },
    { AccessibilityRoleType::REMOTE_WINDOW, "remotewindow" }, { AccessibilityRoleType::RICH_EDITOR, "richeditor" },
    { AccessibilityRoleType::RICH_TEXT, "richtext" }, { AccessibilityRoleType::ROLE_PAGER, "rolepager" },
    { AccessibilityRoleType::ROW, "row" }, { AccessibilityRoleType::ROW_SPLIT, "rowsplit" },
    { AccessibilityRoleType::SCROLL, "scroll" }, { AccessibilityRoleType::SCROLL_BAR, "scrollbar" },
    { AccessibilityRoleType::SEARCH, "search" }, { AccessibilityRoleType::SEARCH_FIELD, "searchfield" },
    { AccessibilityRoleType::SELECT, "select" }, { AccessibilityRoleType::SHAPE, "shape" },
    { AccessibilityRoleType::SIDEBAR_CONTAINER, "sidebarcontainer" }, { AccessibilityRoleType::SLIDER, "slider" },
    { AccessibilityRoleType::SPAN, "span" }, { AccessibilityRoleType::STACK, "stack" },
    { AccessibilityRoleType::STEPPER, "stepper" }, { AccessibilityRoleType::STEPPER_ITEM, "stepperitem" },
    { AccessibilityRoleType::SWIPER, "swiper" }, { AccessibilityRoleType::SWIPER_INDICATOR, "swiperindicator" },
    { AccessibilityRoleType::SWITCH, "switch" }, { AccessibilityRoleType::SYMBOL_GLYPH, "symbolglyph" },
    { AccessibilityRoleType::TAB_CONTENT, "tabcontent" }, { AccessibilityRoleType::TAB_BAR, "tab-bar" },
    { AccessibilityRoleType::TABS, "tabs" }, { AccessibilityRoleType::TEXT, "text" },
    { AccessibilityRoleType::TEXT_CLOCK, "textclock" }, { AccessibilityRoleType::TEXT_ENTRY, "textentry" },
    { AccessibilityRoleType::TEXT_INPUT, "textinput" }, { AccessibilityRoleType::TEXT_PICKER, "textpicker" },
    { AccessibilityRoleType::TEXT_TIMER, "texttimer" }, { AccessibilityRoleType::TEXT_AREA, "textarea" },
    { AccessibilityRoleType::TEXT_FIELD, "textfield" }, { AccessibilityRoleType::TIME_PICKER, "timepicker" },
    { AccessibilityRoleType::TITLE_BAR, "titlebar" }, { AccessibilityRoleType::TOGGLER, "toggler" },
    { AccessibilityRoleType::UI_EXTENSION_COMPONENT, "uiextensioncomponent" },
    { AccessibilityRoleType::VIDEO, "video" }, { AccessibilityRoleType::WATER_FLOW, "waterflow" },
    { AccessibilityRoleType::WEB, "web" }, { AccessibilityRoleType::XCOMPONENT, "xcomponent" },
    { AccessibilityRoleType::ROLE_NONE, "NULL" }
};

const std::vector<AccessibilitySamePageMode> PAGE_MODE_TYPE = { AccessibilitySamePageMode::SEMI_SILENT,
    AccessibilitySamePageMode::FULL_SILENT };
}

void JSViewAbstract::JsAccessibilityGroup(const JSCallbackInfo& info)
{
    bool isGroup = false;
    if (info[0]->IsBoolean()) {
        isGroup = info[0]->ToBoolean();
    }
    ViewAbstractModel::GetInstance()->SetAccessibilityGroup(isGroup);

    if (info.Length() > 1 && info[1]->IsObject()) {
        auto obj = JSRef<JSObject>::Cast(info[1]);

        auto preferAccessibilityTextObj = obj->GetProperty("accessibilityPreferred");
        auto preferAccessibilityText =
            preferAccessibilityTextObj->IsBoolean() ? preferAccessibilityTextObj->ToBoolean() : false;
        ViewAbstractModel::GetInstance()->SetAccessibilityTextPreferred(preferAccessibilityText);
    }
}

void JSViewAbstract::JsAccessibilityText(const JSCallbackInfo& info)
{
    const JSRef<JSVal>& jsValue = info[0];
    std::string text;
    if (!ParseJsString(jsValue, text)) {
        return;
    }
    ViewAbstractModel::GetInstance()->SetAccessibilityText(text);
}

void JSViewAbstract::JsAccessibilityTextHint(const std::string& text)
{
    ViewAbstractModel::GetInstance()->SetAccessibilityTextHint(text);
}

void JSViewAbstract::JsAccessibilityNextFocusId(const JSCallbackInfo& info)
{
    const JSRef<JSVal>& jsValue = info[0];
    std::string nextFocusId;
    if (!ParseJsString(jsValue, nextFocusId)) {
        return;
    }
    ViewAbstractModel::GetInstance()->SetAccessibilityNextFocusId(nextFocusId);
}

void JSViewAbstract::JsAccessibilityDescription(const JSCallbackInfo& info)
{
    const JSRef<JSVal>& jsValue = info[0];
    std::string description;
    if (!ParseJsString(jsValue, description)) {
        return;
    }
    std::pair<bool, std::string> autoEventPair(false, "");
    std::pair<bool, std::string> descriptionPair(false, "");
    ParseAccessibilityDescriptionJson(description, autoEventPair, descriptionPair);
    if (descriptionPair.first) {
        ViewAbstractModel::GetInstance()->SetAccessibilityDescription(descriptionPair.second);
    } else {
        ViewAbstractModel::GetInstance()->SetAccessibilityDescription(description);
    }
    if (autoEventPair.first) {
        ViewAbstractModel::GetInstance()->SetAutoEventParam(autoEventPair.second);
    }
}

void JSViewAbstract::ParseAccessibilityDescriptionJson(const std::string& description,
    std::pair<bool, std::string>& autoEventPair, std::pair<bool, std::string>& descriptionPair)
{
    if (description.empty()) {
        return;
    }
    if (!StartWith(description, "{") || !EndWith(description, "}")) {
        return;
    }
    auto jsonObj = JsonUtil::ParseJsonString(description);
    if (!jsonObj || !jsonObj->IsValid() || !jsonObj->IsObject()) {
        return;
    }
    if (jsonObj->Contains("$autoEventParam")) {
        auto param = jsonObj->GetValue("$autoEventParam");
        if (param) {
            autoEventPair = std::make_pair(true, param->ToString());
        }
    }
    if (jsonObj->Contains("$accessibilityDescription")) {
        descriptionPair = std::make_pair(true, jsonObj->GetString("$accessibilityDescription"));
    } else if (jsonObj->Contains("$autoEventParam")) {
        descriptionPair = std::make_pair(true, "");
    }
}

void JSViewAbstract::JsAccessibilityImportance(const std::string& importance)
{
    ViewAbstractModel::GetInstance()->SetAccessibilityImportance(importance);
}

void JSViewAbstract::JsAccessibilityLevel(const std::string& level)
{
    ViewAbstractModel::GetInstance()->SetAccessibilityImportance(level);
}

void JSViewAbstract::JsAccessibilityVirtualNode(const JSCallbackInfo& info)
{
    // parse builder
    if (!info[0]->IsObject()) {
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
    auto builder = obj->GetProperty("builder");
    if (builder->IsFunction()) {
        auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builder));
        CHECK_NULL_VOID(builderFunc);
        auto buildFunc = [execCtx = info.GetExecutionContext(), func = std::move(builderFunc)]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("AccessibilityVirtualNode");
            func->Execute();
        };
        NG::ViewAbstractModelNG::GetInstance()->SetAccessibilityVirtualNode(std::move(buildFunc));
    }
}

void JSViewAbstract::JsAccessibilitySelected(const JSCallbackInfo& info)
{
    bool selected = false;
    bool resetValue = false;
    JSRef<JSVal> arg = info[0];
    if (arg->IsUndefined()) {
        resetValue = true;
    } else if (arg->IsBoolean()) {
        selected = arg->ToBoolean();
    } else {
        return;
    }

    ViewAbstractModel::GetInstance()->SetAccessibilitySelected(selected, resetValue);
}

void JSViewAbstract::JsAccessibilityChecked(const JSCallbackInfo& info)
{
    bool checked = false;
    bool resetValue = false;
    JSRef<JSVal> arg = info[0];
    if (arg->IsUndefined()) {
        resetValue = true;
    } else if (arg->IsBoolean()) {
        checked = arg->ToBoolean();
    } else {
        return;
    }

    ViewAbstractModel::GetInstance()->SetAccessibilityChecked(checked, resetValue);
}

void JSViewAbstract::JsAccessibilityRole(const JSCallbackInfo& info)
{
    bool resetValue = false;
    std::string role;
    if (info.Length() < 1 || !info[0]->IsNumber()) {
        ViewAbstractModel::GetInstance()->SetAccessibilityRole(role, true);
        return;
    }
    auto index = info[0]->ToNumber<int32_t>();
    AccessibilityRoleType text = static_cast<AccessibilityRoleType>(index);
    auto it = accessibilityRoleMap.find(text);
    if (it != accessibilityRoleMap.end()) {
        role = it->second;
    } else {
        resetValue = true;
    }
    ViewAbstractModel::GetInstance()->SetAccessibilityRole(role, resetValue);
}

void JSViewAbstract::JsOnAccessibilityFocus(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined() || !info[0]->IsFunction()) {
        ViewAbstractModel::GetInstance()->ResetOnAccessibilityFocus();
        return;
    }
    RefPtr<JsFunction> jsFoucusFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onAccessibilityFoucus = [execCtx = info.GetExecutionContext(), func = std::move(jsFoucusFunc),
                                     node = frameNode](bool isFocus) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onAccessibilityFoucus");
        PipelineContext::SetCallBackNode(node);
        JSRef<JSVal> newJSVal = JSRef<JSVal>::Make(ToJSValue(isFocus));
        func->ExecuteJS(1, &newJSVal);
    };
    ViewAbstractModel::GetInstance()->SetOnAccessibilityFocus(std::move(onAccessibilityFoucus));
}

void JSViewAbstract::JsAccessibilityDefaultFocus(const JSCallbackInfo& info)
{
    JSRef<JSVal> arg = info[0];
    if (arg->IsBoolean() && arg->ToBoolean()) {
        ViewAbstractModel::GetInstance()->SetAccessibilityDefaultFocus();
    }
}

void JSViewAbstract::JsAccessibilityUseSamePage(const JSCallbackInfo& info)
{
    JSRef<JSVal> arg = info[0];
    if (arg->IsNumber()) {
        auto pageMode = arg->ToNumber<int32_t>();
        if (pageMode >= 0 && pageMode < static_cast<int32_t>(PAGE_MODE_TYPE.size())) {
            bool isFullSilent = static_cast<bool>(PAGE_MODE_TYPE[pageMode]);
            ViewAbstractModel::GetInstance()->SetAccessibilityUseSamePage(isFullSilent);
        }
    }
}
}