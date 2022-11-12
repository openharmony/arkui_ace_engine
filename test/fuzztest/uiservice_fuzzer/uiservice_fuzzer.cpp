/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "uiservice_fuzzer.h"

#include "ui_service_mgr_client.h"
#include "want.h"

namespace OHOS {
constexpr size_t MAXBYTELEN = 65535;

    bool RegisterCallBackTest(const uint8_t* data, const size_t size)
    {
        OHOS::AAFwk::Want want;
        OHOS::Ace::UIServiceMgrClient client;
        sptr<Ace::IUIService> uiService = nullptr;
        std::string randomString(reinterpret_cast<const char*>(data), size);
        int randomNumber = static_cast<int>(size % MAXBYTELEN);
        DialogCallback callback;
        int* id = nullptr;
        client.RegisterCallBack(want, uiService);
        client.ShowDialog(
            randomString, randomString, OHOS::Rosen::WindowType::WINDOW_TYPE_SYSTEM_ALARM_WINDOW,
            randomNumber, randomNumber, randomNumber, randomNumber, callback, id);
        client.UpdateDialog(randomNumber, randomString);
        return  client.CancelDialog(randomNumber) == ERR_OK;
    }

    bool UnregisterCallBackTest(const uint8_t* data, const size_t size)
    {
        OHOS::AAFwk::Want want;
        OHOS::Ace::UIServiceMgrClient client;
        return client.UnregisterCallBack(want) == ERR_OK;
    }

    bool PushTest(const uint8_t* data, const size_t size)
    {
        OHOS::AAFwk::Want want;
        std::string randomString(reinterpret_cast<const char*>(data), size);
        OHOS::Ace::UIServiceMgrClient client;
        return client.Push(want, randomString, randomString, randomString, randomString) == ERR_OK;
    }

    bool RequestTest(const uint8_t* data, const size_t size)
    {
        OHOS::AAFwk::Want want;
        std::string randomString(reinterpret_cast<const char*>(data), size);
        OHOS::Ace::UIServiceMgrClient client;
        return client.Request(want, randomString, randomString) == ERR_OK;
    }

    bool ReturnRequestTest(const uint8_t* data, const size_t size)
    {
        OHOS::AAFwk::Want want;
        std::string randomString(reinterpret_cast<const char*>(data), size);
        OHOS::Ace::UIServiceMgrClient client;
        return client.ReturnRequest(want, randomString, randomString, randomString) == ERR_OK;
    }
}

/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    /* Run your code on data */
    OHOS::RegisterCallBackTest(data, size);
    OHOS::PushTest(data, size);
    OHOS::RequestTest(data, size);
    OHOS::ReturnRequestTest(data, size);
    OHOS::UnregisterCallBackTest(data, size);
    return 0;
}

