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

import { assertEqual, assertContain, assertFalse, assertTrue } from '@ohos.arkui.componentTest';
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function matrix2DTranslateYTest() {
  /*
   * Matrix2D组件 TranslateY属性
   * 找到画面文本为Matrix2DTranslateY的Button组件
   * 点击button，变更TranslateY属性值
   * 断言是否为真
   */
  defineTest('matrix2DTranslateYTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("matrix2DTranslateYTestDemo running")
    let driver: Tester = Tester.create()
    let button: Component = await driver.findComponent(Matcher.create().text('Matrix2DTranslateY').enabled(true))
    await button.tap()
    assertTrue(false)

  }, 0)
}