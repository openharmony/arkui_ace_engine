/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/transform/render_transform.h"

#include "base/utils/utils.h"
#include "core/components/box/render_box_base.h"
#include "core/components/transform/transform_component.h"

namespace OHOS::Ace {

// Effect translate to Matrix at the end for percent needs to be calculated after layout.
void RenderTransform::Translate(const Dimension& x, const Dimension& y)
{
    if (!NearEqual(x.Value(), 0.0)) {
        double moveX = CovertDimensionToPxBySize(x, GetLayoutSize().Width());
        transform_ = Matrix4::CreateTranslate(moveX, 0.0f, 0.0f) * transform_;
    }
    if (!NearEqual(y.Value(), 0.0)) {
        double moveY = CovertDimensionToPxBySize(y, GetLayoutSize().Height());
        transform_ = Matrix4::CreateTranslate(0.0f, moveY, 0.0f) * transform_;
    }
    UpdateTransformLayer();
    auto context = context_.Upgrade();
    if (context) {
        context->MarkForcedRefresh();
    }
#if defined(WINDOWS_PLATFORM) || defined(MAC_PLATFORM)
    UpdateTranslateToAccessibilityNode(x.Value(), y.Value());
#endif
}

void RenderTransform::Scale(float value)
{
    Scale(value, value);
}

void RenderTransform::Scale(float x, float y)
{
    scaleX_ = x;
    scaleY_ = y;
    if (!NearEqual(x, 1.0f) || !NearEqual(y, 1.0f)) {
        transform_ = Matrix4::CreateScale(x, y, 1.0f) * transform_;
    }
    UpdateTransformLayer();
    auto context = context_.Upgrade();
    if (context) {
        context->MarkForcedRefresh();
    }
#if defined(WINDOWS_PLATFORM) || defined(MAC_PLATFORM)
    if (!NearEqual(maxScaleXY_, -1.0)) {
        UpdateScaleToAccessibilityNode(maxScaleXY_);
    }
#endif
}

void RenderTransform::Rotate(float angle, float x, float y, float z)
{
    if (!NearZero(angle) && !NearZero(fmod(angle, 360.0f))) {
        Matrix4 rotate = Matrix4::CreateRotate(angle, x, y, z);
        transform_.SetEntry(INDEX_THREE, INDEX_TWO, PERSPECTIVE);
        transform_ = rotate * transform_;
    }
    UpdateTransformLayer();
    auto context = context_.Upgrade();
    if (context) {
        context->MarkForcedRefresh();
    }

    if (x == 1.0f) {
        rotateX_ = angle;
    }

    if (y == 1.0f) {
        rotateY_ = angle;
    }

    if (z == 1.0f) {
        rotateZ_ = angle;
    }

#if defined(WINDOWS_PLATFORM) || defined(MAC_PLATFORM)
    if (!NearEqual(angle, 0.0) && !NearEqual(z, 0.0)) {
        UpdateRotateToAccessibilityNode(angle, RotateAxis::AXIS_Z);
    }
#endif
}

void RenderTransform::RotateX(float angle)
{
    Rotate(angle, 1.0f, 0.0f, 0.0f);
}

void RenderTransform::RotateY(float angle)
{
    Rotate(angle, 0.0f, 1.0f, 0.0f);
}

void RenderTransform::RotateZ(float angle)
{
    Rotate(angle, 0.0f, 0.0f, 1.0f);
#if defined(WINDOWS_PLATFORM) || defined(MAC_PLATFORM)
    if (!NearEqual(angle, 0.0)) {
        UpdateRotateToAccessibilityNode(angle, RotateAxis::AXIS_Z);
    }
#endif
}

void RenderTransform::ResetTransform()
{
    transform_ = Matrix4::CreateIdentity();
    transformEffects_.clear();
#if defined(WINDOWS_PLATFORM) || defined(MAC_PLATFORM)
    ResetTransformToAccessibilityNode();
#endif
}

#if defined(WINDOWS_PLATFORM) || defined(MAC_PLATFORM)
void RenderTransform::ResetTransformToAccessibilityNode()
{
    const auto& context = context_.Upgrade();
    if (!context) {
        return;
    }
    auto accessibilityManager = context->GetAccessibilityManager();
    if (!accessibilityManager) {
        LOGE("accessibilityManager is null");
        return;
    }
    auto accessibilityNode  = accessibilityManager->GetAccessibilityNodeById(GetNodeId());
    if (!accessibilityNode) {
        LOGE("RenderTransform is null");
        return;
    }
    accessibilityNode->SetScaleToChild(1.0);
    accessibilityNode->SetTranslateOffsetToChild(Offset(0.0, 0.0));
    accessibilityNode->SetRotateToChild(0.0, RotateAxis::AXIS_Z);
    for (const auto& item : GetChildren()) {
        item->NotifyPaintFinish();
    }
}

void RenderTransform::UpdateScaleToAccessibilityNode(float maxScale)
{
    const auto& context = context_.Upgrade();
    if (!context) {
        return;
    }
    auto accessibilityManager = context->GetAccessibilityManager();
    if (!accessibilityManager) {
        LOGE("accessibilityManager is null");
        return;
    }
    auto accessibilityNode  = accessibilityManager->GetAccessibilityNodeById(GetNodeId());
    if (!accessibilityNode) {
        LOGE("RenderTransform is null");
        return;
    }

    if (!NearEqual(maxScale, 1.0)) {
        Size size = GetLayoutSize();
        Offset globalOffset = GetGlobalOffset();
        Offset scaleCenter = Offset(globalOffset.GetX() + size.Width() / 2.0,
                                    globalOffset.GetY() + size.Height() / 2.0);
        accessibilityNode->SetScaleToChild(maxScale);
        accessibilityNode->SetScaleCenterToChild(scaleCenter);
        for (const auto& item : GetChildren()) {
            item->NotifyPaintFinish();
        }
    }
}

void RenderTransform::UpdateTranslateToAccessibilityNode(double translateX, double translateY)
{
    const auto& context = context_.Upgrade();
    if (!context) {
        return;
    }
    auto accessibilityManager = context->GetAccessibilityManager();
    if (!accessibilityManager) {
        LOGE("accessibilityManager is null");
        return;
    }
    auto accessibilityNode  = accessibilityManager->GetAccessibilityNodeById(GetNodeId());
    if (!accessibilityNode) {
        LOGE("RenderTransform is null");
        return;
    }
    if (!NearEqual(translateX, 0.0) || !NearEqual(translateY, 0.0)) {
        Offset translateOffset(translateX, translateY);
        accessibilityNode->SetTranslateOffsetToChild(translateOffset);
        for (const auto& child : GetChildren()) {
            child->NotifyPaintFinish();
        }
    }
}

void RenderTransform::UpdateRotateToAccessibilityNode(float angle, RotateAxis rotateAxis)
{
    const auto& context = context_.Upgrade();
    if (!context) {
        return;
    }
    auto accessibilityManager = context->GetAccessibilityManager();
    if (!accessibilityManager) {
        LOGE("accessibilityManager is null");
        return;
    }
    auto accessibilityNode  = accessibilityManager->GetAccessibilityNodeById(GetNodeId());
    if (!accessibilityNode) {
        LOGE("RenderTransform is null");
        return;
    }
    if (!NearEqual(angle, 0.0)) {
        accessibilityNode->SetRotateToChild(angle, rotateAxis);
        Size size = GetLayoutSize();
        Offset globalOffset = GetGlobalOffset();
        Offset scaleCenter = Offset(globalOffset.GetX() + size.Width() / 2.0,
                                    globalOffset.GetY() + size.Height() / 2.0);
        accessibilityNode->SetScaleCenterToChild(scaleCenter);
        for (const auto& item : GetChildren()) {
            item->NotifyPaintFinish();
        }
    }
}
#endif

void RenderTransform::UpdateTransform()
{
    if (!needUpdateTransform_) {
        return;
    }
    needUpdateTransform_ = false;
    for (const auto& effect : transformEffects_) {
        switch (effect.first) {
            case TransformType::TRANSLATE_X: {
                double moveX = CovertDimensionToPxBySize(effect.second, GetLayoutSize().Width());
                transform_ = Matrix4::CreateTranslate(moveX, 0.0f, 0.0f) * transform_;
                break;
            }
            case TransformType::TRANSLATE_Y: {
                double moveY = CovertDimensionToPxBySize(effect.second, GetLayoutSize().Height());
                transform_ = Matrix4::CreateTranslate(0.0f, moveY, 0.0f) * transform_;
                break;
            }
            case TransformType::SCALE_X: {
                transform_ = Matrix4::CreateScale(effect.second.Value(), 1.0f, 1.0f) * transform_;
                break;
            }
            case TransformType::SCALE_Y: {
                transform_ = Matrix4::CreateScale(1.0f, effect.second.Value(), 1.0f) * transform_;
                break;
            }
            case TransformType::ROTATE_X: {
                transform_.SetEntry(INDEX_THREE, INDEX_TWO, PERSPECTIVE);
                transform_ = Matrix4::CreateRotate(effect.second.Value(), 1.0f, 0.0f, 0.0f) * transform_;
                break;
            }
            case TransformType::ROTATE_Y: {
                transform_.SetEntry(INDEX_THREE, INDEX_TWO, PERSPECTIVE);
                transform_ = Matrix4::CreateRotate(effect.second.Value(), 0.0f, 1.0f, 0.0f) * transform_;
                break;
            }
            case TransformType::ROTATE_Z: {
                transform_.SetEntry(INDEX_THREE, INDEX_TWO, PERSPECTIVE);
                transform_ = Matrix4::CreateRotate(effect.second.Value(), 0.0f, 0.0f, 1.0f) * transform_;
                break;
            }
            default:
                break;
        }
    }
}

void RenderTransform::SetTouchable(bool enable)
{
    LOGD("set transform touchable status: %{public}d", enable);
    enableTouchTest_ = enable;
}

void RenderTransform::Update(const RefPtr<Component>& component)
{
    auto transform = AceType::DynamicCast<TransformComponent>(component);
    if (transform == nullptr) {
        LOGE("transform component is nullptr.");
        return;
    }
    if (!IsDeclarativeAnimationActive()) {
        ResetTransform();
        needUpdateTransform_ = true;
        transform_ = transform->GetTransform();
        transformEffects_ = transform->GetTransformEffects();
        originX_ = transform->GetOriginDimension().GetX();
        originY_ = transform->GetOriginDimension().GetY();
        SetTouchHandle(transform->GetClickSpringEffectType());
        SetShadow(transform->GetShadow());
    }

    MarkNeedLayout();
}

void RenderTransform::PerformLayout()
{
    LOGD("RenderTransform::PerformLayout");
    auto child = GetFirstChild();
    if (child == nullptr) {
        LOGE("child component is nullptr.");
        return;
    }

    Size layoutSize;
    LayoutParam innerLayout;
    Size maxLayoutSize = GetLayoutParam().GetMaxSize();
    if (maxLayoutSize.IsValid()) {
        innerLayout.SetMaxSize(maxLayoutSize);
        child->Layout(innerLayout);
        layoutSize = child->GetLayoutSize();
    }
    SetLayoutSize(layoutSize);
    needUpdateOrigin_ = true;
}

void RenderTransform::UpdateTransformOrigin()
{
    auto child = GetFirstChild();
    if (child == nullptr) {
        LOGE("child component is nullptr.");
        return;
    }
    Size layoutSize = GetLayoutSize();
    const auto& renderBoxBase = AceType::DynamicCast<RenderBoxBase>(child);
    if (renderBoxBase) {
        auto margin = renderBoxBase->GetMargin();
        double marginTop = margin.TopPx();
        double marginLeft = margin.LeftPx();
        double marginBottom = margin.BottomPx();
        double marginRight = margin.RightPx();
        double paintWidthSize = layoutSize.Width() - marginLeft - marginRight;
        double paintHeightSize = layoutSize.Height() - marginTop - marginBottom;
        origin_.SetX(CovertDimensionToPxBySize(originX_, paintWidthSize) + marginLeft);
        origin_.SetY(CovertDimensionToPxBySize(originY_, paintHeightSize) + marginTop);
    } else {
        origin_.SetX(CovertDimensionToPxBySize(originX_, layoutSize.Width()));
        origin_.SetY(CovertDimensionToPxBySize(originY_, layoutSize.Height()));
    }
}

double RenderTransform::CovertDimensionToPxBySize(const Dimension& dimension, double size)
{
    double result = 0.0;
    if (dimension.Unit() == DimensionUnit::PERCENT) {
        result = dimension.Value() * size;
    } else if (dimension.Unit() == DimensionUnit::VP) {
        result = NormalizeToPx(dimension);
    } else {
        result = dimension.Value();
    }
    return result;
};

void RenderTransform::OnTouchTestHit(
    const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    if (rawRecognizer_) {
        rawRecognizer_->SetCoordinateOffset(coordinateOffset);
        result.emplace_back(rawRecognizer_);
    }
}

void RenderTransform::SetTouchHandle(ClickSpringEffectType type)
{
    if (type == ClickSpringEffectType::NONE) {
        if (rawRecognizer_) {
            rawRecognizer_->SetOnTouchUp(nullptr);
            rawRecognizer_->SetOnTouchDown(nullptr);
            rawRecognizer_->SetOnTouchCancel(nullptr);
        }
    } else {
        if (!rawRecognizer_) {
            rawRecognizer_ = AceType::MakeRefPtr<RawRecognizer>();
        }
        if (!clickSpringEffect_) {
            clickSpringEffect_ = AceType::MakeRefPtr<ClickSpringEffect>(GetContext());
            clickSpringEffect_->SetRenderNode(WeakClaim(this));
        }
        auto touchHandle = [weak = AceType::WeakClaim(this)](
                               const TouchEventInfo&, TouchType touchType, ClickSpringEffectType effectType) {
            auto transform = weak.Upgrade();
            if (transform && transform->clickSpringEffect_) {
                transform->clickSpringEffect_->ShowAnimation(touchType, effectType);
            }
        };
        rawRecognizer_->SetOnTouchDown(std::bind(touchHandle, std::placeholders::_1, TouchType::DOWN, type));
        rawRecognizer_->SetOnTouchUp(std::bind(touchHandle, std::placeholders::_1, TouchType::UP, type));
        rawRecognizer_->SetOnTouchCancel(std::bind(touchHandle, std::placeholders::_1, TouchType::CANCEL, type));
    }
}

Matrix4 RenderTransform::UpdateWithEffectMatrix(Matrix4 matrix)
{
    if (clickSpringEffect_ && !disableClickEffect_) {
        double scale = clickSpringEffect_->GetScale();
        if (!NearEqual(scale, 1.0)) {
            return matrix * Matrix4::CreateScale(scale, scale, 1.0);
        }
    }
    return matrix;
}

} // namespace OHOS::Ace
