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
#include "core/components_ng/pattern/search/search_paint_method.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/point_t.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/color.h"
#include "core/components/theme/theme_manager.h"
#include "core/components_ng/pattern/search/search_pattern.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void SearchPaintMethod::UpdateOverlayModifier(PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    auto renderContext = paintWrapper->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto host = renderContext->GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto isRTL = layoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto searchTheme = pipeline->GetTheme<SearchTheme>();
    CHECK_NULL_VOID(searchTheme);
    CHECK_NULL_VOID(searchOverlayModifier_);
    auto searchPattern = host->GetPattern<SearchPattern>();
    CHECK_NULL_VOID(searchPattern);
    auto btnSize = searchPattern->GetButtonSize();
    searchOverlayModifier_->SetButtonSize(btnSize);

    // GetThemeAttributes logic inlined here
    auto [iconHeight, dividerSpace, searchSpace, searchDividerWidth, searchDividerColor] =
        searchOverlayModifier_->GetThemeAttributes(searchTheme);
    auto searchSize = paintWrapper->GetGeometryNode()->GetFrameSize();
    auto [rightOffset, leftOffset, topPadding, bottomPadding] = searchOverlayModifier_->GetPaddingOffsets();
    SearchDividerOffsetsParams params = { isRTL, searchSize, iconHeight, dividerSpace, searchSpace, searchDividerWidth,
        rightOffset, leftOffset, topPadding, bottomPadding };

    // CalculateDividerOffsets logic inlined here
    auto [dividerHorizontalOffset, dividerVerticalOffset, dividerHeight] =
        searchOverlayModifier_->CalculateDividerOffsets(params);
    searchOverlayModifier_->SetDividerHorizontalOffset(dividerHorizontalOffset);
    searchOverlayModifier_->SetDividerVerticalOffset(dividerVerticalOffset);
    searchOverlayModifier_->SetDividerHeight(dividerHeight);
    searchOverlayModifier_->SetSearchDividerWidth(searchDividerWidth);
    searchOverlayModifier_->SetSearchDividerColor(searchDividerColor);
    isSearchButtonEnabled_ = searchPattern->GetIsSearchButtonEnabled();
    searchOverlayModifier_->SetIsSearchButtonEnabled(isSearchButtonEnabled_);
}

} // namespace OHOS::Ace::NG
