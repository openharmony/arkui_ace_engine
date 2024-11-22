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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIALOG_DIALOG_UTIL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIALOG_DIALOG_UTIL_H

#include "base/memory/referenced.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {

class AgingAdapationDialogUtil {
public:
    static RefPtr<FrameNode> ShowLongPressDialog(const std::string& message, const RefPtr<FrameNode>& iconNode);
    static RefPtr<FrameNode> ShowLongPressDialog(const std::u16string& message, const RefPtr<FrameNode>& iconNode);
    static RefPtr<FrameNode> ShowLongPressDialog(const std::string& message, ImageSourceInfo& imageSourceInfo);
    static RefPtr<FrameNode> ShowLongPressDialog(const std::u16string& message, ImageSourceInfo& imageSourceInfo);
    static float GetDialogBigFontSizeScale();
    static float GetDialogLargeFontSizeScale();
    static float GetDialogMaxFontSizeScale();

private:
    static void CreateDialogTextNode(const RefPtr<FrameNode>& columnNode, const std::u16string& message);
    static RefPtr<FrameNode> CreateCustomDialog(const RefPtr<FrameNode>& columnNode);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIALOG_DIALOG_UTIL_H.