/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_DRAWABLE_DESCRIPTOR_OUT_DRAWABLE_DESCRIPTOR_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_DRAWABLE_DESCRIPTOR_OUT_DRAWABLE_DESCRIPTOR_H
#include "animated_drawable_descriptor.h"
#include "pixelmap_drawable_descriptor.h"
#include "layered_drawable_descriptor.h"

namespace OHOS::Ace::Napi {

class DrawableDescriptorFactory {
public:
    using DrawableType = DrawableDescriptor::DrawableType;
    using ResourceManager = Global::Resource::ResourceManager;
    using RState = Global::Resource::RState;
    static std::unique_ptr<DrawableDescriptor> Create(int32_t id, const std::shared_ptr<ResourceManager>& resourceMgr,
        RState& state, DrawableType& drawableType, uint32_t density)
    {
        std::string type;
        size_t len;
        std::unique_ptr<uint8_t[]> jsonBuf;
        state = resourceMgr->GetDrawableInfoById(id, type, len, jsonBuf, density);
        if (state != Global::Resource::SUCCESS) {
            HILOGE("Failed to get drawable info from resmgr");
            return nullptr;
        }
        transform(type.begin(), type.end(), type.begin(), ::tolower);
        if (type == "json") {
            HILOGD("Create LayeredDrawableDescriptor object");
            drawableType = DrawableDescriptor::DrawableType::LAYERED;
            state = Global::Resource::SUCCESS;
            return std::make_unique<LayeredDrawableDescriptor>(std::move(jsonBuf), len, resourceMgr);
        }
        if (type == "png" || type == "jpg" || type == "bmp" || type == "svg" || type == "gif" || type == "webp" ||
            type == "astc" || type == "sut") {
            HILOGD("Create DrawableDescriptor object");
            drawableType = DrawableDescriptor::DrawableType::BASE;
            state = Global::Resource::SUCCESS;
            return std::make_unique<DrawableDescriptor>(std::move(jsonBuf), len);
        }
        HILOGE("unknow resource type: %{public}s", type.c_str());
        state = Global::Resource::INVALID_FORMAT;
        return nullptr;
    }

    static std::unique_ptr<DrawableDescriptor> Create(const char* name,
        const std::shared_ptr<ResourceManager>& resourceMgr, RState& state, DrawableType& drawableType,
        uint32_t density)
    {
        std::string type;
        size_t len;
        std::unique_ptr<uint8_t[]> jsonBuf;
        state = resourceMgr->GetDrawableInfoByName(name, type, len, jsonBuf, density);
        if (state != Global::Resource::SUCCESS) {
            HILOGE("Failed to get drawable info from resmgr");
            return nullptr;
        }
        transform(type.begin(), type.end(), type.begin(), ::tolower);
        if (type == "json") {
            HILOGD("Create LayeredDrawableDescriptor object");
            drawableType = DrawableDescriptor::DrawableType::LAYERED;
            state = Global::Resource::SUCCESS;
            return std::make_unique<LayeredDrawableDescriptor>(std::move(jsonBuf), len, resourceMgr);
        }
        if (type == "png" || type == "jpg" || type == "bmp" || type == "svg" || type == "gif" || type == "webp" ||
            type == "astc" || type == "sut") {
            HILOGD("Create DrawableDescriptor object");
            drawableType = DrawableDescriptor::DrawableType::BASE;
            state = Global::Resource::SUCCESS;
            return std::make_unique<DrawableDescriptor>(std::move(jsonBuf), len);
        }
        HILOGE("unknow resource type: %{public}s", type.c_str());
        state = Global::Resource::INVALID_FORMAT;
        return nullptr;
    }

