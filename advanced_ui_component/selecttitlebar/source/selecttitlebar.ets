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

export declare type SelectTitleBarMenuItem = {
  value: ResourceStr
  isEnabled: boolean
  action?: () => void
}

const PUBLIC_MORE = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAMAAAADACAY' +
  'AAABS3GwHAAAAIGNIUk0AAHomAACAhAAA+gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAAEZ0FNQQAAsY58+1GTAAA' +
  'AAXNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAAlwSFlzAAAOxAAADsQBlSsOGwAABEZJREFUeNrt3D1rFFEUBuA' +
  'xhmAhFlYpUohYiYWFRcAmKAhWK2pjo1iKf8BCMIKFf8BarCyMhVj4VZhGSKEg2FqJyCKWIhYWnstMINgYsh+cmfs88BI' +
  'Cydxw7jmzu2HvNg0AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADBN+3r6dx+LXIqsRpa7FF8j48hm5Fn3Peo9mAEYRdY' +
  'jJ3f582Vj7nZfUe/eDsCRyMPI2h5/fyNyI/JDT6v3Tvt7sBllE15ETkxwjeORi5G3ke/6W737MgBnI68jh6ZwrcORq5H' +
  'nhkC9+zAA5YXXy8jBKV5zKXIu8jjyS7+rd+YBeNVtyrSVO9PRyBM9r94LSTfjWuTUDK9/eYIXeENUbb0zDsBi5PYc1rm' +
  'j79U74wCszuih+F/ljrSi/+uud8YBGA10rayqrnfGAVgb6FpZVV3vjAOwPNC1sqq63hkHYGWga2VVdb0XKt/8Rf1fd70' +
  'zDsB4jmt5u3Tl9a59AMb6v+56ZxyArYGulVXV9c44ABtzXOup/q+73hkH4N2cHio/Rj7r/7rrnXEAfkfuz2Gddb2v3ln' +
  '/DfpgxneLzaY9xE3l9c46AH8iVyI/Z3Dt8nB/Xc+rd5H5QMy3yJemPVs6zY0edc9HUe/0Z4I/dQ/N5Vjd0oTXKp9QcKF' +
  'pD2qj3r0YgO1NeRM507TH6/bifeR85IMeV++d+vTBWOV9JDcjt5rdv6uw3M3uRR7pa/Xu+wBsOxA53bTnTP/3UX1b3fN' +
  'Q1BsAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAKqyr6d/97HIpchqZLlL8TUyjmxGnnX' +
  'fo96DGYBRZD1ycpc/XzbmbvcV9e7tAByJPIys7fH3NyI3Ij/0tHrvtL8Hm1E24UXkxATXOB65GHkb+a6/1bsvA3A28jp' +
  'yaArXOhy5GnluCNS7DwNQXni9jByc4jWXIucijyO/9Lt6Zx6AV92mTFu5Mx2NPNHz6r2QdDOuRU7N8PqXJ3iBN0TV1jv' +
  'jACxGbs9hnTv6Xr0zDsDqjB6K/1XuSCv6v+56ZxyA0UDXyqrqemccgLWBrpVV1fXOOADLA10rq6rrnXEAVga6VlZV13u' +
  'h8s1f1P911zvjAIznuJa3S1de79oHYKz/6653xgHYGuhaWVVd74wDsDHHtZ7q/7rrnXEA3s3pofJj5LP+r7veGQfgd+T' +
  '+HNZZ1/vqnfXfoA9mfLfYbNpD3FRe76wD8CdyJfJzBtcuD/fX9bx6F5kPxHyLfGnas6XT3OhR93wU9U5/JvhT99BcjtU' +
  'tTXit8gkFF5r2oDbq3YsB2N6UN5EzTXu8bi/eR85HPuhx9d6pTx+MVd5HcjNyq9n9uwrL3exe5JG+Vu++D8C2A5HTTXv' +
  'O9H8f1bfVPQ9FvQEAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAgCn7C9HjBtwWfXpKAAAAAElFTkSuQmCC'

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
export struct SelectTitleBar {
  @State selected: number = 0

