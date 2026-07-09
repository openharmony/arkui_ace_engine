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

#include "AccessibilityDialogSubWindow.h"
#include <hilog/log.h>
#include "AccessibilityMaker.h"
#include <arkui/native_interface_accessibility.h>
#include <arkui/native_dialog.h>
#include <string>

constexpr int32_t BUTTON_CLICK_ID = 1;
constexpr float TEXT_HEIGHT_PX = 100.0f;
constexpr float TEXT_RIGHT_BOTTOM_PX = 500.0f;
constexpr float RECT_RIGHT_BOTTOM_PX = 800.0f;
bool g_isShownSubWindow = false;
ArkUI_NodeHandle buttonNodeSubWindow;
static int32_t g_id = 0;
ArkUI_AccessibilityProviderCallbacksWithInstance
    AccessibilityDialogSubWindow::accessibilityProviderCallbacksWithInstance_;
static ArkUI_AccessibilityProvider* accessibilityProvider_ = nullptr;

class AccessibleObject {
public:
    explicit AccessibleObject(const std::string &name) : name_(name), originName_(name) {}
    void SetFocus(bool focus) { focus_ = focus; }
    void SetName(const std::string &name) { name_ = name; }
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
    char *Hint() const override { return "It's a button"; }
    const char *ObjectType() const override { return "QButton"; }
    void OnClick() override
    {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "AccessibleObject", "FakeButton onClick");
    }
    bool Clickable() const override { return true; }
};

