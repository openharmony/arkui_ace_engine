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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_PAINT_PROPERTY_H

#include "core/components_ng/pattern/scroll/inner/scroll_bar.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ListPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(ListPaintProperty, PaintProperty);

public:
    ListPaintProperty() = default;

    ~ListPaintProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto paintProperty = MakeRefPtr<ListPaintProperty>();
        paintProperty->UpdatePaintProperty(this);
        paintProperty->propBarDisplayMode_ = CloneBarDisplayMode();
        return paintProperty;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetBarDisplayMode();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override
    {
        PaintProperty::ToJsonValue(json);
        std::unordered_map<DisplayMode, std::string> scrollBarMap = { { DisplayMode::OFF, "BarState.Off" },
            { DisplayMode::AUTO, "BarState.Auto" }, { DisplayMode::ON, "BarState.On" } };
        json->Put("scrollBar", scrollBarMap[GetBarDisplayMode().value_or(DisplayMode::OFF)].c_str());
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BarDisplayMode, DisplayMode, PROPERTY_UPDATE_RENDER);

protected:
    ACE_DISALLOW_COPY_AND_MOVE(ListPaintProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_LAYOUT_PROPERTY_H
