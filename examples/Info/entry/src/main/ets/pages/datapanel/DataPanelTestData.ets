// 定义要测试的属性以及类型
export interface TestAttributes {
  trackShadow?: DataPanelShadowOptions
  strokeWidth?: Length
  trackBackgroundColor?: ResourceColor
  valueColors?: Array<ResourceColor | LinearGradient>
  closeEffect?: boolean
  linearGradient?: boolean
}

// 初始化测试数据
export const testData: TestAttributes[] = [
  {},
  {
    valueColors: undefined,
    trackShadow: undefined,
    trackBackgroundColor: undefined,
    strokeWidth: undefined,
    closeEffect: undefined
  },
  {
    valueColors: [Color.Green, $r('app.color.yellow'), '#fff10303', 0XFF03CDF1],
    trackShadow: { radius: 10, offsetX: 20, offsetY: 20 },
    trackBackgroundColor: Color.Red,
    strokeWidth: '50%',
    closeEffect: false
  },
  {
    valueColors: ['rgb(11,236,85)'],
    trackBackgroundColor: $r('app.color.rColor1'),
    trackShadow: { radius: -5, offsetX: -20, offsetY: -20 },
    strokeWidth: 200,
    closeEffect: true
  },
  {
    valueColors: ['rgba(255, 100, 255, 0.5)', '#e6f60202', '#2f06f3d7', $r('app.color.yellow'), Color.Black, Color.Blue,
      0xe67c02f6],
    trackBackgroundColor: 0xBBFFFF,
    trackShadow: { radius: 100, offsetX: 200, offsetY: 200 },
    strokeWidth: '50px',
    closeEffect: false
  },
  {
    valueColors: ['#e6f60202', '#2f06f3d7', $r('app.color.yellow'), Color.Black, Color.Blue, 0xe67c02f6],
    trackBackgroundColor: '#ffeca908',
    trackShadow: { radius: 20.1, offsetX: 20.1, offsetY: 20.1 },
    strokeWidth: 5,
    closeEffect: true
  },
  {
    valueColors:
    [new LinearGradient([{ color: '#ffeca908', offset: -10 }, { color: 'rgba(49, 239, 16, 1.00)', offset: 11 }]),
      new LinearGradient([{ color: '#FF67F9D4', offset: '0.6' },
        { color: '#FFFF9554', offset: $r('app.color.rColor1') }]), '#00FF00', '#20FF0000'],
    trackBackgroundColor: 'rgb(255, 100, 255)',
    trackShadow: {
      radius: $r('app.string.rRadius'),
      offsetX: $r('app.string.rOffset'),
      offsetY: $r('app.string.rOffset'),
      colors: [new LinearGradient([{ color: '#65EEC9A3', offset: 0 }, { color: '#65EF629F', offset: 1 }]),
        new LinearGradient([{ color: $r('app.color.yellow'), offset: 0 }, { color: 0x65efbd0, offset: 10 }]),
        new LinearGradient([{ color: '#6572B513', offset: 0 }, { color: '#6508efa6', offset: 0.41 }]),
        new LinearGradient([{ color: '#65ed08f5', offset: 0 }, { color: '#65ef0849', offset: 1 }])
      ]
    },
    strokeWidth: $r('app.string.string_15vp'),
    closeEffect: true,
    linearGradient: true,
  },
  {
    valueColors: ['hhh'],
    trackBackgroundColor: 'adsdasdf',
    trackShadow: { radius: 0, offsetX: 0, offsetY: 0 },
    strokeWidth: 'saddsfgdcasd',
    closeEffect: true
  },
  {
    valueColors: [],
    trackBackgroundColor: 'adsdasdf',
    trackShadow: { radius: 0, offsetX: 0, offsetY: 0 },
    strokeWidth: '200',
    closeEffect: true
  },
]