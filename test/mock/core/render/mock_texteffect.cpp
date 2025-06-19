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

#include "mock_texteffect.h"

namespace OHOS::Ace::NG {
RefPtr<TextEffect> TextEffect::CreateTextEffect()
{
    return AceType::MakeRefPtr<MockTextEffect>();
}

MockTextEffect::MockTextEffect() {}

int MockTextEffect::UpdateEffectConfig(const std::unordered_map<TextEffectAttribute, std::string>& config)
{
    return -1;
}

int MockTextEffect::AppendTypography(const std::vector<RefPtr<Paragraph>>& paragraphs)
{
    return -1;
}

void MockTextEffect::RemoveTypography(const std::vector<RefPtr<Paragraph>>& paragraphs) {}

int MockTextEffect::UpdateTypography(std::vector<std::pair<RefPtr<Paragraph>, RefPtr<Paragraph>>>& paragraphs)
{
    return -1;
}

void MockTextEffect::StartEffect(RSCanvas& canvas, double x, double y) {}
void MockTextEffect::StopEffect() {}
} // namespace OHOS::Ace::NG
