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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TABS_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TABS_PATTERN_H

#include <optional>

#include "base/geometry/axis.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/tabs/tabs_layout_algorithm.h"
#include "core/components_ng/pattern/tabs/tabs_layout_property.h"

namespace OHOS::Ace::NG {

class TabsPattern : public Pattern {
    DECLARE_ACE_TYPE(TabsPattern, Pattern);

public:
    using ChangeEvent = std::function<void(int32_t)>;
    using ChangeEventPtr = std::shared_ptr<ChangeEvent>;

    TabsPattern() = default;
    ~TabsPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<TabsLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<TabsLayoutAlgorithm>();
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    ScopeFocusAlgorithm GetScopeFocusAlgorithm() override;

    void SetOnChangeEvent(std::function<void(const BaseEventInfo*)>&& event);

    void SetOnTabBarClickEvent(std::function<void(const BaseEventInfo*)>&& event);

    ChangeEventPtr GetTabBarClickEvent()
    {
        return onTabBarClickEvent_;
    }

    void OnModifyDone() override;
	
    std::string ProvideRestoreInfo() override;
    
    void OnRestoreInfo(const std::string& restoreInfo) override;
	
    void SetOnIndexChangeEvent(std::function<void(const BaseEventInfo*)>&& event);

private:
    void OnAttachToFrameNode() override;
    void OnUpdateShowDivider();
    WeakPtr<FocusHub> GetNextFocusNode(FocusStep step, const WeakPtr<FocusHub>& currentFocusNode);
    void BeforeCreateLayoutWrapper() override;

    ChangeEventPtr onChangeEvent_;
    ChangeEventPtr onTabBarClickEvent_;
    ChangeEventPtr onIndexChangeEvent_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TABS_PATTERN_H
