/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

import { ArkoalaColor, translateColorToArkoalaColor } from "./ArkoalaColor"
import { isEdgeColors, isEdgeWidths } from "./utils"
import { parseFontWeight } from "../base/textUtils";
import { clamp } from "@koalaui/common";

export interface Equable {
    isEqual(value: Equable): boolean;
}

export enum ArkUIAPIDimensionUnit {
    PX = 0,
    VP = 1,
    FP = 2,
    PERCENTAGE = 3,
    LPX = 4,
}

export class GeoLength implements Equable {
    constructor(readonly value: number, readonly unit: ArkUIAPIDimensionUnit) { }

    isEqual(value: GeoLength): boolean {
        return (this.value == value.value) && (this.unit == value.unit)
    }
}

export class EdgeLength implements Equable {
    top: GeoLength;
    right: GeoLength;
    bottom: GeoLength;
    left: GeoLength;

    get values(): Float32Array { return this.flattenValueArray() }
    get units(): Int32Array { return this.flattenUnitArray() }


    constructor() {
        let length = new GeoLength(0, ArkUIAPIDimensionUnit.VP);
        this.top = length;
        this.bottom = length;
        this.left = length;
        this.right = length;
    }
    setSameValue(value: GeoLength) {
        this.top = value;
        this.bottom = value;
        this.left = value;
        this.right = value;
    }
    isEqual(value: EdgeLength): boolean {
        return this.top.isEqual(value.top) && this.right.isEqual(value.right)
            && this.bottom.isEqual(value.bottom) && this.left.isEqual(value.left)
    }
    protected flattenValueArray() {
        let array = new Float32Array(4)
        for (let i = 0; i < 4; i++) {
            array[i] = this.getGeoLength(i).value
            array[i * 2 + 1] = this.getGeoLength(i).unit
        }
        return array

    }

    protected flattenUnitArray(): Int32Array {
        let array = new Int32Array(4)
        for (let i = 0; i < 4; i++) {
            array[i] = this.getGeoLength(i).unit
        }
        return array
    }
    protected getGeoLength(index: number): GeoLength {

        switch (index) {
            case 0:
                return this.left
            case 1:
                return this.top
            case 2:
                return this.right
            case 3:
                return this.bottom
            default:
                return new GeoLength(0, ArkUIAPIDimensionUnit.VP);
        }
    }
}

let parseDimensionBuffer = new Float32Array(2);
export function parseDimension(dimension: Length, unit: ArkUIAPIDimensionUnit = ArkUIAPIDimensionUnit.VP): GeoLength
{
    if (typeof dimension === "number") {
        return new GeoLength(dimension, unit);
    } else if (typeof dimension === "string") {
        // TODO: think about it
        // withString(dimension, str => {
        //     withFloat32Array(parseDimensionBuffer, Access.WRITE, out => {
        //         nativeModule()._ParseDimension(str, out);
        //     })
        // })
        let unit = parseDimensionBuffer[1];
        let value = parseDimensionBuffer[0];
        if (unit != -1) {
            return new GeoLength(value, unit)
        }
    }
    console.error("Invalid dimension")
    return new GeoLength(0, unit)
}

export class BorderRadiusLength implements Equable {
    topLeft: GeoLength;
    topRight: GeoLength;
    bottomLeft: GeoLength;
    bottomRight: GeoLength;

    get values(): Float32Array { return this.flattenValueArray() }
    get units(): Int32Array { return this.flattenUnitArray() }

