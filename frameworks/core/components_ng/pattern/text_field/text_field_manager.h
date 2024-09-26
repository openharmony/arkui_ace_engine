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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_MANAGER_H

#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/common/ime/text_input_type.h"
#include "core/common/manager_interface.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/text_field/text_content_type.h"
#include "core/components_ng/property/safe_area_insets.h"

namespace OHOS::Ace::NG {

struct TextFieldInfo {
    int32_t nodeId = -1;
    TextInputType inputType;
    TextContentType contentType;
    int32_t autoFillContainerNodeId = -1;
    bool enableAutoFill = true;
};

class ACE_EXPORT TextFieldManagerNG : public ManagerInterface {
    DECLARE_ACE_TYPE(TextFieldManagerNG, ManagerInterface);

public:
    TextFieldManagerNG() = default;
    ~TextFieldManagerNG() override;

    void SetClickPosition(const Offset& position) override;
    const Offset& GetClickPosition() override
    {
        return position_;
    }

    const std::optional<Offset>& GetOptionalClickPosition()
    {
        return optionalPosition_;
    }

    void ResetOptionalClickPosition() {
        optionalPosition_ = std::nullopt;
    }

    void AvoidKeyboardInSheet(const RefPtr<FrameNode>& textField);

    void MovePage(int32_t pageId, const Offset& rootRect, double offsetHeight) override {}
    void RemovePageId(int32_t pageId) override {}

    WeakPtr<Pattern>& GetOnFocusTextField()
    {
        return onFocusTextField_;
    }

    void SetOnFocusTextField(const WeakPtr<Pattern>& onFocusTextField)
    {
        const auto& pattern = onFocusTextField.Upgrade();
        if (pattern && pattern->GetHost()) {
            onFocusTextFieldId = pattern->GetHost()->GetId();
        }
        if (onFocusTextField_ != onFocusTextField) {
            SetImeAttached(false);
        }
        onFocusTextField_ = onFocusTextField;
    }

    bool ScrollTextFieldToSafeArea();

    void ClearOnFocusTextField();

    void ClearOnFocusTextField(int32_t id);

    bool ResetSlidingPanelParentHeight();

    bool UpdatePanelForVirtualKeyboard(double offsetY, double fullHeight);
    void SetHeight(float height);

    float GetHeight() const
    {
        return height_;
    }

    bool OnBackPressed();

    void UpdateScrollableParentViewPort(const RefPtr<FrameNode>& node);

    bool GetImeShow() const override
    {
        if (!imeShow_ && imeAttachCalled_) {
            TAG_LOGI(ACE_KEYBOARD, "imeNotShown but attach called, still consider that as shown");
        }
        return imeShow_ || imeAttachCalled_;
    }

    void SetImeShow(bool imeShow)
    {
        imeShow_ = imeShow;
        imeAttachCalled_ = false;
    }

    void SetImeAttached(bool imeAttached)
    {
        imeAttachCalled_ = imeAttached;
    }

    bool UsingCustomKeyboardAvoid() {
        return usingCustomKeyboardAvoid_;
    }

    void SetUsingCustomKeyboardAvoid(bool usingCustomKeyboardAvoid) {
        usingCustomKeyboardAvoid_ = usingCustomKeyboardAvoid;
    }

    void SetUIExtensionImeShow(bool imeShow) override
    {
        uiExtensionImeShow_ = imeShow;
    }

    bool PrevHasTextFieldPattern() const
    {
        return prevHasTextFieldPattern_;
    }

    void UpdatePrevHasTextFieldPattern()
    {
        prevHasTextFieldPattern_ = onFocusTextField_.Upgrade();
    }

    bool HasKeyboard() const override
    {
        return imeShow_ || uiExtensionImeShow_;
    }

    void AvoidKeyBoardInNavigation();

    void SetNavContentAvoidKeyboardOffset(RefPtr<FrameNode> navNode, float avoidKeyboardOffset);

    void SetNeedToRequestKeyboard(bool val) override
    {
        needToRequestKeyboard_ = val;
    }

