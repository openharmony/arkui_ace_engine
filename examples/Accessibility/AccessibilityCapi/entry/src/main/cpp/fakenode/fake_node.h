/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ACCESSIBILITY_CAPI_FAKE_NODE_H
#define ACCESSIBILITY_CAPI_FAKE_NODE_H
#include <arkui/native_interface_accessibility.h>
#include <hilog/log.h>
#include <cassert>
#include "common/common.h"
#include <string>
namespace NativeXComponentSample {
class AccessibleObject {
public:
    // Constructor to initialize the name of the node.
    explicit AccessibleObject(const std::string &name) : name_(name), originName_(name), elementId_(-1) {}

    // 获取和设置元素ID
    int64_t GetElementId() const
    {
        return elementId_;
    }
    void SetElementId(int64_t id)
    {
        elementId_ = id;
    }

    // 获取和设置父节点
    AccessibleObject* GetParent() const
    {
        return parent_;
    }
    void SetParent(AccessibleObject* parent)
    {
        parent_ = parent;
    }
// 设置string和int类型属性
    void SetAccessibilityLevel(const std::string &accessibilityLevel)
    {
        accessibilityLevel_ = accessibilityLevel;
    }

    void SetComponentType(const std::string &type)
    {
        componentType_ = type;
    }

    std::string GetComponentType() const
    {
        return componentType_;
    }
    void SetAccessibilityText(const std::string &accessibilityText)
    {
        accessibilityText_ = accessibilityText;
    }
    void SetAccessibilityDescription(const std::string &accessibilityDescription)
    {
        accessibilityDescription_ = accessibilityDescription;
    }
    void SetAnnouncedForAccessibility(const std::string &announcedForAccessibility)
    {
        announcedForAccessibility_ = announcedForAccessibility;
    }
    const std::string GetAnnouncedForAccessibility()
    {
        return announcedForAccessibility_;
    }
    void SetName(const std::string &name)
    {
        name_ = name;
    }
    std::string Name() const
    {
        return name_;
    }
    std::string OriginName() const
    {
        return originName_;
    }

    void SetBackgroundColor(const std::string &color)
    {
        backgroundColor_ = color;
    }
    void SetBackgroundImage(const std::string &image)
    {
        backgroundImage_ = image;
    }
    void SetBlue(const std::string &blue)
    {
        blue_ = blue;
    }
    void SetHitTestBehavior(const std::string &hitTestBehavior)
    {
        hitTestBehavior_ = hitTestBehavior;
    }
    void SetSelectedText(int32_t textStart, int32_t textEnd)
    {
        selectedTextStart_ = textStart;
        selectedTextEnd_ = textEnd;
    }
    void SetSelectedItem(int32_t itemCount, int32_t itemStart, int32_t itemCurrent, int32_t itemEnd)
    {
        itemCount_ = itemCount;
        startItemIndex_ = itemStart;
        endItemIndex_ = itemEnd;
        currentItemIndex_ = itemCurrent;
    }
    void SetOffset(int32_t offset)
    {
        offset_ = offset;
    }
    void SetRangeInfo(ArkUI_AccessibleRangeInfo rangeInfo)
    {
        rangeInfo_ = rangeInfo;
    }
    ArkUI_AccessibleRangeInfo GetRangeInfo()
    {
        return rangeInfo_;
    }
    ArkUI_AccessibleGridInfo GetGridInfo()
    {
        return gridInfo_;
    }
    ArkUI_AccessibleGridItemInfo GetGridItemInfo()
    {
        return gridItemInfo_;
    }
    void SetGridInfo(ArkUI_AccessibleGridInfo gridInfo)
    {
        gridInfo_ = gridInfo;
    }
    void SetGridItemInfo(ArkUI_AccessibleGridItemInfo gridItemInfo)
    {
        gridItemInfo_ = gridItemInfo;
    }
    void SetFocus(bool focus)
    {
        focus_ = focus;
    }
    virtual void SetFocusable(bool focusable)
    {
        focusable_ = focusable;
    }
    virtual void SetClickable(bool clickable)
    {
        clickable_ = clickable;
    }
    void SetChecked(bool checked)
    {
        checked_ = checked;
    }
    void SetCheckable(bool checkable)
    {
        checkable_ = checkable;
    }
    void SetIsPassword(bool isPassword)
    {
        isPassword_ = isPassword;
    }
    void SetEditable(bool editable)
    {
        editable_ = editable;
    }
    void SetScrollable(bool isScrollable)
    {
        isScrollable_ = isScrollable;
    }
    void SetLongClickable(bool isLongClick)
    {
        isLongClick_ = isLongClick;
    }
    void SetIsGroup(bool isGroup)
    {
        isGroup_ = isGroup;
    }
    void SetAccessibilityGroup(bool isGroup)
    {
        isGroup_ = isGroup;
    }
    void SetIsSelected(bool isSelected)
    {
        isSelected_ = isSelected;
    }
    void SetSelected(bool isSelected)
    {
        isSelected_ = isSelected;
    }
    void SetIsVisible(bool isVisible)
    {
        isVisible_ = isVisible;
    }
    void SetIsEnable(bool isEnable)
    {
        isEnable_ = isEnable;
    }
    void SetHintText(const std::string &hintText)
    {
        hintText_ = hintText;
    }
    void SetCurrentItemIndex(int32_t currentIndex)
    {
        currentItemIndex_ = currentIndex;
    }
    void SetStartItemIndex(int32_t startIndex)
    {
        startItemIndex_ = startIndex;
    }
    void SetEndItemIndex(int32_t endIndex)
    {
        endItemIndex_ = endIndex;
    }
    void SetItemCount(int32_t count)
    {
        itemCount_ = count;
    }
    
