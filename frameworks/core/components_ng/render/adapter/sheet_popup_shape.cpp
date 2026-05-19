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

#include "core/components_ng/render/sheet_popup_shape.h"
#ifdef ENABLE_ROSEN_BACKEND
#include "render_service_client/core/ui_effect/property/include/rs_ui_shape_base.h"
#endif

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension ARROW_VERTICAL_P1_OFFSET_X = 8.0_vp;
constexpr Dimension ARROW_VERTICAL_P5_OFFSET_X = 8.0_vp;
constexpr Dimension SDF_ARROW_VERTICAL_P3_OFFSET_Y = 9.0_vp;
constexpr Dimension SDF_ARROW_CORNER_P3_OFFSET_Y = 9.5_vp;
constexpr Dimension ARROW_RADIUS = 2.0_vp;
constexpr double SDF_ARROW_SCALING = 1.5f;
constexpr float SDF_UNION_SPACING = 0.1f;
constexpr float TRIANGLE_OFFSET_ADJUSTMENT = 0.5f;
// Enlarge the triangle and extend it into the rectangle
float Get2DLineExtForTriangleShape(float startLinePos, float endLinePos)
{
    return startLinePos + (endLinePos - startLinePos) * SDF_ARROW_SCALING;
}
void RadiusInfoLog(float radiusTopLeft, float radiusTopRight, float radiusBottomRight, float radiusBottomLeft)
{
    TAG_LOGD(AceLogTag::ACE_SHEET,
        "Popup SDFShape DrawClipPath RadiusInfoLog | "
        "radiusTopLeft:%{public}f,radiusTopRight:%{public}f,radiusBottomRight:%{public}f,radiusBottomLeft:%{public}f",
        radiusTopLeft, radiusTopRight, radiusBottomRight, radiusBottomLeft);
}
void GetPopupBottomTriangle(const SizeF& sheetSize, const SheetArrowPosition arrowPosition, const OffsetF& arrowOffset,
    OHOS::Rosen::Vector2f& vertex0, OHOS::Rosen::Vector2f& vertex1, OHOS::Rosen::Vector2f& vertex2)
{
    float arrowP1X = 0.f;
    float arrowP1Y = 0.f;
    float arrowP3X = 0.f;
    float arrowP3Y = 0.f;
    float arrowP5X = 0.f;
    float arrowP5Y = 0.f;

    if (arrowPosition == SheetArrowPosition::BOTTOM_LEFT) {
        arrowP1X = SHEET_ARROW_WIDTH.ConvertToPx();
        arrowP1Y = SHEET_ARROW_HEIGHT.ConvertToPx();
        arrowP3X = 0.f;
        arrowP3Y = (SHEET_ARROW_HEIGHT - SDF_ARROW_CORNER_P3_OFFSET_Y).ConvertToPx();
        arrowP5X = 0.f;
        arrowP5Y = SHEET_ARROW_HEIGHT.ConvertToPx();

        arrowP3X -= TRIANGLE_OFFSET_ADJUSTMENT;
        arrowP5X -= TRIANGLE_OFFSET_ADJUSTMENT;
    }
    if (arrowPosition == SheetArrowPosition::NONE) {
        arrowP1X = arrowOffset.GetX() - ARROW_VERTICAL_P1_OFFSET_X.ConvertToPx();
        arrowP1Y = SHEET_ARROW_HEIGHT.ConvertToPx();
        arrowP3X = arrowOffset.GetX();
        arrowP3Y = (SHEET_ARROW_HEIGHT - SDF_ARROW_VERTICAL_P3_OFFSET_Y).ConvertToPx();
        arrowP5X = arrowOffset.GetX() + ARROW_VERTICAL_P5_OFFSET_X.ConvertToPx();
        arrowP5Y = SHEET_ARROW_HEIGHT.ConvertToPx();
    }
    if (arrowPosition == SheetArrowPosition::BOTTOM_RIGHT) {
        arrowP1X = sheetSize.Width() - SHEET_ARROW_WIDTH.ConvertToPx();
        arrowP1Y = SHEET_ARROW_HEIGHT.ConvertToPx();
        arrowP3X = sheetSize.Width();
        arrowP3Y = (SHEET_ARROW_HEIGHT - SDF_ARROW_CORNER_P3_OFFSET_Y).ConvertToPx();
        arrowP5X = sheetSize.Width();
        arrowP5Y = SHEET_ARROW_HEIGHT.ConvertToPx();

        arrowP3X += TRIANGLE_OFFSET_ADJUSTMENT;
        arrowP5X += TRIANGLE_OFFSET_ADJUSTMENT;
    }

    float scalingArrowP1X = Get2DLineExtForTriangleShape(arrowP3X, arrowP1X);
    float scalingArrowP1Y = Get2DLineExtForTriangleShape(arrowP3Y, arrowP1Y);
    float scalingArrowP5X = Get2DLineExtForTriangleShape(arrowP3X, arrowP5X);
    float scalingArrowP5Y = Get2DLineExtForTriangleShape(arrowP3Y, arrowP5Y);

    vertex0 = OHOS::Rosen::Vector2f(scalingArrowP1X, scalingArrowP1Y); // P1
    vertex1 = OHOS::Rosen::Vector2f(arrowP3X, arrowP3Y); // P3
    vertex2 = OHOS::Rosen::Vector2f(scalingArrowP5X, scalingArrowP5Y); // P5
}

