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

#include <cstdint>
#include <memory>

#include "gtest/gtest.h"

#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/grid/grid_item_model_ng.h"
#include "core/components_ng/pattern/grid/grid_model_ng.h"
#include "core/components_ng/pattern/text/text_model_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {} // namespace

class GridTestNg : public testing::Test {
};

/**
 * @tc.name: GridTest001
 * @tc.desc: Fill all items to grid with fixed row and column
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GridLayoutPropertyTest001, TestSize.Level1)
{
    RefPtr<V2::GridPositionController> positionController;
    RefPtr<ScrollBarProxy> scrollBarProxy;
    GridModelNG grid;
    grid.Create(positionController, scrollBarProxy);
    std::unique_ptr<ViewAbstractModel> instance = std::make_unique<ViewAbstractModelNG>();
    auto height = StringUtils::StringToDimensionWithUnit("70%");
    instance->SetHeight(height);
    auto width = StringUtils::StringToDimensionWithUnit("90%");
    instance->SetWidth(width);
    grid.SetColumnsTemplate("1fr 1fr 1fr");
    grid.SetRowsTemplate("1fr 1fr 1fr");
    GridItemModelNG gridItem;
    TextModelNG text;
    const int32_t ITEM_COUNT = 9;
    for (int32_t i = 0; i < ITEM_COUNT; ++i) {
        gridItem.Create();
        text.Create("test");
        auto textHeight = StringUtils::StringToDimensionWithUnit("50%");
        instance->SetHeight(textHeight);
        auto textWidth = StringUtils::StringToDimensionWithUnit("100%");
        instance->SetWidth(textWidth);
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->Pop();
    }
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    LayoutConstraintF constraint;
    OptionalSizeF size;
    constexpr float DEFAULT_WIDTH = 800.0f;
    size.SetWidth(DEFAULT_WIDTH);
    constraint.UpdateIllegalSelfIdealSizeWithCheck(size);
    layoutWrapper->Measure(constraint);
    layoutWrapper->Layout();
    for (int32_t i = 0; i < ITEM_COUNT; ++i) {
        EXPECT_TRUE(layoutWrapper->GetOrCreateChildByIndex(i, false)->IsActive());
    }
}
} // namespace OHOS::Ace::NG