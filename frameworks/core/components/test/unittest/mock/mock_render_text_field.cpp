/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "base/geometry/offset.h"
#include "core/components/text_field/render_text_field.h"
#include "core/components/text_overlay/text_overlay_component.h"

namespace OHOS::Ace {
#if defined(ENABLE_STANDARD_INPUT)
void RenderTextField::UpdateConfiguration()
{
}
#endif

RenderTextField::RenderTextField()
    : twinklingInterval(0), controller_(nullptr)
{}

RenderTextField::~RenderTextField()
{
}

void RenderTextField::Update(const RefPtr<Component>& component)
{
}

void RenderTextField::SetCallback(const RefPtr<TextFieldComponent>& textField)
{
    onCopy_ = nullptr;
    onCut_ = nullptr;
    onPaste_ = nullptr;
}

void RenderTextField::OnPaintFinish()
{
}

void RenderTextField::PerformLayout()
{
}

bool RenderTextField::HandleMouseEvent(const MouseEvent& event)
{
    return false;
}

void RenderTextField::OnTouchTestHit(
    const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result)
{
}

void RenderTextField::StartPressAnimation(bool pressDown)
{
}

void RenderTextField::StartHoverAnimation(bool isHovered)
{
    hoverController_ = nullptr;
}

void RenderTextField::AnimateMouseHoverEnter()
{
}

void RenderTextField::AnimateMouseHoverExit()
{
}

void RenderTextField::OnClick(const ClickInfo& clickInfo)
{
}

void RenderTextField::OnEditChange(bool isInEditStatus)
{
    isInEditStatus_ = false;
}

void RenderTextField::AddOutOfRectCallbackToContext()
{
}

void RenderTextField::GetFieldAndOverlayTouchRect(std::vector<Rect>& resRectList)
{
}

bool RenderTextField::SearchAction(const Offset& globalPosition, const Offset& globalOffset)
{
    return false;
}

void RenderTextField::OnDoubleClick(const ClickInfo& clickInfo)
{
}

void RenderTextField::OnLongPress(const LongPressInfo& longPressInfo)
{
}

void RenderTextField::ShowTextOverlay(const Offset& showOffset, bool isSingleHandle, bool isUsingMouse)
{
}

void RenderTextField::InitAnimation()
{
}

void RenderTextField::RegisterCallbacksToOverlay()
{
}

void RenderTextField::PushTextOverlayToStack()
{
}

void RenderTextField::PopTextOverlay()
{
    isOverlayShowed_ = false;
}

RefPtr<RenderSlidingPanel> RenderTextField::GetSlidingPanelAncest()
{
    return nullptr;
}

void RenderTextField::ResetSlidingPanelParentHeight()
{
}

void RenderTextField::ResetOnFocusForTextFieldManager()
{
}

bool RenderTextField::RequestKeyboard(bool isFocusViewChanged, bool needStartTwinkling)
{
    return false;
}

bool RenderTextField::CloseKeyboard(bool forceClose)
{
    return false;
}

void RenderTextField::AttachIme()
{
}

void RenderTextField::StartTwinkling()
{
}

void RenderTextField::StopTwinkling()
{
}

const TextEditingValue& RenderTextField::GetEditingValue() const
{
    static TextEditingValue textEdit;
    return textEdit;
}

const TextEditingValue& RenderTextField::GetPreEditingValue() const
{
    static TextEditingValue textEdit;
    return textEdit;
}

void RenderTextField::SetEditingValue(TextEditingValue&& newValue, bool needFireChangeEvent, bool isClearRecords)
{
}

void RenderTextField::SetEditingValue(const std::string& text)
{
}

void RenderTextField::ClearEditingValue()
{
}

std::u16string RenderTextField::GetTextForDisplay(const std::string& text) const
{
    return std::u16string();
}

void RenderTextField::UpdateObscure(const RefPtr<TextFieldComponent>& textField)
{
}

void RenderTextField::UpdateFormatters()
{
}

std::wstring WstringSearch(std::wstring wideText, const std::wregex& regex)
{
    return std::wstring();
}

void RenderTextField::EditingValueFilter(TextEditingValue& result)
{
}

void RenderTextField::UpdateEditingValue(const std::shared_ptr<TextEditingValue>& value, bool needFireChangeEvent)
{
}

void RenderTextField::PerformDefaultAction()
{
}

void RenderTextField::PerformAction(TextInputAction action, bool forceCloseKeyboard)
{
}

Size RenderTextField::Measure()
{
    return Size();
}

void RenderTextField::ScheduleCursorTwinkling()
{
}

void RenderTextField::OnCursorTwinkling()
{
}

bool RenderTextField::OnKeyEvent(const KeyEvent& event)
{
    return false;
}

void RenderTextField::UpdateFocusStyles()
{
}

void RenderTextField::UpdateFocusAnimation()
{
}

void RenderTextField::UpdateIcon(const RefPtr<TextFieldComponent>& textField)
{
}

void RenderTextField::UpdatePasswordIcon(const RefPtr<TextFieldComponent>& textField)
{
}

void RenderTextField::UpdateOverlay()
{
}

void RenderTextField::RegisterFontCallbacks()
{
}

void RenderTextField::OnStatusChanged(OHOS::Ace::RenderStatus renderStatus)
{
}

void RenderTextField::OnValueChanged(bool needFireChangeEvent, bool needFireSelectChangeEvent)
{
}

void RenderTextField::FireSelectChangeIfNeeded(const TextEditingValue& newValue, bool needFireSelectChangeEvent) const
{
}

void RenderTextField::CursorMoveLeft(CursorMoveSkip skip)
{
}

void RenderTextField::CursorMoveRight(CursorMoveSkip skip)
{
}

void RenderTextField::CursorMoveUp()
{
}

void RenderTextField::CursorMoveDown()
{
}

void RenderTextField::CursorMoveOnClick(const Offset& offset)
{
}

void RenderTextField::UpdateSelection(int32_t both)
{
}

void RenderTextField::UpdateSelection(int32_t start, int32_t end)
{
}

void RenderTextField::UpdateRemoteEditing(bool needFireChangeEvent)
{
}

void RenderTextField::UpdateRemoteEditingIfNeeded(bool needFireChangeEvent)
{
}

void RenderTextField::ShowError(const std::string& errorText, bool resetToStart)
{
}

void RenderTextField::SetOnValueChange(const std::function<void()>& onValueChange)
{
    onValueChange_ = onValueChange;
}

const std::function<void()>& RenderTextField::GetOnValueChange() const
{
    return onValueChange_;
}

void RenderTextField::SetOnKeyboardClose(const std::function<void(bool)>& onKeyboardClose)
{
    onKeyboardClose_ = onKeyboardClose;
}

void RenderTextField::SetOnClipRectChanged(const std::function<void(const Rect&)>& onClipRectChanged)
{
    onClipRectChanged_ = onClipRectChanged;
}

void RenderTextField::SetUpdateHandlePosition(const std::function<void(const OverlayShowOption&)>& updateHandlePosition)
{
    updateHandlePosition_ = updateHandlePosition;
}

void RenderTextField::SetUpdateHandleDiameter(const std::function<void(const double&)>& updateHandleDiameter)
{
    updateHandleDiameter_ = updateHandleDiameter;
}

void RenderTextField::SetUpdateHandleDiameterInner(const std::function<void(const double&)>& updateHandleDiameterInner)
{
    updateHandleDiameterInner_ = updateHandleDiameterInner;
}

void RenderTextField::SetIsOverlayShowed(bool isOverlayShowed, bool needStartTwinkling)
{
    isOverlayShowed_ = isOverlayShowed;
}

void RenderTextField::HandleOnSelect(KeyCode keyCode, CursorMoveSkip skip)
{
}

void RenderTextField::HandleOnRevoke()
{
}

void RenderTextField::HandleOnInverseRevoke()
{
}

void RenderTextField::HandleOnCut()
{
}

void RenderTextField::HandleOnCopy()
{
}

void RenderTextField::HandleOnPaste()
{
}

void RenderTextField::HandleOnCopyAll(const std::function<void(const Offset&, const Offset&)>& callback)
{
}

void RenderTextField::HandleOnStartHandleMove(int32_t end, const Offset& startHandleOffset,
    const std::function<void(const Offset&)>& startCallback, bool isSingleHandle)
{
}

void RenderTextField::HandleOnEndHandleMove(
    int32_t start, const Offset& endHandleOffset, const std::function<void(const Offset&)>& endCallback)
{
}

RefPtr<StackElement> RenderTextField::GetLastStack() const
{
    return nullptr;
}

bool RenderTextField::HandleKeyEvent(const KeyEvent& event)
{
    return false;
}

void RenderTextField::InitAccessibilityEventListener()
{
}

void RenderTextField::UpdateDirectionStatus()
{
}

void RenderTextField::UpdateStartSelection(int32_t end, const Offset& pos, bool isSingleHandle, bool isLongPress)
{
}

void RenderTextField::UpdateEndSelection(int32_t start, const Offset& pos)
{
}

Offset RenderTextField::GetPositionForExtend(int32_t extend, bool isSingleHandle)
{
    return Offset();
}

int32_t RenderTextField::GetGraphemeClusterLength(int32_t extend, bool isPrefix) const
{
    return 0;
}

bool RenderTextField::ShowCounter() const
{
    return false;
}

void RenderTextField::ChangeCounterStyle(const TextEditingValue& value)
{
}

void RenderTextField::ChangeBorderToErrorStyle()
{
}

void RenderTextField::HandleDeviceOrientationChange()
{
}

void RenderTextField::OnHiddenChanged(bool hidden)
{
}

void RenderTextField::OnAppHide()
{
}

void RenderTextField::OnOverlayFocusChange(bool isFocus, bool needCloseKeyboard)
{
}

int32_t RenderTextField::GetInstanceId() const
{
    return 0;
}

void RenderTextField::Insert(const std::string& text)
{
}

void RenderTextField::Delete(int32_t start, int32_t end)
{
}

std::string RenderTextField::ProvideRestoreInfo()
{
    return std::string();
}

void RenderTextField::ApplyRestoreInfo()
{
}

void RenderTextField::ApplyAspectRatio()
{
}

void RenderTextField::Dump()
{
}
} // namespace OHOS::Ace