void GetPopupTopTriangle(const SizeF& sheetSize, const SheetArrowPosition arrowPosition, const OffsetF& arrowOffset,
    OHOS::Rosen::Vector2f& vertex0, OHOS::Rosen::Vector2f& vertex1, OHOS::Rosen::Vector2f& vertex2)
{
    float arrowP1X = 0.f;
    float arrowP1Y = 0.f;
    float arrowP3X = 0.f;
    float arrowP3Y = 0.f;
    float arrowP5X = 0.f;
    float arrowP5Y = 0.f;

    if (arrowPosition == SheetArrowPosition::TOP_LEFT) {
        arrowP1X = SHEET_ARROW_WIDTH.ConvertToPx();
        arrowP1Y = sheetSize.Height() - SHEET_ARROW_HEIGHT.ConvertToPx();
        arrowP3X = 0.f;
        arrowP3Y = sheetSize.Height() - (SHEET_ARROW_HEIGHT - SDF_ARROW_CORNER_P3_OFFSET_Y).ConvertToPx();
        arrowP5X = 0.f;
        arrowP5Y = sheetSize.Height() - SHEET_ARROW_HEIGHT.ConvertToPx();

        arrowP3X -= TRIANGLE_OFFSET_ADJUSTMENT;
        arrowP5X -= TRIANGLE_OFFSET_ADJUSTMENT;
    }
    if (arrowPosition == SheetArrowPosition::NONE) {
        arrowP1X = arrowOffset.GetX() + ARROW_VERTICAL_P1_OFFSET_X.ConvertToPx();
        arrowP1Y = sheetSize.Height() - SHEET_ARROW_HEIGHT.ConvertToPx();
        arrowP3X = arrowOffset.GetX();
        arrowP3Y = sheetSize.Height() - (SHEET_ARROW_HEIGHT - SDF_ARROW_VERTICAL_P3_OFFSET_Y).ConvertToPx();
        arrowP5X = arrowOffset.GetX() - ARROW_VERTICAL_P5_OFFSET_X.ConvertToPx();
        arrowP5Y = sheetSize.Height() - SHEET_ARROW_HEIGHT.ConvertToPx();
    }
    if (arrowPosition == SheetArrowPosition::TOP_RIGHT) {
        arrowP1X = sheetSize.Width() - SHEET_ARROW_WIDTH.ConvertToPx();
        arrowP1Y = sheetSize.Height() - SHEET_ARROW_HEIGHT.ConvertToPx();
        arrowP3X = sheetSize.Width();
        arrowP3Y = sheetSize.Height() - (SHEET_ARROW_HEIGHT - SDF_ARROW_CORNER_P3_OFFSET_Y).ConvertToPx();
        arrowP5X = sheetSize.Width();
        arrowP5Y = sheetSize.Height() - SHEET_ARROW_HEIGHT.ConvertToPx();

        arrowP3X += TRIANGLE_OFFSET_ADJUSTMENT;
        arrowP5X += TRIANGLE_OFFSET_ADJUSTMENT;
    }

    float scalingArrowP1X = Get2DLineExtForTriangleShape(arrowP3X, arrowP1X);
    float scalingArrowP1Y = Get2DLineExtForTriangleShape(arrowP3Y, arrowP1Y);
    float scalingArrowP5X = Get2DLineExtForTriangleShape(arrowP3X, arrowP5X);
    float scalingArrowP5Y = Get2DLineExtForTriangleShape(arrowP3Y, arrowP5Y);

    vertex0 = OHOS::Rosen::Vector2f(scalingArrowP1X, scalingArrowP1Y); // P1
    vertex1 = OHOS::Rosen::Vector2f(arrowP3X, arrowP3Y); // P3
    vertex2 = OHOS::Rosen::Vector2f(scalingArrowP5X, scalingArrowP5Y); // P5
}

