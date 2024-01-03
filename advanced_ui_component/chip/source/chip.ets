/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

import { KeyCode } from '@ohos.multimodalInput.keyCode';
import measure from '@ohos.measure';
import mediaquery from '@ohos.mediaquery';
import resourceManager from '@ohos.resourceManager';

export enum ChipSize {
  NORMAL = "NORMAL",
  SMALL = "SMALL"
}

enum BreakPointsType {
  SM = "SM",
  MD = "MD",
  LG = "LG"
}

export interface IconCommonOptions {
  src: ResourceStr;
  size?: SizeOptions;
  fillColor?: ResourceColor
}

export interface SuffixIconOptions extends IconCommonOptions {
  action?: () => void;
}

export interface PrefixIconOptions extends IconCommonOptions {}

export interface LabelMarginOptions {
  left?: Dimension;
  right?: Dimension;
}

export interface LabelOptions {
  text: string;
  fontSize?: Dimension;
  fontColor?: ResourceColor;
  fontFamily?: string;
  labelMargin?: LabelMarginOptions;
}

interface IconTheme {
  size: SizeOptions;
  fillColor: ResourceColor;
}

interface PrefixIconTheme extends IconTheme {}

interface SuffixIconTheme extends IconTheme {
  defaultDeleteIcon: ResourceStr;
  focusable: boolean;
}

interface LabelTheme {
  normalFontSize: Dimension;
  smallFontSize: Dimension;
  fontColor: ResourceColor;
  fontFamily: string;
  normalMargin: Margin;
  smallMargin: Margin;
}

interface ChipNodeOpacity {
  normal: number;
  hover: number;
  pressed: number;
  disabled: number;
}

interface ChipNodeConstraintWidth {
  breakPointMinWidth: number,
  breakPointSmMaxWidth: number,
  breakPointMdMaxWidth: number,
  breakPointLgMaxWidth: number,
}

interface ChipNodeTheme {
  minLabelWidth: Dimension;
  normalHeight: Dimension;
  smallHeight: Dimension;
  enabled: boolean;
  backgroundColor: ResourceColor;
  focusOutlineColor: ResourceColor;
  normalBorderRadius: Dimension;
  smallBorderRadius: Dimension;
  borderWidth: number;
  normalPadding: Padding;
  smallPadding: Padding;
  hoverBlendColor: ResourceColor;
  pressedBlendColor: ResourceColor;
  opacity: ChipNodeOpacity;
  breakPointConstraintWidth: ChipNodeConstraintWidth;
}

interface ChipTheme {
  prefixIcon: PrefixIconTheme;
  label: LabelTheme;
  suffixIcon: SuffixIconTheme;
  chipNode: ChipNodeTheme;
}

export const defaultTheme: ChipTheme = {
  prefixIcon: {
    size: { width: 16, height: 16 },
    fillColor: $r('sys.color.ohos_id_color_secondary'),
  },
  label: {
    normalFontSize: $r('sys.float.ohos_id_text_size_button2'),
    smallFontSize: $r('sys.float.ohos_id_text_size_button3'),
    fontColor: $r('sys.color.ohos_id_color_text_primary'),
    fontFamily: "HarmonyOS Sans",
    normalMargin: { left: 6, right: 6, top: 0, bottom: 0 },
    smallMargin: { left: 4, right: 4, top: 0, bottom: 0 },
  },
  suffixIcon: {
    size: { width: 16, height: 16 },
    fillColor: $r('sys.color.ohos_id_color_primary'),
    defaultDeleteIcon: $r('sys.media.ohos_ic_public_cancel', 16, 16),
    focusable: false,
  },
  chipNode: {
    minLabelWidth: 12,
    normalHeight: 36,
    smallHeight: 28,
    enabled: true,
    backgroundColor: $r('sys.color.ohos_id_color_button_normal'),
    focusOutlineColor: $r('sys.color.ohos_id_color_focused_outline'),
    normalBorderRadius: $r('sys.float.ohos_id_corner_radius_tips_instant_tip'),
    smallBorderRadius: $r('sys.float.ohos_id_corner_radius_piece'),
    borderWidth: 2,
    normalPadding: { left: 16, right: 16, top: 0, bottom: 0 },
    smallPadding: { left: 12, right: 12, top: 0, bottom: 0 },
    hoverBlendColor: $r('sys.color.ohos_id_color_hover'),
    pressedBlendColor: $r('sys.color.ohos_id_color_click_effect'),
    opacity: { normal: 1, hover: 0.95, pressed: 0.9, disabled: 0.4 },
    breakPointConstraintWidth: {
      breakPointMinWidth: 128,
      breakPointSmMaxWidth: 156,
      breakPointMdMaxWidth: 280,
      breakPointLgMaxWidth: 400
    }
  }
};