class FakeText : public AccessibleObject {
public:
    explicit FakeText(const std::string &name) : AccessibleObject(name) {}
    char *Hint() const override { return "It's a text"; }
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

void AccessibilityDialogSubWindow::CloseCustomDialog()
{
    OH_ArkUI_CustomDialog_CloseDialog(g_id);
}

void AccessibilityDialogSubWindow::MainViewMethod(ArkUI_NodeContentHandle handle)
{
    // 获取原生节点 API，用于创建节点并设置属性
    ArkUI_NativeNodeAPI_1 *nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1 *>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    // 创建列容器作为对话框子窗口内容的根节点，并设置宽高
    ArkUI_NodeHandle column = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    ArkUI_NumberValue widthValue[] = {{.f32 = 300}};
    ArkUI_AttributeItem widthItem = {.value = widthValue, .size = sizeof(widthValue) / sizeof(ArkUI_NumberValue)};
    nodeAPI->setAttribute(column, NODE_WIDTH, &widthItem);
    ArkUI_NumberValue heightValue[] = {{.f32 = 300}};
    ArkUI_AttributeItem heightItem = {.value = heightValue, .size = sizeof(heightValue) / sizeof(ArkUI_NumberValue)};
    nodeAPI->setAttribute(column, NODE_HEIGHT, &heightItem);

    // 构建一个按钮用于演示打开/关闭子窗口的行为，并注册点击事件
    buttonNodeSubWindow = nodeAPI->createNode(ARKUI_NODE_BUTTON);
    ArkUI_NumberValue buttonWidthValue[] = {{.f32 = 200}};
    ArkUI_AttributeItem buttonWidthItem = {.value = buttonWidthValue,
                                           .size = sizeof(buttonWidthValue) / sizeof(ArkUI_NumberValue)};
    nodeAPI->setAttribute(buttonNodeSubWindow, NODE_WIDTH, &buttonWidthItem);
    ArkUI_NumberValue buttonHeightValue[] = {{.f32 = 50}};
    ArkUI_AttributeItem buttonHeightItem = {.value = buttonHeightValue,
                                            .size = sizeof(buttonHeightValue) / sizeof(ArkUI_NumberValue)};
    nodeAPI->setAttribute(buttonNodeSubWindow, NODE_HEIGHT, &buttonHeightItem);
    ArkUI_AttributeItem labelItem = {.string = "点击弹窗"};
    nodeAPI->setAttribute(buttonNodeSubWindow, NODE_BUTTON_LABEL, &labelItem);
    ArkUI_NumberValue buttonTypeValue[] = {{.i32 = static_cast<int32_t>(ARKUI_BUTTON_TYPE_NORMAL)}};
    ArkUI_AttributeItem buttonTypeItem = {.value = buttonTypeValue,
                                          .size = sizeof(buttonTypeValue) / sizeof(ArkUI_NumberValue)};
    nodeAPI->setAttribute(buttonNodeSubWindow, NODE_BUTTON_TYPE, &buttonTypeItem);
    nodeAPI->registerNodeEvent(buttonNodeSubWindow, NODE_ON_CLICK, BUTTON_CLICK_ID, nullptr);
    // 将事件接收回调关联到静态回调函数以处理点击事件
    nodeAPI->addNodeEventReceiver(buttonNodeSubWindow, AccessibilityDialogSubWindow::OnButtonClicked);
    nodeAPI->addChild(column, buttonNodeSubWindow);
    // 将构建好的列节点附加到传入的 NodeContent
    OH_ArkUI_NodeContent_AddNode(handle, column);
}

void AccessibilityDialogSubWindow::OnButtonClicked(ArkUI_NodeEvent *event)
{
    if (!event || !buttonNodeSubWindow) {
        return;
    }
    // 根据事件 id 判断是否为点击事件，切换子窗口的显示/隐藏状态
    auto eventId = OH_ArkUI_NodeEvent_GetTargetId(event);
    if (eventId == BUTTON_CLICK_ID) {
        ArkUI_NativeNodeAPI_1 *nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1 *>(
            OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
        if (g_isShownSubWindow) {
            // 当前子窗口已显示，关闭并更新按钮文本
            g_isShownSubWindow = false;
            ArkUI_AttributeItem labelItem = {.string = "显示弹窗"};
            nodeAPI->setAttribute(buttonNodeSubWindow, NODE_BUTTON_LABEL, &labelItem);
            AccessibilityDialogSubWindow::CloseCustomDialog();
        } else {
            // 当前子窗口未显示，创建并展示对话框内容
            g_isShownSubWindow = true;
            ArkUI_AttributeItem labelItem = {.string = "关闭弹窗"};
            nodeAPI->setAttribute(buttonNodeSubWindow, NODE_BUTTON_LABEL, &labelItem);
            AccessibilityDialogSubWindow::CreateNativeNodeDialog();
        }
    }
}

ArkUI_NodeHandle AccessibilityDialogSubWindow::CreateNativeNodeDialog()
{
    ArkUI_NativeNodeAPI_1 *nodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1 *>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    if (nodeApi == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityMaker", "nodeApi is null");
        return nullptr;
    }
    // 构建对话框的根节点（column）并放入 scroll 节点
    ArkUI_NodeHandle column = AccessibilityMaker::BuildColumnNode(nodeApi);
    auto scrollNode = nodeApi->createNode(ARKUI_NODE_SCROLL);
    nodeApi->addChild(scrollNode, column);

    CreateAccessibilityProviderSection_dialog(nodeApi);
    return scrollNode;
}

void AccessibilityDialogSubWindow::CreateAccessibilityProviderSection_dialog(ArkUI_NativeNodeAPI_1* nodeApi)
{
    // 创建 native dialog 并为其设置 custom 内容（customNode），同时为 customNode 注册 accessibility provider
    ArkUI_NativeDialogAPI_1 *dialogApi = reinterpret_cast<ArkUI_NativeDialogAPI_1 *>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_DIALOG, "ArkUI_NativeDialogAPI_1"));
    if (nodeApi == nullptr || dialogApi == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityDialogSubWindow",
                     "nodeApi || dialogApi is NULL");
        return;
    }
    
    ArkUI_NativeDialogHandle dialogHandle = dialogApi->create();
    if (dialogHandle == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityDialogSubWindow", "dialogHandle is NULL");
        return;
    }
    
    // 为 dialog 创建一个 custom node 并设置它的尺寸
    auto customNode = nodeApi->createNode(ARKUI_NODE_CUSTOM);
    if (customNode == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityDialogSubWindow", "customNode is NULL");
        return;
    }
    
    ArkUI_NumberValue NODE_WIDTH_value[] = {200};
    ArkUI_AttributeItem NODE_WIDTH_Item[] = { NODE_WIDTH_value, 1 };
    ArkUI_NumberValue NODE_HEIGHT_value[] = {200};
    ArkUI_AttributeItem NODE_HEIGHT_Item[] = { NODE_HEIGHT_value, 1 };
    
    nodeApi->setAttribute(customNode, NODE_WIDTH, NODE_WIDTH_Item);
    nodeApi->setAttribute(customNode, NODE_HEIGHT, NODE_HEIGHT_Item);
    AccessibilityMaker::SetAccessibilityDisabled(false);
    
    // 将 custom node 设置为 dialog 内容并显示 dialog，同时注册 accessibility provider
    if (dialogApi->setContent != nullptr) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityDialogSubWindow",
                     "dialogApi->setContent not nullptr");
        dialogApi->setContent(dialogHandle, customNode);
    }
    
    char uniqueNodeId[64] = {0};
    AccessibilityDialogSubWindow::GetAccessibilityProvider(&customNode, uniqueNodeId);
    if (dialogApi->show != nullptr) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityDialogSubWindow",
                     "dialogApi->show not nullptr");
        dialogApi->show(dialogHandle, false);
    }
}

