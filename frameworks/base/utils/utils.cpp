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

#include <climits>
#include "core/components_ng/base/frame_node.h"
#include "base/utils/utils.h"
#ifdef WINDOWS_PLATFORM
#include <shlwapi.h>
#endif
namespace OHOS::Ace {
constexpr int64_t MAX_FILE_SIZE = 20 * 1024 * 1024;
    bool RealPath(const std::string& fileName, char* realPath)
{
#if defined(WINDOWS_PLATFORM)
        return PathCanonicalize(realPath, fileName.c_str()) != 0;
#else
        return realpath(fileName.c_str(), realPath) != nullptr;
#endif
}

double RoundToMaxPrecision(double value)
{
    int precision = std::numeric_limits<double>::digits10;
    double factor = std::pow(10, precision - 2);
    if (NearZero(factor)) {
        return value;
    }
    return std::round(value * factor) / factor;
}

std::string ReadFileToString(const std::string& packagePathStr, const std::string& fileName)
{
    auto configPath = packagePathStr + fileName;
    char realPath[PATH_MAX] = { 0x00 };
    if (!RealPath(configPath.c_str(), realPath)) {
        LOGE("realpath fail!");
        return "";
    }
    std::unique_ptr<FILE, decltype(&fclose)> file(fopen(realPath, "rb"), fclose);
    if (!file) {
        LOGE("open file failed");
        return "";
    }
    if (std::fseek(file.get(), 0, SEEK_END) != 0) {
        LOGE("seek file tail error");
        return "";
    }

    int64_t size = std::ftell(file.get());
    if (size <= 0L || size > MAX_FILE_SIZE) {
        return "";
    }

    char* fileData = new (std::nothrow) char[size + 1];
    if (fileData == nullptr) {
        return "";
    }

    rewind(file.get());
    std::unique_ptr<char[]> jsonStream(fileData);
    size_t result = std::fread(jsonStream.get(), 1, size, file.get());
    jsonStream[size] = '\0';
    if (result != static_cast<size_t>(size)) {
        LOGE("read file failed");
        return "";
    }

    return fileData;
}

namespace NG {
RefPtr<FrameNode> FindSameParentComponent(const RefPtr<FrameNode>& nodeA, const RefPtr<FrameNode>& nodeB)
{
    if (!nodeA || !nodeB) {
        return nullptr;
    }
    std::vector<RefPtr<FrameNode>> ancestorsA;
    RefPtr<FrameNode> current = nodeA;

    while (current) {
        ancestorsA.push_back(current);
        if (current->CheckTopWindowBoundary()) {
            break;
        }
        current = current->GetAncestorNodeOfFrame(false);
    }
    current = nodeB;
    while (current) {
        for (const auto& ancestor : ancestorsA) {
            if (ancestor == current) {
                return current;
            }
        }
        if (current->CheckTopWindowBoundary()) {
            break;
        }
        current = current->GetAncestorNodeOfFrame(false);
    }
    return nullptr;
}
} // namespace NG
}