/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ACCESSIBILITY_CAPI_SCENARIO3_NEWS_LIST_H
#define ACCESSIBILITY_CAPI_SCENARIO3_NEWS_LIST_H

#include "ScenarioBase.h"
#include "fakenode/fake_node.h"
#include "fakenode/FakeCustomWidget.h"

namespace NativeXComponentSample {

/**
 * @brief 场景3：新闻列表
 *
 * 演示列表网格、滚动、列表项管理
 * 覆盖接口：11个
 * 测试用例：7个
 */
class Scenario3NewsList : public ScenarioBase {
public:
    Scenario3NewsList();
    ~Scenario3NewsList() override;

    // 实现ScenarioBase接口
    const char* GetId() const override
    {
        return "scenario3_news";
    }

    const char* GetName() const override
    {
        return "新闻列表";
    }

    const char* GetDescription() const override
    {
        return "演示列表网格、滚动、列表项管理（11个接口）";
    }

    void Initialize() override;
    const std::vector<AccessibleObject*>& GetNodes() const override;
    AccessibleObject* GetRootNode() const override;
    AccessibleObject* GetNodeById(int64_t elementId) override;
    bool HandleAction(int64_t elementId, ArkUI_Accessibility_ActionType action) override;
    void Cleanup() override;

    int GetInterfaceCount() const override
    {
        return 11;
    }

    int GetTestCaseCount() const override
    {
        return 7;
    }

private:
    void CreateNodes();
    void ConfigureNodes();

    // 节点指针
    AccessibleObject* rootNode_ = nullptr;
    AccessibleObject* newsList_ = nullptr;

    // 新闻项（20个）
    static const int NEWS_ITEM_COUNT = 20;
    std::vector<AccessibleObject*> newsItems_;

    // 节点列表
    std::vector<AccessibleObject*> nodes_;
    int32_t nextElementId_ = 1;

    // 状态管理
    int32_t currentItemIndex_ = 0;
    int32_t startItemIndex_ = 0;
    int32_t endItemIndex_ = 9;  // 每次显示10个

    // 元素ID分配
    int32_t AllocateElementId()
    {
        return nextElementId_++;
    }

    // 更新列表选择状态
    void UpdateSelectionState()
    {
        if (newsList_) {
            // 设置列表的网格信息
            ArkUI_AccessibleGridInfo gridInfo;
            gridInfo.rowCount = 20;  // 总共20个新闻
            gridInfo.columnCount = 1;  // 单列布局
            gridInfo.selectionMode = 0;  // 单选模式
            newsList_->SetGridInfo(gridInfo);

            // 设置当前项索引
            newsList_->SetCurrentItemIndex(currentItemIndex_);

            // 设置可见范围
            newsList_->SetStartItemIndex(startItemIndex_);
            newsList_->SetEndItemIndex(endItemIndex_);

            // 设置项目总数
            newsList_->SetItemCount(NEWS_ITEM_COUNT);
        }
    }
};

} // namespace NativeXComponentSample

#endif // ACCESSIBILITY_CAPI_SCENARIO3_NEWS_LIST_H
