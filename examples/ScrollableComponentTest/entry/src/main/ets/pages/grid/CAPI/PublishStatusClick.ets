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

/*
 * Description: Grid组件高频接口CAPI补齐
 * Writer: renxiaowen
 */

import { BusinessError, commonEventManager } from '@kit.BasicServicesKit';

@Component
export struct StatusClickComponent {
  build() {
    Button('publicClick').onClick(() => {
      // 发布公共事件
      try {
        commonEventManager.publish('usual.event.STATUSBAR_CLICKED', (err: BusinessError) => {
          if (err) {
            console.error(`wangyu publish failed, code is ${err.code}, message is ${err.message}`);
          } else {
            console.info('wangyu publish success');
          }
        });
      } catch (error) {
        let err: BusinessError = error as BusinessError;
        console.error(`publish failed, code is ${err.code}, message is ${err.message}`);
      }
    }).width(100).height(50).margin(10)
  }
}