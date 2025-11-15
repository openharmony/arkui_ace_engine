/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "drawable_descriptor_ani.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <dlfcn.h>
#include <string>
#include <unordered_set>

#include "ani.h"
#include "cJSON.h"
#include "resource_manager.h"

#include "core/interfaces/drawable/drawable_api.h"

namespace OHOS::Ace::Ani {
namespace {
constexpr char PIXEL_MAP_DRAWABLE[] = "@ohos.arkui.drawableDescriptor.PixelMapDrawableDescriptor";
constexpr char LAYERED_DRAWABLE[] = "@ohos.arkui.drawableDescriptor.LayeredDrawableDescriptor";
constexpr char BACKGROUND_KEY[] = "background";
constexpr char FOREGROUND_KEY[] = "foreground";
constexpr char DEFAULT_MASK[] = "ohos_icon_mask";
constexpr char LIBACE_MODULE[] = "libace_compatible.z.so";
constexpr int32_t DECIMAL_BASE = 10;
constexpr size_t BUFFER_NUMBER = 2;
} // namespace

using GetArkUIDrawableDescriptorFunc = const ArkUIDrawableDescriptor* (*)();

const ArkUIDrawableDescriptor* GetArkUIDrawableModifier()
{
    static void* handle = nullptr;
    static void* drawable = nullptr;
    static bool initialized = false;
    if (!initialized) {
        handle = dlopen(LIBACE_MODULE, RTLD_LAZY | RTLD_LOCAL);
        if (handle != nullptr) {
            drawable = dlsym(handle, DRAWABLE_FUNC_NAME);
            initialized = true;
        }
    }
    if (handle == nullptr) {
        return nullptr;
    }
    auto entry = reinterpret_cast<GetArkUIDrawableDescriptorFunc>(drawable);
    if (entry == nullptr) {
        return nullptr;
    }
    const auto* result = entry();
    return result;
}

bool CheckResourceType(const std::string& type)
{
    static const std::unordered_set<std::string> types = { "png", "jpg", "bmp", "svg", "gif", "webp", "astc", "sut" };
    return types.count(type);
}

bool SafeStringToUint(const std::string& str, uint32_t& result)
{
    if (str.empty()) {
        return false;
    }
    char* end = nullptr;
    unsigned long value = strtoul(str.c_str(), &end, DECIMAL_BASE);
    if (str.c_str() == end) {
        return false;
    }
    while (*end != '\0') {
        if (!isspace(static_cast<unsigned char>(*end))) {
            return false;
        }
        ++end;
    }
    if (value > std::numeric_limits<uint32_t>::max() || errno == ERANGE) {
        return false;
    }
    if (str.find('-') != std::string::npos) {
        return false;
    }
    result = static_cast<uint32_t>(value);
    return true;
}

std::vector<uint32_t> GetResIdInJson(const MediaData& jsonBuf, const std::vector<std::string>& keys)
{
    std::vector<uint32_t> ids;
    cJSON* roots = cJSON_ParseWithLength(reinterpret_cast<const char*>(jsonBuf.data.get()), jsonBuf.len);
    if (roots == nullptr) {
        return ids;
    }
    for (const auto& key : keys) {
        cJSON* item = cJSON_GetObjectItem(roots->child, key.c_str());
        if (item == nullptr || !cJSON_IsString(item)) {
            cJSON_Delete(roots);
            return ids;
        }
        std::string value(item->valuestring);
        std::string idStr;
        size_t pos = value.find(":");
        if (pos != std::string::npos) {
            idStr = value.substr(pos + 1);
        } else {
            cJSON_Delete(roots);
            return ids;
        }
        uint32_t resId = 0;
        if (!SafeStringToUint(idStr, resId)) {
            cJSON_Delete(roots);
            return ids;
        }
        ids.push_back(resId);
    }
    cJSON_Delete(roots);
    return ids;
}

ani_object CreatePixelMapDrawable(ani_env* env, MediaData& mediaData)
{
    ani_class cls;
    ani_object obj = nullptr;
    auto status = env->FindClass(PIXEL_MAP_DRAWABLE, &cls);
    if (status != ANI_OK) {
        return obj;
    }
    ani_method ctor;
    env->Class_FindMethod(cls, "<ctor>", ":", &ctor);
    env->Object_New(cls, ctor, &obj);
    // no media data
    if (mediaData.len <= 0) {
        return obj;
    }
    // have media data
    ani_long nativeObj = 0;
    env->Object_GetPropertyByName_Long(obj, "nativeObj", &nativeObj);
    // take native pixelmap drawable
    auto drawable = reinterpret_cast<void*>(nativeObj);
    if (drawable == nullptr) {
        return obj;
    }
    auto modifier = GetArkUIDrawableModifier();
    if (modifier == nullptr) {
        return obj;
    }
    modifier->setPixelRawData(drawable, mediaData.data.release(), mediaData.len);
    return obj;
}

ani_object CreateLayeredDrawableByJsonBuffer(ani_env* env, DrawableInfo& info)
{
    ani_class cls;
    ani_object obj = nullptr;
    auto status = env->FindClass(LAYERED_DRAWABLE, &cls);
    if (status != ANI_OK) {
        return obj;
    }
    ani_method ctor;
    env->Class_FindMethod(cls, "<ctor>", ":", &ctor);
    env->Object_New(cls, ctor, &obj);
    ani_long nativeObj = 0;
    env->Object_GetPropertyByName_Long(obj, "nativeObj", &nativeObj);
    auto* drawable = reinterpret_cast<void*>(nativeObj);
    if (drawable == nullptr) {
        return obj;
    }
    std::string foreground(FOREGROUND_KEY);
    std::string background(BACKGROUND_KEY);
    auto ids = GetResIdInJson(info.firstBuffer, { foreground, background });
    if (ids.size() < BUFFER_NUMBER) {
        return obj;
    }
    // initialize foreground and background buffer
    auto resMgr = info.manager;
    std::vector<std::pair<uint8_t*, size_t>> datas;
    for (const auto id : ids) {
        std::tuple<std::string, size_t, std::string> dinfo;
        std::unique_ptr<uint8_t[]> data;
        auto state = resMgr->GetDrawableInfoById(id, dinfo, data, 0, info.density);
        if (state == Global::Resource::SUCCESS) {
            datas.push_back({ data.release(), std::get<1>(dinfo) });
        }
    }
    if (datas.size() < BUFFER_NUMBER) {
        return obj;
    }
    auto modifier = GetArkUIDrawableModifier();
    if (modifier == nullptr) {
        return obj;
    }
    modifier->setForegroundData(drawable, datas[0].first, datas[0].second);
    modifier->setBackgroundData(drawable, datas[1].first, datas[1].second);
    // initialize mask data
    std::unique_ptr<uint8_t[]> maskData;
    size_t maskLen = 0;
    auto state = resMgr->GetMediaDataByName(DEFAULT_MASK, maskLen, maskData);
    if (state == Global::Resource::SUCCESS && maskLen > 0) {
        modifier->setMaskData(drawable, maskData.release(), maskLen);
    }
    return obj;
}

ani_object CreateLayerdDrawableByTwoBuffer(ani_env* env, DrawableInfo& info)
{
    ani_class cls;
    ani_object obj = nullptr;
    auto status = env->FindClass(LAYERED_DRAWABLE, &cls);
    if (status != ANI_OK) {
        return obj;
    }
    ani_method ctor;
    env->Class_FindMethod(cls, "<ctor>", ":", &ctor);
    env->Object_New(cls, ctor, &obj);
    ani_long nativeObj = 0;
    env->Object_GetPropertyByName_Long(obj, "nativeObj", &nativeObj);
    auto* drawable = reinterpret_cast<void*>(nativeObj);
    if (drawable == nullptr) {
        return obj;
    }
    auto modifier = GetArkUIDrawableModifier();
    if (modifier == nullptr) {
        return obj;
    }
    modifier->setForegroundData(drawable, info.firstBuffer.data.release(), info.firstBuffer.len);
    modifier->setBackgroundData(drawable, info.secondBuffer.data.release(), info.secondBuffer.len);
    // initialize mask data
    auto resMgr = info.manager;
    auto themeMask = resMgr->GetThemeMask();
    modifier->setMaskPath(drawable, themeMask.c_str());
    std::unique_ptr<uint8_t[]> maskData;
    size_t maskLen = 0;
    auto state = resMgr->GetMediaDataByName(DEFAULT_MASK, maskLen, maskData);
    if (state == Global::Resource::SUCCESS && maskLen > 0) {
        modifier->setMaskData(drawable, maskData.release(), maskLen);
    }
    return obj;
}

ani_object DrawableDescriptorAni::CreateDrawableDescriptor(ani_env* env, DrawableInfo& info)
{
    ani_object object = nullptr;
    std::string type = info.type;
    std::transform(type.begin(), type.end(), type.begin(), ::tolower);
    // type is none
    if (type == "none" && info.firstBuffer.len > 0) {
        object = CreatePixelMapDrawable(env, info.firstBuffer);
        return object;
    }

    // type is json
    if (type == "json" && info.firstBuffer.len > 0) {
        object = CreateLayeredDrawableByJsonBuffer(env, info);
        return object;
    }

    // type is layered
    if (type == "layered" && info.firstBuffer.len > 0 && info.secondBuffer.len > 0) {
        object = CreateLayerdDrawableByTwoBuffer(env, info);
        return object;
    }

    // type is bitmap
    if (CheckResourceType(info.type) && info.firstBuffer.len > 0) {
        object = CreatePixelMapDrawable(env, info.firstBuffer);
        return object;
    }

    return object;
}
} // namespace OHOS::Ace::Ani
