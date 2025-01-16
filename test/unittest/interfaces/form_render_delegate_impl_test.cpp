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

    sptr<FormRendererDelegateImpl> SurfaceCreateOnFormRendererDelegateImpl()
    {
        sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();
        constexpr uint32_t createCode = static_cast<uint32_t>(IFormRendererDelegate::Message::ON_SURFACE_CREATE);
        std::string surfaceNodeName = "ArkTSCardNode";
        struct Rosen::RSSurfaceNodeConfig surfaceNodeConfig = { .SurfaceNodeName = surfaceNodeName };
        OHOS::AppExecFwk::FormJsInfo formJsInfo;
        OHOS::AAFwk::Want want;
        std::shared_ptr<Rosen::RSSurfaceNode> rsNode = OHOS::Rosen::RSSurfaceNode::Create(surfaceNodeConfig, true);
        MessageParcel createData;
        createData.WriteInterfaceToken(FormRendererDelegateImpl::GetDescriptor());
        rsNode->SetId(1);
        rsNode->Marshalling(createData);
        createData.WriteParcelable(&formJsInfo);
        createData.WriteParcelable(&want);
        MessageParcel createReply;
        MessageOption createOption;
        auto createAns = renderDelegate->OnRemoteRequest(createCode, createData, createReply, createOption);
        EXPECT_EQ(createAns, ERR_OK);
        return renderDelegate;
    }
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
    AccessibilityParentRectInfo parentRectInfo;
    parentRectInfo.top = 1;
    parentRectInfo.left = 1;
    EXPECT_EQ(renderDelegate->OnGetRectRelativeToWindow(parentRectInfo), ERR_INVALID_DATA);

    std::string OnGetRectRelativeToWindowEventKey;
    auto onGetRectRelativeToWindow = [&OnGetRectRelativeToWindowEventKey](
        AccessibilityParentRectInfo&) { OnGetRectRelativeToWindowEventKey = CHECK_KEY; };
    renderDelegate->SetGetRectRelativeToWindowHandler(std::move(onGetRectRelativeToWindow));
    EXPECT_EQ(renderDelegate->OnGetRectRelativeToWindow(parentRectInfo), ERR_OK);
    GTEST_LOG_(INFO) << "FormRenderDelegateImplTest_007 end";
}