    constructor() {
        let length = new GeoLength(0, ArkUIAPIDimensionUnit.VP);
        this.topLeft = length;
        this.topRight = length;
        this.bottomLeft = length;
        this.bottomRight = length;
    }
    setSameValue(value: GeoLength) {
        this.topLeft = value;
        this.topRight = value;
        this.bottomLeft = value;
        this.bottomRight = value;
    }
    isEqual(value: BorderRadiusLength): boolean {
        return this.topLeft.isEqual(value.topLeft) && this.topRight.isEqual(value.topRight)
            && this.bottomLeft.isEqual(value.bottomLeft) && this.bottomRight.isEqual(value.bottomRight)
    }
    protected flattenValueArray(): Float32Array {
        let array = new Float32Array(4)
        for (let i = 0; i < 4; i++) {
            array[i] = this.getGeoLength(i).value
            array[i * 2 + 1] = this.getGeoLength(i).unit
        }
        return array
    }
    protected flattenUnitArray(): Int32Array {
        let array = new Int32Array(4)
        for (let i = 0; i < 4; i++) {
            array[i] = this.getGeoLength(i).unit
        }
        return array
    }
    protected getGeoLength(index: number): GeoLength {

        switch (index) {
            case 0:
                return this.topLeft;
            case 1:
                return this.topRight
            case 2:
                return this.bottomLeft
            case 3:
                return this.bottomRight
            default:
                return new GeoLength(0, ArkUIAPIDimensionUnit.VP);
        }
    }
}
export function isBorderRadiuses(value: Length | BorderRadiuses): value is BorderRadiuses {
    let borderRadius = value as BorderRadiuses;
    return borderRadius.bottomLeft !== undefined
        || borderRadius.bottomRight !== undefined
        || borderRadius.topLeft !== undefined
        || borderRadius.topRight !== undefined;
}
export function translateBorderRadiusToArk(value?: Length | BorderRadiuses): BorderRadiusLength {
    let borderRadius = new BorderRadiusLength();
    if (value == undefined) {
        return borderRadius
    }
    if (!isBorderRadiuses(value)) {
        borderRadius.setSameValue(parseDimension(value));
    } else {
        if (value.topLeft !== undefined) {
            borderRadius.topLeft = parseDimension(value.topLeft);
        }
        if (value.topRight !== undefined) {
            borderRadius.topRight = parseDimension(value.topRight);
        }
        if (value.bottomLeft !== undefined) {
            borderRadius.bottomLeft = parseDimension(value.bottomLeft);
        }
        if (value.bottomRight !== undefined) {
            borderRadius.bottomRight = parseDimension(value.bottomRight);
        }
    }
    return borderRadius
}

export function translateBorderColorToArk(colors?: EdgeColors | ResourceColor): Int32Array {
    return flattenColors(translateEdgesColorToArk(colors))
}

export class ArkBorderOptions implements Equable {
    width: EdgeLength;
    colors: Int32Array;
    radius: BorderRadiusLength;
    styles: Int32Array;

    constructor(colors?: ArkoalaColor[]) {
        this.colors = flattenColors(colors);
        let styles = new Int32Array(4).fill(BorderStyle.SOLID);
        this.styles = styles;
        this.radius = new BorderRadiusLength();

        this.width = new EdgeLength();
    }


    isEqual(value: ArkBorderOptions): boolean {
        return this.styles == value.styles && this.width.isEqual(value.width)
            && this.colors == value.colors && this.radius.isEqual(value.radius)
    }

}

export function translateEdgeWidthsToArk(value?: EdgeWidths | Length): EdgeLength {
    let edges = new EdgeLength()
    if (value !== undefined) {
        if (!isEdgeWidths(value)) {
            edges.setSameValue(parseDimension(value));
        } else {
            if (value.bottom !== undefined) {
                edges.bottom = parseDimension(value.bottom);
            }
            if (value.top !== undefined) {
                edges.top = parseDimension(value.top);
            }
            if (value.left !== undefined) {
                edges.left = parseDimension(value.left);
            }
            if (value.right !== undefined) {
                edges.right = parseDimension(value.right);
            }
        }
    }
    return edges
}
function translateEdgesColorToArk(value?: EdgeColors | ResourceColor): ArkoalaColor[] {
    let colors = new Array<ArkoalaColor>(4).fill(ArkoalaColor.Black);
    if (value === undefined) {
        return colors
    }
    if (isEdgeColors(value)) {
        if (value.top !== undefined) {
            colors[0] = translateColorToArkoalaColor(value.top);
        }
        if (value.right !== undefined) {
            colors[1] = translateColorToArkoalaColor(value.right);
        }
        if (value.bottom !== undefined) {
            colors[2] = translateColorToArkoalaColor(value.bottom);
        }
        if (value.left !== undefined) {
            colors[3] = translateColorToArkoalaColor(value.left);
        }
    } else {
        colors.fill(translateColorToArkoalaColor(value))
    }

    return colors
}
function translateEdgeStylesToArk(value?: EdgeStyles | BorderStyle): Int32Array {
    let styles = new Int32Array(4).fill(BorderStyle.SOLID);
    if (value == undefined) {
        return styles
    }
    if (typeof value === 'number') {
        styles.fill(value)
    } else {
        if (value.top !== undefined) {
            styles[0] = value.top
        }
        if (value.right !== undefined) {
            styles[1] = value.right
        }
        if (value.bottom !== undefined) {
            styles[2] = value.bottom
        }
        if (value.left !== undefined) {
            styles[3] = value.left
        }
    }
    return styles
}

