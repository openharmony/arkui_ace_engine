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
import { Point } from '@ohos.UiTest';

const TAG = 'RadioBootcamp'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function RadioBootcampTest() {

  describe('RadioBootcampTest', () => {

    beforeAll(async (done: Function) => {
      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(5000);
        console.info(TAG + 'RadioBootcamp' + ' begin');

        let atomDisplays: Component = await driver.findComponent(ON.text('按钮与选择'));
        await atomDisplays.click();
        await driver.delayMs(1000);

        let ListItems: Component[] = await driver.findComponents(ON.type('ListItem'))
        let width: Point = await ListItems[0].getBoundsCenter()
        let width2: Point = await ListItems[1].getBoundsCenter()
        await driver.swipe(width.x, width2.y, width.x, width.y, 500)
        await driver.delayMs(1000);

        let ListItems1: Component[] = await driver.findComponents(ON.type('ListItem'))
        let width3: Point = await ListItems1[0].getBoundsCenter()
        let width4: Point = await ListItems1[3].getBoundsCenter()
        await driver.swipe(width3.x, width4.y, width3.x, width3.y, 500)
        await driver.delayMs(1000);

        let scrollSearch: Component = await driver.findComponent(ON.text('单选框/Radio'))
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
    /**
     * indicatorType且获取属性正确
     */
    it('ArkUI_Radio_001', 0, async (done: Function) => {

      await Search('参数列表', 'indicatorType')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'indicatorType'
        },
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicatorType', JsonType.value),
        ],
        assertEqual: 'DOT'
      })

      done();
    })

    it('ArkUI_Radio_002', 0, async (done: Function) => {

      await Search('参数列表', 'indicatorType')

      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'indicatorType'
        },
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicatorType', JsonType.value),
        ],
        assertEqual: 'CUSTOM'
      })

      done();
    })

    it('ArkUI_Radio_003', 0, async (done: Function) => {

      await Search('参数列表', 'indicatorType')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'indicatorType',
          toggleClickType: ToggleClick.Close
        },
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicatorType', JsonType.value),
        ],
        assertEqual: 'TICK'
      })

      done();
    })
    /**
     * checkedBackgroundColor且获取属性正确
     */
    it('ArkUI_Radio_004', 0, async (done: Function) => {

      await Search('参数列表', 'checkedBackgroundColor')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'checkedBackgroundColor'
        },
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('radioStyle', JsonType.obj),
        ],
        assertEqual: '{"checkedBackgroundColor":"#FF0A59F7","uncheckedBorderColor":"#66182431","indicatorColor":"#FFFFFFFF"}'
      })

      done();
    })

    it('ArkUI_Radio_005', 0, async (done: Function) => {

      await Search('参数列表', 'checkedBackgroundColor')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'checkedBackgroundColor'
        },
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('radioStyle', JsonType.obj),
        ],
        assertEqual: '{"checkedBackgroundColor":"#FF646AFD","uncheckedBorderColor":"#66182431","indicatorColor":"#FFFFFFFF"}'
      })

      done();
    })

    it('ArkUI_Radio_006', 0, async (done: Function) => {

      await Search('参数列表', 'checkedBackgroundColor')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'checkedBackgroundColor'
        },
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('radioStyle', JsonType.obj),
        ],
        assertEqual: '{"checkedBackgroundColor":"#FFFE7062","uncheckedBorderColor":"#66182431","indicatorColor":"#FFFFFFFF"}'
      })

      done();
    })

    it('ArkUI_Radio_007', 0, async (done: Function) => {

      await Search('参数列表', 'checkedBackgroundColor')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'checkedBackgroundColor'
        },
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('radioStyle', JsonType.obj),
        ],
        assertEqual: '{"checkedBackgroundColor":"#FFE9E8ED","uncheckedBorderColor":"#66182431","indicatorColor":"#FFFFFFFF"}'
      })

      done();
    })

    it('ArkUI_Radio_008', 0, async (done: Function) => {

      await Search('参数列表', 'checkedBackgroundColor')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'checkedBackgroundColor'
        },
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('radioStyle', JsonType.obj),
        ],
        assertEqual: '{"checkedBackgroundColor":"#FF1C1C1C","uncheckedBorderColor":"#66182431","indicatorColor":"#FFFFFFFF"}'
      })

      done();
    })

    it('ArkUI_Radio_009', 0, async (done: Function) => {

      await Search('参数列表', 'checkedBackgroundColor')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'checkedBackgroundColor',
          toggleClickType: ToggleClick.Close
        },
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('radioStyle', JsonType.obj),
        ],
        assertEqual: '{"checkedBackgroundColor":"#FFFFFFFF","uncheckedBorderColor":"#66182431","indicatorColor":"#FFFFFFFF"}'
      })

      done();
    })
    /**
     * uncheckedBorderColor且获取属性正确
     */
    it('ArkUI_Radio_010', 0, async (done: Function) => {

      await Search('参数列表', 'uncheckedBorderColor')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'uncheckedBorderColor'
        },
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('radioStyle', JsonType.obj),
        ],
        assertEqual: '{"checkedBackgroundColor":"#FF007DFF","uncheckedBorderColor":"#FF0A59F7","indicatorColor":"#FFFFFFFF"}'
      })

      done();
    })

    it('ArkUI_Radio_011', 0, async (done: Function) => {

      await Search('参数列表', 'uncheckedBorderColor')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'uncheckedBorderColor'
        },
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('radioStyle', JsonType.obj),
        ],
        assertEqual: '{"checkedBackgroundColor":"#FF007DFF","uncheckedBorderColor":"#FF646AFD","indicatorColor":"#FFFFFFFF"}'
      })

      done();
    })

    it('ArkUI_Radio_012', 0, async (done: Function) => {

      await Search('参数列表', 'uncheckedBorderColor')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'uncheckedBorderColor'
        },
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('radioStyle', JsonType.obj),
        ],
        assertEqual: '{"checkedBackgroundColor":"#FF007DFF","uncheckedBorderColor":"#FFFE7062","indicatorColor":"#FFFFFFFF"}'
      })

      done();
    })

    it('ArkUI_Radio_013', 0, async (done: Function) => {

      await Search('参数列表', 'uncheckedBorderColor')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'uncheckedBorderColor'
        },
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('radioStyle', JsonType.obj),
        ],
        assertEqual: '{"checkedBackgroundColor":"#FF007DFF","uncheckedBorderColor":"#FFE9E8ED","indicatorColor":"#FFFFFFFF"}'
      })

      done();
    })

    it('ArkUI_Radio_014', 0, async (done: Function) => {

      await Search('参数列表', 'uncheckedBorderColor')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'uncheckedBorderColor'
        },
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('radioStyle', JsonType.obj),
        ],
        assertEqual: '{"checkedBackgroundColor":"#FF007DFF","uncheckedBorderColor":"#FF1C1C1C","indicatorColor":"#FFFFFFFF"}'
      })

      done();
    })

    it('ArkUI_Radio_015', 0, async (done: Function) => {

      await Search('参数列表', 'uncheckedBorderColor')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'uncheckedBorderColor',
          toggleClickType: ToggleClick.Close
        },
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('radioStyle', JsonType.obj),
        ],
        assertEqual: '{"checkedBackgroundColor":"#FF007DFF","uncheckedBorderColor":"#FFFFFFFF","indicatorColor":"#FFFFFFFF"}'
      })

      done();
    })
    /**
     * indicatorColor且获取属性正确
     */
    it('ArkUI_Radio_016', 0, async (done: Function) => {

      await Search('参数列表', 'indicatorColor')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'indicatorColor'
        },
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('radioStyle', JsonType.obj),
        ],
        assertEqual: '{"checkedBackgroundColor":"#FF007DFF","uncheckedBorderColor":"#66182431","indicatorColor":"#FF0A59F7"}'
      })

      done();
    })

    it('ArkUI_Radio_017', 0, async (done: Function) => {

      await Search('参数列表', 'indicatorColor')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'indicatorColor'
        },
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('radioStyle', JsonType.obj),
        ],
        assertEqual: '{"checkedBackgroundColor":"#FF007DFF","uncheckedBorderColor":"#66182431","indicatorColor":"#FF646AFD"}'
      })

      done();
    })

    it('ArkUI_Radio_018', 0, async (done: Function) => {

      await Search('参数列表', 'indicatorColor')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'indicatorColor'
        },
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('radioStyle', JsonType.obj),
        ],
        assertEqual: '{"checkedBackgroundColor":"#FF007DFF","uncheckedBorderColor":"#66182431","indicatorColor":"#FFFE7062"}'
      })

      done();
    })

    it('ArkUI_Radio_019', 0, async (done: Function) => {

      await Search('参数列表', 'indicatorColor')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'indicatorColor'
        },
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('radioStyle', JsonType.obj),
        ],
        assertEqual: '{"checkedBackgroundColor":"#FF007DFF","uncheckedBorderColor":"#66182431","indicatorColor":"#FFE9E8ED"}'
      })

      done();
    })

    it('ArkUI_Radio_020', 0, async (done: Function) => {

      await Search('参数列表', 'indicatorColor')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'indicatorColor'
        },
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('radioStyle', JsonType.obj),
        ],
        assertEqual: '{"checkedBackgroundColor":"#FF007DFF","uncheckedBorderColor":"#66182431","indicatorColor":"#FF1C1C1C"}'
      })

      done();
    })

    it('ArkUI_Radio_021', 0, async (done: Function) => {

      await Search('参数列表', 'indicatorColor')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'indicatorColor',
          toggleClickType: ToggleClick.Close
        },
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('radioStyle', JsonType.obj),
        ],
        assertEqual: '{"checkedBackgroundColor":"#FF007DFF","uncheckedBorderColor":"#66182431","indicatorColor":"#FFFFFFFF"}'
      })

      done();
    })
    /**
     * contentModifier
     */
    it('ArkUI_Radio_023', 0, async (done: Function) => {
      // 未找到该属性
      await Search('参数列表', 'contentModifier')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'contentModifier'
        }
      })

      done();
    })

    it('ArkUI_Radio_024', 0, async (done: Function) => {

      await Search('参数列表', 'contentModifier')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'contentModifier',
          toggleClickType: ToggleClick.Close
        }
      })

      done();
    })
    /**
     * 测试组件width且获取属性正确
     */
    it('ArkUI_Radio_Comp_0001', 0, async (done: Function) => {
      await titleSearch('基础属性', 'width');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Radio',
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
        id: 'Radio',
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
    it('ArkUI_Radio_Comp_0002', 0, async (done: Function) => {
      await titleSearch('基础属性', 'height');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Radio',
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
        id: 'Radio',
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
    it('ArkUI_Radio_Comp_0003', 0, async (done: Function) => {
      await titleSearch('基础属性', 'padding');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Radio',
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
        id: 'Radio',
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
    it('ArkUI_Radio_Comp_0004', 0, async (done: Function) => {
      await titleSearch('基础属性', 'margin');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Radio',
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
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('margin', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    /**
     * 测试开启constraintSize
     */
    it('ArkUI_Radio_Comp_0005', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      await toggle[0].click()
      await driver.delayMs(1000);
      done();
    })
    /**
     * 测试组件constraintSize.minWidth且获取属性正确
     */
    it('ArkUI_Radio_Comp_0006', 0, async (done: Function) => {
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.minWidth');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"500.00vp","minHeight":"0.00vp","maxWidth":"Infinityvp","maxHeight":"Infinityvp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"100.00vp","minHeight":"0.00vp","maxWidth":"Infinityvp","maxHeight":"Infinityvp"}'
      })

      done();
    })
    /**
     * 测试组件constraintSize.minHeight且获取属性正确
     */
    it('ArkUI_Radio_Comp_0007', 0, async (done: Function) => {
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.minHeight');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"500.00vp","maxWidth":"Infinityvp","maxHeight":"Infinityvp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"100.00vp","maxWidth":"Infinityvp","maxHeight":"Infinityvp"}'
      })

      done();
    })
    /**
     * 测试组件constraintSize.maxWidth且获取属性正确
     */
    it('ArkUI_Radio_Comp_0008', 0, async (done: Function) => {
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.maxWidth');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"0.00vp","maxWidth":"500.00vp","maxHeight":"Infinityvp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"0.00vp","maxWidth":"100.00vp","maxHeight":"Infinityvp"}'
      })

      done();
    })
    /**
     * 测试组件constraintSize.maxHeight且获取属性正确
     */
    it('ArkUI_Radio_Comp_0009', 0, async (done: Function) => {
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.maxHeight');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"0.00vp","maxWidth":"Infinityvp","maxHeight":"500.00vp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"0.00vp","maxWidth":"Infinityvp","maxHeight":"100.00vp"}'
      })

      done();
    })
    /**
     * 测试关闭constraintSize,无断言
     */
    it('ArkUI_Radio_Comp_0010', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(1000);

      done();
    })
    /**
     * 测试开启position
     */
    it('ArkUI_Radio_Comp_0011', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'position');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      await toggle[0].click()
      await driver.delayMs(1000);
      done();
    })
    /**
     * 测试组件position.top且获取属性正确
     */
    it('ArkUI_Radio_Comp_0012', 0, async (done: Function) => {
      //无值，只有xy的值
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'position.top');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件position.bottom且获取属性正确
     */
    it('ArkUI_Radio_Comp_0013', 0, async (done: Function) => {
      //无值，只有xy的值
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'position.bottom');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件position.left且获取属性正确
     */
    it('ArkUI_Radio_Comp_0014', 0, async (done: Function) => {
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'position.left');
      //无值，只有xy的值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
  })
}