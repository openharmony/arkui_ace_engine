/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License")
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

#include <arkui/native_interface.h>
#include <arkui/styled_string.h>
#include <arkui/native_node.h>
#include <AbilityKit/ability_base/want.h>
#include <hilog/log.h>
#include "AccessibilityMaker.h"
#include <arkui/native_interface_accessibility.h>
#include <ace/xcomponent/native_interface_xcomponent.h>
#include <arkui/native_dialog.h>
#include <string>
#include "AccessibilityDialog.h"

const char *DEFAULT_ID = "CustomId";
constexpr float COL_WIDTH_PX = 300.0f;
constexpr float TEXT_WIDTH_PX = 300.0f;
constexpr float TEXT_HEIGHT_PX = 100.0f;
constexpr float TEXT_RIGHT_BOTTOM_PX = 500.0f;
constexpr float RECT_RIGHT_BOTTOM_PX = 800.0f;
constexpr int32_t ITEM_VALUE = 720;
constexpr const char* SAMPLE_TEXT = "Hello Accessibility Sample";
static ArkUI_AccessibilityState* accessibilityState_;
static ArkUI_AccessibilityProvider* accessibilityProvider_ = nullptr;
ArkUI_AccessibilityProviderCallbacksWithInstance AccessibilityMaker::accessibilityProviderCallbacksWithInstance_;
static ArkUI_CustomDialogOptions* options;

class AccessibleObject {
public:
    explicit AccessibleObject(const std::string &name) : name_(name), originName_(name) {}
    void SetFocus(bool focus) { focus_ = focus; }
    void SetName(const std::string &name) {name_ = name;}
    bool Focused() const { return focus_; }
    virtual bool Focusable() const { return true; }
    std::string Name() const { return name_; }
    std::string OriginName() const { return originName_; }

    virtual const char *ObjectType() const { return "object"; }
    virtual const char *Hint() const { return "It's object"; }
    virtual void OnClick() {}
    virtual bool Clickable() const { return false; }

    void fillAccessibilityElement(ArkUI_AccessibilityElementInfo *element)
    {
        OH_ArkUI_AccessibilityElementInfoSetComponentType(element, ObjectType());
        OH_ArkUI_AccessibilityElementInfoSetContents(element, Name().data());
        OH_ArkUI_AccessibilityElementInfoSetHintText(element, Hint());
        OH_ArkUI_AccessibilityElementInfoSetVisible(element, true);
        OH_ArkUI_AccessibilityElementInfoSetEnabled(element, true);
        OH_ArkUI_AccessibilityElementInfoSetClickable(element, Clickable());
        OH_ArkUI_AccessibilityElementInfoSetFocusable(element, Focusable());
        OH_ArkUI_AccessibilityElementInfoSetFocused(element, Focused());
        OH_ArkUI_AccessibilityElementInfoSetAccessibilityLevel(element, "yes");

        ArkUI_AccessibleAction actions[10];
        int index = 0;
        if (this->Clickable()) {
            actions[index].actionType = ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_CLICK;
            actions[index].description = "Click";
            index++;
        }

        if (this->Focusable()) {
            actions[index].actionType = ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_GAIN_ACCESSIBILITY_FOCUS;
            actions[index].description = "Focus";
            index++;
            actions[index].actionType = ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_CLEAR_ACCESSIBILITY_FOCUS;
            actions[index].description = "ClearFocus";
            index++;
        }
        if (index > 0) {
            OH_ArkUI_AccessibilityElementInfoSetOperationActions(element, index, actions);
        }
    }

private:
    bool focus_ = false;
    std::string name_;
    std::string originName_;
};

class FakeButton : public AccessibleObject {
public:
    explicit FakeButton(const std::string &name) : AccessibleObject(name) {}
    const char *Hint() const override { return "It's a button"; }
    const char *ObjectType() const override  { return "QButton"; }
    void OnClick() override
    {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "AccessibleObject", "FakeButton onClick");
    }
    bool Clickable() const override {return true;}
};

