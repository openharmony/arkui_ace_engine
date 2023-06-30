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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_MODEL_H

#include <functional>
#include <mutex>

#include "base/image/pixel_map.h"
#include "base/memory/ace_type.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"

namespace OHOS::Ace {
struct ImageSpanSize {
    CalcDimension width;
    CalcDimension height;
};

struct ImageSpanAttribute {
    std::optional<ImageSpanSize> size;
    std::optional<VerticalAlign> verticalAlign;
    std::optional<ImageFit> objectFit;
};
struct ImageSpanOptions {
    std::optional<int32_t> offset;
    std::optional<std::string> image;
    std::optional<std::string> bundleName;
    std::optional<std::string> moduleName;
    std::optional<RefPtr<PixelMap>> imagePixelMap;
    std::optional<ImageSpanAttribute> imageAttribute;
};

struct SpanPositionInfo {
    SpanPositionInfo(int32_t index, int32_t start, int32_t end, int32_t offset)
        : spanIndex_(index), spanStart_(start), spanEnd_(end), spanOffset_(offset)
    {}

    SpanPositionInfo()
    {
        spanIndex_ = 0;
        spanStart_ = 0;
        spanEnd_ = 0;
        spanOffset_ = 0;
    }

    int32_t spanIndex_ = 0;
    int32_t spanStart_ = 0;
    int32_t spanEnd_ = 0;
    int32_t spanOffset_ = 0;
};

struct TextSpanOptions {
    std::optional<int32_t> offset;
    std::string value;
    std::optional<TextStyle> style;
};

class ACE_EXPORT RichEditorControllerBase : public AceType {
    DECLARE_ACE_TYPE(RichEditorControllerBase, AceType);

public:
    virtual int32_t AddImageSpan(const ImageSpanOptions& options) = 0;
    virtual int32_t AddTextSpan(const TextSpanOptions& options) = 0;
};

class ACE_EXPORT RichEditorModel {
public:
    static RichEditorModel* GetInstance();
    virtual ~RichEditorModel() = default;
    virtual void Create() = 0;
    virtual RefPtr<RichEditorControllerBase> GetRichEditorController() = 0;
    virtual void SetOnReady(std::function<void()>&& func) = 0;

private:
    static std::unique_ptr<RichEditorModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_MODEL_H
