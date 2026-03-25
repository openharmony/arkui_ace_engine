/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components/common/properties/motion_path_evaluator.h"

namespace OHOS::Ace {
MotionPathEvaluator::MotionPathEvaluator(
    const MotionPathOption& option, const Offset& start, const Offset& end, PositionType type)
    : motionPathOption_(option), startPoint_(start), endPoint_(end), positionType_(type)
{}

DimensionOffset DimensionOffsetEvaluator::Evaluate(
    const DimensionOffset& start, const DimensionOffset& end, float fraction)
{
    return DimensionOffset();
}

float RotateEvaluator::Evaluate(const float& start, const float& end, float fraction)
{
    return 0.0f;
}
} // namespace OHOS::Ace