class FakeText : public AccessibleObject {
public:
    explicit FakeText(const std::string &name) : AccessibleObject(name) {}
    const char *Hint() const override { return "It's a text"; }
    const char *ObjectType() const override { return "QText"; }
    void OnClick() override
    {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "AccessibleObject", "FakeText onClick");
    }
    bool Clickable() const override { return false; }
};

class FakeWidget : public AccessibleObject {
public:
    static FakeWidget &Instance()
    {
        static FakeWidget w;
        return w;
    }

    const std::vector<AccessibleObject *> &getAllObjects(std::string instanceId) const
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

    bool Focusable() const override { return false; }
    const char *Hint() const override { return "It's a widget"; }
    const char *ObjectType() const override { return "QWidget"; }
    void OnClick() override
    {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "AccessibleObject", "FakeWidget onClick");
    }

private:
    FakeWidget() : AccessibleObject("fakeWidget")
    {
        this->AddButton();
        this->AddButton();
        this->AddButton();
        this->AddText();
        this->AddText();
        this->AddText();
    }
    ~FakeWidget()
    {
        for (auto &obj : objects) {
            delete obj;
        }
    }

private:
    void AddButton()
    {
        static int i = 1;
        objects.push_back(new FakeButton("button" + std::to_string(i)));
        i++;
    }
    void AddText()
    {
        static int i = 1;
        objects.push_back(new FakeText("text" + std::to_string(i)));
        i++;
    }

private:
    std::vector<AccessibleObject *> objects;
};

namespace {
void FillEvent(ArkUI_AccessibilityEventInfo *eventInfo, ArkUI_AccessibilityElementInfo *elementInfo,
               ArkUI_AccessibilityEventType eventType)
{
    if (eventInfo == nullptr) {
        return;
    }
    if (elementInfo == nullptr) {
        return;
    }
    OH_ArkUI_AccessibilityEventSetEventType(eventInfo, eventType);

    OH_ArkUI_AccessibilityEventSetElementInfo(eventInfo, elementInfo);
}
ArkUI_AccessibilityProvider *g_provider = nullptr;
}

void AccessibilityMaker::CreateAccessibilityProviderSection_multiple(ArkUI_NativeNodeAPI_1* nodeApi,
                                                                     ArkUI_NodeHandle parent)
{
    // 创建一个不被无障碍焦点识别的标题文本
    ArkUI_NodeHandle text1 = BuildTextNodeWithoutAccessibilityFocus(nodeApi,
        "通过 OH_ArkUI_AccessibilityProviderRegisterCallbackWithInstance 设置自定义绘制:");
    nodeApi->addChild(parent, text1);
    auto customNode1 = nodeApi->createNode(ARKUI_NODE_CUSTOM);
    auto customNode2 = nodeApi->createNode(ARKUI_NODE_CUSTOM);
    auto column =  nodeApi->createNode(ARKUI_NODE_COLUMN);

    ArkUI_NumberValue NODE_WIDTH_value[] = {200};
    ArkUI_AttributeItem NODE_WIDTH_Item[] = { NODE_WIDTH_value, 1 };
    ArkUI_NumberValue NODE_HEIGHT_value[] = {200};
    ArkUI_AttributeItem NODE_HEIGHT_Item[] = { NODE_HEIGHT_value, 1 };
    
    nodeApi->setAttribute(customNode1, NODE_WIDTH, NODE_WIDTH_Item);
    nodeApi->setAttribute(customNode1, NODE_HEIGHT, NODE_HEIGHT_Item);
    nodeApi->setAttribute(customNode2, NODE_WIDTH, NODE_WIDTH_Item);
    nodeApi->setAttribute(customNode2, NODE_HEIGHT, NODE_HEIGHT_Item);

    // 确保 accessibility 状态为启用，并打印当前状态
    SetAccessibilityDisabled(false);
    bool disabled = IsAccessibilityDisabled();
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityMaker",
        "1 IsAccessibilityDisabled: disabled=%{public}d", disabled);

    const char* instanceId1 = "CustomNode1";
    const char* instanceId2 = "CustomNode2";
    // 为两个自定义节点注册 accessibility provider（instanceId 用于区分多个实例）
    GetAccessibilityProvider(&customNode1, instanceId1);
    GetAccessibilityProvider(&customNode2, instanceId2);

    // 将自定义节点及说明文本添加到父节点中
    ArkUI_AttributeItem accessibilityItem = { .object = accessibilityProvider_ };
    accessibilityItem = { .object = accessibilityProvider_ };
    ArkUI_NodeHandle text2 = BuildTextNode(nodeApi, SAMPLE_TEXT);
    GetUniqueId(nodeApi, text2);
    nodeApi->addChild(parent, customNode1);
    nodeApi->addChild(parent, customNode2);
    nodeApi->addChild(parent, text2);
}

