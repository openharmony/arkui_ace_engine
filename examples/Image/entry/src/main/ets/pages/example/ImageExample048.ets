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

import router from "@ohos.router"
import hilog from "@ohos.hilog"
import { common } from '@kit.AbilityKit'

@Entry
@Component
struct onCompleteTest {
  @State flag: boolean = true;

  build() {
    Row() {
      Column() {
        Image($r("app.media.startIcon"))
          .id("1") // 图片唯一标识
          .size(this.flag ? {width: 40, height: 40} : {width: '100%', height: '100%'})
          .objectFit(ImageFit.Fill) // 图片适配：拉伸填充容器
          .autoResize(true) // 允许图片自动调整尺寸
          .borderWidth(2)
          // 图片加载完成触发的事件
          .onComplete((event) => {
            console.log('AceImage 图片加载完成, width' + event?.componentWidth + ',' + event?.loadingStatus)
            // 执行2秒动画：修改flag切换图片尺寸
            animateTo({duration: 2000}, ()=>{
              console.info('AceImage animatedTo enter')
              this.flag = false // 切换为占满容器的尺寸
              console.info('AceImage animatedTo end')
            })
            console.log('AceImage onComplete end')
          })
      }.width('100%')
    }.height('100%')
  }
}