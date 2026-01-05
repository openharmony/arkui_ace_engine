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

#ifndef RENDER_SERVICE_CLIENT_CORE_MODIFIER_NG_CUSTOM_RS_CUSTOM_MODIFIER_H
#define RENDER_SERVICE_CLIENT_CORE_MODIFIER_NG_CUSTOM_RS_CUSTOM_MODIFIER_H

#include "draw/canvas.h"
#include "render_service_client/core/modifier_ng/rs_modifier_ng.h"
namespace OHOS::Rosen {
namespace ModifierNG {
struct RSDrawingContext {
    Drawing::Canvas* canvas;
    float width;
    float height;
};

class RSCustomModifier : public RSModifier {
public:
    RSCustomModifier() = default;
    virtual ~RSCustomModifier() = default;

    virtual void Draw(RSDrawingContext& context) const = 0;

    void SetNoNeedUICaptured(bool noNeedUICaptured)
    {
        noNeedUICaptured_ = noNeedUICaptured;
    }

    bool IsCustom() const override
    {
        return true;
    }

protected:

    virtual RSPropertyType GetInnerPropertyType() const
    {
        return RSPropertyType::CUSTOM;
    }

private:
    bool lastDrawCmdListEmpty_ = false;
    bool noNeedUICaptured_ = false;
};
} // namespace ModifierNG
} // namespace OHOS::Rosen
#endif // RENDER_SERVICE_CLIENT_CORE_MODIFIER_NG_CUSTOM_RS_CUSTOM_MODIFIER_H
