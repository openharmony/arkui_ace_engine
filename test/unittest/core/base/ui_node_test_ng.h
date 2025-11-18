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

#ifndef TEST_UNITTEST_CORE_BASE_UI_NODE_TEST_NG_H
#define TEST_UNITTEST_CORE_BASE_UI_NODE_TEST_NG_H
#include "gtest/gtest.h"

#define protected public
#define private public

namespace OHOS::Ace::NG {
namespace {
const RefPtr<FrameNode> TEN0 = FrameNode::CreateFrameNode("zero", 10, AceType::MakeRefPtr<Pattern>(), true);
const RefPtr<FrameNode> ZERO = FrameNode::CreateFrameNode("zero", 0, AceType::MakeRefPtr<Pattern>(), true);
const RefPtr<FrameNode> ONE = FrameNode::CreateFrameNode("one", 1, AceType::MakeRefPtr<Pattern>(), true);
const RefPtr<FrameNode> TWO = FrameNode::CreateFrameNode("two", 2, AceType::MakeRefPtr<Pattern>());
const RefPtr<FrameNode> THREE = FrameNode::CreateFrameNode("three", 3, AceType::MakeRefPtr<Pattern>());
const RefPtr<FrameNode> FOUR = FrameNode::CreateFrameNode("four", 4, AceType::MakeRefPtr<Pattern>());
const RefPtr<FrameNode> FIVE = FrameNode::CreateFrameNode("five", 5, AceType::MakeRefPtr<Pattern>());
const RefPtr<FrameNode> F_ONE = FrameNode::CreateFrameNode("one", 5, AceType::MakeRefPtr<Pattern>());
const int32_t TEST_ID_ONE = 21;
const int32_t TEST_ID_TWO = 22;
constexpr size_t SIZE_ZERO = 0;
constexpr size_t SIZE_ONE = 1;
} // namespace

class TestNode : public UINode {
    DECLARE_ACE_TYPE(TestNode, UINode);

public:
    static RefPtr<TestNode> CreateTestNode(int32_t nodeId)
    {
        auto spanNode = MakeRefPtr<TestNode>(nodeId);
        return spanNode;
    }

    bool IsAtomicNode() const override
    {
        return true;
    }

    explicit TestNode(int32_t nodeId) : UINode("TestNode", nodeId) {}

    HitTestResult TouchTest(const PointF& globalPoint, const PointF& parentLocalPoint, const PointF& parentRevertPoint,
        TouchRestrict& touchRestrict, TouchTestResult& result, int32_t touchId, ResponseLinkResult& responseLinkResult,
        bool isDispatch = false) override
    {
        return hitTestResult_;
    }

    HitTestResult MouseTest(const PointF& globalPoint, const PointF& parentLocalPoint, MouseTestResult& onMouseResult,
        MouseTestResult& onHoverResult, RefPtr<FrameNode>& hoverNode) override
    {
        return hitTestResult_;
    }

    HitTestResult AxisTest(const PointF &globalPoint, const PointF &parentLocalPoint, const PointF &parentRevertPoint,
        TouchRestrict &touchRestrict, AxisTestResult &axisResult) override
    {
        return hitTestResult_;
    }

    ~TestNode() override = default;

private:
    HitTestResult hitTestResult_;
};

} // namespace OHOS::Ace::NG

#endif // TEST_UNITTEST_CORE_BASE_UI_NODE_TEST_NG_H