void GetPopupLeftTriangle(const SizeF& sheetSize, const SheetArrowPosition arrowPosition, const OffsetF& arrowOffset,
    OHOS::Rosen::Vector2f& vertex0, OHOS::Rosen::Vector2f& vertex1, OHOS::Rosen::Vector2f& vertex2)
{
    float arrowP1X = 0.f;
    float arrowP1Y = 0.f;
    float arrowP3X = 0.f;
    float arrowP3Y = 0.f;
    float arrowP5X = 0.f;
    float arrowP5Y = 0.f;

    if (arrowPosition == SheetArrowPosition::LEFT_TOP) {
        arrowP1X = sheetSize.Width() - SHEET_ARROW_HEIGHT.ConvertToPx();
        arrowP1Y = SHEET_ARROW_WIDTH.ConvertToPx();
        arrowP3X = sheetSize.Width() - (SHEET_ARROW_HEIGHT - SDF_ARROW_CORNER_P3_OFFSET_Y).ConvertToPx();
        arrowP3Y = 0.f;
        arrowP5X = sheetSize.Width() - SHEET_ARROW_HEIGHT.ConvertToPx();
        arrowP5Y = 0.f;

        arrowP3Y -= TRIANGLE_OFFSET_ADJUSTMENT;
        arrowP5Y -= TRIANGLE_OFFSET_ADJUSTMENT;
    }
    if (arrowPosition == SheetArrowPosition::NONE) {
        arrowP1X = sheetSize.Width() - SHEET_ARROW_HEIGHT.ConvertToPx();
        arrowP1Y = arrowOffset.GetY() - ARROW_VERTICAL_P1_OFFSET_X.ConvertToPx();
        arrowP3X = sheetSize.Width() - (SHEET_ARROW_HEIGHT - SDF_ARROW_VERTICAL_P3_OFFSET_Y).ConvertToPx();
        arrowP3Y = arrowOffset.GetY();
        arrowP5X = sheetSize.Width() - SHEET_ARROW_HEIGHT.ConvertToPx();
        arrowP5Y = arrowOffset.GetY() + ARROW_VERTICAL_P5_OFFSET_X.ConvertToPx();
    }
    if (arrowPosition == SheetArrowPosition::LEFT_BOTTOM) {
        arrowP1X = sheetSize.Width() - SHEET_ARROW_HEIGHT.ConvertToPx();
        arrowP1Y = sheetSize.Height() - SHEET_ARROW_WIDTH.ConvertToPx();
        arrowP3X = sheetSize.Width() - (SHEET_ARROW_HEIGHT - SDF_ARROW_CORNER_P3_OFFSET_Y).ConvertToPx();
        arrowP3Y = sheetSize.Height();
        arrowP5X = sheetSize.Width() - SHEET_ARROW_HEIGHT.ConvertToPx();
        arrowP5Y = sheetSize.Height();

        arrowP3Y += TRIANGLE_OFFSET_ADJUSTMENT;
        arrowP5Y += TRIANGLE_OFFSET_ADJUSTMENT;
    }

    float scalingArrowP1X = Get2DLineExtForTriangleShape(arrowP3X, arrowP1X);
    float scalingArrowP1Y = Get2DLineExtForTriangleShape(arrowP3Y, arrowP1Y);
    float scalingArrowP5X = Get2DLineExtForTriangleShape(arrowP3X, arrowP5X);
    float scalingArrowP5Y = Get2DLineExtForTriangleShape(arrowP3Y, arrowP5Y);

    vertex0 = OHOS::Rosen::Vector2f(scalingArrowP1X, scalingArrowP1Y); // P1
    vertex1 = OHOS::Rosen::Vector2f(arrowP3X, arrowP3Y); // P3
    vertex2 = OHOS::Rosen::Vector2f(scalingArrowP5X, scalingArrowP5Y); // P5
}

