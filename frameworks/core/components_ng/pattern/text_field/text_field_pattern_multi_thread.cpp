/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text_field/text_field_pattern.h"

#include <algorithm>
#include <atomic>
#include <cstdint>
#include <optional>
#include <ratio>
#include <regex>
#include <string>
#include <utility>
#include "base/geometry/dimension.h"
#include "base/log/event_report.h"
#include "base/memory/type_info_base.h"
#include "base/utils/utf_helper.h"
#include "core/common/ime/constant.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text_field/text_component_decorator.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/pipeline/pipeline_base.h"
#include "interfaces/inner_api/ui_session/ui_session_manager.h"
#include "base/i18n/localization.h"
#include "base/log/dump_log.h"
#include "base/log/log_wrapper.h"
#include "base/memory/referenced.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "core/common/clipboard/clipboard_proxy.h"
#include "core/common/container_scope.h"
#include "core/common/font_manager.h"
#include "core/common/ime/input_method_manager.h"
#include "core/common/ime/text_edit_controller.h"
#include "core/common/ime/text_input_client.h"
#include "core/common/ime/text_input_connection.h"
#include "core/common/ime/text_input_formatter.h"
#include "core/common/ime/text_input_type.h"
#include "core/common/ime/text_selection.h"
#include "core/common/recorder/event_recorder.h"
#include "core/common/recorder/node_data_cache.h"
#include "core/common/stylus/stylus_detector_mgr.h"
#include "core/common/vibrator/vibrator_utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/image_provider/image_loading_context.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/overlay/modal_style.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/search/search_event_hub.h"
#include "core/components_ng/pattern/search/search_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/text/span/span_string.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/text_field/text_field_paint_property.h"
#include "core/text/text_emoji_processor.h"
#ifndef ACE_UNITTEST
#ifdef ENABLE_STANDARD_INPUT
#include "parameters.h"

#include "core/components_ng/pattern/text_field/on_text_changed_listener_impl.h"
#endif
#endif
#include "core/common/udmf/udmf_client.h"
#ifdef WINDOW_SCENE_SUPPORTED
#include "core/components_ng/pattern/window_scene/helper/window_scene_helper.h"
#endif

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t PREVIEW_TEXT_RANGE_DEFAULT = -1;
const std::string DROP_TYPE_STYLED_STRING = "ApplicationDefinedType";
} // namespace

void TextFieldPattern::OnAttachToFrameNodeMultiThread()
{
    // nothing, thread unsafe
}

void TextFieldPattern::OnDetachFromFrameNodeMultiThread(FrameNode* node)
{
    // nothing, thread unsafe
}

void TextFieldPattern::OnAttachToMainTreeMultiThread()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    
    StylusDetectorMgr::GetInstance()->AddTextFieldFrameNode(host, WeakClaim(this));

    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateCopyOptions(CopyOptions::Local);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto fontManager = pipeline->GetFontManager();
    if (fontManager) {
        auto host = GetHost();
        fontManager->AddFontNodeNG(host);
    }
    auto onTextSelectorChange = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        host->OnAccessibilityEvent(AccessibilityEventType::TEXT_SELECTION_UPDATE);
    };
    selectController_->SetOnAccessibility(std::move(onTextSelectorChange));
    isDetachFromMainTree_ = false;
    auto autoFillContainerNode = host->GetFirstAutoFillContainerNode();
    CHECK_NULL_VOID(autoFillContainerNode);
    firstAutoFillContainerNode_ = WeakClaim(RawPtr(autoFillContainerNode));
    AddTextFieldInfo();
    OnAttachToMainTreeMultiThreadAddition();
}

