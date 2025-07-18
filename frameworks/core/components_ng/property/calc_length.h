/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_PROPERTIES_CALC_LENGTH_H
#define FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_PROPERTIES_CALC_LENGTH_H

#include "ui/properties/ng/calc_length.h"

namespace OHOS::Ace {

class PipelineBase;
};

namespace OHOS::Ace::NG {
#ifdef ACE_STATIC
struct ACE_FORCE_EXPORT ScaleProperty {
#else
struct ACE_EXPORT ScaleProperty {
#endif
    float vpScale = 0.0f;
    float fpScale = 0.0f;
    float lpxScale = 0.0f;

    void Reset()
    {
        vpScale = 0.0;
        fpScale = 0.0;
        lpxScale = 0.0;
    }

    bool operator==(const ScaleProperty& scaleProperty) const
    {
        return NearEqual(vpScale, scaleProperty.vpScale) && NearEqual(fpScale, scaleProperty.fpScale) &&
               NearEqual(lpxScale, scaleProperty.lpxScale);
    }

    bool operator!=(const ScaleProperty& scaleProperty) const
    {
        return !(*this == scaleProperty);
    }

    static ScaleProperty CreateScaleProperty(PipelineBase* context = nullptr);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_PROPERTIES_CALC_LENGTH_H
