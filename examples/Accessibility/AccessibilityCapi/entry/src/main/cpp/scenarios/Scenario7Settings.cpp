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

#include <arkui/native_interface_accessibility.h>
#include <hilog/log.h>

#include "Scenario7Settings.h"
#include "fakenode/FakeCustomWidget.h"
#include "fakenode/FakeCheckbox.h"


namespace {

const int64_t ROOT_ELEMENT_ID = 0;  // Element ID for root node
const int32_t THEME_COUNT = 3;      // Number of themes available
const int32_t LANGUAGE_COUNT = 3;   // Number of languages available

} // namespace


namespace NativeXComponentSample {

/**
 * @brief Constructor for Scenario7Settings
 */
Scenario7Settings::Scenario7Settings()
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario7",
        "Scenario7Settings constructor called");

    // Initialize theme configurations
    themes_[0] = {"浅色", "#FFFFFF", 1.0f, 1};
    themes_[1] = {"深色", "#1A1A1A", 0.95f, 2};
    themes_[2] = {"高对比度", "#000000", 1.0f, 3};
}

/**
 * @brief Destructor for Scenario7Settings
 */
Scenario7Settings::~Scenario7Settings()
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario7",
        "Scenario7Settings destructor called");
    Cleanup();
}

/**
 * @brief Initializes the settings page scenario
 */
void Scenario7Settings::Initialize()
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario7",
        "Initializing Scenario7Settings");
    CreateNodes();
    ConfigureNodes();
}

/**
 * @brief Creates all nodes for the settings page scenario
 */
void Scenario7Settings::CreateNodes()
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario7",
        "Creating nodes for settings page");

    // 1. Create root node (container)
    auto* container = new FakeCustomWidget("settingsPage");
    container->SetElementId(ROOT_ELEMENT_ID);
    container->SetAccessibilityGroup(true);
    container->SetAccessibilityLevel("page");
    rootNode_ = container;
    nodes_.push_back(rootNode_);

    // 2. Create WiFi switch
    wifiSwitch_ = new AccessibleObject("wifiSwitch");
    wifiSwitch_->SetElementId(AllocateElementId());
    wifiSwitch_->SetName("WiFi");
    wifiSwitch_->SetComponentType("toggle");
    wifiSwitch_->SetAccessibilityText("WiFi开关");
    wifiSwitch_->SetHintText("开启或关闭WiFi连接");
    wifiSwitch_->SetClickable(true);
    wifiSwitch_->SetFocusable(true);
    wifiSwitch_->SetIsEnable(true);
    wifiSwitch_->SetIsVisible(true);
    wifiSwitch_->SetParent(rootNode_);
    nodes_.push_back(wifiSwitch_);

    // 3. Create Bluetooth switch
    bluetoothSwitch_ = new AccessibleObject("bluetoothSwitch");
    bluetoothSwitch_->SetElementId(AllocateElementId());
    bluetoothSwitch_->SetName("蓝牙");
    bluetoothSwitch_->SetComponentType("toggle");
    bluetoothSwitch_->SetAccessibilityText("蓝牙开关");
    bluetoothSwitch_->SetHintText("开启或关闭蓝牙");
    bluetoothSwitch_->SetClickable(true);
    bluetoothSwitch_->SetFocusable(true);
    bluetoothSwitch_->SetIsEnable(true);
    bluetoothSwitch_->SetIsVisible(true);
    bluetoothSwitch_->SetParent(rootNode_);
    nodes_.push_back(bluetoothSwitch_);

    // 4. Create notification switch
    notificationSwitch_ = new AccessibleObject("notificationSwitch");
    notificationSwitch_->SetElementId(AllocateElementId());
    notificationSwitch_->SetName("通知");
    notificationSwitch_->SetComponentType("toggle");
    notificationSwitch_->SetAccessibilityText("通知开关");
    notificationSwitch_->SetHintText("开启或关闭应用通知");
    notificationSwitch_->SetClickable(true);
    notificationSwitch_->SetFocusable(true);
    notificationSwitch_->SetIsEnable(true);
    notificationSwitch_->SetIsVisible(true);
    notificationSwitch_->SetParent(rootNode_);
    nodes_.push_back(notificationSwitch_);

    // 5. Create theme selector
    themeSelector_ = new AccessibleObject("themeSelector");
    themeSelector_->SetElementId(AllocateElementId());
    themeSelector_->SetName("主题");
    themeSelector_->SetComponentType("select");
    themeSelector_->SetAccessibilityText("选择显示主题");
    themeSelector_->SetHintText("当前主题：浅色");
    themeSelector_->SetClickable(true);
    themeSelector_->SetFocusable(true);
    themeSelector_->SetIsEnable(true);
    themeSelector_->SetIsVisible(true);
    themeSelector_->SetParent(rootNode_);
    nodes_.push_back(themeSelector_);

    // 6. Create language selector
    languageSelector_ = new AccessibleObject("languageSelector");
    languageSelector_->SetElementId(AllocateElementId());
    languageSelector_->SetName("语言");
    languageSelector_->SetComponentType("select");
    languageSelector_->SetAccessibilityText("选择系统语言");
    languageSelector_->SetHintText("当前语言：简体中文");
    languageSelector_->SetClickable(true);
    languageSelector_->SetFocusable(true);
    languageSelector_->SetIsEnable(true);
    languageSelector_->SetIsVisible(true);
    languageSelector_->SetParent(rootNode_);
    nodes_.push_back(languageSelector_);

    // 7. Create about button
    aboutButton_ = new AccessibleObject("aboutButton");
    aboutButton_->SetElementId(AllocateElementId());
    aboutButton_->SetName("关于");
    aboutButton_->SetComponentType("button");
    aboutButton_->SetAccessibilityText("查看应用信息");
    aboutButton_->SetAccessibilityDescription("版本 1.0.0");
    aboutButton_->SetClickable(true);
    aboutButton_->SetFocusable(true);
    aboutButton_->SetIsEnable(true);
    aboutButton_->SetIsVisible(true);
    aboutButton_->SetParent(rootNode_);
    nodes_.push_back(aboutButton_);

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario7",
        "Created %{public}zu nodes for settings page", nodes_.size());
}

