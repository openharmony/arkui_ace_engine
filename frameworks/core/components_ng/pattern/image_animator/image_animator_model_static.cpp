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

#include "core/components_ng/pattern/image_animator/image_animator_model_static.h"

#include "core/components_ng/base/view_stack_processor.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DEFAULT_DURATION { 1000 };
constexpr int32_t DEFAULT_STATUS { static_cast<int32_t>(ControlledAnimator::ControlStatus::IDLE) };
constexpr int32_t DEFAULT_FILL_MODE { static_cast<int32_t>(FillMode::FORWARDS) };
constexpr int32_t DEFAULT_ITERATIONS { 1 };
} // namespace

void ImageAnimatorModelStatic::SetDuration(FrameNode* frameNode, const std::optional<int32_t>& duration)
{
    CHECK_NULL_VOID(frameNode);
    GetImageAnimatorPattern(frameNode)->SetDuration(duration.value_or(DEFAULT_DURATION));
}

void ImageAnimatorModelStatic::SetState(FrameNode* frameNode, const std::optional<int32_t>& state)
{
    CHECK_NULL_VOID(frameNode);
    GetImageAnimatorPattern(frameNode)->SetStatus(
        static_cast<ControlledAnimator::ControlStatus>(state.value_or(DEFAULT_STATUS)));
}

void ImageAnimatorModelStatic::SetFillMode(FrameNode* frameNode, const std::optional<int32_t>& fillMode)
{
    CHECK_NULL_VOID(frameNode);
    GetImageAnimatorPattern(frameNode)->SetFillMode(static_cast<FillMode>(fillMode.value_or(DEFAULT_FILL_MODE)));
}

void ImageAnimatorModelStatic::SetIteration(FrameNode* frameNode, const std::optional<int32_t>& iteration)
{
    CHECK_NULL_VOID(frameNode);
    GetImageAnimatorPattern(frameNode)->SetIteration(iteration.value_or(DEFAULT_ITERATIONS));
}

RefPtr<ImageAnimatorPattern> ImageAnimatorModelStatic::GetImageAnimatorPattern()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    return AceType::DynamicCast<ImageAnimatorPattern>(frameNode->GetPattern());
}

RefPtr<ImageAnimatorPattern> ImageAnimatorModelStatic::GetImageAnimatorPattern(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    return AceType::DynamicCast<ImageAnimatorPattern>(frameNode->GetPattern());
}
} // namespace OHOS::Ace::NG