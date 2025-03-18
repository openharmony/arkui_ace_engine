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

struct LaterAvoidInfo {
    bool laterAvoid = false;
    Rect keyboardArea;
    double positionY = 0.0;
    double avoidHeight = 0.0;
    int32_t orientation = -1;
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

    RectF GetFocusedNodeCaretRect();
    
    void TriggerAvoidOnCaretChange();

    void AvoidKeyboardInSheet(const RefPtr<FrameNode>& textField);

    void MovePage(int32_t pageId, const Offset& rootRect, double offsetHeight) override {}
    void RemovePageId(int32_t pageId) override {}

    WeakPtr<Pattern>& GetOnFocusTextField()
    {
        return onFocusTextField_;
    }

    void SetOnFocusTextField(const WeakPtr<Pattern>& onFocusTextField);

    void GetOnFocusTextFieldInfo(const WeakPtr<Pattern>& onFocusTextField);

    bool IsScrollableChild()
    {
        return isScrollableChild_;
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

    bool GetImeShow() const override;

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

    void TriggerCustomKeyboardAvoid();

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

    void SetNavContentAvoidKeyboardOffset(const RefPtr<FrameNode>& navNode, float avoidKeyboardOffset);

    void SetNeedToRequestKeyboard(bool val) override
    {
        needToRequestKeyboard_ = val;
    }

    bool GetNeedToRequestKeyboard() override
    {
        return needToRequestKeyboard_;
    }

    bool GetIfFocusTextFieldIsInline() {
        return focusFieldIsInline_;
    }

    void SetIfFocusTextFieldIsInline(bool isinline) {
        focusFieldIsInline_ = isinline;
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
        return onFocusTextFieldId_;
    }

    bool GetLaterAvoid() const
    {
        return laterAvoidInfo_.laterAvoid;
    }

    void SetLaterAvoid(bool laterAvoid)
    {
        laterAvoidInfo_.laterAvoid = laterAvoid;
    }

    void SetLaterAvoidArgs(LaterAvoidInfo laterAvoidInfo)
    {
        laterAvoidInfo_ = laterAvoidInfo;
    }

    Rect GetLaterAvoidKeyboardRect()
    {
        return laterAvoidInfo_.keyboardArea;
    }

    double GetLaterAvoidPositionY()
    {
        return laterAvoidInfo_.positionY;
    }

    double GetLaterAvoidHeight()
    {
        return laterAvoidInfo_.avoidHeight;
    }

    int32_t GetLaterOrientation()
    {
        return laterAvoidInfo_.orientation;
    }

    void SetLastRequestKeyboardId(int32_t lastRequestKeyboardId) {
        lastRequestKeyboardId_ = lastRequestKeyboardId;
    }

    int32_t GetLastRequestKeyboardId() {
        return lastRequestKeyboardId_;
    }

    void SetClickPositionOffset(float clickPositionOffset)
    {
        clickPositionOffset_ = clickPositionOffset;
    }

    float GetClickPositionOffset()
    {
        return clickPositionOffset_;
    }

    RefPtr<FrameNode> FindScrollableOfFocusedTextField(const RefPtr<FrameNode>& textField);
    void AddTextFieldInfo(const TextFieldInfo& textFieldInfo);
    void RemoveTextFieldInfo(const int32_t& autoFillContainerNodeId, const int32_t& nodeId);
    void UpdateTextFieldInfo(const TextFieldInfo& textFieldInfo);
    bool HasAutoFillPasswordNodeInContainer(const int32_t& autoFillContainerNodeId, const int32_t& nodeId);


    bool GetFocusFieldAlreadyTriggerWsCallback() const
    {
        return focusFieldAlreadyTriggerWsCallback_;
    }

    void SetFocusFieldAlreadyTriggerWsCallback(bool focusFieldAlreadyTriggerWsCallback) {
        focusFieldAlreadyTriggerWsCallback_ = focusFieldAlreadyTriggerWsCallback;
    }

    int32_t GetFocusFieldOrientation() const
    {
        return focusFieldOrientation_;
    }

    void SetFocusFieldOrientation(int32_t focusFieldOrientation)
    {
        focusFieldOrientation_ = focusFieldOrientation;
    }

    void SetIsImeAttached(bool isImeAttached)
    {
        isImeAttached_ = isImeAttached;
    }

    bool GetIsImeAttached() const override
    {
        return isImeAttached_;
    }

    void AddAvoidKeyboardCallback(int32_t id, bool isCustomKeyboard, const std::function<void()>&& callback);

    void RemoveAvoidKeyboardCallback(int32_t id)
    {
        avoidCustomKeyboardCallbacks_.erase(id);
        avoidSystemKeyboardCallbacks_.erase(id);
    }

    void OnAfterAvoidKeyboard(bool isCustomKeyboard);

private:
    bool ScrollToSafeAreaHelper(const SafeAreaInsets::Inset& bottomInset, bool isShowKeyboard);
    RefPtr<FrameNode> FindNavNode(const RefPtr<FrameNode>& textField);
    bool IsAutoFillPasswordType(const TextFieldInfo& textFieldInfo);

    bool focusFieldIsInline_ = false;
    double inlinePositionY_ = 0.0f;
    double inlineHeight_ = 0.0f;
    bool hasMove_ = false;
    bool imeShow_ = false;
    bool usingCustomKeyboardAvoid_ = false;
    bool uiExtensionImeShow_ = false;
    bool prevHasTextFieldPattern_ = true;
    bool focusFieldAlreadyTriggerWsCallback_ = false;
    int32_t focusFieldOrientation_ = -1;
    Offset position_;
    float clickPositionOffset_ = 0.0f;
    std::optional<Offset> optionalPosition_;
    float height_ = 0.0f;
    WeakPtr<Pattern> onFocusTextField_;
    WeakPtr<FrameNode> weakNavNode_;
    int32_t onFocusTextFieldId_ = -1;
    int32_t lastAvoidFieldId_ = -1;
    int32_t lastRequestKeyboardId_ = -1;
    bool imeAttachCalled_ = false;
    bool needToRequestKeyboard_ = true;
    std::unordered_map<int32_t, std::unordered_map<int32_t, TextFieldInfo>> textFieldInfoMap_;
    LaterAvoidInfo laterAvoidInfo_;
    bool isScrollableChild_ = false;
    bool isImeAttached_ = false;
    std::unordered_map<int32_t, std::function<void()>> avoidSystemKeyboardCallbacks_;
    std::unordered_map<int32_t, std::function<void()>> avoidCustomKeyboardCallbacks_;
    float lastKeyboardOffset_ = 0.0f;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_MANAGER_H
