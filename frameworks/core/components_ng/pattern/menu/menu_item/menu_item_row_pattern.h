/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_ITEM_MENU_ITEM_ROW_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_ITEM_MENU_ITEM_ROW_PATTERN_H

#include <optional>

#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT MenuItemRowLayoutAlgorithm : public LinearLayoutAlgorithm {
    DECLARE_ACE_TYPE(MenuItemRowLayoutAlgorithm, LinearLayoutAlgorithm);

public:
    MenuItemRowLayoutAlgorithm() = default;
    ~MenuItemRowLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override {};

    ACE_DISALLOW_COPY_AND_MOVE(MenuItemRowLayoutAlgorithm);
};

class MenuItemRowPattern : public LinearLayoutPattern {
    DECLARE_ACE_TYPE(MenuItemRowPattern, LinearLayoutPattern);

public:
    MenuItemRowPattern() : LinearLayoutPattern(false) {};
    ~MenuItemRowPattern() override = default;

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<MenuItemRowLayoutAlgorithm>();
    }

    ACE_DISALLOW_COPY_AND_MOVE(MenuItemRowPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_ITEM_MENU_ITEM_ROW_PATTERN_H
