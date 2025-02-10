/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECT_OVERLAY_CONTENT_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECT_OVERLAY_CONTENT_MODIFIER_H

#include <optional>
#include <vector>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/vector.h"
#include "base/memory/ace_type.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

struct HandleDrawInfo {
    OffsetF startPoint;
    OffsetF endPoint;
    OffsetF centerOffset;
    float handleWidth = 0.0f;
    bool isHandleLineShow = true;
    bool isCircleShow = true;
};

struct PaintHandleParams {
    bool isHandleLineShow = true;
    bool isCircleShow = true;
    bool isDragging = false;
};

class SelectOverlayContentModifier : public ContentModifier {
    DECLARE_ACE_TYPE(SelectOverlayContentModifier, ContentModifier)

public:
    SelectOverlayContentModifier(const WeakPtr<Pattern>& pattern);

    ~SelectOverlayContentModifier() override = default;

    void onDraw(DrawingContext& drawingContext) override;

    void SetInShowArea(bool inShowArea)
    {
        CHECK_NULL_VOID(inShowArea_);
        inShowArea_->Set(inShowArea);
    }

    void SetHandleReverse(bool reverse)
    {
        CHECK_NULL_VOID(handleReverse_);
        handleReverse_->Set(reverse);
    }

    void SetIsSingleHandle(bool isSingle)
    {
        CHECK_NULL_VOID(isSingleHandle_);
        isSingleHandle_->Set(isSingle);
    }

    void SetFirstHandleIsShow(bool isShow)
    {
        CHECK_NULL_VOID(firstHandleIsShow_);
        firstHandleIsShow_->Set(isShow);
    }

    void SetFirstCircleIsShow(bool isShow)
    {
        CHECK_NULL_VOID(firstCircleIsShow_);
        firstCircleIsShow_->Set(isShow);
    }

    void SetSecondHandleIsShow(bool isShow)
    {
        CHECK_NULL_VOID(secondHandleIsShow_);
        secondHandleIsShow_->Set(isShow);
    }

    void SetSecondCircleIsShow(bool isShow)
    {
        CHECK_NULL_VOID(secondCircleIsShow_);
        secondCircleIsShow_->Set(isShow);
    }

    void SetIsHiddenHandle(bool isHidden)
    {
        CHECK_NULL_VOID(isHiddenHandle_);
        isHiddenHandle_->Set(isHidden);
    }

    void SetIsHandleLineShow(bool isShow)
    {
        CHECK_NULL_VOID(isHandleLineShow_);
        isHandleLineShow_->Set(isShow);
    }

    void SetViewPort(const RectF& viewPort)
    {
        CHECK_NULL_VOID(viewPort_);
        viewPort_->Set(viewPort);
    }

    void SetFirstHandle(const RectF& handle)
    {
        CHECK_NULL_VOID(firstHandle_);
        firstHandle_->Set(handle);
    }

    void SetSecondHandle(const RectF& handle)
    {
        CHECK_NULL_VOID(secondHandle_);
        secondHandle_->Set(handle);
    }

    void SetHandleColor(const Color& color)
    {
        CHECK_NULL_VOID(handleColor_);
        handleColor_->Set(color);
    }

    void SetInnerHandleColor(const Color& color)
    {
        CHECK_NULL_VOID(innerHandleColor_);
        innerHandleColor_->Set(color);
    }

    void SetHandleRadius(float radius)
    {
        CHECK_NULL_VOID(handleRadius_);
        handleRadius_->Set(radius);
    }

    void SetHandleStrokeWidth(float width)
    {
        CHECK_NULL_VOID(handleStrokeWidth_);
        handleStrokeWidth_->Set(width);
    }

    void SetInnerHandleRadius(float radius)
    {
        CHECK_NULL_VOID(innerHandleRadius_);
        innerHandleRadius_->Set(radius);
    }

    void SetHandleOpacity(float opacity)
    {
        CHECK_NULL_VOID(handleOpacity_);
        handleOpacity_->Set(opacity);
    }
    
    void SetIsUsingMouse(bool value)
    {
        isUsingMouse_ = value;
    }

