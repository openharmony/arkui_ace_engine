/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PROGRESS_LOADING_PROGRESS_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PROGRESS_LOADING_PROGRESS_MODEL_H

#include <mutex>

#include "core/common/resource/resource_object.h"
#include "core/components/common/properties/color.h"

namespace OHOS::Ace {
enum class LoadingProgressResourceType {
    COLOR,
    FOREGROUNDCOLOR,
};
class ACE_FORCE_EXPORT LoadingProgressModel {
public:
    static LoadingProgressModel* GetInstance();
    virtual ~ LoadingProgressModel() = default;

    virtual void Create() = 0;
    virtual void SetColor(const Color& value) = 0;
    virtual void SetEnableLoading(bool enable) = 0;
    virtual void ResetColor() = 0;
    virtual void SetForegroundColorParseFailed(bool isParseFailed) {};
    virtual void CreateWithResourceObj(LoadingProgressResourceType LoadingProgressResourceType, const RefPtr<ResourceObject>& resObj) = 0;

private:
    static std::unique_ptr<LoadingProgressModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PROGRESS_LOADING_PROGRESS_MODEL_H
