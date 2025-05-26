/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/image_animator/image_animator_model_ng.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/image_animator/controlled_animator.h"

namespace OHOS::Ace::NG {
namespace {
    constexpr int32_t DEFAULT_DURATION = 1000;
    void InitImageNodeInImageAnimator(FrameNode* frameNode)
    {
        CHECK_NULL_VOID(frameNode);
        if (frameNode->GetChildren().empty()) {
            auto imageNode = FrameNode::CreateFrameNode(
                V2::IMAGE_ETS_TAG, -1, AceType::MakeRefPtr<ImagePattern>());
            CHECK_NULL_VOID(imageNode);
            auto imagePattern = AceType::DynamicCast<ImagePattern>(imageNode->GetPattern());
            CHECK_NULL_VOID(imagePattern);
            imagePattern->SetImageAnimator(true);
            auto imageLayoutProperty = AceType::DynamicCast<ImageLayoutProperty>(imageNode->GetLayoutProperty());
            CHECK_NULL_VOID(imageLayoutProperty);
            imageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
            frameNode->GetLayoutProperty()->UpdateAlignment(Alignment::TOP_LEFT);
            frameNode->AddChild(imageNode);
        }
    }
}

void ImageAnimatorModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::IMAGE_ANIMATOR_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ANIMATOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ImageAnimatorPattern>(); });
    CHECK_NULL_VOID(frameNode);
    stack->Push(frameNode);
}

void ImageAnimatorModelNG::SetAutoMonitorInvisibleArea(bool autoMonitorInvisibleArea)
{
    GetImageAnimatorPattern()->SetAutoMonitorInvisibleArea(autoMonitorInvisibleArea);
}

void ImageAnimatorModelNG::SetImages(const std::vector<ImageProperties>& images)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    InitImageNodeInImageAnimator(frameNode);
    std::vector<ImageProperties> imageList = images;
    GetImageAnimatorPattern()->SetImages(std::move(imageList));
}

void ImageAnimatorModelNG::SetState(int32_t state)
{
    GetImageAnimatorPattern()->SetStatus(static_cast<ControlledAnimator::ControlStatus>(state));
}

void ImageAnimatorModelNG::SetDuration(int32_t duration)
{
    GetImageAnimatorPattern()->SetDuration(duration);
}

void ImageAnimatorModelNG::SetIteration(int32_t iteration)
{
    GetImageAnimatorPattern()->SetIteration(iteration);
}

void ImageAnimatorModelNG::SetFillMode(int32_t fillMode)
{
    GetImageAnimatorPattern()->SetFillMode(static_cast<FillMode>(fillMode));
}

void ImageAnimatorModelNG::SetPreDecode(int32_t preDecode)
{
    GetImageAnimatorPattern()->SetPreDecode(preDecode);
}

void ImageAnimatorModelNG::SetIsReverse(bool isReverse)
{
    GetImageAnimatorPattern()->SetIsReverse(isReverse);
}

void ImageAnimatorModelNG::SetFixedSize(bool fixedSize)
{
    GetImageAnimatorPattern()->SetFixedSize(fixedSize);
}

void ImageAnimatorModelNG::SetOnStart(std::function<void()>&& OnStart)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<ImageAnimatorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetStartEvent(OnStart);
}

void ImageAnimatorModelNG::SetOnPause(std::function<void()>&& OnPause)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<ImageAnimatorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetPauseEvent(OnPause);
}

void ImageAnimatorModelNG::SetOnRepeat(std::function<void()>&& OnRepeat)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<ImageAnimatorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetRepeatEvent(OnRepeat);
}

void ImageAnimatorModelNG::SetOnCancel(std::function<void()>&& OnCancel)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<ImageAnimatorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetCancelEvent(OnCancel);
}

void ImageAnimatorModelNG::SetOnFinish(std::function<void()>&& OnFinish)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<ImageAnimatorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetStopEvent(OnFinish);
}

RefPtr<ImageAnimatorPattern> ImageAnimatorModelNG::GetImageAnimatorPattern()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    return AceType::DynamicCast<ImageAnimatorPattern>(frameNode->GetPattern());
}

RefPtr<ImageAnimatorPattern> ImageAnimatorModelNG::GetImageAnimatorPattern(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    return AceType::DynamicCast<ImageAnimatorPattern>(frameNode->GetPattern());
}

RefPtr<FrameNode> ImageAnimatorModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ANIMATOR_ETS_TAG, nodeId, AceType::MakeRefPtr<ImageAnimatorPattern>());
    CHECK_NULL_RETURN(frameNode, nullptr);
    if (frameNode->GetChildren().empty()) {
        auto imageNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, -1, AceType::MakeRefPtr<ImagePattern>());
        CHECK_NULL_RETURN(imageNode, nullptr);
        auto imagePattern = AceType::DynamicCast<ImagePattern>(imageNode->GetPattern());
        CHECK_NULL_RETURN(imagePattern, nullptr);
        imagePattern->SetImageAnimator(true);
        auto imageLayoutProperty = AceType::DynamicCast<ImageLayoutProperty>(imageNode->GetLayoutProperty());
        CHECK_NULL_RETURN(imageLayoutProperty, nullptr);
        imageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
        frameNode->GetLayoutProperty()->UpdateAlignment(Alignment::TOP_LEFT);
        frameNode->AddChild(imageNode);
    }
    return frameNode;
}

