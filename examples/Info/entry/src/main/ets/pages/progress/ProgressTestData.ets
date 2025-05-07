// 定义要测试的属性以及类型
export interface TestAttributes {
  style?: ProgressStyleOptions | CapsuleStyleOptions |
  RingStyleOptions | LinearStyleOptions | ScaleRingStyleOptions | EclipseStyleOptions;
  color?: ResourceColor | LinearGradient | undefined | null | string;
  value?: number | undefined | null;
}

export const testData: TestAttributes[] = [
  {
    value: 90,
    color: Color.Red,
    style: {
      strokeWidth: -10, // 默认值：4.0vp
      scaleCount: 60, // 默认值：120
      scaleWidth: 2, // 默认值：2.0vp
      enableSmoothEffect: true,
    }
  },
  {
    value: 100,
    color: new LinearGradient([{ color: Color.Orange, offset: 0.3 }, { color: Color.Green, offset: 0.5 },
      { color: Color.Red, offset: 2 }]),
    style: {
      strokeWidth: 60,
      scaleCount: -10,
      scaleWidth: '4vp',
      enableSmoothEffect: true,
    }
  },
  {
    value: 0,
    color: null,
    style: {
      strokeWidth: '20vp',
      scaleCount: 120,
      scaleWidth: '4px',
      enableSmoothEffect: true,
    }
  },
  {
    value: 20,
    color: 0xffa500,
    style: {
      strokeWidth: '20px',
      scaleCount: 150,
      scaleWidth: '4fp',
      enableSmoothEffect: true,
    }
  },
  {
    value: -10,
    color: '#00CED1',
    style: {
      strokeWidth: '20fp',
      scaleCount: 240,
      scaleWidth: '4lpx',
      enableSmoothEffect: true,
    }
  },
  {
    value: undefined,
    color: '#ff4B0082',
    style: {
      strokeWidth: '20lpx',
      scaleCount: 30,
      scaleWidth: -5,
      enableSmoothEffect: true,
    }
  },
  {
    value: 120,
    color: undefined,
    style: {
      strokeWidth: 'aaa',
      scaleCount: 10,
      scaleWidth: 10,
      enableSmoothEffect: true,
    },
  },
  {
    value: null,
    color: 'rgb(255, 100, 255)',
    style: {
      strokeWidth: '30%',
      scaleCount: 50,
      scaleWidth: $r('app.string.20fp'),
      enableSmoothEffect: true,
    },
  },
  {
    value: 80,
    color: 'rgba(255, 100, 255, 0.5)',
    style: {
      strokeWidth: undefined,
      scaleCount: 90,
      scaleWidth: $r('app.float.float_fu20'),
      enableSmoothEffect: true,
    },
  },
  {
    value: 88.8,
    color: $r('app.color.purple'),
    style: {
      strokeWidth: $r('app.float.float_30_6'),
      scaleCount: 100,
      scaleWidth: 200,
      enableSmoothEffect: true,
    },
  }
]