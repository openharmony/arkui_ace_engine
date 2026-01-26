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

import { TestRunner } from '../../lib/testRunner'
import { PageController } from '../../lib/pageController'
import { getStateMgmtInfoTests } from '../../common_tests/getStateMgmtInfoTests'
import router from '@system.router'

const json: string = '{"groupId":"7578","userId":null,"comment_group_id":7577,"isCommonRequest":true}';
const nestedJson: string = '{"a":{"b":{"groupId":"888"}}}';
const childJson: string = '{"groupId":"123"}';
const arrayJson: string = '{"a":[{"b":3}, {"c":4}]}';
const objectJson: string =  '{"a":{"1":{"c":2}}}';
interface Node {
    next?: Node;
}
let a: Node = {};
let b: Node = {};
a.next = b;
b.next = a;

@Entry
@Component
struct Parent {

  // This is used in tests. Do not remove.
  // Add more UI elements if your test needs
  @State finalResult: string = "Pending";

  @State val: Object | null = JSON.parse(json);
  @State nestedVal: Object | null = JSON.parse(nestedJson);
  @State childVal: Object | null = JSON.parse(childJson);
  @State rootVal: string = '321';
  @State undefinedVal: undefined = undefined;
  @State circularVal: Node = a;
  @State arrayVal: Object | null = JSON.parse(arrayJson);
  @State objectVal: Object | null = JSON.parse(objectJson);
  regularVar: Object | null = JSON.parse(json);

  aboutToAppear() {
    setTimeout(() => {
      TestRunner.bind(this)(new getStateMgmtInfoTests('V1_getStateMgmtInfo'));
      router.back();
      PageController.notifyPageFinished();
    }, 100)
  }

  build() {
    Column({ space: 10 }) {
      Text(`V1 Testing. Status: ${this.finalResult}`).fontSize(30)
      Child()
      Child({childVar: this.val})
      Child({childVar: this.nestedVal})
      Child({childVar: this.childVal})
    }
  }
}

@Component
struct Child {
  @Prop childVar: Object | null = null;

  build() {
  }
}