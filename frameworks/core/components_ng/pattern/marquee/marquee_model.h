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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MARQUEE_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MARQUEE_MODEL_H

#include <mutex>
#include <optional>

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT MarqueeModel {
public:
    static MarqueeModel* GetInstance();
    virtual ~MarqueeModel() = default;

    virtual void Create() = 0;
    virtual void SetValue(const std::optional<std::string>& value) = 0;
    virtual void SetPlayerStatus(const std::optional<bool>& playerStatus) = 0;
    virtual void SetScrollAmount(const std::optional<double>& scrollAmount) = 0;
    virtual void SetLoop(const std::optional<int32_t>& loop) = 0;
    virtual void SetDirection(const std::optional<MarqueeDirection>& direction) = 0;
    virtual void SetTextColor(const std::optional<Color>& textColor) = 0;
    virtual void SetFontSize(const std::optional<Dimension>& fontSize) = 0;
    virtual void SetFontWeight(const std::optional<FontWeight>& fontWeight) = 0;
    virtual void SetFontFamily(const std::optional<std::vector<std::string>>& fontFamilies) = 0;
    virtual void SetAllowScale(const std::optional<bool>& allowScale) = 0;
    virtual void SetOnStart(std::function<void()>&& onChange) = 0;
    virtual void SetOnBounce(std::function<void()>&& onChange) = 0;
    virtual void SetOnFinish(std::function<void()>&& onChange) = 0;
    virtual void SetMarqueeUpdateStrategy(const std::optional<MarqueeUpdateStrategy>& marqueeUpdateStrategy) {};

private:
    static std::unique_ptr<MarqueeModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MARQUEE_MODEL_H
