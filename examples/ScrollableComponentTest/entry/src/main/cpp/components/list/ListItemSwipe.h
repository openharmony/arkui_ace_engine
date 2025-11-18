/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef SCROLLABLE_COMPONENTS_LIST_ITEM_SWIPE_H
#define SCROLLABLE_COMPONENTS_LIST_ITEM_SWIPE_H

#include <functional>

#include <arkui/native_node.h>
#include <arkui/native_type.h>
#include <hilog/log.h>

#ifndef LOG_TAG
#define LOG_TAG "ListItemSwipe"
#endif

/**
 * 轻量封装：为 ARKUI_NODE_LIST_ITEM 配置 Swipe Action（左右动作区、阈值、回调等）
 */
class ListItemSwipe {
public:
    explicit ListItemSwipe(ArkUI_NativeNodeAPI_1 *api) : api_(api)
    {
    }
    ~ListItemSwipe()
    {
        if (option_) {
            OH_ArkUI_ListItemSwipeActionOption_Dispose(option_);
            option_ = nullptr;
        }
        if (startItem_) {
            OH_ArkUI_ListItemSwipeActionItem_Dispose(startItem_);
            startItem_ = nullptr;
        }
        if (endItem_) {
            OH_ArkUI_ListItemSwipeActionItem_Dispose(endItem_);
            endItem_ = nullptr;
        }
    }

    // ====== 构建左右动作区 ======
    ListItemSwipe &BuildStartArea(const std::function<ArkUI_NodeHandle(ArkUI_NativeNodeAPI_1 *)> &builder)
    {
        EnsureOption();
        if (!startItem_) {
            startItem_ = OH_ArkUI_ListItemSwipeActionItem_Create();
        }
        ArkUI_NodeHandle node = builder ? builder(api_) : nullptr;
        OH_ArkUI_ListItemSwipeActionItem_SetContent(startItem_, node);
        OH_ArkUI_ListItemSwipeActionOption_SetStart(option_, startItem_);
        return *this;
    }

    ListItemSwipe &BuildEndArea(const std::function<ArkUI_NodeHandle(ArkUI_NativeNodeAPI_1 *)> &builder)
    {
        EnsureOption();
        if (!endItem_) {
            endItem_ = OH_ArkUI_ListItemSwipeActionItem_Create();
        }
        ArkUI_NodeHandle node = builder ? builder(api_) : nullptr;
        OH_ArkUI_ListItemSwipeActionItem_SetContent(endItem_, node);
        OH_ArkUI_ListItemSwipeActionOption_SetEnd(option_, endItem_);
        return *this;
    }

    // ====== 阈值（长距离删除阈值） ======
    ListItemSwipe &SetActionAreaDistance(float distance)
    {
        EnsureStartEnd();
        if (startItem_) {
            OH_ArkUI_ListItemSwipeActionItem_SetActionAreaDistance(startItem_, distance);
        }
        if (endItem_) {
            OH_ArkUI_ListItemSwipeActionItem_SetActionAreaDistance(endItem_, distance);
        }
        return *this;
    }

    float GetActionAreaDistanceStart() const
    {
        if (startItem_) {
            return OH_ArkUI_ListItemSwipeActionItem_GetActionAreaDistance(startItem_);
        }
        return -1.0f;
    }

    float GetActionAreaDistanceEnd() const
    {
        if (endItem_) {
            return OH_ArkUI_ListItemSwipeActionItem_GetActionAreaDistance(endItem_);
        }
        return -1.0f;
    }

    // ====== 进入/退出/触发/状态变化 ======
    ListItemSwipe &OnEnter(const std::function<void()> &cb)
    {
        EnsureStartEnd();
        enter_ = cb;
        if (startItem_) {
            OH_ArkUI_ListItemSwipeActionItem_SetOnEnterActionArea(startItem_, &ThunkEnter);
        }
        if (endItem_) {
            OH_ArkUI_ListItemSwipeActionItem_SetOnEnterActionArea(endItem_, &ThunkEnter);
        }
        return *this;
    }

