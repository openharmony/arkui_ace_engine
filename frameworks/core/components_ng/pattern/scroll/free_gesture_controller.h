// /*
//  * Copyright (c) 2025 Huawei Device Co., Ltd.
//  * Licensed under the Apache License, Version 2.0 (the "License");
//  * you may not use this file except in compliance with the License.
//  * You may obtain a copy of the License at
//  *
//  *     http://www.apache.org/licenses/LICENSE-2.0
//  *
//  * Unless required by applicable law or agreed to in writing, software
//  * distributed under the License is distributed on an "AS IS" BASIS,
//  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  * See the License for the specific language governing permissions and
//  * limitations under the License.
//  */
// #ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_FREE_GESTURE_CONTROLLER_H
// #define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_FREE_GESTURE_CONTROLLER_H

// #include "core/components_ng/scroll_pattern.h"
// #include "core/components_ng/base/modifier.h"

// namespace OHOS::Ace::NG {
// class FreeGestureController {
//     public:
//     FreeGestureController() {}
//     OffsetF GetOffset() const {
//         return offset_;
//     }
//     void Reset() {
//         freePanGesture_.Reset();
//         offset_.Reset();
//     }

//     void InitTouch() {
//         OnTouchUp(() => {
//             // check if out of bounds, if out of bounds, do spring animation
//         });
//         OnTouchDown(()=> {
//             // StopAnimation
//         })
//     }
// void InitFreeScroll()
// {
//     if (freePanGesture_) {
//         return;
//     }
//     offset_ = MakeRefPtr<AnimatablePropertyOffsetF>();

//     PanDirection panDirection { .type = PanDirection::ALL };
//     double distance = SystemProperties::GetScrollableDistance();
//     PanDistanceMap distanceMap;
//     if (Positive(distance)) {
//         distanceMap[SourceTool::UNKNOWN] = distance;
//     } else {
//         distanceMap[SourceTool::UNKNOWN] = DEFAULT_PAN_DISTANCE.ConvertToPx();
//         distanceMap[SourceTool::PEN] = DEFAULT_PEN_PAN_DISTANCE.ConvertToPx();
//     }
//     freePanGesture_ = AceType::MakeRefPtr<NG::PanRecognizer>(DEFAULT_PAN_FINGER, panDirection, distanceMap);
//     freePanGesture_->SetOnActionUpdate([this](const GestureEvent& event) {
//         offset_ += event.GetDelta();
//         auto host = GetHost();
//         host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
//     });
//     freePanGesture_->SetOnActionEnd([this](const GestureEvent& event) {
//         auto velocity = event.GetVelocity();
//         float finalPosition = offset_ + correctVelocity / (friction * -FRICTION_SCALE);
//     AnimationOption option;
//     option.SetCurve(curve);
//     option.SetDuration(CUSTOM_SPRING_ANIMATION_DURATION);
//     option.SetFinishCallbackType(FinishCallbackType::LOGICALLY);
//         offset_->AnimateWithVelocity();
//     });
// }
// private:
//     // ScrollPattern& scroll_;
//     RefPtr<PanRecognizer> freePanGesture_; // all-direction pan recognizer for free scroll mode
//     RefPtr<AnimatablePropertyOffsetF> offset_;
// };
// }
// #endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_FREE_GESTURE_CONTROLLER_H
