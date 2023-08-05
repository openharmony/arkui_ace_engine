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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_MODEL_H

#include <mutex>

#include "core/components/scroll/scroll_controller_base.h"
#include "core/components/scroll_bar/scroll_proxy.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"

namespace OHOS::Ace {
class WaterFlowModel {
public:
    static WaterFlowModel* GetInstance();
    virtual ~WaterFlowModel() = default;

    virtual void Create() = 0;
    virtual void SetFooter(std::function<void()>&& footer) = 0;
    virtual RefPtr<ScrollControllerBase> CreateScrollController() = 0;
    virtual RefPtr<ScrollProxy> CreateScrollBarProxy() = 0;
    virtual void SetScroller(RefPtr<ScrollControllerBase> scroller, RefPtr<ScrollProxy> proxy) = 0;

    virtual void SetColumnsTemplate(const std::string& value) = 0;
    virtual void SetRowsTemplate(const std::string& value) = 0;

    // itemConstraintSize
    virtual void SetItemMinWidth(const Dimension& minWidth) = 0;
    virtual void SetItemMinHeight(const Dimension& minHeight) = 0;
    virtual void SetItemMaxWidth(const Dimension& maxWidth) = 0;
    virtual void SetItemMaxHeight(const Dimension& maxHeight) = 0;

    virtual void SetColumnsGap(const Dimension& value) = 0;
    virtual void SetRowsGap(const Dimension& value) = 0;

    virtual void SetLayoutDirection(FlexDirection value) = 0;
    virtual void SetNestedScroll(const NestedScrollOptions& nestedOpt) = 0;
    virtual void SetScrollEnabled(bool scrollEnabled) = 0;

    virtual void SetOnReachStart(OnReachEvent&& onReachStart) = 0;
    virtual void SetOnReachEnd(OnReachEvent&& onReachEnd) = 0;
    virtual void SetOnScrollFrameBegin(OnScrollFrameBeginEvent&& ScrollFrameBegin) = 0;
    virtual void SetFriction(double friction) = 0;

private:
    static std::unique_ptr<WaterFlowModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_MODEL_H