const noop = () => {
};

interface ChipOptions {
  prefixIcon?: PrefixIconOptions;
  label: LabelOptions;
  suffixIcon?: SuffixIconOptions;
  allowClose?: boolean;
  enabled?: boolean;
  backgroundColor?: ResourceColor;
  borderRadius?: Dimension;
  size?: ChipSize | SizeOptions;
  onClose?: () => void
}

@Builder
export function Chip(options: ChipOptions) {
  ChipComponent({
    chipSize: options.size,
    prefixIcon: options.prefixIcon,
    label: options.label,
    suffixIcon: options.suffixIcon,
    allowClose: options.allowClose,
    chipEnabled: options.enabled,
    chipNodeBackgroundColor: options.backgroundColor,
    chipNodeRadius: options.borderRadius,
    onClose: options.onClose
  })
}

@Component
export struct ChipComponent {
  private theme: ChipTheme = defaultTheme;
  @Prop chipSize: ChipSize | SizeOptions = ChipSize.NORMAL
  @Prop allowClose: boolean = true
  @Prop prefixIcon: PrefixIconOptions = { src: "" }
  @Prop label: LabelOptions = { text: "" }
  @Prop suffixIcon: SuffixIconOptions = { src: "" }
  @Prop chipNodeBackgroundColor: ResourceColor = this.theme.chipNode.backgroundColor
  @Prop chipNodeRadius: Dimension | undefined = void (0)
  @Prop chipEnabled: boolean = true
  @State isHover: boolean = false
  @State chipScale: ScaleOptions = { x: 1, y: 1 }
  @State chipOpacity: number = 1
  @State chipBlendColor: ResourceColor = Color.Transparent
  @State deleteChip: boolean = false
  @State chipNodeOnFocus: boolean = false
  @State useDefaultSuffixIcon: boolean = false
  private chipNodeSize: SizeOptions = {}
  private onClose: () => void = noop
  @State suffixIconOnFocus: boolean = false
  @State chipBreakPoints: BreakPointsType = BreakPointsType.SM
  private smListener: mediaquery.MediaQueryListener = mediaquery.matchMediaSync("0vp<width<600vp")
  private mdListener: mediaquery.MediaQueryListener = mediaquery.matchMediaSync("600vp<=width<840vp")
  private lgListener: mediaquery.MediaQueryListener = mediaquery.matchMediaSync("840vp<=width")

  private isChipSizeEnum(): boolean {
    return typeof (this.chipSize) === 'string'
  }

  private getLabelFontSize(): Dimension {
    try {
      if (this.label?.fontSize !== void (0) && this.toVp(this.label.fontSize) >= 0) {
        return this.label.fontSize
      } else {
        if (this.isChipSizeEnum() && this.chipSize === ChipSize.SMALL) {
          return resourceManager.getSystemResourceManager()
            .getNumberByName((((this.theme.label.smallFontSize as Resource).params as string[])[0]).split('.')[2])
        } else {
          return resourceManager.getSystemResourceManager()
            .getNumberByName((((this.theme.label.normalFontSize as Resource).params as string[])[0]).split('.')[2])
        }
      }
    }
    catch (error) {
      return 0
    }

  }

  private getLabelFontColor(): ResourceColor {
    return this.label?.fontColor ?? this.theme.label.fontColor
  }

  private getLabelFontFamily(): string {
    return this.label?.fontFamily ?? this.theme.label.fontFamily
  }

