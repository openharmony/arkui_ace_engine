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

#include "core/components/transform/flutter_render_transform.h"

namespace OHOS::Ace {

using namespace Flutter;

tonic::Float64List ToFloat64List(const Matrix4& matrix4)
{
    tonic::Float64List floatData(matrix4.Count());
    for (int32_t i = 0; i < matrix4.Count(); i++) {
        floatData[i] = matrix4[i];
    }
    return floatData;
}

RefPtr<RenderNode> RenderTransform::Create()
{
    return AceType::MakeRefPtr<FlutterRenderTransform>();
}

RenderLayer FlutterRenderTransform::GetRenderLayer()
{
    if (!layer_) {
        layer_ = AceType::MakeRefPtr<TransformLayer>(Matrix4::CreateIdentity(), 0.0, 0.0);
    }
    return AceType::RawPtr(layer_);
}

void FlutterRenderTransform::UpdateTransformLayer()
{
    UpdateTransformByGlobalOffset();
}

void FlutterRenderTransform::Paint(RenderContext& context, const Offset& offset)
{
    if (needUpdateOrigin_) {
        UpdateTransformOrigin();
        needUpdateOrigin_ = false;
    }
    UpdateTransform(); // Update transform param to Matrix.

    if (!CheckNeedPaint()) {
        return;
    }

    UpdateTransformByGlobalOffset();
    RenderNode::Paint(context, offset);
}

void FlutterRenderTransform::UpdateTransformByGlobalOffset()
{
    Offset absoluteOffset = GetGlobalOffset();
    Matrix4 transform = GetEffectiveTransform(absoluteOffset);
    if (layer_) {
        layer_->Update(transform);
    }
}

void FlutterRenderTransform::OnGlobalPositionChanged()
{
    UpdateTransformByGlobalOffset();
}

bool FlutterRenderTransform::TouchTest(const Point& globalPoint, const Point& parentLocalPoint,
    const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    LOGD("Global point is %{public}lf, %{public}lf", globalPoint.GetX(), globalPoint.GetY());
    LOGD("Local point  is %{public}lf, %{public}lf", parentLocalPoint.GetX(), parentLocalPoint.GetY());

    if (!enableTouchTest_ || disabled_) {
        LOGD("transform touch test disabled, skip touch test");
        return false;
    }
    Offset offset = GetPosition();
    Matrix4 transform = GetEffectiveTransform(offset);
    Matrix4 inverse = Matrix4::Invert(transform);
    Point beforeTransform = inverse * parentLocalPoint;
    if (GetTouchRect().IsInRegion(beforeTransform)) {
        const auto localPoint = beforeTransform - GetPaintRect().GetOffset();
        for (const auto& child : GetChildren()) {
            if (child->TouchTest(globalPoint, localPoint, touchRestrict, result)) {
                break;
            }
        }
        const auto coordinateOffset = globalPoint - localPoint;
        OnTouchTestHit(coordinateOffset, touchRestrict, result);
        return true;
    }
    return false;
}

Matrix4 FlutterRenderTransform::GetTransformByOffset(Matrix4 matrix, const Offset& offset)
{
    LOGD("Offset(%{public}lf, %{public}lf)", offset.GetX(), offset.GetY());
    if (offset.IsZero()) {
        return matrix;
    }

    Matrix4 transform =
        Matrix4::CreateTranslate(static_cast<float>(-offset.GetX()), static_cast<float>(-offset.GetY()), 0.0f);
    transform = matrix * transform;
    transform = Matrix4::CreateTranslate(static_cast<float>(offset.GetX()), static_cast<float>(offset.GetY()), 0.0f) *
                transform;
    return transform;
}

Matrix4 FlutterRenderTransform::GetEffectiveTransform(const Offset& offset)
{
    Matrix4 transform = GetTransformByOffset(UpdateWithEffectMatrix(transform_), origin_);
    if (!offset.IsZero()) {
        transform = GetTransformByOffset(transform, offset);
    }
    return transform;
}

bool FlutterRenderTransform::HasEffectiveTransform() const
{
    if (!layer_) {
        return false;
    }
    return !layer_->GetMatrix4().IsIdentityMatrix();
}

bool FlutterRenderTransform::CheckNeedPaint() const
{
    double rotateX = 0.0;
    double rotateY = 0.0;
    double sy = sqrt(transform_[0] * transform_[0] + transform_[4] * transform_[4]);
    if (NearZero(sy)) {
        rotateX = atan2(-transform_[6], transform_[5]);
        rotateY = atan2(-transform_[8], sy);
    } else {
        rotateX = atan2(transform_[9], transform_[10]);
        rotateY = atan2(-transform_[8], sy);
    }
    rotateX = std::abs(rotateX * (180.0f / M_PI));
    rotateY = std::abs(rotateY * (180.0f / M_PI));
    if (NearEqual(rotateX, 90.0, 1e-5) || NearEqual(rotateY, 90.0, 1e-5)) {
        return false; // If RotateX or RotateY is 90 deg, not need to paint.
    }
    return true;
}

} // namespace OHOS::Ace
