/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "ability_context.h"
#include "ability_info.h"
#include "context_impl.h"
#include "gtest/gtest.h"
#include "interfaces/inner_api/ace/ui_content.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
class UiContentTest : public testing::Test {};

/**
 * @tc.name: DumpTest001
 * @tc.desc: test Dump infos
 * @tc.type: FUNC
 */
HWTEST_F(UiContentTest, DumpTest001, TestSize.Level1)
{
    auto infos = std::vector<std::string>();
    UIContent::ShowDumpHelp(infos);
    EXPECT_GT(infos.size(), 0);
    for (const auto& info : infos) {
        GTEST_LOG_(INFO) << info;
    }
}

/**
 * @tc.name: CreateUIContent001
 * @tc.desc: test CreateUIContent001
 * @tc.type: FUNC
 */
HWTEST_F(UiContentTest, CreateUIContent001, TestSize.Level1)
{
    OHOS::AbilityRuntime::Context* context = nullptr;
    NativeEngine* runtime = nullptr;
    bool isFormRender = false;
    std::unique_ptr<UIContent> ret = UIContent::Create(context, runtime, isFormRender);
    EXPECT_TRUE((ret.get() != nullptr));
    std::unique_ptr<UIContent> ret2 = UIContent::Create(context, runtime);
    EXPECT_TRUE((ret2.get() != nullptr));
    OHOS::AppExecFwk::Ability* ability = nullptr;
    std::unique_ptr<UIContent> ret3 = UIContent::Create(ability);
    EXPECT_TRUE(ret3.get() != nullptr);
}

/**
 * @tc.name: GetUIContent001
 * @tc.desc: test GetCurrentUIStackInfo/GetUIContent
 * @tc.type: FUNC
 */
HWTEST_F(UiContentTest, GetUIContent001, TestSize.Level1)
{
    int32_t instanceId = 1;
    UIContent* ret = UIContent::GetUIContent(instanceId);
    EXPECT_TRUE(ret == nullptr);
    std::string ret2 = UIContent::GetCurrentUIStackInfo();
    EXPECT_TRUE(ret2 == std::string());
}
} // namespace OHOS::Ace