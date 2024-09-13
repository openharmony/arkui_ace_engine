/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace PanGestureOptionsModifier {
Ark_NativePointer CtorImpl(const Opt_Literal_Opt_Number_fingers_distance_Opt_PanDirection_direction* value)
{
    return 0;
}
Ark_NativePointer GetFinalizerImpl()
{
    return 0;
}
void SetDirectionImpl(PanGestureOptionsPeer* peer,
                      enum Ark_PanDirection value)
{
}
void SetDistanceImpl(PanGestureOptionsPeer* peer,
                     const Ark_Number* value)
{
}
void SetFingersImpl(PanGestureOptionsPeer* peer,
                    const Ark_Number* value)
{
}
Ark_NativePointer GetDirectionImpl(PanGestureOptionsPeer* peer)
{
    return 0;
}
} // PanGestureOptionsModifier
const GENERATED_ArkUIPanGestureOptionsAccessor* GetPanGestureOptionsAccessor()
{
    static const GENERATED_ArkUIPanGestureOptionsAccessor PanGestureOptionsAccessorImpl {
        PanGestureOptionsModifier::CtorImpl,
        PanGestureOptionsModifier::GetFinalizerImpl,
        PanGestureOptionsModifier::SetDirectionImpl,
        PanGestureOptionsModifier::SetDistanceImpl,
        PanGestureOptionsModifier::SetFingersImpl,
        PanGestureOptionsModifier::GetDirectionImpl,
    };
    return &PanGestureOptionsAccessorImpl;
}

}
