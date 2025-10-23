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

#ifndef ARKUI_CAPI_DEMO_IMAGESPAN_COMPONENT_H
#define ARKUI_CAPI_DEMO_IMAGESPAN_COMPONENT_H

#include <cstdint>
#include <string>

#include "components/component.h"

namespace ArkUICApiDemo {
class ImageSpanComponent : public Component {
public:
    ImageSpanComponent() : Component(ARKUI_NODE_IMAGE_SPAN) {}
    explicit ImageSpanComponent(ArkUI_NodeHandle handle) : Component(handle) {}

    int32_t SetImageSpanSrc(const std::string& content);
    int32_t SetImageSpanSrc(ArkUI_DrawableDescriptor* descriptors);
    int32_t SetImageSpanAlt(const std::string& alt);
};
} // namespace ArkUICApiDemo
#endif // ARKUI_CAPI_DEMO_IMAGESPAN_COMPONENT_H