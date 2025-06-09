import { KBoolean, KStringPtr } from "@koalaui/interop"
import { Indicator } from "./ArkIndicatorBuilder"
import { Length, ResourceColor, Font } from "./ArkUnitsInterfaces"
import { LengthMetrics } from "./ArkLengthMetricsMaterialized"
import { DotIndicator } from "./ArkDotIndicatorBuilder"
export class DigitIndicator {
    _left?: Length | undefined
    _top?: Length | undefined
    _right?: Length | undefined
    _bottom?: Length | undefined
    _start?: LengthMetrics | undefined
    _end?: LengthMetrics | undefined
    _fontColor?: ResourceColor | undefined
    _selectedFontColor?: ResourceColor | undefined
    _digitFont?: Font | undefined
    _selectedDigitFont?: Font | undefined
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
    fontColor(value: ResourceColor): this {
        this._fontColor = value
        return this
    }
    selectedFontColor(value: ResourceColor): this {
        this._selectedFontColor = value
        return this
    }
    digitFont(value: Font): this {
        this._digitFont = value
        return this
    }
    selectedDigitFont(value: Font): this {
        this._selectedDigitFont = value
        return this
    }
}