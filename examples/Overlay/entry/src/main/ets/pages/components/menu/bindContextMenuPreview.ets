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

@Builder
export function bindContextMenuPreviewBuilder(name: string, param: Object) {
  bindContextMenuPreviewExample()
}

// 菜单预览图
@Builder
export function PreviewBuilder() {
  Image($r('app.media.app_icon'))
    .width(200)
    .height(120)
}

@Entry
@Component
struct bindContextMenuPreviewExample {
  pathStack: NavPathStack = new NavPathStack()
  private iconStr: Resource = $r('app.media.app_icon');
  @State widthArray: Array<Length | undefined> = [
    10000, 900, 800, 700, 600, 500, 400, 300, 200, 100, '50%', '80%', '100%', '1000%'
  ];
  @State heightArray: Array<Length | undefined> = [
    100, 200, 300, 400, 500, 600, 700, 800, 900, 10000, '100%', '80%', '50%', '1000%'
  ];
  @State previewScaleModeArray: Array<PreviewScaleMode | undefined> = [
    PreviewScaleMode.AUTO,
    PreviewScaleMode.CONSTANT,
    PreviewScaleMode.MAINTAIN,
    undefined
  ];
  @State previewScaleModeArrayStr: Array<string> = [
    'PreviewScaleMode.AUTO',
    'PreviewScaleMode.CONSTANT',
    'PreviewScaleMode.MAINTAIN',
    'undefined'
  ];
  @State arrayIndex: number = 0;
  @State previewScaleModeArrayIndex: number = 0;

  @Builder
  MyMenu1() {
    Menu() {
      MenuItem({ startIcon: this.iconStr, content: '菜单选项' })
      MenuItem({ content: '菜单选项' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项' })
      MenuItem({ content: '菜单选项' })
    }
  }

  @Builder
  MyPreview() {
    Row()
      .width(this.widthArray[this.arrayIndex])
      .height(this.heightArray[this.arrayIndex])
      .backgroundColor(Color.Pink)
  }

  build() {
    NavDestination() {
      Column() {
        Button('点击切换预览图宽高: width = ' + this.widthArray[this.arrayIndex] + 'height = ' +
        this.heightArray[this.arrayIndex])
          .onClick(() => {
            if (this.arrayIndex < this.widthArray.length - 1) {
              this.arrayIndex++
            } else {
              this.arrayIndex = 0
            }
          })
        Button('点击切换预览图缩放模式:' + this.previewScaleModeArrayStr[this.previewScaleModeArrayIndex])
          .onClick(() => {
            if (this.previewScaleModeArrayIndex < this.previewScaleModeArray.length - 1) {
              this.previewScaleModeArrayIndex++
            } else {
              this.previewScaleModeArrayIndex = 0
            }
          })

        Blank()
          .height(100)
        Button('bindContextMenu百分比缩放为SAFE_AREA')
          .bindContextMenu(this.MyMenu1(), ResponseType.LongPress, {
            preview: this.MyPreview(),
            previewScaleMode: this.previewScaleModeArray[this.previewScaleModeArrayIndex],
            availableLayoutArea: AvailableLayoutArea.SAFE_AREA,
          })
          .onClick(() => {
          })
        Button('bindContextMenu百分比缩放为undefined')
          .bindContextMenu(this.MyMenu1(), ResponseType.LongPress, {
            preview: this.MyPreview(),
            previewScaleMode: this.previewScaleModeArray[this.previewScaleModeArrayIndex],
            availableLayoutArea: undefined
          })
          .onClick(() => {
          })
        Button('bindContextMenu啥也没设置')
          .bindContextMenu(this.MyMenu1(), ResponseType.LongPress, {
            preview: this.MyPreview(),
          })
          .onClick(() => {
          })
      }
      .height('100%')
      .width('100%')
    }
    .title('bindContextMenuPreview')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}