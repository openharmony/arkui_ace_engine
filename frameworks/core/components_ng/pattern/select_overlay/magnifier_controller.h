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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_PATTERN_MAGNIFIER_CONTROLLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_PATTERN_MAGNIFIER_CONTROLLER_H

#include "base/memory/type_info_base.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/render/drawing_forward.h"
#include "frameworks/base/memory/referenced.h"

namespace OHOS::Ace::NG {

class MagnifierController : public virtual AceType {
    DECLARE_ACE_TYPE(MagnifierController, AceType);

public:
    explicit MagnifierController(const WeakPtr<Pattern>& pattern) : pattern_(pattern) {}
    ~MagnifierController() override = default;

    void OpenMagnifier();
    void CloseMagnifier();

    bool UpdateMagnifierOffsetX(OffsetF& magnifierPaintOffset, VectorF& magnifierOffset, const OffsetF& basePaintOffset,
        const RefPtr<FrameNode>& host);
    bool UpdateMagnifierOffsetY(OffsetF& magnifierPaintOffset, VectorF& magnifierOffset, const OffsetF& basePaintOffset,
        const RefPtr<FrameNode>& host);
    bool UpdateMagnifierOffset();

    void UpdateShowMagnifier(bool isShowMagnifier = false);

    bool GetShowMagnifier() const
    {
        return isShowMagnifier_;
    }

    void SetLocalOffset(OffsetF localOffset)
    {
        localOffset_.SetX(localOffset.GetX());
        localOffset_.SetY(localOffset.GetY());
        magnifierNodeExist_ = true;
        UpdateShowMagnifier(true);
    }

    OffsetF GetLocalOffset() const
    {
        return localOffset_;
    }

    RefPtr<FrameNode> GetMagnifierNode() const
    {
        return magnifierFrameNode_;
    }
    void ChangeMagnifierVisibility(const bool& visible);

    void InitMagnifierParams();

    uint32_t ArgbToRgba(const uint32_t& color);

    void RemoveMagnifierFrameNode();

    void SetColorModeChange(const bool& colorModeChange)
    {
        colorModeChange_ = colorModeChange;
    }
    RefPtr<FrameNode> GetRootNode();

    RefPtr<UINode> FindWindowScene(const RefPtr<FrameNode>& targetNode);

    bool GetMagnifierNodeExist() const
    {
        return magnifierNodeExist_;
    }

    void SetHostViewPort(const RectF& viewPort)
    {
        hostViewPort_ = viewPort;
    }
private:
    MagnifierParams params_;
    bool visible_ = false;
    void CreateMagnifierChildNode();
    RefPtr<FrameNode> magnifierFrameNode_ = nullptr;
    bool isShowMagnifier_ = false;
    OffsetF localOffset_;
    WeakPtr<Pattern> pattern_;
    bool removeFrameNode_ = false;
    bool colorModeChange_ = false;
    bool magnifierNodeExist_ = false;
    Dimension magnifierNodeWidth_;
    Dimension magnifierNodeHeight_;
    std::optional<RectF> hostViewPort_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_PATTERN_MAGNIFIER_CONTROLLER_H
