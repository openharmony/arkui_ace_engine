import { describe, beforeAll, it, } from '@ohos/hypium'
import { abilityDelegatorRegistry, Driver, ON } from '@kit.TestKit';
import { Point, Component } from '@ohos.UiTest';
import {
  JsonType,
  KeyStruct,
  Slide,
  Search,
  sliderDrag,
  ToggleClick,
  radioClick,
  buttonClick,
  getToggle,
  searchToggle,
  searchParentBlock,
  titleSearch
} from '../../utils';

const TAG = 'SelectBootcamp'


/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function SelectBootcampTest() {
  describe('SelectBootcampTest', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {
      console.info('beforeAll begin');
      try {
        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });
        await driver.delayMs(1500);
        console.info(TAG + 'SelectBootcamp001' + ' begin');
        let ListItemGroups: Array<Component> = await driver.findComponents(ON.type('ListItemGroup'))
        let width0: Point = await ListItemGroups[0].getBoundsCenter()
        let width1: Point = await ListItemGroups[2].getBoundsCenter()
        await driver.swipe(width0.x, width1.y, width0.x, width0.y, 500)
        await driver.delayMs(2000);
        let atomDisplays: Component = await driver.findComponent(ON.text('按钮与选择'));
        await atomDisplays.click();
        await driver.delayMs(1000);
        let ListItems: Array<Component> = await driver.findComponents(ON.type('ListItem'))
        let width: Point = await ListItems[0].getBoundsCenter()
        let width2: Point = await ListItems[6].getBoundsCenter()
        await driver.swipe(width.x, width2.y, width.x, width.y, 500)
        await driver.delayMs(1500);

        let scrollSearch: Component = await driver.findComponent(ON.text('下拉按钮/Select'))
        await scrollSearch.click()
        await driver.delayMs(1000);

        let Buttons: Array<Component> = await driver.findComponents(ON.type('Button'));
        await Buttons[1].click()
        await driver.delayMs(1000);

      } catch (err) {

        console.info(`beforeAll error: ${JSON.stringify(err)}`);

      }
      console.info(`beforeAll end`);
      done();
    })
    //selected
    it('ArkUI_Select_001', 0, async (done: Function) => {
      await Search('参数列表', 'selected')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selected', JsonType.value)
        ],
        assertEqual: '3'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selected', JsonType.value)
        ],
        assertEqual: '0'
      })
      done()
    })
    //controlSize
    /*
     * 测试组件controlSize支持设置small且获取属性正确
     */
    it('ArkUI_Select_002', 0, async (done: Function) => {
      await Search('参数列表', 'controlSize')
      await radioClick({
        radioClickObj: 0,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('controlSize', JsonType.value),
        ],
        assertEqual: 'ControlSize.SMALL'
      })
      done();
    })
    /*
    * 测试组件controlSize支持设置normal且获取属性正确
    */
    it('ArkUI_Select_003', 0, async (done: Function) => {
      await Search('参数列表', 'controlSize')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('controlSize', JsonType.value),
        ],
        assertEqual: 'ControlSize.NORMAL'
      })
      done();
    })
    //divider.DividerOptions.strokeWidth
    it('ArkUI_Select_004', 0, async (done: Function) => {
      await Search('参数列表', 'divider.DividerOptions.strokeWidth')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj)
        ],
        assertEqual: '{"strokeWidth":"10.00vp","startMargin":"-1.00vp","endMargin":"-1.00vp","color":"#33182431"}'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj)
        ],
        assertEqual: '{"strokeWidth":"0.00vp","startMargin":"-1.00vp","endMargin":"-1.00vp","color":"#33182431"}'
      })
      done()
    })
    //divider.DividerOptions.startMargin
    it('ArkUI_Select_005', 0, async (done: Function) => {
      await Search('参数列表', 'divider.DividerOptions.startMargin')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj)
        ],
        assertEqual: '{"strokeWidth":"1.00px","startMargin":"10.00vp","endMargin":"-1.00vp","color":"#33182431"}'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj)
        ],
        assertEqual: '{"strokeWidth":"1.00px","startMargin":"0.00vp","endMargin":"-1.00vp","color":"#33182431"}'
      })
      done()
    })
    //divider.DividerOptions.endMargin
    it('ArkUI_Select_006', 0, async (done: Function) => {
      await Search('参数列表', 'divider.DividerOptions.endMargin')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj)
        ],
        assertEqual: '{"strokeWidth":"1.00px","startMargin":"-1.00vp","endMargin":"10.00vp","color":"#33182431"}'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj)
        ],
        assertEqual: '{"strokeWidth":"1.00px","startMargin":"-1.00vp","endMargin":"0.00vp","color":"#33182431"}'
      })
      done()
    })
    //divider.DividerOptions.color
    /*
    *测试组件divider.DividerOptions.color支持设置量规图的颜色为1号色显示且获取属性正确
    * */
    it('ArkUI_Select_007', 0, async (done: Function) => {
      await Search('参数列表', 'divider.DividerOptions.color')
      await buttonClick({
        buttonClickObj: 0,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj)
        ],
        assertEqual: '{"strokeWidth":"1.00px","startMargin":"-1.00vp","endMargin":"-1.00vp","color":"#FF0A59F7"}'
      })
      done();
    })
    /**
     * 测试组件divider.DividerOptions.color支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_Select_008', 0, async (done: Function) => {
      await Search('参数列表', 'divider.DividerOptions.color')
      await buttonClick({
        buttonClickObj: 1,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj)
        ],
        assertEqual: '{"strokeWidth":"1.00px","startMargin":"-1.00vp","endMargin":"-1.00vp","color":"#FF646AFD"}'
      })
      done();
    })
    /**
     * 测试组件divider.DividerOptions.color支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_Select_009', 0, async (done: Function) => {
      await Search('参数列表', 'divider.DividerOptions.color')
      await buttonClick({
        buttonClickObj: 2,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj)
        ],
        assertEqual: '{"strokeWidth":"1.00px","startMargin":"-1.00vp","endMargin":"-1.00vp","color":"#FFFE7062"}'
      })
      done();
    })
    /**
     * 测试组件divider.DividerOptions.color支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_Select_010', 0, async (done: Function) => {
      await Search('参数列表', 'divider.DividerOptions.color')
      await buttonClick({
        buttonClickObj: 3,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj)
        ],
        assertEqual: '{"strokeWidth":"1.00px","startMargin":"-1.00vp","endMargin":"-1.00vp","color":"#FFE9E8ED"}'
      })
      done();
    })
    /**
     * 测试组件divider.DividerOptions.color支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_Select_011', 0, async (done: Function) => {
      await Search('参数列表', 'divider.DividerOptions.color')
      await buttonClick({
        buttonClickObj: 4,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj)
        ],
        assertEqual: '{"strokeWidth":"1.00px","startMargin":"-1.00vp","endMargin":"-1.00vp","color":"#FF1C1C1C"}'
      })
      done();
    })
    /**
     * 测试组件divider.DividerOptions.color支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_Select_012', 0, async (done: Function) => {
      await Search('参数列表', 'divider.DividerOptions.color')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj)
        ],
        assertEqual: '{"strokeWidth":"1.00px","startMargin":"-1.00vp","endMargin":"-1.00vp","color":"#FFFFFFFF"}'
      })
      done();
    })
    //font.Font.size
    it('ArkUI_Select_013', 0, async (done: Function) => {
      await Search('参数列表', 'font.Font.size')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('font', JsonType.obj)
        ],
        assertEqual: '{"size":"100.00fp","weight":"FontWeight.Medium","family":"","style":"FontStyle.Normal"}'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('font', JsonType.obj)
        ],
        assertEqual: '{"size":"0.00fp","weight":"FontWeight.Medium","family":"","style":"FontStyle.Normal"}'
      })
      done()
    })
    //font.Font.weight
    /*
     * 测试组件font.Font.weight支持设置Lighter且获取属性正确
     */
    it('ArkUI_Select_014', 0, async (done: Function) => {
      await Search('参数列表', 'font.Font.weight')
      await radioClick({
        radioClickObj: 0,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('font', JsonType.obj)
        ],
        assertEqual: '{"size":"16.00fp","weight":"FontWeight.Lighter","family":"","style":"FontStyle.Normal"}'
      })
      done();
    })
    /*
     * 测试组件font.Font.weight支持设置Normal且获取属性正确
     */
    it('ArkUI_Select_015', 0, async (done: Function) => {
      await Search('参数列表', 'font.Font.weight')
      await radioClick({
        radioClickObj: 1,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('font', JsonType.obj)
        ],
        assertEqual: '{"size":"16.00fp","weight":"FontWeight.Normal","family":"","style":"FontStyle.Normal"}'
      })
      done();
    })
    /*
     * 测试组件font.Font.weight支持设置Regular且获取属性正确
     */
    it('ArkUI_Select_016', 0, async (done: Function) => {
      await Search('参数列表', 'font.Font.weight')
      await radioClick({
        radioClickObj: 2,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('font', JsonType.obj)
        ],
        assertEqual: '{"size":"16.00fp","weight":"FontWeight.Regular","family":"","style":"FontStyle.Normal"}'
      })
      done();
    })
    /*
     * 测试组件font.Font.weight支持设置Medium且获取属性正确
     */
    it('ArkUI_Select_017', 0, async (done: Function) => {
      await Search('参数列表', 'font.Font.weight')
      await radioClick({
        radioClickObj: 3,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('font', JsonType.obj)
        ],
        assertEqual: '{"size":"16.00fp","weight":"FontWeight.Medium","family":"","style":"FontStyle.Normal"}'
      })
      done();
    })
    /*
     * 测试组件font.Font.weight支持设置Bold且获取属性正确
     */
    it('ArkUI_Select_018', 0, async (done: Function) => {
      await Search('参数列表', 'font.Font.weight')
      await radioClick({
        radioClickObj: 4,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('font', JsonType.obj)
        ],
        assertEqual: '{"size":"16.00fp","weight":"FontWeight.Bold","family":"","style":"FontStyle.Normal"}'
      })
      done();
    })
    /*
     * 测试组件font.Font.weight支持设置Bolder且获取属性正确
     */
    it('ArkUI_Select_019', 0, async (done: Function) => {
      await Search('参数列表', 'font.Font.weight')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('font', JsonType.obj)
        ],
        assertEqual: '{"size":"16.00fp","weight":"FontWeight.Bolder","family":"","style":"FontStyle.Normal"}'
      })
      done();
    })
    //font.Font.family  没有属性值，无法断言
    it('ArkUI_Select_020', 0, async (done: Function) => {
      await Search('参数列表', 'font.Font.weight')
      await getToggle(ToggleClick.Close)
      done();
    })
    //font.Font.style
    /*
     * 测试组件font.Font.style支持设置Normal且获取属性正确
     */
    it('ArkUI_Select_021', 0, async (done: Function) => {
      await Search('参数列表', 'font.Font.style')
      await radioClick({
        radioClickObj: 0,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('font', JsonType.obj)
        ],
        assertEqual: '{"size":"16.00fp","weight":"FontWeight.Medium","family":"","style":"FontStyle.Normal"}'
      })
      done();
    })
    /*
     * 测试组件font.Font.style支持设置Italic且获取属性正确
     */
    it('ArkUI_Select_022', 0, async (done: Function) => {
      await Search('参数列表', 'font.Font.style')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('font', JsonType.obj)
        ],
        assertEqual: '{"size":"16.00fp","weight":"FontWeight.Medium","family":"","style":"FontStyle.Italic"}'
      })
      done();
    })
    //fontColor
    /*
    *测试组件fontColor支持设置量规图的颜色为1号色显示且获取属性正确
    * */
    it('ArkUI_Select_023', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 0,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value)
        ],
        assertEqual: '#FF0A59F7'
      })
      done();
    })
    /**
     * 测试组件fontColor支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_Select_024', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 1,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value)
        ],
        assertEqual: '#FF646AFD'
      })
      done();
    })
    /**
     * 测试组件fontColor支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_Select_025', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 2,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value)
        ],
        assertEqual: '#FFFE7062'
      })
      done();
    })
    /**
     * 测试组件fontColor支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_Select_026', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 3,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value)
        ],
        assertEqual: '#FFE9E8ED'
      })
      done();
    })
    /**
     * 测试组件fontColor支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_Select_027', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 4,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value)
        ],
        assertEqual: '#FF1C1C1C'
      })
      done();
    })
    /**
     * 测试组件fontColor支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_Select_028', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value)
        ],
        assertEqual: '#FFFFFFFF'
      })
      done();
    })
    //selectedOptionBgColor
    /*
    *测试组件selectedOptionBgColor支持设置量规图的颜色为1号色显示且获取属性正确
    * */
    it('ArkUI_Select_029', 0, async (done: Function) => {
      await Search('参数列表', 'selectedOptionBgColor')
      await buttonClick({
        buttonClickObj: 0,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedOptionBgColor', JsonType.value)
        ],
        assertEqual: '#FF0A59F7'
      })
      done();
    })
    /**
     * 测试组件selectedOptionBgColor支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_Select_030', 0, async (done: Function) => {
      await Search('参数列表', 'selectedOptionBgColor')
      await buttonClick({
        buttonClickObj: 1,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedOptionBgColor', JsonType.value)
        ],
        assertEqual: '#FF646AFD'
      })
      done();
    })
    /**
     * 测试组件selectedOptionBgColor支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_Select_031', 0, async (done: Function) => {
      await Search('参数列表', 'selectedOptionBgColor')
      await buttonClick({
        buttonClickObj: 2,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedOptionBgColor', JsonType.value)
        ],
        assertEqual: '#FFFE7062'
      })
      done();
    })
    /**
     * 测试组件selectedOptionBgColor支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_Select_032', 0, async (done: Function) => {
      await Search('参数列表', 'selectedOptionBgColor')
      await buttonClick({
        buttonClickObj: 3,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedOptionBgColor', JsonType.value)
        ],
        assertEqual: '#FFE9E8ED'
      })
      done();
    })
    /**
     * 测试组件selectedOptionBgColor支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_Select_033', 0, async (done: Function) => {
      await Search('参数列表', 'selectedOptionBgColor')
      await buttonClick({
        buttonClickObj: 4,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedOptionBgColor', JsonType.value)
        ],
        assertEqual: '#FF1C1C1C'
      })
      done();
    })
    /**
     * 测试组件selectedOptionBgColor支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_Select_034', 0, async (done: Function) => {
      await Search('参数列表', 'selectedOptionBgColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedOptionBgColor', JsonType.value)
        ],
        assertEqual: '#FFFFFFFF'
      })
      done();
    })
    //selectedOptionFont.Font.size
    it('ArkUI_Select_035', 0, async (done: Function) => {
      await Search('参数列表', 'selectedOptionFont.Font.size')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedOptionFont', JsonType.obj)
        ],
        assertEqual: '{"size":"100.00fp","weight":"FontWeight.Regular","family":"","style":"FontStyle.Normal"}'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedOptionFont', JsonType.obj)
        ],
        assertEqual: '{"size":"0.00fp","weight":"FontWeight.Regular","family":"","style":"FontStyle.Normal"}'
      })
      done()
    })
    //selectedOptionFont.Font.weight
    /*
     * 测试组件selectedOptionFont.Font.weight支持设置Lighter且获取属性正确
     */
    it('ArkUI_Select_036', 0, async (done: Function) => {
      await Search('参数列表', 'selectedOptionFont.Font.weight')
      await radioClick({
        radioClickObj: 0,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedOptionFont', JsonType.obj)
        ],
        assertEqual: '{"size":"16.00fp","weight":"FontWeight.Lighter","family":"","style":"FontStyle.Normal"}'
      })
      done();
    })
    /*
     * 测试组件selectedOptionFont.Font.weight支持设置Normal且获取属性正确
     */
    it('ArkUI_Select_037', 0, async (done: Function) => {
      await Search('参数列表', 'selectedOptionFont.Font.weight')
      await radioClick({
        radioClickObj: 1,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedOptionFont', JsonType.obj)
        ],
        assertEqual: '{"size":"16.00fp","weight":"FontWeight.Normal","family":"","style":"FontStyle.Normal"}'
      })
      done();
    })
    /*
     * 测试组件selectedOptionFont.Font.weight支持设置Regular且获取属性正确
     */
    it('ArkUI_Select_038', 0, async (done: Function) => {
      await Search('参数列表', 'selectedOptionFont.Font.weight')
      await radioClick({
        radioClickObj: 2,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedOptionFont', JsonType.obj)
        ],
        assertEqual: '{"size":"16.00fp","weight":"FontWeight.Regular","family":"","style":"FontStyle.Normal"}'
      })
      done();
    })
    /*
     * 测试组件selectedOptionFont.Font.weight支持设置Medium且获取属性正确
     */
    it('ArkUI_Select_039', 0, async (done: Function) => {
      await Search('参数列表', 'selectedOptionFont.Font.weight')
      await radioClick({
        radioClickObj: 3,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedOptionFont', JsonType.obj)
        ],
        assertEqual: '{"size":"16.00fp","weight":"FontWeight.Medium","family":"","style":"FontStyle.Normal"}'
      })
      done();
    })
    /*
     * 测试组件selectedOptionFont.Font.weight支持设置Bold且获取属性正确
     */
    it('ArkUI_Select_040', 0, async (done: Function) => {
      await Search('参数列表', 'selectedOptionFont.Font.weight')
      await radioClick({
        radioClickObj: 4,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedOptionFont', JsonType.obj)
        ],
        assertEqual: '{"size":"16.00fp","weight":"FontWeight.Bold","family":"","style":"FontStyle.Normal"}'
      })
      done();
    })
    /*
     * 测试组件selectedOptionFont.Font.weight支持设置Bolder且获取属性正确
     */
    it('ArkUI_Select_041', 0, async (done: Function) => {
      await Search('参数列表', 'selectedOptionFont.Font.weight')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedOptionFont', JsonType.obj)
        ],
        assertEqual: '{"size":"16.00fp","weight":"FontWeight.Bolder","family":"","style":"FontStyle.Normal"}'
      })
      done();
    })
    //selectedOptionFont.Font.family  没有属性值，无法断言
    it('ArkUI_Select_042', 0, async (done: Function) => {
      await Search('参数列表', 'selectedOptionFont.Font.weight')
      await getToggle(ToggleClick.Close)
      done();
    })
    //selectedOptionFont.Font.style
    /*
     * 测试组件selectedOptionFont.Font.style支持设置Normal且获取属性正确
     */
    it('ArkUI_Select_043', 0, async (done: Function) => {
      await Search('参数列表', 'selectedOptionFont.Font.style')
      await radioClick({
        radioClickObj: 0,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedOptionFont', JsonType.obj)
        ],
        assertEqual: '{"size":"16.00fp","weight":"FontWeight.Regular","family":"","style":"FontStyle.Normal"}'
      })
      done();
    })
    /*
     * 测试组件selectedOptionFont.Font.style支持设置Italic且获取属性正确
     */
    it('ArkUI_Select_044', 0, async (done: Function) => {
      await Search('参数列表', 'selectedOptionFont.Font.style')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedOptionFont', JsonType.obj)
        ],
        assertEqual: '{"size":"16.00fp","weight":"FontWeight.Regular","family":"","style":"FontStyle.Italic"}'
      })
      done();
    })
    //selectedOptionFontColor
    /*
    *测试组件selectedOptionFontColor支持设置量规图的颜色为1号色显示且获取属性正确
    * */
    it('ArkUI_Select_045', 0, async (done: Function) => {
      await Search('参数列表', 'selectedOptionFontColor')
      await buttonClick({
        buttonClickObj: 0,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedOptionFontColor', JsonType.value)
        ],
        assertEqual: '#FF0A59F7'
      })
      done();
    })
    /**
     * 测试组件selectedOptionFontColor支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_Select_046', 0, async (done: Function) => {
      await Search('参数列表', 'selectedOptionFontColor')
      await buttonClick({
        buttonClickObj: 1,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedOptionFontColor', JsonType.value)
        ],
        assertEqual: '#FF646AFD'
      })
      done();
    })
    /**
     * 测试组件selectedOptionFontColor支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_Select_047', 0, async (done: Function) => {
      await Search('参数列表', 'selectedOptionFontColor')
      await buttonClick({
        buttonClickObj: 2,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedOptionFontColor', JsonType.value)
        ],
        assertEqual: '#FFFE7062'
      })
      done();
    })
    /**
     * 测试组件selectedOptionFontColor支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_Select_048', 0, async (done: Function) => {
      await Search('参数列表', 'selectedOptionFontColor')
      await buttonClick({
        buttonClickObj: 3,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedOptionFontColor', JsonType.value)
        ],
        assertEqual: '#FFE9E8ED'
      })
      done();
    })
    /**
     * 测试组件selectedOptionFontColor支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_Select_049', 0, async (done: Function) => {
      await Search('参数列表', 'selectedOptionFontColor')
      await buttonClick({
        buttonClickObj: 4,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedOptionFontColor', JsonType.value)
        ],
        assertEqual: '#FF1C1C1C'
      })
      done();
    })
    /**
     * 测试组件selectedOptionFontColor支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_Select_050', 0, async (done: Function) => {
      await Search('参数列表', 'selectedOptionFontColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedOptionFontColor', JsonType.value)
        ],
        assertEqual: '#FFFFFFFF'
      })
      done();
    })


  })
}