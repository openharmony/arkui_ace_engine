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

#ifndef PATH_EFFECT_H
#define PATH_EFFECT_H

#include "draw/path.h"
#include "utils/scalar.h"

namespace OHOS {
namespace Rosen {
namespace Drawing {
enum class PathDashStyle {
    TRANSLATE,
    ROTATE,
    MORPH,
};
class PathEffect {
public:
    enum class PathEffectType {
        NO_TYPE,
        DASH,
        PATH_DASH,
        CORNER,
        DISCRETE,
        SUM,
        COMPOSE,
    };

    static std::shared_ptr<PathEffect> CreatePathDashEffect(
        const Path& /* path */, float /* advance */, float /* phase */, PathDashStyle /* style */)
    {
        return std::make_shared<PathEffect>();
    }

    static std::shared_ptr<PathEffect> CreateDashPathEffect(const float intervals[], int count, float phase)
    {
        return std::make_shared<PathEffect>();
    }
};
} // namespace Drawing
} // namespace Rosen
} // namespace OHOS
#endif
