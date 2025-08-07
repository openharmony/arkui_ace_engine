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
#include "test/mock/core/common/mock_resource_adapter_v2.h"

#include "core/components/theme/resource_adapter.h"
#include <map>

namespace OHOS::Ace {
namespace {
std::map<uint32_t, Color> g_colorMap;
std::map<uint32_t, Dimension> g_dimensionMap;
std::map<uint32_t, std::string> g_strMap;
std::map<uint32_t, std::vector<std::string>> g_strsMap;
std::map<uint32_t, double> g_doubleMap;
std::map<uint32_t, int32_t> g_int32Map;
std::mutex g_mapMutex;
} // namespace

RefPtr<ResourceAdapter> ResourceAdapter::Create()
{
    return AceType::MakeRefPtr<MockResourceAdapterV2>();
}

RefPtr<ResourceAdapter> ResourceAdapter::CreateNewResourceAdapter(
    const std::string& bundleName, const std::string& moduleName)
{
    return AceType::MakeRefPtr<MockResourceAdapterV2>();
}

bool MockResourceAdapterV2::GetMockResourceData(uint32_t id, Color& data)
{
    std::lock_guard<std::mutex> lock(g_mapMutex);
    if (g_colorMap.count(id) == 0) {
        return false;
    }
    data = g_colorMap[id];
    return true;
}

bool MockResourceAdapterV2::GetMockResourceData(uint32_t id, Dimension& data)
{
    std::lock_guard<std::mutex> lock(g_mapMutex);
    if (g_dimensionMap.count(id) == 0) {
        return false;
    }
    data = g_dimensionMap[id];
    return true;
}

bool MockResourceAdapterV2::GetMockResourceData(uint32_t id, std::string& data)
{
    std::lock_guard<std::mutex> lock(g_mapMutex);
    if (g_strMap.count(id) == 0) {
        return false;
    }
    data = g_strMap[id];
    return true;
}
bool MockResourceAdapterV2::GetMockResourceData(uint32_t id, std::vector<std::string>& data)
{
    std::lock_guard<std::mutex> lock(g_mapMutex);
    if (g_strsMap.count(id) == 0) {
        return false;
    }
    data = g_strsMap[id];
    return true;
}
bool MockResourceAdapterV2::GetMockResourceData(uint32_t id, double& data)
{
    std::lock_guard<std::mutex> lock(g_mapMutex);
    if (g_doubleMap.count(id) == 0) {
        return false;
    }
    data = g_doubleMap[id];
    return true;
}
bool MockResourceAdapterV2::GetMockResourceData(uint32_t id, int32_t& data)
{
    std::lock_guard<std::mutex> lock(g_mapMutex);
    if (g_int32Map.count(id) == 0) {
        return false;
    }
    data = g_int32Map[id];
    return true;
}

void AddMockResourceData(uint32_t id, const Color& data)
{
    std::lock_guard<std::mutex> lock(g_mapMutex);
    g_colorMap.insert(std::make_pair(id, data));
}

void AddMockResourceData(uint32_t id, const Dimension& data)
{
    std::lock_guard<std::mutex> lock(g_mapMutex);
    g_dimensionMap.insert(std::make_pair(id, data));
}

void AddMockResourceData(uint32_t id, const std::string& data)
{
    std::lock_guard<std::mutex> lock(g_mapMutex);
    g_strMap.insert(std::make_pair(id, data));
}
void AddMockResourceData(uint32_t id, const std::vector<std::string>& data)
{
    std::lock_guard<std::mutex> lock(g_mapMutex);
    g_strsMap.insert(std::make_pair(id, data));
}

void AddMockResourceData(uint32_t id, const double& data)
{
    std::lock_guard<std::mutex> lock(g_mapMutex);
    g_doubleMap.insert(std::make_pair(id, data));
}

void AddMockResourceData(uint32_t id, const int32_t& data)
{
    std::lock_guard<std::mutex> lock(g_mapMutex);
    g_int32Map.insert(std::make_pair(id, data));
}

void ResetMockResourceData()
{
    std::lock_guard<std::mutex> lock(g_mapMutex);
    g_colorMap.clear();
    g_dimensionMap.clear();
    g_strMap.clear();
    g_strsMap.clear();
    g_doubleMap.clear();
    g_int32Map.clear();
}
} // namespace OHOS::Ace
