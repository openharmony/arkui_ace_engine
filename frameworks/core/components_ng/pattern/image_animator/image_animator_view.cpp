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

#include "core/components_ng/pattern/image_animator/image_animator_view.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void ImageAnimatorView::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ANIMATOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ImageAnimatorPattern>(); });
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GetChildren().empty()) {
        auto imageNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, -1, AceType::MakeRefPtr<ImagePattern>());
        CHECK_NULL_VOID(imageNode);
        auto imageLayoutProperty = AceType::DynamicCast<ImageLayoutProperty>(imageNode->GetLayoutProperty());
        CHECK_NULL_VOID(imageLayoutProperty);
        imageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
        frameNode->AddChild(imageNode);
    }
    stack->Push(frameNode);
}

void ImageAnimatorView::SetImages(std::vector<ImageProperties>&& images)
{
    GetImageAnimatorPattern()->SetImages(std::move(images));
}

void ImageAnimatorView::SetStatus(Animator::Status status)
{
    GetImageAnimatorPattern()->SetStatus(status);
}

void ImageAnimatorView::SetDuration(int32_t duration)
{
    GetImageAnimatorPattern()->SetDuration(duration);
}

void ImageAnimatorView::SetIteration(int32_t iteration)
{
    GetImageAnimatorPattern()->SetIteration(iteration);
}

void ImageAnimatorView::SetFillMode(FillMode fillMode)
{
    GetImageAnimatorPattern()->SetFillMode(fillMode);
}

void ImageAnimatorView::SetPreDecode(int32_t preDecode)
{
    GetImageAnimatorPattern()->SetPreDecode(preDecode);
}

void ImageAnimatorView::SetIsReverse(bool isReverse)
{
    GetImageAnimatorPattern()->SetIsReverse(isReverse);
}

void ImageAnimatorView::SetFixedSize(bool fixedSize)
{
    GetImageAnimatorPattern()->SetFixedSize(fixedSize);
}

void ImageAnimatorView::SetImageAnimatorEvent(const AnimatorEvent& imageAnimatorEvent, AnimatorEventType eventType)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ImageAnimatorEventHub>();
    CHECK_NULL_VOID(eventHub);
    switch (eventType) {
        case AnimatorEventType::ON_START:
            eventHub->SetStartEvent(imageAnimatorEvent);
            break;
        case AnimatorEventType::ON_PAUSE:
            eventHub->SetPauseEvent(imageAnimatorEvent);
            break;
        case AnimatorEventType::ON_REPEAT:
            eventHub->SetRepeatEvent(imageAnimatorEvent);
            break;
        case AnimatorEventType::ON_CANCEL:
            eventHub->SetCancelEvent(imageAnimatorEvent);
            break;
        case AnimatorEventType::ON_FINISH:
            eventHub->SetStopEvent(imageAnimatorEvent);
            break;
        default:
            LOGE("Unsupported image animator event type");
    }
}

RefPtr<ImageAnimatorPattern> ImageAnimatorView::GetImageAnimatorPattern()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    return AceType::DynamicCast<ImageAnimatorPattern>(frameNode->GetPattern());
}

} // namespace OHOS::Ace::NG