void GetPopupRightTriangle(const SizeF& sheetSize, const SheetArrowPosition arrowPosition, const OffsetF& arrowOffset,
    OHOS::Rosen::Vector2f& vertex0, OHOS::Rosen::Vector2f& vertex1, OHOS::Rosen::Vector2f& vertex2)
{
    float arrowP1X = 0.f;
    float arrowP1Y = 0.f;
    float arrowP3X = 0.f;
    float arrowP3Y = 0.f;
    float arrowP5X = 0.f;
    float arrowP5Y = 0.f;

    if (arrowPosition == SheetArrowPosition::RIGHT_TOP) {
        arrowP1X = SHEET_ARROW_HEIGHT.ConvertToPx();
        arrowP1Y = SHEET_ARROW_WIDTH.ConvertToPx();
        arrowP3X = (SHEET_ARROW_HEIGHT - SDF_ARROW_CORNER_P3_OFFSET_Y).ConvertToPx();
        arrowP3Y = 0.f;
        arrowP5X = SHEET_ARROW_HEIGHT.ConvertToPx();
        arrowP5Y = 0.f;

        arrowP3Y -= TRIANGLE_OFFSET_ADJUSTMENT;
        arrowP5Y -= TRIANGLE_OFFSET_ADJUSTMENT;
    }
    if (arrowPosition == SheetArrowPosition::NONE) {
        arrowP1X = SHEET_ARROW_HEIGHT.ConvertToPx();
        arrowP1Y = arrowOffset.GetY() - ARROW_VERTICAL_P1_OFFSET_X.ConvertToPx();
        arrowP3X = (SHEET_ARROW_HEIGHT - SDF_ARROW_VERTICAL_P3_OFFSET_Y).ConvertToPx();
        arrowP3Y = arrowOffset.GetY();
        arrowP5X = SHEET_ARROW_HEIGHT.ConvertToPx();
        arrowP5Y = arrowOffset.GetY() + ARROW_VERTICAL_P5_OFFSET_X.ConvertToPx();
    }
    if (arrowPosition == SheetArrowPosition::RIGHT_BOTTOM) {
        arrowP1X = SHEET_ARROW_HEIGHT.ConvertToPx();
        arrowP1Y = sheetSize.Height() - SHEET_ARROW_WIDTH.ConvertToPx();
        arrowP3X = (SHEET_ARROW_HEIGHT - SDF_ARROW_CORNER_P3_OFFSET_Y).ConvertToPx();
        arrowP3Y = sheetSize.Height();
        arrowP5X = SHEET_ARROW_HEIGHT.ConvertToPx();
        arrowP5Y = sheetSize.Height();

        arrowP3Y += TRIANGLE_OFFSET_ADJUSTMENT;
        arrowP5Y += TRIANGLE_OFFSET_ADJUSTMENT;
    }

    float scalingArrowP1X = Get2DLineExtForTriangleShape(arrowP3X, arrowP1X);
    float scalingArrowP1Y = Get2DLineExtForTriangleShape(arrowP3Y, arrowP1Y);
    float scalingArrowP5X = Get2DLineExtForTriangleShape(arrowP3X, arrowP5X);
    float scalingArrowP5Y = Get2DLineExtForTriangleShape(arrowP3Y, arrowP5Y);

    vertex0 = OHOS::Rosen::Vector2f(scalingArrowP1X, scalingArrowP1Y); // P1
    vertex1 = OHOS::Rosen::Vector2f(arrowP3X, arrowP3Y); // P3
    vertex2 = OHOS::Rosen::Vector2f(scalingArrowP5X, scalingArrowP5Y); // P5
}
} // namespace
std::shared_ptr<OHOS::Rosen::RSNGShapeBase> SheetPopupShape::DrawClipPathBottomSDF(const SizeF& sheetSize,
    const NG::BorderRadiusProperty& sheetRadius, const SheetArrowPosition arrowPosition, const OffsetF& arrowOffset)
{
    auto unionShape = OHOS::Rosen::RSNGShapeBase::Create(OHOS::Rosen::RSNGEffectType::SDF_SMOOTH_UNION_OP_SHAPE);
    float radiusTopLeft = sheetRadius.radiusTopLeft->ConvertToPx();
    float radiusTopRight = sheetRadius.radiusTopRight->ConvertToPx();
    float radiusBottomRight = sheetRadius.radiusBottomRight->ConvertToPx();
    float radiusBottomLeft = sheetRadius.radiusBottomLeft->ConvertToPx();
    if (arrowPosition == SheetArrowPosition::BOTTOM_LEFT) {
        radiusTopLeft = 0.f;
    }
    if (arrowPosition == SheetArrowPosition::BOTTOM_RIGHT) {
        radiusTopRight = 0.f;
    }
    RadiusInfoLog(radiusTopLeft, radiusTopRight, radiusBottomRight, radiusBottomLeft);
    OHOS::Rosen::RRect rectParams(
        OHOS::Rosen::RectF(0.f, static_cast<float>(SHEET_ARROW_HEIGHT.ConvertToPx()), sheetSize.Width(),
            sheetSize.Height() - static_cast<float>(SHEET_ARROW_HEIGHT.ConvertToPx())),
        OHOS::Rosen::Vector4(radiusTopLeft, radiusTopRight, radiusBottomRight, radiusBottomLeft));
    auto rectShape = OHOS::Rosen::RSNGShapeBase::Create(OHOS::Rosen::RSNGEffectType::SDF_RRECT_SHAPE);
    auto rectShapeModify = std::static_pointer_cast<OHOS::Rosen::RSNGSDFRRectShape>(rectShape);
    CHECK_NULL_RETURN(rectShapeModify, nullptr);
    rectShapeModify->Setter<OHOS::Rosen::SDFRRectShapeRRectTag>(rectParams);

    auto triangleShape = OHOS::Rosen::RSNGShapeBase::Create(OHOS::Rosen::RSNGEffectType::SDF_TRIANGLE_SHAPE);
    auto triangleShapeModify = std::static_pointer_cast<OHOS::Rosen::RSNGSDFTriangleShape>(triangleShape);
    CHECK_NULL_RETURN(triangleShapeModify, nullptr);

    float arrowRadius0 = ARROW_RADIUS.ConvertToPx();
    OHOS::Rosen::Vector2f vertex0 = OHOS::Rosen::Vector2f(0.f, 0.f);
    OHOS::Rosen::Vector2f vertex1 = OHOS::Rosen::Vector2f(0.f, 0.f);
    OHOS::Rosen::Vector2f vertex2 = OHOS::Rosen::Vector2f(0.f, 0.f);
    GetPopupBottomTriangle(sheetSize, arrowPosition, arrowOffset, vertex0, vertex1, vertex2);

    triangleShapeModify->Setter<OHOS::Rosen::SDFTriangleShapeVertex0Tag>(vertex0);
    triangleShapeModify->Setter<OHOS::Rosen::SDFTriangleShapeVertex1Tag>(vertex1);
    triangleShapeModify->Setter<OHOS::Rosen::SDFTriangleShapeVertex2Tag>(vertex2);
    triangleShapeModify->Setter<OHOS::Rosen::SDFTriangleShapeRadiusTag>(arrowRadius0);

    auto unionShapeModify = std::static_pointer_cast<OHOS::Rosen::RSNGSDFSmoothUnionOpShape>(unionShape);
    CHECK_NULL_RETURN(unionShapeModify, nullptr);
    unionShapeModify->Setter<OHOS::Rosen::SDFSmoothUnionOpShapeShapeXTag>(rectShape);
    unionShapeModify->Setter<OHOS::Rosen::SDFSmoothUnionOpShapeShapeYTag>(triangleShape);
    unionShapeModify->Setter<OHOS::Rosen::SDFSmoothUnionOpShapeSpacingTag>(SDF_UNION_SPACING);

    return unionShape;
}

