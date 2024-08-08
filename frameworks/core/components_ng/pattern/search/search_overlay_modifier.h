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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SEARCH_OVERLAY_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SEARCH_OVERLAY_MODIFIER_H

#include <optional>
#include <vector>

#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "core/components/common/properties/color.h"
#include "core/components/search/search_theme.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
struct SearchDividerOffsetsParams {
    bool isRTL;
    OHOS::Ace::NG::SizeF searchSize;
    OHOS::Ace::Dimension iconHeight;
    double dividerSpace;
    double searchSpace;
    double searchDividerWidth;
    float rightOffset;
    float leftOffset;
    float topPadding;
    float bottomPadding;
};
class SearchOverlayModifier : public OverlayModifier {
    DECLARE_ACE_TYPE(SearchOverlayModifier, OverlayModifier)

public:
    SearchOverlayModifier(const WeakPtr<OHOS::Ace::NG::Pattern>& pattern);
    ~SearchOverlayModifier() override = default;

    void onDraw(DrawingContext& drawingContext) override;
    void SetDividerHorizontalOffset(float offset);
    void SetDividerVerticalOffset(float offset);
    void SetDividerHeight(float value);
    void SetIsSearchButtonEnabled(bool value);
    void SetSearchDividerColor(Color value);
    void SetSearchDividerWidth(double value);
    void SetButtonSize(SizeF buttonSize);
    std::tuple<float, float, float, float> GetPaddingOffsets() const;
    std::tuple<float, float, float> CalculateDividerOffsets(const SearchDividerOffsetsParams& params) const;
    std::tuple<OHOS::Ace::Dimension, double, double, double, OHOS::Ace::Color> GetThemeAttributes(
        const RefPtr<OHOS::Ace::SearchTheme>& searchTheme) const;

private:
    void DrawDivider(DrawingContext& drawingContext);
    void InitModifierProperty();
    void AttachModifierProperty();

    RefPtr<AnimatablePropertyFloat> dividerHorizontalOffset_;
    RefPtr<AnimatablePropertyFloat> dividerVerticalOffset_;
    RefPtr<AnimatablePropertyFloat> dividerHeight_;

    RefPtr<PropertyBool> isSearchButtonEnabled_;
    RefPtr<PropertyColor> searchDividerColor_;

    WeakPtr<Pattern> pattern_;
    SizeF buttonSize_;
    double searchDividerWidth_;
    ACE_DISALLOW_COPY_AND_MOVE(SearchOverlayModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SEARCH_OVERLAY_MODIFIER_H