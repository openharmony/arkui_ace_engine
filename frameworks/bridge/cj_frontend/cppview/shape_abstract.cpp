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

#include "bridge/cj_frontend/cppview/shape_abstract.h"

namespace OHOS::Ace::Framework {

NativeShapeAbstract::NativeShapeAbstract() : FFIData()
{
    LOGI("Native ShapeAbstract constructed: %{public}" PRId64, GetID());
}

NativeShapeAbstract::~NativeShapeAbstract()
{
    LOGI("Native ShapeAbstract Destroyed: %{public}" PRId64, GetID());
}

void NativeShapeAbstract::SetWidth(const Dimension& value)
{
    if (basicShape_) {
        basicShape_->SetWidth(value);
    } else {
        LOGE("basicShape is not exist");
    }
}

void NativeShapeAbstract::SetHeight(const Dimension& value)
{
    if (basicShape_) {
        basicShape_->SetHeight(value);
    } else {
        LOGE("basicShape is not exist");
    }
}

void NativeShapeAbstract::SetSize(const Dimension& width, const Dimension& height)
{
    SetWidth(width);
    SetHeight(height);
}

void NativeShapeAbstract::SetOffset(const Dimension& x, const Dimension& y)
{
    if (basicShape_) {
        basicShape_->SetOffset(DimensionOffset(x, y));
    } else {
        LOGE("basicShape is not exist");
    }
}

void NativeShapeAbstract::SetFill(const Color& color)
{
    if (basicShape_) {
        basicShape_->SetColor(color);
    } else {
        LOGE("basicShape is not exist");
    }
}

NativeCircle::NativeCircle(const Dimension& width, const Dimension& height) : NativeShapeAbstract()
{
    auto circle = AceType::MakeRefPtr<Circle>();
    circle->SetWidth(width);
    circle->SetHeight(height);
    SetBasicShape(circle);
    LOGI("NativeCircle constructed: %{public}" PRId64, GetID());
}

NativeCircle::~NativeCircle()
{
    LOGI("NativeCircle Destroyed: %{public}" PRId64, GetID());
}

NativeEllipse::NativeEllipse(const Dimension& width, const Dimension& height) : NativeShapeAbstract()
{
    auto ellipse = AceType::MakeRefPtr<Ellipse>();
    ellipse->SetWidth(width);
    ellipse->SetHeight(height);
    SetBasicShape(ellipse);
    LOGI("NativeEllipse constructed: %{public}" PRId64, GetID());
}

NativeEllipse::~NativeEllipse()
{
    LOGI("NativeEllipse Destroyed: %{public}" PRId64, GetID());
}

NativeRect::NativeRect(const Dimension& width, const Dimension& height) : NativeShapeAbstract()
{
    auto rect = AceType::MakeRefPtr<ShapeRect>();
    rect->SetWidth(width);
    rect->SetHeight(height);
    SetBasicShape(rect);
    LOGI("NativeRect constructed: %{public}" PRId64, GetID());
}

NativeRect::~NativeRect()
{
    LOGI("NativeRect Destroyed: %{public}" PRId64, GetID());
}

void NativeRect::SetRadius(const OHOS::Ace::Dimension& value)
{
    SetRadiusWidth(value);
    SetRadiusHeight(value);
}

void NativeRect::SetRadiusWidth(const OHOS::Ace::Dimension& value)
{
    if (basicShape_) {
        auto rect = AceType::DynamicCast<ShapeRect>(basicShape_);
        rect->SetRadiusWidth(value);
    } else {
        LOGE("basicShape is not exist");
    }
}

void NativeRect::SetRadiusHeight(const OHOS::Ace::Dimension& value)
{
    if (basicShape_) {
        auto rect = AceType::DynamicCast<ShapeRect>(basicShape_);
        rect->SetRadiusHeight(value);
    } else {
        LOGE("basicShape is not exist");
    }
}

NativePath::NativePath(const std::string& pathCmd) : NativeShapeAbstract()
{
    auto path = AceType::MakeRefPtr<Path>();
    path->SetValue(pathCmd);
    SetBasicShape(path);
    LOGI("NativePath constructed: %{public}" PRId64, GetID());
}

NativePath::~NativePath()
{
    LOGI("NativePath Destroyed: %{public}" PRId64, GetID());
}
} // namespace OHOS::Ace::Framework
