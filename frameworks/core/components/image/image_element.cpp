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

#include "core/components/image/image_element.h"

namespace OHOS::Ace {

void ImageElement::Update()
{
    RenderElement::Update();

    auto imageComponent = AceType::DynamicCast<ImageComponent>(component_);
    if (imageComponent) {
        SetFocusable(imageComponent->GetFocusable());
    }
}

bool ImageElement::OnKeyEvent(const KeyEvent& keyEvent)
{
    if (FocusNode::OnKeyEvent(keyEvent)) {
        return true;
    }

    auto renderImage = DynamicCast<RenderImage>(renderNode_);
    return (renderImage && renderImage->HandleKeyEvent(keyEvent));
}

} // namespace OHOS::Ace
