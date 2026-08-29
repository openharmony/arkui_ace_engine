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

#include "lazy_grid_layout_test.h"

#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

namespace OHOS::Ace::NG {

class LazyGridPatternVisibleIndexesTest : public LazyGridLayoutTest {
public:
    void SetUp() override
    {
        LazyGridLayoutTest::SetUp();
        pattern_ = AceType::MakeRefPtr<LazyGridLayoutPattern>();
    }
    void TearDown() override
    {
        LazyGridLayoutTest::TearDown();
    }
};

/**
 * @tc.name: GetVisibleIndexesRangeForCallback001
 * @tc.desc: Test when layoutInfo_ is null
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridPatternVisibleIndexesTest, GetVisibleIndexesRangeForCallback001, TestSize.Level1)
{
    pattern_->layoutInfo_ = nullptr; // nullptr ： layoutInfo_ 置空
    auto result = pattern_->GetVisibleIndexesRangeForCallback();
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, -1);
}

} // namespace OHOS::Ace::NG
