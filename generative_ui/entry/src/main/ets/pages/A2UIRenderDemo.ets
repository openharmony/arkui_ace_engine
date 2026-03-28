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

import { A2UIRenderComponent, SurfaceController, Catalog, CatalogItem, SurfaceEventType, SurfaceEventCallback,
  SurfaceErrorType } from 'a2ui_library'
import { DemoUtils } from './DemoUtils';
import { common } from '@kit.AbilityKit';
import { router } from '@kit.ArkUI';

@Entry
@Component
struct A2UIRenderDemo {
  private surfaceEventCallback: SurfaceEventCallback = (eventType: SurfaceEventType, controller: SurfaceController)=>{

  }

  @State fileName : string = "mock_data.json"
  @State hasError: boolean = false
  @State errorMsg: string = ''
  private myCatalog = Catalog.basic();
  private mySurfaceController = new SurfaceController(this.myCatalog, this.surfaceEventCallback)

  aboutToAppear(): void {
    this.mySurfaceController.registerErrorCallback((code: SurfaceErrorType, errorMsg: string)=>{
      this.hasError = true;
      this.errorMsg = errorMsg;
    })
  }

  private handleMockData() {
    console.log('handleMockData: src/main/resources/rawfile/mock_data.json');
    let mockData: string[] = DemoUtils.loadMockData(this.getUIContext().getHostContext() as common.Context, this.fileName);
    console.log(`handleMockData: ${mockData.length} start`)
    let time: number = 0
    for (const record of mockData) {
      if (record == null || record == undefined) {
        console.log(`HandleLocalDebugClick record: is invalid： ${time} `)
        return
      }

      setTimeout(() => {
        this.mySurfaceController.onReceive(record)
      }, time);

      time += 1000;
    }
  }

  build() {
    Column() {
      // 顶部导航栏
      Row() {
        Button('返回')
          .onClick(() => {
            router.back();
          })
          .margin({ left: 10 })

        Text('A2UI 渲染演示页面')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .layoutWeight(1)
          .textAlign(TextAlign.Center)
          .margin({ right: 50 })
      }
      .width('100%')
      .height(50)
      .backgroundColor('#f1f3f5')
      .padding(10)

      // 内容区域
      Column() {
        Button('点击获取测试数据')
          .onClick(()=>{
            this.handleMockData()
          })
          .margin({ top: 20 })

        if (this.hasError) {
          Text('Error: ' + this.errorMsg)
            .fontSize(16)
            .fontColor(Color.Red)
            .margin({ top: 20 })
        } else {
          Divider().strokeWidth(20).backgroundColor(Color.Red)
          A2UIRenderComponent({surfaceControllerBound: this.mySurfaceController})
          Divider().strokeWidth(20).backgroundColor(Color.Blue)
        }
      }
      .layoutWeight(1)
      .width('100%')
    }
    .height('100%')
    .width('100%')
  }
}
