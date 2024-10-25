export const useEnabled = <T>(enabled: boolean, value: T, defaultValue: T | undefined = undefined) => {
  return enabled ? value : defaultValue;
}

export function tagDesRule(title: string, radioName: string): string {
  return `开启了[${title}]调整为[${radioName}]`
}