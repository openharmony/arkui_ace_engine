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
#ifndef CAPI_STUBS_COMPONENT_SNAPSHOT_H
#define CAPI_STUBS_COMPONENT_SNAPSHOT_H

#include "base/memory/ace_type.h"
#include "core/components_ng/render/snapshot_param.h"
#include <functional>
#include <memory>

namespace OHOS::Media {
class PixelMap {
};
}

namespace OHOS::Ace::NG {
class ComponentSnapshot {
public:
    using JsCallback = std::function<void(std::shared_ptr<Media::PixelMap>, int32_t, std::function<void()>)>;
    static void Get(const std::string& componentId, JsCallback&& callback, const SnapshotOptions& options);
};

} // namespace OHOS::Ace::NG
#endif //CAPI_STUBS_COMPONENT_SNAPSHOT_H