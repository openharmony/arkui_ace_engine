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

#ifndef OHOS_ACE_FORM_SURFACE_STUB_H
#define OHOS_ACE_FORM_SURFACE_STUB_H

#include "form_surface_interface.h"

#include <iremote_object.h>
#include <iremote_stub.h>
#include <map>

#include "hilog_wrapper.h"

namespace OHOS {
namespace Ace {
/**
 * @class FormSurfaceServiceStub
 * FormSurfaceServiceStub
 */
class FormSurfaceServiceStub : public IRemoteStub<IFormSurfaceService> {
public:
    FormSurfaceServiceStub() = default;
    ~FormSurfaceServiceStub() override = default;
    int32_t OnRemoteRequest(uint32_t code, MessageParcel& data, MessageParcel& reply, MessageOption& option) override;
};
} // namespace Ace
} // namespace OHOS
#endif  // OHOS_ACE_FORM_SURFACE_STUB_H
