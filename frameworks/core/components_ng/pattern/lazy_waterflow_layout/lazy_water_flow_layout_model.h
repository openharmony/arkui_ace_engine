/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_WATERFLOW_LAYOUT_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_WATERFLOW_LAYOUT_MODEL_H

#include <cstdint>
#include <functional>
#include <string>

#include "base/geometry/dimension.h"
#include "base/memory/referenced.h"

namespace OHOS::Ace {

enum class PresetFillType;

namespace NG {

class FrameNode;
class UINode;

class ACE_EXPORT LazyWaterFlowLayoutModel {
public:
    // (startIndex, endIndex). -1 = not visible.
    using VisibleIndexesChangeEvent = std::function<void(int32_t, int32_t)>;

    static void Create();
    static void SetRowGap(const Dimension& space);
    static void SetColumnGap(const Dimension& space);
    static void SetRowGap(FrameNode* frameNode, const Dimension& space);
    static void SetColumnGap(FrameNode* frameNode, const Dimension& space);
    static void SetOnVisibleIndexesChange(VisibleIndexesChangeEvent&& onVisibleIndexesChange);
    static void SetOnVisibleIndexesChange(FrameNode* frameNode, VisibleIndexesChangeEvent&& onVisibleIndexesChange);
};

// Vertical LazyVWaterFlow: adds columnsTemplate / itemFillPolicy.
class ACE_EXPORT LazyVWaterFlowLayoutModel : public LazyWaterFlowLayoutModel {
public:
    // e.g. "1fr 1fr 1fr" or "100px 1fr 100px".
    static void SetColumnsTemplate(const std::string& value);
    static void SetColumnsTemplate(FrameNode* frameNode, const std::string& value);
    // Higher priority than columnsTemplate.
    static void SetItemFillPolicy(PresetFillType policy);
    static void SetItemFillPolicy(FrameNode* frameNode, PresetFillType policy);
    static void ResetItemFillPolicy();
    static void ResetItemFillPolicy(FrameNode* frameNode);
};

} // namespace NG
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_WATERFLOW_LAYOUT_MODEL_H
