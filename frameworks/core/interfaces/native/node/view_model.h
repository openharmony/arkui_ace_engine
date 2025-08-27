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
#ifndef FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_VIEW_MODEL_H
#define FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_VIEW_MODEL_H

#pragma once

#include "core/interfaces/native/node/node_api.h"

#include "core/interfaces/native/node/extension_companion_node.h"

namespace OHOS::Ace::NG::ViewModel {

void* CreateNode(ArkUINodeType tag, ArkUI_Int32 nodeId);

void* CreateNodeWithParams(ArkUINodeType tag, ArkUI_Int32 nodeId, const ArkUI_Params& params);

ArkUI_CharPtr GetName(void* nativePtr);

void DisposeNode(void* nativePtr);

void AddChild(void* parentNode, void* childNode);

void RemoveChild(void* parentNode, void* childNode);

void RemoveChildMultiThread(void* parentNode, void* childNode);

void InsertChildAt(void* parentNode, void* childNode, int32_t position);

void InsertChildAfter(void* parentNode, void* childNode, void* siblingNode);

void InsertChildBefore(void* parentNode, void* childNode, void* siblingNode);

void RegisterCompanion(void* node, int peerId, ArkUI_Int32 flags);

ExtensionCompanionNode* GetCompanion(void* nodePtr);

void SetCustomCallback(ArkUIVMContext context, void* nodePtr, ArkUI_Int32 callback);

void SetCallbackMethod(ArkUIAPICallbackMethod* method);

ArkUIAPICallbackMethod* GetCallbackMethod();

ArkUI_Int32 MeasureNode(ArkUIVMContext context, ArkUINodeHandle nodePtr, ArkUI_Float32* data);

ArkUI_Int32 LayoutNode(ArkUIVMContext context, ArkUINodeHandle nodePtr, ArkUI_Float32  (*data)[2]);

ArkUI_Int32 DrawNode(ArkUIVMContext context, ArkUINodeHandle nodePtr, ArkUI_Float32* data);

void SetAttachNodePtr(ArkUINodeHandle nodePtr, void* attachNode);

void* GetAttachNodePtr(ArkUINodeHandle nodePtr);

ArkUI_Bool IsBuilderNode(void* nodePtr);

void* CreateCustomNode(ArkUI_CharPtr tag);

void* GetOrCreateCustomNode(ArkUI_CharPtr tag);

void* CreateCustomNodeByNodeId(ArkUI_CharPtr tag, ArkUI_Int32 nodeId);

} // namespace OHOS::Ace::NG::ViewModel
#endif
