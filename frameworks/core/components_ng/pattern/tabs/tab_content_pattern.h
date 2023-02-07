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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TAB_CONTENT_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TAB_CONTENT_PATTERN_H

#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/tabs/tab_bar_pattern.h"
#include "core/components_ng/pattern/tabs/tab_content_layout_property.h"
#include "core/components_ng/syntax/shallow_builder.h"
#include "core/pipeline_ng/pipeline_context.h"

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

    bool UsResRegion() override
    {
        return false;
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

    bool HasSurfaceChangedCallback()
    {
        return surfaceChangedCallbackId_.has_value();
    }

    void HandleSurfaceChanged(int32_t newWidth, int32_t newHeight)
    {
        LOGD("TabContent handle surface change, new width %{public}d, new height %{public}d", newWidth, newHeight);
        isLandscape_ = newHeight / newWidth <= 1;
    }

    void UpdateSurfaceChangedCallbackId(int32_t id)
    {
        surfaceChangedCallbackId_ = id;
    }

    bool GetIsLandscape() const
    {
        return isLandscape_;
    }

private:
    void OnDetachFromFrameNode(FrameNode* node) override
    {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        if (HasSurfaceChangedCallback()) {
            LOGD("Unregister surface change callback with id %{public}d", surfaceChangedCallbackId_.value_or(-1));
            pipeline->UnregisterSurfaceChangedCallback(surfaceChangedCallbackId_.value_or(-1));
        }
    }

    RefPtr<ShallowBuilder> shallowBuilder_;
    TabBarParam tabBarParam_;
    std::optional<int32_t> surfaceChangedCallbackId_;
    bool isLandscape_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(TabContentPattern);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TAB_CONTENT_PATTERN_H
