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

#include "frameworks/bridge/declarative_frontend/jsview/js_tabs.h"

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/jsview/js_tabs_controller.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/tabs_model_impl.h"
#include "core/components_ng/pattern/tabs/tabs_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<TabsModel> TabsModel::instance_ = nullptr;
std::mutex TabsModel::mutex_;

TabsModel* TabsModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::TabsModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::TabsModelNG());
            } else {
                instance_.reset(new Framework::TabsModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
namespace {
constexpr int32_t SM_COLUMN_NUM = 4;
constexpr int32_t MD_COLUMN_NUM = 8;
constexpr int32_t LG_COLUMN_NUM = 12;
const static int32_t PLATFORM_VERSION_TEN = 10;
const std::vector<BarPosition> BAR_POSITIONS = { BarPosition::START, BarPosition::END };

JSRef<JSVal> TabContentChangeEventToJSValue(const TabContentChangeEvent& eventInfo)
{
    return JSRef<JSVal>::Make(ToJSValue(eventInfo.GetIndex()));
}

} // namespace

void JSTabs::SetOnChange(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }

    auto changeHandler = AceType::MakeRefPtr<JsEventFunction<TabContentChangeEvent, 1>>(
        JSRef<JSFunc>::Cast(info[0]), TabContentChangeEventToJSValue);
    auto onChange = [executionContext = info.GetExecutionContext(), func = std::move(changeHandler)](
                        const BaseEventInfo* info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext);
        const auto* tabsInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        if (!tabsInfo) {
            LOGE("SetOnChange tabsInfo is nullptr");
            return;
        }
        ACE_SCORING_EVENT("Tabs.onChange");
        func->Execute(*tabsInfo);
    };
    TabsModel::GetInstance()->SetOnChange(std::move(onChange));
}

void JSTabs::SetOnTabBarClick(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }

    auto changeHandler = AceType::MakeRefPtr<JsEventFunction<TabContentChangeEvent, 1>>(
        JSRef<JSFunc>::Cast(info[0]), TabContentChangeEventToJSValue);
    auto onTabBarClick = [executionContext = info.GetExecutionContext(), func = std::move(changeHandler)](
                             const BaseEventInfo* info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext);
        const auto* tabsInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        if (!tabsInfo) {
            LOGE("SetTabBarClick tabsInfo is nullptr");
            return;
        }
        ACE_SCORING_EVENT("Tabs.onTabBarClick");
        func->Execute(*tabsInfo);
    };
    TabsModel::GetInstance()->SetOnTabBarClick(std::move(onTabBarClick));
}

void ParseTabsIndexObject(const JSCallbackInfo& info, const JSRef<JSVal>& changeEventVal)
{
    CHECK_NULL_VOID(changeEventVal->IsFunction());

    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(changeEventVal));
    auto onChangeEvent = [executionContext = info.GetExecutionContext(), func = std::move(jsFunc)](
                             const BaseEventInfo* info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext);
        const auto* tabsInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        if (!tabsInfo) {
            LOGE("ParseTabsIndexObject tabsInfo is nullptr");
            return;
        }
        ACE_SCORING_EVENT("Tabs.onChangeEvent");
        auto newJSVal = JSRef<JSVal>::Make(ToJSValue(tabsInfo->GetIndex()));
        func->ExecuteJS(1, &newJSVal);
    };
    TabsModel::GetInstance()->SetOnChangeEvent(std::move(onChangeEvent));
}