std::shared_ptr<OHOS::Rosen::RSNGShapeBase> SheetPopupShape::DrawClipPathTopSDF(const SizeF& sheetSize,
    const NG::BorderRadiusProperty& sheetRadius, const SheetArrowPosition arrowPosition, const OffsetF& arrowOffset)
{
    auto unionShape = OHOS::Rosen::RSNGShapeBase::Create(OHOS::Rosen::RSNGEffectType::SDF_SMOOTH_UNION_OP_SHAPE);
    float radiusTopLeft = sheetRadius.radiusTopLeft->ConvertToPx();
    float radiusTopRight = sheetRadius.radiusTopRight->ConvertToPx();
    float radiusBottomRight = sheetRadius.radiusBottomRight->ConvertToPx();
    float radiusBottomLeft = sheetRadius.radiusBottomLeft->ConvertToPx();
    if (arrowPosition == SheetArrowPosition::TOP_LEFT) {
        radiusBottomLeft = 0.f;
    }
    if (arrowPosition == SheetArrowPosition::TOP_RIGHT) {
        radiusBottomRight = 0.f;
    }
    RadiusInfoLog(radiusTopLeft, radiusTopRight, radiusBottomRight, radiusBottomLeft);
    OHOS::Rosen::RRect rectParams(OHOS::Rosen::RectF(0.f, 0.f, sheetSize.Width(),
                                      static_cast<float>(sheetSize.Height() - SHEET_ARROW_HEIGHT.ConvertToPx())),
        OHOS::Rosen::Vector4(radiusTopLeft, radiusTopRight, radiusBottomRight, radiusBottomLeft));
    auto rectShape = OHOS::Rosen::RSNGShapeBase::Create(OHOS::Rosen::RSNGEffectType::SDF_RRECT_SHAPE);
    auto rectShapeModify = std::static_pointer_cast<OHOS::Rosen::RSNGSDFRRectShape>(rectShape);
    CHECK_NULL_RETURN(rectShapeModify, nullptr);
    rectShapeModify->Setter<OHOS::Rosen::SDFRRectShapeRRectTag>(rectParams);

    auto triangleShape = OHOS::Rosen::RSNGShapeBase::Create(OHOS::Rosen::RSNGEffectType::SDF_TRIANGLE_SHAPE);
    auto triangleShapeModify = std::static_pointer_cast<OHOS::Rosen::RSNGSDFTriangleShape>(triangleShape);
    CHECK_NULL_RETURN(triangleShapeModify, nullptr);

    float arrowRadius0 = ARROW_RADIUS.ConvertToPx();
    OHOS::Rosen::Vector2f vertex0 = OHOS::Rosen::Vector2f(0.f, 0.f);
    OHOS::Rosen::Vector2f vertex1 = OHOS::Rosen::Vector2f(0.f, 0.f);
    OHOS::Rosen::Vector2f vertex2 = OHOS::Rosen::Vector2f(0.f, 0.f);
    GetPopupTopTriangle(sheetSize, arrowPosition, arrowOffset, vertex0, vertex1, vertex2);

    triangleShapeModify->Setter<OHOS::Rosen::SDFTriangleShapeVertex0Tag>(vertex0);
    triangleShapeModify->Setter<OHOS::Rosen::SDFTriangleShapeVertex1Tag>(vertex1);
    triangleShapeModify->Setter<OHOS::Rosen::SDFTriangleShapeVertex2Tag>(vertex2);
    triangleShapeModify->Setter<OHOS::Rosen::SDFTriangleShapeRadiusTag>(arrowRadius0);

    auto unionShapeModify = std::static_pointer_cast<OHOS::Rosen::RSNGSDFSmoothUnionOpShape>(unionShape);
    CHECK_NULL_RETURN(unionShapeModify, nullptr);
    unionShapeModify->Setter<OHOS::Rosen::SDFSmoothUnionOpShapeShapeXTag>(rectShape);
    unionShapeModify->Setter<OHOS::Rosen::SDFSmoothUnionOpShapeShapeYTag>(triangleShape);
    unionShapeModify->Setter<OHOS::Rosen::SDFSmoothUnionOpShapeSpacingTag>(SDF_UNION_SPACING);

    return unionShape;
}

