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
#include "frameworks/core/common/container.h"

#include "base/base64/base64_util.h"
#include "core/components_ng/svg/parse/svg_constants.h"
#include "core/image/image_source_info.h"
#include "core/common/ace_application_info.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/core/components_ng/svg/svg_utils.h"

namespace OHOS::Ace::NG {

SvgImage::SvgImage() : SvgNode() {}

RefPtr<SvgNode> SvgImage::Create()
{
    return AceType::MakeRefPtr<SvgImage>();
}

void SvgImage::OnDraw(RSCanvas& canvas, const Size& viewPort, const std::optional<Color>& color)
{
    if (imageAttr_.href.empty()) {
        LOGW("Svg image href is empty");
        return;
    }

    auto x = ConvertDimensionToPx(imageAttr_.x, viewPort, SvgLengthType::HORIZONTAL);
    auto y = ConvertDimensionToPx(imageAttr_.y, viewPort, SvgLengthType::VERTICAL);
    auto width = ConvertDimensionToPx(imageAttr_.width, viewPort, SvgLengthType::HORIZONTAL);
    auto height = ConvertDimensionToPx(imageAttr_.height, viewPort, SvgLengthType::VERTICAL);
    if (LessOrEqual(width, 0.0f) || LessOrEqual(height, 0.0f)) {
        LOGW("Svg image size is illegal");
        return;
    }

    auto srcType = ParseHrefAttr(imageAttr_.href);
    auto data = std::make_shared<RSData>();
    switch (srcType) {
        case SrcType::BASE64:
            data = LoadBase64Image(imageAttr_.href);
            break;
        case SrcType::ASSET:
            data = LoadLocalImage(imageAttr_.href);
            break;
        default:
            LOGW("Unknown svg href src type");
    }
    CHECK_NULL_VOID(data);
    RSImage image;
    image.MakeFromEncoded(data);
    auto dstRect = CalcDstRect(Size(image.GetWidth(), image.GetHeight()), Rect(x, y, width, height));
    canvas.DrawImageRect(image, dstRect, RSSamplingOptions());
}

void SvgImage::OnDraw(RSCanvas& canvas, const SvgLengthScaleRule& lengthRule)
{
    if (imageAttr_.href.empty()) {
        LOGW("Svg image href is empty");
        return;
    }
    auto x = GetMeasuredPosition(imageAttr_.x, lengthRule, SvgLengthType::HORIZONTAL);
    auto y = GetMeasuredPosition(imageAttr_.y, lengthRule, SvgLengthType::VERTICAL);
    auto width = GetMeasuredLength(imageAttr_.width, lengthRule, SvgLengthType::HORIZONTAL);
    auto height = GetMeasuredLength(imageAttr_.height, lengthRule, SvgLengthType::VERTICAL);
    if (LessOrEqual(width, 0.0f) || LessOrEqual(height, 0.0f)) {
        LOGW("Svg image size is illegal");
        return;
    }

    auto srcType = ParseHrefAttr(imageAttr_.href);
    auto data = std::make_shared<RSData>();
    switch (srcType) {
        case SrcType::BASE64:
            data = LoadBase64Image(imageAttr_.href);
            break;
        case SrcType::ASSET:
            data = LoadLocalImage(imageAttr_.href);
            break;
        default:
            LOGW("Unknown svg href src type");
    }
    CHECK_NULL_VOID(data);
    RSImage image;
    image.MakeFromEncoded(data);
    auto dstRect = CalcDstRect(Size(image.GetWidth(), image.GetHeight()), Rect(x, y, width, height));
    canvas.DrawImageRect(image, dstRect, RSSamplingOptions());
}

std::shared_ptr<RSData> SvgImage::LoadLocalImage(const std::string& uri)
{
    std::string svgPath = GetImagePath();
    auto realPath = uri;
    auto dotPos = realPath.find_last_of('.');
    auto format = realPath.substr(dotPos + 1);
    if (format == "svg" || format == "gif") {
        LOGW("Svg image format is not supported");
        return nullptr;
    }
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

RSRect SvgImage::CalcDstRect(const Size& realSize, const Rect& viewBox)
{
    if (NearEqual(realSize.Width(), 0.0f) || NearEqual(realSize.Height(), 0.0f)) {
        return RSRect(0, 0, 0, 0);
    }
    auto scaleX = 0.0f;
    auto scaleY = 0.0f;
    auto offsetX = 0.0f;
    auto offsetY = 0.0f;
    if (!SvgUtils::IsFeatureEnable(SVG_FEATURE_SUPPORT_TWO, GetUsrConfigVersion())) {
        scaleX = std::min(viewBox.Width() / realSize.Width(), viewBox.Height() / realSize.Height());
        scaleY = scaleX;
        auto spaceX = viewBox.Width() - realSize.Width() * scaleX;
        auto spaceY = viewBox.Height() - realSize.Height() * scaleY;
        offsetX = viewBox.Left() + spaceX * 0.5f; // 0.5f Align Center
        offsetY = viewBox.Top() + spaceY * 0.5f; // 0.5f Align Center
        return RSRect(offsetX, offsetY, realSize.Width() * scaleX + offsetX, realSize.Height() * scaleY + offsetY);
    }
    auto translateX = 0.0f;
    auto translateY = 0.0f;
    SvgPreserveAspectRatio preserveAspectRatio;
    SvgAttributesParser::ComputeScale(realSize, viewBox.GetSize(), preserveAspectRatio, scaleX, scaleY);
    SvgAttributesParser::ComputeTranslate(realSize, viewBox.GetSize(), scaleX, scaleY, preserveAspectRatio.svgAlign,
        translateX, translateY);
    offsetX = viewBox.Left() + translateX;
    offsetY = viewBox.Top() + translateY;
    return RSRect(offsetX, offsetY, realSize.Width() * scaleX + offsetX, realSize.Height() * scaleY + offsetY);
}

bool SvgImage::ParseAndSetSpecializedAttr(const std::string& name, const std::string& value)
{
    static const LinearMapNode<void (*)(const std::string&, SvgImageAttribute&)> attrs[] = {
        { SVG_HEIGHT,
            [](const std::string& val, SvgImageAttribute& attr) {
                attr.height = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_HREF,
            [](const std::string& val, SvgImageAttribute& attr) {
                attr.href = val;
            } },
        { SVG_WIDTH,
            [](const std::string& val, SvgImageAttribute& attr) {
                attr.width = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_X,
            [](const std::string& val, SvgImageAttribute& attr) {
                attr.x = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_XLINK_HREF,
            [](const std::string& val, SvgImageAttribute& attr) {
                attr.href = val;
            } },
        { SVG_Y,
            [](const std::string& val, SvgImageAttribute& attr) {
                attr.y = SvgAttributesParser::ParseDimension(val);
            } },
    };
    std::string key = name;
    StringUtils::TransformStrCase(key, StringUtils::TEXT_CASE_LOWERCASE);
    auto attrIter = BinarySearchFindIndex(attrs, ArraySize(attrs), key.c_str());
    if (attrIter != -1) {
        attrs[attrIter].value(value, imageAttr_);
        return true;
    }
    return false;
}

} // namespace OHOS::Ace::NG
