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
#include "grid_test_ng.h"
#include "test/mock/core/pattern/mock_koala_lazy_for_each.h"

namespace OHOS::Ace::NG {
class GridArkoalaTest : public GridTestNg {
private:
    void IncrementAndLayout()
    {
        lazy_.Increment();
        frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        FlushLayoutTask(frameNode_);
    }
    void InitMockLazy(int32_t itemCnt)
    {
        lazy_ = MockKoalaLazyForEach(frameNode_.GetRawPtr(), itemCnt, [](int32_t idx) {
            auto node = GridItemModelNG::CreateGridItem(-1);
            node->GetLayoutProperty()->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(450.0f)));
            return node;
        });
        auto adapter = pattern_->GetOrCreateScrollWindowAdapter();
        adapter->RegisterUpdater([&](int32_t s, int32_t e, void* pointer) {
            // frontend
            lazy_.Update(s, e, pointer);
        });
        adapter->SetTotalCount(itemCnt);
    }

    MockKoalaLazyForEach lazy_ { nullptr, 0, nullptr };
};

/**
 * @tc.name: Basic001
 * @tc.desc: Test ScrollWindowAdapter with MockKoala
 * @tc.type: FUNC
 */
HWTEST_F(GridArkoalaTest, Basic001, TestSize.Level1)
{
    /**
     * @tc.cases: Grid at top, ScrollTo index:0, text each ScrollAlign
     * @tc.expected: Each test grid does not scroll
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    InitMockLazy(100);
    CreateDone(frameNode_);

    IncrementAndLayout();

    EXPECT_EQ(frameNode_->GetChildren().size(), 4);
    EXPECT_EQ(GetChildRect(frameNode_, 0).ToString(), "RectT (0.00, 0.00) - [240.00 x 450.00]");
    EXPECT_EQ(GetChildRect(frameNode_, 1).ToString(), "RectT (240.00, 0.00) - [240.00 x 450.00]");

    UpdateCurrentOffset(-200.0f);
    IncrementAndLayout();
    EXPECT_EQ(frameNode_->GetChildren().size(), 6);
    EXPECT_EQ(GetChildRect(frameNode_, 4).ToString(), "RectT (0.00, 700.00) - [240.00 x 450.00]");
    EXPECT_EQ(GetChildRect(frameNode_, 5).ToString(), "RectT (240.00, 700.00) - [240.00 x 450.00]");

    UpdateCurrentOffset(-500.0f);
    IncrementAndLayout();
    EXPECT_EQ(frameNode_->GetChildren().size(), 6);
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 1));
    EXPECT_EQ(GetChildRect(frameNode_, 2).ToString(), "RectT (0.00, -250.00) - [240.00 x 450.00]");
    EXPECT_EQ(GetChildRect(frameNode_, 3).ToString(), "RectT (240.00, -250.00) - [240.00 x 450.00]");
}
} // namespace OHOS::Ace::NG