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

#include "gtest/gtest.h"

#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/relaxed_interaction/frame_node_finder.h"
#include "core/components_ng/base/frame_node.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class FrameNodeFinderTest : public testing::Test {
public:
    static void SetUpTestCase()
    {
        mockPipelineContext_ = AceType::MakeRefPtr<MockPipelineContext>();
        ASSERT_NE(mockPipelineContext_, nullptr);
    }

    static void TearDownTestCase()
    {
        mockPipelineContext_.Reset();
    }

protected:
    inline static RefPtr<MockPipelineContext> mockPipelineContext_ = nullptr;
};

class FrameNodeFinderFindAtTest : public FrameNodeFinderTest {};

HWTEST_F(FrameNodeFinderFindAtTest, FindAt_NullContext, TestSize.Level1)
{
    WeakPtr<PipelineContext> nullContext;
    FrameNodeFinder finder(nullContext, nullptr);
    auto result = finder.FindAt(100.0f, 100.0f);
    EXPECT_EQ(result.GetNode(), nullptr);
}

HWTEST_F(FrameNodeFinderFindAtTest, FindAt_NullRootNode, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    FrameNodeFinder finder(context, nullptr);
    auto result = finder.FindAt(100.0f, 100.0f);
    EXPECT_EQ(result.GetNode(), nullptr);
}

} // namespace OHOS::Ace::NG
