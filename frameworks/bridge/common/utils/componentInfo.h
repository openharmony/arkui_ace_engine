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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_UTILS_COMPONENTINFO_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_UTILS_COMPONENTINFO_H

#include "base/geometry/matrix4.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/geometry/rect.h"

namespace OHOS::Ace::NG {
struct TranslateOption {
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
};
struct ScaleOption {
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    double centerX = 0.0;
    double centerY = 0.0;
};
struct RotateOption {
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    double angle = 0.0;
    double centerX = 0.0;
    double centerY = 0.0;
};
struct Rectangle {
    SizeF size;
    OffsetF localOffset;
    OffsetF windowOffset;
    Rect screenRect;
    TranslateOption translate;
    ScaleOption scale;
    RotateOption rotate;
    Matrix4 matrix4;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_UTILS_COMPONENTINFO_H
