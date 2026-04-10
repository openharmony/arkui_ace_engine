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
  SurfaceController,
  Catalog,
  SurfaceEventCallback,
  SurfaceEventType,
  SurfaceErrorType
} from 'a2ui_library';
import { router } from '@kit.ArkUI';

@Entry
@Component
export struct MultiRenderComponentDemo {
  // Controller 1 和相关状态
  private surfaceEventCallback1: SurfaceEventCallback = (
    eventType: SurfaceEventType,
    controller: SurfaceController
  ) => {
    console.log(`MultiRenderComponentDemo: Controller1 event - type: ${JSON.stringify(eventType)}`);
  };

  @State catalog1: Catalog = Catalog.basic();
  @State controller1: SurfaceController | null = null;
  @State controller1Created: boolean = false;
  @State controller1MessagesReceived: boolean = false;
  @State controller1Bound: boolean = false;
  @State render1Visible: boolean = false;

  // 测试数据
  private createSurfaceJson1: string =
    '{"version":"v0.9","createSurface":{"surfaceId":"testSurface1","catalogId":"https://a2ui.org/specification/v0_9/standard_catalog.json"}}';
  private updateComponentsJson1: string =
    '{"version":"v0.9","updateComponents":{"surfaceId":"testSurface1","components":[{"id":"root","component":"Column","children":["title1"]},{"id":"title1","component":"Text","text":"RenderComponent 1 - 先创建后绑定","fontSize":20,"fontColor":"#FF6B9D","textAlign":"center"}]}}';
  private updateDataModelJson1: string =
    '{"version":"v0.9","updateDataModel":{"surfaceId":"testSurface1","value":{"title":"Updated Data 1"}}}';

  // Controller 2 和相关状态
  private surfaceEventCallback2: SurfaceEventCallback = (
    eventType: SurfaceEventType,
    controller: SurfaceController
  ) => {
    console.log(`MultiRenderComponentDemo: Controller2 event - type: ${JSON.stringify(eventType)}`);
  };

  @State catalog2: Catalog = Catalog.basic();
  @State controller2: SurfaceController | null = null;
  @State controller2Created: boolean = false;
  @State controller2MessagesReceived: boolean = false;
  @State controller2Bound: boolean = false;
  @State render2Visible: boolean = true;
  @State render3Visible: boolean = false;

  // 测试数据
  private createSurfaceJson2: string =
    '{"version":"v0.9","createSurface":{"surfaceId":"testSurface2","catalogId":"https://a2ui.org/specification/v0_9/standard_catalog.json"}}';
  private updateComponentsJson2: string =
    '{"version":"v0.9","updateComponents":{"surfaceId":"testSurface2","components":[{"id":"root","component":"Column","children":["title2"]},{"id":"title2","component":"Text","text":"RenderComponent 2 - 先绑定后创建","fontSize":20,"fontColor":"#4CAF50","textAlign":"center"}]}}';
  private updateDataModelJson2: string =
    '{"version":"v0.9","updateDataModel":{"surfaceId":"testSurface2","value":{"title":"Updated Data 2"}}}';

  // 测试场景说明
  private getTestDescription(): string {
    return `多RenderComponent测试

本页面测试一个页面同时显示多个A2UIRenderComponent的场景。

【测试场景】
1. RenderComponent 1（先创建后绑定）
   - 步骤1: 创建Controller1
   - 步骤2: 接收消息（创建Surface、更新组件、数据更新）
   - 步骤3: 将A2UIRenderComponent与Controller1绑定显示

2. RenderComponent 2（先绑定后创建）
   - 步骤1: 创建Controller2
   - 步骤2: 先将A2UIRenderComponent与Controller2绑定
   - 步骤3: 接收消息（创建Surface、更新组件、数据更新）

3. RenderComponent 3（动态替换）
   - 步骤1: 销毁RenderComponent 2
   - 步骤2: 创建新的RenderComponent 3
   - 步骤3: 将Controller2与新组件绑定

【测试要点】
- 验证多个Controller可以独立工作
- 验证绑定时机灵活性（先创建后绑定 vs 先绑定后创建）
- 验证RenderComponent可以动态销毁和重建
- 验证Controller重用性（Controller2可绑定到不同组件）`;
  }

