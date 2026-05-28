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

#ifndef FOUNDATION_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECTION_CONTAINER_SELECTION_CONTAINER_LAYOUT_PROPERTY_H
#define FOUNDATION_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECTION_CONTAINER_SELECTION_CONTAINER_LAYOUT_PROPERTY_H

#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/selection_container/selection_container_model.h"
#include "core/components_ng/pattern/stack/stack_layout_property.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT SelectionContainerLayoutProperty : public StackLayoutProperty {
    DECLARE_ACE_TYPE(SelectionContainerLayoutProperty, StackLayoutProperty);

public:
    SelectionContainerLayoutProperty() = default;
    ~SelectionContainerLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto prop = MakeRefPtr<SelectionContainerLayoutProperty>();
        prop->UpdateLayoutProperty(this);
        return prop;
    }

    void Reset() override
    {
        StackLayoutProperty::Reset();
        ResetCopyOption();
        ResetCaretColor();
        ResetSelectedBackgroundColor();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CopyOption, CopyOptions, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CaretColor, Color, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SelectedBackgroundColor, Color, PROPERTY_UPDATE_MEASURE_SELF);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECTION_CONTAINER_SELECTION_CONTAINER_LAYOUT_PROPERTY_H
