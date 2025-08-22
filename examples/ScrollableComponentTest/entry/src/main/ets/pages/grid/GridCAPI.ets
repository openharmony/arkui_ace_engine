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

import nativeNode from 'libentry.so';
import { NodeContent } from '@kit.ArkUI';

@Entry
@Component
struct GridCAPI {
  // 初始化NodeContent对象。
  private rootSlot = new NodeContent();
  @State @Watch('changeNativeFlag') showNative: boolean = false;

  changeNativeFlag(): void {
    if (this.showNative) {
      // 传递NodeContent对象用于Native创建组件的挂载显示
      nativeNode.createNativeRoot(this.rootSlot);
    } else {
      // 销毁NativeModule组件
      nativeNode.destroyNativeRoot();
    }
  }

  build() {
    Column() {
      Button(this.showNative ? 'HideNativeUI' : 'ShowNativeUI').onClick(() => {
        this.showNative = !this.showNative;
      })
      Row() {
        // 将NodeContent和ContentSlot占位组件绑定。
        ContentSlot(this.rootSlot)
      }.layoutWeight(1)
    }
    .width('100%')
    .height('100%')
  }
}