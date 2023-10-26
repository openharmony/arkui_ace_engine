/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/menu/menu_paint_method.h"

#include "base/utils/utils.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/pattern/menu/menu_paint_property.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/divider_painter.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension BEZIER_HORIZON_OFFSET_FIRST = 1.3_vp;
constexpr Dimension BEZIER_HORIZON_OFFSET_SECOND = 3.2_vp;
constexpr Dimension BEZIER_HORIZON_OFFSET_THIRD = 6.6_vp;
constexpr Dimension BEZIER_HORIZON_OFFSET_FOURTH = 16.0_vp;
constexpr Dimension BEZIER_VERTICAL_OFFSET_FIRST = 0.1_vp;
constexpr Dimension BEZIER_VERTICAL_OFFSET_SECOND = 3.0_vp;
constexpr Dimension BEZIER_VERTICAL_OFFSET_THIRD = 8.0_vp;
} // namespace

void MenuPaintMethod::GetTopPath(float arrowX, float arrowY, RSPath& path)
{
    path.MoveTo(arrowX - horizonOffsetForth_, arrowY - verticalOffsetThird_);
    path.QuadTo(arrowX - horizonOffsetThird_, arrowY - verticalOffsetThird_, arrowX - horizonOffsetSecond_,
        arrowY - verticalOffsetSecond_);
    path.QuadTo(arrowX - horizonOffsetFirst_, arrowY + verticalOffsetFirst_, arrowX, arrowY);
    path.QuadTo(arrowX + horizonOffsetFirst_, arrowY + verticalOffsetFirst_, arrowX + horizonOffsetSecond_,
        arrowY - verticalOffsetSecond_);
    path.QuadTo(arrowX + horizonOffsetThird_, arrowY - verticalOffsetThird_, arrowX + horizonOffsetForth_,
        arrowY - verticalOffsetThird_);
}

void MenuPaintMethod::GetBottomPath(float arrowX, float arrowY, RSPath& path)
{
    path.MoveTo(arrowX - horizonOffsetForth_, arrowY + verticalOffsetThird_);
    path.QuadTo(arrowX - horizonOffsetThird_, arrowY + verticalOffsetThird_, arrowX - horizonOffsetSecond_,
        arrowY + verticalOffsetSecond_);
    path.QuadTo(arrowX - horizonOffsetFirst_, arrowY - verticalOffsetFirst_, arrowX, arrowY);
    path.QuadTo(arrowX + horizonOffsetFirst_, arrowY - verticalOffsetFirst_, arrowX + horizonOffsetSecond_,
        arrowY + verticalOffsetSecond_);
    path.QuadTo(arrowX + horizonOffsetThird_, arrowY + verticalOffsetThird_, arrowX + horizonOffsetForth_,
        arrowY + verticalOffsetThird_);
}

void MenuPaintMethod::GetRightPath(float arrowX, float arrowY, RSPath& path)
{
    path.MoveTo(arrowX + verticalOffsetThird_, arrowY - horizonOffsetForth_);
    path.QuadTo(arrowX + verticalOffsetThird_, arrowY - horizonOffsetThird_, arrowX + verticalOffsetSecond_,
        arrowY - horizonOffsetSecond_);
    path.QuadTo(arrowX - verticalOffsetFirst_, arrowY - horizonOffsetFirst_, arrowX, arrowY);
    path.QuadTo(arrowX - verticalOffsetFirst_, arrowY + horizonOffsetFirst_, arrowX + verticalOffsetSecond_,
        arrowY + horizonOffsetSecond_);
    path.QuadTo(arrowX + verticalOffsetThird_, arrowY + horizonOffsetThird_, arrowX + verticalOffsetThird_,
        arrowY + horizonOffsetForth_);
}

