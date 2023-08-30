/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_SELECTION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_SELECTION_H

#include <list>

#include "base/geometry/offset.h"
#include "base/image/pixel_map.h"
#include "base/memory/ace_type.h"
#include "core/event/ace_events.h"
#include "core/event/axis_event.h"
namespace OHOS::Ace {
enum GetSpansMethod : int32_t {
    GETSPANS,
    ONSELECT,
};

enum RichEditorImageSize : int32_t {
    SIZEWIDTH,
    SIZEHEIGHT,
};

enum RichEditorSpanRange : int32_t {
    RANGESTART,
    RANGEEND,
};

enum RichEditorSpanType : int32_t {
    TYPESPAN,
    TYPEIMAGE,
};

enum class RichEditorType : int32_t {
    TEXT = 0,
    IMAGE,
    MIXED,
};

struct SpanPosition {
    int32_t spanIndex = 0;
    int32_t spanRange[2] = { 0, 0 };
};

struct TextStyleResult {
    std::string fontColor = "";
    double fontSize = 0.0;
    double leadingMargin[2] = { 0.0, 0.0 };
    int32_t fontStyle = 0;
    int32_t textAlign = 0;
    int32_t fontWeight = 0;
    std::string fontFamily = "";
    int32_t decorationType = 0;
    std::string decorationColor = "";
};

struct ImageStyleResult {
    double size[2] = { 0.0, 0.0 };
    int32_t verticalAlign = 0;
    int32_t objectFit = 0;
};

struct ResultObject {
    SpanPosition spanPosition;
    RichEditorSpanType type = RichEditorSpanType::TYPESPAN;
    int32_t offsetInSpan[2] = { 0, 0 };
    std::string valueString = "";
    RefPtr<PixelMap> valuePixelMap;
    TextStyleResult textStyle;
    ImageStyleResult imageStyle;
};

struct Selection {
    int32_t selection[2] = { 0, 0 };
    std::list<ResultObject> resultObjects;
};

class RichEditorSelection : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(RichEditorSelection, BaseEventInfo);

public:
    RichEditorSelection() : BaseEventInfo("RichEditorSelection") {}

    ~RichEditorSelection() = default;

    Selection GetSelection() const
    {
        return selection_;
    }

    void SetSelectionStart(int32_t start)
    {
        selection_.selection[RichEditorSpanRange::RANGESTART] = start;
    }

    void SetSelectionEnd(int32_t end)
    {
        selection_.selection[RichEditorSpanRange::RANGEEND] = end;
    }

    void SetResultObjectList(const std::list<ResultObject>& resultObjectList)
    {
        for (auto& resultObject : resultObjectList) {
            selection_.resultObjects.emplace_back(resultObject);
        }
    }

private:
    Selection selection_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_SELECTION_H
