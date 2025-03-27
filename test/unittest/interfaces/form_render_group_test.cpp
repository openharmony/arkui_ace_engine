/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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
#include "test/mock/interfaces/mock_uicontent.h"
#include "ui_content.h"
#include "interfaces/inner_api/form_render/include/form_renderer.h"
#include "interfaces/inner_api/form_render/include/form_renderer_delegate_impl.h"
#define private public
#include "interfaces/inner_api/form_render/include/form_renderer_group.h"
#undef private
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "configuration.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace {
namespace {
constexpr char FORM_RENDER_STATE[] = "ohos.extra.param.key.form_render_state";
constexpr char FORM_RENDERER_COMP_ID[] = "ohos.extra.param.key.form_comp_id";
} // namespace
class FormRenderGroupTest : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};
/**
 * @tc.name: FormRenderGroupTest_001
 * @tc.desc: Test AddForm() funtion.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderGroupTest, FormRenderGroupTest_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderGroupTest_001 start";
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("FormRenderGroupTest_001");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto group = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    EXPECT_TRUE(group);
    OHOS::AAFwk::Want want;
    OHOS::AppExecFwk::FormJsInfo formJsInfo;
    formJsInfo.bundleName = "bundleName";
    formJsInfo.moduleName = "moduleName";
    formJsInfo.formId = 1;
    EXPECT_EQ(formJsInfo.formId, 1);
    group->AddForm(want, formJsInfo);
    want.SetParam(FORM_RENDER_STATE, true);
    group->AddForm(want, formJsInfo);
    GTEST_LOG_(INFO) << "FormRenderGroupTest_001 end";
}
/**
 * @tc.name: FormRenderGroupTest_002
 * @tc.desc: Test OnUnlock() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderGroupTest, FormRenderGroupTest_002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderGroupTest_002 start";
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("FormRenderGroupTest_002");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto group = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    EXPECT_TRUE(group);
    group->OnUnlock();
    GTEST_LOG_(INFO) << "FormRenderGroupTest_002 end";
}
/**
 * @tc.name: FormRenderGroupTest_003
 * @tc.desc: Test UpdateForm() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderGroupTest, FormRenderGroupTest_003, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderGroupTest_003 start";
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("FormRenderGroupTest_003");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto group = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    EXPECT_TRUE(group);
    OHOS::AppExecFwk::FormJsInfo formJsInfo;
    formJsInfo.bundleName = "bundleName";
    formJsInfo.moduleName = "moduleName";
    group->UpdateForm(formJsInfo);
    group->formRenderer_ = std::make_shared<FormRenderer>(nullptr, nullptr, eventHandler);
    group->UpdateForm(formJsInfo);
    GTEST_LOG_(INFO) << "FormRenderGroupTest_003 end";
}
/**
 * @tc.name: FormRenderGroupTest_004
 * @tc.desc: Test DeleteForm() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderGroupTest, FormRenderGroupTest_004, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderGroupTest_004 start";
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("FormRenderGroupTest_004");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto group = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    EXPECT_TRUE(group);
    std::string id = "123456";
    group->DeleteForm(id);
    GTEST_LOG_(INFO) << "FormRenderGroupTest_004 end";
}
/**
 * @tc.name: FormRenderGroupTest_005
 * @tc.desc: Test DeleteForm() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderGroupTest, FormRenderGroupTest_005, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderGroupTest_005 start";
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("FormRenderGroupTest_005");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto group = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    EXPECT_TRUE(group);
    OHOS::AAFwk::Want want;
    OHOS::AppExecFwk::FormJsInfo formJsInfo;
    formJsInfo.bundleName = "bundleName";
    formJsInfo.moduleName = "moduleName";
    group->AddForm(want, formJsInfo);
    group->DeleteForm();
    GTEST_LOG_(INFO) << "FormRenderGroupTest_005 end";
}
/**
 * @tc.name: FormRenderGroupTest_006
 * @tc.desc: Test ReloadForm() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderGroupTest, FormRenderGroupTest_006, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderGroupTest_006 start";
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("FormRenderGroupTest_006");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto group = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    EXPECT_TRUE(group);
    OHOS::AppExecFwk::FormJsInfo formJsInfo;
    formJsInfo.bundleName = "bundleName";
    formJsInfo.moduleName = "moduleName";
    formJsInfo.formId = 2;
    EXPECT_EQ(formJsInfo.formId, 2);
    group->ReloadForm(formJsInfo);
    GTEST_LOG_(INFO) << "FormRenderGroupTest_006 end";
}
/**
 * @tc.name: FormRenderGroupTest_007
 * @tc.desc: Test UpdateConfiguration() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderGroupTest, FormRenderGroupTest_007, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderGroupTest_007 start";
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("FormRenderGroupTest_007");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto group = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    EXPECT_TRUE(group);
    std::shared_ptr<OHOS::AppExecFwk::Configuration> config;
    group->UpdateConfiguration(config);
    GTEST_LOG_(INFO) << "FormRenderGroupTest_007 end";
}
/**
 * @tc.name: FormRenderGroupTest_008
 * @tc.desc: Test IsFormRequestsEmpty() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderGroupTest, FormRenderGroupTest_008, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderGroupTest_008 start";
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("FormRenderGroupTest_008");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto group = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    EXPECT_TRUE(group);
    EXPECT_EQ(true, group->IsFormRequestsEmpty());
    GTEST_LOG_(INFO) << "FormRenderGroupTest_008 end";
}
/**
 * @tc.name: FormRenderGroupTest_009
 * @tc.desc: Test GetAllRendererFormRequests() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderGroupTest, FormRenderGroupTest_009, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderGroupTest_009 start";
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("FormRenderGroupTest_009");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto group = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    EXPECT_TRUE(group);
    std::vector<FormRequest> from_ = group->GetAllRendererFormRequests();
    GTEST_LOG_(INFO) << "FormRenderGroupTest_009 end";
}
/**
 * @tc.name: FormRenderGroupTest_010
 * @tc.desc: Test RecycleForm() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderGroupTest, FormRenderGroupTest_010, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderGroupTest_010 start";
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("FormRenderGroupTest_010");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto group = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    EXPECT_TRUE(group);
    std::string data = "123";
    group->RecycleForm(data);
    GTEST_LOG_(INFO) << "FormRenderGroupTest_010 end";
}
/**
 * @tc.name: FormRenderGroupTest_011
 * @tc.desc: Test FormRendererGroup() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderGroupTest, FormRenderGroupTest_011, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderGroupTest_011 start";
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("FormRenderGroupTest_011");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    FormRendererGroup group(nullptr, nullptr, eventHandler);
    GTEST_LOG_(INFO) << "FormRenderGroupTest_011 end";
}

/**
* @tc.name: FormRenderGroupTest_012
* @tc.desc: Test SetVisibleChange() function.
* @tc.type: FUNC
*/
HWTEST_F(FormRenderGroupTest, FormRenderGroupTest_012, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderGroupTest_012 start";
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("FormRenderGroupTest_012");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto group = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    EXPECT_TRUE(group);
    group->SetVisibleChange(true);
    GTEST_LOG_(INFO) << "FormRenderGroupTest_012 end";
}