void ImageAnimatorModelNG::SetImages(FrameNode* frameNode, const std::vector<ImageProperties>& images)
{
    CHECK_NULL_VOID(frameNode);
    InitImageNodeInImageAnimator(frameNode);
    std::vector<ImageProperties> imageList = images;
    auto imageAnimatorPattern = AceType::DynamicCast<ImageAnimatorPattern>(frameNode->GetPattern());
    imageAnimatorPattern->SetImages(std::move(imageList));
}

void ImageAnimatorModelNG::SetIsReverse(FrameNode* frameNode, bool isReverse)
{
    GetImageAnimatorPattern(frameNode)->SetIsReverse(isReverse);
}

void ImageAnimatorModelNG::SetDuration(FrameNode* frameNode, int32_t duration)
{
    CHECK_NULL_VOID(frameNode);
    AceType::DynamicCast<ImageAnimatorPattern>(frameNode->GetPattern())->SetDuration(duration);
}

void ImageAnimatorModelNG::SetState(FrameNode* frameNode, int32_t state)
{
    GetImageAnimatorPattern(frameNode)->SetStatus(static_cast<ControlledAnimator::ControlStatus>(state));
}

void ImageAnimatorModelNG::SetFixedSize(FrameNode* frameNode, bool fixedSize)
{
    GetImageAnimatorPattern(frameNode)->SetFixedSize(fixedSize);
}

void ImageAnimatorModelNG::SetFillMode(FrameNode* frameNode, int32_t fillMode)
{
    GetImageAnimatorPattern(frameNode)->SetFillMode(static_cast<FillMode>(fillMode));
}

void ImageAnimatorModelNG::SetIteration(FrameNode* frameNode, int32_t iteration)
{
    GetImageAnimatorPattern(frameNode)->SetIteration(iteration);
}

void ImageAnimatorModelNG::SetAutoMonitorInvisibleArea(FrameNode* frameNode, bool autoMonitorInvisibleArea)
{
    GetImageAnimatorPattern(frameNode)->SetAutoMonitorInvisibleArea(autoMonitorInvisibleArea);
}

bool ImageAnimatorModelNG::IsReverse(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = AceType::DynamicCast<ImageAnimatorPattern>(frameNode->GetPattern());
    CHECK_NULL_RETURN(pattern, false);
    return pattern->IsReverse();
}

int32_t ImageAnimatorModelNG::GetDuration(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, DEFAULT_DURATION);
    auto pattern = AceType::DynamicCast<ImageAnimatorPattern>(frameNode->GetPattern());
    CHECK_NULL_RETURN(pattern, DEFAULT_DURATION);
    return pattern->GetDuration();
}

int32_t ImageAnimatorModelNG::GetState(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    auto pattern = AceType::DynamicCast<ImageAnimatorPattern>(frameNode->GetPattern());
    CHECK_NULL_RETURN(pattern, 0);
    return static_cast<int32_t>(pattern->GetStatus());
}

bool ImageAnimatorModelNG::IsFixedSize(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, true);
    auto pattern = AceType::DynamicCast<ImageAnimatorPattern>(frameNode->GetPattern());
    CHECK_NULL_RETURN(pattern, true);
    return pattern->IsFixedSize();
}

int32_t ImageAnimatorModelNG::GetFillMode(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 1);
    auto pattern = AceType::DynamicCast<ImageAnimatorPattern>(frameNode->GetPattern());
    CHECK_NULL_RETURN(pattern, 1);
    return static_cast<int32_t>(pattern->GetFillMode());
}

int32_t ImageAnimatorModelNG::GetIteration(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 1);
    auto pattern = AceType::DynamicCast<ImageAnimatorPattern>(frameNode->GetPattern());
    CHECK_NULL_RETURN(pattern, 1);
    return pattern->GetIteration();
}

int32_t ImageAnimatorModelNG::GetImagesSize(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    auto pattern = AceType::DynamicCast<ImageAnimatorPattern>(frameNode->GetPattern());
    CHECK_NULL_RETURN(pattern, 0);
    return pattern->GetImagesSize();
}

void ImageAnimatorModelNG::SetOnStart(FrameNode* frameNode, std::function<void()>&& onStart)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<ImageAnimatorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetStartEvent(onStart);
}

void ImageAnimatorModelNG::SetOnPause(FrameNode* frameNode, std::function<void()>&& onPause)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<ImageAnimatorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetPauseEvent(onPause);
}

void ImageAnimatorModelNG::SetOnRepeat(FrameNode* frameNode, std::function<void()>&& onRepeat)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<ImageAnimatorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetRepeatEvent(onRepeat);
}

void ImageAnimatorModelNG::SetOnCancel(FrameNode* frameNode, std::function<void()>&& onCancel)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<ImageAnimatorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetCancelEvent(onCancel);
}

void ImageAnimatorModelNG::SetOnFinish(FrameNode* frameNode, std::function<void()>&& onFinish)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<ImageAnimatorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetStopEvent(onFinish);
}

} // namespace OHOS::Ace::NG
