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

#include "core/components_ng/base/extension_handler.h"

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

ExtensionLayoutConstraint ExtensionLayoutConstraint::Create(const LayoutConstraintF& layoutConstraintF)
{
    auto maxWidth = floor(layoutConstraintF.maxSize.Width());
    auto maxHeight = floor(layoutConstraintF.maxSize.Height());
    auto minWidth = floor(layoutConstraintF.minSize.Width());
    auto minHeight = floor(layoutConstraintF.minSize.Height());
    if (layoutConstraintF.selfIdealSize.Width().has_value()) {
        maxWidth = floor(layoutConstraintF.selfIdealSize.Width().value());
        minWidth = maxWidth;
    }
    if (layoutConstraintF.selfIdealSize.Height().has_value()) {
        maxHeight = floor(layoutConstraintF.selfIdealSize.Height().value());
        minHeight = maxHeight;
    }
    auto parentIdealWidth = floor(layoutConstraintF.percentReference.Width());
    auto parentIdealHeight = floor(layoutConstraintF.percentReference.Height());
    return { maxWidth, minWidth, maxHeight, minHeight, parentIdealWidth, parentIdealHeight };
}

void ExtensionHandler::Measure(const ExtensionLayoutConstraint& layoutConstraint)
{
    OnMeasure(layoutConstraint);
}

void ExtensionHandler::Layout(int32_t width, int32_t height, int32_t positionX, int32_t positionY)
{
    OnLayout(width, height, positionX, positionY);
}

void ExtensionHandler::Draw(DrawingContext& context)
{
    needRender_ = false;
    OnDraw(context);
}

void ExtensionHandler::ForegroundDraw(DrawingContext& context)
{
    needRender_ = false;
    OnForegroundDraw(context);
}

void ExtensionHandler::OverlayDraw(DrawingContext& context)
{
    needRender_ = false;
    OnOverlayDraw(context);
}

// 调用封装内部原始布局，绘制方法。
void ExtensionHandler::InnerMeasure(const ExtensionLayoutConstraint& layoutConstraint)
{
    if (innerMeasureImpl_) {
        innerMeasureImpl_(layoutConstraint);
    }
}

void ExtensionHandler::InnerLayout(int32_t width, int32_t height, int32_t positionX, int32_t positionY)
{
    if (innerLayoutImpl_) {
        innerLayoutImpl_(width, height, positionX, positionY);
    }
}

void ExtensionHandler::InnerDraw(DrawingContext& context)
{
    if (innerDrawImpl_) {
        innerDrawImpl_(context);
    }
}

void ExtensionHandler::InnerForegroundDraw(DrawingContext& context)
{
    if (innerForegroundDrawImpl_) {
        innerForegroundDrawImpl_(context);
    }
}

void ExtensionHandler::InnerOverlayDraw(DrawingContext& context)
{
    if (innerOverlayDrawImpl_) {
        innerOverlayDrawImpl_(context);
    }
}

void ExtensionHandler::OnMeasure(const ExtensionLayoutConstraint& layoutConstraint)
{
    InnerMeasure(layoutConstraint);
}

void ExtensionHandler::OnLayout(int32_t width, int32_t height, int32_t positionX, int32_t positionY)
{
    InnerLayout(width, height, positionX, positionY);
}

void ExtensionHandler::OnForegroundDraw(DrawingContext& context)
{
    if (drawModifier_ && drawModifier_->drawForegroundFunc) {
        drawModifier_->drawForegroundFunc(context);
    } else {
        InnerForegroundDraw(context);
    }
}

void ExtensionHandler::OnDraw(DrawingContext& context)
{
    if (drawModifier_ && drawModifier_->drawBehindFunc) {
        drawModifier_->drawBehindFunc(context);
    }

    if (drawModifier_ && drawModifier_->drawContentFunc) {
        drawModifier_->drawContentFunc(context);
    } else {
        InnerDraw(context);
    }

    if (drawModifier_ && drawModifier_->drawFrontFunc) {
        drawModifier_->drawFrontFunc(context);
    }
}

void ExtensionHandler::OnOverlayDraw(DrawingContext& context)
{
    InnerOverlayDraw(context);
}

void ExtensionHandler::InvalidateRender()
{
    if (invalidateRender_) {
        invalidateRender_();
    } else if (node_) {
        node_->MarkNeedRenderOnly();
    }
    needRender_ = true;
}

void ExtensionHandler::OverlayRender()
{
    if (overlayRender_) {
        overlayRender_();
    } else if (node_) {
        node_->MarkNeedRenderOnly();
    }
    needRender_ = true;
}

void ExtensionHandler::ForegroundRender()
{
    if (foreGroundRender_) {
        foreGroundRender_();
    } else if (node_) {
        node_->MarkNeedRenderOnly();
    }
    needRender_ = true;
}

} // namespace OHOS::Ace::NG
