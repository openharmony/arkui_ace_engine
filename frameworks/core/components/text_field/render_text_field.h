/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_FIELD_RENDER_TEXT_FIELD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_FIELD_RENDER_TEXT_FIELD_H

#include <functional>

#include "base/geometry/dimension.h"
#include "base/geometry/offset.h"
#include "base/geometry/rect.h"
#include "base/geometry/size.h"
#include "base/utils/system_properties.h"
#include "core/common/clipboard/clipboard.h"
#include "core/common/ime/text_edit_controller.h"
#include "core/common/ime/text_input_client.h"
#include "core/common/ime/text_input_connection.h"
#include "core/common/ime/text_input_formatter.h"
#include "core/common/ime/text_input_type.h"
#include "core/common/ime/text_selection.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/decoration.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/image/render_image.h"
#include "core/components/text_field/text_field_component.h"
#include "core/gestures/click_recognizer.h"
#include "core/gestures/long_press_recognizer.h"
#include "core/gestures/raw_recognizer.h"
#include "core/pipeline/base/overlay_show_option.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace {

class ClickRecognizer;
class ClickInfo;
class TextOverlayComponent;
struct TextEditingValue;

enum class DirectionStatus : uint8_t {
    LEFT_LEFT = 0, // System direction is LTR, text direction is LTR.
    LEFT_RIGHT,
    RIGHT_LEFT,
    RIGHT_RIGHT,
};

enum class CursorPositionType {
    NONE = 0,
    END,      // end of paragraph
    BOUNDARY, // boundary of LTR and RTL
    NORMAL,
};

class RenderTextField : public RenderNode, public TextInputClient, public ValueChangeObserver {
    DECLARE_ACE_TYPE(RenderTextField, RenderNode, TextInputClient, ValueChangeObserver);

public:
    ~RenderTextField() override;

    static RefPtr<RenderNode> Create();

    using TapCallback = std::function<bool()>;

    void Update(const RefPtr<Component>& component) override;
    void PerformLayout() override;
    // Override TextInputClient
    void UpdateEditingValue(const std::shared_ptr<TextEditingValue>& value, bool needFireChangeEvent = true) override;
    void PerformAction(TextInputAction action, bool forceCloseKeyboard = false) override;
    void OnStatusChanged(RenderStatus renderStatus) override;
    void OnValueChanged(bool needFireChangeEvent = true) override;
    void OnPaintFinish() override;

    bool OnKeyEvent(const KeyEvent& event);
    bool RequestKeyboard(bool isFocusViewChanged, bool needStartTwinkling = false);
    bool CloseKeyboard(bool forceClose = false);
    void ShowError(const std::string& errorText, bool resetToStart = true);
    void ShowTextOverlay(const Offset& showOffset, bool isSingleHandle);
    void SetOnValueChange(const std::function<void()>& onValueChange);
    const std::function<void()>& GetOnValueChange() const;
    void SetOnKeyboardClose(const std::function<void(bool)>& onKeyboardClose);
    void SetOnClipRectChanged(const std::function<void(const Rect&)>& onClipRectChanged);
    void SetUpdateHandlePosition(const std::function<void(const OverlayShowOption&)>& updateHandlePosition);
    void SetUpdateHandleDiameter(const std::function<void(const double&)>& updateHandleDiameter);
    void SetUpdateHandleDiameterInner(const std::function<void(const double&)>& updateHandleDiameterInner);
    void SetIsOverlayShowed(bool isOverlayShowed, bool needStartTwinkling = true);
    void UpdateFocusAnimation();
    const TextEditingValue& GetEditingValue() const;
    void Delete(int32_t start, int32_t end);
    void SetOnOverlayFocusChange(const std::function<void(bool)>& onOverlayFocusChange)
    {
        onOverlayFocusChange_ = onOverlayFocusChange;
    }

    // Whether textOverlay is showed.
    bool IsOverlayShowed() const
    {
        return isOverlayShowed_;
    }

    void SetOverlayColor(const Color& overlayColor)
    {
        overlayColor_ = overlayColor;
    }

    void RegisterTapCallback(const TapCallback& callback)
    {
        tapCallback_ = callback;
    }

    void SetNextFocusEvent(const std::function<void()>& event)
    {
        moveNextFocusEvent_ = event;
    }

    void SetSubmitEvent(std::function<void(const std::string&)>&& event)
    {
        onSubmitEvent_ = event;
    }

    const Color& GetColor() const
    {
        if (decoration_) {
            return decoration_->GetBackgroundColor();
        }
        return Color::TRANSPARENT;
    }

