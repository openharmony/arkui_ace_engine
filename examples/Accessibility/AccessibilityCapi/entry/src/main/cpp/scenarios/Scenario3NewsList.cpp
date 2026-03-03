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

#include "Scenario3NewsList.h"


namespace {

const int64_t ROOT_ELEMENT_ID = 0;       // Element ID for root node
const int32_t VALUE_ZERO = 0;            // Zero value
const int32_t VALUE_ONE = 1;             // One value
const int32_t VALUE_TWO = 2;             // Two value
const int32_t VALUE_THREE = 3;           // Three value
const int32_t PAGE_SIZE = 9;             // Page size for scrolling
const int32_t NEWS_ITEM_OFFSET = 3;      // Offset for news items in element ID

} // namespace


namespace NativeXComponentSample {

/**
 * @brief Constructor for Scenario3NewsList
 */
Scenario3NewsList::Scenario3NewsList()
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario3",
        "Scenario3NewsList constructor called");
}

/**
 * @brief Destructor for Scenario3NewsList
 */
Scenario3NewsList::~Scenario3NewsList()
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario3",
        "Scenario3NewsList destructor called");
    Cleanup();
}

/**
 * @brief Initializes the news list scenario
 */
void Scenario3NewsList::Initialize()
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario3",
        "Initializing Scenario3NewsList");
    CreateNodes();
    ConfigureNodes();
}

/**
 * @brief Creates all nodes for the news list scenario
 */
void Scenario3NewsList::CreateNodes()
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario3",
        "Creating nodes for news list");

    // 1. Create root node (container)
    auto* container = new FakeCustomWidget("newsList");
    container->SetElementId(ROOT_ELEMENT_ID);
    container->SetAccessibilityGroup(true);
    container->SetAccessibilityLevel("page");
    rootNode_ = container;
    nodes_.push_back(rootNode_);

    // 2. Create news list
    newsList_ = new AccessibleObject("newsList");
    newsList_->SetElementId(AllocateElementId());
    newsList_->SetName("新闻列表");
    newsList_->SetComponentType("list");
    newsList_->SetAccessibilityText("包含20条新闻的列表");
    newsList_->SetScrollable(true);
    newsList_->SetClickable(true);
    newsList_->SetFocusable(true);
    newsList_->SetParent(rootNode_);
    nodes_.push_back(newsList_);

    // 3. Create news items (20 items)
    for (int i = VALUE_ZERO; i < NEWS_ITEM_COUNT; i++) {
        auto* newsItem = new AccessibleObject("newsItem_" + std::to_string(i));
        newsItem->SetElementId(AllocateElementId());
        newsItem->SetName("新闻" + std::to_string(i + 1));
        newsItem->SetComponentType("listitem");
        newsItem->SetAccessibilityText("新闻标题 " + std::to_string(i + 1));
        newsItem->SetClickable(true);
        newsItem->SetFocusable(true);
        newsItem->SetIsSelected(i == currentItemIndex_);

        // Set grid item info
        ArkUI_AccessibleGridItemInfo gridItemInfo;
        gridItemInfo.rowIndex = i;
        gridItemInfo.columnIndex = VALUE_ZERO;
        gridItemInfo.rowSpan = VALUE_ONE;
        gridItemInfo.columnSpan = VALUE_ONE;
        gridItemInfo.heading = (i == VALUE_ZERO);  // First item as heading
        gridItemInfo.selected = (i == currentItemIndex_);
        newsItem->SetGridItemInfo(gridItemInfo);

        newsItem->SetParent(rootNode_);
        newsItems_.push_back(newsItem);
        nodes_.push_back(newsItem);
    }

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario3",
        "Created %{public}zu nodes for news list", nodes_.size());
}

/**
 * @brief Configures the initial state of nodes
 */
void Scenario3NewsList::ConfigureNodes()
{
    // Configure initial state
    UpdateSelectionState();

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario3",
        "Configured news list nodes");
}

