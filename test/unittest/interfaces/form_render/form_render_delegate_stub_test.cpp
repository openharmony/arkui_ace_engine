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

#define private public
#include "interfaces/inner_api/form_render/include/form_renderer_delegate_impl.h"
#undef private
#include "interfaces/inner_api/form_render/include/form_renderer_delegate_stub.h"
#include "test/mock/interfaces/mock_form_render_delegate_stub.h"
#include "test/mock/interfaces/mock_i_remote_object_form.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {

} // namespace
class FormRenderDelegateStubTest : public testing::Test {
public:
    static void SetUpTestCase() {};

    static void TearDownTestCase() {};
};

/*
 * @tc.name: FormRenderDelegateStubTest_001
 * @tc.desc: Test OnRemoteRequest() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateStubTest, FormRenderDelegateStubTest_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderDelegateStubTest_001 start";
    MockFormRenderDelegateStub renderDelegate;
    uint32_t code = 11;
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;

    std::u16string name = u"form_render_delegate_stub";
    data.WriteInterfaceToken(name);
    EXPECT_EQ(renderDelegate.OnRemoteRequest(code, data, reply, option), ERR_INVALID_VALUE);

    code = 3;
    std::u16string descriptor = FormRendererDelegateStub::GetDescriptor();
    data.WriteInterfaceToken(descriptor);
    EXPECT_EQ(renderDelegate.OnRemoteRequest(code, data, reply, option), ERR_OK);
    GTEST_LOG_(INFO) << "FormRenderDelegateStubTest_001 end";
}

/*
 * @tc.name: FormRenderDelegateStubTest_002
 * @tc.desc: Test HandleOnSurfaceCreate(), HandleOnSurfaceReuse() function formJsInfo is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateStubTest, FormRenderDelegateStubTest_002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderDelegateStubTest_002 start";
    MockFormRenderDelegateStub renderDelegate;
    MessageParcel data;
    MessageParcel reply;
    EXPECT_EQ(renderDelegate.HandleOnSurfaceCreate(data, reply), ERR_INVALID_VALUE);
    EXPECT_EQ(renderDelegate.HandleOnSurfaceReuse(data, reply), ERR_INVALID_VALUE);

    std::string surfaceNodeName = "ArkTSCardNode";
    struct Rosen::RSSurfaceNodeConfig surfaceNodeConfig = { .SurfaceNodeName = surfaceNodeName };
    std::shared_ptr<Rosen::RSSurfaceNode> rsNode = OHOS::Rosen::RSSurfaceNode::Create(surfaceNodeConfig, true);
    ASSERT_NE(rsNode, nullptr);
    rsNode->Marshalling(data);
    EXPECT_EQ(renderDelegate.HandleOnSurfaceCreate(data, reply), ERR_INVALID_VALUE);
    data.WriteUint64(rsNode->GetId());
    EXPECT_EQ(renderDelegate.HandleOnSurfaceReuse(data, reply), ERR_INVALID_VALUE);
    GTEST_LOG_(INFO) << "FormRenderDelegateStubTest_002 end";
}

/*
 * @tc.name: FormRenderDelegateStubTest_003
 * @tc.desc: Test HandleOnSurfaceCreate(), HandleOnSurfaceReuse() function wan is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateStubTest, FormRenderDelegateStubTest_003, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderDelegateStubTest_003 start";
    MockFormRenderDelegateStub renderDelegate;
    MessageParcel data;
    MessageParcel reply;

    std::string surfaceNodeName = "ArkTSCardNode";
    struct Rosen::RSSurfaceNodeConfig surfaceNodeConfig = { .SurfaceNodeName = surfaceNodeName };
    std::shared_ptr<Rosen::RSSurfaceNode> rsNode = OHOS::Rosen::RSSurfaceNode::Create(surfaceNodeConfig, true);
    ASSERT_NE(rsNode, nullptr);
    rsNode->Marshalling(data);

    OHOS::AppExecFwk::FormJsInfo formJsInfo = {};
    formJsInfo.bundleName = "bundleName";
    formJsInfo.moduleName = "moduleName";
    data.WriteParcelable(&formJsInfo);
    EXPECT_EQ(renderDelegate.HandleOnSurfaceCreate(data, reply), ERR_INVALID_VALUE);
    data.WriteUint64(rsNode->GetId());
    formJsInfo.bundleName = "bundleName";
    formJsInfo.moduleName = "moduleName";
    data.WriteParcelable(&formJsInfo);
    EXPECT_EQ(renderDelegate.HandleOnSurfaceReuse(data, reply), ERR_INVALID_VALUE);
    GTEST_LOG_(INFO) << "FormRenderDelegateStubTest_003 end";
}

/*
 * @tc.name: FormRenderDelegateStubTest_004
 * @tc.desc: Test HandleOnSurfaceCreate(), HandleOnSurfaceReuse() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateStubTest, FormRenderDelegateStubTest_004, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderDelegateStubTest_004 start";
    MockFormRenderDelegateStub renderDelegate;
    MessageParcel data;
    MessageParcel reply;

    std::string surfaceNodeName = "ArkTSCardNode";
    struct Rosen::RSSurfaceNodeConfig surfaceNodeConfig = { .SurfaceNodeName = surfaceNodeName };
    std::shared_ptr<Rosen::RSSurfaceNode> rsNode = OHOS::Rosen::RSSurfaceNode::Create(surfaceNodeConfig, true);
    ASSERT_NE(rsNode, nullptr);
    rsNode->Marshalling(data);

    OHOS::AppExecFwk::FormJsInfo formJsInfo = {};
    formJsInfo.bundleName = "bundleName";
    formJsInfo.moduleName = "moduleName";
    data.WriteParcelable(&formJsInfo);

    OHOS::AAFwk::Want want = {};
    data.WriteParcelable(&want);
    EXPECT_EQ(renderDelegate.HandleOnSurfaceCreate(data, reply), ERR_OK);
    data.WriteUint64(rsNode->GetId());
    formJsInfo.bundleName = "bundleName";
    formJsInfo.moduleName = "moduleName";
    data.WriteParcelable(&formJsInfo);
    data.WriteParcelable(&formJsInfo);
    EXPECT_EQ(renderDelegate.HandleOnSurfaceReuse(data, reply), ERR_OK);
    GTEST_LOG_(INFO) << "FormRenderDelegateStubTest_004 end";
}

/*
 * @tc.name: FormRenderDelegateStubTest_005
 * @tc.desc: Test HandleOnSurfaceRelease() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateStubTest, FormRenderDelegateStubTest_005, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderDelegateStubTest_005 start";
    MockFormRenderDelegateStub renderDelegate;
    MessageParcel data;
    MessageParcel reply;
    EXPECT_EQ(renderDelegate.HandleOnSurfaceRelease(data, reply), ERR_OK);

    std::string surfaceNodeName = "ArkTSCardNode";
    struct Rosen::RSSurfaceNodeConfig surfaceNodeConfig = { .SurfaceNodeName = surfaceNodeName };
    std::shared_ptr<Rosen::RSSurfaceNode> rsNode = OHOS::Rosen::RSSurfaceNode::Create(surfaceNodeConfig, true);
    ASSERT_NE(rsNode, nullptr);
    rsNode->Marshalling(data);
    renderDelegate.HandleOnSurfaceCreate(data, reply);
    data.WriteUint64(rsNode->GetId());
    EXPECT_EQ(renderDelegate.HandleOnSurfaceRelease(data, reply), ERR_OK);
    GTEST_LOG_(INFO) << "FormRenderDelegateStubTest_005 end";
}

/*
 * @tc.name: FormRenderDelegateStubTest_006
 * @tc.desc: Test HandleOnSurfaceDetach(), HandleOnActionEvent(), HandleOnError, HandleOnSurfaceChange(),
 *           HandleOnFormLinkInfoUpdate(), HandleOnGetRectRelativeToWindow() HandleOnUpdateFormDone() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateStubTest, FormRenderDelegateStubTest_006, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderDelegateStubTest_006 start";
    MockFormRenderDelegateStub renderDelegate;
    MessageParcel data;
    MessageParcel reply;

    EXPECT_EQ(renderDelegate.HandleOnSurfaceDetach(data, reply), ERR_OK);
    EXPECT_EQ(renderDelegate.HandleOnActionEvent(data, reply), ERR_OK);
    EXPECT_EQ(renderDelegate.HandleOnError(data, reply), ERR_OK);
    EXPECT_EQ(renderDelegate.HandleOnSurfaceChange(data, reply), ERR_OK);
    EXPECT_EQ(renderDelegate.HandleOnFormLinkInfoUpdate(data, reply), ERR_OK);
    EXPECT_EQ(renderDelegate.HandleOnGetRectRelativeToWindow(data, reply), ERR_OK);
    EXPECT_EQ(renderDelegate.HandleOnUpdateFormDone(data, reply), ERR_OK);
    GTEST_LOG_(INFO) << "FormRenderDelegateStubTest_006 end";
}
}
