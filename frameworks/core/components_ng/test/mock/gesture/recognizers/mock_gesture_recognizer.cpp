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

#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"

namespace OHOS::Ace::NG {
bool NGGestureRecognizer::HandleEvent(const TouchEvent& /* point */)
{
    return true;
}

bool NGGestureRecognizer::HandleEvent(const AxisEvent& /* event */)
{
    return true;
}

std::unordered_map<int, TransformConfig>& NGGestureRecognizer::GetGlobalTransCfg()
{
    std::unordered_map<int, TransformConfig> transCfg {};
    return transCfg;
}

std::unordered_map<int, AncestorNodeInfo>& NGGestureRecognizer::GetGlobalTransIds()
{
    std::unordered_map<int, AncestorNodeInfo> transVid {};
    return transVid;
}

void NGGestureRecognizer::ResetGlobalTransCfg() {}

void NGGestureRecognizer::BatchAdjudicate(const RefPtr<NGGestureRecognizer>& recognizer, GestureDisposal disposal) {}

void NGGestureRecognizer::Transform(PointF& windowPointF, PointF& originPointF) {}

void NGGestureRecognizer::SetTransInfo(int id) {}
} // namespace OHOS::Ace::NG
