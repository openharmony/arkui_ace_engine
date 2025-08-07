/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/render/adapter/matrix2d.h"
#include "matrix2d_peer_impl.h"

namespace {
const double ERROR_VALUE = 0;
}

void Matrix2DPeer::Identity()
{
    OHOS::Ace::NG::Matrix2D::Identity(transform_);
}
void Matrix2DPeer::Invert()
{
    bool retValue = OHOS::Ace::NG::Matrix2D::Invert(transform_);
    if (!retValue) {
        transform_.scaleX = NAN;
        transform_.scaleY = NAN;
        transform_.skewX = NAN;
        transform_.skewY = NAN;
        transform_.translateX = NAN;
        transform_.translateY = NAN;
    }
}
void Matrix2DPeer::Rotate(double degree, const std::optional<float>& optX, const std::optional<float>& optY)
{
    double rx = optX.value_or(0);
    double ry = optY.value_or(0);
    double density = GetDensity();
    rx *= density;
    ry *= density;
    OHOS::Ace::NG::Matrix2D::Rotate(transform_, degree, rx, ry);
}
void Matrix2DPeer::Translate(const std::optional<float>& optX, const std::optional<float>& optY)
{
    double tx = optX.value_or(0);
    double ty = optY.value_or(0);
    double density = GetDensity();
    tx *= density;
    ty *= density;
    OHOS::Ace::NG::Matrix2D::Translate(transform_, tx, ty);
}
void Matrix2DPeer::Scale(const std::optional<float>& optX, const std::optional<float>& optY)
{
    double sx = optX.value_or(1.0);
    double sy = optX.value_or(1.0);
    OHOS::Ace::NG::Matrix2D::Scale(transform_, sx, sy);
}
double Matrix2DPeer::GetScaleX()
{
    return transform_.scaleX;
}
void Matrix2DPeer::SetScaleX(double scaleX)
{
    transform_.scaleX = scaleX;
}
double Matrix2DPeer::GetRotateY()
{
    return transform_.skewY;
}
void Matrix2DPeer::SetRotateY(double rotateY)
{
    transform_.skewY = rotateY;
}
double Matrix2DPeer::GetRotateX()
{
    return transform_.skewX;
}
void Matrix2DPeer::SetRotateX(double rotateX)
{
    transform_.skewX = rotateX;
}
double Matrix2DPeer::GetScaleY()
{
    return transform_.scaleY;
}
void Matrix2DPeer::SetScaleY(double scaleY)
{
    transform_.scaleY = scaleY;
}
double Matrix2DPeer::GetTranslateX()
{
    double translateX = transform_.translateX;
    double density = GetDensity();
    if (density == 0) {
        return ERROR_VALUE;
    }
    translateX /= density;
    return translateX;
}
void Matrix2DPeer::SetTranslateX(double translateX)
{
    double density = GetDensity();
    translateX *= density;
    transform_.translateX = translateX;
}
double Matrix2DPeer::GetTranslateY()
{
    double translateY = transform_.translateY;
    double density = GetDensity();
    if (density == 0) {
        return ERROR_VALUE;
    }
    translateY /= density;
    return translateY;
}
void Matrix2DPeer::SetTranslateY(double translateY)
{
    double density = GetDensity();
    translateY *= density;
    transform_.translateY = translateY;
}