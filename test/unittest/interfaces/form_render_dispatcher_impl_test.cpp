/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "gtest/gtest.h"
#include "ui_content.h"
#define private public
#include "interfaces/inner_api/form_render/include/form_renderer.h"
#undef private

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
class FormRenderDispatcherImplTest : public testing::Test {
public:
    static void SetUpTestCase() {};

    static void TearDownTestCase() {};

    sptr<FormRendererDispatcherImpl> GetFormRendererDispatcherImpl()
    {
        std::shared_ptr<UIContent> uiContent = nullptr;
        std::shared_ptr<FormRenderer> formRenderer = nullptr;
        std::weak_ptr<OHOS::AppExecFwk::EventHandler> eventHandler;
        sptr<FormRendererDispatcherImpl> renderDispatcher =
            new FormRendererDispatcherImpl(uiContent, formRenderer, eventHandler);
        return renderDispatcher;
    }
};

/**
 * @tc.name: FormRenderDispatcherImplTest002
 * @tc.type: FUNC
 * Function: DispatchPointerEvent
 **@tc.desc: 1. system running normally
 *           2. test FormRendererDispatcherImpl
 */
HWTEST_F(FormRenderDispatcherImplTest, FormRenderDispatcherImplTest002, TestSize.Level1)
{
    sptr<FormRendererDispatcherImpl> renderDispatcher = GetFormRendererDispatcherImpl();
    bool flag = false;
    if (renderDispatcher != nullptr) {
        std::shared_ptr<OHOS::MMI::PointerEvent> pointerEvent = OHOS::MMI::PointerEvent::Create();
        pointerEvent->pointerAction_ = OHOS::MMI::PointerEvent::POINTER_ACTION_DOWN;
        SerializedGesture serializedGesture;
        renderDispatcher->DispatchPointerEvent(pointerEvent, serializedGesture);
        flag = true;
    }
    EXPECT_TRUE(flag);
}

/**
 * @tc.name: FormRenderDispatcherImplTest003
 * @tc.type: FUNC
 * Function: DispatchPointerEvent
 **@tc.desc: 1. system running normally
 *           2. test FormRendererDispatcherImpl
 */
HWTEST_F(FormRenderDispatcherImplTest, FormRenderDispatcherImplTest003, TestSize.Level1)
{
    sptr<FormRendererDispatcherImpl> renderDispatcher = GetFormRendererDispatcherImpl();
    bool flag = false;
    if (renderDispatcher != nullptr) {
        std::shared_ptr<OHOS::MMI::PointerEvent> pointerEvent = OHOS::MMI::PointerEvent::Create();
        pointerEvent->pointerAction_ = OHOS::MMI::PointerEvent::POINTER_ACTION_UP;
        SerializedGesture serializedGesture;
        renderDispatcher->DispatchPointerEvent(pointerEvent, serializedGesture);
        flag = true;
    }
    EXPECT_TRUE(flag);
}

/**
 * @tc.name: FormRenderDispatcherImplTest004
 * @tc.type: FUNC
 * Function: DispatchPointerEvent
 **@tc.desc: 1. system running normally
 *           2. test FormRendererDispatcherImpl
 */
HWTEST_F(FormRenderDispatcherImplTest, FormRenderDispatcherImplTest004, TestSize.Level1)
{
    sptr<FormRendererDispatcherImpl> renderDispatcher = GetFormRendererDispatcherImpl();
    bool flag = false;
    if (renderDispatcher != nullptr) {
        std::shared_ptr<OHOS::MMI::PointerEvent> pointerEvent = OHOS::MMI::PointerEvent::Create();
        pointerEvent->pointerAction_ = OHOS::MMI::PointerEvent::POINTER_ACTION_UP;
        SerializedGesture serializedGesture;
        renderDispatcher->DispatchPointerEvent(pointerEvent, serializedGesture);
        flag = true;
    }
    EXPECT_TRUE(flag);
}

/**
 * @tc.name: FormRenderDispatcherImplTest005
 * @tc.type: FUNC
 * Function: SetObscured
 **@tc.desc: 1. system running normally
 *           2. test FormRendererDispatcherImpl
 */