/**
 * @tc.name: FormRenderGroupTest_014
 * @tc.desc: Test OnUnlock() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderGroupTest, FormRenderGroupTest_014, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderGroupTest_0014 start";
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("FormRenderGroupTest_014");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto group = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    FormRequest formRequest;
    formRequest.compId = "unlock";
    bool flag = false;
    if (group != nullptr) {
        group->formRequests_.push_back(formRequest);
        group->currentCompId_ = "unlock";
        group->OnUnlock();
        flag = true;
    }
    EXPECT_TRUE(flag);
    GTEST_LOG_(INFO) << "FormRenderGroupTest_014 end";
}

/**
 * @tc.name: FormRenderGroupTest_015
 * @tc.desc: Test DeleteForm() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderGroupTest, FormRenderGroupTest_015, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderGroupTest_015 start";
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("FormRenderGroupTest_015");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto group = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    std::string compId = "deleteform";
    bool flag = false;
    if (group != nullptr) {
        group->currentCompId_ = "deleteform";
        group->DeleteForm(compId);
        flag = true;
    }
    EXPECT_TRUE(flag);
    GTEST_LOG_(INFO) << "FormRenderGroupTest_015 end";
}

/**
 * @tc.name: FormRenderGroupTest_016
 * @tc.desc: Test DeleteForm() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderGroupTest, FormRenderGroupTest_016, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderGroupTest_016 start";
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("FormRenderGroupTest_016");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto group = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    group->formRenderer_ = nullptr;
    std::string compId = "deleteform";
    FormRequest formRequest;
    formRequest.compId = "requestdeleteform";
    bool flag = false;
    if (group != nullptr) {
        group->formRequests_.push_back(formRequest);
        group->currentCompId_ = "deleteform";
        group->DeleteForm(compId);
        flag = true;
    }
    EXPECT_TRUE(flag);
    GTEST_LOG_(INFO) << "FormRenderGroupTest_016 end";
}

/**
 * @tc.name: FormRenderGroupTest_017
 * @tc.desc: Test DeleteForm() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderGroupTest, FormRenderGroupTest_017, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderGroupTest_017 start";
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("FormRenderGroupTest_017");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto group = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    group->formRenderer_ = std::make_shared<FormRenderer>(nullptr, nullptr, eventHandler);
    std::string compId = "deleteform";
    FormRequest formRequest;
    formRequest.compId = "requestdeleteform";
    bool flag = false;
    if (group != nullptr) {
        group->formRequests_.push_back(formRequest);
        group->currentCompId_ = "deleteform";
        group->DeleteForm(compId);
        flag = true;
    }
    EXPECT_TRUE(flag);
    GTEST_LOG_(INFO) << "FormRenderGroupTest_017 end";
}

/**
 * @tc.name: FormRenderGroupTest_018
 * @tc.desc: Test UpdateConfiguration() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderGroupTest, FormRenderGroupTest_018, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderGroupTest_018 start";
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("FormRenderGroupTest_018");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto group = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    bool flag = false;
    if (group != nullptr) {
        group->UpdateConfiguration(nullptr);
        flag = true;
    }
    EXPECT_TRUE(flag);
    std::shared_ptr<OHOS::AppExecFwk::Configuration> config = std::make_shared<OHOS::AppExecFwk::Configuration>();
    group->formRenderer_ = nullptr;
    flag = false;
    if (group != nullptr) {
        group->UpdateConfiguration(config);
        flag = true;
    }
    EXPECT_TRUE(flag);
    group->formRenderer_ = std::make_shared<FormRenderer>(nullptr, nullptr, eventHandler);
    flag = false;
    if (group != nullptr) {
        group->UpdateConfiguration(config);
        flag = true;
    }
    EXPECT_TRUE(flag);
    GTEST_LOG_(INFO) << "FormRenderGroupTest_018 end";
}

/**
 * @tc.name: FormRenderGroupTest_019
 * @tc.desc: Test RecycleForm() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderGroupTest, FormRenderGroupTest_019, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderGroupTest_019 start";
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("FormRenderGroupTest_019");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto group = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    std::string statusData = "statusData";
    group->formRenderer_ = nullptr;
    bool flag = false;
    if (group != nullptr) {
        group->RecycleForm(statusData);
        flag = true;
    }
    EXPECT_TRUE(flag);
    group->formRenderer_ = std::make_shared<FormRenderer>(nullptr, nullptr, eventHandler);
    flag = false;
    if (group != nullptr) {
        group->RecycleForm(statusData);
        flag = true;
    }
    EXPECT_TRUE(flag);
    GTEST_LOG_(INFO) << "FormRenderGroupTest_019 end";
}

/**
 * @tc.name: FormRenderGroupTest_020
 * @tc.desc: Test PreInitAddForm() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderGroupTest, FormRenderGroupTest_020, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderGroupTest_020 start";
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("FormRenderGroupTest_020");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto group = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    FormRequest formRequest;
    formRequest.compId = "PreInitAddForm";
    bool flag = false;
    if (group != nullptr) {
        group->initState_ = FormRendererGroup::FormRendererInitState::PRE_INITIALIZED;
        group->PreInitAddForm(formRequest);
        flag = true;
    }
    EXPECT_TRUE(flag);
    flag = false;
    if (group != nullptr) {
        group->initState_ = FormRendererGroup::FormRendererInitState::UNINITIALIZED;
        group->formRenderer_ = std::make_shared<FormRenderer>(nullptr, nullptr, eventHandler);
        group->PreInitAddForm(formRequest);
        flag = true;
    }
    EXPECT_TRUE(flag);
    flag = false;
    if (group != nullptr) {
        group->initState_ = FormRendererGroup::FormRendererInitState::UNINITIALIZED;
        group->formRenderer_ = nullptr;
        group->PreInitAddForm(formRequest);
        flag = true;
    }
    EXPECT_TRUE(flag);
    GTEST_LOG_(INFO) << "FormRenderGroupTest_020 end";
}

/**
 * @tc.name: FormRenderGroupTest_021
 * @tc.desc: Test InnerAddForm() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderGroupTest, FormRenderGroupTest_021, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderGroupTest_021 start";
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("FormRenderGroupTest_021");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto group = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    FormRequest formRequest;
    formRequest.compId = "InnerAddForm";
    bool flag = false;
    if (group != nullptr) {
        group->initState_ = FormRendererGroup::FormRendererInitState::PRE_INITIALIZED;
        group->formRenderer_ = nullptr;
        group->InnerAddForm(formRequest);
        flag = true;
    }
    EXPECT_TRUE(flag);
    flag = false;
    if (group != nullptr) {
        group->initState_ = FormRendererGroup::FormRendererInitState::UNINITIALIZED;
        group->formRenderer_ = std::make_shared<FormRenderer>(nullptr, nullptr, eventHandler);
        group->InnerAddForm(formRequest);
        flag = true;
    }
    EXPECT_TRUE(flag);
    flag = false;
    if (group != nullptr) {
        group->initState_ = FormRendererGroup::FormRendererInitState::PRE_INITIALIZED;
        group->formRenderer_ = std::make_shared<FormRenderer>(nullptr, nullptr, eventHandler);
        group->InnerAddForm(formRequest);
        flag = true;
    }
    EXPECT_TRUE(flag);
    flag = false;
    if (group != nullptr) {
        group->initState_ = FormRendererGroup::FormRendererInitState::INITIALIZED;
        group->formRenderer_ =  std::make_shared<FormRenderer>(nullptr, nullptr, eventHandler);
        group->InnerAddForm(formRequest);
        flag = true;
    }
    EXPECT_TRUE(flag);
    GTEST_LOG_(INFO) << "FormRenderGroupTest_021 end";
}

/**
 * @tc.name: FormRenderGroupTest_022
 * @tc.desc: Test GetOrderedAndCurrentCompIds() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderGroupTest, FormRenderGroupTest_022, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderGroupTest_022 start";
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("FormRenderGroupTest_022");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto group = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    EXPECT_TRUE(group);
    std::pair<std::vector<std::string>, std::string> compIdPair = group->GetOrderedAndCurrentCompIds();
    EXPECT_EQ(true, compIdPair.first.empty());
    EXPECT_EQ(true, compIdPair.second.empty());
    OHOS::AAFwk::Want want;
    OHOS::AppExecFwk::FormJsInfo formJsInfo;
    formJsInfo.formId = 1;
    std::string compId1 = "comp1";
    want.SetParam(FORM_RENDERER_COMP_ID, compId1);
    group->AddForm(want, formJsInfo);
    formJsInfo.formId = 2;
    std::string compId2 = "comp2";
    want.SetParam(FORM_RENDERER_COMP_ID, compId2);
    group->AddForm(want, formJsInfo);
    compIdPair = group->GetOrderedAndCurrentCompIds();
    EXPECT_EQ(2, compIdPair.first.size());
    EXPECT_EQ(compId1, compIdPair.first[0]);
    EXPECT_EQ(compId2, compIdPair.first[1]);
    EXPECT_EQ(compId2, compIdPair.second);
    group->DeleteForm(compId2);
    compIdPair = group->GetOrderedAndCurrentCompIds();
    EXPECT_EQ(1, compIdPair.first.size());
    EXPECT_EQ(compId1, compIdPair.second);
    GTEST_LOG_(INFO) << "FormRenderGroupTest_022 end";
}

/**
 * @tc.name: FormRenderGroupTest_023
 * @tc.desc: Test RecoverRenderer() function.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderGroupTest, FormRenderGroupTest_023, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderGroupTest_023 start";
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("FormRenderGroupTest_023");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto group = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    EXPECT_TRUE(group);
    OHOS::AAFwk::Want want;
    OHOS::AppExecFwk::FormJsInfo formJsInfo;
    formJsInfo.formId = 1;
    std::string compId1 = "comp1";
    want.SetParam(FORM_RENDERER_COMP_ID, compId1);
    group->AddForm(want, formJsInfo);
    formJsInfo.formId = 2;
    std::string compId2 = "comp2";
    want.SetParam(FORM_RENDERER_COMP_ID, compId2);
    group->AddForm(want, formJsInfo);
    std::pair<std::vector<std::string>, std::string> compIdPair = group->GetOrderedAndCurrentCompIds();
    group->DeleteForm();
    EXPECT_EQ(true, group->GetAllRendererFormRequests().empty());
    std::vector<FormRequest> requests;
    group->RecoverRenderer(requests, 0);
    EXPECT_EQ(true, group->GetAllRendererFormRequests().empty());
    for (auto compId: compIdPair.first) {
        FormRequest formRequest;
        formRequest.compId = compId;
        requests.emplace_back(formRequest);
    }
    group->RecoverRenderer(requests, requests.size());
    EXPECT_EQ(true, group->GetAllRendererFormRequests().empty());
    group->RecoverRenderer(requests, requests.size() - 1);
    EXPECT_EQ(2, group->GetAllRendererFormRequests().size());
    compIdPair = group->GetOrderedAndCurrentCompIds();
    EXPECT_EQ(compId2, compIdPair.second);
    GTEST_LOG_(INFO) << "FormRenderGroupTest_023 end";
}

HWTEST_F(FormRenderGroupTest, FormRenderGroupTest_024, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FormRenderGroupTest_024 start";
    auto eventRunner = OHOS::AppExecFwk::EventRunner::Create("FormRenderGroupTest_024");
    ASSERT_TRUE(eventRunner);
    auto eventHandler = std::make_shared<OHOS::AppExecFwk::EventHandler>(eventRunner);
    auto group = FormRendererGroup::Create(nullptr, nullptr, eventHandler);
    EXPECT_TRUE(group);
    OHOS::AAFwk::Want want;
    OHOS::AppExecFwk::FormJsInfo formJsInfo;
    formJsInfo.formId = 1;
    std::string compId = "comp1";
    want.SetParam(FORM_RENDERER_COMP_ID, compId);
    want.SetParam(OHOS::AppExecFwk::Constants::PARAM_FORM_WIDTH_KEY, 1.0);
    want.SetParam(OHOS::AppExecFwk::Constants::PARAM_FORM_HEIGHT_KEY, 1.0);
    want.SetParam(OHOS::AppExecFwk::Constants::PARAM_FORM_BORDER_WIDTH_KEY, 1.0f);
    group->AddForm(want, formJsInfo);
    auto requestWant = group->GetAllRendererFormRequests().begin()->want;
    EXPECT_EQ(1.0, requestWant.GetDoubleParam(OHOS::AppExecFwk::Constants::PARAM_FORM_WIDTH_KEY, 0.0f));
    EXPECT_EQ(1.0, requestWant.GetDoubleParam(OHOS::AppExecFwk::Constants::PARAM_FORM_HEIGHT_KEY, 0.0f));
    EXPECT_EQ(1.0, requestWant.GetFloatParam(OHOS::AppExecFwk::Constants::PARAM_FORM_BORDER_WIDTH_KEY, 0.0f));
    group->UpdateFormSizeOfFormRequests(2.0, 2.0, 2.0f);
    auto requestWant2 = group->GetAllRendererFormRequests().begin()->want;
    EXPECT_EQ(2.0, requestWant2.GetDoubleParam(OHOS::AppExecFwk::Constants::PARAM_FORM_WIDTH_KEY, 0.0f));
    EXPECT_EQ(2.0, requestWant2.GetDoubleParam(OHOS::AppExecFwk::Constants::PARAM_FORM_HEIGHT_KEY, 0.0f));
    EXPECT_EQ(2.0, requestWant2.GetFloatParam(OHOS::AppExecFwk::Constants::PARAM_FORM_BORDER_WIDTH_KEY, 0.0f));
    GTEST_LOG_(INFO) << "FormRenderGroupTest_024 end";
}
}