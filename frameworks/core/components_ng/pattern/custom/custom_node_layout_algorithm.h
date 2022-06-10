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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_CUSTOM_NODE_LAYOUR_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_CUSTOM_NODE_LAYOUR_ALGORITHM_H

#include <string>

#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"

namespace OHOS::Ace::NG {

using RenderFunction = std::function<RefPtr<FrameNode>()>;

// CustomNodeLayoutAlgorithm acts as the underlying @component view.
class ACE_EXPORT CustomNodeLayoutAlgorithm : public BoxLayoutAlgorithm {
    DECLARE_ACE_TYPE(CustomNodeLayoutAlgorithm, BoxLayoutAlgorithm);

public:
    CustomNodeLayoutAlgorithm(const RenderFunction& renderFunction) : renderFunction_(renderFunction) {}

    ~CustomNodeLayoutAlgorithm() override = default;

    void OnReset() override
    {
        renderFunction_ = nullptr;
    }

    void Measure(LayoutWrapper* layoutWrapper) override;

private:
    RenderFunction renderFunction_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_CUSTOM_NODE_LAYOUR_ALGORITHM_H
