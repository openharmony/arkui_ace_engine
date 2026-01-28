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

import { SerializerBase, runtimeType, RuntimeType, InteropNativeModule, KPointer } from "@koalaui/interop"
import { ArkUIGeneratedNativeModule } from "#components"
import { NavPathStack, NavigationModuleInfo, ArkNavigationComponent, ArkNavigationPeer, NavPathStack_serializer, NavigationModuleInfo_serializer, HomePathInfo_serializer, HomePathInfo } from "../component/navigation"
import { NavDestinationContextInternal, RouteMapConfig } from "../component/navDestination"
import { NavExtender, ArkComponentRootPeer } from "../component/idlize"
import { int32 } from "@koalaui/common"
import { addPartialUpdate, createUiDetachedRoot } from "../ArkUIEntry"
import { PeerNode } from "../PeerNode"
import { ArkStackComponent, ArkStackPeer } from "../component/stack"
import { __context } from "@koalaui/runtime"
import { PageMapBuilder, WrappedBuilder } from "../component/builder"
import { setNeedCreate } from "../ArkComponentRoot"
import { ObserveSingleton } from "../stateManagement/base/observeSingleton"
import { ExtendableComponent } from '../component/extendableComponent'
import { ComponentContent } from 'arkui.ComponentContent'

export type NavDestinationBuilder =
/** @memo */
(name: string, params: Object | null | undefined) => void

interface BuildNavDestinationParam {
    currentRenderingComponent: int;
    currentExtendableComponent: Object | undefined;
    name: string;
    param: Object | null | undefined;
}

function BuildNavDestination(builder: NavDestinationBuilder, param: BuildNavDestinationParam): PeerNode {
    return createUiDetachedRoot(
        () => {
            return ArkComponentRootPeer.create(undefined);
        },
        () => {
            const lastRenderingComponent = ObserveSingleton.instance.renderingComponent;
            const lastExtendableComponent = ExtendableComponent.current;
            ObserveSingleton.instance.renderingComponent = param.currentRenderingComponent;
            ExtendableComponent.current = param.currentExtendableComponent;
            try {
                builder(param.name, param.param);
            } finally {
                ObserveSingleton.instance.renderingComponent = lastRenderingComponent;
                ExtendableComponent.current = lastExtendableComponent;
            }
        });
}

export class NavigationRouterMap {
    private static routerMap: Map<string, WrappedBuilder<NavDestinationBuilder>> = new Map<string, WrappedBuilder<NavDestinationBuilder>>()
    static RegisterNavDestinationBuilder(name: string, builder: WrappedBuilder<NavDestinationBuilder>): void {
        InteropNativeModule._NativeLog(`AceNavigation: RegisterNavDestinationBuilder for name: ${name}`)
        NavigationRouterMap.routerMap.set(name, builder);
    }

    static CreateNavDestinationFromRouterMap(param: BuildNavDestinationParam): PeerNode | undefined {
        if (!NavigationRouterMap.routerMap.has(param.name)) {
            InteropNativeModule._NativeLog(`AceNavigation: NavDestination builder for ${param.name} does't exist`)
            return undefined;
        }
        let builder = NavigationRouterMap.routerMap.get(param.name)!;
        return BuildNavDestination(builder.builder, param);
    }
}

export class NavigationOpsHandWritten {
    static hookSetNavigationOptionsImpl(component: ArkNavigationComponent, pathInfos?: NavPathStack, homeDestination?: HomePathInfo, moduleInfo?: NavigationModuleInfo) {
        let info: NavPathStack = new NavPathStack();
        const pathInfos_type = runtimeType(pathInfos)
        if (pathInfos_type != RuntimeType.UNDEFINED) {
            info = pathInfos!
        }
        NavExtender.setUpdateStackCallback(info, () => {
            addPartialUpdate(() => {
                InteropNativeModule._NativeLog(`AceNavigation: trigger navigation stack sync in js`);
                NavExtender.syncStack(info)
            }, __context, (isBefore: boolean) => {})
        })
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt8(RuntimeType.OBJECT)
        const pathInfosTmpValue  = info
        NavPathStack_serializer.write(thisSerializer, pathInfosTmpValue)
        if (homeDestination !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const homeDestinationTmpValue  = homeDestination!
            HomePathInfo_serializer.write(thisSerializer, homeDestinationTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (moduleInfo !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const moduleInfoTmpValue  = moduleInfo!
            NavigationModuleInfo_serializer.write(thisSerializer, moduleInfoTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        let peerPtr = component.getPeer().peer.ptr
        ArkUIGeneratedNativeModule._NavigationInterface_setNavigationOptions1(peerPtr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        if (info == undefined || info == null) {
            console.log(`AceNavigation: NavPathStack is empty!`)
            return;
        }
        const currentRenderingComponent = ObserveSingleton.instance.renderingComponent;
        const currentExtendableComponent = ExtendableComponent.current;
        NavExtender.setNavDestinationRouterMapBuilderCallback(component.getPeer().peer.ptr, (name: string, param?: Object): KPointer => {
            InteropNativeModule._NativeLog(`AceNavigation: create new node: name: ${name} from router map`);
            let buildParam = {
                currentRenderingComponent: currentRenderingComponent,
                currentExtendableComponent: currentExtendableComponent,
                name: name,
                param: param
            } as BuildNavDestinationParam;
            let node = NavigationRouterMap.CreateNavDestinationFromRouterMap(buildParam);
            if (!node) {
                InteropNativeModule._NativeLog(`AceNavigation: failed to create NavDestination from router map`);
                return 0;
            }
            return node.peer.ptr;
        })
    }
    static hookSetNavDestinationImpl(peer: ArkNavigationPeer, value: PageMapBuilder | undefined) {
        if (value === undefined) {
            return
        }
        const currentRenderingComponent = ObserveSingleton.instance.renderingComponent;
        const currentExtendableComponent = ExtendableComponent.current;
        NavExtender.setNavDestinationBuilderCallback(peer.peer.ptr, (name: string, param?: Object) => {
            let buildParam = {
                currentRenderingComponent: currentRenderingComponent,
                currentExtendableComponent: currentExtendableComponent,
                name: name,
                param: param
            } as BuildNavDestinationParam;
            const peer = BuildNavDestination(value!, buildParam);
            return peer.peer.ptr;
        });
    }
    static hookSplitPlaceholderImpl(peer: ArkNavigationPeer, value: ComponentContent<Object>) {
        let peerPtr = peer.peer.ptr;
        let ptr: KPointer = 0;
        if (value.getNodePtr() !== undefined) {
            ptr = value.getNodePtr() as KPointer;
        }
        NavExtender.setSplitPlaceholder(peerPtr, ptr);
    }
    static hookGetRouteConfigImpl(context: NavDestinationContextInternal): RouteMapConfig | undefined {
        let info: Array<string> = NavExtender.getRouteMapInConfig(context.getPeer()!.ptr);
        if (info.length === 0) {
            return undefined;
        }
        let config: RouteMapConfig = {
            name: info[0],
            pageSourceFile: info[1],
            data: {}
        };
        const dataIndex = 2;
        if (info.length <= dataIndex) {
            return config;
        }
        let value: jsonx.JsonElement = JSON.parseJsonElement(info[dataIndex]);
        let vType: jsonx.JsonType = value.jsonType;
        if (vType === jsonx.JsonType.JsonObject) {
            let iterVal: IterableIterator<[string, jsonx.JsonElement]> = value.$_iterator();
            let result: Record<string, string> = new Record<string, string>();
            for (let t of iterVal) {
                result[t[0]] = t[1].asString();
            }
            config.data = result;
        }
        return config;
    }
}
