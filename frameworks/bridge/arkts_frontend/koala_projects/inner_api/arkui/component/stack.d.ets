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

import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent } from 'arkui/component/common';
import { ComponentBase } from 'arkui.ComponentBase';
import { Alignment } from 'arkui.component.enums';
import { StackModifier } from 'arkui.StackModifier';
import { PointLightStyle, AttributeModifier } from 'arkui.component.common';

type KPointer = long;
type int32 = int;

export declare class ArkStackPeer extends ArkCommonMethodPeer {
    _attributeSet?:StackModifier;
    constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0);

    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkStackPeer;

    setStackOptionsAttribute(options?: StackOptions): void;

    alignContentAttribute(value: Alignment | undefined): void;

    pointLightAttribute(value: PointLightStyle | undefined): void;
}

export interface StackOptions {
    alignContent?: Alignment;
}

export interface StackAttribute extends CommonMethod {
    setStackOptions(options?: StackOptions): this;
    alignContent(value: Alignment | undefined): this;
    pointLight(value: PointLightStyle | undefined): this;
    attributeModifier(value: AttributeModifier<StackAttribute> | AttributeModifier<CommonMethod> | undefined): this;
}

export declare class ArkStackComponent extends ArkCommonMethodComponent implements StackAttribute {
    getPeer(): ArkStackPeer;

    public setStackOptions(options?: StackOptions): this;

    public alignContent(value: Alignment | undefined): this;

    public pointLight(value: PointLightStyle | undefined): this;

    public attributeModifier(
        modifier: AttributeModifier<StackAttribute> | AttributeModifier<CommonMethod> | undefined): this;

    public applyAttributesFinish(): void;
}
