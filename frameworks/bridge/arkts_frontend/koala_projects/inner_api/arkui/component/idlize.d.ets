/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { NavPathStack, NavPathInfo, NavigationOptions } from 'arkui.component.navigation'
import { ComponentBase } from 'arkui/ComponentBase';
import { PeerNode } from 'arkui/PeerNode';

type KPointer = long;
type int32 = int;

export declare class NavExtender {
    public static setUpdateStackCallback(peer: NavPathStack, callback: NavExtender_OnUpdateStack): void;
    public static syncStack(peer: NavPathStack): void;
    public static checkNeedCreate(navigation: KPointer, index: int32): boolean;
    public static setNavDestinationNode(peer: NavPathStack, index: int32, node: KPointer): void;
    public static pushPath(pathStack: NavPathStack, info: NavPathInfo, options: NavigationOptions): void;
    public static replacePath(pathStack: NavPathStack, info: NavPathInfo, options: NavigationOptions): void;
    public static pop(pathStack: NavPathStack, animated: boolean): string;
    public static setOnPopCallback(pathStack: NavPathStack, callback: (id: string) => void): void;
    public static getIdByIndex(pathStack: NavPathStack, index: int32): string;
    public static getIdByName(pathStack: NavPathStack, name: string): Array<string>;
    public static popToIndex(pathStack: NavPathStack, index: int32, animated: boolean): void;
    public static popToName(pathStack: NavPathStack, name: string, animated: boolean): number;
}
export type NavExtender_OnUpdateStack = () => void;

export declare class ArkComponentRootPeer extends PeerNode {
    constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0);
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkComponentRootPeer;
}
