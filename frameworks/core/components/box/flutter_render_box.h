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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BOX_FLUTTER_RENDER_BOX_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BOX_FLUTTER_RENDER_BOX_H

#include "flutter/lib/ui/ui_dart_state.h"

#include "core/components/box/render_box.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/border_edge.h"
#include "core/image/image_provider.h"
#include "core/pipeline/base/flutter_render_context.h"
#include "core/pipeline/layers/clip_layer.h"
#include "core/pipeline/layers/container_layer.h"

namespace OHOS::Ace {

class FlutterRenderBox : public RenderBox {
    DECLARE_ACE_TYPE(FlutterRenderBox, RenderBox);

public:
    FlutterRenderBox() = default;
    ~FlutterRenderBox() override = default;

    void Update(const RefPtr<Component>& component) override;
    void PerformLayout() override;
    void Paint(RenderContext& context, const Offset& offset) override;
    RenderLayer GetRenderLayer() override;

    bool SupportOpacity() override
    {
        return true;
    }

protected:
    virtual bool MaybeRelease() override;

    void OnVisibleChanged() override
    {
        RenderBox::OnVisibleChanged();

        if (NeedWindowBlur()) {
            if (GetVisible()) {
                UpdateWindowBlurRRect();
            } else {
                UpdateWindowBlurRRect(true);
            }
        }
    }

    void OnHiddenChanged(bool hidden) override
    {
        RenderBox::OnHiddenChanged(hidden);

        if (NeedWindowBlur()) {
            if (GetHidden()) {
                UpdateWindowBlurRRect(true);
            } else {
                UpdateWindowBlurRRect();
            }
        }
    }

    void OnWindowBlurChanged() override
    {
        RenderBox::OnWindowBlurChanged();

        if (NeedWindowBlur()) {
            UpdateWindowBlurRRect();
        } else {
            UpdateWindowBlurRRect(true);
        }
    }

    RRect GetWindowBlurRRect() const override
    {
        return windowBlurRRect_;
    }

    void CalculateRepeatParam();

private:
    bool CheckBorderEdgeForRRect(const Border& border);
    SkVector GetSkRadii(const Radius& radius, double shrinkFactor, double borderWidth);
    void UpdateBackgroundImage(const RefPtr<BackgroundImage>& image);
    void UpdateBlurRRect(const flutter::RRect& rRect, const Offset& offset);
    void DrawLayerForBlur(SkCanvas* canvas, Flutter::ContainerLayer* containerLayer);
    flutter::RRect GetBoxRRect(const Offset& offset, const Border& border, double shrinkFactor, bool isRound);

    RefPtr<Flutter::ClipLayer> clipLayer_;
    RRect windowBlurRRect_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BOX_FLUTTER_RENDER_BOX_H
