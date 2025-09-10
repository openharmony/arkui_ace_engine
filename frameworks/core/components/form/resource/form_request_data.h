/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_FORM_RESOURCE_FORM_REQUEST_DATA_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_FORM_RESOURCE_FORM_REQUEST_DATA_H

#include <sstream>
#include <string>

#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "base/want/want_wrap.h"

namespace OHOS::Ace {

struct RequestFormInfo {
    int64_t id = 0;
    std::string cardName;
    std::string bundleName;
    std::string abilityName;
    std::string moduleName;
    RefPtr<WantWrap> wantWrap;
    bool temporary = false;
    int32_t dimension = -1;
    bool allowUpdate = true;
    Dimension width;
    Dimension height;
    int32_t renderingMode = 0;
    uint64_t index = GetNanoseconds();
    float borderWidth = 0.0f;
    float layoutWidth = 0.0f;
    float layoutHeight = 0.0f;
    bool obscuredMode = false;
    int32_t shape = -1;
    bool exemptAppLock;

    std::string ToString() const
    {
        std::stringstream paramStream;
        paramStream << bundleName << abilityName << moduleName << cardName << dimension << renderingMode
            << index << temporary << shape << layoutWidth << layoutHeight;
        if (wantWrap) {
            paramStream << wantWrap->ToString();
        }
        return paramStream.str();
    }

    bool operator==(const RequestFormInfo& formInfo) const
    {
        return id == formInfo.id && cardName == formInfo.cardName && bundleName == formInfo.bundleName &&
               abilityName == formInfo.abilityName && moduleName == formInfo.moduleName &&
               temporary == formInfo.temporary && dimension == formInfo.dimension &&
               allowUpdate == formInfo.allowUpdate && width == formInfo.width && height == formInfo.height &&
               renderingMode == formInfo.renderingMode && index == formInfo.index && wantWrap == formInfo.wantWrap &&
               shape == formInfo.shape && NearEqual(layoutWidth, formInfo.layoutWidth) &&
               NearEqual(layoutHeight, formInfo.layoutHeight);
    }
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_FORM_RESOURCE_FORM_REQUEST_DATA_H