    ListItemSwipe &OnExit(const std::function<void()> &cb)
    {
        EnsureStartEnd();
        exit_ = cb;
        if (startItem_) {
            OH_ArkUI_ListItemSwipeActionItem_SetOnExitActionArea(startItem_, &ThunkExit);
        }
        if (endItem_) {
            OH_ArkUI_ListItemSwipeActionItem_SetOnExitActionArea(endItem_, &ThunkExit);
        }
        return *this;
    }

    ListItemSwipe &OnAction(const std::function<void()> &cb)
    {
        EnsureStartEnd();
        action_ = cb;
        if (startItem_) {
            OH_ArkUI_ListItemSwipeActionItem_SetOnAction(startItem_, &ThunkAction);
        }
        if (endItem_) {
            OH_ArkUI_ListItemSwipeActionItem_SetOnAction(endItem_, &ThunkAction);
        }
        return *this;
    }

    ListItemSwipe &OnStateChange(const std::function<void(int /*state*/)> &cb)
    {
        EnsureStartEnd();
        state_ = cb;
        if (startItem_) {
            OH_ArkUI_ListItemSwipeActionItem_SetOnStateChange(startItem_, &ThunkState);
        }
        if (endItem_) {
            OH_ArkUI_ListItemSwipeActionItem_SetOnStateChange(endItem_, &ThunkState);
        }
        return *this;
    }

    ListItemSwipe &OnEnterWithUserData(const std::function<void(void *ud)> &cb)
    {
        EnsureStartEnd();
        enterUD_ = cb;
        if (startItem_) {
            OH_ArkUI_ListItemSwipeActionItem_SetOnEnterActionAreaWithUserData(startItem_, this, &ThunkEnterUD);
        }
        if (endItem_) {
            OH_ArkUI_ListItemSwipeActionItem_SetOnEnterActionAreaWithUserData(endItem_, this, &ThunkEnterUD);
        }
        return *this;
    }

    ListItemSwipe &OnExitWithUserData(const std::function<void(void *ud)> &cb)
    {
        EnsureStartEnd();
        exitUD_ = cb;
        if (startItem_) {
            OH_ArkUI_ListItemSwipeActionItem_SetOnExitActionAreaWithUserData(startItem_, this, &ThunkExitUD);
        }
        if (endItem_) {
            OH_ArkUI_ListItemSwipeActionItem_SetOnExitActionAreaWithUserData(endItem_, this, &ThunkExitUD);
        }
        return *this;
    }

    ListItemSwipe &OnActionWithUserData(const std::function<void(void *ud)> &cb)
    {
        EnsureStartEnd();
        actionUD_ = cb;
        if (startItem_) {
            OH_ArkUI_ListItemSwipeActionItem_SetOnActionWithUserData(startItem_, this, &ThunkActionUD);
        }
        if (endItem_) {
            OH_ArkUI_ListItemSwipeActionItem_SetOnActionWithUserData(endItem_, this, &ThunkActionUD);
        }
        return *this;
    }

    ListItemSwipe &OnStateChangeWithUserData(const std::function<void(int, void *ud)> &cb)
    {
        EnsureStartEnd();
        stateUD_ = cb;
        if (startItem_) {
            OH_ArkUI_ListItemSwipeActionItem_SetOnStateChangeWithUserData(startItem_, this, &ThunkStateUD);
        }
        if (endItem_) {
            OH_ArkUI_ListItemSwipeActionItem_SetOnStateChangeWithUserData(endItem_, this, &ThunkStateUD);
        }
        return *this;
    }

    // ====== Edge Effect / Offset 回调 ======
    ListItemSwipe &SetEdgeEffect(int edgeEffect /*ArkUI_ListItemSwipeEdgeEffect*/)
    {
        EnsureOption();
        OH_ArkUI_ListItemSwipeActionOption_SetEdgeEffect(option_,
                                                         static_cast<ArkUI_ListItemSwipeEdgeEffect>(edgeEffect));
        return *this;
    }

    int GetEdgeEffect() const
    {
        if (option_) {
            return OH_ArkUI_ListItemSwipeActionOption_GetEdgeEffect(option_);
        }
        return -1;
    }

