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

#ifndef ARKUI_CAPI_DEMO_IMAGEANIMATOR_COMPONENT_H
#define ARKUI_CAPI_DEMO_IMAGEANIMATOR_COMPONENT_H

#include <string>

#include "components/component.h"

namespace ArkUICApiDemo {
class ImageAnimatorComponent : public Component {
public:
    ImageAnimatorComponent() : Component(ARKUI_NODE_IMAGE_ANIMATOR) {}
    explicit ImageAnimatorComponent(ArkUI_NodeHandle handle) : Component(handle) {}
    void SetState(int32_t state);
    void SetIteration(int32_t iteration);
    void SetImage(std::vector<ArkUI_ImageAnimatorFrameInfo*>& vector);
    void SetFixedSize(int32_t fixedSize);
    void SetReverse(int32_t reverse);
    void SetFillMode(int32_t mode);
    void SetDuration(int32_t duration);
};
} // namespace ArkUICApiDemo
#endif // ARKUI_CAPI_DEMO_IMAGEANIMATOR_COMPONENT_H
