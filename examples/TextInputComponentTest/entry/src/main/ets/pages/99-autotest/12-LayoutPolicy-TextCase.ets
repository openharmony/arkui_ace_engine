import { LengthMetrics, TextModifier } from "@kit.ArkUI";

type TextUnit = Length | LayoutPolicy
interface CaseItem {
	name: string;
	value: TextUnit;
}

class MyModifier extends TextModifier {
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
export struct TextLayoutPolicy {
	@State msgArray: string[] = ["","","",""]
	@State msg: string = ""
	@State textWidth: TestCase = new TestCase('TextWidth', 0, this.recvMsg.bind(this))
	@State textHeight: TestCase = new TestCase('TextHeight', 1, this.recvMsg.bind(this))
	@State parentWidth: TestCase = new TestCase('ParentWidth', 2, this.recvMsg.bind(this))
	@State parentHeight: TestCase = new TestCase('ParentHeight', 3, this.recvMsg.bind(this))
	@State myModifier: MyModifier = new MyModifier()

	@State textAlign: TextAlign = TextAlign.Start
	@State textAligns: TextAlign[] = [
		TextAlign.Start,
		TextAlign.Center,
		TextAlign.End,
		TextAlign.JUSTIFY
	]
	@State textAlignStr: string[] = ['Start', 'Center', 'End', 'JUSTIFY']
	@State textAlignIndex: number = 0
	@State text: string = 'Hello World!'

	@State lineHeight: (string | number | Resource | null)[] = ['-1', '20%' , '20abc', '20fp', -40, 0, 40, null, 40, 40, 40]
	@State lineHeightStr: string[] = ['-1', '20%' , '20abc', '20fp', '-40', '0', '40', 'null', 'f_40', 'i_40', 's_40'];
	@State lineHeightIndex: number = 0

	@State baselineOffsets: (string | number)[] = ['120%', '30abc', '30fp', -30, 0, 30];
	@State baselineOffsetsStr: string[] = ['120%', '30abc', '30fp', '-30', '0', '30'];
	@State baselineOffsetsIndex: number = 0

	@State lineSpacingTest: number = -1

	@State halfleading: (boolean | undefined | null)[] = [false , true, undefined, null];
	@State halfleadingStr: string[] = ['false' , 'true', 'undefined', 'null'];
	@State halfleadingIndex: number = 0


	build() {
		Column() {
			Stack() {
				Column() {
					Text(this.text)
						.width(this.textWidth.unit)
						.height(this.textHeight.unit)
						.borderWidth(1)
						.borderColor(Color.Blue)
						.textAlign(this.textAlign)
						.lineHeight(this.lineHeight[this.lineHeightIndex])
						.baselineOffset(this.baselineOffsets[this.baselineOffsetsIndex])
						.lineSpacing(LengthMetrics.vp(this.lineSpacingTest))
						.halfLeading(this.halfleading[this.halfleadingIndex])
						.constraintSize({
							minWidth: '200vp',
							maxWidth: '300vp',
							minHeight: '100vp',
							maxHeight: '300vp'
						})
						.ignoreLayoutSafeArea([LayoutSafeAreaType.SYSTEM], [LayoutSafeAreaEdge.ALL])
				}.width(this.parentWidth.unit)
				.height(this.parentHeight.unit)
				.borderWidth(1)
				.borderColor(Color.Orange)
			}.height('60%').width('100%')

			TextArea({text: this.msg})
				.width('100%')
				.height('20%').fontSize('20fp')
				.fontWeight(FontWeight.Bold).textAlign(TextAlign.Start)

			Scroll() {
				Row() {
					Button("Text切换宽").onClick(() => {
						this.textWidth.switchCase()
						this.myModifier.updateWidth(this.textWidth.unit)
					})
					Button("Text切换高").onClick(() => {
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
						this.text = '天底下没谁是欠你的,但是你欠了别人,就别不当回事。天底下没谁是欠你的,但是你欠了别人,就别不当回事。'
					})
					Button("update textContent 文本").onClick(() => {
						this.text = 'hello world!'
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
					Button("baselineOffset:" + this.baselineOffsetsStr[this.baselineOffsetsIndex])
						.onClick(() => {
							this.baselineOffsetsIndex ++
							if (this.baselineOffsetsIndex > (this.baselineOffsetsStr.length - 1)) {
								this.baselineOffsetsIndex = 0
							}
						})
					Button('lineSpacing+,' + this.lineSpacingTest)
						.width('40%').fontSize('13vp')
						.onClick(() => {
							this.lineSpacingTest += 10
						}).margin(2)

					Button('lineSpacing-,' + this.lineSpacingTest)
						.width('40%')
						.fontSize('13vp')
						.onClick(() => {
							this.lineSpacingTest -= 10
						}).margin(2)
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