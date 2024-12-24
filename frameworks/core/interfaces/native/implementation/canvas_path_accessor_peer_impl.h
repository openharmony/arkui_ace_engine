/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_CANVAS_PATH_ACCESSOR_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_CANVAS_PATH_ACCESSOR_PEER_IMPL_H

#include "base/utils/utils.h"
#include "core/common/container_consts.h"
#include "core/components_ng/pattern/waterflow/water_flow_sections.h"
#include "core/components_ng/pattern/canvas/canvas_pattern.h"

namespace OHOS::Ace::NG::GeneratedModifier {
class CanvasPathPeerImpl : public Referenced {
public:
    CanvasPathPeerImpl() = default;
    ~CanvasPathPeerImpl() override = default;

public:
    RefPtr<CanvasPattern> path;
};
} // namespace OHOS::Ace::NG::GeneratedModifier
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_CANVAS_PATH_ACCESSOR_PEER_IMPL_H