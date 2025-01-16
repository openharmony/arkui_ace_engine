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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_LAYOUT_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_LAYOUT_LAYOUT_ALGORITHM_H

#include <functional>
#include <optional>

#include "ui/base/ace_type.h"
#include "ui/base/geometry/ng/size_t.h"
#include "ui/base/referenced.h"
#include "ui/view/frame_node.h"

namespace OHOS::Ace::NG {
template<class T>
struct LayoutConstraintT;
}

namespace OHOS::Ace::Kit {

class LayoutAlgorithm : public AceType {
    DECLARE_ACE_TYPE(LayoutAlgorithm, AceType);

public:
    explicit LayoutAlgorithm(const WeakPtr<FrameNode>& host) : host_(host) {}
    virtual ~LayoutAlgorithm() = default;

    virtual void Measure() {}

    virtual void Layout() {}

    virtual std::optional<NG::SizeF> MeasureContent(const NG::LayoutConstraintT<float>& contentConstraint)
    {
        return std::nullopt;
    }

protected:
    WeakPtr<FrameNode> host_;
};

} // namespace OHOS::Ace::Kit

#endif
