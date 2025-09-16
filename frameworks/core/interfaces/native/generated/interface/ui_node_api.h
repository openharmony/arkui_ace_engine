/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef GENERATED_FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NODE_API_H
#define GENERATED_FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NODE_API_H

#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
    const GENERATED_ArkUINodeModifiers* GENERATED_GetArkUINodeModifiers();
    const GENERATED_ArkUIFullNodeAPI* GENERATED_GetFullAPI();

    inline const struct GENERATED_ArkUINodeModifiers* GetGeneratedNodeModifiers()
    {
        return GENERATED_GetArkUINodeModifiers();
    }

    inline const struct GENERATED_ArkUIFullNodeAPI* GetFullAPI()
    {
        return GENERATED_GetFullAPI();
    }
}

#endif // GENERATED_FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NODE_API_H
