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

export enum EditableLeftIconType {
  Back,
  Cancel
}

export declare type EditableTitleBarMenuItem = {
  value: ResourceStr
  isEnabled: boolean
  action?: () => void
}

const PUBLIC_CANCEL = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAMAAAADACAYAAABS3Gw' +
  'HAAAAIGNIUk0AAHomAACAhAAA+gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAAEZ0FNQQAAsY58+1GTAAAAAXNSR0IA' +
  'rs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAAlwSFlzAAAOxAAADsQBlSsOGwAABKpJREFUeNrt3bFrlHccx/Ff4o2dgkOQ4' +
  'JzR4SYJgksnbYcGOrTQsUPtpE4d/RNcFBeFlg7NUlTSTrXQQgsKGV0KHTs4ODiJSL8PdxaUGJK7pPc893m94TvleZLnnt' +
  '/7fcc9z5FrDQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAnDQrPTuej2u2a87VvKp5XLNT87OlGiSf1lx' +
  '6Zz2/q3kkgLdZr7k5lX8/7tZ8XfOCU4OgW887U/n341bN9T6s56menLAfaj464OfdM8iF6XYv+dV7+X+pOX/ANuOatZqH' +
  'Amjti5prh9jurAgGI//mIbbtIvi15u9FHvBqD07a50fYdqtmt+YDrg1a/jd8tuiD7kMA4yNuL4LlkH+WtV/KAEYz7COC4' +
  'cs/69ovXQB7M+4ngmHLP8/aL1UAD+bYVwTDlX/etT8W+nAV6M82uQS6PuP+rg4NV/5vBNDa6za5HLY9xzO5CIYl/9OaT5' +
  'obYf/xrE1uioggQ/6LNf/04QGd6tHJFQH5owMQAfnjAxAB+eMDEAH54wMQAfnjAxAB+eMDEAH54wMQAfnjAxAB+eMDEAH' +
  '54wMQAfnjAxAB+eMDEAH54wMQAfnjAxAB+eMDEAH54wMQAfnjAxAB+eMDEAH54wMQAfnjAxAB+eMDSI6A/AKIjYD8AoiN' +
  'gPwCiI2A/AKIjYD8AoiNgPwCiI2A/AKIjYD8AoiNgPwCiI2A/AKIjYD8AoiNgPwCiI2A/AKIjYD8AoiNgPwCiI2A/AKIj' +
  'YD8AoiNgPwCiI2A/AKIjYD8AoiNgPwCiI1gjfyLY8UpmJnNqbjrc/yO32pOk98rQPIrwWnyCyA5AvILQATkF4AIyC8AEZ' +
  'BfACIgvwBEQH4BiID8J8qqU3BiPJ8O+XuMO8Eng8/2CID85BcA+ckvAPKT35tg8h+n/KP2/3/2SADojfzf1+yKYH7cBxi' +
  'm/N39hWX8RnsBkP9Q8r9BBAKIlV8EAoiXXwQCiJdfBAKIl18EAoiXXwQz4D5A/+Tv2KjZmuPvdfu6T+AVYJDyd3Qfo17G' +
  'b7QXAPkPzTMRCCBVfhEIIF5+EQggXn4RCCBefhEIIF5+EQggXn4RCCBefhEIIF5+EQggXn4RCCBefhEIIF5+EQggXn4RC' +
  'CBefhEIIF5+EQggXn4RCCBefhEIwD+qFUFuAOQXQWwA5BdBbADkF0FsAOQXQWwA5BdBbADkF0FsAOQXQWwA5BdBbADkF0' +
  'FsAOQXQWwA5BdBbADkF0FsAOQXQWwA5BdBbADkF0FsAOQXQWwA5BdBbADkF0FsAOQXQWwA5BdBdAD3a8bkj4rgTM2PAmj' +
  'ty5or5I+L4FzNHzV/LfKB9OGb4rfJP0iO49xvL/pB9CGAMfljIxgLoLUR+WMjGAmgtT3yx0awJ4DWdsgfG8HOog+6D1eB' +
  'ntR8WLNB/sFzlKtDnfw3BNDa65rfp2+I3hfBo5rL5B9UBFttcoNzP35qk8vfLxZ9sCs9OnHdG6Kvps8e3TXiVzWPp88Ut' +
  '3k1OLr1vFpz6Z31/LbmntMDAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAEAO/wLvsR65mx80NAAAAABJRU' +
  '5ErkJggg=='

