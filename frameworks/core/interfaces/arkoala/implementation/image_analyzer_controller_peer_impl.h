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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_IMAGE_ANALYZER_CONTROLLER_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_IMAGE_ANALYZER_CONTROLLER_PEER_IMPL_H

#include <optional>
#include "core/interfaces/native/node/node_api.h"
#include "arkoala_api_generated.h"
#include "interfaces/inner_api/ace/ai/image_analyzer.h"

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/common/container_consts.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"

struct ImageAnalyzerControllerPeer : public OHOS::Ace::Referenced {
public:
    ImageAnalyzerControllerPeer() = default;
    ~ImageAnalyzerControllerPeer() override = default;

    std::vector<OHOS::Ace::ImageAnalyzerType> TriggerGetImageAnalyzerSupportTypes()
    {
        return types_;
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
    std::vector<OHOS::Ace::ImageAnalyzerType> types_ = { OHOS::Ace::ImageAnalyzerType::SUBJECT, OHOS::Ace::ImageAnalyzerType::TEXT };
    int32_t instanceId_ = OHOS::Ace::INSTANCE_ID_UNDEFINED;
};
#endif //FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_IMAGE_ANALYZER_CONTROLLER_PEER_IMPL_H
