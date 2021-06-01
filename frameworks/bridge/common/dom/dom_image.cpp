/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/common/dom/dom_image.h"

#include "base/utils/linear_map.h"
#include "base/utils/utils.h"
#include "frameworks/bridge/common/dom/dom_type.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::Framework {
namespace {

ImageFit ConvertStrToFit(const std::string& fit)
{
    static const LinearMapNode<ImageFit> imageFitMap[] = {
        { "contain", ImageFit::CONTAIN },
        { "cover", ImageFit::COVER },
        { "fill", ImageFit::FILL },
        { "none", ImageFit::NONE },
        { "scale-down", ImageFit::SCALEDOWN },
    };
    ImageFit imageFit = ImageFit::COVER;
    auto iter = BinarySearchFindIndex(imageFitMap, ArraySize(imageFitMap), fit.c_str());
    if (iter != -1) {
        imageFit = imageFitMap[iter].value;
    }
    return imageFit;
}

} // namespace

DOMImage::DOMImage(NodeId nodeId, const std::string& nodeName) : DOMNode(nodeId, nodeName)
{
    imageChild_ = AceType::MakeRefPtr<ImageComponent>();
    imageChild_->SetFitMaxSize(true);
    if (IsRightToLeft()) {
        imageChild_->SetTextDirection(TextDirection::RTL);
    }
}

bool DOMImage::SetSpecializedAttr(const std::pair<std::string, std::string>& attr)
{
    if (attr.first == DOM_SRC) {
        imageChild_->SetSrc(attr.second);
        return true;
    }
    if (attr.first == DOM_IMAGE_ALT) {
        imageChild_->SetAlt(attr.second);
        return true;
    }
    return false;
}

bool DOMImage::SetSpecializedStyle(const std::pair<std::string, std::string>& style)
{
    // static linear map must be sorted by key.
    static const LinearMapNode<void (*)(const std::string&, DOMImage&)> imageStylesOperators[] = {
        { DOM_IMAGE_FIT_ORIGINAL_SIZE,
            [](const std::string& val, DOMImage& image) { image.imageChild_->SetFitMaxSize(!StringToBool(val)); } },
        { DOM_IMAGE_MATCH_TEXT_DIRECTION,
            [](const std::string& val, DOMImage& image) {
                image.imageChild_->SetMatchTextDirection(StringToBool(val));
            } },
        { DOM_IMAGE_FIT, [](const std::string& val,
                         DOMImage& image) { image.imageChild_->SetImageFit(ConvertStrToFit(val.c_str())); } },
    };
    auto operatorIter =
        BinarySearchFindIndex(imageStylesOperators, ArraySize(imageStylesOperators), style.first.c_str());
    if (operatorIter != -1) {
        imageStylesOperators[operatorIter].value(style.second, *this);
        return true;
    }
    return false;
}

bool DOMImage::AddSpecializedEvent(int32_t pageId, const std::string& event)
{
    if (event == DOM_COMPLETE) {
        loadSuccessEventId_ = EventMarker(GetNodeIdForEvent(), event, pageId);
        imageChild_->SetLoadSuccessEventId(loadSuccessEventId_);
    } else if (event == DOM_ERROR) {
        loadFailEventId_ = EventMarker(GetNodeIdForEvent(), event, pageId);
        imageChild_->SetLoadFailEventId(loadFailEventId_);
    } else {
        return false;
    }
    return true;
}

void DOMImage::PrepareSpecializedComponent()
{
    // If there is a corresponding box decoration, specialize the box.
    if (boxComponent_) {
        auto backDecoration = boxComponent_->GetBackDecoration();
        if (backDecoration) {
            Border border = backDecoration->GetBorder();
            if (border.TopLeftRadius().IsValid() && border.TopRightRadius().IsValid() &&
                border.BottomLeftRadius().IsValid() && border.BottomRightRadius().IsValid()) {
                imageChild_->SetBorder(border);
            }
        }
    }
    if (flexItemComponent_ && !imageChild_->GetFitMaxSize()) {
        flexItemComponent_->SetStretchFlag(false);
    }
}

} // namespace OHOS::Ace::Framework
