/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { int32, float32 } from "@koalaui/common"
import { KStringPtr, KBoolean, RuntimeType, runtimeType } from "@koalaui/interop"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ComponentBase } from "../ComponentBase"
import { TypeChecker } from "#components"
import { ArkSecurityComponentMethodPeer } from "./peers/ArkSecurityComponentPeer"
import { Dimension, Position, Edges, LocalizedEdges, ResourceColor, Padding, Length, SizeOptions, ConstraintSizeOptions } from "./../component/units"
import { SecurityComponentLayoutDirection, SecurityComponentMethod } from "./../component/securityComponent"
import { FontStyle, FontWeight, BorderStyle } from "./../component/enums"
import { Resource } from "global/resource";
/** @memo:stable */
export class ArkSecurityComponentMethodComponent extends ComponentBase implements SecurityComponentMethod {
    getPeer(): ArkSecurityComponentMethodPeer {
        return (this.peer as ArkSecurityComponentMethodPeer)
    }
    /** @memo */
    public iconSize(value: Dimension): this {
        if (this.checkPriority("iconSize")) {
            const value_casted = value as (Dimension)
            this.getPeer()?.iconSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public layoutDirection(value: SecurityComponentLayoutDirection): this {
        if (this.checkPriority("layoutDirection")) {
            const value_casted = value as (SecurityComponentLayoutDirection)
            this.getPeer()?.layoutDirectionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public position(value: Position): this {
        if (this.checkPriority("position")) {
            const value_casted = value as (Position)
            this.getPeer()?.positionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public markAnchor(value: Position): this {
        if (this.checkPriority("markAnchor")) {
            const value_casted = value as (Position)
            this.getPeer()?.markAnchorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public offset(value: Position | Edges | LocalizedEdges): this {
        if (this.checkPriority("offset")) {
            const value_casted = value as (Position | Edges | LocalizedEdges)
            this.getPeer()?.offsetAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontSize(value: Dimension): this {
        if (this.checkPriority("fontSize")) {
            const value_casted = value as (Dimension)
            this.getPeer()?.fontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontStyle(value: FontStyle): this {
        if (this.checkPriority("fontStyle")) {
            const value_casted = value as (FontStyle)
            this.getPeer()?.fontStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontWeight(value: number | FontWeight | string): this {
        if (this.checkPriority("fontWeight")) {
            const value_casted = value as (number | FontWeight | string)
            this.getPeer()?.fontWeightAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontFamily(value: string | Resource): this {
        if (this.checkPriority("fontFamily")) {
            const value_casted = value as (string | Resource)
            this.getPeer()?.fontFamilyAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontColor(value: ResourceColor): this {
        if (this.checkPriority("fontColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.fontColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public iconColor(value: ResourceColor): this {
        if (this.checkPriority("iconColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.iconColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public backgroundColor(value: ResourceColor): this {
        if (this.checkPriority("backgroundColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.backgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public borderStyle(value: BorderStyle): this {
        if (this.checkPriority("borderStyle")) {
            const value_casted = value as (BorderStyle)
            this.getPeer()?.borderStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public borderWidth(value: Dimension): this {
        if (this.checkPriority("borderWidth")) {
            const value_casted = value as (Dimension)
            this.getPeer()?.borderWidthAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public borderColor(value: ResourceColor): this {
        if (this.checkPriority("borderColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.borderColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public borderRadius(value: Dimension): this {
        if (this.checkPriority("borderRadius")) {
            const value_casted = value as (Dimension)
            this.getPeer()?.borderRadiusAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public padding(value: Padding | Dimension): this {
        if (this.checkPriority("padding")) {
            const value_casted = value as (Padding | Dimension)
            this.getPeer()?.paddingAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public textIconSpace(value: Dimension): this {
        if (this.checkPriority("textIconSpace")) {
            const value_casted = value as (Dimension)
            this.getPeer()?.textIconSpaceAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public key(value: string): this {
        if (this.checkPriority("key")) {
            const value_casted = value as (string)
            this.getPeer()?.keyAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public width(value: Length): this {
        if (this.checkPriority("width")) {
            const value_casted = value as (Length)
            this.getPeer()?.widthAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public height(value: Length): this {
        if (this.checkPriority("height")) {
            const value_casted = value as (Length)
            this.getPeer()?.heightAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public size(value: SizeOptions): this {
        if (this.checkPriority("size")) {
            const value_casted = value as (SizeOptions)
            this.getPeer()?.sizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public constraintSize(value: ConstraintSizeOptions): this {
        if (this.checkPriority("constraintSize")) {
            const value_casted = value as (ConstraintSizeOptions)
            this.getPeer()?.constraintSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public applyAttributesFinish(): void {
        // we calls this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
