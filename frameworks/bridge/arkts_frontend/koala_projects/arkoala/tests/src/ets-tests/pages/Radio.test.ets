@Entry
@Component
struct RadioTest {
    options1: RadioOptions = { group: "", value: ""}
    options2: RadioOptions = { group: "Radio Group Name", value: "Radio Name" }
    style1: RadioStyle = { }
    style2: RadioStyle = { checkedBackgroundColor: Color.Green, uncheckedBorderColor: 333, indicatorColor: "#404040" }
    style3: RadioStyle = { checkedBackgroundColor: Color.Blue, uncheckedBorderColor: 777 }
    style4: RadioStyle = { checkedBackgroundColor: Color.White }

    build() {
        Radio(this.options1)
            .checked(false)
            .radioStyle(this.style1)
        Radio(this.options2)
            .checked(true)
            .radioStyle(this.style2)
        Radio(this.options1)
            .checked(false)
            .radioStyle(this.style3)
        Radio(this.options2)
            .checked(true)
            .radioStyle(this.style4)
    }
}
