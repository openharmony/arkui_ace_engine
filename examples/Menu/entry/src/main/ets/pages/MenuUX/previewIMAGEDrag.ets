/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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

import UDC from '@ohos.data.unifiedDataChannel';
import UTD from '@ohos.data.uniformTypeDescriptor';
@Entry
@Component
struct previewIMAGE3 {
  @State select: boolean = true
  @State imgState: Visibility = Visibility.Visible;

  @Builder MenuBuilder(){
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项1'})
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项2'})
        .enabled(false)
      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '菜单选项3'
      })
    }
  }

  build() {
    Column() {
      Text('MenuPreviewMode.IMAGE 拖拽').margin({ top:10,bottom:30 })
      Text('LongPress to show menu')
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .draggable(true)
        .onDragStart((event)=>{
          let text: UDC.PlainText = new UDC.PlainText;
          let data: UDC.UnifiedData = new UDC.UnifiedData(text);
          (event as DragEvent).setData(data);
          console.log('ets:in start')
        })
        .bindContextMenu(this.MenuBuilder, ResponseType.LongPress, {
          preview: MenuPreviewMode.IMAGE
        })
    }
    .width('100%')
    .height('100%')
  }
}