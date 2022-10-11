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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_LAYOUT_ALGORITHM_H

#include "base/geometry/ng/offset_t.h"
#include "core/components_ng/layout/layout_algorithm.h"

namespace OHOS::Ace::NG {
class MenuLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(MenuLayoutAlgorithm, LayoutAlgorithm)
public:
    MenuLayoutAlgorithm() = default;
    ~MenuLayoutAlgorithm() override = default;

    // override measureSelf and measureChildren.
    void Measure(LayoutWrapper* layoutWrapper) override;

    void Layout(LayoutWrapper* layoutWrapper) override;

private:
    void Initialize(LayoutWrapper* layoutWrapper);

    float VerticalLayout(const SizeF& size, float clickPosition);
    float HorizontalLayout(const SizeF& size, float clickPosition);

    SizeF screenSize_;
    OffsetF position_;

    ACE_DISALLOW_COPY_AND_MOVE(MenuLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_LAYOUT_ALGORITHM_H