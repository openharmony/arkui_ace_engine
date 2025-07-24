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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_OFFSCREEN_CANVAS_PEER_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_OFFSCREEN_CANVAS_PEER_H

#include "core/components_ng/pattern/canvas/offscreen_canvas_pattern.h"
#include "offscreen_canvas_rendering_context2d_peer_impl.h"
#include "arkoala_api_generated.h"

struct OffscreenCanvasPeer {
    OffscreenCanvasPeer() = default;
    virtual ~OffscreenCanvasPeer() = default;

    void SetOptions(const double cw, const double ch);
    void RemoveOptions();
    ImageBitmapPeer* TransferToImageBitmap(ImageBitmapPeer* bitmap);
    OffscreenCanvasRenderingContext2DPeer* GetContext2D(OffscreenCanvasRenderingContext2DPeer* offscreenCanvasContext,
        RenderingContextSettingsPeer* offscreenCanvasSettings);
    double OnGetHeight(double errValue);
    void OnSetHeight(double value);
    double OnGetWidth(double errValue);
    void OnSetWidth(double value);

    double GetDensity()
    {
        double density = OHOS::Ace::PipelineBase::GetCurrentDensity();
        return ((GetUnit() == OHOS::Ace::CanvasUnit::DEFAULT) && !OHOS::Ace::NearZero(density)) ? density : 1.0;
    }
    void SetWidth(double value)
    {
        width = value;
    }
    double GetWidth() const
    {
        return width;
    }
    void SetHeight(double value)
    {
        height = value;
    }
    double GetHeight() const
    {
        return height;
    }
    void SetUnit(OHOS::Ace::CanvasUnit value)
    {
        unit = value;
    }
    OHOS::Ace::CanvasUnit GetUnit()
    {
        return unit;
    }
    void SetDetachStatus(bool value)
    {
        isDetached = value;
    }
    bool IsDetached() const
    {
        return isDetached;
    }
    bool IsGetContext() const
    {
        return isGetContext;
    }
    void SetOffScreenPattern(const OHOS::Ace::RefPtr<OHOS::Ace::NG::OffscreenCanvasPattern>& value)
    {
        offscreenCanvasPattern = value;
    }
    enum class ContextType {
        CONTEXT_2D = 0,
    };

private:
    OHOS::Ace::RefPtr<OHOS::Ace::NG::OffscreenCanvasPattern> offscreenCanvasPattern;
    OHOS::Ace::NG::GeneratedModifier::OffscreenCanvasRenderingContext2DPeerImpl* offscreenCanvasContext;
    RenderingContextSettingsPeer* offscreenCanvasSettings;
    double width = 0.0f;
    double height = 0.0f;
    ContextType contextType;
    OHOS::Ace::CanvasUnit unit = OHOS::Ace::CanvasUnit::DEFAULT;
    bool isGetContext = false;
    bool isDetached = false;
};

#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_OFFSCREEN_CANVAS_PEER_H