/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/select_overlay/magnifier_controller.h"

#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void MagnifierController::UpdateShowMagnifier(bool isShowMagnifier)
{
    isShowMagnifier_ = isShowMagnifier;
    if (isShowMagnifier_) {
        OpenMagnifier();
    } else {
        CloseMagnifier();
    }
}

void MagnifierController::OpenMagnifier()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textBasePattern = DynamicCast<TextBase>(pattern);
    CHECK_NULL_VOID(textBasePattern);
    if (!magnifierFrameNode_) {
        CreateMagnifierChildNode();
    }
    CHECK_NULL_VOID(magnifierFrameNode_);
    auto layoutProperty = magnifierFrameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto rootUINode = overlayManager->GetRootNode().Upgrade();
    CHECK_NULL_VOID(rootUINode);
    if (rootUINode->GetChildIndexById(magnifierFrameNode_->GetId()) == -1) {
        magnifierFrameNode_->MountToParent(rootUINode);
    }
    auto childPattern = magnifierFrameNode_->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(childPattern);
    auto childContext = magnifierFrameNode_->GetRenderContext();
    CHECK_NULL_VOID(childContext);

    auto paintOffset = textBasePattern->GetTextPaintOffset();
    childContext->UpdatePosition(OffsetT<Dimension>(Dimension(paintOffset.GetX()), Dimension(paintOffset.GetY())));
    childContext->SetContentRectToFrame(RectF(paintOffset.GetX(), paintOffset.GetY(), 0.0f, 0.0f));

    SetMagnifierRect(childPattern);
    magnifierFrameNode_->ForceSyncGeometryNode();
    magnifierFrameNode_->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void MagnifierController::CloseMagnifier()
{
    CHECK_NULL_VOID(magnifierFrameNode_);
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textBasePattern = DynamicCast<TextBase>(pattern);
    CHECK_NULL_VOID(textBasePattern);

    auto layoutProperty = magnifierFrameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateVisibility(VisibleType::GONE);

    auto childContext = magnifierFrameNode_->GetRenderContext();
    CHECK_NULL_VOID(childContext);

    auto paintOffset = textBasePattern->GetTextPaintOffset();
    childContext->UpdatePosition(OffsetT<Dimension>(Dimension(paintOffset.GetX()), Dimension(paintOffset.GetY())));
    childContext->SetContentRectToFrame(RectF(paintOffset.GetX(), paintOffset.GetY(), 0.0f, 0.0f));
    magnifierFrameNode_->ForceSyncGeometryNode();
    magnifierFrameNode_->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void MagnifierController::CreateMagnifierChildNode()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textBasePattern = DynamicCast<TextBase>(pattern);
    CHECK_NULL_VOID(textBasePattern);

    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    ACE_SCOPED_TRACE("Create[%s][self:%d]", V2::TEXTINPUT_ETS_TAG, nodeId);
    auto childNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    CHECK_NULL_VOID(childNode);
    magnifierFrameNode_ = childNode;
    auto childPattern = childNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(childPattern);
    auto childController = childPattern->GetMagnifierController();
    CHECK_NULL_VOID(childController);

    magnifierRect_.parent = pattern_;
    magnifierRect_.childNodeId = childNode->GetId();
    magnifierRect_.isChildNode = true;
    childController->SetMagnifierRect(magnifierRect_);
    magnifierRect_.isChildNode = false;
}

void MagnifierController::SetMagnifierRect(const RefPtr<Pattern>& childPattern)
{
    auto childMagnifier = DynamicCast<Magnifier>(childPattern);
    CHECK_NULL_VOID(childMagnifier);
    auto childController = childMagnifier->GetMagnifierController();
    CHECK_NULL_VOID(childController);

    auto textBasepattern = DynamicCast<TextBase>(pattern_.Upgrade());
    CHECK_NULL_VOID(textBasepattern);

    auto contentRect = textBasepattern->GetPaintContentRect();
    magnifierRect_.localOffset = localOffset_;
    magnifierRect_.cursorOffset = textBasepattern->GetCaretOffset();
    magnifierRect_.contentSize = SizeF(contentRect.Width(), contentRect.Height());
    magnifierRect_.contentOffset = OffsetF(contentRect.GetX(), contentRect.GetY());
    magnifierRect_.isChildNode = true;
    childController->SetMagnifierRect(magnifierRect_);
    magnifierRect_.isChildNode = false;
}

RefPtr<PixelMap> MagnifierController::GetPixelMap()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, NULL);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_RETURN(overlayManager, NULL);
    auto rootUINode = overlayManager->GetRootNode().Upgrade();
    CHECK_NULL_RETURN(rootUINode, NULL);
    auto rootFrameNode = DynamicCast<FrameNode>(rootUINode);
    CHECK_NULL_RETURN(rootFrameNode, NULL);

    auto context = rootFrameNode->GetRenderContext();
    if (!context) {
        UpdateShowMagnifier();
    }
    CHECK_NULL_RETURN(context, NULL);
    auto pixelMap = context->GetThumbnailPixelMap();
    if (!pixelMap) {
        UpdateShowMagnifier();
    }
    CHECK_NULL_RETURN(pixelMap, NULL);
    return pixelMap;
}
} // namespace OHOS::Ace::NG
