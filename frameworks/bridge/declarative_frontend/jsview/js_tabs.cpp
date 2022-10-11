/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/models/tabs_model_impl.h"
#include "core/components_ng/pattern/tabs/tabs_model_ng.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_tabs_controller.h"

namespace OHOS::Ace {

std::unique_ptr<TabsModel> TabsModel::instance_ = nullptr;

TabsModel* TabsModel::GetInstance()
{
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
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
namespace {

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
            LOGE("HandleChangeEvent tabsInfo == nullptr");
            return;
        }
        ACE_SCORING_EVENT("Tabs.onChange");
        func->Execute(*tabsInfo);
    };
    TabsModel::GetInstance()->SetOnChange(std::move(onChange));
}

void JSTabs::Create(const JSCallbackInfo& info)
{
    BarPosition barPosition = BarPosition::START;
    RefPtr<TabController> tabController;
    RefPtr<SwiperController> swiperController;
    int32_t index = 0;
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
            if (!tabController) {
                tabController = JSTabsController::CreateController();
            }
            tabController->SetInitialIndex(index);
        }
    }

    TabsModel::GetInstance()->Create(barPosition, index, tabController, swiperController);
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
    TabsModel::GetInstance()->SetScrollable(StringToBool(value));
}

void JSTabs::SetBarMode(const std::string& value)
{
    TabsModel::GetInstance()->SetTabBarMode(ConvertStrToTabBarMode(value));
}

void JSTabs::SetBarWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    Dimension width;
    if (!ParseJsDimensionVp(info[0], width)) {
        LOGE("The arg is wrong, fail to parse dimension");
        return;
    }

    TabsModel::GetInstance()->SetTabBarWidth(width);
}

void JSTabs::SetBarHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }
    Dimension height;
    if (!ParseJsDimensionVp(info[0], height)) {
        LOGE("The arg is wrong, fail to parse dimension");
        return;
    }

    TabsModel::GetInstance()->SetTabBarHeight(height);
}

void JSTabs::SetIndex(int32_t index)
{
    TabsModel::GetInstance()->SetIndex(index);
}

void JSTabs::SetAnimationDuration(float value)
{
    TabsModel::GetInstance()->SetAnimationDuration(value);
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
    JSClass<JSTabs>::StaticMethod("onChange", &JSTabs::SetOnChange);
    JSClass<JSTabs>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSTabs>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSTabs>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSTabs>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSTabs>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSTabs>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSTabs>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSTabs>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);
    JSClass<JSTabs>::Inherit<JSContainerBase>();
    JSClass<JSTabs>::Bind<>(globalObj);
}

} // namespace OHOS::Ace::Framework
