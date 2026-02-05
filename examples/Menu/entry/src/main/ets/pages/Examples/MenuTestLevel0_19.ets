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

/*
* MenuItem组件设置不同尺寸
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
@Extend(MenuItem) function menuItemBorder() {
  .borderWidth(1.0)
  .borderColor(Color.Black)
}

@Entry
@Component
struct MenuTestLevel0_19 {
  scroller: Scroller = new Scroller()
  @State index: number[] = [0, 0, 0]

  //
  @State menuItemSizeInfo: string = ''
  @Builder
  MenuBuilder_ItemSize() {
    Menu() {
      if (this.menuItemSizeInfo === '不设置尺寸'){
        MenuItem({ 
            content: '复制', 
            labelInfo: 'Ctrl+C' 
        })
          .menuItemBorder()
        MenuItem({ 
            content: '粘贴', 
            labelInfo: 'Ctrl+V' 
        })
      }
      if (this.menuItemSizeInfo === 'height设置-20') {
        MenuItem({ 
            content: '复制', 
            labelInfo: 'Ctrl+C' 
        })
          .height('-20')
          .menuItemBorder()
        MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
      }
      if (this.menuItemSizeInfo === 'height设置0') {
        MenuItem({ 
            content: '复制', 
            labelInfo: 'Ctrl+C' 
        })
          .height(0)
          .menuItemBorder()

        MenuItem({ 
            content: '粘贴', 
            labelInfo: 'Ctrl+V' 
        })
      }
      if (this.menuItemSizeInfo === 'height设置60') {
        MenuItem({ 
            content: '复制', 
            labelInfo: 'Ctrl+C' 
        })
          .height(60)
          .menuItemBorder()

        MenuItem({ 
            content: '粘贴', 
            labelInfo: 'Ctrl+V' 
        })
      }
      if (this.menuItemSizeInfo === 'height设置60vp') {
        MenuItem({ 
            content: '复制', 
            labelInfo: 'Ctrl+C' 
            })
          .height('60vp')
          .menuItemBorder()

        MenuItem({ 
            content: '粘贴', 
            labelInfo: 'Ctrl+V' 
            })
      }
      if (this.menuItemSizeInfo === 'height设置60px') {
        MenuItem({ 
            content: '复制', 
            labelInfo: 'Ctrl+C' 
            })
          .height('60px')
          .menuItemBorder()

        MenuItem({ 
            content: '粘贴', 
            labelInfo: 'Ctrl+V' 
            })
      }
      if (this.menuItemSizeInfo === 'height设置60lpx') {
        MenuItem({ 
            content: '复制', 
            labelInfo: 'Ctrl+C' 
            })
          .height('60lpx')
          .menuItemBorder()

        MenuItem({ 
            content: '粘贴', 
            labelInfo: 'Ctrl+V' 
            })
      }
      if (this.menuItemSizeInfo === 'height设置60fp') {
        MenuItem({ 
            content: '复制', 
            labelInfo: 'Ctrl+C' 
            })
          .height('60fp')
          .menuItemBorder()

        MenuItem({ 
            content: '粘贴', 
            labelInfo: 'Ctrl+V' 
            })
      }
      if (this.menuItemSizeInfo === 'height设置60%') {
        MenuItem({ 
            content: '复制', 
            labelInfo: 'Ctrl+C' 
            })
          .height('60%')
          .menuItemBorder()

        MenuItem({ 
            content: '粘贴', 
            labelInfo: 'Ctrl+V' 
            })
      }
      if (this.menuItemSizeInfo === 'height设置30') {
        MenuItem({ 
            content: '复制', 
            labelInfo: 'Ctrl+C' 
            })
          .height(30)
          .menuItemBorder()

        MenuItem({ 
            content: '粘贴', 
            labelInfo: 'Ctrl+V' 
            })
      }
      if (this.menuItemSizeInfo === 'height设置600') {
        MenuItem({ 
            content: '复制', 
            labelInfo: 'Ctrl+C' 
            })
          .height('600')
          .menuItemBorder()

        MenuItem({ 
            content: '粘贴', 
            labelInfo: 'Ctrl+V' 
            })
      }
    }
  }

  build() {
    Scroll(this.scroller) {
      Column({ space: 5 }) {
        Text(`验证MenuItem尺寸的绘制效果`)
          .paramTextStyle()
        Column({space: 5}){
          Text(`选择MenuItem的尺寸参数`)
            .paramTextStyle()
          Select([
            { value:'不设置尺寸' },
            { value:'height设置-20' },
            { value:'height设置0' },
            { value:'height设置60' },
            { value:'height设置60vp' },
            { value:'height设置60px' },
            { value:'height设置60lpx' },
            { value:'height设置60fp' },
            { value:'height设置60%' },
            { value:'height设置30' },
            { value:'height设置600' },
          ])
            .selectStyle()
            .onSelect((idx, value: string) => {
              this.menuItemSizeInfo = value
            })
            .key('select_menuItemSize')

          Text(`MenuItem: size`)
            .componentTextStyle()
            .bindMenu(this.MenuBuilder_ItemSize())
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
