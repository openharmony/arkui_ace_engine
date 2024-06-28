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

#include <thread>
#include <chrono>
#include "gtest/gtest.h"
#include "test/mock/interfaces/mock_uicontent.h"
#include "ui_content.h"

#define private public
#include "interfaces/inner_api/form_render/include/form_renderer.h"
#include "interfaces/inner_api/form_render/include/form_renderer_delegate_impl.h"
#include "interfaces/inner_api/form_render/include/form_renderer_group.h"
#include "interfaces/inner_api/ace/serialized_gesture.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
constexpr char FORM_RENDERER_ALLOW_UPDATE[] = "allowUpdate";
constexpr char FORM_RENDERER_COMP_ID[] = "ohos.extra.param.key.form_comp_id";
constexpr char FORM_WIDTH_KEY[] = "ohos.extra.param.key.form_width";
constexpr char FORM_HEIGHT_KEY[] = "ohos.extra.param.key.form_height";
constexpr char FORM_RENDERER_PROCESS_ON_ADD_SURFACE[] = "ohos.extra.param.key.process_on_add_surface";
constexpr char FORM_RENDER_STATE[] = "ohos.extra.param.key.form_render_state";
constexpr const char* FORM_STATUS_DATA = "form_status_data";
const std::string FORM_COMPONENT_ID_1 = "111111";
const std::string FORM_COMPONENT_ID_2 = "222222";
const std::string FORM_COMPONENT_ID_3 = "333333";
const std::string CHECK_KEY = "CHECK_KEY";
constexpr double FORM_WIDTH = 100.0f;
constexpr double FORM_HEIGHT = 100.0f;
constexpr double FORM_WIDTH_2 = 200.0f;
constexpr double FORM_HEIGHT_2 = 200.0f;
} // namespace
class FormRenderTest : public testing::Test {
public:
    static void SetUpTestCase()
    {
        NG::MockPipelineContext::SetUp();
    }

    static void TearDownTestCase()
    {
        NG::MockPipelineContext::TearDown();
    }

    sptr<FormRendererDispatcherImpl> GetFormRendererDispatcherImpl()
    {
        std::shared_ptr<UIContent> uiContent = UIContent::Create(nullptr, nullptr);
        EXPECT_CALL(*((MockUIContent*)(uiContent.get())), ProcessPointerEvent(_)).WillRepeatedly(Return(true));
        std::shared_ptr<FormRenderer> formRenderer = nullptr;
        auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("GetFormRendererDispatcherImpl");
        auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
        sptr<FormRendererDispatcherImpl> renderDispatcher =
            new FormRendererDispatcherImpl(uiContent, formRenderer, eventHandler);
        return renderDispatcher;
    }

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

/**
 * @tc.name: FormRenderTest001
 * @tc.desc: test AddForm -> UpdateForm -> ReloadForm -> DeleteForm(comp_id) -> DeleteForm
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create formRenderGroup and prepare want
     * @tc.expected: step1. formRenderGroup is created successfully
     */
    std::weak_ptr<OHOS::AppExecFwk::EventHandler> emptyHandler;
    auto formRendererGroup = FormRendererGroup::Create(nullptr, nullptr, emptyHandler);
    EXPECT_TRUE(formRendererGroup);
    bool isEmpty = formRendererGroup->IsFormRequestsEmpty();
    EXPECT_TRUE(isEmpty);
    OHOS::AAFwk::Want want;
    want.SetParam(FORM_WIDTH_KEY, FORM_WIDTH);
    want.SetParam(FORM_HEIGHT_KEY, FORM_HEIGHT);
    want.SetParam(FORM_RENDERER_COMP_ID, FORM_COMPONENT_ID_1);
    want.SetParam(FORM_RENDERER_ALLOW_UPDATE, true);
    want.SetParam(FORM_RENDER_STATE, true);
    OHOS::AppExecFwk::FormJsInfo formJsInfo;

    /**
     * @tc.steps: step2. call AddForm
     * @tc.expected: step2. formRenderer is created successfully and added to the formRendererGroup
     */
    // formRenderer->uiContent_ is null, so formRenderer->AddForm will not be called
    formRendererGroup->AddForm(want, formJsInfo);
    EXPECT_TRUE(formRendererGroup->formRenderer_ != nullptr);
    isEmpty = formRendererGroup->IsFormRequestsEmpty();
    formRendererGroup->UpdateConfiguration(nullptr);
    EXPECT_FALSE(isEmpty);


