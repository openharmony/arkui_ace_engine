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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_DRAG_RICH_EDITOR_DRAG_CONTENT_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_DRAG_RICH_EDITOR_DRAG_CONTENT_MODIFIER_H

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/modifier.h"

namespace OHOS::Ace::NG {
class RichEditorDragContentModifier : public ContentModifier {
    DECLARE_ACE_TYPE(RichEditorDragContentModifier, ContentModifier);

public:
    RichEditorDragContentModifier() = default;
    ~RichEditorDragContentModifier() override = default;

    void onDraw(DrawingContext& context) override {}

private:
    ACE_DISALLOW_COPY_AND_MOVE(RichEditorDragContentModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_DRAG_RICH_EDITOR_DRAG_CONTENT_MODIFIER_H
