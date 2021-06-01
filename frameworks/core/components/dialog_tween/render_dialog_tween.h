/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DIALOG_TWEEN_RENDER_DIALOG_TWEEN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DIALOG_TWEEN_RENDER_DIALOG_TWEEN_H

#include "core/animation/animator.h"
#include "core/components/common/layout/grid_layout_info.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components/dialog_tween/dialog_tween_component.h"
#include "core/components/slider/render_slider.h"
#include "core/gestures/click_recognizer.h"
#include "core/gestures/drag_recognizer.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace {

class RenderDialogTween : public RenderNode {
    DECLARE_ACE_TYPE(RenderDialogTween, RenderNode);

public:
    RenderDialogTween();
    ~RenderDialogTween() override;

    static RefPtr<RenderNode> Create();
    void Update(const RefPtr<Component>& component) override;
    void PerformLayout() override;
    void OnPaintFinish() override;
    bool PopDialog();
    void SetAnimator(const RefPtr<Animator>& animator_);

protected:
    void OnTouchTestHit(
        const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result) override;
    void HandleClick(const Offset& clickPosition);
    void UpdateTouchRegion(const Offset& topLeftPoint, const Size& maxSize, const Size& childSize);
    double GetMaxWidthBasedOnGridType(const RefPtr<GridColumnInfo>& info, GridSizeType type, DeviceType deviceType);
    void Initialize();

    bool autoCancel_ = true;
    RefPtr<ClickRecognizer> clickDetector_;
    RefPtr<DragRecognizer> dragDetector_;
    TouchRegion maskTouchRegion_;

private:
    void CallOnSuccess(int32_t successType);
    void InitAccessibilityEventListener();
    void RemoveBackendEvent(const RefPtr<DialogTweenComponent>& component);

    std::function<void(int32_t)> onSuccess_;
    std::function<void()> onCancel_;
    std::function<void()> onComplete_;
    std::function<void()> onPop_;

    std::string data_;
    int32_t composedId_ = 0;
    // used for inspector node in PC preview
    int32_t customDialogId_ = -1;
    double dragStart_ = 0.0;
    RefPtr<Animator> animator_;
    bool isLimit_ = true;
    Edge margin_;
    bool isSetMargin_ = false;
    WeakPtr<DialogTweenComponent> weakDialogTweenComponent_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DIALOG_TWEEN_RENDER_DIALOG_TWEEN_H
