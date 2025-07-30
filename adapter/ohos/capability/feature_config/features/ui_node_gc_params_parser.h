/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef UI_NODE_GC_PARAMS_PARSER_H
#define UI_NODE_GC_PARAMS_PARSER_H

#include "adapter/ohos/capability/feature_config/config_xml_parser_base.h"

namespace OHOS::Ace {
  
class UINodeGcParamParser : public ConfigXMLParserBase {
public:
    UINodeGcParamParser() = default;
    ~UINodeGcParamParser() = default;

    ParseErrCode ParseFeatureParam(xmlNode &node) override;
    static bool IsUINodeGcEnable();

private:
    void SetParsedParams();

    static bool enabled_;
};
}  // namespace OHOS::Ace

#endif  // UI_NODE_GC_PARAMS_PARSER_H