  options: Array<SelectOption>
  menuItems: Array<SelectTitleBarMenuItem>

  subtitle: ResourceStr
  badgeValue: number
  hidesBackButton: boolean

  onSelected: ((index: number) => void)

  private static readonly badgeSize = 16
  private static readonly totalHeight = 56
  private static readonly leftPadding = 24
  private static readonly leftPaddingWithBack = 12
  private static readonly rightPadding = 24
  private static readonly badgePadding = 16
  private static readonly subtitleLeftPadding = 4

  @State selectMaxWidth: number = 0
  @State backActive: boolean = false

  build() {
    Flex({
      justifyContent: FlexAlign.SpaceBetween,
      alignItems: ItemAlign.Stretch
    }) {
      Row() {
        if (!this.hidesBackButton) {
          Navigator()
            .active(this.backActive)

          ImageMenuItem({ item: {
            value: PUBLIC_BACK,
            isEnabled: true,
            action: () => this.backActive = true
          } })
        }

        Column() {
          if (this.badgeValue !== undefined) {
            Badge({
              count: this.badgeValue,
              position: BadgePosition.Right,
              style: {
                badgeSize: SelectTitleBar.badgeSize,
                badgeColor: $r('sys.color.ohos_id_color_emphasize'),
                borderColor: $r('sys.color.ohos_id_color_emphasize'),
                borderWidth: 0
              }
            }) {
              Row() {
                Select(this.options)
                  .selected(this.selected)
                  .value(this.selected < this.options.length ? this.options[this.selected].value.toString() : "")
                  .font({ size: this.hidesBackButton && this.subtitle === undefined
                    ? $r('sys.float.ohos_id_text_size_headline7')
                    : $r('sys.float.ohos_id_text_size_headline8') })
                  .fontColor($r('sys.color.ohos_id_color_titlebar_text'))
                  .backgroundColor(Color.Transparent)
                  .onSelect(this.onSelected)
                  .constraintSize({ maxWidth: this.selectMaxWidth })
                  .offset({ x: -4 })
              }
              .justifyContent(FlexAlign.Start)
              .margin({ right: $r('sys.float.ohos_id_elements_margin_horizontal_l') })
            }
          } else {
            Row() {
              Select(this.options)
                .selected(this.selected)
                .value(this.selected < this.options.length ? this.options[this.selected].value.toString() : "")
                .font({ size: this.hidesBackButton && this.subtitle === undefined
                  ? $r('sys.float.ohos_id_text_size_headline7')
                  : $r('sys.float.ohos_id_text_size_headline8') })
                .fontColor($r('sys.color.ohos_id_color_titlebar_text'))
                .backgroundColor(Color.Transparent)
                .onSelect(this.onSelected)
                .constraintSize({ maxWidth: this.selectMaxWidth })
                .offset({ x: -4 })
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
                .constraintSize({ maxWidth: this.selectMaxWidth })
                .offset({ y: -4 })
            }
            .justifyContent(FlexAlign.Start)
            .margin({ left: SelectTitleBar.subtitleLeftPadding })
          }
        }
        .justifyContent(FlexAlign.Start)
        .alignItems(HorizontalAlign.Start)
        .constraintSize({ maxWidth: this.selectMaxWidth })
      }
      .margin({ left: this.hidesBackButton ? $r('sys.float.ohos_id_max_padding_start') : $r('sys.float.ohos_id_default_padding_start') })

      if (this.menuItems !== undefined && this.menuItems.length > 0) {
        CollapsibleMenuSection({ menuItems: this.menuItems })
      }
    }
    .width('100%')
    .height(SelectTitleBar.totalHeight)
    .backgroundColor($r('sys.color.ohos_id_color_background'))
    .onAreaChange((_oldValue: Area, newValue: Area) => {
      let newWidth = Number(newValue.width)
      if (!this.hidesBackButton) {
        newWidth -= ImageMenuItem.imageHotZoneWidth
        newWidth += SelectTitleBar.leftPadding
        newWidth -= SelectTitleBar.leftPaddingWithBack
      }
      if (this.menuItems !== undefined) {
        let menusLength = this.menuItems.length
        if (menusLength >= CollapsibleMenuSection.maxCountOfVisibleItems) {
          newWidth -= ImageMenuItem.imageHotZoneWidth * CollapsibleMenuSection.maxCountOfVisibleItems
        } else if (menusLength > 0) {
          newWidth -= ImageMenuItem.imageHotZoneWidth * menusLength
        }
      }
      if (this.badgeValue !== undefined) {
        this.selectMaxWidth = newWidth - SelectTitleBar.badgeSize - SelectTitleBar.leftPadding - SelectTitleBar.rightPadding - SelectTitleBar.badgePadding
      } else {
        this.selectMaxWidth = newWidth - SelectTitleBar.leftPadding - SelectTitleBar.rightPadding
      }
    })
  }
}