void AccessibilityMaker::CreateAccessibilityProviderSection(ArkUI_NativeNodeAPI_1* nodeApi, ArkUI_NodeHandle parent)
{
    // 创建单个自定义节点和其 accessibility provider
    ArkUI_NodeHandle text1 = BuildTextNodeWithoutAccessibilityFocus(nodeApi,
        "通过 OH_ArkUI_AccessibilityProviderRegisterCallbackWithInstance 设置自定义绘制:");
    nodeApi->addChild(parent, text1);
    auto customNode1 = nodeApi->createNode(ARKUI_NODE_CUSTOM);
    auto column =  nodeApi->createNode(ARKUI_NODE_COLUMN);
    
    ArkUI_NumberValue NODE_WIDTH_value[] = {200};
    ArkUI_AttributeItem NODE_WIDTH_Item[] = {NODE_WIDTH_value, 1};
    ArkUI_NumberValue NODE_HEIGHT_value[] = {200};
    ArkUI_AttributeItem NODE_HEIGHT_Item[] = {NODE_HEIGHT_value, 1};
    
    nodeApi->setAttribute(customNode1, NODE_WIDTH, NODE_WIDTH_Item);
    nodeApi->setAttribute(customNode1, NODE_HEIGHT, NODE_HEIGHT_Item);
    
    SetAccessibilityDisabled(false);
    char uniqueNodeId[64] = {0};
    GetAccessibilityProvider(&customNode1, uniqueNodeId);
    ArkUI_AttributeItem accessibilityItem = {.object = accessibilityProvider_};
    accessibilityItem = {.object = accessibilityProvider_};
    ArkUI_NodeHandle text2 = BuildTextNode(nodeApi, SAMPLE_TEXT);
    GetUniqueId(nodeApi, text2);
    nodeApi->addChild(parent, customNode1);
    nodeApi->addChild(parent, text2);
}

void AccessibilityMaker::CreateAccessibilityProviderSection_noCustom(ArkUI_NativeNodeAPI_1* nodeApi,
                                                                     ArkUI_NodeHandle parent)
{
    ArkUI_NodeHandle text1 = BuildTextNodeWithoutAccessibilityFocus(nodeApi,
        "非customNode场景验证:");
    nodeApi->addChild(parent, text1);
    auto customNode1 = nodeApi->createNode(ARKUI_NODE_TEXT);
    auto column =  nodeApi->createNode(ARKUI_NODE_COLUMN);
    
    ArkUI_NumberValue NODE_WIDTH_value[] = {200};
    ArkUI_AttributeItem NODE_WIDTH_Item[] = {NODE_WIDTH_value, 1};
    ArkUI_NumberValue NODE_HEIGHT_value[] = {200};
    ArkUI_AttributeItem NODE_HEIGHT_Item[] = {NODE_HEIGHT_value, 1};
    
    nodeApi->setAttribute(customNode1, NODE_WIDTH, NODE_WIDTH_Item);
    nodeApi->setAttribute(customNode1, NODE_HEIGHT, NODE_HEIGHT_Item);
    
    SetAccessibilityDisabled(false);
    char uniqueNodeId[64] = {0};
    GetAccessibilityProvider(&customNode1, uniqueNodeId);
    ArkUI_AttributeItem accessibilityItem = {.object = accessibilityProvider_};
    accessibilityItem = {.object = accessibilityProvider_};
    ArkUI_NodeHandle text2 = BuildTextNode(nodeApi, SAMPLE_TEXT);
    GetUniqueId(nodeApi, text2);
    nodeApi->addChild(parent, customNode1);
    nodeApi->addChild(parent, text2);
}

