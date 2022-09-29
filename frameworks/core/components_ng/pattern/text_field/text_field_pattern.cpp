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

#include "core/components_ng/pattern/text_field/text_field_pattern.h"

#include "base/i18n/localization.h"
#include "base/memory/referenced.h"
#include "core/common/clipboard/clipboard_proxy.h"
#include "core/common/container_scope.h"
#include "core/common/font_manager.h"
#include "core/common/ime/text_edit_controller.h"
#include "core/common/ime/text_input_client.h"
#include "core/common/ime/text_input_connection.h"
#include "core/common/ime/text_input_formatter.h"
#include "core/common/ime/text_input_type.h"
#include "core/common/ime/text_selection.h"
#include "core/components_ng/pattern/text_field/text_field_controller.h"
#include "core/components_ng/pattern/text_field/text_field_event_hub.h"
#include "core/components_ng/pattern/text_field/text_field_layout_algorithm.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/paragraph.h"

#if defined(ENABLE_STANDARD_INPUT)
#include "core/components_ng/pattern/text_field/on_text_changed_listener_impl.h"
#endif

namespace OHOS::Ace::NG {

TextFieldPattern::TextFieldPattern() = default;
TextFieldPattern::~TextFieldPattern()
{
    LOGI("Destruction text field.");
    if (textEditingController_) {
        textEditingController_->Clear();
        textEditingController_->RemoveObserver(WeakClaim(this));
    }

    // If soft keyboard is still exist, close it.
#if defined(ENABLE_STANDARD_INPUT)
        LOGI("Destruction text field, close input method.");
        MiscServices::InputMethodController::GetInstance()->Close();
#endif
}

#if defined(ENABLE_STANDARD_INPUT)
void TextFieldPattern::UpdateConfiguration()
{
    MiscServices::Configuration configuration;
    configuration.SetEnterKeyType(static_cast<MiscServices::EnterKeyType>((int32_t)action_));
    configuration.SetTextInputType(static_cast<MiscServices::TextInputType>((int32_t)keyboard_));
    MiscServices::InputMethodController::GetInstance()->OnConfigurationChange(configuration);
}
#endif

bool TextFieldPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto textFieldLayoutAlgorithm = DynamicCast<TextFieldLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(textFieldLayoutAlgorithm, false);
    auto paragraph = textFieldLayoutAlgorithm->GetParagraph();
    if (!paragraph) {
        LOGD("on layout process, just return");
        return false;
    }
    paragraph_ = textFieldLayoutAlgorithm->GetParagraph();
    textRect_ = textFieldLayoutAlgorithm->GetTextRect();
    imageRect_ = textFieldLayoutAlgorithm->GetTextRect();
    return true;
}

const TextEditingValue& TextFieldPattern::GetEditingValue() const
{
    return textEditingController_->GetValue();
}

void TextFieldPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (clickListener_) {
        return;
    }
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    instanceId_ = context->GetInstanceId();
#if defined(ENABLE_STANDARD_INPUT)
    UpdateConfiguration();
#endif
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto textFieldPattern = weak.Upgrade();
        CHECK_NULL_VOID(textFieldPattern);
        auto context = textFieldPattern->GetHost()->GetContext();
        CHECK_NULL_VOID(context);
        auto textFieldManager = context->GetTextFieldManager();
        CHECK_NULL_VOID(textFieldManager);
        textFieldManager->SetClickPosition(info.GetGlobalLocation());
        textFieldPattern->OnClick();
    };

    clickListener_ = MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gesture->AddClickEvent(clickListener_);

    if (textFieldController_) {
        textFieldController_->SetCaretPosition([weak = WeakClaim(this)](int32_t caretPosition) {
            auto textFieldPattern = weak.Upgrade();
            CHECK_NULL_VOID(textFieldPattern);
            auto host = textFieldPattern->GetHost();
            CHECK_NULL_VOID(host);
            textFieldPattern->UpdateCaretPosition(caretPosition);
            textFieldPattern->cursorPositionType_ = CursorPositionType::NORMAL;
            host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        });
    }
}

void TextFieldPattern::UpdateCaretPosition(int32_t caretPosition) {}

void TextFieldPattern::OnClick()
{
    RequestKeyboard(false, true, true);
}

bool TextFieldPattern::RequestKeyboard(bool isFocusViewChanged, bool needStartTwinkling, bool needShowSoftKeyboard)
{
    auto host = GetHost();
    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, false);
    if (needShowSoftKeyboard) {
        LOGI("Start to request keyboard");
#if defined(ENABLE_STANDARD_INPUT)
        if (textChangeListener_ == nullptr) {
            textChangeListener_ = new OnTextChangedListenerImpl(WeakClaim(this));
        }
        auto inputMethod = MiscServices::InputMethodController::GetInstance();
        if (!inputMethod) {
            LOGE("Request open soft keyboard failed because input method is null.");
            return false;
        }
        if (context) {
            LOGI("RequestKeyboard set calling window id is : %{public}d", context->GetWindowId());
            inputMethod->SetCallingWindow(context->GetWindowId());
        }
        inputMethod->Attach(textChangeListener_, needShowSoftKeyboard);
#endif
    }
    auto manager = context->GetTextFieldManager();
    if (manager && AceType::InstanceOf<TextFieldManager>(manager)) {
        auto textFieldManager = AceType::DynamicCast<TextFieldManager>(manager);
        textFieldManager->SetOnFocusTextField(WeakClaim(this));
    }
    auto textFieldLayoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(textFieldLayoutProperty, false);
    // TODO: start twinkling
    return true;
}

bool TextFieldPattern::CloseKeyboard(bool forceClose)
{
    if (forceClose) {
        LOGI("Request close soft keyboard");
#if defined(ENABLE_STANDARD_INPUT)
        auto inputMethod = MiscServices::InputMethodController::GetInstance();
        if (!inputMethod) {
            LOGE("Request close soft keyboard failed because input method is null.");
            return false;
        }
        inputMethod->HideTextInput();
#endif
        return true;
    }
    return false;
}

void TextFieldPattern::OnTextInputActionUpdate(TextInputAction value) {}

void TextFieldPattern::UpdateEditingValue(const std::shared_ptr<TextEditingValue>& value, bool needFireChangeEvent)
{
    CHECK_NULL_VOID(value);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    ContainerScope scope(context->GetInstanceId());

    TextEditingValue valueNeedToUpdate = *value;
    // TODO: change counter style
    // TODO: filter values
    // TODO: update obscure pending for password input

    SetEditingValue(std::move(valueNeedToUpdate), needFireChangeEvent);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    // TODO: fire events in event hub if value changed
}

void TextFieldPattern::SetEditingValue(TextEditingValue&& newValue, bool needFireChangeEvent)
{
    // set value to layout property
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateValue(newValue.text);
    textEditingController_->SetValue(newValue, needFireChangeEvent);
}

void TextFieldPattern::ClearEditingValue()
{
    TextEditingValue emptyValue;
    SetEditingValue(std::move(emptyValue));
}

void TextFieldPattern::PerformAction(TextInputAction action, bool forceCloseKeyboard) {}

void TextFieldPattern::OnValueChanged(bool needFireChangeEvent, bool needFireSelectChangeEvent) {}

} // namespace OHOS::Ace::NG