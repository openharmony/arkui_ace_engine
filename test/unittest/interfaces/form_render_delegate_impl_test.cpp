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

#include "gtest/gtest.h"
#include "interfaces/inner_api/form_render/include/form_renderer_delegate_impl.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
constexpr double FORM_WIDTH = 100.0f;
constexpr double FORM_HEIGHT = 100.0f;
constexpr double FORM_BORDER_WIDTH = 10.0f;
const std::string CHECK_KEY = "CHECK_KEY";
} // namespace
class FormRenderDelegateImplTest : public testing::Test {
public:
    static void SetUpTestCase() {};

    static void TearDownTestCase() {};
};

/*
 * @tc.name: FormRenderDelegateImplTest_001
 * @tc.desc: Test OnSurfaceCreate() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateImplTest, FormRenderDelegateImplTest_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderDelegateImplTest_001 start";
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();
    OHOS::AAFwk::Want want;
    OHOS::AppExecFwk::FormJsInfo formJsInfo;
    formJsInfo.bundleName = "bundleName";
    formJsInfo.moduleName = "moduleName";
    formJsInfo.formId = -1;
    EXPECT_EQ(renderDelegate->OnSurfaceCreate(nullptr, formJsInfo, want), ERR_NULL_OBJECT);

    std::string surfaceNodeName = "ArkTSCardNode";
    struct Rosen::RSSurfaceNodeConfig surfaceNodeConfig = { .SurfaceNodeName = surfaceNodeName };
    std::shared_ptr<Rosen::RSSurfaceNode> rsNode = OHOS::Rosen::RSSurfaceNode::Create(surfaceNodeConfig, true);
    EXPECT_EQ(renderDelegate->OnSurfaceCreate(rsNode, formJsInfo, want), ERR_INVALID_DATA);

    formJsInfo.formId = 1;
    EXPECT_EQ(renderDelegate->OnSurfaceCreate(rsNode, formJsInfo, want), ERR_INVALID_DATA);

    std::string onSurfaceCreateKey;
    auto onSurfaceCreate = [&onSurfaceCreateKey](const std::shared_ptr<Rosen::RSSurfaceNode>& /* surfaceNode */,
        const OHOS::AppExecFwk::FormJsInfo& /* info */,
        const AAFwk::Want& /* want */) { onSurfaceCreateKey = CHECK_KEY; };
    renderDelegate->SetSurfaceCreateEventHandler(std::move(onSurfaceCreate));
    EXPECT_EQ(renderDelegate->OnSurfaceCreate(rsNode, formJsInfo, want), ERR_OK);
    GTEST_LOG_(INFO) << "FormRenderDelegateImplTest_001 end";
}

/*
 * @tc.name: FormRenderDelegateImplTest_002
 * @tc.desc: Test OnActionEvent() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateImplTest, FormRenderDelegateImplTest_002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderDelegateImplTest_002 start";
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();
    EXPECT_EQ(renderDelegate->OnActionEvent(""), ERR_INVALID_DATA);

    std::string onActionEventKey;
    auto onAction = [&onActionEventKey](const std::string& /* action */) { onActionEventKey = CHECK_KEY; };
    renderDelegate->SetActionEventHandler(std::move(onAction));
    EXPECT_EQ(renderDelegate->OnActionEvent(""), ERR_OK);
    GTEST_LOG_(INFO) << "FormRenderDelegateImplTest_002 end";
}

/*
 * @tc.name: FormRenderDelegateImplTest_003
 * @tc.desc: Test OnError() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateImplTest, FormRenderDelegateImplTest_003, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderDelegateImplTest_003 start";
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();
    EXPECT_EQ(renderDelegate->OnError("", ""), ERR_INVALID_DATA);

    std::string onErrorEventKey;
    auto onError = [&onErrorEventKey](
        const std::string& /* code */, const std::string& /* msg */) { onErrorEventKey = CHECK_KEY; };
    renderDelegate->SetErrorEventHandler(std::move(onError));
    EXPECT_EQ(renderDelegate->OnError("", ""), ERR_OK);
    GTEST_LOG_(INFO) << "FormRenderDelegateImplTest_003 end";
}

