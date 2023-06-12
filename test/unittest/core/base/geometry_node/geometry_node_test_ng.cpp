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
#include <memory>

#include "gtest/gtest.h"

#define protected public
#define private public

#include "core/components_ng/base/geometry_node.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::array<bool, 4> margin { false, true, false, true };
const std::array<bool, 4> content { false, true, true, false };
} // namespace
class GeometryNodeTestNg : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
};

/**
 * @tc.name: GeometryNodeTestNg001
 * @tc.desc: Test geometry node method
 * @tc.type: FUNC
 */
HWTEST_F(GeometryNodeTestNg, GeometryNodeTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. geometry node clone
     * @tc.expected: step1. margin size
     */
    for (int i = 0; i < 4; ++i) {
        auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
        if (margin[i]) {
            geometryNode->margin_ = std::make_unique<MarginPropertyF>();
        }
        if (content[i]) {
            geometryNode->content_ = std::make_unique<GeometryProperty>();
        }
        auto cloneNode = geometryNode->Clone();
        EXPECT_NE(cloneNode, nullptr);
        if (margin[i]) {
            EXPECT_EQ(geometryNode->margin_->Size(), cloneNode->margin_->Size());
        }
    }
}
} // namespace OHOS::Ace::NG