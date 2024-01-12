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

namespace OHOS::Ace::NG {

void MagnifierController::OpenMagnifier()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textFieldpattern = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textFieldpattern);
    auto magnifierRect = textFieldpattern->GetMagnifierRect();
    auto host = textFieldpattern->GetHost();
    CHECK_NULL_VOID(host);

    if (!haveChildNode_) {
        CreateMagnifierChildNode();
    }

    auto rootId = host->GetRootId();
    auto parent = host->GetParent();
    CHECK_NULL_VOID(parent);
    while (!parent->IsRootNode() || parent->GetId() != rootId) {
        parent = parent->GetParent();
        CHECK_NULL_VOID(parent);
    }

    auto index = parent->GetChildIndexById(magnifierRect.childNodeId);
    auto childUINode = parent->GetChildAtIndex(index);
    CHECK_NULL_VOID(childUINode);
    auto childNode = AceType::DynamicCast<FrameNode>(childUINode);
    CHECK_NULL_VOID(childNode);
    auto childPattern = childNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(childPattern);
    auto childContext = childNode->GetRenderContext();
    CHECK_NULL_VOID(childContext);
    childContext->UpdatePosition(OffsetT<Dimension>(Dimension(textFieldpattern->GetTextPaintOffset().GetX()),
        Dimension(textFieldpattern->GetTextPaintOffset().GetY())));
    childContext->SetContentRectToFrame(RectF(
        textFieldpattern->GetTextPaintOffset().GetX(), textFieldpattern->GetTextPaintOffset().GetY(), 0.0f, 0.0f));

    SetMagnifierRect(childPattern);
    childNode->ForceSyncGeometryNode();
    childNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    return;
}

void MagnifierController::CloseMagnifier()
{
    if (!haveChildNode_) {
        return;
    }
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textFieldpattern = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(textFieldpattern);
    auto magnifierRect = textFieldpattern->GetMagnifierRect();
    auto host = textFieldpattern->GetHost();
    CHECK_NULL_VOID(host);
    auto parent = host->GetParent();
    CHECK_NULL_VOID(parent);
    auto rootId = host->GetRootId();
    while (!parent->IsRootNode() || parent->GetId() != rootId) {
        parent = parent->GetParent();
        CHECK_NULL_VOID(parent);
    }
    auto index = parent->GetChildIndexById(magnifierRect.childNodeId);
    if (index != -1) {
        auto child = parent->GetChildAtIndex(index);
        CHECK_NULL_VOID(child);
        parent->RemoveChild(child);
    }
    haveChildNode_ = false;
}

void MagnifierController::CreateMagnifierChildNode()
{
    if (haveChildNode_) {
        return;
    }
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

    auto rootId = host->GetRootId();
    auto parent = host->GetParent();
    CHECK_NULL_VOID(parent);
    while (!parent->IsRootNode() || parent->GetId() != rootId) {
        parent = parent->GetParent();
        CHECK_NULL_VOID(parent);
    }
    if (parent->GetChildIndexById(childNode->GetId()) == -1) {
        childNode->MountToParent(parent);
    }
    haveChildNode_ = true;

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
    auto host = textFieldpattern->GetHost();
    CHECK_NULL_VOID(host);
    auto textFieldTheme = textFieldpattern->GetTheme();
    CHECK_NULL_VOID(textFieldTheme);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto bgColor = renderContext->GetBackgroundColor().value_or(textFieldTheme->GetBgColor());
    magnifierRect.bgColor = ToRSColor(bgColor);
    magnifierRect.localOffset = textFieldpattern->GetLocalOffset();
    magnifierRect.pixelMap = textFieldpattern->GetPixelMap();
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
