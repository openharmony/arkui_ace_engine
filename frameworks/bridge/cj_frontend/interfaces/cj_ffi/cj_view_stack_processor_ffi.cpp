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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_stack_processor_ffi.h"

#include "bridge/cj_frontend/cppview/view_stack_processor.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

extern "C" {
int32_t FfiOHOSAceFrameworkAllocateNewElmetIdForNextComponent()
{
    return ElementRegister::GetInstance()->MakeUniqueId();
}

void FfiOHOSAceFrameworkStartGetAccessRecordingFor(int32_t elmtId)
{
    CJViewStackProcessor::StartGetAccessRecordingFor(elmtId);
}

int32_t FfiOHOSAceFrameworkGetElmtIdToAccountFor()
{
    return CJViewStackProcessor::GetElmtIdToAccountFor();
}

void FfiOHOSAceFrameworkStopGetAccessRecording()
{
    return CJViewStackProcessor::StopGetAccessRecording();
}

void FfiOHOSAceFrameworkImplicitPopBeforeContinue()
{
    CJViewStackProcessor::ImplicitPopBeforeContinue();
}
}
