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

#ifndef MYAPPLICATION_NATIVEENTRY_H
#define MYAPPLICATION_NATIVEENTRY_H

#include <nodes/ArkUIBaseNode.h>
#include <arkui/native_type.h>
#include <js_native_api_types.h>
#include <unordered_map>

namespace NativeModule {

// 布局约束相关接口
napi_value CreateLayoutConstraintNativeRoot(napi_env env, napi_callback_info info);
napi_value DestroyLayoutConstraintNativeRoot(napi_env env, napi_callback_info info);

// 对齐规则相关接口
napi_value CreateAlignRuleOptionNativeRoot(napi_env env, napi_callback_info info);
napi_value DestroyAlignRuleOptionNativeRoot(napi_env env, napi_callback_info info);

// 引导线相关接口
napi_value CreateGuidelineOptionNativeRoot(napi_env env, napi_callback_info info);
napi_value DestroyGuidelineOptionNativeRoot(napi_env env, napi_callback_info info);

// 障碍物相关接口
napi_value CreateBarrierOptionNativeRoot(napi_env env, napi_callback_info info);
napi_value DestroyBarrierOptionNativeRoot(napi_env env, napi_callback_info info);

// 子元素主尺寸相关接口
napi_value CreateListChildrenMainSizeNativeRoot(napi_env env, napi_callback_info info);
napi_value DestroyListChildrenMainSizeNativeRoot(napi_env env, napi_callback_info info);

// 项目对齐相关接口
napi_value CreateItemAlignmentNativeRoot(napi_env env, napi_callback_info info);
napi_value DestroyItemAlignmentNativeRoot(napi_env env, napi_callback_info info);

// 相对布局链相关接口
napi_value CreateRelativeLayoutChainNativeRoot(napi_env env, napi_callback_info info);
napi_value DestroyRelativeLayoutChainNativeRoot(napi_env env, napi_callback_info info);

// Flex布局相关接口
napi_value CreateFlexNativeRoot(napi_env env, napi_callback_info info);
napi_value DestroyFlexNativeRoot(napi_env env, napi_callback_info info);

// Stack布局相关接口
napi_value CreateStackNativeRoot(napi_env env, napi_callback_info info);
napi_value DestroyStackNativeRoot(napi_env env, napi_callback_info info);

// Row布局相关接口
napi_value CreateRowNativeRoot(napi_env env, napi_callback_info info);
napi_value DestroyRowNativeRoot(napi_env env, napi_callback_info info);

// Column布局相关接口
napi_value CreateColumnNativeRoot(napi_env env, napi_callback_info info);
napi_value DestroyColumnNativeRoot(napi_env env, napi_callback_info info);

// 布局位置相关接口
napi_value CreateLayoutPositionNativeRoot(napi_env env, napi_callback_info info);
napi_value DestroyLayoutPositionNativeRoot(napi_env env, napi_callback_info info);

// 安全区域相关接口
napi_value CreateSafeAreaNativeRoot(napi_env env, napi_callback_info info);
napi_value DestroySafeAreaNativeRoot(napi_env env, napi_callback_info info);

// 刷新偏移事件相关接口
napi_value CreateRefreshOffsetEventNativeRoot(napi_env env, napi_callback_info info);
napi_value DestroyRefreshOffsetEventNativeRoot(napi_env env, napi_callback_info info);

// 布局策略相关接口
napi_value CreateLayoutPolicyNativeRoot(napi_env env, napi_callback_info info);
napi_value DestroyLayoutPolicyNativeRoot(napi_env env, napi_callback_info info);

// 位置边缘相关接口
napi_value CreatePositionEdgesNativeRoot(napi_env env, napi_callback_info info);
napi_value DestroyPositionEdgesNativeRoot(napi_env env, napi_callback_info info);

// 像素舍入相关接口
napi_value CreatePixelRoundNativeRoot(napi_env env, napi_callback_info info);
napi_value DestroyPixelRoundNativeRoot(napi_env env, napi_callback_info info);

class NativeEntry {
public:
    static NativeEntry *GetInstance()
    {
        static NativeEntry nativeEntry;
        return &nativeEntry;
    }
    
    // 使用 contentHandle 作为 key，支持多个页面
    void SetRootNode(ArkUI_NodeContentHandle contentHandle, const std::shared_ptr<ArkUIBaseNode>& node)
    {
        roots_[contentHandle] = node;
        OH_ArkUI_NodeContent_AddNode(contentHandle, node->GetHandle());
    }

    void DisposeRootNode(ArkUI_NodeContentHandle contentHandle)
    {
        auto it = roots_.find(contentHandle);
        if (it != roots_.end()) {
            OH_ArkUI_NodeContent_RemoveNode(contentHandle, it->second->GetHandle());
            roots_.erase(it);
        }
    }

private:
    std::unordered_map<ArkUI_NodeContentHandle, std::shared_ptr<ArkUIBaseNode>> roots_;
};

} // namespace NativeModule

#endif // MYAPPLICATION_NATIVE_ENTRY_H