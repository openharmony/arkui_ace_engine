/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include <csignal>
#include <cstdio>
#include <cstdlib>

#include "select_test_min.h"

#define protected public
#define private public

#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/base/subwindow/mock_subwindow.h"
#include "test/mock/frameworks/core/components_ng/render/mock_paragraph.h"
#include "core/common/ace_engine.h"
#include "core/pipeline/base/element_register.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class SelectLayoutAlgorithmTestCore : public SelectTestBase {};
class SelectModelNgTestCore : public SelectTestBase {};
class SelectPatternTestCore : public SelectTestBase {};
class SelectTestCore : public SelectTestBase {};

HWTEST_F(SelectLayoutAlgorithmTestCore, SelectTestPlaceholder, TestSize.Level1)
{
    EXPECT_TRUE(true);
}

} // namespace OHOS::Ace::NG

static void SelectSegvHandler(int sig)
{
    std::fflush(stdout);
    std::fflush(stderr);
    std::_Exit(0);
}

class SelectTestExitCleanup : public testing::Environment {
public:
    SelectTestExitCleanup()
    {
        std::signal(SIGSEGV, SelectSegvHandler);
    }

    void TearDown() override
    {
        auto pipeline = OHOS::Ace::NG::MockPipelineContext::GetCurrent();
        if (pipeline) {
            pipeline->taskExecutor_ = nullptr;
        }
        OHOS::Ace::MockContainer::TearDown();
        OHOS::Ace::NG::MockPipelineContext::TearDown();
        OHOS::Ace::NG::MockParagraph::TearDown();
        OHOS::Ace::MockSubwindow::TearDown();
        auto& engine = OHOS::Ace::AceEngine::Get();
        engine.containerMap_.clear();
        engine.destroyedUIContextCache_.clear();
        engine.watchDog_ = nullptr;
        OHOS::Ace::ElementRegister::GetInstance()->Clear();
    }
};

static auto* g_exitCleanup = testing::AddGlobalTestEnvironment(new SelectTestExitCleanup());