std::shared_ptr<OHOS::Rosen::RSNGShapeBase> SheetPopupShape::DrawClipPathLeftSDF(const SizeF& sheetSize,
    const NG::BorderRadiusProperty& sheetRadius, const SheetArrowPosition arrowPosition, const OffsetF& arrowOffset)
{
    auto unionShape = OHOS::Rosen::RSNGShapeBase::Create(OHOS::Rosen::RSNGEffectType::SDF_SMOOTH_UNION_OP_SHAPE);
    float radiusTopLeft = sheetRadius.radiusTopLeft->ConvertToPx();
    float radiusTopRight = sheetRadius.radiusTopRight->ConvertToPx();
    float radiusBottomRight = sheetRadius.radiusBottomRight->ConvertToPx();
    float radiusBottomLeft = sheetRadius.radiusBottomLeft->ConvertToPx();
    if (arrowPosition == SheetArrowPosition::LEFT_TOP) {
        radiusTopRight = 0.f;
    }
    if (arrowPosition == SheetArrowPosition::LEFT_BOTTOM) {
        radiusBottomRight = 0.f;
    }
    RadiusInfoLog(radiusTopLeft, radiusTopRight, radiusBottomRight, radiusBottomLeft);
    OHOS::Rosen::RRect rectParams(
        OHOS::Rosen::RectF(
            0.f, 0.f, static_cast<float>(sheetSize.Width() - SHEET_ARROW_HEIGHT.ConvertToPx()), sheetSize.Height()),
        OHOS::Rosen::Vector4(radiusTopLeft, radiusTopRight, radiusBottomRight, radiusBottomLeft));
    auto rectShape = OHOS::Rosen::RSNGShapeBase::Create(OHOS::Rosen::RSNGEffectType::SDF_RRECT_SHAPE);
    auto rectShapeModify = std::static_pointer_cast<OHOS::Rosen::RSNGSDFRRectShape>(rectShape);
    CHECK_NULL_RETURN(rectShapeModify, nullptr);
    rectShapeModify->Setter<OHOS::Rosen::SDFRRectShapeRRectTag>(rectParams);

    auto triangleShape = OHOS::Rosen::RSNGShapeBase::Create(OHOS::Rosen::RSNGEffectType::SDF_TRIANGLE_SHAPE);
    auto triangleShapeModify = std::static_pointer_cast<OHOS::Rosen::RSNGSDFTriangleShape>(triangleShape);
    CHECK_NULL_RETURN(triangleShapeModify, nullptr);

    float arrowRadius0 = ARROW_RADIUS.ConvertToPx();
    OHOS::Rosen::Vector2f vertex0 = OHOS::Rosen::Vector2f(0.f, 0.f);
    OHOS::Rosen::Vector2f vertex1 = OHOS::Rosen::Vector2f(0.f, 0.f);
    OHOS::Rosen::Vector2f vertex2 = OHOS::Rosen::Vector2f(0.f, 0.f);
    GetPopupLeftTriangle(sheetSize, arrowPosition, arrowOffset, vertex0, vertex1, vertex2);

    triangleShapeModify->Setter<OHOS::Rosen::SDFTriangleShapeVertex0Tag>(vertex0);
    triangleShapeModify->Setter<OHOS::Rosen::SDFTriangleShapeVertex1Tag>(vertex1);
    triangleShapeModify->Setter<OHOS::Rosen::SDFTriangleShapeVertex2Tag>(vertex2);
    triangleShapeModify->Setter<OHOS::Rosen::SDFTriangleShapeRadiusTag>(arrowRadius0);

    auto unionShapeModify = std::static_pointer_cast<OHOS::Rosen::RSNGSDFSmoothUnionOpShape>(unionShape);
    CHECK_NULL_RETURN(unionShapeModify, nullptr);
    unionShapeModify->Setter<OHOS::Rosen::SDFSmoothUnionOpShapeShapeXTag>(rectShape);
    unionShapeModify->Setter<OHOS::Rosen::SDFSmoothUnionOpShapeShapeYTag>(triangleShape);
    unionShapeModify->Setter<OHOS::Rosen::SDFSmoothUnionOpShapeSpacingTag>(SDF_UNION_SPACING);

    return unionShape;
}

