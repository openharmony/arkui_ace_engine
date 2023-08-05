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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TAB_CONTENT_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TAB_CONTENT_PATTERN_H

#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/tabs/tab_bar_pattern.h"
#include "core/components_ng/pattern/tabs/tab_content_layout_property.h"
#include "core/components_ng/syntax/shallow_builder.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT TabContentPattern : public Pattern {
    DECLARE_ACE_TYPE(TabContentPattern, Pattern);

public:
    explicit TabContentPattern(const RefPtr<ShallowBuilder>& shallowBuilder)
        : shallowBuilder_(shallowBuilder), tabBarParam_(std::string(""), std::string(""), nullptr)
    {}
    ~TabContentPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    bool IsMeasureBoundary() const override
    {
        return false;
    }

    bool UsResRegion() override
    {
        return false;
    }

    void OnAttachToFrameNode() override
    {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->GetRenderContext()->UpdateClipEdge(true);
    }

    void BeforeCreateLayoutWrapper() override
    {
        if (shallowBuilder_ && !shallowBuilder_->IsExecuteDeepRenderDone()) {
            shallowBuilder_->ExecuteDeepRender();
            shallowBuilder_.Reset();
        }
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<TabContentLayoutProperty>();
    }

    void SetTabBar(const std::string& text, const std::string& icon, TabBarBuilderFunc&& builder)
    {
        tabBarParam_.SetText(text);
        tabBarParam_.SetIcon(icon);
        tabBarParam_.SetBuilder(move(builder));
    }

    const TabBarParam& GetTabBarParam() const
    {
        return tabBarParam_;
    }

    void SetTabBarStyle(TabBarStyle tabBarStyle)
    {
        tabBarParam_.SetTabBarStyle(tabBarStyle);
    }

    TabBarStyle GetTabBarStyle() const
    {
        return tabBarParam_.GetTabBarStyle();
    }

    void SetIndicatorStyle(const IndicatorStyle& indicatorStyle)
    {
        indicatorStyle_ = indicatorStyle;
    }

    const IndicatorStyle& GetIndicatorStyle() const
    {
        return indicatorStyle_;
    }

    void SetSelectedMode(SelectedMode selectedMode)
    {
        selectedMode_ = selectedMode;
    }

    SelectedMode GetSelectedMode() const
    {
        return selectedMode_;
    }

    void SetBoardStyle(const BoardStyle& boardStyle)
    {
        boardStyle_ = boardStyle;
    }

    const BoardStyle& GetBoardStyle() const
    {
        return boardStyle_;
    }

    void SetLabelStyle(const LabelStyle& labelStyle)
    {
        labelStyle_ = labelStyle;
    }

    const LabelStyle& GetLabelStyle() const
    {
        return labelStyle_;
    }

private:
    RefPtr<ShallowBuilder> shallowBuilder_;
    TabBarParam tabBarParam_;
    IndicatorStyle indicatorStyle_;
    SelectedMode selectedMode_ = SelectedMode::INDICATOR;
    BoardStyle boardStyle_;
    LabelStyle labelStyle_;

    ACE_DISALLOW_COPY_AND_MOVE(TabContentPattern);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TAB_CONTENT_PATTERN_H
