/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/components_ng/pattern/text_field/text_field_manager.h"

namespace OHOS::Ace::NG {
TextFieldManagerNG::~TextFieldManagerNG() = default;

void TextFieldManagerNG::SetClickPosition(const Offset& position)
{
    position_ = position;
    optionalPosition_ = position;
}

RectF TextFieldManagerNG::GetFocusedNodeCaretRect()
{
    return {};
}

void TextFieldManagerNG::TriggerAvoidOnCaretChange() {}

void TextFieldManagerNG::AvoidKeyboardInSheet(const RefPtr<FrameNode>& textField)
{
    (void)textField;
}

void TextFieldManagerNG::SetOnFocusTextField(const WeakPtr<Pattern>& onFocusTextField)
{
    onFocusTextField_ = onFocusTextField;
}

void TextFieldManagerNG::GetOnFocusTextFieldInfo(const WeakPtr<Pattern>& onFocusTextField)
{
    (void)onFocusTextField;
}

bool TextFieldManagerNG::ScrollTextFieldToSafeArea()
{
    prevHasTextFieldPattern_ = true;
    return false;
}

void TextFieldManagerNG::ClearOnFocusTextField()
{
    onFocusTextField_ = nullptr;
    onFocusTextFieldId_ = -1;
}

void TextFieldManagerNG::ClearOnFocusTextField(int32_t id)
{
    if (onFocusTextFieldId_ == id) {
        ClearOnFocusTextField();
    }
}

bool TextFieldManagerNG::ResetSlidingPanelParentHeight()
{
    return false;
}

bool TextFieldManagerNG::UpdatePanelForVirtualKeyboard(double offsetY, double fullHeight)
{
    (void)offsetY;
    (void)fullHeight;
    return false;
}

void TextFieldManagerNG::SetHeight(float height)
{
    height_ = height;
}

bool TextFieldManagerNG::OnBackPressed()
{
    return false;
}

void TextFieldManagerNG::UpdateScrollableParentViewPort(const RefPtr<FrameNode>& node)
{
    (void)node;
}

bool TextFieldManagerNG::GetImeShow() const
{
    return imeShow_ || uiExtensionImeShow_;
}

void TextFieldManagerNG::TriggerCustomKeyboardAvoid() {}

void TextFieldManagerNG::AvoidKeyBoardInNavigation() {}

void TextFieldManagerNG::SetNavContentAvoidKeyboardOffset(const RefPtr<FrameNode>& navNode, float avoidKeyboardOffset)
{
    (void)navNode;
    (void)avoidKeyboardOffset;
}

void TextFieldManagerNG::TriggerCaretInfoUpdateOnScaleChange() {}

void TextFieldManagerNG::AddAvoidKeyboardCallback(
    int32_t id, bool isCustomKeyboard, const std::function<void()>&& callback)
{
    if (isCustomKeyboard) {
        avoidCustomKeyboardCallbacks_[id] = callback;
    } else {
        avoidSystemKeyboardCallbacks_[id] = callback;
    }
}

void TextFieldManagerNG::OnAfterAvoidKeyboard(bool isCustomKeyboard)
{
    auto& callbacks = isCustomKeyboard ? avoidCustomKeyboardCallbacks_ : avoidSystemKeyboardCallbacks_;
    for (const auto& item : callbacks) {
        if (item.second) {
            item.second();
        }
    }
}

RefPtr<FrameNode> TextFieldManagerNG::FindScrollableOfFocusedTextField(const RefPtr<FrameNode>& textField)
{
    (void)textField;
    return nullptr;
}

void TextFieldManagerNG::AddTextFieldInfo(const TextFieldInfo& textFieldInfo)
{
    textFieldInfoMap_[textFieldInfo.autoFillContainerNodeId][textFieldInfo.nodeId] = textFieldInfo;
}

void TextFieldManagerNG::RemoveTextFieldInfo(const int32_t& autoFillContainerNodeId, const int32_t& nodeId)
{
    auto containerIter = textFieldInfoMap_.find(autoFillContainerNodeId);
    if (containerIter == textFieldInfoMap_.end()) {
        return;
    }
    containerIter->second.erase(nodeId);
}

void TextFieldManagerNG::UpdateTextFieldInfo(const TextFieldInfo& textFieldInfo)
{
    AddTextFieldInfo(textFieldInfo);
}

bool TextFieldManagerNG::HasAutoFillPasswordNodeInContainer(const int32_t& autoFillContainerNodeId, const int32_t& nodeId)
{
    (void)autoFillContainerNodeId;
    (void)nodeId;
    return false;
}

bool TextFieldManagerNG::NeedCloseKeyboard()
{
    return false;
}

void TextFieldManagerNG::ProcessCustomKeyboard(bool matched, int32_t nodeId)
{
    (void)matched;
    (void)nodeId;
}

void TextFieldManagerNG::CloseTextCustomKeyboard(int32_t nodeId, bool isUIExtension)
{
    (void)nodeId;
    (void)isUIExtension;
}

bool TextFieldManagerNG::ParseFillContentJsonValue(const std::unique_ptr<JsonValue>& jsonObject)
{
    (void)jsonObject;
    return false;
}

FillContentMap TextFieldManagerNG::GetFillContentMap(int32_t id)
{
    auto iter = textFieldFillContentMaps_.find(id);
    if (iter == textFieldFillContentMaps_.end()) {
        return {};
    }
    return iter->second;
}

void TextFieldManagerNG::RemoveFillContentMap(int32_t id)
{
    textFieldFillContentMaps_.erase(id);
}

void TextFieldManagerNG::SetIsAskCeliaSupported(bool isAskCeliaSupported)
{
    isAskCeliaSupported_ = isAskCeliaSupported;
}

std::optional<bool> TextFieldManagerNG::IsAskCeliaSupported()
{
    return isAskCeliaSupported_;
}
} // namespace OHOS::Ace::NG
