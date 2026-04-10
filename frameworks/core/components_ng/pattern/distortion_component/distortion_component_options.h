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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DISTORTION_COMPONENT_DISTORTION_COMPONENT_OPTIONS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DISTORTION_COMPONENT_DISTORTION_COMPONENT_OPTIONS_H

#include <utility>

#include "ui/base/macros.h"

namespace OHOS::Ace::NG {

struct DistortionParam {
    DistortionParam() = default;
    VectorF luCorner { 0.0f, 0.0f };
    VectorF ruCorner { 0.0f, 0.0f };
    VectorF lbCorner { 0.0f, 0.0f };
    VectorF rbCorner { 0.0f, 0.0f };
    Vector4F barrelDistortion { 0.0f, 0.0f, 0.0f, 0.0f };
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DISTORTION_COMPONENT_DISTORTION_COMPONENT_OPTIONS_H