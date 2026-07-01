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

// [Start default_drag]
// [Start module_draggable_head]
import { unifiedDataChannel, uniformTypeDescriptor } from '@kit.ArkData';
// [End module_draggable_head]
// [Start onDragEnd_start]
// [StartExclude onDragEnd_start]
import { BusinessError } from '@kit.BasicServicesKit';
import { image } from '@kit.ImageKit';
// [Start drag_hilog_const]
import { hilog } from '@kit.PerformanceAnalysisKit';

const DOMAIN = 0x0000;
const TAG = 'DefaultDragError: ';
// [End drag_hilog_const]

@Entry
@Component
export struct DefaultDrag {
  @State targetImage: string = '';
  @State imageWidth: number = 100;
  @State imageHeight: number = 100;
  @State imgState: Visibility = Visibility.Visible;
  @State pixmap: image.PixelMap | undefined = undefined;

  // [Start generate_pix_map]
  @Builder
  pixelMapBuilder() {
    Column() {
      // 请将$r('app.media.startIcon')替换为实际资源文件
      Image($r('app.media.startIcon'))
        .width(120)
        .height(120)
        // [StartExclude default_drag]
        // [StartExclude generate_pix_map]
        .backgroundColor(Color.Yellow)
      // [EndExclude default_drag]
      // [EndExclude generate_pix_map]
    }
  }

  // [StartExclude generate_pix_map]
  // [Start data_delayed_retry]
  getDataFromUdmfRetry(event: DragEvent, callback: (data: DragEvent) => void) {
    try {
      let data: UnifiedData = event.getData();
      if (!data) {
        return false;
      }
      let records: unifiedDataChannel.UnifiedRecord[] = data.getRecords();
      if (!records || records.length <= 0) {
        return false;
      }
      callback(event);
      return true;
    } catch (e) {
      hilog.error(DOMAIN, TAG, `${(e as BusinessError).code}, message: ${(e as BusinessError).message}`);
      return false;
    }
  }

  getDataFromUdmf(event: DragEvent, callback: (data: DragEvent) => void) {
    if (this.getDataFromUdmfRetry(event, callback)) {
      return;
    }
    setTimeout(() => {
      this.getDataFromUdmfRetry(event, callback);
    }, 1500);
  }

  // [End data_delayed_retry]
  // [EndExclude generate_pix_map]
  // 调用componentSnapshot中的createFromBuilder接口截取自定义builder的截图
  private getComponentSnapshot(): void {
    this.getUIContext().getComponentSnapshot().createFromBuilder(() => {
      this.pixelMapBuilder();
    },
      (error: Error, pixmap: image.PixelMap) => {
        if (error) {
          hilog.error(DOMAIN, TAG, '%{public}s', JSON.stringify(error));
          return;
        }
        this.pixmap = pixmap;
      });
  }

