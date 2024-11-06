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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_CANVAS_RENDERER_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_CANVAS_RENDERER_PEER_IMPL_H

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/common/container_consts.h"
#include "core/components_ng/pattern/canvas/canvas_pattern.h"

#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {

class CanvasRendererPeerImpl : public Referenced {
public:
    CanvasRendererPeerImpl() = default;
    ~CanvasRendererPeerImpl() override = default;

    void TriggerBeginPathImpl();
    void TriggerStroke0Impl();
    void TriggerRestoreImpl();
    void TriggerSaveImpl();
    void TriggerResetTransformImpl();
    void TriggerSaveLayerImpl();
    void TriggerRestoreLayerImpl();
    void TriggerResetImpl();

    void SetCanvasPattern(const RefPtr<AceType>& pattern)
    {
        CHECK_NULL_VOID(pattern);
        auto canvasPattern = AceType::DynamicCast<CanvasPattern>(pattern);
        CHECK_NULL_VOID(canvasPattern);
        if (pattern_ == canvasPattern) {
            return;
        }
        pattern_ = canvasPattern;
    }

    void SetInstanceId(int32_t instanceId)
    {
        instanceId_ = instanceId;
    }

    int32_t GetInstanceId()
    {
        return instanceId_;
    }

private:
    RefPtr<CanvasPattern> pattern_;
    int32_t instanceId_ = INSTANCE_ID_UNDEFINED;

};

} // namespace OHOS::Ace::NG::GeneratedModifier
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_SCROLLER_PEER_IMPL_H