std::shared_ptr<OHOS::Rosen::RSNGShapeBase> SheetPopupShape::DrawClipPathRightSDF(const SizeF& sheetSize,
    const NG::BorderRadiusProperty& sheetRadius, const SheetArrowPosition arrowPosition, const OffsetF& arrowOffset)
{
    auto unionShape = OHOS::Rosen::RSNGShapeBase::Create(OHOS::Rosen::RSNGEffectType::SDF_SMOOTH_UNION_OP_SHAPE);
    float radiusTopLeft = sheetRadius.radiusTopLeft->ConvertToPx();
    float radiusTopRight = sheetRadius.radiusTopRight->ConvertToPx();
    float radiusBottomRight = sheetRadius.radiusBottomRight->ConvertToPx();
    float radiusBottomLeft = sheetRadius.radiusBottomLeft->ConvertToPx();
    if (arrowPosition == SheetArrowPosition::RIGHT_TOP) {
        radiusTopLeft = 0.f;
    }
    if (arrowPosition == SheetArrowPosition::RIGHT_BOTTOM) {
        radiusBottomLeft = 0.f;
    }
    RadiusInfoLog(radiusTopLeft, radiusTopRight, radiusBottomRight, radiusBottomLeft);
    OHOS::Rosen::RRect rectParams(
        OHOS::Rosen::RectF(static_cast<float>(SHEET_ARROW_HEIGHT.ConvertToPx()), 0.f,
            static_cast<float>(sheetSize.Width() - SHEET_ARROW_HEIGHT.ConvertToPx()), sheetSize.Height()),
        OHOS::Rosen::Vector4(radiusTopLeft, radiusTopRight, radiusBottomRight, radiusBottomLeft));
    auto rectShape = OHOS::Rosen::RSNGShapeBase::Create(OHOS::Rosen::RSNGEffectType::SDF_RRECT_SHAPE);
    auto rectShapeModify = std::static_pointer_cast<OHOS::Rosen::RSNGSDFRRectShape>(rectShape);
    CHECK_NULL_RETURN(rectShapeModify, nullptr);
    rectShapeModify->Setter<OHOS::Rosen::SDFRRectShapeRRectTag>(rectParams);

    auto triangleShape = OHOS::Rosen::RSNGShapeBase::Create(OHOS::Rosen::RSNGEffectType::SDF_TRIANGLE_SHAPE);
    auto triangleShapeModify = std::static_pointer_cast<OHOS::Rosen::RSNGSDFTriangleShape>(triangleShape);
    CHECK_NULL_RETURN(triangleShapeModify, nullptr);

    float arrowRadius0 = ARROW_RADIUS.ConvertToPx();
    OHOS::Rosen::Vector2f vertex0 = OHOS::Rosen::Vector2f(0.f, 0.f);
    OHOS::Rosen::Vector2f vertex1 = OHOS::Rosen::Vector2f(0.f, 0.f);
    OHOS::Rosen::Vector2f vertex2 = OHOS::Rosen::Vector2f(0.f, 0.f);
    GetPopupRightTriangle(sheetSize, arrowPosition, arrowOffset, vertex0, vertex1, vertex2);

    triangleShapeModify->Setter<OHOS::Rosen::SDFTriangleShapeVertex0Tag>(vertex0);
    triangleShapeModify->Setter<OHOS::Rosen::SDFTriangleShapeVertex1Tag>(vertex1);
    triangleShapeModify->Setter<OHOS::Rosen::SDFTriangleShapeVertex2Tag>(vertex2);
    triangleShapeModify->Setter<OHOS::Rosen::SDFTriangleShapeRadiusTag>(arrowRadius0);

    auto unionShapeModify = std::static_pointer_cast<OHOS::Rosen::RSNGSDFSmoothUnionOpShape>(unionShape);
    CHECK_NULL_RETURN(unionShapeModify, nullptr);
    unionShapeModify->Setter<OHOS::Rosen::SDFSmoothUnionOpShapeShapeXTag>(rectShape);
    unionShapeModify->Setter<OHOS::Rosen::SDFSmoothUnionOpShapeShapeYTag>(triangleShape);
    unionShapeModify->Setter<OHOS::Rosen::SDFSmoothUnionOpShapeSpacingTag>(SDF_UNION_SPACING);

    return unionShape;
}

