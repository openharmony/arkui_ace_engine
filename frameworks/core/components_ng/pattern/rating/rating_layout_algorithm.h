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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RATING_RATING_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RATING_RATING_LAYOUT_ALGORITHM_H

#include "base/geometry/ng/size_t.h"
#include "core/components_ng/image_provider/image_loading_context.h"
#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT RatingLayoutAlgorithm : public BoxLayoutAlgorithm {
    DECLARE_ACE_TYPE(RatingLayoutAlgorithm, BoxLayoutAlgorithm);

public:
    RatingLayoutAlgorithm();
    RatingLayoutAlgorithm(const RefPtr<ImageLoadingContext>& foregroundLoadingCtx,
        const RefPtr<ImageLoadingContext>& secondaryLoadingCtx, const RefPtr<ImageLoadingContext>& backgroundLoadingCtx)
        : foregroundLoadingCtx_(foregroundLoadingCtx), secondaryLoadingCtx_(secondaryLoadingCtx),
          backgroundLoadingCtx_(backgroundLoadingCtx)
    {}

    ~RatingLayoutAlgorithm() override = default;

    void OnReset() override
    {
        foregroundLoadingCtx_ = nullptr;
        secondaryLoadingCtx_ = nullptr;
        backgroundLoadingCtx_ = nullptr;
    }

    std::optional<SizeF> MeasureContent(
        const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper) override;

    void Layout(LayoutWrapper* layoutWrapper) override;

private:
    RefPtr<ImageLoadingContext> foregroundLoadingCtx_;
    RefPtr<ImageLoadingContext> secondaryLoadingCtx_;
    RefPtr<ImageLoadingContext> backgroundLoadingCtx_;

    ACE_DISALLOW_COPY_AND_MOVE(RatingLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RATING_RATING_LAYOUT_ALGORITHM_H