void TextFieldPattern::OnAttachToMainTreeMultiThreadAddition()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    if (initSurfacePositionChangedCallbackMultiThread_) {
        initSurfacePositionChangedCallbackMultiThread_ = false;
        InitSurfacePositionChangedCallbackMultiThreadAction();
    }
    if (initSurfaceChangedCallbackMultiThread_) {
        initSurfaceChangedCallbackMultiThread_ = false;
        InitSurfaceChangedCallbackMultiThreadAction();
    }
    if (registerWindowSizeCallbackMultiThread_) {
        registerWindowSizeCallbackMultiThread_ = false;
        RegisterWindowSizeCallbackMultiThreadAction();
    }
    if (processDefaultStyleAndBehaviorsMultiThread_) {
        processDefaultStyleAndBehaviorsMultiThread_ = false;
        ProcessDefaultStyleAndBehaviorsMultiThread();
    }
    if (handleCountStyleMultiThread_) {
        handleCountStyleMultiThread_ = false;
        HandleCountStyle();
    }
    if (startTwinklingMultiThread_) {
        startTwinklingMultiThread_ = false;
        StartTwinkling();
    }
}

void TextFieldPattern::OnDetachFromMainTreeMultiThread()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    isDetachFromMainTree_ = true;
    RemoveTextFieldInfo();
    FrameNode* node = RawPtr(host);
    CloseSelectOverlay();
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    if (HasSurfaceChangedCallback()) {
        pipeline->UnregisterSurfaceChangedCallback(surfaceChangedCallbackId_.value_or(-1));
    }
    if (HasSurfacePositionChangedCallback()) {
        pipeline->UnregisterSurfacePositionChangedCallback(surfacePositionChangedCallbackId_.value_or(-1));
    }
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
    if (textFieldManager) {
        textFieldManager->ClearOnFocusTextField(node->GetId());
    }
    auto frameNode = WeakClaim(node);
    pipeline->RemoveFontNodeNG(frameNode);
    auto fontManager = pipeline->GetFontManager();
    if (fontManager) {
        fontManager->UnRegisterCallbackNG(frameNode);
        fontManager->RemoveVariationNodeNG(frameNode);
    }
    pipeline->RemoveWindowSizeChangeCallback(node->GetId());
    pipeline->RemoveOnAreaChangeNode(node->GetId());
}

void TextFieldPattern::HandleSetSelectionMultiThread(int32_t start, int32_t end, bool showHandle)
{
    auto host = GetHost();
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "HandleSetSelection %{public}d, %{public}d, showOverlay:%{public}d", start, end,
        showHandle);
    StopTwinkling();
    UpdateSelection(start, end);
    if (showHandle) {
        ProcessOverlay();
    } else {
        CloseSelectOverlay();
    }
    updateCaretInfoToControllerMultiThread_ = true;
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldPattern::OnModifyDoneMultiThread()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto textFieldTheme = GetTheme();
    CHECK_NULL_VOID(textFieldTheme);
    directionKeysMoveFocusOut_ = textFieldTheme->GetDirectionKeysMoveFocusOut();
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    CheckIfNeedToResetKeyboard();
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto textFieldPaintProperty = host->GetPaintPropertyPtr<TextFieldPaintProperty>();
    if (textFieldPaintProperty && textFieldPaintProperty->HasBorderColorFlagByUser()) {
        textFieldPaintProperty->UpdateBorderColorFlagByUser(
            renderContext->GetBorderColorValue(BorderColorProperty {}));
    }
    isTransparent_ = renderContext->GetOpacityValue(1.0f) == 0.0f;
    ApplyNormalTheme();
    ApplyUnderlineTheme();
    ApplyInlineTheme();
    ProcessInnerPadding();
    ProcessNumberOfLines();

    InitClickEvent();
    InitLongPressEvent();
    InitFocusEvent();
    InitMouseEvent();
    InitTouchEvent();

    SetAccessibilityAction();
    FilterInitializeText();
    InitDisableColor();
    ProcessResponseArea();
    if (!shiftFlag_) {
        InitDragEvent();
    }
    Register2DragDropManager();
    ProcessUnderlineColorOnModifierDone();
    if (!clipboard_ && context) {
        clipboard_ = ClipboardProxy::GetInstance()->GetClipboard(context->GetTaskExecutor());
    }
    if (barState_.has_value() && barState_.value() != layoutProperty->GetDisplayModeValue(DisplayMode::AUTO) &&
        HasFocus() && IsNormalInlineState()) {
        lastTextRectY_ = textRect_.GetY();
    }
    OnModifyDoneMultiThreadPart();
}

