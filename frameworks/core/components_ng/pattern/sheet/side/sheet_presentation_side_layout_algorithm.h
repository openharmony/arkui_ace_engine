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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHEET_SIDE_SHEET_PRESENTATION_SIDE_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHEET_SIDE_SHEET_PRESENTATION_SIDE_LAYOUT_ALGORITHM_H

#include <cstdint>
#include <functional>
#include <optional>
#include <unordered_map>

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/referenced.h"
#include "core/components/common/properties/placement.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_algorithm.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_property.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"

namespace OHOS::Ace::NG {

class SheetPresentationPattern;

class ACE_EXPORT SheetPresentationSideLayoutAlgorithm : public LinearLayoutAlgorithm {
    DECLARE_ACE_TYPE(SheetPresentationSideLayoutAlgorithm, LayoutAlgorithm);

public:
    SheetPresentationSideLayoutAlgorithm() = default;
    ~SheetPresentationSideLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;
    void MeasureOperation(LayoutWrapper* layoutWrapper, LayoutConstraintF constraint);
    void MeasureCloseIcon(LayoutWrapper* layoutWrapper, LayoutConstraintF constraint);
    void MeasureScrollNode(LayoutWrapper* layoutWrapper, LayoutConstraintF constraint);
    void Layout(LayoutWrapper* layoutWrapper) override;

    void LayoutTitleBuilder(LayoutWrapper* layoutWrapper);
    void LayoutScrollNode(LayoutWrapper* layoutWrapper);
    void LayoutCloseIcon(LayoutWrapper* layoutWrapper);
    float GetSheetDefaultWidth(const RefPtr<SheetPresentationPattern>& sheetPattern);

    float GetSideSheetMaxHeight()
    {
        return sheetMaxHeight_;
    }
    float GetSideSheetMaxWidth()
    {
        return sheetMaxWidth_;
    }
    float GetSideSheetWidth()
    {
        return sheetWidth_;
    }

    float GetCenterHeight()
    {
        return sheetHeight_;
    }

private:
    float sheetHeight_ = 0.0f;
    float sheetWidth_ = 0.0f;
    float sheetMaxHeight_ = 0.0f;
    float sheetMaxWidth_ = 0.0f;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHEET_SIDE_SHEET_PRESENTATION_SIDE_LAYOUT_ALGORITHM_H