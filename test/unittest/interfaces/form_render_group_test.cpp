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
#include "test/mock/interfaces/mock_uicontent.h"
#include "ui_content.h"
#include "interfaces/inner_api/form_render/include/form_renderer.h"
#include "interfaces/inner_api/form_render/include/form_renderer_delegate_impl.h"
#include "interfaces/inner_api/form_render/include/form_renderer_group.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace {
namespace {

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
}