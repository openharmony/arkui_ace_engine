import { KBoolean, KStringPtr } from "@koalaui/interop"
import { Length, ResourceColor, Font } from "./ArkUnitsInterfaces"
import { LengthMetrics } from "./ArkLengthMetricsMaterialized"
import { DotIndicator } from "./ArkDotIndicatorBuilder"
import { DigitIndicator } from "./ArkDigitIndicatorBuilder"
import { LengthUnit } from "./ArkArkuiExternalInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { FontWeight, FontStyle } from "./ArkEnumsInterfaces"
export class Indicator<T> {
    _left?: Length | undefined
    _top?: Length | undefined
    _right?: Length | undefined
    _bottom?: Length | undefined
    _start?: LengthMetrics | undefined
    _end?: LengthMetrics | undefined
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
}