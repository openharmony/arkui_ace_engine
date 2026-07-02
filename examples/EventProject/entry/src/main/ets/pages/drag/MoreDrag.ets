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

// [Start more_drag]
import { KeyCode } from '@kit.InputKit';
import { image } from '@kit.ImageKit';

@Entry
@Component
export struct MoreDrag {
  @State pixmap: image.PixelMap | undefined = undefined;
  @State numbers: number[] = [];
  @State isSelectedGrid: boolean[] = [];
  @State previewData: DragItemInfo[] = [];
  @State colors: Color[] =
    [Color.Red, Color.Blue, Color.Brown, Color.Gray, Color.Green, Color.Grey, Color.Orange, Color.Pink, Color.Yellow];
  @State numberBadge: number = 0;

  @Styles
  normalStyles(): void {
    .opacity(1.0);
  }

  @Styles
  selectStyles(): void {
    .opacity(0.4);
  }

  onPageShow(): void {
    let i: number = 0;
    for (i = 0; i < 100; i++) {
      this.numbers.push(i);
      this.isSelectedGrid.push(false);
      this.previewData.push({});
    }
  }

  @Builder
  RandomBuilder(idx: number) {
    Column()
      .backgroundColor(this.colors[idx % 9])
      .width(50)
      .height(50)
      .opacity(1.0)
  }

  build() {
    NavDestination() {
      Column({ space: 12 }) {

        Column({ space: 5 }) {
          // [Start create_grid_item_module]
          Grid() {
            ForEach(this.numbers, (idx: number) => {
              GridItem() {
                Column()
                  .backgroundColor(this.colors[idx % 9])
                  .width(50)
                  .height(50)
                  .opacity(1.0)
                  .id('grid' + idx)
              }
              // [StartExclude create_grid_item_module]
              .dragPreview(this.previewData[idx])
              .selectable(true)
              .selected(this.isSelectedGrid[idx])
              // 设置多选显示效果
              .stateStyles({
                normal: this.normalStyles,
                selected: this.selectStyles
              })
              // [Start grid_item_module_selected_true]
              .onClick(() => {
                this.isSelectedGrid[idx] = !this.isSelectedGrid[idx];
                // [StartExclude grid_item_module_selected_true]
                if (this.isSelectedGrid[idx]) {
                  this.numberBadge++;
                  let gridItemName = 'grid' + idx;
                  // 选中状态下提前调用componentSnapshot中的get接口获取pixmap
                  this.getUIContext()
                    .getComponentSnapshot()
                    .get(gridItemName, (error: Error, pixmap: image.PixelMap) => {
                      this.pixmap = pixmap;
                      this.previewData[idx] = {
                        pixelMap: this.pixmap
                      };
                    });
                } else {
                  this.numberBadge--;
                }
                // [EndExclude grid_item_module_selected_true]
              })
              // [End grid_item_module_selected_true]
              // 使能多选拖拽，右上角数量角标需要应用设置numberBadge参数
              // [EndExclude create_grid_item_module]
              // [Start drag_preview_options]
              .dragPreviewOptions({ numberBadge: this.numberBadge },
                { isMultiSelectionEnabled: true, defaultAnimationBeforeLifting: true })
              // [End drag_preview_options]
              .onDragStart(() => {
              })
            }, (idx: string) => idx)
          }
          // [End create_grid_item_module]
          .columnsTemplate('1fr 1fr 1fr 1fr 1fr')
          .columnsGap(5)
          .rowsGap(10)
          .backgroundColor(0xFAEEE0)
        }.width('100%').margin({ top: 5 })

      }
      .width('100%')
      .height('100%')
      .padding({ left: 12, right: 12 })
    }
    .backgroundColor('#f1f2f3')
    // 请将$r('app.string.Drag_MoreDrag_title')替换为实际资源文件，在本示例中该资源文件的value值为"多选拖拽"
    .title($r('app.string.Drag_MoreDrag_title'))
  }
}
// [End more_drag]