export function translateBorderOptionsToArkBorderOptions(value: BorderOptions): ArkBorderOptions {
    let width = translateEdgeWidthsToArk(value.width as Length);
    let radius = translateBorderRadiusToArk(value.radius as Length);
    let colors = translateEdgesColorToArk(value.color);
    let styles = translateEdgeStylesToArk(value.style);
    let arkBorderOptions = new ArkBorderOptions(colors);
    arkBorderOptions.radius = radius
    arkBorderOptions.width = width
    arkBorderOptions.styles = styles
    return arkBorderOptions
}

function flattenColors(colors?: ArkoalaColor[]): Int32Array {
    if (colors !== undefined) {
        let array = new Int32Array(colors.length)
        for (let i = 0; i < colors.length; i++) {
            array[i] = colors[i].value
        }
        return array
    } else {
        let array = new Int32Array(4).fill(ArkoalaColor.Black.value);
        return array
    }
}

export class BackgroundImageOptions implements Equable {
    src: ResourceStr
    repeat?: ImageRepeat = ImageRepeat.NO_REPEAT

    constructor(src: ResourceStr, repeat?: ImageRepeat) {
        this.src = src;
        this.repeat = repeat
    }


    isEqual(value: BackgroundImageOptions): boolean {
        return this.src == value.src && this.repeat == value.repeat
    }

}

export class BackgroundImageSizeOptions implements Equable {
    flag: boolean = false;
    width: GeoLength = new GeoLength(0, ArkUIAPIDimensionUnit.VP);
    height: GeoLength = new GeoLength(0, ArkUIAPIDimensionUnit.VP);
    ImageSize: ImageSize = ImageSize.AUTO
    get values(): Float32Array { return this.flag ? this.flattenValueArray() : this.flattenEnumsArray() }

    constructor(flag: boolean) {
        this.flag = flag
    }

    isEqual(value: BackgroundImageSizeOptions): boolean {
        return (this.width?.value == value.width?.value && this.width?.unit == this.width?.unit
            && this.height?.value == value.height?.value && this.height?.unit == this.height?.unit) || (this.ImageSize == value.ImageSize)
    }

    protected flattenValueArray(): Float32Array {
        let array = new Float32Array(4)
        array[0] = this.width.value
        array[1] = this.width.unit
        array[2] = this.height.value
        array[3] = this.height.unit
        return array
    }
    protected flattenEnumsArray(): Float32Array {
        let array = new Float32Array(1)
        array[0] = this.ImageSize
        return array
    }

}


function parseAngle (angle: number | string): number  {
    if (typeof angle === "number") {
        return angle;
    }
    if (/([0-9]+)deg/.test(angle)) {
        return parseFloat(RegExp.$1);
    }
    return 180;
}

export class ArkRotationOptions implements Equable {
    x: number
    y: number
    z: number

    angle: number

    centerX: GeoLength
    centerY: GeoLength
    centerZ: GeoLength

    constructor(options: RotateOptions) {
        this.x = options.x ?? 0
        this.y = options.y ?? 0
        this.z = options.z ?? 0
        this.angle = parseAngle(options.angle)

        this.centerX = parseDimension(options.centerX ?? '50%')
        this.centerY = parseDimension(options.centerY ?? '50%')
        this.centerZ = parseDimension(options.centerZ ?? '0')
    }

    getRotateOptions():Float32Array{
        const buffer = new Float32Array(11)
        buffer[0] = this.x
        buffer[1] = this.y
        buffer[2] = this.z
        buffer[3] = this.angle
        buffer[4] = 1.0
        buffer[5] = this.centerX.value
        buffer[6] = this.centerX.unit
        buffer[7] = this.centerY.value
        buffer[8] = this.centerY.unit
        buffer[9] = this.centerZ.value
        buffer[10] = this.centerZ.unit
        return buffer
    }

