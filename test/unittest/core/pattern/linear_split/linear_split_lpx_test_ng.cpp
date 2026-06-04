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

#include <cstdint>
#include <optional>

#define private public
#define protected public

#include "gtest/gtest.h"

#include "core/accessibility/accessibility_manager.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/linear_split/linear_split_layout_property.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "core/components_ng/pattern/linear_split/linear_split_model.h"
#include "core/components_ng/pattern/linear_split/linear_split_pattern.h"
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/components_ng/render/mock_render_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class LinearSplitLpxTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
    }
    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
    }
    RefPtr<FrameNode> CreateLinearSplit(SplitType splitType, const std::function<void(LinearSplitModelNG)>& callback)
    {
        LinearSplitModelNG model;
        model.Create(splitType);
        if (callback) {
            callback(model);
        }
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
        ViewStackProcessor::GetInstance()->PopContainer();
        return frameNode;
    }
};

/**
 * @tc.name: LinearSplitLpxAttribute001
 * @tc.desc: Test SetDivider with LPX startMargin/endMargin registers LPX_LINEAR_SPLIT_DIVIDER attributes.
 * @tc.type: FUNC
 */
HWTEST_F(LinearSplitLpxTestNg, LinearSplitLpxAttribute001, TestSize.Level1)
{
    Dimension lpxDim(10.0, DimensionUnit::LPX);
    Dimension vpDim(10.0, DimensionUnit::VP);

    NG::ColumnSplitDivider divider;
    divider.startMargin = lpxDim;
    divider.endMargin = lpxDim;

    auto frameNode = CreateLinearSplit(SplitType::COLUMN_SPLIT, [&divider](LinearSplitModelNG model) {
        model.SetDivider(SplitType::COLUMN_SPLIT, divider);
    });
    ASSERT_NE(frameNode, nullptr);
    frameNode->AttachToMainTree();

    EXPECT_EQ(frameNode->lpxAttributes_.size(), 2);

    NG::ColumnSplitDivider vpDivider;
    vpDivider.startMargin = vpDim;
    vpDivider.endMargin = vpDim;
    LinearSplitModelNG::SetDivider(frameNode.GetRawPtr(), SplitType::COLUMN_SPLIT, vpDivider);
    EXPECT_EQ(frameNode->lpxAttributes_.size(), 0);
}
} // namespace OHOS::Ace::NG
