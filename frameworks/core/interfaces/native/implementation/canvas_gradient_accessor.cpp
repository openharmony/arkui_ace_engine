/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"
#include "canvas_gradient_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CanvasGradientAccessor {
void DestroyPeerImpl(CanvasGradientPeer* peer)
{
    if (peer) {
        delete peer;
    }
}
Ark_NativePointer CtorImpl()
{
    return new CanvasGradientPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void AddColorStopImpl(CanvasGradientPeer* peer,
                      const Ark_Number* offset,
                      const Ark_String* color)
{

    

     if (!isColorStopValid_ && gradient_->GetColors().empty()) {
        isColorStopValid_ = true;
    }
    if (isColorStopValid_ && info[0]->IsNumber() && info[1]->IsString()) {
        double offset = 0.0;
        JSViewAbstract::ParseJsDouble(info[0], offset);
        if (offset < 0 || offset > 1) {
            isColorStopValid_ = false;
            // if the offset is invalid, fill the shape with transparent
            gradient_->ClearColors();
            GradientColor color;
            color.SetColor(Color::TRANSPARENT);
            color.SetDimension(0.0);
            gradient_->AddColor(color);
            gradient_->AddColor(color);
            return;
        }
        std::string jsColor;
        GradientColor color;
        JSViewAbstract::ParseJsString(info[1], jsColor);
        Color colorFromString = Color::WHITE;
        if (!Color::ParseColorString(jsColor, colorFromString)) {
            gradient_->ClearColors();
            color.SetColor(Color::TRANSPARENT);
            color.SetDimension(0.0);
            gradient_->AddColor(color);
            gradient_->AddColor(color);
            isColorStopValid_ = false;
            return;
        }
        color.SetColor(colorFromString);
        color.SetDimension(offset);
        if (gradient_) {
            gradient_->AddColor(color);
        }
        auto colorSize = gradient_->GetColors().size();
        // prevent setting only one colorStop
        if (colorSize == 1) {
            gradient_->AddColor(color);
        }
    }
}
} // CanvasGradientAccessor
const GENERATED_ArkUICanvasGradientAccessor* GetCanvasGradientAccessor()
{
    static const GENERATED_ArkUICanvasGradientAccessor CanvasGradientAccessorImpl {
        CanvasGradientAccessor::DestroyPeerImpl,
        CanvasGradientAccessor::CtorImpl,
        CanvasGradientAccessor::GetFinalizerImpl,
        CanvasGradientAccessor::AddColorStopImpl,
    };
    return &CanvasGradientAccessorImpl;
}

}
