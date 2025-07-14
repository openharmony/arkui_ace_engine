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

import { ArkDividerPeer, ArkCommonMethodPeer, AttributeModifier, ResourceColor, DividerAttribute, LineCapStyle } from './component';
import { ArkCommonAttributeSet, modifierWithKey, ModifierWithKey } from './handwritten/modifiers/ArkCommonModifier';

class ColorModifier extends ModifierWithKey<ResourceColor | undefined> {
    static identity: string = 'color';

    constructor(value: ResourceColor | undefined) {
        super(value);
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let colorPeerNode = node as ArkDividerPeer;
        if (reset) {
            // now do nothing
        } else {
            if (this.value !== undefined) {
                colorPeerNode.colorAttribute(this.value as ResourceColor);
            }
        }
    }

    static factory(value: ResourceColor | undefined): ColorModifier {
        return new ColorModifier(value);
    }
}

class StrokeWidthModifier extends ModifierWithKey<string | number | undefined> {
    static identity: string = 'strokeWidth';

    constructor(value: string | number | undefined) {
        super(value);
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let strokeWidthPeerNode = node as ArkDividerPeer;
        if (reset) {
            // now do nothing
        } else {
            if (this.value !== undefined) {
                strokeWidthPeerNode.strokeWidthAttribute(this.value as string | number);
            }
        }
    }

    static factory(value: string | number | undefined): StrokeWidthModifier {
        return new StrokeWidthModifier(value);
    }
}

class VerticalModifier extends ModifierWithKey<boolean | undefined> {
    static identity: string = 'vertical';

    constructor(value: boolean | undefined) {
        super(value);
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let verticalPeerNode = node as ArkDividerPeer;
        if (reset) {
            // now do nothing
        } else {
            if (this.value !== undefined) {
                verticalPeerNode.verticalAttribute(this.value as boolean);
            }
        }
    }

    static factory(value: boolean | undefined): VerticalModifier {
        return new VerticalModifier(value);
    }
}

class LineCapModifier extends ModifierWithKey<LineCapStyle | undefined> {
    static identity: string = 'lineCap';

    constructor(value: LineCapStyle | undefined) {
        super(value);
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        let lineCapPeerNode = node as ArkDividerPeer;
        if (reset) {
            // now do nothing
        } else {
            if (this.value !== undefined) {
                lineCapPeerNode.lineCapAttribute(this.value as LineCapStyle);
            }
        }
    }

    static factory(value: LineCapStyle | undefined): LineCapModifier {
        return new LineCapModifier(value);
    }
}

export class ArkDividerAttributeSet extends ArkCommonAttributeSet implements DividerAttribute {
    color(value: ResourceColor | undefined): this {
        modifierWithKey(this._modifiersWithKeys, ColorModifier.identity, ColorModifier.factory, value);
        return this;
    }

    vertical(value: boolean | undefined): this {
        modifierWithKey(this._modifiersWithKeys, VerticalModifier.identity, VerticalModifier.factory, value);
        return this;
    }

    strokeWidth(value: string | number | undefined): this {
        modifierWithKey(this._modifiersWithKeys, StrokeWidthModifier.identity, StrokeWidthModifier.factory, value);
        return this;
    }

    lineCap(value: LineCapStyle | undefined): this {
        modifierWithKey(this._modifiersWithKeys, LineCapModifier.identity, LineCapModifier.factory, value);
        return this;
    }
}

export class DividerModifier implements AttributeModifier<DividerAttribute> {
    attributeSet: ArkDividerAttributeSet = new ArkDividerAttributeSet();

    applyNormalAttribute(instance: DividerAttribute): void {}
    applyPressedAttribute(instance: DividerAttribute): void {}
    applyFocusedAttribute(instance: DividerAttribute): void {}
    applyDisabledAttribute(instance: DividerAttribute): void {}
    applySelectedAttribute(instance: DividerAttribute): void {}

    color(value: ResourceColor | undefined): this {
        this.attributeSet.color(value);
        return this;
    }

    strokeWidth(value: string | number | undefined): this {
        this.attributeSet.strokeWidth(value);
        return this;
    }

    vertical(value: boolean | undefined): this {
        this.attributeSet.vertical(value);
        return this;
    }

    lineCap(value: LineCapStyle | undefined): this {
        this.attributeSet.lineCap(value);
        return this;
    }
}