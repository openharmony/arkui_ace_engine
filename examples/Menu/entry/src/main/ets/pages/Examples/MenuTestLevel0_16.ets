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

/*
 * bindContextMenu设置预览图菜单
 * 验证BindContextMenu的类型和预览图绘制
 */

import { MyComponent } from '../../common/MyComponent'

class SizeOption {
  public width?: Length = '240'
  public height?: Length = '300'
}

@Extend(Text)
function paramTextStyle() {
  .fontSize(9)
  .width('100%')
}

@Extend(Text)
function componentStyle() {
  .backgroundColor(Color.Orange)
  .textAlign(TextAlign.Center)
}

@Extend(Column)
function columnStyle() {
  .borderWidth(1.0)
  .padding(5)
  .width('100%')
  .backgroundColor(Color.Pink)
}

@Entry
@Component
struct MenuTestLevel0_16 {
  //ets layout
  scroller: Scroller = new Scroller()
  @State index: number[] = [0, 0, 0, 0, 0,]
  //菜单交互优化
  @State menuShow: boolean[] = [false, false, false]

  //Menu Builder
  @Builder
  MenuBuilder() {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
    }
  }

  //预览图菜单自定义预览图
  @Builder
  MenuPreviewBuilder() {
    Image($r('app.media.app_icon'))
      .width(160)
      .height(100)
  }

  //Menu菜单：设置不同的高度、宽度
  @Builder
  MenuBuilderSized($$: SizeOption) {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
    }
    .borderWidth(1.0)
    .height($$.height)
    .width($$.width)
  }

  //different size preview
  @Builder
  MenuPreviewBuilderSized($$: SizeOption) {
    Column() {
      Image($r('app.media.app_icon'))
    }
    .width($$.width)
    .height($$.height)
  }

  @State previewBuilderSizeOptions: SizeOption = {
    width: 240,
    height: 160
  }
  //menuPreviewMode test list
  @State menuPreviewModeTestList: (MenuPreviewMode | CustomBuilder | undefined)[] = [
  //1
    MenuPreviewMode.NONE, //无预览图，无蒙层
    //2
    MenuPreviewMode.IMAGE,
    //3
    undefined, ////无预览图，无蒙层
    //4
    7,
  ]

  build() {
    Scroll(this.scroller) {
      Column({ space: 5 }) {
        //bindContextMenu longPress类型不设置自定义预览图
        Text('验证bindContextMenu的类型和预览图绘制')
          .paramTextStyle()
        Column({ space: 5 }) {
          Text('contextMenu设置longPress / show, 不设置preview')
            .paramTextStyle()
          Text('contextMenu: \nlongPress_unsetPreview')
            .key('contextMenu: longPress_unsetPreview')
            .componentStyle()
            .bindContextMenu(this.MenuBuilder(), ResponseType.LongPress, {
              enableArrow: true,
            })
          Text('contextMenu: \nsetShow_unsetPreview')
            .key('contextMenu:setShow_unsetPreview')
            .componentStyle()
            .bindContextMenu(this.menuShow[0], this.MenuBuilder(), {
              enableArrow: true,
              onDisappear: () => {
                this.menuShow[0] = false
              }
            })
            .onClick(() => {
              this.menuShow[0] = true
            })

          Text(`bindContextMenu设置rightClick, 设置preview`)
            .paramTextStyle()
          Text('contextMenu: \nrightClick_preview')
            .key(`contextMenu: rightClick_preview`)
            .componentStyle()
            .bindContextMenu(this.MenuBuilder(), ResponseType.RightClick, {
              preview: MenuPreviewMode.IMAGE, //预期无预览图，没有蒙层
              enableArrow: true,
            })
        }
        .columnStyle()

        Column({ space: 5 }) {
          Text(`bindContextMenu设置longPress/show, 设置preview`)
            .paramTextStyle()
          Row({ space: 2 }) {
            Text(`${this.index[0] + 1}` + ' / ')
              .fontSize(9)
            Text(`${this.menuPreviewModeTestList.length}`)
              .key('paramSets_key_0')
              .fontSize(9)
            MyComponent({
              title: 'Test0+', func: () => {
                this.index[0]++
                if (this.index[0] == this.menuPreviewModeTestList.length) {
                  this.index[0] = 0
                }
              }
            })
            MyComponent({
              title: 'Test0-', func: () => {
                this.index[0]--
                if (this.index[0] <= -1) {
                  this.index[0] = this.menuPreviewModeTestList.length - 1
                }
              }
            })
          }

          Text('contextMenu: \nlongPress_preview')
            .key(`contextMenu: longPress_preview`)
            .componentStyle()
            .bindContextMenu(this.MenuBuilder(), ResponseType.LongPress, {
              preview: this.menuPreviewModeTestList[this.index[0]],
              enableArrow: true,
            })
          Text('contextMenu: \nshow_preview')
            .key(`contextMenu: show_preview`)
            .componentStyle()
            .bindContextMenu(this.menuShow[1], this.MenuBuilder(), {
              preview: this.menuPreviewModeTestList[this.index[0]],
              enableArrow: true,
              onDisappear: () => {
                this.menuShow[1] = false
              }
            })
            .onClick(() => {
              this.menuShow[1] = true
            })
        }
        .columnStyle()

        Column({ space: 5 }) {
          Text(`preview设置自定义预览图的绘制效果`)
            .paramTextStyle()
          Image($r('app.media.app_icon'))
            .key(`contextMenu: previewCustom`)
            .width('120').height(45)
            .bindContextMenu(this.MenuBuilderSized({ width: 200 }), ResponseType.LongPress, {
              preview: this.MenuPreviewBuilderSized({
                width: this.previewBuilderSizeOptions.width,
                height: this.previewBuilderSizeOptions.height
              })
            })
        }
        .columnStyle()
      }
      .width('100%')
    }
    .padding(12)
    .align(Alignment.TopStart)
    .width('100%').height('100%')
  }
}