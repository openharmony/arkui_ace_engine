/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

@Entry
@Component
struct menuEnableHoverScale {
  @State message: string = 'Hello World';
  private iconStr: Resource = $r('app.media.app_icon')
  @State index: number = 0;
  @State arrayStr: Array<string> = ['上半屏', '中轴', '下半屏']
  @State enableHoverMode: boolean | undefined = true;
  @State showInSubwindow: boolean = false;
  @State placement: Placement | undefined = undefined

  @Builder
  MyMenu1() {
    Menu() {
      MenuItem({ startIcon: this.iconStr, content: '菜单选项' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项' })
    }
  }

  @Builder
  MyMenu2() {
    Menu() {
      MenuItem({ startIcon: this.iconStr, content: '菜单选项0' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项1' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项2' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项3' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项4' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项5' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项6' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项7' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项8' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项9' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项0' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项1' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项2' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项3' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项4' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项5' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项6' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项7' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项8' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项9' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项0' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项1' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项2' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项3' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项4' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项5' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项6' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项7' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项8' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项9' })
    }.width(2000)
  }

  @State isShow: boolean = false

  build() {
    RelativeContainer() {
      Column() {
        Button('测试区域:' + this.arrayStr[this.index])
          .onClick(() => {
            if (this.index < 2) {
              this.index++
            } else {
              this.index = 0
            }
          })

        Button('子窗显示:' + (this.showInSubwindow ? '子窗' : '非子窗'))
          .onClick(() => {
            this.showInSubwindow = !this.showInSubwindow
          })

        Button('hoverMode开启:' + this.enableHoverMode)
          .onClick(() => {
            if (this.enableHoverMode == undefined) {
              this.enableHoverMode = true
            } else if (this.enableHoverMode == true) {
              this.enableHoverMode = false
            } else {
              this.enableHoverMode = undefined
            }
          })

        Button('MenuPlacement:' + this.placement)
          .onClick(() => {
            if (this.placement == undefined) {
              this.placement = Placement.Bottom
            } else if (this.placement == Placement.Bottom) {
              this.placement = Placement.Top
            } else if (this.placement == Placement.Top) {
              this.placement = Placement.Left
            } else {
              this.placement = undefined
            }
          })
      }

      Row() {
        Button('Menu测试')
          .fontWeight(FontWeight.Bold)
          .bindMenu(this.MyMenu1(), {
            enableHoverMode: this.enableHoverMode,
            showInSubWindow: this.showInSubwindow,
            placement: this.placement
          })
        Button('MenuMode默认值')
          .fontWeight(FontWeight.Bold)
          .bindMenu(this.MyMenu1(), {
            showInSubWindow: this.showInSubwindow,
            placement: this.placement
          })

        Button('Menu过大')
          .fontWeight(FontWeight.Bold)
          .bindMenu(this.MyMenu2(), {
            enableHoverMode: this.enableHoverMode,
            showInSubWindow: this.showInSubwindow,
            placement: this.placement
          })

        Select([{ value: '选项一' },
          { value: '选项二' },
          { value: '选项三' },
          { value: '选项四' },
          { value: '选项五' },
          { value: '选项六' },
          { value: '选项七' },
          { value: '选项八' },
          { value: '选项九' }]
        )
          .value('Select测试')

        Select([{ value: '选项一' },
          { value: '选项二' },
          { value: '选项三' },
          { value: '选项四' },
          { value: '选项五' },
          { value: '选项六' },
          { value: '选项七' },
          { value: '选项八' },
          { value: '选项九' },
          { value: '选项一' },
          { value: '选项二' },
          { value: '选项三' },
          { value: '选项四' },
          { value: '选项五' },
          { value: '选项六' },
          { value: '选项七' },
          { value: '选项八' },
          { value: '选项九' },
          { value: '选项一' },
          { value: '选项二' },
          { value: '选项三' },
          { value: '选项四' },
          { value: '选项五' },
          { value: '选项六' },
          { value: '选项七' },
          { value: '选项八' },
          { value: '选项九' }]
        )
          .value('Select过大')


      }
      .alignRules({
        center: { anchor: '__container__', align: VerticalAlign.Center },
        middle: { anchor: '__container__', align: HorizontalAlign.Center }
      })
      .margin({
        top: this.index == 2 ? 330 : this.index == 1 ? 50 : 0,
        bottom: this.index == 0 ? 330 : 0
      })
    }
    .height('100%')
    .width('100%')
  }
}
