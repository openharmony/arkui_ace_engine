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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SECURITY_COMPONENT_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SECURITY_COMPONENT_LAYOUT_ALGORITHM_H

#include "base/geometry/ng/offset_t.h"
#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/pattern/security_component/security_component_common.h"
#include "core/components_ng/pattern/security_component/security_component_layout_property.h"
#include "core/components_ng/pattern/security_component/security_component_theme.h"

namespace OHOS::Ace::NG {
struct SecurityComponentLayoutPaddingParams {
    double top = 0.0;
    double right = 0.0;
    double bottom = 0.0;
    double left = 0.0;
    double textIconSpace = 0.0;
    bool iconStart = false;
};

class ACE_EXPORT SecurityComponentLayoutAlgorithm : public BoxLayoutAlgorithm {
    DECLARE_ACE_TYPE(SecurityComponentLayoutAlgorithm, BoxLayoutAlgorithm);

public:
    SecurityComponentLayoutAlgorithm() = default;
    ~SecurityComponentLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;

private:
    RefPtr<LayoutWrapper> GetChildWrapper(LayoutWrapper* layoutWrapper, const std::string& tag);
    void UpdateChildPosition(LayoutWrapper* layoutWrapper, const std::string& tag,
        OffsetT<Dimension>& offset);
    void InitLayoutParams(RefPtr<SecurityComponentLayoutProperty>& property);
    void MeasureIcon(LayoutWrapper* layoutWrapper, RefPtr<SecurityComponentLayoutProperty>& securityComponentProperty);
    void MeasureText(LayoutWrapper* layoutWrapper, RefPtr<SecurityComponentLayoutProperty>& securityComponentProperty);
    void UpdateFrameMeasure(LayoutWrapper* layoutWrapper,
        RefPtr<SecurityComponentLayoutProperty>& securityComponentProperty);
    void MeasureButton(LayoutWrapper* layoutWrapper,
        RefPtr<SecurityComponentLayoutProperty>& securityComponentProperty);
    void FillPaddingParams(RefPtr<SecurityComponentLayoutProperty>& securityComponentProperty,
        SecurityComponentLayoutPaddingParams& res);
    void UpdateHorizontal(OffsetT<Dimension>& offsetIcon, OffsetT<Dimension>& offsetText,
        const SecurityComponentLayoutPaddingParams& params);
    void UpdateVertical(OffsetT<Dimension>& offsetIcon, OffsetT<Dimension>& offsetText,
        const SecurityComponentLayoutPaddingParams& params);
    void UpdateCircleBackground(OffsetT<Dimension>& offsetIcon, OffsetT<Dimension>& offsetText);
    double componentWidth_ = 0.0;
    double componentHeight_ = 0.0;
    SizeF iconSizeF_;
    SizeF textSizeF_;
    SizeF buttonSizeF_;
    int32_t buttonType_ = static_cast<int32_t>(ButtonType::NORMAL);
    ACE_DISALLOW_COPY_AND_MOVE(SecurityComponentLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SECURITY_COMPONENT_LAYOUT_ALGORITHM_H