std::shared_ptr<OHOS::Rosen::RSNGShapeBase> SheetPopupShape::GetPopupStyleSheetClipPathSDF(const SizeF& sheetSize,
    const NG::BorderRadiusProperty& sheetRadius, const Placement placement, const SheetArrowPosition arrowPosition,
    const OffsetF& arrowOffset)
{
    std::shared_ptr<OHOS::Rosen::RSNGShapeBase> sdfShape = nullptr;
    switch (placement) {
        case Placement::BOTTOM_LEFT:
            [[fallthrough]];
        case Placement::BOTTOM_RIGHT:
            [[fallthrough]];
        case Placement::BOTTOM: {
            sdfShape = DrawClipPathBottomSDF(sheetSize, sheetRadius, arrowPosition, arrowOffset);
            break;
        }
        case Placement::TOP_LEFT:
            [[fallthrough]];
        case Placement::TOP_RIGHT:
            [[fallthrough]];
        case Placement::TOP: {
            sdfShape = DrawClipPathTopSDF(sheetSize, sheetRadius, arrowPosition, arrowOffset);
            break;
        }
        case Placement::RIGHT_TOP:
            [[fallthrough]];
        case Placement::RIGHT_BOTTOM:
            [[fallthrough]];
        case Placement::RIGHT: {
            sdfShape = DrawClipPathRightSDF(sheetSize, sheetRadius, arrowPosition, arrowOffset);
            break;
        }
        case Placement::LEFT_TOP:
            [[fallthrough]];
        case Placement::LEFT_BOTTOM:
            [[fallthrough]];
        case Placement::LEFT: {
            sdfShape = DrawClipPathLeftSDF(sheetSize, sheetRadius, arrowPosition, arrowOffset);
            break;
        }
        default:
            break;
    }
    return sdfShape;
}
} // namespace OHOS::Ace::NG