int32_t AccessibilityDialogSubWindow::GetAccessibilityProvider(ArkUI_NodeHandle* customNode, const char* id)
{
    AccessibilityDialogSubWindow::accessibilityProviderCallbacksWithInstance_.findAccessibilityNodeInfosById =
        FindAccessibilityNodeInfosById;
    AccessibilityDialogSubWindow::accessibilityProviderCallbacksWithInstance_.findAccessibilityNodeInfosByText =
        FindAccessibilityNodeInfosByText;
    AccessibilityDialogSubWindow::accessibilityProviderCallbacksWithInstance_.findFocusedAccessibilityNode =
        FindFocusedAccessibilityNode;
    AccessibilityDialogSubWindow::accessibilityProviderCallbacksWithInstance_.findNextFocusAccessibilityNode =
        FindNextFocusAccessibilityNode;
    AccessibilityDialogSubWindow::accessibilityProviderCallbacksWithInstance_.executeAccessibilityAction =
        ExecuteAccessibilityAction;
    AccessibilityDialogSubWindow::accessibilityProviderCallbacksWithInstance_.clearFocusedFocusAccessibilityNode =
        ClearFocusedFocusAccessibilityNode;
    AccessibilityDialogSubWindow::accessibilityProviderCallbacksWithInstance_.getAccessibilityNodeCursorPosition =
        GetAccessibilityNodeCursorPosition;

    // 获取 native accessibility provider 并为其注册回调
    int32_t result = OH_ArkUI_NativeModule_GetNativeAccessibilityProvider(customNode, &accessibilityProvider_);

    if (accessibilityProvider_ == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityDialogSubWindow",
                     "accessibilityProvider_ is null");
        return 0;
    }

    int32_t ret = OH_ArkUI_AccessibilityProviderRegisterCallbackWithInstance(id, accessibilityProvider_,
        &AccessibilityDialogSubWindow::accessibilityProviderCallbacksWithInstance_);
    if (ret != 0) {
        return 0;
    }
    return 0;
}

void AccessibilityDialogSubWindow::FillElementRect(int64_t elementId, ArkUI_AccessibleRect& rect)
{
    // 根据 elementId 计算元素在屏幕上的矩形
    if (elementId == 0) {
        rect.leftTopX = 0;
        rect.leftTopY = 0;
        rect.rightBottomX = RECT_RIGHT_BOTTOM_PX;
        rect.rightBottomY = RECT_RIGHT_BOTTOM_PX;
    } else {
        int i = elementId - 1;
        rect.leftTopX = i * TEXT_HEIGHT_PX;
        rect.leftTopY = TEXT_HEIGHT_PX;
        rect.rightBottomX = i * TEXT_HEIGHT_PX + TEXT_HEIGHT_PX;
        rect.rightBottomY = TEXT_RIGHT_BOTTOM_PX;
    }
}

