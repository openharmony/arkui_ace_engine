/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

//[Start dropAnimationExample_start]
import { unifiedDataChannel, uniformTypeDescriptor } from '@kit.ArkData';
import { hilog } from '@kit.PerformanceAnalysisKit';

//[StartExclude dropAnimationExample_start]
export const dropAnimationRoutePrefix: string = 'dropAnimation';
//[EndExclude dropAnimationExample_start]
//[Start drop_hilog_const]
const DOMAIN = 0x0000;
const TAG = 'DropAnimationExampleTag';
//[End drop_hilog_const]

@Entry
@Component
export struct DropAnimationExample {
  //[StartExclude dropAnimationExample_start]
  @Consume pathStack: NavPathStack;
  //[EndExclude dropAnimationExample_start]
  @State targetImage: string = '';
  @State imageWidth: number = 100;
  @State imageHeight: number = 100;
  @State imgState: Visibility = Visibility.Visible;
  //[Start drop_customDropAnimation_start]
  customDropAnimation =
    () => {
      this.getUIContext().animateTo({ duration: 1000, curve: Curve.EaseOut, playMode: PlayMode.Normal }, () => {
        this.imageWidth = 200;
        this.imageHeight = 200;
        this.imgState = Visibility.None;
      });
    };

  //[End drop_customDropAnimation_start]
  build() {
    //[StartExclude dropAnimationExample_start]
    NavDestination() {
      //[EndExclude dropAnimationExample_start]
      Row() {
        Column() {
          //[Start drop_image_start]
          // 请将$r('app.media.app_icon')替换为实际资源文件
          Image($r('app.media.app_icon'))
            .width(100)
            .height(100)
            .draggable(true)
            .margin({ left: 15, top: 40 })
            .visibility(this.imgState)
            .onDragStart((event) => {
            })
            .onDragEnd((event) => {
              //[StartExclude drop_image_start]
              if (event.getResult() === DragResult.DRAG_SUCCESSFUL) {
                hilog.info(DOMAIN, TAG, '%{public}s', 'Drag Success');
              } else if (event.getResult() === DragResult.DRAG_FAILED) {
                hilog.info(DOMAIN, TAG, '%{public}s', 'Drag failed');
              }
              //[EndExclude drop_image_start]
            })
          //[End drop_image_start]

        }.width('45%')
        .height('100%')

        Column() {
          Text('Drag Target Area')
            .fontSize(20)
            .width(180)
            .height(40)
            .textAlign(TextAlign.Center)
            .margin(10)
            .backgroundColor('rgb(240,250,255)')
          //[Start drop_column_start]
          Column() {
            Image(this.targetImage)
              .width(this.imageWidth)
              .height(this.imageHeight)
          }
          .draggable(true)
          .margin({ left: 15 })
          .border({ color: Color.Black, width: 1 })
          .allowDrop([uniformTypeDescriptor.UniformDataType.IMAGE])
          .onDrop((dragEvent: DragEvent) => {
            let records: Array<unifiedDataChannel.UnifiedRecord> = dragEvent.getData().getRecords();
            let rect: Rectangle = dragEvent.getPreviewRect();
            this.imageWidth = Number(rect.width);
            this.imageHeight = Number(rect.height);
            this.targetImage = (records[0] as unifiedDataChannel.Image).imageUri;
            dragEvent.useCustomDropAnimation = true;
            dragEvent.executeDropAnimation(this.customDropAnimation);
          })
          //[End drop_column_start]
          .width(this.imageWidth)
          .height(this.imageHeight)
        }.width('45%')
        .height('100%')
        .margin({ left: '5%' })
      }
      .height('100%')
      //[StartExclude dropAnimationExample_start]
      .width('100%')
    }
    .backgroundColor('#f1f3f5')
    .title('', {
      backgroundBlurStyle: BlurStyle.COMPONENT_THICK,
      barStyle: BarStyle.STACK
    })
    // 请将$r('app.string.Pages_Index_DropAnimation')替换为实际资源文件，在本示例中该资源文件的value值为"拖放动画事件/DropAnimation"
    .title($r('app.string.Pages_Index_DropAnimation'))

    //[EndExclude dropAnimationExample_start]
  }
}

//[End dropAnimationExample_start]