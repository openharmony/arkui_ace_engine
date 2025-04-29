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
import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest'

export default async function qRCodeContentOpacityTest() {
  /*
   * QRCode组件 ContentOpacity属性
   * 找到画面id为qRCodeContentOpacity的QRCode组件
   * 找到画面文本为QRCodeContentOpacity的Button组件
   * 获取codeContentOpacity1的contentOpacity属性与期待值0.5比对
   * 点击button1，变更codeContentOpacity2的contentOpacity属性值为$r('app.float.qr_code_contentOpacity')
   * 获取codeContentOpacity1的contentOpacity属性与期待值$r('app.float.qr_code_contentOpacity')比对
   */
  defineTest('qRCodeContentOpacityTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('qRCodeContentOpacityTestDemo running')
    let driver: Tester = Tester.create()
    let qRCode: Component = await driver.findComponent(Matcher.create().id('qRCodeContentOpacity').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('QRCodeContentOpacity').enabled(true))
    let codeContentOpacity1: string = await qRCode.getInspectorInfo()
    assertEqual(JSON.parse(codeContentOpacity1).$attrs.opacity, 0.5)
    await button.tap()
    let codeContentOpacity2: string = await qRCode.getInspectorInfo()
    assertEqual(JSON.parse(codeContentOpacity2).$attrs.contentOpacity, $r('app.float.qr_code_contentOpacity'))
  }, 0)
}