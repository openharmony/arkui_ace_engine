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
import { assertTrue, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest'

export default async function gaugeDescriptionTest() {
  /*
   * Gauge组件 Description属性
   * 找到画面id为gaugeDescription的Gauge组件
   * 获取gauge的Description属性与期待值'GaugeDescription'比对
   */
  defineTest('gaugeDescriptionTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('gaugeDescriptionTestDemo running')
    let driver: Tester = Tester.create()
    let text: Component = await driver.findComponent(Matcher.create().text('GaugeDescription').enabled(true))
    let description1: string = await text.getType()
    assertTrue(description1 == 'Text')
  }, 0)
}