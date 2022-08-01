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

#include "core/components/display/flutter_render_display.h"

namespace OHOS::Ace {

using namespace Flutter;

RenderLayer FlutterRenderDisplay::GetRenderLayer()
{
    if (disableLayer_) {
        return nullptr;
    }

    if (opacity_ == 255) {
        layer_ = nullptr;
        return nullptr;
    }
    if (!layer_) {
        layer_ = AceType::MakeRefPtr<OpacityLayer>(opacity_, 0.0, 0.0);
    }
    return AceType::RawPtr(layer_);
}

void FlutterRenderDisplay::Paint(RenderContext& context, const Offset& offset)
{
    if (visible_ == VisibleType::VISIBLE) {
        if (!disableLayer_ && layer_) {
            layer_->SetOpacity(opacity_, 0.0, 0.0);
        }
        if (HasBackgroundMask()) {
            flutter::Canvas* canvas = static_cast<FlutterRenderContext*>(&context)->GetCanvas();
            if (canvas == nullptr) {
                LOGE("Paint canvas is null.");
                return;
            }
            SkPaint paint;
            paint.setColor(GetBackgroundMask().GetValue());
            auto skCanvas = canvas->canvas();
            skCanvas->drawRect(
                SkRect::MakeXYWH(offset.GetX(), offset.GetY(), GetLayoutSize().Width(), GetLayoutSize().Height()),
                paint);
        }
        RenderNode::Paint(context, offset);
    }
}

} // namespace OHOS::Ace