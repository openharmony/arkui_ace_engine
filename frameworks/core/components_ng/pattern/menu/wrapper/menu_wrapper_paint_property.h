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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_WRAPPER_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_WRAPPER_PAINT_PROPERTY_H

#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/placement.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/render/paint_property.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT MenuWrapperPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(MenuWrapperPaintProperty, PaintProperty);

public:
    MenuWrapperPaintProperty() = default;
    ~MenuWrapperPaintProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto paintProperty = MakeRefPtr<MenuWrapperPaintProperty>();
        paintProperty->propRenderFlag_ = CloneRenderFlag();
        return paintProperty;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetRenderFlag();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(RenderFlag, int32_t, PROPERTY_UPDATE_RENDER);
    ACE_DISALLOW_COPY_AND_MOVE(MenuWrapperPaintProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_PAINT_PROPERTY_H