/**
 * @tc.name: FormRenderDelegateImplTest_008
 * @tc.desc: test FormRendererDelegateImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateImplTest, FormRenderDelegateImplTest_008, TestSize.Level1)
{
    auto renderDelegate = SurfaceCreateOnFormRendererDelegateImpl();
    uint64_t surfaceId = 1;
    OHOS::AppExecFwk::FormJsInfo formJsInfo;

    constexpr uint32_t reUseCode = static_cast<uint32_t>(IFormRendererDelegate::Message::ON_SURFACE_REUSE);
    MessageParcel reUseData;
    OHOS::AAFwk::Want want;
    reUseData.WriteInterfaceToken(FormRendererDelegateImpl::GetDescriptor());
    reUseData.WriteUint64(surfaceId);
    reUseData.WriteParcelable(&formJsInfo);
    reUseData.WriteParcelable(&want);
    MessageParcel reUseReply;
    MessageOption reUseOption;
    auto reUseAns = renderDelegate->OnRemoteRequest(reUseCode, reUseData, reUseReply, reUseOption);
    EXPECT_EQ(reUseAns, ERR_OK);
}

/**
 * @tc.name: FormRenderDelegateImplTest_009
 * @tc.desc: test FormRendererDelegateImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateImplTest, FormRenderDelegateImplTest_009, TestSize.Level1)
{
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();
    constexpr uint32_t code = static_cast<uint32_t>(IFormRendererDelegate::Message::ON_SURFACE_CREATE);

    MessageParcel data;
    data.WriteInterfaceToken(FormRendererDelegateImpl::GetDescriptor());
    MessageParcel reply;
    MessageOption option;
    auto ans = renderDelegate->OnRemoteRequest(code, data, reply, option);
    EXPECT_EQ(ans, ERR_INVALID_VALUE);
}

/**
 * @tc.name: FormRenderDelegateImplTest_010
 * @tc.desc: test FormRendererDelegateImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateImplTest, FormRenderDelegateImplTest_010, TestSize.Level1)
{
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();
    constexpr uint32_t code = static_cast<uint32_t>(IFormRendererDelegate::Message::ON_SURFACE_CREATE);
    std::string surfaceNodeName = "ArkTSCardNode";
    struct Rosen::RSSurfaceNodeConfig surfaceNodeConfig = { .SurfaceNodeName = surfaceNodeName };
    std::shared_ptr<Rosen::RSSurfaceNode> rsNode = OHOS::Rosen::RSSurfaceNode::Create(surfaceNodeConfig, true);

    MessageParcel data;
    data.WriteInterfaceToken(FormRendererDelegateImpl::GetDescriptor());
    rsNode->Marshalling(data);
    MessageParcel reply;
    MessageOption option;
    auto ans = renderDelegate->OnRemoteRequest(code, data, reply, option);
    EXPECT_EQ(ans, ERR_INVALID_VALUE);
}

/**
 * @tc.name: FormRenderDelegateImplTest_011
 * @tc.desc: test FormRendererDelegateImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateImplTest, FormRenderDelegateImplTest_011, TestSize.Level1)
{
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();
    constexpr uint32_t code = static_cast<uint32_t>(IFormRendererDelegate::Message::ON_SURFACE_CREATE);
    std::string surfaceNodeName = "ArkTSCardNode";
    struct Rosen::RSSurfaceNodeConfig surfaceNodeConfig = { .SurfaceNodeName = surfaceNodeName };
    OHOS::AppExecFwk::FormJsInfo formJsInfo;
    std::shared_ptr<Rosen::RSSurfaceNode> rsNode = OHOS::Rosen::RSSurfaceNode::Create(surfaceNodeConfig, true);

    MessageParcel data;
    data.WriteInterfaceToken(FormRendererDelegateImpl::GetDescriptor());
    rsNode->Marshalling(data);
    data.WriteParcelable(&formJsInfo);
    MessageParcel reply;
    MessageOption option;
    auto ans = renderDelegate->OnRemoteRequest(code, data, reply, option);
    EXPECT_EQ(ans, ERR_INVALID_VALUE);
}

/**
 * @tc.name: FormRenderDelegateImplTest_012
 * @tc.desc: test FormRendererDelegateImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateImplTest, FormRenderDelegateImplTest_012, TestSize.Level1)
{
    auto renderDelegate = SurfaceCreateOnFormRendererDelegateImpl();
    uint64_t surfaceId = 2;
    OHOS::AppExecFwk::FormJsInfo formJsInfo;

    constexpr uint32_t reUseCode = static_cast<uint32_t>(IFormRendererDelegate::Message::ON_SURFACE_REUSE);
    MessageParcel reUseData;
    OHOS::AAFwk::Want want;
    reUseData.WriteInterfaceToken(FormRendererDelegateImpl::GetDescriptor());
    reUseData.WriteUint64(surfaceId);
    reUseData.WriteParcelable(&formJsInfo);
    reUseData.WriteParcelable(&want);
    MessageParcel reUseReply;
    MessageOption reUseOption;
    auto reUseAns = renderDelegate->OnRemoteRequest(reUseCode, reUseData, reUseReply, reUseOption);
    EXPECT_EQ(reUseAns, ERR_INVALID_VALUE);
}

/**
 * @tc.name: FormRenderDelegateImplTest_013
 * @tc.desc: test FormRendererDelegateImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateImplTest, FormRenderDelegateImplTest_013, TestSize.Level1)
{
    auto renderDelegate = SurfaceCreateOnFormRendererDelegateImpl();
    uint64_t surfaceId = 1;

    constexpr uint32_t reUseCode = static_cast<uint32_t>(IFormRendererDelegate::Message::ON_SURFACE_REUSE);
    MessageParcel reUseData;
    reUseData.WriteInterfaceToken(FormRendererDelegateImpl::GetDescriptor());
    reUseData.WriteUint64(surfaceId);
    MessageParcel reUseReply;
    MessageOption reUseOption;
    auto reUseAns = renderDelegate->OnRemoteRequest(reUseCode, reUseData, reUseReply, reUseOption);
    EXPECT_EQ(reUseAns, ERR_INVALID_VALUE);
}

/**
 * @tc.name: FormRenderDelegateImplTest_014
 * @tc.desc: test FormRendererDelegateImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateImplTest, FormRenderDelegateImplTest_014, TestSize.Level1)
{
    auto renderDelegate = SurfaceCreateOnFormRendererDelegateImpl();
    uint64_t surfaceId = 2;
    OHOS::AppExecFwk::FormJsInfo formJsInfo;

    constexpr uint32_t reUseCode = static_cast<uint32_t>(IFormRendererDelegate::Message::ON_SURFACE_REUSE);
    MessageParcel reUseData;
    reUseData.WriteInterfaceToken(FormRendererDelegateImpl::GetDescriptor());
    reUseData.WriteUint64(surfaceId);
    reUseData.WriteParcelable(&formJsInfo);
    MessageParcel reUseReply;
    MessageOption reUseOption;
    auto reUseAns = renderDelegate->OnRemoteRequest(reUseCode, reUseData, reUseReply, reUseOption);
    EXPECT_EQ(reUseAns, ERR_INVALID_VALUE);
}

/**
 * @tc.name: FormRenderDelegateImplTest_015
 * @tc.desc: test FormRendererDelegateImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateImplTest, FormRenderDelegateImplTest_015, TestSize.Level1)
{
    auto renderDelegate = SurfaceCreateOnFormRendererDelegateImpl();
    uint64_t surfaceId = 2;
    OHOS::AppExecFwk::FormJsInfo formJsInfo;

    constexpr uint32_t reUseCode = static_cast<uint32_t>(IFormRendererDelegate::Message::ON_SURFACE_REUSE);
    MessageParcel reUseData;
    reUseData.WriteInterfaceToken(FormRendererDelegateImpl::GetDescriptor());
    reUseData.WriteUint64(surfaceId);
    reUseData.WriteParcelable(&formJsInfo);
    MessageParcel reUseReply;
    MessageOption reUseOption;
    auto reUseAns = renderDelegate->OnRemoteRequest(reUseCode, reUseData, reUseReply, reUseOption);
    EXPECT_EQ(reUseAns, ERR_INVALID_VALUE);
}

/**
 * @tc.name: FormRenderDelegateImplTest_016
 * @tc.desc: test FormRendererDelegateImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateImplTest, FormRenderDelegateImplTest_016, TestSize.Level1)
{
    auto renderDelegate = SurfaceCreateOnFormRendererDelegateImpl();
    uint64_t surfaceId = 1;

    constexpr uint32_t detachCode = static_cast<uint32_t>(IFormRendererDelegate::Message::ON_FORMSURFACE_DETACH);
    MessageParcel detachData;
    detachData.WriteInterfaceToken(FormRendererDelegateImpl::GetDescriptor());
    detachData.WriteUint64(surfaceId);
    MessageParcel detachReply;
    MessageOption detachOption;
    auto reUseAns = renderDelegate->OnRemoteRequest(detachCode, detachData, detachReply, detachOption);
    EXPECT_EQ(reUseAns, ERR_OK);
}

/**
 * @tc.name: FormRenderDelegateImplTest_017
 * @tc.desc: test FormRendererDelegateImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateImplTest, FormRenderDelegateImplTest_017, TestSize.Level1)
{
    auto renderDelegate = SurfaceCreateOnFormRendererDelegateImpl();
    uint64_t surfaceId = 1;

    constexpr uint32_t releaseCode = static_cast<uint32_t>(IFormRendererDelegate::Message::ON_SURFACE_RELEASE);
    MessageParcel releaseData;
    releaseData.WriteInterfaceToken(FormRendererDelegateImpl::GetDescriptor());
    releaseData.WriteUint64(surfaceId);
    MessageParcel releaseReply;
    MessageOption releaseOption;
    auto reUseAns = renderDelegate->OnRemoteRequest(releaseCode, releaseData, releaseReply, releaseOption);
    EXPECT_EQ(reUseAns, ERR_OK);
}

/**
 * @tc.name: FormRenderDelegateImplTest_018
 * @tc.desc: test FormRendererDelegateImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateImplTest, FormRenderDelegateImplTest_018, TestSize.Level1)
{
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();

    const std::string action = "just a unittest";
    constexpr uint32_t actionCreateCode = static_cast<uint32_t>(IFormRendererDelegate::Message::ON_ACTION_CREATE);
    MessageParcel actionCreateData;
    actionCreateData.WriteInterfaceToken(FormRendererDelegateImpl::GetDescriptor());
    actionCreateData.WriteString(action);
    MessageParcel actionCreateReply;
    MessageOption actionCreateOption;
    auto reUseAns =
        renderDelegate->OnRemoteRequest(actionCreateCode, actionCreateData, actionCreateReply, actionCreateOption);
    EXPECT_EQ(reUseAns, ERR_OK);
}

/**
 * @tc.name: FormRenderDelegateImplTest_019
 * @tc.desc: test FormRendererDelegateImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateImplTest, FormRenderDelegateImplTest_019, TestSize.Level1)
{
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();

    const std::string code = "code in unittest";
    const std::string msg = "code in unittest";
    constexpr uint32_t errorCode = static_cast<uint32_t>(IFormRendererDelegate::Message::ON_ERROR);
    MessageParcel errorData;
    errorData.WriteInterfaceToken(FormRendererDelegateImpl::GetDescriptor());
    errorData.WriteString(code);
    errorData.WriteString(msg);
    MessageParcel errorReply;
    MessageOption errorOption;
    auto reUseAns = renderDelegate->OnRemoteRequest(errorCode, errorData, errorReply, errorOption);
    EXPECT_EQ(reUseAns, ERR_OK);
}

/**
 * @tc.name: FormRenderDelegateImplTest_020
 * @tc.desc: test FormRendererDelegateImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateImplTest, FormRenderDelegateImplTest_020, TestSize.Level1)
{
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();

    float width = 1.0;
    float height = 1.0;
    float borderWidth = 1.0;
    constexpr uint32_t surfaceChangeCode = static_cast<uint32_t>(IFormRendererDelegate::Message::ON_SURFACE_CHANGE);
    MessageParcel surfaceChangeData;
    surfaceChangeData.WriteInterfaceToken(FormRendererDelegateImpl::GetDescriptor());
    surfaceChangeData.WriteFloat(width);
    surfaceChangeData.WriteFloat(height);
    surfaceChangeData.WriteFloat(borderWidth);
    MessageParcel surfaceChangeReply;
    MessageOption surfaceChangeOption;
    auto reUseAns =
        renderDelegate->OnRemoteRequest(surfaceChangeCode, surfaceChangeData, surfaceChangeReply, surfaceChangeOption);
    EXPECT_EQ(reUseAns, ERR_OK);
}

/**
 * @tc.name: FormRenderDelegateImplTest_021
 * @tc.desc: test FormRendererDelegateImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateImplTest, FormRenderDelegateImplTest_021, TestSize.Level1)
{
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();

    const std::vector<std::string> formLinkInfos;
    constexpr uint32_t linkInfoUpdateChangeCode =
        static_cast<uint32_t>(IFormRendererDelegate::Message::ON_FORM_LINK_INFO_UPDATE);
    MessageParcel linkInfoUpdateData;
    linkInfoUpdateData.WriteInterfaceToken(FormRendererDelegateImpl::GetDescriptor());
    linkInfoUpdateData.WriteStringVector(formLinkInfos);
    MessageParcel linkInfoUpdateReply;
    MessageOption linkInfoUpdateOption;
    auto reUseAns = renderDelegate->OnRemoteRequest(
        linkInfoUpdateChangeCode, linkInfoUpdateData, linkInfoUpdateReply, linkInfoUpdateOption);
    EXPECT_EQ(reUseAns, ERR_OK);
}

/**
 * @tc.name: FormRenderDelegateImplTest_022
 * @tc.desc: test FormRendererDelegateImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderDelegateImplTest, FormRenderDelegateImplTest_022, TestSize.Level1)
{
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();

    constexpr uint32_t getRectCode =
        static_cast<uint32_t>(IFormRendererDelegate::Message::ON_GET_RECT_RELATIVE_TO_WINDOW);
    MessageParcel getRectData;
    getRectData.WriteInterfaceToken(FormRendererDelegateImpl::GetDescriptor());
    MessageParcel getRectReply;
    MessageOption getRectOption;
    auto reUseAns = renderDelegate->OnRemoteRequest(getRectCode, getRectData, getRectReply, getRectOption);
    EXPECT_EQ(reUseAns, ERR_OK);
}

}
