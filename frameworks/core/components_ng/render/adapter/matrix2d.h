/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_MATRIX2D_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_MATRIX2D_H

#include <string>
#include "frameworks/core/components/common/properties/paint_state.h"

namespace OHOS::Ace::NG {
class ACE_FORCE_EXPORT Matrix2D final {
public:
    static bool Invert(TransformParam& param);
    static void Identity(TransformParam& param);
    static void Scale(TransformParam& param, double sx, double sy);
    static void Translate(TransformParam& param, double tx, double ty);
    static void Rotate(TransformParam& param, double degree, double dx, double dy);
    static std::string ToString();
};
Matrix4 SetMatrixPolyToPoly(const Matrix4& matrix, const std::vector<OHOS::Ace::NG::PointT<int32_t>>& totalPoint);
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_MATRIX2D_H

