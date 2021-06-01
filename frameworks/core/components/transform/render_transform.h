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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TRANSFORM_RENDER_TRANSFORM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TRANSFORM_RENDER_TRANSFORM_H

#include "base/geometry/axis.h"
#include "base/geometry/matrix4.h"
#include "core/components/transform/click_spring_effect.h"
#include "core/gestures/raw_recognizer.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace {

enum class TransformType {
    TRANSLATE_X,
    TRANSLATE_Y,
    SCALE_X,
    SCALE_Y,
    ROTATE_X,
    ROTATE_Y,
    ROTATE_Z,
};

class RenderTransform : public RenderNode {
    DECLARE_ACE_TYPE(RenderTransform, RenderNode);

public:
    static RefPtr<RenderNode> Create();
    void Translate(const Dimension& x, const Dimension& y);
    void Scale(float value);
    void Scale(float x, float y);
    void Rotate(float angle, float x, float y, float z);
    void RotateX(float angle);
    void RotateY(float angle);
    void RotateZ(float angle);
    void ResetTransform();
    void UpdateTransform();
    void SetTouchable(bool enable);
    void Update(const RefPtr<Component>& component) override;
    void PerformLayout() override;
    void UpdateTransformOrigin();

    void SetMaxScaleXY(double maxScaleXY)
    {
        maxScaleXY_ = maxScaleXY;
    }

    void MarkNeedUpdateOrigin()
    {
        needUpdateOrigin_ = true;
    }

    void SetTransformOrigin(const Dimension& x, const Dimension& y)
    {
        originX_ = x;
        originY_ = y;
        MarkNeedRender();
    }

    void SetDisableClickEffect(bool isDisable)
    {
        disableClickEffect_ = isDisable;
    }

    virtual void UpdateTransformLayer() {}

    Dimension GetTranslateX() const
    {
        Dimension translateX;
        for (const auto& translate : transformEffects_) {
            if (translate.first == TransformType::TRANSLATE_X) {
                translateX = translate.second;
            }
        }
        return translateX;
    }

    Dimension GetTranslateY() const
    {
        Dimension translateY;
        for (const auto& translate : transformEffects_) {
            if (translate.first == TransformType::TRANSLATE_Y) {
                translateY = translate.second;
            }
        }
        return translateY;
    }

    float GetScaleX() const
    {
        return scaleX_;
    }

    float GetScaleY() const
    {
        return scaleY_;
    }

    float GetRotateX() const
    {
        return rotateX_;
    }

    float GetRotateY() const
    {
        return rotateY_;
    }

    float GetRotateZ() const
    {
        return rotateZ_;
    }

protected:
    void OnTouchTestHit(
        const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result) override;
    Matrix4 UpdateWithEffectMatrix(Matrix4 matrix);

    double scaleX_ = 0.0;
    double scaleY_ = 0.0;
    double rotateX_ = 0.0;
    double rotateY_ = 0.0;
    double rotateZ_ = 0.0;
    Matrix4 transform_;
    bool needUpdateTransform_ = false;
    std::vector<std::pair<TransformType, Dimension>> transformEffects_;
    Offset origin_;
    Dimension originX_;
    Dimension originY_;
    bool needUpdateOrigin_ = false;
    double maxScaleXY_ = -1.0;
    RefPtr<RawRecognizer> rawRecognizer_;
    RefPtr<ClickSpringEffect> clickSpringEffect_;
    bool disableClickEffect_ = false;
    bool enableTouchTest_ = true;

private:
    double CovertDimensionToPxBySize(const Dimension& dimension, double size);
    void SetTouchHandle(ClickSpringEffectType type);

#if defined(WINDOWS_PLATFORM) || defined(MAC_PLATFORM)
    void ResetTransformToAccessibilityNode();
    void UpdateScaleToAccessibilityNode(float maxScale);
    void UpdateTranslateToAccessibilityNode(double translateX, double translateY);
    void UpdateRotateToAccessibilityNode(float angle, RotateAxis rotateAxis);
#endif
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TRANSFORM_RENDER_TRANSFORM_H
