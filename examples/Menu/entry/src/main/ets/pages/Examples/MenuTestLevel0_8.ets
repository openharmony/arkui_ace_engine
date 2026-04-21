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
* 验证Menu组件： 是否可以单独使用：在其他父容器中 | Menu包含其他子组件： 可以在其他父容器中；不能包含其他子组件
* 验证Menu的宽度：设置宽度，优先处理宽度；不设置宽度，在父容器宽度范围内跟随子组件；多个子组件，最大宽度为宽度
* 验证Menu的宽度在bindMenu中绘制效果：百分比设置width
 */
import { MyComponent } from '../../common/MyComponent'

class BuilderOptions {
  width?: Length = '240'
  height?: Length = '300'
}

@Extend(Text) function paramTextStyle() {
  .fontSize(9)
  .width('100%')
}
@Extend(Text) function  componentTextStyle() {
  .fontSize(15)
  .backgroundColor(Color.Orange)
  .margin(3).padding(3)
  .borderWidth(1.0)
}
@Extend(Column) function columnStyle() {
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

@Entry
@Component
struct MenuTestLevel0_8 {
  scroller: Scroller = new Scroller()
  @State index: number[] = [0, 0, 0]
  private MenuWidthList: (Length | undefined)[] = [
  //1
    ,
    //2
    undefined,
    //3
    -30,
    //4
    '0',
    //5
    $r('app.float.float_30'),
    //6
    'calc(100-20)',
    //7
    80,
    //8
    '600vp',
    //9
    $r('app.string.EntryAbility_label'),
    //10
    '90aa',
    //11
    64,
    //12
    '90%'
  ]

  //Menu菜单：
  @Builder
  MenuBuilder($$: BuilderOptions) {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
    }
    .height($$.height)
    .width($$.width)
  }

  //Menu宽度Builder:
  @Builder
  MenuWidthBuilder() {
    Menu() {
    }
    .backgroundColor(Color.Blue)
    .height('30')
    .width(this.MenuWidthList[this.index[0]])
  }

  // Menu组件在Column组件中
  @Builder MenuBuilder_inColumn() {
    Column() {
      Menu() {
        MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
        MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
      }
    }
    .padding(10)
    .borderWidth(1.0)
    .borderRadius(12)
  }

  // Menu组件尺寸的不同场景
  @State menuWidthInfo: string = 'NA'
  @State menuHeightInfo: string = 'NA'
  @State menuPaddingMarginInfo: string = 'NA'


  // Menu组件的宽度
  @Builder MenuBuilder_width() {
    if (this.menuWidthInfo === 'Menu不设置width,不设置子组件') {
      Menu()
    }
    if (this.menuWidthInfo === 'Menu不设置width,设置子组件') {
      Menu() {
        MenuItem({ content: '菜单选项' })
      }
    }
    if (this.menuWidthInfo === 'Menu不设置width,设置宽的子组件') {
      Menu() {
        MenuItem({ content: '菜单选项'.repeat(6) })
      }
    }
    if (this.menuWidthInfo === 'Menu设置width-40,不设置子组件') {
      Menu() {

      }
      .width(40)
    }
    if (this.menuWidthInfo === 'Menu设置width-64,不设置子组件') {
      Menu() {

      }
      .width(64)
    }
    if (this.menuWidthInfo === 'Menu设置width-400,不设置子组件') {
      Menu() {

      }
      .borderWidth(1)
      .width(400)
    }
    if (this.menuWidthInfo === 'Menu设置width-100%,不设置子组件') {
      Menu() {

      }
      .borderWidth(1)
      .width('100%')
    }

    if (this.menuWidthInfo === 'Menu设置width-200,设置子组件') {
      Menu() {
        MenuItem({ content: '菜单选项'.repeat(6)})
      }
      .width(200)
    }
    if (this.menuWidthInfo === 'Menu设置width-200,设置不同子组件') {
      Menu() {
        MenuItem({ content: '菜单选项'.repeat(6)})
        MenuItem({ content: '菜单选项'.repeat(2)})
      }
      .width(200)
    }
  }

  // Menu组件的高度
  @Builder MenuBuilder_height() {
    if (this.menuHeightInfo === 'Menu不设置height,不设置子组件') {
      Menu()
        .width(120)
    }
    if (this.menuHeightInfo === 'Menu不设置height,设置子组件') {
      Menu() {
        MenuItem({ content: '菜单选项' })
      }
    }
    if (this.menuHeightInfo === 'Menu设置height-120,不设置子组件') {
      Menu() {
      }
      .width(120)
      .height(120)
    }
    if (this.menuHeightInfo === 'Menu设置height-100%,不设置子组件') {
      Menu() {
      }
      .width(120)
      .height('100%')
    }
    if (this.menuHeightInfo === 'Menu设置height-160,设置子组件') {
      Menu() {
        MenuItem({ content: '菜单选项' })
      }
      .height(160)
    }
    if (this.menuHeightInfo === 'Menu设置height-160,设置多个子组件') {
      Menu() {
        MenuItem({ content: '菜单选项1' })
        MenuItem({ content: '菜单选项2' })
        MenuItem({ content: '菜单选项3' })
        MenuItem({ content: '菜单选项4' })
        MenuItem({ content: '菜单选项5' })
      }
      .height(160)
    }
  }

  // Menu组件的内外边距
  // Menu组件的高度
  @Builder MenuBuilder_padding_margin() {
    if (this.menuPaddingMarginInfo === 'Menu组件不设置padding和margin') {
      Menu(){
        MenuItem({ content: '菜单选项' })
          .backgroundColor('#D2CAB3')
      }
      .backgroundColor('#B6C5D1')
    }
    if (this.menuPaddingMarginInfo === 'Menu组件设置padding为10/不设置margin') {
      Menu(){
        MenuItem({ content: '菜单选项' })
          .backgroundColor('#D2CAB3')
      }
      .backgroundColor('#B6C5D1')
      .padding(10)
    }
    if (this.menuPaddingMarginInfo === 'Menu组件不设置padding/设置margin为10') {
      Menu(){
        MenuItem({ content: '菜单选项' })
          .backgroundColor('#D2CAB3')
      }
      .backgroundColor('#B6C5D1')
      .margin(10)
    }
    if (this.menuPaddingMarginInfo === 'Menu组件设置padding和margin为10') {
      Menu(){
        MenuItem({ content: '菜单选项' })
          .backgroundColor('#D2CAB3')
      }
      .backgroundColor('#B6C5D1')
      .margin(10)
      .padding(10)
    }
  }

  build() {
    Scroll(this.scroller) {
      Column({ space: 5 }) {
        Text(`验证Menu组件作为子组件`)
          .paramTextStyle()
        Column({space: 5}){
          Text(`Menu组件在Column组件中`)
            .componentTextStyle()
            .bindMenu(this.MenuBuilder_inColumn())
        }
        .columnStyle()

        Text(`验证Menu宽度`)
          .paramTextStyle()
        Column({ space: 5 }) {
          Select([
            { value: 'Menu不设置width,不设置子组件' },
            { value: 'Menu不设置width,设置子组件' },
            { value: 'Menu不设置width,设置宽的子组件' },
            { value: 'Menu设置width-40,不设置子组件' },
            { value: 'Menu设置width-64,不设置子组件' },
            { value: 'Menu设置width-400,不设置子组件' },
            { value: 'Menu设置width-100%,不设置子组件' },
            { value: 'Menu设置width-200,设置子组件' },
            { value: 'Menu设置width-200,设置不同子组件' },
          ])
            .selectStyle()
            .onSelect((idx, value: string) => {
              switch (value) {
                case 'Menu不设置width,不设置子组件':
                  this.menuWidthInfo = 'Menu不设置width,不设置子组件'
                  break;
                case 'Menu不设置width,设置子组件':
                  this.menuWidthInfo = 'Menu不设置width,设置子组件'
                  break;
                case 'Menu不设置width,设置宽的子组件':
                  this.menuWidthInfo = 'Menu不设置width,设置宽的子组件'
                  break;
                case 'Menu设置width-40,不设置子组件':
                  this.menuWidthInfo = 'Menu设置width-40,不设置子组件'
                  break;
                case 'Menu设置width-64,不设置子组件':
                  this.menuWidthInfo = 'Menu设置width-64,不设置子组件'
                  break;
                case 'Menu设置width-400,不设置子组件':
                  this.menuWidthInfo = 'Menu设置width-400,不设置子组件'
                  break;
                case 'Menu设置width-100%,不设置子组件':
                  this.menuWidthInfo = 'Menu设置width-100%,不设置子组件'
                  break;
                case 'Menu设置width-200,设置子组件':
                  this.menuWidthInfo = 'Menu设置width-200,设置子组件'
                  break;
                case 'Menu设置width-200,设置不同子组件':
                  this.menuWidthInfo = 'Menu设置width-200,设置不同子组件'
                  break;
              }
            })
            .key('select_menuWidth')

          Text(`Menu: width`)
            .componentTextStyle()
            .bindMenu(this.MenuBuilder_width())
        }
        .columnStyle()

        Text(`验证Menu高度`)
          .paramTextStyle()
        Column({space: 5}){
          Select([
            { value: 'Menu不设置height,不设置子组件' },
            { value: 'Menu不设置height,设置子组件' },
            { value: 'Menu设置height-120,不设置子组件' },
            { value: 'Menu设置height-100%,不设置子组件' },
            { value: 'Menu设置height-160,设置子组件' },
            { value: 'Menu设置height-160,设置多个子组件' },
          ])
            .selectStyle()
            .onSelect((idx, value: string) => {
              switch (value) {
                case 'Menu不设置height,不设置子组件':
                  this.menuHeightInfo = 'Menu不设置height,不设置子组件'
                  break;
                case 'Menu不设置height,设置子组件':
                  this.menuHeightInfo = 'Menu不设置height,设置子组件'
                  break;
                case 'Menu设置height-120,不设置子组件':
                  this.menuHeightInfo = 'Menu设置height-120,不设置子组件'
                  break;
                case 'Menu设置height-100%,不设置子组件':
                  this.menuHeightInfo = 'Menu设置height-100%,不设置子组件'
                  break;
                case 'Menu设置height-160,设置子组件':
                  this.menuHeightInfo = 'Menu设置height-160,设置子组件'
                  break;
                case 'Menu设置height-160,设置多个子组件':
                  this.menuHeightInfo = 'Menu设置height-160,设置多个子组件'
                  break;
              }
            })
            .key('select_menuHeight')

          Text(`Menu: height`)
            .componentTextStyle()
            .bindMenu(this.MenuBuilder_height())
        }
        .columnStyle()

        Text(`验证Menu的内外边距`)
          .paramTextStyle()
        Column({space: 5}){
          Select([
            { value: 'Menu组件不设置padding和margin' },
            { value: 'Menu组件设置padding为10/不设置margin' },
            { value: 'Menu组件不设置padding/设置margin为10' },
            { value: 'Menu组件设置padding和margin为10' },
          ])
            .selectStyle()
            .onSelect((idx, value: string) => {
              switch (value) {
                case 'Menu组件不设置padding和margin':
                  this.menuPaddingMarginInfo = 'Menu组件不设置padding和margin'
                  break;
                case 'Menu组件设置padding为10/不设置margin':
                  this.menuPaddingMarginInfo = 'Menu组件设置padding为10/不设置margin'
                  break;
                case 'Menu组件不设置padding/设置margin为10':
                  this.menuPaddingMarginInfo = 'Menu组件不设置padding/设置margin为10'
                  break;
                case 'Menu组件设置padding和margin为10':
                  this.menuPaddingMarginInfo = 'Menu组件设置padding和margin为10'
                  break;
              }
            })
            .key('select_menuPaddingMargin')

          Text(`Menu: padding-margin`)
            .componentTextStyle()
            .bindMenu(this.MenuBuilder_padding_margin())
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
