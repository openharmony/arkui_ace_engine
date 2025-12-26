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
import { KLong } from "@koalaui/interop"
import { int32 } from "@koalaui/common"
import { CustomComponent } from './component/customComponent'
import { UIContextUtil } from "arkui/base/UIContextUtil";
import { DetachedRootEntryImpl, UIContextImpl } from 'arkui/base/UIContextImpl';

import {
    GlobalStateManager,
    IncrementalNode,
    memoEntry
} from '@koalaui/runtime';
import { StateContext } from 'arkui.incremental.runtime.state';
import { ArkUIAniModule } from "arkui.ani"
import { OBSERVE } from "./stateManagement";
import { ObserveSingleton } from '@ohos.arkui.stateManagement';
import { setNeedCreate } from "arkui/ArkComponentRoot"
import { findPeerNode } from "./PeerNode"
import { InteropNativeModule } from "@koalaui/interop"

const CUSTOM_TITLE_BAR_CLASS: string = "@ohos.window.titlebar.component.System__Reserved_$$$__UI__TitleBar__Component"
const CUSTOM_BUTTOEN_BAR_CLASS: string = "@ohos.window.titlebar.component.System__Reserved_$$$__UI__ButtonBar__Component"
const DEFAULT_TITLE_BAR_CLASS: string = "@ohos.window.titlebar.component.defalut.System__Reserved_$$$__UI__TitleBar__Component"
const DEFAULT_BUTTOEN_BAR_CLASS: string = "@ohos.window.titlebar.component.defalut.System__Reserved_$$$__UI__ButtonBar__Component"

export class XBarProxy {
    // static titleBarComponentMap: Map<KLong, CustomComponent> = new Map();
    static initializeXBarProxy(): void {
        InteropNativeModule._NativeLog(`[createXBarCustomComponent]initializeXBarProxy`)
        const createFunc = (xbarType: int32, instanceID: int32): KLong => {
            return createXBarCustomComponent(xbarType, instanceID);
        };
        ArkUIAniModule._XBar_Set_ComponentCreateFunc(createFunc)
    }

    public static CallNative(xBarType: int32, callType: string, message: string): void {
        ArkUIAniModule._XBar_Call_Native(xBarType, callType, message)
    }
}

export function createXBarCustomComponent<T extends CustomComponent<T, T_Options>, T_Options>(xbarType: int32, instanceID: int32): KLong {
    InteropNativeModule._NativeLog(`[createXBarCustomComponent]start createXBarCustomComponent`)
    let componentInstance: T | undefined = undefined
    const factory = (): T => {
        InteropNativeModule._NativeLog(`[createXBarCustomComponent]createXBarCustomComponent in factory`)
        let reflectTargetName: string = "";
        switch (xbarType) {
            case 0:
                reflectTargetName = CUSTOM_TITLE_BAR_CLASS;
                break;
            case 1:
                reflectTargetName = CUSTOM_BUTTOEN_BAR_CLASS;
                break;
            default:
                reflectTargetName = CUSTOM_TITLE_BAR_CLASS;
        }
        let reflectedType: Type | undefined = Type.resolve(reflectTargetName)
        if (reflectedType === undefined) {
            InteropNativeModule._NativeLog(`[createXBarCustomComponent]${reflectTargetName} is undefined, load default`)
            switch (xbarType) {
                case 0:
                    reflectTargetName = DEFAULT_TITLE_BAR_CLASS;
                    break;
                case 1:
                    reflectTargetName = DEFAULT_BUTTOEN_BAR_CLASS;
                    break;
                default:
                    reflectTargetName = DEFAULT_TITLE_BAR_CLASS;
            }
            reflectedType = Type.resolve(reflectTargetName)
            if (reflectedType === undefined) {
                InteropNativeModule._NativeLog(`[createXBarCustomComponent]${reflectTargetName} is undefined`)
                // return undefined
                throw new Error(`[createXBarCustomComponent]reflectedType is undefined`)
            }
        }
        try {
            let type: ClassType = reflectedType as ClassType
            componentInstance = type.make() as T
            InteropNativeModule._NativeLog(`[createXBarCustomComponent]createXBarCustomComponent end factory`)
            return componentInstance! as T
        } catch (e) {
            InteropNativeModule._NativeLog("[createXBarCustomComponent]make instance error!")
            if (e instanceof Error) {
                InteropNativeModule._NativeLog(`[createXBarCustomComponent]make instance error name: ${e.name} message: ${e.message}`);
                const stack = e.stack
                if (stack) {
                    InteropNativeModule._NativeLog("[createXBarCustomComponent]make instance stack trace: " + stack)
                }
            }
            throw new Error(`[createXBarCustomComponent]make instance error!`)
        }
    }
    InteropNativeModule._NativeLog(`[createXBarCustomComponent]instantiateImpl11`)
    const instantiateImpl = /** @memo */ () => {
        T._instantiateImpl(undefined, factory, undefined, undefined, undefined);
    };
    InteropNativeModule._NativeLog(`[createXBarCustomComponent]start getUIContextById ${instanceID}`)
    const uiContext = UIContextUtil.getOrCreateUIContextById(instanceID) as UIContextImpl;
    InteropNativeModule._NativeLog(`[createXBarCustomComponent]getUIContextById`)
    let manager = uiContext.stateMgr;
    if (manager === undefined) {
        InteropNativeModule._NativeLog(`[createXBarCustomComponent]manager is undefined`)
        manager = GlobalStateManager.instance;
    }
    const node = manager.updatableNode(new IncrementalNode(), (context: StateContext) => {
        ArkUIAniModule._Common_Sync_InstanceId(uiContext.getInstanceId());
        let r = OBSERVE.renderingComponent;
        OBSERVE.renderingComponent = ObserveSingleton.RenderingComponentV1;
        const needCreate = setNeedCreate(true);
        memoEntry<void>(context, 0, instantiateImpl);
        setNeedCreate(needCreate);
        OBSERVE.renderingComponent = r;
        ArkUIAniModule._Common_Restore_InstanceId();
    });
    InteropNativeModule._NativeLog(`[createXBarCustomComponent]updatableNode`)
    const inc = node.value;
    const peerNode = findPeerNode(inc);
    if (peerNode === undefined) {
        InteropNativeModule._NativeLog(`[createXBarCustomComponent]peerNode is undefined`)
        node.dispose();
        return 0;
    }
    uiContext.getDetachedRootEntryManager().detachedRoots_.set(peerNode.peer.ptr, new DetachedRootEntryImpl<IncrementalNode>(node));
    const nodePointer = peerNode.getPeerPtr() as KLong;
    ArkUIAniModule._XBar_Set_JsFunc(nodePointer, componentInstance!)
    InteropNativeModule._NativeLog(`[createXBarCustomComponent]end createXBarCustomComponent`)
    return nodePointer;
}
