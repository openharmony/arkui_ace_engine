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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_PATTERN_MAGNIFIER_CONTROLLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_PATTERN_MAGNIFIER_CONTROLLER_H

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/image/pixel_map.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/render/drawing.h"
#include "frameworks/base/memory/referenced.h"

namespace OHOS::Ace::NG {
struct MagnifierRect {
    bool isChildNode = false;
    int32_t childNodeId = 0;
    float startX = 0.0f;
    float startY = 0.0f;
    float endX = 0.0f;
    float endY = 0.0f;
    OffsetF localOffset;
    OffsetF cursorOffset;
    SizeF contentSize;
    OffsetF contentOffset;
    RefPtr<PixelMap> pixelMap = nullptr;
    WeakPtr<Pattern> parent = nullptr;
};

class MagnifierController : public virtual AceType {
    DECLARE_ACE_TYPE(MagnifierController, AceType);

public:
    explicit MagnifierController(const WeakPtr<Pattern>& pattern) : pattern_(pattern) {}
    ~MagnifierController() override = default;

    void OpenMagnifier();
    void CloseMagnifier();

private:
    void CreateMagnifierChildNode();
    void SetMagnifierRect(const RefPtr<Pattern>& childPattern);

    bool haveChildNode_ = false;
    WeakPtr<Pattern> pattern_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_PATTERN_MAGNIFIER_CONTROLLER_H