void TextFieldPattern::OnModifyDoneMultiThreadPart()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (!IsDisabled() && IsShowError()) {
        SetShowError();
    } else {
        CleanErrorNode();
    }
    // The textRect position can't be changed by only redraw.
    if (!initTextRect_) {
        auto border = GetBorderWidthProperty();
        textRect_.SetLeft(GetPaddingLeft() + GetBorderLeft(border));
        textRect_.SetTop(GetPaddingTop() + GetBorderTop(border));
        AdjustTextRectByCleanNode(textRect_);
        initTextRect_ = true;
    }
    CalculateDefaultCursor();

    ProcessSelection();
    isTextChangedAtCreation_ = false;
    if (layoutProperty->GetTypeChangedValue(false)) {
        layoutProperty->ResetTypeChanged();
        operationRecords_.clear();
        redoOperationRecords_.clear();
    }
    ProcessScroll();
    ProcessCounter();
    Register2DragDropManager();
    auto autoFillContainerNode = firstAutoFillContainerNode_.Upgrade();
    if (autoFillContainerNode) {
        UpdateTextFieldInfo();
    }
    TriggerAvoidWhenCaretGoesDown();
    selectOverlay_->SetMenuTranslateIsSupport(IsShowTranslate());
    selectOverlay_->SetIsSupportMenuSearch(IsShowSearch());
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    SetIsEnableSubWindowMenu();
    isModifyDone_ = true;
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        InitCancelButtonMouseEvent();
        InitPasswordButtonMouseEvent();
    }

    // Multi Thread
    OnModifyDoneMultiThreadAddition();
}

void TextFieldPattern::OnModifyDoneMultiThreadAddition()
{
    if (setShowKeyBoardOnFocusMultiThread_) {
        setShowKeyBoardOnFocusMultiThread_ = false;
        if (setShowKeyBoardOnFocusMultiThreadValue_) {
            RequestKeyboardNotByFocusSwitch(RequestKeyboardReason::SHOW_KEYBOARD_ON_FOCUS);
        } else {
            CloseKeyboard(true, false);
        }
    }
    if (setSelectionFlagMultiThread_) {
        setSelectionFlagMultiThread_ = false;
        if (RequestKeyboardNotByFocusSwitch(RequestKeyboardReason::SET_SELECTION)) {
            NotifyOnEditChanged(true);
        }
        TriggerAvoidWhenCaretGoesDown();
    }
    if (updateCaretInfoToControllerMultiThread_) {
        updateCaretInfoToControllerMultiThread_ = false;
        UpdateCaretInfoToController();
    }
    if (startTwinklingMultiThread_) {
        startTwinklingMultiThread_ = false;
        StartTwinkling();
    }
    if (stopEditingMultiThread_) {
        stopEditingMultiThread_ = false;
        StopEditingMultiThreadAction();
    }
    if (triggerAvoidOnCaretChangeMultiThread_) {
        triggerAvoidOnCaretChangeMultiThread_ = false;
        TriggerAvoidOnCaretChange();
    }
    if (handleCountStyleMultiThread_) {
        handleCountStyleMultiThread_ = false;
        HandleCountStyle();
    }
    if (setCustomKeyboardWithNodeMultiThread_) {
        setCustomKeyboardWithNodeMultiThread_ = false;
        SetCustomKeyboardWithNodeMultiThreadAction(setCustomKeyboardWithNodeMultiThreadValue_);
        setCustomKeyboardWithNodeMultiThreadValue_.Reset();
    }
}

