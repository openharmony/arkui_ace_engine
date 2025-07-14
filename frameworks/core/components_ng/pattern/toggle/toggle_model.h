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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TOGGLE_TOGGLE_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TOGGLE_TOGGLE_MODEL_H

#include <memory>
#include <mutex>

#include "base/geometry/dimension.h"
#include "core/common/resource/resource_object.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/toggle/switch_event_hub.h"
#include "frameworks/core/components_ng/property/measure_property.h"

namespace OHOS::Ace::NG {

enum class ToggleType {
    CHECKBOX = 0,
    SWITCH,
    BUTTON,
};

} // namespace OHOS::Ace::NG

namespace OHOS::Ace {
enum class ToggleColorType {
    SELECTED_COLOR,
    SWITCH_POINT_COLOR,
    UN_SELECTED_COLOR,
    BACKGROUND_COLOR
};
enum class ToggleDimensionType {
    POINT_RADIUS,
    TRACK_BORDER_RADIUS
};
class ACE_FORCE_EXPORT ToggleModel {
public:
    static ToggleModel* GetInstance();
    virtual ~ToggleModel() = default;

    virtual void Create(NG::ToggleType toggleType, bool isOn) = 0;
    virtual void SetSelectedColor(const std::optional<Color>& selectedColor) = 0;
    virtual void SetSwitchPointColor(const std::optional<Color>& switchPointColor) = 0;
    virtual void OnChange(NG::ChangeEvent&& onChange) = 0;
    virtual void SetWidth(const Dimension& width) = 0;
    virtual void SetHeight(const Dimension& height) = 0;
    virtual void SetBackgroundColor(const Color& color, bool flag) {};
    virtual bool IsToggle() = 0;
    virtual void SetPadding(const NG::PaddingPropertyF& args, const NG::PaddingProperty& newArgs) = 0;
    virtual void SetIsUserSetMargin(bool isUserSet) {};
    virtual void OnChangeEvent(NG::ChangeEvent&& onChangeEvent) = 0;
    virtual void SetResponseRegion(const std::vector<DimensionRect>& responseRegion) = 0;
    virtual void SetHoverEffect(HoverEffectType hoverEffect) = 0;
    virtual void SetPointRadius(const Dimension& switchPointRadius) {};
    virtual void ResetPointRadius() {};
    virtual void SetUnselectedColor(const Color& unselectedColor) {};
    virtual void SetTrackBorderRadius(const Dimension& borderRadius) {};
    virtual void ResetTrackBorderRadius() {};
    virtual void Pop();
    virtual void CreateWithColorResourceObj(const RefPtr<ResourceObject>& resObj,
        const ToggleColorType toggleColorType) {};
    virtual void CreateWithDimensionVpResourceObj(const RefPtr<ResourceObject>& resObj,
        const ToggleDimensionType toggleDimensionType) {};
    virtual void SetSwitchPointColorSetByUser(const bool flag) {};
    virtual void SetUnselectedColorSetByUser(const bool flag) {};

private:
    static std::unique_ptr<ToggleModel> instance_;
    static std::mutex mutex_;
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TOGGLE_TOGGLE_MODEL_H