    /**
     * @tc.steps: step3. call formRenderer's AddForm
     * @tc.expected: step3. uiContent's relevant methods are called & formRenderer's property are set
     */
    auto formRenderer = formRendererGroup->formRenderer_;
    EXPECT_TRUE(formRenderer);
    formRenderer->uiContent_ = UIContent::Create(nullptr, nullptr);
    EXPECT_TRUE(formRenderer->uiContent_);
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), SetFormWidth(FORM_WIDTH)).WillOnce(Return());
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), SetFormHeight(FORM_HEIGHT)).WillOnce(Return());
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), UpdateFormSharedImage(_)).WillOnce(Return());
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), UpdateFormData(_)).WillOnce(Return());

    EXPECT_CALL(*((MockUIContent *)(formRenderer->uiContent_.get())),
        PreInitializeForm(An<OHOS::Rosen::Window *>(), "", _)).WillOnce(Return());
    EXPECT_CALL(*((MockUIContent *)(formRenderer->uiContent_.get())), RunFormPage()).Times(Exactly(1));

    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), SetActionEventHandler(_)).WillOnce(Return());
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), SetErrorEventHandler(_)).WillOnce(Return());
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), GetFormRootNode()).Times(Exactly(2));
    // call AddForm manually
    formRenderer->AddForm(want, formJsInfo);
    EXPECT_EQ(formRenderer->allowUpdate_, true);
    EXPECT_EQ(formRenderer->width_, FORM_WIDTH);
    EXPECT_EQ(formRenderer->height_, FORM_HEIGHT);

    /**
     * @tc.steps: step4. add another formRenderer
     * @tc.expected: step4. the formRenderer is created successfully and added to the formRendererGroup
     */
    OHOS::AAFwk::Want want2;
    want2.SetParam(FORM_WIDTH_KEY, FORM_WIDTH);
    want2.SetParam(FORM_HEIGHT_KEY, FORM_HEIGHT);
    want2.SetParam(FORM_RENDERER_COMP_ID, FORM_COMPONENT_ID_2);
    want2.SetParam(FORM_RENDERER_ALLOW_UPDATE, true);
    want2.SetParam(FORM_RENDER_STATE, true);
    formRendererGroup->AddForm(want2, formJsInfo);
    auto formRenderer2 = formRendererGroup->formRenderer_;
    formRenderer2->OnActionEvent("");
    formRenderer2->OnError("", "");
    formRenderer2->OnSurfaceChange(0.0f, 0.0f);

    /**
     * @tc.steps: step5. call formRenderer's UpdateForm
     * @tc.expected: step5. uiContent's relevant methods are called
     */
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), UpdateFormSharedImage(_)).WillOnce(Return());
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), UpdateFormData(_)).WillOnce(Return());
    formRendererGroup->UpdateForm(formJsInfo);

    /**
     * @tc.steps: step6. call formRenderer's ReloadForm
     * @tc.expected: step6. uiContent's relevant methods are called
     */
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), ReloadForm(_)).WillOnce(Return());
    formRendererGroup->ReloadForm(formJsInfo);

    /**
     * @tc.steps: step7. delete formRenderer whose compId not exists
     * @tc.expected: step7. delete fail
     */
    formRendererGroup->DeleteForm(FORM_COMPONENT_ID_3);

    /**
     * @tc.steps: step8. delete formRenderer whose compId exists
     * @tc.expected: step8. delete successfully
     */
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), Destroy()).WillOnce(Return());
    // delete formRenderer that compId exists
    formRendererGroup->DeleteForm(FORM_COMPONENT_ID_1);

    /**
     * @tc.steps: step9. delete all formRenderers
     * @tc.expected: step9. delete successfully
     */
    formRendererGroup->DeleteForm();
}

/**
 * @tc.name: FormRenderTest002
 * @tc.desc: delegate & dispatcher is not null
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create formRenderGroup and add new formRenderer with delegate & dispatcher
     * @tc.expected: step1. formRenderGroup is created successfully and the formRenderer is added to the
     * formRendererGroup
     */
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("formRenderTest002");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto formRendererGroup = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    EXPECT_TRUE(formRendererGroup);
    OHOS::AAFwk::Want want;
    want.SetParam(FORM_RENDERER_COMP_ID, FORM_COMPONENT_ID_1);
    want.SetParam(FORM_RENDERER_ALLOW_UPDATE, false);
    want.SetParam(FORM_RENDER_STATE, true);
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();
    want.SetParam(FORM_RENDERER_PROCESS_ON_ADD_SURFACE, renderDelegate->AsObject());
    OHOS::AppExecFwk::FormJsInfo formJsInfo;
    formRendererGroup->AddForm(want, formJsInfo);
    auto formRenderer = formRendererGroup->formRenderer_;;
    EXPECT_TRUE(formRenderer);
    formRenderer->uiContent_ = UIContent::Create(nullptr, nullptr);
    EXPECT_TRUE(formRenderer->uiContent_);

    /**
     * @tc.steps: step2. register callback for rendererDelegate
     */
    std::string onSurfaceCreateKey;
    auto onSurfaceCreate = [&onSurfaceCreateKey](const std::shared_ptr<Rosen::RSSurfaceNode>& /* surfaceNode */,
                               const OHOS::AppExecFwk::FormJsInfo& /* info */,
                               const AAFwk::Want& /* want */) { onSurfaceCreateKey = CHECK_KEY; };
    renderDelegate->SetSurfaceCreateEventHandler(std::move(onSurfaceCreate));

    std::string onActionEventKey;
    auto onAction = [&onActionEventKey](const std::string& /* action */) { onActionEventKey = CHECK_KEY; };
    renderDelegate->SetActionEventHandler(std::move(onAction));

    std::string onErrorEventKey;
    auto onError = [&onErrorEventKey](
                       const std::string& /* code */, const std::string& /* msg */) { onErrorEventKey = CHECK_KEY; };
    renderDelegate->SetErrorEventHandler(std::move(onError));

    std::string onSurfaceChangeEventKey;
    auto onSurfaceChange = [&onSurfaceChangeEventKey](float /* width */,
                        float /* height */, float /* borderWidth */) { onSurfaceChangeEventKey = CHECK_KEY; };
    renderDelegate->SetSurfaceChangeEventHandler(std::move(onSurfaceChange));

    /**
     * @tc.steps: step3. call formRenderer's AddForm
     * @tc.expected: step3. onSurfaceCreate has been called
     */
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), SetFormWidth(_)).WillOnce(Return());
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), SetFormHeight(_)).WillOnce(Return());
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), UpdateFormSharedImage(_)).WillOnce(Return());
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), UpdateFormData(_)).WillOnce(Return());

    EXPECT_CALL(*((MockUIContent *)(formRenderer->uiContent_.get())),
        PreInitializeForm(An<OHOS::Rosen::Window *>(), "", _)).WillOnce(Return());
    EXPECT_CALL(*((MockUIContent *)(formRenderer->uiContent_.get())), RunFormPage()).Times(Exactly(1));

    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), SetActionEventHandler(_)).WillOnce(Return());
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), SetErrorEventHandler(_)).WillOnce(Return());
    std::string surfaceNodeName = "ArkTSCardNode";
    struct Rosen::RSSurfaceNodeConfig surfaceNodeConfig = { .SurfaceNodeName = surfaceNodeName };
    std::shared_ptr<Rosen::RSSurfaceNode> rsNode = OHOS::Rosen::RSSurfaceNode::Create(surfaceNodeConfig, true);
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), GetFormRootNode())
        .WillOnce(Return(rsNode))
        .WillOnce(Return(rsNode))
        .WillOnce(Return(rsNode));
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), Foreground()).WillOnce(Return());
    formRenderer->AddForm(want, formJsInfo);
    EXPECT_EQ(onSurfaceCreateKey, CHECK_KEY);

    /**
     * @tc.steps: step4. call formRenderer's OnActionEvent & OnErrorEvent
     * @tc.expected: step4. onAction & onError have been called
     */
    formRenderer->OnActionEvent("");
    EXPECT_EQ(onActionEventKey, CHECK_KEY);
    formRenderer->OnError("", "");
    EXPECT_EQ(onErrorEventKey, CHECK_KEY);

    /**
     * @tc.steps: step5. Test surface change
     * @tc.expected: step5. onSurfaceChange & uiContent.OnFormSurfaceChange has been called
     */
    auto formRendererDispatcher = formRenderer->formRendererDispatcherImpl_;
    EXPECT_TRUE(formRendererDispatcher);
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), SetFormWidth(FORM_WIDTH_2)).WillOnce(Return());
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), SetFormHeight(FORM_HEIGHT_2)).WillOnce(Return());
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), OnFormSurfaceChange(FORM_WIDTH_2, FORM_HEIGHT_2))
        .WillOnce(Return());
    formRendererDispatcher->DispatchSurfaceChangeEvent(FORM_WIDTH_2, FORM_HEIGHT_2);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    EXPECT_EQ(onSurfaceChangeEventKey, CHECK_KEY);
    // formRenderer is null
    formRendererDispatcher->formRenderer_.reset();
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), SetFormWidth(FORM_WIDTH_2)).WillOnce(Return());
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), SetFormHeight(FORM_HEIGHT_2)).WillOnce(Return());
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), OnFormSurfaceChange(FORM_WIDTH_2, FORM_HEIGHT_2))
        .WillOnce(Return());
    onSurfaceChangeEventKey = "";
    formRendererDispatcher->DispatchSurfaceChangeEvent(FORM_WIDTH_2, FORM_HEIGHT_2);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    EXPECT_NE(onSurfaceChangeEventKey, CHECK_KEY);

    /**
     * @tc.steps: step6. Test pointer event
     * @tc.expected: step4. uiContent.ProcessPointerEvent has been called
     */
    std::shared_ptr<OHOS::MMI::PointerEvent> event;
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), ProcessPointerEvent(event))
        .WillOnce(Return(true));
    SerializedGesture serializedGesture;
    formRendererDispatcher->DispatchPointerEvent(event, serializedGesture);
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

