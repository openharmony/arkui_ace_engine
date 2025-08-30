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

#include <optional>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/grid_container/grid_container_model_ng.h"
#include "core/components_ng/pattern/grid_container/grid_container_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_model_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
constexpr float DEFAULT_WIDTH = 800.0f;
constexpr int32_t DEFAULT_COLUMN_NUM = 8;
constexpr float DEFAULT_COLUMN_WIDTH = 100.0f;

void MeasureLayout(RefPtr<LayoutWrapperNode>& container, RefPtr<LayoutWrapperNode>& text)
{
    auto algorithm = container->GetLayoutAlgorithm();
    algorithm->Measure(AceType::RawPtr(container));
    algorithm->Layout(AceType::RawPtr(container));

    auto textLayoutProperty = text->GetLayoutProperty();
    textLayoutProperty->BuildGridProperty(text->GetHostNode());
    auto textAlgorithm = text->GetLayoutAlgorithm();
    textAlgorithm->Measure(AceType::RawPtr(text));
    textAlgorithm->Layout(AceType::RawPtr(text));
    textLayoutProperty->UpdateGridOffset(text->GetHostNode());

    container->SwapDirtyLayoutWrapperOnMainThread();
}
} // namespace

class GridContainerTestNg : public testing::Test {
public:
    RefPtr<LayoutWrapperNode> CreateGridContainerWithChild()
    {
        GridContainerInfo::Builder builder;
        GridContainerModelNG modelNG;
        modelNG.Create(builder.Build());

        TextModelNG text;
        text.Create(u"child");
        textNode_ = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
        textNode_->GetLayoutProperty()->UpdateGridProperty(1, 1);
        ViewStackProcessor::GetInstance()->Pop();

        containerNode_ = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
        ViewStackProcessor::GetInstance()->Pop();

        auto layoutWrapper = containerNode_->CreateLayoutWrapper();
        LayoutConstraintF constraint;
        OptionalSizeF size;
        size.SetWidth(DEFAULT_WIDTH);
        constraint.UpdateIllegalSelfIdealSizeWithCheck(size);
        auto layoutProperty = layoutWrapper->GetLayoutProperty();
        layoutProperty->UpdateLayoutConstraint(constraint);
        auto geometryNode = layoutWrapper->GetGeometryNode();
        geometryNode->SetParentLayoutConstraint(constraint);
        layoutProperty->UpdateContentConstraint();

        return layoutWrapper;
    }

private:
    RefPtr<FrameNode> textNode_;
    RefPtr<FrameNode> containerNode_;
};

/**
 * @tc.name: DefaultProperty001
 * @tc.desc: Test default properties of grid-container.
 * @tc.type: FUNC
 */
HWTEST_F(GridContainerTestNg, DefaultProperty001, TestSize.Level0)
{
    GridContainerInfo::Builder builder;
    GridContainerModelNG modelNG;
    modelNG.Create(builder.Build());

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<GridContainerLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    auto clone = AceType::DynamicCast<GridContainerLayoutProperty>(layoutProperty->Clone());
    EXPECT_EQ(*clone, *layoutProperty);

    // rubbish code for coverity
    clone.Reset();
    auto json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json, filter);
}

/**
 * @tc.name: BuildContainer001
 * @tc.desc: Test GridContainer build width.
 * @tc.type: FUNC
 */
HWTEST_F(GridContainerTestNg, BuildContainer001, TestSize.Level0)
{
    auto layoutWrapper = CreateGridContainerWithChild();
    auto textWrapper = AceType::DynamicCast<LayoutWrapperNode>(layoutWrapper->GetOrCreateChildByIndex(0));

    /* update property to mark-dirty children */
    GridContainerInfo::Builder builder;
    builder.SetColumns(DEFAULT_COLUMN_NUM);
    builder.SetGutterWidth(Dimension());
    builder.SetMarginLeft(Dimension());
    builder.SetMarginRight(Dimension());
    builder.SetPaddingLeft(Dimension());
    builder.SetPaddingRight(Dimension());
    auto layoutProperty = AceType::DynamicCast<GridContainerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    layoutProperty->UpdateContainerInfo(*builder.Build());

    /* layout */
    MeasureLayout(layoutWrapper, textWrapper);
    auto rect = textWrapper->GetHostNode()->GetGeometryNode()->GetFrameRect();
    EXPECT_EQ(rect.Width(), 0);
    EXPECT_EQ(rect.GetX(), DEFAULT_COLUMN_WIDTH);
}
} // namespace OHOS::Ace::NG
