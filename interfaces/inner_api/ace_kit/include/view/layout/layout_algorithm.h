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

#include "interfaces/inner_api/ace_kit/include/base/ace_type.h"
#include "interfaces/inner_api/ace_kit/include/base/referenced.h"
#include "interfaces/inner_api/ace_kit/include/view/frame_node.h"

namespace OHOS::Ace::NG {
template<class T>
struct LayoutConstraintT;
}

namespace OHOS::AceKit {
class LayoutAlgorithmFunc : public Ace::AceType {
    DECLARE_ACE_TYPE(LayoutAlgorithmFunc, Ace::AceType);

public:
    LayoutAlgorithmFunc(std::function<void(FrameNode*)>&& measureFunc, std::function<void(FrameNode*)>&& layoutFunc,
        std::function<void(const Ace::NG::LayoutConstraintT<float>&, FrameNode*)>&& measureContentFunc,
        const Ace::WeakPtr<FrameNode>& host)
        : measureFunc_(std::move(measureFunc)), layoutFunc_(std::move(layoutFunc)),
          measureContentFunc_(std::move(measureContentFunc)), host_(host)
    {}
    ~LayoutAlgorithmFunc() = default;

    void FireMeasure()
    {
        auto host = host_.Upgrade();
        if (host && measureFunc_) {
            measureFunc_(Ace::Referenced::RawPtr(host));
        }
    }

    void FireLayout()
    {
        auto host = host_.Upgrade();
        if (host && layoutFunc_) {
            layoutFunc_(Ace::Referenced::RawPtr(host));
        }
    }

    void FireMeasureContent(const Ace::NG::LayoutConstraintT<float>& LayoutConstraint)
    {
        auto host = host_.Upgrade();
        if (host && measureContentFunc_) {
            measureContentFunc_(LayoutConstraint, Ace::Referenced::RawPtr(host));
        }
    }

private:
    std::function<void(FrameNode*)> measureFunc_;
    std::function<void(FrameNode*)> layoutFunc_;
    std::function<void(const Ace::NG::LayoutConstraintT<float>&, FrameNode*)> measureContentFunc_;
    Ace::WeakPtr<FrameNode> host_;
};

class LayoutAlgorithm : public Ace::AceType {
    DECLARE_ACE_TYPE(LayoutAlgorithm, Ace::AceType);

public:
    explicit LayoutAlgorithm(const Ace::RefPtr<LayoutAlgorithmFunc>& layoutAlgorithmFunc)
        : layoutAlgorithmFunc_(layoutAlgorithmFunc)
    {}
    virtual ~LayoutAlgorithm() = default;

    static Ace::RefPtr<LayoutAlgorithm> InitializeLayoutAlgorithm(
        const Ace::RefPtr<LayoutAlgorithmFunc>& layoutAlgorithmFunc);

    void Measure()
    {
        if (layoutAlgorithmFunc_) {
            layoutAlgorithmFunc_->FireMeasure();
        }
    }

    void Layout()
    {
        if (layoutAlgorithmFunc_) {
            layoutAlgorithmFunc_->FireLayout();
        }
    }

    void MeasureContent(const Ace::NG::LayoutConstraintT<float>& contentConstraint)
    {
        if (layoutAlgorithmFunc_) {
            layoutAlgorithmFunc_->FireMeasureContent(contentConstraint);
        }
    }

private:
    Ace::RefPtr<LayoutAlgorithmFunc> layoutAlgorithmFunc_;
};
} // namespace OHOS::AceKit

#endif
