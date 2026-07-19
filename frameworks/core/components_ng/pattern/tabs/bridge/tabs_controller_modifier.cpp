/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/tabs/bridge/tabs_controller_modifier_api.h"
#include "core/components_ng/pattern/tabs/bridge/tabs_transition_proxy_modifier_api.h"

#include "base/log/log_wrapper.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/tabs/tab_content_transition_proxy.h"
#include "core/components_ng/pattern/tabs/tabs_controller.h"
namespace OHOS::Ace {
namespace {

OHOS::Ace::NG::TabsControllerNG* ToController(const RefPtr<AceType>& controller)
{
    auto tabsController = AceType::DynamicCast<OHOS::Ace::NG::TabsControllerNG>(controller);
    return AceType::RawPtr(tabsController);
}

RefPtr<AceType> CreateControllerImpl()
{
    return AceType::MakeRefPtr<OHOS::Ace::NG::TabsControllerNG>();
}

void DestroyControllerImpl(const RefPtr<AceType>& controller)
{
    (void)controller;
}

void ChangeIndex(const RefPtr<AceType>& controller, int32_t index)
{
    auto* tabsController = ToController(controller);
    CHECK_NULL_VOID(tabsController);
    const auto& updateCurve = tabsController->GetUpdateCubicCurveCallback();
    if (updateCurve) {
        updateCurve();
    }
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_TABS, "changeIndex %{public}d", index);
    tabsController->SwipeTo(index);
}

void PreloadItemsImpl(const RefPtr<AceType>& controller, const int32_t* indices, int32_t count)
{
    auto* tabsController = ToController(controller);
    CHECK_NULL_VOID(tabsController);
    CHECK_NULL_VOID(indices);
    std::set<int32_t> indexSet;
    for (int32_t i = 0; i < count; ++i) {
        indexSet.emplace(indices[i]);
    }
    tabsController->PreloadItems(indexSet);
}

void SetPreloadFinishCallbackImpl(
    const RefPtr<AceType>& controller, const std::function<void(const int32_t, const std::string)>& callback)
{
    auto* ctl = ToController(controller);
    CHECK_NULL_VOID(ctl);
    ctl->SetPreloadFinishCallback(callback);
}

void SetTabBarTranslateImpl(const RefPtr<AceType>& controller, double x, double y, double z,
    int32_t unitX, int32_t unitY, int32_t unitZ)
{
    auto* tabsController = ToController(controller);
    CHECK_NULL_VOID(tabsController);
    OHOS::Ace::NG::TranslateOptions translate;
    translate.x = CalcDimension(x, static_cast<DimensionUnit>(unitX));
    translate.y = CalcDimension(y, static_cast<DimensionUnit>(unitY));
    translate.z = CalcDimension(z, static_cast<DimensionUnit>(unitZ));
    tabsController->SetTabBarTranslate(translate);
}

void SetTabBarOpacityImpl(const RefPtr<AceType>& controller, double opacity)
{
    auto* tabsController = ToController(controller);
    CHECK_NULL_VOID(tabsController);
    tabsController->SetTabBarOpacity(opacity);
}

void StartShowTabBarImpl(const RefPtr<AceType>& controller, int32_t delay)
{
    auto* tabsController = ToController(controller);
    CHECK_NULL_VOID(tabsController);
    tabsController->StartShowTabBar(delay);
}

void CancelShowTabBarImpl(const RefPtr<AceType>& controller)
{
    auto* tabsController = ToController(controller);
    CHECK_NULL_VOID(tabsController);
    tabsController->CancelShowTabBar();
}

void UpdateTabBarHiddenOffsetImpl(const RefPtr<AceType>& controller, double offset)
{
    auto* tabsController = ToController(controller);
    CHECK_NULL_VOID(tabsController);
    tabsController->UpdateTabBarHiddenOffset(static_cast<float>(offset));
}

void SetOnChangeImplImpl(const RefPtr<AceType>& controller,
                         const std::function<void(int32_t)>& callback)
{
    auto* ctl = ToController(controller);
    CHECK_NULL_VOID(ctl);
    ctl->SetOnChangeImpl(callback);
}

int32_t TransitionGetFromIndexImpl(const RefPtr<AceType>& proxy)
{
    auto p = AceType::DynamicCast<TabContentTransitionProxy>(proxy);
    return p ? p->GetFromIndex() : 0;
}

int32_t TransitionGetToIndexImpl(const RefPtr<AceType>& proxy)
{
    auto p = AceType::DynamicCast<TabContentTransitionProxy>(proxy);
    return p ? p->GetToIndex() : 0;
}

void TransitionFinishImpl(const RefPtr<AceType>& proxy)
{
    auto p = AceType::DynamicCast<TabContentTransitionProxy>(proxy);
    if (p) {
        p->FinishTransition();
    }
}

} // namespace
namespace NG::NodeModifier {
const ArkUITabsControllerModifier* GetTabsControllerModifier()
{
    static const ArkUITabsControllerModifier modifier = {
        .createController = CreateControllerImpl,
        .destroyController = DestroyControllerImpl,
        .changeIndex = ChangeIndex,
        .preloadItems = PreloadItemsImpl,
        .setPreloadFinishCallback = SetPreloadFinishCallbackImpl,
        .setTabBarTranslate = SetTabBarTranslateImpl,
        .setTabBarOpacity = SetTabBarOpacityImpl,
        .startShowTabBar = StartShowTabBarImpl,
        .cancelShowTabBar = CancelShowTabBarImpl,
        .updateTabBarHiddenOffset = UpdateTabBarHiddenOffsetImpl,
        .setOnChangeImpl = SetOnChangeImplImpl,
    };
    return &modifier;
}

const ArkUITabContentTransitionModifier* GetTabsTransitionProxyModifier()
{
    static const ArkUITabContentTransitionModifier modifier = {
        .getFromIndex = TransitionGetFromIndexImpl,
        .getToIndex = TransitionGetToIndexImpl,
        .finishTransition = TransitionFinishImpl,
    };
    return &modifier;
}
} // namespace NG::NodeModifier
} // namespace OHOS::Ace
