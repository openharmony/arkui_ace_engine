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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_tab_ffi.h"

#include "cj_lambda.h"

#include "core/components_ng/pattern/tabs/tab_content_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace {
const std::vector<BarPosition> BAR_POSITIONS = { BarPosition::START, BarPosition::END };
const std::vector<TabBarMode> TAB_BAR_MODES = {
    TabBarMode::FIXED, TabBarMode::SCROLLABLE
    // not support TabBarMode::FIXED_START yet
};
} // namespace

namespace OHOS::Ace::Framework {

namespace {

int32_t g_tabControllerId = 0;

} // namespace

TabsController::TabsController() : FFIData()
{
    controller_ = TabController::GetController(++g_tabControllerId);
    swiperController_ = AceType::MakeRefPtr<SwiperController>();
    LOGI("Native TabsController constructed: %{public}" PRId64, GetID());
}

TabsController::~TabsController()
{
    LOGI("Native TabsController Destroyed: %{public}" PRId64, GetID());
}

void TabsController::ChangeIndex(int32_t index)
{
    LOGI("Native TabsController %{public}" PRId64 "ChangeIndex: %{public}d", GetID(), index);
    if (swiperController_) {
        const auto& updateCubicCurveCallback = swiperController_->GetUpdateCubicCurveCallback();
        if (updateCubicCurveCallback != nullptr) {
            updateCubicCurveCallback();
        }
        swiperController_->SwipeTo(index);
    }
    if (controller_) {
        controller_->SetIndexByController(index, false);
    }
}

} // namespace OHOS::Ace::Framework

extern "C" {
void FfiOHOSAceFrameworkTabsCreate(int32_t barPosition, int64_t controllerId, int32_t index)
{
#ifndef ARKUI_WEARABLE
    if (!Utils::CheckParamsValid(barPosition, BAR_POSITIONS.size())) {
        LOGE("invalid value for bar position");
        return;
    }
    auto nativeTabsController = FFIData::GetData<TabsController>(controllerId);
    if (nativeTabsController == nullptr) {
        return;
    }
    RefPtr<TabController> tabController;
    RefPtr<SwiperController> swiperController;

    tabController = nativeTabsController->GetController();
    swiperController = nativeTabsController->GetSwiperController();
    tabController->SetInitialIndex(index);
    TabsModel::GetInstance()->Create(BAR_POSITIONS[barPosition], index, tabController, swiperController);
#endif
}

void FfiOHOSAceFrameworkTabsPop()
{
#ifndef ARKUI_WEARABLE
    TabsModel::GetInstance()->Pop();
#endif
}

void FfiOHOSAceFrameworkTabsSetBarWidth(double width, int32_t unit)
{
#ifndef ARKUI_WEARABLE
    Dimension value(width, static_cast<DimensionUnit>(unit));
    TabsModel::GetInstance()->SetTabBarWidth(value);
#endif
}

void FfiOHOSAceFrameworkTabsSetBarHeight(double height, int32_t unit)
{
#ifndef ARKUI_WEARABLE
    Dimension value(height, static_cast<DimensionUnit>(unit));
    TabsModel::GetInstance()->SetTabBarHeight(value);
#endif
}

void FfiOHOSAceFrameworkTabsSetBarMode(int32_t barMode)
{
#ifndef ARKUI_WEARABLE
    if (!Utils::CheckParamsValid(barMode, TAB_BAR_MODES.size())) {
        LOGE("invalid value for tab bar mode");
        return;
    }
    TabsModel::GetInstance()->SetTabBarMode(TAB_BAR_MODES[barMode]);
#endif
}

void FfiOHOSAceFrameworkTabsSetIndex(int32_t index)
{
#ifndef ARKUI_WEARABLE
    TabsModel::GetInstance()->SetIndex(index);
#endif
}

void FfiOHOSAceFrameworkTabsSetVertical(bool isVertical)
{
#ifndef ARKUI_WEARABLE
    TabsModel::GetInstance()->SetIsVertical(isVertical);
#endif
}

void FfiOHOSAceFrameworkTabsSetScrollable(bool isScrollable)
{
#ifndef ARKUI_WEARABLE
    TabsModel::GetInstance()->SetScrollable(isScrollable);
#endif
}

void FfiOHOSAceFrameworkTabsSetAnimationDuration(float duration)
{
#ifndef ARKUI_WEARABLE
    TabsModel::GetInstance()->SetAnimationDuration(duration);
#endif
}

void FfiOHOSAceFrameworkTabsOnChange(void (*callback)(int32_t index))
{
#ifndef ARKUI_WEARABLE
    auto onChange = [lambda = CJLambda::Create(callback)](const BaseEventInfo* info) {
        const auto* tabsInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        if (!tabsInfo) {
            LOGE("HandleChangeEvent tabsInfo == nullptr");
            return;
        }
        lambda(tabsInfo->GetIndex());
    };
    TabsModel::GetInstance()->SetOnChange(std::move(onChange));
#endif
}

int64_t FfiOHOSAceFrameworkTabsControllerCtor()
{
#ifndef ARKUI_WEARABLE
    auto ret_ = FFIData::Create<TabsController>();
    return ret_->GetID();
#else
    return 0;
#endif
}

void FfiOHOSAceFrameworkTabsControllerChangeIndex(int64_t selfId, int32_t index)
{
#ifndef ARKUI_WEARABLE
    auto self_ = FFIData::GetData<TabsController>(selfId);
    if (self_ != nullptr) {
        self_->ChangeIndex(index);
    }
#endif
}

void FfiOHOSAceFrameworkTabContentCreate()
{
#ifndef ARKUI_WEARABLE
    TabContentModel::GetInstance()->Create();
#endif
}

void FfiOHOSAceFrameworkTabContentPop()
{
#ifndef ARKUI_WEARABLE
    TabContentModel::GetInstance()->Pop();
#endif
}

void FfiOHOSAceFrameworkTabContentSetTabBar(const char* content)
{
#ifndef ARKUI_WEARABLE
    TabContentModel::GetInstance()->SetTabBar(content, std::nullopt, std::nullopt, nullptr, true);
#endif
}

void FfiOHOSAceFrameworkTabContentSetTabBarWithIcon(const char* icon, const char* text)
{
#ifndef ARKUI_WEARABLE
    TabContentModel::GetInstance()->SetTabBar(text, icon, std::nullopt, nullptr, false);
#endif
}

void FfiOHOSAceFrameworkTabContentSetTabBarWithComponent(void (*callback)())
{
#ifndef ARKUI_WEARABLE
    TabContentModel::GetInstance()->SetTabBar(
        std::nullopt, std::nullopt, std::nullopt, CJLambda::Create(callback), false);
#endif
}

void FfiOHOSAceFrameworkTabContentPUCreate(void (*callback)())
{
#ifndef ARKUI_WEARABLE
    auto childBuild = CJLambda::Create(callback);
    TabContentModel::GetInstance()->Create(std::move(childBuild));
#endif
}
}
