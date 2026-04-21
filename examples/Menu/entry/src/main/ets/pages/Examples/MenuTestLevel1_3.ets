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
* bindContextMenu设置预览图菜单专项
* 验证bindContextMenu设置预览图和previewAnimationOptions: 组合测试scale/hoverScale和transition
*/
@Extend(Text)
function paramTextStyle_a() {
  .fontSize(10)
  .width('100%')
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
struct MenuTestLevel1_3 {
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
      .dragPreview( () => {
      })
  }

  build() {
    Scroll(this.scroller){
      Column() {
        // previewAnimationOptions的scale和hoverScale
        Text(`验证bindContextMenu预览图的scale/hoverScale和transition的组合测试`).paramTextStyle_a()
        Column({space : 5}){
          Text(`bindContextMenu设置预览图, 设置scale和hoverScale, 不设置transition`).paramTextStyle_a()
          Image($r('app.media.app_icon'))
            .key(`setPreview_scale_hoverScale_unsetTransition`)
            .width('120').height(45)
            .bindContextMenu(this.MenuBuilder(), ResponseType.LongPress, {
              preview: this.MenuPreviewBuilder(),
              previewAnimationOptions: {
                scale: [0.8, 1.2],
                hoverScale: [0.7, 1.3]
              },
            })
          Image($r('app.media.app_icon'))
            .key(`setPreview_scale_hoverScale_unsetTransition_1`)
            .width('120').height(45)
            .bindContextMenu(this.menuShow[0],this.MenuBuilder(),  {
              preview: this.MenuPreviewBuilder(),
              previewAnimationOptions: {
                scale: [0.8, 1.2],
                hoverScale: [0.7, 1.3]
              },
              onDisappear: () => {
                this.menuShow[0] = false
              }
            })
            .onClick( () => {
              this.menuShow[0] = true
            })

          Text(`bindContextMenu设置预览图, 设置scale和hoverScale, 设置transition`).paramTextStyle_a()
          Image($r('app.media.app_icon'))
            .key(`setPreview_scale_hoverScale_setTransition`)
            .width('120').height(45)
            .bindContextMenu(this.MenuBuilder(), ResponseType.LongPress, {
              preview: this.MenuPreviewBuilder(),
              previewAnimationOptions: {
                scale: [0.8, 1.2],
                hoverScale: [0.7, 1.3]
              },
              transition: TransitionEffect.OPACITY.animation({ duration: 2000, curve: Curve.Ease })
            })
          Image($r('app.media.app_icon'))
            .key(`setPreview_scale_hoverScale_setTransition_1`)
            .width('120').height(45)
            .bindContextMenu(this.menuShow[1],this.MenuBuilder(),  {
              preview: this.MenuPreviewBuilder(),
              previewAnimationOptions: {
                scale: [0.8, 1.2],
                hoverScale: [0.7, 1.3]
              },
              transition: TransitionEffect.OPACITY.animation({ duration: 2000, curve: Curve.Ease }),
              onDisappear: () => {
                this.menuShow[1] = false
              }
            })
            .onClick( () => {
              this.menuShow[1] = true
            })

          Text(`bindContextMenu设置预览图, 设置scale和hoverScale, 设置preview的transition`).paramTextStyle_a()
          Image($r('app.media.app_icon'))
            .key(`setPreview_scale_hoverScale_setPreviewTransition`)
            .width('120').height(45)
            .bindContextMenu(this.MenuBuilder(), ResponseType.LongPress, {
              preview: this.MenuPreviewBuilder(),
              previewAnimationOptions: {
                scale: [0.8, 1.2],
                hoverScale: [0.7, 1.3],
                transition: TransitionEffect.OPACITY.animation({ duration: 2000, curve: Curve.Ease })
              },
            })
          Image($r('app.media.app_icon'))
            .key(`setPreview_scale_hoverScale_setPreviewTransition_1`)
            .width('120').height(45)
            .bindContextMenu(this.menuShow[2],this.MenuBuilder(),  {
              preview: this.MenuPreviewBuilder(),
              previewAnimationOptions: {
                scale: [0.8, 1.2],
                hoverScale: [0.7, 1.3],
                transition: TransitionEffect.OPACITY.animation({ duration: 2000, curve: Curve.Ease }),
              },
              onDisappear: () => {
                this.menuShow[2] = false
              }
            })
            .onClick( () => {
              this.menuShow[2] = true
            })

          Text(`bindContextMenu设置预览图, 不设置scale和hoverScale, 设置transition和preview的transition`).paramTextStyle_a()
          Image($r('app.media.app_icon'))
            .key(`setPreview_unsetScale_hoverScale_setPreviewTransition`)
            .width('120').height(45)
            .bindContextMenu(this.MenuBuilder(), ResponseType.LongPress, {
              preview: this.MenuPreviewBuilder(),
              previewAnimationOptions: {
                transition: TransitionEffect.OPACITY.animation({ duration: 2000, curve: Curve.Ease })
              },
            })
          Image($r('app.media.app_icon'))
            .key(`setPreview_unsetScale_hoverScale_setTransition_1`)
            .width('120').height(45)
            .bindContextMenu(this.menuShow[3],this.MenuBuilder(),  {
              preview: this.MenuPreviewBuilder(),
              transition: TransitionEffect.OPACITY.animation({ duration: 2000, curve: Curve.Ease }),
              onDisappear: () => {
                this.menuShow[3] = false
              }
            })
            .onClick( () => {
              this.menuShow[3] = true
            })
        }
        .columnStyle()
        Text(`验证bindContextMenu设置预览图和组件拖拽事件的组合测试`).paramTextStyle_a()
        Column({space: 5}){
          Image($r('app.media.app_icon'))
            .key(`setPreview_dragPreview`)
            .width('120').height(45)
            .bindContextMenu(this.MenuBuilder(), ResponseType.LongPress, {
              preview: this.MenuPreviewBuilder(),
              previewAnimationOptions: {
                hoverScale: [0.8, 1.2]
              }
            })
            .dragPreview( () => {
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