HWTEST_F(FormRenderDispatcherImplTest, FormRenderDispatcherImplTest005, TestSize.Level1)
{
    sptr<FormRendererDispatcherImpl> renderDispatcher = GetFormRendererDispatcherImpl();
    bool flag = false;
    if (renderDispatcher != nullptr) {
        renderDispatcher->SetObscured(true);
        flag = true;
    }
    EXPECT_TRUE(flag);
}

/**
 * @tc.name: FormRenderDispatcherImplTest006
 * @tc.type: FUNC
 * Function: OnAccessibilityChildTreeRegister
 **@tc.desc: 1. system running normally
 *           2. test FormRendererDispatcherImpl
 */
HWTEST_F(FormRenderDispatcherImplTest, FormRenderDispatcherImplTest006, TestSize.Level1)
{
    sptr<FormRendererDispatcherImpl> renderDispatcher = GetFormRendererDispatcherImpl();
    bool flag = false;
    uint32_t windowId = 1;
    int32_t treeId = 11;
    int64_t accessibilityId = 111;
    if (renderDispatcher != nullptr) {
        renderDispatcher->OnAccessibilityChildTreeRegister(windowId, treeId, accessibilityId);
        flag = true;
    }
    EXPECT_TRUE(flag);
}

/**
 * @tc.name: FormRenderDispatcherImplTest007
 * @tc.type: FUNC
 * Function: OnAccessibilityChildTreeDeregister
 **@tc.desc: 1. system running normally
 *           2. test FormRendererDispatcherImpl
 */
HWTEST_F(FormRenderDispatcherImplTest, FormRenderDispatcherImplTest007, TestSize.Level1)
{
    sptr<FormRendererDispatcherImpl> renderDispatcher = GetFormRendererDispatcherImpl();
    bool flag = false;
    if (renderDispatcher != nullptr) {
        renderDispatcher->OnAccessibilityChildTreeDeregister();
        flag = true;
    }
    EXPECT_TRUE(flag);
}

/**
 * @tc.name: FormRenderDispatcherImplTest008
 * @tc.type: FUNC
 * Function: OnAccessibilityDumpChildInfo
 **@tc.desc: 1. system running normally
 *           2. test FormRendererDispatcherImpl
 */
HWTEST_F(FormRenderDispatcherImplTest, FormRenderDispatcherImplTest008, TestSize.Level1)
{
    sptr<FormRendererDispatcherImpl> renderDispatcher = GetFormRendererDispatcherImpl();
    bool flag = false;
    std::vector<std::string> params;
    std::vector<std::string> info;
    if (renderDispatcher != nullptr) {
        renderDispatcher->OnAccessibilityDumpChildInfo(params, info);
        flag = true;
    }
    EXPECT_TRUE(flag);
}

/**
 * @tc.name: FormRenderDispatcherImplTest009
 * @tc.type: FUNC
 * Function: OnAccessibilityDumpChildInfo
 **@tc.desc: 1. system running normally
 *           2. test FormRendererDispatcherImpl
 */
HWTEST_F(FormRenderDispatcherImplTest, FormRenderDispatcherImplTest009, TestSize.Level1)
{
    sptr<FormRendererDispatcherImpl> renderDispatcher = GetFormRendererDispatcherImpl();
    bool flag = false;
    std::vector<std::string> params;
    std::vector<std::string> info;
    if (renderDispatcher != nullptr) {
        renderDispatcher->OnAccessibilityDumpChildInfo(params, info);
        flag = true;
    }
    EXPECT_TRUE(flag);
}

/**
 * @tc.name: FormRenderDispatcherImplTest010
 * @tc.type: FUNC
 * Function: OnAccessibilityTransferHoverEvent
 **@tc.desc: 1. system running normally
 *           2. test FormRendererDispatcherImpl
 */