void TextFieldPattern::InitSurfaceChangedCallbackMultiThread()
{
    initSurfaceChangedCallbackMultiThread_ = true;
}

void TextFieldPattern::InitSurfaceChangedCallbackMultiThreadAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (!HasSurfaceChangedCallback()) {
        auto callbackId = pipeline->RegisterSurfaceChangedCallback(
            [weak = WeakClaim(this)](int32_t newWidth, int32_t newHeight, int32_t prevWidth, int32_t prevHeight,
                WindowSizeChangeReason type) {
                auto pattern = weak.Upgrade();
                if (pattern) {
                    pattern->HandleSurfaceChanged(newWidth, newHeight, prevWidth, prevHeight);
                }
            });
        UpdateSurfaceChangedCallbackId(callbackId);
    }
}

void TextFieldPattern::InitSurfacePositionChangedCallbackMultiThread()
{
    initSurfacePositionChangedCallbackMultiThread_ = true;
}

void TextFieldPattern::InitSurfacePositionChangedCallbackMultiThreadAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (!HasSurfacePositionChangedCallback()) {
        auto callbackId =
            pipeline->RegisterSurfacePositionChangedCallback([weak = WeakClaim(this)](int32_t posX, int32_t posY) {
                auto pattern = weak.Upgrade();
                if (pattern) {
                    pattern->HandleSurfacePositionChanged(posX, posY);
                }
            });
        UpdateSurfacePositionChangedCallbackId(callbackId);
    }
}

void TextFieldPattern::SetCaretPositionMultiThread(int32_t position, bool moveContent)
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "Set caret position to %{public}d", position);
    selectController_->MoveCaretToContentRect(position, TextAffinity::DOWNSTREAM, true, moveContent);
    updateCaretInfoToControllerMultiThread_ = true;
    if (HasFocus() && !magnifierController_->GetShowMagnifier()) {
        startTwinklingMultiThread_ = true;
    }
    CloseSelectOverlay();
    CancelDelayProcessOverlay();
    triggerAvoidOnCaretChangeMultiThread_ = true;
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldPattern::SetSelectionFlagMultiThread(
    int32_t selectionStart, int32_t selectionEnd, const std::optional<SelectionOptions>& options, bool isForward)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!HasFocus() || GetIsPreviewText()) {
        return;
    }
    auto length = static_cast<int32_t>(contentController_->GetTextUtf16Value().length());
    selectionStart = std::clamp(selectionStart, 0, length);
    selectionEnd = std::clamp(selectionEnd, 0, length);
    moveCaretState_.isTouchCaret = false;
    bool isShowMenu = selectOverlay_->IsCurrentMenuVisibile();
    isTouchPreviewText_ = false;
    if (selectionStart == selectionEnd) {
        selectController_->MoveCaretToContentRect(selectionEnd, TextAffinity::DOWNSTREAM);
        startTwinklingMultiThread_ = true;
    } else {
        cursorVisible_ = false;
        showSelect_ = true;
        HandleSetSelection(selectionStart, selectionEnd, false);
        if (isForward) {
            selectController_->MoveSecondHandleToContentRect(selectionEnd);
            selectController_->MoveFirstHandleToContentRect(selectionStart, false);
        } else {
            selectController_->MoveFirstHandleToContentRect(selectionStart);
            selectController_->MoveSecondHandleToContentRect(selectionEnd);
        }
    }
    
    SetIsSingleHandle(!IsSelected());
    if (!IsShowHandle()) {
        CloseSelectOverlay(true);
    } else {
        isShowMenu = IsShowMenu(options, isShowMenu);
        if (!isShowMenu && IsUsingMouse()) {
            CloseSelectOverlay();
        } else {
            ProcessOverlay({ .menuIsShow = isShowMenu, .animation = true });
        }
    }
    setSelectionFlagMultiThread_ = true;
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldPattern::StopEditingMultiThread()
{
    if (!HasFocus()) {
        return;
    }
    stopEditingMultiThread_ = true;
}

