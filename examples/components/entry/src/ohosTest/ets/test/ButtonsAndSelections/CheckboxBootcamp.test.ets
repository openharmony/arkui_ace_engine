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

const TAG = 'CheckboxBootcamp'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function CheckboxBootcampTest() {
  describe('CheckboxBootcampTest', () => {

    beforeAll(async (done: Function) => {

      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(5000);
        console.info(TAG + 'CheckboxBootcamp' + ' begin');

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

        let scrollSearch: Component = await driver.findComponent(ON.text('多选框/Checkbox'))
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

    // Checkbox.options.indicatorBuilder
    it('ArkUI_Checkbox_001', 0, async (done: Function) => {
      // 获取不到属性
      await Search('参数列表', 'Checkbox.options.indicatorBuilder')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'Checkbox.options.indicatorBuilder'
        },
      })

      done();
    })

    it('ArkUI_Checkbox_002', 0, async (done: Function) => {

      await Search('参数列表', 'Checkbox.options.indicatorBuilder')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done();
    })

    // select
    it('ArkUI_Checkbox_003', 0, async (done: Function) => {

      await Search('参数列表', 'select')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'select'
        },
        id: 'Checkbox',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('select', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();
    })

    it('ArkUI_Checkbox_004', 0, async (done: Function) => {

      await Search('参数列表', 'select')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Checkbox',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('select', JsonType.value),
        ],
        assertEqual: 'false'
      })

      done();
    })

    // selectedColor
    it('ArkUI_Checkbox_005', 0, async (done: Function) => {

      await Search('参数列表', 'selectedColor')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'selectedColor'
        },
        id: 'Checkbox',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();
    })

    it('ArkUI_Checkbox_006', 0, async (done: Function) => {

      await Search('参数列表', 'selectedColor')

      await buttonClick({
        buttonClickObj: 1,
        id: 'Checkbox',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();
    })

    it('ArkUI_Checkbox_007', 0, async (done: Function) => {

      await Search('参数列表', 'selectedColor')

      await buttonClick({
        buttonClickObj: 2,
        id: 'Checkbox',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })

    it('ArkUI_Checkbox_008', 0, async (done: Function) => {

      await Search('参数列表', 'selectedColor')

      await buttonClick({
        buttonClickObj: 3,
        id: 'Checkbox',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();
    })

    it('ArkUI_Checkbox_009', 0, async (done: Function) => {

      await Search('参数列表', 'selectedColor')

      await buttonClick({
        buttonClickObj: 4,
        id: 'Checkbox',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();
    })

    it('ArkUI_Checkbox_010', 0, async (done: Function) => {

      await Search('参数列表', 'selectedColor')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Checkbox',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();
    })

    // unselectedColor
    it('ArkUI_Checkbox_011', 0, async (done: Function) => {

      await Search('参数列表', 'unselectedColor')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'unselectedColor'
        },
        id: 'Checkbox',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('unselectedColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();
    })

    it('ArkUI_Checkbox_012', 0, async (done: Function) => {

      await Search('参数列表', 'unselectedColor')

      await buttonClick({
        buttonClickObj: 1,
        id: 'Checkbox',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('unselectedColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();
    })

    it('ArkUI_Checkbox_013', 0, async (done: Function) => {

      await Search('参数列表', 'unselectedColor')

      await buttonClick({
        buttonClickObj: 2,
        id: 'Checkbox',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('unselectedColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })

    it('ArkUI_Checkbox_014', 0, async (done: Function) => {

      await Search('参数列表', 'unselectedColor')

      await buttonClick({
        buttonClickObj: 3,
        id: 'Checkbox',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('unselectedColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();
    })

    it('ArkUI_Checkbox_015', 0, async (done: Function) => {

      await Search('参数列表', 'unselectedColor')

      await buttonClick({
        buttonClickObj: 4,
        id: 'Checkbox',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('unselectedColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();
    })

    it('ArkUI_Checkbox_016', 0, async (done: Function) => {

      await Search('参数列表', 'unselectedColor')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Checkbox',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('unselectedColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();
    })

    // mark.value.strokeColor
    it('ArkUI_Checkbox_017', 0, async (done: Function) => {

      await Search('参数列表', 'mark.value.strokeColor')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'mark.value.strokeColor'
        },
        id: 'Checkbox',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('mark', JsonType.obj),
        ],
        assertEqual: '{"strokeColor":"#FF0A59F7","size":"-1.00px","strokeWidth":"2.00vp"}'
      })

      done();
    })

    it('ArkUI_Checkbox_018', 0, async (done: Function) => {

      await Search('参数列表', 'mark.value.strokeColor')

      await buttonClick({
        buttonClickObj: 1,
        id: 'Checkbox',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('mark', JsonType.obj),
        ],
        assertEqual: '{"strokeColor":"#FF646AFD","size":"-1.00px","strokeWidth":"2.00vp"}'
      })

      done();
    })

    it('ArkUI_Checkbox_019', 0, async (done: Function) => {

      await Search('参数列表', 'mark.value.strokeColor')

      await buttonClick({
        buttonClickObj: 2,
        id: 'Checkbox',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('mark', JsonType.obj),
        ],
        assertEqual: '{"strokeColor":"#FFFE7062","size":"-1.00px","strokeWidth":"2.00vp"}'
      })

      done();
    })

    it('ArkUI_Checkbox_020', 0, async (done: Function) => {

      await Search('参数列表', 'mark.value.strokeColor')

      await buttonClick({
        buttonClickObj: 3,
        id: 'Checkbox',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('mark', JsonType.obj),
        ],
        assertEqual: '{"strokeColor":"#FFE9E8ED","size":"-1.00px","strokeWidth":"2.00vp"}'
      })

      done();
    })

    it('ArkUI_Checkbox_021', 0, async (done: Function) => {

      await Search('参数列表', 'mark.value.strokeColor')

      await buttonClick({
        buttonClickObj: 4,
        id: 'Checkbox',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('mark', JsonType.obj),
        ],
        assertEqual: '{"strokeColor":"#FF1C1C1C","size":"-1.00px","strokeWidth":"2.00vp"}'
      })

      done();
    })

    it('ArkUI_Checkbox_022', 0, async (done: Function) => {

      await Search('参数列表', 'mark.value.strokeColor')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Checkbox',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('mark', JsonType.obj),
        ],
        assertEqual: '{"strokeColor":"#FFFFFFFF","size":"-1.00px","strokeWidth":"2.00vp"}'
      })

      done();
    })

    // mark.value.size
    it('ArkUI_Checkbox_023', 0, async (done: Function) => {

      await Search('参数列表', 'mark.value.size')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'mark.value.size'
        },
        id: 'Checkbox',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('mark', JsonType.obj),
        ],
        assertEqual: '{"strokeColor":"#FFFFFFFF","size":"20.00vp","strokeWidth":"2.00vp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'mark.value.size',
          toggleClickType: ToggleClick.Close
        },
        id: 'Checkbox',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('mark', JsonType.obj),
        ],
        assertEqual: '{"strokeColor":"#FFFFFFFF","size":"0.00vp","strokeWidth":"2.00vp"}'
      })

      done();
    })

    //mark.value.strokeWidth
    it('ArkUI_Checkbox_024', 0, async (done: Function) => {

      await Search('参数列表', 'mark.value.strokeWidth')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'mark.value.strokeWidth'
        },
        id: 'Checkbox',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('mark', JsonType.obj),
        ],
        assertEqual: '{"strokeColor":"#FFFFFFFF","size":"-1.00px","strokeWidth":"20.00vp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'mark.value.strokeWidth',
          toggleClickType: ToggleClick.Close,
        },
        id: 'Checkbox',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('mark', JsonType.obj),
        ],
        assertEqual: '{"strokeColor":"#FFFFFFFF","size":"-1.00px","strokeWidth":"0.00vp"}'
      })

      done();
    })

    // shape
    it('ArkUI_Checkbox_025', 0, async (done: Function) => {

      await Search('参数列表', 'shape')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'shape'
        },
        id: 'Checkbox',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shape', JsonType.value),
        ],
        assertEqual: '1'
      })

      done();
    })

    it('ArkUI_Checkbox_026', 0, async (done: Function) => {

      await Search('参数列表', 'shape')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'shape',
          toggleClickType: ToggleClick.Close
        },
        id: 'Checkbox',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shape', JsonType.value),
        ],
        assertEqual: '0'
      })

      done();
    })

    // modifier
    it('ArkUI_Checkbox_027', 0, async (done: Function) => {
      // 获取不到属性
      await Search('参数列表', 'modifier')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'modifier'
        },
      })

      done();
    })

    it('ArkUI_Checkbox_028', 0, async (done: Function) => {

      await Search('参数列表', 'modifier')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'modifier',
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })

    /**
     * 测试组件width且获取属性正确
     */
    it('ArkUI_Checkbox_Comp_0001', 0, async (done: Function) => {
      await titleSearch('基础属性', 'width');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Checkbox',
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
        id: 'Checkbox',
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
    it('ArkUI_Checkbox_Comp_0002', 0, async (done: Function) => {
      await titleSearch('基础属性', 'height');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Checkbox',
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
        id: 'Checkbox',
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
    it('ArkUI_Checkbox_Comp_0003', 0, async (done: Function) => {
      await titleSearch('基础属性', 'padding');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        // id: 'Checkbox',
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
        id: 'Checkbox',
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
    it('ArkUI_Checkbox_Comp_0004', 0, async (done: Function) => {
      await titleSearch('基础属性', 'margin');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Checkbox',
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
        id: 'Checkbox',
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
    it('ArkUI_Checkbox_Comp_0005', 0, async (done: Function) => {
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
    it('ArkUI_Checkbox_Comp_0006', 0, async (done: Function) => {
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
        id: 'Checkbox',
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
        id: 'Checkbox',
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
    it('ArkUI_Checkbox_Comp_0007', 0, async (done: Function) => {
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
        id: 'Checkbox',
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
        id: 'Checkbox',
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
    it('ArkUI_Checkbox_Comp_0008', 0, async (done: Function) => {
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
        id: 'Checkbox',
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
        id: 'Checkbox',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"0.00vp","maxWidth":"100.00vp","maxHeight":"Infinityvp"}'
      })

      done();
    })
  })
}