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
#ifndef FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_PA_ENGINE_ENGINE_JSI_JSI_PA_SOURCE_MAP_OPERATOR_H
#define FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_PA_ENGINE_ENGINE_JSI_JSI_PA_SOURCE_MAP_OPERATOR_H

#include "js_runtime.h"
#include "source_map_operator.h"

namespace OHOS::Ace {
class JsiPaSourceMapOperatorImpl : public JsEnv::SourceMapOperatorImpl {
public:
    JsiPaSourceMapOperatorImpl(std::shared_ptr<JsRuntime> runtime) : rumtime_(runtime) {}

    ~JsiPaSourceMapOperatorImpl() = default;

    std::string TranslateBySourceMap(const std::string& rawStack) override;

private:
    std::shared_ptr<JsRuntime> runtime_ = nullptr;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_PA_ENGINE_ENGINE_JSI_JSI_PA_SOURCE_MAP_OPERATOR_H
