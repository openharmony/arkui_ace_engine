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
#include "interfaces/inner_api/form_render/include/form_renderer_delegate_impl.h"
#include "interfaces/inner_api/form_render/include/form_renderer_delegate_proxy.h"
#include "interfaces/inner_api/form_render/include/form_renderer_group.h"
#include "test/mock/interfaces/mock_i_remote_object_form.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
constexpr double FORM_WIDTH = 100.0f;
constexpr double FORM_HEIGHT = 100.0f;
constexpr double FORM_BORDER_WIDTH = 10.0f;
} // namespace
class FormRenderDelegateProxyTest : public testing::Test {
public:
    static void SetUpTestCase() {};

    static void TearDownTestCase() {};
};

/*
 * @tc.name: FormRenderDelegateProxyTest_001
 * @tc.desc: Test OnSurfaceCreate() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateProxyTest, FormRenderDelegateProxyTest_001, TestSize.Level1)
{
    sptr<AppExecFwk::MockFormIRemoteObject> iremoteObject = new (std::nothrow) AppExecFwk::MockFormIRemoteObject();
    sptr<FormRendererDelegateProxy> renderDelegate =
        new FormRendererDelegateProxy(static_cast<FormRendererDelegateProxy>(iremoteObject));
    ASSERT_NE(renderDelegate, nullptr);

    OHOS::AAFwk::Want newWant;
    OHOS::AppExecFwk::FormJsInfo formJsInfo;
    formJsInfo.bundleName = "bundleName";
    formJsInfo.moduleName = "moduleName";
    formJsInfo.formId = 1;
    EXPECT_EQ(formJsInfo.formId, 1);
    EXPECT_EQ(renderDelegate->OnSurfaceCreate(nullptr, formJsInfo, newWant), ERR_INVALID_VALUE);

    std::string surfaceNodeName = "ArkTSCardNode";
    struct Rosen::RSSurfaceNodeConfig surfaceNodeConfig = { .SurfaceNodeName = surfaceNodeName };
    std::shared_ptr<Rosen::RSSurfaceNode> rsNode = OHOS::Rosen::RSSurfaceNode::Create(surfaceNodeConfig, true);
    ASSERT_NE(rsNode, nullptr);

    EXPECT_CALL(*iremoteObject, SendRequest(_, _, _, _)).Times(1).WillRepeatedly(Return(ERR_OK));
    EXPECT_EQ(renderDelegate->OnSurfaceCreate(rsNode, formJsInfo, newWant), ERR_OK);
    EXPECT_CALL(*iremoteObject, SendRequest(_, _, _, _)).Times(1).WillRepeatedly(Return(ERR_INVALID_VALUE));
    EXPECT_EQ(renderDelegate->OnSurfaceCreate(rsNode, formJsInfo, newWant), ERR_INVALID_VALUE);
}

/*
 * @tc.name: FormRenderDelegateProxyTest_002
 * @tc.desc: Test OnSurfaceReuse() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateProxyTest, FormRenderDelegateProxyTest_002, TestSize.Level1)
{
    sptr<AppExecFwk::MockFormIRemoteObject> iremoteObject = new (std::nothrow) AppExecFwk::MockFormIRemoteObject();
    sptr<FormRendererDelegateProxy> renderDelegate =
        new FormRendererDelegateProxy(static_cast<FormRendererDelegateProxy>(iremoteObject));
    ASSERT_NE(renderDelegate, nullptr);

    OHOS::AAFwk::Want newWant;
    OHOS::AppExecFwk::FormJsInfo formJsInfo;
    formJsInfo.bundleName = "bundleName";
    formJsInfo.moduleName = "moduleName";
    formJsInfo.formId = 1;
    EXPECT_EQ(formJsInfo.formId, 1);

    std::string surfaceNodeName = "ArkTSCardNode";
    struct Rosen::RSSurfaceNodeConfig surfaceNodeConfig = { .SurfaceNodeName = surfaceNodeName };
    std::shared_ptr<Rosen::RSSurfaceNode> rsNode = OHOS::Rosen::RSSurfaceNode::Create(surfaceNodeConfig, true);
    ASSERT_NE(rsNode, nullptr);

    EXPECT_CALL(*iremoteObject, SendRequest(_, _, _, _)).Times(1).WillRepeatedly(Return(ERR_OK));
    EXPECT_EQ(renderDelegate->OnSurfaceReuse(rsNode->GetId(), formJsInfo, newWant), ERR_OK);
    EXPECT_CALL(*iremoteObject, SendRequest(_, _, _, _)).Times(1).WillRepeatedly(Return(ERR_INVALID_VALUE));
    EXPECT_EQ(renderDelegate->OnSurfaceReuse(rsNode->GetId(), formJsInfo, newWant), ERR_INVALID_VALUE);
}

/*
 * @tc.name: FormRenderDelegateProxyTest_003
 * @tc.desc: Test OnSurfaceDetach() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateProxyTest, FormRenderDelegateProxyTest_003, TestSize.Level1)
{
    sptr<AppExecFwk::MockFormIRemoteObject> iremoteObject = new (std::nothrow) AppExecFwk::MockFormIRemoteObject();
    sptr<FormRendererDelegateProxy> renderDelegate =
        new FormRendererDelegateProxy(static_cast<FormRendererDelegateProxy>(iremoteObject));
    ASSERT_NE(renderDelegate, nullptr);

    std::string surfaceNodeName = "ArkTSCardNode";
    struct Rosen::RSSurfaceNodeConfig surfaceNodeConfig = { .SurfaceNodeName = surfaceNodeName };
    std::shared_ptr<Rosen::RSSurfaceNode> rsNode = OHOS::Rosen::RSSurfaceNode::Create(surfaceNodeConfig, true);
    ASSERT_NE(rsNode, nullptr);

    EXPECT_CALL(*iremoteObject, SendRequest(_, _, _, _)).Times(1).WillRepeatedly(Return(ERR_OK));
    EXPECT_EQ(renderDelegate->OnSurfaceDetach(rsNode->GetId()), ERR_OK);
    EXPECT_CALL(*iremoteObject, SendRequest(_, _, _, _)).Times(1).WillRepeatedly(Return(ERR_INVALID_VALUE));
    EXPECT_EQ(renderDelegate->OnSurfaceDetach(rsNode->GetId()), ERR_INVALID_VALUE);
}

/*
 * @tc.name: FormRenderDelegateProxyTest_004
 * @tc.desc: Test OnSurfaceRelease() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateProxyTest, FormRenderDelegateProxyTest_004, TestSize.Level1)
{
    sptr<AppExecFwk::MockFormIRemoteObject> iremoteObject = new (std::nothrow) AppExecFwk::MockFormIRemoteObject();
    sptr<FormRendererDelegateProxy> renderDelegate =
        new FormRendererDelegateProxy(static_cast<FormRendererDelegateProxy>(iremoteObject));
    ASSERT_NE(renderDelegate, nullptr);

    std::string surfaceNodeName = "ArkTSCardNode";
    struct Rosen::RSSurfaceNodeConfig surfaceNodeConfig = { .SurfaceNodeName = surfaceNodeName };
    std::shared_ptr<Rosen::RSSurfaceNode> rsNode = OHOS::Rosen::RSSurfaceNode::Create(surfaceNodeConfig, true);
    ASSERT_NE(rsNode, nullptr);

    EXPECT_CALL(*iremoteObject, SendRequest(_, _, _, _)).Times(1).WillRepeatedly(Return(ERR_OK));
    EXPECT_EQ(renderDelegate->OnSurfaceRelease(rsNode->GetId()), ERR_OK);
    EXPECT_CALL(*iremoteObject, SendRequest(_, _, _, _)).Times(1).WillRepeatedly(Return(ERR_INVALID_VALUE));
    EXPECT_EQ(renderDelegate->OnSurfaceRelease(rsNode->GetId()), ERR_INVALID_VALUE);
}

/*
 * @tc.name: FormRenderDelegateProxyTest_005
 * @tc.desc: Test OnActionEvent() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateProxyTest, FormRenderDelegateProxyTest_005, TestSize.Level1)
{
    sptr<AppExecFwk::MockFormIRemoteObject> iremoteObject = new (std::nothrow) AppExecFwk::MockFormIRemoteObject();
    sptr<FormRendererDelegateProxy> renderDelegate =
        new FormRendererDelegateProxy(static_cast<FormRendererDelegateProxy>(iremoteObject));
    ASSERT_NE(renderDelegate, nullptr);

    EXPECT_CALL(*iremoteObject, SendRequest(_, _, _, _)).Times(1).WillRepeatedly(Return(ERR_OK));
    EXPECT_EQ(renderDelegate->OnActionEvent(""), ERR_OK);
    EXPECT_CALL(*iremoteObject, SendRequest(_, _, _, _)).Times(1).WillRepeatedly(Return(ERR_INVALID_VALUE));
    EXPECT_EQ(renderDelegate->OnActionEvent(""), ERR_INVALID_VALUE);
}

/*
 * @tc.name: FormRenderDelegateProxyTest_006
 * @tc.desc: Test OnError() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateProxyTest, FormRenderDelegateProxyTest_006, TestSize.Level1)
{
    sptr<AppExecFwk::MockFormIRemoteObject> iremoteObject = new (std::nothrow) AppExecFwk::MockFormIRemoteObject();
    sptr<FormRendererDelegateProxy> renderDelegate =
        new FormRendererDelegateProxy(static_cast<FormRendererDelegateProxy>(iremoteObject));
    ASSERT_NE(renderDelegate, nullptr);

    EXPECT_CALL(*iremoteObject, SendRequest(_, _, _, _)).Times(1).WillRepeatedly(Return(ERR_OK));
    EXPECT_EQ(renderDelegate->OnError("", ""), ERR_OK);
    EXPECT_CALL(*iremoteObject, SendRequest(_, _, _, _)).Times(1).WillRepeatedly(Return(ERR_INVALID_VALUE));
    EXPECT_EQ(renderDelegate->OnError("", ""), ERR_INVALID_VALUE);
}

/*
 * @tc.name: FormRenderDelegateProxyTest_007
 * @tc.desc: Test OnSurfaceChange() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateProxyTest, FormRenderDelegateProxyTest_007, TestSize.Level1)
{
    sptr<AppExecFwk::MockFormIRemoteObject> iremoteObject = new (std::nothrow) AppExecFwk::MockFormIRemoteObject();
    sptr<FormRendererDelegateProxy> renderDelegate =
        new FormRendererDelegateProxy(static_cast<FormRendererDelegateProxy>(iremoteObject));
    ASSERT_NE(renderDelegate, nullptr);

    EXPECT_CALL(*iremoteObject, SendRequest(_, _, _, _)).Times(1).WillRepeatedly(Return(ERR_OK));
    EXPECT_EQ(renderDelegate->OnSurfaceChange(FORM_WIDTH, FORM_HEIGHT, FORM_BORDER_WIDTH), ERR_OK);
}

/*
 * @tc.name: FormRenderDelegateProxyTest_008
 * @tc.desc: Test OnFormLinkInfoUpdate() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateProxyTest, FormRenderDelegateProxyTest_008, TestSize.Level1)
{
    sptr<AppExecFwk::MockFormIRemoteObject> iremoteObject = new (std::nothrow) AppExecFwk::MockFormIRemoteObject();
    sptr<FormRendererDelegateProxy> renderDelegate =
        new FormRendererDelegateProxy(static_cast<FormRendererDelegateProxy>(iremoteObject));
    ASSERT_NE(renderDelegate, nullptr);

    std::vector<std::string> info = {};
    EXPECT_CALL(*iremoteObject, SendRequest(_, _, _, _)).Times(1).WillRepeatedly(Return(ERR_OK));
    EXPECT_EQ(renderDelegate->OnFormLinkInfoUpdate(info), ERR_OK);
    EXPECT_CALL(*iremoteObject, SendRequest(_, _, _, _)).Times(1).WillRepeatedly(Return(ERR_INVALID_VALUE));
    EXPECT_EQ(renderDelegate->OnFormLinkInfoUpdate(info), ERR_INVALID_VALUE);
}

/*
 * @tc.name: FormRenderDelegateProxyTest_009
 * @tc.desc: Test OnGetRectRelativeToWindow() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateProxyTest, FormRenderDelegateProxyTest_009, TestSize.Level1)
{
    sptr<AppExecFwk::MockFormIRemoteObject> iremoteObject = new (std::nothrow) AppExecFwk::MockFormIRemoteObject();
    sptr<FormRendererDelegateProxy> renderDelegate =
        new FormRendererDelegateProxy(static_cast<FormRendererDelegateProxy>(iremoteObject));
    ASSERT_NE(renderDelegate, nullptr);

    AccessibilityParentRectInfo parentRectInfo;
    parentRectInfo.top = 0;
    parentRectInfo.left = 0;
    EXPECT_CALL(*iremoteObject, SendRequest(_, _, _, _)).Times(1).WillRepeatedly(Return(ERR_OK));
    EXPECT_EQ(renderDelegate->OnGetRectRelativeToWindow(parentRectInfo), ERR_OK);
    EXPECT_CALL(*iremoteObject, SendRequest(_, _, _, _)).Times(1).WillRepeatedly(Return(ERR_INVALID_VALUE));
    EXPECT_EQ(renderDelegate->OnGetRectRelativeToWindow(parentRectInfo), ERR_INVALID_VALUE);
}

/*
 * @tc.name: FormRenderDelegateProxyTest_010
 * @tc.desc: Test OnUpdateFormDone() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateProxyTest, FormRenderDelegateProxyTest_010, TestSize.Level1)
{
    sptr<AppExecFwk::MockFormIRemoteObject> iremoteObject = new (std::nothrow) AppExecFwk::MockFormIRemoteObject();
    sptr<FormRendererDelegateProxy> renderDelegate =
        new FormRendererDelegateProxy(static_cast<FormRendererDelegateProxy>(iremoteObject));
    ASSERT_NE(renderDelegate, nullptr);

    EXPECT_CALL(*iremoteObject, SendRequest(_, _, _, _)).Times(1).WillRepeatedly(Return(ERR_OK));
    EXPECT_EQ(renderDelegate->OnUpdateFormDone(0), ERR_OK);
    EXPECT_CALL(*iremoteObject, SendRequest(_, _, _, _)).Times(1).WillRepeatedly(Return(ERR_INVALID_VALUE));
    EXPECT_EQ(renderDelegate->OnUpdateFormDone(0), ERR_INVALID_VALUE);
}
}
