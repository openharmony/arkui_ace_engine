/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/animation/curves.h"

namespace OHOS::Ace {
const RefPtr<DecelerationCurve> Curves::DECELE = nullptr;
const RefPtr<LinearCurve> Curves::LINEAR = nullptr;
const RefPtr<SineCurve> Curves::SINE = nullptr;
const RefPtr<CubicCurve> Curves::EASE = nullptr;
const RefPtr<CubicCurve> Curves::EASE_IN = nullptr;
const RefPtr<CubicCurve> Curves::EASE_OUT = nullptr;
const RefPtr<CubicCurve> Curves::EASE_IN_OUT = nullptr;
const RefPtr<CubicCurve> Curves::FAST_OUT_SLOW_IN = nullptr;
const RefPtr<CubicCurve> Curves::LINEAR_OUT_SLOW_IN = nullptr;
const RefPtr<CubicCurve> Curves::FAST_OUT_LINEAR_IN = nullptr;
const RefPtr<CubicCurve> Curves::FRICTION = nullptr;
const RefPtr<CubicCurve> Curves::EXTREME_DECELERATION = nullptr;
const RefPtr<CubicCurve> Curves::SHARP = nullptr;
const RefPtr<CubicCurve> Curves::RHYTHM = nullptr;
const RefPtr<CubicCurve> Curves::SMOOTH = nullptr;
const RefPtr<AnticipateCurve> Curves::ANTICIPATE = nullptr;
const RefPtr<CubicCurve> Curves::MAGNETIC = nullptr;
const RefPtr<ElasticsCurve> Curves::ELASTICS = nullptr;
const std::string Curves::DEFAULT_CURVE_NAME = "default";

std::string Curves::ToString(const RefPtr<Curve>& curve)
{
    (void)curve;
    return DEFAULT_CURVE_NAME;
}
} // namespace OHOS::Ace
