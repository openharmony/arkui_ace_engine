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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_RENDER_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_RENDER_PROPERTY_H

#include <memory>

#include "core/components_ng/property/property.h"
#include "core/components_ng/property/render_property.h"
#include "core/components_ng/render/render_context.h"

namespace OHOS::Ace::NG {
// RenderProperty are used to set render properties.
class RenderProperty : public Property {
    DECLARE_ACE_TYPE(RenderProperty, Property)

public:
    RenderProperty() = default;
    ~RenderProperty() override = default;

    virtual RefPtr<RenderProperty> Clone() const
    {
        auto renderProperty = MakeRefPtr<RenderProperty>();
        renderProperty->UpdateRenderProperty(this);
        return renderProperty;
    }

    virtual void Reset() {}

protected:
    void UpdateRenderProperty(const RenderProperty* renderProperty) {}

private:
    friend class RenderContext;
    friend class RosenRenderContext;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_RENDER_PROPERTY_H