void MenuPaintMethod::GetLeftPath(float arrowX, float arrowY, RSPath& path)
{
    path.MoveTo(arrowX - verticalOffsetThird_, arrowY - horizonOffsetForth_);
    path.QuadTo(arrowX - verticalOffsetThird_, arrowY - horizonOffsetThird_, arrowX - verticalOffsetSecond_,
        arrowY - horizonOffsetSecond_);
    path.QuadTo(arrowX + verticalOffsetFirst_, arrowY - horizonOffsetFirst_, arrowX, arrowY);
    path.QuadTo(arrowX + verticalOffsetFirst_, arrowY + horizonOffsetFirst_, arrowX - verticalOffsetSecond_,
        arrowY + horizonOffsetSecond_);
    path.QuadTo(arrowX - verticalOffsetThird_, arrowY + horizonOffsetThird_, arrowX - verticalOffsetThird_,
        arrowY + horizonOffsetForth_);
}

void MenuPaintMethod::UpdateArrowPath(Placement placement, float arrowX, float arrowY, RSPath& path)
{
    horizonOffsetFirst_ = BEZIER_HORIZON_OFFSET_FIRST.ConvertToPx();
    horizonOffsetSecond_ = BEZIER_HORIZON_OFFSET_SECOND.ConvertToPx();
    horizonOffsetThird_ = BEZIER_HORIZON_OFFSET_THIRD.ConvertToPx();
    horizonOffsetForth_ = BEZIER_HORIZON_OFFSET_FOURTH.ConvertToPx();
    verticalOffsetFirst_ = BEZIER_VERTICAL_OFFSET_FIRST.ConvertToPx();
    verticalOffsetSecond_ = BEZIER_VERTICAL_OFFSET_SECOND.ConvertToPx();
    verticalOffsetThird_ = BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx();
    switch (placement) {
        case Placement::TOP:
        case Placement::TOP_LEFT:
        case Placement::TOP_RIGHT:
            GetTopPath(arrowX, arrowY, path);
            break;
        case Placement::BOTTOM:
        case Placement::BOTTOM_LEFT:
        case Placement::BOTTOM_RIGHT:
            GetBottomPath(arrowX, arrowY, path);
            break;
        case Placement::RIGHT:
        case Placement::RIGHT_BOTTOM:
        case Placement::RIGHT_TOP:
            GetRightPath(arrowX, arrowY, path);
            break;
        case Placement::LEFT:
        case Placement::LEFT_BOTTOM:
        case Placement::LEFT_TOP:
            GetLeftPath(arrowX, arrowY, path);
            break;
        default:
            break;
    }
}

CanvasDrawFunction MenuPaintMethod::GetOverlayDrawFunction(PaintWrapper* paintWrapper)
{
    return [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
        auto menu = weak.Upgrade();
        if (menu) {
            auto props = DynamicCast<MenuPaintProperty>(paintWrapper->GetPaintProperty());
            CHECK_NULL_VOID(props);
            if (props->GetEnableArrow().has_value()) {
                if (!props->GetEnableArrow().value() || !props->GetArrowPosition().has_value() ||
                    !props->GetArrowPlacement().has_value()) {
                    return;
                }
                auto arrowPosition = props->GetArrowPosition().value();
                auto arrowPlaceMent = props->GetArrowPlacement().value();
                auto arrowX = arrowPosition.GetX();
                auto arrowY = arrowPosition.GetY();
                RSPath path;
                menu->UpdateArrowPath(arrowPlaceMent, arrowX, arrowY, path);
                RSBrush brush;
                auto pipeline = PipelineBase::GetCurrentContext();
                CHECK_NULL_VOID(pipeline);
                auto selectTheme = pipeline->GetTheme<SelectTheme>();
                CHECK_NULL_VOID(selectTheme);
                auto backgroundColor = selectTheme->GetBackgroundColor();
                brush.SetColor(static_cast<int>(backgroundColor.GetValue()));
                brush.SetAntiAlias(true);
                canvas.AttachBrush(brush);
                canvas.DrawPath(path);
            }
        }
    };
}
} // namespace OHOS::Ace::NG