    isEqual(value: Equable): boolean {
        if (!(value instanceof ArkRotationOptions)) {
            return false
        }

        return this.x === value.x &&
            this.y === value.y &&
            this.z === value.z &&
            this.angle === value.angle &&
            this.centerX.isEqual(value.centerX) &&
            this.centerY.isEqual(value.centerY)
    }
}

export class ArkScaleOptions implements Equable {
    x: number;
    y: number;
    z: number;

    centerX: GeoLength;
    centerY: GeoLength;

    constructor(options: ScaleOptions) {
        this.x = options.x ?? 1.0
        this.y = options.y ?? 1.0
        this.z = options.z ?? 1.0
        this.centerX = parseDimension(options.centerX ?? '50%')
        this.centerY = parseDimension(options.centerY ?? '50%')
    }

    getScaleOptions():Float32Array{
        const buffer = new Float32Array(7)
        buffer[0] = this.x
        buffer[1] = this.y
        buffer[2] = this.z
        buffer[3] = this.centerX.value
        buffer[4] = this.centerX.unit
        buffer[5] = this.centerY.value
        buffer[6] = this.centerY.unit
        return buffer
    }

    isEqual(value: Equable): boolean {
        if (!(value instanceof ArkScaleOptions)) {
            return false
        }

        return this.x === value.x &&
            this.y === value.y &&
            this.z === value.z &&
            this.centerX.isEqual(value.centerX) &&
            this.centerY.isEqual(value.centerY)
    }
}

export class ArkTranslateOptions implements Equable {
    x: GeoLength;
    y: GeoLength;
    z: GeoLength;

    constructor(options: TranslateOptions) {
        this.x = parseDimension(options.x ?? 0.0)
        this.y = parseDimension(options.y ?? 0.0)
        this.z = parseDimension(options.z ?? 0.0)
    }

    getTranslateOptions():Float32Array{
        const buffer = new Float32Array(6)
        buffer[0] = this.x.value
        buffer[1] = this.x.unit
        buffer[2] = this.y.value
        buffer[3] = this.y.unit
        buffer[4] = this.z.value
        buffer[5] = this.z.unit
        return buffer
    }

    isEqual(value: Equable): boolean {
        if (!(value instanceof ArkTranslateOptions)) {
            return false
        }

        return this.x.isEqual(value.x) &&
            this.y.isEqual(value.y) && this.z.isEqual(value.z)
    }
}

export class ArkTransitionOptions implements Equable {
    type: TransitionType = TransitionType.ALL
    opacity: number = 0
    translate: Float32Array
    scale: Float32Array
    rotate: Float32Array

    constructor(translateVal: ArkTranslateOptions, scaleVal: ArkScaleOptions, rotateVal: ArkRotationOptions) {
        this.translate = translateVal.getTranslateOptions()
        this.scale = scaleVal.getScaleOptions()
        this.rotate = rotateVal.getRotateOptions()
    }

    isEqual(value: Equable): boolean {
        if (!(value instanceof ArkTransitionOptions)) {
            return false
        }

        return this.type === value.type && this.opacity === value.opacity &&
            this.translate === value.translate && this.scale === value.scale && this.rotate === value.rotate
    }
}

export function translateArkTransitionOption(value: TransitionOptions): ArkTransitionOptions {
    let translate = new ArkTranslateOptions(value.translate ?? {})
    let scale = new ArkScaleOptions(value.scale ?? {})
    let rotate = new ArkRotationOptions(value.rotate ?? { angle: 0})
    let transition = new ArkTransitionOptions(translate, scale, rotate)
    if (value.type) {
        transition.type = value.type
    }
    if (value.opacity) {
        transition.opacity = (value.opacity < 0 || value.opacity > 1) ? 1 : value.opacity
    }
    return transition;
}

export class ArkPosition implements Equable {
    x: GeoLength
    y: GeoLength

    constructor(options: Position) {
        this.x = parseDimension(options.x ?? 0)
        this.y = parseDimension(options.y ?? 0)
    }

