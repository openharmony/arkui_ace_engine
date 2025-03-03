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
#ifndef FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_CAVANS_PATTERN_H
#define FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_CAVANS_PATTERN_H

#include "ffi_remote_data.h"

#include "bridge/cj_frontend/cppview/canvas_renderer.h"
#include "base/memory/referenced.h"
#include "core/components/common/properties/decoration.h"
#include "frameworks/core/components/common/properties/paint_state.h"


namespace OHOS::Ace::Framework {

class ACE_EXPORT NativeCanvasPattern : public OHOS::FFI::FFIData, public Referenced {
public:
    NativeCanvasPattern();
    ~NativeCanvasPattern() override;

    void SetTransform(int64_t matrixId);

    void SetCanvasRenderer(const sptr<NativeCanvasRenderer>& canvasRenderer)
    {
        canvasRenderWeak_ = canvasRenderer;
    }

    void SetUnit(CanvasUnit unit)
    {
        unit_ = unit;
    }

    CanvasUnit GetUnit()
    {
        return unit_;
    }

    double GetDensity()
    {
        double density = PipelineBase::GetCurrentDensity();
        return ((GetUnit() == CanvasUnit::DEFAULT) && !NearZero(density)) ? density : 1.0;
    }

    void SetId(int32_t id)
    {
        id_ = id;
    }

    int32_t GetId() const
    {
        return id_;
    }
private:
    TransformParam transform_;
    sptr<NativeCanvasRenderer> canvasRenderWeak_;
    CanvasUnit unit_ = CanvasUnit::DEFAULT;
    int32_t id_ = 0;
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_CAVANS_PATTERN_H
