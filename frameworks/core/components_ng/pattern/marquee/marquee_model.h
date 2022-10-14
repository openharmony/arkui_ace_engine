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

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"

namespace OHOS::Ace {
class MarqueeModel {
public:
    static MarqueeModel* GetInstance();
    virtual ~MarqueeModel() = default;

    virtual void Create() = 0;
    virtual void SetValue(const std::string& value) = 0;
    virtual void SetPlayerStatus(bool playerStatus) = 0;
    virtual void SetScrollAmount(double scrollAmount) = 0;
    virtual void SetLoop(int32_t loop) = 0;
    virtual void SetDirection(MarqueeDirection direction) = 0;
    virtual void SetTextColor(const Color& textColor) = 0;
    virtual void SetFontSize(const Dimension& fontSize) = 0;
    virtual void SetFontWeight(const FontWeight& fontWeight) = 0;
    virtual void SetFontFamily(const std::vector<std::string>& fontFamilies) = 0;
    virtual void SetAllowScale(bool allowScale) = 0;
    virtual void SetOnStart(std::function<void()>&& onChange) = 0;
    virtual void SetOnBounce(std::function<void()>&& onChange) = 0;
    virtual void SetOnFinish(std::function<void()>&& onChange) = 0;

private:
    static std::unique_ptr<MarqueeModel> instance_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MARQUEE_MODEL_H
