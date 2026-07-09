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
import { Entry, Component, Column, ContentSlot } from '@ohos.arkui.component';
import { NodeContent } from '@ohos.arkui.node';

export class NativeMethods {
  static { loadLibrary("entry") }
  static native CreateNativeAccessibilityNodeDialogSubWindow(nodeContent: NodeContent): void;
}

@Entry
@Component
struct PageCustomDialogSubWindow {
  private nodeContent: NodeContent = new NodeContent();
  aboutToAppear(): void {
    try {
      NativeMethods.CreateNativeAccessibilityNodeDialogSubWindow(this.nodeContent);
    } catch (err) {
      console.error(`[PageCustomDialogSubWindow] failed: ${(err as Error).message}`);
    }
  }
  build(): void {
    Column() {
      ContentSlot(this.nodeContent)
    }
    .width('100%')
    .height('100%')
  }
}
