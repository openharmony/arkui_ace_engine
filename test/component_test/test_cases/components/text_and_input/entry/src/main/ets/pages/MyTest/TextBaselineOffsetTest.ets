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
import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest';

export default async function textBaselineOffsetTest() {
  /*
   * Text组件 BaselineOffset属性
   * 找到画面id为textBaselineOffset1的Text组件
   * 找到画面文本为TextBaselineOffset的Button组件
   * 获取text的BaselineOffset属性与期待值10比对
   * 点击button，变更text的BaselineOffset属性值为'100px'
   * 获取text的BaselineOffset属性与期待值'100px'比对
   */
  defineTest('textBaselineOffsetTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textBaselineOffsetTestDemo running")
    let driver: Tester = Tester.create()
    let text: Component = await driver.findComponent(Matcher.create().id('textBaselineOffset1').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextBaselineOffset').enabled(true))

    let baselineOffset1: string = await text.getInspectorInfo()
    assertEqual(JSON.parse(baselineOffset1).$attrs.baselineOffset, '10')

    await button.tap()
    let baselineOffset2: string = await text.getInspectorInfo()
    assertEqual(JSON.parse(baselineOffset2).$attrs.baselineOffset, '100')
  }, 0)
}