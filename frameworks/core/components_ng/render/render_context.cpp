/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/render/render_context.h"

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
void RenderContext::SetRequestFrame(const std::function<void()>& requestFrame)
{
    requestFrame_ = requestFrame;
}

void RenderContext::RequestNextFrame() const
{
    if (requestFrame_) {
        requestFrame_();
    }
}

void RenderContext::SetHostNode(const WeakPtr<FrameNode>& host)
{
    host_ = host;
}

RefPtr<FrameNode> RenderContext::GetHost() const
{
    return host_.Upgrade();
}

void RenderContext::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    ACE_PROPERTY_TO_JSON_VALUE(propBorder_, BorderProperty);
    ACE_PROPERTY_TO_JSON_VALUE(propBdImage_, BorderImageProperty);
    ACE_PROPERTY_TO_JSON_VALUE(propOverlay_, OverlayProperty);
    ACE_PROPERTY_TO_JSON_VALUE(propPositionProperty_, RenderPositionProperty);
    ACE_PROPERTY_TO_JSON_VALUE(propBackground_, BackgroundProperty);
    ACE_PROPERTY_TO_JSON_VALUE(propGraphics_, GraphicsProperty);
    ACE_PROPERTY_TO_JSON_VALUE(propGradient_, GradientProperty);
    ACE_PROPERTY_TO_JSON_VALUE(propTransform_, TransformProperty);
    ACE_PROPERTY_TO_JSON_VALUE(propClip_, ClipProperty);
    if (propTransformMatrix_.has_value()) {
        auto jsonValue = JsonUtil::Create(true);
        jsonValue->Put("type", "matrix");
        auto matrixString = propTransformMatrix_->ToString();
        while (matrixString.find("\n") != std::string::npos) {
            auto num = matrixString.find("\n");
            matrixString.replace(num, 1, "");
        }
        jsonValue->Put("matrix", matrixString.c_str());
        json->Put("transform", jsonValue);
    } else {
        json->Put("transform", JsonUtil::Create(true));
    }
    json->Put("backgroundColor", propBackgroundColor_.value_or(Color::TRANSPARENT).ColorToString().c_str());
    json->Put("zIndex", propZIndex_.value_or(0));
    json->Put("opacity", propOpacity_.value_or(1));
    static const char* STYLE[] = {"", "BlurStyle.Thin", "BlurStyle.Regular", "BlurStyle.Thick",
        "BlurStyle.BackgroundThin", "BlurStyle.BackgroundRegular",
        "BlurStyle.BackgroundThick", "BlurStyle.BackgroundUltraThick"};
    json->Put("backgroundBlurStyle", STYLE[static_cast<int>(
        GetBackBlurStyle().value_or(BlurStyleOption()).blurStyle)]);
}
} // namespace OHOS::Ace::NG
