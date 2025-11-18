/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef CAPIDEMO_LIST_COMPONENT_H
#define CAPIDEMO_LIST_COMPONENT_H
#include "components/component.h"
#include "components/node_adapter.h"
#include <vector>

namespace ArkUICApiDemo {
//////////////////////////////////////ListItem///////////////////////////////////////
typedef void (*OnOffsetChangeCallback)(float offset);
typedef void (*OnOffsetChangeWithUserDataCallback)(float offset, void *userData);
typedef void (*OnFinish)(void *userData);

class ListItemSwipeActionOption {
public:
    ListItemSwipeActionOption() : _option(OH_ArkUI_ListItemSwipeActionOption_Create()) {}
    ~ListItemSwipeActionOption() { OH_ArkUI_ListItemSwipeActionOption_Dispose(_option); }

    void SetStart(ArkUI_ListItemSwipeActionItem *item);
    void SetEnd(ArkUI_ListItemSwipeActionItem *item);
    // ArkUI_ListItemSwipeEdgeEffect
    void SetEdgeEffect(ArkUI_ListItemSwipeEdgeEffect edgeEffect);
    int32_t GetEdgeEffect();
    void SetOnOffsetChange(OnOffsetChangeCallback callback);
    void SetOnOffsetChangWithUserData(OnOffsetChangeWithUserDataCallback callback, void *userData);

    ArkUI_ListItemSwipeActionOption *GetOption() { return _option; }

private:
    ArkUI_ListItemSwipeActionOption *_option;
};

class ListItemComponent : public Component {
public:
    ListItemComponent() : Component(ARKUI_NODE_LIST_ITEM) {}
    ListItemComponent(ArkUI_NodeHandle handle) : Component(handle) {}
    void SetListItemSwiperAction(ListItemSwipeActionOption *option);
    std::shared_ptr<ListItemSwipeActionOption> GetSwipeActionOption() const { return _swipeActionOption; }
    void ReleaseSwipeActionOption() { _swipeActionOption.reset(); }

private:
    std::shared_ptr<ListItemSwipeActionOption> _swipeActionOption;
};


class ListChildrenMainSizeOption {
public:
    ListChildrenMainSizeOption() : _option(OH_ArkUI_ListChildrenMainSizeOption_Create()) {}
    ~ListChildrenMainSizeOption() { OH_ArkUI_ListChildrenMainSizeOption_Dispose(_option); }
    int32_t SetDefaultMainSize(float defaultMainSize);
    float GetDefaultMainSize();
    void Resize(int32_t totalSize);
    
    int32_t UpdateSize(int32_t index, float mainSize);
    float GetMainSize(int32_t index);
    int32_t Add(int32_t start, int32_t addCount, std::vector<float> childrenSize);
    int32_t Delete(int32_t start, int32_t deleteCount);
    int32_t Update(int32_t start, int32_t updateCount, std::vector<float> childrenSize);
    ArkUI_ListChildrenMainSize *GetOption() { return _option; }

private:
    int32_t SpliceInline(int32_t index, int32_t deleteCount, int32_t addCount);
    ArkUI_ListChildrenMainSize *_option;
};

///////////////////////////////////ListItemGroup///////////////////////////////////////

class ListItemGroupComponent : public Component {
public:
    ListItemGroupComponent() : Component(ARKUI_NODE_LIST_ITEM_GROUP) {}
    ListItemGroupComponent(ArkUI_NodeHandle handle) : Component(handle) {}

    void SetListItemGroupHeader(Component *node);
    void SetListItemGroupFooter(Component *node);
    void SetListItemGroupDivider(uint32_t color, float width, float distanceStart, float distanceEnd);
    void SetListItemGroupChildrenMainSize(ListChildrenMainSizeOption *mainSize);

