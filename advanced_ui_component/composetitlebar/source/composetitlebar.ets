/*
 * Copyright (c) 2023-2023 Huawei Device Co., Ltd.
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

export declare interface ComposeTitleBarMenuItem {
  value: ResourceStr
  isEnabled: boolean
  action?: () => void
}

const PUBLIC_MORE = $r('sys.media.ohos_ic_public_more')

const PUBLIC_BACK = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAMAAAADACAY' +
  'AAABS3GwHAAAAIGNIUk0AAHomAACAhAAA+gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAAEZ0FNQQAAsY58+1GTAAAAA' +
  'XNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAAlwSFlzAAAOxAAADsQBlSsOGwAAA8VJREFUeNrt3LFLlHEYwPFXz0G' +
  'iIZpEoikkwsFRIiK3gqCigxIC/4Kmhv6OoChouaGoqKCgCKducGh0cDAIamhwiCaHCIeelztpUszee/vl8/nAM3Vd8nufr' +
  '+fddVYVAAAAAAAAAAAAAAAAAAAAAABQijFH0KhrMd2Y2ZitmNWYRzHLjkYAB9lUzMOYizv8eS/mZsymoypLxxE0svzvY07' +
  'vcpu5mOmY145LAAdx+U/u4bZzwx+JPjq2cow7glaWf1vXsQkg6/JvPwoggJTLjwDSL/8nRyiAzN/5nzpGAWRd/n7MM0cpg' +
  'IzLvx6z6CjL453gdpZ/IWbDcQrA8iMAy48ALD8CsPwIwPIjAMuPACw/ArD8CMDyIwDLjwAsPwKw/AjA8iMAy48ALD8CsPw' +
  'IwPIjAMuPACw/ArD85A3A8pM2AMtP2gAsP2kDsPykDcDykzYAy0/aACw/aQOw/KQNwPKTNgDLT9oALD9pA7D8pA3A8pM2A' +
  'MtP2gAsP2kDsPykDcDykzYAy0/aACw/aQOw/KQNwPKTNgDLT9oALD9pA7D8pA3A8pM2AMtP2gAsP2kDsPykDcDykzYAy0/' +
  'aACw/aQOw/KQNwPLz3xlv6H4mYp5YfrI+AizF9BwnI/AlZi3mbsxy03feaeh+HsQcc60YgSMxMzE3YmZj3sX8LOlHoPoLn' +
  'HedaEE35n5pzwF856dN9SPBpZICmHRNaNnlkgL46nrQsvmSAqhftlx1TWjR4ZICqPVcE1q0XloA96rBa7XQhl5pAWzFXKm' +
  '8i8vo9WMeN3VnnQa/sO8xL2POxEy7Toxo+RdjNpu6w1F9HuBqNXi99lw1eKMM9utHzIeYV8MftbccCQAAAAAAsBdt/XLc+s' +
  'Py9W+MmPqL+1iJuVA1+C4gdFr6d77FvK0GH2nb739lPR5zNuZ51eBnQhFAJQIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIE' +
  'IAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAI' +
  'EIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIEIAIE8M8jmBlGgABSRnAqZiXms+MUQNYIDnkUKMu4I/gj6z' +
  'ELMRv7/PsnHKEAMkcw6fgEkDmCNUcngMwRvHFsngRnfWJcL/9tRyaAgxrB+ZijO9ymH7MUs+m4yjLmCBozEXMr5nr1+9We1' +
  'ZgXMXccDwAAAAAAAAAAAAAAAAAAAAAAwO5+AfVgtqHKRnawAAAAAElFTkSuQmCC'

@Component
struct ComposeTitleBar {
  item: ComposeTitleBarMenuItem | undefined = undefined
  title: ResourceStr = ''
  subtitle: ResourceStr = ''
  menuItems?: Array<ComposeTitleBarMenuItem>

  @State titleMaxWidth: number = 0
  @State backActive: boolean = false

  private static readonly totalHeight = 56
  private static readonly leftPadding = 12
  private static readonly rightPadding = 12
  private static readonly portraitImageSize = 40
  private static readonly portraitImageLeftPadding = 4
  private static readonly portraitImageRightPadding = 16
  private static instanceCount = 0

  build() {
    Flex({
      justifyContent: FlexAlign.SpaceBetween,
      alignItems: ItemAlign.Stretch
    }) {
      Row() {
        Navigator()
          .active(this.backActive)

        ImageMenuItem({ item: {
          value: $r('sys.media.ohos_ic_back'),
          isEnabled: true,
          action: () => this.backActive = true
        }, index: -1 })

        if (this.item !== undefined) {
          Image(this.item.value)
            .width(ComposeTitleBar.portraitImageSize)
            .height(ComposeTitleBar.portraitImageSize)
            .margin({
              left: $r('sys.float.ohos_id_text_paragraph_margin_xs'),
              right: $r('sys.float.ohos_id_text_paragraph_margin_m')
            })
            .focusable(false)
            .borderRadius(ImageMenuItem.buttonBorderRadius)
        }

        Column() {
          if (this.title !== undefined) {
            Row() {
              Text(this.title)
                .fontWeight(FontWeight.Medium)
                .fontSize($r('sys.float.ohos_id_text_size_headline8'))
                .fontColor($r('sys.color.ohos_id_color_titlebar_text'))
                .maxLines(this.subtitle !== undefined ? 1 : 2)
                .textOverflow({ overflow: TextOverflow.Ellipsis })
                .constraintSize({ maxWidth: this.titleMaxWidth })
            }
            .justifyContent(FlexAlign.Start)
          }
          if (this.subtitle !== undefined) {
            Row() {
              Text(this.subtitle)
                .fontSize($r('sys.float.ohos_id_text_size_over_line'))
                .fontColor($r('sys.color.ohos_id_color_titlebar_subtitle_text'))
                .maxLines(1)
                .textOverflow({ overflow: TextOverflow.Ellipsis })
                .constraintSize({ maxWidth: this.titleMaxWidth })
            }
            .justifyContent(FlexAlign.Start)
          }
        }
        .justifyContent(FlexAlign.Start)
        .alignItems(HorizontalAlign.Start)
        .constraintSize({ maxWidth: this.titleMaxWidth })
      }
      .margin({ left: $r('sys.float.ohos_id_default_padding_start') })

      if (this.menuItems !== undefined && this.menuItems.length > 0) {
        CollapsibleMenuSection({ menuItems: this.menuItems, index: 1 + ComposeTitleBar.instanceCount++ })
      }
    }
    .width('100%')
    .height(ComposeTitleBar.totalHeight)
    .backgroundColor($r('sys.color.ohos_id_color_background'))
    .onAreaChange((_oldValue: Area, newValue: Area) => {
      let newWidth = Number(newValue.width)
      if (this.menuItems !== undefined) {
        let menusLength = this.menuItems.length
        if (menusLength >= CollapsibleMenuSection.maxCountOfVisibleItems) {
          newWidth = newWidth - ImageMenuItem.imageHotZoneWidth * CollapsibleMenuSection.maxCountOfVisibleItems
        } else if (menusLength > 0) {
          newWidth = newWidth - ImageMenuItem.imageHotZoneWidth * menusLength
        }
      }
      this.titleMaxWidth = newWidth
      this.titleMaxWidth -= ComposeTitleBar.leftPadding
      this.titleMaxWidth -= ImageMenuItem.imageHotZoneWidth
      if (this.item !== undefined) {
        this.titleMaxWidth -= ComposeTitleBar.portraitImageLeftPadding +
          ComposeTitleBar.portraitImageSize +
          ComposeTitleBar.portraitImageRightPadding
      }
      this.titleMaxWidth -= ComposeTitleBar.rightPadding
    })
  }
}

@Component
struct CollapsibleMenuSection {
  menuItems?: Array<ComposeTitleBarMenuItem>
  index: number = 0

  static readonly maxCountOfVisibleItems = 3
  private static readonly focusPadding = 4
  private static readonly marginsNum = 2
  private firstFocusableIndex = -1

  @State isPopupShown: boolean = false

  @State isMoreIconOnFocus: boolean = false
  @State isMoreIconOnHover: boolean = false
  @State isMoreIconOnClick: boolean = false

  getMoreIconFgColor() {
    return this.isMoreIconOnClick
      ? $r('sys.color.ohos_id_color_titlebar_icon_pressed')
      : $r('sys.color.ohos_id_color_titlebar_icon')
  }

  getMoreIconBgColor() {
    if (this.isMoreIconOnClick) {
      return $r('sys.color.ohos_id_color_click_effect')
    } else if (this.isMoreIconOnHover) {
      return $r('sys.color.ohos_id_color_hover')
    } else {
      return Color.Transparent
    }
  }

  aboutToAppear() {
    if (this.menuItems) {
      this.menuItems.forEach((item, index) => {
        if (item.isEnabled && this.firstFocusableIndex == -1 && index > CollapsibleMenuSection.maxCountOfVisibleItems - 2) {
          this.firstFocusableIndex = this.index * 1000 + index + 1
        }
      })
    }
  }

  build() {
    Column() {
      Row() {
        if (this.menuItems) {
          if (this.menuItems.length <= CollapsibleMenuSection.maxCountOfVisibleItems) {
            ForEach(this.menuItems, (item: ComposeTitleBarMenuItem, index:number) => {
              ImageMenuItem({ item: item, index: this.index * 1000 + index + 1 })
            })
          } else {
            ForEach(this.menuItems.slice(0, CollapsibleMenuSection.maxCountOfVisibleItems - 1), (item:ComposeTitleBarMenuItem, index:number) => {
              ImageMenuItem({ item: item, index: this.index * 1000 + index + 1 })
            })

            Row() {
              Image(PUBLIC_MORE)
                .width(ImageMenuItem.imageSize)
                .height(ImageMenuItem.imageSize)
                .fillColor($r('sys.color.icon_primary'))
                .focusable(true)
            }
            .width(ImageMenuItem.imageHotZoneWidth)
            .height(ImageMenuItem.imageHotZoneWidth)
            .borderRadius(ImageMenuItem.buttonBorderRadius)
            .foregroundColor(this.getMoreIconFgColor())
            .backgroundColor(this.getMoreIconBgColor())
            .justifyContent(FlexAlign.Center)
            .stateStyles({
              focused: {
                .border({
                  radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                  width: ImageMenuItem.focusBorderWidth,
                  color: $r('sys.color.ohos_id_color_focused_outline'),
                  style: BorderStyle.Solid
                })
              },
              normal: {
                .border({
                  radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                  width: 0
                })
              }
            })
            .onFocus(() => this.isMoreIconOnFocus = true)
            .onBlur(() => this.isMoreIconOnFocus = false)
            .onHover((isOn) => this.isMoreIconOnHover = isOn)
            .onKeyEvent((event) => {
              if (event.keyCode !== KeyCode.KEYCODE_ENTER && event.keyCode !== KeyCode.KEYCODE_SPACE) {
                return
              }
              if (event.type === KeyType.Down) {
                this.isMoreIconOnClick = true
              }
              if (event.type === KeyType.Up) {
                this.isMoreIconOnClick = false
              }
            })
            .onTouch((event) => {
              if (event.type === TouchType.Down) {
                this.isMoreIconOnClick = true
              }
              if (event.type === TouchType.Up) {
                this.isMoreIconOnClick = false
              }
            })
            .onClick(() => this.isPopupShown = true)
            .bindPopup(this.isPopupShown, {
              builder: this.popupBuilder,
              placement: Placement.Bottom,
              popupColor: Color.White,
              enableArrow: false,
              onStateChange: (e) => {
                this.isPopupShown = e.isVisible
                if (!e.isVisible) {
                  this.isMoreIconOnClick = false
                }
              }
            })
          }
        }
      }
    }
    .height('100%')
    .margin({ right: $r('sys.float.ohos_id_default_padding_end') })
    .justifyContent(FlexAlign.Center)
  }

  @Builder
  popupBuilder() {
    Column() {
      if (this.menuItems) {
        ForEach(this.menuItems.slice(CollapsibleMenuSection.maxCountOfVisibleItems - 1, this.menuItems.length), (item:ComposeTitleBarMenuItem, index:number) => {
          ImageMenuItem({ item: item, index: this.index * 1000 + CollapsibleMenuSection.maxCountOfVisibleItems + index })
        })
      }
    }
    .width(ImageMenuItem.imageHotZoneWidth + CollapsibleMenuSection.focusPadding * CollapsibleMenuSection.marginsNum)
    .margin({ top: CollapsibleMenuSection.focusPadding, bottom: CollapsibleMenuSection.focusPadding })
    .onAppear(() => {
      focusControl.requestFocus(ImageMenuItem.focusablePrefix + this.firstFocusableIndex)
    })
  }
}

@Component
struct ImageMenuItem {
  item: ComposeTitleBarMenuItem | null = null
  index: number = 0

  static readonly imageSize = 24
  static readonly imageHotZoneWidth = 48
  static readonly buttonBorderRadius = 8
  static readonly focusBorderWidth = 2
  static readonly disabledImageOpacity = 0.4
  static readonly focusablePrefix = "Id-ComposeTitleBar-ImageMenuItem-"

  @State isOnFocus: boolean = false
  @State isOnHover: boolean = false
  @State isOnClick: boolean = false

  getFgColor() {
    return this.isOnClick
      ? $r('sys.color.ohos_id_color_titlebar_icon_pressed')
      : $r('sys.color.ohos_id_color_titlebar_icon')
  }

  getBgColor() {
    if (this.isOnClick) {
      return $r('sys.color.ohos_id_color_click_effect')
    } else if (this.isOnHover) {
      return $r('sys.color.ohos_id_color_hover')
    } else {
      return Color.Transparent
    }
  }

  build() {
    Row() {
      Image(this.item?.value)
        .width(ImageMenuItem.imageSize)
        .height(ImageMenuItem.imageSize)
        .focusable(this.item?.isEnabled)
        .key(ImageMenuItem.focusablePrefix + this.index)
        .fillColor($r('sys.color.ohos_id_color_text_primary'))
    }
    .width(ImageMenuItem.imageHotZoneWidth)
    .height(ImageMenuItem.imageHotZoneWidth)
    .borderRadius(ImageMenuItem.buttonBorderRadius)
    .foregroundColor(this.getFgColor())
    .backgroundColor(this.getBgColor())
    .justifyContent(FlexAlign.Center)
    .opacity(this.item?.isEnabled ? 1 : ImageMenuItem.disabledImageOpacity)
    .stateStyles({
      focused: {
        .border({
          radius: $r('sys.float.ohos_id_corner_radius_clicked'),
          width: ImageMenuItem.focusBorderWidth,
          color: $r('sys.color.ohos_id_color_focused_outline'),
          style: BorderStyle.Solid
        })
      },
      normal: {
        .border({
          radius: $r('sys.float.ohos_id_corner_radius_clicked'),
          width: 0
        })
      }
    })
    .onFocus(() => {
      if (!this.item?.isEnabled) {
        return
      }
      this.isOnFocus = true
    })
    .onBlur(() => this.isOnFocus = false)
    .onHover((isOn) => {
      if (!this.item?.isEnabled) {
        return
      }
      this.isOnHover = isOn
    })
    .onKeyEvent((event) => {
      if (!this.item?.isEnabled) {
        return
      }
      if (event.keyCode !== KeyCode.KEYCODE_ENTER && event.keyCode !== KeyCode.KEYCODE_SPACE) {
        return
      }
      if (event.type === KeyType.Down) {
        this.isOnClick = true
      }
      if (event.type === KeyType.Up) {
        this.isOnClick = false
      }
    })
    .onTouch((event) => {
      if (!this.item?.isEnabled) {
        return
      }
      if (event.type === TouchType.Down) {
        this.isOnClick = true
      }
      if (event.type === TouchType.Up) {
        this.isOnClick = false
      }
    })
    .onClick(() => {
      if (this.item) {
        return this.item.isEnabled && this.item.action?.()
      }
    })
  }
}

export  { ComposeTitleBar }