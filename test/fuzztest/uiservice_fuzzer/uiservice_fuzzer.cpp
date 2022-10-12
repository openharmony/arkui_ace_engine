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
    bool RegisterCallBackTest(const AAFwk::Want& want)
    {
        OHOS::Ace::UIServiceMgrClient client;
        sptr<Ace::IUIService> uiService = nullptr;
        return client.RegisterCallBack(want, uiService) == ERR_OK;
    }

    bool UnregisterCallBackTest(const uint8_t* data, const AAFwk::Want& want)
    {
        OHOS::Ace::UIServiceMgrClient client;
        return client.UnregisterCallBack(want) == ERR_OK;
    }

    bool PushTest(const uint8_t* data, const AAFwk::Want& want)
    {
        std::string randomString = reinterpret_cast<const char*>(data);
        OHOS::Ace::UIServiceMgrClient client;
        return client.Push(want, randomString, randomString, randomString, randomString) == ERR_OK;
    }

    bool RequestTest(const uint8_t* data, const AAFwk::Want& want)
    {
        std::string randomString = reinterpret_cast<const char*>(data);
        OHOS::Ace::UIServiceMgrClient client;
        return client.Request(want, randomString, randomString) == ERR_OK;
    }

    bool ReturnRequestTest(const uint8_t* data, const AAFwk::Want& want)
    {
        std::string randomString = reinterpret_cast<const char*>(data);
        OHOS::Ace::UIServiceMgrClient client;
        return client.ReturnRequest(want, randomString, randomString, randomString) == ERR_OK;
    }
}

/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    /* Run your code on data */
    OHOS::AAFwk::Want want;
    std::string randomString = reinterpret_cast<const char*>(data);
    want = want.SetUri(randomString);
    OHOS::RegisterCallBackTest(want);
    OHOS::PushTest(data, want);
    OHOS::RequestTest(data, want);
    OHOS::ReturnRequestTest(data, want);
    OHOS::UnregisterCallBackTest(data, want);
    return 0;
}

