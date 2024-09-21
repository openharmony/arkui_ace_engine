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
import { assertEqual, assertFalse } from '@ohos.arkui.componentTest';
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function textDataDetectorConfigTest() {
  /*
   * Text组件 DataDetectorConfig属性
   * 找到画面id为textDataDetectorConfig1的Text组件
   * 找到画面文本为TextDataDetectorConfig1的Button组件
   * 获取text1的DataDetectorConfig属性DataDetectorConfig.type与期待值[TextDataDetectorType.PHONE_NUMBER]比对
   * 获取text1的DataDetectorConfig属性DataDetectorConfig.onDetectResultUpdate与期待值(result: string) => {}比对
   * 点击button1，变更text1的DataDetectorConfig属性DataDetectorConfig.type值为[TextDataDetectorType.URL]
   * 获取text1的DataDetectorConfig属性DataDetectorConfig.type与期待值[TextDataDetectorType.URL]比对
   * 点击button1，变更text1的DataDetectorConfig属性DataDetectorConfig.type值为[TextDataDetectorType.EMAIL]
   * 获取text1的DataDetectorConfig属性DataDetectorConfig.type与期待值[TextDataDetectorType.EMAIL]比对
   * 点击button1，变更text1的DataDetectorConfig属性DataDetectorConfig.type值为[TextDataDetectorType.ADDRESS]
   * 获取text1的DataDetectorConfig属性DataDetectorConfig.type与期待值[TextDataDetectorType.ADDRESS]比对
   */
  defineTest('textDataDetectorConfigTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textDataDetectorConfigTestDemo running")
    let driver: Tester = Tester.create()
    let text1: Component = await driver.findComponent(Matcher.create().id('textDataDetectorConfig1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('TextDataDetectorConfig1').enabled(true))

    let dataDetectorConfig1: string = await text1.getInspectorInfo()
    assertFalse(JSON.parse(dataDetectorConfig1).$attrs.dataDetectorConfig.types == undefined)
    assertEqual(JSON.parse(dataDetectorConfig1).$attrs.dataDetectorConfig.types, [TextDataDetectorType.PHONE_NUMBER])
    assertEqual(JSON.parse(dataDetectorConfig1).$attrs.dataDetectorConfig.onDetectResultUpdate, (result: string) => {
    })

    await button1.tap()
    let dataDetectorConfig3: string = await text1.getInspectorInfo()
    assertEqual(JSON.parse(dataDetectorConfig3).$attrs.dataDetectorConfig.types, [TextDataDetectorType.URL])
    await button1.tap()
    assertEqual(JSON.parse(dataDetectorConfig3).$attrs.dataDetectorConfig.types, [TextDataDetectorType.EMAIL])
    await button1.tap()
    assertEqual(JSON.parse(dataDetectorConfig3).$attrs.dataDetectorConfig.types, [TextDataDetectorType.ADDRESS])
  }, 0)
}