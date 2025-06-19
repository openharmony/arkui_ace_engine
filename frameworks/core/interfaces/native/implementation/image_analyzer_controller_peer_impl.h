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
#include "arkoala_api_generated.h"
#include "interfaces/inner_api/ace/ai/image_analyzer.h"

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/common/container_consts.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

struct ImageAnalyzerControllerPeer : public OHOS::Ace::Referenced {
public:
    ImageAnalyzerControllerPeer() = default;
    ~ImageAnalyzerControllerPeer() override = default;

    std::vector<OHOS::Ace::ImageAnalyzerType> GetImageAnalyzerSupportTypes()
    {
        LOGE("ARKOALA ImageAnalyzerControllerPeer::TriggerGetImageAnalyzerSupportTypes ImageAnalayzerController"
            " and ImageAIOptions are not implemented in Ace_Engine.");
        return std::vector<OHOS::Ace::ImageAnalyzerType>(0);
    }
};
#endif //FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_IMAGE_ANALYZER_CONTROLLER_PEER_IMPL_H
