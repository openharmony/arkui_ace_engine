/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "base/geometry/dimension.h"

namespace OHOS::Ace {
double Dimension::ConvertToVp() const
{
    return value_;
}

double Dimension::ConvertToPx() const
{
    return value_;
}

double Dimension::ConvertToFp() const
{
    return value_;
}

double Dimension::ConvertToPxWithSize(double size) const
{
    if (unit_ == DimensionUnit::PERCENT) {
        return size * value_ / 100.0;
    }
    return value_;
}

DimensionUnit Dimension::GetAdaptDimensionUnit(const Dimension& dimension)
{
    (void)dimension;
    return unit_;
}

double Dimension::ConvertToPxDistribute(
    std::optional<float> minOptional, std::optional<float> maxOptional, bool allowScale) const
{
    (void)minOptional;
    (void)maxOptional;
    (void)allowScale;
    return ConvertToPx();
}

double Dimension::ConvertToPxByCustomFontScale(float minFontScale, float maxFontScale) const
{
    (void)minFontScale;
    (void)maxFontScale;
    return ConvertToPx();
}

double Dimension::ConvertToPxByAppFontScale(float minFontScale) const
{
    (void)minFontScale;
    return ConvertToPx();
}

double Dimension::ConvertToVpByAppFontScale() const
{
    return ConvertToVp();
}

std::string Dimension::ToString() const
{
    return std::to_string(value_);
}

Dimension Dimension::FromString(const std::string& str)
{
    (void)str;
    return Dimension();
}

bool Dimension::NormalizeToPx(double vpScale, double fpScale, double lpxScale, double parentLength, double& result) const
{
    (void)vpScale;
    (void)fpScale;
    (void)lpxScale;
    if (unit_ == DimensionUnit::PERCENT) {
        result = parentLength * value_ / 100.0;
    } else {
        result = value_;
    }
    return true;
}
} // namespace OHOS::Ace