/*
 * @tc.name: FormRenderDelegateImplTest_004
 * @tc.desc: Test OnSurfaceChange() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateImplTest, FormRenderDelegateImplTest_004, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderDelegateImplTest_004 start";
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();
    EXPECT_EQ(renderDelegate->OnSurfaceChange(FORM_WIDTH, FORM_HEIGHT, FORM_BORDER_WIDTH), ERR_INVALID_DATA);

    std::string onSurfaceChangeEventKey;
    auto onSurfaceChange = [&onSurfaceChangeEventKey](float /* width */,
        float /* height */, float /* borderWidth */) { onSurfaceChangeEventKey = CHECK_KEY; };
    renderDelegate->SetSurfaceChangeEventHandler(std::move(onSurfaceChange));
    EXPECT_EQ(renderDelegate->OnSurfaceChange(FORM_WIDTH, FORM_HEIGHT, FORM_BORDER_WIDTH), ERR_OK);
    GTEST_LOG_(INFO) << "FormRenderDelegateImplTest_004 end";
}

/*
 * @tc.name: FormRenderDelegateImplTest_005
 * @tc.desc: Test OnSurfaceDetach() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateImplTest, FormRenderDelegateImplTest_005, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderDelegateImplTest_005 start";
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();
    uint16_t surfaceId= 11111;
    EXPECT_EQ(renderDelegate->OnSurfaceDetach(surfaceId), ERR_INVALID_DATA);

    std::string onSurfaceDetachEventKey;
    auto onSurfaceDetach = [&onSurfaceDetachEventKey]() { onSurfaceDetachEventKey = CHECK_KEY; };
    renderDelegate->SetSurfaceDetachEventHandler(std::move(onSurfaceDetach));
    EXPECT_EQ(renderDelegate->OnSurfaceDetach(surfaceId), ERR_OK);
    GTEST_LOG_(INFO) << "FormRenderDelegateImplTest_005 end";
}

/*
 * @tc.name: FormRenderDelegateImplTest_006
 * @tc.desc: Test OnFormLinkInfoUpdate() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateImplTest, FormRenderDelegateImplTest_006, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderDelegateImplTest_006 start";
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();
    std::vector<std::string> info = {};
    EXPECT_EQ(renderDelegate->OnFormLinkInfoUpdate(info), ERR_INVALID_DATA);

    std::string onFormLinkInfoUpdateEventKey;
    auto onFormLinkInfoUpdate = [&onFormLinkInfoUpdateEventKey](
        const std::vector<std::string>& /* formLinkInfos */) { onFormLinkInfoUpdateEventKey = CHECK_KEY; };
    renderDelegate->SetFormLinkInfoUpdateHandler(std::move(onFormLinkInfoUpdate));
    EXPECT_EQ(renderDelegate->OnFormLinkInfoUpdate(info), ERR_OK);
    GTEST_LOG_(INFO) << "FormRenderDelegateImplTest_006 end";
}

/*
 * @tc.name: FormRenderDelegateImplTest_007
 * @tc.desc: Test OnGetRectRelativeToWindow() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateImplTest, FormRenderDelegateImplTest_007, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderDelegateImplTest_007 start";
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();
    int32_t top = 1;
    int32_t left = 1;
    EXPECT_EQ(renderDelegate->OnGetRectRelativeToWindow(top, left), ERR_INVALID_DATA);

    std::string OnGetRectRelativeToWindowEventKey;
    auto onGetRectRelativeToWindow = [&OnGetRectRelativeToWindowEventKey](
        int32_t& /* top */, int32_t& /* left */) { OnGetRectRelativeToWindowEventKey = CHECK_KEY; };
    renderDelegate->SetGetRectRelativeToWindowHandler(std::move(onGetRectRelativeToWindow));
    EXPECT_EQ(renderDelegate->OnGetRectRelativeToWindow(top, left), ERR_OK);
    GTEST_LOG_(INFO) << "FormRenderDelegateImplTest_007 end";
}
}
