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

#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"

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
    void CancelImageMeasure(LayoutWrapper* layoutWrapper);
    void CancelButtonMeasure(LayoutWrapper* layoutWrapper);
    void TextFieldMeasure(LayoutWrapper* layoutWrapper);
    void ImageMeasure(LayoutWrapper* layoutWrapper);
    void SearchButtonMeasure(LayoutWrapper* layoutWrapper);
    void SelfMeasure(LayoutWrapper* layoutWrapper);
    bool IsFixedHeightMode(LayoutWrapper* layoutWrapper);
    double CalcSearchAdaptHeight(LayoutWrapper* layoutWrapper);
    void CalcChildrenHotZone(LayoutWrapper* layoutWrapper);
    double CalcSearchWidth(const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper);

    // children frame size
    SizeF searchIconSizeMeasure_;
    SizeF cancelIconSizeMeasure_;
    SizeF searchButtonSizeMeasure_;
    SizeF cancelBtnSizeMeasure_;
    SizeF textFieldSizeMeasure_;

    ACE_DISALLOW_COPY_AND_MOVE(SearchLayoutAlgorithm);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SEARCH_SEARCH_LAYOUT_ALGORITHM_H
