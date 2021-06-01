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

#include "frameworks/bridge/common/dom/dom_input.h"

#include <set>

#include "core/components/button/button_component.h"
#include "core/components/checkable/checkable_component.h"
#include "core/components/text_field/text_field_component.h"
#include "frameworks/bridge/common/dom/input/dom_button_util.h"
#include "frameworks/bridge/common/dom/input/dom_checkbox_util.h"
#include "frameworks/bridge/common/dom/input/dom_radio_util.h"
#include "frameworks/bridge/common/dom/input/dom_textfield_util.h"

namespace OHOS::Ace::Framework {
namespace {

constexpr uint32_t METHOD_SHOW_ERROR_ARGS_SIZE = 1;

// input type
constexpr char INPUT_TYPE_BUTTON[] = "button";
constexpr char INPUT_TYPE_CHECKBOX[] = "checkbox";
constexpr char INPUT_TYPE_RADIO[] = "radio";
constexpr char INPUT_TYPE_TEXT[] = "text";
constexpr char INPUT_TYPE_EMAIL[] = "email";
constexpr char INPUT_TYPE_DATE[] = "date";
constexpr char INPUT_TYPE_TIME[] = "time";
constexpr char INPUT_TYPE_NUMBER[] = "number";
constexpr char INPUT_TYPE_PASSWORD[] = "password";

std::set<std::string> g_textCategory;

// If type is changed between g_textCategory, there is no need to recreate components.
bool ShouldCreateNewComponent(const std::string& oldType, const std::string& newType)
{
    if (g_textCategory.empty()) {
        g_textCategory = std::set<std::string>({ INPUT_TYPE_TEXT, INPUT_TYPE_EMAIL, INPUT_TYPE_DATE, INPUT_TYPE_TIME,
            INPUT_TYPE_NUMBER, INPUT_TYPE_PASSWORD });
    }
    return g_textCategory.find(oldType) == g_textCategory.end() || g_textCategory.find(newType) == g_textCategory.end();
}

} // namespace

DOMInput::DOMInput(NodeId nodeId, const std::string& nodeName) : DOMNode(nodeId, nodeName) {}

DOMInput::~DOMInput()
{
    if (!checkableChangeMarker_.IsEmpty()) {
        BackEndEventManager<void(const std::string&)>::GetInstance().RemoveBackEndEvent(checkableChangeMarker_);
        checkableChangeMarker_.Reset();
    }
}

bool DOMInput::SetSpecializedAttr(const std::pair<std::string, std::string>& attr)
{
    static const std::set<std::string> inputCategory { INPUT_TYPE_BUTTON, INPUT_TYPE_CHECKBOX, INPUT_TYPE_RADIO,
        INPUT_TYPE_TEXT, INPUT_TYPE_EMAIL, INPUT_TYPE_DATE, INPUT_TYPE_TIME, INPUT_TYPE_NUMBER, INPUT_TYPE_PASSWORD };
    if (attr.first == DOM_INPUT_TYPE) {
        std::string typeName = attr.second;
        if (typeName.empty() || inputCategory.find(typeName) == inputCategory.end()) {
            typeName = INPUT_TYPE_TEXT;
        }
        type_.second = ShouldCreateNewComponent(type_.first, typeName);
        type_.first = typeName;
    }
    inputAttrs_[attr.first] = attr.second;
    return false;
}

void DOMInput::ResetInitializedStyle()
{
    if (type_.first == INPUT_TYPE_CHECKBOX) {
        InitCheckable<CheckboxComponent, CheckboxTheme>();
    } else if (type_.first == INPUT_TYPE_RADIO) {
        InitCheckable<RadioComponent<std::string>, RadioTheme>();
    } else {
        const auto& theme = GetTheme<TextFieldTheme>();
        DOMTextFieldUtil::InitDefaultValue(
            GetBoxComponent(), AceType::DynamicCast<TextFieldComponent>(inputChild_), theme);
        DOMTextFieldUtil::SetDisableStyle(AceType::DynamicCast<TextFieldComponent>(inputChild_), theme);
    }
}

bool DOMInput::SetSpecializedStyle(const std::pair<std::string, std::string>& style)
{
    inputStyles_[style.first] = style.second;
    return false;
}

bool DOMInput::AddSpecializedEvent(int32_t pageId, const std::string& event)
{
    tempEvent_.emplace_back(event);
    pageId_ = pageId;
    return false;
}

void DOMInput::CallSpecializedMethod(const std::string& method, const std::string& args)
{
    auto textField = AceType::DynamicCast<TextFieldComponent>(inputChild_);
    if (!textField) {
        return;
    }
    auto controller = textField->GetTextFieldController();
    if (!controller) {
        return;
    }
    if (method == DOM_INPUT_METHOD_SHOW_ERROR) {
        std::unique_ptr<JsonValue> argsValue = JsonUtil::ParseJsonString(args);
        if (!argsValue || !argsValue->IsArray() || argsValue->GetArraySize() != METHOD_SHOW_ERROR_ARGS_SIZE) {
            LOGE("parse args error");
            return;
        }

        std::unique_ptr<JsonValue> error = argsValue->GetArrayItem(0)->GetValue("error");
        if (!error || !error->IsString()) {
            LOGE("get error text failed");
            return;
        }
        std::string errorText = error->GetString();
        controller->ShowError(errorText);
    } else if (method == DOM_INPUT_METHOD_DELETE) {
        controller->Delete();
    }
}

void DOMInput::OnRequestFocus(bool shouldFocus)
{
    if ((type_.first == INPUT_TYPE_CHECKBOX) || (type_.first == INPUT_TYPE_RADIO) ||
        (type_.first == INPUT_TYPE_BUTTON)) {
        DOMNode::OnRequestFocus(shouldFocus);
        return;
    }
    auto textField = AceType::DynamicCast<TextFieldComponent>(inputChild_);
    if (!textField) {
        return;
    }
    auto textFieldController = textField->GetTextFieldController();
    if (!textFieldController) {
        return;
    }
    textFieldController->Focus(shouldFocus);
}

void DOMInput::PrepareCheckedListener()
{
    bool isCheckbox = (type_.first == INPUT_TYPE_CHECKBOX);
    bool isRadio = (type_.first == INPUT_TYPE_RADIO);
    if (isCheckbox || isRadio) {
        if (!checkableChangeMarker_.IsEmpty()) {
            BackEndEventManager<void(const std::string&)>::GetInstance().RemoveBackEndEvent(checkableChangeMarker_);
            checkableChangeMarker_.Reset();
        }
        auto checkableChangeCallback = [weak = AceType::WeakClaim(this), isCheckbox](const std::string& checked) {
            auto domNode = weak.Upgrade();
            if (!domNode) {
                LOGE("get dom node failed!");
                return;
            }
            bool isChecked = false;
            if (checked.find("\"checked\":true") != std::string::npos) {
                isChecked = true;
            }
            domNode->OnChecked(isChecked);
        };
        checkableChangeMarker_ = BackEndEventManager<void(const std::string&)>::GetInstance().GetAvailableMarker();
        BackEndEventManager<void(const std::string&)>::GetInstance().BindBackendEvent(
            checkableChangeMarker_, checkableChangeCallback);
        AceType::DynamicCast<CheckableComponent>(inputChild_)->SetDomChangeEvent(checkableChangeMarker_);
    }
}

void DOMInput::PrepareSpecializedComponent()
{
    if (boxComponent_) {
        boxComponent_->SetMouseAnimationType(HoverAnimationType::OPACITY);
    }
    if (boxComponent_ && boxComponent_->GetBackDecoration()) {
        boxBorder_ = boxComponent_->GetBackDecoration()->GetBorder();
    }
    // dom is created and type is not changed
    if (!type_.second && inputChild_) {
        UpdateSpecializedComponent();
    } else {
        CreateSpecializedComponent();
    }

    auto textField = AceType::DynamicCast<TextFieldComponent>(inputChild_);
    if (textField) {
        textField->SetInputOptions(inputOptions_);
    }

    inputAttrs_.erase(DOM_INPUT_VALUE);
    UpdateSpecializedComponentStyle();
    if (HasCheckedPseudo()) {
        PrepareCheckedListener();
    }
    AddSpecializedComponentEvent();
}

RefPtr<Component> DOMInput::GetSpecializedComponent()
{
    return inputChild_;
}

void DOMInput::CreateSpecializedComponent()
{
    type_.second = false;
    auto radioComponent = AceType::DynamicCast<RadioComponent<std::string>>(inputChild_);
    if (radioComponent) {
        DOMRadioUtil::RemoveRadioComponent(*this, radioComponent);
    }
    if (type_.first == INPUT_TYPE_BUTTON) {
        boxComponent_->SetDeliverMinToChild(true);
        inputChild_ = DOMButtonUtil::CreateComponentAndSetChildAttr(inputAttrs_, *this);
    } else if (type_.first == INPUT_TYPE_CHECKBOX) {
        boxComponent_->SetDeliverMinToChild(true);
        inputChild_ = DOMCheckboxUtil::CreateComponentAndSetChildAttr(inputAttrs_, *this);
    } else if (type_.first == INPUT_TYPE_RADIO) {
        boxComponent_->SetDeliverMinToChild(true);
        inputChild_ = DOMRadioUtil::CreateComponentAndSetChildAttr(inputAttrs_, *this);
    } else {
        // if type is not be set, will create a textfield component
        inputChild_ =
            DOMTextFieldUtil::CreateComponentAndSetChildAttr(GetBoxComponent(), type_.first, inputAttrs_, *this);
    }
    if (IsRightToLeft()) {
        inputChild_->SetTextDirection(TextDirection::RTL);
    }
}

void DOMInput::UpdateSpecializedComponent()
{
    if (type_.first == INPUT_TYPE_BUTTON) {
        boxComponent_->SetDeliverMinToChild(true);
        DOMButtonUtil::SetChildAttr(
            AceType::DynamicCast<ButtonComponent>(inputChild_), inputAttrs_, GetTheme<ButtonTheme>());
    } else if (type_.first == INPUT_TYPE_CHECKBOX) {
        boxComponent_->SetDeliverMinToChild(true);
        DOMCheckboxUtil::SetChildAttr(AceType::DynamicCast<CheckboxComponent>(inputChild_), inputAttrs_);
    } else if (type_.first == INPUT_TYPE_RADIO) {
        boxComponent_->SetDeliverMinToChild(true);
        DOMRadioUtil::SetChildAttr(*this, AceType::DynamicCast<RadioComponent<std::string>>(inputChild_), inputAttrs_);
    } else {
        DOMTextFieldUtil::SetChildAttr(
            AceType::DynamicCast<TextFieldComponent>(inputChild_), GetBoxComponent(), type_.first, inputAttrs_);
    }
}

void DOMInput::UpdateSpecializedComponentStyle()
{
    static const LinearMapNode<void (*)(const RefPtr<BoxComponent>&, const RefPtr<Component>&,
        const std::map<std::string, std::string>&, const Border&, DOMInput&)>
        styleOperators[] = {
            { INPUT_TYPE_BUTTON,
                [](const RefPtr<BoxComponent>& boxComponent, const RefPtr<Component>& component,
                    const std::map<std::string, std::string>& styles, const Border& boxBorder, DOMInput& input) {
                    DOMButtonUtil::SetChildStyle(
                        boxComponent, AceType::DynamicCast<ButtonComponent>(component), styles, input);
                } },
            { INPUT_TYPE_DATE,
                [](const RefPtr<BoxComponent>& boxComponent, const RefPtr<Component>& component,
                    const std::map<std::string, std::string>& styles, const Border& boxBorder, DOMInput& input) {
                    DOMTextFieldUtil::SetChildStyle(
                        boxComponent, AceType::DynamicCast<TextFieldComponent>(component), styles, boxBorder, input);
                } },
            { INPUT_TYPE_EMAIL,
                [](const RefPtr<BoxComponent>& boxComponent, const RefPtr<Component>& component,
                    const std::map<std::string, std::string>& styles, const Border& boxBorder, DOMInput& input) {
                    DOMTextFieldUtil::SetChildStyle(
                        boxComponent, AceType::DynamicCast<TextFieldComponent>(component), styles, boxBorder, input);
                } },
            { INPUT_TYPE_NUMBER,
                [](const RefPtr<BoxComponent>& boxComponent, const RefPtr<Component>& component,
                    const std::map<std::string, std::string>& styles, const Border& boxBorder, DOMInput& input) {
                    DOMTextFieldUtil::SetChildStyle(
                        boxComponent, AceType::DynamicCast<TextFieldComponent>(component), styles, boxBorder, input);
                } },
            { INPUT_TYPE_PASSWORD,
                [](const RefPtr<BoxComponent>& boxComponent, const RefPtr<Component>& component,
                    const std::map<std::string, std::string>& styles, const Border& boxBorder, DOMInput& input) {
                    DOMTextFieldUtil::SetChildStyle(
                        boxComponent, AceType::DynamicCast<TextFieldComponent>(component), styles, boxBorder, input);
                } },
            { INPUT_TYPE_RADIO,
                [](const RefPtr<BoxComponent>& boxComponent, const RefPtr<Component>& component,
                    const std::map<std::string, std::string>& styles, const Border& boxBorder, DOMInput& input) {
                    DOMRadioUtil::SetChildStyle(
                        boxComponent, AceType::DynamicCast<RadioComponent<std::string>>(component), styles);
                } },
            { INPUT_TYPE_TEXT,
                [](const RefPtr<BoxComponent>& boxComponent, const RefPtr<Component>& component,
                    const std::map<std::string, std::string>& styles, const Border& boxBorder, DOMInput& input) {
                    DOMTextFieldUtil::SetChildStyle(
                        boxComponent, AceType::DynamicCast<TextFieldComponent>(component), styles, boxBorder, input);
                } },
            { INPUT_TYPE_TIME,
                [](const RefPtr<BoxComponent>& boxComponent, const RefPtr<Component>& component,
                    const std::map<std::string, std::string>& styles, const Border& boxBorder, DOMInput& input) {
                    DOMTextFieldUtil::SetChildStyle(
                        boxComponent, AceType::DynamicCast<TextFieldComponent>(component), styles, boxBorder, input);
                } },
        };
    auto styleOperatorIter = BinarySearchFindIndex(styleOperators, ArraySize(styleOperators), type_.first.c_str());
    if (styleOperatorIter != -1) {
        styleOperators[styleOperatorIter].value(GetBoxComponent(), inputChild_, inputStyles_, boxBorder_, *this);
    }
    auto textField = DynamicCast<TextFieldComponent>(inputChild_);
    if (textField) {
        textField->SetIsVisible(IsShow());
    }
}

void DOMInput::AddSpecializedComponentEvent()
{
    static const LinearMapNode<void (*)(
        const RefPtr<Component>&, const int32_t, const std::string&, const std::vector<std::string>&)>
        eventOperators[] = {
            { INPUT_TYPE_BUTTON,
                [](const RefPtr<Component>& component, int32_t pageId, const std::string& nodeId,
                    const std::vector<std::string>& events) {
                    DOMButtonUtil::AddChildEvent(
                        AceType::DynamicCast<ButtonComponent>(component), pageId, nodeId, events);
                } },
            { INPUT_TYPE_CHECKBOX,
                [](const RefPtr<Component>& component, int32_t pageId, const std::string& nodeId,
                    const std::vector<std::string>& events) {
                    DOMCheckboxUtil::AddChildEvent(
                        AceType::DynamicCast<CheckboxComponent>(component), pageId, nodeId, events);
                } },
            { INPUT_TYPE_DATE,
                [](const RefPtr<Component>& component, int32_t pageId, const std::string& nodeId,
                    const std::vector<std::string>& events) {
                    DOMTextFieldUtil::AddChildEvent(
                        AceType::DynamicCast<TextFieldComponent>(component), pageId, nodeId, events);
                } },
            { INPUT_TYPE_EMAIL,
                [](const RefPtr<Component>& component, int32_t pageId, const std::string& nodeId,
                    const std::vector<std::string>& events) {
                    DOMTextFieldUtil::AddChildEvent(
                        AceType::DynamicCast<TextFieldComponent>(component), pageId, nodeId, events);
                } },
            { INPUT_TYPE_NUMBER,
                [](const RefPtr<Component>& component, int32_t pageId, const std::string& nodeId,
                    const std::vector<std::string>& events) {
                    DOMTextFieldUtil::AddChildEvent(
                        AceType::DynamicCast<TextFieldComponent>(component), pageId, nodeId, events);
                } },
            { INPUT_TYPE_PASSWORD,
                [](const RefPtr<Component>& component, int32_t pageId, const std::string& nodeId,
                    const std::vector<std::string>& events) {
                    DOMTextFieldUtil::AddChildEvent(
                        AceType::DynamicCast<TextFieldComponent>(component), pageId, nodeId, events);
                } },
            { INPUT_TYPE_RADIO,
                [](const RefPtr<Component>& component, int32_t pageId, const std::string& nodeId,
                    const std::vector<std::string>& events) {
                    DOMRadioUtil::AddChildEvent(
                        AceType::DynamicCast<RadioComponent<std::string>>(component), pageId, nodeId, events);
                } },
            { INPUT_TYPE_TEXT,
                [](const RefPtr<Component>& component, int32_t pageId, const std::string& nodeId,
                    const std::vector<std::string>& events) {
                    DOMTextFieldUtil::AddChildEvent(
                        AceType::DynamicCast<TextFieldComponent>(component), pageId, nodeId, events);
                } },
            { INPUT_TYPE_TIME,
                [](const RefPtr<Component>& component, int32_t pageId, const std::string& nodeId,
                    const std::vector<std::string>& events) {
                    DOMTextFieldUtil::AddChildEvent(
                        AceType::DynamicCast<TextFieldComponent>(component), pageId, nodeId, events);
                } },
        };
    auto eventOperatorIter = BinarySearchFindIndex(eventOperators, ArraySize(eventOperators), type_.first.c_str());
    if (eventOperatorIter != -1) {
        eventOperators[eventOperatorIter].value(inputChild_, pageId_, GetNodeIdForEvent(), tempEvent_);
    }
}

} // namespace OHOS::Ace::Framework