/**
 * @brief Gets all nodes in this scenario
 * @return Vector of pointers to all nodes
 */
const std::vector<AccessibleObject*>& Scenario3NewsList::GetNodes() const
{
    return nodes_;
}

/**
 * @brief Gets the root node of this scenario
 * @return Pointer to the root node
 */
AccessibleObject* Scenario3NewsList::GetRootNode() const
{
    return rootNode_;
}

/**
 * @brief Finds a node by its element ID
 * @param elementId The element ID to search for
 * @return Pointer to the node if found, nullptr otherwise
 */
AccessibleObject* Scenario3NewsList::GetNodeById(int64_t elementId)
{
    if (elementId <= VALUE_ZERO || elementId > static_cast<int64_t>(nodes_.size())) {
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
bool Scenario3NewsList::HandleAction(int64_t elementId,
    ArkUI_Accessibility_ActionType action)
{
    auto* node = GetNodeById(elementId);
    if (!node) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Scenario3",
            "Node not found: elementId=%{public}lld", elementId);
        return false;
    }

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario3",
        "HandleAction: elementId=%{public}lld, action=%{public}d",
        elementId, action);

    switch (action) {
        case ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_CLICK:
            // Handle news item click
            if (elementId > NEWS_ITEM_OFFSET) {  // News items start from elementId=3
                int itemIndex = static_cast<int>(elementId - NEWS_ITEM_OFFSET);
                currentItemIndex_ = itemIndex;

                // Update selection state
                for (size_t i = VALUE_ZERO; i < newsItems_.size(); i++) {
                    newsItems_[i]->SetIsSelected(false);
                    // Update grid item info
                    ArkUI_AccessibleGridItemInfo gridItemInfo;
                    gridItemInfo.rowIndex = i;
                    gridItemInfo.columnIndex = VALUE_ZERO;
                    gridItemInfo.rowSpan = VALUE_ONE;
                    gridItemInfo.columnSpan = VALUE_ONE;
                    gridItemInfo.heading = (i == VALUE_ZERO);
                    gridItemInfo.selected = (i == currentItemIndex_);
                    newsItems_[i]->SetGridItemInfo(gridItemInfo);
                }

                newsItems_[itemIndex]->SetIsSelected(true);
                UpdateSelectionState();

                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario3",
                    "News item %{public}d clicked", itemIndex + 1);
                return true;
            }
            break;

        case ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_SCROLL_FORWARD:
            // Scroll forward (show next page)
            if (endItemIndex_ < NEWS_ITEM_COUNT - 1) {
                startItemIndex_ = endItemIndex_ + 1;
                endItemIndex_ = std::min(startItemIndex_ + PAGE_SIZE, NEWS_ITEM_COUNT - 1);
                UpdateSelectionState();
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario3",
                    "Scrolled forward: start=%{public}d, end=%{public}d",
                    startItemIndex_, endItemIndex_);
                return true;
            }
            break;

        case ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_SCROLL_BACKWARD:
            // Scroll backward (show previous page)
            if (startItemIndex_ > VALUE_ZERO) {
                endItemIndex_ = startItemIndex_ - 1;
                startItemIndex_ = std::max(VALUE_ZERO, endItemIndex_ - PAGE_SIZE);
                UpdateSelectionState();
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario3",
                    "Scrolled backward: start=%{public}d, end=%{public}d",
                    startItemIndex_, endItemIndex_);
                return true;
            }
            break;

        default:
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario3",
                "Unhandled action: %{public}d", action);
            break;
    }

    return false;
}

/**
 * @brief Cleans up all resources used by this scenario
 */
void Scenario3NewsList::Cleanup()
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Scenario3",
        "Cleaning up %{public}zu nodes", nodes_.size());

    if (auto* customWidget = dynamic_cast<FakeCustomWidget*>(rootNode_)) {
        customWidget->Cleanup();
    }

    nodes_.clear();
    newsItems_.clear();
    rootNode_ = nullptr;
    newsList_ = nullptr;
}

} // namespace NativeXComponentSample
