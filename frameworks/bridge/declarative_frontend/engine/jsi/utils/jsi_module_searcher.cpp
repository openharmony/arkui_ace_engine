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

#include "jsi_module_searcher.h"

#include <algorithm>
#include <fstream>
#include <vector>

#include "base/utils/string_utils.h"

#ifdef WINDOWS_PLATFORM
#include <io.h>

namespace {
char* realpath(const char* path, char* resolvedPath)
{
    if (_access(path, 0) < 0) {
        return nullptr;
    }
    if (strcpy_s(resolvedPath, PATH_MAX, path) != 0) {
        return nullptr;
    }
    return resolvedPath;
}
}
#endif

namespace OHOS::Ace::Framework {
namespace {
constexpr char PREFIX_BUNDLE[] = "@bundle:";
constexpr char PREFIX_MODULE[] = "@module:";
constexpr char PREFIX_LOCAL[] = "@local:";

constexpr char NPM_PATH_SEGMENT[] = "node_modules";
constexpr char DIST_PATH_SEGMENT[] = "dist";

constexpr char NPM_ENTRY_FILE[] = "index.abc";
constexpr char NPM_ENTRY_LINK[] = "entry.txt";

#if defined(WINDOWS_PLATFORM)
constexpr char SEPERATOR[] = "\\";
constexpr char SOURCE_ASSETS_PATH[] = "\\assets\\default";
constexpr char NODE_MODULES_PATH[] = "\\assets_esmodule\\default\\node_modules\\0";
#else
constexpr char SEPERATOR[] = "/";
constexpr char SOURCE_ASSETS_PATH[] = "/assets/default";
constexpr char NODE_MODULES_PATH[] = "/assets_esmodule/default/node_modules/0";
#endif

constexpr char EXT_NAME_ABC[] = ".abc";
constexpr char EXT_NAME_ETS[] = ".ets";
constexpr char EXT_NAME_TS[] = ".ts";
constexpr char EXT_NAME_JS[] = ".js";

constexpr size_t MAX_NPM_LEVEL = 1;

void SplitString(const std::string& str, std::vector<std::string>& out, size_t pos = 0, const char* seps = SEPERATOR)
{
    if (str.empty() || pos >= str.length()) {
        return;
    }

    size_t startPos = pos;
    size_t endPos = 0;
    while ((endPos = str.find_first_of(seps, startPos)) != std::string::npos) {
        if (endPos > startPos) {
            out.emplace_back(str.substr(startPos, endPos - startPos));
        }
        startPos = endPos + 1;
    }

    if (startPos < str.length()) {
        out.emplace_back(str.substr(startPos));
    }
}

std::string JoinString(const std::vector<std::string>& strs, const char* sep, size_t startIndex = 0)
{
    std::string out;
    for (size_t index = startIndex; index < strs.size(); ++index) {
        if (!strs[index].empty()) {
            out.append(strs[index]) += sep;
        }
    }
    if (!out.empty()) {
        out.pop_back();
    }
    return out;
}

inline std::string StripString(const std::string& str, const char* charSet = " \t\n\r")
{
    size_t startPos = str.find_first_not_of(charSet);
    if (startPos == std::string::npos) {
        return std::string();
    }

    return str.substr(startPos, str.find_last_not_of(charSet) - startPos + 1);
}
}

JsiModuleSearcher::JsiModuleSearcher(const std::string& bundleName, const std::string& assetPath)
{
    std::vector<std::string> pathVector;
    SplitString(assetPath, pathVector);
    // pop "ets" directory from path
    pathVector.pop_back();
    // pop "default" directory from path
    pathVector.pop_back();
    // pop "assets" directory from path
    pathVector.pop_back();
    bundleInstallPath_ = JoinString(pathVector, SEPERATOR);
    bundleName_ = bundleName;
}

std::string JsiModuleSearcher::operator()(const std::string& curJsModulePath, const std::string& newJsModuleUri) const
{
    std::string newJsModulePath;

    if (curJsModulePath.empty() || newJsModuleUri.empty()) {
        return newJsModulePath;
    }

    switch (newJsModuleUri[0]) {
        case '.': {
            newJsModulePath = MakeNewJsModulePath(curJsModulePath, newJsModuleUri);
            break;
        }
        case '@': {
            newJsModulePath = ParseOhmUri(curJsModulePath, newJsModuleUri);
            if (newJsModulePath.empty()) {
                newJsModulePath = FindNpmPackage(curJsModulePath, newJsModuleUri);
            }
            break;
        }
        default: {
            newJsModulePath = FindNpmPackage(curJsModulePath, newJsModuleUri);
            break;
        }
    }
    FixExtName(newJsModulePath);

    return newJsModulePath;
}

void JsiModuleSearcher::FixExtName(std::string& path)
{
    if (path.empty()) {
        return;
    }

    if (StringUtils::EndWith(path, EXT_NAME_ABC, sizeof(EXT_NAME_ABC) - 1)) {
        return;
    }

    if (StringUtils::EndWith(path, EXT_NAME_ETS, sizeof(EXT_NAME_ETS) - 1)) {
        path.erase(path.length() - (sizeof(EXT_NAME_ETS) - 1), sizeof(EXT_NAME_ETS) - 1);
    } else if (StringUtils::EndWith(path, EXT_NAME_TS, sizeof(EXT_NAME_TS) - 1)) {
        path.erase(path.length() - (sizeof(EXT_NAME_TS) - 1), sizeof(EXT_NAME_TS) - 1);
    } else if (StringUtils::EndWith(path, EXT_NAME_JS, sizeof(EXT_NAME_JS) - 1)) {
        path.erase(path.length() - (sizeof(EXT_NAME_JS) - 1), sizeof(EXT_NAME_JS) - 1);
    }

    path.append(EXT_NAME_ABC);
}

std::string JsiModuleSearcher::GetInstallPath(const std::string& curJsModulePath, bool module) const
{
    size_t pos = std::string::npos;
    if (StringUtils::StartWith(curJsModulePath, bundleInstallPath_.c_str(), bundleInstallPath_.length())) {
        pos = bundleInstallPath_.length() - 1;
    }

    if (module) {
        pos = curJsModulePath.find(SEPERATOR, pos + 1);
        if (pos == std::string::npos) {
            return std::string();
        }
    }

    return curJsModulePath.substr(0, pos + 1);
}

std::string JsiModuleSearcher::MakeNewJsModulePath(
    const std::string& curJsModulePath, const std::string& newJsModuleUri) const
{
    std::string moduleInstallPath = GetInstallPath(curJsModulePath, true);
    if (moduleInstallPath.empty()) {
        return std::string();
    }

    std::vector<std::string> pathVector;
    SplitString(curJsModulePath, pathVector, moduleInstallPath.length());

    if (pathVector.empty()) {
        return std::string();
    }

    // Remove file name, reserve only dir name
    pathVector.pop_back();

    std::vector<std::string> relativePathVector;
    SplitString(newJsModuleUri, relativePathVector);

    for (auto& value : relativePathVector) {
        if (value == ".") {
            continue;
        } else if (value == "..") {
            if (pathVector.empty()) {
                return std::string();
            }
            pathVector.pop_back();
        } else {
            pathVector.emplace_back(std::move(value));
        }
    }

    std::string jsModulePath = moduleInstallPath + JoinString(pathVector, SEPERATOR);
    FixExtName(jsModulePath);
    if (jsModulePath.size() >= PATH_MAX) {
        return std::string();
    }

    char path[PATH_MAX];
    if (realpath(jsModulePath.c_str(), path) != nullptr) {
        return std::string(path);
    }
    return std::string();
}

std::string JsiModuleSearcher::FindNpmPackageInPath(const std::string& npmPath) const
{
    std::string fileName = npmPath + SEPERATOR + DIST_PATH_SEGMENT + SEPERATOR + NPM_ENTRY_FILE;

    char path[PATH_MAX];
    if (fileName.size() >= PATH_MAX) {
        return std::string();
    }
    if (realpath(fileName.c_str(), path) != nullptr) {
        return path;
    }

    fileName = npmPath + SEPERATOR + NPM_ENTRY_LINK;
    if (fileName.size() >= PATH_MAX) {
        return std::string();
    }
    if (realpath(fileName.c_str(), path) == nullptr) {
        return std::string();
    }

    std::ifstream stream(path, std::ios::ate);
    if (!stream.is_open()) {
        return std::string();
    }

    auto fileLen = stream.tellg();
    if (fileLen >= PATH_MAX) {
        return std::string();
    }

    stream.seekg(0);
    stream.read(path, fileLen);
    path[fileLen] = '\0';
    return npmPath + SEPERATOR + StripString(path);
}

std::string JsiModuleSearcher::FindNpmPackageInTopLevel(
    const std::string& moduleInstallPath, const std::string& npmPackage, size_t start) const
{
    for (size_t level = start; level <= MAX_NPM_LEVEL; ++level) {
        std::string path =
            moduleInstallPath + NPM_PATH_SEGMENT + SEPERATOR + std::to_string(level) + SEPERATOR + npmPackage;
        path = FindNpmPackageInPath(path);
        if (!path.empty()) {
            return path;
        }
    }

    return std::string();
}

std::string JsiModuleSearcher::FindNpmPackage(const std::string& curJsModulePath, const std::string& npmPackage) const
{
    std::string moduleInstallPath = bundleInstallPath_;
    moduleInstallPath.append(NODE_MODULES_PATH).append(SEPERATOR);

    std::string path = moduleInstallPath + npmPackage;
    path = FindNpmPackageInPath(path);
    if (!path.empty()) {
        return path;
    }
    return std::string();
}

std::string JsiModuleSearcher::ParseOhmUri(const std::string& curJsModulePath, const std::string& newJsModuleUri) const
{
    std::string moduleInstallPath;
    std::vector<std::string> pathVector;
    size_t index = 0;

    if (StringUtils::StartWith(newJsModuleUri, PREFIX_BUNDLE, sizeof(PREFIX_BUNDLE) - 1)) {
        SplitString(newJsModuleUri, pathVector, sizeof(PREFIX_BUNDLE) - 1);

        // Uri should have atleast 3 segments
        if (pathVector.size() < 3) {
            return std::string();
        }

        const auto& bundleName = pathVector[index];
        // skip hapName for preview has no hap directory
        index = index + 2; // skip 2 of directory segments
        if (bundleName == bundleName_) {
            moduleInstallPath = bundleInstallPath_;
        }
        moduleInstallPath.append(SOURCE_ASSETS_PATH).append(SEPERATOR);
        moduleInstallPath.append(pathVector[index++]).append(SEPERATOR);
    } else if (StringUtils::StartWith(newJsModuleUri, PREFIX_MODULE, sizeof(PREFIX_MODULE) - 1)) {
        SplitString(newJsModuleUri, pathVector, sizeof(PREFIX_MODULE) - 1);

        // Uri should have atleast 2 segments
        if (pathVector.size() < 2) {
            return std::string();
        }

        moduleInstallPath = GetInstallPath(curJsModulePath, false);
        if (moduleInstallPath.empty()) {
            return std::string();
        }
        moduleInstallPath.append(pathVector[index++]).append(SEPERATOR);
    } else if (StringUtils::StartWith(newJsModuleUri, PREFIX_LOCAL, sizeof(PREFIX_LOCAL) - 1)) {
        SplitString(newJsModuleUri, pathVector, sizeof(PREFIX_LOCAL) - 1);

        if (pathVector.empty()) {
            return std::string();
        }

        moduleInstallPath = GetInstallPath(curJsModulePath);
        if (moduleInstallPath.empty()) {
            return std::string();
        }
    } else {
        return std::string();
    }

    if (pathVector[index] != NPM_PATH_SEGMENT) {
        return moduleInstallPath + JoinString(pathVector, SEPERATOR, index);
    }

    return FindNpmPackageInTopLevel(moduleInstallPath, JoinString(pathVector, SEPERATOR, index + 1));
}
} // namespace OHOS::Ace::Framework