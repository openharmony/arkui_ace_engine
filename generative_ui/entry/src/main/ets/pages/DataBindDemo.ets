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
struct DataBindDemo {
  private surfaceEventCallback: SurfaceEventCallback = (eventType: SurfaceEventType, controller: SurfaceController)=>{

  }

  @State hasError: boolean = false
  @State errorMsg: string = ''
  @State fileName : string = "data_bind_and_update.json"
  @State testData: string[] = []
  @State currentStep: number = 0

  private myCatalog = Catalog.basic();
  private mySurfaceController = new SurfaceController(this.myCatalog, this.surfaceEventCallback)

  aboutToAppear(): void {
    // 页面初始化时加载测试数据
    this.testData = DemoUtils.loadMockData(
      this.getUIContext().getHostContext() as common.Context,
      this.fileName
    );
    console.log(`DataBindDemo: Loaded ${this.testData.length} test records`);

    this.mySurfaceController.registerErrorCallback((code: SurfaceErrorType, errorMsg: string)=>{
      this.hasError = true;
      this.errorMsg = errorMsg;
    })
  }

  // 测试场景说明
  private getTestDescription(): string {
    return `数据绑定与更新测试

本页面测试A2UI的数据绑定和数据更新功能。

测试数据文件: data_bind_and_update.json
共包含 ${this.testData.length} 条测试记录：

【测试场景】
1. 创建Surface (createSurface)
   - 创建一个名为"main"的Surface

2. 更新组件 - 数据绑定 (updateComponents)
   - 创建带数据绑定的Text组件
   - 使用 {"path":"/contact/colleague/email"} 绑定数据

3. 更新组件 - 添加更多组件 (updateComponents)
   - 添加更多Text组件到界面

4. 更新数据模型 - 整体更新 (updateDataModel)
   - 一次性更新整个数据模型
   - 包含contact/family和contact/colleague的完整数据

5. 更新数据模型 - 更新特定字段 (updateDataModel)
   - 使用path指定更新 /contact/colleague/email
   - 验证数据绑定自动更新

6. 更新数据模型 - 删除特定字段 (updateDataModel)
   - 使用path删除 /contact/family/phone
   - 验证删除后UI自动隐藏或显示默认值`;
  }

  // 场景1: 创建Surface
  private createSurface() {
    if (this.testData.length > 0) {
      console.log('Step 1: Create Surface');
      this.currentStep = 1;
      this.mySurfaceController.onReceive(this.testData[0]);
    }
  }

  // 场景2: 更新组件（带数据绑定）
  private updateComponentsWithDataBinding() {
    if (this.testData.length > 1) {
      console.log('Step 2: Update Components with Data Binding');
      this.currentStep = 2;
      this.mySurfaceController.onReceive(this.testData[1]);
    }
  }

  // 场景3: 更新组件（添加更多组件）
  private updateComponentsAddMore() {
    if (this.testData.length > 2) {
      console.log('Step 3: Update Components - Add More');
      this.currentStep = 3;
      this.mySurfaceController.onReceive(this.testData[2]);
    }
  }

  // 场景4: 更新数据模型（整体更新）
  private updateDataModelFull() {
    if (this.testData.length > 3) {
      console.log('Step 4: Update Data Model - Full Update');
      this.currentStep = 4;
      this.mySurfaceController.onReceive(this.testData[3]);
    }
  }

  // 场景5: 更新数据模型（特定字段）
  private updateDataModelSpecificField() {
    if (this.testData.length > 4) {
      console.log('Step 5: Update Data Model - Specific Field');
      this.currentStep = 5;
      this.mySurfaceController.onReceive(this.testData[4]);
    }
  }

  // 场景6: 更新数据模型（删除字段）
  private updateDataModelDeleteField() {
    if (this.testData.length > 5) {
      console.log('Step 6: Update Data Model - Delete Field');
      this.currentStep = 6;
      this.mySurfaceController.onReceive(this.testData[5]);
    }
  }

  // 自动执行所有测试步骤
  private runAllTests() {
    console.log('Running all tests automatically');
    this.currentStep = 0;

    let delay = 0;
    for (let i = 0; i < this.testData.length; i++) {
      setTimeout(() => {
        this.currentStep = i + 1;
        console.log(`Auto Step ${i + 1}: ${this.getStepName(i)}`);
        this.mySurfaceController.onReceive(this.testData[i]);
      }, delay);
      delay += 1500; // 每步间隔1.5秒
    }
  }

  // 重置测试
  private resetTest() {
    console.log('Reset test');
    this.currentStep = 0;
    this.hasError = false;
    this.errorMsg = '';
  }