    static std::unique_ptr<DrawableDescriptor> Create(std::tuple<int32_t, uint32_t, uint32_t>& drawableInfo,
        const std::shared_ptr<ResourceManager>& resourceMgr, RState& state, DrawableType& drawableType)
    {
        int32_t resId = std::get<0>(drawableInfo);
        uint32_t iconType = std::get<1>(drawableInfo);
        uint32_t density = std::get<2>(drawableInfo);
        std::unique_ptr<uint8_t[]> jsonBuf;
        std::tuple<std::string, size_t, std::string> info;
        state = resourceMgr->GetDrawableInfoById(resId, info, jsonBuf, iconType, density);
        if (state != Global::Resource::SUCCESS) {
            HILOGW("Failed to get drawable info from resmgr");
            return nullptr;
        }
        std::string type = std::get<0>(info);
        size_t len = std::get<1>(info);
        std::string path = std::get<2>(info);
        transform(type.begin(), type.end(), type.begin(), ::tolower);
        if (type == "json") {
            HILOGD("Create LayeredDrawableDescriptor object");
            drawableType = DrawableDescriptor::DrawableType::LAYERED;
            auto layeredDrawableDescriptor =
                std::make_unique<LayeredDrawableDescriptor>(std::move(jsonBuf), len, resourceMgr,
                    path, iconType, density);
            return layeredDrawableDescriptor;
        }
        if (type == "png" || type == "jpg" || type == "bmp" || type == "svg" || type == "gif" || type == "webp" ||
            type == "astc" || type == "sut") {
            HILOGD("Create DrawableDescriptor object");
            drawableType = DrawableDescriptor::DrawableType::BASE;
            return std::make_unique<DrawableDescriptor>(std::move(jsonBuf), len);
        }
        HILOGE("unknow resource type: %{public}s", type.c_str());
        state = Global::Resource::INVALID_FORMAT;
        return nullptr;
    }

    static std::unique_ptr<DrawableDescriptor> Create(std::tuple<const char*, uint32_t, uint32_t>& drawableInfo,
        const std::shared_ptr<ResourceManager>& resourceMgr, RState& state, DrawableType& drawableType)
    {
        const char* name = std::get<0>(drawableInfo);
        uint32_t iconType = std::get<1>(drawableInfo);
        uint32_t density = std::get<2>(drawableInfo);
        std::unique_ptr<uint8_t[]> jsonBuf;
        std::tuple<std::string, size_t, std::string> info;
        state = resourceMgr->GetDrawableInfoByName(name, info, jsonBuf, iconType, density);
        if (state != Global::Resource::SUCCESS) {
            HILOGW("Failed to get drawable info from resmgr");
            return nullptr;
        }
        std::string type = std::get<0>(info);
        size_t len = std::get<1>(info);
        std::string path = std::get<2>(info);
        transform(type.begin(), type.end(), type.begin(), ::tolower);
        if (type == "json") {
            HILOGD("Create LayeredDrawableDescriptor object");
            drawableType = DrawableDescriptor::DrawableType::LAYERED;
            auto layeredDrawableDescriptor = std::make_unique<LayeredDrawableDescriptor>(
                std::move(jsonBuf), len, resourceMgr, path, iconType, density);
            return layeredDrawableDescriptor;
        }
        if (type == "png" || type == "jpg" || type == "bmp" || type == "svg" || type == "gif" || type == "webp" ||
            type == "astc" || type == "sut") {
            HILOGD("Create DrawableDescriptor object");
            drawableType = DrawableDescriptor::DrawableType::BASE;
            return std::make_unique<DrawableDescriptor>(std::move(jsonBuf), len);
        }
        HILOGE("unknow resource type: %{public}s", type.c_str());
        state = Global::Resource::INVALID_FORMAT;
        return nullptr;
    }

    static std::unique_ptr<DrawableDescriptor> Create(std::pair<std::unique_ptr<uint8_t[]>, size_t> &foregroundInfo,
        std::pair<std::unique_ptr<uint8_t[]>, size_t> &backgroundInfo, std::string &path, DrawableType& drawableType,
        const std::shared_ptr<ResourceManager>& resourceMgr)
    {
        std::unique_ptr<uint8_t[]> jsonBuf;
        drawableType = DrawableDescriptor::DrawableType::LAYERED;
        auto layeredDrawableDescriptor = std::make_unique<LayeredDrawableDescriptor>(
            std::move(jsonBuf), 0, resourceMgr, path, 1, foregroundInfo, backgroundInfo);
        return layeredDrawableDescriptor;
    }
};
} // namespace OHOS::Ace::Napi

#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_DRAWABLE_DESCRIPTOR_OUT_DRAWABLE_DESCRIPTOR_H