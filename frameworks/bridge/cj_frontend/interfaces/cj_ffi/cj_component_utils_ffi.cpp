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

#include "cj_component_utils_ffi.h"
#include "core/components_ng/base/inspector.h"

using namespace OHOS;
using namespace OHOS::Ace;

extern "C" {
CComponentInfo FFIOHOSAceFrameworkComponentUtilsGetById(const char *id)
{
    OHOS::Ace::NG::Rectangle rectangle;
    std::string key = id;
    NG::Inspector::GetRectangleById(key, rectangle);

    CComponentInfo info;
    info.size.width = rectangle.size.Width();
    info.size.height = rectangle.size.Height();
    info.localOffset.x = rectangle.localOffset.GetX();
    info.localOffset.y = rectangle.localOffset.GetY();
    info.windowOffset.x = rectangle.windowOffset.GetX();
    info.windowOffset.y = rectangle.windowOffset.GetY();
    info.screenOffset.x = rectangle.windowOffset.GetX() + rectangle.screenRect.GetOffset().GetX();
    info.screenOffset.y = rectangle.windowOffset.GetY() + rectangle.screenRect.GetOffset().GetY();
    info.translate.x = rectangle.translate.x;
    info.translate.y = rectangle.translate.y;
    info.translate.z = rectangle.translate.z;
    info.scale.x = rectangle.scale.x;
    info.scale.y = rectangle.scale.y;
    info.scale.z = rectangle.scale.z;
    info.scale.centerX = rectangle.scale.centerX;
    info.scale.centerY = rectangle.scale.centerY;
    info.rotate.x = rectangle.rotate.x;
    info.rotate.y = rectangle.rotate.y;
    info.rotate.z = rectangle.rotate.z;
    info.rotate.centerX = rectangle.rotate.centerX;
    info.rotate.centerY = rectangle.rotate.centerY;
    info.rotate.angle = rectangle.rotate.angle;

    const size_t TRANSFORM_SIZE = 16;
    CArrFloat32 transform = {NULL, 0};
    transform.head = static_cast<float *>(malloc(sizeof(float) * TRANSFORM_SIZE));
    if (transform.head != NULL) {
        for (size_t i = 0; i < TRANSFORM_SIZE; ++i) {
            transform.head[i] = rectangle.matrix4[i];
        }
    }
    transform.size = TRANSFORM_SIZE;
    info.transform = transform;

    return info;
}
} // extern "C"