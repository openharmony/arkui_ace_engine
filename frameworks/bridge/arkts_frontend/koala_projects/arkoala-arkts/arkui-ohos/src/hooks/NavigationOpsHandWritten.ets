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

import { SerializerBase, runtimeType, RuntimeType, InteropNativeModule } from "@koalaui/interop"
import { ArkUIGeneratedNativeModule } from "#components"
import { NavPathStack, ArkNavigationComponent, NavPathStack_serializer } from "../component/navigation"
import { NavExtender } from "../component/idlize"
import { int32 } from "@koalaui/common"
import { addPartialUpdate, createUiDetachedRoot } from "../ArkUIEntry"
import { PeerNode } from "../PeerNode"
import { ArkStackComponent, ArkStackPeer } from "../component/stack"
import { __context } from "@koalaui/runtime"
import { PageMapBuilder } from "../component/builder"
import { setNeedCreate } from "../ArkComponentRoot"
import { ObserveSingleton } from "../stateManagement/base/observeSingleton"
import { ExtendableComponent } from "../component/extendableComponent"

export class NavigationOpsHandWritten {
    static hookSetNavigationOptionsImpl(component: ArkNavigationComponent, pathInfos?: NavPathStack) {
        let info: NavPathStack = new NavPathStack();
        const pathInfos_type = runtimeType(pathInfos)
        if (pathInfos_type != RuntimeType.UNDEFINED) {
            info = pathInfos!
        }
        
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (pathInfos !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const pathInfosTmpValue  = pathInfos!
            NavPathStack_serializer.write(thisSerializer, pathInfosTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        let peerPtr = component.getPeer().peer.ptr
        ArkUIGeneratedNativeModule._NavigationInterface_setNavigationOptions(peerPtr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()

        if (pathInfos != undefined) {
            const currentRenderingComponent = ObserveSingleton.instance.renderingComponent;
            const currentExtendableComponent = ExtendableComponent.current;
            const updater: (name: string, param: object|null|undefined)=>PeerNode =
            (name: string, param: object|null|undefined) => {
                return createUiDetachedRoot((): PeerNode => ArkStackPeer.create(new ArkStackComponent()), () => {
                    setNeedCreate(true)
                    const lastRenderingComponent = ObserveSingleton.instance.renderingComponent;
                    const lastExtendableComponent = ExtendableComponent.current;
                    ObserveSingleton.instance.renderingComponent = currentRenderingComponent;
                    ExtendableComponent.current = currentExtendableComponent;
                    component._navDestination(name, param);
                    setNeedCreate(false)
                    ObserveSingleton.instance.renderingComponent = lastRenderingComponent;
                    ExtendableComponent.current = lastExtendableComponent;
                })
            }
            const value_casted = updater as ((name: string, param: object|null|undefined) => PeerNode)
            NavExtender.setUpdateStackCallback(pathInfos!, () => {
                addPartialUpdate(() => {
                    if (!component.isNeedSync()) {
                        return
                    }
                    InteropNativeModule._NativeLog("AceNavigation: sync navigation stack")
                    component.updateNeedSync(false)
                    let size: int32 = pathInfos!.size() as int32
                    InteropNativeModule._NativeLog("AceNavigation: path stack size: " + size)
                    let names: Array<string> = pathInfos!.getAllPathName()
                    for (let index: int32 = 0; index < size; index++) {
                        if (NavExtender.checkNeedCreate(peerPtr, index)) {
                            InteropNativeModule._NativeLog("AceNavigation: create new node: " + index + ", name: " + names[index])
                            let param = pathInfos!.getParamByIndex(index)
                            let node = value_casted(names[index], param)
                            NavExtender.setNavDestinationNode(pathInfos!, index, node.peer.ptr)
                        }
                    }
                    NavExtender.syncStack(pathInfos!)
                }, __context, (isBefore: boolean) => {})
                component.updateNeedSync(true)
            })
        }
    }
    static hookSetNavDestinationImpl(component: ArkNavigationComponent, value: PageMapBuilder | undefined) {
        if (value !== undefined) {
            component.updateNavDestination(value);
        }
    }
}