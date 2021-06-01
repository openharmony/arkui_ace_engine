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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_FIELD_TEXT_FIELD_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_FIELD_TEXT_FIELD_COMPONENT_H

#include "base/memory/referenced.h"
#include "base/utils/label_target.h"
#include "core/common/ime/text_edit_controller.h"
#include "core/common/ime/text_input_action.h"
#include "core/common/ime/text_input_proxy.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/decoration.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/image/image_component.h"
#include "core/components/text_field/text_field_controller.h"
#include "core/event/ace_event_handler.h"
#include "core/pipeline/base/render_component.h"
#include "frameworks/bridge/common/dom/dom_input.h"

namespace OHOS::Ace {

class RenderNode;
class Element;

class TextFieldComponent : public RenderComponent, public LabelTarget {
    DECLARE_ACE_TYPE(TextFieldComponent, RenderComponent, LabelTarget);

public:
    TextFieldComponent() = default;
    ~TextFieldComponent() override = default;

    RefPtr<RenderNode> CreateRenderNode() override;
    RefPtr<Element> CreateElement() override;

    const std::string& GetValue() const;
    void SetValue(const std::string& value);

    const std::string& GetPlaceholder() const;
    void SetPlaceholder(const std::string& placeholder);

    const Color& GetPlaceholderColor() const;
    void SetPlaceholderColor(const Color& placeholderColor);

    void SetTextMaxLines(uint32_t textMaxLines);
    TextAlign GetTextAlign() const;

    void SetTextAlign(TextAlign textAlign);
    uint32_t GetTextMaxLines() const;

    const TextStyle& GetTextStyle() const;
    void SetTextStyle(const TextStyle& textStyle);

    const TextStyle& GetErrorTextStyle() const;
    void SetErrorTextStyle(const TextStyle& errorTextStyle);

    const Dimension& GetErrorSpacing() const;
    void SetErrorSpacing(const Dimension& errorSpacing);

    bool GetErrorIsInner() const;
    void SetErrorIsInner(bool errorIsInner);

    const Dimension& GetErrorBorderWidth() const;
    void SetErrorBorderWidth(const Dimension& errorBorderWidth);

    const Color& GetErrorBorderColor() const;
    void SetErrorBorderColor(const Color& errorBorderColor);

    bool NeedFade() const;
    void SetNeedFade(bool needFade);

    RefPtr<Decoration> GetDecoration() const;
    void SetDecoration(const RefPtr<Decoration>& decoration);

    void SetOriginBorder(const Border& originBorder);
    const Border& GetOriginBorder() const;

    bool ShowCursor() const;
    void SetShowCursor(bool show);

    bool NeedObscure() const;
    void SetObscure(bool obscure);

    bool IsEnabled() const;
    void SetEnabled(bool enable);

    TextInputType GetTextInputType() const;
    void SetTextInputType(TextInputType type);

    TextInputAction GetAction() const;
    void SetAction(TextInputAction action);

    void SetCursorColor(const Color& color);
    const Color& GetCursorColor();

    void SetCursorRadius(const Dimension& radius);
    const Dimension& GetCursorRadius() const;

    bool IsCursorColorSet() const;

    const std::string& GetActionLabel() const;
    void SetActionLabel(const std::string& actionLabel);

    uint32_t GetMaxLength() const;
    void SetMaxLength(uint32_t maxLength);

    bool IsTextLengthLimited() const;

    const Dimension& GetHeight() const;
    void SetHeight(const Dimension& height);

    bool GetAutoFocus() const;
    void SetAutoFocus(bool autoFocus);

    bool IsExtend() const;
    void SetExtend(bool extend);

    bool ShowEllipsis() const;
    void SetShowEllipsis(bool showEllipsis);

    const std::string& GetIconImage() const;
    void SetIconImage(const std::string& iconImage);

    const std::string& GetShowIconImage() const;
    void SetShowIconImage(const std::string& showImage);

    const std::string& GetHideIconImage() const;
    void SetHideIconImage(const std::string& hideImage);

    const Dimension& GetIconSize() const;
    void SetIconSize(const Dimension& iconSize);

    const Dimension& GetIconHotZoneSize() const;
    void SetIconHotZoneSize(const Dimension& iconHotZoneSize);

    const EventMarker& GetOnTextChange() const;
    void SetOnTextChange(const EventMarker& onTextChange);

    const EventMarker& GetOnFinishInput() const;
    void SetOnFinishInput(const EventMarker& onFinishInput);

    const EventMarker& GetOnTap() const;
    void SetOnTap(const EventMarker& onTap);

    const EventMarker& GetOnLongPress() const;
    void SetOnLongPress(const EventMarker& onLongPress);

    const RefPtr<TextEditController>& GetTextEditController() const;
    void SetTextEditController(const RefPtr<TextEditController>& controller);

    const RefPtr<TextFieldController>& GetTextFieldController() const;
    void SetTextFieldController(const RefPtr<TextFieldController>& controller);

    void SetFocusBgColor(const Color& focusBgColor);
    const Color& GetFocusBgColor();