    void SetColor(const Color& color)
    {
        if (decoration_) {
            decoration_->SetBackgroundColor(color);
            MarkNeedRender();
        }
    }

    double GetHeight() const
    {
        return height_.Value();
    }

    void SetHeight(double height)
    {
        if (GreatOrEqual(height, 0.0) && !NearEqual(height_.Value(), height)) {
            height_.SetValue(height);
            MarkNeedLayout();
        }
    }

    const WeakPtr<StackElement> GetStackElement() const
    {
        return stackElement_;
    }

    void SetWidthReservedForSearch(double widthReservedForSearch)
    {
        widthReservedForSearch_ = widthReservedForSearch;
    }

    void SetPaddingHorizonForSearch(double paddingHorizon)
    {
        paddingHorizonForSearch_ = paddingHorizon;
    }

    bool HasTextOverlayPushed() const
    {
        return hasTextOverlayPushed_;
    }

    void SetTextOverlayPushed(bool hasTextOverlayPushed)
    {
        hasTextOverlayPushed_ = hasTextOverlayPushed;
    }

    bool IsSingleHandle() const
    {
        return isSingleHandle_;
    }

    int32_t GetInitIndex() const
    {
        return initIndex_;
    }

    void SetInitIndex(int32_t initIndex)
    {
        initIndex_ = initIndex;
    }

    void SetOnTextChangeEvent(const std::function<void(const std::string&)>& onTextChangeEvent)
    {
        onTextChangeEvent_ = onTextChangeEvent;
    }

    void SetNeedNotifyChangeEvent(bool needNotifyChangeEvent)
    {
        needNotifyChangeEvent_ = needNotifyChangeEvent;
    }

protected:
    // Describe where caret is and how tall visually.
    struct CaretMetrics {
        void Reset()
        {
            offset.Reset();
            height = 0.0;
        }

        Offset offset;
        // When caret is close to different glyphs, the height will be different.
        double height = 0.0;
    };

    RenderTextField();
    virtual Size Measure();
    virtual int32_t GetCursorPositionForMoveUp() = 0;
    virtual int32_t GetCursorPositionForMoveDown() = 0;
    virtual int32_t GetCursorPositionForClick(const Offset& offset) = 0;
    virtual Offset GetHandleOffset(int32_t extend) = 0;
    virtual double PreferredLineHeight() = 0;
    virtual int32_t AdjustCursorAndSelection(int32_t currentCursorPosition) = 0;
    virtual DirectionStatus GetDirectionStatusOfPosition(int32_t position) const = 0;
    virtual Size ComputeDeflateSizeOfErrorAndCountText() const = 0;

    void OnTouchTestHit(
        const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result) override;
    void OnHiddenChanged(bool hidden) override;
    void OnClick(const ClickInfo& clickInfo);
    void OnLongPress(const LongPressInfo& longPressInfo);

    void StartTwinkling();
    void StopTwinkling();

    void SetEditingValue(TextEditingValue&& newValue, bool needFireChangeEvent = true);
    std::u16string GetTextForDisplay(const std::string& text) const;

    void UpdateStartSelection(int32_t end, const Offset& pos, bool isSingleHandle, bool isLongPress);
    void UpdateEndSelection(int32_t start, const Offset& pos);
    void UpdateSelection(int32_t both);
    void UpdateSelection(int32_t start, int32_t end);
    void UpdateDirectionStatus();
    Offset GetPositionForExtend(int32_t extend, bool isSingleHandle);
    /**
     * Get grapheme cluster length before or after extend.
     * For example, here is a sentence: 123🎉👍
     * The emoji character contains 2 code unit. Assumpt that the cursor is at the end (that will be 3+2+2 = 7).
     * When calling GetGraphemeClusterLength(3, false), '🎉' is not in Utf16Bmp, so result is 2.
     * When calling GetGraphemeClusterLength(3, true), '3' is in Utf16Bmp, so result is 1.
     */
    int32_t GetGraphemeClusterLength(int32_t extend, bool isPrefix) const;

    bool HasConnection() const
    {
        return connection_;
    }

    bool ShowCounter() const;

    // Used for compare to the current value and decide whether to UpdateRemoteEditing().
    std::shared_ptr<TextEditingValue> lastKnownRemoteEditingValue_;

    // An outline for caret. It is used by default when the actual size cannot be retrieved.
    Rect caretProto_;
    Rect innerRect_;
    // Click region of password icon.
    Rect passwordIconRect_;

