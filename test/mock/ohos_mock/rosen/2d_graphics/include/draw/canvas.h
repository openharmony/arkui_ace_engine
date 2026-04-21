/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef CANVAS_H
#define CANVAS_H

#include <iostream>
#include <string>
#include <vector>

#include "core_canvas.h"

namespace OHOS {
namespace Rosen {
namespace Drawing {
class Canvas : public CoreCanvas {
public:
    Canvas() {}
    Canvas(int32_t width, int32_t height) : CoreCanvas(width, height) {}

    virtual ~Canvas();

    void RestoreToCount(uint32_t count);
};
} // namespace Drawing
} // namespace Rosen
} // namespace OHOS
#endif
