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
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

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
        NG::MockPipelineBase::SetUp();
    }

    static void TearDownTestCase()
    {
        NG::MockPipelineBase::TearDown();
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
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), Initialize(An<OHOS::Rosen::Window*>(), _, _))
        .WillOnce(Return());
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
    auto onSurfaceChange = [&onSurfaceChangeEventKey](
                               float /* width */, float /* height */) { onSurfaceChangeEventKey = CHECK_KEY; };
    renderDelegate->SetSurfaceChangeEventHandler(std::move(onSurfaceChange));

    /**
     * @tc.steps: step3. call formRenderer's AddForm
     * @tc.expected: step3. onSurfaceCreate has been called
     */
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), SetFormWidth(_)).WillOnce(Return());
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), SetFormHeight(_)).WillOnce(Return());
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), UpdateFormSharedImage(_)).WillOnce(Return());
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), UpdateFormData(_)).WillOnce(Return());
    EXPECT_CALL(*((MockUIContent*)(formRenderer->uiContent_.get())), Initialize(An<OHOS::Rosen::Window*>(), _, _))
        .WillOnce(Return());
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
    formRendererDispatcher->DispatchPointerEvent(event);
    std::this_thread::sleep_for(std::chrono::seconds(1));
}
} // namespace OHOS::Ace
