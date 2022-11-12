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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_ADAPTER_FLUTTER_IMAGE_PROVIDER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_ADAPTER_FLUTTER_IMAGE_PROVIDER_H

#include "flutter/flow/skia_gpu_object.h"
#include "flutter/lib/ui/io_manager.h"

#include "core/components_ng/image_provider/image_provider.h"

namespace OHOS::Ace::NG {

struct FlutterRenderTaskHolder : public RenderTaskHolder {
    DECLARE_ACE_TYPE(FlutterRenderTaskHolder, RenderTaskHolder);

public:
    FlutterRenderTaskHolder(fml::RefPtr<flutter::SkiaUnrefQueue> queue, fml::WeakPtr<flutter::IOManager> manager,
        fml::RefPtr<fml::TaskRunner> taskRunner)
        : unrefQueue(queue), ioManager(manager), ioTaskRunner(taskRunner)
    {}
    ~FlutterRenderTaskHolder() override = default;

    fml::RefPtr<flutter::SkiaUnrefQueue> unrefQueue;
    // weak reference of io manager must be check and used on io thread, because io manager is created on io thread.
    fml::WeakPtr<flutter::IOManager> ioManager;
    fml::RefPtr<fml::TaskRunner> ioTaskRunner;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_ADAPTER_FLUTTER_IMAGE_PROVIDER_H