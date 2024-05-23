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
#include "frameworks/bridge/declarative_frontend/jsview/js_state_mgmt_profiler.h"
#include "base/log/dump_log.h"
#include "base/utils/utils.h"

namespace OHOS::Ace::Framework {
JSStateMgmtProfiler::JSStateMgmtProfiler(std::string profilerPackage) : profilerPackage_(std::move(profilerPackage))
{
}

void JSStateMgmtProfiler::JSBind(BindingTarget globalObj)
{
    JSClass<JSStateMgmtProfiler>::Declare("StateMgmtProfiler");
    JSClass<JSStateMgmtProfiler>::Method("begin", &JSStateMgmtProfiler::Begin);
    JSClass<JSStateMgmtProfiler>::Method("end", &JSStateMgmtProfiler::End);
    JSClass<JSStateMgmtProfiler>::Method("report", &JSStateMgmtProfiler::Report);
    JSClass<JSStateMgmtProfiler>::Method("clear", &JSStateMgmtProfiler::Clear);
    JSClass<JSStateMgmtProfiler>::Bind(globalObj, JSStateMgmtProfiler::ConstructorCallback);
}

void JSStateMgmtProfiler::ConstructorCallback(const JSCallbackInfo& info)
{
    if (info[0]->IsString()) {
        auto instance = new JSStateMgmtProfiler(info[0]->ToString());
        info.SetReturnValue(instance);
    } else {
        LOGE("JSStateMgmtProfiler invalid arguments! Expected a string");
    }
}

void JSStateMgmtProfiler::Begin(const std::string& blockName)
{
    auto then = GetNanoseconds();
    std::shared_ptr<ProfileBlock> block = nullptr;
    if (currentBlocks_.empty()) {
        for (const auto& rootBlock : rootBlocks_) {
            if (blockName == rootBlock->Name()) {
                block = rootBlock;
                break;
            }
        }
        if (!block) {
            block = std::make_shared<ProfileBlock>(blockName);
            rootBlocks_.push_back(block);
        }
    } else {
        block = currentBlocks_.top()->GetOrCreateChild(blockName);
    }

    currentBlocks_.push(block);
    block->IncreaseCalls();
    block->SetOwnLookupTime(GetNanoseconds() - then);
    block->SetStartTime(GetNanoseconds());
}

void JSStateMgmtProfiler::End()
{
    auto now = GetNanoseconds();
    auto then = currentBlocks_.top();
    then->SetTotalTime(then->TotalTime() + (now - then->StartTime()));
    currentBlocks_.pop();
    if (!currentBlocks_.empty()) {
        auto parent = currentBlocks_.top();
        parent->SetOwnLookupTime(parent->OwnLookupTime() + then->OwnLookupTime());
    }
}

void JSStateMgmtProfiler::Report()
{
    if (rootBlocks_.empty()) {
        DumpLog::GetInstance().Print(0, "StateMgmtProfiler: nothing to report.");
        return;
    }
    const int nameWidth = 70;
    const int itemWidth = 14;

    DumpLog::GetInstance().Reset();
    std::unique_ptr<std::ostringstream> stdOut = std::make_unique<std::ostringstream>();
    DumpLog::GetInstance().SetDumpFile(std::move(stdOut));
    std::ostringstream ss;
    ss << std::left << "Block name" << std::setw(nameWidth) << std::right << "#Calls" << std::setw(itemWidth) << "Self"
       << std::setw(itemWidth) << "Total";
    std::string out = ss.str();
    std::string dashes(out.size(), '=');
    DumpLog::GetInstance().Print(0, dashes);
    DumpLog::GetInstance().Print(0, out);
    DumpLog::GetInstance().Print(0, dashes);
    DumpLog::GetInstance().Print(0, profilerPackage_);
    for (const auto& blocks : rootBlocks_) {
        blocks->Report(1);
    }
    DumpLog::GetInstance().Print(0, dashes);

    Clear();
}

void JSStateMgmtProfiler::ProfileBlock::Report(int32_t depth) const
{
    std::ostringstream ss;
    uint64_t childrenTime = 0ULL;
    for (const auto& childrenBlocks : childrenBlocks_) {
        childrenTime += childrenBlocks->TotalTime();
    }
    const int nameAdjustWidth = 80;
    const int itemAdjustWidth = 12;
    const int itemPrecision = 3;
    const int nanoSecsInMilliSec = 1000000;
    
    ss << std::left << std::string(depth, ' ');
    ss << name_;
    ss << std::setw(nameAdjustWidth - static_cast<int32_t>(name_.size()) - depth);
    ss << std::right << numberOfCalls_;
    ss << std::setw(itemAdjustWidth);
    ss << std::fixed << std::setprecision(itemPrecision)
       << (static_cast<double>(totalTime_ - childrenTime - ownLookupTime_) / nanoSecsInMilliSec) << "ms";
    ss << std::setw(itemAdjustWidth);
    ss << (static_cast<double>(totalTime_ - ownLookupTime_) / nanoSecsInMilliSec) << "ms";

    DumpLog::GetInstance().Print(0, ss.str());
    for (const auto& childrenBlocks : childrenBlocks_) {
        childrenBlocks->Report(depth + 1);
    }
}

void JSStateMgmtProfiler::Clear()
{
    rootBlocks_.clear();
    std::stack<std::shared_ptr<ProfileBlock>> empty;
    currentBlocks_.swap(empty);
}
} // namespace OHOS::Ace::Framework