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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_SHAPE_OVERLAY_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_SHAPE_OVERLAY_MODIFIER_H

#include <optional>
#include <vector>

#include "base/memory/ace_type.h"
#include "core/components_ng/base/modifier.h"

namespace OHOS::Ace::NG {
class Pattern;

class ShapeOverlayModifier : public OverlayModifier {
    DECLARE_ACE_TYPE(ShapeOverlayModifier, OverlayModifier)

public:
    static constexpr double SHAPE_OVERLAY_SIZE_DEFAULT = 4096.0f;
    static constexpr double SHAPE_OVERLAY_SIZE_FACTOR = 1000.0f;

    ShapeOverlayModifier() = default;
    ~ShapeOverlayModifier() override = default;
    void onDraw(DrawingContext& drawingContext) override;

private:

    ACE_DISALLOW_COPY_AND_MOVE(ShapeOverlayModifier);
};
} // namespace OHOS::Ace::NG

#endif