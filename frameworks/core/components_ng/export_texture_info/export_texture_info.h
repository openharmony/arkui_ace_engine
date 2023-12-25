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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EXPORT_TEXTURE_INFO_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EXPORT_TEXTURE_INFO_H

#include <optional>
#include <string>

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ExportTextureInfo : public virtual AceType {
public:
    ExportTextureInfo() = default;
    ~ExportTextureInfo() override = default;

    std::string GetSurfaceId() const
    {
        return surfaceId_.value_or("");
    }

    void SetSurfaceId(const std::string& surfaceId)
    {
        surfaceId_ = surfaceId;
    }

    NodeRenderType GetCurrentRenderType() const
    {
        return curRenderType_;
    }

    void SetCurrentRenderType(NodeRenderType renderType)
    {
        curRenderType_ = renderType;
    }

private:
    std::optional<std::string> surfaceId_;
    NodeRenderType curRenderType_ = NodeRenderType::RENDER_TYPE_DISPLAY;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EXPORT_TEXTURE_INFO_H