const PUBLIC_OK = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAMAAAADACAYAAABS3' +
  'GwHAAAAIGNIUk0AAHomAACAhAAA+gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAAEZ0FNQQAAsY58+1GTAAAAAXNSR0IArs4c6QAAAAZ' +
  'iS0dEAP8A/wD/oL2nkwAAAAlwSFlzAAAOxAAADsQBlSsOGwAAA+lJREFUeNrt3bFrFgccx+GLlSDi4JDBITiJZHBwEBGRIoqKoIu6iVMd3' +
  'OosCg6W0sm/wEFUDDgpCDoIDoqOKqIoHUrp4CDFoUMRB39HLotoeXMpMXff54EfFE0ivv1+kpQGrmkAAAAAAAAAAAAAAAAAAAAAAAAAAAA' +
  'AAAAAAAAAAAAAAIBJTHkJGIhddT/V7ajbUPey7l7dlbpPAmCs1tb9Wne2++cvPa07Vfd7nw/+g9eXVT7+m3Wn69Z8421m6w7WXa37KADGN' +
  'v4TE7ztTN36uvtL/UPWeJ0Z+PgXnejzBwmAMYx/8VuhTQIgcfy9CYCxjP9D3TsBkPqZf95XAFLH3372vyAAEsf/T93Ruvd93tn/CWbo4z9' +
  'c96jvBxAAseMXANHjFwDR4xcA0eMXANHjFwDR4xcA0eMXANHjFwDR4xcA0eMXANHjFwDR4xcA0eMXANHjFwDR4xcA0eMXANHjFwDR4xcA0' +
  'eMXANHjFwDR4xcA0eMXANHjFwDR4xcA0eMXANHjFwDR4xcA0eP/HgG0z3f9uVl45uu2ZuGBBu3zXn9rej7mEuMfSgDtA46v1c195ff+rbt' +
  'U94stGv9KWqnHpLaPsXxSt/k//iXsq9vY9HjUJca/2gNoH2e/c4K32yUC4x9bAOvqrjeTP41GBMY/qgC2151Z4vuIwPhXxEo8I2xdz/c7W' +
  '3fZXo1/6F8B/q471/N9fSUw/sEH8LEb8hYRGH9iAK3HdafrpkVg/IkBtA8yflt3bBn/3SEC4x9sAK3Xda9EYPypAYjA+OMDEIHxxwcgAuO' +
  'PD0AExh8fgAiMPz4AERh/fAAiMP74AERg/PEBiMD44wMQgfHHByAC448PQATGHx+ACIw/PgARGH98AMkRGL8AYiMwfgHERmD8AoiNwPgFE' +
  'BuB8QsgNgLjF0BsBMYvgNgIjF8AsREYvwBiIzB+AcRGYPwCiI3A+AUQG4HxCyA2AuMXQGwExi+A2AiMXwCxERi/AGIjMH4BjDaCTXUP6j5' +
  '9423aJ2PeMH4BjDWCHd24n9f9+cXvHa+7U7fb+Fe/qeC/ezvU+e5bleX40A11pm6u+xapMX5fARK+Eix+u7O1brbp/1Bw4xfAoCP4Pxi/A' +
  'GIjMH4BxEZg/AKIjcD4BRAbgfELIDYC4xdAbATGL4DYCIxfAIOL4EXdkbrpZX6sd3WH6p56WQUwJG/qbtX92Cz8EFwfD+sO1L31cq4uU16' +
  'CibU/M3Sy7nzdlgnf51ndxbrbXj4BjCmEPXX76/Y2Cz8DNNP9+l91f3Sf8e92AQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA' +
  'AAAAAzKZwK1uX4kZ6mnAAAAAElFTkSuQmCC'

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
export struct EditableTitleBar {
  leftIconStyle: EditableLeftIconType
  title: ResourceStr
  menuItems: Array<EditableTitleBarMenuItem>
  onSave?: () => void
  onCancel?: () => void

