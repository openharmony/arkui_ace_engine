/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SEARCH_SEARCH_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SEARCH_SEARCH_LAYOUT_ALGORITHM_H

#include "core/components/search/search_theme.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/search/search_layout_property.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT SearchLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(SearchLayoutAlgorithm, LayoutAlgorithm);

public:
    SearchLayoutAlgorithm() = default;

    ~SearchLayoutAlgorithm() override = default;

    void OnReset() override {}

    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

private:
    struct LayoutSearchParams {
        LayoutWrapper* layoutWrapper = nullptr;
        RefPtr<SearchLayoutProperty> layoutProperty = nullptr;
        RefPtr<SearchTheme> searchTheme = nullptr;
        float searchFrameWidth = 0.0f;
        float searchFrameHeight = 0.0f;
        bool isRTL = false;
    };
    void CancelImageMeasure(LayoutWrapper* layoutWrapper);
    void CancelButtonMeasure(LayoutWrapper* layoutWrapper);
    void TextFieldMeasure(LayoutWrapper* layoutWrapper);
    void ImageMeasure(LayoutWrapper* layoutWrapper);
    void SearchButtonMeasure(LayoutWrapper* layoutWrapper);
    void DividerMeasure(LayoutWrapper* layoutWrapper);
    void SelfMeasure(LayoutWrapper* layoutWrapper);
    bool IsFixedHeightMode(LayoutWrapper* layoutWrapper);
    double CalcSearchAdaptHeight(LayoutWrapper* layoutWrapper);
    void CalcChildrenHotZone(LayoutWrapper* layoutWrapper);
    double CalcSearchWidth(const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper);
    double CalcSearchHeight(const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper);
    float CalculateMaxFontScale(LayoutWrapper* layoutWrapper);
    float CalculateMinFontScale(LayoutWrapper* layoutWrapper);
    CalcSize searchButtonCalcSize(const RefPtr<SearchTheme>& searchTheme, RefPtr<SearchLayoutProperty> layoutProperty,
        LayoutWrapper* layoutWrapper, float maxFontScale, float minFontScale);
    void UpdateFontFeature(LayoutWrapper* layoutWrapper);
    void UpdateTextFieldSize(LayoutWrapper* layoutWrapper);
    void SetTextFieldLayoutConstraintHeight(LayoutConstraintF& contentConstraint, double textFieldHeight,
        LayoutWrapper* layoutWrapper);

    // children frame size
    SizeF searchIconSizeMeasure_;
    SizeF cancelIconSizeMeasure_;
    SizeF searchButtonSizeMeasure_;
    SizeF cancelBtnSizeMeasure_;
    SizeF textFieldSizeMeasure_;
    SizeF dividerSizeMeasure_;
    void LayoutSearchIcon(const LayoutSearchParams& params);
    void LayoutSearchButton(const LayoutSearchParams& params);
    void LayoutDivider(const LayoutSearchParams& params);
    void LayoutCancelButton(const LayoutSearchParams& params);
    void LayoutCancelImage(const LayoutSearchParams& params);
    void LayoutTextField(const LayoutSearchParams& params);
    void UpdateClipBounds(LayoutWrapper* layoutWrapper, float height);
    double CalcSymbolIconHeight(LayoutWrapper* layoutWrapper, int32_t index, double defaultImageHeight);
    float CalculateTextFieldWidth(
        LayoutWrapper* layoutWrapper, float searchWidthMax, const RefPtr<SearchTheme>& searchTheme);
    float GetSearchFieldMinWidth(LayoutWrapper* layoutWrapper);
    std::optional<float> GetSearchFixAtIdealMaxWidth(LayoutWrapper* layoutWrapper);
    float GetTextFieldMinWidth(LayoutWrapper* layoutWrapper, const RefPtr<SearchTheme>& searchTheme);
    float GetTextFieldMaxWidth(LayoutWrapper* layoutWrapper, LayoutCalPolicy layoutPolicy, float maxWidth);
    void ResetChildrenMeasureSize();

    // cached data
    float maxFontScale_;
    float minFontScale_;
    double searchHeight_;
    float searchWidthReducedLength_ = 0.0f;
    ACE_DISALLOW_COPY_AND_MOVE(SearchLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SEARCH_SEARCH_LAYOUT_ALGORITHM_H