void JSTabs::Create(const JSCallbackInfo& info)
{
    BarPosition barPosition = BarPosition::START;
    RefPtr<TabController> tabController;
    RefPtr<SwiperController> swiperController;
    int32_t index = -1;
    JSRef<JSVal> changeEventVal;
    if (info[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> val = obj->GetProperty("barPosition");
        if (val->IsNumber()) {
            auto barPositionVal = val->ToNumber<int32_t>();
            if (barPositionVal >= 0 && barPositionVal < static_cast<int32_t>(BAR_POSITIONS.size())) {
                barPosition = BAR_POSITIONS[barPositionVal];
            }
        }
        JSRef<JSVal> controller = obj->GetProperty("controller");
        if (controller->IsObject()) {
            auto* jsTabsController = JSRef<JSObject>::Cast(controller)->Unwrap<JSTabsController>();
            if (jsTabsController) {
                tabController = jsTabsController->GetController();
                swiperController = jsTabsController->GetSwiperController();
            }
        }
        JSRef<JSVal> indexVal = obj->GetProperty("index");
        if (indexVal->IsNumber()) {
            index = indexVal->ToNumber<int32_t>();
            index = index < 0 ? 0 : index;
            if (!tabController) {
                tabController = JSTabsController::CreateController();
            }
#ifndef NG_BUILD
            tabController->SetInitialIndex(index);
#endif
        } else if (indexVal->IsObject()) {
            JSRef<JSObject> indexObj = JSRef<JSObject>::Cast(indexVal);
            auto indexValueProperty = indexObj->GetProperty("value");
            if (indexValueProperty->IsNumber()) {
                index = indexValueProperty->ToNumber<int32_t>();
                index = index < 0 ? 0 : index;
            }
            changeEventVal = indexObj->GetProperty("changeEvent");
        }
    }

    TabsModel::GetInstance()->Create(barPosition, index, tabController, swiperController);
    if (!changeEventVal->IsUndefined() && changeEventVal->IsFunction()) {
        ParseTabsIndexObject(info, changeEventVal);
    }
}

void JSTabs::Pop()
{
    TabsModel::GetInstance()->Pop();
}

void JSTabs::SetBarPosition(const JSCallbackInfo& info)
{
    BarPosition barVal = BarPosition::START;
    if (info.Length() > 0 && info[0]->IsNumber()) {
        auto barPositionVal = info[0]->ToNumber<int32_t>();
        if (barPositionVal >= 0 && barPositionVal < static_cast<int32_t>(BAR_POSITIONS.size())) {
            barVal = BAR_POSITIONS[barPositionVal];
        }
    }

    TabsModel::GetInstance()->SetTabBarPosition(barVal);
}

void JSTabs::SetVertical(const std::string& value)
{
    TabsModel::GetInstance()->SetIsVertical(StringToBool(value));
}

void JSTabs::SetScrollable(const std::string& value)
{
    if (value == "undefined") {
        TabsModel::GetInstance()->SetScrollable(true);
        return;
    }
    TabsModel::GetInstance()->SetScrollable(StringToBool(value));
}

void JSTabs::SetBarMode(const JSCallbackInfo& info)
{
    TabBarMode barMode = TabBarMode::FIXED;
    if (info.Length() < 1) {
        TabsModel::GetInstance()->SetTabBarMode(barMode);
        return;
    }
    if (info[0]->IsString()) {
        barMode = ConvertStrToTabBarMode(info[0]->ToString());
    }
    if (barMode == TabBarMode::SCROLLABLE) {
        if (info.Length() > 1 && info[1]->IsObject()) {
            SetScrollableBarModeOptions(info[1]);
        } else {
            ScrollableBarModeOptions option;
            TabsModel::GetInstance()->SetScrollableBarModeOptions(option);
        }
    }
    TabsModel::GetInstance()->SetTabBarMode(barMode);
}

void JSTabs::SetBarWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    CalcDimension width = Dimension(-1.0, DimensionUnit::VP);
    if (PipelineBase::GetCurrentContext() &&
        PipelineBase::GetCurrentContext()->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN) {
        if (!ParseJsDimensionVpNG(info[0], width)) {
            TabsModel::GetInstance()->SetTabBarWidth(width);
            return;
        }
    } else if (!ParseJsDimensionVp(info[0], width)) {
        LOGE("The arg is wrong, fail to parse dimension");
    }

    TabsModel::GetInstance()->SetTabBarWidth(width);
}

void JSTabs::SetBarHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }
    CalcDimension height = Dimension(-1.0, DimensionUnit::VP);
    bool adaptiveHeight = false;
    if (info[0]->IsString() && info[0]->ToString() == "auto") {
        adaptiveHeight = true;
    } else {
        if (PipelineBase::GetCurrentContext() &&
            PipelineBase::GetCurrentContext()->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN) {
            if (!ParseJsDimensionVpNG(info[0], height)) {
                LOGD("The arg is wrong, fail to parse dimension");
            }
        } else if (!ParseJsDimensionVp(info[0], height)) {
            LOGD("The arg is wrong, fail to parse dimension");
        }
    }
    TabsModel::GetInstance()->SetBarAdaptiveHeight(adaptiveHeight);
    TabsModel::GetInstance()->SetTabBarHeight(height);
}

void JSTabs::SetIndex(int32_t index)
{
    TabsModel::GetInstance()->SetIndex(index);
}

void JSTabs::SetAnimationDuration(float value)
{
    if (std::isnan(value)) {
        LOGI("The arg is nan, use default value");
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto tabTheme = pipelineContext->GetTheme<TabTheme>();
        CHECK_NULL_VOID(tabTheme);
        TabsModel::GetInstance()->SetAnimationDuration(static_cast<float>(tabTheme->GetTabContentAnimationDuration()));
        return;
    }
    TabsModel::GetInstance()->SetAnimationDuration(value);
}

