/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include <hilog/log.h>

#include "Scenario1LoginPage.h"


namespace {

const int64_t ROOT_ELEMENT_ID = 0;  // Element ID for root node

} // namespace


namespace NativeXComponentSample {

/**
 * @brief Constructor for Scenario1LoginPage
 */
Scenario1LoginPage::Scenario1LoginPage()
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario1",
        "Scenario1LoginPage created");
}

/**
 * @brief Destructor for Scenario1LoginPage
 */
Scenario1LoginPage::~Scenario1LoginPage()
{
    Cleanup();
}

/**
 * @brief Creates all nodes for the login page scenario
 */
void Scenario1LoginPage::CreateNodes()
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario1",
        "Creating nodes for login page");

    // 1. Create root node (container)
    auto* container = new FakeCustomWidget("loginPage");
    container->SetElementId(ROOT_ELEMENT_ID);
    container->SetAccessibilityGroup(true);
    container->SetAccessibilityLevel("page");
    rootNode_ = container;
    nodes_.push_back(rootNode_);

    // 2. Create username input field
    usernameField_ = new FakeTextField("username");
    usernameField_->SetElementId(AllocateElementId());
    usernameField_->SetHintText("请输入用户名");
    usernameField_->SetEditable(true);
    usernameField_->SetFocusable(true);
    usernameField_->SetIsPassword(false);
    usernameField_->SetAccessibilityText("用户名输入框");
    usernameField_->SetParent(rootNode_);
    nodes_.push_back(usernameField_);

    // 3. Create password input field
    passwordField_ = new FakeTextField("password");
    passwordField_->SetElementId(AllocateElementId());
    passwordField_->SetHintText("请输入密码");
    passwordField_->SetEditable(true);
    passwordField_->SetFocusable(true);
    passwordField_->SetIsPassword(true);
    passwordField_->SetAccessibilityText("密码输入框");
    passwordField_->SetParent(rootNode_);
    nodes_.push_back(passwordField_);

    // 4. Create remember password checkbox
    rememberCheckbox_ = new FakeCheckbox("rememberPassword");
    rememberCheckbox_->SetElementId(AllocateElementId());
    rememberCheckbox_->SetLabel("记住密码");
    rememberCheckbox_->SetCheckable(true);
    rememberCheckbox_->SetChecked(false);
    rememberCheckbox_->SetClickable(true);
    rememberCheckbox_->SetFocusable(true);
    rememberCheckbox_->SetAccessibilityText("记住密码");
    rememberCheckbox_->SetParent(rootNode_);
    nodes_.push_back(rememberCheckbox_);

    // 5. Create login button
    loginButton_ = new FakeButton("login");
    loginButton_->SetElementId(AllocateElementId());
    loginButton_->SetAccessibilityText("登录按钮");
    loginButton_->SetName("登录");
    loginButton_->SetClickable(true);
    loginButton_->SetFocusable(true);
    loginButton_->SetIsEnable(true);
    loginButton_->SetParent(rootNode_);
    nodes_.push_back(loginButton_);

    // 6. Create cancel button
    cancelButton_ = new FakeButton("cancel");
    cancelButton_->SetElementId(AllocateElementId());
    cancelButton_->SetAccessibilityText("取消按钮");
    cancelButton_->SetName("取消");
    cancelButton_->SetClickable(true);
    cancelButton_->SetFocusable(true);
    cancelButton_->SetParent(rootNode_);
    nodes_.push_back(cancelButton_);

    // Add child nodes to container
    if (auto* customWidget = dynamic_cast<FakeCustomWidget*>(rootNode_)) {
        customWidget->AddChild(usernameField_);
        customWidget->AddChild(passwordField_);
        customWidget->AddChild(rememberCheckbox_);
        customWidget->AddChild(loginButton_);
        customWidget->AddChild(cancelButton_);
    }

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario1",
        "Created %{public}zu nodes for login page", nodes_.size());
}

/**
 * @brief Initializes the login page scenario
 */
void Scenario1LoginPage::Initialize()
{
    CreateNodes();
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario1",
        "LoginPage initialized with %{public}zu nodes", nodes_.size());
}

/**
 * @brief Gets all nodes in this scenario
 * @return Vector of pointers to all nodes
 */
const std::vector<AccessibleObject*>& Scenario1LoginPage::GetNodes() const
{
    return nodes_;
}

/**
 * @brief Gets the root node of this scenario
 * @return Pointer to the root node
 */
AccessibleObject* Scenario1LoginPage::GetRootNode() const
{
    return rootNode_;
}

/**
 * @brief Finds a node by its element ID
 * @param elementId The element ID to search for
 * @return Pointer to the node if found, nullptr otherwise
 */
AccessibleObject* Scenario1LoginPage::GetNodeById(int64_t elementId)
{
    for (auto* node : nodes_) {
        if (node->GetElementId() == elementId) {
            return node;
        }
    }
    OH_LOG_Print(LOG_APP, LOG_WARN, LOG_PRINT_DOMAIN, "Scenario1",
        "Node not found: elementId=%{public}ld", elementId);
    return nullptr;
}

/**
 * @brief Handles an accessibility action on a node
 * @param elementId The element ID to perform the action on
 * @param action The type of action to perform
 * @return true if the action was handled, false otherwise
 */
bool Scenario1LoginPage::HandleAction(int64_t elementId,
    ArkUI_Accessibility_ActionType action)
{
    auto* node = GetNodeById(elementId);
    if (!node) {
        return false;
    }

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario1",
        "HandleAction: elementId=%{public}ld, action=%{public}d",
        elementId, action);

    switch (action) {
        case ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_CLICK:
            if (node == loginButton_) {
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario1",
                    "Login button clicked");
                node->OnClick();
                return true;
            }
            if (node == cancelButton_) {
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario1",
                    "Cancel button clicked");
                node->OnClick();
                return true;
            }
            if (node == rememberCheckbox_) {
                rememberCheckbox_->OnClick();
                return true;
            }
            break;

        case ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_GAIN_ACCESSIBILITY_FOCUS:
            node->SetFocus(true);
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario1",
                "Node %{public}ld gained focus", elementId);
            return true;

        case ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_CLEAR_ACCESSIBILITY_FOCUS:
            node->SetFocus(false);
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario1",
                "Node %{public}ld cleared focus", elementId);
            return true;

        default:
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario1",
                "Unhandled action: %{public}d", action);
            break;
    }

    return false;
}

/**
 * @brief Cleans up all resources used by this scenario
 */
void Scenario1LoginPage::Cleanup()
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario1",
        "Cleaning up %{public}zu nodes", nodes_.size());

    // Note: rootNode will clean up its child nodes, so only clean rootNode here
    if (auto* customWidget = dynamic_cast<FakeCustomWidget*>(rootNode_)) {
        customWidget->Cleanup();
    }

    nodes_.clear();
    rootNode_ = nullptr;
    usernameField_ = nullptr;
    passwordField_ = nullptr;
    rememberCheckbox_ = nullptr;
    loginButton_ = nullptr;
    cancelButton_ = nullptr;
}

} // namespace NativeXComponentSample
