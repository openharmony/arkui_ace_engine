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
import { pageOneTmp } from './PageOne'
@Entry
@Component
struct NavigationExample {
	@Provide('pageInfos') pageInfos: NavPathStack = new NavPathStack()
	@State barStyle: BarStyle = BarStyle.STANDARD
	@State hideNavBar:boolean=false
	@State hideTitleBar:boolean=false
	@State hideToolBar:boolean=false
	@State Click: ClickEffectLevel=ClickEffectLevel.HEAVY
	@State pathStack: NavPathStack = new NavPathStack();
	@State titleMode:NavigationTitleMode=NavigationTitleMode.Mini
	@State edge: Array<LayoutSafeAreaEdge> = [];
	@State type: Array<LayoutSafeAreaType> = [];
	@State mode:NavigationMode=	NavigationMode.Auto
	@State navBarPosition:NavBarPosition=NavBarPosition.Start
	@State navBarWidth:number=200
	@State top:number=0
	@State bottom:number=0
	@State left:number=0
	@State right:number=0

	@State type2: Array<SafeAreaType> = [SafeAreaType.SYSTEM, SafeAreaType.CUTOUT, SafeAreaType.KEYBOARD];
	@State edge2: Array<SafeAreaEdge> = [SafeAreaEdge.TOP, SafeAreaEdge.BOTTOM, SafeAreaEdge.START, SafeAreaEdge.END];

	@State marginValue:number = 0

	@Builder
	PageMap(name: string) {
		if (name === 'pageOne') {
			pageOneTmp({pageId: Date.now()})
		}
	}

	@Styles buttonStyles() {
		.margin(2)
		.padding(2)
		.height(25)
	}

