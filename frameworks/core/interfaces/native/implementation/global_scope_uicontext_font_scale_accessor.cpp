/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace GlobalScopeUicontextFontScaleAccessor {
Ark_Boolean IsFollowingSystemFontScaleImpl()
{
    bool follow = false;
    auto container = Container::CurrentSafely();
    CHECK_NULL_RETURN(container, Converter::ArkValue<Ark_Boolean>(follow));
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, Converter::ArkValue<Ark_Boolean>(follow));
    follow = pipelineContext->IsFollowSystem();
    return Converter::ArkValue<Ark_Boolean>(follow);
}
Ark_Number GetMaxFontScaleImpl()
{
    float maxFontScale = 0.0f;
    auto container = Container::CurrentSafely();
    CHECK_NULL_RETURN(container, Converter::ArkValue<Ark_Number>(maxFontScale));
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, Converter::ArkValue<Ark_Number>(maxFontScale));
    maxFontScale = pipelineContext->GetMaxAppFontScale();
    return Converter::ArkValue<Ark_Number>(maxFontScale);
}
} // GlobalScopeUicontextFontScaleAccessor
const GENERATED_ArkUIGlobalScopeUicontextFontScaleAccessor* GetGlobalScopeUicontextFontScaleAccessor()
{
    static const GENERATED_ArkUIGlobalScopeUicontextFontScaleAccessor GlobalScopeUicontextFontScaleAccessorImpl {
        GlobalScopeUicontextFontScaleAccessor::IsFollowingSystemFontScaleImpl,
        GlobalScopeUicontextFontScaleAccessor::GetMaxFontScaleImpl,
    };
    return &GlobalScopeUicontextFontScaleAccessorImpl;
}

}

