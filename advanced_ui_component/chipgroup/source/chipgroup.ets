/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import { Chip, ChipSize } from '@ohos.arkui.advanced.Chip'

interface ChipGroupTheme {
  itemStyle: ChipItemStyle;
  chipGroupSpace: ChipGroupSpaceOptions;
  leftPadding:number;
  rightPadding:number;
}

const noop = (selectedIndexes: Array<number>) => {
}
const alpha: Array<[string, number]> = [['rgba(0, 0, 0, 1)', 0.5], ['rgba(0, 0, 0, 0)', 1]]
const defaultTheme: ChipGroupTheme = {
  itemStyle: {
    size: ChipSize.NORMAL,
    backgroundColor: $r('sys.color.ohos_id_color_button_normal'),
    fontColor: $r('sys.color.ohos_id_color_text_primary'),
    selectedFontColor: $r('sys.color.ohos_id_color_text_primary_contrary'),
    selectedBackgroundColor: $r('sys.color.ohos_id_color_emphasize'),
  },
  chipGroupSpace: { itemSpace: 8, startSpace: 16, endSpace: 0 },
  leftPadding:0,
  rightPadding:8,
}

const chipGroupSuffixTheme: BuilderTheme = {
  backgroundColor: $r('sys.color.ohos_id_color_button_normal'),
  borderRadius: $r('sys.float.ohos_id_corner_radius_tips_instant_tip'),
  smallIconSize: 16,
  normalIconSize: 24,
  smallBackgroundSize: 28,
  normalbackgroundSize: 36,
  marginLeft: 8,
}

interface IconOptions {
  src: ResourceStr;
  size?: SizeOptions;
}

interface LabelOptions {
  text: string;
}

interface ChipGroupItemOptions {
  prefixIcon?: IconOptions;
  label: LabelOptions;
  suffixIcon?: IconOptions;
  allowClose?: boolean;
}

interface ChipItemStyle {
  size?: ChipSize | SizeOptions;
  backgroundColor?: ResourceColor;
  fontColor?: ResourceColor;
  selectedFontColor?: ResourceColor;
  selectedBackgroundColor?: ResourceColor;
}

interface ChipGroupSpaceOptions {
  itemSpace?: string | number;
  startSpace?: Length;
  endSpace?: Length;
}


export interface IconItemOptions {
  icon: IconOptions,
  action: Callback<void>
}

interface BuilderTheme {
  smallIconSize: number;
  normalIconSize: number;
  backgroundColor: ResourceColor;
  smallBackgroundSize: number;
  normalbackgroundSize: number;
  borderRadius: Dimension;
  marginLeft: number;

}


@Component
export struct IconGroupSuffix {
  @Consume chipSize: ChipSize | SizeOptions | undefined
  @Prop items: Array<IconItemOptions> = []

  private getIconSize(): number {
    if (this.chipSize === ChipSize.SMALL) {
      return chipGroupSuffixTheme.smallIconSize
    } else {
      return chipGroupSuffixTheme.normalIconSize
    }
  }

  private getBackgroundSize(): number {
    if (this.chipSize === ChipSize.SMALL) {
      return chipGroupSuffixTheme.smallBackgroundSize
    } else {
      return chipGroupSuffixTheme.normalbackgroundSize
    }
  }

  build() {
    Stack() {
      Row() {
        ForEach(this.items, (suffixItem: IconItemOptions, index) => {
          Image(suffixItem.icon.src)
            .size(suffixItem.icon.size ?? { width: this.getIconSize(), height: this.getIconSize() })
            .constraintSize({ maxWidth: this.getIconSize(), maxHeight: this.getIconSize() })
            .backgroundColor(chipGroupSuffixTheme.backgroundColor)
            .fillColor($r('sys.color.ohos_id_color_primary'))
            .onClick((event: ClickEvent) => {
              suffixItem.action()
            })
        })
      }
    }
    .margin({ left: chipGroupSuffixTheme.marginLeft })
    .borderRadius(chipGroupSuffixTheme.borderRadius)
    .backgroundColor(chipGroupSuffixTheme.backgroundColor)
    .constraintSize({ maxWidth: this.getBackgroundSize(), maxHeight: this.getBackgroundSize() })
    .size({ width: this.getBackgroundSize(), height: this.getBackgroundSize() })
    .align(Alignment.Center)
  }
}