  private getStepName(index: number): string {
    const names = [
      'Create Surface',
      'Update Components (Data Binding)',
      'Update Components (Add More)',
      'Update Data Model (Full)',
      'Update Data Model (Specific Field)',
      'Update Data Model (Delete Field)'
    ];
    return names[index] || `Step ${index + 1}`;
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

        Text('A2UI 数据绑定与更新测试')
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

      // 当前步骤提示
      if (this.currentStep > 0) {
        Text(`当前步骤: ${this.currentStep}/6 - ${this.getStepName(this.currentStep - 1)}`)
          .fontSize(14)
          .fontColor('#0066cc')
          .fontWeight(FontWeight.Medium)
          .padding(10)
          .backgroundColor('#e6f2ff')
          .margin({ left: 10, right: 10, top: 5 })
      }

      Scroll() {
        Column() {
          // 自动执行所有测试按钮
          Button('▶ 自动执行所有测试')
            .width('90%')
            .height(45)
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .backgroundColor('#4CAF50')
            .margin({ top: 10, bottom: 10 })
            .onClick(() => {
              this.runAllTests();
            })

          // 分步骤测试按钮
          Text('--- 分步骤测试 ---')
            .fontSize(14)
            .fontColor('#666666')
            .margin({ top: 10, bottom: 5 })

          Row({ space: 10 }) {
            Button('1. 创建Surface')
              .fontSize(12)
              .backgroundColor('#FF6B9D')
              .enabled(this.currentStep === 0 || this.currentStep === 1)
              .onClick(() => {
                this.createSurface();
              })

            Button('2. 发送组件消息')
              .fontSize(12)
              .backgroundColor('#9C27B0')
              .enabled(this.currentStep >= 1)
              .onClick(() => {
                this.updateComponentsWithDataBinding();
              })
          }
          .width('90%')
          .justifyContent(FlexAlign.SpaceEvenly)
          .margin({ bottom: 10 })

          Row({ space: 10 }) {
            Button('3. 发送组件消息')
              .fontSize(12)
              .backgroundColor('#3F51B5')
              .enabled(this.currentStep >= 2)
              .onClick(() => {
                this.updateComponentsAddMore();
              })

            Button('4. 整体更新数据')
              .fontSize(12)
              .backgroundColor('#2196F3')
              .enabled(this.currentStep >= 3)
              .onClick(() => {
                this.updateDataModelFull();
              })
          }
          .width('90%')
          .justifyContent(FlexAlign.SpaceEvenly)
          .margin({ bottom: 10 })

          Row({ space: 10 }) {
            Button('5. 更新特定字段')
              .fontSize(12)
              .backgroundColor('#009688')
              .enabled(this.currentStep >= 4)
              .onClick(() => {
                this.updateDataModelSpecificField();
              })

            Button('6. 删除字段')
              .fontSize(12)
              .backgroundColor('#FF9800')
              .enabled(this.currentStep >= 5)
              .onClick(() => {
                this.updateDataModelDeleteField();
              })
          }
          .width('90%')
          .justifyContent(FlexAlign.SpaceEvenly)
          .margin({ bottom: 10 })

          // 重置按钮
          Button('⟲ 重置测试')
            .width('90%')
            .height(40)
            .fontSize(14)
            .backgroundColor('#757575')
            .margin({ top: 5, bottom: 10 })
            .onClick(() => {
              this.resetTest();
            })

          // 渲染区域
          if (this.hasError) {
            Column() {
              Text('❌ 发生错误')
                .fontSize(18)
                .fontColor(Color.Red)
                .fontWeight(FontWeight.Bold)
                .margin({ bottom: 10 })

              Text(this.errorMsg)
                .fontSize(14)
                .fontColor(Color.Red)
                .padding(10)
                .backgroundColor('#ffebee')
                .borderRadius(5)
            }
            .width('90%')
            .margin({ top: 20 })
          } else {
            Column() {
              Text('--- A2UI 渲染区域 ---')
                .fontSize(14)
                .fontColor('#666666')
                .margin({ bottom: 10 })

              Divider().strokeWidth(2).backgroundColor('#FF5722')
              A2UIRenderComponent({ surfaceControllerBound: this.mySurfaceController })
                .width('100%')
                .height(250)
              Divider().strokeWidth(2).backgroundColor('#2196F3')
            }
            .width('90%')
            .margin({ top: 20 })
          }
        }
        .width('100%')
      }
      .layoutWeight(1)
      .width('100%')
    }
    .height('100%')
    .width('100%')
    .backgroundColor('#ffffff')
  }
}
