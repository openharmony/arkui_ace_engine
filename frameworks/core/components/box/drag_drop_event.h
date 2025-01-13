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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BOX_DRAG_DROP_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BOX_DRAG_DROP_EVENT_H

#include "core/gestures/drag_event.h"
#include "core/pipeline/base/component.h"
#include "frameworks/base/memory/ace_type.h"
#include "frameworks/base/window/drag_window.h"
#include "frameworks/core/gestures/gesture_recognizer.h"
#include "frameworks/core/common/clipboard/clipboard_proxy.h"

namespace OHOS::Ace {

class PipelineContext;
class Component;

/**
 * @brief Used for drag event info.
 */
struct DragItemInfo {
    RefPtr<Component> customComponent;
    RefPtr<PixelMap> pixelMap;
    std::string extraInfo;
};

using OnDragFunc = std::function<DragItemInfo(const RefPtr<DragEvent>&, const std::string&)>;
using OnDropFunc = std::function<void(const RefPtr<DragEvent>&, const std::string&)>;
using UpdateBuilderFunc = std::function<void(const Dimension&, const Dimension&)>;

class DragDropEvent : public virtual AceType {
    DECLARE_ACE_TYPE(DragDropEvent, AceType);

public:
    DragDropEvent() = default;
    ~DragDropEvent() override = default;

    // render
    const OnDragFunc& GetOnDragStart() const
    {
        return onDragStart_;
    }

    const OnDropFunc& GetOnDragEnter() const
    {
        return onDragEnter_;
    }

    const OnDropFunc& GetOnDragMove() const
    {
        return onDragMove_;
    }

    const OnDropFunc& GetOnDragLeave() const
    {
        return onDragLeave_;
    }

    const OnDropFunc& GetOnDrop() const
    {
        return onDrop_;
    }

    void SetPreDragDropNode(const RefPtr<DragDropEvent>& preDragDropNode)
    {
        preDragDropNode_ = preDragDropNode;
    }

    const RefPtr<DragDropEvent>& GetPreDragDropNode() const
    {
        return preDragDropNode_;
    }

    void SetLocalPoint(const Point& localPoint)
    {
        localPoint_ = localPoint;
    }

    const Point& GetLocalPoint() const
    {
        return localPoint_;
    }

    const UpdateBuilderFunc& GetUpdateBuilderFuncId() const
    {
        return updateBuilder_;
    }

    void SetUpdateBuilderFuncId(const UpdateBuilderFunc& updateBuilder)
    {
        updateBuilder_ = updateBuilder;
    }

    void CreateDragDropRecognizer(const WeakPtr<PipelineContext>& pipelineContext);
    void LongPressOnAction(const GestureEvent& info);
    virtual void PanOnActionStart(const GestureEvent& info) = 0;
    virtual void PanOnActionUpdate(const GestureEvent& info) = 0;
    virtual void PanOnActionEnd(const GestureEvent& info) = 0;
    virtual void PanOnActionCancel(const GestureEvent& info) = 0;
    virtual DragItemInfo GenerateDragItemInfo(const RefPtr<PipelineContext>& context, const GestureEvent& info) = 0;
    RefPtr<DragDropEvent> FindDragDropNode(const RefPtr<PipelineContext>& context, const GestureEvent& info);
    virtual void AddDataToClipboard(const RefPtr<PipelineContext>& context, const std::string& extraInfo,
        const std::string& selectedText, const std::string& imageSrc);
    void MergeClipboardData(const RefPtr<PipelineContext>& context, const std::string& newData);
    void RestoreCilpboardData(const RefPtr<PipelineContext>& context);
    Point UpdatePoint(const RefPtr<PipelineContext>& context, const Point& prePoint);

protected:
    RefPtr<GestureRecognizer> dragDropGesture_;
    OnDragFunc onDragStart_;
    OnDropFunc onDragEnter_;
    OnDropFunc onDragMove_;
    OnDropFunc onDragLeave_;
    OnDropFunc onDrop_;
    RefPtr<DragWindow> dragWindow_;
    bool isDragDropNode_ = false;
    bool hasDragItem_ = false;
    RefPtr<DragDropEvent> preDragDropNode_;
    RefPtr<DragDropEvent> initialDragDropNode_;
    Size selectedItemSize_;
    Point localPoint_;
    Point startPoint_;
    UpdateBuilderFunc updateBuilder_;
    std::function<void(const std::string&)> clipboardCallback_ = nullptr;
    std::function<void(const std::string&)> deleteDataCallback_ = nullptr;
    RefPtr<Clipboard> clipboard_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BOX_DRAG_DROP_EVENT_H
