/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law wasmli applicable law is agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

@Entry
@Component
struct MenuWithPreview {
  @State message: string = '';
  @State imageScale: number = 1.0;
  scroller: Scroller = new Scroller()
  
  private iconStr: Resource = $r('app.media.app_icon');

  @Builder
  ImagePreviewBuilder() {
    Column() {
      Image($r('app.media.app_icon'))
        .width(100)
        .height(100)
        .objectFit(ImageFit.Contain)
        .margin(10)
      Text('预览图片')
        .fontSize(14)
        .margin(5)
    }
    .backgroundColor('#f5f5f5')
    .borderRadius(10)
    .padding(10)
  }

  @Builder
  CustomPreviewBuilder() {
    Column() {
      Row({ space: 10 }) {
        Image($r('app.media.app_icon'))
          .width(60)
          .height(60)
          .objectFit(ImageFit.Contain)
        Column() {
          Text('自定义预览')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
          Text('这是自定义预览内容')
            .fontSize(12)
            .fontColor('#666666')
        }
        .alignItems(HorizontalAlign.Start)
      }
      .padding(10)
      .backgroundColor('#ffffff')
      .borderRadius(8)
    }
    .width(200)
    .backgroundColor('#f0f0f0')
    .borderRadius(12)
    .padding(10)
  }

  @Builder
  MenuWithPreviewContent() {
    Menu() {
      MenuItem({ content: '分享', startIcon: this.iconStr })
      MenuItem({ content: '复制链接', startIcon: this.iconStr })
      MenuItem({ content: '在新窗口打开', startIcon: this.iconStr })
      MenuItem({ content: '刷新', startIcon: this.iconStr })
      MenuItem({ content: '打印', startIcon: this.iconStr })
    }
  }

  build() {
    Scroll(this.scroller) {
      Column({ space: 20 }) {
        Text('菜单与预览图结合示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20 });

        Column({ space: 15 }) {
          Text('1. 基础预览菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('长按显示预览菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#e3f2fd')
            .borderRadius(8)
            .bindContextMenu(this.MenuWithPreviewContent, ResponseType.LongPress, {
              preview: this.ImagePreviewBuilder(),
              placement: Placement.Bottom,
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('2. 自定义预览菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('长按显示自定义预览')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#e8f5e9')
            .borderRadius(8)
            .bindContextMenu(this.MenuWithPreviewContent, ResponseType.LongPress, {
              preview: this.CustomPreviewBuilder(),
              placement: Placement.Bottom,
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('3. 预览图缩放效果')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Row({ space: 10 }) {
            Text('缩放 0.5')
              .fontSize(14)
              .padding(12)
              .backgroundColor('#fff3e0')
              .borderRadius(8)
              .bindContextMenu(this.MenuWithPreviewContent, ResponseType.LongPress, {
                preview: this.ImagePreviewBuilder(),
                previewAnimationOptions: { scale: [0.5, 0.5] },
                placement: Placement.Bottom
              })

            Text('缩放 1.0')
              .fontSize(14)
              .padding(12)
              .backgroundColor('#fce4ec')
              .borderRadius(8)
              .bindContextMenu(this.MenuWithPreviewContent, ResponseType.LongPress, {
                preview: this.ImagePreviewBuilder(),
                previewAnimationOptions: { scale: [1.0, 1.0] },
                placement: Placement.Bottom
              })

            Text('缩放 1.5')
              .fontSize(14)
              .padding(12)
              .backgroundColor('#f3e5f5')
              .borderRadius(8)
              .bindContextMenu(this.MenuWithPreviewContent, ResponseType.LongPress, {
                preview: this.ImagePreviewBuilder(),
                previewAnimationOptions: { scale: [1.5, 1.5] },
                placement: Placement.Bottom
              })
          }
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('4. 悬停缩放效果')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Row({ space: 10 }) {
            Text('hoverScale 1.0')
              .fontSize(14)
              .padding(12)
              .backgroundColor('#efebe9')
              .borderRadius(8)
              .bindContextMenu(this.MenuWithPreviewContent, ResponseType.LongPress, {
                preview: this.ImagePreviewBuilder(),
                previewAnimationOptions: {
                  hoverScale: [1.0, 1.0]
                },
                placement: Placement.Bottom
              })

            Text('hoverScale 1.2')
              .fontSize(14)
              .padding(12)
              .backgroundColor('#e8eaf6')
              .borderRadius(8)
              .bindContextMenu(this.MenuWithPreviewContent, ResponseType.LongPress, {
                preview: this.ImagePreviewBuilder(),
                previewAnimationOptions: {
                  hoverScale: [1.2, 1.2]
                },
                placement: Placement.Bottom
              })
          }
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('5. 不同位置预览')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Row({ space: 10 }) {
            Text('顶部')
              .fontSize(14)
              .padding(12)
              .backgroundColor('#e1f5fe')
              .borderRadius(8)
              .bindContextMenu(this.MenuWithPreviewContent, ResponseType.LongPress, {
                preview: this.ImagePreviewBuilder(),
                placement: Placement.Top
              })

            Text('左侧')
              .fontSize(14)
              .padding(12)
              .backgroundColor('#e8f5e9')
              .borderRadius(8)
              .bindContextMenu(this.MenuWithPreviewContent, ResponseType.LongPress, {
                preview: this.ImagePreviewBuilder(),
                placement: Placement.Left
              })

            Text('右侧')
              .fontSize(14)
              .padding(12)
              .backgroundColor('#fff3e0')
              .borderRadius(8)
              .bindContextMenu(this.MenuWithPreviewContent, ResponseType.LongPress, {
                preview: this.ImagePreviewBuilder(),
                placement: Placement.Right
              })
          }
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        if (this.message) {
          Text(`选择: ${this.message}`)
            .fontSize(16)
            .fontColor(Color.Red)
            .margin({ top: 10 });
        }
      }
    }
  }
}
