/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef SHADOW_H
#define SHADOW_H

namespace OHOS {
namespace Rosen {
namespace Drawing {
enum class ShadowFlags {
    NONE = 0,
    /**
     * The occluding object is not opaque. Knowing that the occluder is opaque allows
     * us to cull shadow geometry behind it and improve performance.
     */
    TRANSPARENT_OCCLUDER,
    /** Don't try to use analytic shadows. */
    GEOMETRIC_ONLY,
    /** mask for all shadow flags */
    ALL,
};
} // namespace Drawing
} // namespace Rosen
} // namespace OHOS
#endif
