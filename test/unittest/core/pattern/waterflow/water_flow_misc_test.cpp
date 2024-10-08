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

#include <utility>

#include "test/mock/core/render/mock_render_context.h"
#include "test/unittest/core/pattern/scrollable/scrollable_test_utils.h"
#include "water_flow_test_ng.h"

#include "core/components_ng/pattern/scrollable/scrollable_paint_property.h"

namespace OHOS::Ace::NG {
/**
 * @tc.name: Clip001
 * @tc.desc: Test contentClip.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Clip001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    ViewAbstract::SetMargin(CalcLength(5.0f));
    ViewAbstract::SetPadding(CalcLength(5.0f));
    model.SetColumnsTemplate("1fr 1fr 1fr");
    CreateWaterFlowItems();
    CreateDone();

    auto ctx = AceType::DynamicCast<MockRenderContext>(frameNode_->GetRenderContext());
    ASSERT_TRUE(ctx);
    auto props = frameNode_->GetPaintProperty<ScrollablePaintProperty>();

    auto rect = AceType::MakeRefPtr<ShapeRect>();
    rect->SetWidth(Dimension(200.0f));
    rect->SetHeight(Dimension(200.0f));
    EXPECT_CALL(*ctx, SetContentClip(ClipRectEq(rect))).Times(1);
    props->UpdateContentClip({ ContentClipMode::CUSTOM, rect });
    FlushLayoutTask(frameNode_);

    EXPECT_EQ(frameNode_->GetGeometryNode()->GetPaddingSize(true), SizeF(470.0f, 790.0f));
    EXPECT_CALL(*ctx, SetContentClip(ClipRectEq(frameNode_->GetGeometryNode()->GetPaddingRect(true)))).Times(1);
    props->UpdateContentClip({ ContentClipMode::SAFE_AREA, nullptr });
    FlushLayoutTask(frameNode_);

    EXPECT_CALL(*ctx, SetContentClip(ClipRectEq(frameNode_->GetGeometryNode()->GetFrameRect()))).Times(1);
    props->UpdateContentClip({ ContentClipMode::BOUNDARY, nullptr });
    FlushLayoutTask(frameNode_);
}

/**
 * @tc.name: Clip002
 * @tc.desc: Test contentClip with relative offset.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Clip002, TestSize.Level1)
{
    RefPtr<UINode> col;
    CreateColumn([&](ColumnModelNG colModel) {
        ViewAbstract::SetMargin(CalcLength(5.0f));
        col = ViewStackProcessor::GetInstance()->GetMainElementNode();
    
        WaterFlowModelNG model = CreateWaterFlow();
        ViewAbstract::SetMargin(CalcLength(5.0f));
        ViewAbstract::SetPadding(CalcLength(5.0f));
        model.SetColumnsTemplate("1fr 1fr 1fr");
        CreateWaterFlowItems();
        CreateDone();
    });
    ASSERT_TRUE(col);
    auto ctx = AceType::DynamicCast<MockRenderContext>(frameNode_->GetRenderContext());
    ASSERT_TRUE(ctx);
    auto props = frameNode_->GetPaintProperty<ScrollablePaintProperty>();

    auto rect = AceType::MakeRefPtr<ShapeRect>();
    rect->SetWidth(Dimension(200.0f));
    rect->SetHeight(Dimension(200.0f));
    EXPECT_CALL(*ctx, SetContentClip(ClipRectEq(rect))).Times(1);
    props->UpdateContentClip({ ContentClipMode::CUSTOM, rect });
    FlushLayoutTask(frameNode_);

    EXPECT_EQ(frameNode_->GetGeometryNode()->GetPaddingSize(true), SizeF(470.0f, 790.0f));
    auto rect1 = frameNode_->GetGeometryNode()->GetPaddingRect();
    rect1.SetOffset(OffsetF(5.0f, 5.0f)); // padding offset
    EXPECT_CALL(*ctx, SetContentClip(ClipRectEq(rect1))).Times(1);
    props->UpdateContentClip({ ContentClipMode::CONTENT_ONLY, nullptr });
    FlushLayoutTask(frameNode_);

    auto rect2 = frameNode_->GetGeometryNode()->GetFrameRect();
    rect2.SetOffset(OffsetF(0.0f, 0.0f));
    EXPECT_CALL(*ctx, SetContentClip(ClipRectEq(rect2))).Times(1);
    props->UpdateContentClip({ ContentClipMode::BOUNDARY, nullptr });
    FlushLayoutTask(frameNode_);
}
} // namespace OHOS::Ace::NG