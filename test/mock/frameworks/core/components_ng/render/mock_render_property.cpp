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

#include "core/components/common/properties/border_image.h"
#include "core/components_ng/render/render_property.h"

namespace OHOS::Ace::NG {
void BorderProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const {}
void RenderPositionProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const {}
void GraphicsProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const {}
void BackgroundProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const {}
void ForegroundProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const {}
void ClipProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const {}
void GradientProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const {}
void TransformProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const {}
void PointLightProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const {}

const std::optional<RefPtr<BorderImage>>& BorderImageProperty::GetBorderImage() const
{
    return propBorderImage;
}

bool BorderImageProperty::HasBorderImage() const
{
    return propBorderImage.has_value();
}

RefPtr<BorderImage> BorderImageProperty::GetBorderImageValue() const
{
    return propBorderImage.value();
}

bool BorderImageProperty::UpdateBorderImage(const RefPtr<BorderImage>& value)
{
    if (propBorderImage.has_value()) {
        if (NearEqual(propBorderImage.value(), value)) {
            return false;
        }
    }
    propBorderImage = value;
    return true;
}

bool BorderImageProperty::UpdateBorderImage(const std::optional<RefPtr<BorderImage>>& value)
{
    if (value.has_value()) {
        return UpdateBorderImage(value.value());
    }
    return false;
}

bool BorderImageProperty::CheckBorderImage(const RefPtr<BorderImage>& value) const
{
    if (!propBorderImage.has_value()) {
        return false;
    }
    return NearEqual(propBorderImage.value(), value);
}

void BorderImageProperty::ResetBorderImage()
{
    propBorderImage.reset();
}

void BorderImageProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const {}
} // namespace OHOS::Ace::NG