    void SetSecondHandlePaintInfo(const SelectHandlePaintInfo& paintInfo)
    {
        secondHandlePaintInfo_ = paintInfo;
    }

    void SetFirstHandlePaintInfo(const SelectHandlePaintInfo& paintInfo)
    {
        firstHandlePaintInfo_ = paintInfo;
    }

    void SetPaintHandleUsePoints(bool isPaintHandleUsePoints)
    {
        isPaintHandleUsePoints_ = isPaintHandleUsePoints;
    }

    static OffsetF CalculateCenterPoint(const OffsetF& start, const OffsetF& end, float radius, bool handleOnTop);

    void SetIsOverlayMode(bool isOverlayMode)
    {
        isOverlayMode_ = isOverlayMode;
    }

    void SetScale(const VectorF& scale)
    {
        scale_ = scale;
    }

    void SetClipHandleDrawRect(bool isClipHandleDrawRect)
    {
        isClipHandleDrawRect_ = isClipHandleDrawRect;
    }

    RefPtr<Pattern> GetSelectOverlayPattern() const
    {
        return pattern_.Upgrade();
    }

private:
    void PaintHandle(RSCanvas& canvas, const RectF& handleRect, bool handleOnTop, const PaintHandleParams& params);
    void PaintHandle(RSCanvas& canvas, const HandleDrawInfo& handleInfo);
    void PaintHandleLine(RSCanvas& canvas, const HandleDrawInfo& handleInfo, Color handleColor);

    void PaintSingleHandle(RSCanvas& canvas);
    bool PaintSingleHandleWithPoints(RSCanvas& canvas);
    void PaintSingleHandleWithRect(RSCanvas& canvas);

    bool PaintDoubleHandleWithPoint(RSCanvas& canvas);
    void PaintDoubleHandleWithRect(RSCanvas& canvas);
    void PaintDoubleHandle(RSCanvas& canvas);

    void ClipViewPort(RSCanvas& canvas);
    void ClipHandleDrawRect(RSCanvas& canvas, const RectF& handleRect, bool handleOnTop, bool isDragging);
    RectF ConvertPointsToRect(const SelectHandlePaintInfo& paintInfo) const;
    RectF GetFirstPaintRect() const;
    RectF GetSecondPaintRect() const;

    float GetDrawHandleRadius()
    {
        return handleRadius_->Get() + handleStrokeWidth_->Get() / 2.0f;
    }
    bool CheckHandleCircleIsShow(const RectF& handlRect);
    bool IsDraggingHandle(bool isFirst);

    RefPtr<PropertyBool> inShowArea_;
    RefPtr<PropertyBool> handleReverse_;
    RefPtr<PropertyBool> isSingleHandle_;
    RefPtr<PropertyBool> firstHandleIsShow_;
    RefPtr<PropertyBool> firstCircleIsShow_;
    RefPtr<PropertyBool> secondHandleIsShow_;
    RefPtr<PropertyBool> secondCircleIsShow_;
    RefPtr<PropertyBool> isHiddenHandle_;
    RefPtr<PropertyBool> isHandleLineShow_;
    RefPtr<PropertyRectF> viewPort_;
    RefPtr<PropertyRectF> firstHandle_;
    RefPtr<PropertyRectF> secondHandle_;
    RefPtr<PropertyColor> handleColor_;
    RefPtr<PropertyColor> innerHandleColor_;
    RefPtr<PropertyFloat> handleRadius_;
    RefPtr<PropertyFloat> handleStrokeWidth_;
    RefPtr<PropertyFloat> innerHandleRadius_;
    RefPtr<AnimatablePropertyFloat> handleOpacity_;
    bool isUsingMouse_ = false;
    bool isPaintHandleUsePoints_ = false;
    SelectHandlePaintInfo firstHandlePaintInfo_;
    SelectHandlePaintInfo secondHandlePaintInfo_;
    bool isOverlayMode_ = true;
    bool isClipHandleDrawRect_ = false;
    VectorF scale_ = VectorF(1.0f, 1.0f);
    WeakPtr<Pattern> pattern_;

    ACE_DISALLOW_COPY_AND_MOVE(SelectOverlayContentModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECT_OVERLAY_CONTENT_MODIFIER_H