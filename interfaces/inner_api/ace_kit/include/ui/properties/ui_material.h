/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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
 
#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_PROPERTIES_UI_MATERIAL_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_PROPERTIES_UI_MATERIAL_H

#include <memory>
#include <vector>

#include "ui/base/ace_type.h"
#include "ui/properties/color.h"
#include "ui/properties/ui_material_enums.h"
#include "ui/resource/resource_object.h"

namespace OHOS::Ace {

struct ImmersiveOptions {
    UiMaterialStyle style = UiMaterialStyle::REGULAR;
    Color materialColor = Color::TRANSPARENT;
    bool colorInvert = false;
    bool applyShadow = true;
    RefPtr<ResourceObject> colorResObj = nullptr;
};

class ACE_FORCE_EXPORT UiMaterial : public AceType {
    DECLARE_ACE_TYPE(UiMaterial, AceType);

public:
    UiMaterial() = default;
    ~UiMaterial() override = default;
    bool operator==(const UiMaterial& other) const
    {
        return type_  == other.type_ && isEmpty_ == other.isEmpty_;
    }
    void SetType(int32_t type)
    {
        type_ = type;
    }
    int32_t GetType() const
    {
        return type_;
    }
    void SetEmpty(bool isEmpty)
    {
        isEmpty_ = isEmpty;
    }
    bool IsEmpty() const
    {
        return isEmpty_;
    }
    void SetImmersiveOptions(const ImmersiveOptions& options);
    const std::shared_ptr<ImmersiveOptions>& GetImmersiveOptions() const;
    // create a copy of immersiveOptions.
    std::shared_ptr<ImmersiveOptions> CopyImmersiveOptions() const;
    // create a copy of UiMaterial.
    virtual RefPtr<UiMaterial> Copy() const;
    // return whether contains applyShadow effect.
    virtual bool IsForceShadow() const;
    // Get material state from application configuration.
    static MaterialState GetConfiguredMaterialState();
    // Check if material is disabled (state == DISABLE).
    static bool IsMaterialDisabled();
    // Check if material is enabled (state == ENABLE).
    static bool IsMaterialEnabled();
    static RefPtr<UiMaterial> CreateEmpty();
protected:
    // copy member of self.
    virtual void CopyTo(RefPtr<UiMaterial>& other) const;

    int32_t type_{0};
    bool isEmpty_{false};
    std::shared_ptr<ImmersiveOptions> immersiveOptions_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_PROPERTIES_UI_MATERIAL_H
