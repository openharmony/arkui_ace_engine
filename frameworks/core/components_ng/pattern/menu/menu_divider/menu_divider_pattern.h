/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_DIVIDER_MENU_DIVIDER_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_DIVIDER_MENU_DIVIDER_PATTERN_H

#include "core/components_ng/pattern/menu/menu_divider/menu_divider_layout_algorithm.h"
#include "core/components_ng/pattern/menu/menu_divider/menu_divider_paint_method.h"
#include "core/components_ng/pattern/menu/menu_divider/menu_divider_paint_property.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
class MenuDividerPattern : public Pattern {
    DECLARE_ACE_TYPE(MenuDividerPattern, Pattern);

public:
    MenuDividerPattern() = default;
    ~MenuDividerPattern() override = default;

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<MenuDividerPaintProperty>();
    }

    void BindMenuItem(WeakPtr<FrameNode> menuItemWk)
    {
        menuItemWk_ = menuItemWk;
        auto item = menuItemWk.Upgrade();
        isOption_ = item && item->GetTag() == V2::OPTION_ETS_TAG;
    }

    RefPtr<FrameNode> GetMenuItem()
    {
        return menuItemWk_.Upgrade();
    }

    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

private:
    WeakPtr<FrameNode> menuItemWk_ = nullptr;
    RefPtr<MenuDividerPaintMethod> paintMethod_ = nullptr;
    bool isOption_ = false;
    ACE_DISALLOW_COPY_AND_MOVE(MenuDividerPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIVIDER_DIVIDER_PATTERN_H