void TextFieldPattern::StopEditingMultiThreadAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    ContainerScope scope(host->GetInstanceId());
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "textfield %{public}d Stop Editing", host->GetId());
    FocusHub::LostFocusToViewRoot();
    UpdateSelection(selectController_->GetCaretIndex());
    StopTwinkling();
    CloseKeyboard(true);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldPattern::RegisterWindowSizeCallbackMultiThread()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (isOritationListenerRegisted_) {
        return;
    }
    isOritationListenerRegisted_ = true;
    registerWindowSizeCallbackMultiThread_ = true;
}

void TextFieldPattern::RegisterWindowSizeCallbackMultiThreadAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddWindowSizeChangeCallback(host->GetId());
}

void TextFieldPattern::SetPreviewTextOperationMultiThread(PreviewTextInfo info)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (!hasPreviewText_) {
        auto fullStr = GetTextUtf16Value();
        if (host->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY) && IsSelected()) {
            uint32_t startIndex = static_cast<uint32_t>(selectController_->GetStartIndex());
            uint32_t endIndex = static_cast<uint32_t>(selectController_->GetEndIndex());
            if (startIndex < fullStr.length() && endIndex <= fullStr.length()) {
                fullStr.erase(startIndex, endIndex - startIndex);
            }
        }
        bodyTextInPreivewing_ = fullStr;
    }
    auto rangeStart = info.range.start;
    auto rangeEnd = info.range.end;
    auto start = GetPreviewTextStart();
    auto end = GetPreviewTextEnd();
    if (IsSelected()) {
        start = selectController_->GetStartIndex();
        end = selectController_->GetEndIndex();
    } else {
        start = (rangeStart == PREVIEW_TEXT_RANGE_DEFAULT) ? start : rangeStart;
        end = (rangeEnd == PREVIEW_TEXT_RANGE_DEFAULT) ? end : rangeEnd;
    }

    SetPreviewTextOperationMultiThreadPart(info, start, end);

    if (HasFocus()) {
        cursorVisible_ = true;
        startTwinklingMultiThread_ = true;
    } else {
        cursorVisible_ = false;
        StopTwinkling();
    }
}

void TextFieldPattern::SetPreviewTextOperationMultiThreadPart(PreviewTextInfo info, int32_t start, int32_t end)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto oldHasPreviewText = hasPreviewText_;
    ChangeValueInfo changeValueInfo;
    changeValueInfo.oldPreviewText.offset = hasPreviewText_ ? GetPreviewTextStart() : -1;
    changeValueInfo.oldPreviewText.value = GetPreviewTextValue();
    changeValueInfo.oldContent = GetBodyTextValue();
    changeValueInfo.rangeBefore = TextRange { GetPreviewTextStart(), GetPreviewTextStart() };
    changeValueInfo.rangeAfter = TextRange { GetPreviewTextStart(), GetPreviewTextStart() };
    auto originCaretIndex =
            TextRange { changeValueInfo.oldPreviewText.offset, changeValueInfo.oldPreviewText.offset };
    auto originLength = static_cast<int32_t>(contentController_->GetTextUtf16Value().length()) - (end - start);
    contentController_->ReplaceSelectedValue(start, end, info.text);
    int32_t caretMoveLength = abs(static_cast<int32_t>(contentController_->GetTextUtf16Value().length()) -
        originLength);

    int32_t delta =
            static_cast<int32_t>(contentController_->GetTextUtf16Value().length()) - originLength - (end - start);
    int32_t newCaretPosition = std::max(end, GetPreviewTextEnd()) + delta;
    newCaretPosition = std::clamp(newCaretPosition, 0,
        static_cast<int32_t>(contentController_->GetTextUtf16Value().length()));
    selectController_->UpdateCaretIndex(start + caretMoveLength);

    UpdatePreviewIndex(start, newCaretPosition);
    hasPreviewText_ = true;
    changeValueInfo.value = GetBodyTextValue();
    changeValueInfo.previewText.offset = hasPreviewText_ ? GetPreviewTextStart() : -1;
    changeValueInfo.previewText.value = GetPreviewTextValue();
    bool isWillChange = FireOnWillChange(changeValueInfo);
    if (!isWillChange && !info.isIme) {
        RecoverTextValueAndCaret(changeValueInfo.oldContent, originCaretIndex);
        hasPreviewText_ = oldHasPreviewText;
        return;
    }
}

