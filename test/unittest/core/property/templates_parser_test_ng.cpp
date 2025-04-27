/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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

#include <cstdint>
#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "gtest/gtest.h"

#include "base/geometry/dimension.h"

#define protected public
#define private public

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/property/templates_parser.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {}

class TemplatesParserTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: TemplatesParserTestNg001
 * @tc.desc: Test ParseTemplateArgs.
 * @tc.type: FUNC
 */
HWTEST_F(TemplatesParserTestNg, TemplatesParserTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1 init args of ParseTemplateArgs and
                call ParseTemplateArgs.
     * @tc.expected: the return value is same as the forth val of tuple.
     */
    double size = 0;
    double gap = 0;
    int32_t childrenCount = 0;
    std::vector<std::tuple<std::function<std::string(void)>, double, double, int32_t, std::vector<double>>> parms = {
        { [&]() {
            size = 200;
            gap = 10;
            childrenCount = 5;
            return "";
        },
            size, gap, childrenCount, {} },
        { [&]() {
            size = 200;
            gap = 10;
            childrenCount = 5;
            return "abc";
        },
            size, gap, childrenCount, {} },
        { [&]() {
            size = 200;
            gap = 10;
            childrenCount = 5;
            return "1fr 2px 3%";
        },
            size, gap, childrenCount, { -2, 0, 0 } },
        { [&]() {
            size = 200;
            gap = 10;
            childrenCount = 5;
            return "1fr 2px 900%";
        },
            size, gap, childrenCount, { -2, 0, 0 } },
        { [&]() {
            size = 200;
            gap = 10;
            childrenCount = 5;
            return "auto-fill 1fr 3fr";
        },
            size, gap, childrenCount, {} },
        { [&]() {
            size = 200;
            gap = 100;
            childrenCount = 5;
            return "0.1fr 20px 100px";
        },
            size, gap, childrenCount, { -12, 0, 0 } },
        { [&]() {
            size = 200;
            gap = 10;
            childrenCount = 5;
            return "repeat";
        },
            size, gap, childrenCount, {} },
        { [&]() {
            size = 200;
            gap = 10;
            childrenCount = 5;
            return "auto-fill";
        },
            size, gap, childrenCount, {} },
        { [&]() {
            size = 200;
            gap = 10;
            childrenCount = 5;
            return "repeat(1, 100px 2px 3px 4px 5px 6px 7px 8px)";
        },
            size, gap, childrenCount, { 0, 0, 0, 0, 0, 0, 0, 0 } },
        { [&]() {
            size = 200;
            gap = 10;
            childrenCount = 5;
            return "repeatabcdefghi";
        },
            size, gap, childrenCount, {} },
        { [&]() {
            size = 200;
            gap = 10;
            childrenCount = 5;
            return "repeat(3, 100px a b c d e f g)";
        },
            size, gap, childrenCount, {} },
        { [&]() {
            size = 200;
            gap = 10;
            childrenCount = 5;
            return "repeat auto-fill 1fr 2px 900%";
        },
            size, gap, childrenCount, { 0 } },
        { [&]() {
            size = 200;
            gap = 10;
            childrenCount = 5;
            return "auto-fill arepeatpx10vp10 10)2";
        },
            size, gap, childrenCount, { 0 } },
        { [&]() {
            size = 200;
            gap = 10;
            childrenCount = 5;
            return "repeat(auto-fill, 2px )repeat(auto-fill, 2px )repeat(auto-fill, 2vp)";
        },
            size, gap, childrenCount, { 0 } },
        { [&]() {
            size = 200;
            gap = 10;
            childrenCount = 5;
            return "repeat(auto-fill, 2px 2% 2vp 2 )";
        },
            size, gap, childrenCount, { 2, 0, 2, 2 } },
        { [&]() {
            size = 200;
            gap = 10;
            childrenCount = 5;
            return "2px 2px repeat(auto-fill, 2px 2% 2 ) 2px";
        },
            size, gap, childrenCount, { 2, 2, 2, 0, 2, 2 } },
        { [&]() {
            size = 200;
            gap = 10;
            childrenCount = 5;
            return "(auto-fit, 2px 2)";
        },
            size, gap, childrenCount, {} },
        { [&]() {
            size = 200;
            gap = 10;
            childrenCount = 5;
            return "repeat(auto-fit, ) 2px";
        },
            size, gap, childrenCount, { 0 } }
    };
    for (auto [args, size, gap, childrenCount, rt] : parms) {
        auto result = ParseTemplateArgs(args(), size, gap, childrenCount);
        EXPECT_EQ(result.first.size(), rt.size());
        for (int i = 0; i < rt.size() && i < result.first.size(); i++) {
            EXPECT_EQ(rt[i], result.first[i]);
        }
    }
}

