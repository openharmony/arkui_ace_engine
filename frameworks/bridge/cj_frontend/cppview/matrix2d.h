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

#ifndef FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_MATRIX2D_H
#define FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_MATRIX2D_H

#include "ffi_remote_data.h"

#include "base/memory/referenced.h"
#include "core/components/common/properties/decoration.h"
#include "frameworks/core/components/common/properties/paint_state.h"

namespace OHOS::Ace::Framework {

class ACE_EXPORT NativeMatrix2d : public OHOS::FFI::FFIData, public Referenced {
public:
    NativeMatrix2d();
    explicit NativeMatrix2d(const int32_t unit);
    ~NativeMatrix2d() override;
    void Identity();
    void Invert();
    void Rotate(double degree, double rx, double ry);
    void Translate(double tx, double ty);
    void Scale(double sx, double sy);

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

    double GetTranslateX()
    {
        double density = Positive(GetDensity()) ? GetDensity() : 1;
        return transform_.translateX / density;
    }

    double GetTranslateY()
    {
        double density = Positive(GetDensity()) ? GetDensity() : 1;
        return transform_.translateY / density;
    }

    void SetScaleX(double value)
    {
        transform_.scaleX = value;
    }

    void SetScaleY(double value)
    {
        transform_.scaleY = value;
    }

    void SetRotateX(double value)
    {
        transform_.skewX = value;
    }

    void SetRotateY(double value)
    {
        transform_.skewY = value;
    }

    void SetTranslateX(double value)
    {
        double density = GetDensity();
        transform_.translateX = value * density;
    }

    void SetTranslateY(double value)
    {
        double density = GetDensity();
        transform_.translateY = value * density;
    }

    TransformParam GetTransform() const
    {
        return transform_;
    }

    void SetTransform(const TransformParam& param)
    {
        transform_ = param;
    }

    CanvasUnit GetUnit()
    {
        return unit_;
    }

    double GetDensity();

private:
    TransformParam transform_;
    CanvasUnit unit_ = CanvasUnit::DEFAULT;
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_MATRIX2D_H