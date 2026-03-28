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

import {
  A2UIRenderComponent,
  Catalog,
  SurfaceController,
  SurfaceEventCallback,
  SurfaceEventType
} from 'a2ui_library';
import { router } from '@kit.ArkUI';

@Entry
@Component
export struct MultiSurfaceDemo {
  // Surface 1: 主界面
  private createSurface1Json: string =
    '{"version":"v0.9","createSurface":{"surfaceId":"surface1","catalogId":"https://a2ui.org/specification/v0_9/standard_catalog.json"}}';
  private updateSurface1Json: string =
    '{"version":"v0.9","updateComponents":{"surfaceId":"surface1","components":[{"id":"root","component":"Column", "children":["title1"]},{"id":"title1","component":"Text","text":"Surface 1 - 主界面"}]}}';

  // Surface 2: 详情页
  private createSurface2Json: string =
    '{"version":"v0.9","createSurface":{"surfaceId":"surface2","catalogId":"https://a2ui.org/specification/v0_9/standard_catalog.json"}}';
  private updateSurface2Json: string =
    '{"version":"v0.9","updateComponents":{"surfaceId":"surface2","components":[{"id":"root","component":"Column","children":["title2"]},{"id":"title2","component":"Text","text":"Surface 2 - 详情页","fontSize":20,"fontColor":"#FFFFFF","textAlign":"center"}]}}';

  // Surface 3: 设置页
  private createSurface3Json: string =
    '{"version":"v0.9","createSurface":{"surfaceId":"surface3","catalogId":"https://a2ui.org/specification/v0_9/standard_catalog.json"}}';
  private updateSurface3Json: string =
    '{"version":"v0.9","updateComponents":{"surfaceId":"surface3","components":[{"id":"root","component":"Column","children":["title3"]},{"id":"title3","component":"Text","text":"Surface 3 - 设置页","fontSize":20,"fontColor":"#FFFFFF","textAlign":"center"}]}}';

  // 删除 Surface 的 JSON
  private deleteSurface1Json: string =
    '{"version":"v0.9","deleteSurface":{"surfaceId":"surface1"}}';
  private deleteSurface2Json: string =
    '{"version":"v0.9","deleteSurface":{"surfaceId":"surface2"}}';
  private deleteSurface3Json: string =
    '{"version":"v0.9","deleteSurface":{"surfaceId":"surface3"}}';

  private surfaceEventCallback: SurfaceEventCallback = (
    eventType: SurfaceEventType,
    controller: SurfaceController
  ) => {
    console.log(`MultiSurfaceDemo: Surface event - type: ${JSON.stringify(eventType)}`);
  }

  @State catalog: Catalog = Catalog.basic();
  @State surfaceController: SurfaceController =
    new SurfaceController(this.catalog, this.surfaceEventCallback);

  @State currentSurface: string = 'surface1';
  @State showSwitchButtons: boolean = false;

  // 测试场景说明
  private getTestDescription(): string {
    return `多Surface管理测试

本页面测试一个SurfaceController管理多个Surface的功能。

【核心功能】
1. 多Surface管理
   - 一个SurfaceController可以同时管理多个Surface
   - 每个Surface有唯一的surfaceId标识

2. 自动显示切换
   - 最新创建的Surface自动获得显示权
   - 通过contentHandle自动管理显示优先级

3. 返回（Back）功能
   - 支持返回到上一个Surface
   - 自动销毁当前Surface并显示前一个
   - 类似导航栈的后退功能

4. Surface删除
   - 可以删除指定的Surface
   - 删除后自动调整显示权

【测试场景】
- 创建顺序示例：Surface1 → Surface2 → Surface3
- 当前显示：Surface3（最新创建）
- 执行Back：删除Surface3，显示Surface2
- 再执行Back：删除Surface2，显示Surface1`;
  }