	build() {
			Navigation(this.pageInfos) {
				Column() {
					Text('Main').margin({bottom:10})
					Flex({wrap: FlexWrap.Wrap}) {
						Button('pushPageOne', { stateEffect: true, type: ButtonType.Capsule })
							.buttonStyles()
							.fontSize(12)
							.onClick(() => {
								this.pageInfos.pushPath({ name: 'pageOne' })
							})
						Button('NavigationTitleMode.Mini')
							.onClick(() => {
								this.titleMode = NavigationTitleMode.Mini
							})
							.buttonStyles()
							.fontSize(12)
							.clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor(Color.Orange)
						Button('NavigationTitleMode.Free')
							.onClick(() => {
								this.titleMode = NavigationTitleMode.Free
							})
							.buttonStyles()
							.fontSize(12)
							.clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor(Color.Orange)
						Button('NavigationTitleMode.Full')
							.onClick(() => {
								this.titleMode = NavigationTitleMode.Full
							})
							.buttonStyles()
							.fontSize(12)
							.clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor(Color.Orange)

						Button('mode=NavigationMode.Auto')
							.onClick(() => {
								this.mode = NavigationMode.Auto
							})
							.buttonStyles()
							.fontSize(12)
							.clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#71B26C')
						Button('mode=NavigationMode.Stack')
							.onClick(() => {
								this.mode = NavigationMode.Stack
							})
							.buttonStyles()
							.fontSize(12)
							.clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#71B26C')
						Button('mode=NavigationMode.Split')
							.onClick(() => {
								this.mode = NavigationMode.Split
							})
							.buttonStyles()
							.fontSize(12)
							.clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#71B26C')
						Button('hideTitleBar=true')
							.onClick(() => {
								this.hideTitleBar = true
							})
							.buttonStyles()
							.fontSize(12)
							.clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#6CB2AC')
						Button('hideTitleBar=false')
							.onClick(() => {
								this.hideTitleBar = false
							})
							.buttonStyles()
							.fontSize(12)
							.clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#6CB2AC')

						Button('hideNavBar=true')
							.onClick(() => {
								this.hideNavBar = true
							})
							.buttonStyles()
							.fontSize(12)
							.clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#6CB2AC')
						Button('hideNavBar=false')
							.onClick(() => {
								this.hideNavBar = false
							})
							.buttonStyles()
							.fontSize(12)
							.clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#6CB2AC')

						Button('hideToolBar=true')
							.onClick(() => {
								this.hideToolBar = true
							})
							.buttonStyles()
							.fontSize(12)
							.clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#6CB2AC')
						Button('hideToolBar=false')
							.onClick(() => {
								this.hideToolBar = false
							})
							.buttonStyles()
							.fontSize(12)
							.clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#6CB2AC')
						Button('ExpandTop')
							.onClick(() => {
								this.edge = [LayoutSafeAreaEdge.TOP]
							})
							.buttonStyles()
							.fontSize(12)
							.clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#AD6CB2')
						Button('ExpandBottom')
							.onClick(() => {
								this.edge = [LayoutSafeAreaEdge.BOTTOM]
							})
							.buttonStyles()
							.fontSize(12)
							.clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#AD6CB2')
						Button('ExpandAll')
							.onClick(() => {
								this.edge = [LayoutSafeAreaEdge.TOP, LayoutSafeAreaEdge.BOTTOM]
							})
							.buttonStyles()
							.fontSize(12)
							.clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#AD6CB2')
						Button('ExpandNone')
							.buttonStyles()
							.fontSize(12)
							.onClick(() => {
								this.edge = []
							})
							.clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#AD6CB2')
						Button('ExpandTypeNone')
							.onClick(() => {
								this.type = []
							})
							.buttonStyles()
							.fontSize(12)
							.clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#AD6CB2')
						Button('ExpandTypeSystem')
							.onClick(() => {
								this.type = [LayoutSafeAreaType.SYSTEM]
							})
							.buttonStyles()
							.fontSize(12)
							.clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#AD6CB2')
						Button('paddingTop++')
							.onClick(() => {
								this.top++
							})
							.buttonStyles()
							.fontSize(12)
							.clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#B2786C')

						Button('paddingBottom++')
							.onClick(() => {
								this.bottom++
							})
							.buttonStyles()
							.fontSize(12)
							.clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#B2786C')

						Button('title：' + this.barStyle)
							.key('barStyle')
							.buttonStyles()
							.fontSize(12)
							.onClick(() => {
								if (this.barStyle == BarStyle.STANDARD) {
									this.barStyle = BarStyle.STACK;
								} else {
									this.barStyle = BarStyle.STANDARD;
								}
							}).margin({ top: 2, left: 20 }).backgroundColor('#AAB26C')

						Button('set safeAear CUTOUT')
							.buttonStyles()
							.fontSize(12)
							.onClick(()=>{
								this.type2 = [SafeAreaType.CUTOUT]
							})
						Button('set safeAear KEYBOARD')
							.buttonStyles()
							.fontSize(12)
							.onClick(()=>{
								this.type2 = [SafeAreaType.KEYBOARD]
							})
					}
				}
				.width('100%')
				.height('100%')
				.backgroundColor(Color.Red)
			}
			.expandSafeArea(this.type2,this.edge2)
			.padding({top:this.top, bottom:this.bottom, left:this.left, right:this.right})
			.margin(this.marginValue)
			.titleMode(this.titleMode)
			.hideTitleBar(this.hideTitleBar)
			.navBarWidth(this.navBarWidth)
			.hideToolBar(this.hideToolBar)
			.navDestination(this.PageMap)
			.backgroundColor(Color.Green)
			.title('NavTitle', {
				backgroundColor: '#90121314',
				backgroundBlurStyle:BlurStyle.BACKGROUND_THIN,
				barStyle: this.barStyle,
			})
			.hideNavBar(this.hideNavBar)
			.mode(this.mode)
			.ignoreLayoutSafeArea(this.type, this.edge)
			.toolbarConfiguration([
				{value: 'a'},
				{value: 'b'},
				{value: 'c'},
			], {
				backgroundColor: '#38182431',
			})
		}
}
