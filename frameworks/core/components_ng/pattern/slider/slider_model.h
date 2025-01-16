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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SLIDER_SLIDER_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SLIDER_SLIDER_MODEL_H

#include <functional>
#include <memory>
#include <mutex>
#include <optional>

#include "base/geometry/axis.h"
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components/common/properties/clip_path.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/property/gradient_property.h"

#ifdef SUPPORT_DIGITAL_CROWN
#include "core/event/crown_event.h"
#endif

namespace OHOS::Ace {
class ACE_FORCE_EXPORT SliderModel {
public:
    enum class SliderMode {
        OUTSET,  // block on track, track is thin
        INSET,   // block inside track, track is rough
        NONE,    // no block
        CAPSULE, // capsule slider.
    };

    enum class BlockStyleType {
        DEFAULT,
        IMAGE,
        SHAPE,
    };

    enum class SliderInteraction {
        SLIDE_AND_CLICK,
        SLIDE_ONLY,
        SLIDE_AND_CLICK_UP,
    };

    class SliderValidRange final : public AceType {
    public:
        SliderValidRange() = default;
        SliderValidRange(float from, float to) : fromValue(from), toValue(to) {}
        ~SliderValidRange() = default;
        float GetFromValue() const
        {
            return fromValue;
        }
        float GetToValue() const
        {
            return toValue;
        }
        bool HasValidValues() const
        {
            return std::isfinite(fromValue) && std::isfinite(toValue);
        }

    private:
        float fromValue = std::numeric_limits<float>::quiet_NaN();
        float toValue = std::numeric_limits<float>::quiet_NaN();
    };

    static SliderModel* GetInstance();
    virtual ~SliderModel() = default;

    virtual void Create(float value, float step, float min, float max) = 0;
    virtual void SetSliderMode(const SliderMode& value) = 0;
    virtual void SetDirection(Axis value) = 0;
    virtual void SetReverse(bool value) = 0;
    virtual void SetBlockColor(const Color& value) = 0;
    virtual void SetTrackBackgroundColor(const Color& value) = 0;
    virtual void SetTrackBackgroundColor(const NG::Gradient& value, bool isResourceColor = false) = 0;
    virtual void SetSelectColor(const Color& value) = 0;
    virtual void SetSelectColor(const NG::Gradient& value, bool isResourceColor = false) = 0;
    virtual void SetMinLabel(float value) = 0;
    virtual void SetMaxLabel(float value) = 0;
    virtual void SetMinResponsiveDistance(float value) {};
    virtual void SetShowSteps(bool value) = 0;
    virtual void SetShowTips(bool value, const std::optional<std::string>& content) = 0;
    virtual void SetThickness(const Dimension& value) = 0;
    virtual void SetBlockBorderColor(const Color& value) = 0;
    virtual void SetBlockBorderWidth(const Dimension& value) = 0;
    virtual void SetStepColor(const Color& value) = 0;
    virtual void SetTrackBorderRadius(const Dimension& value) = 0;
    virtual void SetSelectedBorderRadius(const Dimension& value) = 0;
    virtual void SetBlockSize(const Dimension& width, const Dimension& height) = 0;
    virtual void SetBlockType(BlockStyleType value) = 0;
    virtual void SetBlockImage(
        const std::string& value, const std::string& bundleName, const std::string& moduleName) = 0;
    virtual void SetBlockShape(const RefPtr<BasicShape>& value) = 0;
    virtual void SetStepSize(const Dimension& value) = 0;
    virtual void SetSliderInteractionMode(SliderInteraction mode) {};
    virtual void SetOnChange(std::function<void(float, int32_t)>&& eventOnChange) = 0;
    virtual void SetOnChangeEvent(std::function<void(float)>&& onChangeEvent) = 0;
    virtual void SetValidSlideRange(float fromValue, float toValue) {};
#ifdef SUPPORT_DIGITAL_CROWN
    virtual void SetDigitalCrownSensitivity(CrownSensitivity sensitivity) {};
#endif

    virtual void ResetBlockBorderColor() = 0;
    virtual void ResetBlockBorderWidth() = 0;
    virtual void ResetStepColor() = 0;
    virtual void ResetTrackBorderRadius() = 0;
    virtual void ResetSelectedBorderRadius() = 0;
    virtual void ResetBlockSize() = 0;
    virtual void ResetBlockType() = 0;
    virtual void ResetBlockImage() = 0;
    virtual void ResetBlockShape() = 0;
    virtual void ResetStepSize() = 0;
    virtual void ResetSliderInteractionMode() = 0;
    virtual void ResetMinResponsiveDistance() = 0;
    virtual void ResetValidSlideRange() = 0;
    virtual void SetEnableHapticFeedback(bool isEnableHapticFeedback) = 0;
#ifdef SUPPORT_DIGITAL_CROWN
    virtual void ResetDigitalCrownSensitivity() = 0;
#endif

private:
    static std::unique_ptr<SliderModel> instance_;
    static std::mutex mutex_;
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SLIDER_SLIDER_MODEL_H
