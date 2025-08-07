import { LengthMetrics, SearchModifier } from "@kit.ArkUI";

type TextUnit = Length | LayoutPolicy
interface CaseItem {
	name: string;
	value: TextUnit;
}

class MyModifier extends SearchModifier {
	count: number = 0
	updateWidth(value: TextUnit) {
		this.width(value)
		this.count++
	}

	updateHeight(value: TextUnit) {
		this.height(value)
		this.count++
	}
}
class TestCase {
	policyArray: Array<CaseItem> = [
		{
			name: '100vp',
			value: '100vp'
		},
		{
			name: '100%',
			value: '100%'
		},
		{
			name: 'wrapContent',
			value: LayoutPolicy.wrapContent
		},
		{
			name: 'matchParent',
			value: LayoutPolicy.matchParent
		},
		{
			name: 'fixAtIdealSize',
			value: LayoutPolicy.fixAtIdealSize
		},
		{
			name: 'auto',
			value: 'auto'
		}
	]
	unit: TextUnit = '100vp';
	caseNumber: number = 0
	listener: Function | undefined = undefined
	name: string = ""
	index: number = 0

	constructor(name: string, index: number, listener: Function) {
		this.name = name
		this.index = index
		this.listener = listener
		this.output(`${this.name}: ${this.policyArray[this.caseNumber].name}`, this.index)
	}

	switchCase() {
		this.caseNumber++
		if (this.caseNumber > this.policyArray.length - 1) {
			this.caseNumber = 0
		}
		this.unit = this.policyArray[this.caseNumber].value
		this.output(`${this.name}: ${this.policyArray[this.caseNumber].name}`, this.index)
	}

	output(str: string, index: number) {
		if (this.listener) {
			this.listener(index, str)
		}
	}
}

@Component
export struct SearchLayoutPolicy {
	prefix: string = 'Search'
	@State msgArray: string[] = ["","","",""]
	@State msg: string = ""
	@State textWidth: TestCase = new TestCase(`${this.prefix}Width`, 0, this.recvMsg.bind(this))
	@State textHeight: TestCase = new TestCase(`${this.prefix}Height`, 1, this.recvMsg.bind(this))
	@State parentWidth: TestCase = new TestCase('ParentWidth', 2, this.recvMsg.bind(this))
	@State parentHeight: TestCase = new TestCase('ParentHeight', 3, this.recvMsg.bind(this))
	@State myModifier: MyModifier = new MyModifier()


	marginArray: Array<Margin | Length | LocalizedMargin | undefined> = [
		undefined, 1, {top: '5px', bottom: '5px'}, {top: LengthMetrics.vp(6), bottom: LengthMetrics.vp(6)}
	]
	@State myMargin: Margin | Length | LocalizedMargin | undefined = this.marginArray[0]

	marginIndex = 0
	@State text: string = 'Hello World!'
	@State fontSize: number = 16
	@State textAlign: TextAlign = TextAlign.Start
	@State textAligns: TextAlign[] = [
		TextAlign.Start,
		TextAlign.Center,
		TextAlign.End,
		TextAlign.JUSTIFY
	]
	@State textAlignStr: string[] = ['Start', 'Center', 'End', 'JUSTIFY']
	@State textAlignIndex: number = 0

	@State lineHeight: (string | number | Resource | null)[] = ['-1', '20%' , '20abc', '20fp', -40, 0, 40, null, $r('app.float.lineHeight_40'), $r('app.integer.lineHeight_40'), $r('app.string.lineHeight_40')]
	@State lineHeightStr: string[] = ['-1', '20%' , '20abc', '20fp', '-40', '0', '40', 'null', 'f_40', 'i_40', 's_40'];
	@State lineHeightIndex: number = 0

	@State halfleading: (boolean | undefined | null)[] = [false , true, undefined, null];
	@State halfleadingStr: string[] = ['false' , 'true', 'undefined', 'null'];
	@State halfleadingIndex: number = 0
	@State lineSpacingTest: number = -1


