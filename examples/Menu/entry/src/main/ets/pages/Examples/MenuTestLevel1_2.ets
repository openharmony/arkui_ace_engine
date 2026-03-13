/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

// xxx.ets
/*
/
* 不同次级菜单类型, 多级菜单绘制效果绘制
*
* 验证Menu的customBuilder:
* 多级菜单的绘制验证：重点验证UX位置和避让
*
 */
import { MyComponent } from '../../common/MyComponent'

class BuilderOptions {
  width?: Length = '240'
  height?: Length = '300'
}

@Extend(Text)
function paramTextStyle() {
  .fontSize(9)
  .width('100%')
}
@Extend(Text)
function componentTextStyle() {
  .fontSize(15)
  .borderWidth(1.0)
  .backgroundColor(Color.Orange)
  .textAlign(TextAlign.Center)
}
@Extend(Column)
function columnStyle() {
  .borderWidth(1.0)
  .padding(10)
  .width('100%')
  .backgroundColor(Color.Pink)
}
@Extend(Select) function selectStyle() {
  .width('50%')
  .controlSize(ControlSize.SMALL)
  .selected(0)
  .backgroundColor(Color.Orange)
}
@Extend(MenuItem) function menuItemStyle() {
  .borderWidth(1.0)
}

@Entry
@Component
struct MenuTestLevel1_2 {
  scroller: Scroller = new Scroller()
  @State showInSubWindow: boolean = false
  @State subMenuMode: SubMenuExpandingMode = 0
  @State subMenuMode_1: SubMenuExpandingMode = 0
  @State menuShow: boolean = false

  @State menuHoverInfo: string = ''

  // 一级菜单
  @Builder MenuBuilder_NO_0() {
    Menu() {
      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '二级菜单',
        endIcon: $r('app.media.app_icon'),
        builder: this.SubMenuBuilder_NO_0()
      })
      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '三级菜单',
        endIcon: $r('app.media.app_icon'),
        builder: this.MenuBuilder_NO_1()
      })
    }
    .subMenuExpandingMode(this.subMenuMode)
  }
  @Builder MenuBuilder_NO_1() {
    Menu() {
      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '次级菜单',
        endIcon: $r('app.media.app_icon'),
        builder: this.SubMenuBuilder_NO_0()
      })
        .borderWidth(1.0)
      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '菜单选项',
        endIcon: $r('app.media.app_icon'),
      })
    }
    .subMenuExpandingMode(this.subMenuMode_1)
  }
  @Builder SubMenuBuilder_NO_0() {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
        .borderWidth(1.0)
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
    }
  }

  @Builder SubMenuBuilder_NO_1() {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
        .borderWidth(1.0)
        .margin({top: 10})
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
    }
  }

  // hover对齐的菜单
  @Builder
  HoverMenuBuilder() {
    Menu() {
      MenuItem({
        content: '默认选项',
        builder: this.SubMenuBuilder_NO_0()
      })
        .borderWidth(1.0)
      MenuItem({
        content: '外边距次级',
        builder: this.SubMenuBuilder_NO_1()
      })
        .borderWidth(1.0)

      MenuItem({
        content: '外边距选项',
        builder: this.SubMenuBuilder_NO_0()
      })
        .margin({top: 10})
        .borderWidth(1.0)
      MenuItem({
        content: '外边距选项/次级',
        builder: this.SubMenuBuilder_NO_1()
      })
        .margin({top: 10})
        .borderWidth(1.0)

      MenuItem({
        content: '三级菜单',
        builder: this.MenuBuilder_NO_1()
      })
        .borderWidth(1.0)
    }
    .padding(10)
  }

  build() {
    Scroll(this.scroller) {
      Column({ space: 5 }) {
        Text(`验证多级菜单的绘制`)
          .paramTextStyle()
        Column({ space: 3 }) {
          Text(`切换一级菜单的次级菜单类型`)
            .paramTextStyle()
          Select([
            { value:'SIDE' },
            { value:'EMBEDDED' },
            { value:'STACK' },
          ])
            .selectStyle()
            .value('SIDE')
            .onSelect((idx, value: string) => {
              switch (value) {
                case 'SIDE':
                  this.subMenuMode = 0
                  break;
                case 'EMBEDDED':
                  this.subMenuMode = 1
                  break;
                case 'STACK':
                  this.subMenuMode = 2
                  break;

              }
            })
            .key('select_main_subMenuMode')

          Text(`切换二级菜单的次级菜单类型`)
            .paramTextStyle()
          Select([
            { value:'SIDE' },
            { value:'EMBEDDED' },
            { value:'STACK' },
          ])
            .selectStyle()
            .value('SIDE')
            .onSelect((idx, value: string) => {
              switch (value) {
                case 'SIDE':
                  this.subMenuMode_1 = 0
                  break;
                case 'EMBEDDED':
                  this.subMenuMode_1 = 1
                  break;
                case 'STACK':
                  this.subMenuMode_1 = 2
                  break;
              }
            })
            .key('select_sub_subMenuMode')

          Text('Menu：MultipleLevel')
            .backgroundColor(Color.Orange)
            .bindContextMenu(this.menuShow, this.MenuBuilder_NO_0(), {
              placement: Placement.Bottom,
              onDisappear: () => {
                this.menuShow = false
              }
            })
            .onClick( () => {
              this.menuShow = true
            })
        }
        .columnStyle()

        Column({space: 5}){
          Text(`验证side次级菜单的hover对齐`)
            .paramTextStyle()
          Text(`菜单: hover对齐`)
            .componentTextStyle()
            .bindMenu(this.HoverMenuBuilder())
        }
        .columnStyle()
      }
      .width('100%')
    }
    .padding(12)
    .align(Alignment.TopStart)
    .width('100%').height('100%')
  }

  pageTransition() {
    //进入该界面没有跳转延迟
    PageTransitionEnter({ type: RouteType.None, duration: 0 })
  }
}