/**
 * @tc.name: FormRenderTest003
 * @tc.type: FUNC
 * Function: OnActionEvent,SetActionEventHandler
 **@tc.desc: 1. system running normally
 *           2. test FormRendererDelegateImpl
 */
HWTEST_F(FormRenderTest, FormRenderTest003, TestSize.Level1)
{
    std::string action = "action";
    auto fun = [](const std::string&) {};
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();
    renderDelegate->SetActionEventHandler(nullptr);
    EXPECT_EQ(renderDelegate->OnActionEvent(action), ERR_INVALID_DATA);
    renderDelegate->SetActionEventHandler(fun);
    EXPECT_EQ(renderDelegate->OnActionEvent(action), ERR_OK);
}

/**
 * @tc.name: FormRenderTest004
 * @tc.type: FUNC
 * Function: OnError,SetErrorEventHandler
 **@tc.desc: 1. system running normally
 *           2. test FormRendererDelegateImpl
 */
HWTEST_F(FormRenderTest, FormRenderTest004, TestSize.Level1)
{
    std::string code = "code";
    std::string msg = "msg";
    auto fun = [](const std::string&, const std::string&) {};
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();
    renderDelegate->SetErrorEventHandler(nullptr);
    EXPECT_EQ(renderDelegate->OnError(code, msg), ERR_INVALID_DATA);
    renderDelegate->SetErrorEventHandler(fun);
    EXPECT_EQ(renderDelegate->OnError(code, msg), ERR_OK);
}

/**
 * @tc.name: FormRenderTest005
 * @tc.type: FUNC
 * Function: OnSurfaceChange,SetSurfaceChangeEventHandler
 **@tc.desc: 1. system running normally
 *           2. test FormRendererDelegateImpl
 */
HWTEST_F(FormRenderTest, FormRenderTest005, TestSize.Level1)
{
    float width = 1.1;
    float height = 2.2;
    auto fun = [](float, float, float) {};
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();
    renderDelegate->SetSurfaceChangeEventHandler(nullptr);
    EXPECT_EQ(renderDelegate->OnSurfaceChange(width, height), ERR_INVALID_DATA);
    renderDelegate->SetSurfaceChangeEventHandler(fun);
    EXPECT_EQ(renderDelegate->OnSurfaceChange(width, height), ERR_OK);
}

/**
 * @tc.name: FormRenderTest006
 * @tc.type: FUNC
 * Function: OnSurfaceDetach,SetSurfaceDetachEventHandler
 **@tc.desc: 1. system running normally
 *           2. test FormRendererDelegateImpl
 */
HWTEST_F(FormRenderTest, FormRenderTest006, TestSize.Level1)
{
    uint64_t surfaceId = 1;
    auto fun = []() {};
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();
    renderDelegate->SetSurfaceDetachEventHandler(nullptr);
    EXPECT_EQ(renderDelegate->OnSurfaceDetach(surfaceId), ERR_INVALID_DATA);
    renderDelegate->SetSurfaceDetachEventHandler(fun);
    EXPECT_EQ(renderDelegate->OnSurfaceDetach(surfaceId), ERR_OK);
}

/**
 * @tc.name: FormRenderTest007
 * @tc.type: FUNC
 * Function: OnFormLinkInfoUpdate,SetFormLinkInfoUpdateHandler
 **@tc.desc: 1. system running normally
 *           2. test FormRendererDelegateImpl
 */
