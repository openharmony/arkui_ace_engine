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

#ifndef FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_VIEW_STACK_PROCESSOR_H
#define FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_VIEW_STACK_PROCESSOR_H

#include "core/components/button/button_component.h"
#include "core/components/text/text_component.h"
#include "core/event/ace_event_handler.h"

namespace OHOS::Ace::Framework {

class ACE_EXPORT CJViewStackProcessor {
public:
    static void StartGetAccessRecordingFor(int32_t elmtId);
    static int32_t GetElmtIdToAccountFor();
    static void StopGetAccessRecording();
    static void ImplicitPopBeforeContinue();
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_VIEW_STACK_PROCESSOR_H
