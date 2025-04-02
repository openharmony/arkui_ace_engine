import { KBoolean, KStringPtr } from "@koalaui/interop"
import { ResourceStr, Padding, Dimension, LocalizedPadding, Length, ResourceColor, Font } from "./ArkUnitsInterfaces"
import { ComponentContent } from "./ArkCommonInterfaces"
import { IndicatorStyle } from "./ArkSwiperInterfaces"
import { SelectedMode, BoardStyle } from "./ArkTabContentInterfaces"
import { LabelStyle } from "./ArkButtonInterfaces"
import { TextOverflow, TextHeightAdaptivePolicy, FontWeight, FontStyle } from "./ArkEnumsInterfaces"
import { LengthMetrics } from "./ArkLengthMetricsMaterialized"
import { Resource } from "./ArkResourceInterfaces"
import { LengthUnit } from "./ArkArkuiExternalInterfaces"
export class SubTabBarStyle {
    _content?: ResourceStr | ResourceStr | ComponentContent | undefined
    _indicator?: IndicatorStyle | undefined
    _selectedMode?: SelectedMode | undefined
    _board?: BoardStyle | undefined
    _labelStyle?: LabelStyle | undefined
    _padding?: Padding | Dimension | LocalizedPadding | undefined
    _id?: string | undefined
     constructor(content: ResourceStr | ResourceStr | ComponentContent) {
        this._content = content
    }
    public static of(content: ResourceStr | ResourceStr | ComponentContent): SubTabBarStyle {
        return new SubTabBarStyle(content)
    }
    indicator(value: IndicatorStyle): this {
        this._indicator = value
        return this
    }
    selectedMode(value: SelectedMode): this {
        this._selectedMode = value
        return this
    }
    board(value: BoardStyle): this {
        this._board = value
        return this
    }
    labelStyle(value: LabelStyle): this {
        this._labelStyle = value
        return this
    }
    public padding(value: Padding | Dimension | LocalizedPadding): this {
        this._padding = value
        return this
    }
    id(value: string): this {
        this._id = value
        return this
    }
}