void TextFieldPattern::FinishTextPreviewOperationMultiThread(bool triggerOnWillChange)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!hasPreviewText_) {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "input state now is not at previewing text");
        return;
    }
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    if (layoutProperty->HasMaxLength()) {
        int32_t len = static_cast<int32_t>(contentController_->GetTextUtf16Value().length());
        showCountBorderStyle_ = len >
            static_cast<int32_t>(layoutProperty->GetMaxLengthValue(Infinity<uint32_t>()));
        handleCountStyleMultiThread_ = true;
    }

    FinishTextPreviewOperationMultiThreadPart(triggerOnWillChange);

    if (HasFocus()) {
        cursorVisible_ = true;
        StartTwinkling();
    } else {
        cursorVisible_ = false;
        StopTwinkling();
    }

    bodyTextInPreivewing_ = u"";
    previewTextStart_ = PREVIEW_TEXT_RANGE_DEFAULT;
    previewTextEnd_ = PREVIEW_TEXT_RANGE_DEFAULT;

    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void TextFieldPattern::FinishTextPreviewOperationMultiThreadPart(bool triggerOnWillChange)
{
    auto oldValue = contentController_->GetTextUtf16Value();
    auto originCaretIndex =
            TextRange { selectController_->GetFirstHandleIndex(), selectController_->GetSecondHandleIndex() };
    ChangeValueInfo changeValueInfo;
    changeValueInfo.oldPreviewText.offset = hasPreviewText_ ? GetPreviewTextStart() : -1;
    changeValueInfo.oldPreviewText.value = GetPreviewTextValue();
    changeValueInfo.oldContent = GetBodyTextValue();
    changeValueInfo.rangeBefore = TextRange { GetPreviewTextStart(), GetPreviewTextStart() };
    auto start = GetPreviewTextStart();
    auto end = GetPreviewTextEnd();
    auto previewValue = GetPreviewTextValue();
    hasPreviewText_ = false;

    auto originLength = static_cast<int32_t>(contentController_->GetTextUtf16Value().length()) - (end - start);
    contentController_->ReplaceSelectedValue(start, end, previewValue);
    int32_t caretMoveLength = abs(static_cast<int32_t>(contentController_->GetTextUtf16Value().length()) -
        originLength);
    selectController_->UpdateCaretIndex(start + caretMoveLength);
    UpdateEditingValueToRecord();
    changeValueInfo.rangeAfter =
        TextRange { changeValueInfo.oldPreviewText.offset, start + caretMoveLength };
    changeValueInfo.value = GetBodyTextValue();
    changeValueInfo.previewText.offset = hasPreviewText_ ? GetPreviewTextStart() : -1;
    changeValueInfo.previewText.value = GetPreviewTextValue();
    bool isWillChange = true;
    if (triggerOnWillChange) {
        isWillChange = FireOnWillChange(changeValueInfo);
    }
    if (!isWillChange) {
        RecoverTextValueAndCaret(oldValue, originCaretIndex);
        return;
    }
}