HWTEST_F(FormRenderTest, FormRenderTest007, TestSize.Level1)
{
    std::vector<std::string> formLinkInfos;
    auto fun = [](const std::vector<std::string>&) {};
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();
    renderDelegate->SetFormLinkInfoUpdateHandler(nullptr);
    EXPECT_EQ(renderDelegate->OnFormLinkInfoUpdate(formLinkInfos), ERR_INVALID_DATA);
    renderDelegate->SetFormLinkInfoUpdateHandler(fun);
    EXPECT_EQ(renderDelegate->OnFormLinkInfoUpdate(formLinkInfos), ERR_OK);
}

/**
 * @tc.name: FormRenderTest008
 * @tc.type: FUNC
 * Function: OnGetRectRelativeToWindow,SetGetRectRelativeToWindowHandler
 **@tc.desc: 1. system running normally
 *           2. test FormRendererDelegateImpl
 */
HWTEST_F(FormRenderTest, FormRenderTest008, TestSize.Level1)
{
    int32_t top = 50;
    int32_t left = 50;
    auto fun = [](int32_t&, int32_t&) {};
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();
    renderDelegate->SetGetRectRelativeToWindowHandler(nullptr);
    EXPECT_EQ(renderDelegate->OnGetRectRelativeToWindow(top, left), ERR_INVALID_DATA);
    renderDelegate->SetGetRectRelativeToWindowHandler(fun);
    EXPECT_EQ(renderDelegate->OnGetRectRelativeToWindow(top, left), ERR_OK);
}

