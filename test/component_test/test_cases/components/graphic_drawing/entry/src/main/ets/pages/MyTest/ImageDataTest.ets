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
  assertContain,
  assertEqual,
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest';

export default async function imageDataTest() {
  /*
   * imageData组件 width\height属性
   * 找到画面id为imageData的imageData组件
   * 获取imageData的width\height属性与期待值判断是否为真
   */
  defineTest('imageDataTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("imageDataTestDemo running")
    let driver: Tester = Tester.create()
    let imageData: Component = await driver.findComponent(Matcher.create().id('imageData').enabled(true))

    let imageData1: string = await imageData.getInspectorInfo()
    assertTrue(false)

  }, 0)
}