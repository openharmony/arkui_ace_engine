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
import { NavPathStack, NavigationModuleInfo, ArkNavigationComponent, NavPathStack_serializer, NavigationModuleInfo_serializer } from "../component/navigation"
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

export type NavDestinationBuilder =
/** @memo */
() => void

export class NavigationRouterMap {
    private static routerMap: Map<string, WrappedBuilder<NavDestinationBuilder>> = new Map<string, WrappedBuilder<NavDestinationBuilder>>()
    static RegisterNavDestinationBuilder(name: string, builder: WrappedBuilder<NavDestinationBuilder>): void {
        InteropNativeModule._NativeLog(`AceNavigation: RegisterNavDestinationBuilder for name: ${name}`)
        NavigationRouterMap.routerMap.set(name, builder);
    }

    static CreateNavDestinationFromRouterMap(name: string, param: object|null|undefined): PeerNode | undefined {
        if (!NavigationRouterMap.routerMap.has(name)) {
            InteropNativeModule._NativeLog(`AceNavigation: NavDestination builder for ${name} does't exist`)
            return undefined;
        }
        let builder = NavigationRouterMap.routerMap.get(name)!;
        return createUiDetachedRoot((): PeerNode => ArkStackPeer.create(new ArkStackComponent()), () => {
            setNeedCreate(true)
            builder.builder();
            setNeedCreate(false)
        })
    }
}

export class NavigationOpsHandWritten {
    static hookSetNavigationOptionsImpl(component: ArkNavigationComponent, pathInfos?: NavPathStack, moduleInfo?: NavigationModuleInfo) {
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
        if (moduleInfo !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const moduleInfoTmpValue  = moduleInfo!
            NavigationModuleInfo_serializer.write(thisSerializer, moduleInfoTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        let peerPtr = component.getPeer().peer.ptr
        ArkUIGeneratedNativeModule._NavigationInterface_setNavigationOptions(peerPtr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static hookSetNavDestinationImpl(component: ArkNavigationComponent, value: PageMapBuilder | undefined) {
        if (value === undefined) {
            return
        }
        NavExtender.setNavDestinationBuilderCallback(component.getPeer().peer.ptr, (name: string, param?: Object) => {
            const currentRenderingComponent = ObserveSingleton.instance.renderingComponent;
            const currentExtendableComponent = ExtendableComponent.current;
            const peer = createUiDetachedRoot(() => {
                return ArkComponentRootPeer.create(undefined);
            },
            () => {
                const lastRenderingComponent = ObserveSingleton.instance.renderingComponent;
                const lastExtendableComponent = ExtendableComponent.current;
                ObserveSingleton.instance.renderingComponent = currentRenderingComponent;
                ExtendableComponent.current = currentExtendableComponent;
                /** @memo */
                let builder: (name: string, param: Object | undefined | null) => void = value!;
                builder(name, param)
                ObserveSingleton.instance.renderingComponent = lastRenderingComponent;
                ExtendableComponent.current = lastExtendableComponent;
            });
            return peer.peer.ptr;
        });
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
        let jsonStr: JSONValue = JSONParser.parse(info[dataIndex]);
        if (jsonStr instanceof JSONObject) {
            let keys: Array<JSONString> = jsonStr.keys_;
            let values: Array<JSONValue> = jsonStr.values;
            let result: Record<string, string> = new Record<string, string>();
            for (let i: int = 0; i < keys.length; i++) {
                result[keys[i].value] = (values[i] as JSONString).value;
            }
            config.data = result;
        }
        return config;
    }
}