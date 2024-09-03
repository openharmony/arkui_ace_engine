/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_NATIVE_INTERFACE_ACCESSIBILITY_IMPL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_NATIVE_INTERFACE_ACCESSIBILITY_IMPL_H

#include <map>
#include <mutex>
#include <string>
#include <unordered_set>
#include <vector>

#include "interfaces/native/native_interface_accessibility.h"

#include "base/utils/singleton.h"

struct ArkUI_AccessibilityElementInfo {
    explicit ArkUI_AccessibilityElementInfo();
    void SetPageId(int32_t pageId)
    {
        this->pageId = pageId;
    }

    int32_t GetPageId() const
    {
        return pageId;
    }

    void SetParentId(int64_t parentId)
    {
        this->parentId = parentId;
    }

    int64_t GetParentId() const
    {
        return parentId;
    }

    int32_t GetElementId() const
    {
        return elementId;
    }

    void SetElementId(int64_t elementId)
    {
        this->elementId = elementId;
    }

    void SetTextBeginSelected(int32_t textBeginSelected)
    {
        this->textBeginSelected = textBeginSelected;
    }

    int32_t GetTextBeginSelected() const
    {
        return textBeginSelected;
    }

    void SetTextEndSelected(int32_t textEndSelected)
    {
        this->textEndSelected = textEndSelected;
    }

    int32_t GetTextEndSelected() const
    {
        return textEndSelected;
    }

    void SetCurrentIndex(int32_t currentIndex)
    {
        this->currentIndex = currentIndex;
    }

    int32_t GetCurrentIndex() const
    {
        return currentIndex;
    }

    void SetBeginIndex(int32_t beginIndex)
    {
        this->beginIndex = beginIndex;
    }

    int32_t GetBeginIndex() const
    {
        return beginIndex;
    }

    void SetEndIndex(int32_t endIndex)
    {
        this->endIndex = endIndex;
    }

    int32_t GetEndIndex() const
    {
        return endIndex;
    }

    void SetItemCount(int32_t itemCount)
    {
        this->itemCount = itemCount;
    }

    int32_t GetItemCount() const
    {
        return itemCount;
    }

    void SetOffset(int32_t offset)
    {
        this->offset = offset;
    }

    int32_t GetOffset() const
    {
        return offset;
    }

    void SetZIndex(int32_t zIndex)
    {
        this->zIndex = zIndex;
    }

    int32_t GetZIndex() const
    {
        return zIndex;
    }

    void SetOpacity(float opacity)
    {
        this->opacity = opacity;
    }

    float GetOpacity() const
    {
        return opacity;
    }

    void SetCheckable(bool checkable)
    {
        this->checkable = checkable;
    }

    bool IsCheckable() const
    {
        return checkable;
    }

    void SetChecked(bool checked)
    {
        this->checked = checked;
    }

    bool IsChecked() const
    {
        return checked;
    }

    void SetFocusable(bool focusable)
    {
        this->focusable = focusable;
    }

    bool IsFocusable() const
    {
        return focusable;
    }

    void SetFocused(bool focused)
    {
        this->focused = focused;
    }

    bool IsFocused() const
    {
        return focused;
    }

    void SetVisible(bool visible)
    {
        this->visible = visible;
    }

    bool IsVisible() const
    {
        return visible;
    }

    void SetAccessibilityFocused(bool accessibilityFocused)
    {
        this->accessibilityFocused = accessibilityFocused;
    }

    bool IsAccessibilityFocused() const
    {
        return accessibilityFocused;
    }

    void SetSelected(bool selected)
    {
        this->selected = selected;
    }

    bool IsSelected() const
    {
        return selected;
    }

    void SetClickable(bool clickable)
    {
        this->clickable = clickable;
    }

    bool IsClickable() const
    {
        return clickable;
    }

    void SetLongClickable(bool longClickable)
    {
        this->longClickable = longClickable;
    }

    bool IsLongClickable() const
    {
        return longClickable;
    }

