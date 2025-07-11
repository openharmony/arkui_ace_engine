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

import { int32 } from '@koalaui/compat';
import { KPointer } from '@koalaui/interop';
import { ComponentBase } from 'arkui.ComponentBase';
import {
    ArkCommonMethodPeer,
    CommonMethod,
    ArkCommonMethodStyle,
    ArkCommonMethodComponent,
} from 'arkui/component/common';
import { ListItemOptions, SwipeActionOptions } from 'arkui.component.listItem';

export enum Sticky {
    NONE = 0,
    None = 0,
    NORMAL = 1,
    Normal = 1,
    OPACITY = 2,
    Opacity = 2,
}

export enum EditMode {
    NONE = 0,
    None = 0,
    DELETABLE = 1,
    Deletable = 1,
    MOVABLE = 2,
    Movable = 2,
}

export declare class ArkListItemPeer extends ArkCommonMethodPeer {
    constructor(peerPtr: KPointer, id: int32, name: string);
    constructor(peerPtr: KPointer, id: int32);
    protected constructor(peerPtr: KPointer, id: int32, name: string, flags: int32);
    public static create(component: ComponentBase | undefined, flags?: int32): ArkListItemPeer;
    public setListItemOptions0Attribute(value?: ListItemOptions): void;
    public setListItemOptions1Attribute(value?: string): void;
    public stickyAttribute(value: Sticky | undefined): void;
    public editableAttribute(value: boolean | EditMode | undefined): void;
    public selectableAttribute(value: boolean | undefined): void;
    public selectedAttribute(value: boolean | undefined): void;
    public swipeActionAttribute(value: SwipeActionOptions | undefined): void;
    public onSelectAttribute(value: ((isVisible: boolean) => void) | undefined): void;
    public _onChangeEvent_selectedAttribute(callback: (select: boolean | undefined) => void): void;
}

export interface ListItemAttribute extends CommonMethod {
    sticky(value: Sticky | undefined): this;
    editable(value: boolean | EditMode | undefined): this;
    selectable(value: boolean | undefined): this;
    selected(value: boolean | undefined): this;
    swipeAction(value: SwipeActionOptions | undefined): this;
    onSelect(value: ((isVisible: boolean) => void) | undefined): this;
    _onChangeEvent_selected(callback: (select: boolean | undefined) => void): void;
}

export declare class ArkListItemStyle extends ArkCommonMethodStyle implements ListItemAttribute {
    public sticky_value?: Sticky | undefined;
    public editable_value?: boolean | EditMode | undefined;
    public selectable_value?: boolean | undefined;
    public selected_value?: boolean | undefined;
    public swipeAction_value?: SwipeActionOptions | undefined;
    public onSelect_value?: ((isVisible: boolean) => void) | undefined;
    public sticky(value: Sticky | undefined): this;
    public editable(value: boolean | EditMode | undefined): this;
    public selectable(value: boolean | undefined): this;
    public selected(value: boolean | undefined): this;
    public swipeAction(value: SwipeActionOptions | undefined): this;
    public onSelect(value: ((isVisible: boolean) => void) | undefined): this;
    public _onChangeEvent_selected(callback: (select: boolean | undefined) => void): void;
}
export declare class ArkListItemComponent extends ArkCommonMethodComponent implements ListItemAttribute {
    public getPeer(): ArkListItemPeer;
    public setListItemOptions(value?: ListItemOptions | string): this;
    public sticky(value: Sticky | undefined): this;
    public editable(value: boolean | EditMode | undefined): this;
    public selectable(value: boolean | undefined): this;
    public selected(value: boolean | undefined): this;
    public swipeAction(value: SwipeActionOptions | undefined): this;
    public onSelect(value: ((isVisible: boolean) => void) | undefined): this;
    public _onChangeEvent_selected(callback: (select: boolean | undefined) => void): void;
    public applyAttributesFinish(): void;
}
