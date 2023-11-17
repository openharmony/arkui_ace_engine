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

import { KeyCode } from '@ohos.multimodalInput.keyCode'
export enum ChipSize {
  NORMAL = "NORMAL",
  SMALL = "SMALL"
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
  fontSize: Dimension;
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

interface ChipNodeTheme {
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
    fontSize: $r('sys.float.ohos_id_text_size_button3'),
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
    normalHeight: 36,
    smallHeight: 28,
    enabled: true,
    backgroundColor: $r('sys.color.ohos_id_color_button_normal'),
    focusOutlineColor: $r('sys.color.ohos_id_color_focused_outline'),
    normalBorderRadius: $r('sys.float.ohos_id_corner_radius_button'),
    smallBorderRadius: $r('sys.float.ohos_id_corner_radius_small_button'),
    borderWidth: 2,
    normalPadding: { left: 16, right: 16, top: 0, bottom: 0 },
    smallPadding: { left: 12, right: 12, top: 0, bottom: 0 },
    hoverBlendColor: $r('sys.color.ohos_id_color_hover'),
    pressedBlendColor: $r('sys.color.ohos_id_color_click_effect'),
    opacity: { normal: 1, hover: 0.95, pressed: 0.9, disabled: 0.4 }
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
  @Prop chipNodeRadius: Dimension = this.theme.chipNode.normalBorderRadius
  @Prop chipEnabled: boolean = true
  @State isHover: boolean = false
  @State isPressed: boolean = false
  @State chipScale: ScaleOptions = { x: 1, y: 1 }
  @State chipOpacity: number = 1
  @State chipBlendColor: ResourceColor = Color.Transparent
  @State deleteChip: boolean = false
  private chipNodeSize: SizeOptions = {}
  private onClose: () => void = noop
  private useDefaultSuffixIcon: boolean = false

  private isChipSizeEnum(): boolean {
    return typeof (this.chipSize) === 'string'
  }

  private getLabelFontSize(): Dimension {
    return this.label?.fontSize ?? this.theme.label.fontSize
  }

  private getLabelFontColor(): ResourceColor {
    return this.label?.fontColor ?? this.theme.label.fontColor
  }

  private getLabelFontFamily(): string {
    return this.label?.fontFamily ?? this.theme.label.fontFamily
  }

  private getLabelMargin(): Margin {
    return {
      left: this.label?.labelMargin?.left ??
        ((this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) ? this.theme.label.smallMargin.left : this.theme.label.normalMargin.left),
      right: this.label?.labelMargin?.right ??
        ((this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) ? this.theme.label.smallMargin.right : this.theme.label.normalMargin.right)
    }
  }

  private getSuffixIconSize(): SizeOptions {
    return {
      width: this.suffixIcon?.size?.width ?? ((this.suffixIcon?.src || this.useDefaultSuffixIcon) ? this.theme.suffixIcon.size.width : 0),
      height: this.suffixIcon?.size?.height ?? ((this.suffixIcon?.src || this.useDefaultSuffixIcon) ? this.theme.suffixIcon.size.height : 0)
    }
  }

  private getPrefixIconSize(): SizeOptions {
    return {
      width: this.prefixIcon?.size?.width ?? (this.prefixIcon?.src ? this.theme.prefixIcon.size.width : 0),
      height: this.prefixIcon?.size?.height ?? (this.prefixIcon?.src ? this.theme.prefixIcon.size.height : 0)
    }
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
    return (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) ? this.theme.chipNode.smallPadding : this.theme.chipNode.normalPadding
  }

  private getChipNodeRadius(): Dimension {
    return this.chipNodeRadius ?? (
      (this.isChipSizeEnum() && this.chipSize === ChipSize.SMALL) ? this.theme.chipNode.smallBorderRadius : this.theme.chipNode.normalBorderRadius)
  }

  private getChipNodeBackGroundColor(): ResourceColor {
    return this.chipNodeBackgroundColor ?? this.theme.chipNode.backgroundColor
  }

  private getChipNodeHeight(): Length {
    if (this.isChipSizeEnum()) {
      return this.chipSize === ChipSize.SMALL ? this.theme.chipNode.smallHeight : this.theme.chipNode.normalHeight
    } else {
      this.chipNodeSize = this.chipSize as SizeOptions
      return this.chipNodeSize?.height ?? this.theme.chipNode.normalHeight
    }
  }

  private getChipNodeOpacity(): number {
    return this.chipEnabled ? this.chipOpacity : this.theme.chipNode.opacity.disabled
  }

  private handleTouch(event: TouchEvent) {
    if (!this.chipEnabled) {
      return
    }
    this.isPressed = (event.type === TouchType.Down)
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
    if (!this.chipEnabled) {
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
    })
    animateTo({ duration: 150, curve: Curve.FastOutLinearIn, onFinish: () => {
      this.deleteChip = true
    } },
      () => {
        this.chipScale = { x: 0.85, y: 0.85 }
      })
  }

  private getSuffixIconSrc(): ResourceStr {
    if (!this.suffixIcon?.src && this.allowClose) {
      this.useDefaultSuffixIcon = true
      return this.theme.suffixIcon.defaultDeleteIcon
    }
    return this.suffixIcon.src
  }

  private getChipNodeWidth(): Length | undefined {
    if (!this.isChipSizeEnum()) {
      this.chipNodeSize = this.chipSize as SizeOptions
      return this.chipNodeSize?.width
    }
    return void (0)
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

  @Builder
  chipBuilder() {
    Row() {
      if (this.prefixIcon.src) {
        Image(this.prefixIcon.src)
          .opacity(this.getChipNodeOpacity())
          .size(this.getPrefixIconSize())
          .fillColor(this.getPrefixIconFilledColor())
          .enabled(this.chipEnabled)
          .objectFit(ImageFit.Cover)
          .focusable(false)
          .flexShrink(0)
      }

      Text(this.label.text)
        .opacity(this.getChipNodeOpacity())
        .fontSize(this.getLabelFontSize())
        .fontColor(this.getLabelFontColor())
        .fontFamily(this.getLabelFontFamily())
        .margin(this.getLabelMargin())
        .enabled(this.chipEnabled)
        .maxLines(1)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
        .flexShrink(1)
        .focusable(true)

      Image(this.getSuffixIconSrc())
        .opacity(this.getChipNodeOpacity())
        .size(this.getSuffixIconSize())
        .fillColor(this.getSuffixIconFilledColor())
        .enabled(this.chipEnabled)
        .focusable(this.getSuffixIconFocusable())
        .objectFit(ImageFit.Cover)
        .flexShrink(0)
        .stateStyles({
          focused: this.suffixIconFocusStyles,
          normal: this.suffixIconNormalStyles,
        })
        .onClick(() => {
          if (!this.chipEnabled) {
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
    .justifyContent(FlexAlign.Center)
    .clip(true)
    .padding(this.getChipNodePadding())
    .height(this.getChipNodeHeight())
    .width(this.getChipNodeWidth())
    .backgroundColor(this.getChipNodeBackGroundColor())
    .borderRadius(this.getChipNodeRadius())
    .enabled(this.chipEnabled)
    .scale(this.chipScale)
    .focusable(true)
    .colorBlend(this.chipBlendColor)
    .opacity(this.getChipNodeOpacity())
    .onTouch((event) => {
      this.handleTouch(event)
    })
    .onHover((isHover: boolean) => {
      this.hoverAnimate(isHover)
    })
    .onKeyEvent((event) => {
      if (event.type === KeyType.Down && event.keyCode === KeyCode.KEYCODE_FORWARD_DEL) {
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