  // ========== Controller1 操作 ==========
  private createController1() {
    if (!this.controller1Created) {
      this.controller1 = new SurfaceController(this.catalog1, this.surfaceEventCallback1);
      this.controller1Created = true;
      console.log('MultiRenderComponentDemo: Controller1 created');
    }
  }

  private receiveMessages1() {
    if (this.controller1 && this.controller1Created) {
      this.controller1.onReceive(this.createSurfaceJson1);
      setTimeout(() => {
        if (this.controller1) {
          this.controller1.onReceive(this.updateComponentsJson1);
        }
      }, 100);
      setTimeout(() => {
        if (this.controller1) {
          this.controller1.onReceive(this.updateDataModelJson1);
        }
      }, 200);
      this.controller1MessagesReceived = true;
      console.log('MultiRenderComponentDemo: Controller1 messages received');
    }
  }

  private bindController1() {
    if (this.controller1) {
      this.controller1Bound = true;
      this.render1Visible = true;
      console.log('MultiRenderComponentDemo: Controller1 bound to render component');
    }
  }

  // ========== Controller2 操作 ==========
  private createController2() {
    if (!this.controller2Created) {
      this.controller2 = new SurfaceController(this.catalog2, this.surfaceEventCallback2);
      this.controller2Created = true;
      console.log('MultiRenderComponentDemo: Controller2 created');
    }
  }

  private bindController2() {
    if (this.controller2) {
      this.controller2Bound = true;
      console.log('MultiRenderComponentDemo: Controller2 bound to render component');
    }
  }

  private receiveMessages2() {
    if (this.controller2 && this.controller2Created && this.controller2Bound) {
      this.controller2.onReceive(this.createSurfaceJson2);
      setTimeout(() => {
        if (this.controller2) {
          this.controller2.onReceive(this.updateComponentsJson2);
        }
      }, 100);
      setTimeout(() => {
        if (this.controller2) {
          this.controller2.onReceive(this.updateDataModelJson2);
        }
      }, 200);
      this.controller2MessagesReceived = true;
      console.log('MultiRenderComponentDemo: Controller2 messages received');
    }
  }

  // ========== RenderComponent 3 操作 ==========
  private destroyRender2AndCreateRender3() {
    this.render2Visible = false;
    this.render3Visible = true;
    console.log('MultiRenderComponentDemo: Destroyed RenderComponent 2, created RenderComponent 3');
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

        Text('多 RenderComponent 测试')
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
        .height(180)
        .backgroundColor('#f5f5f5')
        .border({ width: 1, color: '#e0e0e0' })
        .margin(10)
      }
      .width('100%')