    void SetFocusPlaceholderColor(const Color& focusPlaceholderColor);
    const Color& GetFocusPlaceholderColor();

    void SetFocusTextColor(const Color& focusTextColor);
    const Color& GetFocusTextColor();

    void SetBgColor(const Color& bgColor);
    const Color& GetBgColor();

    void SetTextColor(const Color& textColor);
    const Color& GetTextColor();

    void SetWidthReserved(const Dimension& widthReserved);
    const Dimension& GetWidthReserved() const;

    const Color& GetSelectedColor() const;
    void SetSelectedColor(const Color& selectedColor);

    const Color& GetHoverColor() const;
    void SetHoverColor(const Color& hoverColor);

    const Color& GetPressColor() const;
    void SetPressColor(const Color& pressColor);

    void SetBlockRightShade(bool blockRightShade);
    bool GetBlockRightShade() const;

    void SetIsVisible(bool isVisible);
    bool IsVisible() const;

    void SetResetToStart(bool resetToStart);
    bool GetResetToStart() const;

    void SetShowCounter(bool showCounter);
    bool ShowCounter() const;

    void SetCountTextStyle(const TextStyle& countTextStyle);
    const TextStyle& GetCountTextStyle() const;

    void SetOverCountStyle(const TextStyle& overCountStyle);
    const TextStyle& GetOverCountStyle() const;

    void SetCountTextStyleOuter(const TextStyle& countTextStyleOuter);
    const TextStyle& GetCountTextStyleOuter() const;

    void SetOverCountStyleOuter(const TextStyle& overCountStyleOuter);
    const TextStyle& GetOverCountStyleOuter() const;

    void SetInputOptions(const std::vector<Framework::InputOption>& inputOptions);
    const std::vector<Framework::InputOption>& GetInputOptions() const;

    const EventMarker& GetOnOptionsClick() const;
    void SetOnOptionsClick(const EventMarker& onOptionsClick);

    const EventMarker& GetOnTranslate() const;
    void SetOnTranslate(const EventMarker& onTranslate);

    const EventMarker& GetOnShare() const;
    void SetOnShare(const EventMarker& onShare);

    const EventMarker& GetOnSearch() const;
    void SetOnSearch(const EventMarker& onSearch);

    bool IsValueUpdated() const;

private:
    std::string value_;
    std::string placeholder_;
    Color placeholderColor_;
    Color cursorColor_;
    Dimension cursorRadius_;
    Dimension widthReserved_;
    bool cursorColorIsSet_ = false;
    bool showCursor_ = true;
    // Obscure the text, for example, password.
    bool obscure_ = false;
    bool enabled_ = true;
    TextInputType keyboard_ = TextInputType::TEXT;
    // Action when "enter" pressed.
    TextInputAction action_ = TextInputAction::UNSPECIFIED;
    std::string actionLabel_;
    bool lengthLimited_ = false;
    uint32_t maxLength_ = std::numeric_limits<uint32_t>::max();
    bool autoFocus_ = false;
    // Whether height of textfield can auto-extend.
    bool extend_ = false;
    bool showEllipsis_ = false;
    bool blockRightShade_ = false;
    bool isVisible_ = true;
    bool resetToStart_ = true;
    bool isValueUpdated_ = false;

    // Herder-icon of textField.
    std::string iconImage_;
    Dimension iconSize_;
    Dimension iconHotZoneSize_;
    // Icon to control password show or hide.
    std::string showImage_;
    std::string hideImage_;

    TextAlign textAlign_ = TextAlign::START;
    uint32_t textMaxLines_ = 1;
    Dimension height_;
    TextStyle textStyle_;
    TextStyle errorTextStyle_;
    // Spacing between error text and input text.
    Dimension errorSpacing_;
    // Whether error text show inner or under.
    bool errorIsInner_ = false;
    Dimension errorBorderWidth_;
    Color errorBorderColor_;
    bool needFade_ = false;
    RefPtr<Decoration> decoration_;
    Border originBorder_;

    // theme setting
    Color focusBgColor_;
    Color focusPlaceholderColor_;
    Color focusTextColor_;
    Color bgColor_;
    Color textColor_;
    Color selectedColor_;
    Color hoverColor_;
    Color pressColor_;

    // Callback id for when text is changed.
    EventMarker onTextChange_;
    // Callback id for when user press "enter"
    EventMarker onFinishInput_;
    EventMarker onTap_;
    EventMarker onLongPress_;
    EventMarker onOptionsClick_;
    // Callback id for text overlay.
    EventMarker onTranslate_;
    EventMarker onShare_;
    EventMarker onSearch_;

    RefPtr<TextEditController> controller_;
    RefPtr<TextFieldController> textFieldController_;

    // Whether show counter, should work together with maxLength_.
    bool showCounter_ = false;
    TextStyle countTextStyle_;
    TextStyle overCountStyle_;
    TextStyle countTextStyleOuter_;
    TextStyle overCountStyleOuter_;

    std::vector<Framework::InputOption> inputOptions_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_FIELD_TEXT_FIELD_COMPONENT_H
