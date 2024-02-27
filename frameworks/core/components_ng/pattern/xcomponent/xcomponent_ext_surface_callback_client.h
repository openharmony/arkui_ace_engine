/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_XCOMPONENT_XCOMPONENT_EXT_SURFACE_CALLBACK_CLIENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_XCOMPONENT_XCOMPONENT_EXT_SURFACE_CALLBACK_CLIENT_H

#include "base/memory/referenced.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern.h"
#include "core/components_ng/render/ext_surface_callback_interface.h"

namespace OHOS::Ace::NG {
class XComponentExtSurfaceCallbackClient : public ExtSurfaceCallbackInterface {
public:
    explicit XComponentExtSurfaceCallbackClient(const WeakPtr<XComponentPattern>& pattern)
        : weakXComponentPattern_(pattern)
    {}
    ~XComponentExtSurfaceCallbackClient() override = default;

    void ProcessSurfaceCreate() override;

    void ProcessSurfaceChange(int32_t width, int32_t height) override;

    void ProcessSurfaceDestroy() override;

private:
    WeakPtr<XComponentPattern> weakXComponentPattern_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_XCOMPONENT_XCOMPONENT_EXT_SURFACE_CALLBACK_CLIENT_H
