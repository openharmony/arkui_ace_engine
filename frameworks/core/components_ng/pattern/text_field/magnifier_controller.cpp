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
#include "core/components_ng/pattern/text_field/magnifier_controller.h"

#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void MagnifierController::OpenMagnifier()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textFieldpattern = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textFieldpattern);
    auto magnifierRect = textFieldpattern->GetMagnifierRect();
    if (!magnifierFrameNode_) {
        CreateMagnifierChildNode();
    }
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
    childContext->UpdatePosition(OffsetT<Dimension>(Dimension(textFieldpattern->GetTextPaintOffset().GetX()),
        Dimension(textFieldpattern->GetTextPaintOffset().GetY())));
    childContext->SetContentRectToFrame(RectF(
        textFieldpattern->GetTextPaintOffset().GetX(), textFieldpattern->GetTextPaintOffset().GetY(), 0.0f, 0.0f));

    SetMagnifierRect(childPattern);
    magnifierFrameNode_->ForceSyncGeometryNode();
    magnifierFrameNode_->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    return;
}

void MagnifierController::CloseMagnifier()
{
    CHECK_NULL_VOID(magnifierFrameNode_);
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textFieldpattern = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textFieldpattern);
    auto magnifierRect = textFieldpattern->GetMagnifierRect();
    auto childContext = magnifierFrameNode_->GetRenderContext();
    CHECK_NULL_VOID(childContext);
    childContext->UpdatePosition(OffsetT<Dimension>(Dimension(textFieldpattern->GetTextPaintOffset().GetX()),
        Dimension(textFieldpattern->GetTextPaintOffset().GetY())));
    childContext->SetContentRectToFrame(RectF(
        textFieldpattern->GetTextPaintOffset().GetX(), textFieldpattern->GetTextPaintOffset().GetY(), 0.0f, 0.0f));
    magnifierFrameNode_->ForceSyncGeometryNode();
    magnifierFrameNode_->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void MagnifierController::CreateMagnifierChildNode()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textFieldpattern = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textFieldpattern);
    auto host = textFieldpattern->GetHost();
    CHECK_NULL_VOID(host);
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    ACE_SCOPED_TRACE("Create[%s][self:%d]", V2::TEXTINPUT_ETS_TAG, nodeId);
    auto childNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    CHECK_NULL_VOID(childNode);
    magnifierFrameNode_ = childNode;
    auto childPattern = childNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(childPattern);
    auto magnifierRect = textFieldpattern->GetMagnifierRect();
    magnifierRect.parent = pattern_;
    magnifierRect.childNodeId = childNode->GetId();
    magnifierRect.isChildNode = true;
    childPattern->SetMagnifierRect(magnifierRect);
    magnifierRect.isChildNode = false;
    textFieldpattern->SetMagnifierRect(magnifierRect);
}

void MagnifierController::SetMagnifierRect(const RefPtr<Pattern>& childTextFieldPattern)
{
    CHECK_NULL_VOID(childTextFieldPattern);
    auto childPattern = DynamicCast<TextFieldPattern>(childTextFieldPattern);
    CHECK_NULL_VOID(childPattern);
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textFieldpattern = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textFieldpattern);
    auto magnifierRect = textFieldpattern->GetMagnifierRect();
    magnifierRect.localOffset = textFieldpattern->GetLocalOffset();
    magnifierRect.cursorOffset = textFieldpattern->GetCaretOffset();
    magnifierRect.contentSize =
        SizeF(textFieldpattern->GetContentRect().Width(), textFieldpattern->GetContentRect().Height());
    magnifierRect.contentOffset =
        OffsetF(textFieldpattern->GetContentRect().GetX(), textFieldpattern->GetContentRect().GetY());
    magnifierRect.isChildNode = true;
    childPattern->SetMagnifierRect(magnifierRect);
    magnifierRect.isChildNode = false;
    textFieldpattern->SetMagnifierRect(magnifierRect);
}
} // namespace OHOS::Ace::NG
