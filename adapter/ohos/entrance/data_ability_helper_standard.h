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

#ifndef FOUNDATION_ACE_ACE_ENGINE_ADAPTER_OHOS_CPP_DATA_ABILITY_HELPER_STANDARD_H
#define FOUNDATION_ACE_ACE_ENGINE_ADAPTER_OHOS_CPP_DATA_ABILITY_HELPER_STANDARD_H

#include "base/resource/data_ability_helper.h"

#include "pixel_map.h"

namespace OHOS::AppExecFwk {
    class DataAbilityHelper;
    class Context;
}

namespace OHOS::AbilityRuntime {
    class Context;
}

namespace OHOS::DataShare {
    class DataShareHelper;
}

namespace OHOS {
    class Uri;
}

namespace OHOS::Ace {

using DataAbilityThumbnailQueryImpl = std::function<std::unique_ptr<Media::PixelMap>(const std::string&)>;
class DataAbilityHelperStandard : public DataAbilityHelper {
    DECLARE_ACE_TYPE(DataAbilityHelperStandard, DataAbilityHelper)

public:
    DataAbilityHelperStandard(const std::shared_ptr<OHOS::AppExecFwk::Context>& context,
        const std::shared_ptr<OHOS::AbilityRuntime::Context>& runtimeContext, bool useStageModel);
    ~DataAbilityHelperStandard() override = default;

    int32_t OpenFile(const std::string& uriStr, const std::string& mode) override;
    void* QueryThumbnailResFromDataAbility(const std::string& uri) override;

private:
    int32_t OpenFileWithDataAbility(const std::string& uriStr, const std::string& mode);
    int32_t OpenFileWithDataShare(const std::string& uriStr, const std::string& mode);

    bool useStageModel_ = false;
    std::shared_ptr<DataShare::DataShareHelper> dataShareHelper_;
    std::shared_ptr<AppExecFwk::DataAbilityHelper> dataAbilityHelper_;
    std::weak_ptr<OHOS::AbilityRuntime::Context> runtimeContext_;
    std::weak_ptr<OHOS::AppExecFwk::Context> context_;
    std::shared_ptr<OHOS::Uri> uri_;
    DataAbilityThumbnailQueryImpl dataAbilityThumbnailQueryImpl_;
    std::unique_ptr<Media::PixelMap> pixmap_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ACE_ENGINE_ADAPTER_OHOS_CPP_DATA_ABILITY_HELPER_STANDARD_H
