/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#define protected public
#define private public

#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/base/transparent_node_detector.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class TransparentNodeDetectorTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void TransparentNodeDetectorTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->pipelineContext_ = NG::MockPipelineContext::GetCurrentContext();
}

void TransparentNodeDetectorTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: TransparentNodeDetectorTestNg001
 * @tc.desc: CheckWindowTransparent test
 * @tc.type: FUNC
 */
HWTEST_F(TransparentNodeDetectorTestNg, TransparentNodeDetectorTestNg001, TestSize.Level1)
{
    const RefPtr<FrameNode> root = AceType::MakeRefPtr<FrameNode>("root", 0, AceType::MakeRefPtr<Pattern>(), true);
    bool isNavigation = true;
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    auto containerId = pipelineContext->GetInstanceId();
    EXPECT_TRUE(TransparentNodeDetector::GetInstance().CheckWindowTransparent(root, containerId, isNavigation));
}
} // namespace OHOS::Ace::NG