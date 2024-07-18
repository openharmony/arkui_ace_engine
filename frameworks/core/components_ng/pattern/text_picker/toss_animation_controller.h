/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TOSS_ANIMATION_CONTROLLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TOSS_ANIMATION_CONTROLLER_H

#include "core/components/picker/picker_animation.h"
#include "core/components_ng/base/frame_node.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/base/memory/ace_type.h"

namespace OHOS::Ace::NG {
class TextPickerColumnPattern;

class TextPickerTossAnimationController : public virtual AceType {
    DECLARE_ACE_TYPE(TextPickerTossAnimationController, AceType);

public:
    TextPickerTossAnimationController() = default;
    ~TextPickerTossAnimationController() = default;

    void SetColumn(const WeakPtr<TextPickerColumnPattern>& value)
    {
        column_ = value;
    }

    void SetPipelineContext(const WeakPtr<PipelineContext>& pipeline)
    {
        pipeline_ = pipeline;
    }

    void SetStart(double y);

    void SetEnd(double y);

    bool Play();

    RefPtr<NodeAnimatablePropertyFloat> GetTossNodeAnimation() const
    {
        return property_;
    }

    void StartSpringMotion();

    RefPtr<Curve> UpdatePlayAnimationValue();

    void StopTossAnimation();

    double GetTossEndPosition() const
    {
        return end_;
    }

    double GetTossOffset() const;

    bool GetTossPlaying() const;
    void SetTossPlaying(bool playing);
private:
    double GetCurrentTime() const;
    void CreatePropertyCallback();

    double yStart_ = 0.0;
    double yEnd_ = 0.0;
    double timeStart_ = 0.0;
    double timeEnd_ = 0.0;
    double speed_ = 0.0;
    int32_t showCount_ = 0;
    double end_ = 0.0;
    bool isManualStopToss_ = false;
    bool isTossPlaying_ = false;
    WeakPtr<TextPickerColumnPattern> column_;
    WeakPtr<PipelineContext> pipeline_;
    RefPtr<NodeAnimatablePropertyFloat> property_;

    ACE_DISALLOW_COPY_AND_MOVE(TextPickerTossAnimationController);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TOSS_ANIMATION_CONTROLLER_H
