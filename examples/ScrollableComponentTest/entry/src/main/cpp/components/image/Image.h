/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef ARKUI_CAPI_DEMO_IMAGE_COMPONENT_H
#define ARKUI_CAPI_DEMO_IMAGE_COMPONENT_H

#include <cstdint>
#include <string>

#include "components/component.h"

namespace ArkUICApiDemo {
class ImageComponent : public Component {
public:
    ImageComponent() : Component(ARKUI_NODE_IMAGE) {}
    explicit ImageComponent(ArkUI_NodeHandle handle) : Component(handle) {}

    int32_t SetImageSrc(const std::string& content);
    int32_t SetImageSrc(ArkUI_DrawableDescriptor* descriptors);
    int32_t SetObjectFit(const int32_t objectFit);
    int32_t SetResizable(const float left, const float top, const float right, const float bottom);
    int32_t SetImageDraggable(bool isDraggable);
    int32_t SetImageRenderMode(int32_t renderMode);
    int32_t SetImageFitOriginalSize(int32_t fitOriginalSize);
    int32_t SetImageFillColor(uint32_t color);
    int32_t SetGeometryTransition(int32_t type, const std::string &id);
};
} // namespace ArkUICApiDemo
#endif // ARKUI_CAPI_DEMO_IMAGE_COMPONENT_H