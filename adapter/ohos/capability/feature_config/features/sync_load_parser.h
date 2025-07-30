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

#ifndef FRAME_BASED_CREATOR_PARSER_H
#define FRAME_BASED_CREATOR_PARSER_H

#include "adapter/ohos/capability/feature_config/config_xml_parser_base.h"

namespace OHOS::Ace {
class SyncloadParser : public ConfigXMLParserBase {
public:
    SyncloadParser() = default;
    ~SyncloadParser() = default;

    ParseErrCode ParseFeatureParam(xmlNode &node) override;

    static bool IsSyncloadEnable();
    static uint32_t GetSyncloadResponseDeadline();
private:
    // 0-999 is valid
    bool IsValidDigits(const std::string &str);

    static constexpr uint32_t MAX_TIMER_SIZE = 3; // 3 is max size for responseDeadline
    static constexpr uint32_t MS_TO_NS = 1000000; // 1000000 change time form ms to ns

    static bool enabled_;
    static uint32_t responseDeadline_;
};
}  // namespace OHOS::Ace::NG

#endif  // FRAME_BASED_CREATOR_PARSER_H