    bool GetNeedToRequestKeyboard() override
    {
        return needToRequestKeyboard_;
    }

    bool GetIfFocusTextFieldIsInline() {
        return focusFieldIsInline;
    }

    void SetIfFocusTextFieldIsInline(bool isinline) {
        focusFieldIsInline = isinline;
    }

    void GetInlineTextFieldAvoidPositionYAndHeight(double& positionY, double& height) {
        positionY = inlinePositionY_;
        height = inlineHeight_;
    }

    void SetInlineTextFieldAvoidPositionYAndHeight(double positionY, double height) {
        inlinePositionY_ = positionY;
        inlineHeight_ = height;
    }

    void SetLastAvoidFieldId(int32_t lastAvoidFieldId) {
        lastAvoidFieldId_ = lastAvoidFieldId;
    }

    int32_t GetLastAvoidFieldId() {
        return lastAvoidFieldId_;
    }

    int32_t GetOnFocusTextFieldId() {
        return onFocusTextFieldId;
    }

    bool GetLaterAvoid() const
    {
        return laterAvoid_;
    }

    void SetLaterAvoid(bool laterAvoid)
    {
        laterAvoid_ = laterAvoid;
    }

    void SetLaterAvoidArgs(Rect keyboardArea, double positionY, double height)
    {
        laterAvoid_ = true;
        laterAvoidKeyboardArea_ = keyboardArea;
        laterAvoidPositionY_ = positionY;
        laterAvoidHeight_ = height;
    }

    Rect GetLaterAvoidKeyboardRect()
    {
        return laterAvoidKeyboardArea_;
    }

    double GetLaterAvoidPositionY()
    {
        return laterAvoidPositionY_;
    }

    double GetLaterAvoidHeight()
    {
        return laterAvoidHeight_;
    }

    void SetLastRequestKeyboardId(int32_t lastRequestKeyboardId) {
        lastRequestKeyboardId_ = lastRequestKeyboardId;
    }

    int32_t GetLastRequestKeyboardId() {
        return lastRequestKeyboardId_;
    }

    void AddTextFieldInfo(const TextFieldInfo& textFieldInfo);
    void RemoveTextFieldInfo(const int32_t& autoFillContainerNodeId, const int32_t& nodeId);
    void UpdateTextFieldInfo(const TextFieldInfo& textFieldInfo);
    bool HasAutoFillPasswordNodeInContainer(const int32_t& autoFillContainerNodeId, const int32_t& nodeId);

private:
    bool ScrollToSafeAreaHelper(const SafeAreaInsets::Inset& bottomInset, bool isShowKeyboard);
    RefPtr<FrameNode> FindScrollableOfFocusedTextField(const RefPtr<FrameNode>& textField);
    RefPtr<FrameNode> FindNavNode(const RefPtr<FrameNode>& textField);
    bool IsAutoFillPasswordType(const TextFieldInfo& textFieldInfo);

    bool focusFieldIsInline = false;
    double inlinePositionY_ = 0.0f;
    double inlineHeight_ = 0.0f;
    bool hasMove_ = false;
    bool imeShow_ = false;
    bool usingCustomKeyboardAvoid_ = false;
    bool uiExtensionImeShow_ = false;
    bool prevHasTextFieldPattern_ = true;
    Offset position_;
    std::optional<Offset> optionalPosition_;
    float height_ = 0.0f;
    WeakPtr<Pattern> onFocusTextField_;
    WeakPtr<FrameNode> weakNavNode_;
    int32_t onFocusTextFieldId = -1;
    int32_t lastAvoidFieldId_ = -1;
    int32_t lastRequestKeyboardId_ = -1;
    bool imeAttachCalled_ = false;
    bool needToRequestKeyboard_ = true;
    std::unordered_map<int32_t, std::unordered_map<int32_t, TextFieldInfo>> textFieldInfoMap_;
    bool laterAvoid_ = false;
    Rect laterAvoidKeyboardArea_;
    double laterAvoidPositionY_ = 0.0;
    double laterAvoidHeight_ = 0.0;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_MANAGER_H
