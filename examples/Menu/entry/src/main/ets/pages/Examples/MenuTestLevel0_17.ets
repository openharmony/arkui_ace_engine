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
 * 验证bindContextMenu设置预览图和previewAnimationOptions: scale和hoverScale
 */

import { MyComponent } from '../../common/MyComponent'

@Extend(Text) function  paramTextStyle() {
  .fontSize(9)
  .width('100%')
}
@Extend(Column) function columnStyle() {
  .borderWidth(1.0)
  .padding(5)
  .width('100%')
  .backgroundColor(Color.Pink)
}
@Entry
@Component
struct MenuTestLevel0_17 {
  //ets layout
  scroller: Scroller = new Scroller()
  @State index: number[] = [0, 0, 0, 0, 0, ]
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
  @Builder MenuPreviewBuilder() {
    Image($r('app.media.app_icon'))
      .width(160)
      .height(100)
  }
  // previewAnimationOptions test list
  @State menuPreviewAnimationOptionsTestList: (ContextMenuAnimationOptions | undefined) [] = [
  //1
    {
      scale: undefined,
      hoverScale: undefined
    },
    //2
    {
      scale: [0.95, 1.1],
      hoverScale: [0.8, 1.2]
    },
    //3
    {
      scale: [-1.0, 2.0],
      hoverScale: [-0.5, 1.2]
    },
    //4
    {
      scale: [0.7, -1.0],
      hoverScale: [0.5, -1.2]
    },
    //5
    {
      scale: [0, 1.5],
      hoverScale: [0, 1.5]
    },
    //6
    {
      scale: [0.5, 0],
      hoverScale: [0.6, 0]
    },
    //7
    {
      scale: [0.6, 1.5],
      hoverScale: [0.7, 1.2]
    },
    //8
    {
      scale: [1.5,0.6],
      hoverScale: [1.2, 0.7]
    },
    //9
    {
      scale: [2, 3],
      hoverScale: [2, 3]
    },
    //10
    {
      scale: [0.4, 0.7],
      hoverScale: [0.4, 0.7]
    },
  ]
  build() {
    Scroll(this.scroller){
      Column({space: 5}) {
        // previewAnimationOptions的scale和hoverScale
        Text(`验证bindContextMenu入参opt的previewAnimationOptions`)
          .paramTextStyle()
        Column({space : 5}){
          Text(`bindContextMenu设置IMAGE预览图, 设置scale和hoverScale (预期不生效)`)
            .paramTextStyle()
          Image($r('app.media.app_icon'))
            .key(`previewImage_setScaleAndHoverScale`)
            .width('120').height(45)
            .bindContextMenu(this.MenuBuilder(), ResponseType.LongPress, {
              preview: MenuPreviewMode.IMAGE,
              previewAnimationOptions: {
                hoverScale: [0.5, 1.5],
                scale: [0.5, 1.5]
              }
            })
          Text(`bindContextMenu不设置预览图, 设置scale和hoverScale`)
            .paramTextStyle()
          Image($r('app.media.app_icon'))
            .key(`unsetPreview_setScaleAndHoverScale`)
            .width('120').height(45)
            .bindContextMenu(this.MenuBuilder(), ResponseType.LongPress, {
              previewAnimationOptions: {
                hoverScale: [0.5, 1.5],
                scale: [0.5, 1.5]
              }
            })
          Image($r('app.media.app_icon'))
            .key(`unsetPreview_setScaleAndHoverScale_1`)
            .width('120').height(45)
            .bindContextMenu(this.menuShow[1],this.MenuBuilder(),  {
              previewAnimationOptions: {
                hoverScale: [0.5, 1.5],
                scale: [0.5, 1.5]
              },
              onDisappear: () => {
                this.menuShow[1] = false
              }
            })
            .onClick( () => {
              this.menuShow[1] = true
            })
          Text(`bindContextMenu设置自定义预览图, 设置scale和hoverScale`)
            .paramTextStyle()
          Row({ space: 2 }) {
            Text(`${this.index[0] + 1}` + ' / ')
              .fontSize(9)
            Text(`${this.menuPreviewAnimationOptionsTestList.length}`)
              .key('paramSets_key_0')
              .fontSize(9)
            MyComponent({
              title: 'Test0+', func: () => {
                this.index[0]++
                if (this.index[0] == this.menuPreviewAnimationOptionsTestList.length) {
                  this.index[0] = 0
                }
              }
            })
            MyComponent({
              title: 'Test0-', func: () => {
                this.index[0]--
                if (this.index[0] <= -1) {
                  this.index[0] = this.menuPreviewAnimationOptionsTestList.length - 1
                }
              }
            })
          }
          Row({ space: 2 }) {
            Text(`${this.index[1] + 1}` + ' / ')
              .fontSize(9)
            Text(`${this.menuPreviewAnimationOptionsTestList.length}`)
              .key('paramSets_key_1')
              .fontSize(9)
            MyComponent({
              title: 'Test1+', func: () => {
                this.index[1]++
                if (this.index[1] == this.menuPreviewAnimationOptionsTestList.length) {
                  this.index[1] = 0
                }
              }
            })
            MyComponent({
              title: 'Test1-', func: () => {
                this.index[1]--
                if (this.index[1] <= -1) {
                  this.index[1] = this.menuPreviewAnimationOptionsTestList.length - 1
                }
              }
            })
          }
          Image($r('app.media.app_icon'))
            .key(`setPreview_setScaleAndHoverScale`)
            .width('120').height(45)
            .bindContextMenu(this.MenuBuilder(), ResponseType.LongPress, {
              preview: this.MenuPreviewBuilder(),
              previewAnimationOptions: {
                scale: this.menuPreviewAnimationOptionsTestList[this.index[0]]?.scale,
                hoverScale: this.menuPreviewAnimationOptionsTestList[this.index[1]]?.hoverScale,
              }
            })
          Image($r('app.media.app_icon'))
            .key(`setPreview_setScaleAndHoverScale_1`)
            .width('120').height(45)
            .bindContextMenu(this.menuShow[2], this.MenuBuilder(),  {
              preview: this.MenuPreviewBuilder(),
              previewAnimationOptions: {
                scale: this.menuPreviewAnimationOptionsTestList[this.index[0]]?.scale,
                hoverScale: this.menuPreviewAnimationOptionsTestList[this.index[1]]?.hoverScale,
              },
              onDisappear: () => {
                this.menuShow[2] = false
              }
            })
            .onClick( () => {
              this.menuShow[2] = true
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