/**
 * @tc.name: TemplatesParserTestNg002
 * @tc.desc: Test ParseTemplateArgs.
 * @tc.type: FUNC
 */
HWTEST_F(TemplatesParserTestNg, TemplatesParserTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test ParseArgsWithAutoFit.
     * @tc.expected: retVal.first is empty.
     */
    std::string args = "repeat(auto-fit,4px) 2px 2px 2px";
    double size = 100;
    double gap = -10;
    int32_t childrenCount = 6;

    auto retVal = ParseTemplateArgs(args, size, gap, childrenCount);
    EXPECT_EQ(retVal.first.size(), 4);

    /**
     * @tc.steps: step2. Test ParseArgsWithAutoFill.
     * @tc.expected: retVal.first.size() is 100.
     */
    args = "repeat(auto-fill,4px) 2px 2px 2px";
    size = 6;
    gap = 100;
    childrenCount = 6;
    vector<int> gt { 4, 2, 2, 2 };

    retVal = ParseTemplateArgs(args, size, gap, childrenCount);
    EXPECT_EQ(retVal.first.size(), 4);
    for (int i = 0; i < retVal.first.size(); i++) {
        EXPECT_EQ(retVal.first[i], gt[i]);
    }

    /**
     * @tc.steps: step2. Test ParseAutoFill.
     * @tc.expected: retVal.first.size() is empty.
     */
    args = "auto-fill,4px 2px 2px 2px";
    size = 6;
    gap = -10;
    childrenCount = 6;

    retVal = ParseTemplateArgs(args, size, gap, childrenCount);
    EXPECT_TRUE(retVal.first.empty());
}

/**
 * @tc.name: TemplatesParserTestNg003
 * @tc.desc: Test ParseArgsWithAutoStretch.
 * @tc.type: FUNC
 */
HWTEST_F(TemplatesParserTestNg, TemplatesParserTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test ParseArgsWithAutoStretch with normal args.
     * @tc.expected: retVal.first is { 4, 4} and retVal.second is 1
     */
    std::string args = "repeat(auto-stretch, 4)";
    double size = 9;
    double gap = 1;
    int32_t childrenCount = 2;
    vector<int> gt { 4, 4 };

    auto retVal = ParseTemplateArgs(args, size, gap, childrenCount);
    for (int i = 0; i < retVal.first.size(); i++) {
        EXPECT_EQ(retVal.first[i], gt[i]);
    }
    EXPECT_EQ(retVal.second, 1);

    /**
     * @tc.steps: step2. Test ParseArgsWithAutoStretch with invalid args.
     * @tc.expected: retVal.first is empty.
     */
    args = "repeat(auto-stretch, 4, 6)";

    retVal = ParseTemplateArgs(args, size, gap, childrenCount);
    EXPECT_TRUE(retVal.first.empty());

    /**
     * @tc.steps: step3. Test ParseArgsWithAutoStretch with need calculate gap args.
     * @tc.expected: retVal.first is { 4, 4} and retVal.second is 2
     */
    args = "repeat(auto-stretch, 4)";
    size = 10;
    gap = 1;
    gt = { 4, 4 };

    retVal = ParseTemplateArgs(args, size, gap, childrenCount);
    EXPECT_EQ(retVal.first.size(), gt.size());
    for (int i = 0; i < retVal.first.size(); i++) {
        EXPECT_EQ(retVal.first[i], gt[i]);
    }
    EXPECT_EQ(retVal.second, 2);

    /**
     * @tc.steps: step4. Test ParseArgsWithAutoStretch with px args.
     * @tc.expected: retVal.first is { 4, 4, 4, 4 } and retVal.second is 2.
     */
    args = "repeat(auto-stretch, 4px)";
    size = 22;
    gap = 1;
    gt = { 4, 4, 4, 4 };

    retVal = ParseTemplateArgs(args, size, gap, childrenCount);
    EXPECT_EQ(retVal.first.size(), gt.size());
    for (int i = 0; i < retVal.first.size(); i++) {
        EXPECT_EQ(retVal.first[i], gt[i]);
    }
    EXPECT_EQ(retVal.second, 2);

    /**
     * @tc.steps: step5. Test ParseArgsWithAutoStretch with % args.
     * @tc.expected: retVal.first is empty .
     */
    args = "repeat(auto-stretch, 5%)";
    size = 35;
    gap = 2;
    gt = { 5, 5, 5, 5, 5 };
    retVal = ParseTemplateArgs(args, size, gap, childrenCount);
    EXPECT_TRUE(retVal.first.empty());
}

