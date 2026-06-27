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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_RESOURCE_REOURCE_PARSE_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_RESOURCE_REOURCE_PARSE_UTILS_H

#include <functional>
#include <map>
#include <string>

#include "ui/resource/resource_parse_utils.h"
#include "core/common/resource/resource_manager.h"
#include "core/common/resource/resource_wrapper.h"
#include "core/components/theme/resource_adapter.h"

namespace OHOS::Ace {
namespace NG {
class UINode;
} // namespace NG

enum class ResourceType : uint32_t {
    COLOR = 10001,
    FLOAT,
    STRING,
    PLURAL,
    BOOLEAN,
    INTARRAY,
    INTEGER,
    PATTERN,
    STRARRAY,
    MEDIA = 20000,
    RAWFILE = 30000,
    SYMBOL = 40000
};

class ACE_FORCE_EXPORT ResourceParseUtils final : public ResourceParseUtilsBase {
    DECLARE_ACE_TYPE(ResourceParseUtils, ResourceParseUtilsBase);

public:
    using ResourceParseUtilsBase::ParseResInteger;

    static RefPtr<ThemeConstants> GetThemeConstants(const RefPtr<ResourceObject>& resObj);

    static void SetNeedReload(bool needReload)
    {
        needReload_ = needReload;
    }

    static bool NeedReload()
    {
        return needReload_;
    }

    static NG::NodeInfo MakeNativeNodeInfo(NG::UINode* uiNode);

    template<typename T>
    static bool ParseResInteger(const RefPtr<ResourceObject>& resObj, T& result)
    {
        CHECK_NULL_RETURN(resObj, false);
        auto resIdNum = resObj->GetId();
        auto type = resObj->GetType();
        auto resourceAdapter = ResourceManager::GetInstance().GetOrCreateResourceAdapter(resObj);
        RefPtr<ThemeConstants> themeConstants = nullptr;
        auto resourceWrapper = AceType::MakeRefPtr<ResourceWrapper>(themeConstants, resourceAdapter);
        if (resIdNum == -1) {
            auto param = resObj->GetParams()[0];
            if (type == static_cast<int32_t>(ResourceType::INTEGER)) {
                result = static_cast<T>(resourceWrapper->GetIntByName(param.value.value()));
                return true;
            }
            return false;
        }
        if (type == static_cast<int32_t>(ResourceType::INTEGER)) {
            result = static_cast<T>(resourceWrapper->GetInt(resIdNum));
            return true;
        }
        return false;
    }
};
}
#endif
