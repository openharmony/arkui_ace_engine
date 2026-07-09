'use static';

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
import { LocalStorage, State } from '@ohos.arkui.stateManagement';
import { NodeContent } from '@ohos.arkui.node';
import { Button, Color, Column, ColumnOptions, Component, ContentSlot, Entry, Text, FontWeight } from '@ohos.arkui.component';
import window from '@ohos.window';

export class NativeMethods {
  static {
    loadLibrary("entry")
  }
  static native createSingleNode(content: NodeContent): void;
  static native createMultiNode(content: NodeContent): void;
  static native destroyNativeNode(content: NodeContent): void;
}

const msg_tag = '[accessibilityCapi]';

@Entry
@Component
struct Index {
  @State message: string = 'AccessibilityCapi';
  @State loadNativeFailed: boolean = false;
  @State isMultiInstance: boolean = false;
  private nodeContent: NodeContent = new NodeContent();
  private storage: LocalStorage | undefined = this.getUIContext().getSharedLocalStorage();
  private mainWindow: window.Window | undefined = this.storage?.get<window.Window>('mainWindow');

  aboutToAppear(): void {
    console.info(`${msg_tag}: aboutToAppear called`);
    try {
      NativeMethods.createSingleNode(this.nodeContent as NodeContent);
      console.info(`${msg_tag}: createSingleNode succeeded`);
    } catch (err) {
      this.loadNativeFailed = true;
      console.error(`${msg_tag}: createNativeNode failed: ${JSON.stringify(err)}`);
      console.error(`${msg_tag}: error name=${(err as Error).name}, message=${(err as Error).message}`);
      console.error(`${msg_tag}: error stack=${(err as Error).stack}`);
    }
  }

  aboutToDisappear(): void {
    try {
      NativeMethods.destroyNativeNode(this.nodeContent as NodeContent);
    } catch (err) {
      console.error(`${msg_tag}: destroyNativeNode failed: ${JSON.stringify(err)}`);
    }
  }

  build(): void {
    Column({ space: 10 } as ColumnOptions) {
      Text(this.message)
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Black)
      if (this.loadNativeFailed) {
        Text('Native node load failed')
          .fontSize(14)
          .fontColor(Color.Red)
      } else {
        Text('Native render (libentry.so)')
          .fontSize(14)
          .fontColor('#999999')
      }
      Button('SubWindow')
        .width(200)
        .height(48)
        .fontSize(16)
        .onClick(() => {
          try {
            this.mainWindow?.createSubWindowWithOptions('Modal',
              { title: 'SubWindow', decorEnabled: true, isModal: true })
          } catch (err) {
            console.error(`${msg_tag} code: ${err.code}, message: ${err.message}`);
          }
        })
      Button('XComponent单实例/多实例切换')
        .width(200)
        .height(48)
        .fontSize(16)
        .onClick(() => {
          if (this.loadNativeFailed) {
            console.error(`${msg_tag}: native library not loaded, cannot switch`);
            return;
          }
          try {
            NativeMethods.destroyNativeNode(this.nodeContent as NodeContent);
            this.isMultiInstance = !this.isMultiInstance;
            console.info(`${msg_tag}: current XComponent multiInstance is ${this.isMultiInstance}`);
            if (this.isMultiInstance) {
              NativeMethods.createMultiNode(this.nodeContent as NodeContent);
            } else {
              NativeMethods.createSingleNode(this.nodeContent as NodeContent);
            }
          } catch (err) {
            console.error(`${msg_tag}: switch failed: ${JSON.stringify(err)}`);
          }
        })
      Column() {
        ContentSlot(this.nodeContent);
      }
      .width('100%')
      .height(300)
      .backgroundColor('#f0f0f0')
    }
    .width('100%')
    .height('100%')
    .padding(16)
    .backgroundColor('#ffffff')
  }
}
