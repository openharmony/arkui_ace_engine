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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_TEST_UNITTEST_CORE_PATTERN_CUSTOM_CUSTOM_TEST_NG_H
#define FOUNDATION_ARKUI_ACE_ENGINE_TEST_UNITTEST_CORE_PATTERN_CUSTOM_CUSTOM_TEST_NG_H

#include <cstddef>
#include <utility>

#include "gtest/gtest.h"
#define private public
#define protected public
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/custom/custom_measure_layout_node.h"
#include "core/components_ng/pattern/custom/custom_measure_layout_param.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/custom/custom_node_base.h"
#include "core/components_ng/pattern/custom/custom_node_pattern.h"
#include "core/components_ng/pattern/custom/custom_title_node.h"
#include "core/components_ng/pattern/custom/custom_app_bar_node.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
namespace {
const std::string TEST_TAG("test");
constexpr int32_t CHILD_COUNT_0 = 0;
constexpr int32_t CHILD_COUNT_1 = 1;
} // namespace

class CustomTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
    void SetUp() override;
    void TearDown() override;
    RefPtr<FrameNode> CreateNode(const std::string& tag);
};

inline void CustomTestNg::SetUp()
{
    MockPipelineContext::SetUp();
}

inline void CustomTestNg::TearDown()
{
    MockPipelineContext::TearDown();
}

inline RefPtr<FrameNode> CustomTestNg::CreateNode(const std::string& tag)
{
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(tag, -1, pattern);
    pattern->AttachToFrameNode(frameNode);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    return frameNode;
}

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ARKUI_ACE_ENGINE_TEST_UNITTEST_CORE_PATTERN_CUSTOM_CUSTOM_TEST_NG_H