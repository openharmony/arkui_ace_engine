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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MULTI_MENU_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MULTI_MENU_LAYOUT_ALGORITHM_H

#include "base/geometry/ng/offset_t.h"
#include "core/components_ng/pattern/menu/menu_layout_algorithm.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT MultiMenuLayoutAlgorithm : public MenuLayoutAlgorithm {
    DECLARE_ACE_TYPE(MultiMenuLayoutAlgorithm, MenuLayoutAlgorithm)
public:
    MultiMenuLayoutAlgorithm() = default;
    ~MultiMenuLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

    // if child has user defined width, reset 2c min width.
    static LayoutConstraintF ResetLayoutConstraintMinWidth(
        const RefPtr<LayoutWrapper>& child, const LayoutConstraintF& layoutConstraint);

private:
    void UpdateEmbeddedPercentReference(LayoutWrapper* layoutWrapper, LayoutConstraintF& childConstraint,
        std::optional<LayoutConstraintF>& layoutConstraint);
    void UpdateSelfSize(LayoutWrapper* layoutWrapper, LayoutConstraintF& childConstraint,
        std::optional<LayoutConstraintF>& layoutConstraint);
    void UpdateConstraintBaseOnMenuItems(LayoutWrapper* layoutWrapper, LayoutConstraintF& constraint);
    float GetChildrenMaxWidth(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint);
    void UpdateMenuDefaultConstraintByDevice(const RefPtr<MenuPattern>& pattern,
        LayoutConstraintF& childConstraint, float paddingWidth, std::optional<LayoutConstraintF>& layoutConstraint,
        bool idealSizeHasVal);

    float userHeight_ = 0.0f;
    
    ACE_DISALLOW_COPY_AND_MOVE(MultiMenuLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MULTI_MENU_LAYOUT_ALGORITHM_H