    getPositionOptions(): Float32Array{
        const buffer = new Float32Array(4)
        buffer[0] = this.x.value
        buffer[1] = this.x.unit
        buffer[2] = this.y.value
        buffer[3] = this.y.unit
        return buffer
    }

    isEqual(value: Equable): boolean {
    if (!(value instanceof ArkPosition)) {
            return false
        }

        return this.x.isEqual(value.x) && this.y.isEqual(value.y)
    }
}

export class ArkFont {
    size: Float32Array
    weight: number
    family: string | Resource
    style: number
    constructor(value: Font) {
        this.size = translateGeoLengthToArray(value.size ? parseDimension(value.size, ArkUIAPIDimensionUnit.FP) : new GeoLength(16, ArkUIAPIDimensionUnit.FP));
        this.weight = parseFontWeight(value.weight ?? 400)
        this.family = value.family ?? ''
        this.style = value.style ?? FontStyle.NORMAL
    }
}

export function translateGeoLengthToArray(size: GeoLength): Float32Array {
    let ret = new Float32Array(2)
    ret[0] = size.value
    ret[1] = size.unit
    return ret
}

export function parseListItemGroupStyle(style: ListItemGroupStyle): number {
    return style === ListItemGroupStyle.CARD ? 1 : 0;
}

export class ArkAnimate {
    animateOptions: Float32Array
    curve: number
    constructor(param: AnimateParam) {
        this.animateOptions = new Float32Array(5).fill(-1)
        if (param.duration != undefined) {
            this.animateOptions[0] = param.duration
        }
        if (param.tempo != undefined) {
            this.animateOptions[1] = param.tempo
        }
        if (param.delay != undefined) {
            this.animateOptions[2] = param.delay
        }
        if (param.iterations != undefined) {
            this.animateOptions[3] = param.iterations
        }
        if (param.playMode != undefined) {
            this.animateOptions[4] = param.playMode
        }
        this.curve = param.curve ? param.curve as Curve : Curve.EASE_IN_OUT
    }
}

export interface ChainAnimationOptions {
    minSpace: Length;
    maxSpace: Length;
    conductivity?: number;
    intensity?: number;
    edgeEffect?: ChainEdgeEffect;
    stiffness?: number;
    damping?: number;
}

export function translateChainAnimationOptions(value: ChainAnimationOptions): Float32Array {
    let options = new Float32Array(9)
    let minSpace = translateGeoLengthToArray(parseDimension(value.minSpace))
    let maxSpace = translateGeoLengthToArray(parseDimension(value.maxSpace))
    options.set(minSpace, 0)
    options.set(maxSpace, 2)
    options[4] = value.conductivity ?? 0.7
    options[5] = value.intensity ?? 0.3
    options[5] = value.intensity ?? 0.3
    options[6] = value.stiffness ?? 0
    options[7] = value.damping ?? 0
    options[8] = value.edgeEffect ?? ChainEdgeEffect.DEFAULT
    return options;
}

export class ArkTextPickerRangeContent {
    icon: string
    text: string
    constructor(value: TextPickerRangeContent) {
        this.icon = value.icon as string ?? ""
        this.text =  value.text as string ?? ""
    }
}

export function translateDataPanelShadowOptions(value: DataPanelShadowOptions): Float32Array {
    let options: Float32Array = new Float32Array(6);
    let radius = translateGeoLengthToArray(parseDimension(value.radius ?? 5))
    let offsetX = translateGeoLengthToArray(parseDimension(value.offsetX ?? 5))
    let offsetY = translateGeoLengthToArray(parseDimension(value.offsetY ?? 5))
    options.set(radius, 0)
    options.set(offsetX, 2)
    options.set(offsetY, 4)
    return options;
}

export function translateResourceToNumber(value: number | Resource): number {
    if (typeof value == 'number') return value as number
    // TODO get value by resource id
    return value.id as number
}

export function flattenFloatColors(colors: any[]) {
    const array = new Float32Array(colors.length * 3)
    for (let i = 0; i < colors.length; i++) {
        const colorSpec = colors[i]
        array[i*3] = translateColorToArkoalaColor(colorSpec[0]).value
        array[i*3 + 1] = 1 // true
        array[i*3 + 2] = clamp(colorSpec[1], 0, 1)
    }
    return array
}