      Scroll() {
        Column({ space: 20 }) {
          // ========== RenderComponent 1 区域 ==========
          Column({ space: 10 }) {
            Text('--- RenderComponent 1: 先创建后绑定 ---')
              .fontSize(16)
              .fontWeight(FontWeight.Bold)
              .fontColor('#FF6B9D')
              .margin({ top: 10 })

            Row({ space: 10 }) {
              Button('1.创建Controller1')
                .fontSize(12)
                .backgroundColor('#FF6B9D')
                .enabled(!this.controller1Created)
                .onClick(() => {
                  this.createController1();
                })

              Button('2.接收消息')
                .fontSize(12)
                .backgroundColor('#FF6B9D')
                .enabled(this.controller1Created && !this.controller1MessagesReceived)
                .onClick(() => {
                  this.receiveMessages1();
                })

              Button('3.绑定显示')
                .fontSize(12)
                .backgroundColor('#FF6B9D')
                .enabled(this.controller1Created && this.controller1MessagesReceived && !this.controller1Bound)
                .onClick(() => {
                  this.bindController1();
                })
            }
            .width('100%')
            .justifyContent(FlexAlign.SpaceEvenly)
            .margin({ bottom: 10 })

            if (this.render1Visible && this.controller1Bound && this.controller1) {
              Column() {
                Text('Controller1 绑定的渲染区域')
                  .fontSize(12)
                  .fontColor('#999999')
                  .margin({ bottom: 5 })
                Divider().strokeWidth(1).backgroundColor('#FF6B9D')
                A2UIRenderComponent({ surfaceControllerBound: this.controller1 })
                  .width('100%')
                  .height(100)
                Divider().strokeWidth(1).backgroundColor('#FF6B9D')
              }
              .width('90%')
            }
          }
          .width('90%')
          .padding(10)
          .backgroundColor('#fff5f8')
          .borderRadius(8)

          // ========== RenderComponent 2 区域 ==========
          Column({ space: 10 }) {
            Text('--- RenderComponent 2: 先绑定后创建 ---')
              .fontSize(16)
              .fontWeight(FontWeight.Bold)
              .fontColor('#4CAF50')
              .margin({ top: 10 })

            Row({ space: 10 }) {
              Button('1.创建Controller2')
                .fontSize(12)
                .backgroundColor('#4CAF50')
                .enabled(!this.controller2Created)
                .onClick(() => {
                  this.createController2();
                })

              Button('2.绑定显示')
                .fontSize(12)
                .backgroundColor('#4CAF50')
                .enabled(this.controller2Created && !this.controller2Bound && !this.render3Visible)
                .onClick(() => {
                  this.bindController2();
                })

              Button('3.接收消息')
                .fontSize(12)
                .backgroundColor('#4CAF50')
                .enabled(this.controller2Bound && !this.controller2MessagesReceived)
                .onClick(() => {
                  this.receiveMessages2();
                })
            }
            .width('100%')
            .justifyContent(FlexAlign.SpaceEvenly)
            .margin({ bottom: 10 })

            if (this.render2Visible && this.controller2Bound && this.controller2) {
              Column() {
                Text('Controller2 绑定的渲染区域（RenderComponent 2）')
                  .fontSize(12)
                  .fontColor('#999999')
                  .margin({ bottom: 5 })
                Divider().strokeWidth(1).backgroundColor('#4CAF50')
                A2UIRenderComponent({ surfaceControllerBound: this.controller2 })
                  .width('100%')
                  .height(100)
                Divider().strokeWidth(1).backgroundColor('#4CAF50')
              }
              .width('90%')
            }
          }
          .width('90%')
          .padding(10)
          .backgroundColor('#f1f8f4')
          .borderRadius(8)

          // ========== RenderComponent 3 区域 ==========
          Column({ space: 10 }) {
            Text('--- RenderComponent 3: 动态替换测试 ---')
              .fontSize(16)
              .fontWeight(FontWeight.Bold)
              .fontColor('#FF9800')
              .margin({ top: 10 })

            Button('销毁Render2并创建Render3')
              .fontSize(12)
              .backgroundColor('#FF9800')
              .enabled(this.render2Visible && this.controller2Bound)
              .onClick(() => {
                this.destroyRender2AndCreateRender3();
              })
              .margin({ bottom: 10 })

            if (this.render3Visible && this.controller2Bound && this.controller2) {
              Column() {
                Text('Controller2 重新绑定的渲染区域（RenderComponent 3）')
                  .fontSize(12)
                  .fontColor('#999999')
                  .margin({ bottom: 5 })
                Divider().strokeWidth(1).backgroundColor('#FF9800')
                A2UIRenderComponent({ surfaceControllerBound: this.controller2 })
                  .width('100%')
                  .height(100)
                Divider().strokeWidth(1).backgroundColor('#FF9800')
              }
              .width('90%')
            }
          }
          .width('90%')
          .padding(10)
          .backgroundColor('#fff8f1')
          .borderRadius(8)
          .margin({ bottom: 20 })
        }
        .width('100%')
      }
      .layoutWeight(1)
    }
    .height('100%')
    .width('100%')
    .backgroundColor('#ffffff')
  }
}
