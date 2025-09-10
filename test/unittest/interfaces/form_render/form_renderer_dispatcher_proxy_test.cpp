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
#include "interfaces/inner_api/form_render/include/form_renderer.h"
#include "interfaces/inner_api/form_render/include/form_renderer_dispatcher_proxy.h"
#include "test/mock/interfaces/mock_form_renderer_dispatcher_stub.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
class FormRendererDispatcherProxyTest : public testing::Test {
public:
    static void SetUpTestCase() {};

    static void TearDownTestCase() {};
};

/**
  * @tc.number: DispatchPointerEvent_001
  * @tc.name: DispatchPointerEvent_001
  * @tc.desc: Verify the DispatchPointerEvent function when remoteObject is not nullptr.
*/
HWTEST_F(FormRendererDispatcherProxyTest, DispatchPointerEvent_001, TestSize.Level1)
{
    sptr<AppExecFwk::MockFormRendererDispatherStub> mockStub(new AppExecFwk::MockFormRendererDispatherStub());
    auto proxy = std::make_shared<FormRendererDispatcherProxy>(mockStub);
    std::shared_ptr<MMI::PointerEvent> event = MMI::PointerEvent::Create();
    Ace::SerializedGesture serializedGesture;
    proxy->DispatchPointerEvent(event, serializedGesture);
    EXPECT_TRUE(mockStub->SendRequest_called);
}

/**
  * @tc.number: DispatchPointerEvent_002
  * @tc.name: DispatchPointerEvent_002
  * @tc.desc: Verify the DispatchPointerEvent function when remoteObject is nullptr.
*/
HWTEST_F(FormRendererDispatcherProxyTest, DispatchPointerEvent_002, TestSize.Level1)
{
    sptr<AppExecFwk::MockFormRendererDispatherStub> mockStub(new AppExecFwk::MockFormRendererDispatherStub());
    auto proxy = std::make_shared<FormRendererDispatcherProxy>(mockStub);
    std::shared_ptr<MMI::PointerEvent> event = nullptr;
    Ace::SerializedGesture serializedGesture;
    proxy->DispatchPointerEvent(event, serializedGesture);
    EXPECT_FALSE(mockStub->SendRequest_called);
}

/**
  * @tc.number: SetAllowUpdate_001
  * @tc.name: SetAllowUpdate_001
  * @tc.desc: Verify the SetAllowUpdate function when it send request.
*/
HWTEST_F(FormRendererDispatcherProxyTest, SetAllowUpdate_001, TestSize.Level1)
{
    sptr<AppExecFwk::MockFormRendererDispatherStub> mockStub(new AppExecFwk::MockFormRendererDispatherStub());
    auto proxy = std::make_shared<FormRendererDispatcherProxy>(mockStub);
    bool allowUpdate = true;
    proxy->SetAllowUpdate(allowUpdate);
    EXPECT_TRUE(mockStub->SendRequest_called);
}

/**
  * @tc.number: DispatchSurfaceChangeEvent_001
  * @tc.name: DispatchSurfaceChangeEvent_001
  * @tc.desc: Verify the DispatchSurfaceChangeEvent function when it send request.
*/
HWTEST_F(FormRendererDispatcherProxyTest, DispatchSurfaceChangeEvent_001, TestSize.Level1)
{
    sptr<AppExecFwk::MockFormRendererDispatherStub> mockStub(new AppExecFwk::MockFormRendererDispatherStub());
    auto proxy = std::make_shared<FormRendererDispatcherProxy>(mockStub);
    OHOS::AppExecFwk::FormSurfaceInfo formSurfaceInfo;
    formSurfaceInfo.width = 0.0;
    formSurfaceInfo.height = 0.0;
    formSurfaceInfo.borderWidth = 0.0;
    proxy->DispatchSurfaceChangeEvent(formSurfaceInfo);
    EXPECT_TRUE(mockStub->SendRequest_called);
}

