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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_SHEET_POPUP_SHAPE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_SHEET_POPUP_SHAPE_H

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "core/components/common/properties/placement.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/property/border_property.h"

namespace OHOS::Rosen {
class RSNGShapeBase;
} // namespace OHOS::Rosen

namespace OHOS::Ace::NG {
class SheetPopupShape {
public:
    static std::shared_ptr<OHOS::Rosen::RSNGShapeBase> DrawClipPathBottomSDF(const SizeF& sheetSize,
        const NG::BorderRadiusProperty& sheetRadius, const SheetArrowPosition arrowPosition,
        const OffsetF& arrowOffset);
    static std::shared_ptr<OHOS::Rosen::RSNGShapeBase> DrawClipPathTopSDF(const SizeF& sheetSize,
        const NG::BorderRadiusProperty& sheetRadius, const SheetArrowPosition arrowPosition,
        const OffsetF& arrowOffset);
    static std::shared_ptr<OHOS::Rosen::RSNGShapeBase> DrawClipPathLeftSDF(const SizeF& sheetSize,
        const NG::BorderRadiusProperty& sheetRadius, const SheetArrowPosition arrowPosition,
        const OffsetF& arrowOffset);
    static std::shared_ptr<OHOS::Rosen::RSNGShapeBase> DrawClipPathRightSDF(const SizeF& sheetSize,
        const NG::BorderRadiusProperty& sheetRadius, const SheetArrowPosition arrowPosition,
        const OffsetF& arrowOffset);
    static std::shared_ptr<OHOS::Rosen::RSNGShapeBase> GetPopupStyleSheetClipPathSDF(const SizeF& sheetSize,
        const NG::BorderRadiusProperty& sheetRadius, const Placement placement, const SheetArrowPosition arrowPosition,
        const OffsetF& arrowOffset);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_SHEET_POPUP_SHAPE_H