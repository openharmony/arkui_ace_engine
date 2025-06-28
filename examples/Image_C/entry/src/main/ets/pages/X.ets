/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

@Entry
@Component
struct PreviewArea {
  @State surfaceId : string ='';
  controller = new XComponentController();
  build() {
    Column() {
      Text(this.surfaceId)
      XComponent({
        id: 'xcomponent',
        type: 'texture',
        controller: this.controller
      })
      .onLoad(() => {
        this.controller.setXComponentSurfaceSize({surfaceWidth:100,surfaceHeight:50});
        this.surfaceId = this.controller.getXComponentSurfaceId();
        console.log('fffff', this.surfaceId);
      }).backgroundColor(Color.Blue)
    }
    .margin({
      top: 27,
      left: 12,
      right: 12
    })
    .height('40%')
    .width('90%')
  }
}