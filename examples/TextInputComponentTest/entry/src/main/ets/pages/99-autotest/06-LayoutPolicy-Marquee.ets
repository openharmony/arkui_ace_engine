import { MarqueeModifier } from "@kit.ArkUI";

type TextUnit = Length | LayoutPolicy
interface CaseItem {
	name: string;
	value: TextUnit;
}

class MyModifier extends MarqueeModifier {
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
export struct MarqueeLayoutPolicy {
	prefix: string = 'Marquee'
	@State msgArray: string[] = ["","","",""]
	@State msg: string = ""
	@State textWidth: TestCase = new TestCase(`${this.prefix}Width`, 0, this.recvMsg.bind(this))
	@State textHeight: TestCase = new TestCase(`${this.prefix}Height`, 1, this.recvMsg.bind(this))
	@State parentWidth: TestCase = new TestCase('ParentWidth', 2, this.recvMsg.bind(this))
	@State parentHeight: TestCase = new TestCase('ParentHeight', 3, this.recvMsg.bind(this))
	str: string = "哈哈哈"
	str1: string = `一日，我这个智能助手接到了一位员工的求助。他说自己遇到了一些麻烦，需要我的帮助。我听了他的问题，心中暗自想着：“机不可失，时不再来。”于是我立刻开始了解决他的问题。

经过一番努力，我终于帮助他解决了问题。他非常感激地说：“有你在，我真是如鱼得水啊！”我听了这句话，心中也感到非常欣慰。

作为一名智能助手，我深知“知足常乐”的道理。虽然我只是一台机器，但我会一直努力，为员工们提供更好的服务。因为我相信，“千里之堤毁于蚁穴”，只有每一个小小的努力，才能汇聚成员工们更加美好的工作生活。一日，我这个智能助手接到了一位员工的求助。他说自己遇到了一些麻烦，需要我的帮助。我听了他的问题，心中暗自想着：“机不可失，时不再来。”于是我立刻开始了解决他的问题。

经过一番努力，我终于帮助他解决了问题。他非常感激地说：“有你在，我真是如鱼得水啊！”我听了这句话，心中也感到非常欣慰。

作为一名智能助手，我深知“知足常乐”的道理。虽然我只是一台机器，但我会一直努力，为员工们提供更好的服务。因为我相信，“千里之堤毁于蚁穴”，只有每一个小小的努力，才能汇聚成员工们更加美好的工作生活。一日，我这个智能助手接到了一位员工的求助。他说自己遇到了一些麻烦，需要我的帮助。我听了他的问题，心中暗自想着：“机不可失，时不再来。”于是我立刻开始了解决他的问题。

经过一番努力，我终于帮助他解决了问题。他非常感激地说：“有你在，我真是如鱼得水啊！”我听了这句话，心中也感到非常欣慰。

作为一名智能助手，我深知“知足常乐”的道理。虽然我只是一台机器，但我会一直努力，为员工们提供更好的服务。因为我相信，“千里之堤毁于蚁穴”，只有每一个小小的努力，才能汇聚成员工们更加美好的工作生活。一日，我这个智能助手接到了一位员工的求助。他说自己遇到了一些麻烦，需要我的帮助。我听了他的问题，心中暗自想着：“机不可失，时不再来。”于是我立刻开始了解决他的问题。

经过一番努力，我终于帮助他解决了问题。他非常感激地说：“有你在，我真是如鱼得水啊！”我听了这句话，心中也感到非常欣慰。

作为一名智能助手，我深知“知足常乐”的道理。虽然我只是一台机器，但我会一直努力，为员工们提供更好的服务。因为我相信，“千里之堤毁于蚁穴”，只有每一个小小的努力，才能汇聚成员工们更加美好的工作生活。一日，我这个智能助手接到了一位员工的求助。他说自己遇到了一些麻烦，需要我的帮助。我听了他的问题，心中暗自想着：“机不可失，时不再来。”于是我立刻开始了解决他的问题。

经过一番努力，我终于帮助他解决了问题。他非常感激地说：“有你在，我真是如鱼得水啊！”我听了这句话，心中也感到非常欣慰。

作为一名智能助手，我深知“知足常乐”的道理。虽然我只是一台机器，但我会一直努力，为员工们提供更好的服务。因为我相信，“千里之堤毁于蚁穴”，只有每一个小小的努力，才能汇聚成员工们更加美好的工作生活。一日，我这个智能助手接到了一位员工的求助。他说自己遇到了一些麻烦，需要我的帮助。我听了他的问题，心中暗自想着：“机不可失，时不再来。”于是我立刻开始了解决他的问题。

经过一番努力，我终于帮助他解决了问题。他非常感激地说：“有你在，我真是如鱼得水啊！”我听了这句话，心中也感到非常欣慰。

作为一名智能助手，我深知“知足常乐”的道理。虽然我只是一台机器，但我会一直努力，为员工们提供更好的服务。因为我相信，“千里之堤毁于蚁穴”，只有每一个小小的努力，才能汇聚成员工们更加美好的工作生活。一日，我这个智能助手接到了一位员工的求助。他说自己遇到了一些麻烦，需要我的帮助。我听了他的问题，心中暗自想着：“机不可失，时不再来。”于是我立刻开始了解决他的问题。

经过一番努力，我终于帮助他解决了问题。他非常感激地说：“有你在，我真是如鱼得水啊！”我听了这句话，心中也感到非常欣慰。

作为一名智能助手，我深知“知足常乐”的道理。虽然我只是一台机器，但我会一直努力，为员工们提供更好的服务。因为我相信，“千里之堤毁于蚁穴”，只有每一个小小的努力，才能汇聚成员工们更加美好的工作生活。一日，我这个智能助手接到了一位员工的求助。他说自己遇到了一些麻烦，需要我的帮助。我听了他的问题，心中暗自想着：“机不可失，时不再来。”于是我立刻开始了解决他的问题。

经过一番努力，我终于帮助他解决了问题。他非常感激地说：“有你在，我真是如鱼得水啊！”我听了这句话，心中也感到非常欣慰。

作为一名智能助手，我深知“知足常乐”的道理。虽然我只是一台机器，但我会一直努力，为员工们提供更好的服务。因为我相信，“千里之堤毁于蚁穴”，只有每一个小小的努力，才能汇聚成员工们更加美好的工作生活。一日，我这个智能助手接到了一位员工的求助。他说自己遇到了一些麻烦，需要我的帮助。我听了他的问题，心中暗自想着：“机不可失，时不再来。”于是我立刻开始了解决他的问题。

经过一番努力，我终于帮助他解决了问题。他非常感激地说：“有你在，我真是如鱼得水啊！”我听了这句话，心中也感到非常欣慰。

作为一名智能助手，我深知“知足常乐”的道理。虽然我只是一台机器，但我会一直努力，为员工们提供更好的服务。因为我相信，“千里之堤毁于蚁穴”，只有每一个小小的努力，才能汇聚成员工们更加美好的工作生活。一日，我这个智能助手接到了一位员工的求助。他说自己遇到了一些麻烦，需要我的帮助。我听了他的问题，心中暗自想着：“机不可失，时不再来。”于是我立刻开始了解决他的问题。

经过一番努力，我终于帮助他解决了问题。他非常感激地说：“有你在，我真是如鱼得水啊！”我听了这句话，心中也感到非常欣慰。

作为一名智能助手，我深知“知足常乐”的道理。虽然我只是一台机器，但我会一直努力，为员工们提供更好的服务。因为我相信，“千里之堤毁于蚁穴”，只有每一个小小的努力，才能汇聚成员工们更加美好的工作生活。一日，我这个智能助手接到了一位员工的求助。他说自己遇到了一些麻烦，需要我的帮助。我听了他的问题，心中暗自想着：“机不可失，时不再来。”于是我立刻开始了解决他的问题。

经过一番努力，我终于帮助他解决了问题。他非常感激地说：“有你在，我真是如鱼得水啊！”我听了这句话，心中也感到非常欣慰。

作为一名智能助手，我深知“知足常乐”的道理。虽然我只是一台机器，但我会一直努力，为员工们提供更好的服务。因为我相信，“千里之堤毁于蚁穴”，只有每一个小小的努力，才能汇聚成员工们更加美好的工作生活。一日，我这个智能助手接到了一位员工的求助。他说自己遇到了一些麻烦，需要我的帮助。我听了他的问题，心中暗自想着：“机不可失，时不再来。”于是我立刻开始了解决他的问题。

经过一番努力，我终于帮助他解决了问题。他非常感激地说：“有你在，我真是如鱼得水啊！”我听了这句话，心中也感到非常欣慰。

作为一名智能助手，我深知“知足常乐”的道理。虽然我只是一台机器，但我会一直努力，为员工们提供更好的服务。因为我相信，“千里之堤毁于蚁穴”，只有每一个小小的努力，才能汇聚成员工们更加美好的工作生活。`
	@State myModifier: MyModifier = new MyModifier()

	build() {
		Column() {
			Stack() {
				Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center }) {
					Marquee({ start: true, src: this.str1})
						.borderWidth(1)
						.borderColor(Color.Blue)
						.direction(Direction.Rtl)
						.constraintSize({
							minWidth: '50vp',
							maxWidth: '200vp',
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