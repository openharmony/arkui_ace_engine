@Entry
@Component
struct DollarDollar {
  @State n: number = 0.5
  @State s: string = "0.5"
  @State b: boolean = true
  @State d: Date = new Date('2021-08-08')
  @State m: PanelMode = PanelMode.Mini
  @State l: ListItemStyle = ListItemStyle.NONE

  build() {
    Column() {
      Slider({ value: this.n })
      Toggle({ type: ToggleType.Switch, isOn: $$(this.b) })
      Stepper({ index: this.n })
      Checkbox()
        .select($$(this.b))
      CheckboxGroup()
        .selectAll($$(this.b))
      DatePicker({ selected: $$(this.d) })
      TimePicker({ selected: $$(this.d) })
      MenuItem()
        .selected($$(this.b))
      Panel(false)
        .mode($$(this.m))
      Radio({group: "", value: ""})
        .checked($$(this.b))
      Search({ value: $$(this.s) })
      SideBarContainer(SideBarContainerType.Embed)
        .showSideBar($$(this.b))
      Swiper()
        .index($$(this.n))
      Tabs({ index: $$(this.n) })
      TextInput({ text: $$(this.s) })
      TextArea({ text: $$(this.s) })
      TextInput({ text: $$(this.s) })
      Toggle({ type: ToggleType.Checkbox, isOn: $$(this.b) })
      AlphabetIndexer({arrayValue: [], selected: $$(this.n) })
      Refresh({ refreshing: $$(this.b) })
      TextPicker({ range: [], value: $$(this.s), selected: $$(this.n) })
      Select([])
        .value($$(this.s))
        .selected($$(this.n))
      List() {
        ListItemGroup() {
          ListItem({ style: this.l })
            .selected($$(this.b))
        }
      }
      Grid() {
        GridItem({})
          .selected($$(this.b))
      }

      Button()
        .bindSheet($$(this.b), builder)
        .bindContentCover($$(this.b), builder)
    }
  }
}

@Builder
function builder() {
  Text()
}