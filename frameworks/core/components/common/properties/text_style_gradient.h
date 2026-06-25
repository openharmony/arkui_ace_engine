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
 
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_TEXT_STYLE_GRADIENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_TEXT_STYLE_GRADIENT_H
#include "ui/base/ace_type.h"
#include "core/components_ng/property/gradient_property.h"
#include "core/components/common/properties/gradient.h"
 
#define ACE_DEFINE_TEXT_STYLE_GRADIENT_OPTIONAL_TYPE()                        \
    RefPtr<OptGradient> propGradient;                                         \
public:                                                                       \
    bool HasGradient() const                                                  \
    {                                                                         \
        CHECK_NULL_RETURN(propGradient, false);                               \
        return propGradient->GetGradient().has_value();                       \
    }                                                                         \
    std::optional<Gradient> GetGradient() const                               \
    {                                                                         \
        CHECK_NULL_RETURN(propGradient, std::nullopt);                        \
        return propGradient->GetGradient();                                   \
    }                                                                         \
    std::optional<Gradient>& GetOptGradient() const                           \
    {                                                                         \
        return propGradient->GetGradient();                                   \
    }                                                                         \
    void SetGradient(const Gradient& newValue)                                \
    {                                                                         \
        if (!propGradient) {                                                  \
            propGradient = AceType::MakeRefPtr<OptGradient>();                \
        }                                                                     \
        CHECK_NULL_VOID(propGradient);                                        \
        propGradient->SetGradient(newValue);                                  \
    }                                                                         \
    void SetOptGradient(const std::optional<Gradient>& newValue)              \
    {                                                                         \
        if (!newValue.has_value()) {                                          \
            CHECK_NULL_VOID(propGradient);                                    \
            propGradient->ResetGradient();                                    \
            return;                                                           \
        }                                                                     \
        if (!propGradient) {                                                  \
            propGradient = AceType::MakeRefPtr<OptGradient>();                \
        }                                                                     \
        CHECK_NULL_VOID(propGradient);                                        \
        propGradient->SetGradient(newValue);                                  \
    }                                                                         \
    void ResetGradient()                                                      \
    {                                                                         \
        CHECK_NULL_VOID(propGradient);                                        \
        propGradient->ResetGradient();                                        \
    }

#define ACE_DEFINE_TEXT_STYLE_NG_GRADIENT_OPTIONAL_TYPE()                     \
    RefPtr<OptNGGradient> propGradient;                                       \
public:                                                                       \
    bool HasGradient() const                                                  \
    {                                                                         \
        CHECK_NULL_RETURN(propGradient, false);                               \
        return propGradient->GetGradient().has_value();                       \
    }                                                                         \
    std::optional<NG::Gradient> GetGradient() const                           \
    {                                                                         \
        CHECK_NULL_RETURN(propGradient, std::nullopt);                        \
        return propGradient->GetGradient();                                   \
    }                                                                         \
    std::optional<NG::Gradient>& GetOptGradient() const                       \
    {                                                                         \
        return propGradient->GetGradient();                                   \
    }                                                                         \
    void SetGradient(const NG::Gradient& newValue)                            \
    {                                                                         \
        if (!propGradient) {                                                  \
            propGradient = AceType::MakeRefPtr<OptNGGradient>();              \
        }                                                                     \
        CHECK_NULL_VOID(propGradient);                                        \
        propGradient->SetGradient(newValue);                                  \
    }                                                                         \
    void SetOptGradient(const std::optional<NG::Gradient>& newValue)          \
    {                                                                         \
        if (!newValue.has_value()) {                                          \
            CHECK_NULL_VOID(propGradient);                                    \
            propGradient->ResetGradient();                                    \
            return;                                                           \
        }                                                                     \
        if (!propGradient) {                                                  \
            propGradient = AceType::MakeRefPtr<OptNGGradient>();              \
        }                                                                     \
        CHECK_NULL_VOID(propGradient);                                        \
        propGradient->SetGradient(newValue);                                  \
    }                                                                         \
    void ResetGradient()                                                      \
    {                                                                         \
        CHECK_NULL_VOID(propGradient);                                        \
        propGradient->ResetGradient();                                        \
    }
namespace OHOS::Ace {
class ACE_FORCE_EXPORT OptGradient : public AceType {
    DECLARE_ACE_TYPE(OptGradient, AceType);
 
public:
    ACE_FORCE_EXPORT void SetGradient(const std::optional<Gradient>& gradient);
    ACE_FORCE_EXPORT std::optional<Gradient>& GetGradient();
    ACE_FORCE_EXPORT void ResetGradient();
private:
    std::optional<Gradient> gradient_;
};
 
class ACE_FORCE_EXPORT OptNGGradient : public AceType {
    DECLARE_ACE_TYPE(OptNGGradient, AceType);
 
public:
    ACE_FORCE_EXPORT void SetGradient(const std::optional<NG::Gradient>& gradient);
    ACE_FORCE_EXPORT std::optional<NG::Gradient>& GetGradient();
    ACE_FORCE_EXPORT void ResetGradient();
private:
    std::optional<NG::Gradient> gradient_;
};
namespace GradientConvert {
    ACE_FORCE_EXPORT std::optional<NG::Gradient> ToNGGradient(const std::optional<Gradient>& gradient);
    ACE_FORCE_EXPORT std::optional<Gradient> ToGradient(const std::optional<NG::Gradient>& gradient);
    ACE_FORCE_EXPORT RefPtr<OptGradient> ToOptGradient(const NG::Gradient& gradient);
    ACE_FORCE_EXPORT RefPtr<OptGradient> ToOptGradient(const Gradient& gradient);
    ACE_FORCE_EXPORT RefPtr<OptGradient> ToOptGradient(const std::optional<NG::Gradient>& gradient);
    ACE_FORCE_EXPORT RefPtr<OptGradient> ToOptGradient(const std::optional<Gradient>& gradient);
    RefPtr<OptNGGradient> ToOptNGGradient(const NG::Gradient& gradient);
    RefPtr<OptNGGradient> ToOptNGGradient(const Gradient& gradient);
    RefPtr<OptNGGradient> ToOptNGGradient(const std::optional<NG::Gradient>& gradient);
    RefPtr<OptNGGradient> ToOptNGGradient(const std::optional<Gradient>& gradient);
    ACE_FORCE_EXPORT std::optional<NG::GradientDirection> ParseGradientDirection(const NG::Gradient& gradient);
    void ACE_FORCE_EXPORT SetGradientDirection(NG::Gradient& gradient, const NG::GradientDirection& direction);
}
} // namespace OHOS::Ace
 
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_TEXT_STYLE_GRADIENT_H