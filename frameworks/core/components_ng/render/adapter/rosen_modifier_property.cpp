/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/render/adapter/rosen_modifier_property.h"

#ifndef MODIFIER_NG
#include "base/utils/utils.h"
#endif

namespace OHOS::Ace::NG {
#ifndef MODIFIER_NG
template<typename T>
bool CreateOrSetModifierValue(std::shared_ptr<Rosen::RSAnimatableProperty<T>>& property, const T& value)
{
    if (property == nullptr) {
        property = std::make_shared<Rosen::RSAnimatableProperty<T>>(value);
        return true;
    }
    property->Set(value);
    return false;
}

void AddOrChangeScaleModifier(std::shared_ptr<Rosen::RSNode>& rsNode,
    std::shared_ptr<Rosen::RSScaleModifier>& modifier,
    std::shared_ptr<Rosen::RSAnimatableProperty<Rosen::Vector2f>>& property, const Rosen::Vector2f& value)
{
    bool isCreate = CreateOrSetModifierValue(property, value);
    if (isCreate) {
        CHECK_NULL_VOID(rsNode);
        modifier = std::make_shared<Rosen::RSScaleModifier>(property);
        rsNode->AddModifier(modifier);
    }
}

void AddOrChangeScaleZModifier(std::shared_ptr<Rosen::RSNode>& rsNode,
    std::shared_ptr<Rosen::RSScaleZModifier>& modifier,
    std::shared_ptr<Rosen::RSAnimatableProperty<float>>& property, const float value)
{
    bool isCreate = CreateOrSetModifierValue(property, value);
    if (isCreate) {
        CHECK_NULL_VOID(rsNode);
        modifier = std::make_shared<Rosen::RSScaleZModifier>(property);
        rsNode->AddModifier(modifier);
    }
}

void AddOrChangeSkewModifier(std::shared_ptr<Rosen::RSNode>& rsNode,
    std::shared_ptr<Rosen::RSSkewModifier>& modifier,
    std::shared_ptr<Rosen::RSAnimatableProperty<Rosen::Vector3f>>& property, const Rosen::Vector3f& value)
{
    bool isCreate = CreateOrSetModifierValue(property, value);
    if (isCreate) {
        CHECK_NULL_VOID(rsNode);
        modifier = std::make_shared<Rosen::RSSkewModifier>(property);
        rsNode->AddModifier(modifier);
    }
}

void AddOrChangePivotModifier(std::shared_ptr<Rosen::RSNode>& rsNode,
    std::shared_ptr<Rosen::RSPivotModifier>& modifier,
    std::shared_ptr<Rosen::RSAnimatableProperty<Rosen::Vector2f>>& property, const Rosen::Vector2f& value)
{
    bool isCreate = CreateOrSetModifierValue(property, value);
    if (isCreate) {
        CHECK_NULL_VOID(rsNode);
        modifier = std::make_shared<Rosen::RSPivotModifier>(property);
        rsNode->AddModifier(modifier);
    }
}

void AddOrChangeTranslateZModifier(std::shared_ptr<Rosen::RSNode>& rsNode,
    std::shared_ptr<Rosen::RSTranslateZModifier>& modifier,
    std::shared_ptr<Rosen::RSAnimatableProperty<float>>& property, const float value)
{
    bool isCreate = CreateOrSetModifierValue(property, value);
    if (isCreate) {
        CHECK_NULL_VOID(rsNode);
        modifier = std::make_shared<Rosen::RSTranslateZModifier>(property);
        rsNode->AddModifier(modifier);
    }
}

void AddOrChangePerspectiveModifier(std::shared_ptr<Rosen::RSNode>& rsNode,
    std::shared_ptr<Rosen::RSPerspModifier>& modifier,
    std::shared_ptr<Rosen::RSAnimatableProperty<Rosen::Vector4f>>& property, const Rosen::Vector4f& value)
{
    bool isCreate = CreateOrSetModifierValue(property, value);
    if (isCreate) {
        CHECK_NULL_VOID(rsNode);
        modifier = std::make_shared<Rosen::RSPerspModifier>(property);
        rsNode->AddModifier(modifier);
    }
}

void AddOrChangeTranslateModifier(std::shared_ptr<Rosen::RSNode>& rsNode,
    std::shared_ptr<Rosen::RSTranslateModifier>& modifier,
    std::shared_ptr<Rosen::RSAnimatableProperty<Rosen::Vector2f>>& property, const Rosen::Vector2f& value)
{
    bool isCreate = CreateOrSetModifierValue(property, value);
    if (isCreate) {
        CHECK_NULL_VOID(rsNode);
        modifier = std::make_shared<Rosen::RSTranslateModifier>(property);
        rsNode->AddModifier(modifier);
    }
}

void AddOrChangeQuaternionModifier(std::shared_ptr<Rosen::RSNode>& rsNode,
    std::shared_ptr<Rosen::RSQuaternionModifier>& modifier,
    std::shared_ptr<Rosen::RSAnimatableProperty<Rosen::Quaternion>>& property, const Rosen::Quaternion& value)
{
    bool isCreate = CreateOrSetModifierValue(property, value);
    if (isCreate) {
        CHECK_NULL_VOID(rsNode);
        modifier = std::make_shared<Rosen::RSQuaternionModifier>(property);
        rsNode->AddModifier(modifier);
    }
}

void WindowBlurModifier::AddOrChangeRadiusModifier(std::shared_ptr<Rosen::RSNode>& rsNode,
    std::shared_ptr<Rosen::RSBehindWindowFilterRadiusModifier>& modifier,
    std::shared_ptr<Rosen::RSAnimatableProperty<float>>& property, const float& value)
{
    bool isCreate = CreateOrSetModifierValue(property, value);
    if (isCreate) {
        CHECK_NULL_VOID(rsNode);
        modifier = std::make_shared<Rosen::RSBehindWindowFilterRadiusModifier>(property);
        rsNode->AddModifier(modifier);
    }
}
void WindowBlurModifier::AddOrChangeSaturationModifier(std::shared_ptr<Rosen::RSNode>& rsNode,
    std::shared_ptr<Rosen::RSBehindWindowFilterSaturationModifier>& modifier,
    std::shared_ptr<Rosen::RSAnimatableProperty<float>>& property, const float& value)
{
    bool isCreate = CreateOrSetModifierValue(property, value);
    if (isCreate) {
        CHECK_NULL_VOID(rsNode);
        modifier = std::make_shared<Rosen::RSBehindWindowFilterSaturationModifier>(property);
        rsNode->AddModifier(modifier);
    }
}
void WindowBlurModifier::AddOrChangeBrightnessModifier(std::shared_ptr<Rosen::RSNode>& rsNode,
    std::shared_ptr<Rosen::RSBehindWindowFilterBrightnessModifier>& modifier,
    std::shared_ptr<Rosen::RSAnimatableProperty<float>>& property, const float& value)
{
    bool isCreate = CreateOrSetModifierValue(property, value);
    if (isCreate) {
        CHECK_NULL_VOID(rsNode);
        modifier = std::make_shared<Rosen::RSBehindWindowFilterBrightnessModifier>(property);
        rsNode->AddModifier(modifier);
    }
}
void WindowBlurModifier::AddOrChangeMaskColorModifier(std::shared_ptr<Rosen::RSNode>& rsNode,
    std::shared_ptr<Rosen::RSBehindWindowFilterMaskColorModifier>& modifier,
    std::shared_ptr<Rosen::RSAnimatableProperty<Rosen::RSColor>>& property, const Rosen::RSColor& value)
{
    bool isCreate = CreateOrSetModifierValue(property, value);
    if (isCreate) {
        CHECK_NULL_VOID(rsNode);
        modifier = std::make_shared<Rosen::RSBehindWindowFilterMaskColorModifier>(property);
        rsNode->AddModifier(modifier);
    }
}
#endif
} // namespace OHOS::Ace::NG