/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_TABS_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_TABS_MODEL_IMPL_H

#include "core/components/tab_bar/tab_theme.h"
#include "core/components_ng/pattern/tabs/tabs_model.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"

namespace OHOS::Ace::Framework {

class TabsModelImpl : public OHOS::Ace::TabsModel {
public:
    void Create(BarPosition barPosition, int32_t index, const RefPtr<TabController>& tabController,
        const RefPtr<SwiperController>& swiperController) override;
    void Pop() override;
    void SetIndex(int32_t index) override;
    void SetTabBarPosition(BarPosition tabBarPosition) override;
    void SetTabBarMode(TabBarMode tabBarMode) override;
    void SetTabBarWidth(const Dimension& tabBarWidth) override;
    void SetTabBarHeight(const Dimension& tabBarHeight) override;
    void SetWidthAuto(bool isAuto) override {};
    void SetHeightAuto(bool isAuto) override {};
    void SetBarAdaptiveHeight(bool barAdaptiveHeight) override {};
    void SetIsVertical(bool isVertical) override;
    void SetScrollable(bool scrollable) override;
    void SetAnimationDuration(float duration) override;
    void SetOnChange(std::function<void(const BaseEventInfo*)>&& onChange) override;
    void SetOnTabBarClick(std::function<void(const BaseEventInfo*)>&& onChange) override {};
    void SetDivider(const TabsItemDivider& divider) override {};
    void SetFadingEdge(bool fadingEdge) override {};
    void SetBarOverlap(bool barOverlap) override {};
    void SetOnChangeEvent(std::function<void(const BaseEventInfo*)>&& onChangeEvent) override {};
    void SetBarBackgroundColor(const Color& backgroundColor) override {};
    void SetClipEdge(bool clipEdge) override {};
    void SetScrollableBarModeOptions(const ScrollableBarModeOptions& option) override {};
    void SetBarGridAlign(const BarGridColumnOptions& BarGridColumnOptions) override {};
    void SetAnimateMode(TabAnimateMode mode) override {};
    void ResetScrollableBarModeOptions() override {};

private:
    RefPtr<TabTheme> GetTheme() const;
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_TABS_MODEL_IMPL_H