/**
 * @tc.name: FormRenderTest010
 * @tc.desc: test RunFormPage
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest010, TestSize.Level1)
{
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("formRenderTest010");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto formRendererGroup = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    EXPECT_TRUE(formRendererGroup);
    OHOS::AAFwk::Want want;
    want.SetParam(FORM_RENDERER_COMP_ID, FORM_COMPONENT_ID_1);
    want.SetParam(FORM_RENDERER_ALLOW_UPDATE, false);
    want.SetParam(FORM_RENDER_STATE, true);
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();
    want.SetParam(FORM_RENDERER_PROCESS_ON_ADD_SURFACE, renderDelegate->AsObject());
    OHOS::AppExecFwk::FormJsInfo formJsInfo;
    formRendererGroup->AddForm(want, formJsInfo);
    auto formRenderer = formRendererGroup->formRenderer_;;
    EXPECT_TRUE(formRenderer);
    formRenderer->RunFormPage(want, formJsInfo);
    formRenderer->uiContent_ = UIContent::Create(nullptr, nullptr);
    EXPECT_TRUE(formRenderer->uiContent_);
    formRenderer->RunFormPage(want, formJsInfo);
    want.SetParam(FORM_STATUS_DATA, true);
    formRenderer->RunFormPage(want, formJsInfo);
}

/**
 * @tc.name: FormRenderTest011
 * @tc.desc: test OnFormLinkInfoUpdate
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest011, TestSize.Level1)
{
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("formRenderTest011");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto formRendererGroup = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    EXPECT_TRUE(formRendererGroup);
    OHOS::AAFwk::Want want;
    want.SetParam(FORM_RENDERER_COMP_ID, FORM_COMPONENT_ID_1);
    want.SetParam(FORM_RENDERER_ALLOW_UPDATE, false);
    want.SetParam(FORM_RENDER_STATE, true);
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();
    want.SetParam(FORM_RENDERER_PROCESS_ON_ADD_SURFACE, renderDelegate->AsObject());
    OHOS::AppExecFwk::FormJsInfo formJsInfo;
    formRendererGroup->AddForm(want, formJsInfo);
    auto formRenderer = formRendererGroup->formRenderer_;
    EXPECT_TRUE(formRenderer);
    formRenderer->uiContent_ = UIContent::Create(nullptr, nullptr);
    EXPECT_TRUE(formRenderer->uiContent_);
    std::vector<std::string> cachedInfos = formRenderer->cachedInfos_;
    formRenderer->OnFormLinkInfoUpdate(cachedInfos);
    formRenderer->formRendererDelegate_ = renderDelegate;
    EXPECT_TRUE(formRenderer->formRendererDelegate_);
    formRenderer->OnFormLinkInfoUpdate(cachedInfos);
}

/**
 * @tc.name: FormRenderTest012
 * @tc.desc: test ResetRenderDelegate
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest012, TestSize.Level1)
{
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("formRenderTest012");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto formRendererGroup = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    EXPECT_TRUE(formRendererGroup);
    OHOS::AAFwk::Want want;
    want.SetParam(FORM_RENDERER_COMP_ID, FORM_COMPONENT_ID_1);
    want.SetParam(FORM_RENDERER_ALLOW_UPDATE, false);
    want.SetParam(FORM_RENDER_STATE, true);
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();
    want.SetParam(FORM_RENDERER_PROCESS_ON_ADD_SURFACE, renderDelegate->AsObject());
    OHOS::AppExecFwk::FormJsInfo formJsInfo;
    formRendererGroup->AddForm(want, formJsInfo);
    auto formRenderer = formRendererGroup->formRenderer_;
    EXPECT_TRUE(formRenderer);
    formRenderer->uiContent_ = UIContent::Create(nullptr, nullptr);
    EXPECT_TRUE(formRenderer->uiContent_);
    formRenderer->ResetRenderDelegate();
}

/**
 * @tc.name: FormRenderTest013
 * @tc.desc: test UpdateConfiguration
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest013, TestSize.Level1)
{
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("formRenderTest013");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto formRendererGroup = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    EXPECT_TRUE(formRendererGroup);
    OHOS::AAFwk::Want want;
    want.SetParam(FORM_RENDERER_COMP_ID, FORM_COMPONENT_ID_1);
    want.SetParam(FORM_RENDERER_ALLOW_UPDATE, false);
    want.SetParam(FORM_RENDER_STATE, true);
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();
    want.SetParam(FORM_RENDERER_PROCESS_ON_ADD_SURFACE, renderDelegate->AsObject());
    OHOS::AppExecFwk::FormJsInfo formJsInfo;
    formRendererGroup->AddForm(want, formJsInfo);
    auto formRenderer = formRendererGroup->formRenderer_;
    EXPECT_TRUE(formRenderer);
    formRenderer->uiContent_ = UIContent::Create(nullptr, nullptr);
    EXPECT_TRUE(formRenderer->uiContent_);
    formRenderer->UpdateConfiguration(nullptr);
}

/**
 * @tc.name: FormRenderTest014
 * @tc.desc: test OnRemoteDied
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest014, TestSize.Level1)
{
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("formRenderTest014");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto formRendererGroup = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    EXPECT_TRUE(formRendererGroup);
    OHOS::AAFwk::Want want;
    want.SetParam(FORM_RENDERER_COMP_ID, FORM_COMPONENT_ID_1);
    want.SetParam(FORM_RENDERER_ALLOW_UPDATE, false);
    want.SetParam(FORM_RENDER_STATE, true);
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();
    want.SetParam(FORM_RENDERER_PROCESS_ON_ADD_SURFACE, renderDelegate->AsObject());
    OHOS::AppExecFwk::FormJsInfo formJsInfo;
    formRendererGroup->AddForm(want, formJsInfo);
    auto formRenderer = formRendererGroup->formRenderer_;
    EXPECT_TRUE(formRenderer);
    formRenderer->uiContent_ = UIContent::Create(nullptr, nullptr);
    EXPECT_TRUE(formRenderer->uiContent_);
    FormRenderDelegateRecipient::RemoteDiedHandler handler = [](){};
    auto formRenderDelegateRecipient = new FormRenderDelegateRecipient(handler);
    formRenderDelegateRecipient->OnRemoteDied(nullptr);
    formRenderDelegateRecipient->OnRemoteDied(renderDelegate->AsObject());
}

/**
 * @tc.name: FormRenderTest015
 * @tc.desc: test GetRectRelativeToWindow
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest015, TestSize.Level1)
{
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("formRenderTest015");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto formRendererGroup = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    EXPECT_TRUE(formRendererGroup);
    OHOS::AAFwk::Want want;
    want.SetParam(FORM_RENDERER_COMP_ID, FORM_COMPONENT_ID_1);
    want.SetParam(FORM_RENDERER_ALLOW_UPDATE, false);
    want.SetParam(FORM_RENDER_STATE, true);
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();
    want.SetParam(FORM_RENDERER_PROCESS_ON_ADD_SURFACE, renderDelegate->AsObject());
    OHOS::AppExecFwk::FormJsInfo formJsInfo;
    formRendererGroup->AddForm(want, formJsInfo);
    auto formRenderer = formRendererGroup->formRenderer_;
    EXPECT_TRUE(formRenderer);
    formRenderer->uiContent_ = UIContent::Create(nullptr, nullptr);
    EXPECT_TRUE(formRenderer->uiContent_);
    int32_t top = 0;
    int32_t left = 0;
    formRenderer->GetRectRelativeToWindow(top, left);
    formRenderer->formRendererDelegate_ = renderDelegate;
    EXPECT_TRUE(formRenderer->formRendererDelegate_);
    formRenderer->GetRectRelativeToWindow(top, left);
}

/**
 * @tc.name: FormRenderTest016
 * @tc.desc: test RecycleForm
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest016, TestSize.Level1)
{
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("formRenderTest016");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto formRendererGroup = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    EXPECT_TRUE(formRendererGroup);
    OHOS::AAFwk::Want want;
    want.SetParam(FORM_RENDERER_COMP_ID, FORM_COMPONENT_ID_1);
    want.SetParam(FORM_RENDERER_ALLOW_UPDATE, false);
    want.SetParam(FORM_RENDER_STATE, true);
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();
    want.SetParam(FORM_RENDERER_PROCESS_ON_ADD_SURFACE, renderDelegate->AsObject());
    OHOS::AppExecFwk::FormJsInfo formJsInfo;
    formRendererGroup->AddForm(want, formJsInfo);
    auto formRenderer = formRendererGroup->formRenderer_;
    EXPECT_TRUE(formRenderer);
    std::string statusData;
    formRenderer->RecycleForm(statusData);
    formRenderer->uiContent_ = UIContent::Create(nullptr, nullptr);
    EXPECT_TRUE(formRenderer->uiContent_);
    formRenderer->RecycleForm(statusData);
}

/**
 * @tc.name: FormRenderTest017
 * @tc.desc: test RecoverForm
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest017, TestSize.Level1)
{
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("formRenderTest017");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto formRendererGroup = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    EXPECT_TRUE(formRendererGroup);
    OHOS::AAFwk::Want want;
    want.SetParam(FORM_RENDERER_COMP_ID, FORM_COMPONENT_ID_1);
    want.SetParam(FORM_RENDERER_ALLOW_UPDATE, false);
    want.SetParam(FORM_RENDER_STATE, true);
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();
    want.SetParam(FORM_RENDERER_PROCESS_ON_ADD_SURFACE, renderDelegate->AsObject());
    OHOS::AppExecFwk::FormJsInfo formJsInfo;
    formRendererGroup->AddForm(want, formJsInfo);
    auto formRenderer = formRendererGroup->formRenderer_;
    EXPECT_TRUE(formRenderer);
    const std::string statusData = "";
    formRenderer->RecoverForm(statusData);
    formRenderer->uiContent_ = UIContent::Create(nullptr, nullptr);
    EXPECT_TRUE(formRenderer->uiContent_);
    formRenderer->RecoverForm(statusData);
}

/**
 * @tc.name: FormRenderTest018
 * @tc.type: FUNC
 * Function: DispatchPointerEvent
 **@tc.desc: 1. system running normally
 *           2. test FormRendererDispatcherImpl
 */