void AccessibilityDialogSubWindow::InitRootNode(ArkUI_AccessibilityElementInfo* rootNode, int parentOfRoot)
{
    // 初始化根元素信息并设置屏幕位置（模拟根容器在屏幕上的占位矩形）
    OH_ArkUI_AccessibilityElementInfoSetElementId(rootNode, 0);
    OH_ArkUI_AccessibilityElementInfoSetParentId(rootNode, parentOfRoot);
    FakeWidget::Instance().fillAccessibilityElement(rootNode);
    ArkUI_AccessibleRect rect;
    AccessibilityDialogSubWindow::FillElementRect(0, rect);
    OH_ArkUI_AccessibilityElementInfoSetScreenRect(rootNode, &rect);
}

void AccessibilityDialogSubWindow::AddChildNodesForRoot(const char* instanceId,
                                                        ArkUI_AccessibilityElementInfoList* elementList,
                                                        ArkUI_AccessibilityElementInfo* rootNode)
{
    // 将 FakeWidget 的子对象转换为无障碍元素并加入 elementList 中
    auto objects = FakeWidget::Instance().getAllObjects(instanceId);
    int64_t childNodes[1024] = {0};

    for (int i = 0; i < objects.size(); i++) {
        int elementId = i + 1;
        childNodes[i] = elementId;
        auto child = OH_ArkUI_AddAndGetAccessibilityElementInfo(elementList);
        OH_ArkUI_AccessibilityElementInfoSetElementId(child, elementId);
        OH_ArkUI_AccessibilityElementInfoSetParentId(child, 0);

        objects[i]->fillAccessibilityElement(child);
        ArkUI_AccessibleRect rect;
        AccessibilityDialogSubWindow::FillElementRect(elementId, rect);
        OH_ArkUI_AccessibilityElementInfoSetScreenRect(child, &rect);
    }

    // 将子元素 id 数组设置到根元素中，供框架使用
    int ret = OH_ArkUI_AccessibilityElementInfoSetChildNodeIds(rootNode, objects.size(), childNodes);
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityDialogSubWindow",
                 "FindAccessibilityNodeInfosById child count: %{public}ld %{public}d",
                 objects.size(), ret);
}

void AccessibilityDialogSubWindow::HandlePrefetchCurrentMode(const char* instanceId, int64_t elementId,
                                                             ArkUI_AccessibilityElementInfoList* elementList,
                                                             int parentOfRoot)
{
    if (elementId == -1) {
        elementId = 0;
    }

    auto& widget = FakeWidget::Instance();
    AccessibleObject* obj = (elementId == 0) ? &widget : widget.GetChild(elementId);

    if (!obj) {
        return;
    }

    auto node = OH_ArkUI_AddAndGetAccessibilityElementInfo(elementList);
    OH_ArkUI_AccessibilityElementInfoSetElementId(node, elementId);
    OH_ArkUI_AccessibilityElementInfoSetParentId(node, (elementId == 0) ? parentOfRoot : 0);

    obj->fillAccessibilityElement(node);
    ArkUI_AccessibleRect rect;
    AccessibilityDialogSubWindow::FillElementRect(elementId, rect);
    OH_ArkUI_AccessibilityElementInfoSetScreenRect(node, &rect);

    if (elementId == 0) {
        AccessibilityDialogSubWindow::AddChildNodesForRoot(instanceId, elementList, node);
    }
}

