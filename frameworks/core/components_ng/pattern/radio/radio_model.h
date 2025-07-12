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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RADIO_RADIO_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RADIO_RADIO_MODEL_H

#include <functional>
#include <mutex>

#include "core/common/resource/resource_object.h"
#include "core/components_ng/pattern/radio/radio_event_hub.h"

namespace OHOS::Ace {
enum class RadioColorType {
    CHECKED_BACKGROUND_COLOR,
    UNCHECKED_BORDER_COLOR,
    INDICATOR_COLOR
};
class ACE_FORCE_EXPORT RadioModel {
public:
    static RadioModel* GetInstance();
    virtual ~RadioModel() = default;

    virtual void Create(const std::optional<std::string>& value, const std::optional<std::string>& group,
        const std::optional<int32_t>& indicator);
    virtual void SetChecked(bool isChecked);
    virtual void SetOnChange(NG::ChangeEvent&& onChange);
    virtual void SetBuilder(std::function<void()>&& buildFunc) {};
    virtual void SetWidth(const Dimension& width);
    virtual void SetHeight(const Dimension& height);
    virtual void SetPadding(const NG::PaddingPropertyF& args, const NG::PaddingProperty& newArgs);
    virtual void SetIsUserSetMargin(bool isUserSet) {};
    virtual void SetCheckedBackgroundColor(const Color& color) {}
    virtual void SetUncheckedBorderColor(const Color& color) {}
    virtual void SetIndicatorColor(const Color& color) {}
    virtual void SetCheckedBackgroundColorSetByUser(bool flag) {}
    virtual void SetUncheckedBorderColorSetByUser(bool flag) {}
    virtual void SetIndicatorColorSetByUser(bool flag) {}
    virtual void SetOnChangeEvent(NG::ChangeEvent&& onChangeEvent) {};
    virtual void SetOnClickEvent(std::function<void()>&& onClick) {};
    virtual void SetResponseRegion(const std::vector<DimensionRect>& responseRegion) {};
    virtual void SetHoverEffect(HoverEffectType hoverEffect) {};
    virtual void CreateWithColorResourceObj(const RefPtr<ResourceObject>& resObj,
        const RadioColorType radioColorType) {};
    virtual void SetUncheckedBorderColorByJSRadioTheme(bool flag) {}
    virtual void SetIndicatorColorByJSRadioTheme(bool flag) {}
private:
    static std::unique_ptr<RadioModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RADIO_RADIO_MODEL_H
