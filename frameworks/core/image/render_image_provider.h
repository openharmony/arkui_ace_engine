/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_RENDER_IMAGE_PROVIDER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_RENDER_IMAGE_PROVIDER_H

#include <vector>

#include "base/memory/ace_type.h"
#include "core/event/ace_event_handler.h"

namespace OHOS::Ace {

class PipelineContext;

class RenderImageProvider : public virtual AceType {
    DECLARE_ACE_TYPE(RenderImageProvider, AceType);

public:
    static void CanLoadImage(const RefPtr<PipelineContext>& context, const std::string& src,
        const std::map<std::string, EventMarker>& callbacks);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_RENDER_IMAGE_PROVIDER_H