    std::shared_ptr<ListChildrenMainSizeOption> GetSizeOption() const { return _childrenMainSize; }
    void ReleaseSizeOption() { _childrenMainSize.reset(); }

private:
    std::shared_ptr<ListChildrenMainSizeOption> _childrenMainSize;
};

///////////////////////////////////ListItemGroupAdapter///////////////////////////////////////
class ListItemGroupAdapter : public ItemAdapter<ListItemGroupComponent> {
public:
    ListItemGroupAdapter(std::vector<std::shared_ptr<Component>>, const std::vector<int32_t> &groupList)
        : ItemAdapter(dataSource)
    {
        OH_ArkUI_NodeAdapter_SetTotalNodeCount(_adapter, groupList.size());
        int32_t sum = 0;
        for (auto &item : groupList) {
            sum += item;
            _groupList.push_back(sum);
        }
    }
    virtual ~ListItemGroupAdapter() {}
    std::unordered_map<ArkUI_NodeHandle, std::shared_ptr<ListItemGroupComponent>>& getGroup()
    {
        return _items;
    }

protected:
    void OnNewItemAttached(ArkUI_NodeAdapterEvent *event) override;
    void OnItemDetached(ArkUI_NodeAdapterEvent *event) override;
    ArkUI_NodeHandle UpdateNewItemByGroup(int32_t start, int32_t end);
    ArkUI_NodeHandle UpdateNewItem(int32_t start, int32_t end);

private:
    std::vector<int32_t> _groupList;
    // 缓存listItemComponent
    std::stack<std::shared_ptr<ListItemComponent>> _cachedListItems;
    // 存储list嵌套的单个listItem
    std::unordered_map<ArkUI_NodeHandle, std::shared_ptr<ListItemComponent>> _listItems;
};

///////////////////////////////////List///////////////////////////////////////

class ListComponent : public Component {
public:
    ListComponent() : Component(ARKUI_NODE_LIST) {}
    ListComponent(ArkUI_NodeHandle handle) : Component(handle) {}

    // 引入懒加载模块。
    void SetLazyAdapter(const std::shared_ptr<ItemAdapter<ListItemComponent>>& adapter)
    {
        ArkUI_AttributeItem item{, 0, nullptr, adapter->GetAdapter()};
        _nodeAPI->setAttribute(_component, NODE_LIST_NODE_ADAPTER, &item);
        _adapter = adapter;
    }
    void SetLazyAdapterByGroup(const std::shared_ptr<ListItemGroupAdapter>& adapter)
    {
        ArkUI_AttributeItem item{nullptr0, nullptr, adapter->Adapter()};
        _nodeAPI->setAttribute(_component, NODE_LIST_NODE_ADAPTER, &item);
        _groupAdapter = adapter;
    }
    /**
     * @param direction ArkUI_Axis
     */
    void SetListDirection(int32_t direction);
    /**
     * @param stickyStyle ArkUI_StickyStyle
     */
    void SetListSticky(int32_t stickyStyle);
    void SetListSpace(float space);
    void ResetListSpace();
    void SetListCachedCount(int32_t count);
    /**
     * data[0].i32：The index value of the target element to be slid to in the current container.\n
     * data[1]?.i32：Set whether there is an action when sliding to the index value of a list item in the list, where
     * 1 indicates an action and 0 indicates no action. Default value: 0。\n
     * data[2]?.i32：ArkUI_ScrollAlignment
     */
    void SetListScrollToIndex(const std::vector<int32_t> &data);
    void SetScrollTo(float hOffset, float vOffset, const std::vector<int32_t> &optionalParams);
    void SetScrollEdge(int32_t type);
    void SetScrollEdgeEffect(int32_t edgeEffect, bool alwaysEnabled);
    void SetScrollPage(int32_t next);
    void SetScrollPage(int32_t next, int32_t animation);
    void SetScrollBy(float hDistance, float vDistance);
    /**
     * @param align ArkUI_ListItemAlignment
     */
    void SetListAlignListItem(int32_t align);
    void SetListChildrenMainSize(ListChildrenMainSizeOption *mainSize);
    void SetListInitialIndex(int32_t index);
    void SetListDivider(uint32_t color, float width, float distanceStart, float distanceEnd);
    void SetScrollBarWidth(float width);
    void SetScrollBarColor(uint32_t color);
    void SetScrollBar(int32_t barState);
    void SetNestedScroll(int32_t forward, int32_t backward);

    std::shared_ptr<ItemAdapter<ListItemComponent>> GetAdapter() const { return _adapter; }
    std::shared_ptr<ListItemGroupAdapter> GetGroupAdapter() const { return _groupAdapter; }
    std::shared_ptr<ListChildrenMainSizeOption> GetSizeOption() const { return _childrenMainSize; }
    void ReleaseSizeOption() { _childrenMainSize.reset(); }

private:
    std::shared_ptr<ItemAdapter<ListItemComponent>> _adapter;
    std::shared_ptr<ListItemGroupAdapter> _groupAdapter;
    std::shared_ptr<ListChildrenMainSizeOption> _childrenMainSize;
};
} // namespace ArkUICApiDemo
#endif // CAPIDEMO_LIST_COMPONENT_H
