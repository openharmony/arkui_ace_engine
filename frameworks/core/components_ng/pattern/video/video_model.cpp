/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include <cstdlib>

#include "base/log/log_wrapper.h"
#include "core/common/container.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/pattern/video/video_model.h"
#include "core/components_ng/pattern/video/video_model_ng.h"

namespace OHOS::Ace {
VideoModel* VideoModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::VideoModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::VideoModelNG instance;
        return &instance;
    }
    static auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("video");
    if (loader == nullptr) {
        LOGF_ABORT("Cannot find video loader");
    }
    static VideoModel* instance = loader ? reinterpret_cast<VideoModel*>(loader->CreateModel()) : nullptr;
    return instance;
#endif
}
} // namespace OHOS::Ace
