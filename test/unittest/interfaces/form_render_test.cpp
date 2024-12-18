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
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), OnFormSurfaceChange(FORM_WIDTH_2, FORM_HEIGHT_2,
        _, _)).WillOnce(Return());
    formRendererDispatcher->DispatchSurfaceChangeEvent(FORM_WIDTH_2, FORM_HEIGHT_2);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    EXPECT_EQ(onSurfaceChangeEventKey, CHECK_KEY);
    // formRenderer is null
    formRendererDispatcher->formRenderer_.reset();
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), SetFormWidth(FORM_WIDTH_2)).WillOnce(Return());
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), SetFormHeight(FORM_HEIGHT_2)).WillOnce(Return());
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), OnFormSurfaceChange(FORM_WIDTH_2, FORM_HEIGHT_2,
        _, _)).WillOnce(Return());
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
    AccessibilityParentRectInfo parentRectInfo;
    parentRectInfo.top = 50;
    parentRectInfo.left = 50;
    auto fun = [](AccessibilityParentRectInfo&) {};
    sptr<FormRendererDelegateImpl> renderDelegate = new FormRendererDelegateImpl();
    renderDelegate->SetGetRectRelativeToWindowHandler(nullptr);
    EXPECT_EQ(renderDelegate->OnGetRectRelativeToWindow(parentRectInfo), ERR_INVALID_DATA);
    renderDelegate->SetGetRectRelativeToWindowHandler(fun);
    EXPECT_EQ(renderDelegate->OnGetRectRelativeToWindow(parentRectInfo), ERR_OK);
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
    AccessibilityParentRectInfo parentRectInfo;
    parentRectInfo.top = 0;
    parentRectInfo.left = 0;
    formRenderer->GetRectRelativeToWindow(parentRectInfo);
    formRenderer->formRendererDelegate_ = renderDelegate;
    EXPECT_TRUE(formRenderer->formRendererDelegate_);
    formRenderer->GetRectRelativeToWindow(parentRectInfo);
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
 * @tc.desc: test PreInitAddForm
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest018, TestSize.Level1)
{
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("formRenderTest018");
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
 * @tc.name: FormRenderTest019
 * @tc.desc: test AttachForm
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest019, TestSize.Level1)
{
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("formRenderTest019");
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
 * @tc.name: FormRenderTest020
 * @tc.desc: test AttachUIContent
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest020, TestSize.Level1)
{
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("formRenderTest020");
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
 * @tc.name: FormRenderTest021
 * @tc.desc: test OnSurfaceReuse
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest021, TestSize.Level1)
{
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("formRenderTest021");
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
 * @tc.name: FormRenderTest022
 * @tc.desc: test OnSurfaceDetach
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderTest, FormRenderTest022, TestSize.Level1)
{
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("formRenderTest022");
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
* @tc.name: FormRenderTest023
* @tc.desc: test SetVisibleChange
* @tc.type: FUNC
*/
HWTEST_F(FormRenderTest, FormRenderTest023, TestSize.Level1)
{
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("formRenderTest023");
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
    formRenderer->SetVisibleChange(true);
    formRenderer->uiContent_ = UIContent::Create(nullptr, nullptr);
    EXPECT_TRUE(formRenderer->uiContent_);
    formRenderer->SetVisibleChange(true);
}

} // namespace OHOS::Ace