HWTEST_F(FormRenderDispatcherImplTest, FormRenderDispatcherImplTest010, TestSize.Level1)
{
    sptr<FormRendererDispatcherImpl> renderDispatcher = GetFormRendererDispatcherImpl();
    bool flag = false;
    float pointX = 1.1;
    float pointY = 2.2;
    int32_t sourceType = 1;
    int32_t eventType = 2;
    int64_t timeMs = 1000;
    if (renderDispatcher != nullptr) {
        renderDispatcher->OnAccessibilityTransferHoverEvent(pointX, pointY, sourceType, eventType, timeMs);
        flag = true;
    }
    EXPECT_TRUE(flag);
}

/**
 * @tc.name: FormRenderDispatcherImplTest011
 * @tc.type: FUNC
 * Function: DispatchSurfaceChangeEvent
 **@tc.desc: 1. system running normally
 *           2. test FormRendererDispatcherImpl
 */
HWTEST_F(FormRenderDispatcherImplTest, FormRenderDispatcherImplTest011, TestSize.Level1)
{
    sptr<FormRendererDispatcherImpl> renderDispatcher = GetFormRendererDispatcherImpl();
    bool flag = false;
    float width = 11;
    float height = 22;
    if (renderDispatcher != nullptr) {
        renderDispatcher->DispatchSurfaceChangeEvent(width, height);
        flag = true;
    }
    EXPECT_TRUE(flag);
}

/**
 * @tc.name: FormRenderDispatcherImplTest012
 * @tc.type: FUNC
 * Function: DispatchSurfaceChangeEvent
 **@tc.desc: 1. system running normally
 *           2. test FormRendererDispatcherImpl
 */
HWTEST_F(FormRenderDispatcherImplTest, FormRenderDispatcherImplTest012, TestSize.Level1)
{
    sptr<FormRendererDispatcherImpl> renderDispatcher = GetFormRendererDispatcherImpl();
    bool flag = false;
    float width = 11;
    float height = 22;
    if (renderDispatcher != nullptr) {
        renderDispatcher->DispatchSurfaceChangeEvent(width, height);
        flag = true;
    }
    EXPECT_TRUE(flag);
}

