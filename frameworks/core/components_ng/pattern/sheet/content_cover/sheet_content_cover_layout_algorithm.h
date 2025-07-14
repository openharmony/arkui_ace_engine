/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef CORE_COMPONENTS_NG_PATTERN_SHEET_CONTENT_COVER_SHEET_CONTENT_COVER_LAYOUT_ALGORITHM_H
#define CORE_COMPONENTS_NG_PATTERN_SHEET_CONTENT_COVER_SHEET_CONTENT_COVER_LAYOUT_ALGORITHM_H

#include "core/components_ng/layout/box_layout_algorithm.h"

namespace OHOS::Ace::NG {

class SheetPresentationPattern;

class ACE_EXPORT SheetContentCoverLayoutAlgorithm : public BoxLayoutAlgorithm {
    DECLARE_ACE_TYPE(SheetContentCoverLayoutAlgorithm, LayoutAlgorithm);

public:
    SheetContentCoverLayoutAlgorithm() = default;
    ~SheetContentCoverLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

    void MeasureOperation(RefPtr<SheetPresentationPattern> sheetPattern, LayoutConstraintF constraint);
    void MeasureDragBar(RefPtr<SheetPresentationPattern> sheetPattern, LayoutConstraintF constraint);
    void MeasureCloseIcon(RefPtr<SheetPresentationPattern> sheetPattern, LayoutConstraintF constraint);
    void MeasureScrollNode(LayoutWrapper* layoutWrapper, LayoutConstraintF constraint);

    void LayoutTitleBuilder(const NG::OffsetF& translate, LayoutWrapper* layoutWrapper);
    void LayoutDragBar(const NG::OffsetF& translate, LayoutWrapper* layoutWrapper);
    void LayoutCloseIcon(const NG::OffsetF& translate, LayoutWrapper* layoutWrapper);
    void LayoutScrollNode(const NG::OffsetF& translate, LayoutWrapper* layoutWrapper);

    float GetSheetHeight() const
    {
        return sheetHeight_;
    }

private:
    float sheetWidth_ = 0.0f;
    float sheetHeight_ = 0.0f;
};
} // namespace OHOS::Ace::NG
#endif // CORE_COMPONENTS_NG_PATTERN_SHEET_CONTENT_COVER_SHEET_CONTENT_COVER_LAYOUT_ALGORITHM_H
