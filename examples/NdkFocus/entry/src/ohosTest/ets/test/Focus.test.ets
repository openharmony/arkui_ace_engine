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

import { hilog } from '@kit.PerformanceAnalysisKit';
import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium';
import { abilityDelegatorRegistry, BY, Driver, ON } from '@kit.TestKit';
import { UIAbility, Want } from '@kit.AbilityKit';
import nativeNode from 'libnativeNode.so';

const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator();
const bundleName = abilityDelegatorRegistry.getArguments().bundleName;
let want: Want;

interface optionsObj {
  url: string
}

export default function FocusInterfaceTest() {
  describe('FocusInterfaceTest', () => {

    beforeAll(async () => {
      want = {
        bundleName: bundleName,
        abilityName: 'EntryAbility'
      };
      await delegator.startAbility(want);
      let driver = Driver.create();
      await driver.delayMs(2000);
      const ability: UIAbility = await delegator.getCurrentTopAbility();
      console.info('get top ability');
      expect(ability.context.abilityInfo.name).assertEqual('EntryAbility');
    })

    beforeEach(async () => {
    })

    afterEach(() => {
      hilog.info(0x0000, 'FocusTest', 'Focus interface test case completed');
    })

    afterAll(() => {
      hilog.info(0x0000, 'FocusTest', 'All focus interface tests completed');
    })

    /**
     * @tc.number FocusInterface_001
     * @tc.name test DefaultFocus
     * @tc.desc 测试默认焦点接口 - 验证ButtonDefault在XComponent创建后是否获得默认焦点
     */
    it('testDefaultFocus', 0, async (done: Function) => {
      hilog.info(0x0000, 'FocusTest', 'testDefaultFocus begin');
      let driver = Driver.create();
      await driver.delayMs(2000); // 等待XComponent和native节点创建完成
      try {
        const list = await driver.findComponent(ON.id('inner'));
        await list.scrollSearch(ON.id('ButtonDefault')); // 滚动到ButtonDefault
        await driver.delayMs(1500); // 等待滚动动画

        // 检查ButtonDefault是否已经获得默认焦点（应该是红色背景）
        let strJson = getInspectorByKey('ButtonDefault');
        let obj: ESObject = JSON.parse(strJson);
        hilog.info(0x0000, 'FocusTest', 'ButtonDefault backgroundColor: %{public}s', obj.$attrs.backgroundColor);

        strJson = getInspectorByKey('ButtonDefault');
        obj = JSON.parse(strJson);
        hilog.info(0x0000, 'FocusTest', 'ButtonDefault focus backgroundColor after activate: %{public}s', obj.$attrs.backgroundColor);
        expect(obj.$attrs.backgroundColor).assertEqual('#FFFF0000')
      } catch (error) {
        hilog.error(0x0000, 'FocusTest', 'testDefaultFocus failed: %{public}s', error.message);
        expect().assertFail();
      }

      hilog.info(0x0000, 'FocusTest', 'testDefaultFocus end');
      done();
    })

    /**
     * @tc.number FocusInterface_002
     * @tc.name testOH_ArkUI_FocusRequest
     * @tc.desc 测试OH_ArkUI_FocusRequest接口 - 测试请求焦点和focusable
     */
    it('testOH_ArkUI_FocusRequest_Normal', 0, async (done: Function) => {
      hilog.info(0x0000, 'FocusTest', 'testOH_ArkUI_FocusRequest_Normal begin');
      let driver = Driver.create();
      await driver.delayMs(1500);
      try {
        const list = await driver.findComponent(ON.id('inner'));
        await list.scrollSearch(ON.id('Button0')); // 滚动到Button0
        await driver.delayMs(500); // 等待滚动动画
        // 设置Button0不可获焦并请求Button0焦点
        let result: number = nativeNode.setNodeFocusable('Button0', false);
        expect(result).assertEqual(0);
        await driver.delayMs(1000);
        let result2: number = nativeNode.requestFocus('Button0');
        await driver.delayMs(1000);
        expect(result2).assertEqual(150001);
        hilog.info(0x0000, 'FocusTest', 'Button0 focus request result: %{public}d', result);

        // 焦点设置失败
        let strJson = getInspectorByKey('Button0');
        let obj: ESObject = JSON.parse(strJson);
        hilog.info(0x0000, 'FocusTest', 'node focus backgroundColor: %{public}s', obj.$attrs.backgroundColor);
        expect(obj.$attrs.backgroundColor).assertEqual('#F2F2F3F0')

        let result3: number = nativeNode.setNodeFocusable('Button0', true);
        expect(result3).assertEqual(0);
        let result4: number = nativeNode.requestFocus('Button0');
        await driver.delayMs(1000);
        expect(result4).assertEqual(0);
        hilog.info(0x0000, 'FocusTest', 'Button0 focus request result: %{public}d', result);

        // 焦点设置成功
        let strJson2 = getInspectorByKey('Button0');
        let obj2: ESObject = JSON.parse(strJson2);
        hilog.info(0x0000, 'FocusTest', 'node focus backgroundColor: %{public}s', obj.$attrs.backgroundColor);
        expect(obj2.$attrs.backgroundColor).assertEqual('#FFFF0000')

      } catch (error) {
        hilog.error(0x0000, 'FocusTest', 'testOH_ArkUI_FocusRequest_Normal failed: %{public}s', error.message);
        expect().assertFail();
      }

      hilog.info(0x0000, 'FocusTest', 'testOH_ArkUI_FocusRequest_Normal end');
      done();
    })

    /**
     * @tc.number FocusInterface_003
     * @tc.name testOH_ArkUI_FocusClear
     * @tc.desc 测试OH_ArkUI_FocusClear接口 - 异步请求和清除焦点
     */
    it('testOH_ArkUI_FocusClear', 0, async (done: Function) => {
      hilog.info(0x0000, 'FocusTest', 'testOH_ArkUI_FocusClear begin');
      let driver = Driver.create();
      await driver.delayMs(1500);
      try {
        const list = await driver.findComponent(ON.id('inner'));
        await list.scrollSearch(ON.id('Button1')); // 滚动到Button0
        await driver.delayMs(1000); // 等待滚动动画
        // 请求Button1焦点
        let result: number = nativeNode.requestFocusAsync('Button1');
        await driver.delayMs(1000);
        expect(result).assertEqual(0);
        hilog.info(0x0000, 'FocusTest', 'Button1 focus request result: %{public}d', result);
        let strJson = getInspectorByKey('Button1');
        let obj: ESObject = JSON.parse(strJson);
        hilog.info(0x0000, 'FocusTest', 'node focus backgroundColor: %{public}s', obj.$attrs.backgroundColor);
        expect(obj.$attrs.backgroundColor).assertEqual('#FFFF0000')

        nativeNode.clearFocus();
        await driver.delayMs(1000);
        let strJson2 = getInspectorByKey('Button1');
        let obj2: ESObject = JSON.parse(strJson2);
        hilog.info(0x0000, 'FocusTest', 'node blur backgroundColor: %{public}s', obj2.$attrs.backgroundColor);
        expect(obj2.$attrs.backgroundColor).assertEqual('#FF000000')

      } catch (error) {
        hilog.error(0x0000, 'FocusTest', 'testOH_ArkUI_FocusRequest_Normal failed: %{public}s', error.message);
        expect().assertFail();
      }

      hilog.info(0x0000, 'FocusTest', 'testOH_ArkUI_FocusClear end');
      done();
    })

    /**
     * @tc.number FocusInterface_004
     * @tc.name testFocusOnTouch
     * @tc.desc 测试FocusOnTouch接口 - Button2 and Button3
     */
    it('testFocusOnTouch', 0, async (done: Function) => {
      hilog.info(0x0000, 'FocusTest', 'testFocusOnTouch begin');
      let driver = Driver.create();
      await driver.delayMs(1500);
      try {
        const list = await driver.findComponent(ON.id('inner'));
        let result: number = nativeNode.setNodeFocusOnTouch('Button2', false);
        expect(result).assertEqual(0);
        await list.scrollSearch(ON.id('Button2')); // 滚动到Button2
        await driver.delayMs(2000); // 等待滚动动画
        let component = await driver.findComponent(ON.id('Button2'));
        await driver.delayMs(1000);
        await component.click();
        await driver.delayMs(1000);
        let strJson = getInspectorByKey('Button2');
        let obj: ESObject = JSON.parse(strJson);
        hilog.info(0x0000, 'FocusTest', 'Button2 backgroundColor: %{public}s', obj.$attrs.backgroundColor);
        expect(obj.$attrs.backgroundColor).assertEqual('#F2F2F3F0')

        let result2: number = nativeNode.setNodeFocusOnTouch('Button3', true);
        expect(result2).assertEqual(0);

        await list.scrollSearch(ON.id('Button3')); // 滚动到Button3
        await driver.delayMs(1500); // 等待滚动动画
        let component2 = await driver.findComponent(ON.id('Button3'));
        await driver.delayMs(1000);
        await component2.click();
        await driver.delayMs(1000);
        let strJson2 = getInspectorByKey('Button3');
        let obj2: ESObject = JSON.parse(strJson2);
        hilog.info(0x0000, 'FocusTest', 'Button3 focus backgroundColor: %{public}s', obj2.$attrs.backgroundColor);
        expect(obj2.$attrs.backgroundColor).assertEqual('#FFFF0000')
      } catch (error) {
        hilog.error(0x0000, 'FocusTest', 'testFocusOnTouch failed: %{public}s', error.message);
        expect().assertFail();
      }

      hilog.info(0x0000, 'FocusTest', 'testFocusOnTouch end');
      done();
    })

    /**
     * @tc.number FocusInterface_005
     * @tc.name test tabStop
     * @tc.desc 测试tabStop接口 - tabStop
     */
    it('testTabStop', 0, async (done: Function) => {
      hilog.info(0x0000, 'FocusTest', 'testTabStop begin');
      let driver = Driver.create();
      await driver.delayMs(1500);
      try {
        const list = await driver.findComponent(ON.id('inner'));
        await list.scrollSearch(ON.id('Button3')); // 滚动到Button3
        await driver.delayMs(1500); // 等待滚动动画
        let result: number = nativeNode.requestFocus('Button3');
        expect(result).assertEqual(0);
        await driver.delayMs(1000);
        let strJson = getInspectorByKey('Button3');
        let obj: ESObject = JSON.parse(strJson);
        hilog.info(0x0000, 'FocusTest', 'Button3 backgroundColor: %{public}s', obj.$attrs.backgroundColor);
        expect(obj.$attrs.backgroundColor).assertEqual('#FFFF0000');
        let result2: number = nativeNode.setNodeTabStop('Column4', true);
        expect(result2).assertEqual(0);
        await driver.triggerKey(2049);
        await driver.delayMs(1000);
        await driver.triggerKey(2049);
        await driver.delayMs(1000);
        strJson = getInspectorByKey('Button4');
        obj = JSON.parse(strJson);
        hilog.info(0x0000, 'FocusTest', 'Button3 backgroundColor: %{public}s', obj.$attrs.backgroundColor);
        expect(obj.$attrs.backgroundColor).assertEqual('#F2F2F3F0');
        await driver.triggerKey(2054);
        await driver.delayMs(1000);
        strJson = getInspectorByKey('Button4');
        obj = JSON.parse(strJson);
        hilog.info(0x0000, 'FocusTest', 'Button4 focus backgroundColor: %{public}s', obj.$attrs.backgroundColor);
        expect(obj.$attrs.backgroundColor).assertEqual('#FFFF0000')
      } catch (error) {
        hilog.error(0x0000, 'FocusTest', 'testTabStop failed: %{public}s', error.message);
        expect().assertFail();
      }

      hilog.info(0x0000, 'FocusTest', 'testTabStop end');
      done();
    })

    /**
     * @tc.number FocusInterface_006
     * @tc.name test nextFocus
     * @tc.desc 测试nextFocus接口 - nextFocus
     */
    it('testNextFocus', 0, async (done: Function) => {
      hilog.info(0x0000, 'FocusTest', 'testNextFocus begin');
      let driver = Driver.create();
      await driver.delayMs(1500);
      try {
        let result: number = nativeNode.requestFocus('Button5');
        expect(result).assertEqual(0);
        await driver.delayMs(1000);
        let strJson = getInspectorByKey('Button5');
        let obj: ESObject = JSON.parse(strJson);
        hilog.info(0x0000, 'FocusTest', 'Button5 backgroundColor: %{public}s', obj.$attrs.backgroundColor);
        expect(obj.$attrs.backgroundColor).assertEqual('#FFFF0000');
        let result2: number = nativeNode.setNodeNextFocus('Button5', 'Button7', 0);
        expect(result2).assertEqual(0);
        nativeNode.activateFocus(true, true);
        await driver.triggerKey(2049);
        await driver.delayMs(3000);
        strJson = getInspectorByKey('Button7');
        obj = JSON.parse(strJson);
        hilog.info(0x0000, 'FocusTest', 'Button7 backgroundColor: %{public}s', obj.$attrs.backgroundColor);
        expect(obj.$attrs.backgroundColor).assertEqual('#FFFF0000')
      } catch (error) {
        hilog.error(0x0000, 'FocusTest', 'testNextFocus failed: %{public}s', error.message);
        expect().assertFail();
      }

      hilog.info(0x0000, 'FocusTest', 'testNextFocus end');
      done();
    })

    /**
     * @tc.number FocusInterface_007
     * @tc.name test FocusBox
     * @tc.desc 测试FocusBox接口 - FocusBox
     */
    it('testFocusBox', 0, async (done: Function) => {
      hilog.info(0x0000, 'FocusTest', 'testFocusBox begin');
      let driver = Driver.create();
      await driver.delayMs(1500);
      try {
        let result: number = nativeNode.requestFocus('Button8');
        expect(result).assertEqual(0);
        await driver.delayMs(1500);
        let strJson = getInspectorByKey('Button8');
        let obj: ESObject = JSON.parse(strJson);
        hilog.info(0x0000, 'FocusTest', 'Button8 backgroundColor: %{public}s', obj.$attrs.backgroundColor);
        expect(obj.$attrs.backgroundColor).assertEqual('#FFFF0000');
        let result2: number = nativeNode.setNodeFocusBox('Button8', 5.0, 2.0, 0xFF00FF00);
        expect(result2).assertEqual(0);
        nativeNode.activateFocus(false, true);
        await driver.delayMs(1000);
        nativeNode.activateFocus(true, true);
        await driver.delayMs(1000);
        strJson = getInspectorByKey('Button8');
        obj = JSON.parse(strJson);
        hilog.info(0x0000, 'FocusTest', 'Button8 backgroundColor: %{public}s', obj.$attrs.backgroundColor);
        expect(obj.$attrs.backgroundColor).assertEqual('#FFFF0000')
      } catch (error) {
        hilog.error(0x0000, 'FocusTest', 'testFocusBox failed: %{public}s', error.message);
        expect().assertFail();
      }

      hilog.info(0x0000, 'FocusTest', 'testFocusBox end');
      done();
    })

    /**
     * @tc.number FocusInterface_008
     * @tc.name test OH_ArkUI_FocusSetAutoTransfer
     * @tc.desc 测试OH_ArkUI_FocusSetAutoTransfer接口 - 通过Button9点击创建menu测试页面层级变化时的焦点自动转移
     */
    it('testAutoTransfer', 0, async (done: Function) => {
      hilog.info(0x0000, 'FocusTest', 'testAutoTransfer begin');
      let driver = Driver.create();
      await driver.delayMs(1500);
      try {
        // 请求Button9焦点
        let result: number = nativeNode.requestFocus('Button9');
        expect(result).assertEqual(0);
        await driver.delayMs(1000);

        // 验证Button9获得焦点
        let strJson = getInspectorByKey('Button9');
        let obj: ESObject = JSON.parse(strJson);
        hilog.info(0x0000, 'FocusTest', 'Button9 backgroundColor: %{public}s', obj.$attrs.backgroundColor);
        expect(obj.$attrs.backgroundColor).assertEqual('#FFFF0000');

        // 测试禁用AutoTransfer的情况
        nativeNode.setAutoTransfer(false);
        await driver.delayMs(500);
        nativeNode.activateFocus(false, true);
        await driver.delayMs(1000);
        // 触发menu创建（测试新层级页面的焦点转移）
        let menuButton = await driver.findComponent(ON.id('menu'));
        await menuButton.click();
        await driver.delayMs(1000);

        hilog.info(0x0000, 'FocusTest', 'menu should be created for AutoTransfer test');
        strJson = getInspectorByKey('Button9');
        obj = JSON.parse(strJson);
        hilog.info(0x0000, 'FocusTest', 'Button9 backgroundColor: %{public}s', obj.$attrs.backgroundColor);
        expect(obj.$attrs.backgroundColor).assertEqual('#FFFF0000');
        hilog.info(0x0000, 'FocusTest', 'AutoTransfer re-enabled');

      } catch (error) {
        hilog.error(0x0000, 'FocusTest', 'testAutoTransfer failed: %{public}s', error.message);
        expect().assertFail();
      }

      hilog.info(0x0000, 'FocusTest', 'testAutoTransfer end');
      done();
    })
  })
}
