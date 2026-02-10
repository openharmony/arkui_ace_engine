/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef BLENDER_H
#define BLENDER_H

#include <memory>

#include "draw/blend_mode.h"

namespace OHOS {
namespace Rosen {
namespace Drawing {
class Blender {
public:
    Blender() noexcept;
    virtual ~Blender() = default;
    static std::shared_ptr<Blender> CreateWithBlendMode(BlendMode mode)
    {
        return std::make_shared<Blender>();
    }
};
} // namespace Drawing
} // namespace Rosen
} // namespace OHOS
#endif
