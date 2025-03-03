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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_LAYOUT_BOX_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_LAYOUT_BOX_LAYOUT_ALGORITHM_H

#include "ui/base/macros.h"
#include "ui/view/frame_node.h"
#include "ui/view/layout/layout_algorithm.h"
namespace OHOS::Ace::Kit {
class ACE_FORCE_EXPORT BoxLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(BoxLayoutAlgorithm, LayoutAlgorithm);

public:
    explicit BoxLayoutAlgorithm(const WeakPtr<FrameNode>& host) : LayoutAlgorithm(host) {}
    ~BoxLayoutAlgorithm() = default;

    void Measure(const Kit::LayoutConstraintInfo& contentConstraint) override;

    void Layout() override;

    std::optional<NG::SizeF> MeasureContent(const NG::LayoutConstraintT<float>& contentConstraint) override;

    // Called to perform measure current render node.
    static void PerformMeasureSelf(FrameNode* frameNode);

    // Called to perform layout render node.
    static void PerformLayout(FrameNode* frameNode);

    // Called to perform measure current render node.
    static void PerformMeasureSelfWithChildList(FrameNode* frameNode);
};
} // namespace OHOS::Ace::Kit

#endif
