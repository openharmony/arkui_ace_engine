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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_CANVAS_PATTERN_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_CANVAS_PATTERN_PEER_IMPL_H

#include "base/memory/referenced.h"
#include "canvas_renderer_peer_impl.h"
#include "core/common/container.h"
#include "core/components/common/properties/decoration.h"
#include "matrix2d_peer_impl.h"

struct CanvasPatternPeer : OHOS::Ace::Referenced {
public:
    CanvasPatternPeer() = default;
    virtual ~CanvasPatternPeer() = default;

    void SetTransform(const std::optional<Matrix2DPeer*>& optMatrix)
    {
        if (OHOS::Ace::Container::GreatOrEqualAPITargetVersion(OHOS::Ace::PlatformVersion::VERSION_TEN)) {
            if (optMatrix && optMatrix.value()) {
                auto matrix = optMatrix.value();
                auto canvasRenderer = canvasRenderWeak_.Upgrade();
                if (canvasRenderer) {
                    canvasRenderer->SetTransform(GetId(), matrix->GetTransform());
                }
            }
        }
    }

    void SetCanvasRenderer(OHOS::Ace::WeakPtr<OHOS::Ace::NG::GeneratedModifier::CanvasRendererPeerImpl> canvasRenderer)
    {
        canvasRenderWeak_ = canvasRenderer;
    }

    void SetId(int32_t id)
    {
        id_ = id;
    }

    int32_t GetId() const
    {
        return id_;
    }

    void SetUnit(OHOS::Ace::CanvasUnit unit)
    {
        unit_ = unit;
    }

    OHOS::Ace::CanvasUnit GetUnit()
    {
        return unit_;
    }

    double GetDensity()
    {
        return 0;
    }

private:
    int32_t id_ = 0;
    OHOS::Ace::WeakPtr<OHOS::Ace::NG::GeneratedModifier::CanvasRendererPeerImpl> canvasRenderWeak_;
    OHOS::Ace::CanvasUnit unit_ = OHOS::Ace::CanvasUnit::DEFAULT;
};

#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_CANVAS_PATTERN_PEER_IMPL_H
