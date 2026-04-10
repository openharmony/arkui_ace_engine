/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"

namespace OHOS::Ace::NG {
void BoxLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    (void)layoutWrapper;
}

void BoxLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    (void)layoutWrapper;
}

std::optional<SizeF> BoxLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    (void)contentConstraint;
    (void)layoutWrapper;
    return std::nullopt;
}

void BoxLayoutAlgorithm::PerformMeasureSelf(LayoutWrapper* layoutWrapper, bool isEnableChildrenMatchParent)
{
    (void)layoutWrapper;
    (void)isEnableChildrenMatchParent;
}

void BoxLayoutAlgorithm::PerformLayout(LayoutWrapper* layoutWrapper)
{
    (void)layoutWrapper;
}

void BoxLayoutAlgorithm::PerformMeasureSelfWithChildList(
    LayoutWrapper* layoutWrapper, const std::list<RefPtr<LayoutWrapper>>& childList, bool isEnableChildrenMatchParent)
{
    (void)layoutWrapper;
    (void)childList;
    (void)isEnableChildrenMatchParent;
}

std::optional<SizeF> BoxLayoutAlgorithm::PerformMeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    (void)contentConstraint;
    (void)layoutWrapper;
    return std::nullopt;
}

void BoxLayoutAlgorithm::MeasureAdaptiveLayoutChildren(LayoutWrapper* layoutWrapper, SizeF& frameSize)
{
    (void)layoutWrapper;
    (void)frameSize;
}

Alignment BoxLayoutAlgorithm::MapLocalizedToAlignment(std::string localizedAlignment)
{
    (void)localizedAlignment;
    return Alignment();
}

void BoxLayoutAlgorithm::CalcSingleSideMarginFrame(
    MarginPropertyF& margin, const OptionalSizeF& singleSideFrame, float& maxWidth, float& maxHeight)
{
    (void)margin;
    (void)singleSideFrame;
    (void)maxWidth;
    (void)maxHeight;
}
} // namespace OHOS::Ace::NG