/**
 * @brief Configures the initial state of nodes
 */
void Scenario7Settings::ConfigureNodes()
{
    // Configure initial state
    UpdateSwitchStates();

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario7",
        "Configured settings page nodes");
}

/**
 * @brief Updates the switch states to match current settings
 */
void Scenario7Settings::UpdateSwitchStates()
{
    // WiFi switch state
    if (wifiSwitch_) {
        FakeCheckbox* wifiCheckbox = new FakeCheckbox("wifi");
        wifiCheckbox->SetChecked(wifiEnabled_);
    }

    // Bluetooth switch state
    if (bluetoothSwitch_) {
        FakeCheckbox* btCheckbox = new FakeCheckbox("bluetooth");
        btCheckbox->SetChecked(bluetoothEnabled_);
    }

    // Notification switch state
    if (notificationSwitch_) {
        FakeCheckbox* notifCheckbox = new FakeCheckbox("notification");
        notifCheckbox->SetChecked(notificationEnabled_);
    }
}

/**
 * @brief Sends a state changed event for a node
 * @param node The node that changed state
 * @param announcement The announcement text to broadcast
 */
void Scenario7Settings::SendStateChangedEvent(AccessibleObject* node,
    const std::string& announcement)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario7",
        "Sending state changed event: %{public}s", announcement.c_str());

    // Demo event management interface
    // 1. Create event info object
    auto eventInfo = OH_ArkUI_CreateAccessibilityEventInfo();
    if (!eventInfo) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Scenario7",
            "Failed to create event info");
        return;
    }

    // 2. Set event type - use SELECTED event to indicate state change
    OH_ArkUI_AccessibilityEventSetEventType(
        eventInfo,
        ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_SELECTED);

    // 3. Set announcement text
    OH_ArkUI_AccessibilityEventSetTextAnnouncedForAccessibility(
        eventInfo,
        announcement.c_str());

    // 4. Set associated element info
    auto elementInfo = OH_ArkUI_CreateAccessibilityElementInfo();
    if (elementInfo) {
        OH_ArkUI_AccessibilityElementInfoSetElementId(
            elementInfo, node->GetElementId());
        OH_ArkUI_AccessibilityEventSetElementInfo(eventInfo, elementInfo);
        OH_ArkUI_DestoryAccessibilityElementInfo(elementInfo);
    }

    // 5. Send event (actual usage requires sending through provider)
    // This only demonstrates the interface call
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario7",
        "Event created: type=STATE_CHANGED, text=%{public}s",
        announcement.c_str());

    // 6. Destroy event info object
    OH_ArkUI_DestoryAccessibilityEventInfo(eventInfo);
}

/**
 * @brief Sends an announcement event
 * @param text The text to announce
 */
void Scenario7Settings::SendAnnouncementEvent(const std::string& text)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario7",
        "Sending announcement event: %{public}s", text.c_str());

    // Demo announcement event
    auto eventInfo = OH_ArkUI_CreateAccessibilityEventInfo();
    if (!eventInfo) {
        return;
    }

    OH_ArkUI_AccessibilityEventSetEventType(
        eventInfo,
        ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_ANNOUNCE_FOR_ACCESSIBILITY);
    OH_ArkUI_AccessibilityEventSetTextAnnouncedForAccessibility(
        eventInfo,
        text.c_str());

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario7",
        "Announcement event created: %{public}s", text.c_str());

    OH_ArkUI_DestoryAccessibilityEventInfo(eventInfo);
}

/**
 * @brief Gets all nodes in this scenario
 * @return Vector of pointers to all nodes
 */
