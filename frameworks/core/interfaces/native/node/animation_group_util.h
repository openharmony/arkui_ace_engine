/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_ANIMATION_GROUP_UTIL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_ANIMATION_GROUP_UTIL_H

#include <cstdint>
#include <functional>
#include <string>
#include <variant>
#include <vector>

#include "core/interfaces/arkoala/arkoala_api.h"
#include "interfaces/native/native_animate.h"
#include "interfaces/native/native_type.h"
#include "ui/animation/animation_option.h"
#include "ui/animation/curve.h"

namespace OHOS::Ace::NG {

// Framework-side view of one property animation child, with parent-child
// inheritance already resolved (curve falls back to the group curve when the
// child has none; duration falls back to the group duration or the default).
struct PropertyChildView {
    AnimationOption option;
    RefPtr<Curve> curve;
    OH_ArkUI_AnimationPropertyType propertyType = OH_ARKUI_ANIMATION_PROPERTY_TRANSLATION;
    std::vector<ArkUI_NumberValue> fromValue;
    std::vector<ArkUI_NumberValue> toValue;
};

// Framework-side view of one keyframe animation child. The implicit curve is
// the group curve (used to wrap the keyframe sequence); each keyframe's curve
// falls back to it. segmentDuration is precomputed from keyTime and the
// resolved (possibly inherited) total duration.
struct KeyframeChildView {
    struct Keyframe {
        int32_t segmentDuration = 0;
        float fraction = 0.0f;
        RefPtr<Curve> curve;
        std::vector<ArkUI_NumberValue> values;
    };
    AnimationOption option;
    RefPtr<Curve> implicitCurve;
    OH_ArkUI_AnimationPropertyType propertyType = OH_ARKUI_ANIMATION_PROPERTY_TRANSLATION;
    std::vector<Keyframe> keyframes;
};

// Framework-side view of one path animation child, inheritance resolved.
struct PathChildView {
    AnimationOption option;
    RefPtr<Curve> curve;
    std::string path;
    bool autoRotation = false;
};

using ChildView = std::variant<PropertyChildView, KeyframeChildView, PathChildView>;

// Framework-side view of the whole animation group. All C-API struct fields
// have been translated to framework types and all parent-child relationships
// (duration/curve inheritance, keyframe segment timing, group-level
// validation) have been resolved. The Rosen adapter consumes this view and
// only performs RSNode/AnimationUtils orchestration.
struct AnimationGroupView {
    AnimationOption option;
    RefPtr<Curve> curve;
    std::function<void()> onFinish;
    std::vector<ChildView> children;
};

// Builds an AnimationGroupView from an opaque C-API group handle.
// Resolves duration/curve inheritance, precomputes keyframe segment
// durations, and validates that no child uses a duration-independent curve.
// Returns ARKUI_ERROR_CODE_NO_ERROR on success, ARKUI_ERROR_CODE_PARAM_INVALID
// if the handle is null, or ARKUI_ERROR_CODE_SUB_ANIMATION_INVALID if a child
// uses a duration-independent curve.
ArkUI_ErrorCode BuildAnimationGroupView(ArkUIAnimationGroupHandle group, AnimationGroupView& out);

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_ANIMATION_GROUP_UTIL_H
