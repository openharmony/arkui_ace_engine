/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MAGNIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MAGNIFIER_H

#include "base/memory/referenced.h"
#include "base/memory/type_info_base.h"
#include "core/components_ng/pattern/select_overlay/magnifier_controller.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension MAGNIFIER_WIDTH = 112.0_vp;
constexpr Dimension MAGNIFIER_HEIGHT = 72.0_vp;
constexpr Dimension MAGNIFIER_OFFSETX = 0.0_vp;
constexpr Dimension MAGNIFIER_OFFSETY = 80.0_vp;
constexpr Dimension MAGNIFIER_BORDERWIDTH = 2.0_vp;
constexpr Dimension MAGNIFIER_CORNERRADIUS = 36.0_vp;

constexpr Dimension MAGNIFIER_SHADOWOFFSETX = 0.0_vp;
constexpr Dimension MAGNIFIER_SHADOWOFFSETY = 8.0_vp;
constexpr Dimension MAGNIFIER_SHADOWSIZE = 10.0_vp;
constexpr float MAGNIFIER_FACTOR = 1.4f;
constexpr float MAGNIFIER_SHADOWSTRENGTH = 0.08f;
constexpr int32_t ANIMATION_DURATION_150 = 150;
} // namespace
class Magnifier : public virtual AceType {
    DECLARE_ACE_TYPE(Magnifier, AceType);

public:
    RefPtr<MagnifierController> GetMagnifierController()
    {
        return magnifierController_;
    }
    RefPtr<MagnifierController> magnifierController_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MAGNIFIER_H