    virtual bool Focused() const
    {
        return focus_;
    }
    virtual bool Focusable() const
    {
        return focusable_;
    }
    virtual const char *ObjectType() const
    {
        return "object";
    }
    virtual const char *Hint() const
    {
        return "It's object";
    }
    virtual void OnClick()
    {
    }
    bool Clickable() const
    {
        return clickable_;
    }
    bool IsVisible() const
    {
        return isVisible_;
    }
    bool IsEnable() const
    {
        return isEnable_;
    }
    void fillAccessibilityElement(ArkUI_AccessibilityElementInfo *element);

protected:
    int64_t elementId_;
    AccessibleObject* parent_ = nullptr;

private:
    std::string componentType_ = "object";
    std::string accessibilityLevel_ = "auto";
    std::string accessibilityText_;
    std::string accessibilityDescription_;
    std::string announcedForAccessibility_;
    std::string name_;
    std::string originName_;
    std::string backgroundColor_;
    std::string backgroundImage_;
    std::string blue_;
    std::string hitTestBehavior_;
    std::string hintText_;
    
    bool clickable_ = true;
    bool focus_ = false;
    bool focusable_ = true;
    bool checked_ = false;
    bool checkable_ = false;
    bool isPassword_ = false;
    bool editable_ = true;
    bool isScrollable_ = false;
    bool isLongClick_ = false;
    bool isSelected_ = false;
    bool isGroup_ = false;
    bool isVisible_ = true;
    bool isEnable_ = true;
    
    int32_t selectedTextStart_ = 0;
    int32_t selectedTextEnd_ = 0;
    int32_t currentItemIndex_ = 0;
    int32_t startItemIndex_ = 0;
    int32_t endItemIndex_ = 0;
    int32_t itemCount_ = 0;
    int32_t zIndex_ = 0;
    int32_t offset_ = 0;
    float opacity_ = 0.0f;
    
    ArkUI_AccessibleRangeInfo rangeInfo_;
    ArkUI_AccessibleGridInfo gridInfo_;
    ArkUI_AccessibleGridItemInfo gridItemInfo_;
};

class FakeButton : public AccessibleObject {
    // The FakeButton class represents a button node in the accessibility tree.
    // It inherits from AccessibleObject and overrides the Hint, ObjectType,
    // and OnClick methods to provide specific behavior for button nodes.
public:
    explicit FakeButton(const std::string &name) : AccessibleObject(name) {}
    char *Hint() const override
    {
        return "It's a button";
    }
    char *ObjectType() const override
    {
        return "FakeButton";
    }
    void OnClick() override
    {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "AccessibleObject", "FakeButton OnClick");
    }
};

class FakeText : public AccessibleObject {
    // The FakeText class represents a text node in the accessibility tree.
    // It inherits from AccessibleObject and overrides the Hint, ObjectType,
    // and OnClick methods to provide specific behavior for text nodes.
public:
    explicit FakeText(const std::string &name) : AccessibleObject(name) {}

