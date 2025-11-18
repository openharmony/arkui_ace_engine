/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License")
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

#ifndef CAPI0805_2_ARKUILISTNODE_H
#define CAPI0805_2_ARKUILISTNODE_H

#include "ArkUINode.h"

namespace NativeModule {

// 列表节点相关常量定义
namespace ListConstants {
    // 默认主尺寸值
    static constexpr float DEFAULT_MAIN_SIZE = 60.0f;
    
    // 数组操作相关常量
    static constexpr int32_t INITIAL_ARRAY_SIZE = 10;
    static constexpr int32_t SPLICE_START_INDEX = 5;
    static constexpr int32_t SPLICE_DELETE_COUNT = 0;
    static constexpr int32_t SPLICE_INSERT_COUNT = 5;
    
    // 循环范围常量
    static constexpr int32_t LOOP_START_INDEX = 5;
    static constexpr int32_t LOOP_END_INDEX = 10;
    
    // 尺寸设置常量
    static constexpr float ITEM_SIZE = 100.0f;
    static constexpr int32_t TEST_INDEX = 5;
    
    // 属性项数组大小
    static constexpr size_t ATTRIBUTE_ITEM_COUNT = 1;
}

class ArkUIListNode : public ArkUINode {
public:
    ArkUIListNode()
        : ArkUINode((NativeModuleInstance::GetInstance()->GetNativeNodeAPI())->createNode(ARKUI_NODE_LIST)) {}
    
    ~ArkUIListNode() override {}
    
    void SetListItemAlign(int32_t align)
    {
        assert(handle_);
        ArkUI_NumberValue value[] = {{ .i32 = align }};
        ArkUI_AttributeItem item = { value, 1 };
        nativeModule_->setAttribute(handle_, NODE_LIST_ALIGN_LIST_ITEM, &item);
    }
    
    void SetChildrenMainSize(void *mainSize)
    {
        assert(handle_);
        ArkUI_AttributeItem item = { .object = mainSize };
        nativeModule_->setAttribute(handle_, NODE_LIST_CHILDREN_MAIN_SIZE, &item);
    }
    
    std::string SetChildrenMainSizeExample()
    {
        assert(handle_);
        std::string mainSize = "";
        auto childrenMainSize = OH_ArkUI_ListChildrenMainSizeOption_Create();
        
        // 设置默认大小
        auto err = OH_ArkUI_ListChildrenMainSizeOption_SetDefaultMainSize(childrenMainSize,
                                                                          ListConstants::DEFAULT_MAIN_SIZE);
        mainSize += "SetDefaultMainSizeErr: " + std::to_string(err);
        mainSize += "\n";
        
        // 获取默认大小
        auto size = OH_ArkUI_ListChildrenMainSizeOption_GetDefaultMainSize(childrenMainSize);
        mainSize += "defaultMainSize: " + std::to_string(size);
        mainSize += "\n";
        
        // 重置数组大小
        OH_ArkUI_ListChildrenMainSizeOption_Resize(childrenMainSize, ListConstants::INITIAL_ARRAY_SIZE);
        
        // 数组大小+5 此时为15
        err = OH_ArkUI_ListChildrenMainSizeOption_Splice(childrenMainSize,
                                                         ListConstants::SPLICE_START_INDEX,
                                                         ListConstants::SPLICE_DELETE_COUNT,
                                                         ListConstants::SPLICE_INSERT_COUNT);
        mainSize += "spliceErr: " + std::to_string(err);
        mainSize += "\n";
        
        // 从位置5-10处，设置为100
        for (int i = ListConstants::LOOP_START_INDEX; i < ListConstants::LOOP_END_INDEX; i++) {
            err = OH_ArkUI_ListChildrenMainSizeOption_UpdateSize(childrenMainSize, i, ListConstants::ITEM_SIZE);
        }
        mainSize += "UpdateSizeErr: " + std::to_string(err);
        mainSize += "\n";
        
        size = OH_ArkUI_ListChildrenMainSizeOption_GetMainSize(childrenMainSize, ListConstants::TEST_INDEX);
        mainSize += "index [5] size: " + std::to_string(size);
        mainSize += "\n";
        
        SetChildrenMainSize(childrenMainSize);
        OH_ArkUI_ListChildrenMainSizeOption_Dispose(childrenMainSize);
        return mainSize;
    }
};

class ArkUIListItemNode : public ArkUINode {
public:
    ArkUIListItemNode()
        : ArkUINode((NativeModuleInstance::GetInstance()->GetNativeNodeAPI())->createNode(ARKUI_NODE_LIST_ITEM)) {}
    
    ~ArkUIListItemNode() override {}
};

} // namespace NativeModule
#endif // CAPI0805_2_ARKUILISTNODE_H