    std::string placeholder_;
    Color placeholderColor_;
    // Colors when not focused.
    Color inactivePlaceholderColor_;
    Color inactiveBgColor_;
    Color inactiveTextColor_;
    // Colors when focused.
    Color focusPlaceholderColor_;
    Color focusBgColor_;
    Color focusTextColor_;
    // Color when selected.
    Color selectedColor_;
    Color cursorColor_;
    // Overlay color for hover and press.
    Color overlayColor_ = Color::TRANSPARENT;
    // The interval for caret twinkling, in ms.
    uint32_t twinklingInterval = 0;
    bool showPlaceholder_ = false;
    bool cursorVisibility_ = false;
    bool showCursor_ = true;
    bool cursorColorIsSet_ = false;
    Dimension cursorRadius_;
    Dimension fontSize_;
    // Used under case of [obscure_ == true].
    // When a character input, it will be displayed naked for a while.
    // The remaining time to naked display the recent character is indicated by [obscureTickPendings_],
    // multiply by [twinklingInterval]. For example, 3 * 500ms = 1500ms.
    int32_t obscureTickPendings_ = 0;
    // What the keyboard should appears.
    TextInputType keyboard_ = TextInputType::TEXT;
    // Action when "enter" pressed.
    TextInputAction action_ = TextInputAction::UNSPECIFIED;
    std::string actionLabel_;
    uint32_t maxLength_ = std::numeric_limits<uint32_t>::max();
    // Default to the start of text (according to RTL/LTR).
    TextAlign textAlign_ = TextAlign::START;
    // RTL/LTR is inherit from parent.
    TextDirection textDirection_ = TextDirection::INHERIT;
    TextDirection realTextDirection_ = TextDirection::INHERIT;
    TextAffinity textAffinity_ = TextAffinity::DOWNSTREAM;

    TextStyle countTextStyle_;
    TextStyle overCountStyle_;
    TextStyle countTextStyleOuter_;
    TextStyle overCountStyleOuter_;
    TextStyle style_;
    std::string errorText_;
    TextStyle errorTextStyle_;
    double errorSpacing_ = 0.0;
    Dimension errorSpacingInDimension_;
    // Place error text in or under input. In input when device is TV, under input when device is phone.
    bool errorIsInner_ = false;
    Dimension errorBorderWidth_;
    Color errorBorderColor_;

    RefPtr<Decoration> decoration_;
    Border originBorder_;

    // One line TextField is more common in usual cases.
    uint32_t maxLines_ = 1;
    size_t textLines_ = 0;
    int32_t cursorPositionForShow_ = 0;
    CursorPositionType cursorPositionType_ = CursorPositionType::NORMAL;
    DirectionStatus directionStatus_ = DirectionStatus::LEFT_LEFT;

    bool showCounter_ = false; // Whether show counter, 10/100 means maxlength is 100 and 10 has inputed.
    bool overCount_ = false;   // Whether count of text is over limit.
    bool obscure_ = false;     // Obscure the text, for example, password.
    bool enabled_ = true;      // Whether input is disable of enable.
    bool needFade_ = false;    // Fade in/out text when overflow.
    bool blockRightShade_ = false;
    bool isValueFromRemote_ = false;          // Remote value coming form typing, other is from clopboard.
    bool existStrongDirectionLetter_ = false; // Whether exist strong direction letter in text.
    bool isVisible_ = true;
    bool needNotifyChangeEvent_ = true;
    bool resetToStart_ = true;      // When finish inputting text, whether show header of text.
    bool showEllipsis_ = false;     // When text is overflow, whether show ellipsis.
    bool extend_ = false;           // Whether input support extend, this attribute is worked in textarea.
    bool isCallbackCalled_ = false; // Whether custom font is loaded.
    bool isOverlayShowed_ = false;  // Whether overlay has showed.
    double textHeight_ = 0.0;       // Height of text.
    double iconSize_ = 0.0;
    double iconHotZoneSize_ = 0.0;
    double extendHeight_ = 0.0;
    double widthReservedForSearch_ = 0.0;  // Width reserved for delete icon of search.
    double paddingHorizonForSearch_ = 0.0; // Width reserved for search button of search.
    double selectHeight_ = 0.0;
    Dimension height_;
    Dimension iconSizeInDimension_;
    Dimension iconHotZoneSizeInDimension_;
    Dimension widthReserved_;
    std::string iconSrc_;
    std::string showIconSrc_;
    std::string hideIconSrc_;
    RefPtr<RenderImage> iconImage_;
    RefPtr<RenderImage> renderShowIcon_;
    RefPtr<RenderImage> renderHideIcon_;

    Offset clickOffset_;
    // For ensuring caret is visible on screen, we take a strategy that move the whole text painting area.
    // It maybe seems rough, and doesn't support scrolling smoothly.
    Offset textOffsetForShowCaret_;

private:
    // Currently only CHARACTER.
    enum class CursorMoveSkip {
        CHARACTER, // Smallest code unit.
        WORDS,
        SIBLING_SPACE,
        PARAGRAPH,
    };

