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

#include "base/image/image_resizable_slice.h"

namespace OHOS::Ace {

std::string ImageResizableSlice::ToString() const
{
    std::string result;
    result.append("ImageResizableSlice: {");
    result.append("left: ");
    result.append(left.ToString());
    result.append(", right: ");
    result.append(right.ToString());
    result.append(", top: ");
    result.append(top.ToString());
    result.append(", bottom: ");
    result.append(bottom.ToString());
    result.append("}");
    return result;
}

bool ImageResizableSlice::operator==(const ImageResizableSlice& slice) const
{
    return left == slice.left && right == slice.right && top == slice.top && bottom == slice.bottom;
}

bool ImageResizableSlice::Valid() const
{
    return left.IsValid() || right.IsValid() || top.IsValid() || bottom.IsValid();
}

void ImageResizableSlice::SetResizableLeft(const Dimension& sliceDimension)
{
    left = sliceDimension;
}

void ImageResizableSlice::SetResizableRight(const Dimension& sliceDimension)
{
    right = sliceDimension;
}

void ImageResizableSlice::SetResizableBottom(const Dimension& sliceDimension)
{
    bottom = sliceDimension;
}

void ImageResizableSlice::SetResizableTop(const Dimension& sliceDimension)
{
    top = sliceDimension;
}

void ImageResizableSlice::SetEdgeSlice(ResizableOption direction, const Dimension& sliceDimension)
{
    switch (direction) {
        case ResizableOption::TOP:
            SetResizableTop(sliceDimension);
            break;
        case ResizableOption::BOTTOM:
            SetResizableBottom(sliceDimension);
            break;
        case ResizableOption::LEFT:
            SetResizableLeft(sliceDimension);
            break;
        case ResizableOption::RIGHT:
            SetResizableRight(sliceDimension);
            break;
        default:
            break;
    }
}

void ImageResizableSlice::AddResource(
    const std::string& key,
    const RefPtr<ResourceObject>& resObj,
    std::function<void(const RefPtr<ResourceObject>&, ImageResizableSlice&)>&& updateFunc)
{
    if (resObj && updateFunc) {
        resMap_[key] = { resObj, std::move(updateFunc) };
    }
}

void ImageResizableSlice::RemoveResource(const std::string& key)
{
    auto iter = resMap_.find(key);
    if (iter != resMap_.end()) {
        resMap_.erase(iter);
    }
}

void ImageResizableSlice::ReloadResources()
{
    for (const auto& [key, resourceUpdater] : resMap_) {
        resourceUpdater.updateFunc(resourceUpdater.obj, *this);
    }
}

} // namespace OHOS::Ace
