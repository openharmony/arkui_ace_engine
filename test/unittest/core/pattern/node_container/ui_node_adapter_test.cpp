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

#include <optional>

#include "gtest/gtest.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#define private public
#define protected public
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/waterflow/water_flow_pattern.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"
#include "core/interfaces/native/node/node_adapter_impl.h"
#include "core/interfaces/arkoala/arkoala_api.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
struct _ArkUINodeAdapter {
    OHOS::Ace::RefPtr<OHOS::Ace::NG::NativeLazyForEachBuilder> builder;
    OHOS::Ace::RefPtr<OHOS::Ace::NG::LazyForEachNode> node;
};
}

class UINodeAdapterTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
    }
    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
    }
};

/**
 * @tc.name: UINodeAdapter use-after-free test
 * @tc.desc: Test UINodeAdapter use-after-free.
 * @tc.type: FUNC
 */
HWTEST_F(UINodeAdapterTest, UINodeAdapterUseAfterFreeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create mock pipeline context and ArkUINodeAdapterHandle with builder
     * @tc.expected: objects created successfully
     */
    auto mockPipeline = NG::MockPipelineContext::GetCurrent();
    ASSERT_NE(mockPipeline, nullptr);
    auto* handle = new _ArkUINodeAdapter { .builder = AceType::MakeRefPtr<NG::NativeLazyForEachBuilder>() };
    auto builder = handle->builder;
    ASSERT_TRUE(builder);
    builder->SetHostHandle(reinterpret_cast<ArkUINodeAdapterHandle>(handle));

    /**
     * @tc.steps: step2. create UINodeAdapter instance with the handle
     * @tc.expected: UINodeAdapter created successfully, builder's userData and receiver set
     */
    UINodeAdapter* adapter = new UINodeAdapter(reinterpret_cast<ArkUINodeAdapterHandle>(handle));

    /**
     * @tc.steps: step3. delete UINodeAdapter instance (triggering destructor)
     * @tc.expected: UINodeAdapter destroyed, builder's userData and receiver cleared to prevent use-after-free
     */
    delete adapter;
    adapter = nullptr;

    /**
     * @tc.steps: step4. verify builder still exists but callbacks are cleared
     * @tc.expected: builder not null, receiver_ and userData_ are null indicating successful cleanup
     */
    EXPECT_TRUE(builder);
    EXPECT_FALSE(builder->receiver_);
    EXPECT_FALSE(builder->userData_);
}

/**
 * @tc.name: UINodeAdapter use-after-free test
 * @tc.desc: Test UINodeAdapter use-after-free when builder is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(UINodeAdapterTest, UINodeAdapterUseAfterFreeTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create mock pipeline context and ArkUINodeAdapterHandle with builder is nullptr
     * @tc.expected: objects created successfully
     */
    auto mockPipeline = NG::MockPipelineContext::GetCurrent();
    ASSERT_NE(mockPipeline, nullptr);
    auto* handle = new _ArkUINodeAdapter { .builder = nullptr };
    auto builder = handle->builder;
    ASSERT_FALSE(builder);

    /**
     * @tc.steps: step2. create UINodeAdapter instance with the handle
     * @tc.expected: UINodeAdapter created successfully
     */
    UINodeAdapter* adapter = new UINodeAdapter(reinterpret_cast<ArkUINodeAdapterHandle>(handle));

    /**
     * @tc.steps: step3. delete UINodeAdapter instance (triggering destructor)
     * @tc.expected: UINodeAdapter destroyed
     */
    delete adapter;
    adapter = nullptr;

    /**
     * @tc.steps: step4. verify builder still nullptr
     * @tc.expected: builder is nullptr
     */
    EXPECT_FALSE(builder);
}
} // namespace OHOS::Ace::NG
