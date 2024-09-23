/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "base/log/dump_log.h"

#include <fstream>
#include "core/common/ace_application_info.h"

namespace OHOS::Ace {

DumpLog::DumpLog() = default;
DumpLog::~DumpLog() = default;

void DumpLog::Print(int32_t depth, const std::string& className, int32_t childSize)
{
    if (!ostream_->good()) {
        return;
    }
    std::string space = "  ";
    for (int32_t i = 0; i < depth; ++i) {
        ostream_->write(space.c_str(), space.length());
    }
    ostream_->write(space.c_str(), space.length());
    std::string data = "|-> ";
    data.append(className);
    data.append(" childSize:" + std::to_string(childSize));
    data.append("\n");
    ostream_->write(data.c_str(), data.length());
    for (auto& desc : description_) {
        for (int32_t i = 0; i < depth; ++i) {
            ostream_->write(space.c_str(), space.length());
        }
        std::string data = "";
        if (childSize == 0) {
            data = "      ";
        } else {
            data = "    | ";
        }
        data.append(desc);
        ostream_->write(data.c_str(), data.length());
    }
    ostream_->flush();
    description_.clear();
    description_.shrink_to_fit();
}

void DumpLog::Print(const std::string& content)
{
    Print(0, content);
}

void DumpLog::Print(int32_t depth, const std::string& content)
{
    std::string space = " ";
    for (int32_t i = 0; i < depth; ++i) {
        ostream_->write(space.c_str(), space.length());
    }
    std::string data = content + "\n";
    ostream_->write(data.c_str(), data.length());
}

void DumpLog::Reset()
{
    ostream_.reset();
}

void DumpLog::ShowDumpHelp(std::vector<std::string>& info)
{
    info.emplace_back(" -element                       |show element tree");
    info.emplace_back(" -render                        |show render tree");
    info.emplace_back(" -inspector                     |show inspector tree");
    info.emplace_back(" -frontend                      |show path and components count of current page");
    info.emplace_back(" -navigation                    |show navigation path stack");
}

void DumpLog::Append(int32_t depth, const std::string& className, int32_t childSize)
{
    for (int32_t i = 0; i < depth; ++i) {
        result_.append("  ");
    }
    result_.append("|-> ");
    result_.append(className);
    result_.append(" childSize:" + std::to_string(childSize));
    result_.append("\n");
    for (auto& desc : description_) {
        for (int32_t i = 0; i < depth; ++i) {
            result_.append("  ");
        }
        if (childSize == 0) {
            result_.append("      ");
        } else {
            result_.append("    | ");
        }
        result_.append(desc);
    }
    description_.clear();
    description_.shrink_to_fit();
}

bool DumpLog::OutPutBySize()
{
    if (!ostream_->good()) {
        result_.clear();
        return false;
    }
    // if current result size > max size, dump will output as file
    if (result_.size() + 1 > DumpLog::MAX_DUMP_LENGTH) {
        auto dumpFilePath = AceApplicationInfo::GetInstance().GetDataFileDirPath() + "/arkui.dump";
        std::unique_ptr<std::ostream> ostream = std::make_unique<std::ofstream>(dumpFilePath);
        if (!ostream) {
            result_.clear();
            result_.append("Dump output failed,please try again");
            ostream_->write(result_.c_str(), result_.length());
            result_.clear();
        }
        CHECK_NULL_RETURN(ostream, false);
        DumpLog::GetInstance().SetDumpFile(std::move(ostream));
    }
    ostream_->write(result_.c_str(), result_.length());
    result_.clear();
    ostream_->flush();
    return true;
}

void DumpLog::OutPutDefault()
{
    if (!ostream_ || !ostream_->good()) {
        result_.clear();
        return;
    }
    ostream_->write(result_.c_str(), result_.length());
    result_.clear();
    ostream_->flush();
}

void DumpLog::PrintJson(const std::string& content)
{
    if (!ostream_->good()) {
        return;
    }
    ostream_->write(content.c_str(), content.length());
    ostream_->flush();
}

void DumpLog::PrintEndDumpInfoNG(bool isElement)
{
    int32_t depth = GetDepth() + DumpLog::END_POS_TWO;
    std::string result;
    for (int32_t i = 0; i < depth; ++i) {
        result.append("}");
    }
    if (isElement) {
        Append(result);
    } else {
        PrintJson(result);
    }
}

std::string DumpLog::GetPrefix(int32_t depth)
{
    std::string prefix = "";
    if (depth > 0) {
        int32_t lastDepth = GetDepth();
        if (depth == lastDepth) {
            prefix.append("},");
        } else if (depth > lastDepth) {
            prefix = ",";
        } else {
            int32_t diff = lastDepth - depth + 1;
            prefix.assign(diff, '}').append(",");
        }
    }
    SetDepth(depth);
    return prefix;
}

std::string DumpLog::FormatDumpInfo(const std::string& str, int32_t depth)
{
    if (str.length() > DumpLog::MIN_JSON_LENGTH) {
        if (depth == 0) {
            return str.substr(0, str.length() - DumpLog::END_POS_TWO);
        }
        return str.substr(1, str.length() - DumpLog::END_POS_THREE);
    }
    return str;
}
} // namespace OHOS::Ace
