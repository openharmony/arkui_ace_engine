    /*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#pragma once

#ifndef GENERATED_FOUNDATION_ACE_FRAMEWORKS_CORE_UTILITY_UTILS_H
#define GENERATED_FOUNDATION_ACE_FRAMEWORKS_CORE_UTILITY_UTILS_H

#include "core/image/image_source_info.h"
#include "arkoala_api_generated.h"
#include "core/components_ng/base/frame_node.h"
#include "core/common/card_scope.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/common/card_scope.h"
#include "core/common/container.h"

namespace OHOS::Ace::NG::Utils
{
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
        RAWFILE = 30000
    };

    struct ImageResource {
        uint32_t type;
        std::string bundleName;
        std::string moduleName;
        int32_t id;
        std::vector<std::string> params;
    };

    std::string ResourceToString(FrameNode* node, const Ark_Resource& resource);

    ImageSourceInfo Convert(FrameNode* node, const Type_ImageInterface__setImageOptions_Arg0& value);
    ImageSourceInfo Convert(FrameNode* node, const Type_ImageAttribute_alt_Arg0& value);

    ImageResource Convert(const Ark_Resource& value);

}


#endif  // GENERATED_FOUNDATION_ACE_FRAMEWORKS_CORE_UTILITY_UTILS_H