import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium'
import { abilityDelegatorRegistry, Component, Driver, ON } from '@kit.TestKit';

import {
  buttonClick,
  JsonType,
  KeyStruct,
  radioClick,
  Slide,
  sliderDrag,
  ToggleClick,
  scroll,
  Search,
  searchParentBlock,
  searchRadio,
  titleSearch,
  searchToggle,
  getToggle
} from '../../utils/index';
import { On, Point } from '@ohos.UiTest';


/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();


export default function RowSplitBootcampTest() {
  describe('RowSplitBootcampTest', () => {
    // Defines a test suite. Two parameters are supported: test suite name and test suite function.
    beforeAll(async (done: Function) => {

      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(1500);

        let atomDisplays: Component = await driver.findComponent(ON.text('栅格与分栏'));
        await atomDisplays.click();
        await driver.delayMs(1000);

        let scrollSearch: Component = await driver.findComponent(ON.text('横向分割容器/RowSplit'))
        await scrollSearch.click()
        await driver.delayMs(1000);

        let Buttons: Component[] = await driver.findComponents(ON.type('Button'));
        await Buttons[1].click()
        await driver.delayMs(1000);

      } catch (err) {

        console.info(`beforeAll error: ${JSON.stringify(err)}`);

      }
      console.info(`beforeAll end`);
      done();
      // Presets an action, which is performed only once before all test cases of the test suite start.
      // This API supports only one parameter: preset action function.
    })
    beforeEach(() => {
      // Presets an action, which is performed before each unit test case starts.
      // The number of execution times is the same as the number of test cases defined by **it**.
      // This API supports only one parameter: preset action function.
    })
    afterEach(() => {
      // Presets a clear action, which is performed after each unit test case ends.
      // The number of execution times is the same as the number of test cases defined by **it**.
      // This API supports only one parameter: clear action function.
    })
    afterAll(() => {
      // Presets a clear action, which is performed after all test cases of the test suite end.
      // This API supports only one parameter: clear action function.
    })
    it('ArkUI_RowSplit_0001', 0, async (done: Function) => {
      await titleSearch('参数列表', 'resizeable');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'resizeable'
        },
        id: 'RowSplit',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('resizeable', JsonType.value)
        ],
        assertEqual: 'true'
      })
      done();
    })
    it('ArkUI_RowSplit_0002', 0, async (done: Function) => {
      await titleSearch('参数列表', 'resizeable');
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'resizeable'
        },
        id: 'RowSplit',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('resizeable', JsonType.value)
        ],
        assertEqual: 'false'
      })
      done();
    })
  })
}