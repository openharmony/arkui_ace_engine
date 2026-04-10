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

import { router } from '@kit.ArkUI';
import { common } from '@kit.AbilityKit';
import { util } from '@kit.ArkTS';
import { DemoUtils } from './DemoUtils';
import { A2UIRenderComponent, SurfaceController, Catalog, CatalogItem, SurfaceEventType, SurfaceEventCallback,
  SurfaceErrorType } from 'a2ui_library';

interface CreateSurfaceInfo {
  surfaceId: string;
  catalogId: string;
}

interface DeleteSurfaceInfo {
  surfaceId: string;
}

interface A2UIMessage {
  version: string;
  createSurface?: CreateSurfaceInfo;
  deleteSurface?: DeleteSurfaceInfo;
}

@Entry
@Component
struct JSONDetail {
  @State fileName: string = '';
  @State isLoading: boolean = true;
  @State errorMsg: string = '';
  private surfaceId: string = '';
  private surfaceEventCallback: SurfaceEventCallback = (eventType: SurfaceEventType, controller: SurfaceController)=>{

  }
  private myCatalog = Catalog.basic();
  private mySurfaceController = new SurfaceController(this.myCatalog, this.surfaceEventCallback)
  private context: common.Context = this.getUIContext().getHostContext() as common.Context;

  aboutToAppear(): void {
    this.mySurfaceController.registerErrorCallback((code: SurfaceErrorType, errorMsg: string)=>{
      this.errorMsg = errorMsg;
      this.isLoading = false;
    })
    const params = router.getParams() as Record<string, Object>;
    if (params && params.fileName) {
      this.fileName = params.fileName as string;
      this.loadJsonContent(this.fileName);
    } else {
      this.errorMsg = '未接收到文件路径参数';
      this.isLoading = false;
    }
  }

  private loadJsonContent(filePath: string): void {
    try {
      let mockData: string[] = DemoUtils.loadMockData(this.context, filePath);
      console.log(`loadJsonContent: ${mockData.length} messages`)
      if (mockData.length > 0) {
        try {
          const firstMessage: A2UIMessage = JSON.parse(mockData[0]) as A2UIMessage;
          if (firstMessage.createSurface && firstMessage.createSurface.surfaceId) {
            this.surfaceId = firstMessage.createSurface.surfaceId;
            console.log(`Extracted surfaceId: ${this.surfaceId}`);
          }
        } catch (e) {
          console.warn('Failed to parse surfaceId from first message:', e);
        }
      }
      let time: number = 0
      for (const record of mockData) {
        if (record == null || record == undefined) {
          console.log(`loadJsonContent record: is invalid： ${time} `)
          return
        }

        setTimeout(() => {
          this.mySurfaceController.onReceive(record)
        }, time);

        time += 1000;
      }
      this.isLoading = false;
    } catch (error) {
      console.error('加载JSON文件失败:', error);
      this.errorMsg = '加载失败: ' + error;
      this.isLoading = false;
    }
  }

  private handleBack(): void {
    if (this.surfaceId) {
      const deleteSurfaceInfo: DeleteSurfaceInfo = {
        surfaceId: this.surfaceId
      };
      const deleteSurfaceMessage: A2UIMessage = {
        version: 'v0.9',
        deleteSurface: deleteSurfaceInfo
      };
      console.log(`Deleting surface: ${this.surfaceId}`);
      this.mySurfaceController.onReceive(JSON.stringify(deleteSurfaceMessage));
    }
    router.back();
  }

  build() {
    Column() {
      Row() {
        Button('← 返回')
          .onClick(() => {
            this.handleBack();
          })
          .margin({ left: 10, right: 10 })

        Text(this.fileName || 'JSON详情')
          .fontSize(16)
          .layoutWeight(1)
          .maxLines(1)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
      }
      .width('100%')
      .height(50)
      .backgroundColor('#f1f3f5')
      .padding(10)

      if (this.isLoading) {
        Column() {
          Text('加载中...')
            .fontSize(16)
            .fontColor(Color.Gray)
        }
        .layoutWeight(1)
        .width('100%')
        .justifyContent(FlexAlign.Center)
      } else if (this.errorMsg) {
        Text('Error: ' + this.errorMsg)
          .fontSize(16)
          .fontColor(Color.Red)
          .margin({ top: 20 })
      } else {
        A2UIRenderComponent({surfaceControllerBound: this.mySurfaceController})
      }
    }
    .height('100%')
    .width('100%')
  }
}
