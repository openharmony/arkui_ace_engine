import { KBoolean, KStringPtr } from "@koalaui/interop"
import { ResourceStr, Padding, Dimension, LocalizedPadding, Font, Length, ResourceColor } from "./ArkUnitsInterfaces"
import { TabBarSymbol, LayoutMode, TabBarIconStyle } from "./ArkTabContentInterfaces"
import { LabelStyle } from "./ArkButtonInterfaces"
import { VerticalAlign, TextOverflow, TextHeightAdaptivePolicy, FontWeight, FontStyle } from "./ArkEnumsInterfaces"
import { SymbolGlyphModifier } from "./ArkCommonInterfaces"
import { LengthMetrics } from "./ArkLengthMetricsMaterialized"
import { Resource } from "./ArkResourceInterfaces"
import { LengthUnit } from "./ArkArkuiExternalInterfaces"
export class BottomTabBarStyle {
    _icon?: ResourceStr | TabBarSymbol | undefined
    _text?: ResourceStr | undefined
    _labelStyle?: LabelStyle | undefined
    _padding?: Padding | Dimension | LocalizedPadding | undefined
    _layoutMode?: LayoutMode | undefined
    _verticalAlign?: VerticalAlign | undefined
    _symmetricExtensible?: boolean | undefined
    _id?: string | undefined
    _iconStyle?: TabBarIconStyle | undefined
     constructor(icon: ResourceStr | TabBarSymbol, text: ResourceStr) {
        this._icon = icon
        this._text = text
    }
    static of(icon: ResourceStr | TabBarSymbol, text: ResourceStr): BottomTabBarStyle {
        return new BottomTabBarStyle(icon, text)
    }
    labelStyle(value: LabelStyle): this {
        this._labelStyle = value
        return this
    }
    padding(value: Padding | Dimension | LocalizedPadding): this {
        this._padding = value
        return this
    }
    layoutMode(value: LayoutMode): this {
        this._layoutMode = value
        return this
    }
    verticalAlign(value: VerticalAlign): this {
        this._verticalAlign = value
        return this
    }
    symmetricExtensible(value: boolean): this {
        this._symmetricExtensible = value
        return this
    }
    id(value: string): this {
        this._id = value
        return this
    }
    iconStyle(style: TabBarIconStyle): this {
        this._iconStyle = style
        return this
    }
}