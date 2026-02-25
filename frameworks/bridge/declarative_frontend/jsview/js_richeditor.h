/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_RICHEDITOR_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_RICHEDITOR_H

#include "base/utils/device_config.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_event_hub.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model.h"
#include "core/components_ng/pattern/text/span/span_string.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"

namespace OHOS::Ace::Framework {
class JSRichEditorBaseController : public Referenced {
public:
    virtual void SetController(const RefPtr<RichEditorBaseControllerBase>& controller);
    void CloseSelectionMenu();
    void StopEditing();
    bool FontSizeRangeIsNegative(const CalcDimension& size);

    void SetInstanceId(int32_t id)
    {
        instanceId_ = id;
    }

    void SetStyledStringMode(bool isStyledStringMode)
    {
        isStyledStringMode_ = isStyledStringMode;
    }

    bool IsStyledStringMode()
    {
        return isStyledStringMode_;
    }

    ColorMode GetColorMode()
    {
        auto controller = controllerWeak_.Upgrade();
        CHECK_NULL_RETURN(controller, ColorMode::COLOR_MODE_UNDEFINED);
        return controller->GetColorMode();
    }

    void SetPlaceholderStyledStringCache(const RefPtr<SpanString>& styledString)
    {
        placeholderStyledString_ = styledString;
    }

    RefPtr<SpanString> GetPlaceholderStyledStringCache() const
    {
        return placeholderStyledString_;
    }

protected:
    friend class JSRichEditorBaseControllerBinding;
    int32_t instanceId_ = INSTANCE_ID_UNDEFINED;
    WeakPtr<RichEditorBaseControllerBase> controllerWeak_;
    struct UpdateSpanStyle typingStyle_;
    bool isStyledStringMode_ = false;

private:
    RefPtr<SpanString> placeholderStyledString_;
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_RICHEDITOR_H
