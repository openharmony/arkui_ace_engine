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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_MATRIX_2D_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_MATRIX_2D_PEER_IMPL_H

#include "core/components/common/properties/paint_state.h"
#include "core/pipeline/pipeline_base.h"

struct Matrix2DPeer : public OHOS::Ace::Referenced {
public:
    Matrix2DPeer() = default;
    explicit Matrix2DPeer(OHOS::Ace::CanvasUnit unit)
    {
        Matrix2DPeer();
        unit_ = unit;
    }
    ~Matrix2DPeer() override = default;

    void Identity();
    void Invert();
    void Rotate(double degree, const std::optional<float>& optX, const std::optional<float>& optY);
    void Translate(const std::optional<float>& optX, const std::optional<float>& optY);
    void Scale(const std::optional<float>& optX, const std::optional<float>& optY);
    double GetScaleX();
    void SetScaleX(double scaleX);
    double GetRotateY();
    void SetRotateY(double rotateY);
    double GetRotateX();
    void SetRotateX(double rotateX);
    double GetScaleY();
    void SetScaleY(double scaleX);
    double GetTranslateX();
    void SetTranslateX(double translateX);
    double GetTranslateY();
    void SetTranslateY(double translateY);

    double GetScaleX() const
    {
        return transform_.scaleX;
    }
    double GetRotateY() const
    {
        return transform_.skewY;
    }
    double GetRotateX() const
    {
        return transform_.skewX;
    }
    double GetScaleY() const
    {
        return transform_.scaleY;
    }
    double GetTranslateX() const
    {
        return transform_.translateX;
    }
    double GetTranslateY() const
    {
        return transform_.translateY;
    }
    OHOS::Ace::TransformParam GetTransform() const
    {
        return transform_;
    }
    double GetDensity() const
    {
        // double density = OHOS::Ace::PipelineBase::GetCurrentDensity();
        // return ((GetUnit() == OHOS::Ace::CanvasUnit::DEFAULT) && !OHOS::Ace::NearZero(density)) ? density : 1.0;
        return 0;
    }
    void SetTransform(const OHOS::Ace::TransformParam& param)
    {
        transform_ = param;
    }
    void SetUnit(const OHOS::Ace::CanvasUnit& unit)
    {
        unit_ = unit;
    }
    OHOS::Ace::CanvasUnit GetUnit()
    {
        return unit_;
    }
    double GetDensity()
    {
        // double density = OHOS::Ace::PipelineBase::GetCurrentDensity();
        // return ((GetUnit() == OHOS::Ace::CanvasUnit::DEFAULT) && !OHOS::Ace::NearZero(density)) ? density : 1.0;
        return 0;
    }

private:
    OHOS::Ace::TransformParam transform_;
    OHOS::Ace::CanvasUnit unit_ = OHOS::Ace::CanvasUnit::DEFAULT;
};
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_MATRIX_2D_PEER_IMPL_H