ArkUI_NodeHandle AccessibilityMaker::CreateNativeNode()
{
    ArkUI_NativeNodeAPI_1 *nodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1 *>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    if (nodeApi == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityMaker", "nodeApi is null");
        return nullptr;
    }
    // 构建一个列容器并放入 Scroll 节点中，返回 scroll 节点作为根节点
    ArkUI_NodeHandle column = BuildColumnNode(nodeApi);
    auto scrollNode = nodeApi->createNode(ARKUI_NODE_SCROLL);
    nodeApi->addChild(scrollNode, column);

    // 在列中填充 provider
    CreateAccessibilityProviderSection(nodeApi, column);
    return scrollNode;
}

ArkUI_NodeHandle AccessibilityMaker::CreateNativeNode_multiple()
{
    ArkUI_NativeNodeAPI_1 *nodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1 *>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    if (nodeApi == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityMaker", "nodeApi is null");
        return nullptr;
    }
    // 构建列容器并使用多实例 provider
    ArkUI_NodeHandle column = BuildColumnNode(nodeApi);
    auto scrollNode = nodeApi->createNode(ARKUI_NODE_SCROLL);
    nodeApi->addChild(scrollNode, column);
    CreateAccessibilityProviderSection_multiple(nodeApi, column);
    return scrollNode;
}

ArkUI_NodeHandle AccessibilityMaker::CreateNativeNoCustom()
{
    ArkUI_NativeNodeAPI_1 *nodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1 *>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    if (nodeApi == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityMaker", "nodeApi is null");
        return nullptr;
    }
    ArkUI_NodeHandle column = BuildColumnNode(nodeApi);
    auto scrollNode = nodeApi->createNode(ARKUI_NODE_SCROLL);
    nodeApi->addChild(scrollNode, column);
    CreateAccessibilityProviderSection_noCustom(nodeApi, column);
    return scrollNode;
}

ArkUI_NodeHandle AccessibilityMaker::BuildTextNodeWithoutAccessibilityFocus(ArkUI_NativeNodeAPI_1* nodeApi,
    const char* content)
{
    // 创建一个基础文本节点，并将其 accessibility mode 设置为 DISABLED
    ArkUI_NodeHandle text = nodeApi->createNode(ARKUI_NODE_TEXT);
    ArkUI_NumberValue textWidth[] = {{.f32 = TEXT_WIDTH_PX}};
    ArkUI_AttributeItem textWidthItem = { textWidth, sizeof(textWidth) / sizeof(ArkUI_NumberValue) };
    nodeApi->setAttribute(text, NODE_WIDTH, &textWidthItem);
    ArkUI_NumberValue textHeight[] = {{.f32 = TEXT_HEIGHT_PX}};
    ArkUI_AttributeItem textHeightItem = { textHeight, sizeof(textHeight) / sizeof(ArkUI_NumberValue) };
    nodeApi->setAttribute(text, NODE_HEIGHT, &textHeightItem);
    ArkUI_AttributeItem valueItem = {.string = content};
    nodeApi->setAttribute(text, NODE_TEXT_CONTENT, &valueItem);
    // 禁用该文本节点的无障碍识别，作为标题或描述使用
    SetAccessibilityMode(nodeApi, text, ARKUI_ACCESSIBILITY_MODE_DISABLED);
    return text;
}

ArkUI_NodeHandle AccessibilityMaker::BuildTextNode(ArkUI_NativeNodeAPI_1* nodeApi, const char* content)
{
    // 创建一个标准文本节点并设置宽高与文本内容
    ArkUI_NodeHandle text = nodeApi->createNode(ARKUI_NODE_TEXT);
    ArkUI_NumberValue textWidth[] = {{.f32 = TEXT_WIDTH_PX}};
    ArkUI_AttributeItem textWidthItem = { textWidth, sizeof(textWidth) / sizeof(ArkUI_NumberValue) };
    nodeApi->setAttribute(text, NODE_WIDTH, &textWidthItem);
    ArkUI_NumberValue textHeight[] = {{.f32 = TEXT_HEIGHT_PX}};
    ArkUI_AttributeItem textHeightItem = { textHeight, sizeof(textHeight) / sizeof(ArkUI_NumberValue) };
    nodeApi->setAttribute(text, NODE_HEIGHT, &textHeightItem);
    ArkUI_AttributeItem valueItem = {.string = content};
    nodeApi->setAttribute(text, NODE_TEXT_CONTENT, &valueItem);
    return text;
}

