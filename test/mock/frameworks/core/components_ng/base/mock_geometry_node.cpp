/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/components_ng/base/geometry_node.h"

namespace OHOS::Ace::NG {
RectF GeometryNode::GetFrameRect(bool withSafeArea) const
{
    (void)withSafeArea;
    return frame_.rect_;
}

SizeF GeometryNode::GetFrameSize(bool withSafeArea) const
{
    (void)withSafeArea;
    return frame_.rect_.GetSize();
}

OffsetF GeometryNode::GetFrameOffset(bool withSafeArea) const
{
    (void)withSafeArea;
    return frame_.rect_.GetOffset();
}

void GeometryNode::SetMarginFrameOffset(const OffsetF& translate)
{
    frame_.rect_.SetOffset(translate);
}

RectF GeometryNode::GetParentAdjust() const
{
    return {};
}
} // namespace OHOS::Ace::NG
