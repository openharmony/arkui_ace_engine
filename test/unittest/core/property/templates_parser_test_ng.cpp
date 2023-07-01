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

#include <functional>
#include <tuple>
#include <vector>

#include "gtest/gtest.h"

#define protected public
#define private public

#include "core/components_ng/property/templates_parser.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {}

class TemplatesParserTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TeardownTestSuite() {};
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
        EXPECT_EQ(result.size(), rt.size());
        for (int i = 0; i < rt.size() && i < result.size(); i++) {
            EXPECT_EQ(rt[i], result[i]);
        }
    }
}
} // namespace OHOS::Ace::NG
