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

#include "jsi_pa_source_map_operator_impl.h"

#include "base/memory/ace_type.h"
#include "bridge/common/utils/source_map.h"
#include "core/common/container.h"
#include "ecmascript/napi/include/jsnapi.h"
#include "frameworks/bridge/js_frontend/engine/jsi/ark_js_runtime.h"
#include "frameworks/bridge/js_frontend/engine/jsi/jsi_base_utils.h"

namespace OHOS::Ace {
std::string JsiPaSourceMapOperatorImpl::TranslateBySourceMap(const std::string& rawStack)
{
    const AceType* data = static_cast<AceType*>(runtime_->GetEmbedderData());
    std::string pageUrl;
    RefPtr<RevSourceMap> pageMap;
    RefPtr<RevSourceMap> appMap;
    std::unordered_map<std::string, RefPtr<RevSourceMap>> sourceMaps;
    auto vm = const_cast<EcmaVM*>(std::static_pointer_cast<ArkJSRuntime>(runtime_)->GetEcmaVm());
    auto container = Container::Current();
    if (container && container->IsUseNewPipeline()) {
        auto frontEnd = container->GetFrontend();
        if (frontEnd) {
            pageUrl = frontEnd->GetCurrentPageUrl();
            if (!JSNApi::IsBundle(vm)) {
                frontEnd->GetStageSourceMap(sourceMaps);
            } else {
                pageMap = frontEnd->GetCurrentPageSourceMap();
            }
            appMap = frontEnd->GetFaAppSourceMap();
        }
    } else {
        auto runningPage = GetRunningPage(data);
        if (runningPage) {
            pageUrl = runningPage->GetUrl();
            appMap = runningPage->GetAppMap();
            if (!JSNApi::IsBundle(vm)) {
                JsiBaseUtils::GetStageSourceMap(data, sourceMaps);
            } else {
                pageMap = runningPage->GetPageMap();
            }
        }
    }

    std::string showStack;
    if (pageMap || appMap || !sourceMaps.empty()) {
        if (!JSNApi::IsBundle(vm)) {
            showStack = JsiBaseUtils::TranslateBySourceMap(rawStack, pageUrl, sourceMaps, appMap, data);
        } else {
            showStack = JsiBaseUtils::TranslateStack(rawStack, pageUrl, pageMap, appMap, data);
        }
    }

    if (showStack.empty()) {
        showStack.append("Cannot get SourceMap info, dump raw stack:\n");
        showStack.append(rawStack);
    }

#if defined(WINDOWS_PLATFORM) || defined(MAC_PLATFORM)
        std::string showStackInsertedWithTagStr = "";
        std::size_t lastPosOfNextLine = -1;
        std::size_t currPosOfNextLine = 0;
        while (true) {
            lastPosOfNextLine++; // Become the next position at which we start to find the target charactor.
            currPosOfNextLine = showStack.find_first_of("\n", lastPosOfNextLine);
            if (currPosOfNextLine == std::string::npos) {
                break;
            }
            showStackInsertedWithTagStr.append("[Engine Log]")
                .append(showStack.substr(lastPosOfNextLine, (currPosOfNextLine - lastPosOfNextLine) + 1));
            lastPosOfNextLine = currPosOfNextLine;
        }
        return showStackInsertedWithTagStr;
#endif
    return showStack;
}
} // namespace OHOS::Ace