    char *Hint() const override
    {
        return "It's a text";
    }
    char *ObjectType() const override
    {
        return "FakeText";
    }
    void OnClick() override
    {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "AccessibleObject", "FakeText OnClick");
    }
};

class FakeSlider : public AccessibleObject {
    // The FakeSlider class represents a slider node in the accessibility tree.
    // It inherits from AccessibleObject and overrides the Hint, ObjectType,
    // and OnClick methods to provide specific behavior for slider nodes.
public:
    explicit FakeSlider(const std::string &name) : AccessibleObject(name) {}

    char *Hint() const override
    {
        return "It's a slider";
    }
    char *ObjectType() const override
    {
        return "FakeSlider";
    }
    void OnClick() override
    {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "AccessibleObject", "FakeSlider OnClick");
    }
};

class FakeList : public AccessibleObject {
    // The FakeList class represents a list node in the accessibility tree.
    // It inherits from AccessibleObject and overrides the Hint, ObjectType,
    // and OnClick methods to provide specific behavior for list nodes.
public:
    explicit FakeList(const std::string &name) : AccessibleObject(name) {}

    char *Hint() const override
    {
        return "It's a list";
    }
    char *ObjectType() const override
    {
        return "FakeList";
    }
    void OnClick() override
    {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "AccessibleObject", "FakeList OnClick");
    }
};

class FakeSwiper : public AccessibleObject {
    // The FakeSwiper class represents a swiper node in the accessibility tree.
    // It inherits from AccessibleObject and overrides the Hint, ObjectType,
    // and OnClick methods to provide specific behavior for swiper nodes.
public:
    explicit FakeSwiper(const std::string &name) : AccessibleObject(name) {}

    char *Hint() const override
    {
        return "It's a swiper";
    }
    char *ObjectType() const override
    {
        return "FakeSwiper";
    }
    void OnClick() override
    {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "AccessibleObject", "FakeSwiper OnClick");
    }
};

class FakeWidget : public AccessibleObject {
    // The FakeWidget class represents a widget node in the accessibility tree.
    // It inherits from AccessibleObject and contains a collection of child nodes,
    // including buttons, text, sliders, lists, and swipers. It provides methods
    // to add these child nodes and retrieve them based on their element ID.
public:
    // Singleton pattern to ensure only one instance of FakeWidget exists.
    static FakeWidget &Instance()
    {
        static FakeWidget w;
        return w;
    }

    const std::vector<AccessibleObject *> &GetAllObjects(std::string instanceId) const
    {
        for (int i = 0; i < objects.size(); i++) {
            objects[i]->SetName(objects[i]->OriginName() + instanceId);
        }
        return objects;
    }

    AccessibleObject *GetChild(int elementId) const
    {
        if (elementId <= 0) {
            return nullptr;
        }
        if (elementId - 1 >= objects.size()) {
            return nullptr;
        }
        return objects.at(elementId - 1);
    }

    bool Focusable() const override
    {
        return false;
    }
    char *Hint() const override
    {
        return "It's a widget";
    }
    char *ObjectType() const override
    {
        return "Widget";
    }
    void OnClick() override
    {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "AccessibleObject", "FakeWidget OnClick");
    }

private:
    FakeWidget() : AccessibleObject("fakeWidget")
    {
        this->AddButton(true, false);
        this->AddButton(true, true);
        this->AddButton(false, false);
        this->AddButton(false, true);
        this->AddText(true, false);
        this->AddText(true, true);
        this->AddText(false, false);
        this->AddText(false, true);
        this->AddSlider(true, true);
        this->AddList(true, true);
        this->AddSwiper(true, true);
    }
    ~FakeWidget()
    {
        for (auto &obj : objects) {
            delete obj;
        }
    }

private:
    void AddButton(const bool fillText, const bool fillDescription);
    void AddText(const bool fillText, const bool fillDescription);
    void AddSlider(const bool fillText, const bool fillDescription);
    void AddList(const bool fillText, const bool fillDescription);
    void AddSwiper(const bool fillText, const bool fillDescription);

private:
    std::vector<AccessibleObject *> objects;
};
}
#endif //ACCESSIBILITY_CAPI_FAKE_NODE_H
