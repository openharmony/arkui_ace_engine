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
@Component
export struct pageOneTmp {
	@Consume('pageInfos') pageInfos: NavPathStack

	pageId: number = 0;
	@State hideTitleBar:boolean=false
	@State barStyle: BarStyle = BarStyle.STANDARD
	@State Click: ClickEffectLevel=ClickEffectLevel.HEAVY
	@State top:number=0
	@State bottom:number=0
  @State edge: Array<LayoutSafeAreaEdge> = [];
  @State type: Array<LayoutSafeAreaType> = [];

	@State type2: Array<SafeAreaType> = [
		SafeAreaType.SYSTEM,
		SafeAreaType.CUTOUT,
		SafeAreaType.KEYBOARD
	];
	@State edge2: Array<SafeAreaEdge> = [
		SafeAreaEdge.TOP,
		SafeAreaEdge.BOTTOM,
		SafeAreaEdge.START,
		SafeAreaEdge.END
	];

	@State marginValue:number = 0

	build() {
		NavDestination() {
			Column({space: 5}) {
				Button('hideTitleBar=true')
					.key('hideTitleBar-one')
					.onClick(() => {
						this.hideTitleBar = true
					})
					.clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#6CB2AC')
				Button('ExpandTop').onClick(() => {
					this.edge = [LayoutSafeAreaEdge.TOP]
				}).clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#AD6CB2')
				Button('ExpandBottom').onClick(() => {
					this.edge = [LayoutSafeAreaEdge.BOTTOM]
				}).clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#AD6CB2')
				Button('ExpandAll').key('ExpandAll-one').onClick(() => {
					this.edge = [LayoutSafeAreaEdge.TOP, LayoutSafeAreaEdge.BOTTOM]
				}).clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#AD6CB2')
				Button('ExpandNone').onClick(() => {
					this.edge = []
				}).clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#AD6CB2')
				Button('ExpandTypeNone').onClick(() => {
					this.type = []
				}).clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#AD6CB2')
				Button('ExpandTypeSystem').key('ExpandTypeSystem-one').onClick(() => {
					this.type = [LayoutSafeAreaType.SYSTEM]
				}).clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#AD6CB2')

				Button('title：' + this.barStyle)
					.key('barStyle-one')
					.onClick(() => {
						if (this.barStyle == BarStyle.STANDARD) {
							this.barStyle = BarStyle.STACK;
						} else {
							this.barStyle = BarStyle.STANDARD;
						}
					}).margin({ top: 2, left: 20 })

				Button('margin++ :' + this.marginValue)
					.onClick(()=>{
						this.marginValue += 10
					})

				Button('margin-- :' + this.marginValue)
					.onClick(()=>{
						this.marginValue -= 10
					})
			}
			.height('100%')
			.backgroundColor(Color.Red)
		}
	  .margin(this.marginValue)
		.expandSafeArea(this.type2,this.edge2)
		.padding({top:this.top, bottom:this.bottom})
		.title('NavTitle', {
			backgroundColor: '#90121314',
			backgroundBlurStyle:BlurStyle.BACKGROUND_THIN,
			barStyle: this.barStyle,
		})
		.hideTitleBar(this.hideTitleBar)
		.backgroundColor(Color.Yellow)
		.ignoreLayoutSafeArea(this.type, this.edge)
	}
}