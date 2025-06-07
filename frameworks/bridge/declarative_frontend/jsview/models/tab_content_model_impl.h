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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_TAB_CONTENT_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_TAB_CONTENT_MODEL_IMPL_H

#include "core/components_ng/pattern/tabs/tab_content_model.h"
#include "core/components_v2/tabs/tab_content_item_component.h"

namespace OHOS::Ace::Framework {

class TabContentModelImpl : public OHOS::Ace::TabContentModel {
public:
    void Create(std::function<void()>&& deepRenderFunc) override;
    void Create() override;
    void Pop() override;
    void SetTabBar(const std::optional<std::string>& text, const std::optional<std::string>& icon,
        const std::optional<TabBarSymbol>& tabBarSymbol, std::function<void()>&& builder,
        bool useContentOnly) override;
    void SetTabBarWithContent(const RefPtr<NG::UINode>& content) override {}
    void SetTabBarStyle(TabBarStyle tabBarStyle) override {}
    void SetIndicator(const IndicatorStyle& indicator) override {}
    void SetIndicatorColorByUser(bool isByUser) override {};
    void SetBoard(const BoardStyle& board) override {}
    void SetSelectedMode(SelectedMode selectedMode) override {}
    void SetLabelStyle(const LabelStyle& labelStyle) override {}
    void SetLabelUnselectedColorByUser(bool isByUser) override {};
    void SetLabelSelectedColorByUser(bool isByUser) override {};
    void SetIconStyle(const IconStyle& iconStyle) override {}
    void SetIconUnselectedColorByUser(bool isByUser) override {};
    void SetIconSelectedColorByUser(bool isByUser) override {};
    void SetPadding(const NG::PaddingProperty& padding) override {}
    void SetUseLocalizedPadding(bool useLocalizedPadding) override {}
    void SetLayoutMode(LayoutMode layoutMode) override {}
    void SetVerticalAlign(FlexAlign verticalAlign) override {}
    void SetSymmetricExtensible(bool isExtensible) override {}
    void SetId(const std::string& id) override {}
    void SetOnWillShow(std::function<void()>&& onWillShow) override {}
    void SetOnWillHide(std::function<void()>&& onWillHide) override {}

private:
    RefPtr<Component> ProcessTabBarBuilderFunction(
        RefPtr<V2::TabContentItemComponent>& tabContent, std::function<void()>&& builderFunc);
    RefPtr<Component> ProcessTabBarTextIconPair(RefPtr<V2::TabContentItemComponent>& tabContent,
        const std::optional<std::string>& textVal, const std::optional<std::string>& iconVal);
    RefPtr<Component> CreateTabBarLabelComponent(
        RefPtr<V2::TabContentItemComponent>& tabContent, const std::string& labelStr);
    RefPtr<Component> ProcessTabBarLabel(
        RefPtr<V2::TabContentItemComponent>& tabContent, const std::optional<std::string>& textVal);
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_TAB_CONTENT_MODEL_IMPL_H