  private toVp(value: Dimension | Length | undefined): number {
    if (value === void (0)) {
      return Number.NEGATIVE_INFINITY
    }
    switch (typeof (value)) {
      case 'number':
        return value as number
      case 'object':
        try {
          if ((value as Resource).id !== -1) {
            return px2vp(getContext(this).resourceManager.getNumber((value as Resource).id))
          } else {
            return px2vp(getContext(this)
              .resourceManager
              .getNumberByName(((value.params as string[])[0]).split('.')[2]))
          }
        } catch (error) {
          return Number.NEGATIVE_INFINITY
        }
      case 'string':
        let regex: RegExp = new RegExp("(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$", "i");
        let matches: RegExpMatchArray | null = value.match(regex);
        if (!matches) {
          return Number.NEGATIVE_INFINITY
        }
        let length: number = Number(matches?.[1] ?? 0);
        let unit: string = matches?.[2] ?? 'vp'
        switch (unit.toLowerCase()) {
          case 'px':
            length = px2vp(length)
            break
          case 'fp':
            length = px2vp(fp2px(length))
            break
          case 'lpx':
            length = px2vp(lpx2px(length))
            break
          case '%':
            length = Number.NEGATIVE_INFINITY
            break
          case 'vp':
            break
          default:
            break
        }
        return length
      default:
        return Number.NEGATIVE_INFINITY
    }
  }

