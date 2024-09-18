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

import {
  assertEqual,
  assertFalse,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest';
import UTD from '@ohos.data.uniformTypeDescriptor';

export default async function allowDropTest() {
  /*
  * list组件 allowDrop属性
  * 找到画面id为listAllowDrop1，listAllowDrop2的list组件
  * 获取listAllowDrop1的allowDrop属性与期待值[UTD.UniformDataType.TEXT]比对
  * 获取listAllowDrop2的allowDrop属性与期待值[UTD.UniformDataType.IMAGE]比对
  */
  defineTest('allowDropTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("allowDropTestDemo running")
    let driver: Tester = Tester.create()
    let listAllowDrop1: Component = await driver.findComponent(Matcher.create().id('listAllowDrop1').enabled(true))
    let listAllowDrop2: Component = await driver.findComponent(Matcher.create().id('listAllowDrop2').enabled(true))
    let allowDrop1: string = await listAllowDrop1.getInspectorInfo()
    let allowDrop2: string = await listAllowDrop2.getInspectorInfo()
    assertFalse(JSON.parse(allowDrop1).$attrs.allowDrop == undefined)
    assertEqual(JSON.parse(allowDrop1).$attrs.allowDrop, [UTD.UniformDataType.TEXT])
    assertEqual(JSON.parse(allowDrop2).$attrs.allowDrop, [UTD.UniformDataType.IMAGE])
  }, 0)
}