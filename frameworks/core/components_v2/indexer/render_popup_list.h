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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_INDEXER_RENDER_POPUP_LIST_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_INDEXER_RENDER_POPUP_LIST_H

#include <functional>
#include <limits>
#include <list>

#include "core/animation/bilateral_spring_adapter.h"
#include "core/animation/simple_spring_chain.h"
#include "core/components/scroll/scroll_edge_effect.h"
#include "core/components/scroll/scrollable.h"
#include "core/components_v2/indexer/indexer_event_info.h"
#include "core/components_v2/indexer/popup_list_component.h"
#include "core/components_v2/indexer/render_popup_list_item.h"
#include "core/gestures/raw_recognizer.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace::V2 {
namespace {
    constexpr int32_t INVALID_POPUP_SELECTED = -1;
    constexpr int32_t MAX_POPUP_DATA_COUNT = 5;             // not support scroll now.
}

class RenderPopupList : public RenderNode {
    DECLARE_ACE_TYPE(V2::RenderPopupList, RenderNode);

public:
    using OnPopupSelectedFunc = std::function<void(std::shared_ptr<IndexerEventInfo>&)>;
    static RefPtr<RenderNode> Create();

    RenderPopupList() = default;
    ~RenderPopupList() = default;

    void Update(const RefPtr<Component>& component) override;
    void PerformLayout() override;
    virtual bool TouchTest(const Point& globalPoint, const Point& parentLocalPoint, const TouchRestrict& touchRestrict,
        TouchTestResult& result) override;

    template<class T>
    T MakeValue(double mainValue, double crossValue) const
    {
        return vertical_ ? T(crossValue, mainValue) : T(mainValue, crossValue);
    }

    double GetMainAxis(const Offset& size) const
    {
        return vertical_ ? size.GetY() : size.GetX();
    }

    void OnRequestPopupDataSelected(std::vector<std::string>& data);
    void OnPopupSelected(int32_t selected) const;

private:
    bool IsValidDisplay();
    void CalTouchPoint(const Point& globalPoint, int32_t& selected);

    bool vertical_ = true;
    int32_t popupSelected_ = INVALID_POPUP_SELECTED;
    RefPtr<RawRecognizer> rawRecognizer_;
    RefPtr<PopupListComponent> component_;
    std::list<RefPtr<RenderPopupListItem>> listItem_;

    OnPopupSelectedFunc popupSelectedEventFun_;

    ACE_DISALLOW_COPY_AND_MOVE(RenderPopupList);
};
} // namespace OHOS::Ace::V2

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_INDEXER_RENDER_POPUP_LIST_H
