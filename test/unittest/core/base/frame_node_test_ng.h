/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef TEST_UNITTEST_CORE_BASE_FRAME_NODE_TEST_NG_H
#define TEST_UNITTEST_CORE_BASE_FRAME_NODE_TEST_NG_H
#include "gtest/gtest.h"

#define protected public
#define private public
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"

namespace OHOS::Ace::NG {
namespace {
const RefPtr<FrameNode> FRAME_NODE_PARENT =
    FrameNode::CreateFrameNode("parent", 0, AceType::MakeRefPtr<Pattern>(), true);
const RefPtr<FrameNode> FRAME_NODE = FrameNode::CreateFrameNode("one", 1, AceType::MakeRefPtr<Pattern>());
const RefPtr<FrameNode> FRAME_NODE2 = FrameNode::CreateFrameNode("two", 2, AceType::MakeRefPtr<Pattern>());
const RefPtr<FrameNode> FRAME_NODE3 =
    FrameNode::CreateFrameNode("three", 3, AceType::MakeRefPtr<LinearLayoutPattern>(false));
const RefPtr<FrameNode> FRAME_NODE_WEB_ETS_TAG =
    FrameNode::CreateFrameNode(V2::WEB_ETS_TAG, 5, AceType::MakeRefPtr<LinearLayoutPattern>(false));
std::string srcimages = "";

const std::string NAME = "propertyName";
float value = 1.0;
const std::function<void(float)> onCallbackEvent = [](float) {};

const float CONTAINER_WIDTH = 600.0f;
const float CONTAINER_HEIGHT = 1000.0f;
const SizeF CONTAINER_SIZE(CONTAINER_WIDTH, CONTAINER_HEIGHT);

const float CONTAINER_WIDTH_HUGE = 1260.0f;
const SizeF CONTAINER_SIZE_HUGE(CONTAINER_WIDTH_HUGE, CONTAINER_HEIGHT);

const float CONTAINER_WIDTH_SMALL = 10.0f;
const SizeF CONTAINER_SIZE_SMALL(CONTAINER_WIDTH_SMALL, CONTAINER_HEIGHT);

const float CONTAINER_WIDTH_ZERO = 0.0f;
const SizeF CONTAINER_SIZE_ZERO(CONTAINER_WIDTH_ZERO, CONTAINER_WIDTH_ZERO);

const OffsetF OFFSETF { 1.0, 1.0 };
const float DEFAULT_X = 10;
const float DEFAULT_Y = 10;

constexpr uint64_t TIMESTAMP_1 = 100;
constexpr uint64_t TIMESTAMP_2 = 101;
constexpr uint64_t TIMESTAMP_3 = 102;
constexpr uint64_t TIMESTAMP_4 = 103;

const InspectorFilter filter;
} // namespace
class FrameNodeTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

class TestNode : public UINode {
    DECLARE_ACE_TYPE(TestNode, UINode);

public:
    static RefPtr<TestNode> CreateTestNode(int32_t nodeId)
    {
        auto node = MakeRefPtr<TestNode>(nodeId);
        return node;
    }

    bool IsAtomicNode() const override
    {
        return true;
    }

    explicit TestNode(int32_t nodeId) : UINode("TestNode", nodeId) {}
    ~TestNode() override = default;
};
} // namespace OHOS::Ace::NG

#endif // TEST_UNITTEST_CORE_BASE_FRAME_NODE_TEST_NG_H