void JSTabs::SetFadingEdge(const JSCallbackInfo& info)
{
    bool fadingEdge = true;
    if (info.Length() < 1) {
        LOGW("The arg is wrong, it is supposed to have at least 1 arguments");
    } else if (!ParseJsBool(info[0], fadingEdge)) {
        LOGW("The arg is wrong, fail to parse bool");
    }
    TabsModel::GetInstance()->SetFadingEdge(fadingEdge);
}

void JSTabs::SetBarOverlap(const JSCallbackInfo& info)
{
    bool barOverlap = false;
    if (info.Length() < 1) {
        LOGW("The arg is wrong, it is supposed to have at least 1 arguments");
    } else if (!ParseJsBool(info[0], barOverlap)) {
        LOGW("The arg is wrong, fail to parse bool");
    }
    TabsModel::GetInstance()->SetBarOverlap(barOverlap);
}

void JSTabs::SetBarBackgroundColor(const JSCallbackInfo& info)
{
    Color backgroundColor = Color::BLACK.BlendOpacity(0.0f);
    if (info.Length() < 1) {
        LOGD("Invalid parameters. Use default parameters instead.");
    } else if (!ConvertFromJSValue(info[0], backgroundColor)) {
        LOGD("Invalid parameters. Use default parameters instead.");
    }
    TabsModel::GetInstance()->SetBarBackgroundColor(backgroundColor);
}

void JSTabs::SetDivider(const JSCallbackInfo& info)
{
    TabsItemDivider divider;
    CalcDimension dividerStrokeWidth;
    CalcDimension dividerStartMargin;
    CalcDimension dividerEndMargin;
    RefPtr<TabTheme> tabTheme = GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);

    if (info.Length() < 1) {
        LOGW("Invalid params");
    } else {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        if (info[0]->IsNull()) {
            divider.isNull = true;
        } else {
            if (!info[0]->IsObject() || !ParseJsDimensionVp(obj->GetProperty("strokeWidth"), dividerStrokeWidth) ||
                dividerStrokeWidth.Value() < 0.0f || dividerStrokeWidth.Unit() == DimensionUnit::PERCENT) {
                divider.strokeWidth.Reset();
            } else {
                divider.strokeWidth = dividerStrokeWidth;
            }
            if (!info[0]->IsObject() || !ConvertFromJSValue(obj->GetProperty("color"), divider.color)) {
                divider.color = tabTheme->GetDividerColor();
            }
            if (!info[0]->IsObject() || !ParseJsDimensionVp(obj->GetProperty("startMargin"), dividerStartMargin) ||
                dividerStartMargin.Value() < 0.0f || dividerStartMargin.Unit() == DimensionUnit::PERCENT) {
                divider.startMargin.Reset();
            } else {
                divider.startMargin = dividerStartMargin;
            }
            if (!info[0]->IsObject() || !ParseJsDimensionVp(obj->GetProperty("endMargin"), dividerEndMargin) ||
                dividerEndMargin.Value() < 0.0f || dividerEndMargin.Unit() == DimensionUnit::PERCENT) {
                divider.endMargin.Reset();
            } else {
                divider.endMargin = dividerEndMargin;
            }
        }
    }
    TabsModel::GetInstance()->SetDivider(divider);
}

void JSTabs::SetClip(const JSCallbackInfo& info)
{
    if (info[0]->IsObject() || !Container::IsCurrentUseNewPipeline()) {
        JSViewAbstract::JsClip(info);
        return;
    }
    if (info[0]->IsBoolean()) {
        TabsModel::GetInstance()->SetClipEdge(info[0]->ToBoolean());
    }
}

void JSTabs::SetScrollableBarModeOptions(const JSRef<JSVal>& info)
{
    ScrollableBarModeOptions option;
    auto optionParam = JSRef<JSObject>::Cast(info);
    CalcDimension margin = Dimension(0.0, DimensionUnit::VP);
    if (!ParseJsDimensionVp(optionParam->GetProperty("margin"), margin) || Negative(margin.Value()) ||
        margin.Unit() == DimensionUnit::PERCENT) {
        option.margin = 0.0_vp;
    } else {
        option.margin = margin;
    }

    auto nonScrollableLayoutStyle = optionParam->GetProperty("nonScrollableLayoutStyle");
    int32_t layoutStyle;
    if (!ConvertFromJSValue(nonScrollableLayoutStyle, layoutStyle)) {
        option.nonScrollableLayoutStyle = LayoutStyle::ALWAYS_CENTER;
    } else {
        option.nonScrollableLayoutStyle = (static_cast<LayoutStyle>(layoutStyle));
    }
    TabsModel::GetInstance()->SetScrollableBarModeOptions(option);
}

