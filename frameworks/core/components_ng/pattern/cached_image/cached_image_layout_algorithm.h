/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2023-2023. All rights reserved.
 */

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CACHED_IMAGE_CACHED_IMAGE_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CACHED_IMAGE_CACHED_IMAGE_LAYOUT_ALGORITHM_H

#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"

namespace OHOS::Ace::NG {

using LayoutDoneFunc = std::function<void(const SizeF&)>;

class ACE_EXPORT CachedImageLayoutAlgorithm : public BoxLayoutAlgorithm {
    DECLARE_ACE_TYPE(CachedImageLayoutAlgorithm, BoxLayoutAlgorithm);

public:
    CachedImageLayoutAlgorithm() = default;
    ~CachedImageLayoutAlgorithm() override = default;

    std::optional<SizeF> MeasureContent(
        const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper) override;

    void Layout(LayoutWrapper* layoutWrapper) override;

    const RectF& GetSrcRect() const
    {
        return srcRect_;
    }

    const RectF& GetDstRect() const
    {
        return dstRect_;
    }

    std::optional<SizeF> GetSourceSize() const;

    void RegisterLayoutCallback(const LayoutDoneFunc& callback);

    void SetImageSize(const SizeF& imageSize) {
        imageSize_ = imageSize;
    }

private:
    int32_t RoundUp(int32_t value);
    SizeF CalculateTargetSize(const SizeF& srcSize, const SizeF& dstSize, const SizeF& rawImageSize);

    bool isSizeChanging(const SizeF& dstSize)
    {
        return dstSize_.IsPositive() && dstSize != dstSize_;
    }

    void CallbackTargetSize();
    void CallbackTargetSizeIfNeed(const SizeF& dstSize, bool autoResize, ImageFit imageFit,
        const std::optional<SizeF>& sourceSize = std::nullopt);

    LayoutDoneFunc layoutDoneCallback_;
    bool isAutoResize_{true};
    RectF srcRect_{RectF()};
    RectF dstRect_{RectF()};
    SizeF dstSize_;
    SizeF imageSize_{-1.0, -1.0};
    ImageFit imageFit_{ImageFit::COVER};

    // to determine whether the image needs to be reloaded
    int32_t sizeLevel_{-1};
    std::unique_ptr<SizeF> sourceSizePtr_ = nullptr;

    ACE_DISALLOW_COPY_AND_MOVE(CachedImageLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CACHED_IMAGE_CACHED_IMAGE_PATTERN_H