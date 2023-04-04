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

#include <list>

#include "base/geometry/ng/offset_t.h"
#include "base/memory/referenced.h"
#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/layout/layout_algorithm.h"

namespace OHOS::Ace::NG {
class MenuLayoutAlgorithm : public BoxLayoutAlgorithm {
    DECLARE_ACE_TYPE(MenuLayoutAlgorithm, BoxLayoutAlgorithm)
public:
    MenuLayoutAlgorithm() = default;
    ~MenuLayoutAlgorithm() override = default;

    // override measureSelf and measureChildren.
    void Measure(LayoutWrapper* layoutWrapper) override;

    void Layout(LayoutWrapper* layoutWrapper) override;

protected:
    float VerticalLayout(const SizeF& size, float clickPosition);
    float HorizontalLayout(const SizeF& size, float clickPosition, bool IsSelectMenu = false);

    OffsetF position_;

private:
    void Initialize(LayoutWrapper* layoutWrapper);
    LayoutConstraintF CreateChildConstraint(LayoutWrapper* layoutWrapper);
    void UpdateConstraintWidth(LayoutWrapper* layoutWrapper, LayoutConstraintF& constraint);
    void UpdateConstraintHeight(LayoutWrapper* layoutWrapper, LayoutConstraintF& constraint);
    void UpdateConstraintBaseOnOptions(LayoutWrapper* layoutWrapper, LayoutConstraintF& constraint);
    void UpdateOptionConstraint(std::list<RefPtr<LayoutWrapper>>& options, float width);
    void UpdateConstraintBaseOnMenuItems(LayoutWrapper* layoutWrapper, LayoutConstraintF& constraint);

    void LayoutSubMenu(LayoutWrapper* layoutWrapper);
    float VerticalLayoutSubMenu(const SizeF& size, float position, const SizeF& menuItemSize);
    float HorizontalLayoutSubMenu(const SizeF& size, float position, const SizeF& menuItemSize);

    float GetChildrenMaxWidth(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint);

    // get option LayoutWrapper for measure get max width
    std::list<RefPtr<LayoutWrapper>> GetOptionsLayoutWrappper(LayoutWrapper* layoutWrapper);

    SizeF wrapperSize_;

    // current page offset relative to window.
    OffsetF pageOffset_;
    float topSpace_ = 0.0f;
    float bottomSpace_ = 0.0f;
    float leftSpace_ = 0.0f;
    float rightSpace_ = 0.0f;

    float margin_ = 0.0f;
    float optionPadding_ = 0.0f;

    ACE_DISALLOW_COPY_AND_MOVE(MenuLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_LAYOUT_ALGORITHM_H