ArkUI_NodeHandle AccessibilityMaker::BuildColumnNode(ArkUI_NativeNodeAPI_1* nodeApi)
{
    // 创建 Column 容器，并设置固定宽度
    ArkUI_NodeHandle column = nodeApi->createNode(ARKUI_NODE_COLUMN);
    ArkUI_NumberValue colWidth[] = {{.f32 = COL_WIDTH_PX}};
    ArkUI_AttributeItem widthItem = { colWidth, sizeof(colWidth) / sizeof(ArkUI_NumberValue) };
    nodeApi->setAttribute(column, NODE_WIDTH, &widthItem);
    return column;
}

void AccessibilityMaker::SetAccessibilityDisabled(bool isDisabled)
{
    if (accessibilityState_) {
        OH_ArkUI_AccessibilityState_SetDisabled(accessibilityState_, isDisabled);
    }
}

bool AccessibilityMaker::IsAccessibilityDisabled()
{
    if (accessibilityState_) {
        return OH_ArkUI_AccessibilityState_IsDisabled(accessibilityState_);
    }
    return false;
}

// [Start abilitycap_nine_start]
int32_t AccessibilityMaker::GetAccessibilityProvider(ArkUI_NodeHandle* customNode, const char* id)
{
    AccessibilityMaker::accessibilityProviderCallbacksWithInstance_.findAccessibilityNodeInfosById =
        FindAccessibilityNodeInfosById;
    AccessibilityMaker::accessibilityProviderCallbacksWithInstance_.findAccessibilityNodeInfosByText =
        FindAccessibilityNodeInfosByText;
    AccessibilityMaker::accessibilityProviderCallbacksWithInstance_.findFocusedAccessibilityNode =
        FindFocusedAccessibilityNode;
    AccessibilityMaker::accessibilityProviderCallbacksWithInstance_.findNextFocusAccessibilityNode =
        FindNextFocusAccessibilityNode;
    AccessibilityMaker::accessibilityProviderCallbacksWithInstance_.executeAccessibilityAction =
        ExecuteAccessibilityAction;
    AccessibilityMaker::accessibilityProviderCallbacksWithInstance_.clearFocusedFocusAccessibilityNode =
        ClearFocusedFocusAccessibilityNode;
    AccessibilityMaker::accessibilityProviderCallbacksWithInstance_.getAccessibilityNodeCursorPosition =
        GetAccessibilityNodeCursorPosition;

    // 获取 native 层提供的 accessibility provider，并为其注册回调
    OH_ArkUI_NativeModule_GetNativeAccessibilityProvider(customNode, &accessibilityProvider_);
    if (accessibilityProvider_ == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityMaker", "accessibilityProvider_ is null");
        return 0;
    }

    int32_t ret = OH_ArkUI_AccessibilityProviderRegisterCallbackWithInstance(id, accessibilityProvider_,
        &AccessibilityMaker::accessibilityProviderCallbacksWithInstance_);
    if (ret != 0) {
        return 0;
    }
    return 0;
}
// [End abilitycap_nine_start]

void AccessibilityMaker::SetAccessibilityMode(ArkUI_NativeNodeAPI_1* nodeApi, ArkUI_NodeHandle node,
    ArkUI_AccessibilityMode mode)
{
    if (nodeApi && node) {
        ArkUI_NumberValue value[] = {{.i32 = mode}};
        ArkUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
        nodeApi->setAttribute(node, NODE_ACCESSIBILITY_MODE, &item);
    }
}

void AccessibilityMaker::GetUniqueId(ArkUI_NativeNodeAPI_1* nodeApi, ArkUI_NodeHandle node)
{
    if (nodeApi && node) {
        const ArkUI_AttributeItem *attributeItem = nodeApi->getAttribute(node, NODE_UNIQUE_ID);
        auto id = attributeItem->value[0].i32;
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityMaker", "GetUniqueId: id=%{public}d", id);
    }
}