  @State titleMaxWidth: number = 0
  @State backActive: boolean = false

  static readonly maxCountOfExtraItems = 2
  private static readonly totalHeight = 56
  private static readonly leftPadding = 12
  private static readonly rightPadding = 12
  private static readonly titlePadding = 16

  build() {
    Flex({
      justifyContent: FlexAlign.SpaceBetween,
      alignItems: ItemAlign.Stretch
    }) {
      Row() {
        if (this.leftIconStyle == EditableLeftIconType.Back) {
          Navigator()
            .active(this.backActive)

          ImageMenuItem({ item: {
            value: PUBLIC_BACK,
            isEnabled: true,
            action: () => this.backActive = true
          } })
        } else {
          ImageMenuItem({ item: {
            value: PUBLIC_CANCEL,
            isEnabled: true,
            action: () => this.onCancel && this.onCancel()
          } })
        }

        Column() {
          Text(this.title)
            .fontWeight(FontWeight.Medium)
            .fontSize($r('sys.float.ohos_id_text_size_headline8'))
            .fontColor($r('sys.color.ohos_id_color_titlebar_text'))
            .maxLines(1)
            .textOverflow({ overflow: TextOverflow.Ellipsis })
            .constraintSize({ maxWidth: this.titleMaxWidth })
        }
        .justifyContent(FlexAlign.Start)
        .alignItems(HorizontalAlign.Start)
        .constraintSize({ maxWidth: this.titleMaxWidth })
      }
      .margin({ left: $r('sys.float.ohos_id_default_padding_start') })

      EditableTitleBarMenuSection({
        menuItems: this.menuItems,
        onSave: this.onSave
      })
    }
    .width('100%')
    .height(EditableTitleBar.totalHeight)
    .backgroundColor($r('sys.color.ohos_id_color_background'))
    .onAreaChange((_oldValue: Area, newValue: Area) => {
      let nValue = Number(newValue.width)
      nValue = nValue - EditableTitleBar.leftPadding - EditableTitleBar.rightPadding - EditableTitleBar.titlePadding
      nValue = nValue - ImageMenuItem.imageHotZoneWidth - ImageMenuItem.imageHotZoneWidth
      if (this.menuItems === undefined) {
        this.titleMaxWidth = nValue
        return
      }
      if (this.menuItems.length > EditableTitleBar.maxCountOfExtraItems) {
        this.titleMaxWidth = nValue - ImageMenuItem.imageHotZoneWidth * EditableTitleBar.maxCountOfExtraItems
      } else {
        this.titleMaxWidth = nValue - ImageMenuItem.imageHotZoneWidth * this.menuItems.length
      }
    })
  }
}

@Component
struct EditableTitleBarMenuSection {
  menuItems: Array<EditableTitleBarMenuItem>
  onSave?: () => void

  build() {
    Column() {
      Row() {
        if (this.menuItems !== undefined && this.menuItems.length > 0) {
          ForEach(this.menuItems.slice(0, EditableTitleBar.maxCountOfExtraItems), (item: EditableTitleBarMenuItem) => {
            ImageMenuItem({ item: item })
          })
        }
        ImageMenuItem({ item: {
          value: PUBLIC_OK,
          isEnabled: true,
          action: () => this.onSave && this.onSave()
        } })
      }
    }
    .margin({
      left: $r('sys.float.ohos_id_elements_margin_vertical_l'),
      right: $r('sys.float.ohos_id_default_padding_end')
    })
    .justifyContent(FlexAlign.Center)
  }
}

@Component
struct ImageMenuItem {
  item: EditableTitleBarMenuItem

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

export default { EditableLeftIconType, EditableTitleBar }