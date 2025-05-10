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

#include <thread>
#include <chrono>
#define private public
#include "interfaces/inner_api/form_render/include/form_renderer.h"
#include "interfaces/inner_api/form_render/include/form_renderer_dispatcher_stub.h"
#undef private
#include "test/mock/interfaces/mock_form_renderer_dispatcher_stub.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
class FormRendererDispatcherStubTest : public testing::Test {
public:
    static void SetUpTestCase() {};

    static void TearDownTestCase() {};
};

/**
 * @tc.number: FormRendererDispatcherStubTest_001
 * @tc.name: OnRemoteRequest
 * @tc.desc:
 */
HWTEST_F(FormRendererDispatcherStubTest, FormRendererDispatcherStubTest_001, TestSize.Level1)
{
    sptr<AppExecFwk::MockFormRendererDispatherStub> renderDispather = new AppExecFwk::MockFormRendererDispatherStub();
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    uint32_t code = 10;
    std::u16string name = u"form_render_dispatcher_stub";
    data.WriteInterfaceToken(name);
    EXPECT_EQ(renderDispather->OnRemoteRequest(code, data, reply, option), ERR_INVALID_VALUE);

    std::u16string descriptor = FormRendererDispatcherStub::GetDescriptor();
    data.WriteInterfaceToken(descriptor);
    bool flag = false;
    auto itFunc = renderDispather->memberFuncMap_.find(code);
    if (itFunc != renderDispather->memberFuncMap_.end()) {
        auto memberFunc = itFunc->second;
        if (memberFunc != nullptr) {
            flag = true;
        }
    }
    EXPECT_FALSE(flag);

    code = 3;
    itFunc = renderDispather->memberFuncMap_.find(code);
    if (itFunc != renderDispather->memberFuncMap_.end()) {
        auto memberFunc = itFunc->second;
        if (memberFunc != nullptr) {
            flag = true;
        }
    }
    EXPECT_TRUE(flag);
    flag = false;

    itFunc = renderDispather->memberFuncMap_.find(code);
    itFunc->second = nullptr;
    if (itFunc != renderDispather->memberFuncMap_.end()) {
        auto memberFunc = itFunc->second;
        if (memberFunc != nullptr) {
            flag = true;
        }
    }
    EXPECT_FALSE(flag);
}

/**
 * @tc.number: FormRendererDispatcherStubTest_002
 * @tc.name: HandleDispatchPointerEvent
 * @tc.desc:
 */
HWTEST_F(FormRendererDispatcherStubTest, FormRendererDispatcherStubTest_002, TestSize.Level1)
{
    sptr<AppExecFwk::MockFormRendererDispatherStub> renderDispather = new AppExecFwk::MockFormRendererDispatherStub();
    MessageParcel data;
    MessageParcel reply;
    
    EXPECT_EQ(renderDispather->HandleDispatchPointerEvent(data, reply), ERR_INVALID_VALUE);

    std::shared_ptr<MMI::PointerEvent> pointerEvent = MMI::PointerEvent::Create();
    ASSERT_TRUE(pointerEvent);
    bool flag = false;
    pointerEvent->WriteToParcel(data);
    if (pointerEvent->ReadFromParcel(data)) {
        flag = true;
    }

    EXPECT_TRUE(flag);
}

/**
 * @tc.number: FormRendererDispatcherStubTest_003
 * @tc.name: HandleSetAllowUpdate, HandleDispatchSurfaceChangeEvent, HandleSetObscured,
 *           HandleOnAccessibilityChildTreeRegister, HandleOnAccessibilityChildTreeDeregister,
 *           HandleOnAccessibilityDumpChildInfo
 * @tc.desc:
 */
HWTEST_F(FormRendererDispatcherStubTest, FormRendererDispatcherStubTest_003, TestSize.Level1)
{
    sptr<AppExecFwk::MockFormRendererDispatherStub> renderDispather = new AppExecFwk::MockFormRendererDispatherStub();
    MessageParcel data;
    MessageParcel reply;
    
    EXPECT_EQ(renderDispather->HandleSetAllowUpdate(data, reply), ERR_OK);
    EXPECT_EQ(renderDispather->HandleDispatchSurfaceChangeEvent(data, reply), ERR_OK);
    EXPECT_EQ(renderDispather->HandleSetObscured(data, reply), ERR_OK);
    EXPECT_EQ(renderDispather->HandleOnAccessibilityChildTreeRegister(data, reply), ERR_OK);
    EXPECT_EQ(renderDispather->HandleOnAccessibilityChildTreeDeregister(data, reply), ERR_OK);
    EXPECT_EQ(renderDispather->HandleOnAccessibilityDumpChildInfo(data, reply), ERR_OK);
}

/**
 * @tc.number: FormRendererDispatcherStubTest_004
 * @tc.name: HandleOnAccessibilityTransferHoverEvent
 * @tc.desc:
 */
HWTEST_F(FormRendererDispatcherStubTest, FormRendererDispatcherStubTest_004, TestSize.Level1)
{
    sptr<AppExecFwk::MockFormRendererDispatherStub> renderDispather = new AppExecFwk::MockFormRendererDispatherStub();
    MessageParcel data;
    MessageParcel reply;
    EXPECT_EQ(renderDispather->HandleOnAccessibilityTransferHoverEvent(data, reply), ERR_INVALID_VALUE);

    float point = 0.0;
    int32_t type = 0;
    int64_t time = 0;
    data.WriteFloat(point);
    data.WriteInt32(type);
    data.WriteInt64(time);
    EXPECT_TRUE(data.ReadFloat(point));
    EXPECT_TRUE(data.ReadInt32(type));
    EXPECT_TRUE(data.ReadInt64(time));
}
}
}