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

#include "base/log/dump_recorder.h"

#include <fstream>

#include "base/log/dump_log.h"
#include "core/common/ace_application_info.h"

namespace OHOS::Ace {

namespace {
constexpr uint32_t MAX_FILE_SIZE = 100000;
constexpr char REC_FILE_NAME[] = "/arkui_dump.rec";
const std::vector<std::string> SKIP_COMPARE_PARAMS = { "time", "children" };
} // namespace

DumpRecorder::DumpRecorder() = default;
DumpRecorder::~DumpRecorder() = default;

void DumpRecorder::Init()
{
    recordTree_.reset();
    recordTree_ = JsonUtil::Create(true);
    auto jsonNodeArray = JsonUtil::CreateArray(true);
    recordTree_->PutRef("infos", std::move(jsonNodeArray));
}

void DumpRecorder::Start(std::function<bool()>&& func)
{
    if (frameDumpFunc_) {
        Stop();
    }
    Init();
    frameDumpFunc_ = func;
}

void DumpRecorder::Stop()
{
    if (!frameDumpFunc_) {
        return;
    }
    CHECK_NULL_VOID(recordTree_);
    Output(recordTree_->ToString());
    frameDumpFunc_ = nullptr;
    recordTree_.reset();
}

void DumpRecorder::Record(int64_t timestamp, std::unique_ptr<JsonValue>&& json, WeakPtr<TaskExecutor> taskExecutor)
{
    records_[timestamp] = std::move(json);
    if (static_cast<int32_t>(records_.size()) > 1) {
        auto executor = taskExecutor.Upgrade();
        CHECK_NULL_VOID(executor);
        executor->PostTask([timestamp]() -> void { DumpRecorder::GetInstance().Diff(timestamp); },
            TaskExecutor::TaskType::BACKGROUND, "ArkUIDumpDiff");
    } else {
        auto info = JsonUtil::Create();
        info->Put("startTime", timestamp);
        auto& infoJson = records_.at(timestamp);
        info->Put("info", infoJson);
        auto infos = recordTree_->GetValue("infos");
        infos->PutRef(std::move(info));
    }
}

void DumpRecorder::Diff(int64_t timestamp)
{
    if (timestamp <= records_.begin()->first) {
        return;
    }
    auto iter = records_.find(timestamp);
    if (iter == records_.end()) {
        return;
    }
    auto& curNode = iter->second;
    auto& prevNode = records_.begin()->second;

    std::string diff;
    Compare(curNode, prevNode, diff);
    auto info = JsonUtil::Create();
    info->Put("startTime", timestamp);
    if (diff.empty()) {
        info->Put("info", "");
    } else {
        auto infoJson = JsonUtil::ParseJsonString(diff);
        info->PutRef("info", std::move(infoJson));
    }
    auto infos = recordTree_->GetValue("infos");
    infos->PutRef(std::move(info));
    auto output = recordTree_->ToString();
    if (sizeof(output) > MAX_FILE_SIZE) {
        Stop();
    }
    records_.erase(timestamp);
}

bool DumpRecorder::CompareDumpParam(std::unique_ptr<JsonValue>& curParams, std::unique_ptr<JsonValue>& prevParams)
{
    auto curParam = curParams->GetChild();
    while (!curParam->IsNull()) {
        auto curParamKey = curParam->GetKey();
        if (curParamKey.empty()) {
            return false;
        }
        if (std::find(SKIP_COMPARE_PARAMS.begin(), SKIP_COMPARE_PARAMS.end(), curParamKey) !=
            SKIP_COMPARE_PARAMS.end()) {
            curParam = curParam->GetNext();
            continue;
        }
        auto prevParam = prevParams->GetValue(curParamKey);
        if (prevParam->IsNull()) {
            return false;
        }
        if (curParam->ToString() != prevParam->ToString()) {
            return false;
        }
        curParam = curParam->GetNext();
    }
    return true;
}

bool DumpRecorder::Compare(std::unique_ptr<JsonValue>& curNode, std::unique_ptr<JsonValue>& prevNode, std::string& diff)
{
    CHECK_NULL_RETURN(curNode, false);
    CHECK_NULL_RETURN(prevNode, false);
    auto curNodeInfo = curNode->GetChild();
    auto prevNodeInfo = prevNode->GetChild();
    std::string curNodeName = curNodeInfo->GetKey();
    std::string prevNodeName = prevNodeInfo->GetKey();
    if (curNodeName != prevNodeName) {
        diff = curNode->ToString();
        return false;
    }
    auto curNodeChildren = curNodeInfo->GetValue("children");
    auto prevNodeChildren = prevNodeInfo->GetValue("children");
    if (curNodeChildren->GetArraySize() != prevNodeChildren->GetArraySize()) {
        diff = curNode->ToString();
        return false;
    }
    if (!CompareDumpParam(curNodeInfo, prevNodeInfo)) {
        return false;
    }
    for (int32_t i = 0; i < curNodeChildren->GetArraySize(); i++) {
        auto curChild = curNodeChildren->GetArrayItem(i);
        auto prevChild = prevNodeChildren->GetArrayItem(i);
        if (!Compare(curChild, prevChild, diff)) {
            if (diff.empty()) {
                diff = curNode->ToString().c_str();
            }
            return false;
        }
    }
    return true;
}

void DumpRecorder::Output(const std::string& content)
{
    auto dumpFilePath = AceApplicationInfo::GetInstance().GetDataFileDirPath() + REC_FILE_NAME;
    std::unique_ptr<std::ostream> ostream = std::make_unique<std::ofstream>(dumpFilePath);
    ostream->write(content.c_str(), content.length());
    ostream->flush();
}
} // namespace OHOS::Ace