  build() {
    Column() {
      // 顶部导航栏
      Row() {
        Button('返回')
          .fontWeight(FontWeight.Medium)
          .backgroundColor('#ff70c6d2')
          .onClick(() => {
            router.back();
          })
          .margin({ left: 10 })

        Text('多 Surface 管理演示')
          .fontSize(18)
          .fontWeight(FontWeight.Bold)
          .layoutWeight(1)
          .textAlign(TextAlign.Center)
          .margin({ right: 50 })
      }
      .width('100%')
      .height(50)
      .backgroundColor('#f1f3f5')
      .padding(10)

      // 测试说明区域
      Column() {
        Scroll() {
          Text(this.getTestDescription())
            .fontSize(13)
            .fontColor('#333333')
            .lineHeight(20)
            .padding(10)
            .width('100%')
        }
        .width('100%')
        .height(160)
        .backgroundColor('#f5f5f5')
        .border({ width: 1, color: '#e0e0e0' })
        .margin(10)
      }
      .width('100%')

      // 当前显示提示
      Row() {
        Text(`当前显示: ${this.currentSurface}`)
          .fontSize(14)
          .fontColor('#0066cc')
          .fontWeight(FontWeight.Medium)
        Blank()
        Text('最新创建的 Surface 会自动获得显示权')
          .fontSize(12)
          .fontColor('#999999')
      }
      .width('100%')
      .padding({ left: 20, right: 20 })
      .margin({ left: 10, right: 10, top: 5 })
      .backgroundColor('#e6f2ff')
      .borderRadius(5)

      // Surface 显示区域
      Scroll() {
        Column() {
          // Surface 渲染区域
          Column() {
            Text('--- A2UI 渲染区域 ---')
              .fontSize(14)
              .fontColor('#666666')
              .margin({ bottom: 10 })

            Divider().strokeWidth(2).backgroundColor('#FF5722')
            A2UIRenderComponent({ surfaceControllerBound: this.surfaceController })
              .width('100%')
              .height(100)
            Divider().strokeWidth(2).backgroundColor('#2196F3')
          }
          .width('90%')
          .margin({ top: 10, bottom: 20 })

          // 控制按钮区域
          Column({ space: 15 }) {
            // 创建 Surface 按钮
            Text('创建 Surface')
              .fontSize(18)
              .fontWeight(FontWeight.Medium)
              .margin({ top: 10 })

            Row({ space: 10 }) {
              Button('创建Surface1')
                .backgroundColor('#FF6B9D')
                .fontSize(12)
                .onClick(() => {
                  this.surfaceController.onReceive(this.createSurface1Json);
                  setTimeout(() => {
                    this.surfaceController.onReceive(this.updateSurface1Json);
                  }, 100);
                  this.currentSurface = this.surfaceController.getLatestSurfaceId();
                  this.showSwitchButtons = true;
                })

              Button('创建Surface2')
                .backgroundColor('#4CAF50')
                .fontSize(12)
                .onClick(() => {
                  this.surfaceController.onReceive(this.createSurface2Json);
                  this.currentSurface = this.surfaceController.getLatestSurfaceId();
                  this.showSwitchButtons = true;
                  setTimeout(() => {
                    this.surfaceController.onReceive(this.updateSurface2Json);
                  }, 100);
                })

              Button('创建Surface3')
                .backgroundColor('#FF9800')
                .fontSize(12)
                .onClick(() => {
                  this.surfaceController.onReceive(this.createSurface3Json);
                  this.currentSurface = this.surfaceController.getLatestSurfaceId();
                  this.showSwitchButtons = true;
                  setTimeout(() => {
                    this.surfaceController.onReceive(this.updateSurface3Json);
                  }, 100);
                })
            }
            .width('100%')
            .justifyContent(FlexAlign.SpaceEvenly)

            // 切换 Surface 按钮
            if (this.showSwitchButtons) {
              Column({ space: 10 }) {
                Text('切换 Surface (仅支持back返回)')
                  .fontSize(18)
                  .fontWeight(FontWeight.Medium)
                  .margin({ top: 10 })

                Row({ space: 10 }) {
                  Button('返回 Surface')
                    .fontWeight(FontWeight.Medium)
                    .backgroundColor('#ff70c6d2')
                    .fontSize(12)
                    .onClick(() => {
                      this.surfaceController.back();
                      this.currentSurface = this.surfaceController.getLatestSurfaceId();
                    })
                }
                .width('100%')
                .justifyContent(FlexAlign.SpaceEvenly)
              }
            }

            // 删除 Surface 按钮
            if (this.showSwitchButtons) {
              Column({ space: 10 }) {
                Text('删除Surface')
                  .fontSize(18)
                  .fontWeight(FontWeight.Medium)
                  .margin({ top: 10 })

                Row({ space: 10 }) {
                  Button('删除Surface 1')
                    .backgroundColor('#FF0000')
                    .fontSize(12)
                    .onClick(() => {
                      this.surfaceController.onReceive(this.deleteSurface1Json);
                      this.currentSurface = this.surfaceController.getLatestSurfaceId();
                    })

                  Button('删除Surface 2')
                    .backgroundColor('#FF0000')
                    .fontSize(12)
                    .onClick(() => {
                      this.surfaceController.onReceive(this.deleteSurface2Json);
                      this.currentSurface = this.surfaceController.getLatestSurfaceId();
                    })

                  Button('删除Surface 3')
                    .backgroundColor('#FF0000')
                    .fontSize(12)
                    .onClick(() => {
                      this.surfaceController.onReceive(this.deleteSurface3Json);
                      this.currentSurface = this.surfaceController.getLatestSurfaceId();
                    })
                }
                .width('100%')
                .justifyContent(FlexAlign.SpaceEvenly)
              }
            }
          }
          .width('90%')
        }
        .width('100%')
      }
      .layoutWeight(1)
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#ffffff')
  }
}
