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
#include "water_flow_test_ng.h"

#include "core/components_ng/pattern/scrollable/scrollable_paint_property.h"

namespace OHOS::Ace::NG {

using Rect = std::variant<RectF, RefPtr<ShapeRect>>;

bool CmpClipRect(const Rect& lhs, const Rect& rhs)
{
    if (std::holds_alternative<RectF>(lhs) && std::holds_alternative<RectF>(rhs)) {
        return std::get<RectF>(lhs) == std::get<RectF>(rhs);
    }
    if (std::holds_alternative<RefPtr<ShapeRect>>(lhs) && std::holds_alternative<RefPtr<ShapeRect>>(rhs)) {
        auto&& shape1 = std::get<RefPtr<ShapeRect>>(lhs);
        auto&& shape2 = std::get<RefPtr<ShapeRect>>(rhs);
        return *shape1 == *shape2;
    }
    return false;
}

MATCHER_P(RectEq, expected, "clip rect variant")
{
    return CmpClipRect(arg, expected);
}

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
    EXPECT_CALL(*ctx, SetContentClip(RectEq(rect))).Times(1);
    props->UpdateContentClip({ ContentClipMode::CUSTOM, rect });
    FlushLayoutTask(frameNode_);

    EXPECT_EQ(frameNode_->GetGeometryNode()->GetPaddingSize(true), SizeF(470.0f, 790.0f));
    EXPECT_CALL(*ctx, SetContentClip(RectEq(frameNode_->GetGeometryNode()->GetPaddingRect(true)))).Times(1);
    props->UpdateContentClip({ ContentClipMode::SAFE_AREA, nullptr });
    FlushLayoutTask(frameNode_);

    EXPECT_CALL(*ctx, SetContentClip(RectEq(frameNode_->GetGeometryNode()->GetMarginFrameRect()))).Times(1);
    props->UpdateContentClip({ ContentClipMode::BOUNDARY, nullptr });
    FlushLayoutTask(frameNode_);
}
} // namespace OHOS::Ace::NG