    void SetEnabled(bool enabled)
    {
        this->enabled = enabled;
    }

    bool IsEnabled() const
    {
        return enabled;
    }

    void SetPassword(bool isPassword)
    {
        this->password = isPassword;
    }

    bool IsPassword() const
    {
        return password;
    }

    void SetScrollable(bool scrollable)
    {
        this->scrollable = scrollable;
    }

    bool IsScrollable() const
    {
        return scrollable;
    }

    void SetEditable(bool editable)
    {
        this->editable = editable;
    }

    bool IsEditable() const
    {
        return editable;
    }

    void SetHint(bool hint)
    {
        this->hint = hint;
    }

    bool IsHint() const
    {
        return hint;
    }

    void SetAccessibilityGroup(bool accessibilityGroup)
    {
        this->accessibilityGroup = accessibilityGroup;
    }

    bool GetAccessibilityGroup() const
    {
        return accessibilityGroup;
    }

    void SetRect(const ArkUI_AccessibleRect& rect);
    ArkUI_AccessibleRect GetScreenRect() const
    {
        return screenRect;
    }

    void SetRangeInfo(const ArkUI_AccessibleRangeInfo& rangeInfo);
    ArkUI_AccessibleRangeInfo GetRangeInfo() const
    {
        return rangeInfo;
    }

    void SetGridInfo(const ArkUI_AccessibleGridInfo& gridInfo);
    ArkUI_AccessibleGridInfo GetGridInfo() const
    {
        return grid;
    }

    void SetGridItemInfo(const ArkUI_AccessibleGridItemInfo& gridItemInfo);
    ArkUI_AccessibleGridItemInfo GetGridItemInfo() const
    {
        return gridItem;
    }

    void ClearChildNodeIds();
    void AddChildNodeId(int64_t childNodeId);
    const std::vector<int64_t>& GetChildNodeIds() const
    {
        return childNodeIds;
    }

    void ClearOperationActions();
    void AddOperationAction(const ArkUI_AccessibleAction& action);
    const std::vector<ArkUI_AccessibleAction>& GetOperationActions() const
    {
        return operationActions;
    }

    void SetComponentType(const std::string& componentType)
    {
        this->componentType = componentType;
    }

    std::string GetComponentType() const
    {
        return componentType;
    }

    void SetContents(const std::string& contents)
    {
        this->contents = contents;
    }

    std::string GetContents() const
    {
        return contents;
    }

    void SetHintText(const std::string& hintText)
    {
        this->hintText = hintText;
    }

    std::string GetHintText() const
    {
        return hintText;
    }

    void SetAccessibilityText(const std::string& accessibilityText)
    {
        this->accessibilityText = accessibilityText;
    }

    std::string GetAccessibilityText() const
    {
        return accessibilityText;
    }

    void SetAccessibilityDescription(const std::string& accessibilityDescription)
    {
        this->accessibilityDescription = accessibilityDescription;
    }

    std::string GetAccessibilityDescription() const
    {
        return accessibilityDescription;
    }

    void SetAccessibilityLevel(const std::string& accessibilityLevel)
    {
        this->accessibilityLevel = accessibilityLevel;
    }

    std::string GetAccessibilityLevel() const
    {
        return accessibilityLevel;
    }

    void SetBackgroundColor(const std::string& backgroundColor)
    {
        this->backgroundColor = backgroundColor;
    }

    std::string GetBackgroundColor() const
    {
        return backgroundColor;
    }

    void SetBackgroundImage(const std::string& backgroundImage)
    {
        this->backgroundImage = backgroundImage;
    }

    std::string GetBackgroundImage() const
    {
        return backgroundImage;
    }

    void SetBlur(const std::string& blur)
    {
        this->blur = blur;
    }

    std::string GetBlur() const
    {
        return blur;
    }

    void SetHitTestBehavior(const std::string& hitTestBehavior)
    {
        this->hitTestBehavior = hitTestBehavior;
    }

