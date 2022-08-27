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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_UTILS_JSI_MODULE_SEARCHER_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_UTILS_JSI_MODULE_SEARCHER_H

#include <string>

namespace OHOS::Ace::Framework {
class JsiModuleSearcher final {
public:
    explicit JsiModuleSearcher(const std::string& bundleName, const std::string& assetPath);
    ~JsiModuleSearcher() = default;

    JsiModuleSearcher(const JsiModuleSearcher&) = default;
    JsiModuleSearcher(JsiModuleSearcher&&) = default;
    JsiModuleSearcher& operator=(const JsiModuleSearcher&) = default;
    JsiModuleSearcher& operator=(JsiModuleSearcher&&) = default;

    std::string operator()(const std::string& curJsModulePath, const std::string& newJsModuleUri) const;

private:
    static void FixExtName(std::string& path);
    std::string GetInstallPath(const std::string& curJsModulePath, bool module = true) const;
    std::string MakeNewJsModulePath(const std::string& curJsModulePath, const std::string& newJsModuleUri) const;
    std::string FindNpmPackageInPath(const std::string& npmPath) const;
    std::string FindNpmPackageInTopLevel(
        const std::string& moduleInstallPath, const std::string& npmPackage, size_t start = 0) const;
    std::string FindNpmPackage(const std::string& curJsModulePath, const std::string& npmPackage) const;
    std::string ParseOhmUri(const std::string& curJsModulePath, const std::string& newJsModuleUri) const;

    std::string bundleName_;
    std::string bundleInstallPath_;
};
} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_UTILS_JSI_MODULE_SEARCHER_H