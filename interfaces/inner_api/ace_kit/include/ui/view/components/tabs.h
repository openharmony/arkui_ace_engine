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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_VIEW_COMPONENTS_TABS_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_VIEW_COMPONENTS_TABS_H

#include <functional>

#include "ui/base/macros.h"
#include "ui/base/type_info_base.h"
#include "ui/properties/brightness_option.h"
#include "ui/properties/color.h"
#include "ui/view/view.h"

namespace OHOS::Ace::Kit {

class FrameNode;

struct TabsItemDivider {
    Dimension strokeWidth;
    Color color;
    Dimension startMargin;
    Dimension endMargin;
    bool isNull;
};

class ACE_FORCE_EXPORT Tabs : public View {
public:
    using OnChangeEvent = std::function<void(int32_t)>;
    Tabs();
    Tabs(RefPtr<FrameNode>& node);
    ~Tabs();
    static RefPtr<Tabs> Create();
    static RefPtr<Tabs> Create(RefPtr<FrameNode>& node);

    void SetDivider(const TabsItemDivider& divider);
    void UpdateDividerOpacity(const double opacity);

    void UpdateTabBarBrightness(const BrightnessOption& brightnessOption);
    double GetTabBarTop();
    double GetTabBarBottom();
    RefPtr<FrameNode> GetTabBar();
    void SetOnChange(OnChangeEvent onChangeEvent);
};

} // namespace OHOS::Ace::Kit
#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_VIEW_COMPONENTS_TABS_H