/**
 * @tc.name: FormRenderDispatcherImplTest013
 * @tc.desc: test FormRendererDispatcherImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDispatcherImplTest, FormRenderDispatcherImplTest013, TestSize.Level1)
{
    sptr<FormRendererDispatcherImpl> renderDispatcher = GetFormRendererDispatcherImpl();
    constexpr uint32_t code = static_cast<uint32_t>(IFormRendererDispatcher::Message::DISPATCH_POINTER_EVENT);
    MessageParcel data;
    data.WriteInterfaceToken(FormRendererDispatcherImpl::GetDescriptor());
    std::shared_ptr<OHOS::MMI::PointerEvent> pointerEvent = OHOS::MMI::PointerEvent::Create();
    pointerEvent->WriteToParcel(data);
    MessageParcel reply;
    MessageOption option;
    if (renderDispatcher != nullptr) {
        auto ans = renderDispatcher->OnRemoteRequest(code, data, reply, option);
        EXPECT_EQ(ans, ERR_OK);
    }
}

/**
 * @tc.name: FormRenderDispatcherImplTest014
 * @tc.desc: test FormRendererDispatcherImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDispatcherImplTest, FormRenderDispatcherImplTest014, TestSize.Level1)
{
    sptr<FormRendererDispatcherImpl> renderDispatcher = GetFormRendererDispatcherImpl();
    constexpr uint32_t code = static_cast<uint32_t>(IFormRendererDispatcher::Message::DISPATCH_POINTER_EVENT);
    MessageParcel data;
    data.WriteInterfaceToken(FormRendererDispatcherImpl::GetDescriptor());
    MessageParcel reply;
    MessageOption option;
    if (renderDispatcher != nullptr) {
        auto ans = renderDispatcher->OnRemoteRequest(code, data, reply, option);
        EXPECT_EQ(ans, ERR_INVALID_VALUE);
    }
}

/**
 * @tc.name: FormRenderDispatcherImplTest015
 * @tc.desc: test FormRendererDispatcherImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDispatcherImplTest, FormRenderDispatcherImplTest015, TestSize.Level1)
{
    sptr<FormRendererDispatcherImpl> renderDispatcher = GetFormRendererDispatcherImpl();
    constexpr uint32_t code = static_cast<uint32_t>(IFormRendererDispatcher::Message::SET_ALLOW_UPDATE);
    MessageParcel data;
    data.WriteInterfaceToken(FormRendererDispatcherImpl::GetDescriptor());
    data.WriteBool(true);
    MessageParcel reply;
    MessageOption option;
    if (renderDispatcher != nullptr) {
        auto ans = renderDispatcher->OnRemoteRequest(code, data, reply, option);
        EXPECT_EQ(ans, ERR_OK);
    }
}

/**
 * @tc.name: FormRenderDispatcherImplTest016
 * @tc.desc: test FormRendererDispatcherImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDispatcherImplTest, FormRenderDispatcherImplTest016, TestSize.Level1)
{
    sptr<FormRendererDispatcherImpl> renderDispatcher = GetFormRendererDispatcherImpl();
    constexpr uint32_t code = static_cast<uint32_t>(IFormRendererDispatcher::Message::DISPATCH_SURFACE_CHANGE_EVENT);
    MessageParcel data;
    data.WriteInterfaceToken(FormRendererDispatcherImpl::GetDescriptor());
    float width = 1.0;
    float height = 1.0;
    float borderWidth = 1.0;
    data.WriteBool(width);
    data.WriteBool(height);
    data.WriteBool(borderWidth);
    MessageParcel reply;
    MessageOption option;
    if (renderDispatcher != nullptr) {
        auto ans = renderDispatcher->OnRemoteRequest(code, data, reply, option);
        EXPECT_EQ(ans, ERR_OK);
    }
}

/**
 * @tc.name: FormRenderDispatcherImplTest017
 * @tc.desc: test FormRendererDispatcherImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDispatcherImplTest, FormRenderDispatcherImplTest017, TestSize.Level1)
{
    sptr<FormRendererDispatcherImpl> renderDispatcher = GetFormRendererDispatcherImpl();
    constexpr uint32_t code = static_cast<uint32_t>(IFormRendererDispatcher::Message::SET_OBSCURED);
    MessageParcel data;
    data.WriteInterfaceToken(FormRendererDispatcherImpl::GetDescriptor());
    data.WriteBool(true);
    MessageParcel reply;
    MessageOption option;
    if (renderDispatcher != nullptr) {
        auto ans = renderDispatcher->OnRemoteRequest(code, data, reply, option);
        EXPECT_EQ(ans, ERR_OK);
    }
}

/**
 * @tc.name: FormRenderDispatcherImplTest018
 * @tc.desc: test FormRendererDispatcherImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDispatcherImplTest, FormRenderDispatcherImplTest018, TestSize.Level1)
{
    sptr<FormRendererDispatcherImpl> renderDispatcher = GetFormRendererDispatcherImpl();
    constexpr uint32_t code =
        static_cast<uint32_t>(IFormRendererDispatcher::Message::ACCESSIBILITY_CHILD_TREE_REGISTER);
    MessageParcel data;
    data.WriteInterfaceToken(FormRendererDispatcherImpl::GetDescriptor());
    uint32_t windowId = 1;
    int32_t treeId = 2;
    int64_t accessibilityId = 3;
    data.WriteUint32(windowId);
    data.WriteUint32(treeId);
    data.WriteUint64(accessibilityId);
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);
    if (renderDispatcher != nullptr) {
        auto ans = renderDispatcher->OnRemoteRequest(code, data, reply, option);
        EXPECT_EQ(ans, ERR_OK);
    }
}

/**
 * @tc.name: FormRenderDispatcherImplTest019
 * @tc.desc: test FormRendererDispatcherImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDispatcherImplTest, FormRenderDispatcherImplTest019, TestSize.Level1)
{
    sptr<FormRendererDispatcherImpl> renderDispatcher = GetFormRendererDispatcherImpl();
    constexpr uint32_t code =
        static_cast<uint32_t>(IFormRendererDispatcher::Message::ACCESSIBILITY_CHILD_TREE_DEREGISTER);
    MessageParcel data;
    data.WriteInterfaceToken(FormRendererDispatcherImpl::GetDescriptor());
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);
    if (renderDispatcher != nullptr) {
        auto ans = renderDispatcher->OnRemoteRequest(code, data, reply, option);
        EXPECT_EQ(ans, ERR_OK);
    }
}

/**
 * @tc.name: FormRenderDispatcherImplTest020
 * @tc.desc: test FormRendererDispatcherImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDispatcherImplTest, FormRenderDispatcherImplTest020, TestSize.Level1)
{
    sptr<FormRendererDispatcherImpl> renderDispatcher = GetFormRendererDispatcherImpl();
    constexpr uint32_t code = static_cast<uint32_t>(IFormRendererDispatcher::Message::ACCESSIBILITY_DUMP_CHILD_INFO);
    MessageParcel data;
    data.WriteInterfaceToken(FormRendererDispatcherImpl::GetDescriptor());
    const std::vector<std::string> params { "hello", "world" };
    data.WriteStringVector(params);
    MessageParcel reply;
    MessageOption option;
    if (renderDispatcher != nullptr) {
        auto ans = renderDispatcher->OnRemoteRequest(code, data, reply, option);
        EXPECT_EQ(ans, ERR_OK);
    }
}

/**
 * @tc.name: FormRenderDispatcherImplTest021
 * @tc.desc: test FormRendererDispatcherImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDispatcherImplTest, FormRenderDispatcherImplTest021, TestSize.Level1)
{
    sptr<FormRendererDispatcherImpl> renderDispatcher = GetFormRendererDispatcherImpl();
    constexpr uint32_t code = static_cast<uint32_t>(IFormRendererDispatcher::Message::ACCESSIBILITY_DUMP_CHILD_INFO);
    MessageParcel data;
    data.WriteInterfaceToken(FormRendererDispatcherImpl::GetDescriptor());
    data.WriteBool(true);
    MessageParcel reply;
    MessageOption option;
    if (renderDispatcher != nullptr) {
        auto ans = renderDispatcher->OnRemoteRequest(code, data, reply, option);
        EXPECT_EQ(ans, ERR_INVALID_VALUE);
    }
}

/**
 * @tc.name: FormRenderDispatcherImplTest022
 * @tc.desc: test FormRendererDispatcherImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDispatcherImplTest, FormRenderDispatcherImplTest022, TestSize.Level1)
{
    sptr<FormRendererDispatcherImpl> renderDispatcher = GetFormRendererDispatcherImpl();
    constexpr uint32_t code =
        static_cast<uint32_t>(IFormRendererDispatcher::Message::ACCESSIBILITY_TRANSFER_HOVER_EVENT);
    MessageParcel data;
    data.WriteInterfaceToken(FormRendererDispatcherImpl::GetDescriptor());
    float pointX = 0;
    float pointY = 0;
    int32_t sourceType = 0;
    int32_t eventType = 0;
    int64_t timeMs = 1;
    data.WriteFloat(pointX);
    data.WriteFloat(pointY);
    data.WriteInt32(sourceType);
    data.WriteInt32(eventType);
    data.WriteInt64(timeMs);
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);
    if (renderDispatcher != nullptr) {
        auto ans = renderDispatcher->OnRemoteRequest(code, data, reply, option);
        EXPECT_EQ(ans, ERR_OK);
    }
}

/**
 * @tc.name: FormRenderDispatcherImplTest023
 * @tc.desc: test FormRendererDispatcherImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDispatcherImplTest, FormRenderDispatcherImplTest023, TestSize.Level1)
{
    sptr<FormRendererDispatcherImpl> renderDispatcher = GetFormRendererDispatcherImpl();
    constexpr uint32_t code =
        static_cast<uint32_t>(IFormRendererDispatcher::Message::ACCESSIBILITY_TRANSFER_HOVER_EVENT);
    MessageParcel data;
    data.WriteInterfaceToken(FormRendererDispatcherImpl::GetDescriptor());
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);
    if (renderDispatcher != nullptr) {
        auto ans = renderDispatcher->OnRemoteRequest(code, data, reply, option);
        EXPECT_EQ(ans, ERR_INVALID_VALUE);
    }
}

} // namespace OHOS::Ace
