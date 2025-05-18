/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import { int32 } from "@koalaui/common"
import { contextNode, remember, scheduleCallback } from "@koalaui/runtime"
import { PeerNode, PeerNodeType } from "../PeerNode"
import { CallbackTransformer } from "../component/peers/CallbackTransformer"
import { KPointer } from "@koalaui/interop"
import { ArkCommonMethodPeer, CommonMethod, DragDropOps, DragEvent, CustomBuilder, DragItemInfo } from '../component'
import { InteropNativeModule, runtimeType, RuntimeType, toPeerPtr} from "@koalaui/interop"
import { ArkCommonAttributeSet } from "./modifiers/ArkCommonModifier";
import { ArkUIAniModule } from "arkui.ani"
import { CustomNodeBuilder } from "../component/customBuilder"
import { createUiDetachedRoot } from "../ArkUIEntry"
import { ArkComponentRootPeer } from "../component";

export function hookRegisterOnDragStartImpl(node: ArkCommonMethodPeer, onDragStartCallback: (((event: DragEvent, extraParams?: string) => CustomBuilder | DragItemInfo) | undefined)): void {
    DragDropOps.registerOnDragStart(node.getPeerPtr(), (node: KPointer, dragEvent: DragEvent, extraParam: string) => {
        if (onDragStartCallback === undefined) {
            return
        }
        const value_dragEvent = (dragEvent as DragEvent)
        const value_extraParam = (extraParam as string)
        let res: CustomBuilder | DragItemInfo = onDragStartCallback(value_dragEvent, value_extraParam)
        const value_type = runtimeType(res)
        if (RuntimeType.FUNCTION === value_type) {
            const value_builder = res as CustomBuilder
            const peerNode = createUiDetachedRoot((): PeerNode  => {
                return ArkComponentRootPeer.create(undefined)
            }, value_builder)
            const createBuilderNodeTree = () : KPointer => {
                return peerNode.peer.ptr
            }
            let customNode = createBuilderNodeTree();
            ArkUIAniModule._DragEvent_Set_CustomNode(toPeerPtr(dragEvent), customNode)
        } else if (RuntimeType.OBJECT === value_type) {
            const itemInfo = res as DragItemInfo
            const value_extraInfo = itemInfo.extraInfo
            let value_extraInfo_type: int32 = RuntimeType.UNDEFINED
            value_extraInfo_type = runtimeType(value_extraInfo)
            if ((RuntimeType.UNDEFINED) != (value_extraInfo_type)) {
                const value_extraInfo_value = value_extraInfo!
                ArkUIAniModule._DragEvent_Set_ExtraInfo(toPeerPtr(dragEvent), value_extraInfo_value)
            }

            const value_builder = itemInfo.builder as CustomBuilder
            const peerNode = createUiDetachedRoot((): PeerNode  => {
                return ArkComponentRootPeer.create(undefined)
            }, value_builder)
            const createBuilderNodeTree = () : KPointer => {
                return peerNode.peer.ptr
            }
            let customNode = createBuilderNodeTree();
            ArkUIAniModule._DragEvent_Set_CustomNode(toPeerPtr(dragEvent), customNode)
        }
    })
}