void TextFieldPattern::SetShowKeyBoardOnFocusMultiThread(bool value)
{
    if (showKeyBoardOnFocus_ == value) {
        return;
    }
    showKeyBoardOnFocus_ = value;

    if (!HasFocus()) {
        return;
    }

    setShowKeyBoardOnFocusMultiThread_ = true;
    setShowKeyBoardOnFocusMultiThreadValue_ = value;
}

void TextFieldPattern::SetCustomKeyboardWithNodeMultiThread(const RefPtr<UINode>& keyboardBuilder)
{
    setCustomKeyboardWithNodeMultiThread_ = true;
    setCustomKeyboardWithNodeMultiThreadValue_ = keyboardBuilder;
}

void TextFieldPattern::SetCustomKeyboardWithNodeMultiThreadAction(const RefPtr<UINode>& keyboardBuilder)
{
    if (customKeyboard_ && isCustomKeyboardAttached_ && !keyboardBuilder) {
        // close customKeyboard and request system keyboard
        CloseCustomKeyboard();
        customKeyboard_ = keyboardBuilder; // refresh current keyboard
        RequestKeyboardNotByFocusSwitch(RequestKeyboardReason::CUSTOM_KEYBOARD);
        StartTwinkling();
        return;
    }
    if (!customKeyboard_ && keyboardBuilder) {
        // close system keyboard and request custom keyboard
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
        if (imeShown_) {
            CloseKeyboard(true);
            customKeyboard_ = keyboardBuilder; // refresh current keyboard
            RequestKeyboardNotByFocusSwitch(RequestKeyboardReason::CUSTOM_KEYBOARD);
            StartTwinkling();
            return;
        }
#endif
    }
    customKeyboard_ = keyboardBuilder;
}

void TextFieldPattern::ProcessDefaultStyleAndBehaviors()
{
    processDefaultStyleAndBehaviorsMultiThread_ = true;
}

void TextFieldPattern::ProcessDefaultStyleAndBehaviorsMultiThread()
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(textFieldTheme);
    auto textfieldPaintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(textfieldPaintProperty);
    std::set<std::string> allowDropSet({ DROP_TYPE_PLAIN_TEXT, DROP_TYPE_HYPERLINK, DROP_TYPE_STYLED_STRING });
    frameNode->SetAllowDrop(allowDropSet);
    textfieldPaintProperty->UpdatePressBgColor(textFieldTheme->GetPressColor());
    textfieldPaintProperty->UpdateHoverBgColor(textFieldTheme->GetHoverColor());
    auto renderContext = frameNode->GetRenderContext();
    renderContext->UpdateBackgroundColor(textFieldTheme->GetBgColor());
    auto radius = textFieldTheme->GetBorderRadius();
    textfieldPaintProperty->UpdateCursorColor(textFieldTheme->GetCursorColor());
    BorderRadiusProperty borderRadius { radius.GetX(), radius.GetY(), radius.GetY(), radius.GetX() };
    renderContext->UpdateBorderRadius(borderRadius);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->AddTextFieldDragFrameNode(frameNode->GetId(), AceType::WeakClaim(AceType::RawPtr(frameNode)));
    PaddingProperty paddings;
    auto themePadding = textFieldTheme->GetPadding();
    paddings.top = NG::CalcLength(themePadding.Top().ConvertToPx());
    paddings.bottom = NG::CalcLength(themePadding.Bottom().ConvertToPx());
    paddings.left = NG::CalcLength(themePadding.Left().ConvertToPx());
    paddings.right = NG::CalcLength(themePadding.Right().ConvertToPx());
    auto layoutProperty = frameNode->GetLayoutProperty<LayoutProperty>();
    layoutProperty->UpdatePadding(paddings);
    if (frameNode->IsFirstBuilding()) {
        auto draggable = pipeline->GetDraggable<TextFieldTheme>();
        frameNode->SetDraggable(draggable);
        auto gestureHub = frameNode->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        gestureHub->SetTextDraggable(true);
    }
}
} // namespace OHOS::Ace::NG
