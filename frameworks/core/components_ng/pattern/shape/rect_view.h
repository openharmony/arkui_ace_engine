/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_RECT_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_RECT_VIEW_H

#include <string>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/radius.h"
#include "base/utils/macros.h"
#include "core/components/common/properties/animation_option.h"
#include "core/components/common/properties/color.h"


namespace OHOS::Ace::NG {

class ACE_EXPORT RectView {
public:
    static void Create();
    static void SetRadiusWidth(const Dimension& value);
    static void SetRadiusHeight(const Dimension& value);
    static void SetTopLeftRadius(const Radius& topLeftRadius);
    static void SetTopRightRadius(const Radius& topRightRadius);
    static void SetBottomRightRadius(const Radius& bottomRightRadius);
    static void SetBottomLeftRadius(const Radius& bottomLeftRadius);
private:
    static void UpdateRadius(const Radius& radius);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_RECT_VIEW_H