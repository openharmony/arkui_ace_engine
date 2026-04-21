/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

@Entry
@Component
struct BindContextMenu_LongPress {
  @State message: string = 'Hello World';
  @State listData: number[] = [0, 0, 0];
  private iconStr: ResourceStr = $r("app.media.app_icon");
  @State AVisible: Visibility = Visibility.Visible;
  @Builder
  MyMenuPreview() {
    Column() {
      // $r('app.media.image')需要替换为开发者所需的图像资源文件
      Image($r('app.media.app_icon'))
        .width(100)
        .height(100)
        .border({ width: 1 })
        .visibility(this.AVisible)
        .draggable(true)
        .onDragEnd((event: DragEvent) => {
          let ret = event.getResult();
          if(ret == 0) {
            console.info("enter ret == 0")
            this.AVisible = Visibility.Hidden;
          } else {
            console.info("enter ret != 0")
            this.AVisible = Visibility.Visible;
          }
        })
    }.width(200)
    .height(200)
  }
  @Builder
  MyPreview() {
    Column() {
      Image($r('app.media.app_icon'))
        .width(100)
        .height(100)
    }
  }
  @Builder MenuBuilder() {
    Flex({ direction: FlexDirection.Column, justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
      ForEach(this.listData, (item:number, index) => {
        Column() {
          Row() {
            Image($r("app.media.app_icon")).width(20).height(20).margin({ right: 5 })
            Text(`Menu${index as number + 1}`).fontSize(20)
          }
          .width('100%')
          .height(30)
          .justifyContent(FlexAlign.Center)
          .align(Alignment.Center)
          .onClick(() => {
            console.info(`Menu${index as number + 1} Clicked!`);
          })

          if (index != this.listData.length - 1) {
            Divider().height(10).width('80%').color('#ccc')
          }
        }.padding(5).height(40)
      })
    }.width(100)
  }
  @Builder
  MyMenu() {
    Menu() {
      MenuItem({ startIcon: this.iconStr, content: "菜单选项" })
      MenuItem({ startIcon: this.iconStr, content: "菜单选项" })
      MenuItem({ startIcon: this.iconStr, content: "菜单选项" })
    }.width(100).height(100)
  }
  build() {
    Scroll() {
      Column() {
        Text('bindContextMenu设置LongPress，Preview（IMAGE）和菜单在预览图上方时,拖拽预览图的显示效果(sizeChangeEffect为SIZE_TRANSITION)')
          .fontSize(20).fontColor(0x000020).fontWeight(FontWeight.Bold)
        Image($r('app.media.app_icon'))
          .width(80)
          .height(80)
          .dragPreview(this.MyPreview)
          .draggable(true)
          .bindContextMenu(this.MyMenu, ResponseType.LongPress,
          { preview: this.MyMenuPreview,
            placement: Placement.RightTop
          },
          )
          .onDragStart(() => {
            console.info("Image onDragStart")
          })
          .dragPreviewOptions({
            mode: [DragPreviewMode.ENABLE_TOUCH_POINT_CALCULATION_BASED_ON_FINAL_PREVIEW],
            sizeChangeEffect: DraggingSizeChangeEffect.SIZE_TRANSITION
          })
        Text('bindContextMenu设置LongPress，Preview（IMAGE）和菜单在预览图上方时,拖拽预览图的显示效果(sizeChangeEffect为SIZE_CONTENT_TRANSITION)')
          .fontSize(20).fontColor(0x000020).fontWeight(FontWeight.Bold)
        Image($r('app.media.app_icon'))
          .width(80)
          .height(80)
          .dragPreview(this.MyPreview)
          .draggable(true)
          .bindContextMenu(this.MyMenu, ResponseType.LongPress,
            { preview: this.MyMenuPreview,
              placement: Placement.RightTop
            },
          )
          .onDragStart(() => {
            console.info("Image onDragStart")
          })
          .dragPreviewOptions({
            mode: [DragPreviewMode.ENABLE_TOUCH_POINT_CALCULATION_BASED_ON_FINAL_PREVIEW],
            sizeChangeEffect: DraggingSizeChangeEffect.SIZE_CONTENT_TRANSITION
          })
        Text('设置一镜到底动效')
          .fontSize(20).fontColor(0x000020).fontWeight(FontWeight.Bold)
        Image($r('app.media.app_icon'))
          .width(80)
          .height(80)
          .bindContextMenu(this.MyMenu, ResponseType.LongPress,
            { preview: this.MyPreview,
              previewAnimationOptions: {
                hoverScale: [1.0, 0.95]
              }
            },
          )
      }
      .width('100%')
      .height('100%')
    }
  }
}