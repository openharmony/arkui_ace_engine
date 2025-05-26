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

#include "core/components/plugin/plugin_sub_container.h"

namespace OHOS::Ace {
namespace {
constexpr char DECLARATIVE_ARK_ENGINE_SHARED_LIB[] = "libace_engine_declarative_ark.z.so";
} // namespace

const char* GetDeclarativeSharedLibrary()
{
    return DECLARATIVE_ARK_ENGINE_SHARED_LIB;
}

void PluginSubContainer::Initialize(const std::string& codeLanguage) {}

void PluginSubContainer::Destroy() {}

void PluginSubContainer::UpdateRootElementSize()
{
    surfaceWidth_ = 0;
    surfaceHeight_ = 0;
    density_ = 0;
}

void PluginSubContainer::UpdateSurfaceSize() {}

void PluginSubContainer::RunDecompressedPlugin(const std::string& hapPath, const std::string& module,
    const std::string& source, const std::string& moduleResPath, const std::string& data)
{}

void PluginSubContainer::RunPlugin(const std::string& path, const std::string& module, const std::string& source,
    const std::string& moduleResPath, const std::string& data)
{}

void PluginSubContainer::SetPluginComponentTheme(
    const std::string& path, const RefPtr<AssetManager>& flutterAssetManager)
{}

void PluginSubContainer::SetActionEventHandler() {}

RefPtr<AssetManager> PluginSubContainer::GetDecompressedAssetManager(
    const std::string& hapPath, const std::string& module)
{
    return nullptr;
}

RefPtr<AssetManager> PluginSubContainer::SetAssetManager(const std::string& path, const std::string& module)
{
    return nullptr;
}

void PluginSubContainer::UpdatePlugin(const std::string& content) {}
} // namespace OHOS::Ace
