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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TAB_BAR_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TAB_BAR_MODIFIER_H

#include "base/memory/ace_type.h"
#include "base/geometry/axis.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/tabs/tab_content_model.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {
class TabBarModifier : public ContentModifier {
    DECLARE_ACE_TYPE(TabBarModifier, ContentModifier);

public:
    TabBarModifier();

    ~TabBarModifier() override = default;
    
    void SetIndicatorOffset(const OffsetF& indicatorOffset);

    void SetIndicatorColor(const LinearColor& indicatorColor);

    void SetIndicatorWidth(float indicatorWidth);

    void SetIndicatorHeight(float indicatorHeight);

    void SetIndicatorBorderRadius(float indicatorBorderRadius);

    void SetIndicatorMarginTop(float indicatorMarginTop);

    void SetHasIndicator(bool hasIndicator);

    void onDraw(DrawingContext& context) override;

private:

    void PaintIndicator(DrawingContext& context);

    RefPtr<AnimatablePropertyColor> indicatorColor_;
    RefPtr<AnimatablePropertyFloat> indicatorLeft_;
    RefPtr<AnimatablePropertyFloat> indicatorTop_;
    RefPtr<AnimatablePropertyFloat> indicatorWidth_;
    RefPtr<AnimatablePropertyFloat> indicatorHeight_;
    RefPtr<AnimatablePropertyFloat> indicatorBorderRadius_;
    RefPtr<AnimatablePropertyFloat> indicatorMarginTop_;
    RefPtr<PropertyBool> hasIndicator_;

    ACE_DISALLOW_COPY_AND_MOVE(TabBarModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TAB_BAR_MODIFIER_H
