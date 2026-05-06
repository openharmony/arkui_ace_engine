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

import entry from 'libentry.so';
import * as entryNs from 'libentry.so';
import { router } from '@kit.ArkUI';

interface RequireNapiGlobal {
  requireNapi?: (moduleName: string) => Object
}

interface PickerNapiModule {
  pickerTest?: (id: string) => void
}

@Entry
@Component
struct CapiInterfaceTest {
  @State statusText: string = '等待 XComponent 加载...';
  private hasInvoked: boolean = false;

  aboutToAppear(): void {
    this.statusText = '页面已加载，等待 XComponent onAppear...';
  }

  private runNativePickerTest(): void {
    if (this.hasInvoked) {
      return;
    }
    this.hasInvoked = true;
    this.statusText = '开始调用 CAPI 创建 UIPickerComponent...';

    const xComponentId = 'pickerCapiXComponent';
    try {
      // 优先使用直接导入的 so 导出方法
      const entryObj = entry as PickerNapiModule;
      if (typeof entryObj.pickerTest === 'function') {
        entryObj.pickerTest(xComponentId);
        this.statusText = 'CAPI 调用成功：已创建 Picker 测试节点';
        return;
      }

      // 回退到 namespace 方式，兼容不同导入解析路径
      const entryNsObj = entryNs as PickerNapiModule;
      if (typeof entryNsObj.pickerTest === 'function') {
        entryNsObj.pickerTest(xComponentId);
        this.statusText = 'CAPI 调用成功：已创建 Picker 测试节点';
        return;
      }

      // 最后尝试 requireNapi
      const globalObj = globalThis as RequireNapiGlobal;
      if (typeof globalObj.requireNapi === 'function') {
        const moduleObj = globalObj.requireNapi('entry') as PickerNapiModule;
        if (typeof moduleObj.pickerTest === 'function') {
          moduleObj.pickerTest(xComponentId);
          this.statusText = 'CAPI 调用成功：已创建 Picker 测试节点';
          return;
        }
      }

      this.statusText = 'CAPI 调用失败：未找到 pickerTest 导出';
    } catch (error) {
      const message = (error as Error).message;
      this.statusText = 'CAPI 调用异常: ' + (message ? message : JSON.stringify(error));
    }
  }

  build() {
    Column({ space: 10 }) {
      Row({ space: 12 }) {
        Button('返回首页')
          .onClick(() => {
            router.back();
          })
        Text('CAPI 接口测试')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
      }
      .width('100%')
      .margin({ top: 8 })

      Text('通过 CAPI 创建 Picker 并测试 displayedItemCount/itemHeight')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')

      Text(this.statusText)
        .fontSize(12)
        .fontColor('#999999')
        .width('100%')

      XComponent({
        id: 'pickerCapiXComponent',
        type: XComponentType.NODE,
        libraryname: 'entry'
      })
        .onAppear(() => {
          this.runNativePickerTest();
        })
        .width('100%')
        .layoutWeight(1)
        .backgroundColor('#FFFFFF')
    }
    .padding({ left: 12, right: 12, bottom: 12 })
    .backgroundColor('#F5F5F5')
    .height('100%')
    .width('100%')
  }
}