@Component
struct CollapsibleMenuSection {
  menuItems: Array<SelectTitleBarMenuItem>

  static readonly maxCountOfVisibleItems = 3
  private static readonly focusPadding = 4
  private static readonly marginsNum = 2

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

  build() {
    Column() {
      Row() {
        if (this.menuItems.length <= CollapsibleMenuSection.maxCountOfVisibleItems) {
          ForEach(this.menuItems, (item) => {
            ImageMenuItem({ item: item })
          })
        } else {
          ForEach(this.menuItems.slice(0, CollapsibleMenuSection.maxCountOfVisibleItems - 1), (item) => {
            ImageMenuItem({ item: item })
          })

          Row() {
            Image(PUBLIC_MORE)
              .width(ImageMenuItem.imageSize)
              .height(ImageMenuItem.imageSize)
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
            onStateChange: (e) => this.isPopupShown = e.isVisible
          })
        }
      }
    }
    .height('100%')
    .margin({ right: $r('sys.float.ohos_id_default_padding_end') })
    .justifyContent(FlexAlign.Center)
  }

  @Builder popupBuilder() {
    Column() {
      ForEach(this.menuItems.slice(CollapsibleMenuSection.maxCountOfVisibleItems - 1, this.menuItems.length), (item, _index?) => {
        ImageMenuItem({ item: item })
      })
    }
    .width(ImageMenuItem.imageHotZoneWidth + CollapsibleMenuSection.focusPadding * CollapsibleMenuSection.marginsNum)
    .margin({ top: CollapsibleMenuSection.focusPadding, bottom: CollapsibleMenuSection.focusPadding })
  }
}

@Component
struct ImageMenuItem {
  item: SelectTitleBarMenuItem

  static readonly imageSize = 24
  static readonly imageHotZoneWidth = 48
  static readonly buttonBorderRadius = 8
  static readonly focusBorderWidth = 2
  static readonly disabledImageOpacity = 0.4

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
      Image(this.item.value)
        .width(ImageMenuItem.imageSize)
        .height(ImageMenuItem.imageSize)
        .focusable(this.item.isEnabled)
    }
    .width(ImageMenuItem.imageHotZoneWidth)
    .height(ImageMenuItem.imageHotZoneWidth)
    .borderRadius(ImageMenuItem.buttonBorderRadius)
    .foregroundColor(this.getFgColor())
    .backgroundColor(this.getBgColor())
    .justifyContent(FlexAlign.Center)
    .opacity(this.item.isEnabled ? 1 : ImageMenuItem.disabledImageOpacity)
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
      if (!this.item.isEnabled) {
        return
      }
      this.isOnFocus = true
    })
    .onBlur(() => this.isOnFocus = false)
    .onHover((isOn) => {
      if (!this.item.isEnabled) {
        return
      }
      this.isOnHover = isOn
    })
    .onKeyEvent((event) => {
      if (!this.item.isEnabled) {
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
      if (!this.item.isEnabled) {
        return
      }
      if (event.type === TouchType.Down) {
        this.isOnClick = true
      }
      if (event.type === TouchType.Up) {
        this.isOnClick = false
      }
    })
    .onClick(() => this.item.isEnabled && this.item.action && this.item.action())
  }
}

export default { SelectTitleBar }