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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_STRATIFIED_IMAGE_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_STRATIFIED_IMAGE_H

#include <memory>
#include <string>
namespace OHOS::Ace::Napi {
namespace Media {
class PixelMap;
} // namespace Media

class ImageBase {
public:
    ImageBase() = default;
    explicit ImageBase(std::string src) : src_(std::move(src)) {}
    virtual std::unique_ptr<Media::PixelMap> GetPixmap() = 0;

private:
    std::string src_;
};

class StratifiedImage : public virtual ImageBase {
public:
    StratifiedImage(std::string foreground, std::string background)
        : foreground_(std::move(foreground)), background_(std::move(background))
    {}
    // construct from json buffer
    explicit StratifiedImage(std::unique_ptr<uint8_t*>& jsonBuf);

    ~StratifiedImage() = default;

    void UpdateMask(const std::string& mask);

    std::string GetForeground();
    std::string GetBackground();
    std::string GetMask();

    std::unique_ptr<Media::PixelMap> GetPixmap() override;

    std::unique_ptr<Media::PixelMap> GetForegroundPixmap();
    std::unique_ptr<Media::PixelMap> GetBackgroundPixmap();
    std::unique_ptr<Media::PixelMap> GetMaskPixmap();

private:
    std::string foreground_;
    std::string background_;
    std::string mask_;
};
} // namespace OHOS::Ace::Napi
#endif // #define FOUNDATION_ACE_INTERFACE_INNERKITS_STRATIFIED_IMAGE_H