/**
 * @tc.name: TemplatesParserTestNg004
 * @tc.desc: Test ParseArgsWithoutAutoFill.
 * @tc.type: FUNC
 */
HWTEST_F(TemplatesParserTestNg, TemplatesParserTestNg004, TestSize.Level1)
{
    std::string args = "auto-fill 4px) 4";
    double size = 0;
    double gap = -1;
    int32_t childrenCount = 2;
    vector<int> gt { 4, 4 };
    auto retVal = ParseTemplateArgs(args, size, gap, childrenCount);

    /**
     * @tc.steps:. Test ParseArgsWithAutoStretch with vp args.
     * @tc.expected: retVal.first is { 5, 5, 5, 5, 5 } and retVal.second is 2.5 .
     */
    args = "repeat(auto-stretch, 5vp)";
    size = 35;
    gap = 2;
    gt = { 5, 5, 5, 5, 5 };
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    retVal = ParseTemplateArgs(args, size, gap, childrenCount);
    EXPECT_EQ(retVal.first.size(), gt.size());
    for (int i = 0; i < retVal.first.size(); i++) {
        EXPECT_EQ(retVal.first[i], gt[i]);
    }
    EXPECT_EQ(retVal.second, 2.5);
    MockPipelineContext::TearDown();
    MockContainer::TearDown();

    args = "repeat(auto-stretch, 10vp)";
    size = 1;
    gap = 2;
    gt = { 5, 5, 5, 5, 5 };
    retVal = ParseTemplateArgs(args, size, gap, childrenCount);

    args = "repeat(auto-fill,0vp)";
    size = 6;
    gap = 100;
    childrenCount = 6;
    gt = { 4, 2, 2, 2 };
    retVal = ParseTemplateArgs(args, size, gap, childrenCount);
    EXPECT_EQ(gap, 100);
}

/**
 * @tc.name: TemplatesParserTestNg005
 * @tc.desc: Test ParseArgsWithoutAutoFill.
 * @tc.type: FUNC
 */
HWTEST_F(TemplatesParserTestNg, TemplatesParserTestNg005, TestSize.Level1)
{
    std::string args = "repeat(auto-fill,0vp)";
    double size = 6;
    double gap = 100;
    int32_t childrenCount = -1;
    vector<int> gt = { 4, 2, 2, 2 };
    auto retVal = ParseTemplateArgs(args, size, gap, childrenCount);

    args = "repeat(auto-fit,0vp)";
    size = 6;
    gap = 100;
    childrenCount = 6;
    gt = { 4, 2, 2, 2 };
    retVal = ParseTemplateArgs(args, size, gap, childrenCount);

    args = "repeat(auto-fit,0vp)";
    size = 6;
    gap = 100;
    childrenCount = -1;
    gt = { 4, 2, 2, 2 };
    retVal = ParseTemplateArgs(args, size, gap, childrenCount);
    EXPECT_EQ(gap, 100);
}

/**
 * @tc.name: TemplatesParserTestNg006
 * @tc.desc: Test ParseArgsWithoutAutoFill with large repeat number
 * @tc.type: FUNC
 */
HWTEST_F(TemplatesParserTestNg, TemplatesParserTestNg006, TestSize.Level1)
{
    std::string args = "repeat(10000000, 2px)";
    double size = 100;
    double gap = 2;
    int32_t childrenCount = 10;
    auto retVal = ParseTemplateArgs(args, size, gap, childrenCount);
    EXPECT_EQ(retVal.first.size(), size);
}
} // namespace OHOS::Ace::NG
