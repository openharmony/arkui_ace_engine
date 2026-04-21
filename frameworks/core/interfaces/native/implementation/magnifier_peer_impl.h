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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_MAGNIFIER_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_MAGNIFIER_PEER_IMPL_H

#include "arkoala_api_generated.h"
#include "base/memory/ace_type.h"
#include "core/components/common/properties/paint_state.h"
#include "core/components_ng/pattern/select_overlay/magnifier_controller.h"
#include "core/interfaces/native/utility/peer_utils.h"
#include "core/pipeline/pipeline_base.h"

struct arkui_component_idlize_MagnifierPeer : public OHOS::Ace::Referenced {
protected:
    arkui_component_idlize_MagnifierPeer() = default;
    ~arkui_component_idlize_MagnifierPeer() override = default;
    friend OHOS::Ace::NG::PeerUtils;
public:
    void Bind(const std::string& id);
    void Show(const std::optional<float>& x, const std::optional<float>& y);
    void Unbind();
};
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_MAGNIFIER_PEER_IMPL_H