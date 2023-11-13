/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PANEL_CLOSE_ICON_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PANEL_CLOSE_ICON_PATTERN_H

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/panel/close_icon_layout_algorithm.h"
#include "core/components_ng/pattern/panel/close_icon_layout_property.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
using ClickButtonCallback = std::function<void()>;

class CloseIconPattern : public Pattern {
    DECLARE_ACE_TYPE(CloseIconPattern, Pattern);

public:
    CloseIconPattern() = default;
    ~CloseIconPattern() override = default;
    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<CloseIconLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<CloseIconLayoutAlgorithm>();
    }

    RefPtr<CloseIconLayoutProperty> GetCloseIconLayoutProperty() const
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, nullptr);
        auto layoutProperty = host->GetLayoutProperty<CloseIconLayoutProperty>();
        CHECK_NULL_RETURN(layoutProperty, nullptr);
        return layoutProperty;
    }

    bool HasClickButtonCallback() const
    {
        return (clickButtonCallback_ != nullptr);
    }

    void SetClickButtonCallback(const ClickButtonCallback& callback)
    {
        clickButtonCallback_ = callback;
    }

private:
    void OnModifyDone() override;
    void InitCloseIcon();
    void InitButtonEvent();
    void ButtonClickEvent();

    RefPtr<ClickEvent> buttonClickListenr_;
    ClickButtonCallback clickButtonCallback_;
    bool isFirstLayout_ {true};

    ACE_DISALLOW_COPY_AND_MOVE(CloseIconPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PANEL_CLOSE_ICON_PATTERN_H
