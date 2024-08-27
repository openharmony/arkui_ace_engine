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
#include "core/interfaces/native/node/util_modifier.h"

#include "core/common/container.h"

namespace OHOS::Ace::NG {

ArkUI_Float32 GetDensity(int deviceId)
{
    return SystemProperties::GetResolution();
}

ArkUI_Float32 GetFontScale(int deviceId)
{
    auto scale = 0.0;
    auto density = SystemProperties::GetResolution();
    auto container = Container::Current();
    if (container && container->GetPipelineContext()) {
        scale = container->GetPipelineContext()->GetFontScale() * density;
    }
    return scale;
}

ArkUI_Float32 GetDesignWidthScale(int deviceId)
{
    auto scale = 0.0;
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, scale);
    auto frontend = container->GetFrontend();
    CHECK_NULL_RETURN(frontend, scale);
    auto windowConfig = frontend->GetWindowConfig();
    return windowConfig.GetDesignWidthScale(SystemProperties::GetDeviceWidth());
}

namespace NodeModifier {
const ArkUIUtilsModifier* GetUtilsModifier()
{
    static const ArkUIUtilsModifier modifier = {
        GetDensity,
        GetFontScale,
        GetDesignWidthScale,
    };
    return &modifier;
}

const CJUIUtilsModifier* GetCJUIUtilsModifier()
{
    static const CJUIUtilsModifier modifier = {
        GetDensity,
        GetFontScale,
        GetDesignWidthScale,
    };
    return &modifier;
}
}
} // namespace OHOS::Ace::NG