  private getLabelMargin(): Margin {
    let labelMargin: Margin = { left: 0, right: 0 }
    if (this.label?.labelMargin?.left !== void (0) && this.toVp(this.label.labelMargin.left) >= 0) {
      labelMargin.left = this.label?.labelMargin?.left
    } else if (this.prefixIcon?.src) {
      if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
        labelMargin.left = this.theme.label.smallMargin.left
      } else {
        labelMargin.left = this.theme.label.normalMargin.left
      }
    }
    if (this.label?.labelMargin?.right !== void (0) && this.toVp(this.label.labelMargin.right) >= 0) {
      labelMargin.right = this.label?.labelMargin?.right
    } else if (this.suffixIcon?.src || this.useDefaultSuffixIcon) {
      if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
        labelMargin.right = this.theme.label.smallMargin.right
      } else {
        labelMargin.right = this.theme.label.normalMargin.right
      }

    }
    return labelMargin
  }

  private getSuffixIconSize(): SizeOptions {
    let suffixIconSize: SizeOptions = { width: 0, height: 0 }
    if (this.suffixIcon?.size?.width !== void (0) && this.toVp(this.suffixIcon?.size?.width) >= 0) {
      suffixIconSize.width = this.suffixIcon?.size?.width
    } else {
      if (this.getSuffixIconSrc()) {
        suffixIconSize.width = this.theme.suffixIcon.size.width
      } else {
        suffixIconSize.width = 0
      }
    }
    if (this.suffixIcon?.size?.height !== void (0) && this.toVp(this.suffixIcon?.size?.height) >= 0) {
      suffixIconSize.height = this.suffixIcon?.size?.height
    } else {
      if (this.getSuffixIconSrc()) {
        suffixIconSize.height = this.theme.suffixIcon.size.height
      } else {
        suffixIconSize.height = 0
      }
    }
    return suffixIconSize
  }

  private getPrefixIconSize(): SizeOptions {
    let prefixIconSize: SizeOptions = { width: 0, height: 0 }
    if (this.prefixIcon?.size?.width !== void (0) && this.toVp(this.prefixIcon?.size?.width) >= 0) {
      prefixIconSize.width = this.prefixIcon?.size?.width
    } else {
      if (this.prefixIcon?.src) {
        prefixIconSize.width = this.theme.prefixIcon.size.width
      } else {
        prefixIconSize.width = 0
      }
    }
    if (this.prefixIcon?.size?.height !== void (0) && this.toVp(this.prefixIcon?.size?.height) >= 0) {
      prefixIconSize.height = this.prefixIcon?.size?.height
    } else {
      if (this.prefixIcon?.src) {
        prefixIconSize.height = this.theme.prefixIcon.size.height
      } else {
        prefixIconSize.height = 0
      }
    }
    return prefixIconSize
  }

  private getPrefixIconFilledColor(): ResourceColor {
    return this.prefixIcon?.fillColor ?? this.theme.prefixIcon.fillColor
  }

  private getSuffixIconFilledColor(): ResourceColor {
    return this.suffixIcon?.fillColor ?? this.theme.suffixIcon.fillColor
  }

  private getSuffixIconFocusable(): boolean {
    return (this.useDefaultSuffixIcon && this.allowClose) || this.suffixIcon?.action !== void (0)
  }

  private getChipNodePadding(): Padding {
    return (this.isChipSizeEnum() && this.chipSize === ChipSize.SMALL) ? this.theme.chipNode.smallPadding : this.theme.chipNode.normalPadding
  }

  private getChipNodeRadius(): Dimension {
    if (this.chipNodeRadius !== void (0) && this.toVp(this.chipNodeRadius) >= 0) {
      return this.chipNodeRadius as Dimension
    } else {
      return ((this.isChipSizeEnum() && this.chipSize === ChipSize.SMALL) ? this.theme.chipNode.smallBorderRadius : this.theme.chipNode.normalBorderRadius)
    }
  }

  private getChipNodeBackGroundColor(): ResourceColor {
    return this.chipNodeBackgroundColor ?? this.theme.chipNode.backgroundColor
  }

  private getChipNodeHeight(): Length {
    if (this.isChipSizeEnum()) {
      return this.chipSize === ChipSize.SMALL ? this.theme.chipNode.smallHeight : this.theme.chipNode.normalHeight
    } else {
      this.chipNodeSize = this.chipSize as SizeOptions
      return (this.chipNodeSize?.height !== void (0) && this.toVp(this.chipNodeSize?.height) >= 0) ? this.toVp(this.chipNodeSize?.height) : this.theme.chipNode.normalHeight
    }
  }

  private getLabelWidth(): number {
    return px2vp(measure.measureText({
      textContent: this.label?.text ?? "",
      fontSize: this.getLabelFontSize(),
      fontFamily: this.label?.fontFamily ?? this.theme.label.fontFamily,
      maxLines: 1,
      overflow: TextOverflow.Ellipsis,
      textAlign: TextAlign.Center
    }))
  }

  private getCalculateChipNodeWidth(): number {
    let calWidth: number = 0
    calWidth += this.getChipNodePadding().left as number
    calWidth += this.toVp(this.getPrefixIconSize().width)
    calWidth += this.toVp(this.getLabelMargin().left)
    calWidth += this.getLabelWidth()
    calWidth += this.toVp(this.getLabelMargin().right)
    calWidth += this.toVp(this.getSuffixIconSize().width)
    calWidth += this.getChipNodePadding().right as number
    return calWidth
  }

  private getReserveChipNodeWidth(): number {
    return this.getCalculateChipNodeWidth() - this.getLabelWidth() + (this.theme.chipNode.minLabelWidth as number)
  }

  private getChipEnable(): boolean {
    return this.chipEnabled || this.chipEnabled === void (0)
  }

  private getChipNodeOpacity(): number {
    return this.getChipEnable() ? this.chipOpacity : this.theme.chipNode.opacity.disabled
  }

  private handleTouch(event: TouchEvent) {
    if (!this.getChipEnable()) {
      return
    }
    if (this.isHover) {
      if (event.type === TouchType.Down) {
        animateTo({ curve: Curve.Sharp, duration: 100 }, () => {
          this.chipBlendColor = this.theme.chipNode.pressedBlendColor
          this.chipOpacity = this.theme.chipNode.opacity.pressed
        })
      } else if (event.type === TouchType.Up) {
        animateTo({ curve: Curve.Sharp, duration: 100 }, () => {
          this.chipBlendColor = this.theme.chipNode.hoverBlendColor
          this.chipOpacity = this.theme.chipNode.opacity.hover
        })
      }
    } else {
      if (event.type === TouchType.Down) {
        animateTo({ curve: Curve.Friction, duration: 350 }, () => {
          this.chipBlendColor = this.theme.chipNode.pressedBlendColor
          this.chipOpacity = this.theme.chipNode.opacity.pressed
        })
      } else if (event.type === TouchType.Up) {
        animateTo({ curve: Curve.Friction, duration: 350 }, () => {
          this.chipBlendColor = Color.Transparent
          this.chipOpacity = this.theme.chipNode.opacity.normal
        })
      }
    }
  }

  private hoverAnimate(isHover: boolean) {
    if (!this.getChipEnable()) {
      return
    }
    this.isHover = isHover
    animateTo({
      curve: Curve.Friction,
      duration: 250
    }, () => {
      if (isHover) {
        this.chipBlendColor = this.theme.chipNode.hoverBlendColor
        this.chipOpacity = this.theme.chipNode.opacity.hover
      } else {
        this.chipBlendColor = Color.Transparent
        this.chipOpacity = this.theme.chipNode.opacity.normal
      }
    })
  }

  private deleteChipNodeAnimate() {
    animateTo({ duration: 150, curve: Curve.Sharp }, () => {
      this.chipOpacity = 0
      this.chipBlendColor = Color.Transparent
    })
    animateTo({ duration: 150, curve: Curve.FastOutLinearIn, onFinish: () => {
      this.deleteChip = true
    } },
      () => {
        this.chipScale = { x: 0.85, y: 0.85 }
      })
  }

  private getSuffixIconSrc(): ResourceStr | undefined {
    this.useDefaultSuffixIcon = !this.suffixIcon?.src && this.allowClose
    return this.useDefaultSuffixIcon ? this.theme.suffixIcon.defaultDeleteIcon : (this.suffixIcon?.src ?? void (0))
  }

  private getChipNodeWidth(): Length {
    if (!this.isChipSizeEnum()) {
      this.chipNodeSize = this.chipSize as SizeOptions
      if (this.chipNodeSize?.width !== void (0) && this.toVp(this.chipNodeSize.width) >= 0) {
        return this.toVp(this.chipNodeSize.width)
      }
    }
    let constraintWidth: ConstraintSizeOptions = this.getChipConstraintWidth()
    return Math.min(Math.max(this.getCalculateChipNodeWidth(), constraintWidth.minWidth as number), constraintWidth.maxWidth as number);
  }

  private getFocusOverlaySize(): SizeOptions {
    return {
      width: Math.max(this.getChipNodeWidth() as number, this.getChipConstraintWidth().minWidth as number) + 8,
      height: this.getChipNodeHeight() as number + 8
    }
  }

  private getChipConstraintWidth(): ConstraintSizeOptions {
    let calcMinWidth: number = this.getReserveChipNodeWidth()
    if (!this.isChipSizeEnum()) {
      this.chipNodeSize = this.chipSize as SizeOptions
      if (this.chipNodeSize?.width !== void (0) && this.toVp(this.chipNodeSize?.width) >= 0) {
        return { minWidth: calcMinWidth, maxWidth: this.chipNodeSize.width as number }
      }
    }

    let constraintWidth: number = this.getCalculateChipNodeWidth()
    switch (this.chipBreakPoints) {
      case BreakPointsType.SM:
        return {
          minWidth: calcMinWidth,
          maxWidth: Math.min(constraintWidth, this.theme.chipNode.breakPointConstraintWidth.breakPointSmMaxWidth)
        }
      case BreakPointsType.MD:
        return {
          minWidth: Math.max(constraintWidth, this.theme.chipNode.breakPointConstraintWidth.breakPointMinWidth),
          maxWidth: Math.min(constraintWidth, this.theme.chipNode.breakPointConstraintWidth.breakPointMdMaxWidth)
        }

      case BreakPointsType.LG:
        return {
          minWidth: Math.max(constraintWidth, this.theme.chipNode.breakPointConstraintWidth.breakPointMinWidth),
          maxWidth: Math.min(constraintWidth, this.theme.chipNode.breakPointConstraintWidth.breakPointLgMaxWidth)
        }
      default:
        return { minWidth: calcMinWidth, maxWidth: constraintWidth }
    }
  }

  @Builder
  focusOverlay() {
    Stack() {
      if (this.chipNodeOnFocus && !this.suffixIconOnFocus) {
        Stack()
          .borderRadius(this.toVp(this.getChipNodeRadius()) + 4)
          .size(this.getFocusOverlaySize())
          .borderColor(this.theme.chipNode.focusOutlineColor)
          .borderWidth(this.theme.chipNode.borderWidth)
      }
    }
    .size({ width: 1, height: 1 })
    .align(Alignment.Center)
  }

  @Styles
  suffixIconFocusStyles() {
    .borderColor(this.theme.chipNode.focusOutlineColor)
    .borderWidth(this.getSuffixIconFocusable() ? this.theme.chipNode.borderWidth : 0)
  }

  @Styles
  suffixIconNormalStyles() {
    .borderColor(Color.Transparent)
    .borderWidth(0)
  }

  aboutToAppear() {
    this.smListener.on("change", (mediaQueryResult: mediaquery.MediaQueryResult) => {
      if (mediaQueryResult.matches) {
        this.chipBreakPoints = BreakPointsType.SM
      }
    })
    this.mdListener.on("change", (mediaQueryResult: mediaquery.MediaQueryResult) => {
      if (mediaQueryResult.matches) {
        this.chipBreakPoints = BreakPointsType.MD
      }
    })
    this.lgListener.on("change", (mediaQueryResult: mediaquery.MediaQueryResult) => {
      if (mediaQueryResult.matches) {
        this.chipBreakPoints = BreakPointsType.LG
      }
    })
  }

  private getVisibility(): Visibility {
    if (this.toVp(this.getChipNodeHeight()) > 0) {
      return Visibility.Visible
    } else {
      return Visibility.None
    }
  }

  aboutToDisappear() {
    this.smListener.off("change")
    this.mdListener.off("change")
    this.lgListener.off("change")
  }

  @Builder
  chipBuilder() {
    Row() {
      if (this.prefixIcon?.src !== "") {
        Image(this.prefixIcon?.src)
          .opacity(this.getChipNodeOpacity())
          .size(this.getPrefixIconSize())
          .fillColor(this.getPrefixIconFilledColor())
          .enabled(this.getChipEnable())
          .objectFit(ImageFit.Cover)
          .focusable(false)
          .flexShrink(0)
          .visibility(this.getVisibility())
          .draggable(false)
      }

      Text(this.label?.text ?? "")
        .opacity(this.getChipNodeOpacity())
        .fontSize(this.getLabelFontSize())
        .fontColor(this.getLabelFontColor())
        .fontFamily(this.getLabelFontFamily())
        .margin(this.getLabelMargin())
        .enabled(this.getChipEnable())
        .maxLines(1)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
        .flexShrink(1)
        .focusable(true)
        .textAlign(TextAlign.Center)
        .visibility(this.getVisibility())
        .draggable(false)

      Image(this.getSuffixIconSrc())
        .opacity(this.getChipNodeOpacity())
        .size(this.getSuffixIconSize())
        .fillColor(this.getSuffixIconFilledColor())
        .enabled(this.getChipEnable())
        .focusable(this.getSuffixIconFocusable())
        .objectFit(ImageFit.Cover)
        .flexShrink(0)
        .visibility(this.getVisibility())
        .draggable(false)
        .stateStyles({
          focused: this.suffixIconFocusStyles,
          normal: this.suffixIconNormalStyles,
        })
        .onFocus(() => {
          this.suffixIconOnFocus = true
        })
        .onBlur(() => {
          this.suffixIconOnFocus = false
        })
        .onClick(() => {
          if (!this.getChipEnable()) {
            return
          }
          if (this.suffixIcon?.action) {
            this.suffixIcon.action()
            return
          }
          if (this.allowClose && this.useDefaultSuffixIcon) {
            this.onClose()
            this.deleteChipNodeAnimate()
            return
          }
        })
    }
    .alignItems(VerticalAlign.Center)
    .justifyContent(FlexAlign.Center)
    .clip(false)
    .padding(this.getChipNodePadding())
    .height(this.getChipNodeHeight())
    .width(this.getChipNodeWidth())
    .constraintSize(this.getChipConstraintWidth())
    .backgroundColor(this.getChipNodeBackGroundColor())
    .borderRadius(this.getChipNodeRadius())
    .enabled(this.getChipEnable())
    .scale(this.chipScale)
    .focusable(true)
    .colorBlend(this.chipBlendColor)
    .opacity(this.getChipNodeOpacity())
    .overlay(this.focusOverlay, { align: Alignment.Center })
    .onFocus(() => {
      this.chipNodeOnFocus = true
    })
    .onBlur(() => {
      this.chipNodeOnFocus = false
    })
    .onTouch((event) => {
      this.handleTouch(event)
    })
    .onHover((isHover: boolean) => {
      this.hoverAnimate(isHover)
    })
    .onKeyEvent((event) => {
      if (event.type === KeyType.Down && event.keyCode === KeyCode.KEYCODE_FORWARD_DEL && !this.suffixIconOnFocus) {
        this.deleteChipNodeAnimate()
      }
    })
  }

  build() {
    if (!this.deleteChip) {
      this.chipBuilder()
    }
  }
}