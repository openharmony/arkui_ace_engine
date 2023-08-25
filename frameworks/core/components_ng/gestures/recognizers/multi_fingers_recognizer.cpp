/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/gestures/recognizers/multi_fingers_recognizer.h"

#include "base/memory/ace_type.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DEFAULT_MAX_FINGERS = 10;
} // namespace

MultiFingersRecognizer::MultiFingersRecognizer(int32_t fingers)
{
    if (fingers > DEFAULT_MAX_FINGERS || fingers <= 0) {
        fingers_ = 1;
    } else {
        fingers_ = fingers;
    }
}

void MultiFingersRecognizer::UpdateFingerListInfo(const Offset& coordinateOffset)
{
    fingerList_.clear();
    for (const auto& point : touchPoints_) {
        Offset localLocation = point.second.GetOffset() - coordinateOffset;
        FingerInfo fingerInfo = { point.first, point.second.GetOffset(), localLocation, point.second.sourceType,
            point.second.sourceTool };
        fingerList_.emplace_back(fingerInfo);
    }
}

} // namespace OHOS::Ace::NG
