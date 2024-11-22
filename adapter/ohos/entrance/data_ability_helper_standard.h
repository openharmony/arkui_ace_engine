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

#ifdef MEDIA_LIBRARY_EXISTS
#include "media_library_manager.h"
#endif

#include "pixel_map.h"
#include "datashare_result_set.h"

namespace OHOS::AppExecFwk {
class DataAbilityHelper;
class Context;
} // namespace OHOS::AppExecFwk

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

class ACE_FORCE_EXPORT DataAbilityHelperStandard : public DataAbilityHelper {
    DECLARE_ACE_TYPE(DataAbilityHelperStandard, DataAbilityHelper)

public:
    DataAbilityHelperStandard(const std::shared_ptr<OHOS::AppExecFwk::Context>& context,
        const std::shared_ptr<OHOS::AbilityRuntime::Context>& runtimeContext, bool useStageModel);
    ~DataAbilityHelperStandard() override = default;

    int32_t OpenFile(const std::string& uriStr, const std::string& mode) override;
    void* QueryThumbnailResFromDataAbility(const std::string& uri) override;
    int32_t ReadMovingPhotoVideo(const std::string &uri) override;
    std::string GetMovingPhotoImageUri(const std::string& uri) override;
    int64_t GetMovingPhotoDateModified(const std::string& uri) override;
    int64_t GetMovingPhotoCoverPosition(const std::string& columnName, const std::string& value,
        std::vector<std::string>& columns) override;
    std::string GetMovingPhotoImagePath(const std::string& uri) override;

private:
    int32_t OpenFileWithDataAbility(const std::string& uriStr, const std::string& mode);
    int32_t OpenFileWithDataShare(const std::string& uriStr, const std::string& mode);

    bool useStageModel_ = false;
    std::shared_ptr<DataShare::DataShareHelper> dataShareHelper_;
    std::shared_ptr<AppExecFwk::DataAbilityHelper> dataAbilityHelper_;
    std::weak_ptr<OHOS::AbilityRuntime::Context> runtimeContext_;
    std::weak_ptr<OHOS::AppExecFwk::Context> context_;
#ifdef MEDIA_LIBRARY_EXISTS
    OHOS::Media::MediaLibraryManager mgr_;
#endif
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ACE_ENGINE_ADAPTER_OHOS_CPP_DATA_ABILITY_HELPER_STANDARD_H