    std::string GetHitTestBehavior() const
    {
        return hitTestBehavior;
    }

private:
    int32_t pageId = 0;
    int32_t textBeginSelected = 0;
    int32_t textEndSelected = 0;
    int32_t currentIndex = 0;
    int32_t beginIndex = 0;
    int32_t endIndex = 0;
    int32_t itemCount = 0;
    int32_t offset = 0;
    int32_t zIndex = 0;
    float opacity = 0.0f;

    int64_t parentId = 0;
    int32_t elementId = 0;

    bool checkable = false;
    bool checked = false;
    bool focusable = false;
    bool focused = false;
    bool visible = false;
    bool accessibilityFocused = false;
    bool selected = false;
    bool clickable = false;
    bool longClickable = false;
    bool enabled = false;
    bool password = false;
    bool scrollable = false;
    bool editable = false;
    bool hint = false;
    bool accessibilityGroup = false;

    ArkUI_AccessibleRect screenRect;
    ArkUI_AccessibleRangeInfo rangeInfo;
    ArkUI_AccessibleGridInfo grid;
    ArkUI_AccessibleGridItemInfo gridItem;

    std::vector<int64_t> childNodeIds;
    std::vector<ArkUI_AccessibleAction> operationActions;

    std::string componentType;
    std::string contents;
    std::string hintText;
    std::string accessibilityText;
    std::string accessibilityDescription;

    std::string accessibilityLevel;
    std::string backgroundColor;
    std::string backgroundImage;
    std::string blur;
    std::string hitTestBehavior;
};

struct ArkUI_AccessibilityEventInfo {
public:
    ArkUI_AccessibilityEventInfo() = default;

    ArkUI_AccessibilityEventType GetEventType() const
    {
        return eventType;
    }

    void SetEventType(ArkUI_AccessibilityEventType eventType_)
    {
        eventType = eventType_;
    }

    int32_t GetPageId() const
    {
        return pageId;
    }

    void SetPageId(int32_t pageId)
    {
        this->pageId = pageId;
    }

    int32_t GetRequestFocusId() const
    {
        return requestFocusId;
    }

    void SetRequestFocusId(int32_t requestFocusId)
    {
        this->requestFocusId = requestFocusId;
    }

    ArkUI_AccessibilityElementInfo* GetElementInfo() const
    {
        return elementInfo;
    }

    void SetElementInfo(ArkUI_AccessibilityElementInfo* elementInfo)
    {
        this->elementInfo = elementInfo;
    }

    std::string GetTextAnnouncedForAccessibility() const
    {
        return textAnnouncedForAccessibility;
    }

    void SetTextAnnouncedForAccessibility(const std::string& textAnnouncedForAccessibility)
    {
        this->textAnnouncedForAccessibility = textAnnouncedForAccessibility;
    }

private:
    ArkUI_AccessibilityEventType eventType = ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_INVALID;
    int32_t pageId = 0;
    int32_t requestFocusId = 0;
    ArkUI_AccessibilityElementInfo* elementInfo = nullptr;
    std::string textAnnouncedForAccessibility;
};

// suport multithreads
struct ArkUI_AccessibilityElementInfoList {
public:
    ArkUI_AccessibilityElementInfoList() = default;
    ArkUI_AccessibilityElementInfo* AddAndGetElementInfo();
    bool CopyAccessibilityElementInfo(std::vector<ArkUI_AccessibilityElementInfo>& infos);

private:
    std::mutex mutex_;
    std::vector<ArkUI_AccessibilityElementInfo> elementInfos_;
};

struct ArkUI_AccessibilityActionArguments {
public:
    ArkUI_AccessibilityActionArguments(std::map<std::string, std::string> actionArguments)
    {
        actionArguments_.swap(actionArguments);
    }
    const char* FindValueByKey(const char* key);

private:
    std::map<std::string, std::string> actionArguments_;
};

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_NATIVE_INTERFACE_ACCESSIBILITY_IMPL_H