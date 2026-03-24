/*
 * Copyright (c) 2021-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_IMAGE_IMAGE_RESIZABLE_SLICE_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_IMAGE_IMAGE_RESIZABLE_SLICE_H

#include <functional>
#include <string>
#include <unordered_map>

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "core/common/resource/resource_object.h"

namespace OHOS::Ace {

enum class ResizableOption {
    LEFT,
    RIGHT,
    TOP,
    BOTTOM,
};

struct ACE_FORCE_EXPORT ImageResizableSlice {
    Dimension left;
    Dimension right;
    Dimension top;
    Dimension bottom;

    struct ResourceUpdater {
        RefPtr<ResourceObject> obj;
        std::function<void(const RefPtr<ResourceObject>&, ImageResizableSlice&)> updateFunc;
    };

    std::unordered_map<std::string, ResourceUpdater> resMap_;

    std::string ToString() const;
    bool operator==(const ImageResizableSlice& slice) const;
    bool Valid() const;
    void SetResizableLeft(const Dimension& sliceDimension);
    void SetResizableRight(const Dimension& sliceDimension);
    void SetResizableBottom(const Dimension& sliceDimension);
    void SetResizableTop(const Dimension& sliceDimension);
    void SetEdgeSlice(ResizableOption direction, const Dimension& sliceDimension);
    void AddResource(
        const std::string& key,
        const RefPtr<ResourceObject>& resObj,
        std::function<void(const RefPtr<ResourceObject>&, ImageResizableSlice&)>&& updateFunc);
    void RemoveResource(const std::string& key);
    void ReloadResources();
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_IMAGE_IMAGE_RESIZABLE_SLICE_H
