/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
//测试代码路径
import navigatorParamsTest from '../MyTest/NavigatorParamsTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest';

interface NameObject {
  name: string;
}

class TextObject {
  text: NameObject;

  constructor(text: NameObject) {
    this.text = text;
  }
}

@Entry
@Component
struct NavigatorParamsSample {
  @State name: NameObject = { name: 'NavigatorParamDetail' }

  aboutToAppear(): void {
    loadComponentTestEntry(navigatorParamsTest);
  }

  build() {
    Column() {
      Navigator({ target: 'pages/MyTest/NavigatorParamsDetail' }) {
        Text('Go to NavigatorParamDetail')
          .width('100%')
      }
      .type(NavigationType.Push)
      .params(new TextObject(this.name))
      .id('navigatorParams')
    }
  }
}