HWTEST_F(FormRenderTest, FormRenderTest018, TestSize.Level1)
{
    std::shared_ptr<UIContent> uiContent = UIContent::Create(nullptr, nullptr);
    std::shared_ptr<FormRenderer> formRenderer = nullptr;
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("FormRenderTest018");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    sptr<FormRendererDispatcherImpl> renderDispatcher = new FormRendererDispatcherImpl(uiContent,
        formRenderer, eventHandler);
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
 * @tc.name: FormRenderTest019
 * @tc.type: FUNC
 * Function: DispatchPointerEvent
 **@tc.desc: 1. system running normally
 *           2. test FormRendererDispatcherImpl
 */
HWTEST_F(FormRenderTest, FormRenderTest019, TestSize.Level1)
{
    std::shared_ptr<UIContent> uiContent = nullptr;
    std::shared_ptr<FormRenderer> formRenderer = nullptr;
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("FormRenderTest019");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    sptr<FormRendererDispatcherImpl> renderDispatcher = new FormRendererDispatcherImpl(uiContent,
        formRenderer, eventHandler);
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
 * @tc.name: FormRenderTest020
 * @tc.type: FUNC
 * Function: DispatchPointerEvent
 **@tc.desc: 1. system running normally
 *           2. test FormRendererDispatcherImpl
 */
HWTEST_F(FormRenderTest, FormRenderTest020, TestSize.Level1)
{
    std::shared_ptr<UIContent> uiContent = UIContent::Create(nullptr, nullptr);
    std::shared_ptr<FormRenderer> formRenderer = nullptr;
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("FormRenderTest020");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    sptr<FormRendererDispatcherImpl> renderDispatcher = new FormRendererDispatcherImpl(uiContent,
        formRenderer, eventHandler);
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
 * @tc.name: FormRenderTest021
 * @tc.type: FUNC
 * Function: DispatchPointerEvent
 **@tc.desc: 1. system running normally
 *           2. test FormRendererDispatcherImpl
 */
HWTEST_F(FormRenderTest, FormRenderTest021, TestSize.Level1)
{
    std::shared_ptr<UIContent> uiContent = nullptr;
    std::shared_ptr<FormRenderer> formRenderer = nullptr;
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("FormRenderTest021");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    sptr<FormRendererDispatcherImpl> renderDispatcher = new FormRendererDispatcherImpl(uiContent,
        formRenderer, eventHandler);
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
 * @tc.name: FormRenderTest022
 * @tc.type: FUNC
 * Function: SetObscured
 **@tc.desc: 1. system running normally
 *           2. test FormRendererDispatcherImpl
 */
HWTEST_F(FormRenderTest, FormRenderTest022, TestSize.Level1)
{
    // const std::shared_ptr<UIContent> uiContent = nullptr;
    std::shared_ptr<UIContent> uiContent = UIContent::Create(nullptr, nullptr);
    std::shared_ptr<FormRenderer> formRenderer = nullptr;
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("FormRenderTest022");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    sptr<FormRendererDispatcherImpl> renderDispatcher = new FormRendererDispatcherImpl(uiContent,
        formRenderer, eventHandler);
    bool flag = false;
    if (renderDispatcher != nullptr) {
        renderDispatcher->SetObscured(true);
        flag = true;
    }
    EXPECT_TRUE(flag);
}

/**
 * @tc.name: FormRenderTest023
 * @tc.type: FUNC
 * Function: OnAccessibilityChildTreeRegister
 **@tc.desc: 1. system running normally
 *           2. test FormRendererDispatcherImpl
 */
HWTEST_F(FormRenderTest, FormRenderTest023, TestSize.Level1)
{
    std::shared_ptr<UIContent> uiContent = UIContent::Create(nullptr, nullptr);
    std::shared_ptr<FormRenderer> formRenderer = nullptr;
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("FormRenderTest023");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    sptr<FormRendererDispatcherImpl> renderDispatcher = new FormRendererDispatcherImpl(uiContent,
        formRenderer, eventHandler);
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
 * @tc.name: FormRenderTest024
 * @tc.type: FUNC
 * Function: OnAccessibilityChildTreeDeregister
 **@tc.desc: 1. system running normally
 *           2. test FormRendererDispatcherImpl
 */
HWTEST_F(FormRenderTest, FormRenderTest024, TestSize.Level1)
{
    std::shared_ptr<UIContent> uiContent = UIContent::Create(nullptr, nullptr);
    std::shared_ptr<FormRenderer> formRenderer = nullptr;
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("FormRenderTest024");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    sptr<FormRendererDispatcherImpl> renderDispatcher = new FormRendererDispatcherImpl(uiContent,
        formRenderer, eventHandler);
    bool flag = false;
    if (renderDispatcher != nullptr) {
        renderDispatcher->OnAccessibilityChildTreeDeregister();
        flag = true;
    }
    EXPECT_TRUE(flag);
}

/**
 * @tc.name: FormRenderTest025
 * @tc.type: FUNC
 * Function: OnAccessibilityDumpChildInfo
 **@tc.desc: 1. system running normally
 *           2. test FormRendererDispatcherImpl
 */
HWTEST_F(FormRenderTest, FormRenderTest025, TestSize.Level1)
{
    std::shared_ptr<UIContent> uiContent = nullptr;
    std::shared_ptr<FormRenderer> formRenderer = nullptr;
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("FormRenderTest025");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    sptr<FormRendererDispatcherImpl> renderDispatcher = new FormRendererDispatcherImpl(uiContent,
        formRenderer, eventHandler);
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
 * @tc.name: FormRenderTest026
 * @tc.type: FUNC
 * Function: OnAccessibilityDumpChildInfo
 **@tc.desc: 1. system running normally
 *           2. test FormRendererDispatcherImpl
 */
HWTEST_F(FormRenderTest, FormRenderTest026, TestSize.Level1)
{
    std::shared_ptr<UIContent> uiContent = UIContent::Create(nullptr, nullptr);
    std::shared_ptr<FormRenderer> formRenderer = nullptr;
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("FormRenderTest026");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    sptr<FormRendererDispatcherImpl> renderDispatcher = new FormRendererDispatcherImpl(uiContent,
        formRenderer, eventHandler);
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
 * @tc.name: FormRenderTest027
 * @tc.type: FUNC
 * Function: OnAccessibilityTransferHoverEvent
 **@tc.desc: 1. system running normally
 *           2. test FormRendererDispatcherImpl
 */
HWTEST_F(FormRenderTest, FormRenderTest027, TestSize.Level1)
{
    std::shared_ptr<UIContent> uiContent = UIContent::Create(nullptr, nullptr);
    std::shared_ptr<FormRenderer> formRenderer = nullptr;
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("FormRenderTest027");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    sptr<FormRendererDispatcherImpl> renderDispatcher = new FormRendererDispatcherImpl(uiContent,
        formRenderer, eventHandler);
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
 * @tc.name: FormRenderTest028
 * @tc.desc: test PreInitAddForm
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest028, TestSize.Level1)
{
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("formRenderTest028");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto formRendererGroup = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    EXPECT_TRUE(formRendererGroup);
    OHOS::AAFwk::Want want;
    want.SetParam(FORM_RENDERER_COMP_ID, FORM_COMPONENT_ID_1);
    want.SetParam(FORM_RENDERER_ALLOW_UPDATE, false);
    want.SetParam(FORM_RENDER_STATE, true);
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();
    want.SetParam(FORM_RENDERER_PROCESS_ON_ADD_SURFACE, renderDelegate->AsObject());
    OHOS::AppExecFwk::FormJsInfo formJsInfo;
    formRendererGroup->AddForm(want, formJsInfo);
    auto formRenderer = formRendererGroup->formRenderer_;
    EXPECT_TRUE(formRenderer);
    formRenderer->PreInitAddForm(want, formJsInfo);
    std::string url = "";
    formRenderer->ReloadForm(url);
    formRenderer->UpdateForm(formJsInfo);
    formRenderer->uiContent_ = UIContent::Create(nullptr, nullptr);
    EXPECT_TRUE(formRenderer->uiContent_);
    formRenderer->PreInitAddForm(want, formJsInfo);
}

/**
 * @tc.name: FormRenderTest029
 * @tc.desc: test AttachForm
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest029, TestSize.Level1)
{
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("formRenderTest029");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto formRendererGroup = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    EXPECT_TRUE(formRendererGroup);
    OHOS::AAFwk::Want want;
    want.SetParam(FORM_RENDERER_COMP_ID, FORM_COMPONENT_ID_1);
    want.SetParam(FORM_RENDERER_ALLOW_UPDATE, false);
    want.SetParam(FORM_RENDER_STATE, true);
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();
    want.SetParam(FORM_RENDERER_PROCESS_ON_ADD_SURFACE, renderDelegate->AsObject());
    OHOS::AppExecFwk::FormJsInfo formJsInfo;
    formRendererGroup->AddForm(want, formJsInfo);
    auto formRenderer = formRendererGroup->formRenderer_;
    EXPECT_TRUE(formRenderer);
    formRenderer->AttachForm(want, formJsInfo);
    formRenderer->uiContent_ = UIContent::Create(nullptr, nullptr);
    EXPECT_TRUE(formRenderer->uiContent_);
    formRenderer->AttachForm(want, formJsInfo);
}

/**
 * @tc.name: FormRenderTest030
 * @tc.desc: test AttachUIContent
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest030, TestSize.Level1)
{
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("formRenderTest030");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto formRendererGroup = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    EXPECT_TRUE(formRendererGroup);
    OHOS::AAFwk::Want want;
    want.SetParam(FORM_RENDERER_COMP_ID, FORM_COMPONENT_ID_1);
    want.SetParam(FORM_RENDERER_ALLOW_UPDATE, false);
    want.SetParam(FORM_RENDER_STATE, true);
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();
    want.SetParam(FORM_RENDERER_PROCESS_ON_ADD_SURFACE, renderDelegate->AsObject());
    OHOS::AppExecFwk::FormJsInfo formJsInfo;
    formRendererGroup->AddForm(want, formJsInfo);
    auto formRenderer = formRendererGroup->formRenderer_;
    EXPECT_TRUE(formRenderer);
    formRenderer->uiContent_ = UIContent::Create(nullptr, nullptr);
    EXPECT_TRUE(formRenderer->uiContent_);
    std::string surfaceNodeName = "ArkTSCardNode";
    struct Rosen::RSSurfaceNodeConfig surfaceNodeConfig = { .SurfaceNodeName = surfaceNodeName };
    std::shared_ptr<Rosen::RSSurfaceNode> rsNode = OHOS::Rosen::RSSurfaceNode::Create(surfaceNodeConfig, true);
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), GetFormRootNode()).WillOnce(Return(rsNode));
    formRenderer->AttachUIContent(want, formJsInfo);
}

/**
 * @tc.name: FormRenderTest031
 * @tc.desc: test OnSurfaceReuse
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest031, TestSize.Level1)
{
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("formRenderTest031");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto formRendererGroup = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    EXPECT_TRUE(formRendererGroup);
    OHOS::AAFwk::Want want;
    want.SetParam(FORM_RENDERER_COMP_ID, FORM_COMPONENT_ID_1);
    want.SetParam(FORM_RENDERER_ALLOW_UPDATE, false);
    want.SetParam(FORM_RENDER_STATE, true);
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();
    want.SetParam(FORM_RENDERER_PROCESS_ON_ADD_SURFACE, renderDelegate->AsObject());
    OHOS::AppExecFwk::FormJsInfo formJsInfo;
    formRendererGroup->AddForm(want, formJsInfo);
    auto formRenderer = formRendererGroup->formRenderer_;
    EXPECT_TRUE(formRenderer);
    formRenderer->uiContent_ = UIContent::Create(nullptr, nullptr);
    EXPECT_TRUE(formRenderer->uiContent_);
    formRenderer->formRendererDispatcherImpl_ =
        new FormRendererDispatcherImpl(formRenderer->uiContent_, nullptr, eventHandler);
    formRenderer->formRendererDelegate_ = renderDelegate;
    formRenderer->OnSurfaceReuse(formJsInfo);
    std::string surfaceNodeName = "ArkTSCardNode";
    struct Rosen::RSSurfaceNodeConfig surfaceNodeConfig = { .SurfaceNodeName = surfaceNodeName };
    std::shared_ptr<Rosen::RSSurfaceNode> rsNode = OHOS::Rosen::RSSurfaceNode::Create(surfaceNodeConfig, true);
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), GetFormRootNode()).Times(Exactly(2))
        .WillOnce(Return(rsNode));
    formRenderer->OnSurfaceReuse(formJsInfo);
}

/**
 * @tc.name: FormRenderTest032
 * @tc.desc: test OnSurfaceDetach
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest032, TestSize.Level1)
{
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("formRenderTest032");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto formRendererGroup = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    EXPECT_TRUE(formRendererGroup);
    OHOS::AAFwk::Want want;
    want.SetParam(FORM_RENDERER_COMP_ID, FORM_COMPONENT_ID_1);
    want.SetParam(FORM_RENDERER_ALLOW_UPDATE, false);
    want.SetParam(FORM_RENDER_STATE, true);
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();
    want.SetParam(FORM_RENDERER_PROCESS_ON_ADD_SURFACE, renderDelegate->AsObject());
    OHOS::AppExecFwk::FormJsInfo formJsInfo;
    formRendererGroup->AddForm(want, formJsInfo);
    auto formRenderer = formRendererGroup->formRenderer_;
    EXPECT_TRUE(formRenderer);
    formRenderer->uiContent_ = UIContent::Create(nullptr, nullptr);
    EXPECT_TRUE(formRenderer->uiContent_);
    formRenderer->formRendererDelegate_ = renderDelegate;
    formRenderer->OnSurfaceDetach();
    std::string surfaceNodeName = "ArkTSCardNode";
    struct Rosen::RSSurfaceNodeConfig surfaceNodeConfig = { .SurfaceNodeName = surfaceNodeName };
    std::shared_ptr<Rosen::RSSurfaceNode> rsNode = OHOS::Rosen::RSSurfaceNode::Create(surfaceNodeConfig, true);
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), GetFormRootNode()).Times(Exactly(2)).
        WillOnce(Return(rsNode));
    formRenderer->OnSurfaceDetach();
}

/**
 * @tc.name: FormRenderTest033
 * @tc.desc: test FormRendererDispatcherImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest033, TestSize.Level1)
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
 * @tc.name: FormRenderTest034
 * @tc.desc: test FormRendererDispatcherImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest034, TestSize.Level1)
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
 * @tc.name: FormRenderTest035
 * @tc.desc: test FormRendererDispatcherImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest035, TestSize.Level1)
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
 * @tc.name: FormRenderTest036
 * @tc.desc: test FormRendererDispatcherImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest036, TestSize.Level1)
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
 * @tc.name: FormRenderTest037
 * @tc.desc: test FormRendererDispatcherImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest037, TestSize.Level1)
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
 * @tc.name: FormRenderTest038
 * @tc.desc: test FormRendererDispatcherImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest038, TestSize.Level1)
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
 * @tc.name: FormRenderTest039
 * @tc.desc: test FormRendererDispatcherImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest039, TestSize.Level1)
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
 * @tc.name: FormRenderTest040
 * @tc.desc: test FormRendererDispatcherImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest040, TestSize.Level1)
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
 * @tc.name: FormRenderTest041
 * @tc.desc: test FormRendererDispatcherImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest041, TestSize.Level1)
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
 * @tc.name: FormRenderTest043
 * @tc.desc: test FormRendererDispatcherImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest042, TestSize.Level1)
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
 * @tc.name: FormRenderTest043
 * @tc.desc: test FormRendererDispatcherImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest043, TestSize.Level1)
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

/**
 * @tc.name: FormRenderTest044
 * @tc.desc: test FormRendererDelegateImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest044, TestSize.Level1)
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
 * @tc.name: FormRenderTest045
 * @tc.desc: test FormRendererDelegateImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest045, TestSize.Level1)
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
 * @tc.name: FormRenderTest046
 * @tc.desc: test FormRendererDelegateImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest046, TestSize.Level1)
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
 * @tc.name: FormRenderTest047
 * @tc.desc: test FormRendererDelegateImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest047, TestSize.Level1)
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
 * @tc.name: FormRenderTest048
 * @tc.desc: test FormRendererDelegateImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest048, TestSize.Level1)
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
 * @tc.name: FormRenderTest049
 * @tc.desc: test FormRendererDelegateImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest049, TestSize.Level1)
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
 * @tc.name: FormRenderTest050
 * @tc.desc: test FormRendererDelegateImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest050, TestSize.Level1)
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
 * @tc.name: FormRenderTest051
 * @tc.desc: test FormRendererDelegateImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest051, TestSize.Level1)
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
 * @tc.name: FormRenderTest052
 * @tc.desc: test FormRendererDelegateImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest052, TestSize.Level1)
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
 * @tc.name: FormRenderTest053
 * @tc.desc: test FormRendererDelegateImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest053, TestSize.Level1)
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
 * @tc.name: FormRenderTest054
 * @tc.desc: test FormRendererDelegateImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest054, TestSize.Level1)
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
 * @tc.name: FormRenderTest055
 * @tc.desc: test FormRendererDelegateImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest055, TestSize.Level1)
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
 * @tc.name: FormRenderTest056
 * @tc.desc: test FormRendererDelegateImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest056, TestSize.Level1)
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
 * @tc.name: FormRenderTest057
 * @tc.desc: test FormRendererDelegateImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest057, TestSize.Level1)
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
 * @tc.name: FormRenderTest058
 * @tc.desc: test FormRendererDelegateImpl OnRemoteRequest event
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest058, TestSize.Level1)
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

} // namespace OHOS::Ace
