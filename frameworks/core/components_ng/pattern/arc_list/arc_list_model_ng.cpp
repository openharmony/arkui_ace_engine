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
#include "core/components_ng/pattern/arc_list/arc_list_model_ng.h"

#include "core/components_ng/pattern/arc_list/arc_list_pattern.h"

namespace OHOS::Ace::NG {

void ArcListModelNG::SetHeader(FrameNode* frameNode, FrameNode* headerNode)
{
    CHECK_NULL_VOID(headerNode);
    CHECK_NULL_VOID(frameNode);
    auto pattern = AceType::DynamicCast<ArcListPattern>(frameNode->GetPattern());
    if (pattern) {
        pattern->AddHeader(AceType::Claim(headerNode));
    }
}

RefPtr<FrameNode> ArcListModelNG::GetHeader(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = AceType::DynamicCast<ArcListPattern>(frameNode->GetPattern());
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetHeader();
}

void ArcListModelNG::ResetHeader(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = AceType::DynamicCast<ArcListPattern>(frameNode->GetPattern());
    if (pattern) {
        pattern->ResetHeader();
    }
}

#ifdef SUPPORT_DIGITAL_CROWN
void ArcListModelNG::SetDigitalCrownSensitivity(FrameNode* frameNode, CrownSensitivity sensitivity)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = AceType::DynamicCast<ArcListPattern>(frameNode->GetPattern());
    if (pattern) {
        pattern->SetDigitalCrownSensitivity(sensitivity);
    }
}

CrownSensitivity ArcListModelNG::GetDigitalCrownSensitivity(FrameNode* frameNode)
{
    CrownSensitivity sensitivity = CrownSensitivity::MEDIUM;
    CHECK_NULL_RETURN(frameNode, sensitivity);
    auto pattern = AceType::DynamicCast<ArcListPattern>(frameNode->GetPattern());
    return pattern ? pattern->GetDigitalCrownSensitivity() : sensitivity;
}

void ArcListModelNG::ResetDigitalCrownSensitivity(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = AceType::DynamicCast<ArcListPattern>(frameNode->GetPattern());
    if (pattern) {
        pattern->SetDigitalCrownSensitivity(CrownSensitivity::MEDIUM);
    }
}
#endif

} // namespace OHOS::Ace::NG
