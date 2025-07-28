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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_DRAWING_RENDERING_CONTEXT_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_DRAWING_RENDERING_CONTEXT_PEER_IMPL_H

#include "base/memory/referenced.h"
#include "core/components/common/properties/paint_state.h"
#include "core/components_ng/render/drawing.h"
#include "base/geometry/ng/size_t.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
class DrawingRenderingContextPeerImpl : public Referenced {
public:
    DrawingRenderingContextPeerImpl();
    ~DrawingRenderingContextPeerImpl() override = default;

    void SetOptions(const std::optional<CanvasUnit>& unit);
    void SetInvalidate();
    SizeF GetSize();
    std::shared_ptr<RSCanvas> GetCanvas() const;
    void SetRSCanvasCallback(RefPtr<AceType>& canvasPattern);

    void SetCanvasPattern(const RefPtr<AceType>& canvas)
    {
        canvasPattern_ = canvas;
        SetRSCanvasCallback(canvasPattern_);
    }
    void SetInstanceId(int32_t id)
    {
        instanceId_ = id;
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

protected:
    RefPtr<AceType> canvasPattern_;
    int32_t instanceId_ = INSTANCE_ID_UNDEFINED;

private:
    std::shared_ptr<RSCanvas> rsCanvas_;
    NG::OptionalSizeF size_;
    CanvasUnit unit_ = CanvasUnit::DEFAULT;
};
} // namespace OHOS::Ace::NG::GeneratedModifier
#endif //FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_TABS_CONTROLLER_PEER_IMPL_H
