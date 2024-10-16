/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_SVG_IMAGE_OBJECT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_SVG_IMAGE_OBJECT_H

#include "core/components_ng/image_provider/image_object.h"
#include "core/components_ng/image_provider/svg_dom_base.h"

namespace OHOS::Ace::NG {

class SvgImageObject : public ImageObject {
    DECLARE_ACE_TYPE(SvgImageObject, ImageObject);

public:
    SvgImageObject(const ImageSourceInfo& src, const SizeF& imageSize) : ImageObject(src, imageSize, nullptr) {}
    ~SvgImageObject() override = default;

    static RefPtr<SvgImageObject> Create(const ImageSourceInfo& src, const RefPtr<ImageData>& data);
    RefPtr<SvgDomBase> GetSVGDom() const override;
    std::string GetDumpInfo() override;
    RefPtr<ImageObject> Clone() override
    {
        return Claim(this);
    }

    void MakeCanvasImage(
        const WeakPtr<ImageLoadingContext>& ctxWp, const SizeF& resizeTarget, bool forceResize, bool syncLoad) override;

private:
    // return true if process is successful
    bool MakeSvgDom(const RefPtr<ImageData>& data, const ImageSourceInfo& src);
    RefPtr<SvgDomBase> svgDomBase_;

    ACE_DISALLOW_COPY_AND_MOVE(SvgImageObject);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_SVG_IMAGE_OBJECT_H