  // [End generate_pix_map]
  build() {
    // [StartExclude default_drag]
    NavDestination() {
      Column({ space: 12 }) {
        // [EndExclude default_drag]
        Row() {
          Column() {
            Text('start Drag')
              .fontSize(18)
              .width('100%')
              .height(40)
              .margin(10)
              .backgroundColor('#008888')
            Row() {
              // [Start module_draggable]
              // 请将$r('app.media.app_icon')替换为实际资源文件
              Image($r('app.media.app_icon'))
                .width(100)
                .height(100)
                .draggable(true)
                // [StartExclude module_draggable]
                .margin({ left: 15 })
                .visibility(this.imgState)
                // 绑定平行手势，可同时触发应用自定义长按手势
                // [Start bind_parallel_gesture]
                .parallelGesture(LongPressGesture().onAction(() => {
                  this.getUIContext()
                    .getPromptAction()
                    .showToast({ duration: 100, message: 'Long press gesture trigger' });
                }))
                // [End bind_parallel_gesture]
                // [EndExclude module_draggable]
                .onDragStart((event) => {
                  let data: unifiedDataChannel.Image = new unifiedDataChannel.Image();
                  // 'resources/base/media/app_icon.png'需要替换为开发者所需的图像资源文件
                  data.imageUri = 'resources/base/media/app_icon.png';
                  let unifiedData = new unifiedDataChannel.UnifiedData(data);
                  event.setData(unifiedData);

                  let dragItemInfo: DragItemInfo = {
                    pixelMap: this.pixmap,
                    extraInfo: 'this is extraInfo',
                  };
                  // onDragStart回调函数中返回自定义拖拽背板图
                  return dragItemInfo;
                })
                // [End module_draggable]
                // 提前准备拖拽自定义背板图
                // [Start set_custom_drag_status]
                .onPreDrag((preDragStatus: PreDragStatus) => {
                  if (preDragStatus == PreDragStatus.ACTION_DETECTING_STATUS) {
                    this.getComponentSnapshot();
                  }
                })
                // [End set_custom_drag_status]
                // [Start set_on_drag_end]
                // [EndExclude onDragEnd_start]
                .onDragEnd((event) => {
                  // onDragEnd里取到的result值在接收方onDrop设置
                  if (event.getResult() === DragResult.DRAG_SUCCESSFUL) {
                    this.getUIContext().getPromptAction().showToast({ duration: 100, message: 'Drag Success' });
                  } else if (event.getResult() === DragResult.DRAG_FAILED) {
                    this.getUIContext().getPromptAction().showToast({ duration: 100, message: 'Drag failed' });
                  }
                })
              // [End onDragEnd_start]
              // [End set_on_drag_end]
            }

            Text('Drag Target Area')
              .fontSize(20)
              .width('100%')
              .height(40)
              .margin(10)
              .backgroundColor('#008888')
            Row() {
              Image(this.targetImage)
                .width(this.imageWidth)
                .height(this.imageHeight)
                .draggable(true)
                .margin({ left: 15 })
                .border({ color: Color.Black, width: 1 })// 控制角标显示类型为MOVE，即不显示角标
                // [Start set_drag_behavior_move]
                .onDragMove((event) => {
                  event.setResult(DragResult.DROP_ENABLED);
                  event.dragBehavior = DragBehavior.COPY;
                })
                // [End set_drag_behavior_move]
                // [Start drag_allow_drop]
                .allowDrop([uniformTypeDescriptor.UniformDataType.HYPERLINK,
                  uniformTypeDescriptor.UniformDataType.PLAIN_TEXT])
                // [End drag_allow_drop]
                // [Start allow_drag_type]
                .allowDrop([uniformTypeDescriptor.UniformDataType.IMAGE])
                // [End allow_drag_type]
                // [Start set_on_drop_call]
                .onDrop((dragEvent?: DragEvent) => {
                  // 获取拖拽数据
                  this.getDataFromUdmf((dragEvent as DragEvent), (event: DragEvent) => {
                    let records: unifiedDataChannel.UnifiedRecord[] = event.getData().getRecords();
                    let rect: Rectangle = event.getPreviewRect();
                    this.imageWidth = Number(rect.width);
                    this.imageHeight = Number(rect.height);
                    this.targetImage = (records[0] as unifiedDataChannel.Image).imageUri;
                    this.imgState = Visibility.None;
                    // 显式设置result为successful，则将该值传递给拖出方的onDragEnd
                    event.setResult(DragResult.DRAG_SUCCESSFUL);
                  });
                })
              // [End set_on_drop_call]
            }
          }
          .width('100%')
          .height('100%')
        }
        .height('100%')
      }
      
      // [StartExclude default_drag]
      .width('100%')
      .height('100%')
      .padding({ left: 12, right: 12 })
    }
    .backgroundColor('#f1f2f3')
    // 请将$r('app.string.Drag_DefaultDrag_title')替换为实际资源文件，在本示例中该资源文件的value值为"通用拖拽"
    .title($r('app.string.Drag_DefaultDrag_title'))
  }

  // [EndExclude default_drag]
}

// [End default_drag]