int32_t AccessibilityMaker::FindAccessibilityNodeInfosById(const char* instanceId, int64_t elementId,
                                                           ArkUI_AccessibilitySearchMode mode,
                                                           int32_t requestId,
                                                           ArkUI_AccessibilityElementInfoList *elementList)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityMaker",
                 "FindAccessibilityNodeInfosById start,elementId: %{public}ld, requestId: %{public}d, mode: %{public}d",
                 elementId, requestId, static_cast<int32_t>(mode));

    if (elementList == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "AccessibilityMaker",
                     "FindAccessibilityNodeInfosById elementList is null");
        return OH_NATIVEXCOMPONENT_RESULT_FAILED;
    }

    const int parentOfRoot = -2100000;
    if (elementId == -1 && mode == ARKUI_ACCESSIBILITY_NATIVE_SEARCH_MODE_PREFETCH_RECURSIVE_CHILDREN) {
        auto rootNode = OH_ArkUI_AddAndGetAccessibilityElementInfo(elementList);
        AccessibilityDialog::InitRootNode(rootNode, parentOfRoot);
        AccessibilityDialog::AddChildNodesForRoot(instanceId, elementList, rootNode);
    } else if (mode == ARKUI_ACCESSIBILITY_NATIVE_SEARCH_MODE_PREFETCH_CURRENT) {
        AccessibilityDialog::HandlePrefetchCurrentMode(instanceId, elementId, elementList, parentOfRoot);
    }
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t AccessibilityMaker::FindAccessibilityNodeInfosByText(const char* instanceId, int64_t elementId,
                                                             const char *text, int32_t requestId,
                                                             ArkUI_AccessibilityElementInfoList *elementList)
{
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t AccessibilityMaker::FindFocusedAccessibilityNode(const char* instanceId, int64_t elementId,
                                                         ArkUI_AccessibilityFocusType focusType,
                                                         int32_t requestId,
                                                         ArkUI_AccessibilityElementInfo *elementInfo)

{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityMaker",
                 "FindFocusedAccessibilityNode elementId: %{public}ld, requestId: %{public}d, focusType: %{public}d",
                 elementId, requestId, static_cast<int32_t>(focusType));
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t AccessibilityMaker::FindNextFocusAccessibilityNode(const char* instanceId, int64_t elementId,
                                                           ArkUI_AccessibilityFocusMoveDirection direction,
                                                           int32_t requestId,
                                                           ArkUI_AccessibilityElementInfo *elementInfo)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityMaker",
                 "FindNextFocusAccessibilityNode elementId: %{public}ld, requestId: %{public}d, direction: %{public}d",
                 elementId, requestId, static_cast<int32_t>(direction));

    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t AccessibilityMaker::ExecuteAccessibilityAction(const char* instanceId, int64_t elementId,
                                                       ArkUI_Accessibility_ActionType action,
                                                       ArkUI_AccessibilityActionArguments *actionArguments,
                                                       int32_t requestId)
{
    // 执行来自无障碍框架的操作，并通过 provider 发送异步事件通知框架
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityMaker",
                 "ExecuteAccessibilityAction elementId: %{public}ld, action: %{public}d", elementId, action);
    auto object = FakeWidget::Instance().GetChild(elementId);
    if (!object) {
        return 0;
    }
    // 创建一个 element info，填充后会被用于发送事件
    auto element = OH_ArkUI_CreateAccessibilityElementInfo();
    OH_ArkUI_AccessibilityElementInfoSetElementId(element, elementId);

    switch (action) {
        case ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_CLICK:
            // 点击事件：调用对象的 OnClick 并填充 element，再发送 clicked 事件
            if (object) {
                object->OnClick();
                object->fillAccessibilityElement(element);
            }
            AccessibilityMaker::SendAccessibilityAsyncEvent(element, ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_CLICKED);
            break;

        case ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_GAIN_ACCESSIBILITY_FOCUS:
            // 获得无障碍焦点：设置对象焦点状态并发送 focused 事件
            if (object) {
                object->SetFocus(true);
                object->fillAccessibilityElement(element);
            }
            AccessibilityMaker::SendAccessibilityAsyncEvent(element,
                ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_ACCESSIBILITY_FOCUSED);
            break;

        case ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_CLEAR_ACCESSIBILITY_FOCUS:
            // 清除无障碍焦点：取消对象焦点并发送 focus cleared 事件
            if (object) {
                object->SetFocus(false);
                object->fillAccessibilityElement(element);
            }
            AccessibilityMaker::SendAccessibilityAsyncEvent(
                element, ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_ACCESSIBILITY_FOCUS_CLEARED);
            break;
    }

    // 释放临时 element 结构
    OH_ArkUI_DestoryAccessibilityElementInfo(element);
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t AccessibilityMaker::ClearFocusedFocusAccessibilityNode(const char* instanceId)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityMaker", "ClearFocusedFocusAccessibilityNode");
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t AccessibilityMaker::GetAccessibilityNodeCursorPosition(const char* instanceId, int64_t elementId,
                                                               int32_t requestId, int32_t *index)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityMaker", "GetAccessibilityNodeCursorPosition");
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

