/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_TXT_TEXT_EFFECT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_TXT_TEXT_EFFECT_H

#include "core/components_ng/render/text_effect.h"

namespace OHOS::Ace::NG {

// Paragraph is interface for drawing text and text paragraph.
class MockTextEffect : public TextEffect {
    DECLARE_ACE_TYPE(NG::MockTextEffect, NG::TextEffect);

public:
    MockTextEffect();
    ~MockTextEffect() = default;
    int UpdateEffectConfig(const std::unordered_map<TextEffectAttribute, std::string>& config) override;
    int AppendTypography(const std::vector<RefPtr<Paragraph>>& paragraphs) override;
    void RemoveTypography(const std::vector<RefPtr<Paragraph>>& paragraphs) override;
    int UpdateTypography(std::vector<std::pair<RefPtr<Paragraph>, RefPtr<Paragraph>>>& paragraphs) override;
    void StartEffect(RSCanvas& canvas, double x, double y) override;
    void StopEffect() override;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_TXT_TEXT_EFFECT_H
