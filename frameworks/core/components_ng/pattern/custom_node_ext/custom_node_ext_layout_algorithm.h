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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CUSTOM_NODE_EXT_CUSTOM_NODE_EXT_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CUSTOM_NODE_EXT_CUSTOM_NODE_EXT_LAYOUT_ALGORITHM_H

#include "base/geometry/ng/rect_t.h"
#include "core/components_ng/layout/box_layout_algorithm.h"

namespace OHOS::Ace::NG {

class CustomNodeExtLayoutAlgorithm : public BoxLayoutAlgorithm {
    DECLARE_ACE_TYPE(CustomNodeExtLayoutAlgorithm, BoxLayoutAlgorithm);
public:
    CustomNodeExtLayoutAlgorithm() = default;
    CustomNodeExtLayoutAlgorithm(const std::function<void(LayoutConstraintF constraints)>& measureCallback,
        const std::function<void(RectF rect)>& layoutCallback_)
        : measureCallback_(measureCallback), layoutCallback_(layoutCallback_) {}
    ~CustomNodeExtLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

private:
    std::function<void(LayoutConstraintF constraints)> measureCallback_;
    std::function<void(RectF rect)> layoutCallback_;
};
}

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CUSTOM_NODE_EXT_CUSTOM_NODE_EXT_LAYOUT_ALGORITHM_H