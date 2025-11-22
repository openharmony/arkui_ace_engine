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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_UI_MATERIAL_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_UI_MATERIAL_THEME_H

#include "core/components/common/properties/ui_material.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"

namespace OHOS::Ace {

namespace NG {
class PipelineContext;
};

class ACE_FORCE_EXPORT UiMaterialTheme : public virtual Theme {
    DECLARE_ACE_TYPE(UiMaterialTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;
        RefPtr<UiMaterialTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const;
    };
    UiMaterialTheme() = default;
    ~UiMaterialTheme() override = default;
    std::optional<UiMaterialParam> GetUiMaterialParam(MaterialType type, NG::PipelineContext* pipeline);
    void SetInstanceId(int32_t instanceId);

private:
    bool ParseUiMaterialParam(MaterialType type, NG::PipelineContext* pipeline, ColorMode colorMode,
        UiMaterialParam& result);
    uint32_t GetKeyOfUiMaterial(MaterialType type, ColorMode colorMode);
    int32_t instanceId_ = -1;
    std::unordered_map<uint32_t, UiMaterialParam> materialParams_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_UI_MATERIAL_THEME_H
