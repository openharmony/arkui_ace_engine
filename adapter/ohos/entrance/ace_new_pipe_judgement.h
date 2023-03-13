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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_CPP_ACE_NEWPIPE_JUDJEMENT_H
#define FOUNDATION_ACE_ADAPTER_OHOS_CPP_ACE_NEWPIPE_JUDJEMENT_H

#include <set>
#include <string>

namespace OHOS::Ace {
enum class AceNewPipeEnabledType {
    ACE_NEW_PIPE_DISABLED = 0,
    ACE_NEW_PIPE_ENABLED_FOR_ALL,
    ACE_NEW_PIPE_PARTIALLY_ENABLED,
};

class AceNewPipeJudgement final {
public:
    ~AceNewPipeJudgement() = default;

    // Decide if it's a new framework
    static bool QueryAceNewPipeEnabledFA(const std::string& packagename, uint32_t apiCompatibleVersion,
        uint32_t apiTargetVersion, const std::string& apiReleaseType);
    static bool QueryAceNewPipeEnabledStage(const std::string& packagename, uint32_t apiCompatibleVersion,
        uint32_t apiTargetVersion, const std::string& apiReleaseType, bool closeArkTSPartialUpdate);
    // Load acenewpipe.config
    static void InitAceNewPipeConfig();

private:
    AceNewPipeJudgement() = default;

    // Dealing with Windows type end of line "\r"
    static std::ifstream& SafeGetLine(std::ifstream& configFile, std::string& line);
    static void InitAceNewPipeWithConfigFile();

    static inline AceNewPipeEnabledType aceNewPipeEnabledType_ = AceNewPipeEnabledType::ACE_NEW_PIPE_DISABLED;
    static inline std::set<std::string> aceNewPipeEnabledList_ {};
    static inline bool InitedAceNewPipeConfig_ = false;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_ADAPTER_OHOS_CPP_ACE_NEWPIPE_JUDJEMENT_H