void AccessibilityMaker::SendAccessibilityAsyncEvent(ArkUI_AccessibilityElementInfo *elementInfo,
                                                     ArkUI_AccessibilityEventType eventType)
{
    // 创建事件信息并通过 provider 异步发送给无障碍框架
    auto eventInfo = OH_ArkUI_CreateAccessibilityEventInfo();
    FillEvent(eventInfo, elementInfo, eventType);
    auto callback = [](int32_t errorCode) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityMaker", "result: %{public}d", errorCode);
    };
    OH_ArkUI_SendAccessibilityAsyncEvent(g_provider, eventInfo, callback);
}

int32_t AccessibilityMaker::FindAccessibilityNodeInfosById(int64_t elementId, ArkUI_AccessibilitySearchMode mode,
                                                           int32_t requestId,
                                                           ArkUI_AccessibilityElementInfoList* elementList)
{
    return FindAccessibilityNodeInfosById(DEFAULT_ID, elementId, mode, requestId, elementList);
}
    
int32_t AccessibilityMaker::FindAccessibilityNodeInfosByText(int64_t elementId, const char* text, int32_t requestId,
                                                             ArkUI_AccessibilityElementInfoList* elementList)
{
    return FindAccessibilityNodeInfosByText(DEFAULT_ID, elementId, text, requestId, elementList);
}

int32_t AccessibilityMaker::FindFocusedAccessibilityNode(int64_t elementId, ArkUI_AccessibilityFocusType focusType,
                                                         int32_t requestId,
                                                         ArkUI_AccessibilityElementInfo* elementInfo)
{
    return FindFocusedAccessibilityNode(DEFAULT_ID, elementId, focusType, requestId, elementInfo);
}

int32_t AccessibilityMaker::FindNextFocusAccessibilityNode(int64_t elementId,
                                                           ArkUI_AccessibilityFocusMoveDirection direction,
                                                           int32_t requestId,
                                                           ArkUI_AccessibilityElementInfo* elementInfo)
{
    return FindNextFocusAccessibilityNode(DEFAULT_ID, elementId, direction, requestId, elementInfo);
}

int32_t AccessibilityMaker::ExecuteAccessibilityAction(int64_t elementId, ArkUI_Accessibility_ActionType action,
                                                       ArkUI_AccessibilityActionArguments *actionArguments,
                                                       int32_t requestId)
{
    return ExecuteAccessibilityAction(DEFAULT_ID, elementId, action, actionArguments, requestId);
}

int32_t AccessibilityMaker::ClearFocusedFocusAccessibilityNode()
{
    return ClearFocusedFocusAccessibilityNode(DEFAULT_ID);
}

int32_t AccessibilityMaker::GetAccessibilityNodeCursorPosition(int64_t elementId, int32_t requestId, int32_t* index)
{
    return GetAccessibilityNodeCursorPosition(DEFAULT_ID, elementId, requestId, index);
}