	build() {
		Column() {
			Stack() {
				Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center }) {
					Search({value: this.text})
						.searchButton("搜索")
						.cancelButton({
							style: CancelButtonStyle.INPUT,
							icon: {
								size: '14vp',
								src: $r('sys.media.ohos_ic_public_cancel_filled')
							}
						})
						.borderWidth(1)
						.borderColor(Color.Blue)
						.padding(0)
						.margin(0)
						.textFont({size: this.fontSize})
						.textAlign(this.textAlign)
						.lineHeight(this.lineHeight[this.lineHeightIndex])
						.halfLeading(this.halfleading[this.halfleadingIndex])
						.constraintSize({
							minWidth: '200vp',
							maxWidth: '300vp',
							minHeight: '200vp',
							maxHeight: '300vp'
						})
						.attributeModifier(this.myModifier)
				}.width(this.parentWidth.unit)
				.height(this.parentHeight.unit)
				.borderWidth(1)
				.borderColor(Color.Orange)
			}.height('60%').width('100%')

			Text(this.msg)
				.width('100%')
				.height('20%').fontSize('20fp')
				.fontWeight(FontWeight.Bold).textAlign(TextAlign.Start)

			Scroll() {
				Row() {
					Button(`${this.prefix}切换宽"`).onClick(() => {
						this.textWidth.switchCase()
						this.myModifier.updateWidth(this.textWidth.unit)
						this.marginIndex++;
						if (this.marginIndex > this.marginArray.length - 1) {
							this.marginIndex = 0
						}
						this.myMargin = this.marginArray[this.marginIndex]
					})
					Button(`${this.prefix}切换高`).onClick(() => {
						this.textHeight.switchCase()
						this.myModifier.updateHeight(this.textHeight.unit)
					})
					Button("父组件切换宽").onClick(() => {
						this.parentWidth.switchCase()
					})
					Button("父组件切换高").onClick(() => {
						this.parentHeight.switchCase()
					})
					Button("update textContent 空").onClick(() => {
						this.text = ''
					})
					Button("update textContent 超长文本").onClick(() => {
						this.text = '天底下没谁是欠你的,但是你欠了别人,就别不当回事。天底下没谁是欠你的,但是你欠了别人,就别不当回事。天底下没谁是欠你的,但是你欠了别人,就别不当回事。'
					})
					Button("update textContent 文本").onClick(() => {
						this.text = 'hello world!'
					})
					Button("fontSize++:" + this.fontSize).onClick(() => {
						this.fontSize++
					})
					Button("fontSize--:" + this.fontSize).onClick(() => {
						this.fontSize--
					})
					Button('TextAlign：' + this.textAlignStr[this.textAlignIndex]).onClick(()=> {
						this.textAlignIndex++
						if (this.textAlignIndex > this.textAligns.length - 1) {
							this.textAlignIndex = 0
						}
						this.textAlign = this.textAligns[this.textAlignIndex]
					})
					Button("lineHeight:" + this.lineHeightStr[this.lineHeightIndex])
						.onClick(() => {
							this.lineHeightIndex ++
							if (this.lineHeightIndex > (this.lineHeightStr.length - 1)) {
								this.lineHeightIndex = 0
							}
						})
					Button('halfleading:' + this.halfleadingStr[this.halfleadingIndex]).onClick(() => {
						this.halfleadingIndex ++
						if (this.halfleadingIndex > (this.halfleadingStr.length - 1)) {
							this.halfleadingIndex = 0
						}
					})
				}
			}.scrollable(ScrollDirection.Horizontal)
			.width('100%').height('20%')
		}
	}

	aboutToAppear(): void {

	}

	recvMsg(index: number, str: string) {
		this.msgArray[index] = str
		this.msg = this.msgArray.join("\n")
	}
}