import { KBoolean, KStringPtr } from "@koalaui/interop"
import { Indicator } from "./ArkIndicatorBuilder"
import { Length, ResourceColor, Font } from "./ArkUnitsInterfaces"
import { LengthMetrics } from "./ArkLengthMetricsMaterialized"
import { DigitIndicator } from "./ArkDigitIndicatorBuilder"
import { LengthUnit } from "./ArkArkuiExternalInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { FontWeight, FontStyle } from "./ArkEnumsInterfaces"
export class DotIndicator {
    _left?: Length | undefined
    _top?: Length | undefined
    _right?: Length | undefined
    _bottom?: Length | undefined
    _start?: LengthMetrics | undefined
    _end?: LengthMetrics | undefined
    _itemWidth?: Length | undefined
    _itemHeight?: Length | undefined
    _selectedItemWidth?: Length | undefined
    _selectedItemHeight?: Length | undefined
    _mask?: boolean | undefined
    _color?: ResourceColor | undefined
    _selectedColor?: ResourceColor | undefined
    _maxDisplayCount?: number | undefined
     constructor() {
    }
    static dot(): DotIndicator {
        return new DotIndicator()
    }
    static digit(): DigitIndicator {
        return new DigitIndicator()
    }
    left(value: Length): this {
        this._left = value
        return this
    }
    top(value: Length): this {
        this._top = value
        return this
    }
    right(value: Length): this {
        this._right = value
        return this
    }
    bottom(value: Length): this {
        this._bottom = value
        return this
    }
    start(value: LengthMetrics): this {
        this._start = value
        return this
    }
    end(value: LengthMetrics): this {
        this._end = value
        return this
    }
    itemWidth(value: Length): this {
        this._itemWidth = value
        return this
    }
    itemHeight(value: Length): this {
        this._itemHeight = value
        return this
    }
    selectedItemWidth(value: Length): this {
        this._selectedItemWidth = value
        return this
    }
    selectedItemHeight(value: Length): this {
        this._selectedItemHeight = value
        return this
    }
    mask(value: boolean): this {
        this._mask = value
        return this
    }
    color(value: ResourceColor): this {
        this._color = value
        return this
    }
    selectedColor(value: ResourceColor): this {
        this._selectedColor = value
        return this
    }
    maxDisplayCount(maxDisplayCount: number): this {
        this._maxDisplayCount = maxDisplayCount
        return this
    }
}