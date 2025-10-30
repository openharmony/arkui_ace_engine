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

#include <arkui/native_node_napi.h>
#include <js_native_api.h>
#include "NativeEntry.h"
#include "examples/guidelineOptionExample.h"
#include "examples/layoutConstraintExample.h"
#include "examples/alignRuleOptionExample.h"
#include "examples/barrierOptionExample.h"
#include "examples/layoutPolicyExample.h"
#include "examples/listChildrenMainSizeExample.h"
#include "examples/itemAlignmentExample.h"
#include "examples/relativeLayoutChainExample.h"
#include "examples/flexExample.h"
#include "examples/stackExample.h"
#include "examples/rowExample.h"
#include "examples/columnExample.h"
#include "examples/layoutPositionExample.h"
#include "examples/safeAreaExample.h"
#include "examples/refreshOffsetChangeExample.h"
#include "examples/positionEdgesExample.h"
#include "examples/pixelRoundExample.h"

namespace NativeModule {

template<typename CreateFuncType>
napi_value CreateNativeRootImpl(napi_env env, napi_callback_info info, CreateFuncType createFunc)
{
    size_t argc = 1;
    napi_value args[1] = {nullptr};
    /* 获取NAPI函数调用参数 */
    if (napi_get_cb_info(env, info, &argc, args, nullptr, nullptr) != napi_ok) {
        return nullptr;
    }
    ArkUI_NodeContentHandle contentHandle;
    /* 从NAPI参数中获取NodeContent句柄 */
    if (OH_ArkUI_GetNodeContentFromNapiValue(env, args[0], &contentHandle) != 0) {
        return nullptr;
    }
    /* 创建指定模块的Native组件 */
    auto node = createFunc();
    /* 设置根节点 */
    NativeEntry::GetInstance()->SetRootNode(contentHandle, node);
    return nullptr;
}

napi_value DestroyNativeRootImpl(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1] = {nullptr};
    if (napi_get_cb_info(env, info, &argc, args, nullptr, nullptr) != napi_ok) {
        return nullptr;
    }
    ArkUI_NodeContentHandle contentHandle;
    if (OH_ArkUI_GetNodeContentFromNapiValue(env, args[0], &contentHandle) != 0) {
        return nullptr;
    }
    NativeEntry::GetInstance()->DisposeRootNode(contentHandle);
    return nullptr;
}

#define DEFINE_CREATE_DESTROY_FUNCTIONS(ModuleName, CreateFunc)                                                        \
    napi_value Create##ModuleName##NativeRoot(napi_env env, napi_callback_info info) {                                 \
        return CreateNativeRootImpl(env, info, CreateFunc);                                                           \
    }                                                                                                                  \
    napi_value Destroy##ModuleName##NativeRoot(napi_env env, napi_callback_info info) {                                \
        return DestroyNativeRootImpl(env, info);                                                                      \
    }

// 布局约束模块
DEFINE_CREATE_DESTROY_FUNCTIONS(LayoutConstraint, CreateLayoutConstraintExample)
// 对齐规则模块
DEFINE_CREATE_DESTROY_FUNCTIONS(AlignRuleOption, CreateAlignRuleOptionExample)
// 引导线模块
DEFINE_CREATE_DESTROY_FUNCTIONS(GuidelineOption, CreateGuidelineOptionExample)
// 障碍物模块
DEFINE_CREATE_DESTROY_FUNCTIONS(BarrierOption, CreateBarrierOptionExample)
// 子元素主尺寸模块
DEFINE_CREATE_DESTROY_FUNCTIONS(ListChildrenMainSize, CreateListChildrenMainSizExample)
// 项目对齐模块
DEFINE_CREATE_DESTROY_FUNCTIONS(ItemAlignment, itemAligmentExample)
// 相对布局链模块
DEFINE_CREATE_DESTROY_FUNCTIONS(RelativeLayoutChain, RelativeLayoutChainExample)
// Flex布局模块
DEFINE_CREATE_DESTROY_FUNCTIONS(Flex, CreateFlexExample)
// Stack布局模块
DEFINE_CREATE_DESTROY_FUNCTIONS(Stack, CreateStackExample)
// Row布局模块
DEFINE_CREATE_DESTROY_FUNCTIONS(Row, CreateRowExample)
// Column布局模块
DEFINE_CREATE_DESTROY_FUNCTIONS(Column, CreateColumnExample)
// 布局位置模块
DEFINE_CREATE_DESTROY_FUNCTIONS(LayoutPosition, CreateLayoutPositionExample)
// 安全区域模块
DEFINE_CREATE_DESTROY_FUNCTIONS(SafeArea, SafeAreaExample)
// 刷新偏移事件模块
DEFINE_CREATE_DESTROY_FUNCTIONS(RefreshOffsetEvent, CreateRefreshOffsetEventExample)
// 布局策略模块
DEFINE_CREATE_DESTROY_FUNCTIONS(LayoutPolicy, CreateLayoutPolicyExample)
// 位置边缘模块
DEFINE_CREATE_DESTROY_FUNCTIONS(PositionEdges, CreatePositionEdgesExample)
// 像素舍入模块
DEFINE_CREATE_DESTROY_FUNCTIONS(PixelRound, CreatePixelRoundExample)

} // namespace NativeModule
