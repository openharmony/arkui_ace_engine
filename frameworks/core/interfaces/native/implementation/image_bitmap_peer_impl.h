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
#pragma once

#include "base/utils/utils.h"
#include "base/memory/referenced.h"
#include "core/components_ng/image_provider/image_loading_context.h"
#include "core/components/common/properties/paint_state.h"

struct ImageBitmapPeer {
public:
    ImageBitmapPeer();
    virtual ~ImageBitmapPeer() = default;

    void Close();
    double GetHeight();
    double GetWidth();

    void LoadImage(const std::string& src);

private:
    void LoadImage(const OHOS::Ace::ImageSourceInfo& sourceInfo);

    void OnImageDataReady();
    void OnImageLoadFail(const std::string& errorMsg);

protected:
    void SetHeight(double value) { height = value; }
    void SetWidth(double value) { width = value; }
    void SetCloseCallback(std::function<void()>&& callback);

private:
    double width;
    double height;
    OHOS::Ace::RefPtr<OHOS::Ace::NG::ImageLoadingContext> loadingCtx_;
    std::list<std::function<void()>> closeCallbacks_;
};
