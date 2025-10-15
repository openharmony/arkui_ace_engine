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
struct hoverScaleInterruption {
  private iconStr: ResourceStr = $r('app.media.app_icon');
  @State private hoverScaleInterruption: boolean | undefined = false;
  @State private menuClickStr: string = 'xxx';

  @Builder
  MyMenu() {
    Menu() {
      MenuItem({ startIcon: this.iconStr, content: '菜单选项' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项' })
    }
  }

  @Builder
  MyPreview() {
    Column() {
      Image($r('app.media.app_icon'))
        .width(200)
        .height(20)
    }
  }

  build() {
    Scroll() {
      Column({ space: 10 }) {
        Row() {
          Text('hoverScaleInterruption: ')
          TextPicker({
            range: [
              'false',
              'true',
              'undefined',
            ], selected: 0
          })
            .width(100)
            .height(60)
            .selectedTextStyle({ font: { size: 14 } })
            .disappearTextStyle({ font: { size: 14 } })
            .canLoop(false)
            .textStyle({ font: { size: 14 } })
            .defaultPickerItemHeight(20)
            .onChange((value: string | string[], index: number | number[]) => {
              switch (value) {
                case 'false':
                  this.hoverScaleInterruption = false
                  break;
                case 'true':
                  this.hoverScaleInterruption = true
                  break;
                case 'undefined':
                  this.hoverScaleInterruption = undefined
                  break;
              }
            })
        }

        Row() {
          Text('menu click: ' + this.menuClickStr)
        }

        Divider()
        Text('预览菜单 preview Image').fontSize(9).fontColor(0xCCCCCC)
        Row() {
          Text('preview-image')
            .width(200)
            .height(100)
            .textAlign(TextAlign.Center)
            .margin(100)
            .fontSize(30)
            .bindContextMenu(this.MyMenu, ResponseType.LongPress,
              {
                preview: MenuPreviewMode.IMAGE,
                previewAnimationOptions: {
                  hoverScale: [1.0, 2.0],
                  hoverScaleInterruption: this.hoverScaleInterruption
                },
              })
            .onClick(() => {
              console.info('preview-image onClick')
              this.menuClickStr = 'preview-image click';
            })
            .backgroundColor('#ff3df2f5')
        }

        Divider()
        Text('预览菜单 preview Image_hoverScaleInterruption').fontSize(9).fontColor(0xCCCCCC)
        Row() {
          Text('preview-image')
            .width(200)
            .height(100)
            .textAlign(TextAlign.Center)
            .margin(100)
            .fontSize(30)
            .bindContextMenu(this.MyMenu, ResponseType.LongPress,
              {
                preview: MenuPreviewMode.IMAGE,
                previewAnimationOptions: {
                  hoverScale: [1.0, 2.0],
                  hoverScaleInterruption: this.hoverScaleInterruption
                },
              })
            .onClick(() => {
              console.info('preview-image onClick')
              this.menuClickStr = 'preview-image_hoverScaleInterruption click';
            })
            .backgroundColor('#ff3df2f5')
        }

        Divider()
        Text('无mask预览菜单').fontSize(9).fontColor(0xCCCCCC)
        Row() {
          Image($r('app.media.app_icon'))
            .width(100)
            .height(100)
            .margin(100)
            .bindContextMenu(this.MyMenu, ResponseType.LongPress,
              {
                preview: this.MyPreview,
                previewAnimationOptions: {
                  hoverScale: [1.0, 0.95],
                }
              })
            .onClick(() => {
              console.info('无mask onClick')
              this.menuClickStr = '无mask click';
            })
        }

        Divider()
        Text('无mask预览菜单_hoverScaleInterruption').fontSize(9).fontColor(0xCCCCCC)
        Row() {
          Image($r('app.media.app_icon'))
            .width(100)
            .height(100)
            .margin(100)
            .bindContextMenu(this.MyMenu, ResponseType.LongPress,
              {
                preview: this.MyPreview,
                previewAnimationOptions: {
                  hoverScale: [1.0, 0.95],
                  hoverScaleInterruption: this.hoverScaleInterruption
                },
                onAppear: () => {
                  console.info('bindContextMenu = 菜单弹出时的事件回调')
                },
                onDisappear: () => {
                  console.info('bindContextMenu = 菜单消失时的事件回调')
                },
                aboutToAppear: () => {
                  console.info('bindContextMenu = 菜单显示动效前的事件回调')
                },
                aboutToDisappear: () => {
                  console.info('bindContextMenu = 菜单退出动效前的事件回调')
                }
              })
            .onClick(() => {
              console.info('hoverScaleInterruption onClick')
              this.menuClickStr = 'hoverScaleInterruption click';
            })
        }

        Divider()
        Text('无mask预览菜单_hoverScaleInterruption_hoverScale=undefined').fontSize(9).fontColor(0xCCCCCC)
        Row() {
          Image($r('app.media.app_icon'))
            .width(100)
            .height(100)
            .margin(100)
            .bindContextMenu(this.MyMenu, ResponseType.LongPress,
              {
                preview: this.MyPreview,
                previewAnimationOptions: {
                  hoverScale: undefined,
                  hoverScaleInterruption: this.hoverScaleInterruption
                }
              })
            .onClick(() => {
              console.info('hoverScale=undefined onClick')
              this.menuClickStr = 'hoverScale=undefined click';
            })
        }

        Divider()
        Text('有mask预览菜单').fontSize(9).fontColor(0xCCCCCC)
        Row() {
          Image($r('app.media.app_icon'))
            .width(100)
            .height(100)
            .margin(100)
            .bindContextMenu(this.MyMenu, ResponseType.LongPress,
              {
                preview: this.MyPreview,
                mask: { color: Color.Pink, backgroundBlurStyle: BlurStyle.BACKGROUND_ULTRA_THICK },
                previewAnimationOptions: {
                  hoverScale: [1.0, 0.95]
                },
                onAppear: () => {
                  console.info('bindContextMenu = 菜单弹出时的事件回调')
                },
                onDisappear: () => {
                  console.info('bindContextMenu = 菜单消失时的事件回调')
                },
                aboutToAppear: () => {
                  console.info('bindContextMenu = 菜单显示动效前的事件回调')
                },
                aboutToDisappear: () => {
                  console.info('bindContextMenu = 菜单退出动效前的事件回调')
                }
              })
            .onClick(() => {
              console.info('mask onClick')
              this.menuClickStr = 'mask click';
            })
        }

        Divider()
        Text('有mask预览菜单_hoverScaleInterruption').fontSize(9).fontColor(0xCCCCCC)
        Row() {
          Image($r('app.media.app_icon'))
            .width(100)
            .height(100)
            .margin(100)
            .bindContextMenu(this.MyMenu, ResponseType.LongPress,
              {
                preview: this.MyPreview,
                mask: { color: Color.Green, backgroundBlurStyle: BlurStyle.COMPONENT_THIN },
                previewAnimationOptions: {
                  hoverScale: [1.0, 0.95],
                  hoverScaleInterruption: this.hoverScaleInterruption
                }
              })
            .onClick(() => {
              console.info('mask hoverScaleInterruption onClick')
              this.menuClickStr = 'mask hoverScaleInterruption click';
            })
        }

        Divider()
        Text('有mask预览菜单_hoverScaleInterruption_hoverScale=undefined').fontSize(9).fontColor(0xCCCCCC)
        Row() {
          Image($r('app.media.app_icon'))
            .width(100)
            .height(100)
            .margin(100)
            .bindContextMenu(this.MyMenu, ResponseType.LongPress,
              {
                preview: this.MyPreview,
                mask: { color: Color.Green, backgroundBlurStyle: BlurStyle.COMPONENT_THIN },
                previewAnimationOptions: {
                  hoverScale: undefined,
                  hoverScaleInterruption: this.hoverScaleInterruption
                }
              })
            .onClick(() => {
              console.info('mask hoverScaleInterruption onClick')
              this.menuClickStr = 'mask hoverScaleInterruption click';
            })
        }

        Divider()
        Text('transition 预览菜单').fontSize(9).fontColor(0xCCCCCC)
        Row() {
          Image($r('app.media.app_icon'))
            .width(100)
            .height(100)
            .margin(100)
            .bindContextMenu(this.MyMenu, ResponseType.LongPress,
              {
                preview: this.MyPreview,
                previewAnimationOptions: {
                  hoverScale: [1.0, 0.95],
                  transition: TransitionEffect.asymmetric(
                    TransitionEffect.OPACITY.animation({ duration: 2000, curve: Curve.Ease }).combine(
                      TransitionEffect.translate({ x: 50, y: 50 })),
                    TransitionEffect.OPACITY.animation({ duration: 2000, curve: Curve.Ease }).combine(
                      TransitionEffect.translate({ x: 50, y: 50 }))),
                  hoverScaleInterruption: this.hoverScaleInterruption
                }
              })
            .onClick(() => {
              console.info('transition onClick')
              this.menuClickStr = 'transition click';
            })
        }
      }
    }
  }
}