// return number between min and max
export function createRandomInteger(min: number, max: number): number {
  let range = max - min + 1;
  let value = Math.floor(Math.random() * range + min);
  return value;
}