    void StartPressAnimation(bool isPressDown);
    void ScheduleCursorTwinkling();
    void OnCursorTwinkling();
    void CursorMoveLeft(CursorMoveSkip skip = CursorMoveSkip::CHARACTER);
    void CursorMoveRight(CursorMoveSkip skip = CursorMoveSkip::CHARACTER);
    void CursorMoveUp();
    void CursorMoveDown();
    void CursorMoveOnClick(const Offset& offset);
    void UpdateRemoteEditing(bool needFireChangeEvent = true);
    void UpdateFormatters();
    void UpdateFocusStyles();
    void UpdateIcon(const RefPtr<TextFieldComponent>& textField);
    void UpdatePasswordIcon(const RefPtr<TextFieldComponent>& textField);
    void UpdateOverlay();
    void RegisterFontCallbacks();
    void HandleOnCut();
    void HandleOnCopy();
    void HandleOnPaste();
    void HandleOnCopyAll(const std::function<void(const Offset&, const Offset&)>& callback);
    void HandleOnStartHandleMove(int32_t end, const Offset& startHandleOffset,
        const std::function<void(const Offset&)>& startCallback, bool isSingleHandle = false);
    void HandleOnEndHandleMove(
        int32_t start, const Offset& endHandleOffset, const std::function<void(const Offset&)>& endCallback);
    RefPtr<StackElement> GetLastStack() const;
    void InitAnimation();
    void RegisterCallbacksToOverlay();
    void PushTextOverlayToStack();
    void UpdateAccessibilityAttr();
    void InitAccessibilityEventListener();
    bool HandleKeyEvent(const KeyEvent& event);
    void ClearEditingValue();
    virtual bool GetCaretRect(int32_t extent, Rect& caretRect, double caretHeightOffset = 0.0) const = 0;
    bool SearchAction(const Offset& globalPosition, const Offset& globalOffset);
    void ChangeCounterStyle(const TextEditingValue& value);
    void ChangeBorderToErrorStyle();
    void HandleDeviceOrientationChange();
    void OnOverlayFocusChange(bool isFocus, bool needCloseKeyboard);
    int32_t GetInstanceId() const;

    /**
     * @brief Update remote editing value only if text or selection is changed.
     */
    void UpdateRemoteEditingIfNeeded(bool needFireChangeEvent = true);

    void AttachIme();

    int32_t initIndex_ = 0;
    bool isOverlayFocus_ = false;
    bool isShiftDown_ = false;
    bool hasFocus_ = false;
    double fontScale_ = 1.0;
    bool isSingleHandle_ = false;
    bool hasTextOverlayPushed_ = false;
    Color pressColor_;
    DeviceOrientation deviceOrientation_ = DeviceOrientation::PORTRAIT;
    std::function<void()> onValueChange_;
    std::function<void(bool)> onKeyboardClose_;
    std::function<void(const Rect&)> onClipRectChanged_;
    std::function<void(const OverlayShowOption&)> updateHandlePosition_;
    std::function<void(const double&)> updateHandleDiameter_;
    std::function<void(const double&)> updateHandleDiameterInner_;
    std::function<void(const std::string&)> onTextChangeEvent_;
    std::function<void(const std::string&)> onFinishInputEvent_;
    std::function<void(const std::string&)> onSubmitEvent_;
    std::function<void()> onTapEvent_;
    std::function<void()> onLongPressEvent_;
    std::function<void()> moveNextFocusEvent_;
    std::function<void(bool)> onOverlayFocusChange_;
    EventMarker onOptionsClick_;
    EventMarker onTranslate_;
    EventMarker onShare_;
    EventMarker onSearch_;

    TapCallback tapCallback_;
    CancelableCallback<void()> cursorTwinklingTask_;

    std::vector<Framework::InputOption> inputOptions_;
    std::list<std::unique_ptr<TextInputFormatter>> textInputFormatters_;
    RefPtr<TextEditController> controller_;
    RefPtr<TextInputConnection> connection_;
    RefPtr<Clipboard> clipboard_;
    RefPtr<TextOverlayComponent> textOverlay_;
    WeakPtr<StackElement> stackElement_;
    RefPtr<ClickRecognizer> clickRecognizer_;
    RefPtr<LongPressRecognizer> longPressRecognizer_;
    RefPtr<RawRecognizer> rawRecognizer_;
    RefPtr<Animator> pressController_;
    RefPtr<Animator> animator_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_FIELD_RENDER_TEXT_FIELD_H
