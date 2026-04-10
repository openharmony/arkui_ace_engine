/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_UI_MATERIAL_FILTER_CREATOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_UI_MATERIAL_FILTER_CREATOR_H

#include <memory>

namespace OHOS::Rosen {
class RSNGFilterBase;
}

namespace OHOS::Ace {
class Color;
enum class UiMaterialLevel;
enum class UiMaterialStyle;
enum class ColorMode;
enum class UiMaterialTransparency;
struct ImmersiveMaterialConfig;
}

namespace OHOS::Ace::NG {

class UiMaterialFilterCreator {
public:
    static std::shared_ptr<Rosen::RSNGFilterBase> ConvertToUiMaterialFilter(const ImmersiveMaterialConfig& params);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_UI_MATERIAL_FILTER_CREATOR_H
