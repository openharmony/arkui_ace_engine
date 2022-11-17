/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "manifest_fuzzer.h"

#include "frameworks/bridge/common/manifest/manifest_appinfo.h"
#include "frameworks/bridge/common/manifest/manifest_parser.h"
#include "frameworks/bridge/common/manifest/manifest_router.h"
#include "frameworks/bridge/common/manifest/manifest_widget.h"
#include "frameworks/bridge/common/manifest/manifest_window.h"

namespace OHOS {
    constexpr uint32_t u16m = 65535;
    bool DoSomethingInterestingWithMyAPI(const uint8_t* data, size_t size)
    {
        std::string s(reinterpret_cast<const char*>(data), size % u16m);
        OHOS::Ace::Framework::ManifestRouter manifestRouter;
        manifestRouter.GetPagePath(s);
        OHOS::Ace::Framework::ManifestWidget widget(s, "");
        OHOS::Ace::Framework::ManifestWidgetGroup mg;
        mg.WidgetParse(nullptr);
        OHOS::Ace::Framework::ManifestWindow win;
        win.PrintInfo();
        win.WindowParse(nullptr);
        OHOS::Ace::Framework::ManifestAppInfo mi;
        mi.AppInfoParse(nullptr);
        mi.ParseI18nJsonInfo();
        OHOS::Ace::Framework::ManifestParser mp;
        mp.Parse(s);
        return true;
    }
}

/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    /* Run your code on data */
    OHOS::DoSomethingInterestingWithMyAPI(data, size);
    return 0;
}

