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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MAGNIFIER_PAINTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MAGNIFIER_PAINTER_H

#include <vector>
#include <memory>
#include "base/memory/referenced.h"
#include "base/memory/type_info_base.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/text_drag/text_drag_pattern.h"
#include "core/components_ng/pattern/select_overlay/magnifier_controller.h"
#include "core/components_ng/render/drawing_forward.h"
#include "core/components/common/properties/shadow.h"

namespace OHOS::Ace::NG {

class MagnifierPainter : public virtual AceType {
    DECLARE_ACE_TYPE(MagnifierPainter, AceType);

public:
    MagnifierPainter(const WeakPtr<Pattern>& pattern);
    void PaintMagnifier(RSCanvas& canvas);

private:
    bool GetMagnifierRect(MagnifierRect& rect);
    bool GetMagnifierRect(
        float& startX, float& startY, float& endX, float& endY, float& localOffsetX, float& cursorOffsetY);
    std::vector<TextPoint> GetTextPoints(const MagnifierRect& rect, bool haveOffset);
    std::vector<TextPoint> GetTextPoints(
        float startX, float startY, float endX, float endY, bool haveOffset);
    std::shared_ptr<RSPath> GetPathByPoints(const std::vector<TextPoint>& points);
    void PaintShadow(const RSPath& path, const Shadow& shadow, RSCanvas& canvas);

    WeakPtr<Pattern> pattern_;
    MagnifierRect magnifierRect_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MAGNIFIER_PAINTER_H