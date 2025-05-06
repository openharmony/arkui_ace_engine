import { describe, beforeAll, it } from '@ohos/hypium'
import { abilityDelegatorRegistry, Component, Driver, ON } from '@kit.TestKit';
import {
  buttonClick,
  getToggle,
  JsonType,
  KeyStruct,
  radioClick,
  Search,
  searchParentBlock,
  searchToggle,
  Slide,
  sliderDrag,
  titleSearch,
  ToggleClick
} from '../../utils';

const TAG = 'ToggleBootcamp'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function ToggleBootcampTest() {
  describe('ToggleBootcampTest', () => {

    beforeAll(async (done: Function) => {
      // Presets an action, which is performed only once before all test cases of the test suite start.
      // This API supports only one parameter: preset action function.
      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(5000);
        console.info(TAG + 'ToggleBootcamp' + ' begin');

        let atomDisplays: Component = await driver.findComponent(ON.text('按钮与选择'));
        await atomDisplays.click();
        await driver.delayMs(1000);

        let scrollSearch: Component = await driver.findComponent(ON.text('切换按钮/Toggle'))
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
    })

    // Toggle.type
    it('ArkUI_Toggle_001', 0, async (done: Function) => {

      await Search('参数列表', 'Toggle.type')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'Toggle.type'
        },
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('type', JsonType.value),
        ],
        assertEqual: 'ToggleType.Checkbox'
      })

      done();
    })

    it('ArkUI_Toggle_002', 0, async (done: Function) => {

      await Search('参数列表', 'Toggle.type')

      await radioClick({
        radioClickObj: 2,
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('type', JsonType.value),
        ],
        assertEqual: 'ToggleType.Button'
      })

      done();
    })

    it('ArkUI_Toggle_003', 0, async (done: Function) => {

      await Search('参数列表', 'Toggle.type')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'Toggle.type',
          toggleClickType: ToggleClick.Close,
        },
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('type', JsonType.value),
        ],
        assertEqual: 'ToggleType.Switch'
      })

      done();
    })

    // Toggle.isOn
    it('ArkUI_Toggle_004', 0, async (done: Function) => {

      await Search('参数列表', 'Toggle.isOn')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'Toggle.isOn'
        },
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('isOn', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();
    })

    it('ArkUI_Toggle_005', 0, async (done: Function) => {

      await Search('参数列表', 'Toggle.isOn')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'Toggle.isOn',
          toggleClickType: ToggleClick.Close,
        },
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('isOn', JsonType.value),
        ],
        assertEqual: 'false'
      })

      done();
    })

    // selectedColor
    it('ArkUI_Toggle_006', 0, async (done: Function) => {

      await Search('参数列表', 'selectedColor')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'selectedColor'
        },
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();
    })

    it('ArkUI_Toggle_007', 0, async (done: Function) => {

      await Search('参数列表', 'selectedColor')

      await buttonClick({
        buttonClickObj: 1,
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();
    })

    it('ArkUI_Toggle_008', 0, async (done: Function) => {

      await Search('参数列表', 'selectedColor')

      await buttonClick({
        buttonClickObj: 2,
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })

    it('ArkUI_Toggle_009', 0, async (done: Function) => {

      await Search('参数列表', 'selectedColor')

      await buttonClick({
        buttonClickObj: 3,
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();
    })

    it('ArkUI_Toggle_010', 0, async (done: Function) => {

      await Search('参数列表', 'selectedColor')

      await buttonClick({
        buttonClickObj: 4,
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();
    })

    it('ArkUI_Toggle_011', 0, async (done: Function) => {

      await Search('参数列表', 'selectedColor')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'selectedColor',
          toggleClickType: ToggleClick.Close,
        },
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();
    })

    // switchPointColor(无法获取属性值)
    it('ArkUI_Toggle_012', 0, async (done: Function) => {

      await Search('参数列表', 'switchPointColor')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'switchPointColor'
        },
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('switchPointColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();
    })

    it('ArkUI_Toggle_013', 0, async (done: Function) => {

      await Search('参数列表', 'switchPointColor')

      await buttonClick({
        buttonClickObj: 1,
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('switchPointColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();
    })

    it('ArkUI_Toggle_014', 0, async (done: Function) => {

      await Search('参数列表', 'switchPointColor')

      await buttonClick({
        buttonClickObj: 2,
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('switchPointColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();
    })

    it('ArkUI_Toggle_015', 0, async (done: Function) => {

      await Search('参数列表', 'switchPointColor')

      await buttonClick({
        buttonClickObj: 3,
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('switchPointColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();
    })

    it('ArkUI_Toggle_016', 0, async (done: Function) => {

      await Search('参数列表', 'switchPointColor')

      await buttonClick({
        buttonClickObj: 4,
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('switchPointColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();
    })

    it('ArkUI_Toggle_017', 0, async (done: Function) => {

      await Search('参数列表', 'switchPointColor')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('switchPointColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();
    })

    // switchStyle.pointRadius
    it('ArkUI_Toggle_018', 0, async (done: Function) => {

      await Search('参数列表', 'switchStyle.pointRadius')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'switchStyle.pointRadius'
        },
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pointRadius', JsonType.value),
        ],
        assertEqual: '20.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pointRadius', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();
    })

    // switchStyle.unselectedColor
    it('ArkUI_Toggle_019', 0, async (done: Function) => {

      await Search('参数列表', 'switchStyle.unselectedColor')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'switchStyle.unselectedColor'
        },
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('unselectedColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();
    })

    it('ArkUI_Toggle_020', 0, async (done: Function) => {

      await Search('参数列表', 'switchStyle.unselectedColor')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'switchStyle.unselectedColor'
        },
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('unselectedColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();
    })

    it('ArkUI_Toggle_021', 0, async (done: Function) => {

      await Search('参数列表', 'switchStyle.unselectedColor')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'switchStyle.unselectedColor'
        },
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('unselectedColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })

    it('ArkUI_Toggle_022', 0, async (done: Function) => {

      await Search('参数列表', 'switchStyle.unselectedColor')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'switchStyle.unselectedColor'
        },
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('unselectedColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();
    })

    it('ArkUI_Toggle_023', 0, async (done: Function) => {

      await Search('参数列表', 'switchStyle.unselectedColor')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'switchStyle.unselectedColor'
        },
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('unselectedColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();
    })

    it('ArkUI_Toggle_024', 0, async (done: Function) => {

      await Search('参数列表', 'switchStyle.unselectedColor')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'switchStyle.unselectedColor',
          toggleClickType: ToggleClick.Close,
        },
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('unselectedColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();
    })

    // switchStyle.pointColor
    it('ArkUI_Toggle_025', 0, async (done: Function) => {

      await Search('参数列表', 'switchStyle.pointColor')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'switchStyle.pointColor',
        },
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('switchPointColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();
    })

    it('ArkUI_Toggle_026', 0, async (done: Function) => {

      await Search('参数列表', 'switchStyle.pointColor')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'switchStyle.pointColor',
        },
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('switchPointColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();
    })

    it('ArkUI_Toggle_027', 0, async (done: Function) => {

      await Search('参数列表', 'switchStyle.pointColor')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'switchStyle.pointColor',
        },
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('switchPointColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })

    it('ArkUI_Toggle_028', 0, async (done: Function) => {

      await Search('参数列表', 'switchStyle.pointColor')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'switchStyle.pointColor',
        },
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('switchPointColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();
    })

    it('ArkUI_Toggle_029', 0, async (done: Function) => {

      await Search('参数列表', 'switchStyle.pointColor')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'switchStyle.pointColor',
        },
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('switchPointColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();
    })

    it('ArkUI_Toggle_030', 0, async (done: Function) => {

      await Search('参数列表', 'switchStyle.pointColor')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'switchStyle.pointColor',
          toggleClickType: ToggleClick.Close,
        },
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('switchPointColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();
    })

    // switchStyle.trackBorderRadius
    it('ArkUI_Toggle_031', 0, async (done: Function) => {

      await Search('参数列表', 'switchStyle.trackBorderRadius')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'switchStyle.trackBorderRadius',
        },
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('trackBorderRadius', JsonType.value),
        ],
        assertEqual: '20.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'switchStyle.trackBorderRadius',
          toggleClickType: ToggleClick.Close,
        },
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('trackBorderRadius', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();
    })

    /**
     * 测试组件width且获取属性正确
     */
    it('ArkUI_Toggle_Comp_0001', 0, async (done: Function) => {
      await titleSearch('基础属性', 'width');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('width', JsonType.value),
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('width', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })

      done();
    })
    /**
     * 测试组件height且获取属性正确
     */
    it('ArkUI_Toggle_Comp_0002', 0, async (done: Function) => {
      await titleSearch('基础属性', 'height');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('height', JsonType.value),
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('height', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })

      done();
    })
    /**
     * 测试组件padding且获取属性正确
     */
    it('ArkUI_Toggle_Comp_0003', 0, async (done: Function) => {
      await titleSearch('基础属性', 'padding');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('padding', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('padding', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    /**
     * 测试组件margin且获取属性正确
     */
    it('ArkUI_Toggle_Comp_0004', 0, async (done: Function) => {
      await titleSearch('基础属性', 'margin');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('margin', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('margin', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
  })
}