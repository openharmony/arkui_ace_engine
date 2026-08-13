/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2023-2024. All rights reserved.
 */

#include "core/components_ng/pattern/cached_image/cached_image_model_ng.h"

#include "core/components/image/image_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/cached_image/cached_image_pattern.h"

namespace OHOS::Ace::NG {

void CachedImageModelNG::Create(const std::string& src, RefPtr<PixelMap>& pixMap)
{
    PushFrameNode();
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<CachedImagePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->Create(src, pixMap);
}

void CachedImageModelNG::Create(const std::vector<std::string>& sources, uint32_t column)
{
    PushFrameNode();
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<CachedImagePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->Create(sources, column);
}

void CachedImageModelNG::PushFrameNode()
{
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_VOID(stack);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        "CachedImage", nodeId, []() { return AceType::MakeRefPtr<CachedImagePattern>(); });
    stack->Push(frameNode);

    if (frameNode->IsFirstBuilding()) {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto isDraggable = pipeline->GetDraggable<ImageTheme>();
        if (isDraggable && !frameNode->IsDraggable()) {
            auto gestureHub = frameNode->GetOrCreateGestureEventHub();
            CHECK_NULL_VOID(gestureHub);
            gestureHub->InitDragDropEvent();
        }
        frameNode->SetDraggable(isDraggable);
    }
    auto renderProps = frameNode->GetPaintProperty<ImageRenderProperty>();
    if (renderProps != nullptr) {
        renderProps->ResetNeedBorderRadius();
    }
}

void CachedImageModelNG::SetImageSourceSize(const std::pair<Dimension, Dimension>& size)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<CachedImagePattern>();
    CHECK_NULL_VOID(pattern);
    SizeF sourceSize =
        SizeF(static_cast<float>(size.first.ConvertToPx()), static_cast<float>(size.second.ConvertToPx()));
    pattern->SetRequestOptions(sourceSize);
    ACE_UPDATE_LAYOUT_PROPERTY(ImageLayoutProperty, SourceSize, sourceSize);
}

void CachedImageModelNG::SetCachedImageSrc(FrameNode* frameNode, const std::string& src, RefPtr<PixelMap>& pixMap)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<CachedImagePattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->Create(src, pixMap);
}
 
void CachedImageModelNG::SetCachedImageASTC(FrameNode* frameNode,
    const std::vector<std::string>& sources, uint32_t column)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<CachedImagePattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->Create(sources, column);
}

void CachedImageModelNG::SetCachedImageAlt(FrameNode* frameNode, RefPtr<PixelMap>& pixelMap)
{
    CHECK_NULL_VOID(pixelMap);
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<CachedImagePattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetAlt(pixelMap);
}

void CachedImageModelNG::SetAlt(const ImageSourceInfo& src)
{
    auto pixelMap = src.GetPixmap();
    CHECK_NULL_VOID(pixelMap);
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<CachedImagePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetAlt(pixelMap);
}

} // namespace OHOS::Ace::NG