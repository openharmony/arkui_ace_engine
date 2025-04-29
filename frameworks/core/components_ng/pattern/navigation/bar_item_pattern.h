/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_BAR_ITEM_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_BAR_ITEM_PATTERN_H

#include "base/memory/referenced.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/navigation/bar_item_event_hub.h"
#include "core/components_ng/pattern/navigation/bar_item_layout_algorithm.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {

class BarItemPattern : public Pattern {
    DECLARE_ACE_TYPE(BarItemPattern, Pattern);

public:
    BarItemPattern() = default;
    ~BarItemPattern() override = default;

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<LayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<BarItemLayoutAlgorithm>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<BarItemEventHub>();
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

    void OnModifyDone() override;

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::NODE, true };
    }

    void SetActiveIconImageSourceInfo(const ImageSourceInfo& info)
    {
        info_ = info;
    }

    const ImageSourceInfo& GetActiveIconImageSourceInfo() const
    {
        return info_;
    }

    void SetInitialIconImageSourceInfo(const ImageSourceInfo& info)
    {
        initalInfo_ = info;
    }

    const ImageSourceInfo& GetInitialIconImageSourceInfo() const
    {
        return initalInfo_;
    }

    void SetInitialIconSymbol(const std::function<void(WeakPtr<NG::FrameNode>)>& symbol)
    {
        initalSymbol_ = symbol;
    }

    const std::function<void(WeakPtr<NG::FrameNode>)>& GetInitialIconSymbol() const
    {
        return initalSymbol_;
    }

    void SetActiveIconSymbol(const std::function<void(WeakPtr<NG::FrameNode>)>& symbol)
    {
        activeSymbol_ = symbol;
    }

    const std::function<void(WeakPtr<NG::FrameNode>)>& GetActiveIconSymbol() const
    {
        return activeSymbol_;
    }

    void SetToolbarItemStatus(NavToolbarItemStatus status)
    {
        status_ = status;
    }

    NavToolbarItemStatus GetToolbarItemStatus() const
    {
        return status_;
    }

    void SetCurrentIconStatus(ToolbarIconStatus iconStatus)
    {
        iconStatus_ = iconStatus;
    }

    ToolbarIconStatus GetCurrentIconStatus() const
    {
        return iconStatus_;
    }

    void UpdateBarItemActiveStatusResource();

    void UpdateBarItemTextAndIconStatusResource(const RefPtr<BarItemNode>& barItemNode,
        const RefPtr<FrameNode>& iconNode);

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    bool OnThemeScopeUpdate(int32_t themeScopeId) override;

private:
    RefPtr<NavigationBarTheme> GetNavigationBarTheme();

private:
    RefPtr<ClickEvent> clickListener_;
    ImageSourceInfo info_;
    ImageSourceInfo initalInfo_;
    std::function<void(WeakPtr<NG::FrameNode>)> initalSymbol_;
    std::function<void(WeakPtr<NG::FrameNode>)> activeSymbol_;
    NavToolbarItemStatus status_ = NavToolbarItemStatus::NORMAL;
    ToolbarIconStatus iconStatus_ = ToolbarIconStatus::INITIAL;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_BAR_ITEM_PATTERN_H
