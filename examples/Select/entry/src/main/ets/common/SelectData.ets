export class Model1 {
  public mValue1: ResourceStr | undefined = undefined
  public mIcon1: ResourceStr | undefined = undefined
  public mValue2: ResourceStr | undefined = undefined
  public mIcon2: ResourceStr | undefined = undefined
  public mValue3: ResourceStr | undefined = undefined
  public mIcon3: ResourceStr | undefined = undefined
  public mValue4: ResourceStr | undefined = undefined
  public mIcon4: ResourceStr | undefined = undefined
  public mValue5: ResourceStr | undefined = undefined
  public mIcon5: ResourceStr | undefined = undefined
  public mSymbolIcon1?: SymbolGlyphModifier | undefined = undefined
  public mSymbolIcon2?: SymbolGlyphModifier | undefined = undefined
  public mSymbolIcon3?: SymbolGlyphModifier | undefined = undefined
  public mSymbolIcon4?: SymbolGlyphModifier | undefined = undefined
  public mSymbolIcon5?: SymbolGlyphModifier | undefined = undefined

  constructor(mSymbolIcon1: SymbolGlyphModifier | undefined = undefined,
    mSymbolIcon2: SymbolGlyphModifier | undefined = undefined,
    mSymbolIcon3: SymbolGlyphModifier | undefined = undefined,
    mSymbolIcon4: SymbolGlyphModifier | undefined = undefined,
    mSymbolIcon5: SymbolGlyphModifier | undefined = undefined, mValue1: ResourceStr = 'undefined',
    mValue2: ResourceStr = 'undefined', mValue3: ResourceStr = 'undefined', mValue4: ResourceStr = 'undefined',
    mValue5: ResourceStr = 'undefined', mIcon1?: ResourceStr, mIcon2?: ResourceStr, mIcon3?: ResourceStr,
    mIcon4?: ResourceStr, mIcon5?: ResourceStr) {
    this.mValue1 = mValue1
    this.mIcon1 = mIcon1
    this.mValue2 = mValue2
    this.mIcon2 = mIcon2
    this.mValue3 = mValue3
    this.mIcon3 = mIcon3
    this.mValue4 = mValue4
    this.mIcon4 = mIcon4
    this.mValue5 = mValue5
    this.mIcon5 = mIcon5
    this.mSymbolIcon1 = mSymbolIcon1
    this.mSymbolIcon2 = mSymbolIcon2
    this.mSymbolIcon3 = mSymbolIcon3
    this.mSymbolIcon4 = mSymbolIcon4
    this.mSymbolIcon5 = mSymbolIcon5

  }
}

export class Model2 {
  public controlSize: ControlSize | undefined = undefined
  public margin: Margin | Length | undefined = undefined
  public width: Length | undefined = undefined
  public selected: number | Resource | undefined = undefined
  public value: string | Resource | undefined = undefined
  public font: Font | undefined = undefined
  public fontColor: ResourceColor | undefined = undefined
  public selectedOptionBgColor: ResourceColor | undefined = undefined
  public selectedOptionFont: Font | undefined = undefined
  public selectedOptionFontColor: ResourceColor | undefined = undefined
  public optionBgColor: ResourceColor | undefined = undefined
  public optionFont: Font | undefined = undefined
  public optionFontColor: ResourceColor | undefined = undefined
  public space: Length | undefined = undefined
  public arrowPosition: ArrowPosition | undefined = undefined
  public menuAlignType: MenuAlignType | undefined = undefined
  public menuAlignOffset: Offset | undefined = undefined
  public optionWidth: Dimension | OptionWidthMode | undefined = undefined
  public optionHeight: Dimension | undefined = undefined
  public divider: Optional<DividerOptions> | null | undefined = undefined

  constructor(controlSize?: ControlSize | undefined, margin?: Margin | Length | undefined, width?: Length | undefined,
    optionWidth?: Dimension | OptionWidthMode, optionHeight?: Dimension, selected?: number, value?: string, font?: Font,
    fontColor?: ResourceColor, selectedOptionBgColor?: ResourceColor, selectedOptionFont?: Font,
    selectedOptionFontColor?: ResourceColor, optionBgColor?: ResourceColor, optionFont?: Font,
    optionFontColor?: ResourceColor, space?: Length, arrowPosition?: ArrowPosition, menuAlignType?: MenuAlignType
    , menuAlignOffset?: Offset, divider?: Optional<DividerOptions> | null | undefined) {
    this.controlSize = controlSize
    this.selected = selected
    this.value = value
    this.font = font
    this.fontColor = fontColor
    this.selectedOptionBgColor = selectedOptionBgColor
    this.selectedOptionFont = selectedOptionFont
    this.selectedOptionFontColor = selectedOptionFontColor
    this.optionBgColor = optionBgColor
    this.optionFont = optionFont
    this.optionFontColor = optionFontColor
    this.space = space
    this.arrowPosition = arrowPosition
    this.menuAlignType = menuAlignType
    this.menuAlignOffset = menuAlignOffset
    this.optionWidth = optionWidth
    this.optionHeight = optionHeight
    this.margin = margin
    this.width = width
    this.divider = divider
  }
}