/**
  * @tc.number: SetObscured_001
  * @tc.name: SetObscured_001
  * @tc.desc: Verify the SetObscured function when it send request.
*/
HWTEST_F(FormRendererDispatcherProxyTest, SetObscured_001, TestSize.Level1)
{
    sptr<AppExecFwk::MockFormRendererDispatherStub> mockStub(new AppExecFwk::MockFormRendererDispatherStub());
    auto proxy = std::make_shared<FormRendererDispatcherProxy>(mockStub);
    bool isObscured = true;
    proxy->SetObscured(isObscured);
    EXPECT_TRUE(mockStub->SendRequest_called);
}

/**
  * @tc.number: OnAccessibilityChildTreeRegister_001
  * @tc.name: OnAccessibilityChildTreeRegister_001
  * @tc.desc: Verify the OnAccessibilityChildTreeRegister function when it send request.
*/
HWTEST_F(FormRendererDispatcherProxyTest, OnAccessibilityChildTreeRegister_001, TestSize.Level1)
{
    sptr<AppExecFwk::MockFormRendererDispatherStub> mockStub(new AppExecFwk::MockFormRendererDispatherStub());
    auto proxy = std::make_shared<FormRendererDispatcherProxy>(mockStub);
    uint32_t windowId = 0;
    int32_t treeId = 0;
    int64_t accessibilityId = 0;
    proxy->OnAccessibilityChildTreeRegister(windowId, treeId, accessibilityId);
    EXPECT_TRUE(mockStub->SendRequest_called);
}

/**
  * @tc.number: OnAccessibilityChildTreeDeregister_001
  * @tc.name: OnAccessibilityChildTreeDeregister_001
  * @tc.desc: Verify the OnAccessibilityChildTreeDeregister function when it send request.
*/
HWTEST_F(FormRendererDispatcherProxyTest, OnAccessibilityChildTreeDeregister_001, TestSize.Level1)
{
    sptr<AppExecFwk::MockFormRendererDispatherStub> mockStub(new AppExecFwk::MockFormRendererDispatherStub());
    auto proxy = std::make_shared<FormRendererDispatcherProxy>(mockStub);
    proxy->OnAccessibilityChildTreeDeregister();
    EXPECT_TRUE(mockStub->SendRequest_called);
}

/**
  * @tc.number: OnAccessibilityDumpChildInfo_001
  * @tc.name: OnAccessibilityDumpChildInfo_001
  * @tc.desc: Verify the OnAccessibilityDumpChildInfo function when it send request.
*/
HWTEST_F(FormRendererDispatcherProxyTest, OnAccessibilityDumpChildInfo_001, TestSize.Level1)
{
    sptr<AppExecFwk::MockFormRendererDispatherStub> mockStub(new AppExecFwk::MockFormRendererDispatherStub());
    auto proxy = std::make_shared<FormRendererDispatcherProxy>(mockStub);
    std::vector<std::string> params;
    std::vector<std::string> info;
    proxy->OnAccessibilityDumpChildInfo(params, info);
    EXPECT_TRUE(mockStub->SendRequest_called);
}

/**
  * @tc.number: OnAccessibilityTransferHoverEvent_001
  * @tc.name: OnAccessibilityTransferHoverEvent_001
  * @tc.desc: Verify the OnAccessibilityTransferHoverEvent function when it send request.
*/
HWTEST_F(FormRendererDispatcherProxyTest, OnAccessibilityTransferHoverEvent_001, TestSize.Level1)
{
    sptr<AppExecFwk::MockFormRendererDispatherStub> mockStub(new AppExecFwk::MockFormRendererDispatherStub());
    auto proxy = std::make_shared<FormRendererDispatcherProxy>(mockStub);
    float pointX = 0.0;
    float pointY = 0.0;
    int32_t sourceType = 0;
    int32_t eventType = 0;
    int64_t timeMs = 0;
    proxy->OnAccessibilityTransferHoverEvent(pointX, pointY, sourceType, eventType, timeMs);
    EXPECT_TRUE(mockStub->SendRequest_called);
}
}
}