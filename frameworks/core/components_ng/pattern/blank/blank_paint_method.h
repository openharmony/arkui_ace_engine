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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_Blank_Blank_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_Blank_Blank_PAINT_METHOD_H

#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components_ng/render/paint_wrapper.h"
namespace OHOS::Ace::NG {
class ACE_EXPORT BlankPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(BlankPaintMethod, NodePaintMethod)
public:
    BlankPaintMethod() = default;
    ~BlankPaintMethod() override = default;

    CanvasDrawFunction GetContentDrawFunction(PaintWrapper* paintWrapper) override
    {
        return [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
            auto blank = weak.Upgrade();
            if (blank) {
                blank->PaintRect(canvas, paintWrapper);
            }
        };
    }

    void PaintRect(RSCanvas& canvas, PaintWrapper* paintWrapper);

private:
#ifndef USE_ROSEN_DRAWING
    RSPath path_;
#else
    RSRecordingPath path_;
#endif

    ACE_DISALLOW_COPY_AND_MOVE(BlankPaintMethod);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_Blank_Blank_PAINT_METHOD_H