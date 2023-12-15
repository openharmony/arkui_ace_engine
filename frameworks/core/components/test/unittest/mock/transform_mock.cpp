/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components/test/unittest/mock/transform_mock.h"

#include <utility>

#include "core/components/transform/render_transform.h"
#include "core/components/transform/transform_component.h"

namespace OHOS::Ace {
namespace {

MockRenderTransform::HookRenderTransform g_hookRenderTransform;

} // namespace

void RenderTransform::Translate(const Dimension& x, const Dimension& y, const Dimension& z) {}

void RenderTransform::Scale(float x, float y, float z) {}

void RenderTransform::Skew(float x, float y) {}

void RenderTransform::Perspective(const Dimension& distance) {}

void RenderTransform::Matrix3D(Matrix4 m) {}

Offset RenderTransform::GetGlobalOffsetExternal() const
{
    return Offset(0.0, 0.0);
}

void RenderTransform::Translate(const Dimension& x, const Dimension& y)
{
    auto mock = AceType::DynamicCast<MockRenderTransform>(this);
    if (mock) {
        mock->MockTranslate(x, y);
    }
}

void RenderTransform::Scale(float value)
{
    auto mock = AceType::DynamicCast<MockRenderTransform>(this);
    if (mock) {
        mock->MockScale(value);
    }
}

void RenderTransform::Scale(float x, float y)
{
    auto mock = AceType::DynamicCast<MockRenderTransform>(this);
    if (mock) {
        mock->MockScale(x, y);
    }
}

void RenderTransform::Rotate(float angle, float x, float y, float z)
{
    auto mock = AceType::DynamicCast<MockRenderTransform>(this);
    if (mock) {
        mock->MockRotate(angle, x, y, z);
    }
}

void RenderTransform::RotateX(float angle)
{
    auto mock = AceType::DynamicCast<MockRenderTransform>(this);
    if (mock) {
        mock->MockRotateX(angle);
    }
}

void RenderTransform::RotateY(float angle)
{
    auto mock = AceType::DynamicCast<MockRenderTransform>(this);
    if (mock) {
        mock->MockRotateY(angle);
    }
}

void RenderTransform::RotateZ(float angle)
{
    auto mock = AceType::DynamicCast<MockRenderTransform>(this);
    if (mock) {
        mock->MockRotateZ(angle);
    }
}

void RenderTransform::Update(const RefPtr<Component>& component)
{
    const RefPtr<TransformComponent> transform = AceType::DynamicCast<TransformComponent>(component);
    if (transform) {
        transform_ = transform->GetTransform();
        MarkNeedLayout();
    }
}

void RenderTransform::OnTouchTestHit(
    const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result)
{}

void RenderTransform::ResetTransform() {}

void RenderTransform::PerformLayout()
{
    Size layoutSize;
    if (!GetChildren().empty()) {
        auto child = GetChildren().front();

        LayoutParam innerLayout;
        Size maxLayoutSize = GetLayoutParam().GetMaxSize();
        if (maxLayoutSize.IsValid()) {
            innerLayout.SetMaxSize(maxLayoutSize);
            child->Layout(innerLayout);
            layoutSize += child->GetLayoutSize();
        }
        SetLayoutSize(layoutSize);
        origin_ = Offset(child->GetLayoutSize().Width() / 2.0, child->GetLayoutSize().Height() / 2.0);
    }
}

void RenderTransform::OnTransition(OHOS::Ace::TransitionType, int) {}

bool RenderTransform::HasDisappearingTransition(int)
{
    return false;
}

void RenderTransform::ClearRenderObject() {}

void RenderTransform::SetTouchable(bool enable)
{
    enableTouchTest_ = enable;
}

void MockRenderTransform::SetMockHook(const MockRenderTransform::HookRenderTransform& hook)
{
    g_hookRenderTransform = std::move(hook);
}

RefPtr<RenderNode> RenderTransform::Create()
{
    const auto& transform = AceType::MakeRefPtr<MockRenderTransform>();
    if (g_hookRenderTransform) {
        g_hookRenderTransform(transform);
    }
    return transform;
}

void MockRenderTransform::MockTranslate(Dimension x, Dimension y)
{
    translateX_ = x;
    translateY_ = y;
}

void MockRenderTransform::MockScale(float value)
{
    scaleXY_ = value;
}

void MockRenderTransform::MockScale(float x, float y)
{
    scaleX_ = x;
    scaleY_ = y;
}

void MockRenderTransform::MockRotate(float angle, float x, float y, float z)
{
    rotateAngle_ = angle;
    rotateAxisX_ = x;
    rotateAxisY_ = y;
    rotateAxisZ_ = z;
}

void MockRenderTransform::MockRotateX(float angle)
{
    rotateAxisX_ = angle;
}

void MockRenderTransform::MockRotateY(float angle)
{
    rotateAxisY_ = angle;
}

void MockRenderTransform::MockRotateZ(float angle)
{
    rotateAxisZ_ = angle;
}

void MockRenderTransform::GetTranslateSetting(Dimension& x, Dimension& y) const
{
    x = translateX_;
    y = translateY_;
}

void MockRenderTransform::GetScaleSetting(float& scaleX, float& scaleY) const
{
    scaleX = scaleX_;
    scaleY = scaleY_;
}

void MockRenderTransform::GetScaleSetting(float& scale) const
{
    scale = scaleXY_;
}

void MockRenderTransform::GetRotateSetting(float& angle, float& x, float& y, float& z) const
{
    angle = rotateAngle_;
    x = rotateAxisX_;
    y = rotateAxisY_;
    z = rotateAxisZ_;
}

void MockRenderTransform::ResetSetting()
{
    translateX_ = Dimension();
    translateY_ = Dimension();
    rotateAngle_ = 0.0f;
    rotateAxisX_ = 0.0f;
    rotateAxisY_ = 0.0f;
    rotateAxisZ_ = 0.0f;
    scaleX_ = 0.0f;
    scaleY_ = 0.0f;
}

bool MockRenderTransform::GetTouchable() const
{
    return enableTouchTest_;
}

} // namespace OHOS::Ace