int32_t AccessibilityDialogSubWindow::FindAccessibilityNodeInfosById(const char* instanceId, int64_t elementId,
                                                                     ArkUI_AccessibilitySearchMode mode,
                                                                     int32_t requestId,
                                                                     ArkUI_AccessibilityElementInfoList* elementList)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityDialogSubWindow",
                 "FindAccessibilityNodeInfosById start,elementId: %{public}ld, requestId: %{public}d, mode: %{public}d",
                 elementId, requestId, static_cast<int32_t>(mode));

    if (elementList == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "AccessibilityDialogSubWindow",
                     "FindAccessibilityNodeInfosById elementList is null");
        return OH_NATIVEXCOMPONENT_RESULT_FAILED;
    }

    const int parentOfRoot = -2100000;
    if (elementId == -1 && mode == ARKUI_ACCESSIBILITY_NATIVE_SEARCH_MODE_PREFETCH_RECURSIVE_CHILDREN) {
        auto rootNode = OH_ArkUI_AddAndGetAccessibilityElementInfo(elementList);
        AccessibilityDialogSubWindow::InitRootNode(rootNode, parentOfRoot);
        AccessibilityDialogSubWindow::AddChildNodesForRoot(instanceId, elementList, rootNode);
    } else if (mode == ARKUI_ACCESSIBILITY_NATIVE_SEARCH_MODE_PREFETCH_CURRENT) {
        AccessibilityDialogSubWindow::HandlePrefetchCurrentMode(instanceId, elementId, elementList, parentOfRoot);
    }

    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t AccessibilityDialogSubWindow::FindAccessibilityNodeInfosByText(const char* instanceId, int64_t elementId,
                                                                       const char *text, int32_t requestId,
                                                                       ArkUI_AccessibilityElementInfoList *elementList)
{
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t AccessibilityDialogSubWindow::FindFocusedAccessibilityNode(const char* instanceId, int64_t elementId,
                                                                   ArkUI_AccessibilityFocusType focusType,
                                                                   int32_t requestId,
                                                                   ArkUI_AccessibilityElementInfo *elementInfo)

{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityDialogSubWindow",
                 "FindFocusedAccessibilityNode elementId: %{public}ld, requestId: %{public}d, focusType: %{public}d",
                 elementId, requestId, static_cast<int32_t>(focusType));
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t AccessibilityDialogSubWindow::FindNextFocusAccessibilityNode(const char* instanceId, int64_t elementId,
                                                                     ArkUI_AccessibilityFocusMoveDirection direction,
                                                                     int32_t requestId,
                                                                     ArkUI_AccessibilityElementInfo *elementInfo)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityDialogSubWindow",
                 "FindNextFocusAccessibilityNode elementId: %{public}ld, requestId: %{public}d, direction: %{public}d",
                 elementId, requestId, static_cast<int32_t>(direction));

    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t AccessibilityDialogSubWindow::ExecuteAccessibilityAction(const char* instanceId, int64_t elementId,
                                                                 ArkUI_Accessibility_ActionType action,
                                                                 ArkUI_AccessibilityActionArguments *actionArguments,
                                                                 int32_t requestId)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityDialogSubWindow",
                 "ExecuteAccessibilityAction elementId: %{public}ld, action: %{public}d", elementId, action);
    auto object = FakeWidget::Instance().GetChild(elementId);
    if (!object) {
        return 0;
    }
    auto element = OH_ArkUI_CreateAccessibilityElementInfo();
    OH_ArkUI_AccessibilityElementInfoSetElementId(element, elementId);

    switch (action) {
        case ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_CLICK:
            if (object) {
                object->OnClick();
                object->fillAccessibilityElement(element);
            }
            AccessibilityMaker::SendAccessibilityAsyncEvent(element, ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_CLICKED);
            break;

        case ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_GAIN_ACCESSIBILITY_FOCUS:
            if (object) {
                object->SetFocus(true);
                object->fillAccessibilityElement(element);
            }
            AccessibilityMaker::SendAccessibilityAsyncEvent(element,
                ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_ACCESSIBILITY_FOCUSED);
            break;

        case ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_CLEAR_ACCESSIBILITY_FOCUS:
            if (object) {
                object->SetFocus(false);
                object->fillAccessibilityElement(element);
            }
            AccessibilityMaker::SendAccessibilityAsyncEvent(
                element, ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_ACCESSIBILITY_FOCUS_CLEARED);
            break;
    }

    OH_ArkUI_DestoryAccessibilityElementInfo(element);
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t AccessibilityDialogSubWindow::ClearFocusedFocusAccessibilityNode(const char* instanceId)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityDialogSubWindow",
                 "ClearFocusedFocusAccessibilityNode");
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t AccessibilityDialogSubWindow::GetAccessibilityNodeCursorPosition(const char* instanceId, int64_t elementId,
                                                                         int32_t requestId, int32_t *index)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityDialogSubWindow",
                 "GetAccessibilityNodeCursorPosition");
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}