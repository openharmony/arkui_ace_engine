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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MARQUEE_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MARQUEE_MODEL_NG_H

#include "core/components_ng/pattern/marquee/marquee_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT MarqueeModelNG : public OHOS::Ace::MarqueeModel {
public:
    void Create() override;
    void SetValue(const std::optional<std::string>& value) override;
    void SetPlayerStatus(const std::optional<bool>& playerStatus) override;
    void SetScrollAmount(const std::optional<double>& scrollAmount) override;
    void SetLoop(const std::optional<int32_t>& loop) override;
    void SetDirection(const std::optional<MarqueeDirection>& direction) override;
    void SetTextColor(const std::optional<Color>& textColor) override;
    void SetFontSize(const std::optional<Dimension>& fontSize) override;
    void SetFontWeight(const std::optional<FontWeight>& fontWeight) override;
    void SetFontFamily(const std::optional<std::vector<std::string>>& fontFamilies) override;
    void SetAllowScale(const std::optional<bool>& allowScale) override;
    void SetOnStart(std::function<void()>&& onChange) override;
    void SetOnBounce(std::function<void()>&& onChange) override;
    void SetOnFinish(std::function<void()>&& onChange) override;

    static void SetAllowScale(FrameNode* frameNode, const bool allowScale);
    static void SetFontWeight(FrameNode* frameNode, const std::optional<FontWeight>& fontWeight);
    static void SetFontFamily(FrameNode* frameNode, const std::optional<std::vector<std::string>>& fontFamilies);
    static void SetFontSize(FrameNode* frameNode, const std::optional<Dimension>& fontSize);
    static void SetTextColor(FrameNode* frameNode, const std::optional<Color>& textColor);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MARQUEE_MODEL_NG_H
