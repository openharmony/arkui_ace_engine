/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SEARCH_SEARCH_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SEARCH_SEARCH_PATTERN_H

#include "base/memory/referenced.h"
#include "base/mousestyle/mouse_style.h"
#include "core/components/text_field/text_field_controller.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/search/search_event_hub.h"
#include "core/components_ng/pattern/search/search_layout_algorithm.h"
#include "core/components_ng/pattern/search/search_layout_property.h"
#include "core/components_ng/pattern/search/search_paint_method.h"
#include "core/components_ng/pattern/text_field/text_field_controller.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"

namespace OHOS::Ace::NG {

class SearchPattern : public Pattern {
    DECLARE_ACE_TYPE(SearchPattern, Pattern);

public:
    SearchPattern() = default;
    ~SearchPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<SearchLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<SearchLayoutAlgorithm>();
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        auto paintMethod = MakeRefPtr<SearchPaintMethod>(buttonSize_, searchButton_, isSearchButtonEnabled_);
        return paintMethod;
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<SearchEventHub>();
    }

    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& /*config*/) override;

    const RefPtr<TextFieldController>& GetSearchController()
    {
        return searchController_;
    }

    void SetSearchController(const RefPtr<TextFieldController>& searchController)
    {
        searchController_ = searchController;
    }

    FocusPattern GetFocusPattern() const override;

    bool HandleInputChildOnFocus() const;

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override;

    static std::string ConvertCopyOptionsToString(CopyOptions copyOptions)
    {
        std::string result;
        switch (copyOptions) {
            case CopyOptions::None:
                result = "CopyOptions.None";
                break;
            case CopyOptions::InApp:
                result = "CopyOptions.InApp";
                break;
            case CopyOptions::Local:
                result = "CopyOptions.Local";
                break;
            case CopyOptions::Distributed:
                result = "CopyOptions.Distributed";
                break;
            default:
                LOGD("The input does not match any CopyOptions");
        }
        return result;
    }

    enum class FocusChoice { SEARCH = 0, CANCEL_BUTTON, SEARCH_BUTTON };

    void UpdateChangeEvent(const std::string& value);

private:
    void OnModifyDone() override;
    void InitButtonAndImageClickEvent();
    void InitCancelButtonClickEvent();
    void InitSearchController();
    void OnClickButtonAndImage();
    void OnClickCancelButton();
    void HandleCaretPosition(int32_t caretPosition);
    void StopEditing();
    // Init key event
    void InitOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    bool OnKeyEvent(const KeyEvent& event);
    void PaintFocusState();
    void GetInnerFocusPaintRect(RoundRect& paintRect);
    void RequestKeyboard();
    // Init touch and hover event
    void InitTouchEvent();
    void InitMouseEvent();
    void InitTextFieldMouseEvent();
    void InitButtonTouchEvent(RefPtr<TouchEventImpl>& touchEvent, int32_t childId);
    void InitButtonMouseEvent(RefPtr<InputEvent>& inputEvent, int32_t childId);
    void OnTouchDown();
    void OnTouchUp();
    void SetMouseStyle(MouseFormat format);
    void OnButtonTouchDown(int32_t childId);
    void OnButtonTouchUp(int32_t childId);
    void HandleHoverEvent(bool isHover);
    void HandleMouseEvent(const MouseInfo& info);
    void HandleButtonMouseEvent(bool isHover, int32_t childId);
    void HandleTextFieldHoverEvent(bool isHoverOverTextField);

    void ToJsonValueForTextField(std::unique_ptr<JsonValue>& json) const;
    void ToJsonValueForSearchIcon(std::unique_ptr<JsonValue>& json) const;
    void ToJsonValueForCancelButton(std::unique_ptr<JsonValue>& json) const;
    void ToJsonValueForSearchButtonOption(std::unique_ptr<JsonValue>& json) const;
    void ToJsonValueForCursor(std::unique_ptr<JsonValue>& json) const;

    void AnimateTouchAndHover(RefPtr<RenderContext>& renderContext, float startOpacity, float endOpacity,
        int32_t duration, const RefPtr<Curve>& curve);
    void InitFocusEvent(const RefPtr<FocusHub>& focusHub);
    void HandleFocusEvent();
    void HandleBlurEvent();
    void InitClickEvent();
    void HandleClickEvent(GestureEvent& info);
    std::string searchButton_;
    SizeF searchSize_;
    OffsetF searchOffset_;
    SizeF buttonSize_;
    OffsetF buttonOffset_;
    SizeF cancelButtonSize_;
    OffsetF cancelButtonOffset_;
    RefPtr<ClickEvent> imageClickListener_;
    RefPtr<ClickEvent> buttonClickListener_;
    RefPtr<ClickEvent> cancelButtonClickListener_;
    RefPtr<TextFieldController> searchController_;
    FocusChoice focusChoice_ = FocusChoice::SEARCH;

    RefPtr<TouchEventImpl> touchListener_;
    RefPtr<TouchEventImpl> searchButtonTouchListener_;
    RefPtr<TouchEventImpl> cancelButtonTouchListener_;
    RefPtr<InputEvent> hoverEvent_;
    RefPtr<InputEvent> mouseEvent_;
    RefPtr<InputEvent> searchButtonMouseEvent_;
    RefPtr<InputEvent> cancelButtonMouseEvent_;
    RefPtr<InputEvent> textFieldHoverEvent_ = nullptr;
    RefPtr<ClickEvent> clickListener_;

    bool isHover_ = false;
    bool isCancelButtonHover_ = false;
    bool isSearchButtonHover_ = false;
    bool isSearchButtonEnabled_ = false;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SEARCH_SEARCH_PATTERN_H
