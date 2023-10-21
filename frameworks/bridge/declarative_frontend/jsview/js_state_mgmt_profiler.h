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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_STATE_MGMT_PROFILER_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_STATE_MGMT_PROFILER_H

#include <memory>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "frameworks/bridge/declarative_frontend/engine/bindings.h"

namespace OHOS::Ace::Framework {
class JSStateMgmtProfiler : public AceType {
    DECLARE_ACE_TYPE(JSStateMgmtProfiler, AceType);

public:
    explicit JSStateMgmtProfiler(std::string profilerPackage);
    ~JSStateMgmtProfiler() = default;

    static void JSBind(BindingTarget globalObj);
    static void ConstructorCallback(const JSCallbackInfo& info);
    void Begin(const std::string& blockName);
    void End();
    void Report();
    void Clear();

private:
    class ProfileBlock {
    public:
        ProfileBlock(std::string blockName) : name_(blockName), startTime_(0ULL), totalTime_(0ULL),
            ownLookupTime_(0ULL), numberOfCalls_(0u)
        {}
        ~ProfileBlock() = default;

        std::shared_ptr<ProfileBlock> GetOrCreateChild(const std::string name)
        {
            for (const auto& child : childrenBlocks_) {
                if (child->name_ == name) {
                    return child;
                }
            }
            auto block = std::make_shared<ProfileBlock>(name);
            childrenBlocks_.push_back(block);
            return block;
        }

        void Report(int32_t depth) const;

        uint64_t StartTime() const
        {
            return startTime_;
        }
        uint64_t TotalTime() const
        {
            return totalTime_;
        }
        uint64_t OwnLookupTime() const
        {
            return ownLookupTime_;
        }
        std::string Name() const
        {
            return name_;
        }

        void SetOwnLookupTime(uint64_t lookupTime)
        {
            ownLookupTime_ = lookupTime;
        }
        void SetStartTime(uint64_t startTime)
        {
            startTime_ = startTime;
        }
        void SetTotalTime(uint64_t totalTime)
        {
            totalTime_ = totalTime;
        }
        void IncreaseCalls()
        {
            numberOfCalls_++;
        }

    private:
        std::vector<std::shared_ptr<ProfileBlock>> childrenBlocks_;
        std::string name_;
        uint64_t startTime_;
        uint64_t totalTime_;
        uint64_t ownLookupTime_;
        uint32_t numberOfCalls_;
    };
    std::vector<std::shared_ptr<ProfileBlock>> rootBlocks_;
    std::stack<std::shared_ptr<ProfileBlock>> currentBlocks_;
    std::string profilerPackage_;
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_STATE_MGMT_PROFILER_H
