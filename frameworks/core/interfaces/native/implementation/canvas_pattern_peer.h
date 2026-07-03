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
#include "matrix2d_peer_impl.h"

struct CanvasPatternPeer : OHOS::Ace::Referenced {
public:
    CanvasPatternPeer() = default;
    virtual ~CanvasPatternPeer() = default;

    void SetTransform(const std::optional<Matrix2DPeer*>& optMatrix)
    {
        CHECK_NULL_VOID(pattern_);
        if (optMatrix && optMatrix.value()) {
            auto matrix = optMatrix.value();
            CHECK_NULL_VOID(matrix);
            auto transform = matrix->GetTransform();
            pattern_->SetScaleX(transform.scaleX);
            pattern_->SetScaleY(transform.scaleY);
            pattern_->SetSkewX(transform.skewX);
            pattern_->SetSkewY(transform.skewY);
            pattern_->SetTranslateX(transform.translateX);
            pattern_->SetTranslateY(transform.translateY);
        }
    }

    std::shared_ptr<OHOS::Ace::Pattern> GetPattern() const
    {
        return pattern_;
    }

    void SetPattern(const std::shared_ptr<OHOS::Ace::Pattern>& pattern)
    {
        pattern_ = pattern;
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
        double density = OHOS::Ace::PipelineBase::GetCurrentDensity();
        return ((GetUnit() == OHOS::Ace::CanvasUnit::DEFAULT) && !OHOS::Ace::NearZero(density)) ? density : 1.0;
    }

private:
    std::shared_ptr<OHOS::Ace::Pattern> pattern_;
    OHOS::Ace::CanvasUnit unit_ = OHOS::Ace::CanvasUnit::DEFAULT;
};

#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_CANVAS_PATTERN_PEER_IMPL_H