const std::vector<AccessibleObject*>& Scenario7Settings::GetNodes() const
{
    return nodes_;
}

/**
 * @brief Gets the root node of this scenario
 * @return Pointer to the root node
 */
AccessibleObject* Scenario7Settings::GetRootNode() const
{
    return rootNode_;
}

/**
 * @brief Finds a node by its element ID
 * @param elementId The element ID to search for
 * @return Pointer to the node if found, nullptr otherwise
 */
AccessibleObject* Scenario7Settings::GetNodeById(int64_t elementId)
{
    if (elementId <= ROOT_ELEMENT_ID || elementId > static_cast<int64_t>(nodes_.size())) {
        return nullptr;
    }
    return nodes_[elementId - 1];
}

/**
 * @brief Handles an accessibility action on a node
 * @param elementId The element ID to perform the action on
 * @param action The type of action to perform
 * @return true if the action was handled, false otherwise
 */
bool Scenario7Settings::HandleAction(int64_t elementId,
    ArkUI_Accessibility_ActionType action)
{
    auto* node = GetNodeById(elementId);
    if (!node) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Scenario7",
            "Node not found: elementId=%{public}lld", elementId);
        return false;
    }

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario7",
        "HandleAction: elementId=%{public}lld, action=%{public}d",
        elementId, action);

    switch (action) {
        case ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_CLICK:
            // Handle WiFi switch click
            if (node == wifiSwitch_) {
                wifiEnabled_ = !wifiEnabled_;
                UpdateSwitchStates();
                std::string announcement =
                    wifiEnabled_ ? "WiFi已开启" : "WiFi已关闭";
                SendStateChangedEvent(wifiSwitch_, announcement);
                SendAnnouncementEvent(announcement);
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario7",
                    "WiFi toggled: %{public}d", wifiEnabled_);
                return true;
            }
            // Handle Bluetooth switch click
            else if (node == bluetoothSwitch_) {
                bluetoothEnabled_ = !bluetoothEnabled_;
                UpdateSwitchStates();
                std::string announcement =
                    bluetoothEnabled_ ? "蓝牙已开启" : "蓝牙已关闭";
                SendStateChangedEvent(bluetoothSwitch_, announcement);
                SendAnnouncementEvent(announcement);
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario7",
                    "Bluetooth toggled: %{public}d", bluetoothEnabled_);
                return true;
            }
            // Handle notification switch click
            else if (node == notificationSwitch_) {
                notificationEnabled_ = !notificationEnabled_;
                UpdateSwitchStates();
                std::string announcement =
                    notificationEnabled_ ? "通知已开启" : "通知已关闭";
                SendStateChangedEvent(notificationSwitch_, announcement);
                SendAnnouncementEvent(announcement);
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario7",
                    "Notification toggled: %{public}d",
                    notificationEnabled_);
                return true;
            }
            // Handle theme selection
            else if (node == themeSelector_) {
                currentThemeIndex_ = (currentThemeIndex_ + 1) % THEME_COUNT;
                const auto& theme = themes_[currentThemeIndex_];
                std::string announcement =
                    "已切换到" + std::string(theme.name) + "主题";
                SendStateChangedEvent(themeSelector_, announcement);
                SendAnnouncementEvent(announcement);
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario7",
                    "Theme changed to: %{public}s", theme.name);
                return true;
            }
            // Handle language selection
            else if (node == languageSelector_) {
                currentLanguageIndex_ = (currentLanguageIndex_ + 1) % LANGUAGE_COUNT;
                const char* languages[] = {"简体中文", "English", "繁體中文"};
                std::string announcement =
                    "语言已切换为：" + std::string(languages[currentLanguageIndex_]);
                SendStateChangedEvent(languageSelector_, announcement);
                SendAnnouncementEvent(announcement);
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario7",
                    "Language changed: %{public}s",
                    languages[currentLanguageIndex_]);
                return true;
            }
            // Handle about button
            else if (node == aboutButton_) {
                std::string announcement =
                    "无障碍 C-API 示例应用，版本 1.0.0";
                SendAnnouncementEvent(announcement);
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario7",
                    "About button clicked");
                return true;
            }
            break;

        default:
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario7",
                "Unhandled action: %{public}d", action);
            break;
    }

    return false;
}

/**
 * @brief Cleans up all resources used by this scenario
 */
void Scenario7Settings::Cleanup()
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario7",
        "Cleaning up %{public}zu nodes", nodes_.size());

    if (auto* customWidget = dynamic_cast<FakeCustomWidget*>(rootNode_)) {
        customWidget->Cleanup();
    }

    nodes_.clear();
    rootNode_ = nullptr;
    wifiSwitch_ = nullptr;
    bluetoothSwitch_ = nullptr;
    notificationSwitch_ = nullptr;
    themeSelector_ = nullptr;
    languageSelector_ = nullptr;
    aboutButton_ = nullptr;
}

} // namespace NativeXComponentSample