@Component
export struct ChipGroup {
  @Provide chipSize: ChipSize | SizeOptions | undefined = defaultTheme.itemStyle.size
  @Prop items: ChipGroupItemOptions[] = []
  @Prop itemStyle: ChipItemStyle = defaultTheme.itemStyle
  @Prop selectedIndexes: Array<number> = [0]
  @Prop multiple: boolean = true
  @Prop chipGroupSpaceSize: ChipGroupSpaceOptions = defaultTheme.chipGroupSpace
  @BuilderParam suffix?: Callback<void>
  private scroller: Scroller = new Scroller()
  public onChange: Callback<Array<number>> = noop
  @State isReachEnd: boolean = this.scroller.isAtEnd();

  private init(): boolean {
    this.chipSize = this.itemStyle.size
    return true
  }

  private getChipSize(): ChipSize | SizeOptions | undefined {
    return this.itemStyle.size ?? defaultTheme.itemStyle.size
  }

  private getItemStyle(): ChipItemStyle {
    return this.itemStyle ?? defaultTheme.itemStyle
  }

  private getSelectedIndexes(): Array<number> {
    return this.selectedIndexes ?? [0]
  }

  private getMultiple(): boolean {
    return this.multiple ?? true
  }

  private getChipGroupSpaceSize(): ChipGroupSpaceOptions {
    return this.chipGroupSpaceSize ?? defaultTheme.chipGroupSpace
  }

  private getOnChange(): (selectedIndexes: Array<number>) => void {
    return this.onChange ?? noop
  }

  private isSelected(itemIndex: number): boolean {
    if (!this.getMultiple()) {
      return itemIndex == this.getSelectedIndexes()[0]
    } else {
      return this.selectedIndexes.some((element, index, array) => {
        return (element == itemIndex);
      })
    }
  }

  build() {
    Row() {

      Stack() {
        Scroll(this.scroller) {
          Row({ space: this.getChipGroupSpaceSize().itemSpace }) {
            ForEach(this.items, (chipItem: ChipGroupItemOptions, index) => {
              Chip({
                prefixIcon: {
                  src: chipItem.prefixIcon?.src ?? "",
                },
                label: {
                  text: chipItem.label.text,
                  fontColor: this.getItemStyle().fontColor ?? defaultTheme.itemStyle.fontColor,
                  activatedFontColor: this.getItemStyle().selectedFontColor ?? defaultTheme.itemStyle.selectedFontColor,
                },
                suffixIcon: {
                  src: chipItem.suffixIcon?.src ?? "",
                },
                allowClose: chipItem.allowClose,
                enabled: true,
                activated: this.isSelected(index),
                backgroundColor: this.getItemStyle().backgroundColor ?? defaultTheme.itemStyle.backgroundColor,
                size: this.getChipSize(),
                activatedBackgroundColor: this.getItemStyle()
                  .selectedBackgroundColor ?? defaultTheme.itemStyle.selectedBackgroundColor,
                onClicked: () => {
                  if (this.isSelected(index)) {
                    this.selectedIndexes.splice(this.selectedIndexes.indexOf(index), 1)
                    if (this.getMultiple() == false) {
                      this.selectedIndexes = [];
                    }
                  } else {
                    this.selectedIndexes.push(index)
                    if (!this.getMultiple()) {
                      this.selectedIndexes = [];
                      this.selectedIndexes.push(index)
                    }
                  }
                  this.getOnChange()(this.selectedIndexes)
                }
              })
            });
          }
          .padding({ left: this.getChipGroupSpaceSize().startSpace ?? defaultTheme.chipGroupSpace.startSpace,
            right: this.getChipGroupSpaceSize().endSpace ?? defaultTheme.chipGroupSpace.endSpace })
          .constraintSize({ minWidth: '100%' })
        }
        .scrollable(ScrollDirection.Horizontal)
        .scrollBar(BarState.Off)
        .align(Alignment.Start)
        .width('100%')
        .onScroll(() => {
          this.isReachEnd = this.scroller.isAtEnd()
        })

        if (this.init()) {
          Stack()
            .width(chipGroupSuffixTheme.normalbackgroundSize)
            .height(this.chipSize === ChipSize.SMALL ? chipGroupSuffixTheme.smallBackgroundSize : chipGroupSuffixTheme.normalbackgroundSize)
            .linearGradient({ angle: 90, colors: alpha })
            .blendMode(BlendMode.DST_IN, BlendApplyType.OFFSCREEN)
            .hitTestBehavior(HitTestMode.None)
        }

      }
      .layoutWeight(1)
      .blendMode(BlendMode.SRC_OVER, BlendApplyType.OFFSCREEN)
      .alignContent(Alignment.End)

      if (this.suffix) {
        Row() {
          this.suffix()
        }
      }
    }
    .align(Alignment.End)
    .width("100%")
    .padding({ left: defaultTheme.leftPadding, right: this.suffix == null ? 0 : defaultTheme.rightPadding })
    .height(64)
  }
}