void JSTabs::SetBarGridAlign(const JSCallbackInfo& info)
{
    BarGridColumnOptions columnOption;
    if (info.Length() < 1) {
        LOGD("Invalid parameters. Use default parameters instead.");
    } else if (info[0]->IsObject()) {
        auto gridParam = JSRef<JSObject>::Cast(info[0]);
        auto sm = gridParam->GetProperty("sm");
        if (sm->IsNumber() && sm->ToNumber<int32_t>() >= 0 && sm->ToNumber<int32_t>() <= SM_COLUMN_NUM &&
            sm->ToNumber<int32_t>() % 2 == 0) {
            columnOption.sm = sm->ToNumber<int32_t>();
        }
        auto md = gridParam->GetProperty("md");
        if (md->IsNumber() && md->ToNumber<int32_t>() >= 0 && md->ToNumber<int32_t>() <= MD_COLUMN_NUM &&
            md->ToNumber<int32_t>() % 2 == 0) {
            columnOption.md = md->ToNumber<int32_t>();
        }
        auto lg = gridParam->GetProperty("lg");
        if (lg->IsNumber() && lg->ToNumber<int32_t>() >= 0 && lg->ToNumber<int32_t>() <= LG_COLUMN_NUM &&
            lg->ToNumber<int32_t>() % 2 == 0) {
            columnOption.lg = lg->ToNumber<int32_t>();
        }
        CalcDimension columnGutter;
        if (ParseJsDimensionVp(gridParam->GetProperty("gutter"), columnGutter) && NonNegative(columnGutter.Value()) &&
            columnGutter.Unit() != DimensionUnit::PERCENT) {
            columnOption.gutter = columnGutter;
        }
        CalcDimension columnMargin;
        if (ParseJsDimensionVp(gridParam->GetProperty("margin"), columnMargin) && NonNegative(columnMargin.Value()) &&
            columnMargin.Unit() != DimensionUnit::PERCENT) {
            columnOption.margin = columnMargin;
        }
    }
    TabsModel::GetInstance()->SetBarGridAlign(columnOption);
}

void JSTabs::JSBind(BindingTarget globalObj)
{
    JSClass<JSTabs>::Declare("Tabs");
    JSClass<JSTabs>::StaticMethod("create", &JSTabs::Create);
    JSClass<JSTabs>::StaticMethod("pop", &JSTabs::Pop);
    JSClass<JSTabs>::StaticMethod("vertical", &JSTabs::SetVertical);
    JSClass<JSTabs>::StaticMethod("barPosition", &JSTabs::SetBarPosition);
    JSClass<JSTabs>::StaticMethod("scrollable", &JSTabs::SetScrollable);
    JSClass<JSTabs>::StaticMethod("barMode", &JSTabs::SetBarMode);
    JSClass<JSTabs>::StaticMethod("barWidth", &JSTabs::SetBarWidth);
    JSClass<JSTabs>::StaticMethod("barHeight", &JSTabs::SetBarHeight);
    JSClass<JSTabs>::StaticMethod("index", &JSTabs::SetIndex);
    JSClass<JSTabs>::StaticMethod("animationDuration", &JSTabs::SetAnimationDuration);
    JSClass<JSTabs>::StaticMethod("divider", &JSTabs::SetDivider);
    JSClass<JSTabs>::StaticMethod("onChange", &JSTabs::SetOnChange);
    JSClass<JSTabs>::StaticMethod("onTabBarClick", &JSTabs::SetOnTabBarClick);
    JSClass<JSTabs>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSTabs>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSTabs>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSTabs>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSTabs>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSTabs>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSTabs>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSTabs>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);
    JSClass<JSTabs>::StaticMethod("fadingEdge", &JSTabs::SetFadingEdge);
    JSClass<JSTabs>::StaticMethod("barOverlap", &JSTabs::SetBarOverlap);
    JSClass<JSTabs>::StaticMethod("barBackgroundColor", &JSTabs::SetBarBackgroundColor);
    JSClass<JSTabs>::StaticMethod("clip", &JSTabs::SetClip);
    JSClass<JSTabs>::StaticMethod("barGridAlign", &JSTabs::SetBarGridAlign);

    JSClass<JSTabs>::InheritAndBind<JSContainerBase>(globalObj);
}

} // namespace OHOS::Ace::Framework