    ListItemSwipe &OnOffsetChange(const std::function<void(float)> &cb)
    {
        EnsureOption();
        offset_ = cb;
        OH_ArkUI_ListItemSwipeActionOption_SetOnOffsetChange(option_, &ThunkOffset);
        return *this;
    }

    ListItemSwipe &OnOffsetChangeWithUserData(const std::function<void(float, void *ud)> &cb)
    {
        EnsureOption();
        offsetUD_ = cb;
        OH_ArkUI_ListItemSwipeActionOption_SetOnOffsetChangeWithUserData(option_, this, &ThunkOffsetUD);
        return *this;
    }

    // ====== 挂载到指定 LIST_ITEM 节点 ======
    void AttachToListItem(ArkUI_NodeHandle listItem)
    {
        if (!api_ || !listItem) {
            return;
        }
        EnsureOption();
        ArkUI_AttributeItem it{nullptr, 0, nullptr, option_};
        api_->setAttribute(listItem, NODE_LIST_ITEM_SWIPE_ACTION, &it);

        (void)GetActionAreaDistanceStart();
        (void)GetActionAreaDistanceEnd();
        (void)GetEdgeEffect();
    }

private:
    void EnsureOption()
    {
        if (!option_) {
            option_ = OH_ArkUI_ListItemSwipeActionOption_Create();
        }
    }

    void EnsureStartEnd()
    {
        EnsureOption();
        if (!startItem_) {
            startItem_ = OH_ArkUI_ListItemSwipeActionItem_Create();
        }
        if (!endItem_) {
            endItem_ = OH_ArkUI_ListItemSwipeActionItem_Create();
        }
        OH_ArkUI_ListItemSwipeActionOption_SetStart(option_, startItem_);
        OH_ArkUI_ListItemSwipeActionOption_SetEnd(option_, endItem_);
    }

    static void ThunkEnter()
    {
    }
    static void ThunkExit()
    {
    }
    static void ThunkAction()
    {
    }
    static void ThunkState(ArkUI_ListItemSwipeActionState state)
    {
        (void)state;
    }
    static void ThunkOffset(float offset)
    {
        (void)offset;
    }

    static void ThunkEnterUD(void *ud)
    {
        if (auto *self = static_cast<ListItemSwipe *>(ud); self && self->enterUD_) {
            self->enterUD_(ud);
        }
    }

    static void ThunkExitUD(void *ud)
    {
        if (auto *self = static_cast<ListItemSwipe *>(ud); self && self->exitUD_) {
            self->exitUD_(ud);
        }
    }

    static void ThunkActionUD(void *ud)
    {
        if (auto *self = static_cast<ListItemSwipe *>(ud); self && self->actionUD_) {
            self->actionUD_(ud);
        }
    }

    static void ThunkStateUD(ArkUI_ListItemSwipeActionState state, void *ud)
    {
        if (auto *self = static_cast<ListItemSwipe *>(ud); self && self->stateUD_) {
            self->stateUD_(static_cast<int>(state), ud);
        }
        if (auto *self2 = static_cast<ListItemSwipe *>(ud); self2 && self2->state_) {
            self2->state_(static_cast<int>(state));
        }
    }

    static void ThunkOffsetUD(float offset, void *ud)
    {
        if (auto *self = static_cast<ListItemSwipe *>(ud); self && self->offsetUD_) {
            self->offsetUD_(offset, ud);
        }
    }

private:
    ArkUI_NativeNodeAPI_1 *api_{nullptr};

    ArkUI_ListItemSwipeActionItem *startItem_{nullptr};
    ArkUI_ListItemSwipeActionItem *endItem_{nullptr};
    ArkUI_ListItemSwipeActionOption *option_{nullptr};

    // 无 userData 回调
    std::function<void()> enter_;
    std::function<void()> exit_;
    std::function<void()> action_;
    std::function<void(int)> state_;
    std::function<void(float)> offset_;

    // 带 userData 回调
    std::function<void(void *)> enterUD_;
    std::function<void(void *)> exitUD_;
    std::function<void(void *)> actionUD_;
    std::function<void(int, void *)> stateUD_;
    std::function<void(float, void *)> offsetUD_;
};

#endif // SCROLLABLE_COMPONENTS_LIST_ITEM_SWIPE_H
