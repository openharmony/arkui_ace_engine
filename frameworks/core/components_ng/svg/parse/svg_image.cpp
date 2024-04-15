/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "frameworks/core/components_ng/svg/parse/svg_image.h"

#include "base/utils/utils.h"
#include "base/base64/base64_util.h"
#include "frameworks/core/components/declaration/svg/svg_image_declaration.h"
#include "frameworks/base/network/download_manager.h"

namespace OHOS::Ace::NG {

SvgImage::SvgImage() : SvgNode()
{
    declaration_ = AceType::MakeRefPtr<SvgImageDeclaration>();
    declaration_->Init();
    declaration_->InitializeStyle();
}

RefPtr<SvgNode> SvgImage::Create()
{
    return AceType::MakeRefPtr<SvgImage>();
}

void SvgImage::OnDraw(RSCanvas& canvas, const Size& layout, const std::optional<Color>& color)
{
    auto declaration = AceType::DynamicCast<SvgImageDeclaration>(declaration_);
    CHECK_NULL_VOID(declaration);
    if (declaration->GetHref().empty()) {
        LOGW("Svg image href is empty");
        return;
    }

    auto srcType = ParseHrefAttr(declaration->GetHref());
    auto data = std::make_shared<RSData>();
    switch (srcType) {
        case SrcType::BASE64:
            data = LoadBase64Image(declaration->GetHref());
            break;
        case SrcType::ASSET:
            data = LoadLocalImage(declaration->GetHref());
            break;
        default:
            LOGW("Unknown svg href src type");
    }

    CHECK_NULL_VOID(data);
    RSImage image;
    image.MakeFromEncoded(data);

    auto dstRect = RSRect(declaration->GetX().Value(), declaration->GetY().Value(),
        declaration->GetWidth().Value() + declaration->GetX().Value(),
        declaration->GetHeight().Value() + declaration->GetY().Value());
    canvas.DrawImageRect(image, dstRect, RSSamplingOptions());
}

std::shared_ptr<RSData> SvgImage::LoadLocalImage(const std::string& uri)
{
    std::string svgPath = GetImagePath();
    auto realPath = uri;
    auto pos = svgPath.find_last_of('/');
    if (pos != std::string::npos) {
        realPath = svgPath.substr(0, pos + 1) + uri;
    }

    std::string assetSrc(realPath);
    if (assetSrc[0] == '/') {
        assetSrc = assetSrc.substr(1); // get the asset src without '/'.
    } else if (assetSrc[0] == '.' && assetSrc.size() > 2 && assetSrc[1] == '/') { // 2 : min length
        assetSrc = assetSrc.substr(2); // 2 : get the asset src without './'.
    }

    auto pipelineContext = PipelineContext::GetCurrentContext();
    if (!pipelineContext) {
        LOGW("invalid pipeline context");
        return nullptr;
    }
    auto assetManager = pipelineContext->GetAssetManager();
    if (!assetManager) {
        LOGW("No asset manager!");
        return nullptr;
    }

    auto assetData = assetManager->GetAsset(assetSrc);
    if (!assetData) {
        LOGW("No asset data!");
        return nullptr;
    }
    const uint8_t* data = assetData->GetData();
    const size_t dataSize = assetData->GetSize();

    auto drawingData = std::make_shared<RSData>();
    if (!drawingData->BuildWithCopy(data, dataSize)) {
        LOGW("Load local svg image failed!");
    }
    return drawingData;
}

std::shared_ptr<RSData> SvgImage::LoadBase64Image(const std::string& uri)
{
    std::string dst;
    auto iter = uri.find("base64");
    std::string content = uri.substr(iter + 7);
    Base64Util::Decode(content, dst);

    auto data = std::make_shared<RSData>();
    if (!data->BuildWithCopy(dst.c_str(), dst.length())) {
        LOGW("Load base64 svg image failed!");
    }
    return data;
}

SrcType SvgImage::ParseHrefAttr(const std::string& uri)
{
    if (uri.empty()) {
        return SrcType::UNSUPPORTED;
    }
    auto iter = uri.find_first_of(':');
    if (iter == std::string::npos) {
        return SrcType::ASSET;
    }
    std::string head = uri.substr(0, iter);
    std::transform(head.begin(), head.end(), head.begin(), [](unsigned char c) { return std::tolower(c); });
    if (head == "http" || head == "https") {
        return SrcType::NETWORK;
    } else if (head == "data") {
        static constexpr char BASE64_PATTERN[] =
            "^data:image/(jpeg|JPEG|jpg|JPG|png|PNG|ico|ICO|gif|GIF|bmp|BMP|webp|WEBP);base64$";
        if (ImageSourceInfo::IsValidBase64Head(uri, BASE64_PATTERN)) {
            return SrcType::BASE64;
        }
        return SrcType::UNSUPPORTED;
    } else {
        return SrcType::ASSET;
    }
}
} // namespace OHOS::Ace::NG
