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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_DATA_HANDLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_DATA_HANDLER_H

#include "wm/data_handler_interface.h"

namespace OHOS {
namespace Rosen {
class MockDataHandler : public IDataHandler {
    DataHandlerErr SendDataSync(
        SubSystemId subSystemId, uint32_t customId, const AAFwk::Want& toSend, AAFwk::Want& reply) override
    {
        return DataHandlerErr::OK;
    }

    DataHandlerErr SendDataSync(SubSystemId subSystemId, uint32_t customId, const AAFwk::Want& toSend) override
    {
        return DataHandlerErr::OK;
    }

    DataHandlerErr SendDataAsync(SubSystemId subSystemId, uint32_t customId, const AAFwk::Want& toSend) override
    {
        return DataHandlerErr::OK;
    }

    DataHandlerErr RegisterDataConsumer(SubSystemId subSystemId, DataConsumeCallback&& callback) override
    {
        return DataHandlerErr::OK;
    }

    void UnregisterDataConsumer(SubSystemId subSystemId) override {}
};
} // namespace Rosen
} // namespace OHOS
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_DATA_HANDLER_H